multiline_comment|/*&n; *  linux/fs/proc/base.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  proc base directory handling functions&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
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
id|proc_readdir
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
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_base_inode_operations
r_static
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
id|proc_lookup
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
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|function|proc_pid_fill_inode
r_static
r_void
id|proc_pid_fill_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|pid
op_assign
id|inode-&gt;i_ino
op_rshift
l_int|16
suffix:semicolon
r_int
id|ino
op_assign
id|inode-&gt;i_ino
op_amp
l_int|0xffff
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;dumpable
op_logical_or
id|ino
op_eq
id|PROC_PID_INO
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|p-&gt;euid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|p-&gt;gid
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * This is really a pseudo-entry, and only links&n; * backwards to the parent with no link from the&n; * root directory to this. This way we can have just&n; * one entry for every /proc/&lt;pid&gt;/ directory.&n; */
DECL|variable|proc_pid
r_struct
id|proc_dir_entry
id|proc_pid
op_assign
(brace
id|PROC_PID_INO
comma
l_int|5
comma
l_string|&quot;&lt;pid&gt;&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_base_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
l_int|NULL
comma
op_amp
id|proc_root
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|proc_base_init
r_void
id|proc_base_init
c_func
(paren
r_void
)paren
(brace
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_STATUS
comma
l_int|6
comma
l_string|&quot;status&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_MEM
comma
l_int|3
comma
l_string|&quot;mem&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_mem_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_CWD
comma
l_int|3
comma
l_string|&quot;cwd&quot;
comma
id|S_IFLNK
op_or
id|S_IRWXU
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_link_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_ROOT
comma
l_int|4
comma
l_string|&quot;root&quot;
comma
id|S_IFLNK
op_or
id|S_IRWXU
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_link_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_EXE
comma
l_int|3
comma
l_string|&quot;exe&quot;
comma
id|S_IFLNK
op_or
id|S_IRWXU
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_link_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_FD
comma
l_int|2
comma
l_string|&quot;fd&quot;
comma
id|S_IFDIR
op_or
id|S_IRUSR
op_or
id|S_IXUSR
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_fd_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_ENVIRON
comma
l_int|7
comma
l_string|&quot;environ&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_CMDLINE
comma
l_int|7
comma
l_string|&quot;cmdline&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_STAT
comma
l_int|4
comma
l_string|&quot;stat&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_STATM
comma
l_int|5
comma
l_string|&quot;statm&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_pid
comma
op_amp
(paren
r_struct
id|proc_dir_entry
)paren
(brace
id|PROC_PID_MAPS
comma
l_int|4
comma
l_string|&quot;maps&quot;
comma
id|S_IFIFO
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_arraylong_inode_operations
comma
l_int|NULL
comma
id|proc_pid_fill_inode
comma
)brace
)paren
suffix:semicolon
)brace
suffix:semicolon
eof
