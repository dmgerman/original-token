multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* routines to control the AP1000 Tnet interface */
macro_line|#include &lt;asm/ap1000/apreg.h&gt;
macro_line|#include &lt;asm/ap1000/aplib.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgtsrmmu.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/* message types for system messages */
DECL|macro|TNET_IP
mdefine_line|#define TNET_IP         0
DECL|macro|TNET_IP_SMALL
mdefine_line|#define TNET_IP_SMALL   1
DECL|macro|TNET_RPC
mdefine_line|#define TNET_RPC        2
r_static
r_struct
(brace
DECL|member|errors
r_int
id|errors
suffix:semicolon
DECL|member|alloc_errors
r_int
id|alloc_errors
suffix:semicolon
DECL|member|bytes_received
r_int
id|bytes_received
suffix:semicolon
DECL|member|bytes_sent
r_int
id|bytes_sent
suffix:semicolon
DECL|member|packets_received
r_int
id|packets_received
suffix:semicolon
DECL|member|packets_sent
r_int
id|packets_sent
suffix:semicolon
DECL|member|small_packets_received
r_int
id|small_packets_received
suffix:semicolon
DECL|member|small_packets_sent
r_int
id|small_packets_sent
suffix:semicolon
DECL|variable|tnet_stats
)brace
id|tnet_stats
suffix:semicolon
r_extern
r_int
id|cap_cid0
suffix:semicolon
r_extern
r_int
id|cap_ncel0
suffix:semicolon
DECL|variable|xy_global_head
r_static
id|u_long
id|xy_global_head
suffix:semicolon
r_extern
r_int
id|_ncel
comma
id|_ncelx
comma
id|_ncely
comma
id|_cid
comma
id|_cidx
comma
id|_cidy
suffix:semicolon
r_extern
r_struct
id|ringbuf_struct
id|system_ringbuf
suffix:semicolon
r_extern
id|u_long
id|system_read_ptr
suffix:semicolon
DECL|variable|system_recv_flag
id|u_long
id|system_recv_flag
op_assign
l_int|0
suffix:semicolon
DECL|variable|system_recv_count
r_static
id|u_long
id|system_recv_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|tnet_rel_cid_table
r_int
op_star
id|tnet_rel_cid_table
suffix:semicolon
DECL|variable|dummy
r_static
r_int
id|dummy
op_assign
l_int|1
suffix:semicolon
DECL|macro|TNET_IP_THRESHOLD
mdefine_line|#define TNET_IP_THRESHOLD 100
r_void
id|tnet_check_completion
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|reschedule
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|u_long
id|tnet_add_completion
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
id|a1
comma
dot
dot
dot
)paren
comma
r_int
id|a1
comma
r_int
id|a2
)paren
suffix:semicolon
r_static
r_void
id|tnet_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_struct
(brace
DECL|member|shift
r_int
id|shift
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|iports
)brace
id|iports
(braket
l_int|4
)braket
op_assign
(brace
(brace
id|MC_INTP_0_SH
comma
id|tnet_check_completion
)brace
comma
(brace
id|MC_INTP_1_SH
comma
id|reschedule
)brace
comma
(brace
id|MC_INTP_2_SH
comma
l_int|NULL
)brace
comma
(brace
id|MC_INTP_3_SH
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|rel_cid
r_static
r_inline
r_int
id|rel_cid
c_func
(paren
r_int
id|dst
)paren
(brace
r_int
id|dstx
comma
id|dsty
suffix:semicolon
r_int
id|dx
comma
id|dy
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_eq
id|_cid
)paren
r_return
l_int|0
suffix:semicolon
id|dstx
op_assign
id|dst
op_mod
id|_ncelx
suffix:semicolon
id|dsty
op_assign
id|dst
op_div
id|_ncelx
suffix:semicolon
r_if
c_cond
(paren
id|dstx
op_ge
id|_cidx
)paren
id|dx
op_assign
id|dstx
op_minus
id|_cidx
suffix:semicolon
r_else
id|dx
op_assign
(paren
id|_ncelx
op_minus
id|_cidx
)paren
op_plus
id|dstx
suffix:semicolon
r_if
c_cond
(paren
id|dsty
op_ge
id|_cidy
)paren
id|dy
op_assign
id|dsty
op_minus
id|_cidy
suffix:semicolon
r_else
id|dy
op_assign
(paren
id|_ncely
op_minus
id|_cidy
)paren
op_plus
id|dsty
suffix:semicolon
r_return
(paren
id|dx
op_lshift
l_int|8
)paren
op_or
id|dy
suffix:semicolon
)brace
DECL|macro|SAVE_PID
mdefine_line|#define SAVE_PID() &bslash;&n;  unsigned long flags; &bslash;&n;  int saved_pid; &bslash;&n;  save_flags(flags); cli(); &bslash;&n;  saved_pid = MSC_IN(MSC_PID); &bslash;&n;  MSC_OUT(MSC_PID,SYSTEM_CONTEXT);
DECL|macro|RESTORE_PID
mdefine_line|#define RESTORE_PID() &bslash;&n;  MSC_OUT(MSC_PID,saved_pid); &bslash;&n;  restore_flags(flags);
DECL|function|ap_put
r_void
id|ap_put
c_func
(paren
r_int
id|dest_cell
comma
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|dest_flag
comma
id|u_long
id|local_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
id|entry
op_assign
(paren
r_volatile
id|u_long
op_star
)paren
id|MSC_PUT_QUEUE_S
suffix:semicolon
op_star
id|entry
op_assign
id|tnet_rel_cid_table
(braket
id|dest_cell
)braket
suffix:semicolon
op_star
id|entry
op_assign
(paren
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* remote_addr is physical &n;   local address is virtual &n;   both flags are virtual */
DECL|function|ap_phys_put
r_void
id|ap_phys_put
c_func
(paren
r_int
id|dest_cell
comma
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|dest_flag
comma
id|u_long
id|local_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
id|entry
op_assign
(paren
r_volatile
id|u_long
op_star
)paren
id|MSC_CPUT_QUEUE_S
suffix:semicolon
op_star
id|entry
op_assign
id|tnet_rel_cid_table
(braket
id|dest_cell
)braket
suffix:semicolon
op_star
id|entry
op_assign
(paren
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* broadcast put - yeah! */
DECL|function|ap_bput
r_void
id|ap_bput
c_func
(paren
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|dest_flag
comma
id|u_long
id|local_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
op_assign
(paren
r_volatile
id|u_long
op_star
)paren
id|MSC_XYG_QUEUE_S
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
op_star
id|entry
op_assign
id|xy_global_head
suffix:semicolon
op_star
id|entry
op_assign
(paren
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* remote_addr is physical */
DECL|function|ap_phys_bput
r_void
id|ap_phys_bput
c_func
(paren
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|dest_flag
comma
id|u_long
id|local_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
op_assign
(paren
r_volatile
id|u_long
op_star
)paren
id|MSC_CXYG_QUEUE_S
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
op_star
id|entry
op_assign
id|xy_global_head
suffix:semicolon
op_star
id|entry
op_assign
(paren
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ap_get
r_void
id|ap_get
c_func
(paren
r_int
id|dest_cell
comma
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|local_flag
comma
id|u_long
id|dest_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
id|entry
op_assign
(paren
id|u_long
op_star
)paren
id|MSC_GET_QUEUE_S
suffix:semicolon
op_star
id|entry
op_assign
id|tnet_rel_cid_table
(braket
id|dest_cell
)braket
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* byte --&gt; word */
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* local_addr is physical &n;   remote_addr is virtual&n;   both flags are virtual&n;*/
DECL|function|ap_phys_get
r_void
id|ap_phys_get
c_func
(paren
r_int
id|dest_cell
comma
id|u_long
id|local_addr
comma
r_int
id|size
comma
id|u_long
id|remote_addr
comma
id|u_long
id|local_flag
comma
id|u_long
id|dest_flag
)paren
(brace
r_volatile
id|u_long
op_star
id|entry
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
id|entry
op_assign
(paren
id|u_long
op_star
)paren
id|MSC_CGET_QUEUE_S
suffix:semicolon
op_star
id|entry
op_assign
id|tnet_rel_cid_table
(braket
id|dest_cell
)braket
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* byte --&gt; word */
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|local_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|remote_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * copy a message from the ringbuffer - being careful of wraparound&n;*/
DECL|function|tnet_copyin
r_static
r_inline
r_void
id|tnet_copyin
c_func
(paren
r_int
op_star
id|dest
comma
r_int
op_star
id|src
comma
r_int
id|size
)paren
(brace
r_int
op_star
id|limit
op_assign
(paren
r_int
op_star
)paren
id|system_ringbuf.ringbuf
op_plus
(paren
id|SYSTEM_RINGBUF_SIZE
op_rshift
l_int|2
)paren
suffix:semicolon
r_int
id|size1
op_assign
id|limit
op_minus
id|src
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|size1
)paren
id|size1
op_assign
id|size
suffix:semicolon
id|size
op_sub_assign
id|size1
suffix:semicolon
r_while
c_loop
(paren
id|size1
op_decrement
)paren
(brace
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
id|src
op_assign
id|system_ringbuf.ringbuf
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
(brace
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;  put some data into a tasks ringbuffer. size is in words.&n;  */
DECL|function|memcpy_to_rbuf
r_static
r_inline
r_void
id|memcpy_to_rbuf
c_func
(paren
r_int
id|tid
comma
r_int
op_star
id|msgp
comma
r_int
id|size
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
suffix:semicolon
r_int
id|octx
comma
id|ctx
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|room
suffix:semicolon
id|tsk
op_assign
id|task
(braket
id|tid
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
op_logical_or
op_logical_neg
id|tsk-&gt;aplib
)paren
r_return
suffix:semicolon
id|octx
op_assign
id|srmmu_get_context
c_func
(paren
)paren
suffix:semicolon
id|ctx
op_assign
id|MPP_TASK_TO_CTX
c_func
(paren
id|tid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|octx
op_ne
id|ctx
)paren
id|srmmu_set_context
c_func
(paren
id|ctx
)paren
suffix:semicolon
id|aplib
op_assign
id|tsk-&gt;aplib
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;write_pointer
OL
id|aplib-&gt;read_pointer
)paren
id|room
op_assign
id|aplib-&gt;read_pointer
op_minus
(paren
id|aplib-&gt;write_pointer
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|room
op_assign
id|aplib-&gt;ringbuf_size
op_minus
(paren
(paren
id|aplib-&gt;write_pointer
op_plus
l_int|1
)paren
op_minus
id|aplib-&gt;read_pointer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|room
OL
id|size
)paren
(brace
id|send_sig
c_func
(paren
id|SIGLOST
comma
id|tsk
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
id|tnet_copyin
c_func
(paren
op_amp
id|aplib-&gt;ringbuf
(braket
id|aplib-&gt;write_pointer
)braket
comma
id|msgp
comma
id|size
)paren
suffix:semicolon
id|aplib-&gt;write_pointer
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;write_pointer
op_ge
id|aplib-&gt;ringbuf_size
)paren
id|aplib-&gt;write_pointer
op_sub_assign
id|aplib-&gt;ringbuf_size
suffix:semicolon
id|aplib-&gt;rbuf_flag1
op_increment
suffix:semicolon
id|finished
suffix:colon
r_if
c_cond
(paren
id|octx
op_ne
id|ctx
)paren
id|srmmu_set_context
c_func
(paren
id|octx
)paren
suffix:semicolon
)brace
multiline_comment|/* a aplib message has arrived on the system message queue - process&n;   it immediately and return the number of bytes taken by the message in&n;   the system ringbuffer &n;&n;   Note that this function may be called from interrupt level&n;   */
DECL|function|aplib_system_recv
r_static
r_inline
r_void
id|aplib_system_recv
c_func
(paren
r_int
op_star
id|msgp
)paren
(brace
r_int
id|tag
op_assign
id|msgp
(braket
l_int|1
)braket
op_rshift
l_int|28
suffix:semicolon
r_int
id|size
comma
id|tid
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_eq
id|RBUF_BIGSEND
)paren
(brace
id|aplib_bigrecv
c_func
(paren
id|msgp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|size
op_assign
(paren
id|msgp
(braket
l_int|0
)braket
op_amp
l_int|0xFFFFF
)paren
suffix:semicolon
id|tid
op_assign
(paren
id|msgp
(braket
l_int|1
)braket
op_amp
l_int|0x3FF
)paren
suffix:semicolon
id|memcpy_to_rbuf
c_func
(paren
id|tid
comma
id|msgp
comma
id|size
op_plus
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|tnet_ip_complete
r_void
id|tnet_ip_complete
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|from
)paren
(brace
macro_line|#if IP_DEBUG
r_char
op_star
id|data
op_assign
id|skb-&gt;data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CID(%d) tnet ip complete from %d&bslash;n&quot;
comma
id|_cid
comma
id|from
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|skb-&gt;len
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;(%08x)%c&quot;
comma
op_star
(paren
r_int
op_star
)paren
(paren
id|data
op_plus
id|i
)paren
comma
id|i
op_eq
l_int|32
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* ap_phys_put(from,(u_long)&amp;dummy,4,MC_INTP_0,0,0); */
id|bif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tnet_stats.bytes_received
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|tnet_stats.packets_received
op_increment
suffix:semicolon
)brace
DECL|function|tnet_ip_recv
r_static
r_void
id|tnet_ip_recv
c_func
(paren
r_int
id|cid
comma
id|u_long
op_star
id|info
)paren
(brace
id|u_long
id|flag
suffix:semicolon
id|u_long
id|ipsize
op_assign
id|info
(braket
l_int|1
)braket
suffix:semicolon
id|u_long
id|remote_addr
op_assign
id|info
(braket
l_int|0
)braket
suffix:semicolon
id|u_long
id|remote_flag
op_assign
id|info
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|ipsize
op_plus
l_int|8
)paren
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|ap_put
c_func
(paren
id|cid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|remote_flag
comma
l_int|0
)paren
suffix:semicolon
id|ap_phys_put
c_func
(paren
id|cid
comma
(paren
id|u_long
)paren
op_amp
id|dummy
comma
l_int|4
comma
id|MC_INTP_0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|tnet_stats.alloc_errors
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* align on 16 byte boundary */
id|flag
op_assign
id|tnet_add_completion
c_func
(paren
id|tnet_ip_complete
comma
(paren
r_int
)paren
id|skb
comma
(paren
r_int
)paren
id|cid
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|ipsize
)paren
suffix:semicolon
macro_line|#if 0
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_mod
l_int|500
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;CID(%d) fetching %d bytes from %x to %x&bslash;n&quot;
comma
id|_cid
comma
id|ipsize
comma
id|remote_addr
comma
id|p
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
macro_line|#endif
id|ap_get
c_func
(paren
id|cid
comma
id|p
comma
id|ipsize
comma
id|remote_addr
comma
id|flag
comma
id|remote_flag
)paren
suffix:semicolon
id|ap_phys_get
c_func
(paren
id|cid
comma
id|MC_INTP_0
comma
l_int|4
comma
(paren
id|u_long
)paren
op_amp
id|dummy
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if IP_DEBUG
id|printk
c_func
(paren
l_string|&quot;CID(%d) ip packet of length %ld from %ld&bslash;n&quot;
comma
id|_cid
comma
id|ipsize
comma
id|cid
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|tnet_ip_recv_small
r_static
r_void
id|tnet_ip_recv_small
c_func
(paren
id|u_long
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|size
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|8
)paren
suffix:semicolon
id|tnet_copyin
c_func
(paren
(paren
r_int
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|size
)paren
comma
(paren
r_int
op_star
)paren
id|data
comma
(paren
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|bif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tnet_stats.bytes_received
op_add_assign
id|size
suffix:semicolon
id|tnet_stats.packets_received
op_increment
suffix:semicolon
id|tnet_stats.small_packets_received
op_increment
suffix:semicolon
)brace
r_else
(brace
id|tnet_stats.alloc_errors
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* we&squot;ve got an RPC from a remote cell */
DECL|function|tnet_rpc_recv
r_static
r_void
id|tnet_rpc_recv
c_func
(paren
id|u_long
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_struct
id|fnp
(brace
r_void
(paren
op_star
id|fn
)paren
(paren
)paren
suffix:semicolon
)brace
id|fnp
suffix:semicolon
id|fnp
op_assign
op_star
(paren
r_struct
id|fnp
op_star
)paren
id|data
suffix:semicolon
id|fnp
dot
id|fn
c_func
(paren
id|data
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * receive messages from the system ringbuffer. We don&squot;t bother with&n; * all the niceities that are done in user space, we just always&n; * process the messages in order &n; */
DECL|function|tnet_recv
r_static
r_inline
r_void
id|tnet_recv
c_func
(paren
r_void
)paren
(brace
r_int
id|flags
suffix:semicolon
id|u_long
id|from
comma
op_star
id|data
comma
id|fix
comma
id|align
comma
id|size1
comma
id|size
comma
id|type
suffix:semicolon
r_if
c_cond
(paren
id|system_recv_flag
op_eq
id|system_recv_count
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|system_recv_flag
op_ne
id|system_recv_count
)paren
(brace
id|u_long
id|read_ptr
op_assign
(paren
id|system_read_ptr
op_plus
l_int|1
)paren
op_mod
(paren
id|SYSTEM_RINGBUF_SIZE
op_rshift
l_int|5
)paren
suffix:semicolon
id|u_long
op_star
id|msgp
op_assign
(paren
(paren
id|u_long
op_star
)paren
id|system_ringbuf.ringbuf
)paren
op_plus
(paren
id|read_ptr
op_lshift
l_int|3
)paren
suffix:semicolon
id|u_long
id|tag
op_assign
(paren
id|msgp
(braket
l_int|1
)braket
op_rshift
l_int|28
)paren
op_amp
l_int|0xF
suffix:semicolon
id|size1
op_assign
(paren
id|msgp
(braket
l_int|0
)braket
op_amp
l_int|0xFFFFF
)paren
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* move our read pointer past this message */
id|system_read_ptr
op_assign
(paren
id|system_read_ptr
op_plus
(paren
(paren
id|size1
op_plus
l_int|8
op_plus
l_int|31
)paren
op_rshift
l_int|5
)paren
)paren
op_mod
(paren
id|SYSTEM_RINGBUF_SIZE
op_rshift
l_int|5
)paren
suffix:semicolon
id|system_recv_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_ne
id|RBUF_SYSTEM
)paren
(brace
id|aplib_system_recv
c_func
(paren
id|msgp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|from
op_assign
id|msgp
(braket
l_int|0
)braket
op_rshift
l_int|22
suffix:semicolon
id|data
op_assign
id|msgp
op_plus
l_int|2
suffix:semicolon
id|fix
op_assign
(paren
id|msgp
(braket
l_int|0
)braket
op_rshift
l_int|20
)paren
op_amp
l_int|3
suffix:semicolon
id|align
op_assign
(paren
id|msgp
(braket
l_int|1
)braket
op_rshift
l_int|26
)paren
op_amp
l_int|3
suffix:semicolon
id|size
op_assign
(paren
(paren
id|size1
op_minus
id|align
)paren
op_amp
op_complement
l_int|3
)paren
op_or
id|fix
suffix:semicolon
id|type
op_assign
(paren
id|msgp
(braket
l_int|1
)braket
op_amp
l_int|0xFF
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|TNET_IP
suffix:colon
id|tnet_ip_recv
c_func
(paren
id|from
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TNET_IP_SMALL
suffix:colon
id|tnet_ip_recv_small
c_func
(paren
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TNET_RPC
suffix:colon
id|tnet_rpc_recv
c_func
(paren
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tnet_stats.errors
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;unknown Tnet type %ld&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
)brace
macro_line|#if DEBUG
id|printk
c_func
(paren
l_string|&quot;CID(%d) recvd %d bytes of type %d read_ptr=%x&bslash;n&quot;
comma
id|_cid
comma
id|size
comma
id|type
comma
id|system_read_ptr
)paren
suffix:semicolon
macro_line|#endif
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|COMPLETION_LIST_LENGTH
mdefine_line|#define COMPLETION_LIST_LENGTH 256
DECL|variable|completion_list_rp
r_static
r_int
id|completion_list_rp
op_assign
l_int|0
suffix:semicolon
DECL|variable|completion_list_wp
r_static
r_int
id|completion_list_wp
op_assign
l_int|0
suffix:semicolon
DECL|struct|completion_struct
r_static
r_volatile
r_struct
id|completion_struct
(brace
DECL|member|flag
id|u_long
id|flag
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
id|a1
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|member|args
id|u_long
id|args
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|completion_list
)brace
id|completion_list
(braket
id|COMPLETION_LIST_LENGTH
)braket
suffix:semicolon
DECL|function|tnet_check_completion
r_void
id|tnet_check_completion
c_func
(paren
r_void
)paren
(brace
r_struct
id|completion_struct
op_star
id|cs
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|tnet_recv
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|completion_list
(braket
id|completion_list_rp
)braket
dot
id|flag
op_ne
l_int|2
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|completion_list
(braket
id|completion_list_rp
)braket
dot
id|flag
op_eq
l_int|2
)paren
(brace
id|cs
op_assign
op_amp
id|completion_list
(braket
id|completion_list_rp
)braket
suffix:semicolon
id|cs-&gt;flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|completion_list_rp
op_eq
id|COMPLETION_LIST_LENGTH
)paren
id|completion_list_rp
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|fn
c_func
(paren
id|cs-&gt;args
(braket
l_int|0
)braket
comma
id|cs-&gt;args
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|completion_list
(braket
id|completion_list_rp
)braket
dot
id|flag
op_ne
l_int|2
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|tnet_add_completion
r_static
id|u_long
id|tnet_add_completion
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
id|a1
comma
dot
dot
dot
)paren
comma
r_int
id|a1
comma
r_int
id|a2
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|completion_struct
op_star
id|cs
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|completion_list
(braket
id|completion_list_wp
)braket
dot
id|flag
op_ne
l_int|0
)paren
id|tnet_check_completion
c_func
(paren
)paren
suffix:semicolon
id|cs
op_assign
op_amp
id|completion_list
(braket
id|completion_list_wp
)braket
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|completion_list_wp
op_eq
id|COMPLETION_LIST_LENGTH
)paren
id|completion_list_wp
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cs-&gt;flag
op_assign
l_int|1
suffix:semicolon
id|cs-&gt;fn
op_assign
id|fn
suffix:semicolon
id|cs-&gt;args
(braket
l_int|0
)braket
op_assign
id|a1
suffix:semicolon
id|cs-&gt;args
(braket
l_int|1
)braket
op_assign
id|a2
suffix:semicolon
r_return
(paren
id|u_long
)paren
op_amp
id|cs-&gt;flag
suffix:semicolon
)brace
multiline_comment|/* &n; * send a message to the tnet ringuffer on another cell. When the send has&n; * completed call fn with the args supplied &n; */
DECL|function|tnet_send
r_static
r_void
id|tnet_send
c_func
(paren
r_int
id|cid
comma
r_int
id|type
comma
r_char
op_star
id|src_addr
comma
r_int
id|byteSize
comma
r_int
id|immediate
comma
id|u_long
id|flag
)paren
(brace
r_int
id|wordSize
suffix:semicolon
r_int
id|byteAlign
comma
id|byteFix
suffix:semicolon
id|u_long
id|src
suffix:semicolon
id|u_long
id|info1
comma
id|info2
suffix:semicolon
r_volatile
id|u_long
op_star
id|entry
op_assign
(paren
r_volatile
id|u_long
op_star
)paren
id|MSC_SEND_QUEUE_S
suffix:semicolon
id|SAVE_PID
c_func
(paren
)paren
suffix:semicolon
id|byteAlign
op_assign
(paren
(paren
id|u_long
)paren
id|src_addr
)paren
op_amp
l_int|0x3
suffix:semicolon
id|byteFix
op_assign
id|byteSize
op_amp
l_int|0x3
suffix:semicolon
id|src
op_assign
(paren
id|u_long
)paren
id|src_addr
op_amp
op_complement
l_int|3
suffix:semicolon
id|wordSize
op_assign
(paren
id|byteSize
op_plus
id|byteAlign
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
id|info1
op_assign
(paren
id|_cid
op_lshift
l_int|22
)paren
op_or
(paren
id|byteFix
op_lshift
l_int|20
)paren
op_or
id|wordSize
suffix:semicolon
id|info2
op_assign
(paren
id|RBUF_SYSTEM
op_lshift
l_int|28
)paren
op_or
(paren
id|byteAlign
op_lshift
l_int|26
)paren
op_or
id|type
suffix:semicolon
op_star
id|entry
op_assign
id|tnet_rel_cid_table
(braket
id|cid
)braket
suffix:semicolon
op_star
id|entry
op_assign
id|wordSize
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
op_amp
id|system_recv_flag
suffix:semicolon
op_star
id|entry
op_assign
id|flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
id|u_long
)paren
id|src
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
id|info1
suffix:semicolon
op_star
id|entry
op_assign
id|info2
suffix:semicolon
id|RESTORE_PID
c_func
(paren
)paren
suffix:semicolon
id|ap_phys_put
c_func
(paren
id|cid
comma
(paren
id|u_long
)paren
op_amp
id|dummy
comma
l_int|4
comma
id|MC_INTP_0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|immediate
op_logical_and
id|flag
)paren
id|ap_phys_put
c_func
(paren
id|_cid
comma
(paren
id|u_long
)paren
op_amp
id|dummy
comma
l_int|4
comma
id|MC_INTP_0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|free_skb
r_static
r_void
id|free_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|op
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|op
)paren
suffix:semicolon
)brace
DECL|function|tnet_send_ip
r_void
id|tnet_send_ip
c_func
(paren
r_int
id|cid
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_char
op_star
id|data
op_assign
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|cap_request
)paren
suffix:semicolon
r_int
id|size
op_assign
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|cap_request
)paren
suffix:semicolon
id|u_long
id|flag
suffix:semicolon
macro_line|#if IP_DEBUG
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;[%08x]%c&quot;
comma
op_star
(paren
r_int
op_star
)paren
(paren
id|data
op_plus
id|i
)paren
comma
id|i
op_eq
l_int|32
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|size
OG
id|TNET_IP_THRESHOLD
)paren
(brace
r_int
op_star
id|info
op_assign
(paren
r_int
op_star
)paren
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* re-use the header */
id|info
(braket
l_int|0
)braket
op_assign
(paren
r_int
)paren
id|data
suffix:semicolon
id|info
(braket
l_int|1
)braket
op_assign
id|size
suffix:semicolon
id|info
(braket
l_int|2
)braket
op_assign
id|tnet_add_completion
c_func
(paren
id|free_skb
comma
(paren
r_int
)paren
id|skb
comma
(paren
r_int
)paren
id|FREE_WRITE
)paren
suffix:semicolon
id|tnet_send
c_func
(paren
id|cid
comma
id|TNET_IP
comma
id|info
comma
r_sizeof
(paren
r_int
)paren
op_star
l_int|3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|flag
op_assign
id|tnet_add_completion
c_func
(paren
id|free_skb
comma
(paren
r_int
)paren
id|skb
comma
(paren
r_int
)paren
id|FREE_WRITE
)paren
suffix:semicolon
id|tnet_send
c_func
(paren
id|cid
comma
id|TNET_IP_SMALL
comma
id|data
comma
id|size
comma
l_int|0
comma
id|flag
)paren
suffix:semicolon
id|tnet_stats.small_packets_sent
op_increment
suffix:semicolon
)brace
id|tnet_stats.packets_sent
op_increment
suffix:semicolon
id|tnet_stats.bytes_sent
op_add_assign
id|size
suffix:semicolon
macro_line|#if IP_DEBUG
id|printk
c_func
(paren
l_string|&quot;CID(%d) sent IP of size %d to %d&bslash;n&quot;
comma
id|_cid
comma
id|size
comma
id|cid
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|reschedule
r_static
r_void
id|reschedule
c_func
(paren
r_void
)paren
(brace
id|need_resched
op_assign
l_int|1
suffix:semicolon
id|mark_bh
c_func
(paren
id|TQUEUE_BH
)paren
suffix:semicolon
)brace
multiline_comment|/* make a remote procedure call &n;   If free is set then free the data after sending it &n;   The first element of data is presumed to be a function pointer&n;*/
DECL|function|tnet_rpc
r_int
id|tnet_rpc
c_func
(paren
r_int
id|cell
comma
r_char
op_star
id|data
comma
r_int
id|size
comma
r_int
id|free
)paren
(brace
r_int
id|flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|free
)paren
(brace
id|flag
op_assign
id|tnet_add_completion
c_func
(paren
id|kfree
comma
id|data
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tnet_send
c_func
(paren
id|cell
comma
id|TNET_RPC
comma
id|data
comma
id|size
comma
l_int|0
comma
id|flag
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iport_irq
r_static
r_void
id|iport_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
id|u_long
id|intr
op_assign
id|MC_IN
c_func
(paren
id|MC_INTR_PORT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|intr
op_amp
(paren
id|AP_INTR_REQ
op_lshift
id|iports
(braket
id|i
)braket
dot
id|shift
)paren
)paren
(brace
id|MC_OUT
c_func
(paren
id|MC_INTR_PORT
comma
id|AP_CLR_INTR_REQ
op_lshift
id|iports
(braket
id|i
)braket
dot
id|shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iports
(braket
id|i
)braket
dot
id|fn
)paren
id|iports
(braket
id|i
)braket
dot
id|fn
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|ap_tnet_init
r_void
id|ap_tnet_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|bif_add_debug_key
c_func
(paren
l_char|&squot;T&squot;
comma
id|tnet_info
comma
l_string|&quot;Tnet status&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|completion_list
comma
l_int|0
comma
r_sizeof
(paren
id|completion_list
)paren
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|APIPORT_IRQ
comma
id|iport_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;iport&quot;
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|MC_OUT
c_func
(paren
id|MC_INTR_PORT
comma
id|AP_CLR_INTR_REQ
op_lshift
id|iports
(braket
id|i
)braket
dot
id|shift
)paren
suffix:semicolon
id|MC_OUT
c_func
(paren
id|MC_INTR_PORT
comma
id|AP_CLR_INTR_MASK
op_lshift
id|iports
(braket
id|i
)braket
dot
id|shift
)paren
suffix:semicolon
)brace
id|tnet_rel_cid_table
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|_ncel
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|_ncel
suffix:semicolon
id|i
op_increment
)paren
id|tnet_rel_cid_table
(braket
id|i
)braket
op_assign
id|rel_cid
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_cid
op_eq
l_int|0
)paren
(brace
id|xy_global_head
op_assign
(paren
(paren
(paren
id|_ncelx
op_minus
l_int|1
)paren
op_lshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
id|_ncely
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|_ncel
suffix:semicolon
id|i
op_mul_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|i
op_amp
id|_cid
)paren
(brace
r_int
id|rcidx
op_assign
(paren
id|_cid
op_minus
id|i
)paren
op_mod
id|_ncelx
op_minus
id|_cid
op_mod
id|_ncelx
suffix:semicolon
r_int
id|rcidy
op_assign
(paren
id|_cid
op_minus
id|i
)paren
op_div
id|_ncelx
op_minus
id|_cid
op_div
id|_ncelx
suffix:semicolon
id|xy_global_head
op_assign
(paren
(paren
id|rcidx
op_lshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
op_or
(paren
id|rcidy
op_amp
l_int|0xff
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|tnet_info
r_static
r_void
id|tnet_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|completion_struct
op_star
id|cs
suffix:semicolon
id|printk
c_func
(paren
"&quot;"
id|errors
op_assign
op_mod
id|d
id|alloc_errors
op_assign
op_mod
id|d
id|bytes_received
op_assign
op_mod
id|d
id|bytes_sent
op_assign
op_mod
id|d
id|packets_received
op_assign
op_mod
id|d
id|packets_sent
op_assign
op_mod
id|d
id|small_received
op_assign
op_mod
id|d
id|small_sent
op_assign
op_mod
id|d
"&quot;"
comma
id|tnet_stats.errors
comma
id|tnet_stats.alloc_errors
comma
id|tnet_stats.bytes_received
comma
id|tnet_stats.bytes_sent
comma
id|tnet_stats.packets_received
comma
id|tnet_stats.packets_sent
comma
id|tnet_stats.small_packets_received
comma
id|tnet_stats.small_packets_sent
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;recv_flag=%d recv_count=%d read_ptr=%d&bslash;n&quot;
comma
id|system_recv_flag
comma
id|system_recv_count
comma
id|system_read_ptr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;completion_list_rp=%d  completion_list_wp=%d&bslash;n&quot;
comma
id|completion_list_rp
comma
id|completion_list_wp
)paren
suffix:semicolon
)brace
eof