multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The IP fragmentation functionality.&n; *&t;&t;&n; * Version:&t;$Id: ip_fragment.c,v 1.50 2000/07/07 22:29:42 davem Exp $&n; *&n; * Authors:&t;Fred N. van Kempen &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;Split from ip.c , see ip_input.c for history.&n; *&t;&t;David S. Miller :&t;Begin massive cleanup...&n; *&t;&t;Andi Kleen&t;:&t;Add sysctls.&n; *&t;&t;xxxx&t;&t;:&t;Overlapfrag bug.&n; *&t;&t;Ultima          :       ip_expire() kernel panic.&n; *&t;&t;Bill Hawes&t;:&t;Frag accounting and evictor fixes.&n; *&t;&t;John McDonald&t;:&t;0 length frag bug.&n; *&t;&t;Alexey Kuznetsov:&t;SMP races, threading, cleanup.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
multiline_comment|/* NOTE. Logic of IP defragmentation is parallel to corresponding IPv6&n; * code now. If you change something here, _PLEASE_ update ipv6/reassembly.c&n; * as well. Or notify me, at least. --ANK&n; */
multiline_comment|/* Fragment cache limits. We will commit 256K at one time. Should we&n; * cross that limit we will prune down to 192K. This should cope with&n; * even the most extreme cases without allowing an attacker to measurably&n; * harm machine performance.&n; */
DECL|variable|sysctl_ipfrag_high_thresh
r_int
id|sysctl_ipfrag_high_thresh
op_assign
l_int|256
op_star
l_int|1024
suffix:semicolon
DECL|variable|sysctl_ipfrag_low_thresh
r_int
id|sysctl_ipfrag_low_thresh
op_assign
l_int|192
op_star
l_int|1024
suffix:semicolon
DECL|variable|sysctl_ipfrag_time
r_int
id|sysctl_ipfrag_time
op_assign
id|IP_FRAG_TIME
suffix:semicolon
DECL|struct|ipfrag_skb_cb
r_struct
id|ipfrag_skb_cb
(brace
DECL|member|h
r_struct
id|inet_skb_parm
id|h
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FRAG_CB
mdefine_line|#define FRAG_CB(skb)&t;((struct ipfrag_skb_cb*)((skb)-&gt;cb))
multiline_comment|/* Describe an entry in the &quot;incomplete datagrams&quot; queue. */
DECL|struct|ipq
r_struct
id|ipq
(brace
DECL|member|next
r_struct
id|ipq
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list pointers&t;&t;&t;*/
DECL|member|saddr
id|u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|u32
id|daddr
suffix:semicolon
DECL|member|id
id|u16
id|id
suffix:semicolon
DECL|member|protocol
id|u8
id|protocol
suffix:semicolon
DECL|member|last_in
id|u8
id|last_in
suffix:semicolon
DECL|macro|COMPLETE
mdefine_line|#define COMPLETE&t;&t;4
DECL|macro|FIRST_IN
mdefine_line|#define FIRST_IN&t;&t;2
DECL|macro|LAST_IN
mdefine_line|#define LAST_IN&t;&t;&t;1
DECL|member|fragments
r_struct
id|sk_buff
op_star
id|fragments
suffix:semicolon
multiline_comment|/* linked list of received fragments&t;*/
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* total length of original datagram&t;*/
DECL|member|meat
r_int
id|meat
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* when will this queue expire?&t;&t;*/
DECL|member|pprev
r_struct
id|ipq
op_star
op_star
id|pprev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device - for icmp replies */
)brace
suffix:semicolon
multiline_comment|/* Hash table. */
DECL|macro|IPQ_HASHSZ
mdefine_line|#define IPQ_HASHSZ&t;64
multiline_comment|/* Per-bucket lock is easy to add now. */
DECL|variable|ipq_hash
r_static
r_struct
id|ipq
op_star
id|ipq_hash
(braket
id|IPQ_HASHSZ
)braket
suffix:semicolon
DECL|variable|ipfrag_lock
r_static
id|rwlock_t
id|ipfrag_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|ip_frag_nqueues
r_int
id|ip_frag_nqueues
op_assign
l_int|0
suffix:semicolon
DECL|function|__ipq_unlink
r_static
id|__inline__
r_void
id|__ipq_unlink
c_func
(paren
r_struct
id|ipq
op_star
id|qp
)paren
(brace
r_if
c_cond
(paren
id|qp-&gt;next
)paren
(brace
id|qp-&gt;next-&gt;pprev
op_assign
id|qp-&gt;pprev
suffix:semicolon
)brace
op_star
id|qp-&gt;pprev
op_assign
id|qp-&gt;next
suffix:semicolon
id|ip_frag_nqueues
op_decrement
suffix:semicolon
)brace
DECL|function|ipq_unlink
r_static
id|__inline__
r_void
id|ipq_unlink
c_func
(paren
r_struct
id|ipq
op_star
id|ipq
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
id|__ipq_unlink
c_func
(paren
id|ipq
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Was:&t;((((id) &gt;&gt; 1) ^ (saddr) ^ (daddr) ^ (prot)) &amp; (IPQ_HASHSZ - 1))&n; *&n; * I see, I see evil hand of bigendian mafia. On Intel all the packets hit&n; * one hash bucket with this hash function. 8)&n; */
DECL|function|ipqhashfn
r_static
id|__inline__
r_int
r_int
id|ipqhashfn
c_func
(paren
id|u16
id|id
comma
id|u32
id|saddr
comma
id|u32
id|daddr
comma
id|u8
id|prot
)paren
(brace
r_int
r_int
id|h
op_assign
id|saddr
op_xor
id|daddr
suffix:semicolon
id|h
op_xor_assign
(paren
id|h
op_rshift
l_int|16
)paren
op_xor
id|id
suffix:semicolon
id|h
op_xor_assign
(paren
id|h
op_rshift
l_int|8
)paren
op_xor
id|prot
suffix:semicolon
r_return
id|h
op_amp
(paren
id|IPQ_HASHSZ
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|ip_frag_mem
id|atomic_t
id|ip_frag_mem
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Memory used for fragments */
multiline_comment|/* Memory Tracking Functions. */
DECL|function|frag_kfree_skb
r_extern
id|__inline__
r_void
id|frag_kfree_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|atomic_sub
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|frag_free_queue
r_extern
id|__inline__
r_void
id|frag_free_queue
c_func
(paren
r_struct
id|ipq
op_star
id|qp
)paren
(brace
id|atomic_sub
c_func
(paren
r_sizeof
(paren
r_struct
id|ipq
)paren
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|qp
)paren
suffix:semicolon
)brace
DECL|function|frag_alloc_queue
r_extern
id|__inline__
r_struct
id|ipq
op_star
id|frag_alloc_queue
c_func
(paren
r_void
)paren
(brace
r_struct
id|ipq
op_star
id|qp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipq
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qp
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|atomic_add
c_func
(paren
r_sizeof
(paren
r_struct
id|ipq
)paren
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
multiline_comment|/* Destruction primitives. */
multiline_comment|/* Complete destruction of ipq. */
DECL|function|ip_frag_destroy
r_static
r_void
id|ip_frag_destroy
c_func
(paren
r_struct
id|ipq
op_star
id|qp
)paren
(brace
r_struct
id|sk_buff
op_star
id|fp
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|qp-&gt;last_in
op_amp
id|COMPLETE
)paren
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|del_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Release all fragment data. */
id|fp
op_assign
id|qp-&gt;fragments
suffix:semicolon
r_while
c_loop
(paren
id|fp
)paren
(brace
r_struct
id|sk_buff
op_star
id|xp
op_assign
id|fp-&gt;next
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|fp
)paren
suffix:semicolon
id|fp
op_assign
id|xp
suffix:semicolon
)brace
multiline_comment|/* Finally, release the queue descriptor itself. */
id|frag_free_queue
c_func
(paren
id|qp
)paren
suffix:semicolon
)brace
DECL|function|ipq_put
r_static
id|__inline__
r_void
id|ipq_put
c_func
(paren
r_struct
id|ipq
op_star
id|ipq
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ipq-&gt;refcnt
)paren
)paren
id|ip_frag_destroy
c_func
(paren
id|ipq
)paren
suffix:semicolon
)brace
multiline_comment|/* Kill ipq entry. It is not destroyed immediately,&n; * because caller (and someone more) holds reference count.&n; */
DECL|function|ipq_kill
r_static
id|__inline__
r_void
id|ipq_kill
c_func
(paren
r_struct
id|ipq
op_star
id|ipq
)paren
(brace
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|ipq-&gt;timer
)paren
)paren
id|atomic_dec
c_func
(paren
op_amp
id|ipq-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipq-&gt;last_in
op_amp
id|COMPLETE
)paren
)paren
(brace
id|ipq_unlink
c_func
(paren
id|ipq
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ipq-&gt;refcnt
)paren
suffix:semicolon
id|ipq-&gt;last_in
op_or_assign
id|COMPLETE
suffix:semicolon
)brace
)brace
multiline_comment|/* Memory limiting on fragments.  Evictor trashes the oldest &n; * fragment queue until we are back under the low threshold.&n; */
DECL|function|ip_evictor
r_static
r_void
id|ip_evictor
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|progress
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ip_frag_mem
)paren
op_le
id|sysctl_ipfrag_low_thresh
)paren
r_return
suffix:semicolon
id|progress
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: Make LRU queue of frag heads. -DaveM */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IPQ_HASHSZ
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
r_if
c_cond
(paren
id|ipq_hash
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|qp
op_assign
id|ipq_hash
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* find the oldest queue for this hash bucket */
r_while
c_loop
(paren
id|qp-&gt;next
)paren
id|qp
op_assign
id|qp-&gt;next
suffix:semicolon
id|__ipq_unlink
c_func
(paren
id|qp
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
)paren
id|atomic_dec
c_func
(paren
op_amp
id|qp-&gt;refcnt
)paren
suffix:semicolon
id|qp-&gt;last_in
op_or_assign
id|COMPLETE
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
id|ipq_put
c_func
(paren
id|qp
)paren
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmFails
)paren
suffix:semicolon
id|progress
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|progress
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Oops, a fragment queue timed out.  Kill it and send an ICMP reply.&n; */
DECL|function|ip_expire
r_static
r_void
id|ip_expire
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ipq
op_star
id|qp
op_assign
(paren
r_struct
id|ipq
op_star
)paren
id|arg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;last_in
op_amp
id|COMPLETE
)paren
r_goto
id|out
suffix:semicolon
id|ipq_kill
c_func
(paren
id|qp
)paren
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmTimeout
)paren
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmFails
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|qp-&gt;last_in
op_amp
id|FIRST_IN
)paren
op_logical_and
id|qp-&gt;fragments
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Send an ICMP &quot;Fragment Reassembly Timeout&quot; message. */
id|icmp_send
c_func
(paren
id|qp-&gt;fragments
comma
id|ICMP_TIME_EXCEEDED
comma
id|ICMP_EXC_FRAGTIME
comma
l_int|0
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
id|ipq_put
c_func
(paren
id|qp
)paren
suffix:semicolon
)brace
multiline_comment|/* Creation primitives. */
DECL|function|ip_frag_intern
r_static
r_struct
id|ipq
op_star
id|ip_frag_intern
c_func
(paren
r_int
r_int
id|hash
comma
r_struct
id|ipq
op_star
id|qp_in
)paren
(brace
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* With SMP race we have to recheck hash table, because&n;&t; * such entry could be created on other cpu, while we&n;&t; * promoted read lock to write lock.&n;&t; */
r_for
c_loop
(paren
id|qp
op_assign
id|ipq_hash
(braket
id|hash
)braket
suffix:semicolon
id|qp
suffix:semicolon
id|qp
op_assign
id|qp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|qp-&gt;id
op_eq
id|qp_in-&gt;id
op_logical_and
id|qp-&gt;saddr
op_eq
id|qp_in-&gt;saddr
op_logical_and
id|qp-&gt;daddr
op_eq
id|qp_in-&gt;daddr
op_logical_and
id|qp-&gt;protocol
op_eq
id|qp_in-&gt;protocol
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|qp-&gt;refcnt
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
id|qp_in-&gt;last_in
op_or_assign
id|COMPLETE
suffix:semicolon
id|ipq_put
c_func
(paren
id|qp_in
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
)brace
macro_line|#endif
id|qp
op_assign
id|qp_in
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|qp-&gt;refcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|qp-&gt;next
op_assign
id|ipq_hash
(braket
id|hash
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|qp-&gt;next-&gt;pprev
op_assign
op_amp
id|qp-&gt;next
suffix:semicolon
)brace
id|ipq_hash
(braket
id|hash
)braket
op_assign
id|qp
suffix:semicolon
id|qp-&gt;pprev
op_assign
op_amp
id|ipq_hash
(braket
id|hash
)braket
suffix:semicolon
id|ip_frag_nqueues
op_increment
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
multiline_comment|/* Add an entry to the &squot;ipq&squot; queue for a newly received IP datagram. */
DECL|function|ip_frag_create
r_static
r_struct
id|ipq
op_star
id|ip_frag_create
c_func
(paren
r_int
id|hash
comma
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|qp
op_assign
id|frag_alloc_queue
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|out_nomem
suffix:semicolon
id|qp-&gt;protocol
op_assign
id|iph-&gt;protocol
suffix:semicolon
id|qp-&gt;last_in
op_assign
l_int|0
suffix:semicolon
id|qp-&gt;id
op_assign
id|iph-&gt;id
suffix:semicolon
id|qp-&gt;saddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|qp-&gt;daddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|qp-&gt;len
op_assign
l_int|0
suffix:semicolon
id|qp-&gt;meat
op_assign
l_int|0
suffix:semicolon
id|qp-&gt;fragments
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initialize a timer for this entry. */
id|init_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
id|qp-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|qp
suffix:semicolon
multiline_comment|/* pointer to queue&t;*/
id|qp-&gt;timer.function
op_assign
id|ip_expire
suffix:semicolon
multiline_comment|/* expire function&t;*/
id|qp-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|qp-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ip_frag_intern
c_func
(paren
id|hash
comma
id|qp
)paren
suffix:semicolon
id|out_nomem
suffix:colon
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ip_frag_create: no memory left !&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Find the correct entry in the &quot;incomplete datagrams&quot; queue for&n; * this IP datagram, and create new one, if nothing is found.&n; */
DECL|function|ip_find
r_static
r_inline
r_struct
id|ipq
op_star
id|ip_find
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
id|__u16
id|id
op_assign
id|iph-&gt;id
suffix:semicolon
id|__u32
id|saddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|__u32
id|daddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|__u8
id|protocol
op_assign
id|iph-&gt;protocol
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|ipqhashfn
c_func
(paren
id|id
comma
id|saddr
comma
id|daddr
comma
id|protocol
)paren
suffix:semicolon
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|qp
op_assign
id|ipq_hash
(braket
id|hash
)braket
suffix:semicolon
id|qp
suffix:semicolon
id|qp
op_assign
id|qp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|qp-&gt;id
op_eq
id|id
op_logical_and
id|qp-&gt;saddr
op_eq
id|saddr
op_logical_and
id|qp-&gt;daddr
op_eq
id|daddr
op_logical_and
id|qp-&gt;protocol
op_eq
id|protocol
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|qp-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|ipfrag_lock
)paren
suffix:semicolon
r_return
id|ip_frag_create
c_func
(paren
id|hash
comma
id|iph
)paren
suffix:semicolon
)brace
multiline_comment|/* Add new segment to existing queue. */
DECL|function|ip_frag_queue
r_static
r_void
id|ip_frag_queue
c_func
(paren
r_struct
id|ipq
op_star
id|qp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|sk_buff
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
r_int
id|flags
comma
id|offset
suffix:semicolon
r_int
id|ihl
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;last_in
op_amp
id|COMPLETE
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|qp-&gt;timer
comma
id|jiffies
op_plus
id|sysctl_ipfrag_time
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|qp-&gt;refcnt
)paren
suffix:semicolon
id|offset
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
suffix:semicolon
id|flags
op_assign
id|offset
op_amp
op_complement
id|IP_OFFSET
suffix:semicolon
id|offset
op_and_assign
id|IP_OFFSET
suffix:semicolon
id|offset
op_lshift_assign
l_int|3
suffix:semicolon
multiline_comment|/* offset is in 8-byte chunks */
id|ihl
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* Determine the position of this fragment. */
id|end
op_assign
id|offset
op_plus
(paren
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_minus
id|ihl
)paren
suffix:semicolon
multiline_comment|/* Is this the final fragment? */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|IP_MF
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If we already have some bits beyond end&n;&t;&t; * or have different end, the segment is corrrupted.&n;&t;&t; */
r_if
c_cond
(paren
id|end
OL
id|qp-&gt;len
op_logical_or
(paren
(paren
id|qp-&gt;last_in
op_amp
id|LAST_IN
)paren
op_logical_and
id|end
op_ne
id|qp-&gt;len
)paren
)paren
r_goto
id|err
suffix:semicolon
id|qp-&gt;last_in
op_or_assign
id|LAST_IN
suffix:semicolon
id|qp-&gt;len
op_assign
id|end
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|end
op_amp
l_int|7
)paren
(brace
id|end
op_and_assign
op_complement
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_ne
id|CHECKSUM_UNNECESSARY
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
OG
id|qp-&gt;len
)paren
(brace
multiline_comment|/* Some bits beyond end -&gt; corruption. */
r_if
c_cond
(paren
id|qp-&gt;last_in
op_amp
id|LAST_IN
)paren
r_goto
id|err
suffix:semicolon
id|qp-&gt;len
op_assign
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|end
op_eq
id|offset
)paren
r_goto
id|err
suffix:semicolon
multiline_comment|/* Point into the IP datagram &squot;data&squot; part. */
id|skb_pull
c_func
(paren
id|skb
comma
(paren
id|skb-&gt;nh.raw
op_plus
id|ihl
)paren
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|end
op_minus
id|offset
)paren
suffix:semicolon
multiline_comment|/* Find out which fragments are in front and at the back of us&n;&t; * in the chain of fragments so far.  We must know where to put&n;&t; * this fragment, right?&n;&t; */
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|qp-&gt;fragments
suffix:semicolon
id|next
op_ne
l_int|NULL
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|FRAG_CB
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|offset
op_ge
id|offset
)paren
r_break
suffix:semicolon
multiline_comment|/* bingo! */
id|prev
op_assign
id|next
suffix:semicolon
)brace
multiline_comment|/* We found where to put this one.  Check for overlap with&n;&t; * preceding fragment, and, if needed, align things so that&n;&t; * any overlaps are eliminated.&n;&t; */
r_if
c_cond
(paren
id|prev
)paren
(brace
r_int
id|i
op_assign
(paren
id|FRAG_CB
c_func
(paren
id|prev
)paren
op_member_access_from_pointer
id|offset
op_plus
id|prev-&gt;len
)paren
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|offset
op_add_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|offset
)paren
r_goto
id|err
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_ne
id|CHECKSUM_UNNECESSARY
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|next
op_logical_and
id|FRAG_CB
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|offset
OL
id|end
)paren
(brace
r_int
id|i
op_assign
id|end
op_minus
id|FRAG_CB
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|offset
suffix:semicolon
multiline_comment|/* overlap is &squot;i&squot; bytes */
r_if
c_cond
(paren
id|i
OL
id|next-&gt;len
)paren
(brace
multiline_comment|/* Eat head of the next overlapped fragment&n;&t;&t;&t; * and leave the loop. The next ones cannot overlap.&n;&t;&t;&t; */
id|FRAG_CB
c_func
(paren
id|next
)paren
op_member_access_from_pointer
id|offset
op_add_assign
id|i
suffix:semicolon
id|skb_pull
c_func
(paren
id|next
comma
id|i
)paren
suffix:semicolon
id|qp-&gt;meat
op_sub_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|next-&gt;ip_summed
op_ne
id|CHECKSUM_UNNECESSARY
)paren
id|next-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
r_struct
id|sk_buff
op_star
id|free_it
op_assign
id|next
suffix:semicolon
multiline_comment|/* Old fragmnet is completely overridden with&n;&t;&t;&t; * new one drop it.&n;&t;&t;&t; */
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
r_else
id|qp-&gt;fragments
op_assign
id|next
suffix:semicolon
id|qp-&gt;meat
op_sub_assign
id|free_it-&gt;len
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|free_it
)paren
suffix:semicolon
)brace
)brace
id|FRAG_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|offset
op_assign
id|offset
suffix:semicolon
multiline_comment|/* Insert this fragment in the chain of fragments. */
id|skb-&gt;next
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|skb
suffix:semicolon
r_else
id|qp-&gt;fragments
op_assign
id|skb
suffix:semicolon
id|qp-&gt;dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|qp-&gt;meat
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|atomic_add
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
id|qp-&gt;last_in
op_or_assign
id|FIRST_IN
suffix:semicolon
r_return
suffix:semicolon
id|err
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* Build a new IP datagram from all its fragments.&n; *&n; * FIXME: We copy here because we lack an effective way of handling lists&n; * of bits on input. Until the new skb data handling is in I&squot;m not going&n; * to touch this with a bargepole. &n; */
DECL|function|ip_frag_reasm
r_static
r_struct
id|sk_buff
op_star
id|ip_frag_reasm
c_func
(paren
r_struct
id|ipq
op_star
id|qp
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
id|sk_buff
op_star
id|fp
comma
op_star
id|head
op_assign
id|qp-&gt;fragments
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|ihlen
suffix:semicolon
id|ipq_kill
c_func
(paren
id|qp
)paren
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|head
op_ne
l_int|NULL
)paren
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|FRAG_CB
c_func
(paren
id|head
)paren
op_member_access_from_pointer
id|offset
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Allocate a new buffer for the datagram. */
id|ihlen
op_assign
id|head-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|len
op_assign
id|ihlen
op_plus
id|qp-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|65535
)paren
(brace
r_goto
id|out_oversize
suffix:semicolon
)brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|out_nomem
suffix:semicolon
multiline_comment|/* Fill in the basic details. */
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|FRAG_CB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|h
op_assign
id|FRAG_CB
c_func
(paren
id|head
)paren
op_member_access_from_pointer
id|h
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|head-&gt;ip_summed
suffix:semicolon
id|skb-&gt;csum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Copy the original IP headers into the new buffer. */
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|ihlen
)paren
comma
id|head-&gt;nh.iph
comma
id|ihlen
)paren
suffix:semicolon
multiline_comment|/* Copy the data portions of all fragments into the new buffer. */
r_for
c_loop
(paren
id|fp
op_assign
id|head
suffix:semicolon
id|fp
suffix:semicolon
id|fp
op_assign
id|fp-&gt;next
)paren
(brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|fp-&gt;len
)paren
comma
id|fp-&gt;data
comma
id|fp-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_ne
id|fp-&gt;ip_summed
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
id|skb-&gt;csum
op_assign
id|csum_chain
c_func
(paren
id|skb-&gt;csum
comma
id|fp-&gt;csum
)paren
suffix:semicolon
)brace
id|skb-&gt;dst
op_assign
id|dst_clone
c_func
(paren
id|head-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|head-&gt;pkt_type
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|head-&gt;protocol
suffix:semicolon
id|skb-&gt;dev
op_assign
id|qp-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t;*  Clearly bogus, because security markings of the individual&n;&t;*  fragments should have been checked for consistency before&n;&t;*  gluing, and intermediate coalescing of fragments may have&n;&t;*  taken place in ip_defrag() before ip_glue() ever got called.&n;&t;*  If we&squot;re not going to do the consistency checking, we might&n;&t;*  as well take the value associated with the first fragment.&n;&t;*&t;--rct&n;&t;*/
id|skb-&gt;security
op_assign
id|head-&gt;security
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER
multiline_comment|/* Connection association is same as fragment (if any). */
id|skb-&gt;nfct
op_assign
id|head-&gt;nfct
suffix:semicolon
id|nf_conntrack_get
c_func
(paren
id|skb-&gt;nfct
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
id|head-&gt;nf_debug
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* Done with all fragments. Fixup the new IP header. */
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmOKs
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
id|out_nomem
suffix:colon
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IP: queue_glue: no memory for gluing queue %p&bslash;n&quot;
comma
id|qp
)paren
)paren
suffix:semicolon
r_goto
id|out_fail
suffix:semicolon
id|out_oversize
suffix:colon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Oversized IP packet from %d.%d.%d.%d.&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|qp-&gt;saddr
)paren
)paren
suffix:semicolon
id|out_fail
suffix:colon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmFails
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Process an incoming IP datagram fragment. */
DECL|function|ip_defrag
r_struct
id|sk_buff
op_star
id|ip_defrag
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmReqds
)paren
suffix:semicolon
multiline_comment|/* Start by cleaning up the memory. */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ip_frag_mem
)paren
OG
id|sysctl_ipfrag_high_thresh
)paren
id|ip_evictor
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Lookup (or create) queue header */
r_if
c_cond
(paren
(paren
id|qp
op_assign
id|ip_find
c_func
(paren
id|iph
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|sk_buff
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
id|ip_frag_queue
c_func
(paren
id|qp
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;last_in
op_eq
(paren
id|FIRST_IN
op_or
id|LAST_IN
)paren
op_logical_and
id|qp-&gt;meat
op_eq
id|qp-&gt;len
)paren
id|ret
op_assign
id|ip_frag_reasm
c_func
(paren
id|qp
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|qp-&gt;lock
)paren
suffix:semicolon
id|ipq_put
c_func
(paren
id|qp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|IP_INC_STATS_BH
c_func
(paren
id|IpReasmFails
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
eof
