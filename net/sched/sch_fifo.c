multiline_comment|/*&n; * net/sched/sch_fifo.c&t;Simple FIFO &quot;scheduler&quot;&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
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
multiline_comment|/* 1 band FIFO pseudo-&quot;scheduler&quot; */
DECL|struct|fifo_sched_data
r_struct
id|fifo_sched_data
(brace
DECL|member|qmaxbytes
r_int
id|qmaxbytes
suffix:semicolon
DECL|member|qmaxlen
r_int
id|qmaxlen
suffix:semicolon
DECL|member|qbytes
r_int
id|qbytes
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|bfifo_enqueue
id|bfifo_enqueue
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
id|fifo_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|fifo_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qbytes
op_le
id|q-&gt;qmaxbytes
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
id|q-&gt;qbytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|bfifo_dequeue
id|bfifo_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|fifo_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|fifo_sched_data
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
id|skb_dequeue
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
id|q-&gt;qbytes
op_sub_assign
id|skb-&gt;len
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
r_static
r_void
DECL|function|bfifo_reset
id|bfifo_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|fifo_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|fifo_sched_data
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
id|skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|q-&gt;qbytes
op_sub_assign
id|skb-&gt;len
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q-&gt;qbytes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fifo_reset: qbytes=%d&bslash;n&quot;
comma
id|q-&gt;qbytes
)paren
suffix:semicolon
id|q-&gt;qbytes
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|pfifo_enqueue
id|pfifo_enqueue
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
id|fifo_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|fifo_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;q.qlen
op_le
id|q-&gt;qmaxlen
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|pfifo_dequeue
id|pfifo_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_return
id|skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pfifo_reset
id|pfifo_reset
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
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|fifo_init
r_static
r_int
id|fifo_init
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
multiline_comment|/* int bytes, int pkts */
)paren
(brace
r_struct
id|fifo_sched_data
op_star
id|q
suffix:semicolon
multiline_comment|/*&n;&t;struct device *dev = sch-&gt;dev;&n; */
id|q
op_assign
(paren
r_struct
id|fifo_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t;if (pkts&lt;0)&n;&t;&t;pkts = dev-&gt;tx_queue_len;&n;&t;if (bytes&lt;0)&n;&t;&t;bytes = pkts*dev-&gt;mtu;&n;&t;q-&gt;qmaxbytes = bytes;&n;&t;q-&gt;qmaxlen = pkts;&n; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pfifo_ops
r_struct
id|Qdisc_ops
id|pfifo_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;pfifo&quot;
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fifo_sched_data
)paren
comma
id|pfifo_enqueue
comma
id|pfifo_dequeue
comma
id|pfifo_reset
comma
l_int|NULL
comma
id|fifo_init
comma
)brace
suffix:semicolon
DECL|variable|bfifo_ops
r_struct
id|Qdisc_ops
id|bfifo_ops
op_assign
(brace
l_int|NULL
comma
l_string|&quot;pfifo&quot;
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fifo_sched_data
)paren
comma
id|bfifo_enqueue
comma
id|bfifo_dequeue
comma
id|bfifo_reset
comma
l_int|NULL
comma
id|fifo_init
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
id|pfifo_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|err
op_assign
id|register_qdisc
c_func
(paren
op_amp
id|bfifo_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|unregister_qdisc
c_func
(paren
op_amp
id|pfifo_ops
)paren
suffix:semicolon
)brace
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