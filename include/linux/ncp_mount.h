multiline_comment|/*&n; *  ncp_mount.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_MOUNT_H
DECL|macro|_LINUX_NCP_MOUNT_H
mdefine_line|#define _LINUX_NCP_MOUNT_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ipx.h&gt;
macro_line|#include &lt;linux/ncp.h&gt;
macro_line|#include &lt;linux/ncp_fs_i.h&gt;
DECL|macro|NCP_MOUNT_VERSION
mdefine_line|#define NCP_MOUNT_VERSION 3
multiline_comment|/* Values for flags */
DECL|macro|NCP_MOUNT_SOFT
mdefine_line|#define NCP_MOUNT_SOFT 0x0001
DECL|macro|NCP_MOUNT_INTR
mdefine_line|#define NCP_MOUNT_INTR 0x0002
DECL|struct|ncp_mount_data
r_struct
id|ncp_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|ncp_fd
r_int
r_int
id|ncp_fd
suffix:semicolon
multiline_comment|/* The socket to the ncp port */
DECL|member|mounted_uid
id|uid_t
id|mounted_uid
suffix:semicolon
multiline_comment|/* Who may umount() this filesystem? */
DECL|member|wdog_pid
id|pid_t
id|wdog_pid
suffix:semicolon
multiline_comment|/* Who cares for our watchdog packets? */
DECL|member|mounted_vol
r_int
r_char
id|mounted_vol
(braket
id|NCP_VOLNAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|time_out
r_int
r_int
id|time_out
suffix:semicolon
multiline_comment|/* How long should I wait after&n;&t;&t;&t;&t;   sending a NCP request? */
DECL|member|retry_count
r_int
r_int
id|retry_count
suffix:semicolon
multiline_comment|/* And how often should I retry? */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|file_mode
id|mode_t
id|file_mode
suffix:semicolon
DECL|member|dir_mode
id|mode_t
id|dir_mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
