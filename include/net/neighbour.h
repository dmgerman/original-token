macro_line|#ifndef _NET_NEIGHBOUR_H
DECL|macro|_NET_NEIGHBOUR_H
mdefine_line|#define _NET_NEIGHBOUR_H
multiline_comment|/*&n; *&t;Generic neighbour manipulation&n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&t;Alexey Kuznetsov&t;&lt;kuznet@ms2.inr.ac.ru&gt;&n; */
multiline_comment|/* The following flags &amp; states are exported to user space,&n;   so that they should be moved to include/linux/ directory.&n; */
multiline_comment|/*&n; *&t;Neighbor Cache Entry Flags&n; */
DECL|macro|NTF_PROXY
mdefine_line|#define NTF_PROXY&t;0x08&t;/* == ATF_PUBL */
DECL|macro|NTF_ROUTER
mdefine_line|#define NTF_ROUTER&t;0x80
multiline_comment|/*&n; *&t;Neighbor Cache Entry States.&n; */
DECL|macro|NUD_INCOMPLETE
mdefine_line|#define NUD_INCOMPLETE&t;0x01
DECL|macro|NUD_REACHABLE
mdefine_line|#define NUD_REACHABLE&t;0x02
DECL|macro|NUD_STALE
mdefine_line|#define NUD_STALE&t;0x04
DECL|macro|NUD_DELAY
mdefine_line|#define NUD_DELAY&t;0x08
DECL|macro|NUD_PROBE
mdefine_line|#define NUD_PROBE&t;0x10
DECL|macro|NUD_FAILED
mdefine_line|#define NUD_FAILED&t;0x20
multiline_comment|/* Dummy states */
DECL|macro|NUD_NOARP
mdefine_line|#define NUD_NOARP&t;0x40
DECL|macro|NUD_PERMANENT
mdefine_line|#define NUD_PERMANENT&t;0x80
DECL|macro|NUD_NONE
mdefine_line|#define NUD_NONE&t;0x00
multiline_comment|/* NUD_NOARP &amp; NUD_PERMANENT are pseudostates, they never change&n;   and make no address resolution or NUD.&n;   NUD_PERMANENT is also cannot be deleted by garbage collectors.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|NUD_IN_TIMER
mdefine_line|#define NUD_IN_TIMER&t;(NUD_INCOMPLETE|NUD_DELAY|NUD_PROBE)
DECL|macro|NUD_VALID
mdefine_line|#define NUD_VALID&t;(NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE|NUD_PROBE|NUD_STALE|NUD_DELAY)
DECL|macro|NUD_CONNECTED
mdefine_line|#define NUD_CONNECTED&t;(NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE)
DECL|struct|neigh_parms
r_struct
id|neigh_parms
(brace
DECL|member|next
r_struct
id|neigh_parms
op_star
id|next
suffix:semicolon
DECL|member|neigh_setup
r_int
(paren
op_star
id|neigh_setup
)paren
(paren
r_struct
id|neighbour
op_star
)paren
suffix:semicolon
DECL|member|tbl
r_struct
id|neigh_table
op_star
id|tbl
suffix:semicolon
DECL|member|entries
r_int
id|entries
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|sysctl_table
r_void
op_star
id|sysctl_table
suffix:semicolon
DECL|member|base_reachable_time
r_int
id|base_reachable_time
suffix:semicolon
DECL|member|retrans_time
r_int
id|retrans_time
suffix:semicolon
DECL|member|gc_staletime
r_int
id|gc_staletime
suffix:semicolon
DECL|member|reachable_time
r_int
id|reachable_time
suffix:semicolon
DECL|member|delay_probe_time
r_int
id|delay_probe_time
suffix:semicolon
DECL|member|queue_len
r_int
id|queue_len
suffix:semicolon
DECL|member|ucast_probes
r_int
id|ucast_probes
suffix:semicolon
DECL|member|app_probes
r_int
id|app_probes
suffix:semicolon
DECL|member|mcast_probes
r_int
id|mcast_probes
suffix:semicolon
DECL|member|anycast_delay
r_int
id|anycast_delay
suffix:semicolon
DECL|member|proxy_delay
r_int
id|proxy_delay
suffix:semicolon
DECL|member|proxy_qlen
r_int
id|proxy_qlen
suffix:semicolon
DECL|member|locktime
r_int
id|locktime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|neigh_statistics
r_struct
id|neigh_statistics
(brace
DECL|member|allocs
r_int
r_int
id|allocs
suffix:semicolon
DECL|member|res_failed
r_int
r_int
id|res_failed
suffix:semicolon
DECL|member|rcv_probes_mcast
r_int
r_int
id|rcv_probes_mcast
suffix:semicolon
DECL|member|rcv_probes_ucast
r_int
r_int
id|rcv_probes_ucast
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|neighbour
r_struct
id|neighbour
(brace
DECL|member|next
r_struct
id|neighbour
op_star
id|next
suffix:semicolon
DECL|member|tbl
r_struct
id|neigh_table
op_star
id|tbl
suffix:semicolon
DECL|member|parms
r_struct
id|neigh_parms
op_star
id|parms
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|used
r_int
r_int
id|used
suffix:semicolon
DECL|member|confirmed
r_int
r_int
id|confirmed
suffix:semicolon
DECL|member|updated
r_int
r_int
id|updated
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|nud_state
id|__u8
id|nud_state
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|dead
id|__u8
id|dead
suffix:semicolon
DECL|member|probes
id|atomic_t
id|probes
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|ha
r_int
r_char
id|ha
(braket
(paren
id|MAX_ADDR_LEN
op_plus
r_sizeof
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
)braket
suffix:semicolon
DECL|member|hh
r_struct
id|hh_cache
op_star
id|hh
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|output
r_int
(paren
op_star
id|output
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|arp_queue
r_struct
id|sk_buff_head
id|arp_queue
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|ops
r_struct
id|neigh_ops
op_star
id|ops
suffix:semicolon
DECL|member|primary_key
id|u8
id|primary_key
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|neigh_ops
r_struct
id|neigh_ops
(brace
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|neighbour
op_star
)paren
suffix:semicolon
DECL|member|solicit
r_void
(paren
op_star
id|solicit
)paren
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
DECL|member|error_report
r_void
(paren
op_star
id|error_report
)paren
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
DECL|member|output
r_int
(paren
op_star
id|output
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|connected_output
r_int
(paren
op_star
id|connected_output
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|hh_output
r_int
(paren
op_star
id|hh_output
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|queue_xmit
r_int
(paren
op_star
id|queue_xmit
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pneigh_entry
r_struct
id|pneigh_entry
(brace
DECL|member|next
r_struct
id|pneigh_entry
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|key
id|u8
id|key
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NEIGH_HASHMASK
mdefine_line|#define NEIGH_HASHMASK&t;&t;0x1F
DECL|macro|PNEIGH_HASHMASK
mdefine_line|#define PNEIGH_HASHMASK&t;&t;0xF
multiline_comment|/*&n; *&t;neighbour table manipulation&n; */
DECL|struct|neigh_table
r_struct
id|neigh_table
(brace
DECL|member|next
r_struct
id|neigh_table
op_star
id|next
suffix:semicolon
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|entry_size
r_int
id|entry_size
suffix:semicolon
DECL|member|key_len
r_int
id|key_len
suffix:semicolon
DECL|member|hash
id|__u32
(paren
op_star
id|hash
)paren
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
)paren
suffix:semicolon
DECL|member|constructor
r_int
(paren
op_star
id|constructor
)paren
(paren
r_struct
id|neighbour
op_star
)paren
suffix:semicolon
DECL|member|pconstructor
r_int
(paren
op_star
id|pconstructor
)paren
(paren
r_struct
id|pneigh_entry
op_star
)paren
suffix:semicolon
DECL|member|pdestructor
r_void
(paren
op_star
id|pdestructor
)paren
(paren
r_struct
id|pneigh_entry
op_star
)paren
suffix:semicolon
DECL|member|proxy_redo
r_void
(paren
op_star
id|proxy_redo
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|id
r_char
op_star
id|id
suffix:semicolon
DECL|member|parms
r_struct
id|neigh_parms
id|parms
suffix:semicolon
multiline_comment|/* HACK. gc_* shoul follow parms without a gap! */
DECL|member|gc_interval
r_int
id|gc_interval
suffix:semicolon
DECL|member|gc_thresh1
r_int
id|gc_thresh1
suffix:semicolon
DECL|member|gc_thresh2
r_int
id|gc_thresh2
suffix:semicolon
DECL|member|gc_thresh3
r_int
id|gc_thresh3
suffix:semicolon
DECL|member|last_flush
r_int
r_int
id|last_flush
suffix:semicolon
DECL|member|gc_timer
r_struct
id|timer_list
id|gc_timer
suffix:semicolon
DECL|member|proxy_timer
r_struct
id|timer_list
id|proxy_timer
suffix:semicolon
DECL|member|proxy_queue
r_struct
id|sk_buff_head
id|proxy_queue
suffix:semicolon
DECL|member|entries
r_int
id|entries
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|last_rand
r_int
r_int
id|last_rand
suffix:semicolon
DECL|member|parms_list
r_struct
id|neigh_parms
op_star
id|parms_list
suffix:semicolon
DECL|member|kmem_cachep
id|kmem_cache_t
op_star
id|kmem_cachep
suffix:semicolon
DECL|member|gc_task
r_struct
id|tasklet_struct
id|gc_task
suffix:semicolon
DECL|member|stats
r_struct
id|neigh_statistics
id|stats
suffix:semicolon
DECL|member|hash_buckets
r_struct
id|neighbour
op_star
id|hash_buckets
(braket
id|NEIGH_HASHMASK
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|phash_buckets
r_struct
id|pneigh_entry
op_star
id|phash_buckets
(braket
id|PNEIGH_HASHMASK
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|neigh_table_init
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_int
id|neigh_table_clear
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|neigh_lookup
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|pkey
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|neigh_create
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|pkey
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|neigh_destroy
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
suffix:semicolon
r_extern
r_int
id|__neigh_event_send
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
suffix:semicolon
r_extern
r_int
id|neigh_update
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_const
id|u8
op_star
id|lladdr
comma
id|u8
r_new
comma
r_int
id|override
comma
r_int
id|arp
)paren
suffix:semicolon
r_extern
r_int
id|neigh_ifdown
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|neigh_resolve_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|neigh_connected_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|neigh_compat_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|neigh_event_ns
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
id|u8
op_star
id|lladdr
comma
r_void
op_star
id|saddr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|neigh_parms
op_star
id|neigh_parms_alloc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_void
id|neigh_parms_release
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|neigh_parms
op_star
id|parms
)paren
suffix:semicolon
r_extern
r_int
r_int
id|neigh_rand_reach_time
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_extern
r_void
id|pneigh_enqueue
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|neigh_parms
op_star
id|p
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|pneigh_entry
op_star
id|pneigh_lookup
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|key
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|creat
)paren
suffix:semicolon
r_extern
r_int
id|pneigh_delete
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|key
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|netlink_callback
suffix:semicolon
r_struct
id|nlmsghdr
suffix:semicolon
r_extern
r_int
id|neigh_dump_info
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|neigh_add
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|neigh_delete
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|neigh_app_ns
c_func
(paren
r_struct
id|neighbour
op_star
id|n
)paren
suffix:semicolon
r_extern
r_int
id|neigh_sysctl_register
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|neigh_parms
op_star
id|p
comma
r_int
id|p_id
comma
r_int
id|pdev_id
comma
r_char
op_star
id|p_name
)paren
suffix:semicolon
r_extern
r_void
id|neigh_sysctl_unregister
c_func
(paren
r_struct
id|neigh_parms
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Neighbour references&n; */
DECL|function|neigh_release
r_extern
id|__inline__
r_void
id|neigh_release
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|neigh-&gt;refcnt
)paren
)paren
id|neigh_destroy
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
DECL|function|neigh_clone
r_extern
id|__inline__
r_struct
id|neighbour
op_star
id|neigh_clone
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_if
c_cond
(paren
id|neigh
)paren
id|atomic_inc
c_func
(paren
op_amp
id|neigh-&gt;refcnt
)paren
suffix:semicolon
r_return
id|neigh
suffix:semicolon
)brace
DECL|macro|neigh_hold
mdefine_line|#define neigh_hold(n)&t;atomic_inc(&amp;(n)-&gt;refcnt)
DECL|function|neigh_confirm
r_extern
id|__inline__
r_void
id|neigh_confirm
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_if
c_cond
(paren
id|neigh
)paren
id|neigh-&gt;confirmed
op_assign
id|jiffies
suffix:semicolon
)brace
DECL|function|neigh_is_connected
r_extern
id|__inline__
r_int
id|neigh_is_connected
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_return
id|neigh-&gt;nud_state
op_amp
id|NUD_CONNECTED
suffix:semicolon
)brace
DECL|function|neigh_is_valid
r_extern
id|__inline__
r_int
id|neigh_is_valid
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_return
id|neigh-&gt;nud_state
op_amp
id|NUD_VALID
suffix:semicolon
)brace
DECL|function|neigh_event_send
r_extern
id|__inline__
r_int
id|neigh_event_send
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
(paren
id|NUD_CONNECTED
op_or
id|NUD_DELAY
op_or
id|NUD_PROBE
)paren
)paren
)paren
r_return
id|__neigh_event_send
c_func
(paren
id|neigh
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
id|__inline__
r_struct
id|neighbour
op_star
DECL|function|__neigh_lookup
id|__neigh_lookup
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|pkey
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|creat
)paren
(brace
r_struct
id|neighbour
op_star
id|n
op_assign
id|neigh_lookup
c_func
(paren
id|tbl
comma
id|pkey
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_logical_or
op_logical_neg
id|creat
)paren
r_return
id|n
suffix:semicolon
id|n
op_assign
id|neigh_create
c_func
(paren
id|tbl
comma
id|pkey
comma
id|dev
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|n
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|n
suffix:semicolon
)brace
r_extern
id|__inline__
r_struct
id|neighbour
op_star
DECL|function|__neigh_lookup_errno
id|__neigh_lookup_errno
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|pkey
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|neighbour
op_star
id|n
op_assign
id|neigh_lookup
c_func
(paren
id|tbl
comma
id|pkey
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
r_return
id|n
suffix:semicolon
r_return
id|neigh_create
c_func
(paren
id|tbl
comma
id|pkey
comma
id|dev
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
