multiline_comment|/*&n; *&t;Rose release 001&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.0 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;Rose 001&t;Jonathan(G4KLX)&t;Cloned from nr_out.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ROSE) || defined(CONFIG_ROSE_MODULE)
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
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/rose.h&gt;
multiline_comment|/*&n; *&t;This is where all Rose frames pass;&n; */
DECL|function|rose_output
r_void
id|rose_output
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
id|header
(braket
id|ROSE_MIN_LEN
)braket
suffix:semicolon
r_int
id|err
comma
id|frontlen
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_minus
id|ROSE_MIN_LEN
OG
id|ROSE_PACLEN
)paren
(brace
multiline_comment|/* Save a copy of the Header */
id|memcpy
c_func
(paren
id|header
comma
id|skb-&gt;data
comma
id|ROSE_MIN_LEN
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
)paren
suffix:semicolon
id|frontlen
op_assign
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|frontlen
op_plus
id|ROSE_PACLEN
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skbn-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skbn-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
)paren
suffix:semicolon
id|len
op_assign
(paren
id|ROSE_PACLEN
OG
id|skb-&gt;len
)paren
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ROSE_PACLEN
suffix:semicolon
multiline_comment|/* Copy the user data */
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|len
)paren
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Duplicate the Header */
id|skb_push
c_func
(paren
id|skbn
comma
id|ROSE_MIN_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skbn-&gt;data
comma
id|header
comma
id|ROSE_MIN_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
l_int|0
)paren
id|skbn-&gt;data
(braket
l_int|2
)braket
op_or_assign
id|M_BIT
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skbn
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;state
op_eq
id|ROSE_STATE_3
)paren
id|rose_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;This procedure is passed a buffer descriptor for an iframe. It builds&n; *&t;the rest of the control part of the frame and then writes it out.&n; */
DECL|function|rose_send_iframe
r_static
r_void
id|rose_send_iframe
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_or_assign
(paren
id|sk-&gt;protinfo.rose-&gt;vr
op_lshift
l_int|5
)paren
op_amp
l_int|0xE0
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_or_assign
(paren
id|sk-&gt;protinfo.rose-&gt;vs
op_lshift
l_int|1
)paren
op_amp
l_int|0x0E
suffix:semicolon
id|rose_transmit_link
c_func
(paren
id|skb
comma
id|sk-&gt;protinfo.rose-&gt;neighbour
)paren
suffix:semicolon
)brace
DECL|function|rose_kick
r_void
id|rose_kick
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
id|sk-&gt;timer
)paren
suffix:semicolon
id|start
op_assign
(paren
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|sk-&gt;protinfo.rose-&gt;va
suffix:colon
id|sk-&gt;protinfo.rose-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|sk-&gt;protinfo.rose-&gt;va
op_plus
id|ROSE_DEFAULT_WINDOW
)paren
op_mod
id|ROSE_MODULUS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sk-&gt;protinfo.rose-&gt;condition
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
id|sk-&gt;write_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Transmit data until either we&squot;re out of data to send or&n;&t;&t; * the window is full.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Dequeue the frame and copy it.&n;&t;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;write_queue
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
id|sk-&gt;write_queue
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
id|sk-&gt;protinfo.rose-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|ROSE_MODULUS
suffix:semicolon
id|last
op_assign
(paren
id|next
op_eq
id|end
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Transmit the frame copy.&n;&t;&t;&t; */
id|rose_send_iframe
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Requeue the original data frame.&n;&t;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
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
id|sk-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
id|sk-&gt;protinfo.rose-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
)brace
id|rose_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following routines are taken from page 170 of the 7th ARRL Computer&n; * Networking Conference paper, as is the whole state machine.&n; */
DECL|function|rose_enquiry_response
r_void
id|rose_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
(brace
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RNR
)paren
suffix:semicolon
)brace
r_else
(brace
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RR
)paren
suffix:semicolon
)brace
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
id|sk-&gt;protinfo.rose-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|rose_check_iframes_acked
r_void
id|rose_check_iframes_acked
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;vs
op_eq
id|nr
)paren
(brace
id|rose_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;va
op_ne
id|nr
)paren
(brace
id|rose_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
eof