macro_line|#ifndef _IN2000_H
multiline_comment|/* $Id: in2000.h,v 1.1 1994/03/14 06:27:38 root Exp root $&n; *&n; * Header file for the Always IN 2000 driver for Linux&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
multiline_comment|/* The IN-2000 is based on a WD33C93 */
DECL|macro|INSTAT
mdefine_line|#define&t;INSTAT&t;(base + 0x0)&t;/* R: Auxiliary Status; W: register select */
DECL|macro|INDATA
mdefine_line|#define&t;INDATA&t;(base + 0x1)&t;/* R/W: Data port */
DECL|macro|INFIFO
mdefine_line|#define&t;INFIFO&t;(base + 0x2)&t;/* R/W FIFO, Word access only */
DECL|macro|INREST
mdefine_line|#define&t;INREST&t;(base + 0x3)&t;/* W: Reset everything */
DECL|macro|INFCNT
mdefine_line|#define&t;INFCNT&t;(base + 0x4)&t;/* R: FIFO byte count */
DECL|macro|INFRST
mdefine_line|#define&t;INFRST&t;(base + 0x5)&t;/* W: Reset Fifo count and to write */
DECL|macro|INFWRT
mdefine_line|#define&t;INFWRT&t;(base + 0x7)&t;/* W: Set FIFO to read */
DECL|macro|INFLED
mdefine_line|#define&t;INFLED&t;(base + 0x8)&t;/* W: Set LED; R: Dip Switch settings */
DECL|macro|INNLED
mdefine_line|#define&t;INNLED&t;(base + 0x9)&t;/* W: reset LED */
DECL|macro|INVERS
mdefine_line|#define&t;INVERS&t;(base + 0xa)&t;/* R: Read hw version, end-reset */
DECL|macro|ININTR
mdefine_line|#define&t;ININTR&t;(base + 0xc)&t;/* W: Interrupt Mask Port */
DECL|macro|G2CNTRL_HRDY
mdefine_line|#define G2CNTRL_HRDY&t;0x20&t;&t;/* Sets HOST ready */
multiline_comment|/* WD33C93 defines */
DECL|macro|OWNID
mdefine_line|#define&t;OWNID&t;0
DECL|macro|CONTROL
mdefine_line|#define&t;CONTROL&t;1
DECL|macro|TIMEOUT
mdefine_line|#define&t;TIMEOUT&t;2
DECL|macro|TOTSECT
mdefine_line|#define&t;TOTSECT&t;3
DECL|macro|TOTHEAD
mdefine_line|#define&t;TOTHEAD&t;4
DECL|macro|TOTCYLH
mdefine_line|#define&t;TOTCYLH 5
DECL|macro|TOTCYLL
mdefine_line|#define&t;TOTCYLL&t;6
DECL|macro|LADRSHH
mdefine_line|#define&t;LADRSHH&t;7
DECL|macro|LADRSHL
mdefine_line|#define&t;LADRSHL&t;8
DECL|macro|LADRSLH
mdefine_line|#define&t;LADRSLH&t;9
DECL|macro|LADRSLL
mdefine_line|#define&t;LADRSLL&t;10
DECL|macro|SECTNUM
mdefine_line|#define&t;SECTNUM&t;11
DECL|macro|HEADNUM
mdefine_line|#define&t;HEADNUM&t;12
DECL|macro|CYLNUMH
mdefine_line|#define&t;CYLNUMH&t;13
DECL|macro|CYLNUML
mdefine_line|#define&t;CYLNUML&t;14
DECL|macro|TARGETU
mdefine_line|#define&t;TARGETU&t;15
DECL|macro|CMDPHAS
mdefine_line|#define&t;CMDPHAS&t;16
DECL|macro|SYNCTXR
mdefine_line|#define&t;SYNCTXR&t;17
DECL|macro|TXCNTH
mdefine_line|#define&t;TXCNTH&t;18
DECL|macro|TXCNTM
mdefine_line|#define&t;TXCNTM&t;19
DECL|macro|TXCNTL
mdefine_line|#define TXCNTL&t;20
DECL|macro|DESTID
mdefine_line|#define DESTID&t;21
DECL|macro|SRCID
mdefine_line|#define&t;SRCID&t;22
DECL|macro|SCSIST
mdefine_line|#define&t;SCSIST&t;23
DECL|macro|COMMAND
mdefine_line|#define&t;COMMAND&t;24
DECL|macro|WDDATA
mdefine_line|#define&t;WDDATA&t;25
DECL|macro|AUXSTAT
mdefine_line|#define&t;AUXSTAT&t;31
multiline_comment|/* OWNID Register Bits */
DECL|macro|OWN_EAF
mdefine_line|#define&t;OWN_EAF&t;0x08
DECL|macro|OWN_EHP
mdefine_line|#define&t;OWN_EHP&t;0x10
DECL|macro|OWN_FS0
mdefine_line|#define&t;OWN_FS0&t;0x40
DECL|macro|OWN_FS1
mdefine_line|#define&t;OWN_FS1&t;0x80
multiline_comment|/* AUX Register Bits */
DECL|macro|AUX_DBR
mdefine_line|#define&t;AUX_DBR&t;0
DECL|macro|AUX_PE
mdefine_line|#define&t;AUX_PE&t;1
DECL|macro|AUX_CIP
mdefine_line|#define&t;AUX_CIP&t;0x10
DECL|macro|AUX_BSY
mdefine_line|#define&t;AUX_BSY&t;0x20
DECL|macro|AUX_LCI
mdefine_line|#define&t;AUX_LCI&t;0x40
DECL|macro|AUX_INT
mdefine_line|#define&t;AUX_INT&t;0x80
multiline_comment|/* Select timeout const, 1 count = 8ms */
DECL|macro|IN2000_TMOUT
mdefine_line|#define IN2000_TMOUT 0x1f
macro_line|#if 0
multiline_comment|/* This is used with scatter-gather */
r_struct
id|in2000_chain
(brace
id|ulong
id|dataptr
suffix:semicolon
multiline_comment|/* Location of data */
id|ulong
id|datalen
suffix:semicolon
multiline_comment|/* Size of this part of chain */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* These belong in scsi.h also */
DECL|macro|any2scsi
mdefine_line|#define any2scsi(up, p)&t;&t;&t;&t;&bslash;&n;(up)[0] = (((unsigned long)(p)) &gt;&gt; 16);&t;&t;&bslash;&n;(up)[1] = (((unsigned long)(p)) &gt;&gt; 8);&t;&t;&bslash;&n;(up)[2] = ((unsigned long)(p));
DECL|macro|scsi2int
mdefine_line|#define scsi2int(up) ( ((((long)*(up))&amp;0x1f) &lt;&lt; 16) + (((long)(up)[1]) &lt;&lt; 8) + ((long)(up)[2]) )
DECL|macro|xany2scsi
mdefine_line|#define xany2scsi(up, p)&t;&bslash;&n;(up)[0] = ((long)(p)) &gt;&gt; 24;&t;&bslash;&n;(up)[1] = ((long)(p)) &gt;&gt; 16;&t;&bslash;&n;(up)[2] = ((long)(p)) &gt;&gt; 8;&t;&bslash;&n;(up)[3] = ((long)(p));
DECL|macro|xscsi2int
mdefine_line|#define xscsi2int(up) ( (((long)(up)[0]) &lt;&lt; 24) + (((long)(up)[1]) &lt;&lt; 16) &bslash;&n;&t;&t;      + (((long)(up)[2]) &lt;&lt;  8) +  ((long)(up)[3]) )
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|macro|MAX_SENSE
mdefine_line|#define MAX_SENSE 14
DECL|macro|MAX_STATUS
mdefine_line|#define MAX_STATUS 32
r_static
r_int
id|in2000_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|in2000_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|in2000_queuecommand
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
r_static
r_int
id|in2000_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|in2000_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|in2000_biosparam
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/* next may be &quot;SG_NONE&quot; or &quot;SG_ALL&quot; or nr. of (1k) blocks per R/W Cmd. */
DECL|macro|IN2000_SG
mdefine_line|#define IN2000_SG SG_ALL
DECL|macro|IN2000
mdefine_line|#define IN2000 {NULL, &quot;Always IN2000&quot;, in2000_detect, NULL,&t;&bslash;&n;&t;&t;NULL, in2000_command,&t;&t;&bslash;&n;&t;&t;in2000_queuecommand,&t;&t;&bslash;&n;&t;&t;in2000_abort,&t;&t;&t;&bslash;&n;&t;&t;in2000_reset,&t;&t;&t;&bslash;&n;&t;        NULL,&t;&t;                &bslash;&n;&t;&t;in2000_biosparam,               &bslash;&n;&t;&t;1, 7, IN2000_SG, 1, 0, 0}
macro_line|#endif
eof
