macro_line|#ifndef _SOCKET_H
DECL|macro|_SOCKET_H
mdefine_line|#define _SOCKET_H
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
r_int
id|socket
c_func
(paren
r_int
id|family
comma
r_int
id|type
comma
r_int
id|protocol
)paren
suffix:semicolon
r_int
id|socketpair
c_func
(paren
r_int
id|family
comma
r_int
id|type
comma
r_int
id|protocol
comma
r_int
id|sockvec
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_int
id|bind
c_func
(paren
r_int
id|sockfd
comma
r_struct
id|sockaddr
op_star
id|my_addr
comma
r_int
id|addrlen
)paren
suffix:semicolon
r_int
id|connect
c_func
(paren
r_int
id|sockfd
comma
r_struct
id|sockaddr
op_star
id|serv_addr
comma
r_int
id|addrlen
)paren
suffix:semicolon
r_int
id|listen
c_func
(paren
r_int
id|sockfd
comma
r_int
id|backlog
)paren
suffix:semicolon
r_int
id|accept
c_func
(paren
r_int
id|sockfd
comma
r_struct
id|sockaddr
op_star
id|peer
comma
r_int
op_star
id|paddrlen
)paren
suffix:semicolon
r_int
id|getsockname
c_func
(paren
r_int
id|sockfd
comma
r_struct
id|sockaddr
op_star
id|addr
comma
r_int
op_star
id|paddrlen
)paren
suffix:semicolon
r_int
id|getpeername
c_func
(paren
r_int
id|sockfd
comma
r_struct
id|sockaddr
op_star
id|peer
comma
r_int
op_star
id|paddrlen
)paren
suffix:semicolon
macro_line|#endif /* _SOCKET_H */
eof
