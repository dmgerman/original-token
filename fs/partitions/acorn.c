multiline_comment|/*&n; * linux/arch/arm/drivers/block/adfspart.c&n; *&n; * Copyright (c) 1996,1997 Russell King.&n; *&n; * Scan ADFS partitions on hard disk drives.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;acorn.h&quot;
r_static
r_void
DECL|function|adfspart_setgeometry
id|adfspart_setgeometry
c_func
(paren
id|kdev_t
id|dev
comma
r_int
r_int
id|secspertrack
comma
r_int
r_int
id|heads
comma
r_int
r_int
id|totalblocks
)paren
(brace
r_extern
r_void
id|xd_set_geometry
c_func
(paren
id|kdev_t
id|dev
comma
r_int
r_char
comma
r_int
r_char
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_MFM
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_eq
id|MFM_ACORN_MAJOR
)paren
id|xd_set_geometry
c_func
(paren
id|dev
comma
id|secspertrack
comma
id|heads
comma
id|totalblocks
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|LINUX_NATIVE_MAGIC
mdefine_line|#define LINUX_NATIVE_MAGIC 0xdeafa1de
DECL|macro|LINUX_SWAP_MAGIC
mdefine_line|#define LINUX_SWAP_MAGIC   0xdeafab1e
DECL|struct|linux_part
r_struct
id|linux_part
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
)brace
suffix:semicolon
DECL|function|adfs_partition
r_static
r_struct
id|adfs_discrecord
op_star
id|adfs_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_char
op_star
id|name
comma
r_char
op_star
id|data
comma
r_int
r_int
id|first_sector
comma
r_int
r_int
id|minor
)paren
(brace
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_int
r_int
id|nr_sects
suffix:semicolon
r_if
c_cond
(paren
id|adfs_checkbblk
c_func
(paren
id|data
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|dr
op_assign
(paren
r_struct
id|adfs_discrecord
op_star
)paren
(paren
id|data
op_plus
l_int|0x1c0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dr-&gt;disc_size
op_eq
l_int|0
op_logical_and
id|dr-&gt;disc_size_high
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|nr_sects
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size_high
)paren
op_lshift
l_int|23
)paren
op_or
(paren
id|le32_to_cpu
c_func
(paren
id|dr-&gt;disc_size
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|printk
c_func
(paren
l_string|&quot; [%s]&quot;
comma
id|name
)paren
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|first_sector
comma
id|nr_sects
)paren
suffix:semicolon
r_return
id|dr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
DECL|function|riscix_partition
r_static
r_int
id|riscix_partition
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
id|first_sect
comma
r_int
r_int
id|minor
comma
r_int
r_int
id|nr_sects
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|riscix_record
op_star
id|rr
suffix:semicolon
r_int
r_int
id|riscix_minor
suffix:semicolon
r_if
c_cond
(paren
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_ne
l_int|1024
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; [RISCiX]&quot;
)paren
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|riscix_minor
op_assign
id|minor
op_increment
comma
id|first_sect
comma
id|nr_sects
)paren
suffix:semicolon
id|hd-&gt;sizes
(braket
id|riscix_minor
)braket
op_assign
id|hd-&gt;part
(braket
id|riscix_minor
)braket
dot
id|nr_sects
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
id|dev
op_assign
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|riscix_minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|rr
op_assign
(paren
r_struct
id|riscix_record
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;magic
op_eq
id|RISCIX_MAGIC
)paren
(brace
r_int
id|part
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
l_int|0
suffix:semicolon
id|part
OL
l_int|8
suffix:semicolon
id|part
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|one
op_logical_and
id|memcmp
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|name
comma
l_string|&quot;All&bslash;0&quot;
comma
l_int|4
)paren
)paren
(brace
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
op_increment
comma
id|le32_to_cpu
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|start
)paren
comma
id|le32_to_cpu
c_func
(paren
id|rr-&gt;part
(braket
id|part
)braket
dot
id|length
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(%s)&quot;
comma
id|rr-&gt;part
(braket
id|part
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hd-&gt;part
(braket
id|riscix_minor
)braket
dot
id|nr_sects
OG
l_int|2
)paren
id|hd-&gt;part
(braket
id|riscix_minor
)braket
dot
id|nr_sects
op_assign
l_int|2
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|minor
suffix:semicolon
)brace
macro_line|#endif
DECL|function|linux_partition
r_static
r_int
id|linux_partition
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
id|first_sect
comma
r_int
r_int
id|minor
comma
r_int
r_int
id|nr_sects
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|linux_part
op_star
id|linuxp
suffix:semicolon
r_int
r_int
id|linux_minor
comma
id|mask
op_assign
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_ne
l_int|1024
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; [Linux]&quot;
)paren
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|linux_minor
op_assign
id|minor
op_increment
comma
id|first_sect
comma
id|nr_sects
)paren
suffix:semicolon
id|hd-&gt;sizes
(braket
id|linux_minor
)braket
op_assign
id|hd-&gt;part
(braket
id|linux_minor
)braket
dot
id|nr_sects
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
id|dev
op_assign
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|linux_minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|linuxp
op_assign
(paren
r_struct
id|linux_part
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|linuxp-&gt;magic
op_eq
id|cpu_to_le32
c_func
(paren
id|LINUX_NATIVE_MAGIC
)paren
op_logical_or
id|linuxp-&gt;magic
op_eq
id|cpu_to_le32
c_func
(paren
id|LINUX_SWAP_MAGIC
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|minor
op_amp
id|mask
)paren
)paren
r_break
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
op_increment
comma
id|first_sect
op_plus
id|le32_to_cpu
c_func
(paren
id|linuxp-&gt;start_sect
)paren
comma
id|le32_to_cpu
c_func
(paren
id|linuxp-&gt;nr_sects
)paren
)paren
suffix:semicolon
id|linuxp
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Prevent someone doing a mkswap or mkfs on this partition&n;&t; */
r_if
c_cond
(paren
id|hd-&gt;part
(braket
id|linux_minor
)braket
dot
id|nr_sects
OG
l_int|2
)paren
(brace
id|hd-&gt;part
(braket
id|linux_minor
)braket
dot
id|nr_sects
op_assign
l_int|2
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|minor
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_CUMANA
DECL|function|adfspart_check_CUMANA
r_static
r_int
id|adfspart_check_CUMANA
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
r_int
id|minor
)paren
(brace
r_int
r_int
id|start_blk
op_assign
l_int|0
comma
id|mask
op_assign
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|name
op_assign
l_string|&quot;CUMANA/ADFS&quot;
suffix:semicolon
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_ne
l_int|1024
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try Cumana style partitions - sector 3 contains ADFS boot block with pointer&n;&t; * to next &squot;drive&squot;.&n;&t; *&n;&t; * There are unknowns in this code - is the &squot;cylinder number&squot; of the next&n;&t; * partition relative to the start of this one - I&squot;m assuming it is.&n;&t; *&n;&t; * Also, which ID did Cumana use?&n;&t; *&n;&t; * This is totally unfinished, and will require more work to get it going.&n;&t; * Hence it is totally untested.&n;&t; */
r_do
(brace
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_int
r_int
id|nr_sects
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|minor
op_amp
id|mask
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
id|start_blk
op_plus
l_int|3
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dr
op_assign
id|adfs_partition
c_func
(paren
id|hd
comma
id|name
comma
id|bh-&gt;b_data
comma
id|first_sector
comma
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dr
)paren
r_break
suffix:semicolon
id|name
op_assign
l_int|NULL
suffix:semicolon
id|nr_sects
op_assign
(paren
id|bh-&gt;b_data
(braket
l_int|0x1fd
)braket
op_plus
(paren
id|bh-&gt;b_data
(braket
l_int|0x1fe
)braket
op_lshift
l_int|8
)paren
)paren
op_star
(paren
id|dr-&gt;heads
op_plus
(paren
id|dr-&gt;lowsector
op_amp
l_int|0x40
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
op_star
id|dr-&gt;secspertrack
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_sects
)paren
r_break
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|first_sector
op_add_assign
id|nr_sects
suffix:semicolon
id|start_blk
op_add_assign
id|nr_sects
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
id|nr_sects
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* hmm - should be partition size */
r_switch
c_cond
(paren
id|bh-&gt;b_data
(braket
l_int|0x1fc
)braket
op_amp
l_int|15
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* No partition / ADFS? */
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
r_case
id|PARTITION_RISCIX_SCSI
suffix:colon
multiline_comment|/* RiscIX - we don&squot;t know how to find the next one. */
id|minor
op_assign
id|riscix_partition
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|minor
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PARTITION_LINUX
suffix:colon
id|minor
op_assign
id|linux_partition
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|minor
comma
id|nr_sects
)paren
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
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
op_minus
l_int|1
)paren
r_return
id|minor
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|first
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ADFS
multiline_comment|/*&n; * Purpose: allocate ADFS partitions.&n; *&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; *&t;    first_sector- first readable sector on the device.&n; *&t;    minor&t;- first available minor on device.&n; *&n; * Returns: -1 on error, 0 for no ADFS boot sector, 1 for ok.&n; *&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition on first drive.&n; *&t;    hda2 = non-ADFS partition.&n; */
DECL|function|adfspart_check_ADFS
r_static
r_int
id|adfspart_check_ADFS
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
r_int
id|minor
)paren
(brace
r_int
r_int
id|start_sect
comma
id|nr_sects
comma
id|sectscyl
comma
id|heads
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|adfs_discrecord
op_star
id|dr
suffix:semicolon
r_if
c_cond
(paren
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_ne
l_int|1024
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
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|3
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dr
op_assign
id|adfs_partition
c_func
(paren
id|hd
comma
l_string|&quot;ADFS&quot;
comma
id|bh-&gt;b_data
comma
id|first_sector
comma
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dr
)paren
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
id|heads
op_assign
id|dr-&gt;heads
op_plus
(paren
(paren
id|dr-&gt;lowsector
op_rshift
l_int|6
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|adfspart_setgeometry
c_func
(paren
id|dev
comma
id|dr-&gt;secspertrack
comma
id|heads
comma
id|hd-&gt;part
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
dot
id|nr_sects
)paren
suffix:semicolon
id|sectscyl
op_assign
id|dr-&gt;secspertrack
op_star
id|heads
suffix:semicolon
multiline_comment|/*&n;&t; * Work out start of non-adfs partition.&n;&t; */
id|start_sect
op_assign
(paren
(paren
id|bh-&gt;b_data
(braket
l_int|0x1fe
)braket
op_lshift
l_int|8
)paren
op_plus
id|bh-&gt;b_data
(braket
l_int|0x1fd
)braket
)paren
op_star
id|sectscyl
suffix:semicolon
id|nr_sects
op_assign
id|hd-&gt;part
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
dot
id|nr_sects
op_minus
id|start_sect
suffix:semicolon
r_if
c_cond
(paren
id|start_sect
)paren
(brace
id|first_sector
op_add_assign
id|start_sect
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we now have a problem - how to set the origional disk size if the&n;&t;&t; * disk doesn&squot;t report it, since there is no standard way of getting&n;&t;&t; * that info.&n;&t;&t; */
r_switch
c_cond
(paren
id|bh-&gt;b_data
(braket
l_int|0x1fc
)braket
op_amp
l_int|15
)paren
(brace
macro_line|#ifdef CONFIG_ACORN_PARTITION_RISCIX
r_case
id|PARTITION_RISCIX_SCSI
suffix:colon
r_case
id|PARTITION_RISCIX_MFM
suffix:colon
id|minor
op_assign
id|riscix_partition
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|minor
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PARTITION_LINUX
suffix:colon
id|minor
op_assign
id|linux_partition
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|minor
comma
id|nr_sects
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ICS
DECL|function|adfspart_check_ICSLinux
r_static
r_int
id|adfspart_check_ICSLinux
c_func
(paren
id|kdev_t
id|dev
comma
r_int
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|block
op_amp
l_int|1
ques
c_cond
l_int|512
suffix:colon
l_int|0
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
id|block
op_rshift
l_int|1
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|bh-&gt;b_data
op_plus
id|offset
comma
l_string|&quot;LinuxPart&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
id|result
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Purpose: allocate ICS partitions.&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; *&t;    first_sector- first readable sector on the device.&n; *&t;    minor&t;- first available minor on device.&n; * Returns: -1 on error, 0 for no ICS table, 1 for partitions ok.&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition 0 on first drive.&n; *&t;    hda2 = ADFS partition 1 on first drive.&n; *&t;&t;..etc..&n; */
DECL|function|adfspart_check_ICS
r_static
r_int
id|adfspart_check_ICS
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
r_int
id|minor
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|sum
suffix:semicolon
r_int
r_int
id|i
comma
id|mask
op_assign
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
r_struct
id|ics_part
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
)brace
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
op_ne
l_int|1024
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try ICS style partitions - sector 0 contains partition info.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * check for a valid checksum&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|sum
op_assign
l_int|0x50617274
suffix:semicolon
id|i
OL
l_int|508
suffix:semicolon
id|i
op_increment
)paren
id|sum
op_add_assign
id|bh-&gt;b_data
(braket
id|i
)braket
suffix:semicolon
id|sum
op_sub_assign
id|le32_to_cpu
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|bh-&gt;b_data
(braket
l_int|508
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sum
)paren
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
multiline_comment|/* not ICS partition table */
)brace
id|printk
c_func
(paren
l_string|&quot; [ICS]&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
(paren
r_struct
id|ics_part
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|p-&gt;size
suffix:semicolon
id|p
op_increment
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|minor
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|start
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;start
)paren
suffix:semicolon
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
id|size
op_assign
op_minus
id|size
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We use the first sector to identify what type&n;&t;&t;&t; * this partition is...&n;&t;&t;&t; */
r_if
c_cond
(paren
id|size
OG
l_int|1
op_logical_and
id|adfspart_check_ICSLinux
c_func
(paren
id|dev
comma
id|start
)paren
)paren
(brace
id|start
op_add_assign
l_int|1
suffix:semicolon
id|size
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|size
)paren
(brace
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|first_sector
op_plus
id|start
comma
id|size
)paren
suffix:semicolon
id|minor
op_increment
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_POWERTEC
DECL|struct|ptec_partition
r_struct
id|ptec_partition
(brace
DECL|member|unused1
id|u32
id|unused1
suffix:semicolon
DECL|member|unused2
id|u32
id|unused2
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|unused5
id|u32
id|unused5
suffix:semicolon
DECL|member|type
r_char
id|type
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Purpose: allocate ICS partitions.&n; * Params : hd&t;&t;- pointer to gendisk structure to store partition info.&n; *&t;    dev&t;&t;- device number to access.&n; *&t;    first_sector- first readable sector on the device.&n; *&t;    minor&t;- first available minor on device.&n; * Returns: -1 on error, 0 for no ICS table, 1 for partitions ok.&n; * Alloc  : hda  = whole drive&n; *&t;    hda1 = ADFS partition 0 on first drive.&n; *&t;    hda2 = ADFS partition 1 on first drive.&n; *&t;&t;..etc..&n; */
DECL|function|adfspart_check_POWERTEC
r_static
r_int
id|adfspart_check_POWERTEC
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
r_int
id|minor
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ptec_partition
op_star
id|p
suffix:semicolon
r_int
r_char
id|checksum
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1024
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|checksum
op_assign
l_int|0x2a
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|511
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
id|bh-&gt;b_data
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
id|bh-&gt;b_data
(braket
l_int|511
)braket
)paren
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
id|printk
c_func
(paren
l_string|&quot; [POWERTEC]&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
(paren
r_struct
id|ptec_partition
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|start
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;start
)paren
suffix:semicolon
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|p-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|first_sector
op_plus
id|start
comma
id|size
)paren
suffix:semicolon
id|minor
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Purpose: initialise all the partitions on an ADFS drive.&n; *          These may be other ADFS partitions or a Linux/RiscBSD/RiscIX&n; *&t;    partition.&n; *&n; * Params : hd&t;&t; - pointer to gendisk structure to store devices partitions.&n; *          dev&t;&t; - device number to access&n; *&t;    first_sector - first available sector on the disk.&n; *&t;    minor&t; - first available minor on this device.&n; *&n; * Returns: -1 on error, 0 if not ADFS format, 1 if ok.&n; */
DECL|function|acorn_partition
r_int
id|acorn_partition
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
id|r
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ACORN_PARTITION_ICS
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|r
op_assign
id|adfspart_check_ICS
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_CUMANA
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|r
op_assign
id|adfspart_check_CUMANA
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ADFS
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|r
op_assign
id|adfspart_check_ADFS
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_POWERTEC
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|r
op_assign
id|adfspart_check_POWERTEC
c_func
(paren
id|hd
comma
id|dev
comma
id|first_sector
comma
id|first_part_minor
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot; unable to read boot sectors / partition sectors&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
eof
