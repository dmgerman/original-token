macro_line|#ifndef _LINUX_GENHD_H
DECL|macro|_LINUX_GENHD_H
mdefine_line|#define _LINUX_GENHD_H
multiline_comment|/*&n; * &t;genhd.h Copyright (C) 1992 Drew Eckhardt&n; *&t;Generic hard disk header file by  &n; * &t;&t;Drew Eckhardt&n; *&n; *&t;&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CONFIG_MSDOS_PARTITION
mdefine_line|#define CONFIG_MSDOS_PARTITION 1
macro_line|#ifdef __alpha__
DECL|macro|CONFIG_OSF_PARTITION
mdefine_line|#define CONFIG_OSF_PARTITION 1
macro_line|#endif
macro_line|#if defined(__sparc__) || defined(CONFIG_SMD_DISKLABEL)
DECL|macro|CONFIG_SUN_PARTITION
mdefine_line|#define CONFIG_SUN_PARTITION 1
macro_line|#endif
multiline_comment|/* These three have identical behaviour; use the second one if DOS fdisk gets&n;   confused about extended/logical partitions starting past cylinder 1023. */
DECL|macro|DOS_EXTENDED_PARTITION
mdefine_line|#define DOS_EXTENDED_PARTITION 5
DECL|macro|LINUX_EXTENDED_PARTITION
mdefine_line|#define LINUX_EXTENDED_PARTITION 0x85
DECL|macro|WIN98_EXTENDED_PARTITION
mdefine_line|#define WIN98_EXTENDED_PARTITION 0x0f
DECL|macro|LINUX_SWAP_PARTITION
mdefine_line|#define LINUX_SWAP_PARTITION&t;0x82
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
DECL|macro|SOLARIS_X86_PARTITION
mdefine_line|#define SOLARIS_X86_PARTITION&t;LINUX_SWAP_PARTITION
macro_line|#endif
DECL|macro|DM6_PARTITION
mdefine_line|#define DM6_PARTITION&t;&t;0x54&t;/* has DDO: use xlated geom &amp; offset */
DECL|macro|EZD_PARTITION
mdefine_line|#define EZD_PARTITION&t;&t;0x55&t;/* EZ-DRIVE:  same as DM6 (we think) */
DECL|macro|DM6_AUX1PARTITION
mdefine_line|#define DM6_AUX1PARTITION&t;0x51&t;/* no DDO:  use xlated geom */
DECL|macro|DM6_AUX3PARTITION
mdefine_line|#define DM6_AUX3PARTITION&t;0x53&t;/* no DDO:  use xlated geom */
DECL|struct|partition
r_struct
id|partition
(brace
DECL|member|boot_ind
r_int
r_char
id|boot_ind
suffix:semicolon
multiline_comment|/* 0x80 - active */
DECL|member|head
r_int
r_char
id|head
suffix:semicolon
multiline_comment|/* starting head */
DECL|member|sector
r_int
r_char
id|sector
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|cyl
r_int
r_char
id|cyl
suffix:semicolon
multiline_comment|/* starting cylinder */
DECL|member|sys_ind
r_int
r_char
id|sys_ind
suffix:semicolon
multiline_comment|/* What partition type */
DECL|member|end_head
r_int
r_char
id|end_head
suffix:semicolon
multiline_comment|/* end head */
DECL|member|end_sector
r_int
r_char
id|end_sector
suffix:semicolon
multiline_comment|/* end sector */
DECL|member|end_cyl
r_int
r_char
id|end_cyl
suffix:semicolon
multiline_comment|/* end cylinder */
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector counting from 0 */
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
multiline_comment|/* nr of sectors in partition */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|hd_struct
r_struct
id|hd_struct
(brace
DECL|member|start_sect
r_int
id|start_sect
suffix:semicolon
DECL|member|nr_sects
r_int
id|nr_sects
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gendisk
r_struct
id|gendisk
(brace
DECL|member|major
r_int
id|major
suffix:semicolon
multiline_comment|/* major number of driver */
DECL|member|major_name
r_const
r_char
op_star
id|major_name
suffix:semicolon
multiline_comment|/* name of major driver */
DECL|member|minor_shift
r_int
id|minor_shift
suffix:semicolon
multiline_comment|/* number of times minor is shifted to&n;&t;&t;&t;&t;&t;   get real minor */
DECL|member|max_p
r_int
id|max_p
suffix:semicolon
multiline_comment|/* maximum partitions per device */
DECL|member|max_nr
r_int
id|max_nr
suffix:semicolon
multiline_comment|/* maximum number of real devices */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|gendisk
op_star
)paren
suffix:semicolon
multiline_comment|/* Initialization called before we do our thing */
DECL|member|part
r_struct
id|hd_struct
op_star
id|part
suffix:semicolon
multiline_comment|/* partition table */
DECL|member|sizes
r_int
op_star
id|sizes
suffix:semicolon
multiline_comment|/* device size in blocks, copied to blk_size[] */
DECL|member|nr_real
r_int
id|nr_real
suffix:semicolon
multiline_comment|/* number of real devices */
DECL|member|real_devices
r_void
op_star
id|real_devices
suffix:semicolon
multiline_comment|/* internal use */
DECL|member|next
r_struct
id|gendisk
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
DECL|macro|SOLARIS_X86_NUMSLICE
mdefine_line|#define SOLARIS_X86_NUMSLICE&t;8
DECL|macro|SOLARIS_X86_VTOC_SANE
mdefine_line|#define SOLARIS_X86_VTOC_SANE&t;(0x600DDEEEUL)
DECL|struct|solaris_x86_slice
r_struct
id|solaris_x86_slice
(brace
DECL|member|s_tag
id|ushort
id|s_tag
suffix:semicolon
multiline_comment|/* ID tag of partition */
DECL|member|s_flag
id|ushort
id|s_flag
suffix:semicolon
multiline_comment|/* permision flags */
DECL|member|s_start
id|daddr_t
id|s_start
suffix:semicolon
multiline_comment|/* start sector no of partition */
DECL|member|s_size
r_int
id|s_size
suffix:semicolon
multiline_comment|/* # of blocks in partition */
)brace
suffix:semicolon
DECL|struct|solaris_x86_vtoc
r_struct
id|solaris_x86_vtoc
(brace
DECL|member|v_bootinfo
r_int
r_int
id|v_bootinfo
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* info needed by mboot (unsupported) */
DECL|member|v_sanity
r_int
r_int
id|v_sanity
suffix:semicolon
multiline_comment|/* to verify vtoc sanity */
DECL|member|v_version
r_int
r_int
id|v_version
suffix:semicolon
multiline_comment|/* layout version */
DECL|member|v_volume
r_char
id|v_volume
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* volume name */
DECL|member|v_sectorsz
id|ushort
id|v_sectorsz
suffix:semicolon
multiline_comment|/* sector size in bytes */
DECL|member|v_nparts
id|ushort
id|v_nparts
suffix:semicolon
multiline_comment|/* number of partitions */
DECL|member|v_reserved
r_int
r_int
id|v_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* free space */
r_struct
id|solaris_x86_slice
DECL|member|v_slice
id|v_slice
(braket
id|SOLARIS_X86_NUMSLICE
)braket
suffix:semicolon
multiline_comment|/* slice headers */
DECL|member|timestamp
id|time_t
id|timestamp
(braket
id|SOLARIS_X86_NUMSLICE
)braket
suffix:semicolon
multiline_comment|/* timestamp (unsupported) */
DECL|member|v_asciilabel
r_char
id|v_asciilabel
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* for compatibility */
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SOLARIS_X86_PARTITION */
macro_line|#ifdef CONFIG_BSD_DISKLABEL
multiline_comment|/*&n; * BSD disklabel support by Yossi Gottlieb &lt;yogo@math.tau.ac.il&gt;&n; */
DECL|macro|BSD_PARTITION
mdefine_line|#define BSD_PARTITION&t;&t;0xa5&t;/* Partition ID */
DECL|macro|BSD_DISKMAGIC
mdefine_line|#define BSD_DISKMAGIC&t;(0x82564557UL)&t;/* The disk magic number */
DECL|macro|BSD_MAXPARTITIONS
mdefine_line|#define BSD_MAXPARTITIONS&t;8
DECL|macro|BSD_FS_UNUSED
mdefine_line|#define BSD_FS_UNUSED&t;&t;0&t;/* disklabel unused partition entry ID */
DECL|struct|bsd_disklabel
r_struct
id|bsd_disklabel
(brace
DECL|member|d_magic
id|__u32
id|d_magic
suffix:semicolon
multiline_comment|/* the magic number */
DECL|member|d_type
id|__s16
id|d_type
suffix:semicolon
multiline_comment|/* drive type */
DECL|member|d_subtype
id|__s16
id|d_subtype
suffix:semicolon
multiline_comment|/* controller/d_type specific */
DECL|member|d_typename
r_char
id|d_typename
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* type name, e.g. &quot;eagle&quot; */
DECL|member|d_packname
r_char
id|d_packname
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* pack identifier */
DECL|member|d_secsize
id|__u32
id|d_secsize
suffix:semicolon
multiline_comment|/* # of bytes per sector */
DECL|member|d_nsectors
id|__u32
id|d_nsectors
suffix:semicolon
multiline_comment|/* # of data sectors per track */
DECL|member|d_ntracks
id|__u32
id|d_ntracks
suffix:semicolon
multiline_comment|/* # of tracks per cylinder */
DECL|member|d_ncylinders
id|__u32
id|d_ncylinders
suffix:semicolon
multiline_comment|/* # of data cylinders per unit */
DECL|member|d_secpercyl
id|__u32
id|d_secpercyl
suffix:semicolon
multiline_comment|/* # of data sectors per cylinder */
DECL|member|d_secperunit
id|__u32
id|d_secperunit
suffix:semicolon
multiline_comment|/* # of data sectors per unit */
DECL|member|d_sparespertrack
id|__u16
id|d_sparespertrack
suffix:semicolon
multiline_comment|/* # of spare sectors per track */
DECL|member|d_sparespercyl
id|__u16
id|d_sparespercyl
suffix:semicolon
multiline_comment|/* # of spare sectors per cylinder */
DECL|member|d_acylinders
id|__u32
id|d_acylinders
suffix:semicolon
multiline_comment|/* # of alt. cylinders per unit */
DECL|member|d_rpm
id|__u16
id|d_rpm
suffix:semicolon
multiline_comment|/* rotational speed */
DECL|member|d_interleave
id|__u16
id|d_interleave
suffix:semicolon
multiline_comment|/* hardware sector interleave */
DECL|member|d_trackskew
id|__u16
id|d_trackskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per track */
DECL|member|d_cylskew
id|__u16
id|d_cylskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per cylinder */
DECL|member|d_headswitch
id|__u32
id|d_headswitch
suffix:semicolon
multiline_comment|/* head switch time, usec */
DECL|member|d_trkseek
id|__u32
id|d_trkseek
suffix:semicolon
multiline_comment|/* track-to-track seek, usec */
DECL|member|d_flags
id|__u32
id|d_flags
suffix:semicolon
multiline_comment|/* generic flags */
DECL|macro|NDDATA
mdefine_line|#define NDDATA 5
DECL|member|d_drivedata
id|__u32
id|d_drivedata
(braket
id|NDDATA
)braket
suffix:semicolon
multiline_comment|/* drive-type specific information */
DECL|macro|NSPARE
mdefine_line|#define NSPARE 5
DECL|member|d_spare
id|__u32
id|d_spare
(braket
id|NSPARE
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|d_magic2
id|__u32
id|d_magic2
suffix:semicolon
multiline_comment|/* the magic number (again) */
DECL|member|d_checksum
id|__u16
id|d_checksum
suffix:semicolon
multiline_comment|/* xor of data incl. partitions */
multiline_comment|/* filesystem and partition information: */
DECL|member|d_npartitions
id|__u16
id|d_npartitions
suffix:semicolon
multiline_comment|/* number of partitions in following */
DECL|member|d_bbsize
id|__u32
id|d_bbsize
suffix:semicolon
multiline_comment|/* size of boot area at sn0, bytes */
DECL|member|d_sbsize
id|__u32
id|d_sbsize
suffix:semicolon
multiline_comment|/* max size of fs superblock, bytes */
DECL|struct|bsd_partition
r_struct
id|bsd_partition
(brace
multiline_comment|/* the partition table */
DECL|member|p_size
id|__u32
id|p_size
suffix:semicolon
multiline_comment|/* number of sectors in partition */
DECL|member|p_offset
id|__u32
id|p_offset
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|p_fsize
id|__u32
id|p_fsize
suffix:semicolon
multiline_comment|/* filesystem basic fragment size */
DECL|member|p_fstype
id|__u8
id|p_fstype
suffix:semicolon
multiline_comment|/* filesystem type, see below */
DECL|member|p_frag
id|__u8
id|p_frag
suffix:semicolon
multiline_comment|/* filesystem fragments per block */
DECL|member|p_cpg
id|__u16
id|p_cpg
suffix:semicolon
multiline_comment|/* filesystem cylinders per group */
DECL|member|d_partitions
)brace
id|d_partitions
(braket
id|BSD_MAXPARTITIONS
)braket
suffix:semicolon
multiline_comment|/* actually may be more */
)brace
suffix:semicolon
macro_line|#endif&t;/* CONFIG_BSD_DISKLABEL */
r_extern
r_struct
id|gendisk
op_star
id|gendisk_head
suffix:semicolon
multiline_comment|/* linked list of disks */
multiline_comment|/*&n; * disk_name() is used by genhd.c and md.c.&n; * It formats the devicename of the indicated disk&n; * into the supplied buffer, and returns a pointer&n; * to that same buffer (for convenience).&n; */
r_char
op_star
id|disk_name
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
macro_line|#endif
eof
