macro_line|#ifndef _NET_TCP_ECN_H_
DECL|macro|_NET_TCP_ECN_H_
mdefine_line|#define _NET_TCP_ECN_H_ 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_INET_ECN
macro_line|#include &lt;net/inet_ecn.h&gt;
DECL|macro|TCP_HP_BITS
mdefine_line|#define TCP_HP_BITS (~(TCP_RESERVED_BITS|TCP_FLAG_PSH)|TCP_FLAG_ECE|TCP_FLAG_CWR)
DECL|macro|TCP_ECN_OK
mdefine_line|#define&t;TCP_ECN_OK&t;&t;1
DECL|macro|TCP_ECN_QUEUE_CWR
mdefine_line|#define TCP_ECN_QUEUE_CWR&t;2
DECL|macro|TCP_ECN_DEMAND_CWR
mdefine_line|#define TCP_ECN_DEMAND_CWR&t;4
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_queue_cwr
id|TCP_ECN_queue_cwr
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
id|tp-&gt;ecn_flags
op_or_assign
id|TCP_ECN_QUEUE_CWR
suffix:semicolon
)brace
multiline_comment|/* Output functions */
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_send_synack
id|TCP_ECN_send_synack
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_and_assign
op_complement
id|TCPCB_FLAG_CWR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
)paren
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_and_assign
op_complement
id|TCPCB_FLAG_ECE
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_send_syn
id|TCP_ECN_send_syn
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|tp-&gt;ecn_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sysctl_tcp_ecn
)paren
(brace
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|TCPCB_FLAG_ECE
op_or
id|TCPCB_FLAG_CWR
suffix:semicolon
id|tp-&gt;ecn_flags
op_assign
id|TCP_ECN_OK
suffix:semicolon
)brace
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_make_synack
id|TCP_ECN_make_synack
c_func
(paren
r_struct
id|open_request
op_star
id|req
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;ecn_ok
)paren
id|th-&gt;ece
op_assign
l_int|1
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_send
id|TCP_ECN_send
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|tcp_header_len
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
(brace
multiline_comment|/* Not-retransmitted data segment: set ECT and inject CWR. */
r_if
c_cond
(paren
id|skb-&gt;len
op_ne
id|tcp_header_len
op_logical_and
op_logical_neg
id|before
c_func
(paren
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|seq
comma
id|tp-&gt;snd_nxt
)paren
)paren
(brace
id|INET_ECN_xmit
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_QUEUE_CWR
)paren
(brace
id|tp-&gt;ecn_flags
op_and_assign
op_complement
id|TCP_ECN_QUEUE_CWR
suffix:semicolon
id|skb-&gt;h.th-&gt;cwr
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* ACK or retransmitted segment: clear ECT|CE */
id|INET_ECN_dontxmit
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_DEMAND_CWR
)paren
id|skb-&gt;h.th-&gt;ece
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Input functions */
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_accept_cwr
id|TCP_ECN_accept_cwr
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;h.th-&gt;cwr
)paren
id|tp-&gt;ecn_flags
op_and_assign
op_complement
id|TCP_ECN_DEMAND_CWR
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_check_ce
id|TCP_ECN_check_ce
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
(brace
r_if
c_cond
(paren
id|INET_ECN_is_ce
c_func
(paren
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
id|tp-&gt;ecn_flags
op_or_assign
id|TCP_ECN_DEMAND_CWR
suffix:semicolon
multiline_comment|/* Funny extension: if ECT is not set on a segment,&n;&t;&t; * it is surely retransmit. It is not in ECN RFC,&n;&t;&t; * but Linux follows this rule. */
r_else
r_if
c_cond
(paren
op_logical_neg
id|INET_ECN_is_capable
c_func
(paren
(paren
id|TCP_SKB_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
)paren
id|tcp_enter_quickack_mode
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_rcv_synack
id|TCP_ECN_rcv_synack
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
op_logical_and
(paren
op_logical_neg
id|th-&gt;ece
op_logical_or
id|th-&gt;cwr
)paren
)paren
id|tp-&gt;ecn_flags
op_and_assign
op_complement
id|TCP_ECN_OK
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_rcv_syn
id|TCP_ECN_rcv_syn
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
op_logical_and
(paren
op_logical_neg
id|th-&gt;ece
op_logical_or
op_logical_neg
id|th-&gt;cwr
)paren
)paren
id|tp-&gt;ecn_flags
op_and_assign
op_complement
id|TCP_ECN_OK
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|TCP_ECN_rcv_ecn_echo
id|TCP_ECN_rcv_ecn_echo
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
id|th-&gt;ece
op_logical_and
op_logical_neg
id|th-&gt;syn
op_logical_and
(paren
id|tp-&gt;ecn_flags
op_amp
id|TCP_ECN_OK
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_openreq_child
id|TCP_ECN_openreq_child
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|open_request
op_star
id|req
)paren
(brace
id|tp-&gt;ecn_flags
op_assign
id|req-&gt;ecn_ok
ques
c_cond
id|TCP_ECN_OK
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|TCP_ECN_create_request
id|TCP_ECN_create_request
c_func
(paren
r_struct
id|open_request
op_star
id|req
comma
r_struct
id|tcphdr
op_star
id|th
)paren
(brace
r_if
c_cond
(paren
id|sysctl_tcp_ecn
op_logical_and
id|th-&gt;ece
op_logical_and
id|th-&gt;cwr
)paren
id|req-&gt;ecn_ok
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|macro|TCP_HP_BITS
mdefine_line|#define TCP_HP_BITS (~(TCP_RESERVED_BITS|TCP_FLAG_PSH))
DECL|macro|TCP_ECN_send_syn
mdefine_line|#define TCP_ECN_send_syn(x...)&t;&t;do { } while (0)
DECL|macro|TCP_ECN_send_synack
mdefine_line|#define TCP_ECN_send_synack(x...)&t;do { } while (0)
DECL|macro|TCP_ECN_make_synack
mdefine_line|#define TCP_ECN_make_synack(x...)&t;do { } while (0)
DECL|macro|TCP_ECN_send
mdefine_line|#define TCP_ECN_send(x...)&t;&t;do { } while (0)
DECL|macro|TCP_ECN_queue_cwr
mdefine_line|#define TCP_ECN_queue_cwr(x...)&t;&t;do { } while (0)
DECL|macro|TCP_ECN_accept_cwr
mdefine_line|#define TCP_ECN_accept_cwr(x...)&t;do { } while (0)
DECL|macro|TCP_ECN_check_ce
mdefine_line|#define TCP_ECN_check_ce(x...)&t;&t;do { } while (0)
DECL|macro|TCP_ECN_rcv_synack
mdefine_line|#define TCP_ECN_rcv_synack(x...)&t;do { } while (0)
DECL|macro|TCP_ECN_rcv_syn
mdefine_line|#define TCP_ECN_rcv_syn(x...)&t;&t;do { } while (0)
DECL|macro|TCP_ECN_rcv_ecn_echo
mdefine_line|#define TCP_ECN_rcv_ecn_echo(x...)&t;(0)
DECL|macro|TCP_ECN_openreq_child
mdefine_line|#define TCP_ECN_openreq_child(x...)&t;do { } while (0)
DECL|macro|TCP_ECN_create_request
mdefine_line|#define TCP_ECN_create_request(x...)&t;do { } while (0)
macro_line|#endif
macro_line|#endif
eof
