macro_line|#ifndef _LINUX_SOCKET_H
DECL|macro|_LINUX_SOCKET_H
mdefine_line|#define _LINUX_SOCKET_H
macro_line|#include &lt;asm/socket.h&gt;&t;&t;&t;/* arch-dependent defines&t;*/
macro_line|#include &lt;linux/sockios.h&gt;&t;&t;/* the SIOCxxx I/O controls&t;*/
macro_line|#include &lt;linux/uio.h&gt;&t;&t;&t;/* iovec support&t;&t;*/
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* pid_t&t;&t;&t;*/
DECL|typedef|sa_family_t
r_typedef
r_int
r_int
id|sa_family_t
suffix:semicolon
multiline_comment|/*&n; *&t;1003.1g requires sa_family_t and that sa_data is char.&n; */
DECL|struct|sockaddr
r_struct
id|sockaddr
(brace
DECL|member|sa_family
id|sa_family_t
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
multiline_comment|/*&n; *&t;As we do 4.4BSD message passing we use a 4.4BSD message passing&n; *&t;system, not 4.3. Thus msg_accrights(len) are now missing. They&n; *&t;belong in an obscure libc emulation or the bin.&n; */
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
id|__kernel_size_t
id|msg_iovlen
suffix:semicolon
multiline_comment|/* Number of blocks&t;&t;*/
DECL|member|msg_control
r_void
op_star
id|msg_control
suffix:semicolon
multiline_comment|/* Per protocol magic (eg BSD file descriptor passing) */
DECL|member|msg_controllen
id|__kernel_size_t
id|msg_controllen
suffix:semicolon
multiline_comment|/* Length of cmsg list */
DECL|member|msg_flags
r_int
id|msg_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;POSIX 1003.1g - ancillary data object information&n; *&t;Ancillary data consits of a sequence of pairs of&n; *&t;(cmsghdr, cmsg_data[])&n; */
DECL|struct|cmsghdr
r_struct
id|cmsghdr
(brace
DECL|member|cmsg_len
id|__kernel_size_t
id|cmsg_len
suffix:semicolon
multiline_comment|/* data byte count, including hdr */
DECL|member|cmsg_level
r_int
id|cmsg_level
suffix:semicolon
multiline_comment|/* originating protocol */
DECL|member|cmsg_type
r_int
id|cmsg_type
suffix:semicolon
multiline_comment|/* protocol-specific type */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Ancilliary data object information MACROS&n; *&t;Table 5-14 of POSIX 1003.1g&n; */
DECL|macro|CMSG_NXTHDR
mdefine_line|#define CMSG_NXTHDR(mhdr, cmsg) cmsg_nxthdr(mhdr, cmsg)
DECL|macro|CMSG_ALIGN
mdefine_line|#define CMSG_ALIGN(len) ( ((len)+sizeof(long)-1) &amp; ~(sizeof(long)-1) )
DECL|macro|CMSG_DATA
mdefine_line|#define CMSG_DATA(cmsg)&t;((void *)(cmsg) + CMSG_ALIGN(sizeof(struct cmsghdr)))
DECL|macro|CMSG_SPACE
mdefine_line|#define CMSG_SPACE(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + CMSG_ALIGN(len))
DECL|macro|CMSG_LEN
mdefine_line|#define CMSG_LEN(len) (CMSG_ALIGN(sizeof(struct cmsghdr)) + (len))
DECL|macro|CMSG_FIRSTHDR
mdefine_line|#define&t;CMSG_FIRSTHDR(msg)&t;((msg)-&gt;msg_controllen &gt;= sizeof(struct cmsghdr) ? &bslash;&n;&t;&t;&t;&t; (struct cmsghdr *)(msg)-&gt;msg_control : &bslash;&n;&t;&t;&t;&t; (struct cmsghdr *)NULL)
multiline_comment|/*&n; *&t;This mess will go away with glibc&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|KINLINE
mdefine_line|#define KINLINE extern __inline__
macro_line|#else
DECL|macro|KINLINE
mdefine_line|#define KINLINE static
macro_line|#endif
multiline_comment|/*&n; *&t;Get the next cmsg header&n; */
DECL|function|cmsg_nxthdr
id|KINLINE
r_struct
id|cmsghdr
op_star
id|cmsg_nxthdr
c_func
(paren
r_struct
id|msghdr
op_star
id|mhdr
comma
r_struct
id|cmsghdr
op_star
id|cmsg
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|cmsg
)paren
op_plus
id|CMSG_ALIGN
c_func
(paren
id|cmsg-&gt;cmsg_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_ge
(paren
r_int
r_char
op_star
)paren
id|mhdr-&gt;msg_control
op_plus
id|mhdr-&gt;msg_controllen
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
r_struct
id|cmsghdr
op_star
)paren
id|ptr
suffix:semicolon
)brace
multiline_comment|/* &quot;Socket&quot;-level control message types: */
DECL|macro|SCM_RIGHTS
mdefine_line|#define&t;SCM_RIGHTS&t;0x01&t;&t;/* rw: access rights (array of int) */
DECL|macro|SCM_CREDENTIALS
mdefine_line|#define SCM_CREDENTIALS 0x02&t;&t;/* rw: struct ucred&t;&t;*/
DECL|macro|SCM_CONNECT
mdefine_line|#define SCM_CONNECT&t;0x03&t;&t;/* rw: struct scm_connect&t;*/
DECL|struct|ucred
r_struct
id|ucred
(brace
DECL|member|pid
id|__kernel_pid_t
id|pid
suffix:semicolon
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
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
mdefine_line|#define AF_UNIX&t;&t;1&t;/* Unix domain sockets &t;&t;*/
DECL|macro|AF_LOCAL
mdefine_line|#define AF_LOCAL&t;1&t;/* POSIX name for AF_UNIX&t;*/
DECL|macro|AF_INET
mdefine_line|#define AF_INET&t;&t;2&t;/* Internet IP Protocol &t;*/
DECL|macro|AF_AX25
mdefine_line|#define AF_AX25&t;&t;3&t;/* Amateur Radio AX.25 &t;&t;*/
DECL|macro|AF_IPX
mdefine_line|#define AF_IPX&t;&t;4&t;/* Novell IPX &t;&t;&t;*/
DECL|macro|AF_APPLETALK
mdefine_line|#define AF_APPLETALK&t;5&t;/* Appletalk DDP &t;&t;*/
DECL|macro|AF_NETROM
mdefine_line|#define AF_NETROM&t;6&t;/* Amateur Radio NET/ROM &t;*/
DECL|macro|AF_BRIDGE
mdefine_line|#define AF_BRIDGE&t;7&t;/* Multiprotocol bridge &t;*/
DECL|macro|AF_AAL5
mdefine_line|#define AF_AAL5&t;&t;8&t;/* Reserved for Werner&squot;s ATM &t;*/
DECL|macro|AF_X25
mdefine_line|#define AF_X25&t;&t;9&t;/* Reserved for X.25 project &t;*/
DECL|macro|AF_INET6
mdefine_line|#define AF_INET6&t;10&t;/* IP version 6&t;&t;&t;*/
DECL|macro|AF_ROSE
mdefine_line|#define AF_ROSE&t;&t;11&t;/* Amateur Radio X.25 PLP&t;*/
DECL|macro|AF_DECnet
mdefine_line|#define AF_DECnet&t;12&t;/* Reserved for DECnet project&t;*/
DECL|macro|AF_NETBEUI
mdefine_line|#define AF_NETBEUI&t;13&t;/* Reserved for 802.2LLC project*/
DECL|macro|AF_SECURITY
mdefine_line|#define AF_SECURITY&t;14&t;/* Security callback pseudo AF */
DECL|macro|pseudo_AF_KEY
mdefine_line|#define pseudo_AF_KEY   15      /* PF_KEY key management API */
DECL|macro|AF_MAX
mdefine_line|#define AF_MAX&t;&t;32&t;/* For now.. */
multiline_comment|/* Protocol families, same as address families. */
DECL|macro|PF_UNSPEC
mdefine_line|#define PF_UNSPEC&t;AF_UNSPEC
DECL|macro|PF_UNIX
mdefine_line|#define PF_UNIX&t;&t;AF_UNIX
DECL|macro|PF_LOCAL
mdefine_line|#define PF_LOCAL&t;AF_LOCAL
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
DECL|macro|PF_ROSE
mdefine_line|#define PF_ROSE&t;&t;AF_ROSE
DECL|macro|PF_DECnet
mdefine_line|#define PF_DECnet&t;AF_DECnet
DECL|macro|PF_NETBEUI
mdefine_line|#define PF_NETBEUI&t;AF_NETBEUI
DECL|macro|PF_SECURITY
mdefine_line|#define PF_SECURITY&t;AF_SECURITY
DECL|macro|PF_KEY
mdefine_line|#define PF_KEY          pseudo_AF_KEY
DECL|macro|PF_MAX
mdefine_line|#define PF_MAX&t;&t;AF_MAX
multiline_comment|/* Maximum queue length specifiable by listen.  */
DECL|macro|SOMAXCONN
mdefine_line|#define SOMAXCONN&t;128
multiline_comment|/* Flags we can use with send/ and recv. &n;   Added those for 1003.1g not all are supported yet&n; */
DECL|macro|MSG_OOB
mdefine_line|#define MSG_OOB&t;&t;1
DECL|macro|MSG_PEEK
mdefine_line|#define MSG_PEEK&t;2
DECL|macro|MSG_DONTROUTE
mdefine_line|#define MSG_DONTROUTE&t;4
DECL|macro|MSG_CTRUNC
mdefine_line|#define MSG_CTRUNC&t;8
DECL|macro|MSG_PROXY
mdefine_line|#define MSG_PROXY&t;0x10&t;/* Supply or ask second address. */
DECL|macro|MSG_TRUNC
mdefine_line|#define MSG_TRUNC&t;0x20
DECL|macro|MSG_DONTWAIT
mdefine_line|#define MSG_DONTWAIT&t;0x40&t;/* Nonblocking io&t;&t; */
DECL|macro|MSG_EOR
mdefine_line|#define MSG_EOR         0x80&t;/* End of record */
DECL|macro|MSG_WAITALL
mdefine_line|#define MSG_WAITALL&t;0x100&t;/* Wait for a full request */
DECL|macro|MSG_FIN
mdefine_line|#define MSG_FIN         0x200
DECL|macro|MSG_SYN
mdefine_line|#define MSG_SYN&t;&t;0x400
DECL|macro|MSG_URG
mdefine_line|#define MSG_URG&t;&t;0x800
DECL|macro|MSG_RST
mdefine_line|#define MSG_RST&t;&t;0x1000
DECL|macro|MSG_CTLIGNORE
mdefine_line|#define MSG_CTLIGNORE   0x80000000
DECL|macro|MSG_EOF
mdefine_line|#define MSG_EOF         MSG_FIN
DECL|macro|MSG_CTLFLAGS
mdefine_line|#define MSG_CTLFLAGS&t;(MSG_OOB|MSG_URG|MSG_FIN|MSG_SYN|MSG_RST)
multiline_comment|/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
DECL|macro|SOL_IP
mdefine_line|#define SOL_IP&t;&t;0
DECL|macro|SOL_IPV6
mdefine_line|#define SOL_IPV6&t;41
DECL|macro|SOL_ICMPV6
mdefine_line|#define SOL_ICMPV6&t;58
DECL|macro|SOL_RAW
mdefine_line|#define SOL_RAW&t;&t;255
DECL|macro|SOL_IPX
mdefine_line|#define SOL_IPX&t;&t;256
DECL|macro|SOL_AX25
mdefine_line|#define SOL_AX25&t;257
DECL|macro|SOL_ATALK
mdefine_line|#define SOL_ATALK&t;258
DECL|macro|SOL_NETROM
mdefine_line|#define SOL_NETROM&t;259
DECL|macro|SOL_ROSE
mdefine_line|#define SOL_ROSE&t;260
DECL|macro|SOL_DECNET
mdefine_line|#define SOL_DECNET&t;261
DECL|macro|SOL_X25
mdefine_line|#define&t;SOL_X25&t;&t;262
DECL|macro|SOL_TCP
mdefine_line|#define SOL_TCP&t;&t;6
DECL|macro|SOL_UDP
mdefine_line|#define SOL_UDP&t;&t;17
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
r_int
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
id|memcpy_fromiovecend
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
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_int
id|csum_partial_copy_fromiovecend
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
id|offset
comma
r_int
id|len
comma
r_int
id|csum
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
r_int
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
r_extern
r_void
id|put_cmsg
c_func
(paren
r_struct
id|msghdr
op_star
comma
r_int
id|level
comma
r_int
id|type
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_SOCKET_H */
eof
