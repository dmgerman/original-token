macro_line|#ifndef _ATP870U_H
multiline_comment|/* $Id: atp870u.h,v 1.0 1997/05/07 15:09:00 root Exp root $&n;&n; * Header file for the ACARD 870U/W driver for Linux&n; *&n; * $Log: atp870u.h,v $&n; * Revision 1.0  1997/05/07  15:09:00  root&n; * Initial revision&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
multiline_comment|/* I/O Port */
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|macro|MAX_SENSE
mdefine_line|#define MAX_SENSE 14
r_int
id|atp870u_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|atp870u_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|atp870u_queuecommand
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
id|atp870u_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|atp870u_reset
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
id|atp870u_biosparam
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
r_void
id|send_s870
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
DECL|macro|qcnt
mdefine_line|#define qcnt            32
DECL|macro|ATP870U_SCATTER
mdefine_line|#define ATP870U_SCATTER 127
DECL|macro|ATP870U_CMDLUN
mdefine_line|#define ATP870U_CMDLUN 1
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
r_extern
r_const
r_char
op_star
id|atp870u_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atp870u_proc_info
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
DECL|macro|ATP870U
mdefine_line|#define ATP870U {  &t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&t;&t;&quot;atp870u&quot;,&t;&t;&bslash;&n;&t;proc_info:&t;&t;&t;atp870u_proc_info,      &bslash;&n;&t;name:&t;&t;&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;detect:                 &t;atp870u_detect,&t;&t;&bslash;&n;&t;release:               &t; &t;NULL,                   &bslash;&n;&t;info:                   &t;atp870u_info,           &bslash;&n;&t;command:                &t;atp870u_command,&t;&bslash;&n;        queuecommand:           &t;atp870u_queuecommand,&t;&bslash;&n;        eh_strategy_handler: &t;&t;NULL,&t;&t;&t;&bslash;&n;        eh_abort_handler: &t;&t;NULL,&t;&t;&t;&bslash;&n;        eh_device_reset_handler:&t;NULL,&t;&t;&t;&bslash;&n;        eh_bus_reset_handler:&t;&t;NULL,&t;&t;&t;&bslash;&n;        eh_host_reset_handler:&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;abort:&t;&t;&t;&t;atp870u_abort,          &bslash;&n;&t;reset:&t;&t;&t;&t;atp870u_reset,       &t;&bslash;&n;&t;slave_attach:               &t;NULL,                   &bslash;&n;&t;bios_param:                     atp870u_biosparam,&t;&bslash;&n;&t;can_queue:                     &t;qcnt,                   &bslash;&n;&t;this_id:                     &t;1,&t;&t;&t;&bslash;&n;&t;sg_tablesize:                   ATP870U_SCATTER,        &bslash;&n;&t;cmd_per_lun:                    ATP870U_CMDLUN,         &bslash;&n;&t;present:                     &t;0,                      &bslash;&n;&t;unchecked_isa_dma:              0,                      &bslash;&n;&t;use_clustering:                 ENABLE_CLUSTERING,&t;&bslash;&n;&t;use_new_eh_code:&t;&t;0&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof
