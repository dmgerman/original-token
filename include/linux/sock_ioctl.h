multiline_comment|/* ip.h */
multiline_comment|/* Contains the structures for communicating with the ip level of the&n;   sockets.  Currently just for configuration. */
macro_line|#ifndef _LINUX_SOCK_IOCTL_H
DECL|macro|_LINUX_SOCK_IOCTL_H
mdefine_line|#define _LINUX_SOCK_IOCTL_H
DECL|macro|MAX_IP_NAME
mdefine_line|#define MAX_IP_NAME 20
multiline_comment|/* some ioctl.  Their values are not special. */
DECL|macro|IP_SET_DEV
mdefine_line|#define IP_SET_DEV 0x2401
DECL|macro|IP_ADD_ROUTE
mdefine_line|#define IP_ADD_ROUTE 0x2402
DECL|macro|IP_HANDOFF
mdefine_line|#define IP_HANDOFF 0x2403
DECL|struct|ip_config
r_struct
id|ip_config
(brace
DECL|member|name
r_char
id|name
(braket
id|MAX_IP_NAME
)braket
suffix:semicolon
DECL|member|paddr
r_int
r_int
id|paddr
suffix:semicolon
DECL|member|router
r_int
r_int
id|router
suffix:semicolon
DECL|member|net
r_int
r_int
id|net
suffix:semicolon
DECL|member|up
r_int
r_int
id|up
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
