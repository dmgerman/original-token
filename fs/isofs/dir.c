multiline_comment|/*&n; *  linux/fs/isofs/dir.c&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  isofs directory handling functions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
r_static
r_int
id|isofs_readdir
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
id|dirent
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|isofs_dir_operations
r_static
r_struct
id|file_operations
id|isofs_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|isofs_file_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|isofs_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|isofs_dir_inode_operations
r_struct
id|inode_operations
id|isofs_dir_inode_operations
op_assign
(brace
op_amp
id|isofs_dir_operations
comma
multiline_comment|/* default directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|isofs_lookup
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
id|isofs_bmap
comma
multiline_comment|/* bmap */
l_int|NULL
multiline_comment|/* truncate */
)brace
suffix:semicolon
multiline_comment|/* This is used to speed up lookup.  Without this we would need to&n;make a linear search of the directory to find the file that the&n;directory read just returned.  This is a single element cache. */
DECL|variable|cache
r_struct
id|lookup_cache
id|cache
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|function|isofs_readdir
r_static
r_int
id|isofs_readdir
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
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|block
comma
id|offset
comma
id|i
comma
id|j
suffix:semicolon
r_char
id|c
op_assign
l_int|0
suffix:semicolon
r_int
id|inode_number
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|cpnt
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|old_offset
suffix:semicolon
r_int
id|dlen
comma
id|rrflag
suffix:semicolon
r_char
op_star
id|dpnt
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|BLOCK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|block
op_assign
id|isofs_bmap
c_func
(paren
id|inode
comma
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|BLOCK_SIZE_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|filp-&gt;f_pos
OL
id|inode-&gt;i_size
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Block, offset: %x %x %x&bslash;n&quot;
comma
id|block
comma
id|offset
comma
id|filp-&gt;f_pos
)paren
suffix:semicolon
macro_line|#endif
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|offset
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
id|inode_number
op_assign
(paren
id|block
op_lshift
id|BLOCK_SIZE_BITS
)paren
op_plus
(paren
id|offset
op_amp
(paren
id|BLOCK_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* If the length byte is zero, we should move on to the next CDROM sector.&n;&t;&t;   If we are at the end of the directory, we kick out of the while loop. */
r_if
c_cond
(paren
op_star
(paren
(paren
r_char
op_star
)paren
id|de
)paren
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_assign
(paren
id|filp-&gt;f_pos
op_amp
op_complement
(paren
id|ISOFS_BLOCK_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|ISOFS_BLOCK_SIZE
suffix:semicolon
id|block
op_assign
id|isofs_bmap
c_func
(paren
id|inode
comma
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|BLOCK_SIZE_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Make sure that the entire directory record is in the current bh block.&n;&t;&t;   If not, we malloc a buffer, and put the two halves together, so that&n;&t;&t;   we can cleanly read the block */
id|old_offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|BLOCK_SIZE
)paren
(brace
id|cpnt
op_assign
id|kmalloc
c_func
(paren
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
comma
id|bh-&gt;b_data
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
(paren
id|old_offset
op_plus
id|cpnt
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
op_amp
(paren
id|BLOCK_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|block
op_assign
id|isofs_bmap
c_func
(paren
id|inode
comma
(paren
id|filp-&gt;f_pos
)paren
op_rshift
id|BLOCK_SIZE_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
op_logical_or
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
comma
id|ISOFS_BUFFER_SIZE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|cpnt
op_plus
id|BLOCK_SIZE
comma
id|bh-&gt;b_data
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
)brace
multiline_comment|/* Handle the case of the &squot;.&squot; directory */
id|rrflag
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
id|put_fs_byte
c_func
(paren
l_char|&squot;.&squot;
comma
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|inode_number
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|dpnt
op_assign
l_string|&quot;.&quot;
suffix:semicolon
)brace
multiline_comment|/* Handle the case of the &squot;..&squot; directory */
r_else
r_if
c_cond
(paren
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|1
)paren
(brace
id|put_fs_byte
c_func
(paren
l_char|&squot;.&squot;
comma
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_char|&squot;.&squot;
comma
id|dirent-&gt;d_name
op_plus
l_int|1
)paren
suffix:semicolon
id|i
op_assign
l_int|2
suffix:semicolon
id|dpnt
op_assign
l_string|&quot;..&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_firstdatazone
op_lshift
id|BLOCK_SIZE_BITS
)paren
op_ne
id|inode-&gt;i_ino
)paren
(brace
id|inode_number
op_assign
id|inode-&gt;u.isofs_i.i_backlink
suffix:semicolon
)brace
r_else
id|inode_number
op_assign
id|inode-&gt;i_ino
suffix:semicolon
multiline_comment|/* This should never happen, but who knows.  Try to be forgiving */
r_if
c_cond
(paren
id|inode_number
op_eq
op_minus
l_int|1
)paren
(brace
id|inode_number
op_assign
id|isofs_lookup_grandparent
c_func
(paren
id|inode
comma
id|find_rock_ridge_relocation
c_func
(paren
id|de
comma
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode_number
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Should never happen */
id|printk
c_func
(paren
l_string|&quot;Backlink not properly set.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
)brace
)brace
multiline_comment|/* Handle everything else.  Do name translation if there&n;&t;&t;   is no Rock Ridge NM field. */
r_else
(brace
id|dlen
op_assign
id|de-&gt;name_len
(braket
l_int|0
)braket
suffix:semicolon
id|dpnt
op_assign
id|de-&gt;name
suffix:semicolon
id|i
op_assign
id|dlen
suffix:semicolon
id|rrflag
op_assign
id|get_rock_ridge_filename
c_func
(paren
id|de
comma
op_amp
id|dpnt
comma
op_amp
id|dlen
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rrflag
)paren
(brace
r_if
c_cond
(paren
id|rrflag
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* This is a rock ridge reloc dir */
r_if
c_cond
(paren
id|cpnt
)paren
(brace
id|kfree_s
c_func
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|cpnt
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
id|i
op_assign
id|dlen
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_mapping
op_eq
l_char|&squot;n&squot;
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dlen
op_logical_and
id|i
OL
id|NAME_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|c
op_assign
id|dpnt
(braket
id|i
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* lower case */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
op_logical_and
id|i
op_eq
id|dlen
op_minus
l_int|2
op_logical_and
id|de-&gt;name
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/* Drop trailing &squot;;1&squot; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
)paren
id|c
op_assign
l_char|&squot;.&squot;
suffix:semicolon
multiline_comment|/* Convert remaining &squot;;&squot; to &squot;.&squot; */
id|dpnt
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
)brace
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
id|put_fs_byte
c_func
(paren
id|dpnt
(braket
id|j
)braket
comma
id|j
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
)brace
multiline_comment|/* And save it */
)brace
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Nchar: %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|i
)paren
(brace
r_while
c_loop
(paren
id|cache.lock
)paren
suffix:semicolon
id|cache.lock
op_assign
l_int|1
suffix:semicolon
id|cache.ino
op_assign
id|inode_number
suffix:semicolon
id|cache.dir
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|cache.dev
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|strncpy
c_func
(paren
id|cache.filename
comma
id|dpnt
comma
id|i
)paren
suffix:semicolon
id|cache.dlen
op_assign
id|dlen
suffix:semicolon
id|cache.lock
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|rrflag
)paren
id|kfree
c_func
(paren
id|dpnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpnt
)paren
(brace
id|kfree_s
c_func
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|cpnt
op_assign
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|put_fs_long
c_func
(paren
id|inode_number
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
multiline_comment|/* We go here for any condition we cannot handle.  We also drop through&n;&t;   to here at the end of the directory. */
id|out
suffix:colon
r_if
c_cond
(paren
id|cpnt
)paren
id|kfree_s
c_func
(paren
id|cpnt
comma
l_int|1
op_lshift
id|ISOFS_BLOCK_BITS
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof