multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/expire.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *  Copyright 1999 Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &quot;autofs_i.h&quot;
multiline_comment|/*&n; * Determine if a dentry tree is in use.  This is much the&n; * same as the standard is_root_busy() function, except&n; * that :-&n; *  - the extra dentry reference in autofs dentries is not&n; *    considered to be busy&n; *  - mountpoints within the tree are not busy&n; *  - it traverses across mountpoints&n; * XXX doesn&squot;t consider children of covered dentries at mountpoints&n; */
DECL|function|is_tree_busy
r_static
r_int
id|is_tree_busy
c_func
(paren
r_struct
id|dentry
op_star
id|root
)paren
(brace
r_struct
id|dentry
op_star
id|this_parent
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_int
id|count
suffix:semicolon
id|root
op_assign
id|root-&gt;d_mounts
suffix:semicolon
id|count
op_assign
id|root-&gt;d_count
suffix:semicolon
id|this_parent
op_assign
id|root
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: starting at %.*s/%.*s, d_count=%d&bslash;n&quot;
comma
id|root-&gt;d_covers-&gt;d_parent-&gt;d_name.len
comma
id|root-&gt;d_covers-&gt;d_parent-&gt;d_name.name
comma
id|root-&gt;d_name.len
comma
id|root-&gt;d_name.name
comma
id|root-&gt;d_count
)paren
)paren
suffix:semicolon
multiline_comment|/* Ignore autofs&squot;s extra reference */
r_if
c_cond
(paren
id|is_autofs4_dentry
c_func
(paren
id|root
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: autofs&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Mountpoints don&squot;t count */
r_if
c_cond
(paren
id|d_mountpoint
c_func
(paren
id|root
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: mountpoint&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|repeat
suffix:colon
id|next
op_assign
id|this_parent-&gt;d_mounts-&gt;d_subdirs.next
suffix:semicolon
id|resume
suffix:colon
r_while
c_loop
(paren
id|next
op_ne
op_amp
id|this_parent-&gt;d_mounts-&gt;d_subdirs
)paren
(brace
r_int
id|adj
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
op_assign
id|next
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
id|next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|dentry
op_assign
id|dentry-&gt;d_mounts
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: considering %.*s/%.*s, d_count=%d, count=%d&bslash;n&quot;
comma
id|this_parent-&gt;d_name.len
comma
id|this_parent-&gt;d_name.name
comma
id|dentry-&gt;d_covers-&gt;d_name.len
comma
id|dentry-&gt;d_covers-&gt;d_name.name
comma
id|dentry-&gt;d_count
comma
id|count
)paren
)paren
suffix:semicolon
multiline_comment|/* Decrement count for unused children */
id|count
op_add_assign
(paren
id|dentry-&gt;d_count
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Mountpoints don&squot;t count */
r_if
c_cond
(paren
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: mountpoint&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|adj
op_increment
suffix:semicolon
)brace
multiline_comment|/* Ignore autofs&squot;s extra reference */
r_if
c_cond
(paren
id|is_autofs4_dentry
c_func
(paren
id|dentry
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: autofs&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|adj
op_increment
suffix:semicolon
)brace
id|count
op_sub_assign
id|adj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dentry-&gt;d_mounts-&gt;d_subdirs
)paren
)paren
(brace
id|this_parent
op_assign
id|dentry-&gt;d_mounts
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* root is busy if any leaf is busy */
r_if
c_cond
(paren
id|dentry-&gt;d_count
op_ne
id|adj
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: busy leaf (d_count=%d adj=%d)&bslash;n&quot;
comma
id|dentry-&gt;d_count
comma
id|adj
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * All done at this level ... ascend and resume the search.&n;&t; */
r_if
c_cond
(paren
id|this_parent
op_ne
id|root
)paren
(brace
id|next
op_assign
id|this_parent-&gt;d_covers-&gt;d_child.next
suffix:semicolon
id|this_parent
op_assign
id|this_parent-&gt;d_covers-&gt;d_parent
suffix:semicolon
r_goto
id|resume
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;is_tree_busy: count=%d&bslash;n&quot;
comma
id|count
)paren
)paren
suffix:semicolon
r_return
id|count
op_ne
l_int|0
suffix:semicolon
multiline_comment|/* remaining users? */
)brace
multiline_comment|/*&n; * Find an eligible tree to time-out&n; * A tree is eligible if :-&n; *  - it is unused by any user process&n; *  - it has been unused for exp_timeout time&n; */
DECL|function|autofs4_expire
r_static
r_struct
id|dentry
op_star
id|autofs4_expire
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
id|do_now
)paren
(brace
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* snapshot of now */
r_int
r_int
id|timeout
suffix:semicolon
r_struct
id|dentry
op_star
id|root
op_assign
id|sb-&gt;s_root
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;exp_timeout
op_logical_or
op_logical_neg
id|root
)paren
r_return
l_int|NULL
suffix:semicolon
id|timeout
op_assign
id|sbi-&gt;exp_timeout
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|root-&gt;d_subdirs.next
suffix:semicolon
id|tmp
op_ne
op_amp
id|root-&gt;d_subdirs
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* dentry in the process of being deleted */
r_continue
suffix:semicolon
)brace
multiline_comment|/* No point expiring a pending mount */
r_if
c_cond
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|do_now
)paren
(brace
multiline_comment|/* Too young to die */
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|ino-&gt;last_used
op_plus
id|timeout
comma
id|now
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* update last_used here :- &n;&t;&t;&t;   - obviously makes sense if it is in use now&n;&t;&t;&t;   - less obviously, prevents rapid-fire expire&n;&t;&t;&t;   attempts if expire fails the first time */
id|ino-&gt;last_used
op_assign
id|now
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_tree_busy
c_func
(paren
id|dentry
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_expire: returning %p %.*s&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
multiline_comment|/* Start from here next time */
id|list_del
c_func
(paren
op_amp
id|root-&gt;d_subdirs
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|root-&gt;d_subdirs
comma
op_amp
id|dentry-&gt;d_child
)paren
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Perform an expiry operation */
DECL|function|autofs4_expire_run
r_int
id|autofs4_expire_run
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|autofs_packet_expire
op_star
id|pkt_p
)paren
(brace
r_struct
id|autofs_packet_expire
id|pkt
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pkt
comma
l_int|0
comma
r_sizeof
id|pkt
)paren
suffix:semicolon
id|pkt.hdr.proto_version
op_assign
id|sbi-&gt;version
suffix:semicolon
id|pkt.hdr.type
op_assign
id|autofs_ptype_expire
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dentry
op_assign
id|autofs4_expire
c_func
(paren
id|sb
comma
id|sbi
comma
l_int|0
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|pkt.len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|memcpy
c_func
(paren
id|pkt.name
comma
id|dentry-&gt;d_name.name
comma
id|pkt.len
)paren
suffix:semicolon
id|pkt.name
(braket
id|pkt.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|pkt_p
comma
op_amp
id|pkt
comma
r_sizeof
(paren
r_struct
id|autofs_packet_expire
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Call repeatedly until it returns -EAGAIN, meaning there&squot;s nothing&n;   more to be done */
DECL|function|autofs4_expire_multi
r_int
id|autofs4_expire_multi
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
op_star
id|arg
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_int
id|do_now
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_logical_and
id|get_user
c_func
(paren
id|do_now
comma
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dentry
op_assign
id|autofs4_expire
c_func
(paren
id|sb
comma
id|sbi
comma
id|do_now
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|autofs_info
op_star
id|de_info
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* This is synchronous because it makes the daemon a&n;                   little easier */
id|de_info-&gt;flags
op_or_assign
id|AUTOFS_INF_EXPIRING
suffix:semicolon
id|ret
op_assign
id|autofs4_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
comma
id|NFY_EXPIRE
)paren
suffix:semicolon
id|de_info-&gt;flags
op_and_assign
op_complement
id|AUTOFS_INF_EXPIRING
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
