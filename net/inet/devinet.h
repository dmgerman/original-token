multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the INET bits of the interfaces handler.&n; *&n; */
macro_line|#ifndef _DEVINET_H
DECL|macro|_DEVINET_H
mdefine_line|#define _DEVINET_H
macro_line|#ifndef _DEV_H
macro_line|#include &quot;dev.h&quot;
macro_line|#endif
r_extern
r_int
id|ip_addr_match
c_func
(paren
r_int
r_int
id|addr1
comma
r_int
r_int
id|addr2
)paren
suffix:semicolon
r_extern
r_int
id|chk_addr
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|dev_check
c_func
(paren
r_int
r_int
id|daddr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|my_addr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* _DEVINET_H */
eof
