multiline_comment|/*&n; *  mmap.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
multiline_comment|/*&n; * Fill in the supplied page for mmap&n; */
DECL|function|ncp_file_mmap_nopage
r_static
r_int
r_int
id|ncp_file_mmap_nopage
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
id|no_share
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|area-&gt;vm_dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
r_int
id|clear
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|bufsize
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_int
r_int
id|fs
suffix:semicolon
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|page
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|pos
op_assign
id|address
op_minus
id|area-&gt;vm_start
op_plus
id|area-&gt;vm_offset
suffix:semicolon
id|clear
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|address
op_plus
id|PAGE_SIZE
OG
id|area-&gt;vm_end
)paren
(brace
id|clear
op_assign
id|address
op_plus
id|PAGE_SIZE
op_minus
id|area-&gt;vm_end
suffix:semicolon
)brace
multiline_comment|/* what we can read in one go */
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
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDONLY
)paren
OL
l_int|0
)paren
(brace
id|clear
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_int
id|already_read
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
id|PAGE_SIZE
op_minus
id|clear
suffix:semicolon
r_int
id|to_read
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|pos
op_mod
id|bufsize
)paren
op_ne
l_int|0
)paren
(brace
id|to_read
op_assign
id|bufsize
op_minus
(paren
id|pos
op_mod
id|bufsize
)paren
suffix:semicolon
)brace
r_else
(brace
id|to_read
op_assign
id|bufsize
suffix:semicolon
)brace
id|to_read
op_assign
id|min
c_func
(paren
id|to_read
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
(paren
r_char
op_star
)paren
(paren
id|page
op_plus
id|already_read
)paren
comma
op_amp
id|read_this_time
)paren
op_ne
l_int|0
)paren
(brace
id|read_this_time
op_assign
l_int|0
suffix:semicolon
)brace
id|pos
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
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
id|tmp
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|clear
op_decrement
)paren
(brace
op_star
(paren
r_char
op_star
)paren
op_decrement
id|tmp
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
)brace
DECL|variable|ncp_file_mmap
r_struct
id|vm_operations_struct
id|ncp_file_mmap
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* close */
l_int|NULL
comma
multiline_comment|/* unmap */
l_int|NULL
comma
multiline_comment|/* protect */
l_int|NULL
comma
multiline_comment|/* sync */
l_int|NULL
comma
multiline_comment|/* advise */
id|ncp_file_mmap_nopage
comma
multiline_comment|/* nopage */
l_int|NULL
comma
multiline_comment|/* wppage */
l_int|NULL
comma
multiline_comment|/* swapout */
l_int|NULL
comma
multiline_comment|/* swapin */
)brace
suffix:semicolon
multiline_comment|/* This is used for a general mmap of a ncp file */
DECL|function|ncp_mmap
r_int
id|ncp_mmap
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_mmap: called&bslash;n&quot;
)paren
suffix:semicolon
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
multiline_comment|/* only PAGE_COW or read-only supported now */
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EACCES
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
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|vma-&gt;vm_dentry
op_assign
id|dget
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|ncp_file_mmap
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
