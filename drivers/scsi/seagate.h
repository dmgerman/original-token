multiline_comment|/*&n; *&t;seagate.h Copyright (C) 1992 Drew Eckhardt &n; *&t;low level scsi driver header for ST01/ST02 by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SEAGATE_H
DECL|macro|SEAGATE_H
mdefine_line|#define SEAGATE_H
multiline_comment|/*&n;&t;$Header&n;*/
macro_line|#ifndef ASM
r_int
id|seagate_st0x_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_queue_command
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
id|seagate_st0x_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|seagate_st0x_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#include &lt;linux/kdev_t.h&gt;
r_int
id|seagate_st0x_biosparam
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
DECL|macro|SEAGATE_ST0X
mdefine_line|#define SEAGATE_ST0X  {  NULL, NULL, NULL, NULL, &bslash;&n;&t;&t;&t; NULL, seagate_st0x_detect, &t;&bslash;&n;&t;&t;&t; NULL, &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t; seagate_st0x_info, seagate_st0x_command,  &t;&bslash;&n;&t;&t;&t; seagate_st0x_queue_command, seagate_st0x_abort, &bslash;&n;&t;&t;&t; seagate_st0x_reset, NULL, seagate_st0x_biosparam, &bslash;&n;&t;&t;&t; 1, 7, SG_ALL, 1, 0, 0, DISABLE_CLUSTERING}
macro_line|#endif /* ASM */
macro_line|#endif /* _SEAGATE_H */
eof
