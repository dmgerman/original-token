multiline_comment|/*&n; * QLogic ISP1020 Intelligent SCSI Processor Driver (PCI)&n; * Written by Erik H. Moe, ehm@cris.com&n; * Copyright 1995, Erik H. Moe&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
multiline_comment|/* Renamed and updated to 1.3.x by Michael Griffith &lt;grif@cs.ucr.edu&gt; */
multiline_comment|/*&n; * $Date: 1995/09/22 02:32:56 $&n; * $Revision: 0.5 $&n; *&n; * $Log: isp1020.h,v $&n; * Revision 0.5  1995/09/22  02:32:56  root&n; * do auto request sense&n; *&n; * Revision 0.4  1995/08/07  04:48:28  root&n; * supply firmware with driver.&n; * numerous bug fixes/general cleanup of code.&n; *&n; * Revision 0.3  1995/07/16  16:17:16  root&n; * added reset/abort code.&n; *&n; * Revision 0.2  1995/06/29  03:19:43  root&n; * fixed biosparam.&n; * added queue protocol.&n; *&n; * Revision 0.1  1995/06/25  01:56:13  root&n; * Initial release.&n; *&n; */
macro_line|#ifndef _QLOGICISP_H
DECL|macro|_QLOGICISP_H
mdefine_line|#define _QLOGICISP_H
r_int
id|isp1020_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|isp1020_release
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
id|isp1020_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|isp1020_queuecommand
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
id|isp1020_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|isp1020_reset
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
id|isp1020_biosparam
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
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL (0)
macro_line|#endif
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_isp1020
suffix:semicolon
DECL|macro|QLOGICISP
mdefine_line|#define QLOGICISP {&t;&t;&t;&t;&t;&bslash;&n;&t;/* next */&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;/* usage_count */&t;NULL,&t;&t;&t;&bslash;&n;        /* proc dir */          NULL,                   &bslash;&n;        /* procfs info */       NULL,                   &bslash;&n;&t;/* name */&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;/* detect */&t;&t;isp1020_detect,&t;&t;&bslash;&n;&t;/* release */&t;&t;isp1020_release,&t;&bslash;&n;&t;/* info */&t;&t;isp1020_info,&t;&t;&bslash;&n;&t;/* command */&t;&t;NULL,&t;&t; &t;&bslash;&n;&t;/* queuecommand */&t;isp1020_queuecommand,&t;&bslash;&n;&t;/* abort */&t;&t;isp1020_abort,&t;&t;&bslash;&n;&t;/* reset */&t;&t;isp1020_reset,&t;&t;&bslash;&n;&t;/* slave_attach */&t;NULL,&t;&t;&t;&bslash;&n;&t;/* bios_param */&t;isp1020_biosparam,&t;&bslash;&n;&t;/* can_queue */&t;&t;8,&t;&t;&t;&bslash;&n;&t;/* this_id */&t;&t;-1,&t;&t;&t;&bslash;&n;&t;/* sg_tablesize */&t;4,&t;&t;&t;&bslash;&n;&t;/* cmd_per_lun */&t;1,&t;&t;&t;&bslash;&n;&t;/* present */&t;&t;0,&t;&t;&t;&bslash;&n;&t;/* unchecked_isa_dma */&t;0,&t;&t;&t;&bslash;&n;&t;/* use_clustering */&t;DISABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif /* _QLOGICISP_H */
eof
