multiline_comment|/*&n; *  linux/fs/affs/symlink.c&n; *&n; *  1995  Hans-Joachim Widmaier - Modified for affs.&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  affs symlink handling code&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|function|affs_symlink_readpage
r_static
r_int
id|affs_symlink_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
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
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_char
op_star
id|link
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_struct
id|slink_front
op_star
id|lf
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_char
id|c
suffix:semicolon
r_char
id|lc
suffix:semicolon
r_char
op_star
id|pf
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: follow_link(ino=%lu)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|fail
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|lf
op_assign
(paren
r_struct
id|slink_front
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|lc
op_assign
l_int|0
suffix:semicolon
id|pf
op_assign
id|inode-&gt;i_sb-&gt;u.affs_sb.s_prefix
ques
c_cond
id|inode-&gt;i_sb-&gt;u.affs_sb.s_prefix
suffix:colon
l_string|&quot;/&quot;
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|lf-&gt;symname
comma
l_char|&squot;:&squot;
)paren
)paren
(brace
multiline_comment|/* Handle assign or volume name */
r_while
c_loop
(paren
id|i
OL
l_int|1023
op_logical_and
(paren
id|c
op_assign
id|pf
(braket
id|i
)braket
)paren
)paren
id|link
(braket
id|i
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
l_int|1023
op_logical_and
id|lf-&gt;symname
(braket
id|j
)braket
op_ne
l_char|&squot;:&squot;
)paren
id|link
(braket
id|i
op_increment
)braket
op_assign
id|lf-&gt;symname
(braket
id|j
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|1023
)paren
id|link
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|j
op_increment
suffix:semicolon
id|lc
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
l_int|1023
op_logical_and
(paren
id|c
op_assign
id|lf-&gt;symname
(braket
id|j
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
op_logical_and
id|lc
op_eq
l_char|&squot;/&squot;
op_logical_and
id|i
OL
l_int|1020
)paren
(brace
multiline_comment|/* parent dir */
id|link
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
id|link
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
id|link
(braket
id|i
op_increment
)braket
op_assign
id|c
suffix:semicolon
id|lc
op_assign
id|c
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
id|link
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|affs_symlink_aops
r_struct
id|address_space_operations
id|affs_symlink_aops
op_assign
(brace
id|readpage
suffix:colon
id|affs_symlink_readpage
comma
)brace
suffix:semicolon
DECL|variable|affs_symlink_inode_operations
r_struct
id|inode_operations
id|affs_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|page_readlink
comma
id|follow_link
suffix:colon
id|page_follow_link
comma
id|setattr
suffix:colon
id|affs_notify_change
comma
)brace
suffix:semicolon
eof
