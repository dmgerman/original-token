multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The IP fragmentation functionality.&n; *&t;&t;&n; * Authors:&t;Fred N. van Kempen &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;Split from ip.c , see ip_input.c for history.&n; */
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
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;linux/ip_fw.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
multiline_comment|/*&n; *&t;Fragment cache limits. We will commit 256K at one time. Should we&n; *&t;cross that limit we will prune down to 192K. This should cope with&n; *&t;even the most extreme cases without allowing an attacker to measurably&n; *&t;harm machine performance.&n; */
DECL|macro|IPFRAG_HIGH_THRESH
mdefine_line|#define IPFRAG_HIGH_THRESH&t;&t;(256*1024)
DECL|macro|IPFRAG_LOW_THRESH
mdefine_line|#define IPFRAG_LOW_THRESH&t;&t;(192*1024)
multiline_comment|/*&n; *&t;This fragment handler is a bit of a heap. On the other hand it works quite&n; *&t;happily and handles things quite well.&n; */
DECL|variable|ipqueue
r_static
r_struct
id|ipq
op_star
id|ipqueue
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* IP fragment queue&t;*/
DECL|variable|ip_frag_mem
id|atomic_t
id|ip_frag_mem
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Memory used for fragments */
multiline_comment|/*&n; *&t;Memory Tracking Functions&n; */
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
comma
r_int
id|type
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
comma
id|type
)paren
suffix:semicolon
)brace
DECL|function|frag_kfree_s
r_extern
id|__inline__
r_void
id|frag_kfree_s
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|len
)paren
(brace
id|atomic_sub
c_func
(paren
id|len
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|ptr
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|frag_kmalloc
r_extern
id|__inline__
r_void
op_star
id|frag_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|pri
)paren
(brace
r_void
op_star
id|vp
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|pri
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vp
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|atomic_add
c_func
(paren
id|size
comma
op_amp
id|ip_frag_mem
)paren
suffix:semicolon
r_return
id|vp
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Create a new fragment entry.&n; */
DECL|function|ip_frag_create
r_static
r_struct
id|ipfrag
op_star
id|ip_frag_create
c_func
(paren
r_int
id|offset
comma
r_int
id|end
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|ptr
)paren
(brace
r_struct
id|ipfrag
op_star
id|fp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|fp
op_assign
(paren
r_struct
id|ipfrag
op_star
)paren
id|frag_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipfrag
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_eq
l_int|NULL
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;IP: frag_create: no memory left !&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipfrag
)paren
)paren
suffix:semicolon
multiline_comment|/* Fill in the structure. */
id|fp-&gt;offset
op_assign
id|offset
suffix:semicolon
id|fp-&gt;end
op_assign
id|end
suffix:semicolon
id|fp-&gt;len
op_assign
id|end
op_minus
id|offset
suffix:semicolon
id|fp-&gt;skb
op_assign
id|skb
suffix:semicolon
id|fp-&gt;ptr
op_assign
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Charge for the SKB as well.&n;&t; */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ip_frag_mem
op_add_assign
id|skb-&gt;truesize
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|fp
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Find the correct entry in the &quot;incomplete datagrams&quot; queue for&n; *&t;this IP datagram, and return the queue entry address if found.&n; */
DECL|function|ip_find
r_static
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
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
r_struct
id|ipq
op_star
id|qplast
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|qplast
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|qp
op_assign
id|ipqueue
suffix:semicolon
id|qp
op_ne
l_int|NULL
suffix:semicolon
id|qplast
op_assign
id|qp
comma
id|qp
op_assign
id|qp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|iph-&gt;id
op_eq
id|qp-&gt;iph-&gt;id
op_logical_and
id|iph-&gt;saddr
op_eq
id|qp-&gt;iph-&gt;saddr
op_logical_and
id|iph-&gt;daddr
op_eq
id|qp-&gt;iph-&gt;daddr
op_logical_and
id|iph-&gt;protocol
op_eq
id|qp-&gt;iph-&gt;protocol
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* So it doesn&squot;t vanish on us. The timer will be reset anyway */
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove an entry from the &quot;incomplete datagrams&quot; queue, either&n; *&t;because we completed, reassembled and processed it, or because&n; *&t;it timed out.&n; */
DECL|function|ip_free
r_static
r_void
id|ip_free
c_func
(paren
r_struct
id|ipq
op_star
id|qp
)paren
(brace
r_struct
id|ipfrag
op_star
id|fp
suffix:semicolon
r_struct
id|ipfrag
op_star
id|xp
suffix:semicolon
multiline_comment|/*&n;&t; * Stop the timer for this entry.&n;&t; */
id|del_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Remove this entry from the &quot;incomplete datagrams&quot; queue. */
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;prev
op_eq
l_int|NULL
)paren
(brace
id|ipqueue
op_assign
id|qp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ipqueue
op_ne
l_int|NULL
)paren
id|ipqueue-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|qp-&gt;prev-&gt;next
op_assign
id|qp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;next
op_ne
l_int|NULL
)paren
id|qp-&gt;next-&gt;prev
op_assign
id|qp-&gt;prev
suffix:semicolon
)brace
multiline_comment|/* Release all fragment data. */
id|fp
op_assign
id|qp-&gt;fragments
suffix:semicolon
r_while
c_loop
(paren
id|fp
op_ne
l_int|NULL
)paren
(brace
id|xp
op_assign
id|fp-&gt;next
suffix:semicolon
id|IS_SKB
c_func
(paren
id|fp-&gt;skb
)paren
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|fp-&gt;skb
comma
id|FREE_READ
)paren
suffix:semicolon
id|frag_kfree_s
c_func
(paren
id|fp
comma
r_sizeof
(paren
r_struct
id|ipfrag
)paren
)paren
suffix:semicolon
id|fp
op_assign
id|xp
suffix:semicolon
)brace
multiline_comment|/* Release the IP header. */
id|frag_kfree_s
c_func
(paren
id|qp-&gt;iph
comma
l_int|64
op_plus
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Finally, release the queue descriptor itself. */
id|frag_kfree_s
c_func
(paren
id|qp
comma
r_sizeof
(paren
r_struct
id|ipq
)paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Oops- a fragment queue timed out.  Kill it and send an ICMP reply.&n; */
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
suffix:semicolon
id|qp
op_assign
(paren
r_struct
id|ipq
op_star
)paren
id|arg
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send an ICMP &quot;Fragment Reassembly Timeout&quot; message.&n;&t; */
id|ip_statistics.IpReasmTimeout
op_increment
suffix:semicolon
id|ip_statistics.IpReasmFails
op_increment
suffix:semicolon
multiline_comment|/* This if is always true... shrug */
r_if
c_cond
(paren
id|qp-&gt;fragments
op_ne
l_int|NULL
)paren
(brace
id|icmp_send
c_func
(paren
id|qp-&gt;fragments-&gt;skb
comma
id|ICMP_TIME_EXCEEDED
comma
id|ICMP_EXC_FRAGTIME
comma
l_int|0
comma
id|qp-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Nuke the fragment queue.&n;&t; */
id|ip_free
c_func
(paren
id|qp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Memory limiting on fragments. Evictor trashes the oldest &n; *&t;fragment queue until we are back under the low threshold&n; */
DECL|function|ip_evictor
r_static
r_void
id|ip_evictor
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|ip_frag_mem
OG
id|IPFRAG_LOW_THRESH
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ipqueue
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;ip_evictor: memcount&quot;
)paren
suffix:semicolon
)brace
id|ip_free
c_func
(paren
id|ipqueue
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * &t;Add an entry to the &squot;ipq&squot; queue for a newly received IP datagram.&n; * &t;We will (hopefully :-) receive all other fragments of this datagram&n; * &t;in time, so we just create a queue for this datagram, in which we&n; * &t;will insert the received fragments at their respective positions.&n; */
DECL|function|ip_create
r_static
r_struct
id|ipq
op_star
id|ip_create
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|iphdr
op_star
id|iph
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
r_int
id|ihlen
suffix:semicolon
id|qp
op_assign
(paren
r_struct
id|ipq
op_star
)paren
id|frag_kmalloc
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
id|qp
op_eq
l_int|NULL
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;IP: create: no memory left !&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|skb-&gt;dev
op_assign
id|qp-&gt;dev
suffix:semicolon
)brace
id|memset
c_func
(paren
id|qp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipq
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate memory for the IP header (plus 8 octets for ICMP).&n;&t; */
id|ihlen
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|qp-&gt;iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|frag_kmalloc
c_func
(paren
l_int|64
op_plus
l_int|8
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;iph
op_eq
l_int|NULL
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;IP: create: no memory left !&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|frag_kfree_s
c_func
(paren
id|qp
comma
r_sizeof
(paren
r_struct
id|ipq
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|qp-&gt;iph
comma
id|iph
comma
id|ihlen
op_plus
l_int|8
)paren
suffix:semicolon
id|qp-&gt;len
op_assign
l_int|0
suffix:semicolon
id|qp-&gt;ihlen
op_assign
id|ihlen
suffix:semicolon
id|qp-&gt;fragments
op_assign
l_int|NULL
suffix:semicolon
id|qp-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Start a timer for this entry. */
id|qp-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|IP_FRAG_TIME
suffix:semicolon
multiline_comment|/* about 30 seconds&t;*/
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
id|add_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Add this entry to the queue. */
id|qp-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|qp-&gt;next
op_assign
id|ipqueue
suffix:semicolon
r_if
c_cond
(paren
id|qp-&gt;next
op_ne
l_int|NULL
)paren
id|qp-&gt;next-&gt;prev
op_assign
id|qp
suffix:semicolon
id|ipqueue
op_assign
id|qp
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|qp
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;See if a fragment queue is complete.&n; */
DECL|function|ip_done
r_static
r_int
id|ip_done
c_func
(paren
r_struct
id|ipq
op_star
id|qp
)paren
(brace
r_struct
id|ipfrag
op_star
id|fp
suffix:semicolon
r_int
id|offset
suffix:semicolon
multiline_comment|/* Only possible if we received the final fragment. */
r_if
c_cond
(paren
id|qp-&gt;len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check all fragment offsets to see if they connect. */
id|fp
op_assign
id|qp-&gt;fragments
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|fp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|fp-&gt;offset
OG
id|offset
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* fragment(s) missing */
id|offset
op_assign
id|fp-&gt;end
suffix:semicolon
id|fp
op_assign
id|fp-&gt;next
suffix:semicolon
)brace
multiline_comment|/* All fragments are present. */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Build a new IP datagram from all its fragments.&n; *&n; *&t;FIXME: We copy here because we lack an effective way of handling lists&n; *&t;of bits on input. Until the new skb data handling is in I&squot;m not going&n; *&t;to touch this with a bargepole. &n; */
DECL|function|ip_glue
r_static
r_struct
id|sk_buff
op_star
id|ip_glue
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
id|ipfrag
op_star
id|fp
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|count
comma
id|len
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate a new buffer for the datagram.&n;&t; */
id|len
op_assign
id|qp-&gt;ihlen
op_plus
id|qp-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|len
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ip_statistics.IpReasmFails
op_increment
suffix:semicolon
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;IP: queue_glue: no memory for gluing queue %p&bslash;n&quot;
comma
id|qp
)paren
)paren
suffix:semicolon
id|ip_free
c_func
(paren
id|qp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Fill in the basic details. */
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Copy the original IP headers into the new buffer. */
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
(paren
(paren
r_int
r_char
op_star
)paren
id|qp-&gt;iph
)paren
comma
id|qp-&gt;ihlen
)paren
suffix:semicolon
id|ptr
op_add_assign
id|qp-&gt;ihlen
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Copy the data portions of all fragments into the new buffer. */
id|fp
op_assign
id|qp-&gt;fragments
suffix:semicolon
r_while
c_loop
(paren
id|fp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|count
op_plus
id|fp-&gt;len
OG
id|skb-&gt;len
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Invalid fragment list: Fragment over size.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ip_free
c_func
(paren
id|qp
)paren
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|ip_statistics.IpReasmFails
op_increment
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
id|ptr
op_plus
id|fp-&gt;offset
)paren
comma
id|fp-&gt;ptr
comma
id|fp-&gt;len
)paren
suffix:semicolon
id|count
op_add_assign
id|fp-&gt;len
suffix:semicolon
id|fp
op_assign
id|fp-&gt;next
suffix:semicolon
)brace
multiline_comment|/* We glued together all fragments, so remove the queue entry. */
id|ip_free
c_func
(paren
id|qp
)paren
suffix:semicolon
multiline_comment|/* Done with all fragments. Fixup the new IP header. */
id|iph
op_assign
id|skb-&gt;h.iph
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
(paren
id|iph-&gt;ihl
op_star
l_int|4
)paren
op_plus
id|count
)paren
suffix:semicolon
id|skb-&gt;ip_hdr
op_assign
id|iph
suffix:semicolon
id|ip_statistics.IpReasmOKs
op_increment
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Process an incoming IP datagram fragment.&n; */
DECL|function|ip_defrag
r_struct
id|sk_buff
op_star
id|ip_defrag
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ipfrag
op_star
id|prev
comma
op_star
id|next
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|ipfrag
op_star
id|tfp
suffix:semicolon
r_struct
id|ipq
op_star
id|qp
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|flags
comma
id|offset
suffix:semicolon
r_int
id|i
comma
id|ihl
comma
id|end
suffix:semicolon
id|ip_statistics.IpReasmReqds
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Start by cleaning up the memory&n;&t; */
r_if
c_cond
(paren
id|ip_frag_mem
OG
id|IPFRAG_HIGH_THRESH
)paren
(brace
id|ip_evictor
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; *&t;Find the entry of this IP datagram in the &quot;incomplete datagrams&quot; queue. &n;&t; */
id|qp
op_assign
id|ip_find
c_func
(paren
id|iph
)paren
suffix:semicolon
multiline_comment|/* Is this a non-fragmented datagram? */
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
r_if
c_cond
(paren
(paren
(paren
id|flags
op_amp
id|IP_MF
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|offset
op_eq
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|qp
op_ne
l_int|NULL
)paren
id|ip_free
c_func
(paren
id|qp
)paren
suffix:semicolon
multiline_comment|/* Huh? How could this exist?? */
r_return
id|skb
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * If the queue already existed, keep restarting its timer as long&n;&t; * as we still are receiving fragments.  Otherwise, create a fresh&n;&t; * queue entry.&n;&t; */
r_if
c_cond
(paren
id|qp
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* ANK. If the first fragment is received,&n;&t;&t; * we should remember the correct IP header (with options)&n;&t;&t; */
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
(brace
id|qp-&gt;ihlen
op_assign
id|ihl
suffix:semicolon
id|memcpy
c_func
(paren
id|qp-&gt;iph
comma
id|iph
comma
id|ihl
op_plus
l_int|8
)paren
suffix:semicolon
)brace
id|del_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
id|qp-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|IP_FRAG_TIME
suffix:semicolon
multiline_comment|/* about 30 seconds */
id|qp-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|qp
suffix:semicolon
multiline_comment|/* pointer to queue */
id|qp-&gt;timer.function
op_assign
id|ip_expire
suffix:semicolon
multiline_comment|/* expire function */
id|add_timer
c_func
(paren
op_amp
id|qp-&gt;timer
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *&t;If we failed to create it, then discard the frame&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|qp
op_assign
id|ip_create
c_func
(paren
id|skb
comma
id|iph
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
id|ip_statistics.IpReasmFails
op_increment
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Determine the position of this fragment.&n;&t; */
id|end
op_assign
id|offset
op_plus
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_minus
id|ihl
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Point into the IP datagram &squot;data&squot; part.&n;&t; */
id|ptr
op_assign
id|skb-&gt;data
op_plus
id|ihl
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Is this the final fragment?&n;&t; */
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
id|qp-&gt;len
op_assign
id|end
suffix:semicolon
multiline_comment|/*&n;&t; * &t;Find out which fragments are in front and at the back of us&n;&t; * &t;in the chain of fragments so far.  We must know where to put&n;&t; * &t;this fragment, right?&n;&t; */
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
id|next-&gt;offset
OG
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
multiline_comment|/*&n;&t; * &t;We found where to put this one.&n;&t; * &t;Check for overlap with preceding fragment, and, if needed,&n;&t; * &t;align things so that any overlaps are eliminated.&n;&t; */
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
op_logical_and
id|offset
OL
id|prev-&gt;end
)paren
(brace
id|i
op_assign
id|prev-&gt;end
op_minus
id|offset
suffix:semicolon
id|offset
op_add_assign
id|i
suffix:semicolon
multiline_comment|/* ptr into datagram */
id|ptr
op_add_assign
id|i
suffix:semicolon
multiline_comment|/* ptr into fragment data */
)brace
multiline_comment|/*&n;&t; * Look for overlap with succeeding segments.&n;&t; * If we can merge fragments, do it.&n;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
id|next
suffix:semicolon
id|tmp
op_ne
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|tfp
)paren
(brace
id|tfp
op_assign
id|tmp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;offset
op_ge
id|end
)paren
r_break
suffix:semicolon
multiline_comment|/* no overlaps at all */
id|i
op_assign
id|end
op_minus
id|next-&gt;offset
suffix:semicolon
multiline_comment|/* overlap is &squot;i&squot; bytes */
id|tmp-&gt;len
op_sub_assign
id|i
suffix:semicolon
multiline_comment|/* so reduce size of&t;*/
id|tmp-&gt;offset
op_add_assign
id|i
suffix:semicolon
multiline_comment|/* next fragment&t;*/
id|tmp-&gt;ptr
op_add_assign
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;If we get a frag size of &lt;= 0, remove it and the packet&n;&t;&t; *&t;that it goes with.&n;&t;&t; */
r_if
c_cond
(paren
id|tmp-&gt;len
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;prev
op_ne
l_int|NULL
)paren
id|tmp-&gt;prev-&gt;next
op_assign
id|tmp-&gt;next
suffix:semicolon
r_else
id|qp-&gt;fragments
op_assign
id|tmp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tfp-&gt;next
op_ne
l_int|NULL
)paren
id|tmp-&gt;next-&gt;prev
op_assign
id|tmp-&gt;prev
suffix:semicolon
id|next
op_assign
id|tfp
suffix:semicolon
multiline_comment|/* We have killed the original next frame */
id|frag_kfree_skb
c_func
(paren
id|tmp-&gt;skb
comma
id|FREE_READ
)paren
suffix:semicolon
id|frag_kfree_s
c_func
(paren
id|tmp
comma
r_sizeof
(paren
r_struct
id|ipfrag
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Insert this fragment in the chain of fragments.&n;&t; */
id|tfp
op_assign
l_int|NULL
suffix:semicolon
id|tfp
op_assign
id|ip_frag_create
c_func
(paren
id|offset
comma
id|end
comma
id|skb
comma
id|ptr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;No memory to save the fragment - so throw the lot&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|tfp
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|frag_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|tfp-&gt;prev
op_assign
id|prev
suffix:semicolon
id|tfp-&gt;next
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
)paren
id|prev-&gt;next
op_assign
id|tfp
suffix:semicolon
r_else
id|qp-&gt;fragments
op_assign
id|tfp
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
l_int|NULL
)paren
id|next-&gt;prev
op_assign
id|tfp
suffix:semicolon
multiline_comment|/*&n;&t; * &t;OK, so we inserted this new fragment into the chain.&n;&t; * &t;Check if we now have a full IP datagram which we can&n;&t; * &t;bump up to the IP layer...&n;&t; */
r_if
c_cond
(paren
id|ip_done
c_func
(paren
id|qp
)paren
)paren
(brace
id|skb2
op_assign
id|ip_glue
c_func
(paren
id|qp
)paren
suffix:semicolon
multiline_comment|/* glue together the fragments */
r_return
id|skb2
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This IP datagram is too large to be sent in one piece.  Break it up into&n; *&t;smaller pieces (each of size equal to the MAC header plus IP header plus&n; *&t;a block of the data of the original IP data part) that will yet fit in a&n; *&t;single device frame, and queue such a frame for sending by calling the&n; *&t;ip_queue_xmit().  Note that this is recursion, and bad things will happen&n; *&t;if this function causes a loop...&n; *&n; *&t;Yes this is inefficient, feel free to submit a quicker one.&n; *&n; */
DECL|function|ip_fragment
r_void
id|ip_fragment
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
id|device
op_star
id|dev
comma
r_int
id|is_frag
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_int
r_char
op_star
id|raw
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_int
id|left
comma
id|mtu
comma
id|hlen
comma
id|len
suffix:semicolon
r_int
id|offset
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Point into the IP datagram header.&n;&t; */
id|raw
op_assign
id|skb-&gt;data
suffix:semicolon
macro_line|#if 0
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|raw
op_plus
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|skb-&gt;ip_hdr
op_assign
id|iph
suffix:semicolon
macro_line|#else
id|iph
op_assign
id|skb-&gt;ip_hdr
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Setup starting values.&n;&t; */
id|hlen
op_assign
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|left
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_minus
id|hlen
suffix:semicolon
multiline_comment|/* Space per frame */
id|hlen
op_add_assign
id|dev-&gt;hard_header_len
suffix:semicolon
multiline_comment|/* Total header size */
id|mtu
op_assign
(paren
id|dev-&gt;mtu
op_minus
id|hlen
)paren
suffix:semicolon
multiline_comment|/* Size of data space */
id|ptr
op_assign
(paren
id|raw
op_plus
id|hlen
)paren
suffix:semicolon
multiline_comment|/* Where to start from */
multiline_comment|/*&n;&t; *&t;Check for any &quot;DF&quot; flag. [DF means do not fragment]&n;&t; */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_DF
)paren
(brace
id|ip_statistics.IpFragFails
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ip_queue_xmit: frag needed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;The protocol doesn&squot;t seem to say what to do in the case that the&n;&t; *&t;frame + options doesn&squot;t fit the mtu. As it used to fall down dead&n;&t; *&t;in this case we were fortunate it didn&squot;t happen&n;&t; */
r_if
c_cond
(paren
id|mtu
OL
l_int|8
)paren
(brace
multiline_comment|/* It&squot;s wrong but it&squot;s better than nothing */
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|dev-&gt;mtu
comma
id|dev
)paren
suffix:semicolon
id|ip_statistics.IpFragFails
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Fragment the datagram.&n;&t; */
multiline_comment|/*&n;&t; *&t;The initial offset is 0 for a complete frame. When&n;&t; *&t;fragmenting fragments it&squot;s wherever this one starts.&n;&t; */
r_if
c_cond
(paren
id|is_frag
op_amp
l_int|2
)paren
id|offset
op_assign
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_OFFSET
)paren
op_lshift
l_int|3
suffix:semicolon
r_else
id|offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Keep copying data until we run out.&n;&t; */
r_while
c_loop
(paren
id|left
OG
l_int|0
)paren
(brace
id|len
op_assign
id|left
suffix:semicolon
multiline_comment|/* IF: it doesn&squot;t fit, use &squot;mtu&squot; - the data space left */
r_if
c_cond
(paren
id|len
OG
id|mtu
)paren
id|len
op_assign
id|mtu
suffix:semicolon
multiline_comment|/* IF: we are not sending upto and including the packet end&n;&t;&t;   then align the next start on an eight byte boundary */
r_if
c_cond
(paren
id|len
OL
id|left
)paren
(brace
id|len
op_div_assign
l_int|8
suffix:semicolon
id|len
op_mul_assign
l_int|8
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Allocate buffer.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|alloc_skb
c_func
(paren
id|len
op_plus
id|hlen
op_plus
l_int|15
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;IP: frag: no memory for new fragment!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ip_statistics.IpFragFails
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Set up data on packet&n;&t;&t; */
id|skb2-&gt;arp
op_assign
id|skb-&gt;arp
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;free
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IP fragmenter: BUG free!=1 in fragmenter&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|skb2-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb_put
c_func
(paren
id|skb2
comma
id|len
op_plus
id|hlen
)paren
suffix:semicolon
id|skb2-&gt;h.raw
op_assign
(paren
r_char
op_star
)paren
id|skb2-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Charge the memory for the fragment to any owner&n;&t;&t; *&t;it might possess&n;&t;&t; */
r_if
c_cond
(paren
id|sk
)paren
(brace
id|atomic_add
c_func
(paren
id|skb2-&gt;truesize
comma
op_amp
id|sk-&gt;wmem_alloc
)paren
suffix:semicolon
id|skb2-&gt;sk
op_assign
id|sk
suffix:semicolon
)brace
id|skb2-&gt;raddr
op_assign
id|skb-&gt;raddr
suffix:semicolon
multiline_comment|/* For rebuild_header - must be here */
multiline_comment|/*&n;&t;&t; *&t;Copy the packet header into the new buffer.&n;&t;&t; */
id|memcpy
c_func
(paren
id|skb2-&gt;h.raw
comma
id|raw
comma
id|hlen
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Copy a block of the IP datagram.&n;&t;&t; */
id|memcpy
c_func
(paren
id|skb2-&gt;h.raw
op_plus
id|hlen
comma
id|ptr
comma
id|len
)paren
suffix:semicolon
id|left
op_sub_assign
id|len
suffix:semicolon
id|skb2-&gt;h.raw
op_add_assign
id|dev-&gt;hard_header_len
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Fill in the new header fields.&n;&t;&t; */
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|skb2-&gt;h.raw
multiline_comment|/*+dev-&gt;hard_header_len*/
)paren
suffix:semicolon
id|iph-&gt;frag_off
op_assign
id|htons
c_func
(paren
(paren
id|offset
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
id|skb2-&gt;ip_hdr
op_assign
id|iph
suffix:semicolon
multiline_comment|/* ANK: dirty, but effective trick. Upgrade options only if&n;&t;&t; * the segment to be fragmented was THE FIRST (otherwise,&n;&t;&t; * options are already fixed) and make it ONCE&n;&t;&t; * on the initial skb, so that all the following fragments&n;&t;&t; * will inherit fixed options.&n;&t;&t; */
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
id|ip_options_fragment
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Added AC : If we are fragmenting a fragment thats not the&n;&t;&t; *&t;&t;   last fragment then keep MF on each bit&n;&t;&t; */
r_if
c_cond
(paren
id|left
OG
l_int|0
op_logical_or
(paren
id|is_frag
op_amp
l_int|1
)paren
)paren
id|iph-&gt;frag_off
op_or_assign
id|htons
c_func
(paren
id|IP_MF
)paren
suffix:semicolon
id|ptr
op_add_assign
id|len
suffix:semicolon
id|offset
op_add_assign
id|len
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Put this fragment into the sending queue.&n;&t;&t; */
id|ip_statistics.IpFragCreates
op_increment
suffix:semicolon
id|ip_queue_xmit
c_func
(paren
id|sk
comma
id|dev
comma
id|skb2
comma
l_int|2
)paren
suffix:semicolon
)brace
id|ip_statistics.IpFragOKs
op_increment
suffix:semicolon
)brace
eof
