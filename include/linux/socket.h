macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
macro_line|#include &lt;linux/sockios.h&gt;&t;&t;/* the SIOCxxx I/O controls&t;*/
DECL|struct|sockaddr
r_struct
id|sockaddr
(brace
DECL|member|sa_family
r_int
r_int
id|sa_family
suffix:semicolon
multiline_comment|/* address family, AF_xxx&t;*/
DECL|member|sa_data
r_char
id|sa_data
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* 14 bytes of protocol address&t;*/
)brace
suffix:semicolon
DECL|struct|linger
r_struct
id|linger
(brace
DECL|member|l_onoff
r_int
id|l_onoff
suffix:semicolon
multiline_comment|/* Linger active&t;&t;*/
DECL|member|l_linger
r_int
id|l_linger
suffix:semicolon
multiline_comment|/* How long to linger for&t;*/
)brace
suffix:semicolon
multiline_comment|/* Socket types. */
DECL|macro|SOCK_STREAM
mdefine_line|#define SOCK_STREAM&t;1&t;&t;/* stream (connection) socket&t;*/
DECL|macro|SOCK_DGRAM
mdefine_line|#define SOCK_DGRAM&t;2&t;&t;/* datagram (conn.less) socket&t;*/
DECL|macro|SOCK_RAW
mdefine_line|#define SOCK_RAW&t;3&t;&t;/* raw socket&t;&t;&t;*/
DECL|macro|SOCK_RDM
mdefine_line|#define SOCK_RDM&t;4&t;&t;/* reliably-delivered message&t;*/
DECL|macro|SOCK_SEQPACKET
mdefine_line|#define SOCK_SEQPACKET&t;5&t;&t;/* sequential packet socket&t;*/
DECL|macro|SOCK_PACKET
mdefine_line|#define SOCK_PACKET&t;10&t;&t;/* linux specific way of&t;*/
multiline_comment|/* getting packets at the dev&t;*/
multiline_comment|/* level.  For writing rarp and&t;*/
multiline_comment|/* other similar things on the&t;*/
multiline_comment|/* user level.&t;&t;&t;*/
multiline_comment|/* Supported address families. */
DECL|macro|AF_UNSPEC
mdefine_line|#define AF_UNSPEC&t;0
DECL|macro|AF_UNIX
mdefine_line|#define AF_UNIX&t;&t;1
DECL|macro|AF_INET
mdefine_line|#define AF_INET&t;&t;2
DECL|macro|AF_AX25
mdefine_line|#define AF_AX25&t;&t;3
DECL|macro|AF_IPX
mdefine_line|#define AF_IPX&t;&t;4
DECL|macro|AF_MAX
mdefine_line|#define AF_MAX&t;&t;8&t;/* For now.. */
multiline_comment|/* Protocol families, same as address families. */
DECL|macro|PF_UNSPEC
mdefine_line|#define PF_UNSPEC&t;AF_UNSPEC
DECL|macro|PF_UNIX
mdefine_line|#define PF_UNIX&t;&t;AF_UNIX
DECL|macro|PF_INET
mdefine_line|#define PF_INET&t;&t;AF_INET
DECL|macro|PF_AX25
mdefine_line|#define PF_AX25&t;&t;AF_AX25
DECL|macro|PF_IPX
mdefine_line|#define PF_IPX&t;&t;AF_IPX
DECL|macro|PF_MAX
mdefine_line|#define PF_MAX&t;&t;AF_MAX
multiline_comment|/* Flags we can use with send/ and recv. */
DECL|macro|MSG_OOB
mdefine_line|#define MSG_OOB&t;&t;1
DECL|macro|MSG_PEEK
mdefine_line|#define MSG_PEEK&t;2
DECL|macro|MSG_DONTROUTE
mdefine_line|#define MSG_DONTROUTE&t;4
multiline_comment|/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;1
DECL|macro|SOL_IP
mdefine_line|#define SOL_IP&t;&t;0
DECL|macro|SOL_IPX
mdefine_line|#define SOL_IPX&t;&t;256
DECL|macro|SOL_AX25
mdefine_line|#define SOL_AX25&t;257
DECL|macro|SOL_TCP
mdefine_line|#define SOL_TCP&t;&t;6
DECL|macro|SOL_UDP
mdefine_line|#define SOL_UDP&t;&t;17
multiline_comment|/* For setsockoptions(2) */
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
mdefine_line|#define SO_OOBINLINE&t;10
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK&t;11
DECL|macro|SO_PRIORITY
mdefine_line|#define SO_PRIORITY&t;12
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;13
multiline_comment|/* IP options */
DECL|macro|IP_TOS
mdefine_line|#define IP_TOS&t;&t;1
DECL|macro|IPTOS_LOWDELAY
mdefine_line|#define&t;IPTOS_LOWDELAY&t;&t;0x10
DECL|macro|IPTOS_THROUGHPUT
mdefine_line|#define&t;IPTOS_THROUGHPUT&t;0x08
DECL|macro|IPTOS_RELIABILITY
mdefine_line|#define&t;IPTOS_RELIABILITY&t;0x04
DECL|macro|IP_TTL
mdefine_line|#define IP_TTL&t;&t;2
multiline_comment|/* IPX options */
DECL|macro|IPX_TYPE
mdefine_line|#define IPX_TYPE&t;1
multiline_comment|/* TCP options - this way around because someone left a set in the c library includes */
DECL|macro|TCP_NODELAY
mdefine_line|#define TCP_NODELAY&t;1
DECL|macro|TCP_MAXSEG
mdefine_line|#define TCP_MAXSEG&t;2
multiline_comment|/* The various priorities. */
DECL|macro|SOPRI_INTERACTIVE
mdefine_line|#define SOPRI_INTERACTIVE&t;0
DECL|macro|SOPRI_NORMAL
mdefine_line|#define SOPRI_NORMAL&t;&t;1
DECL|macro|SOPRI_BACKGROUND
mdefine_line|#define SOPRI_BACKGROUND&t;2
macro_line|#endif /* _LINUX_SOCKET_H */
eof
