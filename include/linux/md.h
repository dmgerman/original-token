multiline_comment|/*&n;   md.h : Multiple Devices driver for Linux&n;          Copyright (C) 1994-96 Marc ZYNGIER&n;&t;  &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;  &lt;maz@gloups.fdn.fr&gt;&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_H
DECL|macro|_MD_H
mdefine_line|#define _MD_H
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Different major versions are not compatible.&n; * Different minor versions are only downward compatible.&n; * Different patchlevel versions are downward and upward compatible.&n; */
DECL|macro|MD_MAJOR_VERSION
mdefine_line|#define MD_MAJOR_VERSION&t;&t;0
DECL|macro|MD_MINOR_VERSION
mdefine_line|#define MD_MINOR_VERSION&t;&t;36
DECL|macro|MD_PATCHLEVEL_VERSION
mdefine_line|#define MD_PATCHLEVEL_VERSION&t;&t;6
DECL|macro|MD_DEFAULT_DISK_READAHEAD
mdefine_line|#define MD_DEFAULT_DISK_READAHEAD&t;(256 * 1024)
multiline_comment|/* ioctls */
DECL|macro|REGISTER_DEV
mdefine_line|#define REGISTER_DEV _IO (MD_MAJOR, 1)
DECL|macro|START_MD
mdefine_line|#define START_MD     _IO (MD_MAJOR, 2)
DECL|macro|STOP_MD
mdefine_line|#define STOP_MD      _IO (MD_MAJOR, 3)
multiline_comment|/*&n;   personalities :&n;   Byte 0 : Chunk size factor&n;   Byte 1 : Fault tolerance count for each physical device&n;            (   0 means no fault tolerance,&n;             0xFF means always tolerate faults), not used by now.&n;   Byte 2 : Personality&n;   Byte 3 : Reserved.&n; */
DECL|macro|FAULT_SHIFT
mdefine_line|#define FAULT_SHIFT       8
DECL|macro|PERSONALITY_SHIFT
mdefine_line|#define PERSONALITY_SHIFT 16
DECL|macro|FACTOR_MASK
mdefine_line|#define FACTOR_MASK       0x000000FFUL
DECL|macro|FAULT_MASK
mdefine_line|#define FAULT_MASK        0x0000FF00UL
DECL|macro|PERSONALITY_MASK
mdefine_line|#define PERSONALITY_MASK  0x00FF0000UL
DECL|macro|MD_RESERVED
mdefine_line|#define MD_RESERVED       0&t;/* Not used by now */
DECL|macro|LINEAR
mdefine_line|#define LINEAR            (1UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|STRIPED
mdefine_line|#define STRIPED           (2UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|RAID0
mdefine_line|#define RAID0             STRIPED
DECL|macro|RAID1
mdefine_line|#define RAID1             (3UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|RAID5
mdefine_line|#define RAID5             (4UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|MAX_PERSONALITY
mdefine_line|#define MAX_PERSONALITY   5
multiline_comment|/*&n; * MD superblock.&n; *&n; * The MD superblock maintains some statistics on each MD configuration.&n; * Each real device in the MD set contains it near the end of the device.&n; * Some of the ideas are copied from the ext2fs implementation.&n; *&n; * We currently use 4096 bytes as follows:&n; *&n; *&t;word offset&t;function&n; *&n; *&t;   0  -    31&t;Constant generic MD device information.&n; *        32  -    63   Generic state information.&n; *&t;  64  -   127&t;Personality specific information.&n; *&t; 128  -   511&t;12 32-words descriptors of the disks in the raid set.&n; *&t; 512  -   911&t;Reserved.&n; *&t; 912  -  1023&t;Disk specific descriptor.&n; */
multiline_comment|/*&n; * If x is the real device size in bytes, we return an apparent size of:&n; *&n; *&t;y = (x &amp; ~(MD_RESERVED_BYTES - 1)) - MD_RESERVED_BYTES&n; *&n; * and place the 4kB superblock at offset y.&n; */
DECL|macro|MD_RESERVED_BYTES
mdefine_line|#define MD_RESERVED_BYTES&t;&t;(64 * 1024)
DECL|macro|MD_RESERVED_SECTORS
mdefine_line|#define MD_RESERVED_SECTORS&t;&t;(MD_RESERVED_BYTES / 512)
DECL|macro|MD_RESERVED_BLOCKS
mdefine_line|#define MD_RESERVED_BLOCKS&t;&t;(MD_RESERVED_BYTES / BLOCK_SIZE)
DECL|macro|MD_NEW_SIZE_SECTORS
mdefine_line|#define MD_NEW_SIZE_SECTORS(x)&t;&t;((x &amp; ~(MD_RESERVED_SECTORS - 1)) - MD_RESERVED_SECTORS)
DECL|macro|MD_NEW_SIZE_BLOCKS
mdefine_line|#define MD_NEW_SIZE_BLOCKS(x)&t;&t;((x &amp; ~(MD_RESERVED_BLOCKS - 1)) - MD_RESERVED_BLOCKS)
DECL|macro|MD_SB_BYTES
mdefine_line|#define MD_SB_BYTES&t;&t;&t;4096
DECL|macro|MD_SB_WORDS
mdefine_line|#define MD_SB_WORDS&t;&t;&t;(MD_SB_BYTES / 4)
DECL|macro|MD_SB_BLOCKS
mdefine_line|#define MD_SB_BLOCKS&t;&t;&t;(MD_SB_BYTES / BLOCK_SIZE)
DECL|macro|MD_SB_SECTORS
mdefine_line|#define MD_SB_SECTORS&t;&t;&t;(MD_SB_BYTES / 512)
multiline_comment|/*&n; * The following are counted in 32-bit words&n; */
DECL|macro|MD_SB_GENERIC_OFFSET
mdefine_line|#define&t;MD_SB_GENERIC_OFFSET&t;&t;0
DECL|macro|MD_SB_PERSONALITY_OFFSET
mdefine_line|#define MD_SB_PERSONALITY_OFFSET&t;64
DECL|macro|MD_SB_DISKS_OFFSET
mdefine_line|#define MD_SB_DISKS_OFFSET&t;&t;128
DECL|macro|MD_SB_DESCRIPTOR_OFFSET
mdefine_line|#define MD_SB_DESCRIPTOR_OFFSET&t;&t;992
DECL|macro|MD_SB_GENERIC_CONSTANT_WORDS
mdefine_line|#define MD_SB_GENERIC_CONSTANT_WORDS&t;32
DECL|macro|MD_SB_GENERIC_STATE_WORDS
mdefine_line|#define MD_SB_GENERIC_STATE_WORDS&t;32
DECL|macro|MD_SB_GENERIC_WORDS
mdefine_line|#define MD_SB_GENERIC_WORDS&t;&t;(MD_SB_GENERIC_CONSTANT_WORDS + MD_SB_GENERIC_STATE_WORDS)
DECL|macro|MD_SB_PERSONALITY_WORDS
mdefine_line|#define MD_SB_PERSONALITY_WORDS&t;&t;64
DECL|macro|MD_SB_DISKS_WORDS
mdefine_line|#define MD_SB_DISKS_WORDS&t;&t;384
DECL|macro|MD_SB_DESCRIPTOR_WORDS
mdefine_line|#define MD_SB_DESCRIPTOR_WORDS&t;&t;32
DECL|macro|MD_SB_RESERVED_WORDS
mdefine_line|#define MD_SB_RESERVED_WORDS&t;&t;(1024 - MD_SB_GENERIC_WORDS - MD_SB_PERSONALITY_WORDS - MD_SB_DISKS_WORDS - MD_SB_DESCRIPTOR_WORDS)
DECL|macro|MD_SB_EQUAL_WORDS
mdefine_line|#define MD_SB_EQUAL_WORDS&t;&t;(MD_SB_GENERIC_WORDS + MD_SB_PERSONALITY_WORDS + MD_SB_DISKS_WORDS)
DECL|macro|MD_SB_DISKS
mdefine_line|#define MD_SB_DISKS&t;&t;&t;(MD_SB_DISKS_WORDS / MD_SB_DESCRIPTOR_WORDS)
multiline_comment|/*&n; * Device &quot;operational&quot; state bits&n; */
DECL|macro|MD_FAULTY_DEVICE
mdefine_line|#define MD_FAULTY_DEVICE&t;&t;0&t;/* Device is faulty / operational */
DECL|macro|MD_ACTIVE_DEVICE
mdefine_line|#define MD_ACTIVE_DEVICE&t;&t;1&t;/* Device is a part or the raid set / spare disk */
DECL|macro|MD_SYNC_DEVICE
mdefine_line|#define MD_SYNC_DEVICE&t;&t;&t;2&t;/* Device is in sync with the raid set */
DECL|struct|md_device_descriptor_s
r_typedef
r_struct
id|md_device_descriptor_s
(brace
DECL|member|number
id|__u32
id|number
suffix:semicolon
multiline_comment|/* 0 Device number in the entire set */
DECL|member|major
id|__u32
id|major
suffix:semicolon
multiline_comment|/* 1 Device major number */
DECL|member|minor
id|__u32
id|minor
suffix:semicolon
multiline_comment|/* 2 Device minor number */
DECL|member|raid_disk
id|__u32
id|raid_disk
suffix:semicolon
multiline_comment|/* 3 The role of the device in the raid set */
DECL|member|state
id|__u32
id|state
suffix:semicolon
multiline_comment|/* 4 Operational state */
DECL|member|reserved
id|__u32
id|reserved
(braket
id|MD_SB_DESCRIPTOR_WORDS
op_minus
l_int|5
)braket
suffix:semicolon
DECL|typedef|md_descriptor_t
)brace
id|md_descriptor_t
suffix:semicolon
DECL|macro|MD_SB_MAGIC
mdefine_line|#define MD_SB_MAGIC&t;&t;0xa92b4efc
multiline_comment|/*&n; * Superblock state bits&n; */
DECL|macro|MD_SB_CLEAN
mdefine_line|#define MD_SB_CLEAN&t;&t;0
DECL|macro|MD_SB_ERRORS
mdefine_line|#define MD_SB_ERRORS&t;&t;1
DECL|struct|md_superblock_s
r_typedef
r_struct
id|md_superblock_s
(brace
multiline_comment|/*&n;&t; * Constant generic information&n;&t; */
DECL|member|md_magic
id|__u32
id|md_magic
suffix:semicolon
multiline_comment|/*  0 MD identifier */
DECL|member|major_version
id|__u32
id|major_version
suffix:semicolon
multiline_comment|/*  1 major version to which the set conforms */
DECL|member|minor_version
id|__u32
id|minor_version
suffix:semicolon
multiline_comment|/*  2 minor version to which the set conforms */
DECL|member|patch_version
id|__u32
id|patch_version
suffix:semicolon
multiline_comment|/*  3 patchlevel version to which the set conforms */
DECL|member|gvalid_words
id|__u32
id|gvalid_words
suffix:semicolon
multiline_comment|/*  4 Number of non-reserved words in this section */
DECL|member|set_magic
id|__u32
id|set_magic
suffix:semicolon
multiline_comment|/*  5 Raid set identifier */
DECL|member|ctime
id|__u32
id|ctime
suffix:semicolon
multiline_comment|/*  6 Creation time */
DECL|member|level
id|__u32
id|level
suffix:semicolon
multiline_comment|/*  7 Raid personality (mirroring, raid5, ...) */
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/*  8 Apparent size of each individual disk, in kB */
DECL|member|nr_disks
id|__u32
id|nr_disks
suffix:semicolon
multiline_comment|/*  9 Number of total disks in the raid set */
DECL|member|raid_disks
id|__u32
id|raid_disks
suffix:semicolon
multiline_comment|/* 10 Number of disks in a fully functional raid set */
DECL|member|gstate_creserved
id|__u32
id|gstate_creserved
(braket
id|MD_SB_GENERIC_CONSTANT_WORDS
op_minus
l_int|11
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Generic state information&n;&t; */
DECL|member|utime
id|__u32
id|utime
suffix:semicolon
multiline_comment|/*  0 Superblock update time */
DECL|member|state
id|__u32
id|state
suffix:semicolon
multiline_comment|/*  1 State bits (clean, ...) */
DECL|member|active_disks
id|__u32
id|active_disks
suffix:semicolon
multiline_comment|/*  2 Number of currently active disks (some non-faulty disks might not be in sync) */
DECL|member|working_disks
id|__u32
id|working_disks
suffix:semicolon
multiline_comment|/*  3 Number of working disks */
DECL|member|failed_disks
id|__u32
id|failed_disks
suffix:semicolon
multiline_comment|/*  4 Number of failed disks */
DECL|member|spare_disks
id|__u32
id|spare_disks
suffix:semicolon
multiline_comment|/*  5 Number of spare disks */
DECL|member|gstate_sreserved
id|__u32
id|gstate_sreserved
(braket
id|MD_SB_GENERIC_STATE_WORDS
op_minus
l_int|6
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Personality information&n;&t; */
DECL|member|parity_algorithm
id|__u32
id|parity_algorithm
suffix:semicolon
DECL|member|chunk_size
id|__u32
id|chunk_size
suffix:semicolon
DECL|member|pstate_reserved
id|__u32
id|pstate_reserved
(braket
id|MD_SB_PERSONALITY_WORDS
op_minus
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Disks information&n;&t; */
DECL|member|disks
id|md_descriptor_t
id|disks
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Reserved&n;&t; */
DECL|member|reserved
id|__u32
id|reserved
(braket
id|MD_SB_RESERVED_WORDS
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Active descriptor&n;&t; */
DECL|member|descriptor
id|md_descriptor_t
id|descriptor
suffix:semicolon
DECL|typedef|md_superblock_t
)brace
id|md_superblock_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
multiline_comment|/*&n; * Kernel-based reconstruction is mostly working, but still requires&n; * some additional work.&n; */
DECL|macro|SUPPORT_RECONSTRUCTION
mdefine_line|#define SUPPORT_RECONSTRUCTION&t;0
DECL|macro|MAX_REAL
mdefine_line|#define MAX_REAL     8&t;&t;/* Max number of physical dev per md dev */
DECL|macro|MAX_MD_DEV
mdefine_line|#define MAX_MD_DEV   4&t;&t;/* Max number of md dev */
macro_line|#if SUPPORT_RECONSTRUCTION
DECL|macro|MAX_MD_THREADS
mdefine_line|#define MAX_MD_THREADS (MAX_MD_DEV * 3)&t;/* Max number of kernel threads */
macro_line|#else
DECL|macro|MAX_MD_THREADS
mdefine_line|#define MAX_MD_THREADS (MAX_MD_DEV)&t;/* Max number of kernel threads */
macro_line|#endif /* SUPPORT_RECONSTRUCTION */
DECL|macro|FACTOR
mdefine_line|#define FACTOR(a)         ((a)-&gt;repartition &amp; FACTOR_MASK)
DECL|macro|MAX_FAULT
mdefine_line|#define MAX_FAULT(a)      (((a)-&gt;repartition &amp; FAULT_MASK)&gt;&gt;8)
DECL|macro|PERSONALITY
mdefine_line|#define PERSONALITY(a)    ((a)-&gt;repartition &amp; PERSONALITY_MASK)
DECL|macro|FACTOR_SHIFT
mdefine_line|#define FACTOR_SHIFT(a) (PAGE_SHIFT + (a) - 10)
DECL|struct|real_dev
r_struct
id|real_dev
(brace
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
multiline_comment|/* Device number */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Device size (in blocks) */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* Real device offset (in blocks) in md dev&n;&t;&t;&t;&t;   (only used in linear mode) */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* Lock inode */
DECL|member|sb
id|md_superblock_t
op_star
id|sb
suffix:semicolon
DECL|member|sb_offset
id|u32
id|sb_offset
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|md_dev
suffix:semicolon
DECL|macro|SPARE_INACTIVE
mdefine_line|#define SPARE_INACTIVE&t;0
DECL|macro|SPARE_WRITE
mdefine_line|#define SPARE_WRITE&t;1
DECL|macro|SPARE_ACTIVE
mdefine_line|#define SPARE_ACTIVE&t;2
DECL|struct|md_personality
r_struct
id|md_personality
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|map
r_int
(paren
op_star
id|map
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|kdev_t
op_star
id|rdev
comma
r_int
r_int
op_star
id|rsector
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|make_request
r_int
(paren
op_star
id|make_request
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|member|end_request
r_void
(paren
op_star
id|end_request
)paren
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
suffix:semicolon
DECL|member|run
r_int
(paren
op_star
id|run
)paren
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|status
r_int
(paren
op_star
id|status
)paren
(paren
r_char
op_star
id|page
comma
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
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
suffix:semicolon
DECL|member|max_invalid_dev
r_int
id|max_invalid_dev
suffix:semicolon
DECL|member|error_handler
r_int
(paren
op_star
id|error_handler
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|kdev_t
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Some personalities (RAID-1, RAID-5) can get disks hot-added and&n; * hot-removed. Hot removal is different from failure. (failure marks&n; * a disk inactive, but the disk is still part of the array)&n; */
DECL|member|hot_add_disk
r_int
(paren
op_star
id|hot_add_disk
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|kdev_t
id|dev
)paren
suffix:semicolon
DECL|member|hot_remove_disk
r_int
(paren
op_star
id|hot_remove_disk
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|kdev_t
id|dev
)paren
suffix:semicolon
DECL|member|mark_spare
r_int
(paren
op_star
id|mark_spare
)paren
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|md_descriptor_t
op_star
id|descriptor
comma
r_int
id|state
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|md_dev
r_struct
id|md_dev
(brace
DECL|member|devices
r_struct
id|real_dev
id|devices
(braket
id|MAX_REAL
)braket
suffix:semicolon
DECL|member|pers
r_struct
id|md_personality
op_star
id|pers
suffix:semicolon
DECL|member|sb
id|md_superblock_t
op_star
id|sb
suffix:semicolon
DECL|member|sb_dirty
r_int
id|sb_dirty
suffix:semicolon
DECL|member|repartition
r_int
id|repartition
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|nb_dev
r_int
id|nb_dev
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|md_thread
r_struct
id|md_thread
(brace
DECL|member|run
r_void
(paren
op_star
id|run
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|wqueue
r_struct
id|wait_queue
op_star
id|wqueue
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|THREAD_WAKEUP
mdefine_line|#define THREAD_WAKEUP&t;0
r_extern
r_struct
id|md_dev
id|md_dev
(braket
id|MAX_MD_DEV
)braket
suffix:semicolon
r_extern
r_int
id|md_size
(braket
id|MAX_MD_DEV
)braket
suffix:semicolon
r_extern
r_int
id|md_maxreadahead
(braket
id|MAX_MD_DEV
)braket
suffix:semicolon
r_extern
r_char
op_star
id|partition_name
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_md_personality
(paren
r_int
id|p_num
comma
r_struct
id|md_personality
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|unregister_md_personality
(paren
r_int
id|p_num
)paren
suffix:semicolon
r_extern
r_struct
id|md_thread
op_star
id|md_register_thread
(paren
r_void
(paren
op_star
id|run
)paren
(paren
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|md_unregister_thread
(paren
r_struct
id|md_thread
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_void
id|md_wakeup_thread
c_func
(paren
r_struct
id|md_thread
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_int
id|md_update_sb
(paren
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_int
id|md_do_sync
c_func
(paren
r_struct
id|md_dev
op_star
id|mddev
)paren
suffix:semicolon
macro_line|#endif __KERNEL__
macro_line|#endif _MD_H
eof
