multiline_comment|/*&n; *  linux/include/linux/ufs_fs.h&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Clean swab support by Fare &lt;rideau@ens.fr&gt;&n; * just hope no one is using NNUUXXI on __?64 structure elements&n; * 64-bit clean thanks to Maciej W. Rozycki &lt;macro@ds2.pg.gda.pl&gt;&n; *&n; * 4.4BSD (FreeBSD) support added on February 1st 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt; partially based&n; * on code by Martin von Loewis &lt;martin@mira.isdn.cs.tu-berlin.de&gt;.&n; *&n; * NeXTstep support added on February 5th 1998 by&n; * Niels Kristian Bech Jensen &lt;nkbj@image.dk&gt;.&n; */
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
DECL|macro|UFS_FSOSF1
mdefine_line|#define UFS_FSOSF1    ((char)0x03)&t;/* is this correct for DEC OSF/1? */
DECL|macro|UFS_FSBAD
mdefine_line|#define UFS_FSBAD     ((char)0xff)
multiline_comment|/* From here to next blank line, s_flags for ufs_sb_info */
multiline_comment|/* endianness */
DECL|macro|UFS_BYTESEX
mdefine_line|#define UFS_BYTESEX&t;&t;0x00000001&t;/* mask; leave room to 0xF */
DECL|macro|UFS_LITTLE_ENDIAN
mdefine_line|#define UFS_LITTLE_ENDIAN&t;0x00000000
DECL|macro|UFS_BIG_ENDIAN
mdefine_line|#define UFS_BIG_ENDIAN&t;&t;0x00000001
multiline_comment|/* directory entry encoding */
DECL|macro|UFS_DE_MASK
mdefine_line|#define UFS_DE_MASK&t;&t;0x00000010&t;/* mask for the following */
DECL|macro|UFS_DE_OLD
mdefine_line|#define UFS_DE_OLD&t;&t;0x00000000
DECL|macro|UFS_DE_44BSD
mdefine_line|#define UFS_DE_44BSD&t;&t;0x00000010
multiline_comment|/* uid encoding */
DECL|macro|UFS_UID_MASK
mdefine_line|#define UFS_UID_MASK&t;&t;0x00000060&t;/* mask for the following */
DECL|macro|UFS_UID_OLD
mdefine_line|#define UFS_UID_OLD&t;&t;0x00000000
DECL|macro|UFS_UID_44BSD
mdefine_line|#define UFS_UID_44BSD&t;&t;0x00000020
DECL|macro|UFS_UID_EFT
mdefine_line|#define UFS_UID_EFT&t;&t;0x00000040
multiline_comment|/* superblock state encoding */
DECL|macro|UFS_ST_MASK
mdefine_line|#define UFS_ST_MASK&t;&t;0x00000700&t;/* mask for the following */
DECL|macro|UFS_ST_OLD
mdefine_line|#define UFS_ST_OLD&t;&t;0x00000000
DECL|macro|UFS_ST_44BSD
mdefine_line|#define UFS_ST_44BSD&t;&t;0x00000100
DECL|macro|UFS_ST_SUN
mdefine_line|#define UFS_ST_SUN&t;&t;0x00000200
DECL|macro|UFS_ST_NEXT
mdefine_line|#define UFS_ST_NEXT&t;&t;0x00000400
multiline_comment|/* filesystem flavors (combo of features) */
DECL|macro|UFS_FEATURES
mdefine_line|#define UFS_FEATURES&t;&t;0x00FFFFF0&t;/* room for extension */
DECL|macro|UFS_VANILLA
mdefine_line|#define UFS_VANILLA&t;&t;0x00000000
DECL|macro|UFS_OLD
mdefine_line|#define UFS_OLD&t;&t;&t;0x00000000&t;/* 4.2BSD */
DECL|macro|UFS_44BSD
mdefine_line|#define UFS_44BSD&t;&t;0x00000130
DECL|macro|UFS_HURD
mdefine_line|#define UFS_HURD&t;&t;0x00000130
DECL|macro|UFS_SUN
mdefine_line|#define UFS_SUN&t;&t;&t;0x00000200
DECL|macro|UFS_NEXT
mdefine_line|#define UFS_NEXT&t;&t;0x00000400
multiline_comment|/* we preserve distinction in flavor identification even without difference,&n; * because yet-to-be-supported features may introduce difference in the future&n; */
multiline_comment|/* last but not least, debug flags */
DECL|macro|UFS_DEBUG
mdefine_line|#define UFS_DEBUG       &t;0x01000000
DECL|macro|UFS_DEBUG_INODE
mdefine_line|#define UFS_DEBUG_INODE &t;0x02000000
DECL|macro|UFS_DEBUG_NAMEI
mdefine_line|#define UFS_DEBUG_NAMEI &t;0x04000000
DECL|macro|UFS_DEBUG_LINKS
mdefine_line|#define UFS_DEBUG_LINKS &t;0x08000000
macro_line|#ifdef UFS_HEAVY_DEBUG
DECL|macro|UFS_DEBUG_INITIAL
macro_line|#  define UFS_DEBUG_INITIAL UFS_DEBUG
macro_line|#else
DECL|macro|UFS_DEBUG_INITIAL
macro_line|#  define UFS_DEBUG_INITIAL 0
macro_line|#endif
multiline_comment|/* fs_inodefmt options */
DECL|macro|UFS_42INODEFMT
mdefine_line|#define UFS_42INODEFMT&t;-1
DECL|macro|UFS_44INODEFMT
mdefine_line|#define UFS_44INODEFMT&t;2
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
multiline_comment|/* current filesystem state; method depends on flags */
DECL|macro|UFS_STATE
mdefine_line|#define UFS_STATE(usb) &bslash;&n;&t;&t;( ((flags&amp;UFS_ST_MASK) == UFS_ST_OLD) &bslash;&n;                  ? (usb)-&gt;fs_u.fs_sun.fs_state /* old normal way */ &bslash;&n;                  : (usb)-&gt;fs_u.fs_44.fs_state /* 4.4BSD way */ )
DECL|macro|UFS_MAXNAMLEN
mdefine_line|#define&t;UFS_MAXNAMLEN 255
DECL|macro|ufs_lbn
mdefine_line|#define ufs_lbn(sb, block)&t;&t;((block) &gt;&gt; (sb)-&gt;u.ufs_sb.s_lshift)
DECL|macro|ufs_boff
mdefine_line|#define ufs_boff(sb, block)&t;&t;((block) &amp; ~((sb)-&gt;u.ufs_sb.s_lmask))
DECL|macro|ufs_dbn
mdefine_line|#define ufs_dbn(sb, block, boff)&t;((block) + ufs_boff((sb), (boff)))
DECL|struct|ufs_timeval
r_struct
id|ufs_timeval
(brace
DECL|member|tv_sec
id|__s32
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|__s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
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
r_union
(brace
DECL|member|d_namlen
id|__u16
id|d_namlen
suffix:semicolon
multiline_comment|/* actual length of d_name */
r_struct
(brace
DECL|member|d_type
id|__u8
id|d_type
suffix:semicolon
multiline_comment|/* file type */
DECL|member|d_namlen
id|__u8
id|d_namlen
suffix:semicolon
multiline_comment|/* length of string in d_name */
DECL|member|d_44
)brace
id|d_44
suffix:semicolon
DECL|member|d_u
)brace
id|d_u
suffix:semicolon
DECL|member|d_name
id|__u8
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
id|__u32
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
r_union
(brace
r_struct
(brace
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
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_sun
)brace
id|fs_sun
suffix:semicolon
r_struct
(brace
DECL|member|fs_sparecon
id|__s32
id|fs_sparecon
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* reserved for future constants */
DECL|member|fs_contigsumsize
id|__s32
id|fs_contigsumsize
suffix:semicolon
multiline_comment|/* size of cluster summary array */
DECL|member|fs_maxsymlinklen
id|__s32
id|fs_maxsymlinklen
suffix:semicolon
multiline_comment|/* max length of an internal symlink */
DECL|member|fs_inodefmt
id|__s32
id|fs_inodefmt
suffix:semicolon
multiline_comment|/* format of on-disk inodes */
DECL|member|fs_maxfilesize
id|__u64
id|fs_maxfilesize
suffix:semicolon
multiline_comment|/* max representable file size */
DECL|member|fs_qbmask
id|__u32
id|fs_qbmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_bmask */
DECL|member|fs_qfmask
id|__u32
id|fs_qfmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ~usb_fmask */
DECL|member|fs_state
id|__s32
id|fs_state
suffix:semicolon
multiline_comment|/* file system state time stamp */
DECL|member|fs_44
)brace
id|fs_44
suffix:semicolon
DECL|member|fs_u
)brace
id|fs_u
suffix:semicolon
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
r_union
(brace
r_struct
(brace
DECL|member|suid
id|__u16
id|suid
suffix:semicolon
multiline_comment|/*  0x4 */
DECL|member|sgid
id|__u16
id|sgid
suffix:semicolon
multiline_comment|/*  0x6 */
DECL|member|oldids
)brace
id|oldids
suffix:semicolon
DECL|member|inumber
id|__u32
id|inumber
suffix:semicolon
multiline_comment|/*  0x4 lsf: inode number */
DECL|member|author
id|__u32
id|author
suffix:semicolon
multiline_comment|/*  0x4 GNU HURD: author */
DECL|member|ui_u1
)brace
id|ui_u1
suffix:semicolon
DECL|member|ui_size
id|__u64
id|ui_size
suffix:semicolon
multiline_comment|/*  0x8 */
DECL|member|ui_atime
r_struct
id|ufs_timeval
id|ui_atime
suffix:semicolon
multiline_comment|/* 0x10 access */
DECL|member|ui_mtime
r_struct
id|ufs_timeval
id|ui_mtime
suffix:semicolon
multiline_comment|/* 0x18 modification */
DECL|member|ui_ctime
r_struct
id|ufs_timeval
id|ui_ctime
suffix:semicolon
multiline_comment|/* 0x20 creation */
r_union
(brace
r_struct
(brace
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
DECL|member|ui_addr
)brace
id|ui_addr
suffix:semicolon
DECL|member|ui_symlink
id|__u8
id|ui_symlink
(braket
l_int|4
op_star
(paren
id|UFS_NDADDR
op_plus
id|UFS_NINDIR
)paren
)braket
suffix:semicolon
multiline_comment|/* 0x28 fast symlink */
DECL|member|ui_u2
)brace
id|ui_u2
suffix:semicolon
DECL|member|ui_flags
id|__u32
id|ui_flags
suffix:semicolon
multiline_comment|/* 0x64 immutable, append-only... */
DECL|member|ui_blocks
id|__u32
id|ui_blocks
suffix:semicolon
multiline_comment|/* 0x68 blocks in use */
DECL|member|ui_gen
id|__u32
id|ui_gen
suffix:semicolon
multiline_comment|/* 0x6c like ext2 i_version, for NFS support */
r_union
(brace
r_struct
(brace
DECL|member|ui_shadow
id|__u32
id|ui_shadow
suffix:semicolon
multiline_comment|/* 0x70 shadow inode with security data */
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
DECL|member|ui_sun
)brace
id|ui_sun
suffix:semicolon
r_struct
(brace
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x70 File owner */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x74 File group */
DECL|member|ui_spare
id|__s32
id|ui_spare
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x78 reserved */
DECL|member|ui_44
)brace
id|ui_44
suffix:semicolon
r_struct
(brace
DECL|member|ui_uid
id|__u32
id|ui_uid
suffix:semicolon
multiline_comment|/* 0x70 */
DECL|member|ui_gid
id|__u32
id|ui_gid
suffix:semicolon
multiline_comment|/* 0x74 */
DECL|member|ui_modeh
id|__u16
id|ui_modeh
suffix:semicolon
multiline_comment|/* 0x78 mode high bits */
DECL|member|ui_spare
id|__u16
id|ui_spare
suffix:semicolon
multiline_comment|/* 0x7A unused */
DECL|member|ui_trans
id|__u32
id|ui_trans
suffix:semicolon
multiline_comment|/* 0x7c filesystem translator */
DECL|member|ui_hurd
)brace
id|ui_hurd
suffix:semicolon
DECL|member|ui_u3
)brace
id|ui_u3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FreeBSD has these in sys/stat.h */
multiline_comment|/* ui_flags that can be set by a file owner */
DECL|macro|UFS_UF_SETTABLE
mdefine_line|#define UFS_UF_SETTABLE   0x0000ffff
DECL|macro|UFS_UF_NODUMP
mdefine_line|#define UFS_UF_NODUMP     0x00000001  /* do not dump */
DECL|macro|UFS_UF_IMMUTABLE
mdefine_line|#define UFS_UF_IMMUTABLE  0x00000002  /* immutable (can&squot;t &quot;change&quot;) */
DECL|macro|UFS_UF_APPEND
mdefine_line|#define UFS_UF_APPEND     0x00000004  /* append-only */
DECL|macro|UFS_UF_OPAQUE
mdefine_line|#define UFS_UF_OPAQUE     0x00000008  /* directory is opaque (unionfs) */
DECL|macro|UFS_UF_NOUNLINK
mdefine_line|#define UFS_UF_NOUNLINK   0x00000010  /* can&squot;t be removed or renamed */
multiline_comment|/* ui_flags that only root can set */
DECL|macro|UFS_SF_SETTABLE
mdefine_line|#define UFS_SF_SETTABLE   0xffff0000
DECL|macro|UFS_SF_ARCHIVED
mdefine_line|#define UFS_SF_ARCHIVED   0x00010000  /* archived */
DECL|macro|UFS_SF_IMMUTABLE
mdefine_line|#define UFS_SF_IMMUTABLE  0x00020000  /* immutable (can&squot;t &quot;change&quot;) */
DECL|macro|UFS_SF_APPEND
mdefine_line|#define UFS_SF_APPEND     0x00040000  /* append-only */
DECL|macro|UFS_SF_NOUNLINK
mdefine_line|#define UFS_SF_NOUNLINK   0x00100000  /* can&squot;t be removed or renamed */
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
