multiline_comment|/*&n; *&n; * Definitions for mount interface. This describes the in the kernel build &n; * linkedlist with mounted filesystems.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; * Version: $Id: mount.h,v 2.0 1996/11/17 16:48:14 mvw Exp mvw $&n; *&n; */
macro_line|#ifndef _LINUX_MOUNT_H
DECL|macro|_LINUX_MOUNT_H
mdefine_line|#define _LINUX_MOUNT_H
DECL|macro|DQUOT_USR_ENABLED
mdefine_line|#define DQUOT_USR_ENABLED&t;0x01&t;&t;/* User diskquotas enabled */
DECL|macro|DQUOT_GRP_ENABLED
mdefine_line|#define DQUOT_GRP_ENABLED&t;0x02&t;&t;/* Group diskquotas enabled */
DECL|struct|quota_mount_options
r_struct
id|quota_mount_options
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags for diskquotas on this device */
DECL|member|semaphore
r_struct
id|semaphore
id|semaphore
suffix:semicolon
multiline_comment|/* lock device while I/O in progress */
DECL|member|files
r_struct
id|file
op_star
id|files
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* fp&squot;s to quotafiles */
DECL|member|inode_expire
id|time_t
id|inode_expire
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* expiretime for inode-quota */
DECL|member|block_expire
id|time_t
id|block_expire
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* expiretime for block-quota */
DECL|member|rsquash
r_char
id|rsquash
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* for quotas threath root as any other user */
)brace
suffix:semicolon
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
DECL|member|mnt_flags
r_int
r_int
id|mnt_flags
suffix:semicolon
multiline_comment|/* Flags of this device */
DECL|member|mnt_sb
r_struct
id|super_block
op_star
id|mnt_sb
suffix:semicolon
multiline_comment|/* pointer to superblock */
DECL|member|mnt_dquot
r_struct
id|quota_mount_options
id|mnt_dquot
suffix:semicolon
multiline_comment|/* Diskquota specific mount options */
DECL|member|mnt_next
r_struct
id|vfsmount
op_star
id|mnt_next
suffix:semicolon
multiline_comment|/* pointer to next in linkedlist */
)brace
suffix:semicolon
r_struct
id|vfsmount
op_star
id|lookup_vfsmnt
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Umount options&n; */
DECL|macro|MNT_FORCE
mdefine_line|#define MNT_FORCE&t;0x00000001&t;/* Attempt to forcibily umount */
macro_line|#endif /* _LINUX_MOUNT_H */
eof
