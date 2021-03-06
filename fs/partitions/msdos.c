multiline_comment|/*&n; *  fs/partitions/msdos.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *&n; *  Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug&n; *  in the early extended-partition checks and added DM partitions&n; *&n; *  Support for DiskManager v6.0x added by Mark Lord,&n; *  with information provided by OnTrack.  This now works for linux fdisk&n; *  and LILO, as well as loadlin and bootln.  Note that disks other than&n; *  /dev/hda *must* have a &quot;DOS&quot; type 0x51 partition in the first slot (hda1).&n; *&n; *  More flexible handling of extended partitions - aeb, 950831&n; *&n; *  Check partition table on IDE disks for common CHS translations&n; *&n; *  Re-organised Feb 1998 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_IDE
macro_line|#include &lt;linux/ide.h&gt;&t;/* IDE xlate */
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;msdos.h&quot;
macro_line|#if CONFIG_BLK_DEV_MD &amp;&amp; CONFIG_AUTODETECT_RAID
r_extern
r_void
id|md_autodetect_dev
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|current_minor
r_static
r_int
id|current_minor
suffix:semicolon
multiline_comment|/*&n; * Many architectures don&squot;t like unaligned accesses, which is&n; * frequently the case with the nr_sects and start_sect partition&n; * table entries.&n; */
macro_line|#include &lt;asm/unaligned.h&gt;
DECL|macro|SYS_IND
mdefine_line|#define SYS_IND(p)&t;(get_unaligned(&amp;p-&gt;sys_ind))
DECL|macro|NR_SECTS
mdefine_line|#define NR_SECTS(p)&t;({ __typeof__(p-&gt;nr_sects) __a =&t;&bslash;&n;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;nr_sects);&t;&bslash;&n;&t;&t;&t;&t;le32_to_cpu(__a); &bslash;&n;&t;&t;&t;})
DECL|macro|START_SECT
mdefine_line|#define START_SECT(p)&t;({ __typeof__(p-&gt;start_sect) __a =&t;&bslash;&n;&t;&t;&t;&t;get_unaligned(&amp;p-&gt;start_sect);&t;&bslash;&n;&t;&t;&t;&t;le32_to_cpu(__a); &bslash;&n;&t;&t;&t;})
DECL|function|is_extended_partition
r_static
r_inline
r_int
id|is_extended_partition
c_func
(paren
r_struct
id|partition
op_star
id|p
)paren
(brace
r_return
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DOS_EXTENDED_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|WIN98_EXTENDED_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_EXTENDED_PARTITION
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create devices for each logical partition in an extended partition.&n; * The logical partitions form a linked list, with each entry being&n; * a partition table with two entries.  The first entry&n; * is the real data partition (with a start relative to the partition&n; * table start).  The second is a pointer to the next logical partition&n; * (with a start relative to the entire extended partition).&n; * We do not create a Linux partition for the partition tables, but&n; * only for the actual data partitions.&n; */
DECL|function|extended_partition
r_static
r_void
id|extended_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
r_int
id|first_sector
comma
id|first_size
comma
id|this_sector
comma
id|this_size
suffix:semicolon
r_int
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
r_int
id|sector_size
op_assign
id|get_hardsect_size
c_func
(paren
id|dev
)paren
op_div
l_int|512
suffix:semicolon
r_int
id|loopct
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of links followed&n;&t;&t;&t;&t;   without finding a data partition */
r_int
id|i
suffix:semicolon
id|first_sector
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
id|start_sect
suffix:semicolon
id|first_size
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
suffix:semicolon
id|this_sector
op_assign
id|first_sector
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_increment
id|loopct
OG
l_int|100
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_return
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
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
(paren
id|__u16
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|510
)paren
)paren
op_ne
id|cpu_to_le16
c_func
(paren
id|MSDOS_LABEL_MAGIC
)paren
)paren
r_goto
id|done
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
l_int|0x1BE
op_plus
id|bh-&gt;b_data
)paren
suffix:semicolon
id|this_size
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
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Usually, the first entry is the real data partition,&n;&t;&t; * the 2nd entry is the next extended partition, or empty,&n;&t;&t; * and the 3rd and 4th entries are unused.&n;&t;&t; * However, DRDOS sometimes has the extended partition as&n;&t;&t; * the first entry (when the data partition is empty),&n;&t;&t; * and OS/2 seems to use all four entries.&n;&t;&t; */
multiline_comment|/* &n;&t;&t; * First process the data partition(s)&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|NR_SECTS
c_func
(paren
id|p
)paren
op_logical_or
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check the 3rd and 4th entries -&n;&t;&t;&t;   these sometimes contain random garbage */
r_if
c_cond
(paren
id|i
op_ge
l_int|2
op_logical_and
id|START_SECT
c_func
(paren
id|p
)paren
op_plus
id|NR_SECTS
c_func
(paren
id|p
)paren
OG
id|this_size
op_logical_and
(paren
id|this_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
template_param
id|first_sector
op_plus
id|first_size
)paren
)paren
r_continue
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|current_minor
comma
id|this_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
)paren
suffix:semicolon
macro_line|#if CONFIG_BLK_DEV_MD &amp;&amp; CONFIG_AUTODETECT_RAID
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_RAID_PARTITION
)paren
(brace
id|md_autodetect_dev
c_func
(paren
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|current_minor
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|current_minor
op_increment
suffix:semicolon
id|loopct
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Next, process the (first) extended partition, if present.&n;&t;&t; * (So far, there seems to be no reason to make&n;&t;&t; *  extended_partition()  recursive and allow a tree&n;&t;&t; *  of extended partitions.)&n;&t;&t; * It should be a link to the next logical partition.&n;&t;&t; * Create a minor for this just long enough to get the next&n;&t;&t; * partition table.  The minor will be reused for the next&n;&t;&t; * data partition.&n;&t;&t; */
id|p
op_sub_assign
l_int|4
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
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
r_if
c_cond
(paren
id|NR_SECTS
c_func
(paren
id|p
)paren
op_logical_and
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|4
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* nothing left to do */
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
multiline_comment|/* JSt */
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|first_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|this_sector
op_assign
id|first_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
suffix:semicolon
id|dev
op_assign
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|current_minor
)paren
suffix:semicolon
multiline_comment|/* Use bforget(), as we have changed the disk geometry */
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|get_partition_table_block
id|get_partition_table_block
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_int
id|blocknr
)paren
(brace
id|kdev_t
id|dev
op_assign
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|minor
)paren
suffix:semicolon
r_return
id|bread
c_func
(paren
id|dev
comma
id|blocknr
comma
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
multiline_comment|/* james@bpgc.com: Solaris has a nasty indicator: 0x82 which also&n;   indicates linux swap.  Be careful before believing this is Solaris. */
r_static
r_void
DECL|function|solaris_x86_partition
id|solaris_x86_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
)paren
(brace
r_int
id|offset
op_assign
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|solaris_x86_vtoc
op_star
id|v
suffix:semicolon
r_struct
id|solaris_x86_slice
op_star
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|get_partition_table_block
c_func
(paren
id|hd
comma
id|minor
comma
l_int|0
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|v
op_assign
(paren
r_struct
id|solaris_x86_vtoc
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;v_sanity
op_ne
id|SOLARIS_X86_VTOC_SANE
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s: &lt;solaris:&quot;
comma
id|disk_name
c_func
(paren
id|hd
comma
id|minor
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;v_version
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  cannot handle version %ld vtoc&gt;&bslash;n&quot;
comma
id|v-&gt;v_version
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SOLARIS_X86_NUMSLICE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|s
op_assign
op_amp
id|v-&gt;v_slice
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_size
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [s%d]&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* solaris partitions are relative to current MS-DOS&n;&t;&t; * one but add_gd_partition starts relative to sector&n;&t;&t; * zero of the disk.  Therefore, must add the offset&n;&t;&t; * of the current partition */
id|add_gd_partition
c_func
(paren
id|hd
comma
id|current_minor
comma
id|s-&gt;s_start
op_plus
id|offset
comma
id|s-&gt;s_size
)paren
suffix:semicolon
id|current_minor
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_BSD_DISKLABEL
r_static
r_void
DECL|function|check_and_add_bsd_partition
id|check_and_add_bsd_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_struct
id|bsd_partition
op_star
id|bsd_p
comma
r_int
id|minor
)paren
(brace
r_struct
id|hd_struct
op_star
id|lin_p
suffix:semicolon
multiline_comment|/* check relative position of partitions.  */
r_for
c_loop
(paren
id|lin_p
op_assign
id|hd-&gt;part
op_plus
l_int|1
op_plus
id|minor
suffix:semicolon
id|lin_p
op_minus
id|hd-&gt;part
op_minus
id|minor
OL
id|current_minor
suffix:semicolon
id|lin_p
op_increment
)paren
(brace
multiline_comment|/* no relationship -&gt; try again */
r_if
c_cond
(paren
id|lin_p-&gt;start_sect
op_plus
id|lin_p-&gt;nr_sects
op_le
id|bsd_p-&gt;p_offset
op_logical_or
id|lin_p-&gt;start_sect
op_ge
id|bsd_p-&gt;p_offset
op_plus
id|bsd_p-&gt;p_size
)paren
r_continue
suffix:semicolon
multiline_comment|/* equal -&gt; no need to add */
r_if
c_cond
(paren
id|lin_p-&gt;start_sect
op_eq
id|bsd_p-&gt;p_offset
op_logical_and
id|lin_p-&gt;nr_sects
op_eq
id|bsd_p-&gt;p_size
)paren
r_return
suffix:semicolon
multiline_comment|/* bsd living within dos partition */
r_if
c_cond
(paren
id|lin_p-&gt;start_sect
op_le
id|bsd_p-&gt;p_offset
op_logical_and
id|lin_p-&gt;start_sect
op_plus
id|lin_p-&gt;nr_sects
op_ge
id|bsd_p-&gt;p_offset
op_plus
id|bsd_p-&gt;p_size
)paren
(brace
macro_line|#ifdef DEBUG_BSD_DISKLABEL
id|printk
c_func
(paren
l_string|&quot;w: %d %ld+%ld,%d+%d&quot;
comma
id|lin_p
op_minus
id|hd-&gt;part
comma
id|lin_p-&gt;start_sect
comma
id|lin_p-&gt;nr_sects
comma
id|bsd_p-&gt;p_offset
comma
id|bsd_p-&gt;p_size
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
multiline_comment|/* ouch: bsd and linux overlap. Don&squot;t even try for that partition */
macro_line|#ifdef DEBUG_BSD_DISKLABEL
id|printk
c_func
(paren
l_string|&quot;???: %d %ld+%ld,%d+%d&quot;
comma
id|lin_p
op_minus
id|hd-&gt;part
comma
id|lin_p-&gt;start_sect
comma
id|lin_p-&gt;nr_sects
comma
id|bsd_p-&gt;p_offset
comma
id|bsd_p-&gt;p_size
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;???&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* if the bsd partition is not currently known to linux, we end&n;&t;   * up here &n;&t;   */
id|add_gd_partition
c_func
(paren
id|hd
comma
id|current_minor
comma
id|bsd_p-&gt;p_offset
comma
id|bsd_p-&gt;p_size
)paren
suffix:semicolon
id|current_minor
op_increment
suffix:semicolon
)brace
multiline_comment|/* &n; * Create devices for BSD partitions listed in a disklabel, under a&n; * dos-like partition. See extended_partition() for more information.&n; */
DECL|function|bsd_disklabel_partition
r_static
r_void
id|bsd_disklabel_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_int
id|type
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bsd_disklabel
op_star
id|l
suffix:semicolon
r_struct
id|bsd_partition
op_star
id|p
suffix:semicolon
r_int
id|max_partitions
suffix:semicolon
r_int
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
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|get_partition_table_block
c_func
(paren
id|hd
comma
id|minor
comma
l_int|0
)paren
)paren
)paren
r_return
suffix:semicolon
id|l
op_assign
(paren
r_struct
id|bsd_disklabel
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l-&gt;d_magic
op_ne
id|BSD_DISKMAGIC
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s:&quot;
comma
id|disk_name
c_func
(paren
id|hd
comma
id|minor
comma
id|buf
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
(paren
id|type
op_eq
id|OPENBSD_PARTITION
)paren
ques
c_cond
l_string|&quot; &lt;openbsd:&quot;
suffix:colon
(paren
id|type
op_eq
id|NETBSD_PARTITION
)paren
ques
c_cond
l_string|&quot; &lt;netbsd:&quot;
suffix:colon
l_string|&quot; &lt;bsd:&quot;
)paren
suffix:semicolon
id|max_partitions
op_assign
(paren
(paren
id|type
op_eq
id|OPENBSD_PARTITION
)paren
ques
c_cond
id|OPENBSD_MAXPARTITIONS
suffix:colon
id|BSD_MAXPARTITIONS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l-&gt;d_npartitions
OL
id|max_partitions
)paren
id|max_partitions
op_assign
id|l-&gt;d_npartitions
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|l-&gt;d_partitions
suffix:semicolon
id|p
op_minus
id|l-&gt;d_partitions
OL
id|max_partitions
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
id|mask
)paren
op_ge
(paren
l_int|4
op_plus
id|hd-&gt;max_p
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_fstype
op_ne
id|BSD_FS_UNUSED
)paren
id|check_and_add_bsd_partition
c_func
(paren
id|hd
comma
id|p
comma
id|minor
)paren
suffix:semicolon
)brace
multiline_comment|/* Use bforget(), as we have changed the disk setup */
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_UNIXWARE_DISKLABEL
multiline_comment|/*&n; * Create devices for Unixware partitions listed in a disklabel, under a&n; * dos-like partition. See extended_partition() for more information.&n; */
DECL|function|unixware_partition
r_static
r_void
id|unixware_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
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
id|unixware_disklabel
op_star
id|l
suffix:semicolon
r_struct
id|unixware_slice
op_star
id|p
suffix:semicolon
r_int
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
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|get_partition_table_block
c_func
(paren
id|hd
comma
id|minor
comma
l_int|14
)paren
)paren
)paren
r_return
suffix:semicolon
id|l
op_assign
(paren
r_struct
id|unixware_disklabel
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|l-&gt;d_magic
)paren
op_ne
id|UNIXWARE_DISKMAGIC
op_logical_or
id|le32_to_cpu
c_func
(paren
id|l-&gt;vtoc.v_magic
)paren
op_ne
id|UNIXWARE_DISKMAGIC2
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s: &lt;unixware:&quot;
comma
id|disk_name
c_func
(paren
id|hd
comma
id|minor
comma
id|buf
)paren
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|l-&gt;vtoc.v_slice
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* I omit the 0th slice as it is the same as whole disk. */
r_while
c_loop
(paren
id|p
op_minus
op_amp
id|l-&gt;vtoc.v_slice
(braket
l_int|0
)braket
OL
id|UNIXWARE_NUMSLICE
)paren
(brace
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;s_label
op_ne
id|UNIXWARE_FS_UNUSED
)paren
(brace
id|add_gd_partition
c_func
(paren
id|hd
comma
id|current_minor
comma
id|START_SECT
c_func
(paren
id|p
)paren
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|current_minor
op_increment
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* Use bforget, as we have changed the disk setup */
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|msdos_partition
r_int
id|msdos_partition
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
comma
id|minor
op_assign
id|current_minor
op_assign
id|first_part_minor
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_int
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
r_int
id|sector_size
op_assign
id|get_hardsect_size
c_func
(paren
id|dev
)paren
op_div
l_int|512
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_int
id|tested_for_xlate
op_assign
l_int|0
suffix:semicolon
id|read_mbr
suffix:colon
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
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
id|get_ptable_blocksize
c_func
(paren
id|dev
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot; unable to read partition table&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|data
op_assign
id|bh-&gt;b_data
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|check_table
suffix:colon
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
multiline_comment|/* Use bforget(), because we may have changed the disk geometry */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
l_int|0x1fe
op_plus
id|data
)paren
op_ne
id|cpu_to_le16
c_func
(paren
id|MSDOS_LABEL_MAGIC
)paren
)paren
(brace
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
l_int|0x1be
op_plus
id|data
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_if
c_cond
(paren
op_logical_neg
id|tested_for_xlate
op_increment
)paren
(brace
multiline_comment|/* Do this only once per disk */
multiline_comment|/*&n;&t;&t; * Look for various forms of IDE disk geometry translation&n;&t;&t; */
r_int
r_int
id|sig
op_assign
id|le16_to_cpu
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|data
op_plus
l_int|2
)paren
)paren
suffix:semicolon
r_int
id|heads
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The i386 partition handling programs very often&n;&t;&t; * make partitions end on cylinder boundaries.&n;&t;&t; * There is no need to do so, and Linux fdisk doesnt always&n;&t;&t; * do this, and Windows NT on Alpha doesnt do this either,&n;&t;&t; * but still, this helps to guess #heads.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|partition
op_star
id|q
op_assign
op_amp
id|p
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|NR_SECTS
c_func
(paren
id|q
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|q-&gt;sector
op_amp
l_int|63
)paren
op_eq
l_int|1
op_logical_and
(paren
id|q-&gt;end_sector
op_amp
l_int|63
)paren
op_eq
l_int|63
)paren
id|heads
op_assign
id|q-&gt;end_head
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|EZD_PARTITION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Accesses to sector 0 must go to sector 1 instead.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ide_xlate_1024
c_func
(paren
id|dev
comma
op_minus
l_int|1
comma
id|heads
comma
l_string|&quot; [EZD]&quot;
)paren
)paren
(brace
id|data
op_add_assign
l_int|512
suffix:semicolon
r_goto
id|check_table
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DM6_PARTITION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Everything on the disk is offset by 63 sectors,&n;&t;&t;&t; * including a &quot;new&quot; MBR with its own partition table.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ide_xlate_1024
c_func
(paren
id|dev
comma
l_int|1
comma
id|heads
comma
l_string|&quot; [DM6:DDO]&quot;
)paren
)paren
(brace
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|read_mbr
suffix:semicolon
multiline_comment|/* start over with new MBR */
)brace
)brace
r_else
r_if
c_cond
(paren
id|sig
op_le
l_int|0x1ae
op_logical_and
id|data
(braket
id|sig
)braket
op_eq
l_int|0xAA
op_logical_and
id|data
(braket
id|sig
op_plus
l_int|1
)braket
op_eq
l_int|0x55
op_logical_and
(paren
id|data
(braket
id|sig
op_plus
l_int|2
)braket
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/* DM6 signature in MBR, courtesy of OnTrack */
(paren
r_void
)paren
id|ide_xlate_1024
(paren
id|dev
comma
l_int|0
comma
id|heads
comma
l_string|&quot; [DM6:MBR]&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DM6_AUX1PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|DM6_AUX3PARTITION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * DM6 on other than the first (boot) drive&n;&t;&t;&t; */
(paren
r_void
)paren
id|ide_xlate_1024
c_func
(paren
id|dev
comma
l_int|0
comma
id|heads
comma
l_string|&quot; [DM6:AUX]&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
(paren
r_void
)paren
id|ide_xlate_1024
c_func
(paren
id|dev
comma
l_int|2
comma
id|heads
comma
l_string|&quot; [PTBL]&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
multiline_comment|/* Look for partitions in two passes:&n;&t;   First find the primary partitions, and the DOS-type extended partitions.&n;&t;   On the second pass look inside *BSD and Unixware and Solaris partitions. */
id|current_minor
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* first &quot;extra&quot; minor (for extended partitions) */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|minor
op_increment
comma
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|first_sector
op_plus
id|START_SECT
c_func
(paren
id|p
)paren
op_star
id|sector_size
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
op_star
id|sector_size
)paren
suffix:semicolon
macro_line|#if CONFIG_BLK_DEV_MD &amp;&amp; CONFIG_AUTODETECT_RAID
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|LINUX_RAID_PARTITION
)paren
(brace
id|md_autodetect_dev
c_func
(paren
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|minor
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|is_extended_partition
c_func
(paren
id|p
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If we are rereading the partition table, we need&n;&t;&t;&t; * to set the size of the partition so that we will&n;&t;&t;&t; * be able to bread the block containing the extended&n;&t;&t;&t; * partition info.&n;&t;&t;&t; */
id|hd-&gt;sizes
(braket
id|minor
)braket
op_assign
id|hd-&gt;part
(braket
id|minor
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
id|extended_partition
c_func
(paren
id|hd
comma
id|MKDEV
c_func
(paren
id|hd-&gt;major
comma
id|minor
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
multiline_comment|/* prevent someone doing mkfs or mkswap on an&n;&t;&t;&t;   extended partition, but leave room for LILO */
r_if
c_cond
(paren
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
OG
l_int|2
)paren
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  Check for old-style Disk Manager partition table&n;&t; */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|data
op_plus
l_int|0xfc
)paren
op_eq
id|cpu_to_le16
c_func
(paren
id|MSDOS_LABEL_MAGIC
)paren
)paren
(brace
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
l_int|0x1be
op_plus
id|data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
comma
id|current_minor
op_increment
)paren
(brace
id|p
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|START_SECT
c_func
(paren
id|p
)paren
op_logical_and
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
)paren
r_continue
suffix:semicolon
id|add_gd_partition
c_func
(paren
id|hd
comma
id|current_minor
comma
id|START_SECT
c_func
(paren
id|p
)paren
comma
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* second pass - output for each on a separate line */
id|minor
op_sub_assign
l_int|4
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
(paren
l_int|0x1be
op_plus
id|data
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
op_le
l_int|4
suffix:semicolon
id|minor
op_increment
comma
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|NR_SECTS
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
macro_line|#ifdef CONFIG_BSD_DISKLABEL
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|BSD_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|NETBSD_PARTITION
op_logical_or
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|OPENBSD_PARTITION
)paren
id|bsd_disklabel_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|SYS_IND
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UNIXWARE_DISKLABEL
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|UNIXWARE_PARTITION
)paren
id|unixware_partition
c_func
(paren
id|hd
comma
id|minor
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
r_if
c_cond
(paren
id|SYS_IND
c_func
(paren
id|p
)paren
op_eq
id|SOLARIS_X86_PARTITION
)paren
(brace
id|solaris_x86_partition
c_func
(paren
id|hd
comma
id|minor
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
