multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the IP router interface.&n; *&n; * Version:&t;@(#)route.h&t;1.0.3&t;05/27/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ROUTE_H
DECL|macro|_LINUX_ROUTE_H
mdefine_line|#define _LINUX_ROUTE_H
macro_line|#include &lt;linux/if.h&gt;
multiline_comment|/* This structure gets passed by the SIOCADDRTOLD and SIOCDELRTOLD calls. */
DECL|struct|old_rtentry
r_struct
id|old_rtentry
(brace
DECL|member|rt_genmask
r_int
r_int
id|rt_genmask
suffix:semicolon
DECL|member|rt_dst
r_struct
id|sockaddr
id|rt_dst
suffix:semicolon
DECL|member|rt_gateway
r_struct
id|sockaddr
id|rt_gateway
suffix:semicolon
DECL|member|rt_flags
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_refcnt
r_int
id|rt_refcnt
suffix:semicolon
DECL|member|rt_use
r_int
r_int
id|rt_use
suffix:semicolon
DECL|member|rt_dev
r_char
op_star
id|rt_dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This structure gets passed by the SIOCADDRT and SIOCDELRT calls. */
DECL|struct|rtentry
r_struct
id|rtentry
(brace
DECL|member|rt_hash
r_int
r_int
id|rt_hash
suffix:semicolon
multiline_comment|/* hash key for lookups&t;&t;*/
DECL|member|rt_dst
r_struct
id|sockaddr
id|rt_dst
suffix:semicolon
multiline_comment|/* target address&t;&t;*/
DECL|member|rt_gateway
r_struct
id|sockaddr
id|rt_gateway
suffix:semicolon
multiline_comment|/* gateway addr (RTF_GATEWAY)&t;*/
DECL|member|rt_genmask
r_struct
id|sockaddr
id|rt_genmask
suffix:semicolon
multiline_comment|/* target network mask (IP)&t;*/
DECL|member|rt_flags
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_refcnt
r_int
id|rt_refcnt
suffix:semicolon
DECL|member|rt_use
r_int
r_int
id|rt_use
suffix:semicolon
DECL|member|rt_ifp
r_struct
id|ifnet
op_star
id|rt_ifp
suffix:semicolon
DECL|member|rt_metric
r_int
id|rt_metric
suffix:semicolon
multiline_comment|/* +1 for binary compatibility!&t;*/
DECL|member|rt_dev
r_char
op_star
id|rt_dev
suffix:semicolon
multiline_comment|/* forcing the device at add&t;*/
DECL|member|rt_mtu
r_int
r_int
id|rt_mtu
suffix:semicolon
multiline_comment|/* per route MTU/Window */
)brace
suffix:semicolon
DECL|macro|RTF_UP
mdefine_line|#define&t;RTF_UP&t;&t;0x0001&t;&t;/* route useable&t;&t;  */
DECL|macro|RTF_GATEWAY
mdefine_line|#define&t;RTF_GATEWAY&t;0x0002&t;&t;/* destination is a gateway&t;  */
DECL|macro|RTF_HOST
mdefine_line|#define&t;RTF_HOST&t;0x0004&t;&t;/* host entry (net otherwise)&t;  */
DECL|macro|RTF_REINSTATE
mdefine_line|#define RTF_REINSTATE&t;0x0008&t;&t;/* re-instate route after tmout&t;  */
DECL|macro|RTF_DYNAMIC
mdefine_line|#define&t;RTF_DYNAMIC&t;0x0010&t;&t;/* created dyn. (by redirect)&t;  */
DECL|macro|RTF_MODIFIED
mdefine_line|#define&t;RTF_MODIFIED&t;0x0020&t;&t;/* modified dyn. (by redirect)&t;  */
DECL|macro|RTF_MTU
mdefine_line|#define RTF_MTU&t;&t;0x0040&t;&t;/* specific MSS for this route&t;  */
macro_line|#endif&t;/* _LINUX_ROUTE_H */
eof
