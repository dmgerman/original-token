multiline_comment|/*&n; *&t;&t;IP_MASQ_FTP ftp masquerading module&n; *&n; *&n; * Version:&t;@(#)ip_masq_ftp.c 0.01   02/05/96&n; *&n; * Author:&t;Wouter Gadeyne&n; *&n; *&n; * Fixes:&n; *&t;Wouter Gadeyne&t;&t;:&t;Fixed masquerading support of ftp PORT commands&n; * &t;Juan Jose Ciarlante&t;:&t;Code moved and adapted from ip_fw.c&n; *&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ip_masq.h&gt;
DECL|macro|DEBUG_CONFIG_IP_MASQ_FTP
mdefine_line|#define DEBUG_CONFIG_IP_MASQ_FTP 0
r_static
r_int
DECL|function|masq_ftp_init_1
id|masq_ftp_init_1
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
DECL|function|masq_ftp_done_1
id|masq_ftp_done_1
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
DECL|function|masq_ftp_out
id|masq_ftp_out
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
id|__u32
id|maddr
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
id|p
comma
op_star
id|data
comma
op_star
id|data_limit
suffix:semicolon
r_int
r_char
id|p1
comma
id|p2
comma
id|p3
comma
id|p4
comma
id|p5
comma
id|p6
suffix:semicolon
id|__u32
id|from
suffix:semicolon
id|__u16
id|port
suffix:semicolon
r_struct
id|ip_masq
op_star
id|n_ms
suffix:semicolon
r_char
id|buf
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* xxx.xxx.xxx.xxx,ppp,ppp&bslash;000 */
r_int
id|buf_len
suffix:semicolon
r_int
id|diff
suffix:semicolon
id|skb
op_assign
op_star
id|skb_p
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
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
id|data_limit
op_assign
id|skb-&gt;h.raw
op_plus
id|skb-&gt;len
op_minus
l_int|18
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|data_limit
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
l_string|&quot;PORT &quot;
comma
l_int|5
)paren
op_logical_and
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;port &quot;
comma
l_int|5
)paren
)paren
(brace
id|data
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|p
op_assign
id|data
op_plus
l_int|5
suffix:semicolon
id|p1
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|5
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
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p2
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
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
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p3
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
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
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p4
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
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
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p5
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
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
op_ne
l_char|&squot;,&squot;
)paren
r_continue
suffix:semicolon
id|p6
op_assign
id|simple_strtoul
c_func
(paren
id|data
op_plus
l_int|1
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
op_ne
l_char|&squot;&bslash;r&squot;
op_logical_and
op_star
id|data
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
id|from
op_assign
(paren
id|p1
op_lshift
l_int|24
)paren
op_or
(paren
id|p2
op_lshift
l_int|16
)paren
op_or
(paren
id|p3
op_lshift
l_int|8
)paren
op_or
id|p4
suffix:semicolon
id|port
op_assign
(paren
id|p5
op_lshift
l_int|8
)paren
op_or
id|p6
suffix:semicolon
macro_line|#if DEBUG_CONFIG_IP_MASQ_FTP
id|printk
c_func
(paren
l_string|&quot;PORT %X:%X detected&bslash;n&quot;
comma
id|from
comma
id|port
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Now update or create an masquerade entry for it&n;&t;&t; */
macro_line|#if DEBUG_CONFIG_IP_MASQ_FTP
id|printk
c_func
(paren
l_string|&quot;protocol %d %lX:%X %X:%X&bslash;n&quot;
comma
id|iph-&gt;protocol
comma
id|htonl
c_func
(paren
id|from
)paren
comma
id|htons
c_func
(paren
id|port
)paren
comma
id|iph-&gt;daddr
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|n_ms
op_assign
id|ip_masq_out_get_2
c_func
(paren
id|iph-&gt;protocol
comma
id|htonl
c_func
(paren
id|from
)paren
comma
id|htons
c_func
(paren
id|port
)paren
comma
id|iph-&gt;daddr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms
)paren
(brace
multiline_comment|/* existing masquerade, clear timer */
id|ip_masq_set_expire
c_func
(paren
id|n_ms
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|n_ms
op_assign
id|ip_masq_new
c_func
(paren
id|maddr
comma
id|IPPROTO_TCP
comma
id|htonl
c_func
(paren
id|from
)paren
comma
id|htons
c_func
(paren
id|port
)paren
comma
id|iph-&gt;daddr
comma
l_int|0
comma
id|IP_MASQ_F_NO_DPORT
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
)brace
multiline_comment|/*&n;                 * keep for a bit longer than tcp_fin, caller may not reissue&n;                 * PORT before tcp_fin_timeout.&n;                 */
id|ip_masq_set_expire
c_func
(paren
id|n_ms
comma
id|ip_masq_expire-&gt;tcp_fin_timeout
op_star
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Replace the old PORT with the new one&n;&t;&t; */
id|from
op_assign
id|ntohl
c_func
(paren
id|n_ms-&gt;maddr
)paren
suffix:semicolon
id|port
op_assign
id|ntohs
c_func
(paren
id|n_ms-&gt;mport
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d,%d,%d,%d,%d,%d&quot;
comma
id|from
op_rshift
l_int|24
op_amp
l_int|255
comma
id|from
op_rshift
l_int|16
op_amp
l_int|255
comma
id|from
op_rshift
l_int|8
op_amp
l_int|255
comma
id|from
op_amp
l_int|255
comma
id|port
op_rshift
l_int|8
op_amp
l_int|255
comma
id|port
op_amp
l_int|255
)paren
suffix:semicolon
id|buf_len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#if DEBUG_CONFIG_IP_MASQ_FTP
id|printk
c_func
(paren
l_string|&quot;new PORT %X:%X&bslash;n&quot;
comma
id|from
comma
id|port
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Calculate required delta-offset to keep TCP happy&n;&t;&t; */
id|diff
op_assign
id|buf_len
op_minus
(paren
id|data
op_minus
id|p
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;No shift.&n;&t;&t; */
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * simple case, just replace the old PORT cmd&n; &t;&t;&t; */
id|memcpy
c_func
(paren
id|p
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
id|p
comma
id|data
op_minus
id|p
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
DECL|variable|ip_masq_ftp
r_struct
id|ip_masq_app
id|ip_masq_ftp
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* next */
l_string|&quot;ftp&quot;
comma
multiline_comment|/* name */
l_int|0
comma
multiline_comment|/* type */
l_int|0
comma
multiline_comment|/* n_attach */
id|masq_ftp_init_1
comma
multiline_comment|/* ip_masq_init_1 */
id|masq_ftp_done_1
comma
multiline_comment|/* ip_masq_done_1 */
id|masq_ftp_out
comma
multiline_comment|/* pkt_out */
l_int|NULL
multiline_comment|/* pkt_in */
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;ip_masq_ftp initialization&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|ip_masq_ftp_init
c_func
(paren
r_void
)paren
)paren
(brace
r_return
id|register_ip_masq_app
c_func
(paren
op_amp
id|ip_masq_ftp
comma
id|IPPROTO_TCP
comma
l_int|21
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;ip_masq_ftp fin.&n; */
DECL|function|ip_masq_ftp_done
r_int
id|ip_masq_ftp_done
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
id|ip_masq_ftp
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
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
id|ip_masq_ftp_init
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
id|ip_masq_ftp_done
c_func
(paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip_masq_ftp: can&squot;t remove module&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
