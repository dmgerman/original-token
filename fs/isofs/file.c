multiline_comment|/*&n; *  linux/fs/isofs/file.c&n; *&n; *  (C) 1992, 1993, 1994  Eric Youngdale Modified for ISO9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; *&n; *  isofs regular file handling primitives&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NBUF
mdefine_line|#define&t;NBUF&t;32
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b))?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
r_static
r_int
id|isofs_file_read
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
)paren
suffix:semicolon
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the isofs filesystem.&n; */
DECL|variable|isofs_file_operations
r_static
r_struct
id|file_operations
id|isofs_file_operations
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
id|generic_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open is needed */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|isofs_file_inode_operations
r_struct
id|inode_operations
id|isofs_file_inode_operations
op_assign
(brace
op_amp
id|isofs_file_operations
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
id|isofs_bmap
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
multiline_comment|/* This is a heuristic to determine if a file is text of binary.  If it&n; * is text, then we translate all 0x0d characters to spaces.  If the 0x0d&n; * character is not preceded or followed by a 0x0a, then we turn it into&n; * a 0x0a.  A control-Z is also turned into a linefeed.&n; */
DECL|function|unixify_to_fs
r_static
r_inline
r_void
id|unixify_to_fs
c_func
(paren
r_char
op_star
id|outbuf
comma
r_char
op_star
id|buffer
comma
r_int
id|chars
comma
r_int
id|mode
)paren
(brace
r_char
id|outchar
suffix:semicolon
r_while
c_loop
(paren
id|chars
op_decrement
)paren
(brace
id|outchar
op_assign
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|outchar
op_eq
l_int|0x1a
)paren
(brace
id|outchar
op_assign
l_int|0x0a
suffix:semicolon
)brace
r_if
c_cond
(paren
id|outchar
op_eq
l_int|0x0d
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|ISOFS_FILE_TEXT_M
)paren
(brace
id|outchar
op_assign
l_int|0x0a
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode
op_eq
id|ISOFS_FILE_TEXT
)paren
(brace
id|outchar
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
)brace
id|put_user
c_func
(paren
id|outchar
comma
id|outbuf
op_increment
)paren
suffix:semicolon
id|buffer
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*This function determines if a given file has a DOS-like text format or not*/
DECL|function|isofs_determine_filetype
r_static
r_void
id|isofs_determine_filetype
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|block
suffix:semicolon
r_int
id|result
comma
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_char
op_star
id|pnt
suffix:semicolon
id|block
op_assign
id|isofs_bmap
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
id|block
op_logical_and
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
c_func
(paren
id|inode
)paren
)paren
)paren
)paren
(brace
id|pnt
op_assign
(paren
r_int
r_char
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|result
op_assign
id|ISOFS_FILE_TEXT_M
suffix:semicolon
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
id|inode-&gt;i_size
OL
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
ques
c_cond
id|inode-&gt;i_size
suffix:colon
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|i
op_increment
comma
id|pnt
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|pnt
op_amp
l_int|0x80
)paren
(brace
id|result
op_assign
id|ISOFS_FILE_BINARY
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pnt
op_ge
l_int|0x20
op_logical_or
op_star
id|pnt
op_eq
l_int|0x1a
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|pnt
op_eq
l_int|0x0a
)paren
(brace
id|result
op_assign
id|ISOFS_FILE_TEXT
suffix:semicolon
r_continue
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pnt
op_ge
l_int|0x9
op_logical_and
op_star
id|pnt
op_le
l_int|0x0d
)paren
(brace
r_continue
suffix:semicolon
)brace
id|result
op_assign
id|ISOFS_FILE_BINARY
suffix:semicolon
r_break
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode-&gt;u.isofs_i.i_file_format
op_assign
id|result
suffix:semicolon
)brace
)brace
DECL|function|isofs_file_read
r_static
r_int
id|isofs_file_read
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|read
comma
id|left
comma
id|chars
suffix:semicolon
r_int
id|block
comma
id|blocks
comma
id|offset
comma
id|total_blocks
suffix:semicolon
r_int
id|bhrequest
suffix:semicolon
r_int
id|ra_blocks
comma
id|max_block
comma
id|nextblock
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|bhb
comma
op_star
op_star
id|bhe
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhreq
(braket
id|NBUF
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|buflist
(braket
id|NBUF
)braket
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
l_string|&quot;isofs_file_read: inode = NULL&bslash;n&quot;
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
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;isofs_file_read: mode = %07o&bslash;n&quot;
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
id|inode-&gt;u.isofs_i.i_file_format
op_eq
id|ISOFS_FILE_UNKNOWN
)paren
id|isofs_determine_filetype
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
OG
id|inode-&gt;i_size
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_else
id|left
op_assign
id|inode-&gt;i_size
op_minus
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
id|count
)paren
id|left
op_assign
id|count
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
id|read
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|filp-&gt;f_pos
op_rshift
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|inode-&gt;u.isofs_i.i_first_extent
op_plus
id|filp-&gt;f_pos
)paren
op_amp
(paren
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|blocks
op_assign
(paren
id|left
op_plus
id|offset
op_plus
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
op_minus
l_int|1
)paren
op_div
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|bhb
op_assign
id|bhe
op_assign
id|buflist
suffix:semicolon
id|ra_blocks
op_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|inode-&gt;i_dev
)paren
)braket
op_div
(paren
id|BLOCK_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ra_blocks
OG
id|blocks
)paren
(brace
id|blocks
op_assign
id|ra_blocks
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * this is for stopping read ahead at EOF. It&squot;s  important for&n;&t; * reading PhotoCD&squot;s, because they have many small data tracks instead&n;&t; * of one big. And between two data-tracks are some unreadable sectors.&n;&t; * A read ahead after a EOF may try to read such an unreadable sector.&n;&t; *    kraxel@cs.tu-berlin.de (Gerd Knorr)&n;&t; */
id|total_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
(paren
l_int|1
op_lshift
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
)paren
op_minus
l_int|1
)paren
op_rshift
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_plus
id|blocks
OG
id|total_blocks
)paren
id|blocks
op_assign
id|total_blocks
op_minus
id|block
suffix:semicolon
id|max_block
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|BLOCK_SIZE
op_minus
l_int|1
)paren
op_div
id|BLOCK_SIZE
suffix:semicolon
id|nextblock
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* We do this in a two stage process.  We first try and request&n;&t;   as many blocks as we can, then we wait for the first one to&n;&t;   complete, and then we try and wrap up as many as are actually&n;&t;   done.  This routine is rather generic, in that it can be used&n;&t;   in a filesystem by substituting the appropriate function in&n;&t;   for getblk.&n;&n;&t;   This routine is optimized to make maximum use of the various&n;&t;   buffers and caches. */
r_do
(brace
id|bhrequest
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|blocks
)paren
(brace
r_int
id|uptodate
suffix:semicolon
op_decrement
id|blocks
suffix:semicolon
op_star
id|bhb
op_assign
id|getblk
c_func
(paren
id|inode-&gt;i_dev
comma
id|isofs_bmap
c_func
(paren
id|inode
comma
id|block
op_increment
)paren
comma
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|uptodate
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bhb
op_logical_and
op_logical_neg
(paren
op_star
id|bhb
)paren
op_member_access_from_pointer
id|b_uptodate
)paren
(brace
id|uptodate
op_assign
l_int|0
suffix:semicolon
id|bhreq
(braket
id|bhrequest
op_increment
)braket
op_assign
op_star
id|bhb
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhb
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhb
op_assign
id|buflist
suffix:semicolon
multiline_comment|/* If the block we have on hand is uptodate, go ahead&n;&t;&t;&t;   and complete processing. */
r_if
c_cond
(paren
id|uptodate
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bhb
op_eq
id|bhe
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Now request them all */
r_if
c_cond
(paren
id|bhrequest
)paren
id|ll_rw_block
c_func
(paren
id|READ
comma
id|bhrequest
comma
id|bhreq
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* Finish off all I/O that has actually completed */
r_if
c_cond
(paren
op_star
id|bhe
)paren
(brace
multiline_comment|/* test for valid buffer */
id|wait_on_buffer
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_uptodate
)paren
(brace
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
id|left
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|left
OL
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
op_minus
id|offset
)paren
id|chars
op_assign
id|left
suffix:semicolon
r_else
id|chars
op_assign
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
op_minus
id|offset
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|chars
suffix:semicolon
id|left
op_sub_assign
id|chars
suffix:semicolon
id|read
op_add_assign
id|chars
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bhe
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;u.isofs_i.i_file_format
op_eq
id|ISOFS_FILE_TEXT
op_logical_or
id|inode-&gt;u.isofs_i.i_file_format
op_eq
id|ISOFS_FILE_TEXT_M
)paren
id|unixify_to_fs
c_func
(paren
id|buf
comma
id|offset
op_plus
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_data
comma
id|chars
comma
id|inode-&gt;u.isofs_i.i_file_format
)paren
suffix:semicolon
r_else
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|offset
op_plus
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_data
comma
id|chars
)paren
suffix:semicolon
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|chars
op_decrement
OG
l_int|0
)paren
id|put_user
c_func
(paren
l_int|0
comma
id|buf
op_increment
)paren
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
r_while
c_loop
(paren
id|bhe
op_ne
id|bhb
op_logical_and
(paren
op_star
id|bhe
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
op_star
id|bhe
)paren
op_member_access_from_pointer
id|b_lock
)paren
op_logical_and
(paren
id|left
OG
l_int|0
)paren
)paren
(brace
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|left
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Release the read-ahead blocks */
r_while
c_loop
(paren
id|bhe
op_ne
id|bhb
)paren
(brace
r_if
c_cond
(paren
op_star
id|bhe
)paren
id|brelse
c_func
(paren
op_star
id|bhe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|bhe
op_eq
op_amp
id|buflist
(braket
id|NBUF
)braket
)paren
id|bhe
op_assign
id|buflist
suffix:semicolon
)brace
suffix:semicolon
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|read
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
eof
