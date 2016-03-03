multiline_comment|/*&n; * QLogic ISP2100 SCSI-FCP&n; * &n; * Written by Erik H. Moe, ehm@cris.com&n; * Copyright 1995, Erik H. Moe&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
multiline_comment|/* Renamed and updated to 1.3.x by Michael Griffith &lt;grif@cs.ucr.edu&gt; */
multiline_comment|/* This is a version of the isp1020 driver which was modified by&n; * Chris Loveland &lt;cwl@iol.unh.edu&gt; to support the isp2100&n; */
multiline_comment|/*&n; * $Date: 1995/09/22 02:32:56 $&n; * $Revision: 0.5 $&n; *&n; * $Log: isp1020.h,v $&n; * Revision 0.5  1995/09/22  02:32:56  root&n; * do auto request sense&n; *&n; * Revision 0.4  1995/08/07  04:48:28  root&n; * supply firmware with driver.&n; * numerous bug fixes/general cleanup of code.&n; *&n; * Revision 0.3  1995/07/16  16:17:16  root&n; * added reset/abort code.&n; *&n; * Revision 0.2  1995/06/29  03:19:43  root&n; * fixed biosparam.&n; * added queue protocol.&n; *&n; * Revision 0.1  1995/06/25  01:56:13  root&n; * Initial release.&n; *&n; */
macro_line|#ifndef _QLOGICFC_H
DECL|macro|_QLOGICFC_H
mdefine_line|#define _QLOGICFC_H
multiline_comment|/*&n; * With the qlogic interface, every queue slot can hold a SCSI&n; * command with up to 2 scatter/gather entries.  If we need more&n; * than 2 entries, continuation entries can be used that hold&n; * another 5 entries each.  Unlike for other drivers, this means&n; * that the maximum number of scatter/gather entries we can&n; * support at any given time is a function of the number of queue&n; * slots available.  That is, host-&gt;can_queue and host-&gt;sg_tablesize&n; * are dynamic and _not_ independent.  This all works fine because&n; * requests are queued serially and the scatter/gather limit is&n; * determined for each queue request anew.&n; */
DECL|macro|QLOGICFC_REQ_QUEUE_LEN
mdefine_line|#define QLOGICFC_REQ_QUEUE_LEN&t;63&t;/* must be power of two - 1 */
DECL|macro|QLOGICFC_MAX_SG
mdefine_line|#define QLOGICFC_MAX_SG(ql)&t;(2 + (((ql) &gt; 0) ? 5*((ql) - 1) : 0))
DECL|macro|QLOGICFC_CMD_PER_LUN
mdefine_line|#define QLOGICFC_CMD_PER_LUN    8
r_int
id|isp2100_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|isp2100_release
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
id|isp2100_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|isp2100_queuecommand
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
id|isp2100_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|isp2100_reset
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
id|isp2100_biosparam
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
id|proc_scsi_isp2100
suffix:semicolon
DECL|macro|QLOGICFC
mdefine_line|#define QLOGICFC {&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;        detect:                 isp2100_detect,                            &bslash;&n;        release:                isp2100_release,                           &bslash;&n;        info:                   isp2100_info,                              &bslash;&n;        queuecommand:           isp2100_queuecommand,                      &bslash;&n;        abort:                  isp2100_abort,                             &bslash;&n;        reset:                  isp2100_reset,                             &bslash;&n;        bios_param:             isp2100_biosparam,                         &bslash;&n;        can_queue:              QLOGICFC_REQ_QUEUE_LEN,                    &bslash;&n;        this_id:                -1,                                        &bslash;&n;        sg_tablesize:           QLOGICFC_MAX_SG(QLOGICFC_REQ_QUEUE_LEN),   &bslash;&n;        cmd_per_lun:            QLOGICFC_CMD_PER_LUN,                      &bslash;&n;        present:                0,                                         &bslash;&n;        unchecked_isa_dma:      0,                                         &bslash;&n;        use_clustering:         DISABLE_CLUSTERING                         &bslash;&n;}
macro_line|#endif /* _QLOGICFC_H */
eof
