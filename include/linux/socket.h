macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
DECL|struct|sockaddr
r_struct
id|sockaddr
(brace
DECL|member|sa_family
r_int
r_int
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
DECL|macro|SOCK_RAW
mdefine_line|#define SOCK_RAW&t;3&t;&t;/* raw socket */
DECL|macro|SOCK_RDM
mdefine_line|#define SOCK_RDM&t;4&t;&t;/* reliably-delivered message */
DECL|macro|SOCK_SEQPACKET
mdefine_line|#define SOCK_SEQPACKET&t;5&t;&t;/* sequential packet socket */
DECL|macro|SOCK_PACKET
mdefine_line|#define SOCK_PACKET    10&t;&t;/* linux specific way of getting&n;&t;&t;&t;&t;&t;   packets at the dev level.  For&n;&t;&t;&t;&t;&t;   writing rarp and other similiar&n;&t;&t;&t;&t;&t;   things on the user level. */
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
multiline_comment|/* flags we can use with send/ and recv. */
DECL|macro|MSG_OOB
mdefine_line|#define MSG_OOB&t;&t;1
DECL|macro|MSG_PEEK
mdefine_line|#define MSG_PEEK&t;2
multiline_comment|/* for setsockoptions */
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;1
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;2
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;3
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;4
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;5
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;6
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;7
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;8
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;9
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE   10
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK    11
multiline_comment|/* setsockoptions level */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;1
macro_line|#endif /* _LINUX_SOCKET_H */
eof
