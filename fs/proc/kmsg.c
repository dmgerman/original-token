multiline_comment|/*&n; *  linux/fs/proc/kmsg.c&n; *&n; *  Copyright (C) 1992  by Linus Torvalds&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_int
r_int
id|log_size
suffix:semicolon
r_extern
r_struct
id|wait_queue
op_star
id|log_wait
suffix:semicolon
r_extern
r_int
id|sys_syslog
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|bug
comma
r_int
id|count
)paren
suffix:semicolon
DECL|function|kmsg_open
r_static
r_int
id|kmsg_open
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
id|file
)paren
(brace
r_return
id|sys_syslog
c_func
(paren
l_int|1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|kmsg_release
r_static
r_void
id|kmsg_release
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
id|file
)paren
(brace
(paren
r_void
)paren
id|sys_syslog
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|kmsg_read
r_static
r_int
id|kmsg_read
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
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_return
id|sys_syslog
c_func
(paren
l_int|2
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|kmsg_select
r_static
r_int
id|kmsg_select
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
id|file
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
(brace
r_if
c_cond
(paren
id|sel_type
op_ne
id|SEL_IN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|log_size
)paren
r_return
l_int|1
suffix:semicolon
id|select_wait
c_func
(paren
op_amp
id|log_wait
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_kmsg_operations
r_static
r_struct
id|file_operations
id|proc_kmsg_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* kmsg_lseek */
id|kmsg_read
comma
l_int|NULL
comma
multiline_comment|/* kmsg_write */
l_int|NULL
comma
multiline_comment|/* kmsg_readdir */
id|kmsg_select
comma
multiline_comment|/* kmsg_select */
l_int|NULL
comma
multiline_comment|/* kmsg_ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|kmsg_open
comma
id|kmsg_release
)brace
suffix:semicolon
DECL|variable|proc_kmsg_inode_operations
r_struct
id|inode_operations
id|proc_kmsg_inode_operations
op_assign
(brace
op_amp
id|proc_kmsg_operations
comma
multiline_comment|/* default base directory file-ops */
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
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
