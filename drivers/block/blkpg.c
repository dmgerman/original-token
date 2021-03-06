multiline_comment|/*&n; * Partition table and disk geometry handling&n; *&n; * This obsoletes the partition-handling code in genhd.c:&n; * Userspace can look at a disk in arbitrary format and tell&n; * the kernel what partitions there are on the disk, and how&n; * these should be numbered.&n; * It also allows one to repartition a disk that is being used.&n; *&n; * A single ioctl with lots of subfunctions:&n; *&n; * Device number stuff:&n; *    get_whole_disk()          (given the device number of a partition, find&n; *                               the device number of the encompassing disk)&n; *    get_all_partitions()      (given the device number of a disk, return the&n; *                               device numbers of all its known partitions)&n; *&n; * Partition stuff:&n; *    add_partition()&n; *    delete_partition()&n; *    test_partition_in_use()   (also for test_disk_in_use)&n; *&n; * Geometry stuff:&n; *    get_geometry()&n; *    set_geometry()&n; *    get_bios_drivedata()&n; *&n; * For today, only the partition stuff - aeb, 990515&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;&t;&t;&t;/* for BLKRASET, ... */
macro_line|#include &lt;linux/sched.h&gt;&t;&t;/* for capable() */
macro_line|#include &lt;linux/blk.h&gt;&t;&t;&t;/* for set_device_ro() */
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/swap.h&gt;&t;&t;&t;/* for is_swap_partition() */
macro_line|#include &lt;linux/module.h&gt;               /* for EXPORT_SYMBOL */
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * What is the data describing a partition?&n; *&n; * 1. a device number (kdev_t)&n; * 2. a starting sector and number of sectors (hd_struct)&n; *    given in the part[] array of the gendisk structure for the drive.&n; *&n; * The number of sectors is replicated in the sizes[] array of&n; * the gendisk structure for the major, which again is copied to&n; * the blk_size[][] array.&n; * (However, hd_struct has the number of 512-byte sectors,&n; *  g-&gt;sizes[] and blk_size[][] have the number of 1024-byte blocks.)&n; * Note that several drives may have the same major.&n; */
multiline_comment|/* a linear search, superfluous when dev is a pointer */
DECL|function|get_gendisk
r_static
r_struct
id|gendisk
op_star
id|get_gendisk
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|gendisk
op_star
id|g
suffix:semicolon
r_int
id|m
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|g
op_assign
id|gendisk_head
suffix:semicolon
id|g
suffix:semicolon
id|g
op_assign
id|g-&gt;next
)paren
r_if
c_cond
(paren
id|g-&gt;major
op_eq
id|m
)paren
r_break
suffix:semicolon
r_return
id|g
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a partition.&n; *&n; * returns: EINVAL: bad parameters&n; *          ENXIO: cannot find drive&n; *          EBUSY: proposed partition overlaps an existing one&n; *                 or has the same number as an existing one&n; *          0: all OK.&n; */
DECL|function|add_partition
r_int
id|add_partition
c_func
(paren
id|kdev_t
id|dev
comma
r_struct
id|blkpg_partition
op_star
id|p
)paren
(brace
r_struct
id|gendisk
op_star
id|g
suffix:semicolon
r_int
r_int
id|ppstart
comma
id|pplength
suffix:semicolon
r_int
id|pstart
comma
id|plength
suffix:semicolon
r_int
id|i
comma
id|drive
comma
id|first_minor
comma
id|end_minor
comma
id|minor
suffix:semicolon
multiline_comment|/* convert bytes to sectors, check for fit in a hd_struct */
id|ppstart
op_assign
(paren
id|p-&gt;start
op_rshift
l_int|9
)paren
suffix:semicolon
id|pplength
op_assign
(paren
id|p-&gt;length
op_rshift
l_int|9
)paren
suffix:semicolon
id|pstart
op_assign
id|ppstart
suffix:semicolon
id|plength
op_assign
id|pplength
suffix:semicolon
r_if
c_cond
(paren
id|pstart
op_ne
id|ppstart
op_logical_or
id|plength
op_ne
id|pplength
op_logical_or
id|pstart
OL
l_int|0
op_logical_or
id|plength
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* find the drive major */
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* existing drive? */
id|drive
op_assign
(paren
id|MINOR
c_func
(paren
id|dev
)paren
op_rshift
id|g-&gt;minor_shift
)paren
suffix:semicolon
id|first_minor
op_assign
(paren
id|drive
op_lshift
id|g-&gt;minor_shift
)paren
suffix:semicolon
id|end_minor
op_assign
id|first_minor
op_plus
id|g-&gt;max_p
suffix:semicolon
r_if
c_cond
(paren
id|drive
op_ge
id|g-&gt;nr_real
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* drive and partition number OK? */
r_if
c_cond
(paren
id|first_minor
op_ne
id|MINOR
c_func
(paren
id|dev
)paren
op_logical_or
id|p-&gt;pno
op_le
l_int|0
op_logical_or
id|p-&gt;pno
op_ge
id|g-&gt;max_p
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* partition number in use? */
id|minor
op_assign
id|first_minor
op_plus
id|p-&gt;pno
suffix:semicolon
r_if
c_cond
(paren
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* overlap? */
r_for
c_loop
(paren
id|i
op_assign
id|first_minor
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|end_minor
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|pstart
op_plus
id|plength
op_le
id|g-&gt;part
(braket
id|i
)braket
dot
id|start_sect
op_logical_or
id|pstart
op_ge
id|g-&gt;part
(braket
id|i
)braket
dot
id|start_sect
op_plus
id|g-&gt;part
(braket
id|i
)braket
dot
id|nr_sects
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* all seems OK */
id|g-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_assign
id|pstart
suffix:semicolon
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
id|plength
suffix:semicolon
r_if
c_cond
(paren
id|g-&gt;sizes
)paren
id|g-&gt;sizes
(braket
id|minor
)braket
op_assign
(paren
id|plength
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a partition given by partition number&n; *&n; * returns: EINVAL: bad parameters&n; *          ENXIO: cannot find partition&n; *          EBUSY: partition is busy&n; *          0: all OK.&n; *&n; * Note that the dev argument refers to the entire disk, not the partition.&n; */
DECL|function|del_partition
r_int
id|del_partition
c_func
(paren
id|kdev_t
id|dev
comma
r_struct
id|blkpg_partition
op_star
id|p
)paren
(brace
r_struct
id|gendisk
op_star
id|g
suffix:semicolon
id|kdev_t
id|devp
suffix:semicolon
r_int
id|drive
comma
id|first_minor
comma
id|minor
suffix:semicolon
multiline_comment|/* find the drive major */
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* drive and partition number OK? */
id|drive
op_assign
(paren
id|MINOR
c_func
(paren
id|dev
)paren
op_rshift
id|g-&gt;minor_shift
)paren
suffix:semicolon
id|first_minor
op_assign
(paren
id|drive
op_lshift
id|g-&gt;minor_shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_minor
op_ne
id|MINOR
c_func
(paren
id|dev
)paren
op_logical_or
id|p-&gt;pno
op_le
l_int|0
op_logical_or
id|p-&gt;pno
op_ge
id|g-&gt;max_p
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* existing drive and partition? */
id|minor
op_assign
id|first_minor
op_plus
id|p-&gt;pno
suffix:semicolon
r_if
c_cond
(paren
id|drive
op_ge
id|g-&gt;nr_real
op_logical_or
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_eq
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* partition in use? Incomplete check for now. */
id|devp
op_assign
id|MKDEV
c_func
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_super
c_func
(paren
id|devp
)paren
op_logical_or
multiline_comment|/* mounted? */
id|is_swap_partition
c_func
(paren
id|devp
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* all seems OK */
id|fsync_dev
c_func
(paren
id|devp
)paren
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|devp
)paren
suffix:semicolon
id|g-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|g-&gt;sizes
)paren
id|g-&gt;sizes
(braket
id|minor
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|blkpg_ioctl
r_int
id|blkpg_ioctl
c_func
(paren
id|kdev_t
id|dev
comma
r_struct
id|blkpg_ioctl_arg
op_star
id|arg
)paren
(brace
r_struct
id|blkpg_ioctl_arg
id|a
suffix:semicolon
r_struct
id|blkpg_partition
id|p
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|blkpg_ioctl_arg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|a.op
)paren
(brace
r_case
id|BLKPG_ADD_PARTITION
suffix:colon
r_case
id|BLKPG_DEL_PARTITION
suffix:colon
id|len
op_assign
id|a.datalen
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
r_struct
id|blkpg_partition
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|p
comma
id|a.data
comma
r_sizeof
(paren
r_struct
id|blkpg_partition
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|a.op
op_eq
id|BLKPG_ADD_PARTITION
)paren
r_return
id|add_partition
c_func
(paren
id|dev
comma
op_amp
id|p
)paren
suffix:semicolon
r_else
r_return
id|del_partition
c_func
(paren
id|dev
comma
op_amp
id|p
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Common ioctl&squot;s for block devices&n; */
DECL|function|blk_ioctl
r_int
id|blk_ioctl
c_func
(paren
id|kdev_t
id|dev
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
r_int
id|intval
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKROSET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|intval
comma
(paren
r_int
op_star
)paren
(paren
id|arg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|set_device_ro
c_func
(paren
id|dev
comma
id|intval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKROGET
suffix:colon
id|intval
op_assign
(paren
id|is_read_only
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|intval
comma
(paren
r_int
op_star
)paren
(paren
id|arg
)paren
)paren
suffix:semicolon
r_case
id|BLKRASET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
id|arg
OG
l_int|0xff
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKRAGET
suffix:colon
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
r_return
id|put_user
c_func
(paren
id|read_ahead
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKFLSBUF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|fsync_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKSSZGET
suffix:colon
multiline_comment|/* get block device sector size as needed e.g. by fdisk */
id|intval
op_assign
id|get_hardsect_size
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|intval
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#if 0
r_case
id|BLKGETSIZE
suffix:colon
multiline_comment|/* Today get_gendisk() requires a linear scan;&n;&t;&t;&t;   add this when dev has pointer type. */
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g
)paren
id|longval
op_assign
l_int|0
suffix:semicolon
r_else
id|longval
op_assign
id|g-&gt;part
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
r_return
id|put_user
c_func
(paren
id|longval
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_case
id|BLKRRPART
suffix:colon
multiline_comment|/* Re-read partition tables */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_return
id|reread_partitions
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_case
id|BLKPG
suffix:colon
r_return
id|blkpg_ioctl
c_func
(paren
id|dev
comma
(paren
r_struct
id|blkpg_ioctl_arg
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKELVGET
suffix:colon
r_return
id|blkelvget_ioctl
c_func
(paren
op_amp
id|blk_get_queue
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|elevator
comma
(paren
id|blkelv_ioctl_arg_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKELVSET
suffix:colon
r_return
id|blkelvset_ioctl
c_func
(paren
op_amp
id|blk_get_queue
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|elevator
comma
(paren
id|blkelv_ioctl_arg_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|variable|blk_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|blk_ioctl
)paren
suffix:semicolon
eof
