multiline_comment|/*&n; *&t;Types and definitions for AF_INET6 &n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Sources:&n; *&t;IPv6 Program Interfaces for BSD Systems&n; *      &lt;draft-ietf-ipngwg-bsd-api-05.txt&gt;&n; *&n; *&t;Advanced Sockets API for IPv6&n; *&t;&lt;draft-stevens-advanced-api-00.txt&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IN6_H
DECL|macro|_LINUX_IN6_H
mdefine_line|#define _LINUX_IN6_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; *&t;IPv6 address structure&n; */
DECL|struct|in6_addr
r_struct
id|in6_addr
(brace
r_union
(brace
DECL|member|u6_addr8
id|__u8
id|u6_addr8
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u6_addr16
id|__u16
id|u6_addr16
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|u6_addr32
id|__u32
id|u6_addr32
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#if (~0UL) &gt; 0xffffffff
DECL|member|u6_addr64
id|__u64
id|u6_addr64
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
DECL|member|in6_u
)brace
id|in6_u
suffix:semicolon
DECL|macro|s6_addr
mdefine_line|#define s6_addr&t;&t;&t;in6_u.u6_addr8
DECL|macro|s6_addr16
mdefine_line|#define s6_addr16&t;&t;in6_u.u6_addr16
DECL|macro|s6_addr32
mdefine_line|#define s6_addr32&t;&t;in6_u.u6_addr32
DECL|macro|s6_addr64
mdefine_line|#define s6_addr64&t;&t;in6_u.u6_addr64
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
DECL|member|ipv6mr_ifindex
r_int
id|ipv6mr_ifindex
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
multiline_comment|/*&n; *&t;IPV6 extension headers&n; */
DECL|macro|IPPROTO_HOPOPTS
mdefine_line|#define IPPROTO_HOPOPTS&t;&t;0&t;/* IPv6 hop-by-hop options&t;*/
DECL|macro|IPPROTO_ROUTING
mdefine_line|#define IPPROTO_ROUTING&t;&t;43&t;/* IPv6 routing header&t;&t;*/
DECL|macro|IPPROTO_FRAGMENT
mdefine_line|#define IPPROTO_FRAGMENT&t;44&t;/* IPv6 fragmentation header&t;*/
DECL|macro|IPPROTO_ESP
mdefine_line|#define IPPROTO_ESP&t;&t;50&t;/* encapsulating security payload */
DECL|macro|IPPROTO_AH
mdefine_line|#define IPPROTO_AH&t;&t;51&t;/* authentication header&t;*/
DECL|macro|IPPROTO_ICMPV6
mdefine_line|#define IPPROTO_ICMPV6&t;&t;58&t;/* ICMPv6&t;&t;&t;*/
DECL|macro|IPPROTO_NONE
mdefine_line|#define IPPROTO_NONE&t;&t;59&t;/* IPv6 no next header&t;&t;*/
DECL|macro|IPPROTO_DSTOPTS
mdefine_line|#define IPPROTO_DSTOPTS&t;&t;60&t;/* IPv6 destination options&t;*/
multiline_comment|/*&n; *&t;IPV6 socket options&n; */
DECL|macro|IPV6_ADDRFORM
mdefine_line|#define IPV6_ADDRFORM&t;&t;1
DECL|macro|IPV6_PKTINFO
mdefine_line|#define IPV6_PKTINFO&t;&t;2
DECL|macro|IPV6_RXHOPOPTS
mdefine_line|#define IPV6_RXHOPOPTS&t;&t;3 /* obsolete name */
DECL|macro|IPV6_RXDSTOPTS
mdefine_line|#define IPV6_RXDSTOPTS&t;&t;4 /* obsolete name */
DECL|macro|IPV6_HOPOPTS
mdefine_line|#define IPV6_HOPOPTS&t;&t;IPV6_RXHOPOPTS  /* new name */
DECL|macro|IPV6_DSTOPTS
mdefine_line|#define IPV6_DSTOPTS&t;&t;IPV6_RXDSTOPTS  /* new name */
DECL|macro|IPV6_RXSRCRT
mdefine_line|#define IPV6_RXSRCRT&t;&t;5
DECL|macro|IPV6_PKTOPTIONS
mdefine_line|#define IPV6_PKTOPTIONS&t;&t;6
DECL|macro|IPV6_CHECKSUM
mdefine_line|#define IPV6_CHECKSUM&t;&t;7
DECL|macro|IPV6_HOPLIMIT
mdefine_line|#define IPV6_HOPLIMIT&t;&t;8
multiline_comment|/*&n; *&t;Alternative names&n; */
DECL|macro|SCM_SRCRT
mdefine_line|#define SCM_SRCRT&t;&t;IPV6_RXSRCRT
DECL|macro|IPV6_UNICAST_HOPS
mdefine_line|#define IPV6_UNICAST_HOPS&t;16
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
DECL|macro|IPV6_ROUTER_ALERT
mdefine_line|#define IPV6_ROUTER_ALERT&t;22
macro_line|#endif
eof
