multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP protocol.&n; *&n; * Version:&t;@(#)ip.h&t;1.0.2&t;04/28/93&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IP_H
DECL|macro|_LINUX_IP_H
mdefine_line|#define _LINUX_IP_H
DECL|macro|IPOPT_END
mdefine_line|#define IPOPT_END&t;0
DECL|macro|IPOPT_NOOP
mdefine_line|#define IPOPT_NOOP&t;1
DECL|macro|IPOPT_SEC
mdefine_line|#define IPOPT_SEC&t;130
DECL|macro|IPOPT_LSRR
mdefine_line|#define IPOPT_LSRR&t;131
DECL|macro|IPOPT_SSRR
mdefine_line|#define IPOPT_SSRR&t;137
DECL|macro|IPOPT_RR
mdefine_line|#define IPOPT_RR&t;7
DECL|macro|IPOPT_SID
mdefine_line|#define IPOPT_SID&t;136
DECL|macro|IPOPT_TIMESTAMP
mdefine_line|#define IPOPT_TIMESTAMP&t;68
DECL|struct|timestamp
r_struct
id|timestamp
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|ptr
r_int
r_char
id|ptr
suffix:semicolon
r_union
(brace
r_int
r_char
id|flags
suffix:colon
l_int|4
comma
id|overflow
suffix:colon
l_int|4
suffix:semicolon
DECL|member|full_char
r_int
r_char
id|full_char
suffix:semicolon
DECL|member|x
)brace
id|x
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
(braket
l_int|9
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_ROUTE
mdefine_line|#define MAX_ROUTE&t;16
DECL|struct|route
r_struct
id|route
(brace
DECL|member|route_size
r_char
id|route_size
suffix:semicolon
DECL|member|pointer
r_char
id|pointer
suffix:semicolon
DECL|member|route
r_int
r_int
id|route
(braket
id|MAX_ROUTE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|options
r_struct
id|options
(brace
DECL|member|record_route
r_struct
id|route
id|record_route
suffix:semicolon
DECL|member|loose_route
r_struct
id|route
id|loose_route
suffix:semicolon
DECL|member|strict_route
r_struct
id|route
id|strict_route
suffix:semicolon
DECL|member|tstamp
r_struct
id|timestamp
id|tstamp
suffix:semicolon
DECL|member|security
r_int
r_int
id|security
suffix:semicolon
DECL|member|compartment
r_int
r_int
id|compartment
suffix:semicolon
DECL|member|handling
r_int
r_int
id|handling
suffix:semicolon
DECL|member|stream
r_int
r_int
id|stream
suffix:semicolon
DECL|member|tcc
r_int
id|tcc
suffix:semicolon
DECL|member|option_length
r_int
id|option_length
suffix:semicolon
DECL|member|option_data
r_void
op_star
id|option_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iphdr
r_struct
id|iphdr
(brace
DECL|member|ihl
r_int
r_char
id|ihl
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|tos
r_int
r_char
id|tos
suffix:semicolon
DECL|member|tot_len
r_int
r_int
id|tot_len
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|frag_off
r_int
r_int
id|frag_off
suffix:semicolon
DECL|member|ttl
r_int
r_char
id|ttl
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|check
r_int
r_int
id|check
suffix:semicolon
DECL|member|saddr
r_int
r_int
id|saddr
suffix:semicolon
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/*The options start here. */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IP_H */
eof
