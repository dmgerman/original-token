multiline_comment|/*&n; *  linux/drivers/block/loop.c&n; *&n; *  Written by Theodore Ts&squot;o, 3/29/93&n; * &n; * Copyright 1993 by Theodore Ts&squot;o.  Redistribution of this file is&n; * permitted under the GNU Public License.&n; *&n; * more DES encryption plus IDEA encryption by Nicholas J. Leon, June 20, 1996&n; * DES encryption plus some minor changes by Werner Almesberger, 30-MAY-1993&n; *&n; * Modularized and updated for 1.1.16 kernel - Mitch Dsouza 28th May 1994&n; *&n; * Adapted for 1.3.59 kernel - Andries Brouwer, 1 Feb 1996&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_LOOP_DES
macro_line|#include &lt;linux/des.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_LOOP_IDEA
macro_line|#include &lt;linux/idea.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/loop.h&gt;&t;&t;/* must follow des.h */
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR LOOP_MAJOR
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;loop&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_lo_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (MINOR(device))
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device)
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device)
DECL|macro|DEVICE_NO_RANDOM
mdefine_line|#define DEVICE_NO_RANDOM
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (6 * HZ)
macro_line|#include &lt;linux/blk.h&gt;
DECL|macro|MAX_LOOP
mdefine_line|#define MAX_LOOP 8
DECL|variable|loop_dev
r_static
r_struct
id|loop_device
id|loop_dev
(braket
id|MAX_LOOP
)braket
suffix:semicolon
DECL|variable|loop_sizes
r_static
r_int
id|loop_sizes
(braket
id|MAX_LOOP
)braket
suffix:semicolon
DECL|variable|loop_blksizes
r_static
r_int
id|loop_blksizes
(braket
id|MAX_LOOP
)braket
suffix:semicolon
multiline_comment|/*&n; * Transfer functions&n; */
DECL|function|transfer_none
r_static
r_int
id|transfer_none
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
id|memcpy
c_func
(paren
id|loop_buf
comma
id|raw_buf
comma
id|size
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|raw_buf
comma
id|loop_buf
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|transfer_xor
r_static
r_int
id|transfer_xor
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
)paren
(brace
r_char
op_star
id|in
comma
op_star
id|out
comma
op_star
id|key
suffix:semicolon
r_int
id|i
comma
id|keysize
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|in
op_assign
id|raw_buf
suffix:semicolon
id|out
op_assign
id|loop_buf
suffix:semicolon
)brace
r_else
(brace
id|in
op_assign
id|loop_buf
suffix:semicolon
id|out
op_assign
id|raw_buf
suffix:semicolon
)brace
id|key
op_assign
id|lo-&gt;lo_encrypt_key
suffix:semicolon
id|keysize
op_assign
id|lo-&gt;lo_encrypt_key_size
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
id|size
suffix:semicolon
id|i
op_increment
)paren
op_star
id|out
op_increment
op_assign
op_star
id|in
op_increment
op_xor
id|key
(braket
(paren
id|i
op_amp
l_int|511
)paren
op_mod
id|keysize
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DES_AVAILABLE
DECL|function|transfer_des
r_static
r_int
id|transfer_des
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|tmp
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|x0
comma
id|x1
comma
id|p0
comma
id|p1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_amp
l_int|7
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|x0
op_assign
id|lo-&gt;lo_des_init
(braket
l_int|0
)braket
suffix:semicolon
id|x1
op_assign
id|lo-&gt;lo_des_init
(braket
l_int|1
)braket
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|tmp
(braket
l_int|0
)braket
op_assign
(paren
id|p0
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|0
)braket
)paren
op_xor
id|x0
suffix:semicolon
id|tmp
(braket
l_int|1
)braket
op_assign
(paren
id|p1
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|1
)braket
)paren
op_xor
id|x1
suffix:semicolon
id|des_ecb_encrypt
c_func
(paren
(paren
id|des_cblock
op_star
)paren
id|tmp
comma
(paren
id|des_cblock
op_star
)paren
id|loop_buf
comma
id|lo-&gt;lo_des_key
comma
id|DES_ENCRYPT
)paren
suffix:semicolon
id|x0
op_assign
id|p0
op_xor
(paren
(paren
r_int
r_int
op_star
)paren
id|loop_buf
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|x1
op_assign
id|p1
op_xor
(paren
(paren
r_int
r_int
op_star
)paren
id|loop_buf
)paren
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
id|p0
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|loop_buf
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|p1
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|loop_buf
)paren
(braket
l_int|1
)braket
suffix:semicolon
id|des_ecb_encrypt
c_func
(paren
(paren
id|des_cblock
op_star
)paren
id|loop_buf
comma
(paren
id|des_cblock
op_star
)paren
id|raw_buf
comma
id|lo-&gt;lo_des_key
comma
id|DES_DECRYPT
)paren
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|0
)braket
op_xor_assign
id|x0
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|1
)braket
op_xor_assign
id|x1
suffix:semicolon
id|x0
op_assign
id|p0
op_xor
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|x1
op_assign
id|p1
op_xor
(paren
(paren
r_int
r_int
op_star
)paren
id|raw_buf
)paren
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|size
op_sub_assign
l_int|8
suffix:semicolon
id|raw_buf
op_add_assign
l_int|8
suffix:semicolon
id|loop_buf
op_add_assign
l_int|8
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef IDEA_AVAILABLE
r_extern
r_void
id|idea_encrypt_block
c_func
(paren
id|idea_key
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|transfer_idea
r_static
r_int
id|transfer_idea
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|READ
)paren
(brace
id|idea_encrypt_block
c_func
(paren
id|lo-&gt;lo_idea_en_key
comma
id|raw_buf
comma
id|loop_buf
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|idea_encrypt_block
c_func
(paren
id|lo-&gt;lo_idea_de_key
comma
id|loop_buf
comma
id|raw_buf
comma
id|size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|xfer_funcs
r_static
id|transfer_proc_t
id|xfer_funcs
(braket
id|MAX_LOOP
)braket
op_assign
(brace
id|transfer_none
comma
multiline_comment|/* LO_CRYPT_NONE */
id|transfer_xor
comma
multiline_comment|/* LO_CRYPT_XOR */
macro_line|#ifdef DES_AVAILABLE
id|transfer_des
comma
multiline_comment|/* LO_CRYPT_DES */
macro_line|#else
l_int|NULL
comma
multiline_comment|/* LO_CRYPT_DES */
macro_line|#endif
macro_line|#ifdef IDEA_AVAILABLE           /* LO_CRYPT_IDEA */
id|transfer_idea
macro_line|#else
l_int|NULL
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|MAX_DISK_SIZE
mdefine_line|#define MAX_DISK_SIZE 1024*1024*1024
DECL|function|figure_loop_size
r_static
r_void
id|figure_loop_size
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
)paren
(brace
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|lo-&gt;lo_inode-&gt;i_mode
)paren
)paren
id|size
op_assign
(paren
id|lo-&gt;lo_inode-&gt;i_size
op_minus
id|lo-&gt;lo_offset
)paren
op_div
id|BLOCK_SIZE
suffix:semicolon
r_else
(brace
id|kdev_t
id|lodev
op_assign
id|lo-&gt;lo_device
suffix:semicolon
r_if
c_cond
(paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|lodev
)paren
)braket
)paren
id|size
op_assign
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|lodev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|lodev
)paren
)braket
op_minus
id|lo-&gt;lo_offset
op_div
id|BLOCK_SIZE
suffix:semicolon
r_else
id|size
op_assign
id|MAX_DISK_SIZE
suffix:semicolon
)brace
id|loop_sizes
(braket
id|lo-&gt;lo_number
)braket
op_assign
id|size
suffix:semicolon
)brace
DECL|function|do_lo_request
r_static
r_void
id|do_lo_request
c_func
(paren
r_void
)paren
(brace
r_int
id|real_block
comma
id|block
comma
id|offset
comma
id|len
comma
id|blksize
comma
id|size
suffix:semicolon
r_char
op_star
id|dest_addr
suffix:semicolon
r_struct
id|loop_device
op_star
id|lo
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|repeat
suffix:colon
id|INIT_REQUEST
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|CURRENT-&gt;rq_dev
)paren
op_ge
id|MAX_LOOP
)paren
r_goto
id|error_out
suffix:semicolon
id|lo
op_assign
op_amp
id|loop_dev
(braket
id|MINOR
c_func
(paren
id|CURRENT-&gt;rq_dev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;lo_inode
op_logical_or
op_logical_neg
id|lo-&gt;transfer
)paren
r_goto
id|error_out
suffix:semicolon
id|blksize
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
id|lo-&gt;lo_device
)paren
)braket
)paren
(brace
id|blksize
op_assign
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|lo-&gt;lo_device
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|lo-&gt;lo_device
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blksize
)paren
id|blksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
)brace
id|dest_addr
op_assign
id|CURRENT-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
id|blksize
OL
l_int|512
)paren
(brace
id|block
op_assign
id|CURRENT-&gt;sector
op_star
(paren
l_int|512
op_div
id|blksize
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|block
op_assign
id|CURRENT-&gt;sector
op_div
(paren
id|blksize
op_rshift
l_int|9
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|CURRENT-&gt;sector
op_mod
(paren
id|blksize
op_rshift
l_int|9
)paren
)paren
op_lshift
l_int|9
suffix:semicolon
)brace
id|block
op_add_assign
id|lo-&gt;lo_offset
op_div
id|blksize
suffix:semicolon
id|offset
op_add_assign
id|lo-&gt;lo_offset
op_mod
id|blksize
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|blksize
)paren
(brace
id|block
op_increment
suffix:semicolon
id|offset
op_sub_assign
id|blksize
suffix:semicolon
)brace
id|len
op_assign
id|CURRENT-&gt;current_nr_sectors
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|WRITE
)paren
(brace
r_if
c_cond
(paren
id|lo-&gt;lo_flags
op_amp
id|LO_FLAGS_READ_ONLY
)paren
r_goto
id|error_out
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_ne
id|READ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unknown loop device command (%d)?!?&quot;
comma
id|CURRENT-&gt;cmd
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|real_block
op_assign
id|block
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;lo_flags
op_amp
id|LO_FLAGS_DO_BMAP
)paren
(brace
id|real_block
op_assign
id|bmap
c_func
(paren
id|lo-&gt;lo_inode
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|real_block
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;loop: block %d not present&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
)brace
id|bh
op_assign
id|getblk
c_func
(paren
id|lo-&gt;lo_device
comma
id|real_block
comma
id|blksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;loop: device %s: getblk(-, %d, %d) returned NULL&quot;
comma
id|kdevname
c_func
(paren
id|lo-&gt;lo_device
)paren
comma
id|block
comma
id|blksize
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_logical_and
(paren
(paren
id|CURRENT-&gt;cmd
op_eq
id|READ
)paren
op_logical_or
(paren
id|offset
op_logical_or
(paren
id|len
OL
id|blksize
)paren
)paren
)paren
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
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
r_goto
id|error_out
suffix:semicolon
)brace
)brace
id|size
op_assign
id|blksize
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|len
)paren
id|size
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lo-&gt;transfer
)paren
(paren
id|lo
comma
id|CURRENT-&gt;cmd
comma
id|bh-&gt;b_data
op_plus
id|offset
comma
id|dest_addr
comma
id|size
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;loop: transfer error block %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|WRITE
)paren
(brace
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
l_int|1
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|dest_addr
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
id|error_out
suffix:colon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
DECL|function|loop_set_fd
r_static
r_int
id|loop_set_fd
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|arg
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;lo_inode
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_inode
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
l_string|&quot;loop_set_fd: NULL inode?!?&bslash;n&quot;
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
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_int
id|error
op_assign
id|blkdev_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|lo-&gt;lo_device
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
id|lo-&gt;lo_flags
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|lo-&gt;lo_device
op_assign
id|inode-&gt;i_dev
suffix:semicolon
id|lo-&gt;lo_flags
op_assign
id|LO_FLAGS_DO_BMAP
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
(paren
id|inode
)paren
op_logical_or
id|is_read_only
c_func
(paren
id|lo-&gt;lo_device
)paren
)paren
(brace
id|lo-&gt;lo_flags
op_or_assign
id|LO_FLAGS_READ_ONLY
suffix:semicolon
id|set_device_ro
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|invalidate_inode_pages
(paren
id|inode
)paren
suffix:semicolon
id|set_device_ro
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
)brace
id|lo-&gt;lo_inode
op_assign
id|inode
suffix:semicolon
id|lo-&gt;lo_inode-&gt;i_count
op_increment
suffix:semicolon
id|lo-&gt;transfer
op_assign
l_int|NULL
suffix:semicolon
id|figure_loop_size
c_func
(paren
id|lo
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|loop_clr_fd
r_static
r_int
id|loop_clr_fd
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
id|kdev_t
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;lo_inode
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;lo_refcnt
OG
l_int|1
)paren
multiline_comment|/* we needed one fd for the ioctl */
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|lo-&gt;lo_inode-&gt;i_mode
)paren
)paren
id|blkdev_release
(paren
id|lo-&gt;lo_inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|lo-&gt;lo_inode
)paren
suffix:semicolon
id|lo-&gt;lo_device
op_assign
l_int|0
suffix:semicolon
id|lo-&gt;lo_inode
op_assign
l_int|NULL
suffix:semicolon
id|lo-&gt;lo_encrypt_type
op_assign
l_int|0
suffix:semicolon
id|lo-&gt;lo_offset
op_assign
l_int|0
suffix:semicolon
id|lo-&gt;lo_encrypt_key_size
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|lo-&gt;lo_encrypt_key
comma
l_int|0
comma
id|LO_KEY_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
id|lo-&gt;lo_name
comma
l_int|0
comma
id|LO_NAME_SIZE
)paren
suffix:semicolon
id|loop_sizes
(braket
id|lo-&gt;lo_number
)braket
op_assign
l_int|0
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|loop_set_status
r_static
r_int
id|loop_set_status
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_struct
id|loop_info
op_star
id|arg
)paren
(brace
r_struct
id|loop_info
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;lo_inode
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|arg
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|info
comma
id|arg
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|info.lo_encrypt_key_size
OG
id|LO_KEY_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|info.lo_encrypt_type
)paren
(brace
r_case
id|LO_CRYPT_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|LO_CRYPT_XOR
suffix:colon
r_if
c_cond
(paren
id|info.lo_encrypt_key_size
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef DES_AVAILABLE
r_case
id|LO_CRYPT_DES
suffix:colon
r_if
c_cond
(paren
id|info.lo_encrypt_key_size
op_ne
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|des_set_key
c_func
(paren
(paren
id|des_cblock
op_star
)paren
id|lo-&gt;lo_encrypt_key
comma
id|lo-&gt;lo_des_key
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|lo-&gt;lo_des_init
comma
id|info.lo_init
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef IDEA_AVAILABLE
r_case
id|LO_CRYPT_IDEA
suffix:colon
(brace
id|uint16
id|tmpkey
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info.lo_encrypt_key_size
op_ne
id|IDEAKEYSIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* create key in lo-&gt; from info.lo_encrypt_key */
id|memcpy
c_func
(paren
id|tmpkey
comma
id|info.lo_encrypt_key
comma
r_sizeof
(paren
id|tmpkey
)paren
)paren
suffix:semicolon
id|en_key_idea
c_func
(paren
id|tmpkey
comma
id|lo-&gt;lo_idea_en_key
)paren
suffix:semicolon
id|de_key_idea
c_func
(paren
id|lo-&gt;lo_idea_en_key
comma
id|lo-&gt;lo_idea_de_key
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|lo-&gt;lo_offset
op_assign
id|info.lo_offset
suffix:semicolon
id|strncpy
c_func
(paren
id|lo-&gt;lo_name
comma
id|info.lo_name
comma
id|LO_NAME_SIZE
)paren
suffix:semicolon
id|lo-&gt;lo_encrypt_type
op_assign
id|info.lo_encrypt_type
suffix:semicolon
id|lo-&gt;transfer
op_assign
id|xfer_funcs
(braket
id|lo-&gt;lo_encrypt_type
)braket
suffix:semicolon
id|lo-&gt;lo_encrypt_key_size
op_assign
id|info.lo_encrypt_key_size
suffix:semicolon
r_if
c_cond
(paren
id|info.lo_encrypt_key_size
)paren
id|memcpy
c_func
(paren
id|lo-&gt;lo_encrypt_key
comma
id|info.lo_encrypt_key
comma
id|info.lo_encrypt_key_size
)paren
suffix:semicolon
id|figure_loop_size
c_func
(paren
id|lo
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|loop_get_status
r_static
r_int
id|loop_get_status
c_func
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_struct
id|loop_info
op_star
id|arg
)paren
(brace
r_struct
id|loop_info
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;lo_inode
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|arg
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.lo_number
op_assign
id|lo-&gt;lo_number
suffix:semicolon
id|info.lo_device
op_assign
id|kdev_t_to_nr
c_func
(paren
id|lo-&gt;lo_inode-&gt;i_dev
)paren
suffix:semicolon
id|info.lo_inode
op_assign
id|lo-&gt;lo_inode-&gt;i_ino
suffix:semicolon
id|info.lo_rdevice
op_assign
id|kdev_t_to_nr
c_func
(paren
id|lo-&gt;lo_device
)paren
suffix:semicolon
id|info.lo_offset
op_assign
id|lo-&gt;lo_offset
suffix:semicolon
id|info.lo_flags
op_assign
id|lo-&gt;lo_flags
suffix:semicolon
id|strncpy
c_func
(paren
id|info.lo_name
comma
id|lo-&gt;lo_name
comma
id|LO_NAME_SIZE
)paren
suffix:semicolon
id|info.lo_encrypt_type
op_assign
id|lo-&gt;lo_encrypt_type
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;lo_encrypt_key_size
op_logical_and
id|suser
c_func
(paren
)paren
)paren
(brace
id|info.lo_encrypt_key_size
op_assign
id|lo-&gt;lo_encrypt_key_size
suffix:semicolon
id|memcpy
c_func
(paren
id|info.lo_encrypt_key
comma
id|lo-&gt;lo_encrypt_key
comma
id|lo-&gt;lo_encrypt_key_size
)paren
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lo_ioctl
r_static
r_int
id|lo_ioctl
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|loop_device
op_star
id|lo
suffix:semicolon
r_int
id|dev
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ne
id|MAJOR_NR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lo_ioctl: pseudo-major != %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_LOOP
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|lo
op_assign
op_amp
id|loop_dev
(braket
id|dev
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|LOOP_SET_FD
suffix:colon
r_return
id|loop_set_fd
c_func
(paren
id|lo
comma
id|inode-&gt;i_rdev
comma
id|arg
)paren
suffix:semicolon
r_case
id|LOOP_CLR_FD
suffix:colon
r_return
id|loop_clr_fd
c_func
(paren
id|lo
comma
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_case
id|LOOP_SET_STATUS
suffix:colon
r_return
id|loop_set_status
c_func
(paren
id|lo
comma
(paren
r_struct
id|loop_info
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|LOOP_GET_STATUS
suffix:colon
r_return
id|loop_get_status
c_func
(paren
id|lo
comma
(paren
r_struct
id|loop_info
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKGETSIZE
suffix:colon
multiline_comment|/* Return device size */
r_if
c_cond
(paren
op_logical_neg
id|lo-&gt;lo_inode
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|put_fs_long
c_func
(paren
id|loop_sizes
(braket
id|lo-&gt;lo_number
)braket
op_lshift
l_int|1
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lo_open
r_static
r_int
id|lo_open
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
id|loop_device
op_star
id|lo
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ne
id|MAJOR_NR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lo_open: pseudo-major != %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_LOOP
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|lo
op_assign
op_amp
id|loop_dev
(braket
id|dev
)braket
suffix:semicolon
id|lo-&gt;lo_refcnt
op_increment
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lo_release
r_static
r_void
id|lo_release
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
id|loop_device
op_star
id|lo
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ne
id|MAJOR_NR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lo_release: pseudo-major != %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_LOOP
)paren
r_return
suffix:semicolon
id|fsync_dev
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|lo
op_assign
op_amp
id|loop_dev
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|lo-&gt;lo_refcnt
op_le
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;lo_release: refcount(%d) &lt;= 0&bslash;n&quot;
comma
id|lo-&gt;lo_refcnt
)paren
suffix:semicolon
r_else
(brace
id|lo-&gt;lo_refcnt
op_decrement
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
DECL|variable|lo_fops
r_static
r_struct
id|file_operations
id|lo_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|block_read
comma
multiline_comment|/* read - general block-dev read */
id|block_write
comma
multiline_comment|/* write - general block-dev write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select */
id|lo_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|lo_open
comma
multiline_comment|/* open */
id|lo_release
multiline_comment|/* release */
)brace
suffix:semicolon
multiline_comment|/*&n; * And now the modules code and kernel interface.&n; */
macro_line|#ifdef MODULE
DECL|macro|loop_init
mdefine_line|#define loop_init init_module
macro_line|#endif
r_int
DECL|function|loop_init
id|loop_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;loop&quot;
comma
op_amp
id|lo_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to get major number %d for loop device&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifndef MODULE
id|printk
c_func
(paren
l_string|&quot;loop: registered device at major %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
macro_line|#ifdef DES_AVAILABLE
id|printk
c_func
(paren
l_string|&quot;loop: DES encryption available&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef IDEA_AVAILABLE
id|printk
c_func
(paren
l_string|&quot;loop: IDEA encryption available&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
id|blk_dev
(braket
id|MAJOR_NR
)braket
dot
id|request_fn
op_assign
id|DEVICE_REQUEST
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
id|MAX_LOOP
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
op_amp
id|loop_dev
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|loop_device
)paren
)paren
suffix:semicolon
id|loop_dev
(braket
id|i
)braket
dot
id|lo_number
op_assign
id|i
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|loop_sizes
comma
l_int|0
comma
r_sizeof
(paren
id|loop_sizes
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|loop_blksizes
comma
l_int|0
comma
r_sizeof
(paren
id|loop_blksizes
)paren
)paren
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|loop_sizes
suffix:semicolon
id|blksize_size
(braket
id|MAJOR_NR
)braket
op_assign
id|loop_blksizes
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|unregister_blkdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;loop&quot;
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;loop: cleanup_module failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
