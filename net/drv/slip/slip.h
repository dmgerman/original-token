multiline_comment|/*&n; * slip.h&t;Define the SLIP device driver interface and constants.&n; *&n; * NOTE:&t;THIS FILE WILL BE MOVED TO THE LINUX INCLUDE DIRECTORY&n; *&t;&t;AS SOON AS POSSIBLE!&n; *&n; * Version:&t;@(#)slip.h&t;1.2.0&t;(02/11/93)&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_SLIP_H
DECL|macro|_LINUX_SLIP_H
mdefine_line|#define _LINUX_SLIP_H
multiline_comment|/* SLIP configuration. */
DECL|macro|SL_NRUNIT
mdefine_line|#define SL_NRUNIT&t;4&t;&t;/* number of SLIP channels&t;*/
DECL|macro|SL_MTU
mdefine_line|#define SL_MTU&t;&t;296&t;&t;/* 296; I am used to 600- FvK&t;*/
DECL|macro|SL_BUF_SIZE
mdefine_line|#define SL_BUF_SIZE&t;8192&t;&t;/* same as TTY for now&t;&t;*/
macro_line|#ifdef not_any_more
DECL|macro|SL_RCV_SIZE
mdefine_line|#define SL_RCV_SIZE&t;2048
macro_line|#endif
multiline_comment|/* SLIP protocol characters. */
DECL|macro|END
mdefine_line|#define END             0300&t;&t;/* indicates end of frame&t;*/
DECL|macro|ESC
mdefine_line|#define ESC             0333&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|ESC_END
mdefine_line|#define ESC_END         0334&t;&t;/* ESC ESC_END means END &squot;data&squot;&t;*/
DECL|macro|ESC_ESC
mdefine_line|#define ESC_ESC         0335&t;&t;/* ESC ESC_ESC means ESC &squot;data&squot;&t;*/
DECL|struct|sl_queue
r_struct
id|sl_queue
(brace
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|proc_list
r_struct
id|wait_queue
op_star
id|proc_list
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|SL_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|slip
r_struct
id|slip
(brace
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
multiline_comment|/* are we allocated?&t;&t;*/
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* SLIP channel number&t;&t;*/
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;&t;*/
macro_line|#if 0
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
macro_line|#endif
DECL|member|sending
r_int
r_int
id|sending
suffix:semicolon
multiline_comment|/* &quot;channel busy&quot; indicator&t;*/
DECL|member|rcv_queue
r_struct
id|sl_queue
id|rcv_queue
suffix:semicolon
DECL|member|snd_buf
r_char
id|snd_buf
(braket
(paren
id|SL_MTU
op_star
l_int|2
)paren
op_plus
l_int|4
)braket
suffix:semicolon
DECL|member|xbuff
r_int
r_char
id|xbuff
(braket
(paren
id|SL_MTU
op_star
l_int|2
)paren
)braket
suffix:semicolon
DECL|member|escape
r_int
id|escape
suffix:semicolon
multiline_comment|/* SLIP state machine&t;&t;*/
DECL|member|received
r_int
id|received
suffix:semicolon
multiline_comment|/* SLIP receive counter&t;&t;*/
DECL|member|sent
r_int
r_int
id|sent
suffix:semicolon
multiline_comment|/* #frames sent&t;&t;&t;*/
DECL|member|rcvd
r_int
r_int
id|rcvd
suffix:semicolon
multiline_comment|/* #frames rcvd&t;&t;&t;*/
DECL|member|errors
r_int
r_int
id|errors
suffix:semicolon
multiline_comment|/* error count&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|SL_INC
mdefine_line|#define SL_INC(a)&t;((a) = ((a)+1) &amp; (SL_BUF_SIZE-1))
DECL|macro|SL_DEC
mdefine_line|#define SL_DEC(a)&t;((a) = ((a)-1) &amp; (SL_BUF_SIZE-1))
DECL|macro|SL_EMPTY
mdefine_line|#define SL_EMPTY(a)&t;((a)-&gt;head == (a)-&gt;tail)
DECL|macro|SL_LEFT
mdefine_line|#define SL_LEFT(a)&t;(((a)-&gt;tail-(a)-&gt;head-1)&amp;(SL_BUF_SIZE-1))
DECL|macro|SL_LAST
mdefine_line|#define SL_LAST(a)&t;((a)-&gt;buf[(SL_BUF_SIZE-1)&amp;((a)-&gt;head-1)])
DECL|macro|SL_FULL
mdefine_line|#define SL_FULL(a)&t;(!SL_LEFT(a))
DECL|macro|SL_CHARS
mdefine_line|#define SL_CHARS(a)&t;(((a)-&gt;head-(a)-&gt;tail)&amp;(SL_BUF_SIZE-1))
r_extern
r_int
id|slip_init
c_func
(paren
r_struct
id|ddi
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_SLIP.H */
eof
