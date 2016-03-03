multiline_comment|/*&n; *  smb_fs_sb.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _SMB_FS_SB
DECL|macro|_SMB_FS_SB
mdefine_line|#define _SMB_FS_SB
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/smb.h&gt;
multiline_comment|/* structure access macros */
DECL|macro|server_from_inode
mdefine_line|#define server_from_inode(inode) (&amp;(inode)-&gt;i_sb-&gt;u.smbfs_sb)
DECL|macro|server_from_dentry
mdefine_line|#define server_from_dentry(dentry) (&amp;(dentry)-&gt;d_sb-&gt;u.smbfs_sb)
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
id|smb_mount_data_kernel
op_star
id|mnt
suffix:semicolon
DECL|member|temp_buf
r_int
r_char
op_star
id|temp_buf
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
id|wait_queue_head_t
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
multiline_comment|/* We use our own data_ready callback, but need the original one */
DECL|member|data_ready
r_void
op_star
id|data_ready
suffix:semicolon
multiline_comment|/* nls pointers for codepage conversions */
DECL|member|remote_nls
r_struct
id|nls_table
op_star
id|remote_nls
suffix:semicolon
DECL|member|local_nls
r_struct
id|nls_table
op_star
id|local_nls
suffix:semicolon
multiline_comment|/* utf8 can make strings longer so we can&squot;t do in-place conversion.&n;&t;   This is a buffer for temporary stuff. We only need one so no need&n;&t;   to put it on the stack. This points to temp_buf space. */
DECL|member|name_buf
r_char
op_star
id|name_buf
suffix:semicolon
DECL|member|convert
r_int
(paren
op_star
id|convert
)paren
(paren
r_char
op_star
comma
r_int
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|nls_table
op_star
comma
r_struct
id|nls_table
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
