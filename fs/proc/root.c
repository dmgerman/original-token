multiline_comment|/*&n; *  linux/fs/proc/root.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  proc root directory handling functions&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ZORRO
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#endif
r_static
r_int
id|proc_root_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|proc_root_lookup
c_func
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
r_static
r_int
id|proc_unlink
c_func
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
DECL|variable|proc_alloc_map
r_static
r_int
r_char
id|proc_alloc_map
(braket
id|PROC_NDYNAMIC
op_div
l_int|8
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * These are the generic /proc directory operations. They&n; * use the in-memory &quot;struct proc_dir_entry&quot; tree to parse&n; * the /proc directory.&n; */
DECL|variable|proc_dir_operations
r_static
r_struct
id|file_operations
id|proc_dir_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|proc_readdir
comma
multiline_comment|/* readdir */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_dir_inode_operations
r_struct
id|inode_operations
id|proc_dir_inode_operations
op_assign
(brace
op_amp
id|proc_dir_operations
comma
multiline_comment|/* default net directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookup
comma
multiline_comment|/* lookup */
)brace
suffix:semicolon
multiline_comment|/*&n; * /proc dynamic directories now support unlinking&n; */
DECL|variable|proc_dyna_dir_inode_operations
r_struct
id|inode_operations
id|proc_dyna_dir_inode_operations
op_assign
(brace
op_amp
id|proc_dir_operations
comma
multiline_comment|/* default proc dir ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookup
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link&t;*/
id|proc_unlink
comma
multiline_comment|/* unlink(struct inode *, struct dentry *) */
)brace
suffix:semicolon
multiline_comment|/*&n; * The root /proc directory is special, as it has the&n; * &lt;pid&gt; directories. Thus we don&squot;t use the generic&n; * directory handling functions for that..&n; */
DECL|variable|proc_root_operations
r_static
r_struct
id|file_operations
id|proc_root_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|proc_root_readdir
comma
multiline_comment|/* readdir */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc root can do almost nothing..&n; */
DECL|variable|proc_root_inode_operations
r_static
r_struct
id|inode_operations
id|proc_root_inode_operations
op_assign
(brace
op_amp
id|proc_root_operations
comma
multiline_comment|/* default base directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_root_lookup
comma
multiline_comment|/* lookup */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the root &quot;inode&quot; in the /proc tree..&n; */
DECL|variable|proc_root
r_struct
id|proc_dir_entry
id|proc_root
op_assign
(brace
id|PROC_ROOT_INO
comma
l_int|5
comma
l_string|&quot;/proc&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_root_inode_operations
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|proc_root
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|proc_net
DECL|variable|proc_bus
DECL|variable|proc_root_fs
DECL|variable|proc_root_driver
r_struct
id|proc_dir_entry
op_star
id|proc_net
comma
op_star
id|proc_bus
comma
op_star
id|proc_root_fs
comma
op_star
id|proc_root_driver
suffix:semicolon
macro_line|#ifdef CONFIG_MCA
DECL|variable|proc_mca
r_struct
id|proc_dir_entry
op_star
id|proc_mca
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|proc_sys_root
r_struct
id|proc_dir_entry
op_star
id|proc_sys_root
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SUN_OPENPROMFS) || defined(CONFIG_SUN_OPENPROMFS_MODULE)
DECL|variable|proc_openprom_defreaddir_ptr
r_static
r_int
(paren
op_star
id|proc_openprom_defreaddir_ptr
)paren
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
DECL|variable|proc_openprom_deflookup_ptr
r_static
r_struct
id|dentry
op_star
(paren
op_star
id|proc_openprom_deflookup_ptr
)paren
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
DECL|variable|proc_openprom_use
r_void
(paren
op_star
id|proc_openprom_use
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
op_assign
l_int|0
suffix:semicolon
DECL|variable|proc_openprom_devices
r_static
r_struct
id|openpromfs_dev
op_star
id|proc_openprom_devices
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|proc_openpromdev_ino
r_static
id|ino_t
id|proc_openpromdev_ino
op_assign
id|PROC_OPENPROMD_FIRST
suffix:semicolon
r_struct
id|inode_operations
op_star
DECL|function|proc_openprom_register
id|proc_openprom_register
c_func
(paren
r_int
(paren
op_star
id|readdir
)paren
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
comma
r_struct
id|dentry
op_star
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
comma
r_void
(paren
op_star
id|use
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
comma
r_struct
id|openpromfs_dev
op_star
op_star
op_star
id|devices
)paren
(brace
id|proc_openprom_defreaddir_ptr
op_assign
(paren
id|proc_openprom_inode_operations.default_file_ops
)paren
op_member_access_from_pointer
id|readdir
suffix:semicolon
id|proc_openprom_deflookup_ptr
op_assign
id|proc_openprom_inode_operations.lookup
suffix:semicolon
(paren
id|proc_openprom_inode_operations.default_file_ops
)paren
op_member_access_from_pointer
id|readdir
op_assign
id|readdir
suffix:semicolon
id|proc_openprom_inode_operations.lookup
op_assign
id|lookup
suffix:semicolon
id|proc_openprom_use
op_assign
id|use
suffix:semicolon
op_star
id|devices
op_assign
op_amp
id|proc_openprom_devices
suffix:semicolon
r_return
op_amp
id|proc_openprom_inode_operations
suffix:semicolon
)brace
DECL|function|proc_openprom_regdev
r_int
id|proc_openprom_regdev
c_func
(paren
r_struct
id|openpromfs_dev
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|proc_openpromdev_ino
op_eq
id|PROC_OPENPROMD_FIRST
op_plus
id|PROC_NOPENPROMD
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|d-&gt;next
op_assign
id|proc_openprom_devices
suffix:semicolon
id|d-&gt;inode
op_assign
id|proc_openpromdev_ino
op_increment
suffix:semicolon
id|proc_openprom_devices
op_assign
id|d
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_openprom_unregdev
r_int
id|proc_openprom_unregdev
c_func
(paren
r_struct
id|openpromfs_dev
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|d
op_eq
id|proc_openprom_devices
)paren
(brace
id|proc_openprom_devices
op_assign
id|d-&gt;next
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|proc_openprom_devices
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
(brace
r_struct
id|openpromfs_dev
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|proc_openprom_devices
suffix:semicolon
id|p-&gt;next
op_ne
id|d
op_logical_and
id|p-&gt;next
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;next
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p-&gt;next
op_assign
id|d-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SUN_OPENPROMFS_MODULE
r_void
DECL|function|proc_openprom_deregister
id|proc_openprom_deregister
c_func
(paren
r_void
)paren
(brace
(paren
id|proc_openprom_inode_operations.default_file_ops
)paren
op_member_access_from_pointer
id|readdir
op_assign
id|proc_openprom_defreaddir_ptr
suffix:semicolon
id|proc_openprom_inode_operations.lookup
op_assign
id|proc_openprom_deflookup_ptr
suffix:semicolon
id|proc_openprom_use
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_SUN_OPENPROMFS_MODULE) &amp;&amp; defined(CONFIG_KMOD)
r_static
r_int
DECL|function|proc_openprom_defreaddir
id|proc_openprom_defreaddir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;openpromfs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|proc_openprom_inode_operations.default_file_ops
)paren
op_member_access_from_pointer
id|readdir
op_ne
id|proc_openprom_defreaddir
)paren
r_return
(paren
id|proc_openprom_inode_operations.default_file_ops
)paren
op_member_access_from_pointer
id|readdir
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|macro|OPENPROM_DEFREADDIR
mdefine_line|#define OPENPROM_DEFREADDIR proc_openprom_defreaddir
r_static
r_struct
id|dentry
op_star
DECL|function|proc_openprom_deflookup
id|proc_openprom_deflookup
c_func
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
(brace
id|request_module
c_func
(paren
l_string|&quot;openpromfs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_openprom_inode_operations.lookup
op_ne
id|proc_openprom_deflookup
)paren
r_return
id|proc_openprom_inode_operations.lookup
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
)brace
DECL|macro|OPENPROM_DEFLOOKUP
mdefine_line|#define OPENPROM_DEFLOOKUP proc_openprom_deflookup
macro_line|#else
DECL|macro|OPENPROM_DEFREADDIR
mdefine_line|#define OPENPROM_DEFREADDIR NULL
DECL|macro|OPENPROM_DEFLOOKUP
mdefine_line|#define OPENPROM_DEFLOOKUP NULL
macro_line|#endif
DECL|variable|proc_openprom_operations
r_static
r_struct
id|file_operations
id|proc_openprom_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
l_int|NULL
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
id|OPENPROM_DEFREADDIR
comma
multiline_comment|/* readdir */
)brace
suffix:semicolon
DECL|variable|proc_openprom_inode_operations
r_struct
id|inode_operations
id|proc_openprom_inode_operations
op_assign
(brace
op_amp
id|proc_openprom_operations
comma
multiline_comment|/* default net directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|OPENPROM_DEFLOOKUP
comma
multiline_comment|/* lookup */
)brace
suffix:semicolon
DECL|variable|proc_openprom
r_struct
id|proc_dir_entry
id|proc_openprom
op_assign
(brace
id|PROC_OPENPROM
comma
l_int|8
comma
l_string|&quot;openprom&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_openprom_inode_operations
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|proc_root
comma
l_int|NULL
)brace
suffix:semicolon
r_extern
r_void
id|openpromfs_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SUN_OPENPROMFS */
DECL|function|make_inode_number
r_static
r_int
id|make_inode_number
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
id|find_first_zero_bit
c_func
(paren
(paren
r_void
op_star
)paren
id|proc_alloc_map
comma
id|PROC_NDYNAMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
id|i
op_ge
id|PROC_NDYNAMIC
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|set_bit
c_func
(paren
id|i
comma
(paren
r_void
op_star
)paren
id|proc_alloc_map
)paren
suffix:semicolon
r_return
id|PROC_DYNAMIC_FIRST
op_plus
id|i
suffix:semicolon
)brace
DECL|function|proc_readlink
r_int
id|proc_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;readlink_proc
)paren
id|len
op_assign
id|de
op_member_access_from_pointer
id|readlink_proc
c_func
(paren
id|de
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|buflen
)paren
id|len
op_assign
id|buflen
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buffer
comma
id|page
comma
id|len
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_follow_link
r_struct
id|dentry
op_star
id|proc_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|base
comma
r_int
r_int
id|follow
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_struct
id|dentry
op_star
id|d
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;readlink_proc
)paren
id|len
op_assign
id|de
op_member_access_from_pointer
id|readlink_proc
c_func
(paren
id|de
comma
id|page
)paren
suffix:semicolon
id|d
op_assign
id|lookup_dentry
c_func
(paren
id|page
comma
id|base
comma
id|follow
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|d
suffix:semicolon
)brace
DECL|variable|proc_link_inode_operations
r_static
r_struct
id|inode_operations
id|proc_link_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-ops */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|proc_readlink
comma
multiline_comment|/* readlink */
id|proc_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* get_block */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|function|proc_register
r_int
id|proc_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
r_struct
id|proc_dir_entry
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;low_ino
op_eq
l_int|0
)paren
(brace
id|i
op_assign
id|make_inode_number
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|dp-&gt;low_ino
op_assign
id|i
suffix:semicolon
)brace
id|dp-&gt;next
op_assign
id|dir-&gt;subdir
suffix:semicolon
id|dp-&gt;parent
op_assign
id|dir
suffix:semicolon
id|dir-&gt;subdir
op_assign
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dp-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;ops
op_eq
l_int|NULL
)paren
id|dp-&gt;ops
op_assign
op_amp
id|proc_dir_inode_operations
suffix:semicolon
id|dir-&gt;nlink
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|dp-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;ops
op_eq
l_int|NULL
)paren
id|dp-&gt;ops
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dp-&gt;ops
op_eq
l_int|NULL
)paren
id|dp-&gt;ops
op_assign
op_amp
id|proc_file_inode_operations
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Kill an inode that got unregistered..&n; */
DECL|function|proc_kill_inodes
r_static
r_void
id|proc_kill_inodes
c_func
(paren
r_int
id|ino
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/*&n;&t; * Actually it&squot;s a partial revoke(). We have to go through all&n;&t; * copies of procfs. proc_super_blocks is protected by the big&n;&t; * lock for the time being.&n;&t; */
r_for
c_loop
(paren
id|sb
op_assign
id|proc_super_blocks
suffix:semicolon
id|sb
suffix:semicolon
id|sb
op_assign
(paren
r_struct
id|super_block
op_star
)paren
id|sb-&gt;u.generic_sbp
)paren
(brace
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|sb-&gt;s_files.next
suffix:semicolon
id|p
op_ne
op_amp
id|sb-&gt;s_files
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|file
op_star
id|filp
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|file
comma
id|f_list
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_op
op_ne
op_amp
id|proc_dentry_operations
)paren
r_continue
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_ne
id|ino
)paren
r_continue
suffix:semicolon
id|filp-&gt;f_op
op_assign
l_int|NULL
suffix:semicolon
)brace
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|proc_unregister
r_int
id|proc_unregister
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
r_int
id|ino
)paren
(brace
r_struct
id|proc_dir_entry
op_star
op_star
id|p
op_assign
op_amp
id|dir-&gt;subdir
comma
op_star
id|dp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dp
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;low_ino
op_eq
id|ino
)paren
(brace
op_star
id|p
op_assign
id|dp-&gt;next
suffix:semicolon
id|dp-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dp-&gt;mode
)paren
)paren
id|dir-&gt;nlink
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
id|PROC_DYNAMIC_FIRST
op_logical_and
id|ino
OL
id|PROC_DYNAMIC_FIRST
op_plus
id|PROC_NDYNAMIC
)paren
id|clear_bit
c_func
(paren
id|ino
op_minus
id|PROC_DYNAMIC_FIRST
comma
(paren
r_void
op_star
)paren
id|proc_alloc_map
)paren
suffix:semicolon
id|proc_kill_inodes
c_func
(paren
id|ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|dp-&gt;next
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * /proc/self:&n; */
DECL|function|proc_self_readlink
r_static
r_int
id|proc_self_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
id|tmp
(braket
l_int|30
)braket
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;%d&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OL
id|len
)paren
id|len
op_assign
id|buflen
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buffer
comma
id|tmp
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_self_follow_link
r_static
r_struct
id|dentry
op_star
id|proc_self_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|base
comma
r_int
r_int
id|follow
)paren
(brace
r_char
id|tmp
(braket
l_int|30
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;%d&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_return
id|lookup_dentry
c_func
(paren
id|tmp
comma
id|base
comma
id|follow
)paren
suffix:semicolon
)brace
DECL|variable|proc_self_inode_operations
r_static
r_struct
id|inode_operations
id|proc_self_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-ops */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|proc_self_readlink
comma
multiline_comment|/* readlink */
id|proc_self_follow_link
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* get_block */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|proc_root_self
r_static
r_struct
id|proc_dir_entry
id|proc_root_self
op_assign
(brace
l_int|0
comma
l_int|4
comma
l_string|&quot;self&quot;
comma
id|S_IFLNK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IXUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|64
comma
op_amp
id|proc_self_inode_operations
comma
)brace
suffix:semicolon
macro_line|#ifdef __powerpc__
DECL|variable|proc_root_ppc_htab
r_static
r_struct
id|proc_dir_entry
id|proc_root_ppc_htab
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_string|&quot;ppc_htab&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
op_or
id|S_IROTH
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_ppc_htab_inode_operations
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* get_info, fill_inode */
l_int|NULL
comma
multiline_comment|/* next */
l_int|NULL
comma
l_int|NULL
multiline_comment|/* parent, subdir */
)brace
suffix:semicolon
macro_line|#endif
DECL|function|proc_root_init
r_void
id|__init
id|proc_root_init
c_func
(paren
r_void
)paren
(brace
id|proc_misc_init
c_func
(paren
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_root_self
)paren
suffix:semicolon
id|proc_net
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;net&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSVIPC
id|create_proc_entry
c_func
(paren
l_string|&quot;sysvipc&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
id|proc_sys_root
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;sys&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
id|proc_mca
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;mca&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|proc_root_fs
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;fs&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
id|proc_root_driver
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;driver&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SUN_OPENPROMFS) || defined(CONFIG_SUN_OPENPROMFS_MODULE)
macro_line|#ifdef CONFIG_SUN_OPENPROMFS
id|openpromfs_init
(paren
)paren
suffix:semicolon
macro_line|#endif
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_openprom
)paren
suffix:semicolon
macro_line|#endif
id|proc_tty_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef __powerpc__
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_root_ppc_htab
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_DEVICETREE
id|proc_device_tree_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|proc_bus
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;bus&quot;
comma
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * As some entries in /proc are volatile, we want to &n; * get rid of unused dentries.  This could be made &n; * smarter: we could keep a &quot;volatile&quot; flag in the &n; * inode to indicate which ones to keep.&n; */
r_static
r_void
DECL|function|proc_delete_dentry
id|proc_delete_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|d_drop
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
DECL|variable|proc_dentry_operations
r_struct
id|dentry_operations
id|proc_dentry_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* revalidate */
l_int|NULL
comma
multiline_comment|/* d_hash */
l_int|NULL
comma
multiline_comment|/* d_compare */
id|proc_delete_dentry
multiline_comment|/* d_delete(struct dentry *) */
)brace
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t create negative dentries here, return -ENOENT by hand&n; * instead.&n; */
DECL|function|proc_lookup
r_struct
id|dentry
op_star
id|proc_lookup
c_func
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
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|dir-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
r_for
c_loop
(paren
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|de
suffix:semicolon
id|de
op_assign
id|de-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de
op_logical_or
op_logical_neg
id|de-&gt;low_ino
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;namelen
op_ne
id|dentry-&gt;d_name.len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|de-&gt;name
comma
id|de-&gt;namelen
)paren
)paren
(brace
r_int
id|ino
op_assign
id|de-&gt;low_ino
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|inode
op_assign
id|proc_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
comma
id|de
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|inode
)paren
(brace
id|dentry-&gt;d_op
op_assign
op_amp
id|proc_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
DECL|function|proc_root_lookup
r_static
r_struct
id|dentry
op_star
id|proc_root_lookup
c_func
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
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|PROC_ROOT_INO
)paren
(brace
multiline_comment|/* check for safety... */
r_extern
r_int
r_int
id|total_forks
suffix:semicolon
r_static
r_int
id|last_timestamp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * this one can be a serious &squot;ps&squot; performance problem if&n;&t;&t; * there are many threads running - thus we do &squot;lazy&squot;&n;&t;&t; * link-recalculation - we change it only if the number&n;&t;&t; * of threads has increased.&n;&t;&t; */
r_if
c_cond
(paren
id|total_forks
op_ne
id|last_timestamp
)paren
(brace
r_int
id|nlink
op_assign
id|proc_root.nlink
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|last_timestamp
op_assign
id|total_forks
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
id|nlink
op_increment
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * subtract the # of idle threads which&n;&t;&t;&t; * do not show up in /proc:&n;&t;&t;&t; */
id|dir-&gt;i_nlink
op_assign
id|nlink
op_minus
id|smp_num_cpus
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|proc_lookup
c_func
(paren
id|dir
comma
id|dentry
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|proc_pid_lookup
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This returns non-zero if at EOF, so that the /proc&n; * root directory can use this and check if it should&n; * continue with the &lt;pid&gt; entries..&n; *&n; * Note that the VFS-layer doesn&squot;t care about the return&n; * value of the readdir() call, as long as it&squot;s non-negative&n; * for success..&n; */
DECL|function|proc_readdir
r_int
id|proc_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|i
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|i
comma
id|ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|i
comma
id|de-&gt;parent-&gt;low_ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|i
op_sub_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_break
suffix:semicolon
id|de
op_assign
id|de-&gt;next
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|de-&gt;namelen
comma
id|filp-&gt;f_pos
comma
id|de-&gt;low_ino
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|de
op_assign
id|de-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|de
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|proc_root_readdir
r_static
r_int
id|proc_root_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
r_int
id|nr
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
id|FIRST_PROCESS_ENTRY
)paren
(brace
r_int
id|error
op_assign
id|proc_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_le
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|FIRST_PROCESS_ENTRY
suffix:semicolon
)brace
r_return
id|proc_pid_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
)paren
suffix:semicolon
)brace
DECL|function|proc_unlink
r_static
r_int
id|proc_unlink
c_func
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
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|dir-&gt;u.generic_ip
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;proc_file_unlink: deleting %s/%s&bslash;n&quot;
comma
id|dp-&gt;name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|dp
)paren
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|d_delete
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
