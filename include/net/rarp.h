multiline_comment|/* linux/net/inet/rarp.h */
macro_line|#ifndef _RARP_H
DECL|macro|_RARP_H
mdefine_line|#define _RARP_H
r_extern
r_int
id|rarp_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|rarp_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
suffix:semicolon
macro_line|#endif&t;/* _RARP_H */
eof
