multiline_comment|/* $Id: advansys.h,v 1.10 1996/01/15 04:51:06 bobf Exp bobf $ */
multiline_comment|/*&n; * advansys.h - Linux Host Driver for AdvanSys SCSI Adapters&n; *&n; * Copyright (c) 1995-1996 Advanced System Products, Inc.&n; *&n; * This driver may be modified and freely distributed provided that&n; * the above copyright message and this comment are included in the&n; * distribution. The latest version of this driver is available at&n; * the AdvanSys FTP and BBS sites listed below.&n; *&n; * Please send questions, comments, and bug reports to:&n; * bobf@advansys.com (Bob Frey)&n; */
macro_line|#ifndef _ADVANSYS_H
DECL|macro|_ADVANSYS_H
mdefine_line|#define _ADVANSYS_H
multiline_comment|/* The driver can be used in Linux 1.2.X or 1.3.X. */
macro_line|#if !defined(LINUX_1_2) &amp;&amp; !defined(LINUX_1_3)
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#if LINUX_VERSION_CODE &gt; 65536 + 3 * 256
DECL|macro|LINUX_1_3
mdefine_line|#define LINUX_1_3
macro_line|#else /* LINUX_VERSION_CODE */
DECL|macro|LINUX_1_2
mdefine_line|#define LINUX_1_2
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#endif /* !defined(LINUX_1_2) &amp;&amp; !defined(LINUX_1_3) */
multiline_comment|/*&n; * Scsi_Host_Template function prototypes.&n; */
r_int
id|advansys_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|advansys_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|advansys_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|advansys_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|advansys_queuecommand
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
id|advansys_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|advansys_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#ifdef LINUX_1_2
r_int
id|advansys_biosparam
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
(braket
)braket
)paren
suffix:semicolon
macro_line|#else /* LINUX_1_3 */
r_int
id|advansys_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_advansys
suffix:semicolon
r_int
id|advansys_proc_info
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
macro_line|#endif /* LINUX_1_3 */
multiline_comment|/* init/main.c setup function */
r_void
id|advansys_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * AdvanSys Host Driver Scsi_Host_Template (struct SHT) from hosts.h.&n; */
macro_line|#ifdef LINUX_1_2
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* struct SHT *next */ &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* int *usage_count */ &bslash;&n;&t;&quot;advansys&quot;,&t;&t;&t;&t;/* char *name */ &bslash;&n;&t;advansys_detect,&t;&t;/* int (*detect)(struct SHT *) */ &bslash;&n;&t;advansys_release,&t;&t;/* int (*release)(struct Scsi_Host *) */ &bslash;&n;&t;advansys_info,&t;&t;&t;/* const char *(*info)(struct Scsi_Host *) */ &bslash;&n;&t;advansys_command, &t;&t;/* int (*command)(Scsi_Cmnd *) */ &bslash;&n;&t;advansys_queuecommand, &bslash;&n;&t;&t;&t;/* int (*queuecommand)(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *)) */ &bslash;&n;&t;advansys_abort,&t;&t;&t;/* int (*abort)(Scsi_Cmnd *) */ &bslash;&n;&t;advansys_reset,&t;&t;&t;/* int (*reset)(Scsi_Cmnd *) */ &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* int (*slave_attach)(int, int) */ &bslash;&n;&t;advansys_biosparam,&t;&t;/* int (* bios_param)(Disk *, int, int []) */ &bslash;&n;&t;/* &bslash;&n;&t; * The following fields are set per adapter in advansys_detect(). &bslash;&n;&t; */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* int can_queue */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* int this_id */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* short unsigned int sg_tablesize */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* short cmd_per_lun */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* unsigned char present */&t;&bslash;&n;&t;/* &bslash;&n;&t; * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;&t; * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;&t; * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;&t; */ &bslash;&n;&t;1,&t;&t;&t;&t;&t;&t;/* unsigned unchecked_isa_dma:1 */ &bslash;&n;&t;/* &bslash;&n;&t; * All adapters controlled by this driver are capable of large &bslash;&n;&t; * scatter-gather lists. This apparently obviates any performance&n;&t; * gain provided by setting &squot;use_clustering&squot;. &bslash;&n;&t; */ &bslash;&n;&t;DISABLE_CLUSTERING,&t;&t;/* unsigned use_clustering:1 */ &bslash;&n;}
macro_line|#else /* LINUX_1_3 */
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* struct SHT *next */ &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* long *usage_count */ &bslash;&n;&t;&amp;proc_scsi_advansys,&t;/* struct proc_dir_entry *proc_dir */ &bslash;&n;&t;advansys_proc_info,&t;&bslash;&n;&t;&t;&t;/* int (*proc_info)(char *, char **, off_t, int, int, int) */ &bslash;&n;&t;&quot;advansys&quot;,&t;&t;&t;&t;/* const char *name */ &bslash;&n;&t;advansys_detect,&t;&t;/* int (*detect)(struct SHT *) */ &bslash;&n;&t;advansys_release,&t;&t;/* int (*release)(struct Scsi_Host *) */ &bslash;&n;&t;advansys_info,&t;&t;&t;/* const char *(*info)(struct Scsi_Host *) */ &bslash;&n;&t;advansys_command, &t;&t;/* int (*command)(Scsi_Cmnd *) */ &bslash;&n;&t;advansys_queuecommand, &bslash;&n;&t;&t;&t;/* int (*queuecommand)(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *)) */ &bslash;&n;&t;advansys_abort,&t;&t;&t;/* int (*abort)(Scsi_Cmnd *) */ &bslash;&n;&t;advansys_reset,&t;&t;&t;/* int (*reset)(Scsi_Cmnd *) */ &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;/* int (*slave_attach)(int, int) */ &bslash;&n;&t;advansys_biosparam,&t;&t;/* int (* bios_param)(Disk *, kdev_t, int []) */ &bslash;&n;&t;/* &bslash;&n;&t; * The following fields are set per adapter in advansys_detect(). &bslash;&n;&t; */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* int can_queue */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* int this_id */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* short unsigned int sg_tablesize */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* short cmd_per_lun */ &bslash;&n;&t;0,&t;&t;&t;&t;&t;&t;/* unsigned char present */&t;&bslash;&n;&t;/* &bslash;&n;&t; * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;&t; * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;&t; * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;&t; */ &bslash;&n;&t;1,&t;&t;&t;&t;&t;&t;/* unsigned unchecked_isa_dma:1 */ &bslash;&n;&t;/* &bslash;&n;&t; * All adapters controlled by this driver are capable of large &bslash;&n;&t; * scatter-gather lists. This apparently obviates any performance&n;&t; * gain provided by setting &squot;use_clustering&squot;. &bslash;&n;&t; */ &bslash;&n;&t;DISABLE_CLUSTERING,&t;&t;/* unsigned use_clustering:1 */ &bslash;&n;}
macro_line|#endif /* LINUX_1_3 */
macro_line|#endif /* _ADVANSYS_H */
eof
