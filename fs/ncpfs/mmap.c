multiline_comment|/*&n; *  mmap.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Modified 1997 Peter Waltenberg, Bill Hawes, David Woodhouse for 2.1 dcache&n; *&n; */
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
r_struct
id|page
op_star
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
id|write_access
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|area-&gt;vm_file
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_char
op_star
id|pg_addr
suffix:semicolon
r_int
r_int
id|already_read
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_int
id|bufsize
suffix:semicolon
r_int
id|pos
suffix:semicolon
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_HIGHMEM
)paren
suffix:semicolon
multiline_comment|/* ncpfs has nothing against GFP_HIGHMEM&n;&t;           as long as recvmsg and memset works on it */
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|page
suffix:semicolon
id|pg_addr
op_assign
id|kmap
c_func
(paren
id|page
)paren
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
(paren
id|area-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|count
op_assign
id|PAGE_SIZE
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
id|count
op_assign
id|area-&gt;vm_end
op_minus
id|address
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
id|already_read
op_assign
l_int|0
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
op_ge
l_int|0
)paren
(brace
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
suffix:semicolon
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
id|ncp_read_kernel
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
id|pg_addr
op_plus
id|already_read
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
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|already_read
OL
id|PAGE_SIZE
)paren
id|memset
c_func
(paren
id|pg_addr
op_plus
id|already_read
comma
l_int|0
comma
id|PAGE_SIZE
op_minus
id|already_read
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|variable|ncp_file_mmap
r_static
r_struct
id|vm_operations_struct
id|ncp_file_mmap
op_assign
(brace
id|nopage
suffix:colon
id|ncp_file_mmap_nopage
comma
)brace
suffix:semicolon
multiline_comment|/* This is used for a general mmap of a ncp file */
DECL|function|ncp_mmap
r_int
id|ncp_mmap
c_func
(paren
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
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
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
multiline_comment|/* we do not support files bigger than 4GB... We eventually &n;&t;   supports just 4GB... */
r_if
c_cond
(paren
(paren
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_plus
id|vma-&gt;vm_pgoff
OG
(paren
l_int|1U
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
)paren
r_return
op_minus
id|EFBIG
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
