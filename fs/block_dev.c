multiline_comment|/*&n; *  linux/fs/block_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
op_star
id|blk_size
(braket
)braket
suffix:semicolon
r_extern
r_int
op_star
id|blksize_size
(braket
)braket
suffix:semicolon
DECL|macro|MAX_BUF_PER_PAGE
mdefine_line|#define MAX_BUF_PER_PAGE (PAGE_SIZE / 512)
DECL|macro|NBUF
mdefine_line|#define NBUF 64
DECL|function|block_write
id|ssize_t
id|block_write
c_func
(paren
r_struct
id|file
op_star
id|filp
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
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|blocksize
comma
id|blocksize_bits
comma
id|i
comma
id|buffercount
comma
id|write_error
suffix:semicolon
id|ssize_t
id|block
comma
id|blocks
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
id|ssize_t
id|chars
suffix:semicolon
id|ssize_t
id|written
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhlist
(braket
id|NBUF
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bufferlist
(braket
id|NBUF
)braket
suffix:semicolon
r_register
r_char
op_star
id|p
suffix:semicolon
id|write_error
op_assign
id|buffercount
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_if
c_cond
(paren
id|is_read_only
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_logical_and
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
)paren
id|blocksize
op_assign
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
id|i
op_assign
id|blocksize
suffix:semicolon
id|blocksize_bits
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
l_int|1
)paren
(brace
id|blocksize_bits
op_increment
suffix:semicolon
id|i
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|block
op_assign
op_star
id|ppos
op_rshift
id|blocksize_bits
suffix:semicolon
id|offset
op_assign
op_star
id|ppos
op_amp
(paren
id|blocksize
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
)paren
id|size
op_assign
(paren
(paren
id|loff_t
)paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
op_lshift
id|BLOCK_SIZE_BITS
)paren
op_rshift
id|blocksize_bits
suffix:semicolon
r_else
id|size
op_assign
id|INT_MAX
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|block
op_ge
id|size
)paren
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|ENOSPC
suffix:semicolon
id|chars
op_assign
id|blocksize
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|chars
OG
id|count
)paren
id|chars
op_assign
id|count
suffix:semicolon
macro_line|#if 0
multiline_comment|/* get the buffer head */
(brace
r_struct
id|buffer_head
op_star
(paren
op_star
id|fn
)paren
(paren
id|kdev_t
comma
r_int
comma
r_int
)paren
op_assign
id|getblk
suffix:semicolon
r_if
c_cond
(paren
id|chars
op_ne
id|blocksize
)paren
id|fn
op_assign
id|bread
suffix:semicolon
id|bh
op_assign
id|fn
c_func
(paren
id|dev
comma
id|block
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
macro_line|#else
id|bh
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|block
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
id|chars
op_eq
id|blocksize
)paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_else
(brace
id|bhlist
(braket
l_int|0
)braket
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_reada
op_logical_or
op_logical_neg
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
)paren
(brace
multiline_comment|/* We do this to force the read of a single buffer */
id|blocks
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Read-ahead before write */
id|blocks
op_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_div
(paren
id|blocksize
op_rshift
l_int|9
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|block
op_plus
id|blocks
OG
id|size
)paren
id|blocks
op_assign
id|size
op_minus
id|block
suffix:semicolon
r_if
c_cond
(paren
id|blocks
OG
id|NBUF
)paren
id|blocks
op_assign
id|NBUF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocks
)paren
id|blocks
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bhlist
(braket
id|i
)braket
op_assign
id|getblk
(paren
id|dev
comma
id|block
op_plus
id|i
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bhlist
(braket
id|i
)braket
)paren
(brace
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bhlist
(braket
id|i
op_decrement
)braket
)paren
suffix:semicolon
)brace
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
)brace
)brace
id|ll_rw_block
c_func
(paren
id|READ
comma
id|blocks
comma
id|bhlist
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|bhlist
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
id|block
op_increment
suffix:semicolon
id|p
op_assign
id|offset
op_plus
id|bh-&gt;b_data
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
op_star
id|ppos
op_add_assign
id|chars
suffix:semicolon
id|written
op_add_assign
id|chars
suffix:semicolon
id|count
op_sub_assign
id|chars
suffix:semicolon
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|chars
)paren
suffix:semicolon
id|p
op_add_assign
id|chars
suffix:semicolon
id|buf
op_add_assign
id|chars
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_SYNC
)paren
id|bufferlist
(braket
id|buffercount
op_increment
)braket
op_assign
id|bh
suffix:semicolon
r_else
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffercount
op_eq
id|NBUF
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
id|buffercount
comma
id|bufferlist
)paren
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
id|buffercount
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wait_on_buffer
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
)paren
id|write_error
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|buffercount
op_assign
l_int|0
suffix:semicolon
)brace
id|balance_dirty
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_error
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffercount
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
id|buffercount
comma
id|bufferlist
)paren
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
id|buffercount
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wait_on_buffer
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
)paren
id|write_error
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bufferlist
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_error
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|written
suffix:semicolon
)brace
DECL|function|block_read
id|ssize_t
id|block_read
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|block
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
id|ssize_t
id|blocksize
suffix:semicolon
id|ssize_t
id|blocksize_bits
comma
id|i
suffix:semicolon
r_int
id|blocks
comma
id|rblocks
comma
id|left
suffix:semicolon
r_int
id|bhrequest
comma
id|uptodate
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
id|buflist
(braket
id|NBUF
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhreq
(braket
id|NBUF
)braket
suffix:semicolon
r_int
r_int
id|chars
suffix:semicolon
id|loff_t
id|size
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
id|blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_logical_and
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
)paren
id|blocksize
op_assign
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
id|i
op_assign
id|blocksize
suffix:semicolon
id|blocksize_bits
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
l_int|1
)paren
(brace
id|blocksize_bits
op_increment
suffix:semicolon
id|i
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|offset
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
)paren
id|size
op_assign
(paren
id|loff_t
)paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
op_lshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_else
id|size
op_assign
id|INT_MAX
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|size
)paren
id|left
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* size - offset might not fit into left, so check explicitly. */
r_else
r_if
c_cond
(paren
id|size
op_minus
id|offset
OG
id|INT_MAX
)paren
id|left
op_assign
id|INT_MAX
suffix:semicolon
r_else
id|left
op_assign
id|size
op_minus
id|offset
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
id|offset
op_rshift
id|blocksize_bits
suffix:semicolon
id|offset
op_and_assign
id|blocksize
op_minus
l_int|1
suffix:semicolon
id|size
op_rshift_assign
id|blocksize_bits
suffix:semicolon
id|rblocks
op_assign
id|blocks
op_assign
(paren
id|left
op_plus
id|offset
op_plus
id|blocksize
op_minus
l_int|1
)paren
op_rshift
id|blocksize_bits
suffix:semicolon
id|bhb
op_assign
id|bhe
op_assign
id|buflist
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_reada
)paren
(brace
r_if
c_cond
(paren
id|blocks
OL
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_div
(paren
id|blocksize
op_rshift
l_int|9
)paren
)paren
id|blocks
op_assign
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_div
(paren
id|blocksize
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rblocks
OG
id|blocks
)paren
id|blocks
op_assign
id|rblocks
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_plus
id|blocks
OG
id|size
)paren
(brace
id|blocks
op_assign
id|size
op_minus
id|block
suffix:semicolon
r_if
c_cond
(paren
id|blocks
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We do this in a two stage process.  We first try to request&n;&t;   as many blocks as we can, then we wait for the first one to&n;&t;   complete, and then we try to wrap up as many as are actually&n;&t;   done.  This routine is rather generic, in that it can be used&n;&t;   in a filesystem by substituting the appropriate function in&n;&t;   for getblk.&n;&n;&t;   This routine is optimized to make maximum use of the various&n;&t;   buffers and caches. */
r_do
(brace
id|bhrequest
op_assign
l_int|0
suffix:semicolon
id|uptodate
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|blocks
)paren
(brace
op_decrement
id|blocks
suffix:semicolon
op_star
id|bhb
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|block
op_increment
comma
id|blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bhb
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
op_star
id|bhb
)paren
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
r_break
suffix:semicolon
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
(brace
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
)brace
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
id|buffer_uptodate
c_func
(paren
op_star
id|bhe
)paren
)paren
(brace
multiline_comment|/* read error? */
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
id|blocksize
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
id|blocksize
op_minus
id|offset
suffix:semicolon
op_star
id|ppos
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
id|copy_to_user
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
id|left
OG
l_int|0
op_logical_and
id|bhe
op_ne
id|bhb
op_logical_and
(paren
op_logical_neg
op_star
id|bhe
op_logical_or
op_logical_neg
id|buffer_locked
c_func
(paren
op_star
id|bhe
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bhe
op_eq
id|bhb
op_logical_and
op_logical_neg
id|blocks
)paren
r_break
suffix:semicolon
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
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Filp may be NULL when we are called by an msync of a vma&n; *&t;since the vma has no handle.&n; */
DECL|function|block_fsync
r_static
r_int
id|block_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|fsync_dev
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * bdev cache handling - shamelessly stolen from inode.c&n; * We use smaller hashtable, though.&n; */
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS&t;6
DECL|macro|HASH_SIZE
mdefine_line|#define HASH_SIZE&t;(1UL &lt;&lt; HASH_BITS)
DECL|macro|HASH_MASK
mdefine_line|#define HASH_MASK&t;(HASH_SIZE-1)
DECL|variable|bdev_hashtable
r_static
r_struct
id|list_head
id|bdev_hashtable
(braket
id|HASH_SIZE
)braket
suffix:semicolon
DECL|variable|bdev_lock
r_static
id|spinlock_t
id|bdev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|bdev_cachep
r_static
id|kmem_cache_t
op_star
id|bdev_cachep
suffix:semicolon
DECL|macro|alloc_bdev
mdefine_line|#define alloc_bdev() &bslash;&n;&t; ((struct block_device *) kmem_cache_alloc(bdev_cachep, SLAB_KERNEL))
DECL|macro|destroy_bdev
mdefine_line|#define destroy_bdev(bdev) kmem_cache_free(bdev_cachep, (bdev))
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
(paren
r_struct
id|block_device
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
id|memset
c_func
(paren
id|bdev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|bdev
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|bdev_init
r_void
id|bdev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
id|bdev_hashtable
suffix:semicolon
id|i
op_assign
id|HASH_SIZE
suffix:semicolon
r_do
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|head
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
id|bdev_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bdev_cache&quot;
comma
r_sizeof
(paren
r_struct
id|block_device
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;cannot create bdev slab cache&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Most likely _very_ bad one - but then it&squot;s hardly critical for small&n; * /dev and can be fixed when somebody will need really large one.&n; */
DECL|function|hash
r_static
r_inline
r_int
r_int
id|hash
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|dev
suffix:semicolon
id|tmp
op_assign
id|tmp
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
)paren
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|tmp
op_amp
id|HASH_MASK
suffix:semicolon
)brace
DECL|function|bdfind
r_static
r_struct
id|block_device
op_star
id|bdfind
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head-&gt;next
suffix:semicolon
id|p
op_ne
id|head
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
id|bdev
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|block_device
comma
id|bd_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
suffix:semicolon
r_return
id|bdev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bdget
r_struct
id|block_device
op_star
id|bdget
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|head
op_assign
id|bdev_hashtable
op_plus
id|hash
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
comma
op_star
id|new_bdev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|bdev
op_assign
id|bdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
r_return
id|bdev
suffix:semicolon
id|new_bdev
op_assign
id|alloc_bdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_bdev
)paren
r_return
l_int|NULL
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|new_bdev-&gt;bd_count
comma
l_int|1
)paren
suffix:semicolon
id|new_bdev-&gt;bd_dev
op_assign
id|dev
suffix:semicolon
id|new_bdev-&gt;bd_op
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|bdev
op_assign
id|bdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|new_bdev-&gt;bd_hash
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_return
id|new_bdev
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|destroy_bdev
c_func
(paren
id|new_bdev
)paren
suffix:semicolon
r_return
id|bdev
suffix:semicolon
)brace
DECL|function|bdput
r_void
id|bdput
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|bdev-&gt;bd_openers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|bdev-&gt;bd_hash
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|destroy_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
)brace
)brace
r_static
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|bdops
r_struct
id|block_device_operations
op_star
id|bdops
suffix:semicolon
DECL|variable|blkdevs
)brace
id|blkdevs
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|function|get_blkdev_list
r_int
id|get_blkdev_list
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;nBlock devices:&bslash;n&quot;
)paren
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
id|MAX_BLKDEV
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|blkdevs
(braket
id|i
)braket
dot
id|bdops
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|p
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|i
comma
id|blkdevs
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Return the function table of a device.&n;&t;Load the driver if needed.&n;*/
DECL|function|get_blkfops
r_static
r_const
r_struct
id|block_device_operations
op_star
id|get_blkfops
c_func
(paren
r_int
r_int
id|major
)paren
(brace
r_const
r_struct
id|block_device_operations
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* major 0 is used for non-device mounts */
r_if
c_cond
(paren
id|major
op_logical_and
id|major
OL
id|MAX_BLKDEV
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
op_logical_neg
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
)paren
(brace
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;block-major-%d&quot;
comma
id|major
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|register_blkdev
r_int
id|register_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|block_device_operations
op_star
id|bdops
)paren
(brace
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|major
op_assign
id|MAX_BLKDEV
op_minus
l_int|1
suffix:semicolon
id|major
OG
l_int|0
suffix:semicolon
id|major
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_eq
l_int|NULL
)paren
(brace
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
id|bdops
suffix:semicolon
r_return
id|major
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_logical_and
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_ne
id|bdops
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
id|bdops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_blkdev
r_int
id|unregister_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|name
comma
id|name
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks whether a removable media has been changed,&n; * and invalidates all buffer-cache-entries in that case. This&n; * is a relatively slow routine, so we have to try to minimize using&n; * it. Thus it is called only upon a &squot;mount&squot; or &squot;open&squot;. This&n; * is the best way of combining speed and utility, I think.&n; * People changing diskettes in the middle of an operation deserve&n; * to lose :-)&n; */
DECL|function|check_disk_change
r_int
id|check_disk_change
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_struct
id|block_device_operations
op_star
id|bdops
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
id|i
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|MAX_BLKDEV
op_logical_or
(paren
id|bdops
op_assign
id|blkdevs
(braket
id|i
)braket
dot
id|bdops
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bdops-&gt;check_media_change
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdops
op_member_access_from_pointer
id|check_media_change
c_func
(paren
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;VFS: Disk change detected on device %s&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
op_logical_and
id|invalidate_inodes
c_func
(paren
id|sb
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: busy inodes on changed media.&bslash;n&quot;
)paren
suffix:semicolon
id|destroy_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdops-&gt;revalidate
)paren
id|bdops
op_member_access_from_pointer
id|revalidate
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ioctl_by_bdev
r_int
id|ioctl_by_bdev
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|kdev_t
id|rdev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
r_struct
id|inode
id|inode_fake
suffix:semicolon
r_int
id|res
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op-&gt;ioctl
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|inode_fake.i_rdev
op_assign
id|rdev
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|inode_fake.i_wait
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|res
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
op_amp
id|inode_fake
comma
l_int|NULL
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|blkdev_get
r_int
id|blkdev_get
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
id|mode_t
id|mode
comma
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|kdev_t
id|rdev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
multiline_comment|/* this should become bdev */
id|down
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op
)paren
id|bdev-&gt;bd_op
op_assign
id|get_blkfops
c_func
(paren
id|MAJOR
c_func
(paren
id|rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op
)paren
(brace
multiline_comment|/*&n;&t;&t; * This crockload is due to bad choice of -&gt;open() type.&n;&t;&t; * It will go away.&n;&t;&t; */
r_struct
id|file
id|fake_file
op_assign
(brace
)brace
suffix:semicolon
r_struct
id|dentry
id|fake_dentry
op_assign
(brace
)brace
suffix:semicolon
r_struct
id|inode
op_star
id|fake_inode
op_assign
id|get_empty_inode
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|fake_inode
)paren
(brace
id|fake_file.f_mode
op_assign
id|mode
suffix:semicolon
id|fake_file.f_flags
op_assign
id|flags
suffix:semicolon
id|fake_file.f_dentry
op_assign
op_amp
id|fake_dentry
suffix:semicolon
id|fake_dentry.d_inode
op_assign
id|fake_inode
suffix:semicolon
id|fake_inode-&gt;i_rdev
op_assign
id|rdev
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;open
)paren
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|open
c_func
(paren
id|fake_inode
comma
op_amp
id|fake_file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_openers
)paren
suffix:semicolon
id|iput
c_func
(paren
id|fake_inode
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|blkdev_open
r_int
id|blkdev_open
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
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
id|down
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op
)paren
id|bdev-&gt;bd_op
op_assign
id|get_blkfops
c_func
(paren
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;open
)paren
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_openers
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|blkdev_put
r_int
id|blkdev_put
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|kind
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|kdev_t
id|rdev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
multiline_comment|/* this should become bdev */
id|down
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
multiline_comment|/* syncing will go here */
r_if
c_cond
(paren
id|kind
op_eq
id|BDEV_FILE
op_logical_or
id|kind
op_eq
id|BDEV_FS
)paren
id|fsync_dev
c_func
(paren
id|rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|bdev-&gt;bd_openers
)paren
)paren
(brace
multiline_comment|/* invalidating buffers will go here */
id|invalidate_buffers
c_func
(paren
id|rdev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;release
)paren
(brace
r_struct
id|inode
op_star
id|fake_inode
op_assign
id|get_empty_inode
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|fake_inode
)paren
(brace
id|fake_inode-&gt;i_rdev
op_assign
id|rdev
suffix:semicolon
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|release
c_func
(paren
id|fake_inode
comma
l_int|NULL
)paren
suffix:semicolon
id|iput
c_func
(paren
id|fake_inode
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|bdev-&gt;bd_openers
)paren
)paren
id|bdev-&gt;bd_op
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* we can&squot;t rely on driver being */
multiline_comment|/* kind to stay around. */
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|blkdev_close
r_static
r_int
id|blkdev_close
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
r_return
id|blkdev_put
c_func
(paren
id|inode-&gt;i_bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
)brace
DECL|function|blkdev_ioctl
r_static
r_int
id|blkdev_ioctl
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_bdev-&gt;bd_op-&gt;ioctl
)paren
r_return
id|inode-&gt;i_bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|def_blk_fops
r_struct
id|file_operations
id|def_blk_fops
op_assign
(brace
id|open
suffix:colon
id|blkdev_open
comma
id|release
suffix:colon
id|blkdev_close
comma
id|read
suffix:colon
id|block_read
comma
id|write
suffix:colon
id|block_write
comma
id|fsync
suffix:colon
id|block_fsync
comma
id|ioctl
suffix:colon
id|blkdev_ioctl
comma
)brace
suffix:semicolon
DECL|variable|blkdev_inode_operations
r_struct
id|inode_operations
id|blkdev_inode_operations
op_assign
(brace
op_amp
id|def_blk_fops
comma
multiline_comment|/* default file operations */
)brace
suffix:semicolon
DECL|function|bdevname
r_const
r_char
op_star
id|bdevname
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|blkdevs
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
dot
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;unknown-block&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s(%d,%d)&quot;
comma
id|name
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
eof
