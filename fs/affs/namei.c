multiline_comment|/*&n; *  linux/fs/affs/namei.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* Simple toupper() for DOS&bslash;1 */
r_static
r_int
r_int
DECL|function|affs_toupper
id|affs_toupper
c_func
(paren
r_int
r_int
id|ch
)paren
(brace
r_return
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
ques
c_cond
id|ch
op_sub_assign
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
)paren
suffix:colon
id|ch
suffix:semicolon
)brace
multiline_comment|/* International toupper() for DOS&bslash;3 (&quot;international&quot;) */
r_static
r_int
r_int
DECL|function|affs_intl_toupper
id|affs_intl_toupper
c_func
(paren
r_int
r_int
id|ch
)paren
(brace
r_return
(paren
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
id|ch
op_ge
l_int|0xE0
op_logical_and
id|ch
op_le
l_int|0xFE
op_logical_and
id|ch
op_ne
l_int|0xF7
)paren
ques
c_cond
id|ch
op_minus
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
)paren
suffix:colon
id|ch
suffix:semicolon
)brace
r_static
r_int
id|affs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|affs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|variable|affs_dentry_operations
r_struct
id|dentry_operations
id|affs_dentry_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* d_validate&t;*/
id|affs_hash_dentry
comma
multiline_comment|/* d_hash&t;*/
id|affs_compare_dentry
comma
multiline_comment|/* d_compare&t;*/
l_int|NULL
multiline_comment|/* d_delete&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Note: the dentry argument is the parent dentry.&n; */
r_static
r_int
DECL|function|affs_hash_dentry
id|affs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_int
r_int
(paren
op_star
id|toupper
)paren
(paren
r_int
r_int
)paren
op_assign
id|affs_toupper
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|affs_check_name
c_func
(paren
id|qstr-&gt;name
comma
id|qstr-&gt;len
)paren
)paren
)paren
r_return
id|i
suffix:semicolon
multiline_comment|/* Check whether to use the international &squot;toupper&squot; routine */
r_if
c_cond
(paren
id|AFFS_I2FSTYPE
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
id|toupper
op_assign
id|affs_intl_toupper
suffix:semicolon
id|hash
op_assign
id|init_name_hash
c_func
(paren
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
id|qstr-&gt;len
op_logical_and
id|i
OL
l_int|30
suffix:semicolon
id|i
op_increment
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|toupper
c_func
(paren
id|qstr-&gt;name
(braket
id|i
)braket
)paren
comma
id|hash
)paren
suffix:semicolon
id|qstr-&gt;hash
op_assign
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_compare_dentry
id|affs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_int
r_int
(paren
op_star
id|toupper
)paren
(paren
r_int
r_int
)paren
op_assign
id|affs_toupper
suffix:semicolon
r_int
id|alen
op_assign
id|a-&gt;len
suffix:semicolon
r_int
id|blen
op_assign
id|b-&gt;len
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* &squot;a&squot; is the qstr of an already existing dentry, so the name&n;&t; * must be valid. &squot;b&squot; must be validated first.&n;&t; */
r_if
c_cond
(paren
id|affs_check_name
c_func
(paren
id|b-&gt;name
comma
id|b-&gt;len
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* If the names are longer than the allowed 30 chars,&n;&t; * the excess is ignored, so their length may differ.&n;&t; */
r_if
c_cond
(paren
id|alen
OG
l_int|30
)paren
id|alen
op_assign
l_int|30
suffix:semicolon
r_if
c_cond
(paren
id|blen
OG
l_int|30
)paren
id|blen
op_assign
l_int|30
suffix:semicolon
r_if
c_cond
(paren
id|alen
op_ne
id|blen
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Check whether to use the international &squot;toupper&squot; routine */
r_if
c_cond
(paren
id|AFFS_I2FSTYPE
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
id|toupper
op_assign
id|affs_intl_toupper
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
id|alen
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|toupper
c_func
(paren
id|a-&gt;name
(braket
id|i
)braket
)paren
op_ne
id|toupper
c_func
(paren
id|b-&gt;name
(braket
id|i
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE! unlike strncmp, affs_match returns 1 for success, 0 for failure.&n; */
r_static
r_int
DECL|function|affs_match
id|affs_match
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
comma
r_const
r_int
r_char
op_star
id|compare
comma
r_int
id|dlen
comma
r_int
id|intl
)paren
(brace
r_int
r_int
(paren
op_star
id|toupper
)paren
(paren
r_int
r_int
)paren
op_assign
id|intl
ques
c_cond
id|affs_intl_toupper
suffix:colon
id|affs_toupper
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compare
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|30
)paren
id|len
op_assign
l_int|30
suffix:semicolon
r_if
c_cond
(paren
id|dlen
OG
l_int|30
)paren
id|dlen
op_assign
l_int|30
suffix:semicolon
multiline_comment|/* &quot;&quot; means &quot;.&quot; ---&gt; so paths like &quot;/usr/lib//libc.a&quot; work */
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_and
id|dlen
op_eq
l_int|1
op_logical_and
id|compare
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dlen
op_ne
id|len
)paren
r_return
l_int|0
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
id|len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|toupper
c_func
(paren
id|name
(braket
id|i
)braket
)paren
op_ne
id|toupper
c_func
(paren
id|compare
(braket
id|i
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|affs_hash_name
id|affs_hash_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|intl
comma
r_int
id|hashsize
)paren
(brace
r_int
r_int
id|i
comma
id|x
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|30
)paren
id|len
op_assign
l_int|30
suffix:semicolon
id|x
op_assign
id|len
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
id|len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|intl
)paren
id|x
op_assign
(paren
id|x
op_star
l_int|13
op_plus
id|affs_intl_toupper
c_func
(paren
id|name
(braket
id|i
)braket
op_amp
l_int|0xFF
)paren
)paren
op_amp
l_int|0x7ff
suffix:semicolon
r_else
id|x
op_assign
(paren
id|x
op_star
l_int|13
op_plus
id|affs_toupper
c_func
(paren
id|name
(braket
id|i
)braket
op_amp
l_int|0xFF
)paren
)paren
op_amp
l_int|0x7ff
suffix:semicolon
r_return
id|x
op_mod
id|hashsize
suffix:semicolon
)brace
r_static
r_struct
id|buffer_head
op_star
DECL|function|affs_find_entry
id|affs_find_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
r_int
op_star
id|ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|intl
op_assign
id|AFFS_I2FSTYPE
c_func
(paren
id|dir
)paren
suffix:semicolon
id|s32
id|key
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: find_entry(&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
id|namelen
comma
id|name
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|dir-&gt;i_ino
comma
id|AFFS_I2BSIZE
c_func
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|namelen
op_eq
l_int|1
op_logical_and
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_star
id|ino
op_assign
id|dir-&gt;i_ino
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|namelen
op_eq
l_int|2
op_logical_and
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_star
id|ino
op_assign
id|affs_parent_ino
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
id|key
op_assign
id|AFFS_GET_HASHENTRY
c_func
(paren
id|bh-&gt;b_data
comma
id|affs_hash_name
c_func
(paren
id|name
comma
id|namelen
comma
id|intl
comma
id|AFFS_I2HSIZE
c_func
(paren
id|dir
)paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
op_star
id|cname
suffix:semicolon
r_int
id|cnamelen
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|dir-&gt;i_dev
comma
id|key
comma
id|AFFS_I2BSIZE
c_func
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_break
suffix:semicolon
id|cnamelen
op_assign
id|affs_get_file_name
c_func
(paren
id|AFFS_I2BSIZE
c_func
(paren
id|dir
)paren
comma
id|bh-&gt;b_data
comma
op_amp
id|cname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|affs_match
c_func
(paren
id|name
comma
id|namelen
comma
id|cname
comma
id|cnamelen
comma
id|intl
)paren
)paren
r_break
suffix:semicolon
id|key
op_assign
id|be32_to_cpu
c_func
(paren
id|FILE_END
c_func
(paren
id|bh-&gt;b_data
comma
id|dir
)paren
op_member_access_from_pointer
id|hash_chain
)paren
suffix:semicolon
)brace
op_star
id|ino
op_assign
id|key
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_int
DECL|function|affs_lookup
id|affs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: lookup(&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
comma
op_amp
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
r_if
c_cond
(paren
id|FILE_END
c_func
(paren
id|bh-&gt;b_data
comma
id|dir
)paren
op_member_access_from_pointer
id|original
)paren
id|ino
op_assign
id|be32_to_cpu
c_func
(paren
id|FILE_END
c_func
(paren
id|bh-&gt;b_data
comma
id|dir
)paren
op_member_access_from_pointer
id|original
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|dentry-&gt;d_op
op_assign
op_amp
id|affs_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|affs_unlink
id|affs_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: unlink(dir=%ld,&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
comma
op_amp
id|ino
)paren
)paren
)paren
r_goto
id|unlink_done
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_and
id|current-&gt;fsuid
op_ne
id|dir-&gt;i_uid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_goto
id|unlink_done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_remove_header
c_func
(paren
id|bh
comma
id|inode
)paren
)paren
OL
l_int|0
)paren
r_goto
id|unlink_done
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|retval
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|d_delete
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|unlink_done
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_int
DECL|function|affs_create
id|affs_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: create(%lu,&bslash;&quot;%.*s&bslash;&quot;,0%o)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|mode
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: ino=%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_sb-&gt;u.affs_sb.s_flags
op_amp
id|SF_OFS
)paren
id|inode-&gt;i_op
op_assign
op_amp
id|affs_file_inode_operations_ofs
suffix:semicolon
r_else
id|inode-&gt;i_op
op_assign
op_amp
id|affs_file_inode_operations
suffix:semicolon
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
l_int|NULL
comma
id|inode
comma
id|dentry
comma
id|ST_FILE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_iput
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;u.affs_i.i_protect
op_assign
id|mode_to_prot
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_iput
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_int
DECL|function|affs_mkdir
id|affs_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: mkdir(%lu,&bslash;&quot;%.*s&bslash;&quot;,0%o)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|mode
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|affs_dir_inode_operations
suffix:semicolon
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
l_int|NULL
comma
id|inode
comma
id|dentry
comma
id|ST_USERDIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_iput
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
(paren
id|mode
op_amp
l_int|0777
op_amp
op_complement
id|current-&gt;fs-&gt;umask
)paren
suffix:semicolon
id|inode-&gt;u.affs_i.i_protect
op_assign
id|mode_to_prot
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_iput
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_static
r_int
DECL|function|empty_dir
id|empty_dir
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|hashsize
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|hashsize
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|dir_front
op_star
)paren
id|bh-&gt;b_data
)paren
op_member_access_from_pointer
id|hashtable
(braket
id|hashsize
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|affs_rmdir
id|affs_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: rmdir(dir=%lu,&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
comma
op_amp
id|ino
)paren
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_and
id|current-&gt;fsuid
op_ne
id|dir-&gt;i_uid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_ne
id|dir-&gt;i_dev
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
id|dir
)paren
multiline_comment|/* we may not delete &quot;.&quot;, but &quot;../dir&quot; is ok */
r_goto
id|rmdir_done
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure the directory is empty and the dentry isn&squot;t busy.&n;&t; */
r_if
c_cond
(paren
id|dentry-&gt;d_count
OG
l_int|1
)paren
id|shrink_dcache_parent
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty_dir
c_func
(paren
id|bh
comma
id|AFFS_I2HSIZE
c_func
(paren
id|inode
)paren
)paren
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_count
OG
l_int|1
)paren
r_goto
id|rmdir_done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_remove_header
c_func
(paren
id|bh
comma
id|inode
)paren
)paren
OL
l_int|0
)paren
r_goto
id|rmdir_done
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|retval
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|d_delete
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|rmdir_done
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_int
DECL|function|affs_symlink
id|affs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|i
comma
id|maxlen
comma
id|error
suffix:semicolon
r_char
id|c
comma
id|lc
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: symlink(%lu,&bslash;&quot;%.*s&bslash;&quot; -&gt; &bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|symname
)paren
suffix:semicolon
id|maxlen
op_assign
l_int|4
op_star
id|AFFS_I2HSIZE
c_func
(paren
id|dir
)paren
op_minus
l_int|1
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|affs_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0777
suffix:semicolon
id|inode-&gt;u.affs_i.i_protect
op_assign
id|mode_to_prot
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|AFFS_I2BSIZE
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|out_iput
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
(paren
(paren
r_struct
id|slink_front
op_star
)paren
id|bh-&gt;b_data
)paren
op_member_access_from_pointer
id|symname
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_while
c_loop
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
id|symname
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|inode-&gt;i_sb-&gt;u.affs_sb.s_volume
(braket
id|i
)braket
)paren
multiline_comment|/* Cannot overflow */
op_star
id|p
op_increment
op_assign
id|inode-&gt;i_sb-&gt;u.affs_sb.s_volume
(braket
id|i
op_increment
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|maxlen
op_logical_and
(paren
id|c
op_assign
op_star
id|symname
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
op_logical_and
id|lc
op_eq
l_char|&squot;/&squot;
op_logical_and
op_star
id|symname
op_eq
l_char|&squot;.&squot;
op_logical_and
id|symname
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|symname
op_add_assign
l_int|2
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
op_logical_and
id|lc
op_eq
l_char|&squot;/&squot;
op_logical_and
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|symname
op_increment
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
id|lc
op_assign
id|c
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lc
op_eq
l_char|&squot;/&squot;
)paren
r_while
c_loop
(paren
op_star
id|symname
op_eq
l_char|&squot;/&squot;
)paren
id|symname
op_increment
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* N.B. This test shouldn&squot;t be necessary ... dentry must be negative */
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
r_goto
id|out_release
suffix:semicolon
multiline_comment|/* N.B. Shouldn&squot;t we add the entry before dirtying the buffer? */
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
l_int|NULL
comma
id|inode
comma
id|dentry
comma
id|ST_SOFTLINK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_release
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_release
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|out_iput
suffix:colon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_int
DECL|function|affs_link
id|affs_link
c_func
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|oldinode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: link(%lu,%lu,&bslash;&quot;%.*s&bslash;&quot;)&bslash;n&quot;
comma
id|oldinode-&gt;i_ino
comma
id|dir-&gt;i_ino
comma
(paren
r_int
)paren
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* N.B. Do we need this test? The dentry must be negative ... */
id|bh
op_assign
id|affs_find_entry
c_func
(paren
id|dir
comma
id|dentry
comma
op_amp
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldinode-&gt;u.affs_i.i_hlink
)paren
(brace
multiline_comment|/* Cannot happen */
id|affs_warning
c_func
(paren
id|dir-&gt;i_sb
comma
l_string|&quot;link&quot;
comma
l_string|&quot;Impossible link to link&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|affs_new_inode
c_func
(paren
id|dir
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_op
op_assign
id|oldinode-&gt;i_op
suffix:semicolon
id|inode-&gt;u.affs_i.i_protect
op_assign
id|mode_to_prot
c_func
(paren
id|oldinode-&gt;i_mode
)paren
suffix:semicolon
id|inode-&gt;u.affs_i.i_original
op_assign
id|oldinode-&gt;i_ino
suffix:semicolon
id|inode-&gt;u.affs_i.i_hlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|oldinode-&gt;i_mtime
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|oldinode-&gt;i_mode
)paren
)paren
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
id|oldinode
comma
id|inode
comma
id|dentry
comma
id|ST_LINKDIR
)paren
suffix:semicolon
r_else
id|error
op_assign
id|affs_add_entry
c_func
(paren
id|dir
comma
id|oldinode
comma
id|inode
comma
id|dentry
comma
id|ST_LINKFILE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|oldinode
)paren
suffix:semicolon
id|oldinode-&gt;i_count
op_increment
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|oldinode
)paren
suffix:semicolon
)brace
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_int
DECL|function|affs_rename
id|affs_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_struct
id|inode
op_star
id|old_inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|old_bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|new_bh
suffix:semicolon
r_int
r_int
id|old_ino
suffix:semicolon
r_int
r_int
id|new_ino
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: rename(old=%lu,&bslash;&quot;%*s&bslash;&quot; (inode=%p) to new=%lu,&bslash;&quot;%*s&bslash;&quot; (inode=%p))&bslash;n&quot;
comma
id|old_dir-&gt;i_ino
comma
id|old_dentry-&gt;d_name.len
comma
id|old_dentry-&gt;d_name.name
comma
id|old_inode
comma
id|new_dir-&gt;i_ino
comma
id|new_dentry-&gt;d_name.len
comma
id|new_dentry-&gt;d_name.name
comma
id|new_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_check_name
c_func
(paren
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|new_bh
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|old_bh
op_assign
id|affs_find_entry
c_func
(paren
id|old_dir
comma
id|old_dentry
comma
op_amp
id|old_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_bh
)paren
r_goto
id|end_rename
suffix:semicolon
id|new_bh
op_assign
id|affs_find_entry
c_func
(paren
id|new_dir
comma
id|new_dentry
comma
op_amp
id|new_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_bh
op_logical_and
op_logical_neg
id|new_inode
)paren
(brace
id|affs_error
c_func
(paren
id|old_inode-&gt;i_sb
comma
l_string|&quot;affs_rename&quot;
comma
l_string|&quot;No inode for entry found (key=%lu)&bslash;n&quot;
comma
id|new_ino
)paren
suffix:semicolon
r_goto
id|end_rename
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_inode
op_eq
id|old_inode
)paren
(brace
r_if
c_cond
(paren
id|old_ino
op_eq
id|new_ino
)paren
(brace
multiline_comment|/* Filename might have changed case&t;*/
id|retval
op_assign
id|new_dentry-&gt;d_name.len
OL
l_int|31
ques
c_cond
id|new_dentry-&gt;d_name.len
suffix:colon
l_int|30
suffix:semicolon
id|strncpy
c_func
(paren
id|DIR_END
c_func
(paren
id|old_bh-&gt;b_data
comma
id|old_inode
)paren
op_member_access_from_pointer
id|dir_name
op_plus
l_int|1
comma
id|new_dentry-&gt;d_name.name
comma
id|retval
)paren
suffix:semicolon
id|DIR_END
c_func
(paren
id|old_bh-&gt;b_data
comma
id|old_inode
)paren
op_member_access_from_pointer
id|dir_name
(braket
l_int|0
)braket
op_assign
id|retval
suffix:semicolon
r_goto
id|new_checksum
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|end_rename
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_inode
op_logical_and
id|S_ISDIR
c_func
(paren
id|new_inode-&gt;i_mode
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EISDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|is_subdir
c_func
(paren
id|new_dentry
comma
id|old_dentry
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
r_if
c_cond
(paren
id|new_dentry-&gt;d_count
OG
l_int|1
)paren
id|shrink_dcache_parent
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty_dir
c_func
(paren
id|new_bh
comma
id|AFFS_I2HSIZE
c_func
(paren
id|new_inode
)paren
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|new_dentry-&gt;d_count
OG
l_int|1
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|new_inode-&gt;i_mode
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|is_subdir
c_func
(paren
id|new_dentry
comma
id|old_dentry
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
r_if
c_cond
(paren
id|affs_parent_ino
c_func
(paren
id|old_inode
)paren
op_ne
id|old_dir-&gt;i_ino
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
multiline_comment|/* Unlink destination if it already exists */
r_if
c_cond
(paren
id|new_inode
)paren
(brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_remove_header
c_func
(paren
id|new_bh
comma
id|new_dir
)paren
)paren
OL
l_int|0
)paren
r_goto
id|end_rename
suffix:semicolon
id|new_inode-&gt;i_nlink
op_assign
id|retval
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode-&gt;i_ino
op_eq
id|new_ino
)paren
id|new_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Remove header from its parent directory. */
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_remove_hash
c_func
(paren
id|old_bh
comma
id|old_dir
)paren
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
multiline_comment|/* And insert it into the new directory with the new name. */
id|affs_copy_name
c_func
(paren
id|FILE_END
c_func
(paren
id|old_bh-&gt;b_data
comma
id|old_inode
)paren
op_member_access_from_pointer
id|file_name
comma
id|new_dentry-&gt;d_name.name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|affs_insert_hash
c_func
(paren
id|new_dir-&gt;i_ino
comma
id|old_bh
comma
id|new_dir
)paren
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
id|new_checksum
suffix:colon
id|affs_fix_checksum
c_func
(paren
id|AFFS_I2BSIZE
c_func
(paren
id|new_dir
)paren
comma
id|old_bh-&gt;b_data
comma
l_int|5
)paren
suffix:semicolon
id|new_dir-&gt;i_ctime
op_assign
id|new_dir-&gt;i_mtime
op_assign
id|old_dir-&gt;i_ctime
op_assign
id|old_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|new_dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|old_dir-&gt;i_version
op_assign
op_increment
id|event
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_dir
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|old_bh
comma
l_int|1
)paren
suffix:semicolon
id|d_move
c_func
(paren
id|old_dentry
comma
id|new_dentry
)paren
suffix:semicolon
id|end_rename
suffix:colon
id|affs_brelse
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof
