multiline_comment|/*&n; *&t;fs/nfs/mmap.c&t;by Jon Tombs 15 Aug 1993&n; *&n; * This code is from&n; *&t;linux/mm/mmap.c which was written by obz, Linus and Eric&n; * and&n; *&t;linux/mm/memory.c  by Linus Torvalds and others&n; *&n; *&t;Copyright (C) 1993&n; *&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Fill in the supplied page for mmap&n; */
DECL|function|nfs_file_mmap_nopage
r_static
r_int
r_int
id|nfs_file_mmap_nopage
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
r_int
id|page
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
id|area-&gt;vm_inode
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
id|n
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
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
id|n
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
suffix:semicolon
multiline_comment|/* what we can read in one go */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|PAGE_SIZE
op_minus
id|clear
)paren
suffix:semicolon
id|i
op_add_assign
id|n
)paren
(brace
r_int
id|hunk
comma
id|result
suffix:semicolon
id|hunk
op_assign
id|PAGE_SIZE
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|hunk
OG
id|n
)paren
id|hunk
op_assign
id|n
suffix:semicolon
id|result
op_assign
id|nfs_proc_read
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
id|pos
comma
id|hunk
comma
(paren
r_char
op_star
)paren
(paren
id|page
op_plus
id|i
)paren
comma
op_amp
id|fattr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_break
suffix:semicolon
id|pos
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|n
)paren
(brace
id|i
op_add_assign
id|result
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#ifdef doweneedthishere
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
macro_line|#endif
id|tmp
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|clear
OG
l_int|0
)paren
(brace
id|memset
(paren
(paren
r_char
op_star
)paren
(paren
id|tmp
op_minus
id|clear
)paren
comma
l_int|0
comma
id|clear
)paren
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
)brace
DECL|variable|nfs_file_mmap
r_struct
id|vm_operations_struct
id|nfs_file_mmap
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
id|nfs_file_mmap_nopage
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
multiline_comment|/* This is used for a general mmap of a nfs file */
DECL|function|nfs_mmap
r_int
id|nfs_mmap
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
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
multiline_comment|/* only PAGE_COW or read-only supported now */
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
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|vma-&gt;vm_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|nfs_file_mmap
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
