multiline_comment|/*&n; * file.c&n; *&n; * PURPOSE&n; *  File handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *  E-mail regarding any portion of the Linux UDF file system should be&n; *  directed to the development team mailing list (run by majordomo):&n; *    linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *  This file is distributed under the terms of the GNU General Public&n; *  License (GPL). Copies of the GPL can be obtained from:&n; *    ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *  Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998-1999 Dave Boynton&n; *  (C) 1998-1999 Ben Fennema&n; *  (C) 1999 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; *  10/02/98 dgb  Attempt to integrate into udf.o&n; *  10/07/98      Switched to using generic_readpage, etc., like isofs&n; *                And it works!&n; *  12/06/98 blf  Added udf_file_read. uses generic_file_read for all cases but&n; *                ICB_FLAG_AD_IN_ICB.&n; *  04/06/99      64 bit file handling on 32 bit systems taken from ext2 file.c&n; *  05/12/99      Preliminary file write support&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt; /* memset */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
DECL|macro|NBUF
mdefine_line|#define NBUF&t;32
DECL|typedef|poll_table
r_typedef
r_void
op_star
id|poll_table
suffix:semicolon
r_static
r_int
r_int
id|udf_file_llseek
c_func
(paren
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_static
id|ssize_t
id|udf_file_read_adinicb
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|udf_file_write
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &lt; 64
r_static
r_int
id|udf_open_file
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
macro_line|#endif
r_static
r_int
id|udf_release_file
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
DECL|variable|udf_file_operations
r_static
r_struct
id|file_operations
id|udf_file_operations
op_assign
(brace
id|udf_file_llseek
comma
multiline_comment|/* llseek */
id|generic_file_read
comma
multiline_comment|/* read */
id|udf_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
id|udf_ioctl
comma
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
macro_line|#if BITS_PER_LONG == 64
l_int|NULL
comma
multiline_comment|/* open */
macro_line|#else
id|udf_open_file
comma
multiline_comment|/* open */
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* flush */
id|udf_release_file
comma
multiline_comment|/* release */
id|udf_sync_file
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
DECL|variable|udf_file_inode_operations
r_struct
id|inode_operations
id|udf_file_inode_operations
op_assign
(brace
op_amp
id|udf_file_operations
comma
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
id|udf_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
id|block_write_full_page
comma
multiline_comment|/* writepage */
id|block_flushpage
comma
multiline_comment|/* flushpage */
macro_line|#ifdef CONFIG_UDF_RW
id|udf_truncate
comma
multiline_comment|/* truncate */
macro_line|#else
l_int|NULL
comma
multiline_comment|/* truncate */
macro_line|#endif
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
DECL|variable|udf_file_operations_adinicb
r_static
r_struct
id|file_operations
id|udf_file_operations_adinicb
op_assign
(brace
id|udf_file_llseek
comma
multiline_comment|/* llseek */
id|udf_file_read_adinicb
comma
multiline_comment|/* read */
id|udf_file_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
id|udf_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* flush */
id|udf_release_file
comma
multiline_comment|/* release */
id|udf_sync_file
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
DECL|variable|udf_file_inode_operations_adinicb
r_struct
id|inode_operations
id|udf_file_inode_operations_adinicb
op_assign
(brace
op_amp
id|udf_file_operations_adinicb
comma
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
id|udf_get_block
comma
multiline_comment|/* get_block */
id|block_read_full_page
comma
multiline_comment|/* readpage */
id|block_write_full_page
comma
multiline_comment|/* writepage */
id|block_flushpage
comma
multiline_comment|/* flushpage */
macro_line|#ifdef CONFIG_UDF_RW
id|udf_truncate
comma
multiline_comment|/* truncate */
macro_line|#else
l_int|NULL
comma
multiline_comment|/* truncate */
macro_line|#endif
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
multiline_comment|/*&n; * Make sure the offset never goes beyond the 32-bit mark..&n; */
DECL|function|udf_file_llseek
r_static
r_int
r_int
id|udf_file_llseek
c_func
(paren
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
id|origin
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
(brace
id|offset
op_add_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
(brace
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
r_int
)paren
id|offset
op_rshift
l_int|32
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#if BITS_PER_LONG &lt; 64
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|offset
OG
ques
c_cond
ques
c_cond
ques
c_cond
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|remove_suid
r_static
r_inline
r_void
id|remove_suid
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* set S_IGID if S_IXGRP is set, and always set S_ISUID */
id|mode
op_assign
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXGRP
)paren
op_star
(paren
id|S_ISGID
op_div
id|S_IXGRP
)paren
op_or
id|S_ISUID
suffix:semicolon
multiline_comment|/* was any of the uid bits set? */
id|mode
op_and_assign
id|inode-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FSETID
)paren
)paren
(brace
id|inode-&gt;i_mode
op_and_assign
op_complement
id|mode
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|udf_file_write
r_static
id|ssize_t
id|udf_file_write
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
id|ssize_t
id|retval
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|remove_suid
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_eq
id|ICB_FLAG_AD_IN_ICB
)paren
(brace
r_int
id|i
comma
id|err
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|udf_expand_adinicb
c_func
(paren
id|inode
comma
op_amp
id|i
comma
l_int|0
comma
op_amp
id|err
)paren
)paren
)paren
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|retval
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
id|block_write_partial_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|UDF_I_UCTIME
c_func
(paren
id|inode
)paren
op_assign
id|UDF_I_UMTIME
c_func
(paren
id|inode
)paren
op_assign
id|CURRENT_UTIME
suffix:semicolon
)brace
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_file_read&n; *&n; * PURPOSE&n; *&t;Read from an open file.&n; *&n; * DESCRIPTION&n; *&t;Optional - sys_read() will return -EINVAL if this routine is not&n; *&t;available.&n; *&n; *&t;Refer to sys_read() in fs/read_write.c&n; *&t;sys_read() -&gt; .&n; *&n; *&t;Note that you can use generic_file_read() instead, which requires that&n; *&t;udf_readpage() be available, but you can use generic_readpage(), which&n; *&t;requires that udf_block_map() be available. Reading will then be done by&n; *&t;memory-mapping the file a page at a time. This is not suitable for&n; *&t;devices that don&squot;t handle read-ahead [example: CD-R/RW that may have&n; *&t;blank sectors that shouldn&squot;t be read].&n; *&n; *&t;Refer to generic_file_read() in mm/filemap.c and to generic_readpage()&n; *&t;in fs/buffer.c&n; *&n; *&t;Block devices can use block_read() instead. Refer to fs/block_dev.c&n; *&n; * PRE-CONDITIONS&n; *&t;inode&t;&t;&t;Pointer to inode to read from (never NULL).&n; *&t;filp&t;&t;&t;Pointer to file to read from (never NULL).&n; *&t;buf&t;&t;&t;Point to read buffer (validated).&n; *&t;bufsize&t;&t;&t;Size of read buffer.&n; *&n; * POST-CONDITIONS&n; *&t;&lt;return&gt;&t;&t;Bytes read (&gt;=0) or an error code (&lt;0) that&n; *&t;&t;&t;&t;sys_read() will return.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; */
DECL|function|udf_file_read_adinicb
r_static
id|ssize_t
id|udf_file_read_adinicb
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|bufsize
comma
id|loff_t
op_star
id|loff
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|Uint32
id|size
comma
id|left
comma
id|pos
comma
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
op_star
id|loff
OG
id|size
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_else
id|left
op_assign
id|size
op_minus
op_star
id|loff
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
id|bufsize
)paren
id|left
op_assign
id|bufsize
suffix:semicolon
r_if
c_cond
(paren
id|left
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|pos
op_assign
op_star
id|loff
op_plus
id|UDF_I_EXT0OFFS
c_func
(paren
id|inode
)paren
suffix:semicolon
id|block
op_assign
id|udf_block_map
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|udf_tread
c_func
(paren
id|inode-&gt;i_sb
comma
id|udf_get_lb_pblock
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
comma
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|copy_to_user
c_func
(paren
id|buf
comma
id|bh-&gt;b_data
op_plus
id|pos
comma
id|left
)paren
)paren
op_star
id|loff
op_add_assign
id|left
suffix:semicolon
r_else
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|left
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_ioctl&n; *&n; * PURPOSE&n; *&t;Issue an ioctl.&n; *&n; * DESCRIPTION&n; *&t;Optional - sys_ioctl() will return -ENOTTY if this routine is not&n; *&t;available, and the ioctl cannot be handled without filesystem help.&n; *&n; *&t;sys_ioctl() handles these ioctls that apply only to regular files:&n; *&t;&t;FIBMAP [requires udf_block_map()], FIGETBSZ, FIONREAD&n; *&t;These ioctls are also handled by sys_ioctl():&n; *&t;&t;FIOCLEX, FIONCLEX, FIONBIO, FIOASYNC&n; *&t;All other ioctls are passed to the filesystem.&n; *&n; *&t;Refer to sys_ioctl() in fs/ioctl.c&n; *&t;sys_ioctl() -&gt; .&n; *&n; * PRE-CONDITIONS&n; *&t;inode&t;&t;&t;Pointer to inode that ioctl was issued on.&n; *&t;filp&t;&t;&t;Pointer to file that ioctl was issued on.&n; *&t;cmd&t;&t;&t;The ioctl command.&n; *&t;arg&t;&t;&t;The ioctl argument [can be interpreted as a&n; *&t;&t;&t;&t;user-space pointer if desired].&n; *&n; * POST-CONDITIONS&n; *&t;&lt;return&gt;&t;&t;Success (&gt;=0) or an error code (&lt;=0) that&n; *&t;&t;&t;&t;sys_ioctl() will return.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; */
DECL|function|udf_ioctl
r_int
id|udf_ioctl
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|FileEntry
op_star
id|fe
suffix:semicolon
id|Uint16
id|ident
suffix:semicolon
r_if
c_cond
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;no permission to access inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;invalid argument to udf_ioctl&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* first, do ioctls that don&squot;t need to udf_read */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|UDF_GETVOLIDENT
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_eq
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|arg
comma
l_int|32
)paren
)paren
op_eq
l_int|0
)paren
id|result
op_assign
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|UDF_SB_VOLIDENT
c_func
(paren
id|inode-&gt;i_sb
)paren
comma
l_int|32
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* ok, we need to read the inode */
id|bh
op_assign
id|udf_read_ptagged
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
comma
op_amp
id|ident
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|ident
op_ne
id|TID_FILE_ENTRY
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;bread failed (ino=%ld) or ident (%d) != TID_FILE_ENTRY&quot;
comma
id|inode-&gt;i_ino
comma
id|ident
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|fe
op_assign
(paren
r_struct
id|FileEntry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|fe-&gt;lengthExtendedAttr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|UDF_GETEASIZE
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|arg
comma
l_int|4
)paren
)paren
op_eq
l_int|0
)paren
id|result
op_assign
id|put_user
c_func
(paren
id|size
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UDF_GETEABLOCK
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|arg
comma
id|size
)paren
)paren
op_eq
l_int|0
)paren
id|result
op_assign
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|fe-&gt;extendedAttr
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|udf_debug
c_func
(paren
l_string|&quot;ino=%ld, cmd=%d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_release_file&n; *&n; * PURPOSE&n; *  Called when all references to the file are closed&n; *&n; * DESCRIPTION&n; *  Discard prealloced blocks&n; *&n; * HISTORY&n; *&n; */
DECL|function|udf_release_file
r_static
r_int
id|udf_release_file
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
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|udf_discard_prealloc
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if BITS_PER_LONG &lt; 64
multiline_comment|/*&n; * udf_open_file&n; *&n; * PURPOSE&n; *  Called when an inode is about to be open.&n; *&n; * DESCRIPTION&n; *  Use this to disallow opening RW large files on 32 bit systems.&n; *&n; * HISTORY&n; *&n; */
DECL|function|udf_open_file
r_static
r_int
id|udf_open_file
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
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_size
op_eq
(paren
id|Uint32
)paren
op_minus
l_int|1
op_logical_and
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
