macro_line|#ifndef _NET_NEIGHBOUR_H
DECL|macro|_NET_NEIGHBOUR_H
mdefine_line|#define _NET_NEIGHBOUR_H
multiline_comment|/*&n; *&t;Generic neighbour manipulation&n; *&n; *&t;authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
multiline_comment|/*&n; *&t;flags&n; *&n; */
DECL|macro|NTF_COMPLETE
mdefine_line|#define NTF_COMPLETE&t;0x02
DECL|macro|NTF_PERMANENT
mdefine_line|#define NTF_PERMANENT&t;0x04
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
DECL|member|prev
r_struct
id|neighbour
op_star
id|prev
suffix:semicolon
DECL|member|tbl
r_struct
id|neigh_table
op_star
id|tbl
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|lastused
r_int
r_int
id|lastused
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ha
r_int
r_char
id|ha
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|ops
r_struct
id|neigh_ops
op_star
id|ops
suffix:semicolon
DECL|member|arp_queue
r_struct
id|sk_buff_head
id|arp_queue
suffix:semicolon
DECL|member|primary_key
r_char
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
DECL|member|hash
r_int
r_int
(paren
op_star
id|hash
)paren
(paren
r_void
op_star
id|primary_key
)paren
suffix:semicolon
DECL|member|resolve
r_int
(paren
op_star
id|resolve
)paren
(paren
r_int
r_char
op_star
id|h_dest
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
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
)brace
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|neigh_alloc
c_func
(paren
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Neighbour references&n; *&n; *&t;When neighbour pointers are passed to &quot;client&quot; code the&n; *&t;reference count is increased. The count is 0 if the node&n; *&t;is only referenced by the corresponding table.&n; *&n; *&t;Nodes cannot be unlinked from the table if their&n; *&t;reference count != 0.&n; *&n; *&t;i.e. you can&squot;t reclaim a neighbour if it is being used by a&n; *&t;dst_cache or routing entry - hopefully those will react&n; *&t;to memory shortage and GC their unused entries&n; */
DECL|function|neighbour_unlock
r_static
id|__inline__
r_void
id|neighbour_unlock
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
id|neigh-&gt;lastused
op_assign
id|jiffies
suffix:semicolon
)brace
DECL|function|neighbour_clone
r_static
id|__inline__
r_struct
id|neighbour
op_star
id|neighbour_clone
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
DECL|macro|NT_MASK_QUEUE
mdefine_line|#define NT_MASK_QUEUE&t;0x01
DECL|macro|NT_MASK_GC
mdefine_line|#define NT_MASK_GC&t;0x02
multiline_comment|/*&n; *&t;neighbour table manipulation&n; */
DECL|struct|neigh_table
r_struct
id|neigh_table
(brace
DECL|member|tbl_size
r_int
id|tbl_size
suffix:semicolon
multiline_comment|/* num. of hash&t;buckets&t;*/
DECL|member|tbl_entries
r_int
id|tbl_entries
suffix:semicolon
multiline_comment|/* entry count&t;&t;*/
DECL|member|hash_buckets
r_struct
id|neighbour
op_star
op_star
id|hash_buckets
suffix:semicolon
DECL|member|tbl_lock
id|atomic_t
id|tbl_lock
suffix:semicolon
DECL|member|tbl_bh_mask
r_int
r_int
id|tbl_bh_mask
suffix:semicolon
multiline_comment|/* bh mask&t;&t;*/
DECL|member|neigh_ops
r_struct
id|neigh_ops
op_star
id|neigh_ops
suffix:semicolon
DECL|member|request_queue
r_struct
id|neighbour
op_star
id|request_queue
suffix:semicolon
multiline_comment|/* pending inserts&t;*/
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
comma
r_struct
id|neigh_ops
op_star
id|ops
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|neigh_table_destroy
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_void
id|neigh_table_run_bh
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_void
id|neigh_table_ins
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|neighbour
op_star
id|neigh
)paren
suffix:semicolon
r_extern
r_void
id|neigh_queue_ins
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|neighbour
op_star
id|neigh
)paren
suffix:semicolon
r_extern
r_void
id|neigh_unlink
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
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
r_void
op_star
id|pkey
comma
r_int
id|key_len
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|neigh_insert
r_static
id|__inline__
r_void
id|neigh_insert
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
id|start_bh_atomic
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbl-&gt;tbl_lock
op_eq
l_int|1
)paren
(brace
id|neigh_table_ins
c_func
(paren
id|tbl
comma
id|neigh
)paren
suffix:semicolon
)brace
r_else
(brace
id|tbl-&gt;tbl_bh_mask
op_or_assign
id|NT_MASK_QUEUE
suffix:semicolon
id|neigh_queue_ins
c_func
(paren
id|tbl
comma
id|neigh
)paren
suffix:semicolon
)brace
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|typedef|ntbl_examine_t
r_typedef
r_int
(paren
op_star
id|ntbl_examine_t
)paren
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;examine every element of a neighbour table.&n; *&t;For every neighbour the callback function will be called.&n; *&n; *&t;parameters:&n; *&t;&t;max&t;:&t;max bucket index (&lt;= tbl_size, 0 all)&n; *&t;&t;filter&t;:&t;(neigh-&gt;flags &amp; (~filter)) -&gt; call func&n; *&t;&t;args&t;:&t;opaque pointer&n; *&n; *&t;return values&n; *&t;&t;0&t;&t;nop&n; *&t;&t;!0&t;&t;unlink node from table and destroy it&n; */
r_extern
r_void
id|ntbl_walk_table
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
id|ntbl_examine_t
id|func
comma
r_int
r_int
id|filter
comma
r_int
id|max
comma
r_void
op_star
id|args
)paren
suffix:semicolon
DECL|function|neigh_table_lock
r_static
id|__inline__
r_void
id|neigh_table_lock
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|tbl-&gt;tbl_lock
)paren
suffix:semicolon
)brace
r_extern
r_void
id|neigh_tbl_run_bh
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
suffix:semicolon
DECL|function|neigh_table_unlock
r_static
id|__inline__
r_void
id|neigh_table_unlock
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
)paren
(brace
id|start_bh_atomic
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|tbl-&gt;tbl_lock
)paren
op_logical_and
id|tbl-&gt;tbl_bh_mask
)paren
(brace
id|neigh_tbl_run_bh
c_func
(paren
id|tbl
)paren
suffix:semicolon
)brace
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
