multiline_comment|/*&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IPV6_ROUTE_H
DECL|macro|_LINUX_IPV6_ROUTE_H
mdefine_line|#define _LINUX_IPV6_ROUTE_H
DECL|macro|RTF_DEFAULT
mdefine_line|#define RTF_DEFAULT&t;0x00010000&t;/* default - learned via ND&t;*/
DECL|macro|RTF_ALLONLINK
mdefine_line|#define RTF_ALLONLINK&t;0x00020000&t;/* fallback, no routers on link&t;*/
DECL|macro|RTF_ADDRCONF
mdefine_line|#define RTF_ADDRCONF&t;0x00040000&t;/* addrconf route - RA&t;&t;*/
DECL|macro|RTF_LINKRT
mdefine_line|#define RTF_LINKRT&t;0x00100000&t;/* link specific - device match&t;*/
DECL|macro|RTF_NONEXTHOP
mdefine_line|#define RTF_NONEXTHOP&t;0x00200000&t;/* route with no nexthop&t;*/
DECL|macro|RTF_CACHE
mdefine_line|#define RTF_CACHE&t;0x01000000&t;/* cache entry&t;&t;&t;*/
DECL|macro|RTF_FLOW
mdefine_line|#define RTF_FLOW&t;0x02000000&t;/* flow significant route&t;*/
DECL|macro|RTF_POLICY
mdefine_line|#define RTF_POLICY&t;0x04000000&t;/* policy route&t;&t;&t;*/
DECL|struct|in6_rtmsg
r_struct
id|in6_rtmsg
(brace
DECL|member|rtmsg_dst
r_struct
id|in6_addr
id|rtmsg_dst
suffix:semicolon
DECL|member|rtmsg_src
r_struct
id|in6_addr
id|rtmsg_src
suffix:semicolon
DECL|member|rtmsg_gateway
r_struct
id|in6_addr
id|rtmsg_gateway
suffix:semicolon
DECL|member|rtmsg_type
id|__u32
id|rtmsg_type
suffix:semicolon
DECL|member|rtmsg_dst_len
id|__u16
id|rtmsg_dst_len
suffix:semicolon
DECL|member|rtmsg_src_len
id|__u16
id|rtmsg_src_len
suffix:semicolon
DECL|member|rtmsg_metric
id|__u32
id|rtmsg_metric
suffix:semicolon
DECL|member|rtmsg_info
r_int
r_int
id|rtmsg_info
suffix:semicolon
DECL|member|rtmsg_flags
id|__u32
id|rtmsg_flags
suffix:semicolon
DECL|member|rtmsg_ifindex
r_int
id|rtmsg_ifindex
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
