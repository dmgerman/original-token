multiline_comment|/*&n; *  linux/kernel/blk_drv/ramdisk.c&n; *&n; *  Written by Theodore Ts&squot;o, 12/2/91&n; *&n; * Modifications by Fred N. van Kempen to allow for bootable root&n; * disks (which are used in LINUX/Pro).  Also some cleanups.  03/03/93&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR  MEM_MAJOR
macro_line|#include &quot;blk.h&quot;
DECL|macro|RAMDISK_MINOR
mdefine_line|#define RAMDISK_MINOR&t;1
r_extern
r_void
id|wait_for_keypress
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rd_start
r_char
op_star
id|rd_start
suffix:semicolon
DECL|variable|rd_length
r_int
id|rd_length
op_assign
l_int|0
suffix:semicolon
DECL|variable|rd_blocksizes
r_static
r_int
id|rd_blocksizes
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|do_rd_request
r_static
r_void
id|do_rd_request
c_func
(paren
r_void
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|repeat
suffix:colon
id|INIT_REQUEST
suffix:semicolon
id|addr
op_assign
id|rd_start
op_plus
(paren
id|CURRENT-&gt;sector
op_lshift
l_int|9
)paren
suffix:semicolon
id|len
op_assign
id|CURRENT-&gt;current_nr_sectors
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
(paren
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
op_ne
id|RAMDISK_MINOR
)paren
op_logical_or
(paren
id|addr
op_plus
id|len
OG
id|rd_start
op_plus
id|rd_length
)paren
)paren
(brace
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
r_if
c_cond
(paren
id|CURRENT
op_member_access_from_pointer
id|cmd
op_eq
id|WRITE
)paren
(brace
(paren
r_void
)paren
id|memcpy
c_func
(paren
id|addr
comma
id|CURRENT-&gt;buffer
comma
id|len
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|READ
)paren
(brace
(paren
r_void
)paren
id|memcpy
c_func
(paren
id|CURRENT-&gt;buffer
comma
id|addr
comma
id|len
)paren
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;RAMDISK: unknown RAM disk command !&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
DECL|variable|rd_fops
r_static
r_struct
id|file_operations
id|rd_fops
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
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
id|block_fsync
multiline_comment|/* fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * Returns amount of memory which needs to be reserved.&n; */
DECL|function|rd_init
r_int
id|rd_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|length
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|MEM_MAJOR
comma
l_string|&quot;rd&quot;
comma
op_amp
id|rd_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: Unable to get major %d.&bslash;n&quot;
comma
id|MEM_MAJOR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|blk_dev
(braket
id|MEM_MAJOR
)braket
dot
id|request_fn
op_assign
id|DEVICE_REQUEST
suffix:semicolon
id|rd_start
op_assign
(paren
r_char
op_star
)paren
id|mem_start
suffix:semicolon
id|rd_length
op_assign
id|length
suffix:semicolon
id|cp
op_assign
id|rd_start
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
id|length
suffix:semicolon
id|i
op_increment
)paren
op_star
id|cp
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rd_blocksizes
(braket
id|i
)braket
op_assign
l_int|1024
suffix:semicolon
)brace
id|blksize_size
(braket
id|MAJOR_NR
)braket
op_assign
id|rd_blocksizes
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|do_load
r_static
r_void
id|do_load
c_func
(paren
r_void
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|super_block
(brace
r_union
(brace
r_char
id|minix
(braket
r_sizeof
(paren
r_struct
id|minix_super_block
)paren
)braket
suffix:semicolon
r_char
id|ext2
(braket
r_sizeof
(paren
r_struct
id|ext2_super_block
)paren
)braket
suffix:semicolon
)brace
id|record
suffix:semicolon
)brace
id|sb
suffix:semicolon
r_struct
id|minix_super_block
op_star
id|minixsb
op_assign
(paren
r_struct
id|minix_super_block
op_star
)paren
op_amp
id|sb
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|ext2sb
op_assign
(paren
r_struct
id|ext2_super_block
op_star
)paren
op_amp
id|sb
suffix:semicolon
r_int
id|block
comma
id|tries
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_int
id|nblocks
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
multiline_comment|/*&n;&t; * Check for a super block on the diskette.&n;&t; * The old-style boot/root diskettes had their RAM image&n;&t; * starting at block 512 of the boot diskette.  LINUX/Pro&n;&t; * uses the entire diskette as a file system, so in that&n;&t; * case, we have to look at block 0.  Be intelligent about&n;&t; * this, and check both... - FvK&n;&t; */
r_for
c_loop
(paren
id|tries
op_assign
l_int|0
suffix:semicolon
id|tries
OL
l_int|1000
suffix:semicolon
id|tries
op_add_assign
l_int|512
)paren
(brace
id|block
op_assign
id|tries
suffix:semicolon
id|bh
op_assign
id|breada
c_func
(paren
id|ROOT_DEV
comma
id|block
op_plus
l_int|1
comma
id|BLOCK_SIZE
comma
l_int|0
comma
id|PAGE_SIZE
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
l_string|&quot;RAMDISK: I/O error while looking for super block!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This is silly- why do we require it to be a MINIX FS? */
op_star
(paren
(paren
r_struct
id|super_block
op_star
)paren
op_amp
id|sb
)paren
op_assign
op_star
(paren
(paren
r_struct
id|super_block
op_star
)paren
id|bh-&gt;b_data
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* Try Minix */
id|nblocks
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minixsb-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC
op_logical_or
id|minixsb-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: Minix filesystem found at block %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|nblocks
op_assign
id|minixsb-&gt;s_nzones
op_lshift
id|minixsb-&gt;s_log_zone_size
suffix:semicolon
)brace
multiline_comment|/* Try ext2 */
r_if
c_cond
(paren
id|nblocks
op_eq
op_minus
l_int|1
op_logical_and
(paren
id|ext2sb-&gt;s_magic
op_eq
id|EXT2_PRE_02B_MAGIC
op_logical_or
id|ext2sb-&gt;s_magic
op_eq
id|EXT2_SUPER_MAGIC
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: Ext2 filesystem found at block %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|nblocks
op_assign
id|ext2sb-&gt;s_blocks_count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nblocks
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: trying old-style RAM image.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nblocks
OG
(paren
id|rd_length
op_rshift
id|BLOCK_SIZE_BITS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: image too big! (%d/%d blocks)&bslash;n&quot;
comma
id|nblocks
comma
id|rd_length
op_rshift
id|BLOCK_SIZE_BITS
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: Loading %d blocks into RAM disk&quot;
comma
id|nblocks
)paren
suffix:semicolon
multiline_comment|/* We found an image file system.  Load it into core! */
id|cp
op_assign
id|rd_start
suffix:semicolon
r_while
c_loop
(paren
id|nblocks
)paren
(brace
r_if
c_cond
(paren
id|nblocks
OG
l_int|2
)paren
id|bh
op_assign
id|breada
c_func
(paren
id|ROOT_DEV
comma
id|block
comma
id|BLOCK_SIZE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_else
id|bh
op_assign
id|bread
c_func
(paren
id|ROOT_DEV
comma
id|block
comma
id|BLOCK_SIZE
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
l_string|&quot;RAMDISK: I/O error on block %d, aborting!&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
(paren
r_void
)paren
id|memcpy
c_func
(paren
id|cp
comma
id|bh-&gt;b_data
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nblocks
op_decrement
op_amp
l_int|15
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|cp
op_add_assign
id|BLOCK_SIZE
suffix:semicolon
id|block
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;ndone&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* We loaded the file system image.  Prepare for mounting it. */
id|ROOT_DEV
op_assign
(paren
(paren
id|MEM_MAJOR
op_lshift
l_int|8
)paren
op_or
id|RAMDISK_MINOR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * If the root device is the RAM disk, try to load it.&n; * In order to do this, the root device is originally set to the&n; * floppy, and we later change it to be RAM disk.&n; */
DECL|function|rd_load
r_void
id|rd_load
c_func
(paren
r_void
)paren
(brace
r_struct
id|inode
id|inode
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
multiline_comment|/* If no RAM disk specified, give up early. */
r_if
c_cond
(paren
op_logical_neg
id|rd_length
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RAMDISK: %d bytes, starting at 0x%p&bslash;n&quot;
comma
id|rd_length
comma
id|rd_start
)paren
suffix:semicolon
multiline_comment|/* If we are doing a diskette boot, we might have to pre-load it. */
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_ne
id|FLOPPY_MAJOR
)paren
r_return
suffix:semicolon
multiline_comment|/* for Slackware install disks */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;VFS: Insert ramdisk floppy and press ENTER&bslash;n&quot;
)paren
suffix:semicolon
id|wait_for_keypress
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|filp
comma
l_int|0
comma
r_sizeof
(paren
id|filp
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|inode
comma
l_int|0
comma
r_sizeof
(paren
id|inode
)paren
)paren
suffix:semicolon
id|inode.i_rdev
op_assign
id|ROOT_DEV
suffix:semicolon
id|filp.f_mode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* read only */
id|filp.f_inode
op_assign
op_amp
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|blkdev_open
c_func
(paren
op_amp
id|inode
comma
op_amp
id|filp
)paren
op_eq
l_int|0
)paren
(brace
id|do_load
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp.f_op
op_logical_and
id|filp.f_op-&gt;release
)paren
(brace
id|filp.f_op
op_member_access_from_pointer
id|release
c_func
(paren
op_amp
id|inode
comma
op_amp
id|filp
)paren
suffix:semicolon
)brace
)brace
)brace
eof
