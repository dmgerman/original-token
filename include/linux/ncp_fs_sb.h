multiline_comment|/*&n; *  ncp_fs_sb.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _NCP_FS_SB
DECL|macro|_NCP_FS_SB
mdefine_line|#define _NCP_FS_SB
macro_line|#include &lt;linux/ncp_mount.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|NCP_DEFAULT_BUFSIZE
mdefine_line|#define NCP_DEFAULT_BUFSIZE 1024
DECL|struct|ncp_server
r_struct
id|ncp_server
(brace
DECL|member|m
r_struct
id|ncp_mount_data
id|m
suffix:semicolon
multiline_comment|/* Nearly all of the mount data is of&n;&t;&t;&t;&t;&t;   interest for us later, so we store&n;&t;&t;&t;&t;&t;   it completely. */
DECL|member|name_space
id|__u8
id|name_space
(braket
id|NCP_NUMBER_OF_VOLUMES
)braket
suffix:semicolon
DECL|member|ncp_filp
r_struct
id|file
op_star
id|ncp_filp
suffix:semicolon
multiline_comment|/* File pointer to ncp socket */
DECL|member|sequence
id|u8
id|sequence
suffix:semicolon
DECL|member|task
id|u8
id|task
suffix:semicolon
DECL|member|connection
id|u16
id|connection
suffix:semicolon
multiline_comment|/* Remote connection number */
DECL|member|completion
id|u8
id|completion
suffix:semicolon
multiline_comment|/* Status message from server */
DECL|member|conn_status
id|u8
id|conn_status
suffix:semicolon
multiline_comment|/* Bit 4 = 1 ==&gt; Server going down, no&n;&t;&t;&t;&t;   requests allowed anymore.&n;&t;&t;&t;&t;   Bit 0 = 1 ==&gt; Server is down. */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Negotiated bufsize */
DECL|member|reply_size
r_int
id|reply_size
suffix:semicolon
multiline_comment|/* Size of last reply */
DECL|member|packet_size
r_int
id|packet_size
suffix:semicolon
DECL|member|packet
r_int
r_char
op_star
id|packet
suffix:semicolon
multiline_comment|/* Here we prepare requests and&n;&t;&t;&t;&t;   receive replies */
DECL|member|lock
r_int
id|lock
suffix:semicolon
multiline_comment|/* To prevent mismatch in protocols. */
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|current_size
r_int
id|current_size
suffix:semicolon
multiline_comment|/* for packet preparation */
DECL|member|has_subfunction
r_int
id|has_subfunction
suffix:semicolon
DECL|member|ncp_reply_size
r_int
id|ncp_reply_size
suffix:semicolon
DECL|member|root
r_struct
id|ncp_inode_info
id|root
suffix:semicolon
DECL|member|root_path
r_char
id|root_path
suffix:semicolon
multiline_comment|/* &squot;&bslash;0&squot; */
)brace
suffix:semicolon
DECL|function|ncp_conn_valid
r_static
r_inline
r_int
id|ncp_conn_valid
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
(brace
r_return
(paren
(paren
id|server-&gt;conn_status
op_amp
l_int|0x11
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ncp_invalidate_conn
r_static
r_inline
r_void
id|ncp_invalidate_conn
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
(brace
id|server-&gt;conn_status
op_or_assign
l_int|0x01
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif
eof
