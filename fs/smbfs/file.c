multiline_comment|/*&n; *  file.c&n; *&n; *  Copyright (C) 1995, 1996, 1997 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/smbno.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
DECL|macro|SMBFS_PARANOIA
mdefine_line|#define SMBFS_PARANOIA 1
multiline_comment|/* #define SMBFS_DEBUG_VERBOSE 1 */
multiline_comment|/* #define pr_debug printk */
r_static
r_inline
r_int
DECL|function|min
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
DECL|function|smb_fsync
id|smb_fsync
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_fsync: sync file %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page synchronously.&n; */
r_static
r_int
DECL|function|smb_readpage_sync
id|smb_readpage_sync
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_char
op_star
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|page-&gt;pg_offset
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
id|rsize
op_assign
id|smb_get_rsize
c_func
(paren
id|server_from_dentry
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_int
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_int
id|result
suffix:semicolon
multiline_comment|/* We can&squot;t replace this with ClearPageError. why? is it a problem? &n;&t;   fs/buffer.c:brw_page does the same. */
multiline_comment|/* clear_bit(PG_error, &amp;page-&gt;flags); */
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_readpage_sync: file %s/%s, count=%d@%ld, rsize=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|count
comma
id|offset
comma
id|rsize
)paren
suffix:semicolon
macro_line|#endif
id|result
op_assign
id|smb_open
c_func
(paren
id|dentry
comma
id|SMB_O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_readpage_sync: %s/%s open failed, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|io_error
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|rsize
)paren
id|rsize
op_assign
id|count
suffix:semicolon
id|result
op_assign
id|smb_proc_read
c_func
(paren
id|dentry
comma
id|offset
comma
id|rsize
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|io_error
suffix:semicolon
id|count
op_sub_assign
id|result
suffix:semicolon
id|offset
op_add_assign
id|result
suffix:semicolon
id|buffer
op_add_assign
id|result
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|rsize
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|io_error
suffix:colon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_int
DECL|function|smb_readpage
id|smb_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;SMB: smb_readpage %08lx&bslash;n&quot;
comma
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;smb_readpage: page not already locked!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|error
op_assign
id|smb_readpage_sync
c_func
(paren
id|dentry
comma
id|page
)paren
suffix:semicolon
id|put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a page synchronously.&n; * Offset is the data offset within the page.&n; */
r_static
r_int
DECL|function|smb_writepage_sync
id|smb_writepage_sync
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
(paren
id|u8
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
r_int
id|wsize
op_assign
id|smb_get_wsize
c_func
(paren
id|server_from_dentry
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_int
id|result
comma
id|written
op_assign
l_int|0
suffix:semicolon
id|offset
op_add_assign
id|page-&gt;pg_offset
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_writepage_sync: file %s/%s, count=%d@%ld, wsize=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|count
comma
id|offset
comma
id|wsize
)paren
suffix:semicolon
macro_line|#endif
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|wsize
)paren
id|wsize
op_assign
id|count
suffix:semicolon
id|result
op_assign
id|smb_proc_write
c_func
(paren
id|dentry
comma
id|offset
comma
id|wsize
comma
id|buffer
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
multiline_comment|/* N.B. what if result &lt; wsize?? */
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
id|result
OL
id|wsize
)paren
id|printk
c_func
(paren
l_string|&quot;smb_writepage_sync: short write, wsize=%d, result=%d&bslash;n&quot;
comma
id|wsize
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
id|buffer
op_add_assign
id|wsize
suffix:semicolon
id|offset
op_add_assign
id|wsize
suffix:semicolon
id|written
op_add_assign
id|wsize
suffix:semicolon
id|count
op_sub_assign
id|wsize
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Update the inode now rather than waiting for a refresh.&n;&t;&t; */
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|inode-&gt;i_size
)paren
id|inode-&gt;i_size
op_assign
id|offset
suffix:semicolon
id|inode-&gt;u.smbfs_i.cache_valid
op_or_assign
id|SMB_F_LOCALWRITE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
r_return
id|written
ques
c_cond
id|written
suffix:colon
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a page to the server. This will be used for NFS swapping only&n; * (for now), and we currently do this synchronously only.&n; *&n; * We are called with the page locked and the caller unlocks.&n; */
r_static
r_int
DECL|function|smb_writepage
id|smb_writepage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|result
suffix:semicolon
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;smb_writepage: page not already locked!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|result
op_assign
id|smb_writepage_sync
c_func
(paren
id|dentry
comma
id|page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_updatepage
id|smb_updatepage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;SMBFS: smb_updatepage(%s/%s %d@%ld)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|count
comma
(paren
id|page-&gt;pg_offset
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_return
id|smb_writepage_sync
c_func
(paren
id|dentry
comma
id|page
comma
id|offset
comma
id|count
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|smb_file_read
id|smb_file_read
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|ssize_t
id|status
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_read: file %s/%s, count=%lu@%lu&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
op_star
id|ppos
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_file_read: %s/%s validation failed, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_read: before read, size=%ld, pages=%ld, flags=%x, atime=%ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_size
comma
id|dentry-&gt;d_inode-&gt;i_nrpages
comma
id|dentry-&gt;d_inode-&gt;i_flags
comma
id|dentry-&gt;d_inode-&gt;i_atime
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|generic_file_read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_file_mmap
id|smb_file_mmap
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
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|status
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_mmap: file %s/%s, address %lu - %lu&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_file_mmap: %s/%s validation failed, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
id|status
op_assign
id|generic_file_mmap
c_func
(paren
id|file
comma
id|vma
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * This does the &quot;real&quot; work of the write. The generic routine has&n; * allocated the page, locked it, done all the page alignment stuff&n; * calculations etc. Now we should just copy the data from user&n; * space and write it back to the real medium..&n; *&n; * If the writer ends up delaying the write, the writer needs to&n; * increment the page use counts until he is done with the page.&n; */
DECL|function|smb_write_one_page
r_static
r_int
id|smb_write_one_page
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bytes
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_int
id|status
suffix:semicolon
id|bytes
op_sub_assign
id|copy_from_user
c_func
(paren
(paren
id|u8
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|offset
comma
id|buf
comma
id|bytes
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|bytes
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|smb_updatepage
c_func
(paren
id|file
comma
id|page
comma
id|offset
comma
id|bytes
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/* &n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|smb_file_write
id|smb_file_write
c_func
(paren
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
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|ssize_t
id|result
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_write: file %s/%s, count=%lu@%lu, pages=%ld&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
op_star
id|ppos
comma
id|dentry-&gt;d_inode-&gt;i_nrpages
)paren
suffix:semicolon
macro_line|#endif
id|result
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
id|printk
c_func
(paren
l_string|&quot;smb_file_write: %s/%s validation failed, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
id|result
op_assign
id|smb_open
c_func
(paren
id|dentry
comma
id|SMB_O_WRONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|result
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
comma
id|smb_write_one_page
)paren
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_write: pos=%ld, size=%ld, mtime=%ld, atime=%ld&bslash;n&quot;
comma
(paren
r_int
)paren
id|file-&gt;f_pos
comma
id|dentry-&gt;d_inode-&gt;i_size
comma
id|dentry-&gt;d_inode-&gt;i_mtime
comma
id|dentry-&gt;d_inode-&gt;i_atime
)paren
suffix:semicolon
macro_line|#endif
)brace
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_file_open
id|smb_file_open
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
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_open: opening %s/%s, d_count=%d&bslash;n&quot;
comma
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_name.name
comma
id|file-&gt;f_dentry-&gt;d_name.name
comma
id|file-&gt;f_dentry-&gt;d_count
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_file_release
id|smb_file_release
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
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_release: closing %s/%s, d_count=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_count
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dentry-&gt;d_count
op_eq
l_int|1
)paren
(brace
id|smb_close
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether the required access is compatible with&n; * an inode&squot;s permission. SMB doesn&squot;t recognize superuser&n; * privileges, so we need our own check for this.&n; */
r_static
r_int
DECL|function|smb_file_permission
id|smb_file_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
r_int
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
id|printk
c_func
(paren
l_string|&quot;smb_file_permission: mode=%x, mask=%x&bslash;n&quot;
comma
id|mode
comma
id|mask
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Look at user permissions */
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mode
op_amp
l_int|7
op_amp
id|mask
)paren
op_ne
id|mask
)paren
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|smb_file_operations
r_static
r_struct
id|file_operations
id|smb_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|smb_file_read
comma
multiline_comment|/* read */
id|smb_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* poll - default */
id|smb_ioctl
comma
multiline_comment|/* ioctl */
id|smb_file_mmap
comma
multiline_comment|/* mmap(struct file*, struct vm_area_struct*) */
id|smb_file_open
comma
multiline_comment|/* open(struct inode*, struct file*) */
l_int|NULL
comma
multiline_comment|/* flush */
id|smb_file_release
comma
multiline_comment|/* release(struct inode*, struct file*) */
id|smb_fsync
comma
multiline_comment|/* fsync(struct file*, struct dentry*) */
l_int|NULL
comma
multiline_comment|/* fasync(struct file*, int) */
l_int|NULL
comma
multiline_comment|/* check_media_change(kdev_t dev) */
l_int|NULL
comma
multiline_comment|/* revalidate(kdev_t dev) */
l_int|NULL
multiline_comment|/* lock(struct file*, int, struct file_lock*) */
)brace
suffix:semicolon
DECL|variable|smb_file_inode_operations
r_struct
id|inode_operations
id|smb_file_inode_operations
op_assign
(brace
op_amp
id|smb_file_operations
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
multiline_comment|/* get_block */
id|smb_readpage
comma
multiline_comment|/* readpage */
id|smb_writepage
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
id|smb_file_permission
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
id|smb_revalidate_inode
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
