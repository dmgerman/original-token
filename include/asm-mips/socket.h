macro_line|#ifndef __ASM_MIPS_SOCKET_H
DECL|macro|__ASM_MIPS_SOCKET_H
mdefine_line|#define __ASM_MIPS_SOCKET_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/*&n; * For setsockoptions(2)&n; *&n; * This defines are ABI conformant as far as Linux supports these ...&n; */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;0xffff
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;0x0001&t;/* Record debugging information.  */
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;0x0004&t;/* Allow reuse of local addresses.  */
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;0x0008&t;/* Keep connections alive and send&n;&t;&t;&t;&t;   SIGPIPE when they die.  */
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;0x0010&t;/* Don&squot;t do local routing.  */
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;0x0020&t;/* Allow transmission of&n;&t;&t;&t;&t;   broadcast messages.  */
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;0x0080&t;/* Block on close of a reliable&n;&t;&t;&t;&t;   socket to transmit pending data.  */
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE 0x0100&t;/* Receive out-of-band data in-band.  */
macro_line|#if 0
id|To
id|add
suffix:colon
mdefine_line|#define SO_REUSEPORT 0x0200&t;/* Allow local address and port reuse.  */
macro_line|#endif
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;0x1008&t;/* Compatible name for SO_STYLE.  */
DECL|macro|SO_STYLE
mdefine_line|#define SO_STYLE&t;SO_TYPE&t;/* Synonym */
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;0x1007&t;/* get error status and clear */
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;0x1001&t;/* Send buffer size. */
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;0x1002&t;/* Receive buffer. */
DECL|macro|SO_SNDLOWAT
mdefine_line|#define SO_SNDLOWAT&t;0x1003&t;/* send low-water mark */
DECL|macro|SO_RCVLOWAT
mdefine_line|#define SO_RCVLOWAT&t;0x1004&t;/* receive low-water mark */
DECL|macro|SO_SNDTIMEO
mdefine_line|#define SO_SNDTIMEO&t;0x1005&t;/* send timeout */
DECL|macro|SO_RCVTIMEO
mdefine_line|#define SO_RCVTIMEO &t;0x1006&t;/* receive timeout */
multiline_comment|/* linux-specific, might as well be the same as on i386 */
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK&t;11
DECL|macro|SO_PRIORITY
mdefine_line|#define SO_PRIORITY&t;12
DECL|macro|SO_BSDCOMPAT
mdefine_line|#define SO_BSDCOMPAT&t;14
DECL|macro|SO_PASSCRED
mdefine_line|#define SO_PASSCRED&t;17
DECL|macro|SO_PEERCRED
mdefine_line|#define SO_PEERCRED&t;18
multiline_comment|/* Security levels - as per NRL IPv6 - don&squot;t actually do anything */
DECL|macro|SO_SECURITY_AUTHENTICATION
mdefine_line|#define SO_SECURITY_AUTHENTICATION&t;&t;22
DECL|macro|SO_SECURITY_ENCRYPTION_TRANSPORT
mdefine_line|#define SO_SECURITY_ENCRYPTION_TRANSPORT&t;23
DECL|macro|SO_SECURITY_ENCRYPTION_NETWORK
mdefine_line|#define SO_SECURITY_ENCRYPTION_NETWORK&t;&t;24
multiline_comment|/* Types of sockets.  */
DECL|enum|__socket_type
r_enum
id|__socket_type
(brace
DECL|enumerator|SOCK_DGRAM
id|SOCK_DGRAM
op_assign
l_int|1
comma
multiline_comment|/* Connectionless, unreliable datagrams&n;                                   of fixed maximum length.  */
DECL|enumerator|SOCK_STREAM
id|SOCK_STREAM
op_assign
l_int|2
comma
multiline_comment|/* Sequenced, reliable, connection-based&n;                                   byte streams.  */
DECL|enumerator|SOCK_RAW
id|SOCK_RAW
op_assign
l_int|3
comma
multiline_comment|/* Raw protocol interface.  */
DECL|enumerator|SOCK_RDM
id|SOCK_RDM
op_assign
l_int|4
comma
multiline_comment|/* Reliably-delivered messages.  */
DECL|enumerator|SOCK_SEQPACKET
id|SOCK_SEQPACKET
op_assign
l_int|5
comma
multiline_comment|/* Sequenced, reliable, connection-based,&n;                                   datagrams of fixed maximum length.  */
DECL|enumerator|SOCK_PACKET
id|SOCK_PACKET
op_assign
l_int|10
comma
multiline_comment|/* linux specific way of getting packets at&n;&t;&t;&t;&t;   the dev level.  For writing rarp and&n;&t;&t;&t;&t;   other similar things on the user level.  */
)brace
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_SOCKET_H */
eof
