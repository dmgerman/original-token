multiline_comment|/*&n; *&n; * Definitions for mount interface. This describes the in the kernel build &n; * linkedlist with mounted filesystems.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; * Version: $Id: mount.h,v 2.0 1996/11/17 16:48:14 mvw Exp mvw $&n; *&n; */
macro_line|#ifndef _LINUX_MOUNT_H
DECL|macro|_LINUX_MOUNT_H
mdefine_line|#define _LINUX_MOUNT_H
DECL|struct|vfsmount
r_struct
id|vfsmount
(brace
DECL|member|mnt_dev
id|kdev_t
id|mnt_dev
suffix:semicolon
multiline_comment|/* Device this applies to */
DECL|member|mnt_devname
r_char
op_star
id|mnt_devname
suffix:semicolon
multiline_comment|/* Name of device e.g. /dev/dsk/hda1 */
DECL|member|mnt_dirname
r_char
op_star
id|mnt_dirname
suffix:semicolon
multiline_comment|/* Name of directory mounted on */
DECL|member|mnt_sb
r_struct
id|super_block
op_star
id|mnt_sb
suffix:semicolon
multiline_comment|/* pointer to superblock */
DECL|member|mnt_next
r_struct
id|vfsmount
op_star
id|mnt_next
suffix:semicolon
multiline_comment|/* pointer to next in linkedlist */
)brace
suffix:semicolon
multiline_comment|/* MOUNT_REWRITE: fill these */
DECL|function|mntget
r_static
r_inline
r_struct
id|vfsmount
op_star
id|mntget
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
r_return
id|mnt
suffix:semicolon
)brace
DECL|function|mntput
r_static
r_inline
r_void
id|mntput
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
)paren
(brace
)brace
macro_line|#endif /* _LINUX_MOUNT_H */
eof
