multiline_comment|/*&n; *  smb_mount.h&n; *&n; *  Copyright (C) 1995, 1996 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_MOUNT_H
DECL|macro|_LINUX_SMB_MOUNT_H
mdefine_line|#define _LINUX_SMB_MOUNT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|SMB_MOUNT_VERSION
mdefine_line|#define SMB_MOUNT_VERSION 6
DECL|struct|smb_mount_data
r_struct
id|smb_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|mounted_uid
id|__kernel_uid_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|__kernel_mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|__kernel_mode_t
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
