multiline_comment|/*&n; *  Syncookies implementation for the Linux kernel&n; *&n; *  Copyright (C) 1997 Andi Kleen&n; *  Based on ideas by D.J.Bernstein and Eric Schenk. &n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; * &n; *  $Id: syncookies.c,v 1.5 1998/04/03 09:49:46 freitag Exp $&n; *&n; *  Missing: IPv6 support. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_SYN_COOKIES) 
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
r_extern
r_int
id|sysctl_tcp_syncookies
suffix:semicolon
DECL|variable|tcp_lastsynq_overflow
r_static
r_int
r_int
id|tcp_lastsynq_overflow
suffix:semicolon
multiline_comment|/* &n; * This table has to be sorted. Only 8 entries are allowed and the&n; * last entry has to be duplicated.&n; * XXX generate a better table.&n; * Unresolved Issues: HIPPI with a 64k MSS is not well supported.&n; */
DECL|variable|msstab
r_static
id|__u16
r_const
id|msstab
(braket
)braket
op_assign
(brace
l_int|64
comma
l_int|256
comma
l_int|512
comma
l_int|536
comma
l_int|1024
comma
l_int|1440
comma
l_int|1460
comma
l_int|4312
comma
l_int|4312
)brace
suffix:semicolon
DECL|function|make_syncookie
r_static
id|__u32
id|make_syncookie
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|counter
comma
id|__u32
id|seq
)paren
(brace
id|__u32
id|z
suffix:semicolon
id|z
op_assign
id|secure_tcp_syn_cookie
c_func
(paren
id|skb-&gt;nh.iph-&gt;saddr
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|skb-&gt;h.th-&gt;source
comma
id|skb-&gt;h.th-&gt;dest
comma
id|seq
comma
id|counter
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;msc: z=%u,cnt=%u,seq=%u,sadr=%u,dadr=%u,sp=%u,dp=%u&bslash;n&quot;
comma
id|z
comma
id|counter
comma
id|seq
comma
id|skb-&gt;nh.iph-&gt;saddr
comma
id|skb-&gt;nh.iph-&gt;daddr
comma
id|ntohs
c_func
(paren
id|skb-&gt;h.th-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|skb-&gt;h.th-&gt;dest
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|z
suffix:semicolon
)brace
multiline_comment|/*&n; * Generate a syncookie. &n; */
DECL|function|cookie_v4_init_sequence
id|__u32
id|cookie_v4_init_sequence
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u16
op_star
id|mssp
)paren
(brace
r_int
id|i
suffix:semicolon
id|__u32
id|isn
suffix:semicolon
r_const
id|__u16
id|mss
op_assign
op_star
id|mssp
comma
op_star
id|w
suffix:semicolon
id|tcp_lastsynq_overflow
op_assign
id|jiffies
suffix:semicolon
id|isn
op_assign
id|make_syncookie
c_func
(paren
id|skb
comma
(paren
id|jiffies
op_div
id|HZ
)paren
op_rshift
l_int|6
comma
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX sort msstab[] by probability? */
id|w
op_assign
id|msstab
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mss
op_ge
op_star
id|w
op_logical_and
id|mss
OL
op_star
op_increment
id|w
)paren
r_goto
id|found
suffix:semicolon
id|i
op_decrement
suffix:semicolon
id|found
suffix:colon
op_star
id|mssp
op_assign
id|w
(braket
op_minus
l_int|1
)braket
suffix:semicolon
id|net_statistics.SyncookiesSent
op_increment
suffix:semicolon
id|isn
op_or_assign
id|i
suffix:semicolon
r_return
id|isn
suffix:semicolon
)brace
multiline_comment|/* This value should be dependent on TCP_TIMEOUT_INIT and &n; * sysctl_tcp_retries1. It&squot;s a rather complicated formula &n; * (exponential backoff) to compute at runtime so it&squot;s currently hardcoded&n; * here.&n; */
DECL|macro|COUNTER_TRIES
mdefine_line|#define COUNTER_TRIES 4
multiline_comment|/*  &n; * Check if a ack sequence number is a valid syncookie. &n; */
DECL|function|cookie_check
r_static
r_inline
r_int
id|cookie_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|cookie
)paren
(brace
r_int
id|mssind
suffix:semicolon
r_int
id|i
suffix:semicolon
id|__u32
id|counter
suffix:semicolon
id|__u32
id|seq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|jiffies
op_minus
id|tcp_lastsynq_overflow
)paren
OG
id|TCP_TIMEOUT_INIT
op_logical_and
id|tcp_lastsynq_overflow
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|mssind
op_assign
id|cookie
op_amp
l_int|7
suffix:semicolon
id|cookie
op_and_assign
op_complement
l_int|7
suffix:semicolon
id|counter
op_assign
(paren
id|jiffies
op_div
id|HZ
)paren
op_rshift
l_int|6
suffix:semicolon
id|seq
op_assign
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|COUNTER_TRIES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|make_syncookie
c_func
(paren
id|skb
comma
id|counter
op_minus
id|i
comma
id|seq
)paren
op_eq
id|cookie
)paren
r_return
id|msstab
(braket
id|mssind
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_struct
id|or_calltable
id|or_ipv4
suffix:semicolon
r_static
r_inline
r_struct
id|sock
op_star
DECL|function|get_cookie_sock
id|get_cookie_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|open_request
op_star
id|req
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
id|sk
op_assign
id|tp-&gt;af_specific
op_member_access_from_pointer
id|syn_recv_sock
c_func
(paren
id|sk
comma
id|skb
comma
id|req
comma
id|dst
)paren
suffix:semicolon
id|req-&gt;sk
op_assign
id|sk
suffix:semicolon
multiline_comment|/* Queue up for accept() */
id|tcp_synq_queue
c_func
(paren
id|tp
comma
id|req
)paren
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
r_struct
id|sock
op_star
DECL|function|cookie_v4_check
id|cookie_v4_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_options
op_star
id|opt
)paren
(brace
id|__u32
id|cookie
op_assign
id|ntohl
c_func
(paren
id|skb-&gt;h.th-&gt;ack_seq
)paren
op_minus
l_int|1
suffix:semicolon
r_struct
id|open_request
op_star
id|req
suffix:semicolon
r_int
id|mss
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
id|__u8
id|rcv_wscale
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysctl_tcp_syncookies
)paren
r_return
id|sk
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;h.th-&gt;ack
)paren
r_return
id|sk
suffix:semicolon
id|mss
op_assign
id|cookie_check
c_func
(paren
id|skb
comma
id|cookie
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mss
op_eq
l_int|0
)paren
(brace
id|net_statistics.SyncookiesFailed
op_increment
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
id|net_statistics.SyncookiesRecv
op_increment
suffix:semicolon
id|req
op_assign
id|tcp_openreq_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|req-&gt;rcv_isn
op_assign
id|htonl
c_func
(paren
id|skb-&gt;h.th-&gt;seq
)paren
op_minus
l_int|1
suffix:semicolon
id|req-&gt;snt_isn
op_assign
id|cookie
suffix:semicolon
id|req-&gt;mss
op_assign
id|mss
suffix:semicolon
id|req-&gt;rmt_port
op_assign
id|skb-&gt;h.th-&gt;source
suffix:semicolon
id|req-&gt;af.v4_req.loc_addr
op_assign
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
id|req-&gt;af.v4_req.rmt_addr
op_assign
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
id|req
op_member_access_from_pointer
r_class
op_assign
op_amp
id|or_ipv4
suffix:semicolon
multiline_comment|/* for savety */
multiline_comment|/* We throwed the options of the initial SYN away, so we hope&n;&t; * the ACK carries the same options again (see RFC1122 4.2.3.8)&n;&t; */
r_if
c_cond
(paren
id|opt
op_logical_and
id|opt-&gt;optlen
)paren
(brace
r_int
id|opt_size
op_assign
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
id|opt-&gt;optlen
suffix:semicolon
id|req-&gt;af.v4_req.opt
op_assign
id|kmalloc
c_func
(paren
id|opt_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;af.v4_req.opt
)paren
(brace
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
id|req-&gt;af.v4_req.opt
comma
id|skb
)paren
)paren
(brace
id|kfree_s
c_func
(paren
id|req-&gt;af.v4_req.opt
comma
id|opt_size
)paren
suffix:semicolon
id|req-&gt;af.v4_req.opt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
id|req-&gt;af.v4_req.opt
op_assign
l_int|NULL
suffix:semicolon
id|req-&gt;snd_wscale
op_assign
id|req-&gt;rcv_wscale
op_assign
id|req-&gt;tstamp_ok
op_assign
l_int|0
suffix:semicolon
id|req-&gt;wscale_ok
op_assign
l_int|0
suffix:semicolon
id|req-&gt;expires
op_assign
l_int|0UL
suffix:semicolon
id|req-&gt;retrans
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We need to lookup the route here to get at the correct&n;&t; * window size. We should better make sure that the window size&n;&t; * hasn&squot;t changed since we received the original syn, but I see&n;&t; * no easy way to do this. &n;&t; */
r_if
c_cond
(paren
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|opt
op_logical_and
id|opt-&gt;srr
ques
c_cond
id|opt-&gt;faddr
suffix:colon
id|req-&gt;af.v4_req.rmt_addr
comma
id|req-&gt;af.v4_req.loc_addr
comma
id|sk-&gt;ip_tos
op_or
id|RTO_CONN
comma
l_int|0
)paren
)paren
(brace
id|tcp_openreq_free
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Try to redo what tcp_v4_send_synack did. */
id|req-&gt;window_clamp
op_assign
id|rt-&gt;u.dst.window
suffix:semicolon
id|tcp_select_initial_window
c_func
(paren
id|sock_rspace
c_func
(paren
id|sk
)paren
op_div
l_int|2
comma
id|req-&gt;mss
comma
op_amp
id|req-&gt;rcv_wnd
comma
op_amp
id|req-&gt;window_clamp
comma
l_int|0
comma
op_amp
id|rcv_wscale
)paren
suffix:semicolon
id|req-&gt;rcv_wscale
op_assign
id|rcv_wscale
suffix:semicolon
r_return
id|get_cookie_sock
c_func
(paren
id|sk
comma
id|skb
comma
id|req
comma
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
