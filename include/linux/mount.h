multiline_comment|/*&n; *&n; * Definitions for mount interface. This describes the in the kernel build &n; * linkedlist with mounted filesystems.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@mcs.ow.nl&gt; &lt;mvw@tnix.net&gt; &lt;mvw@cistron.nl&gt;&n; *&n; * Version: $Id: mount.h,v 1.3 1994/07/20 22:01:00 mvw Exp mvw $&n; *&n; */
macro_line|#ifndef _LINUX_MOUNT_H
DECL|macro|_LINUX_MOUNT_H
mdefine_line|#define _LINUX_MOUNT_H
DECL|struct|vfsmount
r_struct
id|vfsmount
(brace
DECL|member|mnt_dev
id|dev_t
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
DECL|member|mnt_sem
r_struct
id|semaphore
id|mnt_sem
suffix:semicolon
multiline_comment|/* lock device while I/O in progress */
DECL|member|mnt_sb
r_struct
id|super_block
op_star
id|mnt_sb
suffix:semicolon
multiline_comment|/* pointer to superblock */
DECL|member|mnt_quotas
r_struct
id|file
op_star
id|mnt_quotas
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* fp&squot;s to quotafiles */
DECL|member|mnt_iexp
id|time_t
id|mnt_iexp
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* expiretime for inodes */
DECL|member|mnt_bexp
id|time_t
id|mnt_bexp
(braket
id|MAXQUOTAS
)braket
suffix:semicolon
multiline_comment|/* expiretime for blocks */
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
id|dev_t
id|dev
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MOUNT_H */
eof
