multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP router.&n; *&n; * Version:&t;@(#)route.h&t;1.0.4&t;05/27/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ROUTE_H
DECL|macro|_ROUTE_H
mdefine_line|#define _ROUTE_H
macro_line|#include &lt;linux/route.h&gt;
multiline_comment|/* This is an entry in the IP routing table. */
DECL|struct|rtable
r_struct
id|rtable
(brace
DECL|member|rt_next
r_struct
id|rtable
op_star
id|rt_next
suffix:semicolon
DECL|member|rt_dst
r_int
r_int
id|rt_dst
suffix:semicolon
DECL|member|rt_gateway
r_int
r_int
id|rt_gateway
suffix:semicolon
DECL|member|rt_flags
id|u_char
id|rt_flags
suffix:semicolon
DECL|member|rt_metric
id|u_char
id|rt_metric
suffix:semicolon
DECL|member|rt_refcnt
r_int
id|rt_refcnt
suffix:semicolon
DECL|member|rt_use
id|u_long
id|rt_use
suffix:semicolon
DECL|member|rt_dev
r_struct
id|device
op_star
id|rt_dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|rt_flush
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|rt_add
c_func
(paren
r_int
id|flags
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|gw
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|rtable
op_star
id|rt_route
c_func
(paren
r_int
r_int
id|daddr
comma
r_struct
id|options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|rt_get_info
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|rt_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
macro_line|#endif&t;/* _ROUTE_H */
eof