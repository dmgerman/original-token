multiline_comment|/*&n; *&t;Types and definitions for AF_INET6 &n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Source:&n; *&t;IPv6 Program Interfaces for BSD Systems&n; *      &lt;draft-ietf-ipngwg-bsd-api-05.txt&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN6_H
DECL|macro|_LINUX_IN6_H
mdefine_line|#define _LINUX_IN6_H
multiline_comment|/*&n; *&t;IPv6 address structure&n; */
DECL|struct|in6_addr
r_struct
id|in6_addr
(brace
r_union
(brace
DECL|member|u6_addr8
r_int
r_char
id|u6_addr8
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u6_addr32
id|__u32
id|u6_addr32
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|in6_u
)brace
id|in6_u
suffix:semicolon
DECL|macro|s6_addr32
mdefine_line|#define s6_addr32&t;&t;in6_u.u6_addr32
DECL|macro|s6_addr
mdefine_line|#define s6_addr&t;&t;&t;in6_u.u6_addr8
)brace
suffix:semicolon
DECL|struct|sockaddr_in6
r_struct
id|sockaddr_in6
(brace
DECL|member|sin6_family
r_int
r_int
r_int
id|sin6_family
suffix:semicolon
multiline_comment|/* AF_INET6 */
DECL|member|sin6_port
id|__u16
id|sin6_port
suffix:semicolon
multiline_comment|/* Transport layer port # */
DECL|member|sin6_flowinfo
id|__u32
id|sin6_flowinfo
suffix:semicolon
multiline_comment|/* IPv6 flow information */
DECL|member|sin6_addr
r_struct
id|in6_addr
id|sin6_addr
suffix:semicolon
multiline_comment|/* IPv6 address */
)brace
suffix:semicolon
DECL|struct|ipv6_mreq
r_struct
id|ipv6_mreq
(brace
multiline_comment|/* IPv6 multicast address of group */
DECL|member|ipv6mr_multiaddr
r_struct
id|in6_addr
id|ipv6mr_multiaddr
suffix:semicolon
multiline_comment|/* local IPv6 address of interface */
DECL|member|ipv6mr_interface
r_struct
id|in6_addr
id|ipv6mr_interface
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Bitmask constant declarations to help applications select out the &n; *&t;flow label and priority fields.&n; *&n; *&t;Note that this are in host byte order while the flowinfo field of&n; *&t;sockaddr_in6 is in network byte order.&n; */
DECL|macro|IPV6_FLOWINFO_FLOWLABEL
mdefine_line|#define IPV6_FLOWINFO_FLOWLABEL&t;&t;0x00ff
DECL|macro|IPV6_FLOWINFO_PRIORITY
mdefine_line|#define IPV6_FLOWINFO_PRIORITY&t;&t;0x0f00
DECL|macro|IPV6_PRIORITY_UNCHARACTERIZED
mdefine_line|#define IPV6_PRIORITY_UNCHARACTERIZED&t;0x0000
DECL|macro|IPV6_PRIORITY_FILLER
mdefine_line|#define IPV6_PRIORITY_FILLER&t;&t;0x0100
DECL|macro|IPV6_PRIORITY_UNATTENDED
mdefine_line|#define IPV6_PRIORITY_UNATTENDED&t;0x0200
DECL|macro|IPV6_PRIORITY_RESERVED1
mdefine_line|#define IPV6_PRIORITY_RESERVED1&t;&t;0x0300
DECL|macro|IPV6_PRIORITY_BULK
mdefine_line|#define IPV6_PRIORITY_BULK&t;&t;0x0400
DECL|macro|IPV6_PRIORITY_RESERVED2
mdefine_line|#define IPV6_PRIORITY_RESERVED2&t;&t;0x0500
DECL|macro|IPV6_PRIORITY_INTERACTIVE
mdefine_line|#define IPV6_PRIORITY_INTERACTIVE&t;0x0600
DECL|macro|IPV6_PRIORITY_CONTROL
mdefine_line|#define IPV6_PRIORITY_CONTROL&t;&t;0x0700
DECL|macro|IPV6_PRIORITY_8
mdefine_line|#define IPV6_PRIORITY_8&t;&t;&t;0x0800
DECL|macro|IPV6_PRIORITY_9
mdefine_line|#define IPV6_PRIORITY_9&t;&t;&t;0x0900
DECL|macro|IPV6_PRIORITY_10
mdefine_line|#define IPV6_PRIORITY_10&t;&t;0x0a00
DECL|macro|IPV6_PRIORITY_11
mdefine_line|#define IPV6_PRIORITY_11&t;&t;0x0b00
DECL|macro|IPV6_PRIORITY_12
mdefine_line|#define IPV6_PRIORITY_12&t;&t;0x0c00
DECL|macro|IPV6_PRIORITY_13
mdefine_line|#define IPV6_PRIORITY_13&t;&t;0x0d00
DECL|macro|IPV6_PRIORITY_14
mdefine_line|#define IPV6_PRIORITY_14&t;&t;0x0e00
DECL|macro|IPV6_PRIORITY_15
mdefine_line|#define IPV6_PRIORITY_15&t;&t;0x0f00
multiline_comment|/*&n; *&t;IPV6 socket options&n; */
DECL|macro|IPV6_ADDRFORM
mdefine_line|#define IPV6_ADDRFORM&t;&t;1
DECL|macro|IPV6_RXINFO
mdefine_line|#define IPV6_RXINFO&t;&t;2
DECL|macro|IPV6_TXINFO
mdefine_line|#define IPV6_TXINFO&t;&t;IPV6_RXINFO
DECL|macro|SCM_SRCINFO
mdefine_line|#define SCM_SRCINFO&t;&t;IPV6_TXINFO
DECL|macro|SCM_SRCRT
mdefine_line|#define SCM_SRCRT&t;&t;4
DECL|macro|IPV6_UNICAST_HOPS
mdefine_line|#define IPV6_UNICAST_HOPS&t;5
DECL|macro|IPV6_MULTICAST_IF
mdefine_line|#define IPV6_MULTICAST_IF&t;17
DECL|macro|IPV6_MULTICAST_HOPS
mdefine_line|#define IPV6_MULTICAST_HOPS&t;18
DECL|macro|IPV6_MULTICAST_LOOP
mdefine_line|#define IPV6_MULTICAST_LOOP&t;19
DECL|macro|IPV6_ADD_MEMBERSHIP
mdefine_line|#define IPV6_ADD_MEMBERSHIP&t;20
DECL|macro|IPV6_DROP_MEMBERSHIP
mdefine_line|#define IPV6_DROP_MEMBERSHIP&t;21
macro_line|#endif
eof
