multiline_comment|/*&n; *  linux/fs/sysv/namei.c&n; *&n; *  minix/namei.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/namei.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/namei.c&n; *  Copyright (C) 1993  Bruno Haible&n; *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* compare strings: name[0..len-1] (not zero-terminated) and&n; * buffer[0..] (filled with zeroes up to buffer[0..maxlen-1])&n; */
DECL|function|namecompare
r_static
r_inline
r_int
id|namecompare
c_func
(paren
r_int
id|len
comma
r_int
id|maxlen
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|len
OG
id|maxlen
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|maxlen
op_logical_and
id|buffer
(braket
id|len
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ok, we cannot use strncmp, as the name is not in our data space. [Now it is!]&n; * Thus we&squot;ll have to use sysv_match. No big problem. Match also makes&n; * some sanity tests.&n; *&n; * NOTE! unlike strncmp, sysv_match returns 1 for success, 0 for failure.&n; */
DECL|function|sysv_match
r_static
r_int
id|sysv_match
c_func
(paren
r_int
id|len
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|sysv_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
op_logical_or
id|len
OG
id|SYSV_NAMELEN
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* &quot;&quot; means &quot;.&quot; ---&gt; so paths like &quot;/usr/lib//libc.a&quot; work */
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_and
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|de-&gt;name
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|namecompare
c_func
(paren
id|len
comma
id|SYSV_NAMELEN
comma
id|name
comma
id|de-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;sysv_find_entry()&n; *&n; * finds an entry in the specified directory with the wanted name. It&n; * returns the cache buffer in which the entry was found, and the entry&n; * itself (as a parameter - res_dir). It does NOT read the inode of the&n; * entry - you&squot;ll have to do that yourself if you want to.&n; */
DECL|function|sysv_find_entry
r_static
r_struct
id|buffer_head
op_star
id|sysv_find_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|sysv_dir_entry
op_star
op_star
id|res_dir
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
r_int
id|pos
comma
id|block
comma
id|offset
suffix:semicolon
multiline_comment|/* pos = block * block_size + offset */
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
id|SYSV_NAMELEN
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_truncate
)paren
id|namelen
op_assign
id|SYSV_NAMELEN
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|pos
op_assign
id|block
op_assign
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|dir-&gt;i_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|dir
comma
id|block
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
multiline_comment|/* offset = 0; */
id|block
op_increment
suffix:semicolon
id|pos
op_add_assign
id|sb-&gt;sv_block_size
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sysv_match
c_func
(paren
id|namelen
comma
id|name
comma
op_star
id|res_dir
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
)paren
)paren
r_return
id|bh
suffix:semicolon
id|pos
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
id|offset
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|sb-&gt;sv_block_size
)paren
r_continue
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sysv_lookup
r_static
r_struct
id|dentry
op_star
id|sysv_lookup
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
l_int|NULL
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
r_int
id|ino
op_assign
id|de-&gt;inode
suffix:semicolon
id|brelse
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
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;sysv_add_entry()&n; *&n; * adds a file entry to the specified directory, returning a possible&n; * error value if it fails.&n; *&n; * NOTE!! The inode part of &squot;de&squot; is left at 0 - which means you&n; * may not sleep between calling this and putting something into&n; * the entry, as someone else might have used it while you slept.&n; */
DECL|function|sysv_add_entry
r_static
r_int
id|sysv_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|buffer_head
op_star
op_star
id|res_buf
comma
r_struct
id|sysv_dir_entry
op_star
op_star
id|res_dir
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|pos
comma
id|block
comma
id|offset
suffix:semicolon
multiline_comment|/* pos = block * block_size + offset */
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
op_star
id|res_buf
op_assign
l_int|NULL
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
id|SYSV_NAMELEN
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;sv_truncate
)paren
id|namelen
op_assign
id|SYSV_NAMELEN
suffix:semicolon
r_else
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|pos
op_assign
id|block
op_assign
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|dir
comma
id|block
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
id|pos
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
id|offset
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|dir-&gt;i_size
)paren
(brace
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_size
op_assign
id|pos
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
r_if
c_cond
(paren
id|namecompare
c_func
(paren
id|namelen
comma
id|SYSV_NAMELEN
comma
id|name
comma
id|de-&gt;name
)paren
)paren
(brace
id|brelse
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
)brace
r_else
(brace
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
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
id|SYSV_NAMELEN
suffix:semicolon
id|i
op_increment
)paren
id|de-&gt;name
(braket
id|i
)braket
op_assign
(paren
id|i
OL
id|namelen
)paren
ques
c_cond
id|name
(braket
id|i
)braket
suffix:colon
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
op_star
id|res_dir
op_assign
id|de
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
id|sb-&gt;sv_block_size
)paren
r_continue
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
op_star
id|res_buf
op_assign
id|bh
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_create
r_static
r_int
id|sysv_create
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
r_int
id|error
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
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|inode
op_assign
id|sysv_new_inode
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|sysv_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|sysv_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysv_aops
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|sysv_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
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
r_return
id|error
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_mknod
r_static
r_int
id|sysv_mknod
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
comma
r_int
id|rdev
)paren
(brace
r_int
id|error
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
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
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
id|inode
op_assign
id|sysv_new_inode
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|mode
comma
id|rdev
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|sysv_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
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
r_return
id|error
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_mkdir
r_static
r_int
id|sysv_mkdir
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
r_int
id|error
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
comma
op_star
id|dir_block
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
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
id|dir-&gt;i_nlink
op_ge
id|dir-&gt;i_sb-&gt;sv_link_max
)paren
r_return
op_minus
id|EMLINK
suffix:semicolon
id|inode
op_assign
id|sysv_new_inode
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|sysv_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|sysv_dir_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|2
op_star
id|SYSV_DIRSIZE
suffix:semicolon
id|dir_block
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_block
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|dir_block-&gt;b_data
op_plus
l_int|0
op_star
id|SYSV_DIRSIZE
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
multiline_comment|/* rest of de-&gt;name is zero, see sysv_new_block */
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|dir_block-&gt;b_data
op_plus
l_int|1
op_star
id|SYSV_DIRSIZE
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
multiline_comment|/* rest of de-&gt;name is zero, see sysv_new_block */
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dir_block
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|dir_block
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_ISGID
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|sysv_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * routine to check that the specified directory is empty (for rmdir)&n; */
DECL|function|empty_dir
r_static
r_int
id|empty_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
r_int
id|pos
comma
id|block
comma
id|offset
suffix:semicolon
multiline_comment|/* pos = block * block_size + offset */
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|block
op_assign
l_int|0
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|pos
op_assign
id|offset
op_assign
l_int|2
op_star
id|SYSV_DIRSIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
(paren
id|inode-&gt;i_size
)paren
op_mod
id|SYSV_DIRSIZE
)paren
r_goto
id|bad_dir
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OL
id|pos
)paren
r_goto
id|bad_dir
suffix:semicolon
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|bad_dir
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|0
op_star
id|SYSV_DIRSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
op_logical_or
id|strcmp
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;.&quot;
)paren
)paren
r_goto
id|bad_dir
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|1
op_star
id|SYSV_DIRSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
op_logical_or
id|strcmp
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;..&quot;
)paren
)paren
r_goto
id|bad_dir
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|inode-&gt;i_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|sysv_file_bread
c_func
(paren
id|inode
comma
id|block
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
multiline_comment|/* offset = 0; */
id|block
op_increment
suffix:semicolon
id|pos
op_add_assign
id|sb-&gt;sv_block_size
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|de
op_assign
(paren
r_struct
id|sysv_dir_entry
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
id|pos
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
id|offset
op_add_assign
id|SYSV_DIRSIZE
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
id|sb-&gt;sv_block_size
)paren
r_continue
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|bad_dir
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bad directory on device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sysv_rmdir
r_static
r_int
id|sysv_rmdir
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
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
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
id|bh
op_logical_or
id|de-&gt;inode
op_ne
id|inode-&gt;i_ino
)paren
r_goto
id|end_rmdir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty_dir
c_func
(paren
id|inode
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_goto
id|end_rmdir
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_ne
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;empty directory has nlink!=2 (%d)&bslash;n&quot;
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|de-&gt;inode
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
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
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
id|end_rmdir
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sysv_unlink
r_static
r_int
id|sysv_unlink
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
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|de-&gt;inode
op_ne
id|inode-&gt;i_ino
)paren
r_goto
id|end_unlink
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Deleting nonexistent file (%s:%lu), %d&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|inode-&gt;i_dev
)paren
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
id|de-&gt;inode
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
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|end_unlink
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sysv_symlink
r_static
r_int
id|sysv_symlink
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
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|l
suffix:semicolon
id|err
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
id|l
op_assign
id|strlen
c_func
(paren
id|symname
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|dir-&gt;i_sb-&gt;sv_block_size_1
)paren
r_goto
id|out
suffix:semicolon
id|err
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
id|sysv_new_inode
c_func
(paren
id|dir
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0777
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|sysv_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysv_aops
suffix:semicolon
id|err
op_assign
id|block_symlink
c_func
(paren
id|inode
comma
id|symname
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_no_entry
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|sysv_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_no_entry
suffix:semicolon
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
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
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_no_entry
suffix:colon
id|inode-&gt;i_nlink
op_decrement
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
DECL|function|sysv_link
r_static
r_int
id|sysv_link
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
r_int
id|error
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
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
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldinode-&gt;i_nlink
op_ge
id|oldinode-&gt;i_sb-&gt;sv_link_max
)paren
(brace
r_return
op_minus
id|EMLINK
suffix:semicolon
)brace
id|bh
op_assign
id|sysv_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|brelse
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
id|error
op_assign
id|sysv_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|bh
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|de-&gt;inode
op_assign
id|oldinode-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|oldinode-&gt;i_nlink
op_increment
suffix:semicolon
id|oldinode-&gt;i_ctime
op_assign
id|CURRENT_TIME
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PARENT_INO
mdefine_line|#define PARENT_INO(buffer) &bslash;&n;(((struct sysv_dir_entry *) ((buffer) + 1*SYSV_DIRSIZE))-&gt;inode)
multiline_comment|/*&n; * Anybody can rename anything with this: the permission checks are left to the&n; * higher-level routines.&n; */
DECL|function|sysv_rename
r_static
r_int
id|sysv_rename
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
comma
op_star
id|new_inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|old_bh
comma
op_star
id|new_bh
comma
op_star
id|dir_bh
suffix:semicolon
r_struct
id|sysv_dir_entry
op_star
id|old_de
comma
op_star
id|new_de
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|old_inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
id|new_bh
op_assign
id|dir_bh
op_assign
l_int|NULL
suffix:semicolon
id|old_bh
op_assign
id|sysv_find_entry
c_func
(paren
id|old_dir
comma
id|old_dentry-&gt;d_name.name
comma
id|old_dentry-&gt;d_name.len
comma
op_amp
id|old_de
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
id|old_bh
op_logical_or
id|old_de-&gt;inode
op_ne
id|old_inode-&gt;i_ino
)paren
r_goto
id|end_rename
suffix:semicolon
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
id|new_bh
op_assign
id|sysv_find_entry
c_func
(paren
id|new_dir
comma
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
comma
op_amp
id|new_de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|new_inode
)paren
(brace
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
id|new_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|new_inode
)paren
(brace
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
id|new_inode
)paren
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|dir_bh
op_assign
id|sysv_file_bread
c_func
(paren
id|old_inode
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_bh
)paren
r_goto
id|end_rename
suffix:semicolon
r_if
c_cond
(paren
id|PARENT_INO
c_func
(paren
id|dir_bh-&gt;b_data
)paren
op_ne
id|old_dir-&gt;i_ino
)paren
r_goto
id|end_rename
suffix:semicolon
id|retval
op_assign
op_minus
id|EMLINK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_inode
op_logical_and
id|new_dir
op_ne
id|old_dir
op_logical_and
id|new_dir-&gt;i_nlink
op_ge
id|new_dir-&gt;i_sb-&gt;sv_link_max
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_bh
)paren
(brace
id|retval
op_assign
id|sysv_add_entry
c_func
(paren
id|new_dir
comma
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
comma
op_amp
id|new_bh
comma
op_amp
id|new_de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
id|new_de-&gt;inode
op_assign
id|old_inode-&gt;i_ino
suffix:semicolon
id|old_de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|old_dir-&gt;i_ctime
op_assign
id|old_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|new_dir-&gt;i_ctime
op_assign
id|new_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|old_bh
comma
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|new_bh
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir_bh
)paren
(brace
id|PARENT_INO
c_func
(paren
id|dir_bh-&gt;b_data
)paren
op_assign
id|new_dir-&gt;i_ino
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|dir_bh
comma
l_int|1
)paren
suffix:semicolon
id|old_dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|new_dir-&gt;i_nlink
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_dir
)paren
suffix:semicolon
)brace
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
id|end_rename
suffix:colon
id|brelse
c_func
(paren
id|dir_bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|sysv_dir_inode_operations
r_struct
id|inode_operations
id|sysv_dir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|sysv_create
comma
id|lookup
suffix:colon
id|sysv_lookup
comma
id|link
suffix:colon
id|sysv_link
comma
id|unlink
suffix:colon
id|sysv_unlink
comma
id|symlink
suffix:colon
id|sysv_symlink
comma
id|mkdir
suffix:colon
id|sysv_mkdir
comma
id|rmdir
suffix:colon
id|sysv_rmdir
comma
id|mknod
suffix:colon
id|sysv_mknod
comma
id|rename
suffix:colon
id|sysv_rename
comma
id|setattr
suffix:colon
id|sysv_notify_change
comma
)brace
suffix:semicolon
eof
