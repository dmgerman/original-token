multiline_comment|/*&n; * linux/fs/inode.c&n; *&n; * (C) 1997 Linus Torvalds&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * New inode.c implementation.&n; *&n; * This implementation has the basic premise of trying&n; * to be extremely low-overhead and SMP-safe, yet be&n; * simple enough to be &quot;obviously correct&quot;.&n; *&n; * Famous last words.&n; */
multiline_comment|/*&n; * Inode lookup is no longer as critical as it used to be:&n; * most of the lookups are going to be through the dcache.&n; */
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS&t;8
DECL|macro|HASH_SIZE
mdefine_line|#define HASH_SIZE&t;(1UL &lt;&lt; HASH_BITS)
DECL|macro|HASH_MASK
mdefine_line|#define HASH_MASK&t;(HASH_SIZE-1)
multiline_comment|/*&n; * Each inode can be on two separate lists. One is&n; * the hash list of the inode, used for lookups. The&n; * other linked list is the &quot;type&quot; list:&n; *  &quot;in_use&quot; - valid inode, hashed&n; *  &quot;dirty&quot; - valid inode, hashed, dirty.&n; *  &quot;unused&quot; - ready to be re-used. Not hashed.&n; *&n; * The two first versions also have a dirty list, allowing&n; * for low-overhead inode sync() operations.&n; */
r_static
id|LIST_HEAD
c_func
(paren
id|inode_in_use
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|inode_dirty
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|inode_unused
)paren
suffix:semicolon
DECL|variable|inode_hashtable
r_static
r_struct
id|list_head
id|inode_hashtable
(braket
id|HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * A simple spinlock to protect the list manipulations&n; */
DECL|variable|inode_lock
id|spinlock_t
id|inode_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Statistics gathering.. Not actually done yet.&n; */
r_struct
(brace
DECL|member|nr_inodes
r_int
id|nr_inodes
suffix:semicolon
DECL|member|nr_free_inodes
r_int
id|nr_free_inodes
suffix:semicolon
DECL|member|dummy
r_int
id|dummy
(braket
l_int|10
)braket
suffix:semicolon
DECL|variable|inodes_stat
)brace
id|inodes_stat
suffix:semicolon
DECL|variable|max_inodes
r_int
id|max_inodes
op_assign
id|NR_INODE
suffix:semicolon
DECL|function|__mark_inode_dirty
r_void
id|__mark_inode_dirty
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_dirty
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
DECL|function|unlock_inode
r_static
r_inline
r_void
id|unlock_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|clear_bit
c_func
(paren
id|I_LOCK
comma
op_amp
id|inode-&gt;i_state
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|inode-&gt;i_wait
)paren
suffix:semicolon
)brace
DECL|function|__wait_on_inode
r_static
r_void
id|__wait_on_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|I_LOCK
comma
op_amp
id|inode-&gt;i_state
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|inode-&gt;i_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
DECL|function|wait_on_inode
r_static
r_inline
r_void
id|wait_on_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|I_LOCK
comma
op_amp
id|inode-&gt;i_state
)paren
)paren
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are initializations that only need to be done&n; * once, because the fields are idempotent across use&n; * of the inode..&n; */
DECL|function|init_once
r_static
r_inline
r_void
id|init_once
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|memset
c_func
(paren
id|inode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|init_waitqueue
c_func
(paren
op_amp
id|inode-&gt;i_wait
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|inode-&gt;i_dentry
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|inode-&gt;i_sem
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Look out! This returns with the inode lock held if&n; * it got an inode..&n; */
DECL|function|grow_inodes
r_static
r_struct
id|inode
op_star
id|grow_inodes
c_func
(paren
r_void
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
r_int
id|size
suffix:semicolon
r_struct
id|inode
op_star
id|tmp
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|size
op_assign
id|PAGE_SIZE
op_minus
l_int|2
op_star
r_sizeof
(paren
r_struct
id|inode
)paren
suffix:semicolon
id|tmp
op_assign
id|inode
suffix:semicolon
r_do
(brace
id|tmp
op_increment
suffix:semicolon
id|init_once
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|tmp-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
id|size
op_sub_assign
r_sizeof
(paren
r_struct
id|inode
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
l_int|0
)paren
suffix:semicolon
id|init_once
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|write_inode
r_static
r_inline
r_void
id|write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;s_op
op_logical_and
id|inode-&gt;i_sb-&gt;s_op-&gt;write_inode
)paren
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|write_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|sync_list
r_static
r_inline
r_void
id|sync_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|list_head
op_star
id|clean
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|head-&gt;prev
)paren
op_ne
id|head
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|tmp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the inode is locked, it&squot;s already being written out.&n;&t;&t; * We have to wait for it, though.&n;&t;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|I_LOCK
comma
op_amp
id|inode-&gt;i_state
)paren
)paren
(brace
id|list_add
c_func
(paren
id|tmp
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|list_add
c_func
(paren
id|tmp
comma
id|clean
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|I_DIRTY
comma
op_amp
id|inode-&gt;i_state
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|I_LOCK
comma
op_amp
id|inode-&gt;i_state
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|write_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * &quot;sync_inodes()&quot; goes through the dirty list &n; * and writes them out and puts them back on&n; * the normal list.&n; */
DECL|function|sync_inodes
r_void
id|sync_inodes
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|sync_list
c_func
(paren
op_amp
id|inode_dirty
comma
op_amp
id|inode_in_use
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called by the filesystem to tell us&n; * that the inode is no longer useful. We just&n; * terminate it with extreme predjudice.&n; */
DECL|function|clear_inode
r_void
id|clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|truncate_inode_pages
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_WRITABLE
c_func
(paren
id|inode
)paren
op_logical_and
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|drop
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_state
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|CAN_UNUSE
mdefine_line|#define CAN_UNUSE(inode) &bslash;&n;&t;(((inode)-&gt;i_count == 0) &amp;&amp; &bslash;&n;&t; ((inode)-&gt;i_nrpages == 0) &amp;&amp; &bslash;&n;&t; (!(inode)-&gt;i_state))
DECL|function|invalidate_list
r_static
r_void
id|invalidate_list
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
id|kdev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|next
suffix:semicolon
id|next
op_assign
id|head-&gt;next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
op_assign
id|next
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|head
)paren
r_break
suffix:semicolon
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CAN_UNUSE
c_func
(paren
id|inode
)paren
)paren
r_continue
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
)brace
)brace
DECL|function|invalidate_inodes
r_void
id|invalidate_inodes
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|invalidate_list
c_func
(paren
op_amp
id|inode_in_use
comma
id|dev
)paren
suffix:semicolon
id|invalidate_list
c_func
(paren
op_amp
id|inode_dirty
comma
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called with the inode lock held. It just looks at the last&n; * inode on the in-use list, and if the inode is trivially freeable&n; * we just move it to the unused list.&n; *&n; * Otherwise we just move the inode to be the first inode and expect to&n; * get back to the problem later..&n; */
DECL|function|try_to_free_inodes
r_static
r_void
id|try_to_free_inodes
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
op_amp
id|inode_in_use
suffix:semicolon
id|tmp
op_assign
id|head-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|head
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|list_del
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CAN_UNUSE
c_func
(paren
id|inode
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|inode_unused
suffix:semicolon
)brace
id|list_add
c_func
(paren
id|tmp
comma
id|head
)paren
suffix:semicolon
)brace
)brace
DECL|function|find_inode
r_static
r_struct
id|inode
op_star
id|find_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|ino
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|tmp
op_assign
id|head
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|head
)paren
r_break
suffix:semicolon
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_ne
id|sb
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_ne
id|ino
)paren
r_continue
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * This just initializes the inode fields&n; * to known values before returning the inode..&n; *&n; * i_sb, i_ino, i_count, i_state and the lists have&n; * been initialized elsewhere..&n; */
DECL|function|clean_inode
r_void
id|clean_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|memset
c_func
(paren
op_amp
id|inode-&gt;u
comma
l_int|0
comma
r_sizeof
(paren
id|inode-&gt;u
)paren
)paren
suffix:semicolon
id|inode-&gt;i_sock
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_writecount
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|inode-&gt;i_dquot
comma
l_int|0
comma
r_sizeof
(paren
id|inode-&gt;i_dquot
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|inode-&gt;i_sem
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called with I_LOCK held: it needs&n; * to read the inode and then unlock it&n; */
DECL|function|read_inode
r_static
r_inline
r_void
id|read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|sb-&gt;s_op
op_member_access_from_pointer
id|read_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|get_empty_inode
r_struct
id|inode
op_star
id|get_empty_inode
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|last_ino
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|try_to_free_inodes
c_func
(paren
)paren
suffix:semicolon
id|tmp
op_assign
id|inode_unused.next
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_amp
id|inode_unused
)paren
(brace
id|list_del
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
id|add_new_inode
suffix:colon
id|inode-&gt;i_sb
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_ino
op_assign
op_increment
id|last_ino
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|1
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_in_use
)paren
suffix:semicolon
id|inode-&gt;i_state
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|clean_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Warning: if this succeeded, we will now&n;&t; * return with the inode lock.&n;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|inode
op_assign
id|grow_inodes
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
r_goto
id|add_new_inode
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called with the inode lock held.. Be careful.&n; */
DECL|function|get_new_inode
r_static
r_struct
id|inode
op_star
id|get_new_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|ino
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
op_assign
id|inode_unused.next
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
op_amp
id|inode_unused
)paren
(brace
id|list_del
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|inode
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|inode
comma
id|i_list
)paren
suffix:semicolon
id|add_new_inode
suffix:colon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_in_use
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_hash
comma
id|head
)paren
suffix:semicolon
id|inode-&gt;i_sb
op_assign
id|sb
suffix:semicolon
id|inode-&gt;i_dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|ino
suffix:semicolon
id|inode-&gt;i_flags
op_assign
id|sb-&gt;s_flags
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_state
op_assign
l_int|1
op_lshift
id|I_LOCK
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|clean_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|read_inode
c_func
(paren
id|inode
comma
id|sb
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Uhhuh.. We need to expand.  Unlock for the allocation,&n;&t; * but note that &quot;grow_inodes()&quot; will return with the&n;&t; * lock held again if the allocation succeeded.&n;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|inode
op_assign
id|grow_inodes
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
multiline_comment|/* We released the lock, so.. */
r_struct
id|inode
op_star
id|old
op_assign
id|find_inode
c_func
(paren
id|sb
comma
id|ino
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old
)paren
r_goto
id|add_new_inode
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|wait_on_inode
c_func
(paren
id|old
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|hash
r_static
r_inline
r_int
r_int
id|hash
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|i_ino
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|i_ino
op_or
(paren
r_int
r_int
)paren
id|sb
suffix:semicolon
id|tmp
op_assign
id|tmp
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
)paren
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|tmp
op_amp
id|HASH_MASK
suffix:semicolon
)brace
DECL|function|iget
r_struct
id|inode
op_star
id|iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|ino
)paren
(brace
r_struct
id|list_head
op_star
id|head
op_assign
id|inode_hashtable
op_plus
id|hash
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|inode
op_assign
id|find_inode
c_func
(paren
id|sb
comma
id|ino
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|try_to_free_inodes
c_func
(paren
)paren
suffix:semicolon
r_return
id|get_new_inode
c_func
(paren
id|sb
comma
id|ino
comma
id|head
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|insert_inode_hash
r_void
id|insert_inode_hash
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|list_head
op_star
id|head
op_assign
id|inode_hashtable
op_plus
id|hash
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_hash
comma
id|head
)paren
suffix:semicolon
)brace
DECL|function|iput
r_void
id|iput
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|inode
)paren
(brace
r_struct
id|super_operations
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;s_op
)paren
id|op
op_assign
id|inode-&gt;i_sb-&gt;s_op
suffix:semicolon
r_if
c_cond
(paren
id|op
op_logical_and
id|op-&gt;put_inode
)paren
id|op
op_member_access_from_pointer
id|put_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|inode-&gt;i_count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
op_logical_and
id|op-&gt;delete_inode
)paren
(brace
r_void
(paren
op_star
r_delete
)paren
(paren
r_struct
id|inode
op_star
)paren
op_assign
id|op-&gt;delete_inode
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_delete
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|bmap
r_int
id|bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;bmap
)paren
r_return
id|inode-&gt;i_op
op_member_access_from_pointer
id|bmap
c_func
(paren
id|inode
comma
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the hash tables&n; */
DECL|function|inode_init
r_void
id|inode_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
id|inode_hashtable
suffix:semicolon
id|i
op_assign
id|HASH_SIZE
suffix:semicolon
r_do
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|head
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME! These need to go through the in-use inodes to&n; * check whether we can mount/umount/remount.&n; */
DECL|function|fs_may_mount
r_int
id|fs_may_mount
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|fs_may_umount
r_int
id|fs_may_umount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
)paren
(brace
id|shrink_dcache
c_func
(paren
)paren
suffix:semicolon
r_return
id|root-&gt;d_count
op_eq
l_int|1
suffix:semicolon
)brace
DECL|function|fs_may_remount_ro
r_int
id|fs_may_remount_ro
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
eof
