multiline_comment|/*&n; *  linux/include/linux/ufs_fs.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_fs.h,v 1.1 1996/04/21 14:45:11 davem Exp $&n; *&n; */
macro_line|#ifndef __LINUX_UFS_FS_H
DECL|macro|__LINUX_UFS_FS_H
mdefine_line|#define __LINUX_UFS_FS_H
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
DECL|macro|UFS_FSIZE
mdefine_line|#define UFS_FSIZE 1024
DECL|macro|UFS_BSIZE
mdefine_line|#define UFS_BSIZE 8192
DECL|macro|UFS_NDADDR
mdefine_line|#define UFS_NDADDR 12
DECL|macro|UFS_NINDIR
mdefine_line|#define UFS_NINDIR 3
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
DECL|struct|_ufsquad
r_typedef
r_struct
id|_ufsquad
(brace
DECL|member|val
id|__u32
id|val
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|ufsquad
)brace
id|ufsquad
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
DECL|member|fs_cblkno
id|__u32
id|fs_cblkno
suffix:semicolon
DECL|member|fs_iblkno
id|__u32
id|fs_iblkno
suffix:semicolon
DECL|member|fs_dblkno
id|__u32
id|fs_dblkno
suffix:semicolon
DECL|member|fs_cgoffset
id|__u32
id|fs_cgoffset
suffix:semicolon
DECL|member|fs_cgmask
id|__u32
id|fs_cgmask
suffix:semicolon
DECL|member|fs_time
id|time_t
id|fs_time
suffix:semicolon
multiline_comment|/* XXX - check type */
DECL|member|fs_size
id|__u32
id|fs_size
suffix:semicolon
DECL|member|fs_dsize
id|__u32
id|fs_dsize
suffix:semicolon
DECL|member|fs_ncg
id|__u32
id|fs_ncg
suffix:semicolon
DECL|member|fs_bsize
id|__u32
id|fs_bsize
suffix:semicolon
DECL|member|fs_fsize
id|__u32
id|fs_fsize
suffix:semicolon
DECL|member|fs_frag
id|__u32
id|fs_frag
suffix:semicolon
DECL|member|fs_minfree
id|__u32
id|fs_minfree
suffix:semicolon
DECL|member|fs_rotdelay
id|__u32
id|fs_rotdelay
suffix:semicolon
DECL|member|fs_rps
id|__u32
id|fs_rps
suffix:semicolon
DECL|member|fs_bmask
id|__u32
id|fs_bmask
suffix:semicolon
DECL|member|fs_fmask
id|__u32
id|fs_fmask
suffix:semicolon
DECL|member|fs_bshift
id|__u32
id|fs_bshift
suffix:semicolon
DECL|member|fs_fshift
id|__u32
id|fs_fshift
suffix:semicolon
DECL|member|fs_maxcontig
id|__u32
id|fs_maxcontig
suffix:semicolon
DECL|member|fs_maxbpg
id|__u32
id|fs_maxbpg
suffix:semicolon
DECL|member|fs_fragshift
id|__u32
id|fs_fragshift
suffix:semicolon
DECL|member|fs_fsbtodb
id|__u32
id|fs_fsbtodb
suffix:semicolon
DECL|member|fs_sbsize
id|__u32
id|fs_sbsize
suffix:semicolon
DECL|member|fs_csmask
id|__u32
id|fs_csmask
suffix:semicolon
DECL|member|fs_csshift
id|__u32
id|fs_csshift
suffix:semicolon
DECL|member|fs_nindir
id|__u32
id|fs_nindir
suffix:semicolon
DECL|member|fs_inopb
id|__u32
id|fs_inopb
suffix:semicolon
DECL|member|fs_nspf
id|__u32
id|fs_nspf
suffix:semicolon
DECL|member|fs_optim
id|__u32
id|fs_optim
suffix:semicolon
DECL|member|fs_XXX1
id|__u32
id|fs_XXX1
suffix:semicolon
DECL|member|fs_interleave
id|__u32
id|fs_interleave
suffix:semicolon
DECL|member|fs_trackskew
id|__u32
id|fs_trackskew
suffix:semicolon
DECL|member|fs_id
id|__u32
id|fs_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fs_csaddr
id|__u32
id|fs_csaddr
suffix:semicolon
DECL|member|fs_cssize
id|__u32
id|fs_cssize
suffix:semicolon
DECL|member|fs_cgsize
id|__u32
id|fs_cgsize
suffix:semicolon
DECL|member|fs_ntrak
id|__u32
id|fs_ntrak
suffix:semicolon
DECL|member|fs_nsect
id|__u32
id|fs_nsect
suffix:semicolon
DECL|member|fs_spc
id|__u32
id|fs_spc
suffix:semicolon
DECL|member|fs_ncyl
id|__u32
id|fs_ncyl
suffix:semicolon
DECL|member|fs_cpg
id|__u32
id|fs_cpg
suffix:semicolon
DECL|member|fs_ipg
id|__u32
id|fs_ipg
suffix:semicolon
DECL|member|fs_fpg
id|__u32
id|fs_fpg
suffix:semicolon
DECL|member|fs_cstotal
r_struct
id|ufs_csum
id|fs_cstotal
suffix:semicolon
DECL|member|fs_fmod
id|__u8
id|fs_fmod
suffix:semicolon
DECL|member|fs_clean
id|__u8
id|fs_clean
suffix:semicolon
DECL|member|fs_ronly
id|__u8
id|fs_ronly
suffix:semicolon
DECL|member|fs_flags
id|__u8
id|fs_flags
suffix:semicolon
DECL|member|fs_fsmnt
id|__u8
id|fs_fsmnt
(braket
id|MAXMNTLEN
)braket
suffix:semicolon
DECL|member|fs_cgrotor
id|__u32
id|fs_cgrotor
suffix:semicolon
DECL|member|fs_csp
r_struct
id|ufs_csum
op_star
id|fs_csp
(braket
id|MAXCSBUFS
)braket
suffix:semicolon
DECL|member|fs_cpc
id|__u32
id|fs_cpc
suffix:semicolon
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
id|ufsquad
id|fs_qbmask
suffix:semicolon
multiline_comment|/* ~usb_bmask - for use with __s64 size */
DECL|member|fs_qfmask
id|ufsquad
id|fs_qfmask
suffix:semicolon
multiline_comment|/* ~usb_fmask - for use with __s64 size */
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
id|ufsquad
id|ui_size
suffix:semicolon
multiline_comment|/*  0x8 */
multiline_comment|/* XXX - should be __u64 */
DECL|member|ui_atime
r_struct
id|timeval
id|ui_atime
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|ui_mtime
r_struct
id|timeval
id|ui_mtime
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|ui_ctime
r_struct
id|timeval
id|ui_ctime
suffix:semicolon
multiline_comment|/* 0x20 */
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
multiline_comment|/* 0x64 unused */
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
r_extern
r_int
id|init_ufs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_UFS_FS_H */
multiline_comment|/*&n; * Local Variables: ***&n; * c-indent-level: 8 ***&n; * c-continued-statement-offset: 8 ***&n; * c-brace-offset: -8 ***&n; * c-argdecl-indent: 0 ***&n; * c-label-offset: -8 ***&n; * End: ***&n; */
eof
