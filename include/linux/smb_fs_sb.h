multiline_comment|/*&n; *  smb_fs_sb.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _SMB_FS_SB
DECL|macro|_SMB_FS_SB
mdefine_line|#define _SMB_FS_SB
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/smb.h&gt;
multiline_comment|/* Get the server for the specified dentry */
DECL|macro|server_from_dentry
mdefine_line|#define server_from_dentry(dentry) &amp;dentry-&gt;d_sb-&gt;u.smbfs_sb
DECL|macro|SB_of
mdefine_line|#define SB_of(server) ((struct super_block *) ((char *)(server) - &bslash;&n;&t;(unsigned long)(&amp;((struct super_block *)0)-&gt;u.smbfs_sb)))
DECL|struct|smb_sb_info
r_struct
id|smb_sb_info
(brace
DECL|member|state
r_enum
id|smb_conn_state
id|state
suffix:semicolon
DECL|member|sock_file
r_struct
id|file
op_star
id|sock_file
suffix:semicolon
DECL|member|mnt
r_struct
id|smb_mount_data
op_star
id|mnt
suffix:semicolon
multiline_comment|/* Connections are counted. Each time a new socket arrives,&n;&t; * generation is incremented.&n;&t; */
DECL|member|generation
r_int
r_int
id|generation
suffix:semicolon
DECL|member|conn_pid
id|pid_t
id|conn_pid
suffix:semicolon
DECL|member|opt
r_struct
id|smb_conn_opt
id|opt
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|packet_size
id|__u32
id|packet_size
suffix:semicolon
DECL|member|packet
r_int
r_char
op_star
id|packet
suffix:semicolon
DECL|member|rcls
r_int
r_int
id|rcls
suffix:semicolon
multiline_comment|/* The error codes we received */
DECL|member|err
r_int
r_int
id|err
suffix:semicolon
multiline_comment|/* We use our on data_ready callback, but need the original one */
DECL|member|data_ready
r_void
op_star
id|data_ready
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
