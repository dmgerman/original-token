macro_line|#ifndef _ADFS_FS_H
DECL|macro|_ADFS_FS_H
mdefine_line|#define _ADFS_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Structures of data on the disk&n; */
multiline_comment|/*&n; * Disc Record at disc address 0xc00&n; */
DECL|struct|adfs_discrecord
r_struct
id|adfs_discrecord
(brace
DECL|member|log2secsize
r_int
r_char
id|log2secsize
suffix:semicolon
DECL|member|secspertrack
r_int
r_char
id|secspertrack
suffix:semicolon
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|density
r_int
r_char
id|density
suffix:semicolon
DECL|member|idlen
r_int
r_char
id|idlen
suffix:semicolon
DECL|member|log2bpmb
r_int
r_char
id|log2bpmb
suffix:semicolon
DECL|member|skew
r_int
r_char
id|skew
suffix:semicolon
DECL|member|bootoption
r_int
r_char
id|bootoption
suffix:semicolon
DECL|member|lowsector
r_int
r_char
id|lowsector
suffix:semicolon
DECL|member|nzones
r_int
r_char
id|nzones
suffix:semicolon
DECL|member|zone_spare
r_int
r_int
id|zone_spare
suffix:semicolon
DECL|member|root
r_int
r_int
id|root
suffix:semicolon
DECL|member|disc_size
r_int
r_int
id|disc_size
suffix:semicolon
DECL|member|disc_id
r_int
r_int
id|disc_id
suffix:semicolon
DECL|member|disc_name
r_int
r_char
id|disc_name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|disc_type
r_int
r_int
id|disc_type
suffix:semicolon
DECL|member|disc_size_high
r_int
r_int
id|disc_size_high
suffix:semicolon
DECL|member|log2sharesize
r_int
r_char
id|log2sharesize
suffix:colon
l_int|4
suffix:semicolon
DECL|member|unused
r_int
r_char
id|unused
suffix:colon
l_int|4
suffix:semicolon
DECL|member|big_flag
r_int
r_char
id|big_flag
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ADFS_DISCRECORD
mdefine_line|#define ADFS_DISCRECORD&t;&t;(0xc00)
DECL|macro|ADFS_DR_OFFSET
mdefine_line|#define ADFS_DR_OFFSET&t;&t;(0x1c0)
DECL|macro|ADFS_DR_SIZE
mdefine_line|#define ADFS_DR_SIZE&t;&t; 60
DECL|macro|ADFS_SUPER_MAGIC
mdefine_line|#define ADFS_SUPER_MAGIC&t; 0xadf5
DECL|macro|ADFS_FREE_FRAG
mdefine_line|#define ADFS_FREE_FRAG&t;&t; 0
DECL|macro|ADFS_BAD_FRAG
mdefine_line|#define ADFS_BAD_FRAG&t;&t; 1
DECL|macro|ADFS_ROOT_FRAG
mdefine_line|#define ADFS_ROOT_FRAG&t;&t; 2
multiline_comment|/*&n; * Directory header&n; */
DECL|struct|adfs_dirheader
r_struct
id|adfs_dirheader
(brace
DECL|member|startmasseq
r_int
r_char
id|startmasseq
suffix:semicolon
DECL|member|startname
r_int
r_char
id|startname
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ADFS_NEWDIR_SIZE
mdefine_line|#define ADFS_NEWDIR_SIZE&t;2048
DECL|macro|ADFS_OLDDIR_SIZE
mdefine_line|#define ADFS_OLDDIR_SIZE&t;1024
DECL|macro|ADFS_NUM_DIR_ENTRIES
mdefine_line|#define ADFS_NUM_DIR_ENTRIES&t;77
multiline_comment|/*&n; * Directory entries&n; */
DECL|struct|adfs_direntry
r_struct
id|adfs_direntry
(brace
DECL|member|dirobname
r_char
id|dirobname
(braket
l_int|10
)braket
suffix:semicolon
DECL|macro|ADFS_NAME_LEN
mdefine_line|#define ADFS_NAME_LEN 10
DECL|member|dirload
id|__u8
id|dirload
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|direxec
id|__u8
id|direxec
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dirlen
id|__u8
id|dirlen
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dirinddiscadd
id|__u8
id|dirinddiscadd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|newdiratts
id|__u8
id|newdiratts
suffix:semicolon
DECL|macro|ADFS_NDA_OWNER_READ
mdefine_line|#define ADFS_NDA_OWNER_READ&t;(1 &lt;&lt; 0)
DECL|macro|ADFS_NDA_OWNER_WRITE
mdefine_line|#define ADFS_NDA_OWNER_WRITE&t;(1 &lt;&lt; 1)
DECL|macro|ADFS_NDA_LOCKED
mdefine_line|#define ADFS_NDA_LOCKED&t;&t;(1 &lt;&lt; 2)
DECL|macro|ADFS_NDA_DIRECTORY
mdefine_line|#define ADFS_NDA_DIRECTORY&t;(1 &lt;&lt; 3)
DECL|macro|ADFS_NDA_EXECUTE
mdefine_line|#define ADFS_NDA_EXECUTE&t;(1 &lt;&lt; 4)
DECL|macro|ADFS_NDA_PUBLIC_READ
mdefine_line|#define ADFS_NDA_PUBLIC_READ&t;(1 &lt;&lt; 5)
DECL|macro|ADFS_NDA_PUBLIC_WRITE
mdefine_line|#define ADFS_NDA_PUBLIC_WRITE&t;(1 &lt;&lt; 6)
)brace
suffix:semicolon
DECL|macro|ADFS_MAX_NAME_LEN
mdefine_line|#define ADFS_MAX_NAME_LEN&t;255
DECL|struct|adfs_idir_entry
r_struct
id|adfs_idir_entry
(brace
DECL|member|inode_no
id|__u32
id|inode_no
suffix:semicolon
multiline_comment|/* Address&t;&t;*/
DECL|member|file_id
id|__u32
id|file_id
suffix:semicolon
multiline_comment|/* file id&t;&t;*/
DECL|member|name_len
id|__u32
id|name_len
suffix:semicolon
multiline_comment|/* name length&t;&t;*/
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/* size&t;&t;&t;*/
DECL|member|mtime
id|__u32
id|mtime
suffix:semicolon
multiline_comment|/* modification time&t;*/
DECL|member|filetype
id|__u32
id|filetype
suffix:semicolon
multiline_comment|/* RiscOS file type&t;*/
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
multiline_comment|/* internal mode&t;*/
DECL|member|name
r_char
id|name
(braket
id|ADFS_MAX_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* file name&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Directory tail&n; */
DECL|union|adfs_dirtail
r_union
id|adfs_dirtail
(brace
r_struct
(brace
DECL|member|dirlastmask
r_int
r_char
id|dirlastmask
suffix:semicolon
DECL|member|dirname
r_char
id|dirname
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|dirparent
r_int
r_char
id|dirparent
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dirtitle
r_char
id|dirtitle
(braket
l_int|19
)braket
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|endmasseq
r_int
r_char
id|endmasseq
suffix:semicolon
DECL|member|endname
r_int
r_char
id|endname
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dircheckbyte
r_int
r_char
id|dircheckbyte
suffix:semicolon
DECL|member|old
)brace
id|old
suffix:semicolon
r_struct
(brace
DECL|member|dirlastmask
r_int
r_char
id|dirlastmask
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dirparent
r_int
r_char
id|dirparent
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dirtitle
r_char
id|dirtitle
(braket
l_int|19
)braket
suffix:semicolon
DECL|member|dirname
r_char
id|dirname
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|endmasseq
r_int
r_char
id|endmasseq
suffix:semicolon
DECL|member|endname
r_int
r_char
id|endname
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dircheckbyte
r_int
r_char
id|dircheckbyte
suffix:semicolon
DECL|member|new
)brace
r_new
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Calculate the boot block checksum on an ADFS drive.  Note that this will&n; * appear to be correct if the sector contains all zeros, so also check that&n; * the disk size is non-zero!!!&n; */
DECL|function|adfs_checkbblk
r_extern
r_inline
r_int
id|adfs_checkbblk
c_func
(paren
r_int
r_char
op_star
id|ptr
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|ptr
op_plus
l_int|511
suffix:semicolon
r_do
(brace
id|result
op_assign
(paren
id|result
op_amp
l_int|0xff
)paren
op_plus
(paren
id|result
op_rshift
l_int|8
)paren
suffix:semicolon
id|result
op_assign
id|result
op_plus
op_star
op_decrement
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
id|ptr
)paren
suffix:semicolon
r_return
(paren
id|result
op_amp
l_int|0xff
)paren
op_ne
id|ptr
(braket
l_int|511
)braket
suffix:semicolon
)brace
multiline_comment|/* dir.c */
r_extern
r_int
r_int
id|adfs_val
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|adfs_dir_read_parent
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
)paren
suffix:semicolon
r_extern
r_int
id|adfs_dir_read
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
)paren
suffix:semicolon
r_extern
r_int
id|adfs_dir_check
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
r_int
id|buffers
comma
r_union
id|adfs_dirtail
op_star
id|dtp
)paren
suffix:semicolon
r_extern
r_void
id|adfs_dir_free
(paren
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
r_int
id|buffers
)paren
suffix:semicolon
r_extern
r_int
id|adfs_dir_get
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
r_int
id|buffers
comma
r_int
id|pos
comma
r_int
r_int
id|parent_object_id
comma
r_struct
id|adfs_idir_entry
op_star
id|ide
)paren
suffix:semicolon
r_extern
r_int
id|adfs_dir_find_entry
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
r_int
id|buffers
comma
r_int
r_int
id|index
comma
r_struct
id|adfs_idir_entry
op_star
id|ide
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_int
id|adfs_inode_validate
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
r_int
id|adfs_inode_generate
(paren
r_int
r_int
id|parent_id
comma
r_int
id|diridx
)paren
suffix:semicolon
r_extern
r_int
r_int
id|adfs_inode_objid
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
r_int
id|adfs_parent_bmap
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_int
id|adfs_bmap
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_void
id|adfs_read_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* map.c */
r_extern
r_int
id|adfs_map_lookup
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|frag_id
comma
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|adfs_lookup
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_int
id|init_adfs_fs
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|adfs_error
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
suffix:semicolon
multiline_comment|/*&n; * Inodes and file operations&n; */
multiline_comment|/* dir.c */
r_extern
r_struct
id|inode_operations
id|adfs_dir_inode_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|adfs_file_inode_operations
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
