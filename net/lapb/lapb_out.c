multiline_comment|/*&n; *&t;LAPB release 001&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;LAPB 001&t;Jonathan Naylor&t;Started Coding&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_LAPB) || defined(CONFIG_LAPB_MODULE)
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/lapb.h&gt;
multiline_comment|/* &n; *  This procedure is passed a buffer descriptor for an iframe. It builds&n; *  the rest of the control part of the frame and then writes it out.&n; */
DECL|function|lapb_send_iframe
r_static
r_void
id|lapb_send_iframe
c_func
(paren
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|poll_bit
)paren
(brace
r_int
r_char
op_star
id|frame
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
id|frame
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|frame
(braket
l_int|0
)braket
op_assign
id|I
suffix:semicolon
id|frame
(braket
l_int|0
)braket
op_or_assign
(paren
id|lapb-&gt;vs
op_lshift
l_int|1
)paren
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|LAPB_EPF
suffix:colon
l_int|0
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_or_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|frame
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|frame
op_assign
id|I
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|LAPB_SPF
suffix:colon
l_int|0
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|lapb-&gt;vs
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
id|lapb_transmit_buffer
c_func
(paren
id|lapb
comma
id|skb
comma
id|LAPB_COMMAND
)paren
suffix:semicolon
)brace
DECL|function|lapb_kick
r_void
id|lapb_kick
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skbn
suffix:semicolon
r_int
id|modulus
comma
id|last
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|start
comma
id|end
comma
id|next
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|lapb-&gt;timer
)paren
suffix:semicolon
id|modulus
op_assign
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
ques
c_cond
id|LAPB_EMODULUS
suffix:colon
id|LAPB_SMODULUS
suffix:semicolon
id|start
op_assign
(paren
id|skb_peek
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|lapb-&gt;va
suffix:colon
id|lapb-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|lapb-&gt;va
op_plus
id|lapb-&gt;window
)paren
op_mod
id|modulus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lapb-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
)paren
op_logical_and
id|start
op_ne
id|end
op_logical_and
id|skb_peek
c_func
(paren
op_amp
id|lapb-&gt;write_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|lapb-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Dequeue the frame and copy it.&n;&t;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|lapb-&gt;write_queue
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|lapb-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|next
op_assign
(paren
id|lapb-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
macro_line|#ifdef notdef
id|last
op_assign
(paren
id|next
op_eq
id|end
)paren
op_logical_or
id|skb_peek
c_func
(paren
op_amp
id|lapb-&gt;write_queue
)paren
op_eq
l_int|NULL
suffix:semicolon
macro_line|#else
id|last
op_assign
(paren
id|next
op_eq
id|end
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t; * Transmit the frame copy.&n;&t;&t;&t; */
id|lapb_send_iframe
c_func
(paren
id|lapb
comma
id|skbn
comma
id|POLLOFF
)paren
suffix:semicolon
id|lapb-&gt;vs
op_assign
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Requeue the original data frame.&n;&t;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
macro_line|#ifdef notdef
)brace
r_while
c_loop
(paren
op_logical_neg
id|last
)paren
suffix:semicolon
macro_line|#else
)brace
r_while
c_loop
(paren
op_logical_neg
id|last
op_logical_and
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|lapb-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;t1timer
op_eq
l_int|0
)paren
id|lapb-&gt;t1timer
op_assign
id|lapb-&gt;t1
suffix:semicolon
)brace
id|lapb_set_timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
DECL|function|lapb_transmit_buffer
r_void
id|lapb_transmit_buffer
c_func
(paren
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_MLP
)paren
(brace
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_DCE
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_COMMAND
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_C
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_D
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_COMMAND
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_D
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_C
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_DCE
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_COMMAND
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_A
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_B
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_COMMAND
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_B
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|ptr
op_assign
id|LAPB_ADDR_A
suffix:semicolon
)brace
)brace
macro_line|#if LAPB_DEBUG &gt; 2
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX %02X %02X %02X&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
comma
id|skb-&gt;data
(braket
l_int|0
)braket
comma
id|skb-&gt;data
(braket
l_int|1
)braket
comma
id|skb-&gt;data
(braket
l_int|2
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|lapb_data_transmit
c_func
(paren
id|lapb
comma
id|skb
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
DECL|function|lapb_nr_error_recovery
r_void
id|lapb_nr_error_recovery
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|lapb_establish_data_link
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
DECL|function|lapb_establish_data_link
r_void
id|lapb_establish_data_link
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX SABME(1)&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|SABME
comma
id|POLLON
comma
id|LAPB_COMMAND
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX SABM(1)&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|SABM
comma
id|POLLON
comma
id|LAPB_COMMAND
)paren
suffix:semicolon
)brace
id|lapb-&gt;t2timer
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;t1timer
op_assign
id|lapb-&gt;t1
suffix:semicolon
)brace
DECL|function|lapb_transmit_enquiry
r_void
id|lapb_transmit_enquiry
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX RR(1) R%d&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
comma
id|lapb-&gt;vr
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|RR
comma
id|POLLON
comma
id|C_COMMAND
)paren
suffix:semicolon
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
id|lapb-&gt;t1timer
op_assign
id|lapb-&gt;t1
suffix:semicolon
)brace
DECL|function|lapb_enquiry_response
r_void
id|lapb_enquiry_response
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX RR(1) R%d&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
comma
id|lapb-&gt;vr
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|RR
comma
id|POLLON
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
)brace
DECL|function|lapb_timeout_response
r_void
id|lapb_timeout_response
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX RR(0) R%d&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
comma
id|lapb-&gt;vr
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|RR
comma
id|POLLOFF
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
)brace
DECL|function|lapb_check_iframes_acked
r_void
id|lapb_check_iframes_acked
c_func
(paren
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|lapb-&gt;vs
op_eq
id|nr
)paren
(brace
id|lapb_frames_acked
c_func
(paren
id|lapb
comma
id|nr
)paren
suffix:semicolon
id|lapb-&gt;t1timer
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|lapb-&gt;va
op_ne
id|nr
)paren
(brace
id|lapb_frames_acked
c_func
(paren
id|lapb
comma
id|nr
)paren
suffix:semicolon
id|lapb-&gt;t1timer
op_assign
id|lapb-&gt;t1
suffix:semicolon
)brace
)brace
)brace
DECL|function|lapb_check_need_response
r_void
id|lapb_check_need_response
c_func
(paren
id|lapb_cb
op_star
id|lapb
comma
r_int
id|type
comma
r_int
id|pf
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|LAPB_COMMAND
op_logical_and
id|pf
)paren
id|lapb_enquiry_response
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
