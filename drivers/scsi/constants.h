macro_line|#ifndef _CONSTANTS_H
DECL|macro|_CONSTANTS_H
mdefine_line|#define _CONSTANTS_H
r_extern
r_void
id|print_command
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|print_msg
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* extern void print_sense(const char *,  Scsi_Cmnd *); */
r_extern
r_void
id|print_status
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|print_Scsi_Cmnd
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif /* def _CONSTANTS_H */
eof
