multiline_comment|/*&n; *  linux/include/linux/ufs_fs.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Clean swab support by Fare &lt;rideau@ens.fr&gt;&n; * just hope no one is using NNUUXXI on __?64 structure elements&n; */
macro_line|#ifndef __LINUX_UFS_FS_H
DECL|macro|__LINUX_UFS_FS_H
mdefine_line|#define __LINUX_UFS_FS_H
DECL|macro|UFS_HEAVY_DEBUG
macro_line|#undef UFS_HEAVY_DEBUG
multiline_comment|/*#define UFS_HEAVY_DEBUG 1*/
multiline_comment|/* Uncomment the line above when hacking ufs code */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|macro|UFS_BBLOCK
mdefine_line|#define UFS_BBLOCK 0
DECL|macro|UFS_BBSIZE
mdefine_line|#define UFS_BBSIZE 8192
DECL|macro|UFS_SBLOCK
mdefine_line|#define UFS_SBLOCK 8192
DECL|macro|UFS_SBSIZE
mdefine_line|#define UFS_SBSIZE 8192
DECL|macro|UFS_MAGIC
mdefine_line|#define UFS_MAGIC 0x00011954
DECL|macro|UFS_CIGAM
mdefine_line|#define UFS_CIGAM 0x54190100 /* byteswapped MAGIC */
DECL|macro|UFS_FSIZE
mdefine_line|#define UFS_FSIZE 1024
DECL|macro|UFS_BSIZE
mdefine_line|#define UFS_BSIZE 8192
DECL|macro|UFS_NDADDR
mdefine_line|#define UFS_NDADDR 12
DECL|macro|UFS_NINDIR
mdefine_line|#define UFS_NINDIR 3
DECL|macro|UFS_IND_BLOCK
mdefine_line|#define UFS_IND_BLOCK&t;(UFS_NDADDR + 0)
DECL|macro|UFS_DIND_BLOCK
mdefine_line|#define UFS_DIND_BLOCK&t;(UFS_NDADDR + 1)
DECL|macro|UFS_TIND_BLOCK
mdefine_line|#define UFS_TIND_BLOCK&t;(UFS_NDADDR + 2)
DECL|macro|UFS_ROOTINO
mdefine_line|#define UFS_ROOTINO 2
DECL|macro|UFS_USEEFT
mdefine_line|#define UFS_USEEFT  ((__u16)65535)
DECL|macro|UFS_FSOK
mdefine_line|#define UFS_FSOK      0x7c269d38
DECL|macro|UFS_FSACTIVE
mdefine_line|#define UFS_FSACTIVE  ((char)0x00)
DECL|macro|UFS_FSCLEAN
mdefine_line|#define UFS_FSCLEAN   ((char)0x01)
DECL|macro|UFS_FSSTABLE
mdefine_line|#define UFS_FSSTABLE  ((char)0x02)
DECL|macro|UFS_FSBAD
mdefine_line|#define UFS_FSBAD     ((char)0xff)
multiline_comment|/* Flags for ufs_sb_info */
DECL|macro|UFS_DEBUG
mdefine_line|#define UFS_DEBUG       0x00000001
DECL|macro|UFS_DEBUG_INODE
mdefine_line|#define UFS_DEBUG_INODE 0x00000002
DECL|macro|UFS_DEBUG_NAMEI
mdefine_line|#define UFS_DEBUG_NAMEI 0x00000004
DECL|macro|UFS_DEBUG_LINKS
mdefine_line|#define UFS_DEBUG_LINKS 0x00000008
macro_line|#ifdef UFS_HEAVY_DEBUG
DECL|macro|UFS_DEBUG_INITIAL
macro_line|#  define UFS_DEBUG_INITIAL UFS_DEBUG
macro_line|#else
DECL|macro|UFS_DEBUG_INITIAL
macro_line|#  define UFS_DEBUG_INITIAL 0
macro_line|#endif
multiline_comment|/* (!) HERE WE ASSUME EITHER BIG OR LITTLE ENDIAN UFSes */
DECL|macro|UFS_LITTLE_ENDIAN
mdefine_line|#define UFS_LITTLE_ENDIAN 0x00000000&t;/* 0x00010000 */
DECL|macro|UFS_BIG_ENDIAN
mdefine_line|#define UFS_BIG_ENDIAN    0x00010000&t;/* 0x00020000 */
DECL|macro|UFS_BYTESEX
mdefine_line|#define UFS_BYTESEX&t;  0x00010000&t;/* 0x00030000 */
DECL|macro|UFS_ADDR_PER_BLOCK
mdefine_line|#define UFS_ADDR_PER_BLOCK(sb)&t;&t;((sb)-&gt;u.ufs_sb.s_bsize &gt;&gt; 2)
DECL|macro|UFS_ADDR_PER_BLOCK_BITS
mdefine_line|#define UFS_ADDR_PER_BLOCK_BITS(sb)&t;((sb)-&gt;u.ufs_sb.s_bshift - 2)
multiline_comment|/* Test if the inode number is valid. */
DECL|macro|ufs_ino_ok
mdefine_line|#define ufs_ino_ok(inode)  ((inode-&gt;i_ino &lt; 2) &amp;&amp;  &bslash;&n;&t;                    (inode-&gt;i_ino &gt; (inode-&gt;i_sb-&gt;u.ufs_sb.s_ncg * inode-&gt;i_sb-&gt;u.ufs_sb.s_ipg - 1)))
multiline_comment|/* Convert (sb,cg) to the first physical block number for that cg. */
DECL|macro|ufs_cgstart
mdefine_line|#define ufs_cgstart(sb, cg)   &bslash;&n;  (((sb)-&gt;u.ufs_sb.s_fpg * (cg)) + (sb)-&gt;u.ufs_sb.s_cgoffset * ((cg) &amp; ~((sb)-&gt;u.ufs_sb.s_cgmask)))
multiline_comment|/* Convert (sb,cg) to the first phys. block number for inodes in that cg. */
DECL|macro|ufs_cgimin
mdefine_line|#define ufs_cgimin(sb, cg) (ufs_cgstart((sb), (cg)) + (sb)-&gt;u.ufs_sb.s_iblkno)
DECL|macro|ufs_cgdmin
mdefine_line|#define ufs_cgdmin(sb, cg) (ufs_cgstart((sb), (cg)) + (sb)-&gt;u.ufs_sb.s_dblkno)
multiline_comment|/* Convert an inode number to a cg number. */
multiline_comment|/* XXX - this can be optimized if s_ipg is a power of 2. */
DECL|macro|ufs_ino2cg
mdefine_line|#define ufs_ino2cg(inode)  ((inode)-&gt;i_ino/(inode)-&gt;i_sb-&gt;u.ufs_sb.s_ipg)
DECL|macro|UFS_MAXNAMLEN
mdefine_line|#define&t;UFS_MAXNAMLEN 255
DECL|macro|ufs_lbn
mdefine_line|#define ufs_lbn(sb, block)&t;&t;((block) &gt;&gt; (sb)-&gt;u.ufs_sb.s_lshift)
DECL|macro|ufs_boff
mdefine_line|#define ufs_boff(sb, block)&t;&t;((block) &amp; ~((sb)-&gt;u.ufs_sb.s_lmask))
DECL|macro|ufs_dbn
mdefine_line|#define ufs_dbn(sb, block, boff)&t;((block) + ufs_boff((sb), (boff)))
DECL|struct|ufs_direct
r_struct
id|ufs_direct
(brace
DECL|member|d_ino
id|__u32
id|d_ino
suffix:semicolon
multiline_comment|/* inode number of this entry */
DECL|member|d_reclen
id|__u16
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this entry */
DECL|member|d_namlen
id|__u16
id|d_namlen
suffix:semicolon
multiline_comment|/* actual length of d_name */
DECL|member|d_name
r_char
id|d_name
(braket
id|UFS_MAXNAMLEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* file name */
)brace
suffix:semicolon
DECL|macro|MAXMNTLEN
mdefine_line|#define MAXMNTLEN 512
DECL|macro|MAXCSBUFS
mdefine_line|#define MAXCSBUFS 32
DECL|struct|ufs_csum
r_struct
id|ufs_csum
(brace
DECL|member|cs_ndir
id|__u32
id|cs_ndir
suffix:semicolon
multiline_comment|/* number of directories */
DECL|member|cs_nbfree
id|__u32
id|cs_nbfree
suffix:semicolon
multiline_comment|/* number of free blocks */
DECL|member|cs_nifree
id|__u32
id|cs_nifree
suffix:semicolon
multiline_comment|/* number of free inodes */
DECL|member|cs_nffree
id|__u32
id|cs_nffree
suffix:semicolon
multiline_comment|/* number of free frags */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the actual superblock, as it is laid out on the disk.&n; */
DECL|struct|ufs_superblock
r_struct
id|ufs_superblock
(brace
DECL|member|fs_link
id|__u32
id|fs_link
suffix:semicolon
multiline_comment|/* UNUSED */
DECL|member|fs_rlink
id|__u32
id|fs_rlink
suffix:semicolon
multiline_comment|/* UNUSED */
DECL|member|fs_sblkno
id|__u32
id|fs_sblkno
suffix:semicolon
multiline_comment|/* addr of super-block in filesys */
DECL|member|fs_cblkno
id|__u32
id|fs_cblkno
suffix:semicolon
multiline_comment|/* offset of cyl-block in filesys */
DECL|member|fs_iblkno
id|__u32
id|fs_iblkno
suffix:semicolon
multiline_comment|/* offset of inode-blocks in filesys */
DECL|member|fs_dblkno
id|__u32
id|fs_dblkno
suffix:semicolon
multiline_comment|/* offset of first data after cg */
DECL|member|fs_cgoffset
id|__u32
id|fs_cgoffset
suffix:semicolon
multiline_comment|/* cylinder group offset in cylinder */
DECL|member|fs_cgmask
id|__u32
id|fs_cgmask
suffix:semicolon
multiline_comment|/* used to calc mod fs_ntrak */
DECL|member|fs_time
id|__u32
id|fs_time
suffix:semicolon
multiline_comment|/* last time written -- time_t */
DECL|member|fs_size
id|__u32
id|fs_size
suffix:semicolon
multiline_comment|/* number of blocks in fs */
DECL|member|fs_dsize
id|__u32
id|fs_dsize
suffix:semicolon
multiline_comment|/* number of data blocks in fs */
DECL|member|fs_ncg
id|__u32
id|fs_ncg
suffix:semicolon
multiline_comment|/* number of cylinder groups */
DECL|member|fs_bsize
id|__u32
id|fs_bsize
suffix:semicolon
multiline_comment|/* size of basic blocks in fs */
DECL|member|fs_fsize
id|__u32
id|fs_fsize
suffix:semicolon
multiline_comment|/* size of frag blocks in fs */
DECL|member|fs_frag
id|__u32
id|fs_frag
suffix:semicolon
multiline_comment|/* number of frags in a block in fs */
multiline_comment|/* these are configuration parameters */
DECL|member|fs_minfree
id|__u32
id|fs_minfree
suffix:semicolon
multiline_comment|/* minimum percentage of free blocks */
DECL|member|fs_rotdelay
id|__u32
id|fs_rotdelay
suffix:semicolon
multiline_comment|/* num of ms for optimal next block */
DECL|member|fs_rps
id|__u32
id|fs_rps
suffix:semicolon
multiline_comment|/* disk revolutions per second */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_bmask
id|__u32
id|fs_bmask
suffix:semicolon
multiline_comment|/* ``blkoff&squot;&squot; calc of blk offsets */
DECL|member|fs_fmask
id|__u32
id|fs_fmask
suffix:semicolon
multiline_comment|/* ``fragoff&squot;&squot; calc of frag offsets */
DECL|member|fs_bshift
id|__u32
id|fs_bshift
suffix:semicolon
multiline_comment|/* ``lblkno&squot;&squot; calc of logical blkno */
DECL|member|fs_fshift
id|__u32
id|fs_fshift
suffix:semicolon
multiline_comment|/* ``numfrags&squot;&squot; calc number of frags */
multiline_comment|/* these are configuration parameters */
DECL|member|fs_maxcontig
id|__u32
id|fs_maxcontig
suffix:semicolon
multiline_comment|/* max number of contiguous blks */
DECL|member|fs_maxbpg
id|__u32
id|fs_maxbpg
suffix:semicolon
multiline_comment|/* max number of blks per cyl group */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_fragshift
id|__u32
id|fs_fragshift
suffix:semicolon
multiline_comment|/* block to frag shift */
DECL|member|fs_fsbtodb
id|__u32
id|fs_fsbtodb
suffix:semicolon
multiline_comment|/* fsbtodb and dbtofsb shift constant */
DECL|member|fs_sbsize
id|__u32
id|fs_sbsize
suffix:semicolon
multiline_comment|/* actual size of super block */
DECL|member|fs_csmask
id|__u32
id|fs_csmask
suffix:semicolon
multiline_comment|/* csum block offset */
DECL|member|fs_csshift
id|__u32
id|fs_csshift
suffix:semicolon
multiline_comment|/* csum block number */
DECL|member|fs_nindir
id|__u32
id|fs_nindir
suffix:semicolon
multiline_comment|/* value of NINDIR */
DECL|member|fs_inopb
id|__u32
id|fs_inopb
suffix:semicolon
multiline_comment|/* value of INOPB */
DECL|member|fs_nspf
id|__u32
id|fs_nspf
suffix:semicolon
multiline_comment|/* value of NSPF */
multiline_comment|/* yet another configuration parameter */
DECL|member|fs_optim
id|__u32
id|fs_optim
suffix:semicolon
multiline_comment|/* optimization preference, see below */
multiline_comment|/* these fields are derived from the hardware */
DECL|member|fs_npsect
id|__u32
id|fs_npsect
suffix:semicolon
multiline_comment|/* # sectors/track including spares */
DECL|member|fs_interleave
id|__u32
id|fs_interleave
suffix:semicolon
multiline_comment|/* hardware sector interleave */
DECL|member|fs_trackskew
id|__u32
id|fs_trackskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per track */
multiline_comment|/* a unique id for this filesystem (currently unused and unmaintained) */
multiline_comment|/* In 4.3 Tahoe this space is used by fs_headswitch and fs_trkseek */
multiline_comment|/* Neither of those fields is used in the Tahoe code right now but */
multiline_comment|/* there could be problems if they are.                            */
DECL|member|fs_id
id|__u32
id|fs_id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* file system id */
multiline_comment|/* sizes determined by number of cylinder groups and their sizes */
DECL|member|fs_csaddr
id|__u32
id|fs_csaddr
suffix:semicolon
multiline_comment|/* blk addr of cyl grp summary area */
DECL|member|fs_cssize
id|__u32
id|fs_cssize
suffix:semicolon
multiline_comment|/* size of cyl grp summary area */
DECL|member|fs_cgsize
id|__u32
id|fs_cgsize
suffix:semicolon
multiline_comment|/* cylinder group size */
multiline_comment|/* these fields are derived from the hardware */
DECL|member|fs_ntrak
id|__u32
id|fs_ntrak
suffix:semicolon
multiline_comment|/* tracks per cylinder */
DECL|member|fs_nsect
id|__u32
id|fs_nsect
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|fs_spc
id|__u32
id|fs_spc
suffix:semicolon
multiline_comment|/* sectors per cylinder */
multiline_comment|/* this comes from the disk driver partitioning */
DECL|member|fs_ncyl
id|__u32
id|fs_ncyl
suffix:semicolon
multiline_comment|/* cylinders in file system */
multiline_comment|/* these fields can be computed from the others */
DECL|member|fs_cpg
id|__u32
id|fs_cpg
suffix:semicolon
multiline_comment|/* cylinders per group */
DECL|member|fs_ipg
id|__u32
id|fs_ipg
suffix:semicolon
multiline_comment|/* inodes per group */
DECL|member|fs_fpg
id|__u32
id|fs_fpg
suffix:semicolon
multiline_comment|/* blocks per group * fs_frag */
multiline_comment|/* this data must be re-computed after crashes */
DECL|member|fs_cstotal
r_struct
id|ufs_csum
id|fs_cstotal
suffix:semicolon
multiline_comment|/* cylinder summary information */
multiline_comment|/* these fields are cleared at mount time */
DECL|member|fs_fmod
id|__u8
id|fs_fmod
suffix:semicolon
multiline_comment|/* super block modified flag */
DECL|member|fs_clean
id|__u8
id|fs_clean
suffix:semicolon
multiline_comment|/* file system is clean flag */
DECL|member|fs_ronly
id|__u8
id|fs_ronly
suffix:semicolon
multiline_comment|/* mounted read-only flag */
DECL|member|fs_flags
id|__u8
id|fs_flags
suffix:semicolon
multiline_comment|/* currently unused flag */
DECL|member|fs_fsmnt
id|__u8
id|fs_fsmnt
(braket
id|MAXMNTLEN
)braket
suffix:semicolon
multiline_comment|/* name mounted on */
multiline_comment|/* these fields retain the current block allocation info */
DECL|member|fs_cgrotor
id|__u32
id|fs_cgrotor
suffix:semicolon
multiline_comment|/* last cg searched */
DECL|member|fs_csp
r_struct
id|ufs_csum
op_star
id|fs_csp
(braket
id|MAXCSBUFS
)braket
suffix:semicolon
multiline_comment|/* list of fs_cs info buffers */
DECL|member|fs_cpc
id|__u32
id|fs_cpc
suffix:semicolon
multiline_comment|/* cyl per cycle in postbl */
DECL|member|fs_opostbl
id|__u16
id|fs_opostbl
(braket
l_int|16
)braket
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* old rotation block list head */
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|55
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_qbmask
id|__s64
id|fs_qbmask
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__s64
id|fs_qfmask
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_postblformat
id|__s32
id|fs_postblformat
suffix:semicolon
multiline_comment|/* format of positional layout tables */
DECL|member|fs_nrpos
id|__s32
id|fs_nrpos
suffix:semicolon
multiline_comment|/* number of rotational positions */
DECL|member|fs_postbloff
id|__s32
id|fs_postbloff
suffix:semicolon
multiline_comment|/* (__s16) rotation block list head */
DECL|member|fs_rotbloff
id|__s32
id|fs_rotbloff
suffix:semicolon
multiline_comment|/* (__u8) blocks for each rotation */
DECL|member|fs_magic
id|__s32
id|fs_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|fs_space
id|__u8
id|fs_space
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* list of blocks for each rotation */
)brace
suffix:semicolon
multiline_comment|/*&n; * structure of an on-disk inode&n; */
DECL|struct|ufs_inode
r_struct
id|ufs_inode
(brace
DECL|member|ui_mode
id|__u16
id|ui_mode
suffix:semicolon
multiline_comment|/*  0x0 */
DECL|member|ui_nlink
id|__u16
id|ui_nlink
suffix:semicolon
multiline_comment|/*  0x2 */
DECL|member|ui_suid
id|__u16
id|ui_suid
suffix:semicolon
multiline_comment|/*  0x4 */
DECL|member|ui_sgid
id|__u16
id|ui_sgid
suffix:semicolon
multiline_comment|/*  0x6 */
DECL|member|ui_size
id|__u64
id|ui_size
suffix:semicolon
multiline_comment|/*  0x8 */
DECL|member|ui_atime
r_struct
id|timeval
id|ui_atime
suffix:semicolon
multiline_comment|/* 0x10 access */
DECL|member|ui_mtime
r_struct
id|timeval
id|ui_mtime
suffix:semicolon
multiline_comment|/* 0x18 modification */
DECL|member|ui_ctime
r_struct
id|timeval
id|ui_ctime
suffix:semicolon
multiline_comment|/* 0x20 creation */
DECL|member|ui_db
id|__u32
id|ui_db
(braket
id|UFS_NDADDR
)braket
suffix:semicolon
multiline_comment|/* 0x28 data blocks */
DECL|member|ui_ib
id|__u32
id|ui_ib
(braket
id|UFS_NINDIR
)braket
suffix:semicolon
multiline_comment|/* 0x58 indirect blocks */
DECL|member|ui_flags
id|__u32
id|ui_flags
suffix:semicolon
multiline_comment|/* 0x64 unused -- &quot;status flags (chflags)&quot; ??? */
DECL|member|ui_blocks
id|__u32
id|ui_blocks
suffix:semicolon
multiline_comment|/* 0x68 blocks in use */
DECL|member|ui_gen
id|__u32
id|ui_gen
suffix:semicolon
multiline_comment|/* 0x6c generation number XXX - what is this? */
DECL|member|ui_shadow
id|__u32
id|ui_shadow
suffix:semicolon
multiline_comment|/* 0x70 shadow inode XXX - what is this?*/
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x74 long EFT version of uid */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x78 long EFT version of gid */
DECL|member|ui_oeftflag
id|__u32
id|ui_oeftflag
suffix:semicolon
multiline_comment|/* 0x7c reserved */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/* ufs_inode.c */
r_extern
r_int
id|ufs_bmap
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ufs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|ufs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|ufs_print_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* ufs_namei.c */
r_extern
r_int
id|ufs_lookup
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* ufs_super.c */
r_extern
r_void
id|ufs_warning
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|init_ufs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Inodes and files operations&n; */
multiline_comment|/* ufs_dir.c */
r_extern
r_struct
id|inode_operations
id|ufs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_dir_operations
suffix:semicolon
multiline_comment|/* ufs_file.c */
r_extern
r_struct
id|inode_operations
id|ufs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_file_operations
suffix:semicolon
multiline_comment|/* ufs_symlink.c */
r_extern
r_struct
id|inode_operations
id|ufs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ufs_symlink_operations
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __LINUX_UFS_FS_H */
eof
