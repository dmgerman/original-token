multiline_comment|/*&n; *  inode.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Modified for big endian by J.F. Chadima and David S. Miller&n; *  Modified 1997 Peter Waltenberg, Bill Hawes, David Woodhouse for 2.1 dcache&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
r_static
r_void
id|ncp_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|ncp_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|ncp_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|ncp_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|ncp_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|ncp_sops
r_static
r_struct
id|super_operations
id|ncp_sops
op_assign
(brace
id|ncp_read_inode
comma
multiline_comment|/* read inode */
l_int|NULL
comma
multiline_comment|/* write inode */
id|ncp_put_inode
comma
multiline_comment|/* put inode */
id|ncp_delete_inode
comma
multiline_comment|/* delete inode */
id|ncp_notify_change
comma
multiline_comment|/* notify change */
id|ncp_put_super
comma
multiline_comment|/* put superblock */
l_int|NULL
comma
multiline_comment|/* write superblock */
id|ncp_statfs
comma
multiline_comment|/* stat filesystem */
l_int|NULL
multiline_comment|/* remount */
)brace
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|ncp_dentry_operations
suffix:semicolon
DECL|variable|read_nwinfo
r_static
r_struct
id|nw_file_info
op_star
id|read_nwinfo
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|read_sem
r_static
r_struct
id|semaphore
id|read_sem
op_assign
id|MUTEX
suffix:semicolon
multiline_comment|/*&n; * Fill in the ncpfs-specific information in the inode.&n; */
DECL|function|ncp_update_inode
r_void
id|ncp_update_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nw_file_info
op_star
id|nwinfo
)paren
(brace
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|DosDirNum
op_assign
id|nwinfo-&gt;i.DosDirNum
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
op_assign
id|nwinfo-&gt;i.dirEntNum
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
op_assign
id|nwinfo-&gt;i.volNumber
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
op_assign
id|nwinfo-&gt;opened
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|access
op_assign
id|nwinfo-&gt;access
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|server_file_handle
op_assign
id|nwinfo-&gt;server_file_handle
suffix:semicolon
id|memcpy
c_func
(paren
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|nwinfo-&gt;file_handle
comma
r_sizeof
(paren
id|nwinfo-&gt;file_handle
)paren
)paren
suffix:semicolon
macro_line|#ifdef NCPFS_DEBUG_VERBOSE
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_update_inode: updated %s, volnum=%d, dirent=%u&bslash;n&quot;
comma
id|nwinfo-&gt;i.entryName
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ncp_update_inode2
r_void
id|ncp_update_inode2
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nw_file_info
op_star
id|nwinfo
)paren
(brace
r_struct
id|nw_info_struct
op_star
id|nwi
op_assign
op_amp
id|nwinfo-&gt;i
suffix:semicolon
r_struct
id|ncp_server
op_star
id|server
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
)paren
(brace
r_if
c_cond
(paren
id|nwi-&gt;attributes
op_amp
id|aDIR
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|server-&gt;m.dir_mode
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|512
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_mode
op_assign
id|server-&gt;m.file_mode
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|le32_to_cpu
c_func
(paren
id|nwi-&gt;dataStreamSize
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nwi-&gt;attributes
op_amp
id|aRONLY
)paren
id|inode-&gt;i_mode
op_and_assign
op_complement
l_int|0222
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_size
)paren
op_logical_and
(paren
id|inode-&gt;i_blksize
)paren
)paren
(brace
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_minus
l_int|1
)paren
op_div
(paren
id|inode-&gt;i_blksize
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* TODO: times? I&squot;m not sure... */
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|DosDirNum
op_assign
id|nwinfo-&gt;i.DosDirNum
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
op_assign
id|nwinfo-&gt;i.dirEntNum
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
op_assign
id|nwinfo-&gt;i.volNumber
suffix:semicolon
)brace
multiline_comment|/*&n; * Fill in the inode based on the nw_file_info structure.&n; */
DECL|function|ncp_set_attr
r_static
r_void
id|ncp_set_attr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nw_file_info
op_star
id|nwinfo
)paren
(brace
r_struct
id|nw_info_struct
op_star
id|nwi
op_assign
op_amp
id|nwinfo-&gt;i
suffix:semicolon
r_struct
id|ncp_server
op_star
id|server
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nwi-&gt;attributes
op_amp
id|aDIR
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|server-&gt;m.dir_mode
suffix:semicolon
multiline_comment|/* for directories dataStreamSize seems to be some&n;&t;&t;   Object ID ??? */
id|inode-&gt;i_size
op_assign
l_int|512
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_mode
op_assign
id|server-&gt;m.file_mode
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|le32_to_cpu
c_func
(paren
id|nwi-&gt;dataStreamSize
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nwi-&gt;attributes
op_amp
id|aRONLY
)paren
id|inode-&gt;i_mode
op_and_assign
op_complement
l_int|0222
suffix:semicolon
id|DDPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_read_inode: inode-&gt;i_mode = %u&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|server-&gt;m.uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|server-&gt;m.gid
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|512
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;i_blksize
op_ne
l_int|0
)paren
op_logical_and
(paren
id|inode-&gt;i_size
op_ne
l_int|0
)paren
)paren
(brace
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_minus
l_int|1
)paren
op_div
id|inode-&gt;i_blksize
op_plus
l_int|1
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|ncp_date_dos2unix
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|nwi-&gt;modifyTime
)paren
comma
id|le16_to_cpu
c_func
(paren
id|nwi-&gt;modifyDate
)paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|ncp_date_dos2unix
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|nwi-&gt;creationTime
)paren
comma
id|le16_to_cpu
c_func
(paren
id|nwi-&gt;creationDate
)paren
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|ncp_date_dos2unix
c_func
(paren
l_int|0
comma
id|le16_to_cpu
c_func
(paren
id|nwi-&gt;lastAccessDate
)paren
)paren
suffix:semicolon
id|ncp_update_inode
c_func
(paren
id|inode
comma
id|nwinfo
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called from iget() with the read semaphore held. &n; * The global ncpfs_file_info structure has been set up by ncp_iget.&n; */
DECL|function|ncp_read_inode
r_static
r_void
id|ncp_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|read_nwinfo
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_inode: invalid call&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ncp_set_attr
c_func
(paren
id|inode
comma
id|read_nwinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ncp_file_inode_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ncp_dir_inode_operations
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Set up the ncpfs_inode_info pointer and get a new inode.&n; */
r_struct
id|inode
op_star
DECL|function|ncp_iget
id|ncp_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ncpfs_inode_info
op_star
id|info
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_iget: info is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|read_sem
)paren
suffix:semicolon
id|read_nwinfo
op_assign
op_amp
id|info-&gt;nw_info
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|info-&gt;ino
)paren
suffix:semicolon
id|read_nwinfo
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_iget: iget failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|ncp_put_inode
r_static
r_void
id|ncp_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_count
op_eq
l_int|1
)paren
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|ncp_delete_inode
id|ncp_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|DDPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_delete_inode: put directory %ld&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ncp_invalid_dir_cache
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opened
op_logical_and
id|ncp_make_closed
c_func
(paren
id|inode
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* We can&squot;t do anything but complain. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_delete_inode: could not close&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ncp_init_root
r_static
r_void
id|ncp_init_root
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|ncpfs_inode_info
op_star
id|info
)paren
(brace
r_struct
id|ncp_inode_info
op_star
id|root
op_assign
op_amp
(paren
id|server-&gt;root
)paren
suffix:semicolon
r_struct
id|nw_info_struct
op_star
id|i
op_assign
op_amp
(paren
id|root-&gt;finfo.i
)paren
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_init_root: i = %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|i
)paren
suffix:semicolon
id|i-&gt;attributes
op_assign
id|aDIR
suffix:semicolon
id|i-&gt;dataStreamSize
op_assign
l_int|1024
suffix:semicolon
id|i-&gt;dirEntNum
op_assign
l_int|0
suffix:semicolon
id|i-&gt;DosDirNum
op_assign
l_int|0
suffix:semicolon
id|i-&gt;volNumber
op_assign
id|NCP_NUMBER_OF_VOLUMES
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* illegal volnum */
id|ncp_date_unix2dos
c_func
(paren
l_int|0
comma
op_amp
(paren
id|i-&gt;creationTime
)paren
comma
op_amp
(paren
id|i-&gt;creationDate
)paren
)paren
suffix:semicolon
id|ncp_date_unix2dos
c_func
(paren
l_int|0
comma
op_amp
(paren
id|i-&gt;modifyTime
)paren
comma
op_amp
(paren
id|i-&gt;modifyDate
)paren
)paren
suffix:semicolon
id|ncp_date_unix2dos
c_func
(paren
l_int|0
comma
op_amp
(paren
id|dummy
)paren
comma
op_amp
(paren
id|i-&gt;lastAccessDate
)paren
)paren
suffix:semicolon
id|i-&gt;creationTime
op_assign
id|le16_to_cpu
c_func
(paren
id|i-&gt;creationTime
)paren
suffix:semicolon
id|i-&gt;creationDate
op_assign
id|le16_to_cpu
c_func
(paren
id|i-&gt;creationDate
)paren
suffix:semicolon
id|i-&gt;modifyTime
op_assign
id|le16_to_cpu
c_func
(paren
id|i-&gt;modifyTime
)paren
suffix:semicolon
id|i-&gt;modifyDate
op_assign
id|le16_to_cpu
c_func
(paren
id|i-&gt;modifyDate
)paren
suffix:semicolon
id|i-&gt;lastAccessDate
op_assign
id|le16_to_cpu
c_func
(paren
id|i-&gt;lastAccessDate
)paren
suffix:semicolon
id|i-&gt;nameLen
op_assign
l_int|0
suffix:semicolon
id|i-&gt;entryName
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|root-&gt;finfo.opened
op_assign
l_int|0
suffix:semicolon
id|info-&gt;ino
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* tradition */
id|info-&gt;nw_info
op_assign
id|root-&gt;finfo
suffix:semicolon
r_return
suffix:semicolon
)brace
r_struct
id|super_block
op_star
DECL|function|ncp_read_super
id|ncp_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|raw_data
comma
r_int
id|silent
)paren
(brace
r_struct
id|ncp_mount_data
op_star
id|data
op_assign
(paren
r_struct
id|ncp_mount_data
op_star
)paren
id|raw_data
suffix:semicolon
r_struct
id|ncp_server
op_star
id|server
suffix:semicolon
r_struct
id|file
op_star
id|ncp_filp
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
r_int
id|error
suffix:semicolon
macro_line|#ifdef CONFIG_NCPFS_PACKET_SIGNING
r_int
id|options
suffix:semicolon
macro_line|#endif
r_struct
id|ncpfs_inode_info
id|finfo
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
r_goto
id|out_no_data
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;version
op_ne
id|NCP_MOUNT_VERSION
)paren
r_goto
id|out_bad_mount
suffix:semicolon
id|ncp_filp
op_assign
id|fget
c_func
(paren
id|data-&gt;ncp_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ncp_filp
)paren
r_goto
id|out_bad_file
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISSOCK
c_func
(paren
id|ncp_filp-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
r_goto
id|out_bad_file2
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
multiline_comment|/* Eh...  Is this correct? */
id|sb-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|NCP_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|ncp_sops
suffix:semicolon
multiline_comment|/* We must malloc our own super-block info */
id|server
op_assign
(paren
r_struct
id|ncp_server
op_star
)paren
id|ncp_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ncp_server
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server
op_eq
l_int|NULL
)paren
r_goto
id|out_no_server
suffix:semicolon
id|NCP_SBP
c_func
(paren
id|sb
)paren
op_assign
id|server
suffix:semicolon
id|server-&gt;ncp_filp
op_assign
id|ncp_filp
suffix:semicolon
id|server-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|server-&gt;wait
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;packet
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;buffer_size
op_assign
l_int|0
suffix:semicolon
id|server-&gt;conn_status
op_assign
l_int|0
suffix:semicolon
id|server-&gt;root_dentry
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;root_setuped
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NCPFS_PACKET_SIGNING
id|server-&gt;sign_wanted
op_assign
l_int|0
suffix:semicolon
id|server-&gt;sign_active
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|server-&gt;auth.auth_type
op_assign
id|NCP_AUTH_NONE
suffix:semicolon
id|server-&gt;auth.object_name_len
op_assign
l_int|0
suffix:semicolon
id|server-&gt;auth.object_name
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;auth.object_type
op_assign
l_int|0
suffix:semicolon
id|server-&gt;priv.len
op_assign
l_int|0
suffix:semicolon
id|server-&gt;priv.data
op_assign
l_int|NULL
suffix:semicolon
id|server-&gt;m
op_assign
op_star
id|data
suffix:semicolon
multiline_comment|/* Althought anything producing this is buggy, it happens&n;&t;   now because of PATH_MAX changes.. */
r_if
c_cond
(paren
id|server-&gt;m.time_out
OL
l_int|10
)paren
(brace
id|server-&gt;m.time_out
op_assign
l_int|10
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;You need to recompile your ncpfs utils..&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|server-&gt;m.file_mode
op_assign
(paren
id|server-&gt;m.file_mode
op_amp
(paren
id|S_IRWXU
op_or
id|S_IRWXG
op_or
id|S_IRWXO
)paren
)paren
op_or
id|S_IFREG
suffix:semicolon
id|server-&gt;m.dir_mode
op_assign
(paren
id|server-&gt;m.dir_mode
op_amp
(paren
id|S_IRWXU
op_or
id|S_IRWXG
op_or
id|S_IRWXO
)paren
)paren
op_or
id|S_IFDIR
suffix:semicolon
id|server-&gt;packet_size
op_assign
id|NCP_PACKET_SIZE
suffix:semicolon
id|server-&gt;packet
op_assign
id|ncp_kmalloc
c_func
(paren
id|NCP_PACKET_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;packet
op_eq
l_int|NULL
)paren
r_goto
id|out_no_packet
suffix:semicolon
id|ncp_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|error
op_assign
id|ncp_connect
c_func
(paren
id|server
)paren
suffix:semicolon
id|ncp_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out_no_connect
suffix:semicolon
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_read_super: NCP_SBP(sb) = %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|NCP_SBP
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NCPFS_PACKET_SIGNING
r_if
c_cond
(paren
id|ncp_negotiate_size_and_options
c_func
(paren
id|server
comma
id|NCP_DEFAULT_BUFSIZE
comma
id|NCP_DEFAULT_OPTIONS
comma
op_amp
(paren
id|server-&gt;buffer_size
)paren
comma
op_amp
id|options
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|options
op_ne
id|NCP_DEFAULT_OPTIONS
)paren
(brace
r_if
c_cond
(paren
id|ncp_negotiate_size_and_options
c_func
(paren
id|server
comma
id|NCP_DEFAULT_BUFSIZE
comma
id|options
op_amp
l_int|2
comma
op_amp
(paren
id|server-&gt;buffer_size
)paren
comma
op_amp
id|options
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|out_no_bufsize
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|options
op_amp
l_int|2
)paren
id|server-&gt;sign_wanted
op_assign
l_int|1
suffix:semicolon
)brace
r_else
macro_line|#endif&t;/* CONFIG_NCPFS_PACKET_SIGNING */
r_if
c_cond
(paren
id|ncp_negotiate_buffersize
c_func
(paren
id|server
comma
id|NCP_DEFAULT_BUFSIZE
comma
op_amp
(paren
id|server-&gt;buffer_size
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|out_no_bufsize
suffix:semicolon
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncpfs: bufsize = %d&bslash;n&quot;
comma
id|server-&gt;buffer_size
)paren
suffix:semicolon
id|ncp_init_root
c_func
(paren
id|server
comma
op_amp
id|finfo
)paren
suffix:semicolon
id|server-&gt;name_space
(braket
id|finfo.nw_info.i.volNumber
)braket
op_assign
id|NW_NS_DOS
suffix:semicolon
id|root_inode
op_assign
id|ncp_iget
c_func
(paren
id|sb
comma
op_amp
id|finfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|out_no_root
suffix:semicolon
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_read_super: root vol=%d&bslash;n&quot;
comma
id|NCP_FINFO
c_func
(paren
id|root_inode
)paren
op_member_access_from_pointer
id|volNumber
)paren
suffix:semicolon
id|server-&gt;root_dentry
op_assign
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|out_no_root
suffix:semicolon
id|server-&gt;root_dentry-&gt;d_op
op_assign
op_amp
id|ncp_dentry_operations
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|out_no_root
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_goto
id|out_disconnect
suffix:semicolon
id|out_no_bufsize
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: could not get bufsize&bslash;n&quot;
)paren
suffix:semicolon
id|out_disconnect
suffix:colon
id|ncp_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|ncp_disconnect
c_func
(paren
id|server
)paren
suffix:semicolon
id|ncp_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
r_goto
id|out_free_packet
suffix:semicolon
id|out_no_connect
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: Failed connection, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
id|out_free_packet
suffix:colon
id|ncp_kfree_s
c_func
(paren
id|server-&gt;packet
comma
id|server-&gt;packet_size
)paren
suffix:semicolon
r_goto
id|out_free_server
suffix:semicolon
id|out_no_packet
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: could not alloc packet&bslash;n&quot;
)paren
suffix:semicolon
id|out_free_server
suffix:colon
id|ncp_kfree_s
c_func
(paren
id|NCP_SBP
c_func
(paren
id|sb
)paren
comma
r_sizeof
(paren
r_struct
id|ncp_server
)paren
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
id|out_no_server
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: could not alloc ncp_server&bslash;n&quot;
)paren
suffix:semicolon
id|out_unlock
suffix:colon
multiline_comment|/* 23/12/1998 Marcin Dalecki &lt;dalecki@cs.net.pl&gt;:&n;&t; * &n;&t; * The previously used put_filp(ncp_filp); was bogous, since&n;&t; * it doesn&squot;t proper unlocking.&n;&t; */
id|fput
c_func
(paren
id|ncp_filp
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_bad_file2
suffix:colon
id|fput
c_func
(paren
id|ncp_filp
)paren
suffix:semicolon
id|out_bad_file
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: invalid ncp socket&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_bad_mount
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ncp_read_super: kernel requires mount version %d&bslash;n&quot;
comma
id|NCP_MOUNT_VERSION
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_no_data
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ncp_read_super: missing data argument&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ncp_put_super
r_static
r_void
id|ncp_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|ncp_server
op_star
id|server
op_assign
id|NCP_SBP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|ncp_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|ncp_disconnect
c_func
(paren
id|server
)paren
suffix:semicolon
id|ncp_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|fput
c_func
(paren
id|server-&gt;ncp_filp
)paren
suffix:semicolon
id|kill_proc
c_func
(paren
id|server-&gt;m.wdog_pid
comma
id|SIGTERM
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;priv.data
)paren
id|ncp_kfree_s
c_func
(paren
id|server-&gt;priv.data
comma
id|server-&gt;priv.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;auth.object_name
)paren
id|ncp_kfree_s
c_func
(paren
id|server-&gt;auth.object_name
comma
id|server-&gt;auth.object_name_len
)paren
suffix:semicolon
id|ncp_kfree_s
c_func
(paren
id|server-&gt;packet
comma
id|server-&gt;packet_size
)paren
suffix:semicolon
id|ncp_kfree_s
c_func
(paren
id|NCP_SBP
c_func
(paren
id|sb
)paren
comma
r_sizeof
(paren
r_struct
id|ncp_server
)paren
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|ncp_statfs
r_static
r_int
id|ncp_statfs
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
comma
r_int
id|bufsiz
)paren
(brace
r_struct
id|statfs
id|tmp
suffix:semicolon
multiline_comment|/* We cannot say how much disk space is left on a mounted&n;&t;   NetWare Server, because free space is distributed over&n;&t;   volumes, and the current user might have disk quotas. So&n;&t;   free space is not that simple to determine. Our decision&n;&t;   here is to err conservatively. */
id|tmp.f_type
op_assign
id|NCP_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
l_int|512
suffix:semicolon
id|tmp.f_blocks
op_assign
l_int|0
suffix:semicolon
id|tmp.f_bfree
op_assign
l_int|0
suffix:semicolon
id|tmp.f_bavail
op_assign
l_int|0
suffix:semicolon
id|tmp.f_files
op_assign
op_minus
l_int|1
suffix:semicolon
id|tmp.f_ffree
op_assign
op_minus
l_int|1
suffix:semicolon
id|tmp.f_namelen
op_assign
l_int|12
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsiz
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ncp_notify_change
r_int
id|ncp_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|info_mask
suffix:semicolon
r_struct
id|nw_modify_dos_info
id|info
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|result
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|result
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|attr-&gt;ia_uid
op_ne
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|m.uid
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
id|attr-&gt;ia_uid
op_ne
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|m.gid
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
op_logical_and
(paren
id|attr-&gt;ia_mode
op_amp
op_complement
(paren
id|S_IFREG
op_or
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRWXG
op_or
id|S_IRWXO
)paren
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|info_mask
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
macro_line|#if 1 
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_else
(brace
id|umode_t
id|newmode
suffix:semicolon
id|info_mask
op_or_assign
id|DM_ATTRIBUTES
suffix:semicolon
id|newmode
op_assign
id|attr-&gt;ia_mode
suffix:semicolon
id|newmode
op_and_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|m.file_mode
suffix:semicolon
r_if
c_cond
(paren
id|newmode
op_amp
l_int|0222
)paren
multiline_comment|/* any write bit set */
(brace
id|info.attributes
op_and_assign
op_complement
l_int|0x60001
suffix:semicolon
)brace
r_else
(brace
id|info.attributes
op_or_assign
l_int|0x60001
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_CTIME
)paren
op_ne
l_int|0
)paren
(brace
id|info_mask
op_or_assign
(paren
id|DM_CREATE_TIME
op_or
id|DM_CREATE_DATE
)paren
suffix:semicolon
id|ncp_date_unix2dos
c_func
(paren
id|attr-&gt;ia_ctime
comma
op_amp
(paren
id|info.creationTime
)paren
comma
op_amp
(paren
id|info.creationDate
)paren
)paren
suffix:semicolon
id|info.creationTime
op_assign
id|le16_to_cpu
c_func
(paren
id|info.creationTime
)paren
suffix:semicolon
id|info.creationDate
op_assign
id|le16_to_cpu
c_func
(paren
id|info.creationDate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
op_ne
l_int|0
)paren
(brace
id|info_mask
op_or_assign
(paren
id|DM_MODIFY_TIME
op_or
id|DM_MODIFY_DATE
)paren
suffix:semicolon
id|ncp_date_unix2dos
c_func
(paren
id|attr-&gt;ia_mtime
comma
op_amp
(paren
id|info.modifyTime
)paren
comma
op_amp
(paren
id|info.modifyDate
)paren
)paren
suffix:semicolon
id|info.modifyTime
op_assign
id|le16_to_cpu
c_func
(paren
id|info.modifyTime
)paren
suffix:semicolon
id|info.modifyDate
op_assign
id|le16_to_cpu
c_func
(paren
id|info.modifyDate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME
)paren
op_ne
l_int|0
)paren
(brace
id|__u16
id|dummy
suffix:semicolon
id|info_mask
op_or_assign
(paren
id|DM_LAST_ACCESS_DATE
)paren
suffix:semicolon
id|ncp_date_unix2dos
c_func
(paren
id|attr-&gt;ia_ctime
comma
op_amp
(paren
id|dummy
)paren
comma
op_amp
(paren
id|info.lastAccessDate
)paren
)paren
suffix:semicolon
id|info.lastAccessDate
op_assign
id|le16_to_cpu
c_func
(paren
id|info.lastAccessDate
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info_mask
op_ne
l_int|0
)paren
(brace
id|result
op_assign
id|ncp_modify_file_or_subdir_dos_info
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
comma
id|info_mask
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|result
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|info_mask
op_eq
(paren
id|DM_CREATE_TIME
op_or
id|DM_CREATE_DATE
)paren
)paren
(brace
multiline_comment|/* NetWare seems not to allow this. I&n;&t;&t;&t;&t;   do not know why. So, just tell the&n;&t;&t;&t;&t;   user everything went fine. This is&n;&t;&t;&t;&t;   a terrible hack, but I do not know&n;&t;&t;&t;&t;   how to do this correctly. */
id|result
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|written
suffix:semicolon
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncpfs: trying to change size to %ld&bslash;n&quot;
comma
id|attr-&gt;ia_size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDWR
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|ncp_write
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|attr-&gt;ia_size
comma
l_int|0
comma
l_string|&quot;&quot;
comma
op_amp
id|written
)paren
suffix:semicolon
multiline_comment|/* According to ndir, the changes only take effect after&n;&t;&t;   closing the file */
id|result
op_assign
id|ncp_make_closed
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|ncp_invalid_dir_cache
c_func
(paren
id|dentry-&gt;d_parent-&gt;d_inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_NCP_MALLOC
DECL|variable|ncp_malloced
r_int
id|ncp_malloced
suffix:semicolon
DECL|variable|ncp_current_malloced
r_int
id|ncp_current_malloced
suffix:semicolon
macro_line|#endif
DECL|variable|ncp_fs_type
r_static
r_struct
id|file_system_type
id|ncp_fs_type
op_assign
(brace
l_string|&quot;ncpfs&quot;
comma
l_int|0
multiline_comment|/* FS_NO_DCACHE doesn&squot;t work correctly */
comma
id|ncp_read_super
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_ncp_fs
c_func
(paren
r_void
)paren
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|ncp_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncpfs: init_module called&bslash;n&quot;
)paren
suffix:semicolon
id|read_sem
op_assign
id|MUTEX
suffix:semicolon
id|read_nwinfo
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef DEBUG_NCP_MALLOC
id|ncp_malloced
op_assign
l_int|0
suffix:semicolon
id|ncp_current_malloced
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|ncp_init_dir_cache
c_func
(paren
)paren
suffix:semicolon
r_return
id|init_ncp_fs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|DPRINTK
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncpfs: cleanup_module called&bslash;n&quot;
)paren
suffix:semicolon
id|ncp_free_dir_cache
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|ncp_fs_type
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_NCP_MALLOC
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_malloced: %d&bslash;n&quot;
comma
id|ncp_malloced
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ncp_current_malloced: %d&bslash;n&quot;
comma
id|ncp_current_malloced
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof
