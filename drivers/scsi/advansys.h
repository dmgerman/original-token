multiline_comment|/* $Id: advansys.h,v 1.6 1997/05/30 19:25:12 davem Exp $ */
multiline_comment|/*&n; * advansys.h - Linux Host Driver for AdvanSys SCSI Adapters&n; * &n; * Copyright (c) 1995-1997 Advanced System Products, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * There is an AdvanSys Linux WWW page at:&n; *  http://www.advansys.com/linux.html&n; *&n; * The latest version of the AdvanSys driver is available at:&n; *  ftp://ftp.advansys.com/pub/linux&n; *&n; * Please send questions, comments, bug reports to:&n; * bobf@advansys.com (Bob Frey)&n; */
macro_line|#ifndef _ADVANSYS_H
DECL|macro|_ADVANSYS_H
mdefine_line|#define _ADVANSYS_H
multiline_comment|/* Convert Linux Version, Patch-level, Sub-level to LINUX_VERSION_CODE. */
DECL|macro|ASC_LINUX_VERSION
mdefine_line|#define ASC_LINUX_VERSION(V, P, S)    (((V) * 65536) + ((P) * 256) + (S))
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif /* LINUX_VERSION_CODE */
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
comma
r_int
r_int
)paren
suffix:semicolon
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
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;&t;&t;&t;proc_dir:     &amp;proc_scsi_advansys,&t; &bslash;&n;&t;&t;&t;proc_info:    advansys_proc_info,&t; &bslash;&n;&t;&t;&t;name:         &quot;advansys&quot;,&t;&t; &bslash;&n;&t;&t;&t;detect:       advansys_detect,&t;&t; &bslash;&n;&t;&t;&t;release:      advansys_release,&t;         &bslash;&n;&t;&t;&t;info:         advansys_info,&t;&t; &bslash;&n;&t;&t;&t;command:      advansys_command, &t; &bslash;&n;&t;&t;&t;queuecommand: advansys_queuecommand,     &bslash;&n;&t;&t;&t;abort:        advansys_abort,&t;&t; &bslash;&n;&t;&t;&t;reset:        advansys_reset,&t;&t; &bslash;&n;&t;&t;&t;bios_param:    advansys_biosparam,&t; &bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t; * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;&t; * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;&t; * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;&t;unchecked_isa_dma: 1,&t;&t;&t; &bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t; * All adapters controlled by this driver are capable of large &bslash;&n;&t; * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;&t; * this obviates any performance gain provided by setting &bslash;&n;&t; * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;&t; * by enabling clustering, I/O throughput increases as well. &bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;&t;use_clustering: ENABLE_CLUSTERING,&t; &bslash;&n;}
macro_line|#endif /* _ADVANSYS_H */
eof
