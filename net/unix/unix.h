multiline_comment|/*&n; * UNIX&t;&t;An implementation of the AF_UNIX network domain for the&n; *&t;&t;LINUX operating system.  UNIX is implemented using the&n; *&t;&t;BSD Socket interface as the means of communication with&n; *&t;&t;the user level.&n; *&n; *&t;&t;This file descibes some things of the UNIX protocol family&n; *&t;&t;module.  It is mainly used for the &quot;proc&quot; sub-module now,&n; *&t;&t;but it may be useful for cleaning up the UNIX module as a&n; *&t;&t;whole later.&n; *&n; * Version:&t;@(#)unix.h&t;1.0.3&t;05/25/93&n; *&n; * Authors:&t;Orest Zborowski, &lt;obz@Kodak.COM&gt;&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Dmitry Gorodchanin&t;-&t;proc locking&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef _LINUX_UN_H
DECL|struct|unix_proto_data
r_struct
id|unix_proto_data
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
multiline_comment|/* cnt of reference 0=free&t;*/
multiline_comment|/* -1=not initialised&t;-bgm&t;*/
DECL|member|socket
r_struct
id|socket
op_star
id|socket
suffix:semicolon
multiline_comment|/* socket we&squot;re bound to&t;*/
DECL|member|protocol
r_int
id|protocol
suffix:semicolon
DECL|member|sockaddr_un
r_struct
id|sockaddr_un
id|sockaddr_un
suffix:semicolon
DECL|member|sockaddr_len
r_int
id|sockaddr_len
suffix:semicolon
multiline_comment|/* &gt;0 if name bound&t;&t;*/
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|bp_head
DECL|member|bp_tail
r_int
id|bp_head
comma
id|bp_tail
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|peerupd
r_struct
id|unix_proto_data
op_star
id|peerupd
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
multiline_comment|/* Lock across page faults (FvK) */
DECL|member|lock_flag
r_int
id|lock_flag
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|unix_proto_data
id|unix_datas
(braket
id|NSOCKETS
)braket
suffix:semicolon
DECL|macro|last_unix_data
mdefine_line|#define last_unix_data&t;&t;(unix_datas + NSOCKETS - 1)
DECL|macro|UN_DATA
mdefine_line|#define UN_DATA(SOCK) &t;&t;((struct unix_proto_data *)(SOCK)-&gt;data)
DECL|macro|UN_PATH_OFFSET
mdefine_line|#define UN_PATH_OFFSET&t;&t;((unsigned long)((struct sockaddr_un *)0) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;-&gt;sun_path)
multiline_comment|/*&n; * Buffer size must be power of 2. buffer mgmt inspired by pipe code.&n; * note that buffer contents can wraparound, and we can write one byte less&n; * than full size to discern full vs empty.&n; */
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE&t;&t;PAGE_SIZE
DECL|macro|UN_BUF_AVAIL
mdefine_line|#define UN_BUF_AVAIL(UPD)&t;(((UPD)-&gt;bp_head - (UPD)-&gt;bp_tail) &amp; &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;(BUF_SIZE-1))
DECL|macro|UN_BUF_SPACE
mdefine_line|#define UN_BUF_SPACE(UPD)&t;((BUF_SIZE-1) - UN_BUF_AVAIL(UPD))
macro_line|#endif&t;/* _LINUX_UN_H */
r_extern
r_void
id|unix_proto_init
c_func
(paren
r_struct
id|ddi_proto
op_star
id|pro
)paren
suffix:semicolon
eof
