macro_line|#ifndef LINUX_NBD_H
DECL|macro|LINUX_NBD_H
mdefine_line|#define LINUX_NBD_H
DECL|macro|NBD_SET_SOCK
mdefine_line|#define NBD_SET_SOCK&t;_IO( 0xab, 0 )
DECL|macro|NBD_SET_BLKSIZE
mdefine_line|#define NBD_SET_BLKSIZE&t;_IO( 0xab, 1 )
DECL|macro|NBD_SET_SIZE
mdefine_line|#define NBD_SET_SIZE&t;_IO( 0xab, 2 )
DECL|macro|NBD_DO_IT
mdefine_line|#define NBD_DO_IT&t;_IO( 0xab, 3 )
DECL|macro|NBD_CLEAR_SOCK
mdefine_line|#define NBD_CLEAR_SOCK&t;_IO( 0xab, 4 )
DECL|macro|NBD_CLEAR_QUE
mdefine_line|#define NBD_CLEAR_QUE&t;_IO( 0xab, 5 )
DECL|macro|NBD_PRINT_DEBUG
mdefine_line|#define NBD_PRINT_DEBUG&t;_IO( 0xab, 6 )
macro_line|#ifdef MAJOR_NR
macro_line|#include &lt;linux/locks.h&gt;
DECL|macro|LOCAL_END_REQUEST
mdefine_line|#define LOCAL_END_REQUEST
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#ifdef PARANOIA
r_extern
r_int
id|requests_in
suffix:semicolon
r_extern
r_int
id|requests_out
suffix:semicolon
macro_line|#endif
r_static
r_void
DECL|function|nbd_end_request
id|nbd_end_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
macro_line|#ifdef PARANOIA
id|requests_out
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|end_that_request_first
c_func
(paren
id|req
comma
op_logical_neg
id|req-&gt;errors
comma
l_string|&quot;nbd&quot;
)paren
)paren
r_return
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
DECL|macro|MAX_NBD
mdefine_line|#define MAX_NBD 128
macro_line|#endif
DECL|struct|nbd_device
r_struct
id|nbd_device
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|harderror
r_int
id|harderror
suffix:semicolon
multiline_comment|/* Code of hard error&t;&t;&t;*/
DECL|macro|NBD_READ_ONLY
mdefine_line|#define NBD_READ_ONLY 0x0001
DECL|macro|NBD_WRITE_NOCHK
mdefine_line|#define NBD_WRITE_NOCHK 0x0002
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* If == NULL, device is not ready, yet&t;*/
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* FIXME: not if debugging is off&t;*/
DECL|member|head
r_struct
id|request
op_star
id|head
suffix:semicolon
multiline_comment|/* Requests are added here...&t;&t;&t;*/
DECL|member|tail
r_struct
id|request
op_star
id|tail
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This now IS in some kind of include file...&t;*/
multiline_comment|/* These are send over network in request/reply magic field */
DECL|macro|NBD_REQUEST_MAGIC
mdefine_line|#define NBD_REQUEST_MAGIC 0x25609513
DECL|macro|NBD_REPLY_MAGIC
mdefine_line|#define NBD_REPLY_MAGIC 0x67446698
multiline_comment|/* Do *not* use magics: 0x12560953 0x96744668. */
DECL|struct|nbd_request
r_struct
id|nbd_request
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* == READ || == WRITE &t;*/
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|from
id|u64
id|from
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nbd_reply
r_struct
id|nbd_reply
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|error
id|u32
id|error
suffix:semicolon
multiline_comment|/* 0 = ok, else error&t;*/
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* handle you got from request&t;*/
)brace
suffix:semicolon
macro_line|#endif
eof
