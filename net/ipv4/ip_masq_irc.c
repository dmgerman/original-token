multiline_comment|/*&n; *&t;&t;IP_MASQ_IRC irc masquerading module&n; *&n; *&n; * Version:&t;@(#)ip_masq_irc.c 0.01   03/20/96&n; *&n; * Author:&t;Juan Jose Ciarlante&n; *&t;&t;&n; *&n; * Fixes:&n; *&t;- set NO_DADDR flag in ip_masq_new().&n; *&n; * FIXME:&n; *&t;- detect also previous &quot;PRIVMSG&quot; string ?.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ip_masq.h&gt;
DECL|macro|DEBUG_CONFIG_IP_MASQ_IRC
mdefine_line|#define DEBUG_CONFIG_IP_MASQ_IRC 0
r_static
r_int
DECL|function|masq_irc_init_1
id|masq_irc_init_1
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|masq_irc_done_1
id|masq_irc_done_1
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|masq_irc_out
id|masq_irc_out
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
comma
r_struct
id|sk_buff
op_star
op_star
id|skb_p
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|data_limit
suffix:semicolon
id|__u32
id|s_addr
suffix:semicolon
id|__u16
id|s_port
suffix:semicolon
r_struct
id|ip_masq
op_star
id|n_ms
suffix:semicolon
r_char
id|buf
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* &quot;m_addr m_port&quot; (dec base)*/
r_int
id|buf_len
suffix:semicolon
r_int
id|diff
suffix:semicolon
r_int
id|xtra_args
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* extra int args wanted after addr */
r_char
op_star
id|dcc_p
comma
op_star
id|addr_beg_p
comma
op_star
id|addr_end_p
suffix:semicolon
id|skb
op_assign
op_star
id|skb_p
suffix:semicolon
id|iph
op_assign
id|skb-&gt;h.iph
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
(braket
id|iph-&gt;ihl
op_star
l_int|4
)braket
)paren
suffix:semicolon
id|data
op_assign
(paren
r_char
op_star
)paren
op_amp
id|th
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;         *&t;Hunt irc DCC string, the _shortest_:&n;         *&n;         *&t;strlen(&quot;DCC CHAT chat AAAAAAAA P&bslash;x01&bslash;n&quot;)=26&n;         *&t;strlen(&quot;DCC SEND F AAAAAAAA P S&bslash;x01&bslash;n&quot;)=25&n;         *&t;&t;AAAAAAAAA: bound addr (1.0.0.0==16777216, min 8 digits)&n;         *&t;&t;P:         bound port (min 1 d )&n;         *&t;&t;F:         filename   (min 1 d )&n;         *&t;&t;S:         size       (min 1 d ) &n;         *&t;&t;0x01, &bslash;n:  terminators&n;         */
id|data_limit
op_assign
id|skb-&gt;h.raw
op_plus
id|skb-&gt;len
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
(paren
id|data_limit
op_minus
l_int|25
)paren
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;DCC &quot;
comma
l_int|4
)paren
)paren
(brace
id|data
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dcc_p
op_assign
id|data
suffix:semicolon
id|data
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* point to DCC cmd */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;CHAT &quot;
comma
l_int|5
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;SEND &quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;                         *&t;extra arg (file_size) req. for &quot;SEND&quot;&n;                         */
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;S&squot;
)paren
id|xtra_args
op_increment
suffix:semicolon
id|data
op_add_assign
l_int|5
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
multiline_comment|/*&n;                 *&t;skip next string.&n;                 */
r_while
c_loop
(paren
op_star
id|data
op_increment
op_ne
l_char|&squot; &squot;
)paren
multiline_comment|/*&n;                         *&t;must still parse, at least, &quot;AAAAAAAA P&bslash;x01&bslash;n&quot;,&n;                         *      12 bytes left.&n;                         */
r_if
c_cond
(paren
id|data
OG
(paren
id|data_limit
op_minus
l_int|12
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|addr_beg_p
op_assign
id|data
suffix:semicolon
multiline_comment|/*&n;                 *&t;client bound address in dec base&n;                 */
id|s_addr
op_assign
id|simple_strtoul
c_func
(paren
id|data
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;                 *&t;client bound port in dec base&n;                 */
id|s_port
op_assign
id|simple_strtoul
c_func
(paren
id|data
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
id|addr_end_p
op_assign
id|data
suffix:semicolon
multiline_comment|/*&n;                 *&t;should check args consistency?&n;                 */
r_while
c_loop
(paren
id|xtra_args
)paren
(brace
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot; &squot;
)paren
r_break
suffix:semicolon
id|data
op_increment
suffix:semicolon
id|simple_strtoul
c_func
(paren
id|data
comma
op_amp
id|data
comma
l_int|10
)paren
suffix:semicolon
id|xtra_args
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xtra_args
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;                 *&t;terminators.&n;                 */
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_ne
l_int|0x01
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;r&squot;
op_logical_and
id|data
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Now create an masquerade entry for it&n;                 * &t;must set NO_DPORT and NO_DADDR because&n;                 *&t;connection is requested by another client.&n;&t;&t; */
id|n_ms
op_assign
id|ip_masq_new
c_func
(paren
id|dev
comma
id|IPPROTO_TCP
comma
id|htonl
c_func
(paren
id|s_addr
)paren
comma
id|htons
c_func
(paren
id|s_port
)paren
comma
l_int|0
comma
l_int|0
comma
id|IP_MASQ_F_NO_DPORT
op_or
id|IP_MASQ_F_NO_DADDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|ip_masq_set_expire
c_func
(paren
id|n_ms
comma
id|MASQUERADE_EXPIRE_TCP_FIN
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Replace the old &quot;address port&quot; with the new one&n;&t;&t; */
id|buf_len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%lu %u&quot;
comma
id|ntohl
c_func
(paren
id|n_ms-&gt;maddr
)paren
comma
id|ntohs
c_func
(paren
id|n_ms-&gt;mport
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Calculate required delta-offset to keep TCP happy&n;&t;&t; */
id|diff
op_assign
id|buf_len
op_minus
(paren
id|addr_end_p
op_minus
id|addr_beg_p
)paren
suffix:semicolon
macro_line|#if DEBUG_CONFIG_IP_MASQ_IRC
op_star
id|addr_beg_p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;masq_irc_out(): &squot;%s&squot; %X:%X detected (diff=%d)&bslash;n&quot;
comma
id|dcc_p
comma
id|s_addr
comma
id|s_port
comma
id|diff
)paren
suffix:semicolon
macro_line|#endif&t;
multiline_comment|/*&n;&t;&t; *&t;No shift.&n;&t;&t; */
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * simple case, just copy.&n; &t;&t;&t; */
id|memcpy
c_func
(paren
id|addr_beg_p
comma
id|buf
comma
id|buf_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|skb_p
op_assign
id|ip_masq_skb_replace
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
comma
id|addr_beg_p
comma
id|addr_end_p
op_minus
id|addr_beg_p
comma
id|buf
comma
id|buf_len
)paren
suffix:semicolon
r_return
id|diff
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Main irc object&n; *     &t;You need 1 object per port in case you need&n; *&t;to offer also other used irc ports (6665,6666,etc),&n; *&t;they will share methods but they need own space for&n; *&t;data. &n; */
DECL|variable|ip_masq_irc
r_struct
id|ip_masq_app
id|ip_masq_irc
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* next */
l_int|0
comma
multiline_comment|/* type */
l_int|0
comma
multiline_comment|/* n_attach */
id|masq_irc_init_1
comma
multiline_comment|/* init_1 */
id|masq_irc_done_1
comma
multiline_comment|/* done_1 */
id|masq_irc_out
comma
multiline_comment|/* pkt_out */
l_int|NULL
multiline_comment|/* pkt_in */
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;ip_masq_irc initialization&n; */
DECL|function|ip_masq_irc_init
r_int
id|ip_masq_irc_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_ip_masq_app
c_func
(paren
op_amp
id|ip_masq_irc
comma
id|IPPROTO_TCP
comma
l_int|6667
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;ip_masq_irc fin.&n; */
DECL|function|ip_masq_irc_done
r_int
id|ip_masq_irc_done
c_func
(paren
r_void
)paren
(brace
r_return
id|unregister_ip_masq_app
c_func
(paren
op_amp
id|ip_masq_irc
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_masq_irc_init
c_func
(paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|register_symtab
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_masq_irc_done
c_func
(paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;ip_masq_irc: can&squot;t remove module&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
