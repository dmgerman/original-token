multiline_comment|/*&n; * net/sched/sch_prio.c&t;Simple 3-band priority &quot;scheduler&quot;.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
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
multiline_comment|/* New N-band generic scheduler */
DECL|struct|prio_sched_data
r_struct
id|prio_sched_data
(brace
DECL|member|qbytes
r_int
id|qbytes
suffix:semicolon
DECL|member|bands
r_int
id|bands
suffix:semicolon
DECL|member|prio2band
id|u8
id|prio2band
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|queues
r_struct
id|Qdisc
op_star
id|queues
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|prio_enqueue
id|prio_enqueue
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
id|prio_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|prio_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_int
id|prio
op_assign
id|q-&gt;prio2band
(braket
id|skb-&gt;priority
op_amp
l_int|7
)braket
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
id|qdisc
op_assign
id|q-&gt;queues
(braket
id|prio
)braket
suffix:semicolon
r_if
c_cond
(paren
id|qdisc
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|skb
comma
id|qdisc
)paren
op_eq
l_int|0
)paren
(brace
id|q-&gt;qbytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|prio_dequeue
id|prio_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|prio_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_int
id|prio
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
(brace
id|qdisc
op_assign
id|q-&gt;queues
(braket
id|prio
)braket
suffix:semicolon
id|skb
op_assign
id|qdisc
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|qdisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|q-&gt;qbytes
op_sub_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|prio_reset
id|prio_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|prio_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
id|qdisc_reset
c_func
(paren
id|q-&gt;queues
(braket
id|prio
)braket
)paren
suffix:semicolon
id|q-&gt;qbytes
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|prio_destroy
id|prio_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|prio_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
(brace
id|qdisc_destroy
c_func
(paren
id|q-&gt;queues
(braket
id|prio
)braket
)paren
suffix:semicolon
id|q-&gt;queues
(braket
id|prio
)braket
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
)brace
)brace
DECL|function|prio_init
r_static
r_int
id|prio_init
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
r_const
r_static
id|u8
id|prio2band
(braket
l_int|8
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
suffix:semicolon
r_int
id|i
suffix:semicolon
id|q
op_assign
(paren
r_struct
id|prio_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|q-&gt;bands
op_assign
l_int|3
suffix:semicolon
id|memcpy
c_func
(paren
id|q-&gt;prio2band
comma
id|prio2band
comma
r_sizeof
(paren
id|prio2band
)paren
)paren
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
id|q-&gt;bands
suffix:semicolon
id|i
op_increment
)paren
id|q-&gt;queues
(braket
id|i
)braket
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|prio_ops
r_struct
id|Qdisc_ops
id|prio_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;prio&quot;
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|prio_sched_data
)paren
comma
id|prio_enqueue
comma
id|prio_dequeue
comma
id|prio_reset
comma
id|prio_destroy
comma
id|prio_init
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
id|prio_ops
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