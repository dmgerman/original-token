multiline_comment|/*&n; *  linux/fs/umsdos/rdir.c&n; *&n; *  Written 1994 by Jacques Gelinas&n; *&n; *  Extended MS-DOS directory pure MS-DOS handling functions&n; *  (For directory without EMD file).&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_struct
id|dentry
op_star
id|saved_root
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|pseudo_root
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|umsdos_dentry_operations
suffix:semicolon
DECL|struct|RDIR_FILLDIR
r_struct
id|RDIR_FILLDIR
(brace
DECL|member|dirbuf
r_void
op_star
id|dirbuf
suffix:semicolon
DECL|member|filldir
id|filldir_t
id|filldir
suffix:semicolon
DECL|member|real_root
r_int
id|real_root
suffix:semicolon
)brace
suffix:semicolon
DECL|function|rdir_filldir
r_static
r_int
id|rdir_filldir
(paren
r_void
op_star
id|buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|name_len
comma
id|off_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|RDIR_FILLDIR
op_star
id|d
op_assign
(paren
r_struct
id|RDIR_FILLDIR
op_star
)paren
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;real_root
)paren
(brace
id|PRINTK
(paren
(paren
id|KERN_DEBUG
l_string|&quot;rdir_filldir /mn/: real root!&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* real root of a pseudo_rooted partition */
r_if
c_cond
(paren
id|name_len
op_ne
id|UMSDOS_PSDROOT_LEN
op_logical_or
id|memcmp
(paren
id|name
comma
id|UMSDOS_PSDROOT_NAME
comma
id|UMSDOS_PSDROOT_LEN
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* So it is not the /linux directory */
r_if
c_cond
(paren
id|name_len
op_eq
l_int|2
op_logical_and
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
multiline_comment|/* Make sure the .. entry points back to the pseudo_root */
id|ino
op_assign
id|pseudo_root-&gt;i_ino
suffix:semicolon
)brace
id|ret
op_assign
id|d-&gt;filldir
(paren
id|d-&gt;dirbuf
comma
id|name
comma
id|name_len
comma
id|offset
comma
id|ino
comma
id|DT_UNKNOWN
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Any DOS directory */
id|ret
op_assign
id|d-&gt;filldir
(paren
id|d-&gt;dirbuf
comma
id|name
comma
id|name_len
comma
id|offset
comma
id|ino
comma
id|DT_UNKNOWN
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|UMSDOS_rreaddir
r_static
r_int
id|UMSDOS_rreaddir
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirbuf
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|RDIR_FILLDIR
id|bufk
suffix:semicolon
id|bufk.filldir
op_assign
id|filldir
suffix:semicolon
id|bufk.dirbuf
op_assign
id|dirbuf
suffix:semicolon
id|bufk.real_root
op_assign
id|pseudo_root
op_logical_and
(paren
id|dir
op_eq
id|saved_root-&gt;d_inode
)paren
suffix:semicolon
r_return
id|fat_readdir
(paren
id|filp
comma
op_amp
id|bufk
comma
id|rdir_filldir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup into a non promoted directory.&n; * If the result is a directory, make sure we find out if it is&n; * a promoted one or not (calling umsdos_setup_dir_inode(inode)).&n; */
multiline_comment|/* #Specification: pseudo root / DOS/..&n; * In the real root directory (c:&bslash;), the directory ..&n; * is the pseudo root (c:&bslash;linux).&n; */
DECL|function|umsdos_rlookup_x
r_struct
id|dentry
op_star
id|umsdos_rlookup_x
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
comma
r_int
id|nopseudo
)paren
(brace
r_struct
id|dentry
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|saved_root
op_logical_and
id|dir
op_eq
id|saved_root-&gt;d_inode
op_logical_and
op_logical_neg
id|nopseudo
op_logical_and
id|dentry-&gt;d_name.len
op_eq
id|UMSDOS_PSDROOT_LEN
op_logical_and
id|memcmp
(paren
id|dentry-&gt;d_name.name
comma
id|UMSDOS_PSDROOT_NAME
comma
id|UMSDOS_PSDROOT_LEN
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* #Specification: pseudo root / DOS/linux&n;&t;&t; * Even in the real root directory (c:&bslash;), the directory&n;&t;&t; * /linux won&squot;t show&n;&t;&t; */
id|ret
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|msdos_lookup
(paren
id|dir
comma
id|dentry
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
l_string|&quot;umsdos_rlookup_x: %s/%s failed, ret=%ld&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|PTR_ERR
c_func
(paren
id|ret
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
multiline_comment|/* We must install the proper function table&n;&t;&t; * depending on whether this is an MS-DOS or &n;&t;&t; * a UMSDOS directory&n;&t;&t; */
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;umsdos_rlookup_x: patch_dentry_inode %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|umsdos_patch_dentry_inode
c_func
(paren
id|dentry
comma
l_int|0
)paren
suffix:semicolon
)brace
id|out
suffix:colon
multiline_comment|/* always install our dentry ops ... */
id|dentry-&gt;d_op
op_assign
op_amp
id|umsdos_dentry_operations
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|UMSDOS_rlookup
r_struct
id|dentry
op_star
id|UMSDOS_rlookup
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
r_return
id|umsdos_rlookup_x
(paren
id|dir
comma
id|dentry
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* #Specification: dual mode / rmdir in a DOS directory&n; * In a DOS (not EMD in it) directory, we use a reverse strategy&n; * compared with a UMSDOS directory. We assume that a subdirectory&n; * of a DOS directory is also a DOS directory. This is not always&n; * true (umssync may be used anywhere), but makes sense.&n; * &n; * So we call msdos_rmdir() directly. If it failed with a -ENOTEMPTY&n; * then we check if it is a Umsdos directory. We check if it is&n; * really empty (only . .. and --linux-.--- in it). If it is true&n; * we remove the EMD and do a msdos_rmdir() again.&n; * &n; * In a Umsdos directory, we assume all subdirectories are also&n; * Umsdos directories, so we check the EMD file first.&n; */
multiline_comment|/* #Specification: pseudo root / rmdir /DOS&n; * The pseudo sub-directory /DOS can&squot;t be removed!&n; * This is done even if the pseudo root is not a Umsdos&n; * directory anymore (very unlikely), but an accident (under&n; * MS-DOS) is always possible.&n; * &n; * EPERM is returned.&n; */
DECL|function|UMSDOS_rrmdir
r_static
r_int
id|UMSDOS_rrmdir
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
r_int
id|ret
comma
id|empty
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|umsdos_is_pseudodos
(paren
id|dir
comma
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_unhashed
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|msdos_rmdir
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|ENOTEMPTY
)paren
r_goto
id|out
suffix:semicolon
id|empty
op_assign
id|umsdos_isempty
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|empty
op_eq
l_int|1
)paren
(brace
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
multiline_comment|/* We have to remove the EMD file. */
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry
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
op_logical_neg
id|IS_ERR
c_func
(paren
id|demd
)paren
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|demd-&gt;d_inode
)paren
id|ret
op_assign
id|msdos_unlink
(paren
id|dentry-&gt;d_inode
comma
id|demd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|d_delete
c_func
(paren
id|demd
)paren
suffix:semicolon
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* now retry the original ... */
id|ret
op_assign
id|msdos_rmdir
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* #Specification: dual mode / introduction&n; * One goal of UMSDOS is to allow a practical and simple coexistence&n; * between MS-DOS and Linux in a single partition. Using the EMD file&n; * in each directory, UMSDOS adds Unix semantics and capabilities to&n; * a normal DOS filesystem. To help and simplify coexistence, here is&n; * the logic related to the EMD file.&n; * &n; * If it is missing, then the directory is managed by the MS-DOS driver.&n; * The names are limited to DOS limits (8.3). No links, no device special&n; * and pipe and so on.&n; * &n; * If it is there, it is the directory. If it is there but empty, then&n; * the directory looks empty. The utility umssync allows synchronisation&n; * of the real DOS directory and the EMD.&n; * &n; * Whenever umssync is applied to a directory without EMD, one is&n; * created on the fly.  The directory is promoted to full Unix semantics.&n; * Of course, the ls command will show exactly the same content as before&n; * the umssync session.&n; * &n; * It is believed that the user/admin will promote directories to Unix&n; * semantics as needed.&n; * &n; * The strategy to implement this is to use two function table (struct&n; * inode_operations). One for true UMSDOS directory and one for directory&n; * with missing EMD.&n; * &n; * Functions related to the DOS semantic (but aware of UMSDOS) generally&n; * have a &quot;r&quot; prefix (r for real) such as UMSDOS_rlookup, to differentiate&n; * from the one with full UMSDOS semantics.&n; */
DECL|variable|umsdos_rdir_operations
r_struct
id|file_operations
id|umsdos_rdir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|UMSDOS_rreaddir
comma
id|ioctl
suffix:colon
id|UMSDOS_ioctl_dir
comma
)brace
suffix:semicolon
DECL|variable|umsdos_rdir_inode_operations
r_struct
id|inode_operations
id|umsdos_rdir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|msdos_create
comma
id|lookup
suffix:colon
id|UMSDOS_rlookup
comma
id|unlink
suffix:colon
id|msdos_unlink
comma
id|mkdir
suffix:colon
id|msdos_mkdir
comma
id|rmdir
suffix:colon
id|UMSDOS_rrmdir
comma
id|rename
suffix:colon
id|msdos_rename
comma
id|setattr
suffix:colon
id|UMSDOS_notify_change
comma
)brace
suffix:semicolon
eof
