multiline_comment|/*&n; *  fs/partitions/ultrix.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *&n; *  Re-organised Jul 1999 Russell King&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;check.h&quot;
DECL|function|ultrix_partition
r_int
id|ultrix_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ultrix_disklabel
(brace
id|s32
id|pt_magic
suffix:semicolon
multiline_comment|/* magic no. indicating part. info exits */
id|s32
id|pt_valid
suffix:semicolon
multiline_comment|/* set by driver if pt is current */
r_struct
id|pt_info
(brace
id|s32
id|pi_nblocks
suffix:semicolon
multiline_comment|/* no. of sectors */
id|u32
id|pi_blkoff
suffix:semicolon
multiline_comment|/* block offset for start */
)brace
id|pt_part
(braket
l_int|8
)braket
suffix:semicolon
)brace
op_star
id|label
suffix:semicolon
DECL|macro|PT_MAGIC
mdefine_line|#define PT_MAGIC&t;0x032957&t;/* Partition magic number */
DECL|macro|PT_VALID
mdefine_line|#define PT_VALID&t;1&t;&t;/* Indicates if struct is valid */
DECL|macro|SBLOCK
mdefine_line|#define&t;SBLOCK&t;((unsigned long)((16384 - sizeof(struct ultrix_disklabel)) &bslash;&n;                  /get_ptable_blocksize(dev)))
id|bh
op_assign
id|bread
(paren
id|dev
comma
id|SBLOCK
comma
id|get_ptable_blocksize
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
id|bh
)paren
(brace
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
(paren
l_string|&quot; unable to read block 0x%lx&bslash;n&quot;
comma
id|SBLOCK
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|label
op_assign
(paren
r_struct
id|ultrix_disklabel
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_minus
r_sizeof
(paren
r_struct
id|ultrix_disklabel
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|label-&gt;pt_magic
op_eq
id|PT_MAGIC
op_logical_and
id|label-&gt;pt_valid
op_eq
id|PT_VALID
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|first_part_minor
op_increment
)paren
r_if
c_cond
(paren
id|label-&gt;pt_part
(braket
id|i
)braket
dot
id|pi_nblocks
)paren
id|add_gd_partition
c_func
(paren
id|hd
comma
id|first_part_minor
comma
id|label-&gt;pt_part
(braket
id|i
)braket
dot
id|pi_blkoff
comma
id|label-&gt;pt_part
(braket
id|i
)braket
dot
id|pi_nblocks
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
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
)brace
eof
