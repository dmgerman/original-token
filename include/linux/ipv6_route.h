multiline_comment|/*&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IPV6_ROUTE_H
DECL|macro|_LINUX_IPV6_ROUTE_H
mdefine_line|#define _LINUX_IPV6_ROUTE_H
macro_line|#include &lt;linux/route.h&gt;
DECL|macro|RTI_DEVRT
mdefine_line|#define RTI_DEVRT&t;0x00010000&t;/* route lookup, dev must match&t;*/
DECL|macro|RTI_ALLONLINK
mdefine_line|#define RTI_ALLONLINK&t;0x00020000&t;/* all destinations on link&t;*/
DECL|macro|RTI_DCACHE
mdefine_line|#define RTI_DCACHE&t;RTF_DCACHE&t;/* rt6_info is a dcache entry&t;*/
DECL|macro|RTI_INVALID
mdefine_line|#define RTI_INVALID&t;RTF_INVALID&t;/* invalid route/dcache entry&t;*/
DECL|macro|RTI_DYNAMIC
mdefine_line|#define RTI_DYNAMIC&t;RTF_DYNAMIC&t;/* rt6_info created dynamicly&t;*/
DECL|macro|RTI_GATEWAY
mdefine_line|#define RTI_GATEWAY&t;RTF_GATEWAY
DECL|macro|RTI_DYNMOD
mdefine_line|#define RTI_DYNMOD&t;RTF_MODIFIED&t;/* more specific route may exist*/
DECL|macro|DCF_PMTU
mdefine_line|#define DCF_PMTU&t;RTF_MSS&t;&t;/* dest cache has valid PMTU&t;*/
DECL|macro|DCF_INVALID
mdefine_line|#define DCF_INVALID&t;RTF_INVALID
DECL|struct|in6_rtmsg
r_struct
id|in6_rtmsg
(brace
DECL|member|rtmsg_dst
r_struct
id|in6_addr
id|rtmsg_dst
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
DECL|member|rtmsg_prefixlen
id|__u16
id|rtmsg_prefixlen
suffix:semicolon
DECL|member|rtmsg_metric
id|__u16
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
DECL|member|rtmsg_device
r_char
id|rtmsg_device
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
