multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* aplib kernel interface definition */
macro_line|#ifndef _APLIB_H_
DECL|macro|_APLIB_H_
mdefine_line|#define _APLIB_H_
DECL|struct|aplib_struct
r_struct
id|aplib_struct
(brace
DECL|member|ringbuf
r_int
op_star
id|ringbuf
suffix:semicolon
DECL|member|write_pointer
DECL|member|read_pointer
r_int
id|write_pointer
comma
id|read_pointer
suffix:semicolon
multiline_comment|/* in words */
DECL|member|ringbuf_size
r_int
id|ringbuf_size
suffix:semicolon
multiline_comment|/* in words */
DECL|member|rbuf_counter
r_int
id|rbuf_counter
suffix:semicolon
multiline_comment|/* read messages */
DECL|member|rbuf_flag1
DECL|member|rbuf_flag2
r_int
id|rbuf_flag1
comma
id|rbuf_flag2
suffix:semicolon
multiline_comment|/* received messages */
DECL|member|physical_cid
r_int
op_star
id|physical_cid
suffix:semicolon
multiline_comment|/* logical to physical mapping */
DECL|member|rel_cid
r_int
op_star
id|rel_cid
suffix:semicolon
multiline_comment|/* logical to relative (RTC) mapping */
DECL|member|numcells
r_int
id|numcells
suffix:semicolon
multiline_comment|/* number of logical cells */
DECL|member|numcells_x
r_int
id|numcells_x
suffix:semicolon
multiline_comment|/* number of logical cells in x direction */
DECL|member|numcells_y
r_int
id|numcells_y
suffix:semicolon
multiline_comment|/* number of logical cells in y direction */
DECL|member|cid
DECL|member|tid
r_int
id|cid
comma
id|tid
suffix:semicolon
multiline_comment|/* this cells logical cell ID and task ID */
DECL|member|cidx
DECL|member|cidy
r_int
id|cidx
comma
id|cidy
suffix:semicolon
multiline_comment|/* logical cell id in x and y direction */
DECL|member|ack_flag
DECL|member|ack_request
r_int
id|ack_flag
comma
id|ack_request
suffix:semicolon
DECL|member|ok_x
DECL|member|ok_y
DECL|member|ok_xy
r_int
id|ok_x
comma
id|ok_y
comma
id|ok_xy
suffix:semicolon
multiline_comment|/* whether hardware x, y and xy sends are allowed */
)brace
suffix:semicolon
multiline_comment|/*&n; * the system ringbuffer structure&n; * this is also the old way that tasks accessed the MSC hardware&n; */
DECL|struct|ringbuf_struct
r_struct
id|ringbuf_struct
(brace
DECL|member|ringbuf
r_void
op_star
id|ringbuf
suffix:semicolon
multiline_comment|/* pointer to the ringbuf */
DECL|member|shared
r_void
op_star
id|shared
suffix:semicolon
multiline_comment|/* pointer to the shared page */
DECL|member|order
r_int
id|order
suffix:semicolon
multiline_comment|/* arg to __get_free_pages */
DECL|member|write_ptr
r_int
id|write_ptr
suffix:semicolon
multiline_comment|/* write pointer into the ringbuf */
DECL|member|vaddr
r_int
id|vaddr
suffix:semicolon
multiline_comment|/* base virtual address of ringbuf for task */
DECL|member|frag_count
r_int
id|frag_count
suffix:semicolon
multiline_comment|/* how many words in the frag queue */
DECL|member|frag_len
r_int
id|frag_len
suffix:semicolon
multiline_comment|/* how many words expected in the frag queue */
DECL|member|sq_fragment
r_int
id|sq_fragment
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* if the task switches part way through&n;&t;&t;&t;&t;     an op then shove the partial op here */
)brace
suffix:semicolon
DECL|macro|APLIB_INIT
mdefine_line|#define APLIB_INIT    1
DECL|macro|APLIB_SYNC
mdefine_line|#define APLIB_SYNC    2
DECL|macro|APLIB_GET
mdefine_line|#define APLIB_GET     3
DECL|macro|APLIB_PUT
mdefine_line|#define APLIB_PUT     4
DECL|macro|APLIB_SEND
mdefine_line|#define APLIB_SEND    5
DECL|macro|APLIB_PROBE
mdefine_line|#define APLIB_PROBE   6
DECL|macro|APLIB_POLL
mdefine_line|#define APLIB_POLL    7
DECL|macro|APLIB_XSEND
mdefine_line|#define APLIB_XSEND   8
DECL|macro|APLIB_YSEND
mdefine_line|#define APLIB_YSEND   9
DECL|macro|APLIB_XYSEND
mdefine_line|#define APLIB_XYSEND 10
DECL|macro|APLIB_XPUT
mdefine_line|#define APLIB_XPUT   11
DECL|macro|APLIB_YPUT
mdefine_line|#define APLIB_YPUT   12
DECL|macro|APLIB_XYPUT
mdefine_line|#define APLIB_XYPUT  13
multiline_comment|/* message kinds */
DECL|macro|RBUF_SYSTEM
mdefine_line|#define RBUF_SYSTEM  0
DECL|macro|RBUF_SEND
mdefine_line|#define RBUF_SEND    1
DECL|macro|RBUF_X_BRD
mdefine_line|#define RBUF_X_BRD   2
DECL|macro|RBUF_Y_BRD
mdefine_line|#define RBUF_Y_BRD   3
DECL|macro|RBUF_XY_BRD
mdefine_line|#define RBUF_XY_BRD  4
DECL|macro|RBUF_RPC
mdefine_line|#define RBUF_RPC     5
DECL|macro|RBUF_GET
mdefine_line|#define RBUF_GET     6
DECL|macro|RBUF_MPI
mdefine_line|#define RBUF_MPI     7
DECL|macro|RBUF_BIGSEND
mdefine_line|#define RBUF_BIGSEND 8
DECL|macro|RBUF_SEEN
mdefine_line|#define RBUF_SEEN   0xE
DECL|macro|RBUF_READ
mdefine_line|#define RBUF_READ   0xF
DECL|macro|APLIB_PAGE_BASE
mdefine_line|#define APLIB_PAGE_BASE 0xd0000000
DECL|macro|APLIB_PAGE_LEN
mdefine_line|#define APLIB_PAGE_LEN  8192
DECL|struct|aplib_init
r_struct
id|aplib_init
(brace
DECL|member|numcells
DECL|member|cid
r_int
id|numcells
comma
id|cid
suffix:semicolon
DECL|member|numcells_x
DECL|member|numcells_y
r_int
id|numcells_x
comma
id|numcells_y
suffix:semicolon
DECL|member|phys_cells
r_int
op_star
id|phys_cells
suffix:semicolon
multiline_comment|/* physical cell list */
DECL|member|ringbuffer
r_int
op_star
id|ringbuffer
suffix:semicolon
multiline_comment|/* pointer to user supplied ring buffer */
DECL|member|ringbuf_size
r_int
id|ringbuf_size
suffix:semicolon
multiline_comment|/* in words */
)brace
suffix:semicolon
DECL|struct|aplib_putget
r_struct
id|aplib_putget
(brace
DECL|member|cid
r_int
id|cid
suffix:semicolon
DECL|member|src_addr
DECL|member|dest_addr
r_int
op_star
id|src_addr
comma
op_star
id|dest_addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* in words */
DECL|member|dest_flag
DECL|member|src_flag
r_int
op_star
id|dest_flag
comma
op_star
id|src_flag
suffix:semicolon
DECL|member|ack
r_int
id|ack
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aplib_send
r_struct
id|aplib_send
(brace
multiline_comment|/* the ordering here is actually quite important - the parts to be&n;&t;   read by the bigrecv function must be in the first 24 bytes */
DECL|member|src_addr
r_int
id|src_addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|info1
DECL|member|info2
r_int
id|info1
comma
id|info2
suffix:semicolon
DECL|member|flag_addr
r_int
id|flag_addr
suffix:semicolon
DECL|member|flag
r_volatile
r_int
id|flag
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|tag
r_int
id|tag
suffix:semicolon
DECL|member|cid
r_int
id|cid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|MAX_PUT_SIZE
mdefine_line|#define MAX_PUT_SIZE (1024*1024 - 1) /* in words */
DECL|macro|SMALL_SEND_THRESHOLD
mdefine_line|#define SMALL_SEND_THRESHOLD 128
macro_line|#endif
macro_line|#endif /* _APLIB_H_ */
eof
