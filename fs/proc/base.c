multiline_comment|/*&n; *  linux/fs/proc/base.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  proc base directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_static
r_int
id|proc_readbase
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
id|proc_lookupbase
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
DECL|variable|proc_base_operations
r_static
r_struct
id|file_operations
id|proc_base_operations
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
id|proc_readbase
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
DECL|variable|proc_base_inode_operations
r_struct
id|inode_operations
id|proc_base_inode_operations
op_assign
(brace
op_amp
id|proc_base_operations
comma
multiline_comment|/* default base directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookupbase
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
DECL|struct|proc_dir_entry
r_struct
id|proc_dir_entry
(brace
DECL|member|low_ino
r_int
r_int
id|low_ino
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|base_dir
r_static
r_struct
id|proc_dir_entry
id|base_dir
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
l_int|2
comma
l_string|&quot;..&quot;
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_string|&quot;.&quot;
)brace
comma
(brace
l_int|3
comma
l_int|3
comma
l_string|&quot;mem&quot;
)brace
comma
(brace
l_int|4
comma
l_int|3
comma
l_string|&quot;cwd&quot;
)brace
comma
(brace
l_int|5
comma
l_int|4
comma
l_string|&quot;root&quot;
)brace
comma
(brace
l_int|6
comma
l_int|3
comma
l_string|&quot;exe&quot;
)brace
comma
(brace
l_int|7
comma
l_int|2
comma
l_string|&quot;fd&quot;
)brace
comma
(brace
l_int|8
comma
l_int|3
comma
l_string|&quot;lib&quot;
)brace
)brace
suffix:semicolon
DECL|macro|NR_BASE_DIRENTRY
mdefine_line|#define NR_BASE_DIRENTRY ((sizeof (base_dir))/(sizeof (base_dir[0])))
DECL|function|proc_match
r_static
r_int
id|proc_match
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
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_register
r_int
id|same
id|__asm__
c_func
(paren
l_string|&quot;ax&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
op_logical_or
op_logical_neg
id|de-&gt;low_ino
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
r_if
c_cond
(paren
id|de-&gt;namelen
op_ne
id|len
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;fs ; repe ; cmpsb&bslash;n&bslash;t&quot;
l_string|&quot;setz %%al&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|same
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|name
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|de-&gt;name
)paren
comma
l_string|&quot;c&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|same
suffix:semicolon
)brace
DECL|function|proc_lookupbase
r_static
r_int
id|proc_lookupbase
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
id|pid
suffix:semicolon
r_int
id|i
comma
id|ino
suffix:semicolon
op_star
id|result
op_assign
l_int|NULL
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
id|i
op_assign
id|NR_BASE_DIRENTRY
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
op_logical_and
op_logical_neg
id|proc_match
c_func
(paren
id|len
comma
id|name
comma
id|base_dir
op_plus
id|i
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
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
id|base_dir
(braket
id|i
)braket
dot
id|low_ino
op_eq
l_int|1
)paren
id|ino
op_assign
l_int|1
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
id|base_dir
(braket
id|i
)braket
dot
id|low_ino
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
id|task
(braket
id|i
)braket
op_logical_and
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
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
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_dev
comma
id|ino
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
DECL|function|proc_readbase
r_static
r_int
id|proc_readbase
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
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
r_int
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
id|task
(braket
id|i
)braket
op_logical_and
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|filp-&gt;f_pos
)paren
OL
id|NR_BASE_DIRENTRY
)paren
(brace
id|de
op_assign
id|base_dir
op_plus
id|filp-&gt;f_pos
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_assign
id|de-&gt;namelen
suffix:semicolon
id|ino
op_assign
id|de-&gt;low_ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ne
l_int|1
)paren
id|ino
op_or_assign
(paren
id|pid
op_lshift
l_int|16
)paren
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
id|j
op_assign
id|i
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
id|de-&gt;name
(braket
id|i
)braket
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
r_return
l_int|0
suffix:semicolon
)brace
eof
