multiline_comment|/*&n; *  linux/fs/proc/sysvipc.c&n; *&n; *  Copyright (c) 1999 Dragos Acostachioaie&n; *&n; *  This code is derived from linux/fs/proc/generic.c,&n; *  which is Copyright (C) 1991, 1992 Linus Torvalds.&n; *&n; *  /proc/sysvipc directory handling functions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
multiline_comment|/* 4K page size but our output routines use some slack for overruns */
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE&t;(3*1024)
r_static
id|ssize_t
DECL|function|proc_sysvipc_read
id|proc_sysvipc_read
c_func
(paren
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
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|eof
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|n
comma
id|count
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
id|dp
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
(paren
id|nbytes
OG
l_int|0
)paren
op_logical_and
op_logical_neg
id|eof
)paren
(brace
id|count
op_assign
id|MIN
c_func
(paren
id|PROC_BLOCK_SIZE
comma
id|nbytes
)paren
suffix:semicolon
id|start
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;get_info
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Handle backwards compatibility with the old net&n;&t;&t;&t; * routines.&n;&t;&t;&t; * &n;&t;&t;&t; * XXX What gives with the file-&gt;f_flags &amp; O_ACCMODE&n;&t;&t;&t; * test?  Seems stupid to me....&n;&t;&t;&t; */
id|n
op_assign
id|dp
op_member_access_from_pointer
id|get_info
c_func
(paren
id|page
comma
op_amp
id|start
comma
op_star
id|ppos
comma
id|count
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDWR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|count
)paren
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dp-&gt;read_proc
)paren
(brace
id|n
op_assign
id|dp
op_member_access_from_pointer
id|read_proc
c_func
(paren
id|page
comma
op_amp
id|start
comma
op_star
id|ppos
comma
id|count
comma
op_amp
id|eof
comma
id|dp-&gt;data
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * For proc files that are less than 4k&n;&t;&t;&t; */
id|start
op_assign
id|page
op_plus
op_star
id|ppos
suffix:semicolon
id|n
op_sub_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|count
)paren
id|n
op_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* End of file */
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* This is a hack to allow mangling of file pos independent&n; &t;&t; * of actual bytes read.  Simply place the data at page,&n; &t;&t; * return the bytes, and set `start&squot; to the desired offset&n; &t;&t; * as an unsigned int. - Paul.Russell@rustcorp.com.au&n;&t;&t; */
id|n
op_sub_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|start
OL
id|page
ques
c_cond
id|page
suffix:colon
id|start
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|start
OL
id|page
ques
c_cond
(paren
r_int
)paren
id|start
suffix:colon
id|n
suffix:semicolon
multiline_comment|/* Move down the file */
id|nbytes
op_sub_assign
id|n
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|retval
op_add_assign
id|n
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|proc_sysvipc_operations
r_static
r_struct
id|file_operations
id|proc_sysvipc_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek   */
id|proc_sysvipc_read
comma
multiline_comment|/* read&t;   */
l_int|NULL
comma
multiline_comment|/* write   */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll    */
l_int|NULL
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_sysvipc_inode_operations
r_struct
id|inode_operations
id|proc_sysvipc_inode_operations
op_assign
(brace
op_amp
id|proc_sysvipc_operations
comma
multiline_comment|/* default net file-ops */
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
multiline_comment|/* get_block */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
