multiline_comment|/*&n; * proc/fs/generic.c --- generic routines for the proc-fs&n; *&n; * This file contains generic proc-fs routines for handling&n; * directories and files.&n; * &n; * Copyright (C) 1991, 1992 Linus Torvalds.&n; * Copyright (C) 1997 Theodore Ts&squot;o&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
r_static
r_int
id|proc_file_read
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
r_int
id|nbytes
)paren
suffix:semicolon
r_static
r_int
id|proc_file_write
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
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_static
r_int
r_int
id|proc_file_lseek
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
r_int
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
DECL|function|proc_match
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
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|de-&gt;name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|proc_file_operations
r_static
r_struct
id|file_operations
id|proc_file_operations
op_assign
(brace
id|proc_file_lseek
comma
multiline_comment|/* lseek   */
id|proc_file_read
comma
multiline_comment|/* read&t;   */
id|proc_file_write
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
multiline_comment|/*&n; * proc files can do almost nothing..&n; */
DECL|variable|proc_file_inode_operations
r_struct
id|inode_operations
id|proc_file_inode_operations
op_assign
(brace
op_amp
id|proc_file_operations
comma
multiline_comment|/* default proc file-ops */
l_int|NULL
comma
multiline_comment|/* create&t;   */
l_int|NULL
comma
multiline_comment|/* lookup&t;   */
l_int|NULL
comma
multiline_comment|/* link&t;   */
l_int|NULL
comma
multiline_comment|/* unlink&t;   */
l_int|NULL
comma
multiline_comment|/* symlink&t;   */
l_int|NULL
comma
multiline_comment|/* mkdir&t;   */
l_int|NULL
comma
multiline_comment|/* rmdir&t;   */
l_int|NULL
comma
multiline_comment|/* mknod&t;   */
l_int|NULL
comma
multiline_comment|/* rename&t;   */
l_int|NULL
comma
multiline_comment|/* readlink&t;   */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage&t;   */
l_int|NULL
comma
multiline_comment|/* writepage   */
l_int|NULL
comma
multiline_comment|/* bmap&t;   */
l_int|NULL
comma
multiline_comment|/* truncate&t;   */
l_int|NULL
multiline_comment|/* permission  */
)brace
suffix:semicolon
multiline_comment|/*&n; * compatibility to replace fs/proc/net.c&n; */
DECL|variable|proc_net_inode_operations
r_struct
id|inode_operations
id|proc_net_inode_operations
op_assign
(brace
op_amp
id|proc_file_operations
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
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
multiline_comment|/* 4K page size but our output routines use some slack for overruns */
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE&t;(3*1024)
DECL|function|proc_file_read
r_static
r_int
id|proc_file_read
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
r_int
id|nbytes
)paren
(brace
r_char
op_star
id|page
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|eof
op_assign
l_int|0
suffix:semicolon
r_int
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
r_if
c_cond
(paren
id|nbytes
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
id|file-&gt;f_pos
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
id|file-&gt;f_pos
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
id|file-&gt;f_pos
suffix:semicolon
id|n
op_sub_assign
id|file-&gt;f_pos
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
id|n
op_sub_assign
id|copy_to_user
c_func
(paren
id|buf
comma
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
id|file-&gt;f_pos
op_add_assign
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
r_static
r_int
DECL|function|proc_file_write
id|proc_file_write
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
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
id|dp-&gt;write_proc
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|dp
op_member_access_from_pointer
id|write_proc
c_func
(paren
id|file
comma
id|buffer
comma
id|count
comma
id|dp-&gt;data
)paren
suffix:semicolon
)brace
DECL|function|proc_file_lseek
r_static
r_int
r_int
id|proc_file_lseek
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
r_int
id|offset
comma
r_int
id|orig
)paren
(brace
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This function parses a name such as &quot;tty/driver/serial&quot;, and&n; * returns the struct proc_dir_entry for &quot;/proc/tty/driver&quot;, and&n; * returns &quot;serial&quot; in residual.&n; */
DECL|function|xlate_proc_name
r_static
r_int
id|xlate_proc_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
op_star
id|ret
comma
r_const
r_char
op_star
op_star
id|residual
)paren
(brace
r_const
r_char
op_star
id|cp
op_assign
id|name
comma
op_star
id|next
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|len
suffix:semicolon
id|de
op_assign
op_amp
id|proc_root
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|next
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
r_break
suffix:semicolon
id|len
op_assign
id|next
op_minus
id|cp
suffix:semicolon
r_for
c_loop
(paren
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|de
suffix:semicolon
id|de
op_assign
id|de-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|proc_match
c_func
(paren
id|len
comma
id|cp
comma
id|de
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|cp
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
)brace
op_star
id|residual
op_assign
id|cp
suffix:semicolon
op_star
id|ret
op_assign
id|de
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_proc_entry
r_struct
id|proc_dir_entry
op_star
id|create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_const
r_char
op_star
id|fn
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|fn
op_assign
id|name
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|xlate_proc_name
c_func
(paren
id|name
comma
op_amp
id|parent
comma
op_amp
id|fn
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
id|ent
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|ent
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|S_IFDIR
)paren
id|mode
op_or_assign
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mode
op_eq
l_int|0
)paren
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
suffix:semicolon
id|ent-&gt;name
op_assign
id|fn
suffix:semicolon
id|ent-&gt;namelen
op_assign
id|strlen
c_func
(paren
id|fn
)paren
suffix:semicolon
id|ent-&gt;mode
op_assign
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|ent-&gt;nlink
op_assign
l_int|2
suffix:semicolon
r_else
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|proc_register
c_func
(paren
id|parent
comma
id|ent
)paren
suffix:semicolon
r_return
id|ent
suffix:semicolon
)brace
DECL|function|remove_proc_entry
r_void
id|remove_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_const
r_char
op_star
id|fn
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|fn
op_assign
id|name
suffix:semicolon
r_else
r_if
c_cond
(paren
id|xlate_proc_name
c_func
(paren
id|name
comma
op_amp
id|parent
comma
op_amp
id|fn
)paren
)paren
r_return
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|fn
)paren
suffix:semicolon
r_for
c_loop
(paren
id|de
op_assign
id|parent-&gt;subdir
suffix:semicolon
id|de
suffix:semicolon
id|de
op_assign
id|de-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|proc_match
c_func
(paren
id|len
comma
id|fn
comma
id|de
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de
)paren
id|proc_unregister
c_func
(paren
id|parent
comma
id|de-&gt;low_ino
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
eof
