multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP protocol.&n; *&n; * Version:&t;@(#)ip.h&t;1.0.2&t;04/28/93&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IP_H
DECL|macro|_LINUX_IP_H
mdefine_line|#define _LINUX_IP_H
macro_line|#include &lt;asm/byteorder.h&gt;
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
DECL|macro|MAXTTL
mdefine_line|#define MAXTTL&t;&t;255
DECL|struct|timestamp
r_struct
id|timestamp
(brace
DECL|member|len
id|__u8
id|len
suffix:semicolon
DECL|member|ptr
id|__u8
id|ptr
suffix:semicolon
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|flags
id|__u8
id|flags
suffix:colon
l_int|4
comma
DECL|member|overflow
id|overflow
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|member|overflow
id|__u8
id|overflow
suffix:colon
l_int|4
comma
DECL|member|flags
id|flags
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif&t;&t;&t;&t;&t;&t;
DECL|member|data
id|__u32
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
DECL|macro|IPOPT_OPTVAL
mdefine_line|#define IPOPT_OPTVAL 0
DECL|macro|IPOPT_OLEN
mdefine_line|#define IPOPT_OLEN   1
DECL|macro|IPOPT_OFFSET
mdefine_line|#define IPOPT_OFFSET 2
DECL|macro|IPOPT_MINOFF
mdefine_line|#define IPOPT_MINOFF 4
DECL|macro|MAX_IPOPTLEN
mdefine_line|#define MAX_IPOPTLEN 40
DECL|macro|IPOPT_NOP
mdefine_line|#define IPOPT_NOP IPOPT_NOOP
DECL|macro|IPOPT_EOL
mdefine_line|#define IPOPT_EOL IPOPT_END
DECL|macro|IPOPT_TS
mdefine_line|#define IPOPT_TS  IPOPT_TIMESTAMP
DECL|macro|IPOPT_TS_TSONLY
mdefine_line|#define&t;IPOPT_TS_TSONLY&t;&t;0&t;&t;/* timestamps only */
DECL|macro|IPOPT_TS_TSANDADDR
mdefine_line|#define&t;IPOPT_TS_TSANDADDR&t;1&t;&t;/* timestamps and addresses */
DECL|macro|IPOPT_TS_PRESPEC
mdefine_line|#define&t;IPOPT_TS_PRESPEC&t;2&t;&t;/* specified modules only */
DECL|struct|options
r_struct
id|options
(brace
DECL|member|faddr
id|__u32
id|faddr
suffix:semicolon
multiline_comment|/* Saved first hop address */
DECL|member|optlen
r_int
r_char
id|optlen
suffix:semicolon
DECL|member|srr
r_int
r_char
id|srr
suffix:semicolon
DECL|member|rr
r_int
r_char
id|rr
suffix:semicolon
DECL|member|ts
r_int
r_char
id|ts
suffix:semicolon
DECL|member|is_setbyuser
r_int
r_char
id|is_setbyuser
suffix:colon
l_int|1
comma
multiline_comment|/* Set by setsockopt?&t;&t;&t;*/
DECL|member|is_data
id|is_data
suffix:colon
l_int|1
comma
multiline_comment|/* Options in __data, rather than skb&t;*/
DECL|member|is_strictroute
id|is_strictroute
suffix:colon
l_int|1
comma
multiline_comment|/* Strict source route&t;&t;&t;*/
DECL|member|srr_is_hit
id|srr_is_hit
suffix:colon
l_int|1
comma
multiline_comment|/* Packet destination addr was our one&t;*/
DECL|member|is_changed
id|is_changed
suffix:colon
l_int|1
comma
multiline_comment|/* IP checksum more not valid&t;&t;*/
DECL|member|rr_needaddr
id|rr_needaddr
suffix:colon
l_int|1
comma
multiline_comment|/* Need to record addr of outgoing dev&t;*/
DECL|member|ts_needtime
id|ts_needtime
suffix:colon
l_int|1
comma
multiline_comment|/* Need to record timestamp&t;&t;*/
DECL|member|ts_needaddr
id|ts_needaddr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Need to record addr of outgoing dev  */
DECL|member|__pad1
r_int
r_char
id|__pad1
suffix:semicolon
DECL|member|__pad2
r_int
r_char
id|__pad2
suffix:semicolon
DECL|member|__pad3
r_int
r_char
id|__pad3
suffix:semicolon
DECL|member|__data
r_int
r_char
id|__data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iphdr
r_struct
id|iphdr
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ihl
id|__u8
id|ihl
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined (__BIG_ENDIAN_BITFIELD)
id|__u8
id|version
suffix:colon
l_int|4
comma
id|ihl
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|tos
id|__u8
id|tos
suffix:semicolon
DECL|member|tot_len
id|__u16
id|tot_len
suffix:semicolon
DECL|member|id
id|__u16
id|id
suffix:semicolon
DECL|member|frag_off
id|__u16
id|frag_off
suffix:semicolon
DECL|member|ttl
id|__u8
id|ttl
suffix:semicolon
DECL|member|protocol
id|__u8
id|protocol
suffix:semicolon
DECL|member|check
id|__u16
id|check
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/*The options start here. */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IP_H */
eof
