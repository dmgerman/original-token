multiline_comment|/*&n; *  linux/fs/umsdos/inode.c&n; *&n; *      Written 1993 by Jacques Gelinas&n; *      Inspired from linux/fs/msdos/... by Werner Almesberger&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
r_extern
r_struct
id|dentry_operations
id|umsdos_dentry_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|umsdos_rdir_inode_operations
suffix:semicolon
DECL|variable|saved_root
r_struct
id|dentry
op_star
id|saved_root
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Original root if changed */
DECL|variable|pseudo_root
r_struct
id|inode
op_star
id|pseudo_root
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Useful to simulate the pseudo DOS */
multiline_comment|/* directory. See UMSDOS_readdir_x() */
r_static
r_struct
id|dentry
op_star
id|check_pseudo_root
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize a private filp&n; */
DECL|function|fill_new_filp
r_void
id|fill_new_filp
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fill_new_filp: NULL dentry!&bslash;n&quot;
)paren
suffix:semicolon
id|memset
(paren
id|filp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|file
)paren
)paren
suffix:semicolon
id|filp-&gt;f_reada
op_assign
l_int|1
suffix:semicolon
id|filp-&gt;f_flags
op_assign
id|O_RDWR
suffix:semicolon
id|filp-&gt;f_dentry
op_assign
id|dentry
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|dentry-&gt;d_inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
)brace
DECL|function|UMSDOS_put_inode
r_void
id|UMSDOS_put_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|PRINTK
(paren
(paren
id|KERN_DEBUG
l_string|&quot;put inode %p (%lu) pos %lu count=%d&bslash;n&quot;
comma
id|inode
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;u.umsdos_i.pos
comma
id|inode-&gt;i_count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
id|pseudo_root
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Umsdos: Oops releasing pseudo_root.&quot;
l_string|&quot; Notify jacques@solucorp.qc.ca&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_count
op_eq
l_int|1
)paren
id|inode-&gt;u.umsdos_i.i_patched
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|UMSDOS_put_super
r_void
id|UMSDOS_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;UMSDOS_put_super: entering&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_root
)paren
(brace
id|shrink_dcache_parent
c_func
(paren
id|saved_root
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;UMSDOS_put_super: freeing saved root, d_count=%d&bslash;n&quot;
comma
id|saved_root-&gt;d_count
)paren
suffix:semicolon
id|dput
c_func
(paren
id|saved_root
)paren
suffix:semicolon
id|saved_root
op_assign
l_int|NULL
suffix:semicolon
id|pseudo_root
op_assign
l_int|NULL
suffix:semicolon
)brace
id|msdos_put_super
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Complete the setup of a directory dentry based on its&n; * EMD/non-EMD status.  If it has an EMD, then plug the&n; * umsdos function table. If not, use the msdos one.&n; */
DECL|function|umsdos_setup_dir
r_void
id|umsdos_setup_dir
c_func
(paren
r_struct
id|dentry
op_star
id|dir
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dir-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;umsdos_setup_dir: %s/%s not a dir!&bslash;n&quot;
comma
id|dir-&gt;d_parent-&gt;d_name.name
comma
id|dir-&gt;d_name.name
)paren
suffix:semicolon
id|init_waitqueue_head
(paren
op_amp
id|inode-&gt;u.umsdos_i.dir_info.p
)paren
suffix:semicolon
id|inode-&gt;u.umsdos_i.dir_info.looking
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.umsdos_i.dir_info.creating
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;u.umsdos_i.dir_info.pid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_rdir_inode_operations
suffix:semicolon
r_if
c_cond
(paren
id|umsdos_have_emd
c_func
(paren
id|dir
)paren
)paren
(brace
id|Printk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;umsdos_setup_dir: %s/%s using EMD&bslash;n&quot;
comma
id|dir-&gt;d_parent-&gt;d_name.name
comma
id|dir-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_dir_inode_operations
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Add some info into an inode so it can find its owner quickly&n; */
DECL|function|umsdos_set_dirinfo_new
r_void
id|umsdos_set_dirinfo_new
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|off_t
id|f_pos
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
id|dentry
op_star
id|demd
suffix:semicolon
id|inode-&gt;u.umsdos_i.pos
op_assign
id|f_pos
suffix:semicolon
multiline_comment|/* now check the EMD file */
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|demd
)paren
)paren
(brace
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Connect the proper tables in the inode and add some info.&n; */
multiline_comment|/* #Specification: inode / umsdos info&n; * The first time an inode is seen (inode-&gt;i_count == 1),&n; * the inode number of the EMD file which controls this inode&n; * is tagged to this inode. It allows operations such as&n; * notify_change to be handled.&n; */
DECL|function|umsdos_patch_dentry_inode
r_void
id|umsdos_patch_dentry_inode
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|off_t
id|f_pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;umsdos_patch_dentry_inode: inode=%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Classify the inode based on EMD/non-EMD status.&n;&t; */
id|PRINTK
(paren
(paren
l_string|&quot;umsdos_patch_inode: call umsdos_set_dirinfo_new(%p,%lu)&bslash;n&quot;
comma
id|dentry
comma
id|f_pos
)paren
)paren
suffix:semicolon
id|umsdos_set_dirinfo_new
c_func
(paren
id|dentry
comma
id|f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* All set */
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|umsdos_setup_dir
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* address_space operations already set */
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
)brace
r_else
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
)brace
r_int
id|umsdos_notify_change_locked
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * lock the parent dir before starting ...&n; */
DECL|function|UMSDOS_notify_change
r_int
id|UMSDOS_notify_change
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
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|inode_change_ok
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
id|ret
op_assign
id|umsdos_notify_change_locked
c_func
(paren
id|dentry
comma
id|attr
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|inode_setattr
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Must be called with the parent lock held.&n; */
DECL|function|umsdos_notify_change_locked
r_int
id|umsdos_notify_change_locked
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
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
r_struct
id|umsdos_dirent
id|entry
suffix:semicolon
id|Printk
c_func
(paren
(paren
l_string|&quot;UMSDOS_notify_change: entering for %s/%s (%d)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|inode-&gt;u.umsdos_i.i_patched
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|UMSDOS_ROOT_INO
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* get the EMD file dentry */
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|demd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|demd
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|demd-&gt;d_inode
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;UMSDOS_notify_change: no EMD file %s/%s&bslash;n&quot;
comma
id|demd-&gt;d_parent-&gt;d_name.name
comma
id|demd-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out_dput
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t do anything if this is the EMD itself */
r_if
c_cond
(paren
id|inode
op_eq
id|demd-&gt;d_inode
)paren
r_goto
id|out_dput
suffix:semicolon
multiline_comment|/* This inode is not a EMD file nor an inode used internally&n;&t; * by MSDOS, so we can update its status.&n;&t; * See emd.c&n;&t; */
id|fill_new_filp
(paren
op_amp
id|filp
comma
id|demd
)paren
suffix:semicolon
id|filp.f_pos
op_assign
id|inode-&gt;u.umsdos_i.pos
suffix:semicolon
id|Printk
c_func
(paren
(paren
l_string|&quot;UMSDOS_notify_change: %s/%s reading at %d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
)paren
id|filp.f_pos
)paren
)paren
suffix:semicolon
multiline_comment|/* Read only the start of the entry since we don&squot;t touch the name */
id|ret
op_assign
id|umsdos_emd_dir_read
(paren
op_amp
id|filp
comma
(paren
r_char
op_star
)paren
op_amp
id|entry
comma
id|UMSDOS_REC_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;umsdos_notify_change: %s/%s EMD read error, ret=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_dput
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
id|entry.uid
op_assign
id|attr-&gt;ia_uid
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
id|entry.gid
op_assign
id|attr-&gt;ia_gid
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
id|entry.mode
op_assign
id|attr-&gt;ia_mode
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME
)paren
id|entry.atime
op_assign
id|attr-&gt;ia_atime
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
id|entry.mtime
op_assign
id|attr-&gt;ia_mtime
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_CTIME
)paren
id|entry.ctime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
id|entry.nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|filp.f_pos
op_assign
id|inode-&gt;u.umsdos_i.pos
suffix:semicolon
id|ret
op_assign
id|umsdos_emd_dir_write
(paren
op_amp
id|filp
comma
(paren
r_char
op_star
)paren
op_amp
id|entry
comma
id|UMSDOS_REC_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;umsdos_notify_change: %s/%s EMD write error, ret=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|ret
)paren
suffix:semicolon
id|Printk
(paren
(paren
l_string|&quot;notify pos %lu ret %d nlink %d &quot;
comma
id|inode-&gt;u.umsdos_i.pos
comma
id|ret
comma
id|entry.nlink
)paren
)paren
suffix:semicolon
multiline_comment|/* #Specification: notify_change / msdos fs&n;&t; * notify_change operation are done only on the&n;&t; * EMD file. The msdos fs is not even called.&n;&t; */
macro_line|#ifdef UMSDOS_DEBUG_VERBOSE
r_if
c_cond
(paren
id|entry.flags
op_amp
id|UMSDOS_HIDDEN
)paren
id|printk
c_func
(paren
l_string|&quot;umsdos_notify_change: %s/%s hidden, nlink=%d, ret=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|entry.nlink
comma
id|ret
)paren
suffix:semicolon
macro_line|#endif
id|out_dput
suffix:colon
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Update the disk with the inode content&n; */
DECL|function|UMSDOS_write_inode
r_void
id|UMSDOS_write_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|fat_write_inode
(paren
id|inode
)paren
suffix:semicolon
id|newattrs.ia_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|newattrs.ia_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|newattrs.ia_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_MTIME
op_or
id|ATTR_ATIME
op_or
id|ATTR_CTIME
suffix:semicolon
multiline_comment|/*&n;&t; * UMSDOS_notify_change is convenient to call here&n;&t; * to update the EMD entry associated with this inode.&n;&t; * But it has the side effect to re&quot;dirt&quot; the inode.&n;&t; */
multiline_comment|/*      &n; * UMSDOS_notify_change (inode, &amp;newattrs);&n;&n; * inode-&gt;i_state &amp;= ~I_DIRTY; / * FIXME: this doesn&squot;t work.  We need to remove ourselves from list on dirty inodes. /mn/ */
)brace
DECL|variable|umsdos_sops
r_static
r_struct
id|super_operations
id|umsdos_sops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* read_inode */
id|UMSDOS_write_inode
comma
multiline_comment|/* write_inode */
id|UMSDOS_put_inode
comma
multiline_comment|/* put_inode */
id|fat_delete_inode
comma
multiline_comment|/* delete_inode */
id|UMSDOS_notify_change
comma
multiline_comment|/* notify_change */
id|UMSDOS_put_super
comma
multiline_comment|/* put_super */
l_int|NULL
comma
multiline_comment|/* write_super */
id|fat_statfs
comma
multiline_comment|/* statfs */
l_int|NULL
comma
multiline_comment|/* remount_fs */
id|fat_clear_inode
multiline_comment|/* clear_inode */
)brace
suffix:semicolon
multiline_comment|/*&n; * Read the super block of an Extended MS-DOS FS.&n; */
DECL|function|UMSDOS_read_super
r_struct
id|super_block
op_star
id|UMSDOS_read_super
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|super_block
op_star
id|res
suffix:semicolon
r_struct
id|dentry
op_star
id|new_root
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options.isvfat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Call msdos-fs to mount the disk.&n;&t; * Note: this returns res == sb or NULL&n;&t; */
id|res
op_assign
id|msdos_read_super
(paren
id|sb
comma
id|data
comma
id|silent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_goto
id|out_fail
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;UMSDOS 0.86 &quot;
l_string|&quot;(compatibility level %d.%d, fast msdos)&bslash;n&quot;
comma
id|UMSDOS_VERSION
comma
id|UMSDOS_RELEASE
)paren
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|umsdos_sops
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options.dotsOK
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable hidden==dotfile */
multiline_comment|/* install our dentry operations ... */
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|umsdos_dentry_operations
suffix:semicolon
id|umsdos_patch_dentry_inode
c_func
(paren
id|sb-&gt;s_root
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Check whether to change to the /linux root */
id|new_root
op_assign
id|check_pseudo_root
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_root
)paren
(brace
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|new_root-&gt;d_op
op_ne
op_amp
id|umsdos_dentry_operations
)paren
id|printk
c_func
(paren
l_string|&quot;umsdos_read_super: pseudo-root wrong ops!&bslash;n&quot;
)paren
suffix:semicolon
id|pseudo_root
op_assign
id|new_root-&gt;d_inode
suffix:semicolon
id|saved_root
op_assign
id|sb-&gt;s_root
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|new_root
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;UMSDOS: changed to alternate root&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* if d_count is not 1, mount will fail with -EBUSY! */
r_if
c_cond
(paren
id|sb-&gt;s_root-&gt;d_count
OG
l_int|1
)paren
(brace
id|shrink_dcache_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_root-&gt;d_count
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;UMSDOS: root count %d &gt; 1 !&quot;
comma
id|sb-&gt;s_root-&gt;d_count
)paren
suffix:semicolon
)brace
)brace
r_return
id|sb
suffix:semicolon
id|out_fail
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;UMSDOS: msdos_read_super failed, mount aborted.&bslash;n&quot;
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Check for an alternate root if we&squot;re the root device.&n; */
r_extern
id|kdev_t
id|ROOT_DEV
suffix:semicolon
DECL|function|check_pseudo_root
r_static
r_struct
id|dentry
op_star
id|check_pseudo_root
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|dentry
op_star
id|root
comma
op_star
id|init
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether we&squot;re mounted as the root device.&n;&t; * must check like this, because we can be used with initrd&n;&t; */
r_if
c_cond
(paren
id|sb-&gt;s_dev
op_ne
id|ROOT_DEV
)paren
r_goto
id|out_noroot
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;check_pseudo_root: mounted as root&bslash;n&quot;
)paren
suffix:semicolon
id|root
op_assign
id|lookup_dentry
c_func
(paren
id|UMSDOS_PSDROOT_NAME
comma
id|dget
c_func
(paren
id|sb-&gt;s_root
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|root
)paren
)paren
r_goto
id|out_noroot
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root-&gt;d_inode
)paren
r_goto
id|out_dput
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;check_pseudo_root: found %s/%s&bslash;n&quot;
comma
id|root-&gt;d_parent-&gt;d_name.name
comma
id|root-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* look for /sbin/init */
id|init
op_assign
id|lookup_dentry
c_func
(paren
l_string|&quot;sbin/init&quot;
comma
id|dget
c_func
(paren
id|root
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|init
)paren
)paren
(brace
r_if
c_cond
(paren
id|init-&gt;d_inode
)paren
r_goto
id|root_ok
suffix:semicolon
id|dput
c_func
(paren
id|init
)paren
suffix:semicolon
)brace
multiline_comment|/* check for other files? */
r_goto
id|out_dput
suffix:semicolon
id|root_ok
suffix:colon
id|printk
c_func
(paren
l_string|&quot;check_pseudo_root: found %s/%s, enabling pseudo-root&bslash;n&quot;
comma
id|init-&gt;d_parent-&gt;d_name.name
comma
id|init-&gt;d_name.name
)paren
suffix:semicolon
id|dput
c_func
(paren
id|init
)paren
suffix:semicolon
r_return
id|root
suffix:semicolon
multiline_comment|/* Alternate root not found ... */
id|out_dput
suffix:colon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
id|out_noroot
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|umsdos_fs_type
r_static
r_struct
id|file_system_type
id|umsdos_fs_type
op_assign
(brace
l_string|&quot;umsdos&quot;
comma
id|FS_REQUIRES_DEV
comma
id|UMSDOS_read_super
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_umsdos_fs
r_int
id|__init
id|init_umsdos_fs
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
(paren
op_amp
id|umsdos_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_return
id|init_umsdos_fs
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
id|unregister_filesystem
(paren
op_amp
id|umsdos_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
