multiline_comment|/*&n; *&t;linux/fs/fat/mmap.c&n; *&n; *&t;Written by Jacques Gelinas (jacques@solucorp.qc.ca)&n; *&t;Inspired by fs/nfs/mmap.c (Jon Tombs 15 Aug 1993)&n; *&n; *&t;mmap handling for fat-based filesystems&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Fill in the supplied page for mmap&n; */
DECL|function|fat_file_mmap_nopage
r_static
r_int
r_int
id|fat_file_mmap_nopage
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
id|error_code
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
id|page
suffix:semicolon
r_int
r_int
id|clear
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_int
id|gap
suffix:semicolon
multiline_comment|/* distance from eof to pos */
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
id|gap
op_assign
id|inode-&gt;i_size
op_minus
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|gap
op_le
l_int|0
)paren
(brace
multiline_comment|/* mmaping beyond end of file */
id|clear
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_int
id|cur_read
suffix:semicolon
r_int
id|need_read
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|gap
OL
id|PAGE_SIZE
)paren
(brace
id|clear
op_assign
id|PAGE_SIZE
op_minus
id|gap
suffix:semicolon
)brace
id|filp.f_reada
op_assign
l_int|0
suffix:semicolon
id|filp.f_pos
op_assign
id|pos
suffix:semicolon
id|need_read
op_assign
id|PAGE_SIZE
op_minus
id|clear
suffix:semicolon
(brace
r_int
r_int
id|cur_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|cur_read
op_assign
id|fat_file_read
(paren
id|inode
comma
op_amp
id|filp
comma
(paren
r_char
op_star
)paren
id|page
comma
id|need_read
)paren
suffix:semicolon
id|set_fs
(paren
id|cur_fs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur_read
op_ne
id|need_read
)paren
(brace
id|printk
(paren
l_string|&quot;MSDOS: Error while reading an mmap file %d &lt;&gt; %d&bslash;n&quot;
comma
id|cur_read
comma
id|need_read
)paren
suffix:semicolon
)brace
)brace
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
id|page
op_plus
id|PAGE_SIZE
op_minus
id|clear
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
DECL|variable|fat_file_mmap
r_struct
id|vm_operations_struct
id|fat_file_mmap
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
id|fat_file_mmap_nopage
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
multiline_comment|/*&n; * This is used for a general mmap of an msdos file&n; * Returns 0 if ok, or a negative error code if not.&n; */
DECL|function|fat_mmap
r_int
id|fat_mmap
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
id|vma-&gt;vm_offset
op_amp
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
)paren
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
id|fat_file_mmap
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof