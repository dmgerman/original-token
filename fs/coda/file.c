multiline_comment|/*&n; * File operations for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_cnode.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
multiline_comment|/* file operations */
r_static
r_int
id|coda_readpage
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
suffix:semicolon
r_static
id|ssize_t
id|coda_file_read
c_func
(paren
r_struct
id|file
op_star
id|f
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
id|off
)paren
suffix:semicolon
r_static
id|ssize_t
id|coda_file_write
c_func
(paren
r_struct
id|file
op_star
id|f
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
id|off
)paren
suffix:semicolon
r_static
r_int
id|coda_file_mmap
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
suffix:semicolon
multiline_comment|/* exported from this file */
r_int
id|coda_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
DECL|variable|coda_file_inode_operations
r_struct
id|inode_operations
id|coda_file_inode_operations
op_assign
(brace
op_amp
id|coda_file_operations
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
id|coda_readpage
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
id|coda_permission
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* update page */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|coda_file_operations
r_struct
id|file_operations
id|coda_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default should work for coda */
id|coda_file_read
comma
multiline_comment|/* read */
id|coda_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl */
id|coda_file_mmap
comma
multiline_comment|/* mmap */
id|coda_open
comma
multiline_comment|/* open */
id|coda_release
comma
multiline_comment|/* release */
id|coda_fsync
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
multiline_comment|/* lock */
)brace
suffix:semicolon
multiline_comment|/*  File file operations */
DECL|function|coda_readpage
r_static
r_int
id|coda_readpage
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
r_struct
id|dentry
id|cont_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|cont_inode
suffix:semicolon
r_struct
id|cnode
op_star
id|cnp
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cnp
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cnp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cnp-&gt;c_ovp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_readpage: no open inode for ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|cont_inode
op_assign
id|cnp-&gt;c_ovp
suffix:semicolon
id|cont_dentry.d_inode
op_assign
id|cont_inode
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;coda ino: %ld, cached ino %ld, page offset: %lx&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|cont_inode-&gt;i_ino
comma
id|page-&gt;offset
)paren
suffix:semicolon
id|generic_readpage
c_func
(paren
op_amp
id|cont_dentry
comma
id|page
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_file_mmap
r_static
r_int
id|coda_file_mmap
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
id|cnode
op_star
id|cnp
suffix:semicolon
id|cnp
op_assign
id|ITOC
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|cnp-&gt;c_mmcount
op_increment
suffix:semicolon
r_return
id|generic_file_mmap
c_func
(paren
id|file
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|coda_file_read
r_static
id|ssize_t
id|coda_file_read
c_func
(paren
r_struct
id|file
op_star
id|coda_file
comma
r_char
op_star
id|buff
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
id|cnode
op_star
id|cnp
suffix:semicolon
r_struct
id|inode
op_star
id|coda_inode
op_assign
id|coda_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|cont_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file
id|cont_file
suffix:semicolon
r_struct
id|dentry
id|cont_dentry
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cnp
op_assign
id|ITOC
c_func
(paren
id|coda_inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cnp
)paren
suffix:semicolon
id|cont_inode
op_assign
id|cnp-&gt;c_ovp
suffix:semicolon
r_if
c_cond
(paren
id|cont_inode
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_file_read: cached inode is 0!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|coda_prepare_openfile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
comma
op_amp
id|cont_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cont_file.f_op
op_logical_or
op_logical_neg
id|cont_file.f_op-&gt;read
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;container file has no read in file operations.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|result
op_assign
id|cont_file.f_op
op_member_access_from_pointer
id|read
c_func
(paren
op_amp
id|cont_file
comma
id|buff
comma
id|count
comma
op_amp
(paren
id|cont_file.f_pos
)paren
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;ops at %x result %d, count %d, position: %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|cont_file.f_op
comma
id|result
comma
id|count
comma
(paren
r_int
)paren
id|cont_file.f_pos
)paren
suffix:semicolon
id|coda_restore_codafile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|coda_file_write
r_static
id|ssize_t
id|coda_file_write
c_func
(paren
r_struct
id|file
op_star
id|coda_file
comma
r_const
r_char
op_star
id|buff
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
id|cnode
op_star
id|cnp
suffix:semicolon
r_struct
id|inode
op_star
id|coda_inode
op_assign
id|coda_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|cont_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file
id|cont_file
suffix:semicolon
r_struct
id|dentry
id|cont_dentry
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cnp
op_assign
id|ITOC
c_func
(paren
id|coda_inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cnp
)paren
suffix:semicolon
id|cont_inode
op_assign
id|cnp-&gt;c_ovp
suffix:semicolon
r_if
c_cond
(paren
id|cont_inode
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_file_write: cached inode is 0!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|coda_prepare_openfile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
comma
op_amp
id|cont_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cont_file.f_op
op_logical_or
op_logical_neg
id|cont_file.f_op-&gt;write
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_file_write: container file has no file ops.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|cnp-&gt;c_flags
op_and_assign
op_complement
id|C_VATTR
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cont_inode-&gt;i_sem
)paren
suffix:semicolon
id|result
op_assign
id|cont_file.f_op
op_member_access_from_pointer
id|write
c_func
(paren
op_amp
id|cont_file
comma
id|buff
comma
id|count
comma
op_amp
(paren
id|cont_file.f_pos
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cont_inode-&gt;i_sem
)paren
suffix:semicolon
id|coda_restore_codafile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|coda_fsync
r_int
id|coda_fsync
c_func
(paren
r_struct
id|file
op_star
id|coda_file
comma
r_struct
id|dentry
op_star
id|coda_dentry
)paren
(brace
r_struct
id|cnode
op_star
id|cnp
suffix:semicolon
r_struct
id|inode
op_star
id|coda_inode
op_assign
id|coda_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|cont_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file
id|cont_file
suffix:semicolon
r_struct
id|dentry
id|cont_dentry
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|coda_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|coda_inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|coda_inode-&gt;i_mode
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cnp
op_assign
id|ITOC
c_func
(paren
id|coda_inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cnp
)paren
suffix:semicolon
id|cont_inode
op_assign
id|cnp-&gt;c_ovp
suffix:semicolon
r_if
c_cond
(paren
id|cont_inode
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_file_write: cached inode is 0!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|coda_prepare_openfile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
comma
op_amp
id|cont_dentry
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cont_inode-&gt;i_sem
)paren
suffix:semicolon
id|result
op_assign
id|file_fsync
c_func
(paren
op_amp
id|cont_file
comma
op_amp
id|cont_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
id|result
op_assign
id|venus_fsync
c_func
(paren
id|coda_inode-&gt;i_sb
comma
op_amp
(paren
id|cnp-&gt;c_fid
)paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|cont_inode-&gt;i_sem
)paren
suffix:semicolon
id|coda_restore_codafile
c_func
(paren
id|coda_inode
comma
id|coda_file
comma
id|cont_inode
comma
op_amp
id|cont_file
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* &n; * support routines&n; */
multiline_comment|/* instantiate the container file and dentry object to do io */
DECL|function|coda_prepare_openfile
r_void
id|coda_prepare_openfile
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|coda_file
comma
r_struct
id|inode
op_star
id|cont_inode
comma
r_struct
id|file
op_star
id|cont_file
comma
r_struct
id|dentry
op_star
id|cont_dentry
)paren
(brace
id|cont_file-&gt;f_pos
op_assign
id|coda_file-&gt;f_pos
suffix:semicolon
id|cont_file-&gt;f_mode
op_assign
id|coda_file-&gt;f_mode
suffix:semicolon
id|cont_file-&gt;f_flags
op_assign
id|coda_file-&gt;f_flags
suffix:semicolon
id|cont_file-&gt;f_count
op_assign
id|coda_file-&gt;f_count
suffix:semicolon
id|cont_file-&gt;f_owner
op_assign
id|coda_file-&gt;f_owner
suffix:semicolon
id|cont_file-&gt;f_op
op_assign
id|cont_inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
id|cont_file-&gt;f_dentry
op_assign
id|cont_dentry
suffix:semicolon
id|cont_file-&gt;f_dentry-&gt;d_inode
op_assign
id|cont_inode
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* update the Coda file &amp; inode after I/O */
DECL|function|coda_restore_codafile
r_void
id|coda_restore_codafile
c_func
(paren
r_struct
id|inode
op_star
id|coda_inode
comma
r_struct
id|file
op_star
id|coda_file
comma
r_struct
id|inode
op_star
id|open_inode
comma
r_struct
id|file
op_star
id|open_file
)paren
(brace
id|coda_file-&gt;f_pos
op_assign
id|open_file-&gt;f_pos
suffix:semicolon
multiline_comment|/* XXX what about setting the mtime here too? */
id|coda_inode-&gt;i_mtime
op_assign
id|open_inode-&gt;i_mtime
suffix:semicolon
id|coda_inode-&gt;i_size
op_assign
id|open_inode-&gt;i_size
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* grab the ext2 inode of the container file */
DECL|function|coda_inode_grab
r_int
id|coda_inode_grab
c_func
(paren
id|dev_t
id|dev
comma
id|ino_t
id|ino
comma
r_struct
id|inode
op_star
op_star
id|ind
)paren
(brace
r_struct
id|super_block
op_star
id|sbptr
suffix:semicolon
id|sbptr
op_assign
id|get_super
c_func
(paren
id|to_kdev_t
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbptr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_inode_grab: coda_find_super returns NULL.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
op_star
id|ind
op_assign
l_int|NULL
suffix:semicolon
op_star
id|ind
op_assign
id|iget
c_func
(paren
id|sbptr
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ind
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
"&quot;"
id|coda_inode_grab
suffix:colon
id|iget
c_func
(paren
id|dev
suffix:colon
op_mod
id|d
comma
id|ino
suffix:colon
op_mod
id|ld
)paren
id|returns
l_int|NULL
dot
"&bslash;"
id|n
"&quot;"
comma
id|dev
comma
id|ino
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_FILE
comma
l_string|&quot;ino: %ld, ops at %x&bslash;n&quot;
comma
id|ino
comma
(paren
r_int
)paren
(paren
op_star
id|ind
)paren
op_member_access_from_pointer
id|i_op
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof