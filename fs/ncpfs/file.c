multiline_comment|/*&n; *  file.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
macro_line|#include &lt;linux/malloc.h&gt;
DECL|function|min
r_static
r_inline
r_int
id|min
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_return
id|a
OL
id|b
ques
c_cond
id|a
suffix:colon
id|b
suffix:semicolon
)brace
r_static
r_int
DECL|function|ncp_fsync
id|ncp_fsync
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
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|ncp_make_open
id|ncp_make_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_int
id|right
)paren
(brace
r_struct
id|nw_file_info
op_star
id|finfo
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ncp_make_open: got NULL inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|finfo
op_assign
id|NCP_FINFO
c_func
(paren
id|i
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_make_open: dirent-&gt;opened = %d&bslash;n&quot;
comma
id|finfo-&gt;opened
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finfo-&gt;opened
op_eq
l_int|0
)paren
(brace
multiline_comment|/* tries max. rights */
r_if
c_cond
(paren
id|ncp_open_create_file_or_subdir
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|i
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|OC_MODE_OPEN
comma
l_int|0
comma
id|AR_READ
op_or
id|AR_WRITE
comma
id|finfo
)paren
op_eq
l_int|0
)paren
(brace
id|finfo-&gt;access
op_assign
id|O_RDWR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ncp_open_create_file_or_subdir
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|i
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|OC_MODE_OPEN
comma
l_int|0
comma
id|AR_READ
comma
id|finfo
)paren
op_eq
l_int|0
)paren
(brace
id|finfo-&gt;access
op_assign
id|O_RDONLY
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
(paren
id|right
op_eq
id|O_RDONLY
)paren
op_logical_and
(paren
(paren
id|finfo-&gt;access
op_eq
id|O_RDONLY
)paren
op_logical_or
(paren
id|finfo-&gt;access
op_eq
id|O_RDWR
)paren
)paren
)paren
op_logical_or
(paren
(paren
id|right
op_eq
id|O_WRONLY
)paren
op_logical_and
(paren
(paren
id|finfo-&gt;access
op_eq
id|O_WRONLY
)paren
op_logical_or
(paren
id|finfo-&gt;access
op_eq
id|O_RDWR
)paren
)paren
)paren
op_logical_or
(paren
(paren
id|right
op_eq
id|O_RDWR
)paren
op_logical_and
(paren
id|finfo-&gt;access
op_eq
id|O_RDWR
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_static
r_int
DECL|function|ncp_file_read
id|ncp_file_read
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
r_int
id|bufsize
comma
id|already_read
suffix:semicolon
id|off_t
id|pos
suffix:semicolon
r_int
id|errno
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: enter %s&bslash;n&quot;
comma
id|NCP_ISTRUCT
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entryName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: inode = NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
)paren
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: read from non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pos
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|count
OG
id|inode-&gt;i_size
)paren
(brace
id|count
op_assign
id|inode-&gt;i_size
op_minus
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|errno
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|errno
suffix:semicolon
)brace
id|bufsize
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|buffer_size
suffix:semicolon
id|already_read
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First read in as much as possible for each bufsize. */
r_while
c_loop
(paren
id|already_read
OL
id|count
)paren
(brace
r_int
id|read_this_time
suffix:semicolon
r_int
id|to_read
op_assign
id|min
c_func
(paren
id|bufsize
op_minus
(paren
id|pos
op_mod
id|bufsize
)paren
comma
id|count
op_minus
id|already_read
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncp_read
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|pos
comma
id|to_read
comma
id|buf
comma
op_amp
id|read_this_time
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* This is not exact, i know.. */
)brace
id|pos
op_add_assign
id|read_this_time
suffix:semicolon
id|buf
op_add_assign
id|read_this_time
suffix:semicolon
id|already_read
op_add_assign
id|read_this_time
suffix:semicolon
r_if
c_cond
(paren
id|read_this_time
OL
id|to_read
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_read: exit %s&bslash;n&quot;
comma
id|NCP_ISTRUCT
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entryName
)paren
suffix:semicolon
r_return
id|already_read
suffix:semicolon
)brace
r_static
r_int
DECL|function|ncp_file_write
id|ncp_file_write
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
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|bufsize
comma
id|already_written
suffix:semicolon
id|off_t
id|pos
suffix:semicolon
r_int
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: inode = NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
)paren
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: write to non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: enter %s&bslash;n&quot;
comma
id|NCP_ISTRUCT
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entryName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|errno
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDWR
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|errno
suffix:semicolon
)brace
id|pos
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_APPEND
)paren
(brace
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
id|bufsize
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|buffer_size
suffix:semicolon
id|already_written
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|already_written
OL
id|count
)paren
(brace
r_int
id|written_this_time
suffix:semicolon
r_int
id|to_write
op_assign
id|min
c_func
(paren
id|bufsize
op_minus
(paren
id|pos
op_mod
id|bufsize
)paren
comma
id|count
op_minus
id|already_written
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncp_write
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|pos
comma
id|to_write
comma
id|buf
comma
op_amp
id|written_this_time
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|pos
op_add_assign
id|written_this_time
suffix:semicolon
id|buf
op_add_assign
id|written_this_time
suffix:semicolon
id|already_written
op_add_assign
id|written_this_time
suffix:semicolon
r_if
c_cond
(paren
id|written_this_time
OL
id|to_write
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|inode-&gt;i_size
)paren
(brace
id|inode-&gt;i_size
op_assign
id|pos
suffix:semicolon
id|ncp_invalid_dir_cache
c_func
(paren
id|NCP_INOP
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dir-&gt;inode
)paren
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_file_write: exit %s&bslash;n&quot;
comma
id|NCP_ISTRUCT
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entryName
)paren
suffix:semicolon
r_return
id|already_written
suffix:semicolon
)brace
DECL|variable|ncp_file_operations
r_static
r_struct
id|file_operations
id|ncp_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|ncp_file_read
comma
multiline_comment|/* read */
id|ncp_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select - default */
id|ncp_ioctl
comma
multiline_comment|/* ioctl */
id|ncp_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
id|ncp_fsync
comma
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|ncp_file_inode_operations
r_struct
id|inode_operations
id|ncp_file_inode_operations
op_assign
(brace
op_amp
id|ncp_file_operations
comma
multiline_comment|/* default file operations */
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
multiline_comment|/* truncate */
)brace
suffix:semicolon
eof