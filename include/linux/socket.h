macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
DECL|struct|sockaddr
r_struct
id|sockaddr
(brace
DECL|member|sa_family
id|u_short
id|sa_family
suffix:semicolon
multiline_comment|/* address family, AF_xxx */
DECL|member|sa_data
r_char
id|sa_data
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* 14 bytes of protocol address */
)brace
suffix:semicolon
multiline_comment|/*&n; * socket types&n; */
DECL|macro|SOCK_STREAM
mdefine_line|#define SOCK_STREAM&t;1&t;&t;/* stream (connection) socket */
DECL|macro|SOCK_DGRAM
mdefine_line|#define SOCK_DGRAM&t;2&t;&t;/* datagram (connectionless) socket */
DECL|macro|SOCK_SEQPACKET
mdefine_line|#define SOCK_SEQPACKET&t;3&t;&t;/* sequential packet socket */
DECL|macro|SOCK_RAW
mdefine_line|#define SOCK_RAW&t;4&t;&t;/* raw socket */
multiline_comment|/*&n; * supported address families&n; */
DECL|macro|AF_UNSPEC
mdefine_line|#define AF_UNSPEC&t;0
DECL|macro|AF_UNIX
mdefine_line|#define AF_UNIX&t;&t;1
DECL|macro|AF_INET
mdefine_line|#define AF_INET&t;&t;2
multiline_comment|/*&n; * protocol families, same as address families&n; */
DECL|macro|PF_UNIX
mdefine_line|#define PF_UNIX&t;&t;AF_UNIX
DECL|macro|PF_INET
mdefine_line|#define PF_INET&t;&t;AF_INET
macro_line|#endif
eof
