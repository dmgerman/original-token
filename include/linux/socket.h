macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
macro_line|#include &lt;asm/socket.h&gt;&t;&t;&t;/* arch-dependent defines&t;*/
macro_line|#include &lt;linux/sockios.h&gt;&t;&t;/* the SIOCxxx I/O controls&t;*/
macro_line|#include &lt;linux/uio.h&gt;&t;&t;&t;/* iovec support&t;&t;*/
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
DECL|struct|msghdr
r_struct
id|msghdr
(brace
DECL|member|msg_name
r_void
op_star
id|msg_name
suffix:semicolon
multiline_comment|/* Socket name&t;&t;&t;*/
DECL|member|msg_namelen
r_int
id|msg_namelen
suffix:semicolon
multiline_comment|/* Length of name&t;&t;*/
DECL|member|msg_iov
r_struct
id|iovec
op_star
id|msg_iov
suffix:semicolon
multiline_comment|/* Data blocks&t;&t;&t;*/
DECL|member|msg_iovlen
r_int
id|msg_iovlen
suffix:semicolon
multiline_comment|/* Number of blocks&t;&t;*/
DECL|member|msg_accrights
r_void
op_star
id|msg_accrights
suffix:semicolon
multiline_comment|/* Per protocol magic (eg BSD file descriptor passing) */
DECL|member|msg_accrightslen
r_int
id|msg_accrightslen
suffix:semicolon
multiline_comment|/* Length of rights list */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;4.4BSD changed to these new names for no apparent reason.&n; */
DECL|macro|msg_control
mdefine_line|#define msg_control&t;msg_accrights&t;
DECL|macro|msg_controllen
mdefine_line|#define msg_controllen&t;msg_accrightslen
multiline_comment|/* Control Messages */
DECL|macro|SCM_RIGHTS
mdefine_line|#define SCM_RIGHTS&t;&t;1
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
mdefine_line|#define AF_UNIX&t;&t;1&t;/* Unix domain sockets &t;&t;*/
DECL|macro|AF_INET
mdefine_line|#define AF_INET&t;&t;2&t;/* Internet IP Protocol &t;*/
DECL|macro|AF_AX25
mdefine_line|#define AF_AX25&t;&t;3&t;/* Amateur Radio AX.25 &t;&t;*/
DECL|macro|AF_IPX
mdefine_line|#define AF_IPX&t;&t;4&t;/* Novell IPX &t;&t;&t;*/
DECL|macro|AF_APPLETALK
mdefine_line|#define AF_APPLETALK&t;5&t;/* Appletalk DDP &t;&t;*/
DECL|macro|AF_NETROM
mdefine_line|#define&t;AF_NETROM&t;6&t;/* Amateur radio NetROM &t;*/
DECL|macro|AF_BRIDGE
mdefine_line|#define AF_BRIDGE&t;7&t;/* Multiprotocol bridge &t;*/
DECL|macro|AF_AAL5
mdefine_line|#define AF_AAL5&t;&t;8&t;/* Reserved for Werner&squot;s ATM &t;*/
DECL|macro|AF_X25
mdefine_line|#define AF_X25&t;&t;9&t;/* Reserved for X.25 project &t;*/
DECL|macro|AF_INET6
mdefine_line|#define AF_INET6&t;10&t;/* IP version 6&t;&t;&t;*/
DECL|macro|AF_MAX
mdefine_line|#define AF_MAX&t;&t;12&t;/* For now.. */
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
DECL|macro|PF_APPLETALK
mdefine_line|#define PF_APPLETALK&t;AF_APPLETALK
DECL|macro|PF_NETROM
mdefine_line|#define&t;PF_NETROM&t;AF_NETROM
DECL|macro|PF_BRIDGE
mdefine_line|#define PF_BRIDGE&t;AF_BRIDGE
DECL|macro|PF_AAL5
mdefine_line|#define PF_AAL5&t;&t;AF_AAL5
DECL|macro|PF_X25
mdefine_line|#define PF_X25&t;&t;AF_X25
DECL|macro|PF_INET6
mdefine_line|#define PF_INET6&t;AF_INET6
DECL|macro|PF_MAX
mdefine_line|#define PF_MAX&t;&t;AF_MAX
multiline_comment|/* Maximum queue length specificable by listen.  */
DECL|macro|SOMAXCONN
mdefine_line|#define SOMAXCONN&t;128
multiline_comment|/* Flags we can use with send/ and recv. */
DECL|macro|MSG_OOB
mdefine_line|#define MSG_OOB&t;&t;1
DECL|macro|MSG_PEEK
mdefine_line|#define MSG_PEEK&t;2
DECL|macro|MSG_DONTROUTE
mdefine_line|#define MSG_DONTROUTE&t;4
multiline_comment|/*#define MSG_CTRUNC&t;8&t;- We need to support this for BSD oddments */
multiline_comment|/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
DECL|macro|SOL_IP
mdefine_line|#define SOL_IP&t;&t;0
DECL|macro|SOL_IPX
mdefine_line|#define SOL_IPX&t;&t;256
DECL|macro|SOL_AX25
mdefine_line|#define SOL_AX25&t;257
DECL|macro|SOL_ATALK
mdefine_line|#define SOL_ATALK&t;258
DECL|macro|SOL_NETROM
mdefine_line|#define&t;SOL_NETROM&t;259
DECL|macro|SOL_TCP
mdefine_line|#define SOL_TCP&t;&t;6
DECL|macro|SOL_UDP
mdefine_line|#define SOL_UDP&t;&t;17
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
DECL|macro|IP_HDRINCL
mdefine_line|#define IP_HDRINCL&t;3
DECL|macro|IP_OPTIONS
mdefine_line|#define IP_OPTIONS&t;4
DECL|macro|IP_MULTICAST_IF
mdefine_line|#define IP_MULTICAST_IF&t;&t;&t;32
DECL|macro|IP_MULTICAST_TTL
mdefine_line|#define IP_MULTICAST_TTL &t;&t;33
DECL|macro|IP_MULTICAST_LOOP
mdefine_line|#define IP_MULTICAST_LOOP &t;&t;34
DECL|macro|IP_ADD_MEMBERSHIP
mdefine_line|#define IP_ADD_MEMBERSHIP&t;&t;35
DECL|macro|IP_DROP_MEMBERSHIP
mdefine_line|#define IP_DROP_MEMBERSHIP&t;&t;36
multiline_comment|/* These need to appear somewhere around here */
DECL|macro|IP_DEFAULT_MULTICAST_TTL
mdefine_line|#define IP_DEFAULT_MULTICAST_TTL        1
DECL|macro|IP_DEFAULT_MULTICAST_LOOP
mdefine_line|#define IP_DEFAULT_MULTICAST_LOOP       1
DECL|macro|IP_MAX_MEMBERSHIPS
mdefine_line|#define IP_MAX_MEMBERSHIPS              20
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
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|memcpy_fromiovec
c_func
(paren
r_int
r_char
op_star
id|kdata
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|verify_iovec
c_func
(paren
r_struct
id|msghdr
op_star
id|m
comma
r_struct
id|iovec
op_star
id|iov
comma
r_char
op_star
id|address
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|memcpy_toiovec
c_func
(paren
r_struct
id|iovec
op_star
id|v
comma
r_int
r_char
op_star
id|kdata
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|move_addr_to_user
c_func
(paren
r_void
op_star
id|kaddr
comma
r_int
id|klen
comma
r_void
op_star
id|uaddr
comma
r_int
op_star
id|ulen
)paren
suffix:semicolon
r_extern
r_int
id|move_addr_to_kernel
c_func
(paren
r_void
op_star
id|uaddr
comma
r_int
id|ulen
comma
r_void
op_star
id|kaddr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_SOCKET_H */
eof
