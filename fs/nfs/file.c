multiline_comment|/*&n; *  linux/fs/nfs/file.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Changes Copyright (C) 1994 by Florian La Roche&n; *   - Do not copy data too often around in the kernel.&n; *   - In nfs_file_read the return value of kmalloc wasn&squot;t checked.&n; *   - Put in a better version of read look-ahead buffering. Original idea&n; *     and implementation by Wai S Kok elekokws@ee.nus.sg.&n; *&n; *  Expire cache on write to a file by Wai S Kok (Oct 1994).&n; *&n; *  Total rewrite of read side for new NFS buffer cache.. Linus.&n; *&n; *  nfs regular file handling functions&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_FILE
r_static
r_int
id|nfs_file_mmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_file_read
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|nfs_file_write
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|nfs_file_close
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_fsync
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|variable|nfs_file_operations
r_static
r_struct
id|file_operations
id|nfs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|nfs_file_read
comma
multiline_comment|/* read */
id|nfs_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
id|nfs_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
id|nfs_file_close
comma
multiline_comment|/* release */
id|nfs_fsync
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
id|nfs_lock
comma
multiline_comment|/* lock */
)brace
suffix:semicolon
DECL|variable|nfs_file_inode_operations
r_struct
id|inode_operations
id|nfs_file_inode_operations
op_assign
(brace
op_amp
id|nfs_file_operations
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
id|nfs_readpage
comma
multiline_comment|/* readpage */
id|nfs_writepage
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
id|nfs_updatepage
comma
multiline_comment|/* updatepage */
id|nfs_revalidate
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
r_static
r_int
DECL|function|nfs_file_close
id|nfs_file_close
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
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: close(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nfs_flush_dirty_pages
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
r_return
id|nfs_write_error
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_file_read
id|nfs_file_read
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
id|count
)paren
(brace
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: read(%x/%ld, %lu@%lu)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|count
comma
(paren
r_int
r_int
)paren
id|file-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
r_return
id|generic_file_read
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_file_mmap
id|nfs_file_mmap
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
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: mmap(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
r_return
id|generic_file_mmap
c_func
(paren
id|inode
comma
id|file
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|nfs_fsync
r_static
r_int
id|nfs_fsync
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
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: fsync(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
id|nfs_flush_dirty_pages
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Write to a file (through the page cache).&n; */
r_static
r_int
DECL|function|nfs_file_write
id|nfs_file_write
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
r_int
id|count
)paren
(brace
r_int
id|result
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: write(%x/%ld (%d), %lu@%lu)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_count
comma
id|count
comma
(paren
r_int
r_int
)paren
id|file-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_file_write: inode = NULL&bslash;n&quot;
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
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: attempt to write to active swap file!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
)paren
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
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
id|printk
c_func
(paren
l_string|&quot;nfs_file_write: write to non-file, mode %07o&bslash;n&quot;
comma
id|inode-&gt;i_mode
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
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Return error from previous async call */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|nfs_write_error
c_func
(paren
id|inode
)paren
)paren
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_return
id|generic_file_write
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lock a (portion of) a file&n; */
r_int
DECL|function|nfs_lock
id|nfs_lock
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
id|filp
comma
r_int
id|cmd
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_lock(f=%4x/%ld, t=%x, fl=%x, r=%ld:%ld)&bslash;n&quot;
comma
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_dev
comma
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_ino
comma
id|fl-&gt;fl_type
comma
id|fl-&gt;fl_flags
comma
id|fl-&gt;fl_start
comma
id|fl-&gt;fl_end
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* No mandatory locks over NFS */
r_if
c_cond
(paren
(paren
id|inode-&gt;i_mode
op_amp
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
op_eq
id|S_ISGID
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* Fake OK code if mounted without NLM support */
r_if
c_cond
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|NFS_MOUNT_NONLM
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * No BSD flocks over NFS allowed.&n;&t; * Note: we could try to fake a POSIX lock request here by&n;&t; * using ((u32) filp | 0x80000000) or some such as the pid.&n;&t; * Not sure whether that would be unique, though, or whether&n;&t; * that would break in other places.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|fl-&gt;fl_owner
op_logical_or
(paren
id|fl-&gt;fl_flags
op_amp
(paren
id|FL_POSIX
op_or
id|FL_BROKEN
)paren
)paren
op_ne
id|FL_POSIX
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* If unlocking a file region, flush dirty pages (unless we&squot;ve&n;&t; * been killed by a signal, that is). */
r_if
c_cond
(paren
id|cmd
op_eq
id|F_SETLK
op_logical_and
id|fl-&gt;fl_type
op_eq
id|F_UNLCK
op_logical_and
op_logical_neg
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
)paren
(brace
id|status
op_assign
id|nfs_flush_dirty_pages
c_func
(paren
id|inode
comma
id|fl-&gt;fl_start
comma
id|fl-&gt;fl_end
op_eq
id|NLM_OFFSET_MAX
ques
c_cond
l_int|0
suffix:colon
id|fl-&gt;fl_end
op_minus
id|fl-&gt;fl_start
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nlmclnt_proc
c_func
(paren
id|inode
comma
id|cmd
comma
id|fl
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/* Here, we could turn off write-back of pages in the&n;&t; * locked file region */
r_return
l_int|0
suffix:semicolon
)brace
eof
