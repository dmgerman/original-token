multiline_comment|/*&n; * net/sched/sch_tbf.c&t;Token Bucket Filter.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&t;Simple Token Bucket Filter.&n;&t;=======================================&n;&n;&t;SOURCE.&n;&n;&t;None.&n;&n;&t;ALGORITHM.&n;&n;&t;Sequence of packets satisfy token bucket filter with&n;&t;rate $r$ and depth $b$, if all the numbers defined by:&n;&t;&bslash;begin{eqnarray*}&n;&t;n_0 &amp;=&amp; b, &bslash;&bslash;&n;&t;n_i &amp;=&amp; {&bslash;rm max} ( b, n_{i-1} + r*(t_i-t_{i-1}) - L_i ),&n;&t;&bslash;end{eqnarray*}&n;&t;where $t_i$ --- departure time of $i$-th packet and&n;&t;$L_i$ -- its length, never less than zero.&n;&n;&t;It is convenient to rescale $n_i$ by factor $r$, so&n;&t;that the sequence has &quot;canonical&quot; form:&n;&t;&bslash;[&n;&t;n_0 = b/r,&n;&t;n_i = max { b/r, n_{i-1} + t_i - t_{i-1} - L_i/r },&n;&t;&bslash;]&n;&n;&t;If a packet has n_i &lt; 0, we throttle filter&n;&t;by $-n_i$ usecs.&n;&n;&t;NOTES.&n;&n;&t;If TBF throttles, it starts watchdog timer, which will wake up it&n;&t;after 0...10 msec.&n;&t;If no new packets will arrive during this period,&n;&t;or device will not be awaken by EOI for previous packet,&n;&t;tbf could stop its activity for 10 msec.&n;&n;&t;It means that tbf will sometimes introduce pathological&n;&t;10msec delays to flow corresponding to rate*10msec bytes.&n;&t;For 10Mbit/sec flow it is about 12Kb, on 100Mbit/sec -- ~100Kb.&n;&t;This number puts lower reasonbale bound on token bucket depth,&n;&t;but even if depth is larger traffic is erratic at large rates.&n;&n;&t;This problem is not specific for THIS implementation. Really,&n;&t;there exists statement that any attempt to shape traffic&n;&t;in transit will increase delays and jitter much more than&n;&t;we expected naively.&n;&n;&t;Particularily, it means that delay/jitter sensitive traffic&n;&t;MUST NOT be shaped. Cf. CBQ (wrong) and CSZ (correct) approaches.&n;*/
DECL|struct|tbf_sched_data
r_struct
id|tbf_sched_data
(brace
multiline_comment|/* Parameters */
DECL|member|cell_log
r_int
id|cell_log
suffix:semicolon
multiline_comment|/* 1&lt;&lt;cell_log is quantum of packet size */
DECL|member|L_tab
r_int
r_int
id|L_tab
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Lookup table for L/B values */
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
multiline_comment|/* Token bucket depth/B: MUST BE &gt;= MTU/B */
DECL|member|max_bytes
r_int
r_int
id|max_bytes
suffix:semicolon
multiline_comment|/* Maximal length of backlog: bytes */
multiline_comment|/* Variables */
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
multiline_comment|/* Current length of backlog */
DECL|member|tokens
r_int
r_int
id|tokens
suffix:semicolon
multiline_comment|/* Current number of tokens */
DECL|member|t_c
id|psched_time_t
id|t_c
suffix:semicolon
multiline_comment|/* Time check-point */
DECL|member|wd_timer
r_struct
id|timer_list
id|wd_timer
suffix:semicolon
multiline_comment|/* Watchdog timer */
)brace
suffix:semicolon
DECL|macro|L2T
mdefine_line|#define L2T(q,L) ((q)-&gt;L_tab[(L)&gt;&gt;(q)-&gt;cell_log])
r_static
r_int
DECL|function|tbf_enqueue
id|tbf_enqueue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|tbf_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|tbf_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|__skb_queue_tail
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q-&gt;bytes
op_add_assign
id|skb-&gt;len
)paren
op_le
id|q-&gt;max_bytes
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Drop action: undo the things that we just made,&n;&t; * i.e. make tail drop&n;&t; */
id|__skb_unlink
c_func
(paren
id|skb
comma
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
id|q-&gt;bytes
op_sub_assign
id|skb-&gt;len
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tbf_watchdog
r_static
r_void
id|tbf_watchdog
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|Qdisc
op_star
id|sch
op_assign
(paren
r_struct
id|Qdisc
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|tbf_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|tbf_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|q-&gt;wd_timer.function
op_assign
l_int|NULL
suffix:semicolon
id|qdisc_wakeup
c_func
(paren
id|sch-&gt;dev
)paren
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|tbf_dequeue
id|tbf_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|tbf_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|tbf_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|psched_time_t
id|now
suffix:semicolon
r_int
id|toks
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|now
)paren
suffix:semicolon
id|toks
op_assign
id|PSCHED_TDIFF_SAFE
c_func
(paren
id|now
comma
id|q-&gt;t_c
comma
id|q-&gt;depth
comma
l_int|0
)paren
op_plus
id|q-&gt;tokens
op_minus
id|L2T
c_func
(paren
id|q
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|toks
op_ge
l_int|0
)paren
(brace
id|q-&gt;t_c
op_assign
id|now
suffix:semicolon
id|q-&gt;tokens
op_assign
id|toks
op_le
id|q-&gt;depth
ques
c_cond
id|toks
suffix:colon
id|q-&gt;depth
suffix:semicolon
id|q-&gt;bytes
op_sub_assign
id|skb-&gt;len
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* Maybe, we have in queue a shorter packet,&n;&t;&t;   which can be sent now. It sounds cool,&n;&t;&t;   but, however, wrong in principle.&n;&t;&t;   We MUST NOT reorder packets in these curcumstances.&n;&n;&t;&t;   Really, if we splitted flow to independent&n;&t;&t;   subflows, it would be very good solution.&n;&t;&t;   Look at sch_csz.c.&n;&t;&t; */
id|__skb_queue_head
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch-&gt;dev-&gt;tbusy
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;wd_timer.function
)paren
id|del_timer
c_func
(paren
op_amp
id|q-&gt;wd_timer
)paren
suffix:semicolon
id|q-&gt;wd_timer.function
op_assign
id|tbf_watchdog
suffix:semicolon
id|q-&gt;wd_timer.expires
op_assign
id|jiffies
op_plus
id|PSCHED_US2JIFFIE
c_func
(paren
op_minus
id|toks
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|q-&gt;wd_timer
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|tbf_reset
id|tbf_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|tbf_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|tbf_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
)paren
op_ne
l_int|NULL
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|q-&gt;bytes
op_assign
l_int|0
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;t_c
)paren
suffix:semicolon
id|q-&gt;tokens
op_assign
id|q-&gt;depth
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;wd_timer.function
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|q-&gt;wd_timer
)paren
suffix:semicolon
id|q-&gt;wd_timer.function
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|tbf_init
r_static
r_int
id|tbf_init
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|tbf_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|tbf_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|tbfctl
op_star
id|ctl
op_assign
(paren
r_struct
id|tbfctl
op_star
)paren
id|arg
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;t_c
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|q-&gt;wd_timer
)paren
suffix:semicolon
id|q-&gt;wd_timer.function
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;wd_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sch
suffix:semicolon
r_if
c_cond
(paren
id|ctl
)paren
(brace
id|q-&gt;max_bytes
op_assign
id|ctl-&gt;bytes
suffix:semicolon
id|q-&gt;depth
op_assign
id|ctl-&gt;depth
suffix:semicolon
id|q-&gt;tokens
op_assign
id|q-&gt;tokens
suffix:semicolon
id|q-&gt;cell_log
op_assign
id|ctl-&gt;cell_log
suffix:semicolon
id|memcpy
c_func
(paren
id|q-&gt;L_tab
comma
id|ctl-&gt;L_tab
comma
l_int|256
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tbf_ops
r_struct
id|Qdisc_ops
id|tbf_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;tbf&quot;
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tbf_sched_data
)paren
comma
id|tbf_enqueue
comma
id|tbf_dequeue
comma
id|tbf_reset
comma
l_int|NULL
comma
id|tbf_init
comma
l_int|NULL
comma
)brace
suffix:semicolon
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* Load once and never free it. */
id|MOD_INC_USE_COUNT
suffix:semicolon
id|err
op_assign
id|register_qdisc
c_func
(paren
op_amp
id|tbf_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|err
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
)brace
macro_line|#endif
eof