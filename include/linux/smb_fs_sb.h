multiline_comment|/*&n; *  smb_fs_sb.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *&n; */
macro_line|#ifndef _SMB_FS_SB
DECL|macro|_SMB_FS_SB
mdefine_line|#define _SMB_FS_SB
macro_line|#include &lt;linux/smb.h&gt;
macro_line|#include &lt;linux/smb_fs_i.h&gt;
macro_line|#include &lt;linux/smb_mount.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef __KERNEL__
DECL|struct|smb_server
r_struct
id|smb_server
(brace
DECL|member|protocol
r_enum
id|smb_protocol
id|protocol
suffix:semicolon
multiline_comment|/* The protocol this&n;                                              connection accepts. */
DECL|member|case_handling
r_enum
id|smb_case_hndl
id|case_handling
suffix:semicolon
DECL|member|sock_file
r_struct
id|file
op_star
id|sock_file
suffix:semicolon
multiline_comment|/* The socket we transfer&n;                                              data on. */
DECL|member|lock
r_int
id|lock
suffix:semicolon
multiline_comment|/* To prevent mismatch in&n;                                              protocols. */
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|max_xmit
id|__u32
id|max_xmit
suffix:semicolon
DECL|member|hostname
r_char
id|hostname
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|pid
id|word
id|pid
suffix:semicolon
DECL|member|server_uid
id|word
id|server_uid
suffix:semicolon
DECL|member|mid
id|word
id|mid
suffix:semicolon
DECL|member|tid
id|word
id|tid
suffix:semicolon
DECL|member|m
r_struct
id|smb_mount_data
id|m
suffix:semicolon
multiline_comment|/* We store the complete information here&n;                                  * to be able to reconnect.&n;                                  */
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
DECL|member|state
r_enum
id|smb_conn_state
id|state
suffix:semicolon
DECL|member|reconnect_time
r_int
r_int
id|reconnect_time
suffix:semicolon
multiline_comment|/* The time of the last attempt */
multiline_comment|/* The following are LANMAN 1.0 options transferred to us in&n;           SMBnegprot */
DECL|member|secmode
id|word
id|secmode
suffix:semicolon
DECL|member|maxmux
id|word
id|maxmux
suffix:semicolon
DECL|member|maxvcs
id|word
id|maxvcs
suffix:semicolon
DECL|member|blkmode
id|word
id|blkmode
suffix:semicolon
DECL|member|sesskey
id|dword
id|sesskey
suffix:semicolon
multiline_comment|/* We use our on data_ready callback, but need the original one */
DECL|member|data_ready
r_void
op_star
id|data_ready
suffix:semicolon
multiline_comment|/* We do not have unique numbers for files in the smb protocol&n;           like NFS-filehandles. (SMB was designed for DOS, not for&n;           UNIX!) So we have to create our own inode numbers. We keep&n;           a complete path of smb_inode_info&squot;s to each active&n;           inode. The inode number is then created by the address of&n;           this structure. */
DECL|member|root
r_struct
id|smb_inode_info
id|root
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the part of the super-block (in memory) for the SMB file system.&n; */
DECL|struct|smb_sb_info
r_struct
id|smb_sb_info
(brace
DECL|member|s_server
r_struct
id|smb_server
id|s_server
suffix:semicolon
DECL|member|s_attr
r_struct
id|smb_dskattr
id|s_attr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
