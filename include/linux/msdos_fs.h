macro_line|#ifndef _LINUX_MSDOS_FS_H
DECL|macro|_LINUX_MSDOS_FS_H
mdefine_line|#define _LINUX_MSDOS_FS_H
multiline_comment|/*&n; * The MS-DOS filesystem constants/structures&n; */
macro_line|#include &lt;linux/fs.h&gt;
DECL|macro|MSDOS_ROOT_INO
mdefine_line|#define MSDOS_ROOT_INO  1 /* == MINIX_ROOT_INO */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE     512 /* sector size (bytes) */
DECL|macro|SECTOR_BITS
mdefine_line|#define SECTOR_BITS&t;9 /* log2(SECTOR_SIZE) */
DECL|macro|MSDOS_DPB
mdefine_line|#define MSDOS_DPB&t;(MSDOS_DPS*2) /* dir entries per block */
DECL|macro|MSDOS_DPB_BITS
mdefine_line|#define MSDOS_DPB_BITS&t;5 /* log2(MSDOS_DPB) */
DECL|macro|MSDOS_DPS
mdefine_line|#define MSDOS_DPS&t;(SECTOR_SIZE/sizeof(struct msdos_dir_entry))
DECL|macro|MSDOS_DPS_BITS
mdefine_line|#define MSDOS_DPS_BITS&t;4 /* log2(MSDOS_DPS) */
DECL|macro|MSDOS_DIR_BITS
mdefine_line|#define MSDOS_DIR_BITS&t;5 /* log2(sizeof(struct msdos_dir_entry)) */
DECL|macro|MSDOS_SUPER_MAGIC
mdefine_line|#define MSDOS_SUPER_MAGIC 0x4d44 /* MD */
DECL|macro|FAT_CACHE
mdefine_line|#define FAT_CACHE    8 /* FAT cache size */
DECL|macro|ATTR_RO
mdefine_line|#define ATTR_RO      1  /* read-only */
DECL|macro|ATTR_HIDDEN
mdefine_line|#define ATTR_HIDDEN  2  /* hidden */
DECL|macro|ATTR_SYS
mdefine_line|#define ATTR_SYS     4  /* system */
DECL|macro|ATTR_VOLUME
mdefine_line|#define ATTR_VOLUME  8  /* volume label */
DECL|macro|ATTR_DIR
mdefine_line|#define ATTR_DIR     16 /* directory */
DECL|macro|ATTR_ARCH
mdefine_line|#define ATTR_ARCH    32 /* archived */
DECL|macro|ATTR_NONE
mdefine_line|#define ATTR_NONE    0 /* no attribute bits */
DECL|macro|ATTR_UNUSED
mdefine_line|#define ATTR_UNUSED  (ATTR_VOLUME | ATTR_ARCH | ATTR_SYS | ATTR_HIDDEN)
multiline_comment|/* attribute bits that are copied &quot;as is&quot; */
DECL|macro|DELETED_FLAG
mdefine_line|#define DELETED_FLAG 0xe5 /* marks file as deleted when in name[0] */
DECL|macro|MSDOS_SB
mdefine_line|#define MSDOS_SB(s) (&amp;((s)-&gt;u.msdos_sb))
DECL|macro|MSDOS_I
mdefine_line|#define MSDOS_I(i) (&amp;((i)-&gt;u.msdos_i))
DECL|macro|MSDOS_NAME
mdefine_line|#define MSDOS_NAME 11 /* maximum name length */
DECL|macro|MSDOS_DOT
mdefine_line|#define MSDOS_DOT    &quot;.          &quot; /* &quot;.&quot;, padded to MSDOS_NAME chars */
DECL|macro|MSDOS_DOTDOT
mdefine_line|#define MSDOS_DOTDOT &quot;..         &quot; /* &quot;..&quot;, padded to MSDOS_NAME chars */
DECL|macro|MSDOS_FAT12
mdefine_line|#define MSDOS_FAT12 4086 /* maximum number of clusters in a 12 bit FAT */
DECL|struct|msdos_boot_sector
r_struct
id|msdos_boot_sector
(brace
DECL|member|ignored
r_char
id|ignored
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|cluster_size
r_int
r_char
id|cluster_size
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
multiline_comment|/* reserved sectors */
DECL|member|fats
r_int
r_char
id|fats
suffix:semicolon
multiline_comment|/* number of FATs */
DECL|member|dir_entries
r_int
r_char
id|dir_entries
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* root directory entries */
DECL|member|sectors
r_int
r_char
id|sectors
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* number of sectors */
DECL|member|media
r_int
r_char
id|media
suffix:semicolon
multiline_comment|/* media code (unused) */
DECL|member|fat_length
r_int
r_int
id|fat_length
suffix:semicolon
multiline_comment|/* sectors/FAT */
DECL|member|secs_track
r_int
r_int
id|secs_track
suffix:semicolon
multiline_comment|/* sectors per track (unused) */
DECL|member|heads
r_int
r_int
id|heads
suffix:semicolon
multiline_comment|/* number of heads (unused) */
DECL|member|hidden
r_int
r_int
id|hidden
suffix:semicolon
multiline_comment|/* hidden sectors (unused) */
DECL|member|total_sect
r_int
r_int
id|total_sect
suffix:semicolon
multiline_comment|/* number of sectors (if sectors == 0) */
)brace
suffix:semicolon
DECL|struct|msdos_dir_entry
r_struct
id|msdos_dir_entry
(brace
DECL|member|name
DECL|member|ext
r_char
id|name
(braket
l_int|8
)braket
comma
id|ext
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* name and extension */
DECL|member|attr
r_int
r_char
id|attr
suffix:semicolon
multiline_comment|/* attribute bits */
DECL|member|unused
r_char
id|unused
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|time
DECL|member|date
DECL|member|start
r_int
r_int
id|time
comma
id|date
comma
id|start
suffix:semicolon
multiline_comment|/* time, date and first cluster */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* file size (in bytes) */
)brace
suffix:semicolon
DECL|struct|fat_cache
r_struct
id|fat_cache
(brace
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* device number. 0 means unused. */
DECL|member|ino
r_int
id|ino
suffix:semicolon
multiline_comment|/* inode number. */
DECL|member|file_cluster
r_int
id|file_cluster
suffix:semicolon
multiline_comment|/* cluster number in the file. */
DECL|member|disk_cluster
r_int
id|disk_cluster
suffix:semicolon
multiline_comment|/* cluster number on disk. */
DECL|member|next
r_struct
id|fat_cache
op_star
id|next
suffix:semicolon
multiline_comment|/* next cache entry */
)brace
suffix:semicolon
multiline_comment|/* Determine whether this FS has kB-aligned data. */
DECL|macro|MSDOS_CAN_BMAP
mdefine_line|#define MSDOS_CAN_BMAP(mib) (!(((mib)-&gt;cluster_size &amp; 1) || &bslash;&n;    ((mib)-&gt;data_start &amp; 1)))
multiline_comment|/* Convert attribute bits and a mask to the UNIX mode. */
DECL|macro|MSDOS_MKMODE
mdefine_line|#define MSDOS_MKMODE(a,m) (m &amp; (a &amp; ATTR_RO ? 0444 : 0777))
multiline_comment|/* Convert the UNIX mode to MS-DOS attribute bits. */
DECL|macro|MSDOS_MKATTR
mdefine_line|#define MSDOS_MKATTR(m) (!(m &amp; 0200) ? ATTR_RO : ATTR_NONE)
DECL|function|msdos_sread
r_static
r_inline
r_struct
id|buffer_head
op_star
id|msdos_sread
c_func
(paren
r_int
id|dev
comma
r_int
id|sector
comma
r_void
op_star
op_star
id|start
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
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
id|sector
op_rshift
l_int|1
comma
l_int|1024
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|start
op_assign
id|bh-&gt;b_data
op_plus
(paren
(paren
id|sector
op_amp
l_int|1
)paren
op_lshift
id|SECTOR_BITS
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
multiline_comment|/* misc.c */
r_extern
r_int
id|is_binary
c_func
(paren
r_char
id|conversion
comma
r_char
op_star
id|extension
)paren
suffix:semicolon
r_extern
r_void
id|lock_creation
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unlock_creation
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|unlock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_int
id|msdos_add_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|date_dos2unix
c_func
(paren
r_int
r_int
id|time
comma
r_int
r_int
id|date
)paren
suffix:semicolon
r_extern
r_void
id|date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
r_int
r_int
op_star
id|time
comma
r_int
r_int
op_star
id|date
)paren
suffix:semicolon
r_extern
r_int
id|msdos_get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
op_star
id|pos
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
)paren
suffix:semicolon
r_extern
r_int
id|msdos_scan
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_char
op_star
id|name
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
comma
r_int
op_star
id|ino
)paren
suffix:semicolon
r_extern
r_int
id|msdos_parent_ino
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|locked
)paren
suffix:semicolon
r_extern
r_int
id|msdos_subdirs
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
multiline_comment|/* fat.c */
r_extern
r_int
id|fat_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|this
comma
r_int
id|new_value
)paren
suffix:semicolon
r_extern
r_int
id|msdos_smap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|sector
)paren
suffix:semicolon
r_extern
r_int
id|fat_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|skip
)paren
suffix:semicolon
r_extern
r_void
id|cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cache_lookup
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
comma
r_int
op_star
id|f_clu
comma
r_int
op_star
id|d_clu
)paren
suffix:semicolon
r_void
id|cache_add
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|f_clu
comma
r_int
id|d_clu
)paren
suffix:semicolon
r_void
id|cache_inval_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|cache_inval_dev
c_func
(paren
r_int
id|device
)paren
suffix:semicolon
r_int
id|get_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cluster
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|msdos_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
suffix:semicolon
r_extern
r_int
id|msdos_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|mode
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
suffix:semicolon
r_extern
r_int
id|msdos_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|msdos_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|msdos_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|msdos_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_const
r_char
op_star
id|old_name
comma
r_int
id|old_len
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_const
r_char
op_star
id|new_name
comma
r_int
id|new_len
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_void
id|msdos_put_inode
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
id|msdos_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|msdos_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|msdos_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
id|msdos_bmap
c_func
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
id|msdos_read_inode
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
id|msdos_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|msdos_dir_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|msdos_dir_inode_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|file_operations
id|msdos_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|msdos_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|msdos_file_inode_operations_no_bmap
suffix:semicolon
r_extern
r_void
id|msdos_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
macro_line|#endif
eof
