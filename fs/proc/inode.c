multiline_comment|/*&n; *  linux/fs/proc/inode.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|proc_put_inode
r_void
id|proc_put_inode
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
id|inode-&gt;i_nlink
)paren
r_return
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|proc_put_super
r_void
id|proc_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
DECL|variable|proc_sops
r_static
r_struct
id|super_operations
id|proc_sops
op_assign
(brace
id|proc_read_inode
comma
l_int|NULL
comma
id|proc_write_inode
comma
id|proc_put_inode
comma
id|proc_put_super
comma
l_int|NULL
comma
id|proc_statfs
)brace
suffix:semicolon
DECL|function|proc_read_super
r_struct
id|super_block
op_star
id|proc_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
)paren
(brace
id|lock_super
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|PROC_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|proc_sops
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_mounted
op_assign
id|iget
c_func
(paren
id|s
comma
id|PROC_ROOT_INO
)paren
)paren
)paren
(brace
id|s-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|proc_statfs
r_void
id|proc_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
id|put_fs_long
c_func
(paren
id|PROC_SUPER_MAGIC
comma
op_amp
id|buf-&gt;f_type
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|1024
comma
op_amp
id|buf-&gt;f_bsize
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_blocks
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_bfree
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_bavail
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_files
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
op_amp
id|buf-&gt;f_ffree
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t know what value to put in buf-&gt;f_fsid */
)brace
DECL|function|proc_bmap
r_int
id|proc_bmap
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_create_block
r_int
id|proc_create_block
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_read_inode
r_void
id|proc_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|ino
comma
id|pid
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
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
id|p
op_assign
id|task
(braket
l_int|0
)braket
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
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|i
op_ge
id|NR_TASKS
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|PROC_ROOT_INO
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
l_int|0555
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_root_inode_operations
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
r_return
suffix:semicolon
id|ino
op_and_assign
l_int|0x0000ffff
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|p-&gt;euid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|p-&gt;egid
suffix:semicolon
r_switch
c_cond
(paren
id|ino
)paren
(brace
r_case
l_int|2
suffix:colon
id|inode-&gt;i_nlink
op_assign
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
id|task
(braket
id|i
)braket
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
l_int|0500
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_base_inode_operations
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|3
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_mem_inode_operations
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFCHR
op_or
l_int|0600
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
l_int|0x0101
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|3
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0700
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|7
suffix:colon
r_case
l_int|8
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
l_int|0500
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_fd_inode_operations
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
r_return
suffix:semicolon
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
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
id|p-&gt;filp
(braket
id|ino
)braket
)paren
r_return
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|3
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0700
suffix:semicolon
r_return
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
op_ge
id|p-&gt;numlibraries
)paren
r_return
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|3
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0700
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|proc_write_inode
r_void
id|proc_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_dirt
op_assign
l_int|0
suffix:semicolon
)brace
eof
