multiline_comment|/*&n; *  linux/fs/proc/fd.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  proc fd directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_static
r_int
id|proc_readfd
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|dirent
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|proc_lookupfd
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
DECL|variable|proc_fd_operations
r_static
r_struct
id|file_operations
id|proc_fd_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|proc_readfd
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_fd_inode_operations
r_struct
id|inode_operations
id|proc_fd_inode_operations
op_assign
(brace
op_amp
id|proc_fd_operations
comma
multiline_comment|/* default base directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookupfd
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
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
DECL|function|proc_lookupfd
r_static
r_int
id|proc_lookupfd
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
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_int
r_int
id|ino
comma
id|pid
comma
id|fd
comma
id|c
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
comma
id|dev
suffix:semicolon
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
id|ino
op_assign
id|dir-&gt;i_ino
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
id|ino
op_sub_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
op_logical_or
id|ino
OG
l_int|1
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|name
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|len
op_eq
l_int|1
op_logical_or
(paren
id|get_fs_byte
c_func
(paren
id|name
op_plus
l_int|1
)paren
op_eq
l_char|&squot;.&squot;
op_logical_and
id|len
op_eq
l_int|2
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
OL
l_int|2
)paren
(brace
op_star
id|result
op_assign
id|dir
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
(paren
id|pid
op_lshift
l_int|16
)paren
op_plus
l_int|2
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dev
op_assign
id|dir-&gt;i_dev
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
id|fd
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
OG
l_int|0
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|name
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
l_int|9
)paren
(brace
id|fd
op_assign
l_int|0xfffff
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fd
op_mul_assign
l_int|10
suffix:semicolon
id|fd
op_add_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_amp
l_int|0xffff0000
)paren
(brace
id|fd
op_assign
l_int|0xfffff
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
op_logical_neg
id|pid
op_logical_or
id|i
op_ge
id|NR_TASKS
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
id|p-&gt;filp
(braket
id|fd
)braket
op_logical_or
op_logical_neg
id|p-&gt;filp
(braket
id|fd
)braket
op_member_access_from_pointer
id|f_inode
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|ino
op_assign
(paren
id|pid
op_lshift
l_int|16
)paren
op_plus
l_int|0x100
op_plus
id|fd
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|p-&gt;numlibraries
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|ino
op_assign
(paren
id|pid
op_lshift
l_int|16
)paren
op_plus
l_int|0x200
op_plus
id|fd
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dev
comma
id|ino
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_readfd
r_static
r_int
id|proc_readfd
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|fd
comma
id|pid
comma
id|ino
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
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
id|ino
op_sub_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|ino
OG
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|fd
op_assign
id|filp-&gt;f_pos
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|2
)paren
(brace
id|i
op_assign
id|j
op_assign
id|fd
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fd
)paren
id|fd
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_else
id|fd
op_assign
(paren
id|inode-&gt;i_ino
op_amp
l_int|0xffff0000
)paren
op_or
l_int|2
suffix:semicolon
id|put_fs_long
c_func
(paren
id|fd
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|put_fs_byte
c_func
(paren
l_char|&squot;.&squot;
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
r_return
id|j
suffix:semicolon
)brace
id|fd
op_sub_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;filp
(braket
id|fd
)braket
op_logical_or
op_logical_neg
id|p-&gt;filp
(braket
id|fd
)braket
op_member_access_from_pointer
id|f_inode
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fd
op_ge
id|p-&gt;numlibraries
)paren
r_break
suffix:semicolon
id|j
op_assign
l_int|10
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fd
op_ge
id|j
)paren
(brace
id|j
op_mul_assign
l_int|10
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|j
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
id|ino
op_assign
(paren
id|pid
op_lshift
l_int|16
)paren
op_plus
l_int|0x100
op_plus
id|fd
suffix:semicolon
r_else
id|ino
op_assign
(paren
id|pid
op_lshift
l_int|16
)paren
op_plus
l_int|0x200
op_plus
id|fd
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|put_fs_byte
c_func
(paren
l_char|&squot;0&squot;
op_plus
(paren
id|fd
op_mod
l_int|10
)paren
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|fd
op_div_assign
l_int|10
suffix:semicolon
)brace
r_return
id|j
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
