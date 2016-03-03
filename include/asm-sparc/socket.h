multiline_comment|/* $Id: socket.h,v 1.12 1998/07/22 22:06:48 davem Exp $ */
macro_line|#ifndef _ASM_SOCKET_H
DECL|macro|_ASM_SOCKET_H
mdefine_line|#define _ASM_SOCKET_H
macro_line|#include &lt;asm/sockios.h&gt;
multiline_comment|/* For setsockoptions(2) */
DECL|macro|SOL_SOCKET
mdefine_line|#define SOL_SOCKET&t;0xffff
DECL|macro|SO_DEBUG
mdefine_line|#define SO_DEBUG&t;0x0001
DECL|macro|SO_PASSCRED
mdefine_line|#define SO_PASSCRED&t;0x0002
DECL|macro|SO_REUSEADDR
mdefine_line|#define SO_REUSEADDR&t;0x0004
DECL|macro|SO_KEEPALIVE
mdefine_line|#define SO_KEEPALIVE&t;0x0008
DECL|macro|SO_DONTROUTE
mdefine_line|#define SO_DONTROUTE&t;0x0010
DECL|macro|SO_BROADCAST
mdefine_line|#define SO_BROADCAST&t;0x0020
DECL|macro|SO_PEERCRED
mdefine_line|#define SO_PEERCRED&t;0x0040
DECL|macro|SO_LINGER
mdefine_line|#define SO_LINGER&t;0x0080
DECL|macro|SO_OOBINLINE
mdefine_line|#define SO_OOBINLINE&t;0x0100
multiline_comment|/* To add :#define SO_REUSEPORT 0x0200 */
DECL|macro|SO_BSDCOMPAT
mdefine_line|#define SO_BSDCOMPAT    0x0400
DECL|macro|SO_RCVLOWAT
mdefine_line|#define SO_RCVLOWAT     0x0800
DECL|macro|SO_SNDLOWAT
mdefine_line|#define SO_SNDLOWAT     0x1000
DECL|macro|SO_RCVTIMEO
mdefine_line|#define SO_RCVTIMEO     0x2000
DECL|macro|SO_SNDTIMEO
mdefine_line|#define SO_SNDTIMEO     0x4000
multiline_comment|/* wha!??? */
DECL|macro|SO_DONTLINGER
mdefine_line|#define SO_DONTLINGER   (~SO_LINGER)  /* Older SunOS compat. hack */
DECL|macro|SO_SNDBUF
mdefine_line|#define SO_SNDBUF&t;0x1001
DECL|macro|SO_RCVBUF
mdefine_line|#define SO_RCVBUF&t;0x1002
DECL|macro|SO_ERROR
mdefine_line|#define SO_ERROR&t;0x1007
DECL|macro|SO_TYPE
mdefine_line|#define SO_TYPE&t;&t;0x1008
multiline_comment|/* Linux specific, keep the same. */
DECL|macro|SO_NO_CHECK
mdefine_line|#define SO_NO_CHECK&t;0x000b
DECL|macro|SO_PRIORITY
mdefine_line|#define SO_PRIORITY&t;0x000c
DECL|macro|SO_BINDTODEVICE
mdefine_line|#define SO_BINDTODEVICE 0x000d
DECL|macro|SO_ATTACH_FILTER
mdefine_line|#define SO_ATTACH_FILTER&t;0x001a
DECL|macro|SO_DETACH_FILTER
mdefine_line|#define SO_DETACH_FILTER        0x001b
multiline_comment|/* Security levels - as per NRL IPv6 - don&squot;t actually do anything */
DECL|macro|SO_SECURITY_AUTHENTICATION
mdefine_line|#define SO_SECURITY_AUTHENTICATION&t;&t;0x5001
DECL|macro|SO_SECURITY_ENCRYPTION_TRANSPORT
mdefine_line|#define SO_SECURITY_ENCRYPTION_TRANSPORT&t;0x5002
DECL|macro|SO_SECURITY_ENCRYPTION_NETWORK
mdefine_line|#define SO_SECURITY_ENCRYPTION_NETWORK&t;&t;0x5004
macro_line|#endif /* _ASM_SOCKET_H */
eof
