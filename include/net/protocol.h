multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the protocol dispatcher.&n; *&n; * Version:&t;@(#)protocol.h&t;1.0.2&t;05/07/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Changes:&n; *&t;&t;Alan Cox&t;:&t;Added a name field and a frag handler&n; *&t;&t;&t;&t;&t;field for later.&n; *&t;&t;Alan Cox&t;:&t;Cleaned up, and sorted types.&n; *&t;&t;Pedro Roque&t;:&t;inet6 protocols&n; */
macro_line|#ifndef _PROTOCOL_H
DECL|macro|_PROTOCOL_H
mdefine_line|#define _PROTOCOL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#endif
DECL|macro|MAX_INET_PROTOS
mdefine_line|#define MAX_INET_PROTOS&t;32&t;&t;/* Must be a power of 2&t;&t;*/
multiline_comment|/* This is used to register protocols. */
DECL|struct|inet_protocol
r_struct
id|inet_protocol
(brace
DECL|member|handler
r_int
(paren
op_star
id|handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|len
)paren
suffix:semicolon
DECL|member|err_handler
r_void
(paren
op_star
id|err_handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|dp
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|next
r_struct
id|inet_protocol
op_star
id|next
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|copy
r_int
r_char
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|struct|inet6_protocol
r_struct
id|inet6_protocol
(brace
DECL|member|handler
r_int
(paren
op_star
id|handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|len
)paren
suffix:semicolon
DECL|member|err_handler
r_void
(paren
op_star
id|err_handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipv6hdr
op_star
id|hdr
comma
r_struct
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
r_char
op_star
id|buff
comma
id|__u32
id|info
)paren
suffix:semicolon
DECL|member|next
r_struct
id|inet6_protocol
op_star
id|next
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|copy
r_int
r_char
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|inet_protocol
op_star
id|inet_protocol_base
suffix:semicolon
r_extern
r_struct
id|inet_protocol
op_star
id|inet_protos
(braket
id|MAX_INET_PROTOS
)braket
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
r_extern
r_struct
id|inet6_protocol
op_star
id|inet6_protocol_base
suffix:semicolon
r_extern
r_struct
id|inet6_protocol
op_star
id|inet6_protos
(braket
id|MAX_INET_PROTOS
)braket
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|inet_add_protocol
c_func
(paren
r_struct
id|inet_protocol
op_star
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|inet_del_protocol
c_func
(paren
r_struct
id|inet_protocol
op_star
id|prot
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
r_extern
r_void
id|inet6_add_protocol
c_func
(paren
r_struct
id|inet6_protocol
op_star
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|inet6_del_protocol
c_func
(paren
r_struct
id|inet6_protocol
op_star
id|prot
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _PROTOCOL_H */
eof
