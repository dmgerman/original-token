multiline_comment|/*&n; *  Code extracted from&n; *  linux/kernel/hd.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *  Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug&n; *  in the early extended-partition checks and added DM partitions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|variable|gendisk_head
r_struct
id|gendisk
op_star
id|gendisk_head
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|current_minor
r_static
r_int
id|current_minor
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
op_star
id|blk_size
(braket
)braket
suffix:semicolon
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
r_int
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
id|this_sector
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
l_int|1024
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to read partition table of device %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   * This block is from a device that we&squot;re about to stomp on.&n;&t;   * So make sure nobody thinks this block is usable.&n;&t;   */
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|0
suffix:semicolon
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
id|bh-&gt;b_data
op_plus
l_int|510
)paren
op_eq
l_int|0xAA55
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Process the first entry, which should be the real&n;&t;&t; * data partition.&n;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_eq
id|EXTENDED_PARTITION
op_logical_or
op_logical_neg
(paren
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* shouldn&squot;t happen */
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|this_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Logical part %d start %d size %d end %d&bslash;n&bslash;r&quot;
comma
id|current_minor
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_plus
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
id|current_minor
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Process the second entry, which should be a link&n;&t;&t; * to the next logical partition.  Create a minor&n;&t;&t; * for this just long enough to get the next partition&n;&t;&t; * table.  The minor will be reused for the real&n;&t;&t; * data partition.&n;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_ne
id|EXTENDED_PARTITION
op_logical_or
op_logical_neg
(paren
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* no more logicals in this partition */
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|this_sector
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|dev
op_assign
(paren
(paren
id|hd-&gt;major
)paren
op_lshift
l_int|8
)paren
op_or
id|current_minor
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
)brace
id|done
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|check_partition
r_static
r_void
id|check_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
r_int
id|dev
)paren
(brace
r_int
id|i
comma
id|minor
op_assign
id|current_minor
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
r_int
id|first_sector
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
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to read partition table of device %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s%d :&bslash;n&bslash;r&quot;
comma
id|hd-&gt;major_name
comma
id|minor
op_rshift
id|hd-&gt;minor_shift
)paren
suffix:semicolon
id|current_minor
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* first &quot;extra&quot; minor */
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
id|bh-&gt;b_data
op_plus
l_int|510
)paren
op_eq
l_int|0xAA55
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
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
(paren
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_continue
suffix:semicolon
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; part %d start %d size %d end %d &bslash;n&bslash;r&quot;
comma
id|i
comma
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
comma
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
comma
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_plus
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
l_int|0x3f
)paren
op_ge
l_int|60
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_eq
id|EXTENDED_PARTITION
)paren
(brace
id|extended_partition
c_func
(paren
id|hd
comma
(paren
id|hd-&gt;major
op_lshift
l_int|8
)paren
op_or
id|minor
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * check for Disk Manager partition table&n;&t;&t; */
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
id|bh-&gt;b_data
op_plus
l_int|0xfc
)paren
op_eq
l_int|0x55AA
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
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
l_int|0x3f
)paren
op_ge
l_int|60
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;start_sect
op_logical_and
id|p-&gt;nr_sects
)paren
)paren
r_continue
suffix:semicolon
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|p-&gt;start_sect
suffix:semicolon
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; DM part %d start %d size %d end %d&bslash;n&bslash;r&quot;
comma
id|current_minor
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
comma
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|start_sect
op_plus
id|hd-&gt;part
(braket
id|current_minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Bad partition table on dev %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|setup_dev
r_static
r_void
id|setup_dev
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|j
op_assign
id|dev-&gt;max_nr
op_star
id|dev-&gt;max_p
suffix:semicolon
r_int
id|major
op_assign
id|dev-&gt;major
op_lshift
l_int|8
suffix:semicolon
r_int
id|drive
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
id|j
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;part
(braket
id|i
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;part
(braket
id|i
)braket
dot
id|nr_sects
op_assign
l_int|0
suffix:semicolon
)brace
id|dev
op_member_access_from_pointer
id|init
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|drive
op_assign
l_int|0
suffix:semicolon
id|drive
OL
id|dev-&gt;nr_real
suffix:semicolon
id|drive
op_increment
)paren
(brace
id|current_minor
op_assign
l_int|1
op_plus
(paren
id|drive
op_lshift
id|dev-&gt;minor_shift
)paren
suffix:semicolon
id|check_partition
c_func
(paren
id|dev
comma
id|major
op_plus
(paren
id|drive
op_lshift
id|dev-&gt;minor_shift
)paren
)paren
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
id|j
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;sizes
(braket
id|i
)braket
op_assign
id|dev-&gt;part
(braket
id|i
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
id|blk_size
(braket
id|dev-&gt;major
)braket
op_assign
id|dev-&gt;sizes
suffix:semicolon
)brace
multiline_comment|/* This may be used only once, enforced by &squot;static int callable&squot; */
DECL|function|sys_setup
r_int
id|sys_setup
c_func
(paren
r_void
op_star
id|BIOS
)paren
(brace
r_static
r_int
id|callable
op_assign
l_int|1
suffix:semicolon
r_struct
id|gendisk
op_star
id|p
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|callable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|callable
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|gendisk_head
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
id|setup_dev
c_func
(paren
id|p
)paren
suffix:semicolon
id|nr
op_add_assign
id|p-&gt;nr_real
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
)paren
id|printk
c_func
(paren
l_string|&quot;Partition table%s ok.&bslash;n&bslash;r&quot;
comma
(paren
id|nr
OG
l_int|1
)paren
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#ifdef RAMDISK
id|rd_load
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|mount_root
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
