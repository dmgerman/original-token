multiline_comment|/*&n; * DECnet       An implementation of the DECnet protocol suite for the LINUX&n; *              operating system.  DECnet is implemented using the  BSD Socket&n; *              interface as the means of communication with the user level.&n; *&n; *              DECnet Neighbour Functions (Adjacency Database and &n; *                                                        On-Ethernet Cache)&n; *&n; * Author:      Steve Whitehouse &lt;SteveW@ACM.org&gt;&n; *&n; *&n; * Changes:&n; *     Steve Whitehouse     : Fixed router listing routine&n; *     Steve Whitehouse     : Added error_report functions&n; *     Steve Whitehouse     : Added default router detection&n; *     Steve Whitehouse     : Hop counts in outgoing messages&n; *     Steve Whitehouse     : Fixed src/dst in outgoing messages so&n; *                            forwarding now stands a good chance of&n; *                            working.&n; *     Steve Whitehouse     : Fixed neighbour states (for now anyway).&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/netfilter_decnet.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/dn.h&gt;
macro_line|#include &lt;net/dn_dev.h&gt;
macro_line|#include &lt;net/dn_neigh.h&gt;
macro_line|#include &lt;net/dn_route.h&gt;
r_static
id|u32
id|dn_neigh_hash
c_func
(paren
r_const
r_void
op_star
id|pkey
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|dn_neigh_construct
c_func
(paren
r_struct
id|neighbour
op_star
)paren
suffix:semicolon
r_static
r_void
id|dn_long_error_report
c_func
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_void
id|dn_short_error_report
c_func
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_long_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_short_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_phase3_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * For talking to broadcast devices: Ethernet &amp; PPP&n; */
DECL|variable|dn_long_ops
r_static
r_struct
id|neigh_ops
id|dn_long_ops
op_assign
(brace
id|AF_DECnet
comma
l_int|NULL
comma
l_int|NULL
comma
id|dn_long_error_report
comma
id|dn_long_output
comma
id|dn_long_output
comma
id|dev_queue_xmit
comma
id|dev_queue_xmit
)brace
suffix:semicolon
multiline_comment|/*&n; * For talking to pointopoint and multidrop devices: DDCMP and X.25&n; */
DECL|variable|dn_short_ops
r_static
r_struct
id|neigh_ops
id|dn_short_ops
op_assign
(brace
id|AF_DECnet
comma
l_int|NULL
comma
l_int|NULL
comma
id|dn_short_error_report
comma
id|dn_short_output
comma
id|dn_short_output
comma
id|dev_queue_xmit
comma
id|dev_queue_xmit
)brace
suffix:semicolon
multiline_comment|/*&n; * For talking to DECnet phase III nodes&n; */
DECL|variable|dn_phase3_ops
r_static
r_struct
id|neigh_ops
id|dn_phase3_ops
op_assign
(brace
id|AF_DECnet
comma
l_int|NULL
comma
l_int|NULL
comma
id|dn_short_error_report
comma
multiline_comment|/* Can use short version here */
id|dn_phase3_output
comma
id|dn_phase3_output
comma
id|dev_queue_xmit
comma
id|dev_queue_xmit
)brace
suffix:semicolon
DECL|variable|dn_neigh_table
r_struct
id|neigh_table
id|dn_neigh_table
op_assign
(brace
l_int|NULL
comma
id|PF_DECnet
comma
r_sizeof
(paren
r_struct
id|dn_neigh
)paren
comma
r_sizeof
(paren
id|dn_address
)paren
comma
id|dn_neigh_hash
comma
id|dn_neigh_construct
comma
l_int|NULL
comma
multiline_comment|/* pconstructor */
l_int|NULL
comma
multiline_comment|/* pdestructor */
l_int|NULL
comma
multiline_comment|/* proxyredo */
l_string|&quot;dn_neigh_cache&quot;
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|dn_neigh_table
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|30
op_star
id|HZ
comma
multiline_comment|/* base_reachable_time */
l_int|1
op_star
id|HZ
comma
multiline_comment|/* retrans_time */
l_int|60
op_star
id|HZ
comma
multiline_comment|/* gc_staletime */
l_int|30
op_star
id|HZ
comma
multiline_comment|/* reachable_time */
l_int|5
op_star
id|HZ
comma
multiline_comment|/* delay_probe_time */
l_int|3
comma
multiline_comment|/* queue_len */
l_int|0
comma
multiline_comment|/* ucast_probes */
l_int|0
comma
multiline_comment|/* app_probes */
l_int|0
comma
multiline_comment|/* mcast_probes */
l_int|0
comma
multiline_comment|/* anycast_delay */
l_int|0
comma
multiline_comment|/* proxy_delay */
l_int|0
comma
multiline_comment|/* proxy_qlen */
l_int|1
op_star
id|HZ
comma
multiline_comment|/* locktime */
)brace
comma
l_int|30
op_star
id|HZ
comma
multiline_comment|/* gc_interval */
l_int|128
comma
multiline_comment|/* gc_thresh1 */
l_int|512
comma
multiline_comment|/* gc_thresh2 */
l_int|1024
comma
multiline_comment|/* gc_thresh3 */
)brace
suffix:semicolon
DECL|function|dn_neigh_hash
r_static
id|u32
id|dn_neigh_hash
c_func
(paren
r_const
r_void
op_star
id|pkey
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|u32
id|hash_val
suffix:semicolon
id|hash_val
op_assign
op_star
(paren
id|dn_address
op_star
)paren
id|pkey
suffix:semicolon
id|hash_val
op_xor_assign
(paren
id|hash_val
op_rshift
l_int|10
)paren
suffix:semicolon
id|hash_val
op_xor_assign
(paren
id|hash_val
op_rshift
l_int|3
)paren
suffix:semicolon
r_return
id|hash_val
op_amp
id|NEIGH_HASHMASK
suffix:semicolon
)brace
DECL|function|dn_neigh_construct
r_static
r_int
id|dn_neigh_construct
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|dev-&gt;dn_ptr
suffix:semicolon
r_if
c_cond
(paren
id|dn_db
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;neigh_parms
)paren
id|neigh-&gt;parms
op_assign
id|dn_db-&gt;neigh_parms
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;use_long
)paren
id|neigh-&gt;ops
op_assign
op_amp
id|dn_long_ops
suffix:semicolon
r_else
id|neigh-&gt;ops
op_assign
op_amp
id|dn_short_ops
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_P3
)paren
id|neigh-&gt;ops
op_assign
op_amp
id|dn_phase3_ops
suffix:semicolon
id|neigh-&gt;nud_state
op_assign
id|NUD_NOARP
suffix:semicolon
id|neigh-&gt;output
op_assign
id|neigh-&gt;ops-&gt;connected_output
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_IPGRE
)paren
op_logical_or
(paren
id|dev-&gt;flags
op_amp
id|IFF_POINTOPOINT
)paren
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
id|dev-&gt;broadcast
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
op_logical_or
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_LOOPBACK
)paren
)paren
id|dn_dn2eth
c_func
(paren
id|neigh-&gt;ha
comma
id|dn-&gt;addr
)paren
suffix:semicolon
r_else
(brace
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
id|KERN_DEBUG
l_string|&quot;Trying to create neigh for hw %d&bslash;n&quot;
comma
id|dev-&gt;type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dn-&gt;blksize
op_assign
l_int|230
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_long_error_report
r_static
r_void
id|dn_long_error_report
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|dn_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dn_long_error_report: called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cb-&gt;rt_flags
op_amp
id|DN_RT_F_RQR
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
id|ptr
op_assign
id|skb-&gt;data
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ptr
op_amp
id|DN_RT_F_PF
)paren
(brace
r_char
id|padlen
op_assign
(paren
op_star
id|ptr
op_amp
op_complement
id|DN_RT_F_PF
)paren
suffix:semicolon
id|ptr
op_add_assign
id|padlen
suffix:semicolon
)brace
op_star
id|ptr
op_increment
op_or_assign
(paren
id|cb-&gt;rt_flags
op_amp
op_complement
id|DN_RT_F_RQR
)paren
op_or
id|DN_RT_F_RTS
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|ptr
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;src
)paren
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|8
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|ptr
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;dst
)paren
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|6
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;dst-&gt;neighbour-&gt;ops
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_short_error_report
r_static
r_void
id|dn_short_error_report
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|dn_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dn_short_error_report: called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cb-&gt;rt_flags
op_amp
id|DN_RT_F_RQR
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
id|ptr
op_assign
id|skb-&gt;data
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
(paren
id|cb-&gt;rt_flags
op_amp
op_complement
id|DN_RT_F_RQR
)paren
op_or
id|DN_RT_F_RTS
suffix:semicolon
op_star
(paren
id|dn_address
op_star
)paren
id|ptr
op_assign
id|cb-&gt;src
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
op_star
(paren
id|dn_address
op_star
)paren
id|ptr
op_assign
id|cb-&gt;dst
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;dst-&gt;neighbour-&gt;ops
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_neigh_output_packet
r_static
r_int
id|dn_neigh_output_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hard_header
op_logical_or
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ntohs
c_func
(paren
id|skb-&gt;protocol
)paren
comma
id|neigh-&gt;ha
comma
l_int|NULL
comma
id|skb-&gt;len
)paren
op_ge
l_int|0
)paren
r_return
id|neigh-&gt;ops
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
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
id|KERN_DEBUG
l_string|&quot;dn_neigh_output_packet: oops, can&squot;t send packet&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_long_output
r_static
r_int
id|dn_long_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_long_packet
)paren
op_plus
l_int|3
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_long_packet
op_star
id|lp
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|dn_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
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
id|KERN_CRIT
l_string|&quot;dn_long_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
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
l_string|&quot;dn_long_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_long_packet
)paren
op_plus
l_int|3
)paren
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|dn_long_packet
op_star
)paren
(paren
id|data
op_plus
l_int|3
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
op_star
(paren
id|data
op_plus
l_int|2
)paren
op_assign
l_int|1
op_or
id|DN_RT_F_PF
suffix:semicolon
multiline_comment|/* Padding */
id|lp-&gt;msgflg
op_assign
id|DN_RT_PKT_LONG
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_IE
op_or
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|lp-&gt;d_area
op_assign
id|lp-&gt;d_subarea
op_assign
l_int|0
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|lp-&gt;d_id
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;dst
)paren
)paren
suffix:semicolon
id|lp-&gt;s_area
op_assign
id|lp-&gt;s_subarea
op_assign
l_int|0
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|lp-&gt;s_id
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;src
)paren
)paren
suffix:semicolon
id|lp-&gt;nl2
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;visit_ct
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|lp-&gt;s_class
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;pt
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
DECL|function|dn_short_output
r_static
r_int
id|dn_short_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
suffix:semicolon
r_struct
id|dn_short_packet
op_star
id|sp
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|dn_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
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
id|KERN_CRIT
l_string|&quot;dn_short_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
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
l_string|&quot;dn_short_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_struct
id|dn_short_packet
op_star
)paren
(paren
id|data
op_plus
l_int|2
)paren
suffix:semicolon
id|sp-&gt;msgflg
op_assign
id|DN_RT_PKT_SHORT
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|sp-&gt;dstnode
op_assign
id|cb-&gt;dst
suffix:semicolon
id|sp-&gt;srcnode
op_assign
id|cb-&gt;src
suffix:semicolon
id|sp-&gt;forward
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Phase 3 output is the same is short output, execpt that&n; * it clears the area bits before transmission.&n; */
DECL|function|dn_phase3_output
r_static
r_int
id|dn_phase3_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
suffix:semicolon
r_struct
id|dn_short_packet
op_star
id|sp
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|dn_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
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
id|KERN_CRIT
l_string|&quot;dn_phase3_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
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
l_string|&quot;dn_phase3_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
)paren
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_struct
id|dn_short_packet
op_star
)paren
(paren
id|data
op_plus
l_int|2
)paren
suffix:semicolon
id|sp-&gt;msgflg
op_assign
id|DN_RT_PKT_SHORT
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|sp-&gt;dstnode
op_assign
id|cb-&gt;dst
op_amp
id|dn_htons
c_func
(paren
l_int|0x03ff
)paren
suffix:semicolon
id|sp-&gt;srcnode
op_assign
id|cb-&gt;src
op_amp
id|dn_htons
c_func
(paren
l_int|0x03ff
)paren
suffix:semicolon
id|sp-&gt;forward
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unfortunately, the neighbour code uses the device in its hash&n; * function, so we don&squot;t get any advantage from it. This function&n; * basically does a neigh_lookup(), but without comparing the device&n; * field. This is required for the On-Ethernet cache&n; */
DECL|function|dn_neigh_lookup
r_struct
id|neighbour
op_star
id|dn_neigh_lookup
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
id|u32
id|hash_val
suffix:semicolon
id|hash_val
op_assign
id|tbl
op_member_access_from_pointer
id|hash
c_func
(paren
id|ptr
comma
l_int|NULL
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|neigh
op_assign
id|tbl-&gt;hash_buckets
(braket
id|hash_val
)braket
suffix:semicolon
id|neigh
op_ne
l_int|NULL
suffix:semicolon
id|neigh
op_assign
id|neigh-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|neigh-&gt;primary_key
comma
id|ptr
comma
id|tbl-&gt;key_len
)paren
op_eq
l_int|0
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|neigh-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
id|neigh
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Any traffic on a pointopoint link causes the timer to be reset&n; * for the entry in the neighbour table.&n; */
DECL|function|dn_neigh_pointopoint_notify
r_void
id|dn_neigh_pointopoint_notify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Pointopoint link receives a hello message&n; */
DECL|function|dn_neigh_pointopoint_hello
r_void
id|dn_neigh_pointopoint_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ethernet router hello message received&n; */
DECL|function|dn_neigh_router_hello
r_int
id|dn_neigh_router_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|rtnode_hello_message
op_star
id|msg
op_assign
(paren
r_struct
id|rtnode_hello_message
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
suffix:semicolon
id|dn_address
id|src
suffix:semicolon
id|src
op_assign
id|dn_htons
c_func
(paren
id|dn_eth2dn
c_func
(paren
id|msg-&gt;id
)paren
)paren
suffix:semicolon
id|neigh
op_assign
id|__neigh_lookup
c_func
(paren
op_amp
id|dn_neigh_table
comma
op_amp
id|src
comma
id|skb-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
id|neigh
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh-&gt;used
op_assign
id|jiffies
suffix:semicolon
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|neigh-&gt;dev-&gt;dn_ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|neigh-&gt;nud_state
op_amp
id|NUD_PERMANENT
)paren
)paren
(brace
id|neigh-&gt;updated
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|neigh-&gt;dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
op_amp
id|skb-&gt;mac.ethernet-&gt;h_source
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dn-&gt;blksize
op_assign
id|dn_ntohs
c_func
(paren
id|msg-&gt;blksize
)paren
suffix:semicolon
id|dn-&gt;priority
op_assign
id|msg-&gt;priority
suffix:semicolon
id|dn-&gt;flags
op_and_assign
op_complement
id|DN_NDFLAG_P3
suffix:semicolon
r_switch
c_cond
(paren
id|msg-&gt;iinfo
op_amp
id|DN_RT_INFO_TYPE
)paren
(brace
r_case
id|DN_RT_INFO_L1RT
suffix:colon
id|dn-&gt;flags
op_and_assign
op_complement
id|DN_NDFLAG_R2
suffix:semicolon
id|dn-&gt;flags
op_or_assign
id|DN_NDFLAG_R1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DN_RT_INFO_L2RT
suffix:colon
id|dn-&gt;flags
op_or_assign
id|DN_NDFLAG_R2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|dn_db-&gt;router
)paren
(brace
id|dn_db-&gt;router
op_assign
id|neigh_clone
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|msg-&gt;priority
OG
(paren
(paren
r_struct
id|dn_neigh
op_star
)paren
id|dn_db-&gt;router
)paren
op_member_access_from_pointer
id|priority
)paren
id|neigh_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|dn_db-&gt;router
comma
id|neigh_clone
c_func
(paren
id|neigh
)paren
)paren
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh_release
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Endnode hello message received&n; */
DECL|function|dn_neigh_endnode_hello
r_int
id|dn_neigh_endnode_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|endnode_hello_message
op_star
id|msg
op_assign
(paren
r_struct
id|endnode_hello_message
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
id|dn_address
id|src
suffix:semicolon
id|src
op_assign
id|dn_htons
c_func
(paren
id|dn_eth2dn
c_func
(paren
id|msg-&gt;id
)paren
)paren
suffix:semicolon
id|neigh
op_assign
id|__neigh_lookup
c_func
(paren
op_amp
id|dn_neigh_table
comma
op_amp
id|src
comma
id|skb-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
id|neigh
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh-&gt;used
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|neigh-&gt;nud_state
op_amp
id|NUD_PERMANENT
)paren
)paren
(brace
id|neigh-&gt;updated
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|neigh-&gt;dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
op_amp
id|skb-&gt;mac.ethernet-&gt;h_source
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dn-&gt;flags
op_and_assign
op_complement
(paren
id|DN_NDFLAG_R1
op_or
id|DN_NDFLAG_R2
)paren
suffix:semicolon
id|dn-&gt;blksize
op_assign
id|dn_ntohs
c_func
(paren
id|msg-&gt;blksize
)paren
suffix:semicolon
id|dn-&gt;priority
op_assign
l_int|0
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh_release
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_DECNET_ROUTER
DECL|function|dn_find_slot
r_static
r_char
op_star
id|dn_find_slot
c_func
(paren
r_char
op_star
id|base
comma
r_int
id|max
comma
r_int
id|priority
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|min
op_assign
l_int|NULL
suffix:semicolon
id|base
op_add_assign
l_int|6
suffix:semicolon
multiline_comment|/* skip first id */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|min
op_logical_or
(paren
op_star
id|base
OL
op_star
id|min
)paren
)paren
id|min
op_assign
id|base
suffix:semicolon
id|base
op_add_assign
l_int|7
suffix:semicolon
multiline_comment|/* find next priority */
)brace
r_if
c_cond
(paren
op_logical_neg
id|min
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
op_star
id|min
OL
id|priority
)paren
ques
c_cond
(paren
id|min
op_minus
l_int|6
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|dn_neigh_elist
r_int
id|dn_neigh_elist
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_char
op_star
id|ptr
comma
r_int
id|n
)paren
(brace
r_int
id|t
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
r_struct
id|neigh_table
op_star
id|tbl
op_assign
op_amp
id|dn_neigh_table
suffix:semicolon
r_int
r_char
op_star
id|rs
op_assign
id|ptr
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|dev-&gt;dn_ptr
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
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
id|NEIGH_HASHMASK
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|neigh
op_assign
id|tbl-&gt;hash_buckets
(braket
id|i
)braket
suffix:semicolon
id|neigh
op_ne
l_int|NULL
suffix:semicolon
id|neigh
op_assign
id|neigh-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|neigh-&gt;dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dn-&gt;flags
op_amp
(paren
id|DN_NDFLAG_R1
op_or
id|DN_NDFLAG_R2
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;parms.forwarding
op_eq
l_int|1
op_logical_and
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R2
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
id|n
)paren
id|rs
op_assign
id|dn_find_slot
c_func
(paren
id|ptr
comma
id|n
comma
id|dn-&gt;priority
)paren
suffix:semicolon
r_else
id|t
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rs
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|rs
comma
id|dn-&gt;addr
)paren
suffix:semicolon
id|rs
op_add_assign
l_int|6
suffix:semicolon
op_star
id|rs
op_assign
id|neigh-&gt;nud_state
op_amp
id|NUD_CONNECTED
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x0
suffix:semicolon
op_star
id|rs
op_or_assign
id|dn-&gt;priority
suffix:semicolon
id|rs
op_increment
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DECNET_ROUTER */
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|dn_neigh_get_info
r_static
r_int
id|dn_neigh_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
r_struct
id|neighbour
op_star
id|n
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|buf
(braket
id|DN_ASCBUF_LEN
)braket
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Addr    Flags State Use Blksize Dev&bslash;n&quot;
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
op_le
id|NEIGH_HASHMASK
suffix:semicolon
id|i
op_increment
)paren
(brace
id|read_lock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
id|n
op_assign
id|dn_neigh_table.hash_buckets
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
op_ne
l_int|NULL
suffix:semicolon
id|n
op_assign
id|n-&gt;next
)paren
(brace
r_struct
id|dn_neigh
op_star
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|n
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-7s %s%s%s   %02x    %02d  %07ld %-8s&bslash;n&quot;
comma
id|dn_addr2asc
c_func
(paren
id|dn_ntohs
c_func
(paren
id|dn-&gt;addr
)paren
comma
id|buf
)paren
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R1
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;-&quot;
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R2
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
l_string|&quot;-&quot;
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_P3
)paren
ques
c_cond
l_string|&quot;3&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|dn-&gt;n.nud_state
comma
id|atomic_read
c_func
(paren
op_amp
id|dn-&gt;n.refcnt
)paren
comma
id|dn-&gt;blksize
comma
(paren
id|dn-&gt;n.dev
)paren
ques
c_cond
id|dn-&gt;n.dev-&gt;name
suffix:colon
l_string|&quot;?&quot;
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
)brace
id|done
suffix:colon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
id|offset
op_minus
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
DECL|function|dn_neigh_init
r_void
id|__init
id|dn_neigh_init
c_func
(paren
r_void
)paren
(brace
id|neigh_table_init
c_func
(paren
op_amp
id|dn_neigh_table
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_create
c_func
(paren
l_string|&quot;decnet_neigh&quot;
comma
l_int|0
comma
id|dn_neigh_get_info
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
)brace
DECL|function|dn_neigh_cleanup
r_void
id|__exit
id|dn_neigh_cleanup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_remove
c_func
(paren
l_string|&quot;decnet_neigh&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
id|neigh_table_clear
c_func
(paren
op_amp
id|dn_neigh_table
)paren
suffix:semicolon
)brace
eof
