multiline_comment|/*&n; *  linux/fs/block_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
id|chars
op_ne
id|blocksize
op_logical_and
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
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
comma
id|blocksize
)paren
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
id|bhlist
(braket
l_int|0
)braket
op_assign
id|bh
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
suffix:semicolon
)brace
suffix:semicolon
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
)brace
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
id|block
op_increment
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
r_if
c_cond
(paren
id|write_error
)paren
(brace
r_break
suffix:semicolon
)brace
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
eof
