macro_line|#ifndef LINUX_NBD_H
DECL|macro|LINUX_NBD_H
mdefine_line|#define LINUX_NBD_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|NBD_SET_SOCK
mdefine_line|#define NBD_SET_SOCK _IO( 0xab, 0 )
DECL|macro|NBD_SET_BLKSIZE
mdefine_line|#define NBD_SET_BLKSIZE _IO( 0xab, 1 )
DECL|macro|NBD_SET_SIZE
mdefine_line|#define NBD_SET_SIZE _IO( 0xab, 2 )
DECL|macro|NBD_DO_IT
mdefine_line|#define NBD_DO_IT _IO( 0xab, 3 )
DECL|macro|NBD_CLEAR_SOCK
mdefine_line|#define NBD_CLEAR_SOCK _IO( 0xab, 4 )
DECL|macro|NBD_CLEAR_QUE
mdefine_line|#define NBD_CLEAR_QUE _IO( 0xab, 5 )
DECL|macro|NBD_PRINT_DEBUG
mdefine_line|#define NBD_PRINT_DEBUG _IO( 0xab, 6 )
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
DECL|macro|NBD_REQUEST_MAGIC
mdefine_line|#define NBD_REQUEST_MAGIC 0x12560953
DECL|macro|NBD_REPLY_MAGIC
mdefine_line|#define NBD_REPLY_MAGIC 0x96744668
DECL|macro|LO_MAGIC
mdefine_line|#define LO_MAGIC 0x68797548
DECL|struct|nbd_request
r_struct
id|nbd_request
(brace
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
DECL|member|from
id|__u32
id|from
suffix:semicolon
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* == READ || == WRITE &t;*/
)brace
suffix:semicolon
DECL|struct|nbd_reply
r_struct
id|nbd_reply
(brace
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* handle you got from request&t;*/
DECL|member|error
id|__u32
id|error
suffix:semicolon
multiline_comment|/* 0 = ok, else error&t;*/
)brace
suffix:semicolon
macro_line|#endif
eof
