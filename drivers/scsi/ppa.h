multiline_comment|/*  Driver for the PPA3 parallel port SCSI HBA embedded in &n; * the Iomega ZIP drive&n; * &n; * (c) 1996     Grant R. Guenther  grant@torque.net&n; *&t;&t;David Campbell&t;   campbell@torque.net&n; *&n; *&t;All comments to David.&n; */
macro_line|#ifndef _PPA_H
DECL|macro|_PPA_H
mdefine_line|#define _PPA_H
DECL|macro|PPA_VERSION
mdefine_line|#define   PPA_VERSION   &quot;2.01&quot;
multiline_comment|/* &n; * this driver has been hacked by Matteo Frigo (athena@theory.lcs.mit.edu)&n; * to support EPP and scatter-gather.                        [0.26-athena]&n; *&n; * additional hacks by David Campbell&n; * in response to this driver &quot;mis-behaving&quot; on his machine.&n; *      Fixed EPP to handle &quot;software&quot; changing of EPP port data direction.&n; *      Chased down EPP timeouts&n; *      Made this driver &quot;kernel version friendly&quot;           [0.28-athena]&n; *&n; * [ Stuff removed ]&n; *&n; * Corrected ppa.h for 2.1.x kernels (&gt;=2.1.85)&n; * Modified &quot;Nat Semi Kludge&quot; for extended chipsets&n; *&t;&t;&t;&t;&t;&t;&t;[1.41]&n; *&n; * Fixed id_probe for EPP 1.9 chipsets (misdetected as EPP 1.7)&n; *&t;&t;&t;&t;&t;&t;&t;[1.42]&n; *&n; * Development solely for 2.1.x kernels from now on!&n; *&t;&t;&t;&t;&t;&t;&t;[2.00]&n; *&n; * Hack and slash at the init code (EPP device check routine)&n; * Added INSANE option.&n; *&t;&t;&t;&t;&t;&t;&t;[2.01]&n; *&n; * Patch applied to sync against the 2.1.x kernel code&n; * Included qboot_zip.sh&n; *&t;&t;&t;&t;&t;&t;&t;[2.02]&n; */
multiline_comment|/* ------ END OF USER CONFIGURABLE PARAMETERS ----- */
macro_line|#ifdef PPA_CODE
macro_line|#include  &lt;linux/stddef.h&gt;
macro_line|#include  &lt;linux/module.h&gt;
macro_line|#include  &lt;linux/kernel.h&gt;
macro_line|#include  &lt;linux/tqueue.h&gt;
macro_line|#include  &lt;linux/ioport.h&gt;
macro_line|#include  &lt;linux/delay.h&gt;
macro_line|#include  &lt;linux/proc_fs.h&gt;
macro_line|#include  &lt;linux/stat.h&gt;
macro_line|#include  &lt;linux/blk.h&gt;
macro_line|#include  &lt;linux/sched.h&gt;
macro_line|#include  &lt;linux/interrupt.h&gt;
macro_line|#include  &lt;asm/io.h&gt;
macro_line|#include  &quot;sd.h&quot;
macro_line|#include  &quot;hosts.h&quot;
multiline_comment|/* batteries not included :-) */
multiline_comment|/*&n; * modes in which the driver can operate &n; */
DECL|macro|PPA_AUTODETECT
mdefine_line|#define   PPA_AUTODETECT        0&t;/* Autodetect mode                */
DECL|macro|PPA_NIBBLE
mdefine_line|#define   PPA_NIBBLE            1&t;/* work in standard 4 bit mode    */
DECL|macro|PPA_PS2
mdefine_line|#define   PPA_PS2               2&t;/* PS/2 byte mode         */
DECL|macro|PPA_EPP_8
mdefine_line|#define   PPA_EPP_8             3&t;/* EPP mode, 8 bit                */
DECL|macro|PPA_EPP_16
mdefine_line|#define   PPA_EPP_16            4&t;/* EPP mode, 16 bit               */
DECL|macro|PPA_EPP_32
mdefine_line|#define   PPA_EPP_32            5&t;/* EPP mode, 32 bit               */
DECL|macro|PPA_UNKNOWN
mdefine_line|#define   PPA_UNKNOWN           6&t;/* Just in case...                */
DECL|variable|PPA_MODE_STRING
r_static
r_char
op_star
id|PPA_MODE_STRING
(braket
)braket
op_assign
(brace
l_string|&quot;Autodetect&quot;
comma
l_string|&quot;SPP&quot;
comma
l_string|&quot;PS/2&quot;
comma
l_string|&quot;EPP 8 bit&quot;
comma
l_string|&quot;EPP 16 bit&quot;
comma
l_string|&quot;EPP 32 bit&quot;
comma
l_string|&quot;Unknown&quot;
)brace
suffix:semicolon
multiline_comment|/* This is a global option */
DECL|variable|ppa_sg
r_int
id|ppa_sg
op_assign
id|SG_ALL
suffix:semicolon
multiline_comment|/* enable/disable scatter-gather. */
multiline_comment|/* other options */
DECL|macro|PPA_CAN_QUEUE
mdefine_line|#define PPA_CAN_QUEUE   1&t;/* use &quot;queueing&quot; interface */
DECL|macro|PPA_BURST_SIZE
mdefine_line|#define PPA_BURST_SIZE&t;512&t;/* data burst size */
DECL|macro|PPA_SELECT_TMO
mdefine_line|#define PPA_SELECT_TMO  5000&t;/* how long to wait for target ? */
DECL|macro|PPA_SPIN_TMO
mdefine_line|#define PPA_SPIN_TMO    50000&t;/* ppa_wait loop limiter */
DECL|macro|PPA_DEBUG
mdefine_line|#define PPA_DEBUG&t;0&t;/* debuging option */
DECL|macro|IN_EPP_MODE
mdefine_line|#define IN_EPP_MODE(x) (x == PPA_EPP_8 || x == PPA_EPP_16 || x == PPA_EPP_32)
multiline_comment|/* args to ppa_connect */
DECL|macro|CONNECT_EPP_MAYBE
mdefine_line|#define CONNECT_EPP_MAYBE 1
DECL|macro|CONNECT_NORMAL
mdefine_line|#define CONNECT_NORMAL  0
multiline_comment|/* INSANE code */
DECL|macro|PPA_INSANE
mdefine_line|#define PPA_INSANE 0
macro_line|#if PPA_INSANE &gt; 0
DECL|macro|r_dtr
mdefine_line|#define r_dtr(x)        (unsigned char)inb_p((x))
DECL|macro|r_str
mdefine_line|#define r_str(x)        (unsigned char)inb_p((x)+1)
DECL|macro|r_ctr
mdefine_line|#define r_ctr(x)        (unsigned char)inb_p((x)+2)
DECL|macro|r_epp
mdefine_line|#define r_epp(x)        (unsigned char)inb_p((x)+4)
DECL|macro|r_fifo
mdefine_line|#define r_fifo(x)       (unsigned char)inb_p((x)+0x400)
DECL|macro|r_ecr
mdefine_line|#define r_ecr(x)        (unsigned char)inb_p((x)+0x402)
DECL|macro|w_dtr
mdefine_line|#define w_dtr(x,y)      outb_p(y, (x))
DECL|macro|w_str
mdefine_line|#define w_str(x,y)      outb_p(y, (x)+1)
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)      outb_p(y, (x)+2)
DECL|macro|w_epp
mdefine_line|#define w_epp(x,y)      outb_p(y, (x)+4)
DECL|macro|w_fifo
mdefine_line|#define w_fifo(x,y)     outb_p(y, (x)+0x400)
DECL|macro|w_ecr
mdefine_line|#define w_ecr(x,y)      outb_p(y, (x)+0x402)
macro_line|#else /* PPA_INSANE */
DECL|macro|r_dtr
mdefine_line|#define r_dtr(x)        (unsigned char)inb((x))
DECL|macro|r_str
mdefine_line|#define r_str(x)        (unsigned char)inb((x)+1)
DECL|macro|r_ctr
mdefine_line|#define r_ctr(x)        (unsigned char)inb((x)+2)
DECL|macro|r_epp
mdefine_line|#define r_epp(x)        (unsigned char)inb((x)+4)
DECL|macro|r_fifo
mdefine_line|#define r_fifo(x)       (unsigned char)inb((x)+0x400)
DECL|macro|r_ecr
mdefine_line|#define r_ecr(x)        (unsigned char)inb((x)+0x402)
DECL|macro|w_dtr
mdefine_line|#define w_dtr(x,y)      outb(y, (x))
DECL|macro|w_str
mdefine_line|#define w_str(x,y)      outb(y, (x)+1)
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)      outb(y, (x)+2)
DECL|macro|w_epp
mdefine_line|#define w_epp(x,y)      outb(y, (x)+4)
DECL|macro|w_fifo
mdefine_line|#define w_fifo(x,y)     outb(y, (x)+0x400)
DECL|macro|w_ecr
mdefine_line|#define w_ecr(x,y)      outb(y, (x)+0x402)
macro_line|#endif&t;/* PPA_INSANE */
r_static
r_int
id|ppa_engine
c_func
(paren
id|ppa_struct
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|ppa_in
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|ppa_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
id|ppa_interrupt
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|ppa_out
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|proc_scsi_ppa
r_struct
id|proc_dir_entry
id|proc_scsi_ppa
op_assign
(brace
id|PROC_SCSI_PPA
comma
l_int|3
comma
l_string|&quot;ppa&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
)brace
suffix:semicolon
macro_line|#else
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_ppa
suffix:semicolon
DECL|macro|ppa_release
mdefine_line|#define ppa_release 0
macro_line|#endif
r_int
id|ppa_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|ppa_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|ppa_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ppa_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|ppa_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ppa_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ppa_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|ppa_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|PPA
mdefine_line|#define PPA {&t;proc_dir:&t;&t;&t;&amp;proc_scsi_ppa,&t;&t;&bslash;&n;&t;&t;proc_info:&t;&t;&t;ppa_proc_info,&t;&t;&bslash;&n;&t;&t;name:&t;&t;&t;&t;&quot;Iomega parport ZIP drive&quot;,&bslash;&n;&t;&t;detect:&t;&t;&t;&t;ppa_detect,&t;&t;&bslash;&n;&t;&t;release:&t;&t;&t;ppa_release,&t;&t;&bslash;&n;&t;&t;command:&t;&t;&t;ppa_command,&t;&t;&bslash;&n;&t;&t;queuecommand:&t;&t;&t;ppa_queuecommand,&t;&bslash;&n;&t;&t;eh_abort_handler:&t;&t;ppa_abort,&t;&t;&bslash;&n;&t;&t;eh_device_reset_handler:&t;NULL,&t;&t;&t;&bslash;&n;&t;&t;eh_bus_reset_handler:&t;&t;ppa_reset,&t;&t;&bslash;&n;&t;&t;eh_host_reset_handler:&t;&t;ppa_reset,&t;&t;&bslash;&n;&t;&t;bios_param:&t;&t;&t;ppa_biosparam,&t;&t;&bslash;&n;&t;&t;this_id:&t;&t;&t;-1,&t;&t;&t;&bslash;&n;&t;&t;sg_tablesize:&t;&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;&t;&t;cmd_per_lun:&t;&t;&t;1,&t;&t;&t;&bslash;&n;&t;&t;use_clustering:&t;&t;&t;ENABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _PPA_H */
eof
