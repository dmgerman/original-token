macro_line|#ifndef _LINUX_SOCK_IOCTL_H
DECL|macro|_LINUX_SOCK_IOCTL_H
mdefine_line|#define _LINUX_SOCK_IOCTL_H
DECL|macro|MAX_IP_NAME
mdefine_line|#define MAX_IP_NAME 20
multiline_comment|/* some ioctl.  Their values are not special. */
DECL|macro|IP_SET_DEV
mdefine_line|#define IP_SET_DEV 0x2401
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
DECL|member|destroy
r_int
r_int
id|up
suffix:colon
l_int|1
comma
id|destroy
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SIOCSARP
mdefine_line|#define SIOCSARP&t;0x2501
DECL|macro|SIOCGARP
mdefine_line|#define SIOCGARP&t;0x2502
DECL|macro|SIOCDARP
mdefine_line|#define SIOCDARP&t;0x2503
multiline_comment|/*&n; * ARP ioctl request&n; */
DECL|struct|arpreq
r_struct
id|arpreq
(brace
DECL|member|arp_pa
r_struct
id|sockaddr
id|arp_pa
suffix:semicolon
multiline_comment|/* protocol address */
DECL|member|arp_ha
r_struct
id|sockaddr
id|arp_ha
suffix:semicolon
multiline_comment|/* hardware address */
DECL|member|arp_flags
r_int
id|arp_flags
suffix:semicolon
multiline_comment|/* flags */
)brace
suffix:semicolon
DECL|macro|ATF_COM
mdefine_line|#define ATF_COM&t;&t;0x02
DECL|macro|ATF_PERM
mdefine_line|#define ATF_PERM&t;0x04
DECL|macro|ATF_PUBL
mdefine_line|#define ATF_PUBL&t;0x08
DECL|macro|ATF_USETRAILERS
mdefine_line|#define ATF_USETRAILERS&t;0x10
macro_line|#endif
eof
