multiline_comment|/*  Driver for the PPA3 parallel port SCSI HBA embedded in &n; * the Iomega ZIP drive&n; * &n; * (c) 1996     Grant R. Guenther  grant@torque.net&n; */
macro_line|#ifndef _PPA_H
DECL|macro|_PPA_H
mdefine_line|#define _PPA_H
DECL|macro|PPA_VERSION
mdefine_line|#define   PPA_VERSION   &quot;Curtin 1-08-BETA&quot;
multiline_comment|/* This driver reqires a 1.3.37 kernel or higher!! */
multiline_comment|/* Use the following to enable certain chipset support&n; * Default is PEDANTIC = 3&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_SCSI_PPA_HAVE_PEDANTIC
DECL|macro|CONFIG_SCSI_PPA_HAVE_PEDANTIC
mdefine_line|#define CONFIG_SCSI_PPA_HAVE_PEDANTIC&t;3
macro_line|#endif
macro_line|#ifndef CONFIG_SCSI_PPA_EPP_TIME
DECL|macro|CONFIG_SCSI_PPA_EPP_TIME
mdefine_line|#define CONFIG_SCSI_PPA_EPP_TIME&t;64
macro_line|#endif
multiline_comment|/* ------ END OF USER CONFIGURABLE PARAMETERS ----- */
macro_line|#include  &lt;linux/stddef.h&gt;
macro_line|#include  &lt;linux/module.h&gt;
macro_line|#include  &lt;linux/kernel.h&gt;
macro_line|#include  &lt;linux/tqueue.h&gt;
macro_line|#include  &lt;linux/ioport.h&gt;
macro_line|#include  &lt;linux/delay.h&gt;
macro_line|#include  &lt;linux/proc_fs.h&gt;
macro_line|#include  &lt;linux/stat.h&gt;
macro_line|#include  &lt;linux/blk.h&gt;
macro_line|#include  &lt;asm/io.h&gt;
macro_line|#include  &quot;sd.h&quot;
macro_line|#include  &quot;hosts.h&quot;
macro_line|#include  &lt;linux/parport.h&gt;
multiline_comment|/* batteries not included :-) */
DECL|macro|PPA_INITIATOR
mdefine_line|#define&t;PPA_INITIATOR&t;7
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
comma
r_int
r_int
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
r_static
r_int
id|ppa_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#ifndef&t;MODULE
macro_line|#ifdef&t;PPA_CODE
DECL|macro|SKIP_PROC_DIR
mdefine_line|#define SKIP_PROC_DIR
macro_line|#endif
macro_line|#endif
macro_line|#ifndef SKIP_PROC_DIR
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
macro_line|#endif /* !PPA_CODE =&gt; hosts.c */
DECL|macro|PPA
mdefine_line|#define PPA {&t;/* next */&t; &t;0, &bslash;&n;&t;&t;/* usage_count */&t;0, &bslash;&n;&t;&t;/* proc_dir */&t;&t;&amp;proc_scsi_ppa, &bslash;&n;&t;&t;/* proc_info */&t;&t;ppa_proc_info, &bslash;&n;&t;&t;/* name */&t;&t;&quot;Iomega ZIP/JAZ Traveller&quot;, &bslash;&n;&t;&t;/* detect */&t;&t;ppa_detect, &bslash;&n;&t;&t;/* release */&t;&t;ppa_release, &bslash;&n;&t;&t;/* info */&t;&t;0, &bslash;&n;&t;&t;/* command */&t;&t;ppa_command, &bslash;&n;&t;&t;/* queuecommand */&t;ppa_queuecommand, &bslash;&n;&t;&t;/* abort */&t;&t;ppa_abort, &bslash;&n;&t;&t;/* reset */&t;&t;ppa_reset, &bslash;&n;&t;&t;/* slave_attach */&t;0, &bslash;&n;&t;&t;/* bios_param */&t;ppa_biosparam, &bslash;&n;&t;&t;/* can_queue */&t;&t;0, &bslash;&n;&t;&t;/* this_id */&t;&t;PPA_INITIATOR, &bslash;&n;&t;&t;/* sg_tablesize */&t;SG_ALL, &bslash;&n;&t;&t;/* cmd_per_lun */&t;1, &bslash;&n;&t;&t;/* present */&t;&t;0, &bslash;&n;&t;&t;/* unchecked_isa_dma */&t;0, &bslash;&n;&t;&t;/* use_clustering */&t;ENABLE_CLUSTERING &bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _PPA_H */
eof
