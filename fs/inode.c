multiline_comment|/*&n; *  linux/fs/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|struct|inode_hash_entry
r_static
r_struct
id|inode_hash_entry
(brace
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|updating
r_int
id|updating
suffix:semicolon
DECL|variable|hash_table
)brace
id|hash_table
(braket
id|NR_IHASH
)braket
suffix:semicolon
DECL|variable|first_inode
r_static
r_struct
id|inode
op_star
id|first_inode
suffix:semicolon
DECL|variable|inode_wait
r_static
r_struct
id|wait_queue
op_star
id|inode_wait
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Keep these next two contiguous in memory for sysctl.c */
DECL|variable|nr_inodes
DECL|variable|nr_free_inodes
r_int
id|nr_inodes
op_assign
l_int|0
comma
id|nr_free_inodes
op_assign
l_int|0
suffix:semicolon
DECL|variable|max_inodes
r_int
id|max_inodes
op_assign
id|NR_INODE
suffix:semicolon
DECL|function|hashfn
r_static
r_inline
r_int
r_const
id|hashfn
c_func
(paren
id|kdev_t
id|dev
comma
r_int
r_int
id|i
)paren
(brace
r_return
(paren
id|HASHDEV
c_func
(paren
id|dev
)paren
op_xor
id|i
)paren
op_mod
id|NR_IHASH
suffix:semicolon
)brace
DECL|function|hash
r_static
r_inline
r_struct
id|inode_hash_entry
op_star
r_const
id|hash
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|i
)paren
(brace
r_return
id|hash_table
op_plus
id|hashfn
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
DECL|function|insert_inode_free
r_static
r_inline
r_void
id|insert_inode_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_next
op_assign
id|first_inode
suffix:semicolon
id|inode-&gt;i_prev
op_assign
id|first_inode-&gt;i_prev
suffix:semicolon
id|inode-&gt;i_next-&gt;i_prev
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_prev-&gt;i_next
op_assign
id|inode
suffix:semicolon
id|first_inode
op_assign
id|inode
suffix:semicolon
)brace
DECL|function|remove_inode_free
r_static
r_inline
r_void
id|remove_inode_free
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
id|first_inode
op_eq
id|inode
)paren
id|first_inode
op_assign
id|first_inode-&gt;i_next
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_next
)paren
id|inode-&gt;i_next-&gt;i_prev
op_assign
id|inode-&gt;i_prev
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_prev
)paren
id|inode-&gt;i_prev-&gt;i_next
op_assign
id|inode-&gt;i_next
suffix:semicolon
id|inode-&gt;i_next
op_assign
id|inode-&gt;i_prev
op_assign
l_int|NULL
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
id|inode_hash_entry
op_star
id|h
suffix:semicolon
id|h
op_assign
id|hash
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|inode-&gt;i_hash_next
op_assign
id|h-&gt;inode
suffix:semicolon
id|inode-&gt;i_hash_prev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_hash_next
)paren
id|inode-&gt;i_hash_next-&gt;i_hash_prev
op_assign
id|inode
suffix:semicolon
id|h-&gt;inode
op_assign
id|inode
suffix:semicolon
)brace
DECL|function|remove_inode_hash
r_static
r_inline
r_void
id|remove_inode_hash
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|inode_hash_entry
op_star
id|h
suffix:semicolon
id|h
op_assign
id|hash
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;inode
op_eq
id|inode
)paren
id|h-&gt;inode
op_assign
id|inode-&gt;i_hash_next
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_hash_next
)paren
id|inode-&gt;i_hash_next-&gt;i_hash_prev
op_assign
id|inode-&gt;i_hash_prev
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_hash_prev
)paren
id|inode-&gt;i_hash_prev-&gt;i_hash_next
op_assign
id|inode-&gt;i_hash_next
suffix:semicolon
id|inode-&gt;i_hash_prev
op_assign
id|inode-&gt;i_hash_next
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|put_last_free
r_static
r_inline
r_void
id|put_last_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|remove_inode_free
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_prev
op_assign
id|first_inode-&gt;i_prev
suffix:semicolon
id|inode-&gt;i_prev-&gt;i_next
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_next
op_assign
id|first_inode
suffix:semicolon
id|inode-&gt;i_next-&gt;i_prev
op_assign
id|inode
suffix:semicolon
)brace
DECL|function|grow_inodes
r_int
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
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|i
op_assign
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|inode
)paren
suffix:semicolon
id|nr_inodes
op_add_assign
id|i
suffix:semicolon
id|nr_free_inodes
op_add_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first_inode
)paren
id|inode-&gt;i_next
op_assign
id|inode-&gt;i_prev
op_assign
id|first_inode
op_assign
id|inode
op_increment
comma
id|i
op_decrement
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
id|insert_inode_free
c_func
(paren
id|inode
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inode_init
r_int
r_int
id|inode_init
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|memset
c_func
(paren
id|hash_table
comma
l_int|0
comma
r_sizeof
(paren
id|hash_table
)paren
)paren
suffix:semicolon
id|first_inode
op_assign
l_int|NULL
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
r_static
r_void
id|__wait_on_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
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
id|inode-&gt;i_lock
)paren
id|__wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|lock_inode
r_static
r_inline
r_void
id|lock_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_lock
op_assign
l_int|1
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
id|inode-&gt;i_lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|inode-&gt;i_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that we don&squot;t want to disturb any wait-queues when we discard&n; * an inode.&n; *&n; * Argghh. Got bitten by a gcc problem with inlining: no way to tell&n; * the compiler that the inline asm function &squot;memset&squot; changes &squot;inode&squot;.&n; * I&squot;ve been searching for the bug for days, and was getting desperate.&n; * Finally looked at the assembler output... Grrr.&n; *&n; * The solution is the weird use of &squot;volatile&squot;. Ho humm. Have to report&n; * it to the gcc lists, and hope we can do this more cleanly some day..&n; */
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
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
id|invalidate_inode_pages
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
)paren
(brace
r_if
c_cond
(paren
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
)brace
id|remove_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|remove_inode_free
c_func
(paren
id|inode
)paren
suffix:semicolon
id|wait
op_assign
(paren
(paren
r_volatile
r_struct
id|inode
op_star
)paren
id|inode
)paren
op_member_access_from_pointer
id|i_wait
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_count
)paren
id|nr_free_inodes
op_increment
suffix:semicolon
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
(paren
(paren
r_volatile
r_struct
id|inode
op_star
)paren
id|inode
)paren
op_member_access_from_pointer
id|i_wait
op_assign
id|wait
suffix:semicolon
id|insert_inode_free
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|fs_may_mount
r_int
id|fs_may_mount
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
comma
op_star
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|next
op_assign
id|first_inode
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr_inodes
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|inode
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|inode-&gt;i_next
suffix:semicolon
multiline_comment|/* clear_inode() changes the queues.. */
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
id|inode-&gt;i_count
op_logical_or
id|inode-&gt;i_dirt
op_logical_or
id|inode-&gt;i_lock
)paren
r_return
l_int|0
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|fs_may_umount
r_int
id|fs_may_umount
c_func
(paren
id|kdev_t
id|dev
comma
r_struct
id|inode
op_star
id|mount_root
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|inode
op_assign
id|first_inode
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
id|nr_inodes
suffix:semicolon
id|i
op_increment
comma
id|inode
op_assign
id|inode-&gt;i_next
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_ne
id|dev
op_logical_or
op_logical_neg
id|inode-&gt;i_count
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
id|mount_root
op_logical_and
id|inode-&gt;i_count
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|fs_may_remount_ro
r_int
id|fs_may_remount_ro
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Check that no files are currently opened for writing. */
r_for
c_loop
(paren
id|file
op_assign
id|first_file
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_files
suffix:semicolon
id|i
op_increment
comma
id|file
op_assign
id|file-&gt;f_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_count
op_logical_or
op_logical_neg
id|file-&gt;f_inode
op_logical_or
id|file-&gt;f_inode-&gt;i_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|file-&gt;f_inode-&gt;i_mode
)paren
op_logical_and
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|write_inode
r_static
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
op_logical_neg
id|inode-&gt;i_dirt
)paren
r_return
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
op_logical_neg
id|inode-&gt;i_dirt
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
op_logical_or
op_logical_neg
id|inode-&gt;i_sb-&gt;s_op
op_logical_or
op_logical_neg
id|inode-&gt;i_sb-&gt;s_op-&gt;write_inode
)paren
(brace
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_lock
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
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
)paren
(brace
id|lock_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;s_op
op_logical_and
id|inode-&gt;i_sb-&gt;s_op-&gt;read_inode
)paren
id|inode-&gt;i_sb-&gt;s_op
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
multiline_comment|/* POSIX UID/GID verification for setting inode attributes */
DECL|function|inode_change_ok
r_int
id|inode_change_ok
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
multiline_comment|/*&n;&t; *&t;If force is set do it anyway.&n;&t; */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_FORCE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Make sure a caller can chown */
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_or
id|attr-&gt;ia_uid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Make sure caller can chgrp */
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
op_logical_neg
id|in_group_p
c_func
(paren
id|attr-&gt;ia_gid
)paren
op_logical_and
id|attr-&gt;ia_gid
op_ne
id|inode-&gt;i_gid
)paren
op_logical_and
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Make sure a caller can chmod */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Also check the setgid bit! */
r_if
c_cond
(paren
op_logical_neg
id|fsuser
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|in_group_p
c_func
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
ques
c_cond
id|attr-&gt;ia_gid
suffix:colon
id|inode-&gt;i_gid
)paren
)paren
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
)brace
multiline_comment|/* Check for setting the inode time */
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME_SET
)paren
op_logical_and
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME_SET
)paren
op_logical_and
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|fsuser
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the appropriate attributes from an attribute structure into&n; * the inode structure.&n; */
DECL|function|inode_setattr
r_void
id|inode_setattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
id|inode-&gt;i_uid
op_assign
id|attr-&gt;ia_uid
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
id|inode-&gt;i_gid
op_assign
id|attr-&gt;ia_gid
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
id|inode-&gt;i_size
op_assign
id|attr-&gt;ia_size
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME
)paren
id|inode-&gt;i_atime
op_assign
id|attr-&gt;ia_atime
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
id|inode-&gt;i_mtime
op_assign
id|attr-&gt;ia_mtime
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_CTIME
)paren
id|inode-&gt;i_ctime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|attr-&gt;ia_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsuser
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
id|inode-&gt;i_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
)brace
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * notify_change is called for inode-changing operations such as&n; * chown, chmod, utime, and truncate.  It is guaranteed (unlike&n; * write_inode) to be called from the context of the user requesting&n; * the change.&n; */
DECL|function|notify_change
r_int
id|notify_change
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_int
id|retval
suffix:semicolon
id|attr-&gt;ia_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
(paren
id|ATTR_ATIME
op_or
id|ATTR_MTIME
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME_SET
)paren
)paren
id|attr-&gt;ia_atime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME_SET
)paren
)paren
id|attr-&gt;ia_mtime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;s_op
op_logical_and
id|inode-&gt;i_sb-&gt;s_op-&gt;notify_change
)paren
r_return
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|notify_change
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|inode_setattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * bmap is needed for demand-loading and paging: if this function&n; * doesn&squot;t exist for a filesystem, then those things are impossible:&n; * executables cannot be run from the filesystem etc...&n; *&n; * This isn&squot;t as bad as it sounds: the read-routines might still work,&n; * so the filesystem would be otherwise ok (for example, you might have&n; * a DOS filesystem, which doesn&squot;t lend itself to bmap very well, but&n; * you could still transfer files to/from the filesystem)&n; */
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
DECL|function|invalidate_inodes
r_void
id|invalidate_inodes
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
comma
op_star
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|next
op_assign
id|first_inode
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr_inodes
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|inode
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|inode-&gt;i_next
suffix:semicolon
multiline_comment|/* clear_inode() changes the queues.. */
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
id|inode-&gt;i_count
op_logical_or
id|inode-&gt;i_dirt
op_logical_or
id|inode-&gt;i_lock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VFS: inode busy on removed device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|sync_inodes
r_void
id|sync_inodes
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|inode
op_assign
id|first_inode
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
id|nr_inodes
op_star
l_int|2
suffix:semicolon
id|i
op_increment
comma
id|inode
op_assign
id|inode-&gt;i_next
)paren
(brace
r_if
c_cond
(paren
id|dev
op_logical_and
id|inode-&gt;i_dev
op_ne
id|dev
)paren
r_continue
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
id|inode-&gt;i_dirt
)paren
id|write_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
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
op_logical_neg
id|inode
)paren
r_return
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
op_logical_neg
id|inode-&gt;i_count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VFS: iput: trying to free free inode&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VFS: device %s, inode %lu, mode=0%07o&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
id|inode-&gt;i_count
OG
l_int|1
)paren
(brace
id|inode-&gt;i_count
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
id|wake_up
c_func
(paren
op_amp
id|inode_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_pipe
)paren
(brace
r_int
r_int
id|page
op_assign
(paren
r_int
r_int
)paren
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
suffix:semicolon
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;s_op
op_logical_and
id|inode-&gt;i_sb-&gt;s_op-&gt;put_inode
)paren
(brace
id|inode-&gt;i_sb-&gt;s_op
op_member_access_from_pointer
id|put_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_dirt
)paren
(brace
id|write_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* we can sleep - so do again */
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_WRITABLE
c_func
(paren
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
(brace
multiline_comment|/* Here we can sleep also. Let&squot;s do it again&n;&t;&t;&t; * Dmitry Gorodchanin 02/11/96 &n;&t;&t;&t; */
id|inode-&gt;i_lock
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|drop
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
r_goto
id|repeat
suffix:semicolon
)brace
)brace
id|inode-&gt;i_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_mmap
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iput: inode %lu on device %s still has mappings.&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mmap
op_assign
l_int|NULL
suffix:semicolon
)brace
id|nr_free_inodes
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|value
r_static
r_inline
r_int
r_int
id|value
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
id|inode-&gt;i_lock
)paren
r_return
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_dirt
)paren
r_return
l_int|1000
suffix:semicolon
r_return
id|inode-&gt;i_nrpages
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
id|ino
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|inode
comma
op_star
id|best
suffix:semicolon
r_int
r_int
id|badness
op_assign
l_int|1000
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|nr_inodes
OL
id|max_inodes
op_logical_and
id|nr_free_inodes
OL
(paren
id|nr_inodes
op_rshift
l_int|1
)paren
)paren
id|grow_inodes
c_func
(paren
)paren
suffix:semicolon
id|repeat
suffix:colon
id|inode
op_assign
id|first_inode
suffix:semicolon
id|best
op_assign
l_int|NULL
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
id|nr_inodes
suffix:semicolon
id|inode
op_assign
id|inode-&gt;i_next
comma
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_count
)paren
(brace
r_int
r_int
id|i
op_assign
id|value
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|badness
)paren
(brace
id|best
op_assign
id|inode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|badness
op_assign
id|i
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|badness
)paren
r_if
c_cond
(paren
id|nr_inodes
OL
id|max_inodes
)paren
(brace
r_if
c_cond
(paren
id|grow_inodes
c_func
(paren
)paren
op_eq
l_int|0
)paren
r_goto
id|repeat
suffix:semicolon
)brace
id|inode
op_assign
id|best
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VFS: No free inodes - contact Linus&bslash;n&quot;
)paren
suffix:semicolon
id|sleep_on
c_func
(paren
op_amp
id|inode_wait
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_lock
)paren
(brace
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_dirt
)paren
(brace
id|write_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_count
)paren
r_goto
id|repeat
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|inode-&gt;i_sem.count
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ino
op_assign
op_increment
id|ino
suffix:semicolon
id|inode-&gt;i_dev
op_assign
l_int|0
suffix:semicolon
id|nr_free_inodes
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|nr_free_inodes
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;VFS: get_empty_inode: bad free inode count.&bslash;n&quot;
)paren
suffix:semicolon
id|nr_free_inodes
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|get_pipe_inode
r_struct
id|inode
op_star
id|get_pipe_inode
c_func
(paren
r_void
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|pipe_inode_operations
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|get_empty_inode
c_func
(paren
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PIPE_BASE
c_func
(paren
op_star
id|inode
)paren
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|pipe_inode_operations
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* sum of readers/writers */
id|PIPE_WAIT
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|NULL
suffix:semicolon
id|PIPE_START
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_LEN
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_RD_OPENERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WR_OPENERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|PIPE_READERS
c_func
(paren
op_star
id|inode
)paren
op_assign
id|PIPE_WRITERS
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
id|PIPE_LOCK
c_func
(paren
op_star
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_pipe
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mode
op_or_assign
id|S_IFIFO
op_or
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|__iget
r_struct
id|inode
op_star
id|__iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|nr
comma
r_int
id|crossmntp
)paren
(brace
r_static
r_struct
id|wait_queue
op_star
id|update_wait
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode_hash_entry
op_star
id|h
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|inode
op_star
id|empty
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
id|panic
c_func
(paren
l_string|&quot;VFS: iget with sb==NULL&quot;
)paren
suffix:semicolon
id|h
op_assign
id|hash
c_func
(paren
id|sb-&gt;s_dev
comma
id|nr
)paren
suffix:semicolon
id|repeat
suffix:colon
r_for
c_loop
(paren
id|inode
op_assign
id|h-&gt;inode
suffix:semicolon
id|inode
suffix:semicolon
id|inode
op_assign
id|inode-&gt;i_hash_next
)paren
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_eq
id|sb-&gt;s_dev
op_logical_and
id|inode-&gt;i_ino
op_eq
id|nr
)paren
r_goto
id|found_it
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty
)paren
(brace
id|h-&gt;updating
op_increment
suffix:semicolon
id|empty
op_assign
id|get_empty_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|h-&gt;updating
)paren
id|wake_up
c_func
(paren
op_amp
id|update_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|empty
)paren
r_goto
id|repeat
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|inode
op_assign
id|empty
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
id|nr
suffix:semicolon
id|inode-&gt;i_flags
op_assign
id|sb-&gt;s_flags
suffix:semicolon
id|put_last_free
c_func
(paren
id|inode
)paren
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|read_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|return_it
suffix:semicolon
id|found_it
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_count
)paren
id|nr_free_inodes
op_decrement
suffix:semicolon
id|inode-&gt;i_count
op_increment
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
id|inode-&gt;i_dev
op_ne
id|sb-&gt;s_dev
op_logical_or
id|inode-&gt;i_ino
op_ne
id|nr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Whee.. inode changed from under us. Tell Linus&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|crossmntp
op_logical_and
id|inode-&gt;i_mount
)paren
(brace
r_struct
id|inode
op_star
id|tmp
op_assign
id|inode-&gt;i_mount
suffix:semicolon
id|tmp-&gt;i_count
op_increment
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode
op_assign
id|tmp
suffix:semicolon
id|wait_on_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|empty
)paren
id|iput
c_func
(paren
id|empty
)paren
suffix:semicolon
id|return_it
suffix:colon
r_while
c_loop
(paren
id|h-&gt;updating
)paren
id|sleep_on
c_func
(paren
op_amp
id|update_wait
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * The &quot;new&quot; scheduling primitives (new as of 0.97 or so) allow this to&n; * be done without disabling interrupts (other than in the actual queue&n; * updating things: only a couple of 386 instructions). This should be&n; * much better for interrupt latency.&n; */
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
id|inode-&gt;i_lock
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
eof
