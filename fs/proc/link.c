multiline_comment|/*&n; *  linux/fs/proc/link.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  /proc link-file handling code&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_static
r_int
id|proc_readlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|proc_follow_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * links can&squot;t do much...&n; */
DECL|variable|proc_link_inode_operations
r_struct
id|inode_operations
id|proc_link_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|proc_readlink
comma
multiline_comment|/* readlink */
id|proc_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
DECL|function|proc_follow_link
r_static
r_int
id|proc_follow_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|res_inode
)paren
(brace
r_int
r_int
id|pid
comma
id|ino
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
id|iput
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
id|ENOENT
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|pid
op_assign
id|ino
op_rshift
l_int|16
suffix:semicolon
id|ino
op_and_assign
l_int|0x0000ffff
suffix:semicolon
id|iput
c_func
(paren
id|inode
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
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|p
op_assign
id|task
(braket
id|i
)braket
)paren
op_logical_and
id|p-&gt;pid
op_eq
id|pid
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|NR_TASKS
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|ino
)paren
(brace
r_case
l_int|4
suffix:colon
id|inode
op_assign
id|p-&gt;pwd
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|inode
op_assign
id|p-&gt;root
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|inode
op_assign
id|p-&gt;executable
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|ino
op_rshift
l_int|8
)paren
(brace
r_case
l_int|1
suffix:colon
id|ino
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
id|NR_OPEN
op_logical_and
id|p-&gt;filp
(braket
id|ino
)braket
)paren
id|inode
op_assign
id|p-&gt;filp
(braket
id|ino
)braket
op_member_access_from_pointer
id|f_inode
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ino
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
id|p-&gt;numlibraries
)paren
id|inode
op_assign
id|p-&gt;libraries
(braket
id|ino
)braket
dot
id|library
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
op_star
id|res_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_readlink
r_static
r_int
id|proc_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_int
id|i
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OG
l_int|3
)paren
id|buflen
op_assign
l_int|3
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
op_increment
OL
id|buflen
)paren
id|put_fs_byte
c_func
(paren
l_char|&squot;-&squot;
comma
id|buffer
op_increment
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof