macro_line|#ifndef _LINUX_NFS_MOUNT_H
DECL|macro|_LINUX_NFS_MOUNT_H
mdefine_line|#define _LINUX_NFS_MOUNT_H
multiline_comment|/*&n; *  linux/include/linux/nfs_mount.h&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  structure passed from user-space to kernel-space during an nfs mount&n; */
multiline_comment|/*&n; * WARNING!  Do not delete or change the order of these fields.  If&n; * a new field is required then add it to the end.  The version field&n; * tracks which fields are present.  This will ensure some measure of&n; * mount-to-kernel version compatibilty.  Most of these are used yet&n; * but here they are anyway.&n; */
DECL|macro|NFS_MOUNT_VERSION
mdefine_line|#define NFS_MOUNT_VERSION&t;1&t;/* current version */
DECL|struct|nfs_mount_data
r_struct
id|nfs_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|fd
r_int
id|fd
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|root
r_struct
id|nfs_fh
id|root
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|rsize
r_int
id|rsize
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|wsize
r_int
id|wsize
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|timeo
r_int
id|timeo
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|retrans
r_int
id|retrans
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acregmin
r_int
id|acregmin
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acregmax
r_int
id|acregmax
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acdirmin
r_int
id|acdirmin
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acdirmax
r_int
id|acdirmax
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|addr
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|hostname
r_char
id|hostname
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 1 */
)brace
suffix:semicolon
multiline_comment|/* bits in the flags field */
DECL|macro|NFS_MOUNT_SOFT
mdefine_line|#define NFS_MOUNT_SOFT&t;&t;0x0001&t;/* 1 */
DECL|macro|NFS_MOUNT_INTR
mdefine_line|#define NFS_MOUNT_INTR&t;&t;0x0002&t;/* 1 */
DECL|macro|NFS_MOUNT_SECURE
mdefine_line|#define NFS_MOUNT_SECURE&t;0x0004&t;/* 1 */
DECL|macro|NFS_MOUNT_POSIX
mdefine_line|#define NFS_MOUNT_POSIX&t;&t;0x0008&t;/* 1 */
DECL|macro|NFS_MOUNT_NOCTO
mdefine_line|#define NFS_MOUNT_NOCTO&t;&t;0x0010&t;/* 1 */
DECL|macro|NFS_MOUNT_NOAC
mdefine_line|#define NFS_MOUNT_NOAC&t;&t;0x0020&t;/* 1 */
macro_line|#endif
eof
