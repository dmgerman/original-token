multiline_comment|/*&n; *  linux/include/linux/ext2_fs.h&n; *&n; *  Copyright (C) 1992, 1993, 1994  Remy Card (card@masi.ibp.fr)&n; *                                  Laboratoire MASI - Institut Blaise Pascal&n; *                                  Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT2_FS_H
DECL|macro|_LINUX_EXT2_FS_H
mdefine_line|#define _LINUX_EXT2_FS_H
multiline_comment|/*&n; * The second extended filesystem constants/structures&n; */
multiline_comment|/*&n; * Define EXT2FS_DEBUG to produce debug messages&n; */
DECL|macro|EXT2FS_DEBUG
macro_line|#undef EXT2FS_DEBUG
multiline_comment|/*&n; * Define EXT2FS_DEBUG_CACHE to produce cache debug messages&n; */
DECL|macro|EXT2FS_DEBUG_CACHE
macro_line|#undef EXT2FS_DEBUG_CACHE
multiline_comment|/*&n; * Define EXT2FS_CHECK_CACHE to add some checks to the name cache code&n; */
DECL|macro|EXT2FS_CHECK_CACHE
macro_line|#undef EXT2FS_CHECK_CACHE
multiline_comment|/*&n; * Define EXT2FS_PRE_02B_COMPAT to convert ext 2 fs prior to 0.2b&n; */
DECL|macro|EXT2FS_PRE_02B_COMPAT
macro_line|#undef EXT2FS_PRE_02B_COMPAT
multiline_comment|/*&n; * Define DONT_USE_DCACHE to inhibit the directory cache&n; */
DECL|macro|DONT_USE_DCACHE
mdefine_line|#define DONT_USE_DCACHE
multiline_comment|/*&n; * Define EXT2_PREALLOCATE to preallocate data blocks for expanding files&n; */
DECL|macro|EXT2_PREALLOCATE
mdefine_line|#define EXT2_PREALLOCATE
multiline_comment|/*&n; * The second extended file system version&n; */
DECL|macro|EXT2FS_DATE
mdefine_line|#define EXT2FS_DATE&t;&t;&quot;94/03/10&quot;
DECL|macro|EXT2FS_VERSION
mdefine_line|#define EXT2FS_VERSION&t;&t;&quot;0.5&quot;
multiline_comment|/*&n; * Debug code&n; */
macro_line|#ifdef EXT2FS_DEBUG
DECL|macro|ext2_debug
macro_line|#&t;define ext2_debug(f, a...)&t;{ &bslash;&n;&t;&t;&t;&t;&t;printk (&quot;EXT2-fs DEBUG (%s, %d): %s:&quot;, &bslash;&n;&t;&t;&t;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__); &bslash;&n;&t;&t;&t;&t;  &t;printk (f, ## a); &bslash;&n;&t;&t;&t;&t;&t;}
macro_line|#else
DECL|macro|ext2_debug
macro_line|#&t;define ext2_debug(f, a...)&t;/**/
macro_line|#endif
multiline_comment|/*&n; * Special inodes numbers&n; */
DECL|macro|EXT2_BAD_INO
mdefine_line|#define&t;EXT2_BAD_INO&t;&t; 1&t;/* Bad blocks inode */
DECL|macro|EXT2_ROOT_INO
mdefine_line|#define EXT2_ROOT_INO&t;&t; 2&t;/* Root inode */
DECL|macro|EXT2_ACL_IDX_INO
mdefine_line|#define EXT2_ACL_IDX_INO&t; 3&t;/* ACL inode */
DECL|macro|EXT2_ACL_DATA_INO
mdefine_line|#define EXT2_ACL_DATA_INO&t; 4&t;/* ACL inode */
DECL|macro|EXT2_BOOT_LOADER_INO
mdefine_line|#define EXT2_BOOT_LOADER_INO&t; 5&t;/* Boot loader inode */
DECL|macro|EXT2_UNDEL_DIR_INO
mdefine_line|#define EXT2_UNDEL_DIR_INO&t; 6&t;/* Undelete directory inode */
DECL|macro|EXT2_FIRST_INO
mdefine_line|#define EXT2_FIRST_INO&t;&t;11&t;/* First non reserved inode */
multiline_comment|/*&n; * The second extended file system magic number&n; */
DECL|macro|EXT2_PRE_02B_MAGIC
mdefine_line|#define EXT2_PRE_02B_MAGIC&t;0xEF51
DECL|macro|EXT2_SUPER_MAGIC
mdefine_line|#define EXT2_SUPER_MAGIC&t;0xEF53
multiline_comment|/*&n; * Maximal count of links to a file&n; */
DECL|macro|EXT2_LINK_MAX
mdefine_line|#define EXT2_LINK_MAX&t;&t;32000
multiline_comment|/*&n; * Macro-instructions used to manage several block sizes&n; */
DECL|macro|EXT2_MIN_BLOCK_SIZE
mdefine_line|#define EXT2_MIN_BLOCK_SIZE&t;&t;1024
DECL|macro|EXT2_MAX_BLOCK_SIZE
mdefine_line|#define&t;EXT2_MAX_BLOCK_SIZE&t;&t;4096
DECL|macro|EXT2_MIN_BLOCK_LOG_SIZE
mdefine_line|#define EXT2_MIN_BLOCK_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCK_SIZE
macro_line|# define EXT2_BLOCK_SIZE(s)&t;&t;((s)-&gt;s_blocksize)
macro_line|#else
DECL|macro|EXT2_BLOCK_SIZE
macro_line|# define EXT2_BLOCK_SIZE(s)&t;&t;(EXT2_MIN_BLOCK_SIZE &lt;&lt; (s)-&gt;s_log_block_size)
macro_line|#endif
DECL|macro|EXT2_ACLE_PER_BLOCK
mdefine_line|#define EXT2_ACLE_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_acl_entry))
DECL|macro|EXT2_ADDR_PER_BLOCK
mdefine_line|#define&t;EXT2_ADDR_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (unsigned long))
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCK_SIZE_BITS
macro_line|# define EXT2_BLOCK_SIZE_BITS(s)&t;((s)-&gt;u.ext2_sb.s_es-&gt;s_log_block_size + 10)
macro_line|#else
DECL|macro|EXT2_BLOCK_SIZE_BITS
macro_line|# define EXT2_BLOCK_SIZE_BITS(s)&t;((s)-&gt;s_log_block_size + 10)
macro_line|#endif
DECL|macro|EXT2_INODES_PER_BLOCK
mdefine_line|#define&t;EXT2_INODES_PER_BLOCK(s)&t;(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_inode))
multiline_comment|/*&n; * Macro-instructions used to manage fragments&n; */
DECL|macro|EXT2_MIN_FRAG_SIZE
mdefine_line|#define EXT2_MIN_FRAG_SIZE&t;&t;1024
DECL|macro|EXT2_MAX_FRAG_SIZE
mdefine_line|#define&t;EXT2_MAX_FRAG_SIZE&t;&t;4096
DECL|macro|EXT2_MIN_FRAG_LOG_SIZE
mdefine_line|#define EXT2_MIN_FRAG_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_FRAG_SIZE
macro_line|# define EXT2_FRAG_SIZE(s)&t;&t;((s)-&gt;u.ext2_sb.s_frag_size)
DECL|macro|EXT2_FRAGS_PER_BLOCK
macro_line|# define EXT2_FRAGS_PER_BLOCK(s)&t;((s)-&gt;u.ext2_sb.s_frags_per_block)
macro_line|#else
DECL|macro|EXT2_FRAG_SIZE
macro_line|# define EXT2_FRAG_SIZE(s)&t;&t;(EXT2_MIN_FRAG_SIZE &lt;&lt; (s)-&gt;s_log_frag_size)
DECL|macro|EXT2_FRAGS_PER_BLOCK
macro_line|# define EXT2_FRAGS_PER_BLOCK(s)&t;(EXT2_BLOCK_SIZE(s) / EXT2_FRAG_SIZE(s))
macro_line|#endif
multiline_comment|/*&n; * ACL structures&n; */
DECL|struct|ext2_acl_header
r_struct
id|ext2_acl_header
multiline_comment|/* Header of Access Control Lists */
(brace
DECL|member|aclh_size
r_int
r_int
id|aclh_size
suffix:semicolon
DECL|member|aclh_file_count
r_int
r_int
id|aclh_file_count
suffix:semicolon
DECL|member|aclh_acle_count
r_int
r_int
id|aclh_acle_count
suffix:semicolon
DECL|member|aclh_first_acle
r_int
r_int
id|aclh_first_acle
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ext2_acl_entry
r_struct
id|ext2_acl_entry
multiline_comment|/* Access Control List Entry */
(brace
DECL|member|acle_size
r_int
r_int
id|acle_size
suffix:semicolon
DECL|member|acle_perms
r_int
r_int
id|acle_perms
suffix:semicolon
multiline_comment|/* Access permissions */
DECL|member|acle_type
r_int
r_int
id|acle_type
suffix:semicolon
multiline_comment|/* Type of entry */
DECL|member|acle_tag
r_int
r_int
id|acle_tag
suffix:semicolon
multiline_comment|/* User or group identity */
DECL|member|acle_pad1
r_int
r_int
id|acle_pad1
suffix:semicolon
DECL|member|acle_next
r_int
r_int
id|acle_next
suffix:semicolon
multiline_comment|/* Pointer on next entry for the */
multiline_comment|/* same inode or on next free entry */
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of a blocks group descriptor&n; */
DECL|struct|ext2_old_group_desc
r_struct
id|ext2_old_group_desc
(brace
DECL|member|bg_block_bitmap
r_int
r_int
id|bg_block_bitmap
suffix:semicolon
multiline_comment|/* Blocks bitmap block */
DECL|member|bg_inode_bitmap
r_int
r_int
id|bg_inode_bitmap
suffix:semicolon
multiline_comment|/* Inodes bitmap block */
DECL|member|bg_inode_table
r_int
r_int
id|bg_inode_table
suffix:semicolon
multiline_comment|/* Inodes table block */
DECL|member|bg_free_blocks_count
r_int
r_int
id|bg_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|bg_free_inodes_count
r_int
r_int
id|bg_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
)brace
suffix:semicolon
DECL|struct|ext2_group_desc
r_struct
id|ext2_group_desc
(brace
DECL|member|bg_block_bitmap
r_int
r_int
id|bg_block_bitmap
suffix:semicolon
multiline_comment|/* Blocks bitmap block */
DECL|member|bg_inode_bitmap
r_int
r_int
id|bg_inode_bitmap
suffix:semicolon
multiline_comment|/* Inodes bitmap block */
DECL|member|bg_inode_table
r_int
r_int
id|bg_inode_table
suffix:semicolon
multiline_comment|/* Inodes table block */
DECL|member|bg_free_blocks_count
r_int
r_int
id|bg_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|bg_free_inodes_count
r_int
r_int
id|bg_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|bg_used_dirs_count
r_int
r_int
id|bg_used_dirs_count
suffix:semicolon
multiline_comment|/* Directories count */
DECL|member|bg_pad
r_int
r_int
id|bg_pad
suffix:semicolon
DECL|member|bg_reserved
r_int
r_int
id|bg_reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Macro-instructions used to manage group descriptors&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCKS_PER_GROUP
macro_line|# define EXT2_BLOCKS_PER_GROUP(s)&t;((s)-&gt;u.ext2_sb.s_blocks_per_group)
DECL|macro|EXT2_DESC_PER_BLOCK
macro_line|# define EXT2_DESC_PER_BLOCK(s)&t;&t;((s)-&gt;u.ext2_sb.s_desc_per_block)
DECL|macro|EXT2_INODES_PER_GROUP
macro_line|# define EXT2_INODES_PER_GROUP(s)&t;((s)-&gt;u.ext2_sb.s_inodes_per_group)
macro_line|#else
DECL|macro|EXT2_BLOCKS_PER_GROUP
macro_line|# define EXT2_BLOCKS_PER_GROUP(s)&t;((s)-&gt;s_blocks_per_group)
DECL|macro|EXT2_DESC_PER_BLOCK
macro_line|# define EXT2_DESC_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_group_desc))
DECL|macro|EXT2_INODES_PER_GROUP
macro_line|# define EXT2_INODES_PER_GROUP(s)&t;((s)-&gt;s_inodes_per_group)
macro_line|#endif
multiline_comment|/*&n; * Constants relative to the data blocks&n; */
DECL|macro|EXT2_NDIR_BLOCKS
mdefine_line|#define&t;EXT2_NDIR_BLOCKS&t;&t;12
DECL|macro|EXT2_IND_BLOCK
mdefine_line|#define&t;EXT2_IND_BLOCK&t;&t;&t;EXT2_NDIR_BLOCKS
DECL|macro|EXT2_DIND_BLOCK
mdefine_line|#define&t;EXT2_DIND_BLOCK&t;&t;&t;(EXT2_IND_BLOCK + 1)
DECL|macro|EXT2_TIND_BLOCK
mdefine_line|#define&t;EXT2_TIND_BLOCK&t;&t;&t;(EXT2_DIND_BLOCK + 1)
DECL|macro|EXT2_N_BLOCKS
mdefine_line|#define&t;EXT2_N_BLOCKS&t;&t;&t;(EXT2_TIND_BLOCK + 1)
multiline_comment|/*&n; * Inode flags&n; */
DECL|macro|EXT2_SECRM_FL
mdefine_line|#define&t;EXT2_SECRM_FL&t;&t;&t;0x0001&t;/* Secure deletion */
DECL|macro|EXT2_UNRM_FL
mdefine_line|#define&t;EXT2_UNRM_FL&t;&t;&t;0x0002&t;/* Undelete */
DECL|macro|EXT2_COMPR_FL
mdefine_line|#define&t;EXT2_COMPR_FL&t;&t;&t;0x0004&t;/* Compress file */
DECL|macro|EXT2_SYNC_FL
mdefine_line|#define EXT2_SYNC_FL&t;&t;&t;0x0008&t;/* Synchronous updates */
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|EXT2_IOC_GETFLAGS
mdefine_line|#define&t;EXT2_IOC_GETFLAGS&t;&t;_IOR(&squot;f&squot;, 1, long)
DECL|macro|EXT2_IOC_SETFLAGS
mdefine_line|#define&t;EXT2_IOC_SETFLAGS&t;&t;_IOW(&squot;f&squot;, 2, long)
DECL|macro|EXT2_IOC_GETVERSION
mdefine_line|#define&t;EXT2_IOC_GETVERSION&t;&t;_IOR(&squot;v&squot;, 1, long)
DECL|macro|EXT2_IOC_SETVERSION
mdefine_line|#define&t;EXT2_IOC_SETVERSION&t;&t;_IOW(&squot;v&squot;, 2, long)
multiline_comment|/*&n; * Structure of an inode on the disk&n; */
DECL|struct|ext2_inode
r_struct
id|ext2_inode
(brace
DECL|member|i_mode
r_int
r_int
id|i_mode
suffix:semicolon
multiline_comment|/* File mode */
DECL|member|i_uid
r_int
r_int
id|i_uid
suffix:semicolon
multiline_comment|/* Owner Uid */
DECL|member|i_size
r_int
r_int
id|i_size
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|member|i_atime
r_int
r_int
id|i_atime
suffix:semicolon
multiline_comment|/* Access time */
DECL|member|i_ctime
r_int
r_int
id|i_ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|i_mtime
r_int
r_int
id|i_mtime
suffix:semicolon
multiline_comment|/* Modification time */
DECL|member|i_dtime
r_int
r_int
id|i_dtime
suffix:semicolon
multiline_comment|/* Deletion Time */
DECL|member|i_gid
r_int
r_int
id|i_gid
suffix:semicolon
multiline_comment|/* Group Id */
DECL|member|i_links_count
r_int
r_int
id|i_links_count
suffix:semicolon
multiline_comment|/* Links count */
DECL|member|i_blocks
r_int
r_int
id|i_blocks
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|i_flags
r_int
r_int
id|i_flags
suffix:semicolon
multiline_comment|/* File flags */
DECL|member|i_reserved1
r_int
r_int
id|i_reserved1
suffix:semicolon
DECL|member|i_block
r_int
r_int
id|i_block
(braket
id|EXT2_N_BLOCKS
)braket
suffix:semicolon
multiline_comment|/* Pointers to blocks */
DECL|member|i_version
r_int
r_int
id|i_version
suffix:semicolon
multiline_comment|/* File version (for NFS) */
DECL|member|i_file_acl
r_int
r_int
id|i_file_acl
suffix:semicolon
multiline_comment|/* File ACL */
DECL|member|i_dir_acl
r_int
r_int
id|i_dir_acl
suffix:semicolon
multiline_comment|/* Directory ACL */
DECL|member|i_faddr
r_int
r_int
id|i_faddr
suffix:semicolon
multiline_comment|/* Fragment address */
DECL|member|i_frag
r_int
r_char
id|i_frag
suffix:semicolon
multiline_comment|/* Fragment number */
DECL|member|i_fsize
r_int
r_char
id|i_fsize
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|i_pad1
r_int
r_int
id|i_pad1
suffix:semicolon
DECL|member|i_reserved2
r_int
r_int
id|i_reserved2
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * File system states&n; */
DECL|macro|EXT2_VALID_FS
mdefine_line|#define&t;EXT2_VALID_FS&t;&t;&t;0x0001&t;/* Unmounted cleany */
DECL|macro|EXT2_ERROR_FS
mdefine_line|#define&t;EXT2_ERROR_FS&t;&t;&t;0x0002&t;/* Errors detected */
multiline_comment|/*&n; * Mount flags&n; */
DECL|macro|EXT2_MOUNT_CHECK_NORMAL
mdefine_line|#define EXT2_MOUNT_CHECK_NORMAL&t;&t;0x0001&t;/* Do some more checks */
DECL|macro|EXT2_MOUNT_CHECK_STRICT
mdefine_line|#define EXT2_MOUNT_CHECK_STRICT&t;&t;0x0002&t;/* Do again more checks */
DECL|macro|EXT2_MOUNT_CHECK
mdefine_line|#define EXT2_MOUNT_CHECK&t;&t;(EXT2_MOUNT_CHECK_NORMAL | &bslash;&n;&t;&t;&t;&t;&t; EXT2_MOUNT_CHECK_STRICT)
DECL|macro|EXT2_MOUNT_GRPID
mdefine_line|#define EXT2_MOUNT_GRPID&t;&t;0x0004&t;/* Create files with directory&squot;s group */
DECL|macro|EXT2_MOUNT_DEBUG
mdefine_line|#define EXT2_MOUNT_DEBUG&t;&t;0x0008&t;/* Some debugging messages */
DECL|macro|EXT2_MOUNT_ERRORS_CONT
mdefine_line|#define EXT2_MOUNT_ERRORS_CONT&t;&t;0x0010&t;/* Continue on errors */
DECL|macro|EXT2_MOUNT_ERRORS_RO
mdefine_line|#define EXT2_MOUNT_ERRORS_RO&t;&t;0x0020&t;/* Remount fs ro on errors */
DECL|macro|EXT2_MOUNT_ERRORS_PANIC
mdefine_line|#define EXT2_MOUNT_ERRORS_PANIC&t;&t;0x0040&t;/* Panic on errors */
DECL|macro|clear_opt
mdefine_line|#define clear_opt(o, opt)&t;&t;o &amp;= ~EXT2_MOUNT_##opt
DECL|macro|set_opt
mdefine_line|#define set_opt(o, opt)&t;&t;&t;o |= EXT2_MOUNT_##opt
DECL|macro|test_opt
mdefine_line|#define test_opt(sb, opt)&t;&t;((sb)-&gt;u.ext2_sb.s_mount_opt &amp; &bslash;&n;&t;&t;&t;&t;&t; EXT2_MOUNT_##opt)
multiline_comment|/*&n; * Maximal mount counts between two filesystem checks&n; */
DECL|macro|EXT2_DFL_MAX_MNT_COUNT
mdefine_line|#define EXT2_DFL_MAX_MNT_COUNT&t;&t;20&t;/* Allow 20 mounts */
DECL|macro|EXT2_DFL_CHECKINTERVAL
mdefine_line|#define EXT2_DFL_CHECKINTERVAL&t;&t;0&t;/* Don&squot;t use interval check */
multiline_comment|/*&n; * Behaviour when detecting errors&n; */
DECL|macro|EXT2_ERRORS_CONTINUE
mdefine_line|#define EXT2_ERRORS_CONTINUE&t;&t;1&t;/* Continue execution */
DECL|macro|EXT2_ERRORS_RO
mdefine_line|#define EXT2_ERRORS_RO&t;&t;&t;2&t;/* Remount fs read-only */
DECL|macro|EXT2_ERRORS_PANIC
mdefine_line|#define EXT2_ERRORS_PANIC&t;&t;3&t;/* Panic */
DECL|macro|EXT2_ERRORS_DEFAULT
mdefine_line|#define EXT2_ERRORS_DEFAULT&t;&t;EXT2_ERRORS_CONTINUE
multiline_comment|/*&n; * Structure of the super block&n; */
DECL|struct|ext2_super_block
r_struct
id|ext2_super_block
(brace
DECL|member|s_inodes_count
r_int
r_int
id|s_inodes_count
suffix:semicolon
multiline_comment|/* Inodes count */
DECL|member|s_blocks_count
r_int
r_int
id|s_blocks_count
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|s_r_blocks_count
r_int
r_int
id|s_r_blocks_count
suffix:semicolon
multiline_comment|/* Reserved blocks count */
DECL|member|s_free_blocks_count
r_int
r_int
id|s_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|s_free_inodes_count
r_int
r_int
id|s_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|s_first_data_block
r_int
r_int
id|s_first_data_block
suffix:semicolon
multiline_comment|/* First Data Block */
DECL|member|s_log_block_size
r_int
r_int
id|s_log_block_size
suffix:semicolon
multiline_comment|/* Block size */
DECL|member|s_log_frag_size
r_int
id|s_log_frag_size
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|s_blocks_per_group
r_int
r_int
id|s_blocks_per_group
suffix:semicolon
multiline_comment|/* # Blocks per group */
DECL|member|s_frags_per_group
r_int
r_int
id|s_frags_per_group
suffix:semicolon
multiline_comment|/* # Fragments per group */
DECL|member|s_inodes_per_group
r_int
r_int
id|s_inodes_per_group
suffix:semicolon
multiline_comment|/* # Inodes per group */
DECL|member|s_mtime
r_int
r_int
id|s_mtime
suffix:semicolon
multiline_comment|/* Mount time */
DECL|member|s_wtime
r_int
r_int
id|s_wtime
suffix:semicolon
multiline_comment|/* Write time */
DECL|member|s_mnt_count
r_int
r_int
id|s_mnt_count
suffix:semicolon
multiline_comment|/* Mount count */
DECL|member|s_max_mnt_count
r_int
id|s_max_mnt_count
suffix:semicolon
multiline_comment|/* Maximal mount count */
DECL|member|s_magic
r_int
r_int
id|s_magic
suffix:semicolon
multiline_comment|/* Magic signature */
DECL|member|s_state
r_int
r_int
id|s_state
suffix:semicolon
multiline_comment|/* File system state */
DECL|member|s_errors
r_int
r_int
id|s_errors
suffix:semicolon
multiline_comment|/* Behaviour when detecting errors */
DECL|member|s_pad
r_int
r_int
id|s_pad
suffix:semicolon
DECL|member|s_lastcheck
r_int
r_int
id|s_lastcheck
suffix:semicolon
multiline_comment|/* time of last check */
DECL|member|s_checkinterval
r_int
r_int
id|s_checkinterval
suffix:semicolon
multiline_comment|/* max. time between checks */
DECL|member|s_reserved
r_int
r_int
id|s_reserved
(braket
l_int|238
)braket
suffix:semicolon
multiline_comment|/* Padding to the end of the block */
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of a directory entry&n; */
DECL|macro|EXT2_NAME_LEN
mdefine_line|#define EXT2_NAME_LEN 255
DECL|struct|ext2_dir_entry
r_struct
id|ext2_dir_entry
(brace
DECL|member|inode
r_int
r_int
id|inode
suffix:semicolon
multiline_comment|/* Inode number */
DECL|member|rec_len
r_int
r_int
id|rec_len
suffix:semicolon
multiline_comment|/* Directory entry length */
DECL|member|name_len
r_int
r_int
id|name_len
suffix:semicolon
multiline_comment|/* Name length */
DECL|member|name
r_char
id|name
(braket
id|EXT2_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* File name */
)brace
suffix:semicolon
multiline_comment|/*&n; * EXT2_DIR_PAD defines the directory entries boundaries&n; *&n; * NOTE: It must be a multiple of 4&n; */
DECL|macro|EXT2_DIR_PAD
mdefine_line|#define EXT2_DIR_PAD&t;&t; &t;4
DECL|macro|EXT2_DIR_ROUND
mdefine_line|#define EXT2_DIR_ROUND &t;&t;&t;(EXT2_DIR_PAD - 1)
DECL|macro|EXT2_DIR_REC_LEN
mdefine_line|#define EXT2_DIR_REC_LEN(name_len)&t;(((name_len) + 8 + EXT2_DIR_ROUND) &amp; &bslash;&n;&t;&t;&t;&t;&t; ~EXT2_DIR_ROUND)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/*&n; * Ok, these declarations are also in &lt;linux/kernel.h&gt; but none of the&n; * ext2 source programs needs to include it so they are duplicated here.&n; */
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 5)
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    __volatile__
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  /**/
DECL|macro|NORET_AND
macro_line|# define NORET_AND     /**/
macro_line|#else
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
macro_line|#endif
multiline_comment|/* acl.c */
r_extern
r_int
id|ext2_permission
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* balloc.c */
r_extern
r_int
id|ext2_new_block
(paren
r_struct
id|super_block
op_star
comma
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_blocks
(paren
r_struct
id|super_block
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_blocks
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_blocks_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* bitmap.c */
r_extern
r_int
r_int
id|ext2_count_free
(paren
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifndef DONT_USE_DCACHE
multiline_comment|/* dcache.c */
r_extern
r_void
id|ext2_dcache_invalidate
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_dcache_lookup
(paren
r_int
r_int
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_dcache_add
(paren
r_int
r_int
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_dcache_remove
(paren
r_int
r_int
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* dir.c */
r_extern
r_int
id|ext2_check_dir_entry
(paren
r_char
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|ext2_dir_entry
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_int
id|ext2_read
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_write
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* fsync.c */
r_extern
r_int
id|ext2_sync_file
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/* ialloc.c */
r_extern
r_struct
id|inode
op_star
id|ext2_new_inode
(paren
r_const
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_inodes
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_int
id|ext2_bmap
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ext2_getblk
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ext2_bread
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_write_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_put_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_sync_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_discard_prealloc
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_extern
r_int
id|ext2_ioctl
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|ext2_open
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_release
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_lookup
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_create
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_mkdir
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_rmdir
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_unlink
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_symlink
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_link
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_mknod
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_rename
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_void
id|ext2_error
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
id|NORET_TYPE
r_void
id|ext2_panic
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
id|NORET_AND
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
r_void
id|ext2_warning
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
r_void
id|ext2_put_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_remount
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|ext2_read_super
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_statfs
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
multiline_comment|/* truncate.c */
r_extern
r_void
id|ext2_truncate
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Inodes and files operations&n; */
multiline_comment|/* dir.c */
r_extern
r_struct
id|inode_operations
id|ext2_dir_inode_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|ext2_file_inode_operations
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|ext2_symlink_inode_operations
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_EXT2_FS_H */
eof
