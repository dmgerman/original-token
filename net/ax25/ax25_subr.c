multiline_comment|/*&n; *&t;AX.25 release 031&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 1.3.61 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;AX.25 029&t;Alan(GW4PTS)&t;Switched to KA9Q constant names. Removed&n; *&t;&t;&t;&t;&t;old BSD code.&n; *&t;AX.25 030&t;Jonathan(G4KLX)&t;Added support for extended AX.25.&n; *&t;&t;&t;&t;&t;Added fragmentation support.&n; *&t;&t;&t;Darryl(G7LED)&t;Added function ax25_requeue_frames() to split&n; *&t;&t;&t;&t;&t;it up from ax25_frames_acked().&n; *&t;AX.25 031&t;Joerg(DL1BKE)&t;DAMA needs KISS Fullduplex ON/OFF.&n; *&t;&t;&t;&t;&t;Thus we have ax25_kiss_cmd() now... ;-)&n; *&t;&t;&t;Dave Brown(N2RJT)&n; *&t;&t;&t;&t;&t;Killed a silly bug in the DAMA code.&n; *&t;&t;&t;Joerg(DL1BKE)&t;found the real bug in ax25.h --- sorry.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_AX25
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
multiline_comment|/*&n; *&t;This routine purges all the queues of frames.&n; */
DECL|function|ax25_clear_queues
r_void
id|ax25_clear_queues
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;reseq_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|ax25_frames_acked
r_void
id|ax25_frames_acked
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
r_int
id|nr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|ax25-&gt;va
op_ne
id|nr
)paren
(brace
r_while
c_loop
(paren
id|skb_peek
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
op_ne
l_int|NULL
op_logical_and
id|ax25-&gt;va
op_ne
id|nr
)paren
(brace
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|ax25-&gt;va
op_assign
(paren
id|ax25-&gt;va
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;dama_slave
)paren
multiline_comment|/* dl1bke 960120 */
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Maybe this should be your ax25_invoke_retransmission(), which appears&n; * to be used but not do anything.  ax25_invoke_retransmission() used to&n; * be in AX 0.29, but has now gone in 0.30.&n; */
DECL|function|ax25_requeue_frames
r_void
id|ax25_requeue_frames
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skb_prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Requeue all the un-ack-ed frames on the output queue to be picked&n;&t; * up by ax25_kick called from the timer. This arrangement handles the&n;&t; * possibility of an empty output queue.&n;&t; */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|skb_prev
op_eq
l_int|NULL
)paren
id|skb_queue_head
c_func
(paren
op_amp
id|ax25-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_else
id|skb_append
c_func
(paren
id|skb_prev
comma
id|skb
)paren
suffix:semicolon
id|skb_prev
op_assign
id|skb
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Validate that the value of nr is between va and vs. Return true or&n; *&t;false for testing.&n; */
DECL|function|ax25_validate_nr
r_int
id|ax25_validate_nr
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|vc
op_assign
id|ax25-&gt;va
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|ax25-&gt;vs
)paren
(brace
r_if
c_cond
(paren
id|nr
op_eq
id|vc
)paren
r_return
l_int|1
suffix:semicolon
id|vc
op_assign
(paren
id|vc
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_eq
id|ax25-&gt;vs
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This routine is the centralised routine for parsing the control&n; *&t;information for the different frame formats.&n; */
DECL|function|ax25_decode
r_int
id|ax25_decode
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
op_star
id|ns
comma
r_int
op_star
id|nr
comma
r_int
op_star
id|pf
)paren
(brace
r_int
r_char
op_star
id|frame
suffix:semicolon
r_int
id|frametype
op_assign
id|ILLEGAL
suffix:semicolon
id|frame
op_assign
id|skb-&gt;data
suffix:semicolon
op_star
id|ns
op_assign
op_star
id|nr
op_assign
op_star
id|pf
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|MODULUS
)paren
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|S
)paren
op_eq
l_int|0
)paren
(brace
id|frametype
op_assign
id|I
suffix:semicolon
multiline_comment|/* I frame - carries NR/NS/PF */
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|PF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|U
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* S frame - take out PF/NR */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|PF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/* U frame - take out PF */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
op_complement
id|PF
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|PF
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|S
)paren
op_eq
l_int|0
)paren
(brace
id|frametype
op_assign
id|I
suffix:semicolon
multiline_comment|/* I frame - carries NR/NS/PF */
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|1
)braket
op_amp
id|EPF
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|U
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* S frame - take out PF/NR */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|1
)braket
op_amp
id|EPF
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/* U frame - take out PF */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
op_complement
id|PF
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|PF
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
id|frametype
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;This routine is called when the HDLC layer internally  generates a&n; *&t;command or  response  for  the remote machine ( eg. RR, UA etc. ). &n; *&t;Only supervisory or unnumbered frames are processed.&n; */
DECL|function|ax25_send_control
r_void
id|ax25_send_control
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
id|frametype
comma
r_int
id|poll_bit
comma
r_int
id|type
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|ax25-&gt;device
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Route died */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|AX25_BPQ_HEADER_LEN
op_plus
id|size_ax25_addr
c_func
(paren
id|ax25-&gt;digipeat
)paren
op_plus
l_int|2
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|size_ax25_addr
c_func
(paren
id|ax25-&gt;digipeat
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;sk
op_assign
id|ax25-&gt;sk
suffix:semicolon
id|ax25-&gt;sk-&gt;wmem_alloc
op_add_assign
id|skb-&gt;truesize
suffix:semicolon
)brace
multiline_comment|/* Assume a response - address structure for DTE */
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|MODULUS
)paren
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|PF
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|U
)paren
op_eq
id|S
)paren
multiline_comment|/* S frames carry NR */
op_star
id|dptr
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|U
)paren
op_eq
id|U
)paren
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|PF
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|dptr
(braket
l_int|0
)braket
op_assign
id|frametype
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|EPF
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|ax25_transmit_buffer
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send a &squot;DM&squot; to an unknown connection attempt, or an invalid caller.&n; *&n; *&t;Note: src here is the sender, thus its the target of the DM&n; */
DECL|function|ax25_return_dm
r_void
id|ax25_return_dm
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|digi
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_char
op_star
id|dptr
suffix:semicolon
id|ax25_digi
id|retdigi
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|AX25_BPQ_HEADER_LEN
op_plus
id|size_ax25_addr
c_func
(paren
id|digi
)paren
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Next SABM will get DM&squot;d */
id|skb_reserve
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|size_ax25_addr
c_func
(paren
id|digi
)paren
)paren
suffix:semicolon
id|ax25_digi_invert
c_func
(paren
id|digi
comma
op_amp
id|retdigi
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
op_star
id|dptr
op_assign
id|DM
op_or
id|PF
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Do the address ourselves&n;&t; */
id|dptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|size_ax25_addr
c_func
(paren
id|digi
)paren
)paren
suffix:semicolon
id|dptr
op_add_assign
id|build_ax25_addr
c_func
(paren
id|dptr
comma
id|dest
comma
id|src
comma
op_amp
id|retdigi
comma
id|C_RESPONSE
comma
id|MODULUS
)paren
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|ax25_queue_xmit
c_func
(paren
id|skb
comma
id|dev
comma
id|SOPRI_NORMAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Exponential backoff for AX.25&n; */
DECL|function|ax25_calculate_t1
r_int
r_int
id|ax25_calculate_t1
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_int
id|n
comma
id|t
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;backoff
)paren
(brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|ax25-&gt;n2count
suffix:semicolon
id|n
op_increment
)paren
id|t
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
l_int|8
)paren
id|t
op_assign
l_int|8
suffix:semicolon
)brace
r_return
id|t
op_star
id|ax25-&gt;rtt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Calculate the Round Trip Time&n; */
DECL|function|ax25_calculate_rtt
r_void
id|ax25_calculate_rtt
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;t1timer
OG
l_int|0
op_logical_and
id|ax25-&gt;n2count
op_eq
l_int|0
)paren
id|ax25-&gt;rtt
op_assign
(paren
l_int|9
op_star
id|ax25-&gt;rtt
op_plus
id|ax25-&gt;t1
op_minus
id|ax25-&gt;t1timer
)paren
op_div
l_int|10
suffix:semicolon
macro_line|#ifdef&t;AX25_T1CLAMPLO
multiline_comment|/* Don&squot;t go below one tenth of a second */
r_if
c_cond
(paren
id|ax25-&gt;rtt
OL
(paren
id|AX25_T1CLAMPLO
)paren
)paren
id|ax25-&gt;rtt
op_assign
(paren
id|AX25_T1CLAMPLO
)paren
suffix:semicolon
macro_line|#else&t;/* Failsafe - some people might have sub 1/10th RTTs :-) **/
r_if
c_cond
(paren
id|ax25-&gt;rtt
op_eq
l_int|0
)paren
id|ax25-&gt;rtt
op_assign
id|PR_SLOWHZ
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;AX25_T1CLAMPHI
multiline_comment|/* OR above clamped seconds **/
r_if
c_cond
(paren
id|ax25-&gt;rtt
OG
(paren
id|AX25_T1CLAMPHI
)paren
)paren
id|ax25-&gt;rtt
op_assign
(paren
id|AX25_T1CLAMPHI
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Digipeated address processing&n; */
multiline_comment|/*&n; *&t;Given an AX.25 address pull of to, from, digi list, command/response and the start of data&n; *&n; */
DECL|function|ax25_parse_addr
r_int
r_char
op_star
id|ax25_parse_addr
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|digi
comma
r_int
op_star
id|flags
comma
r_int
op_star
id|dama
)paren
(brace
r_int
id|d
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|14
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_ne
l_int|NULL
)paren
(brace
op_star
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|6
)braket
op_amp
id|LAPB_C
)paren
(brace
op_star
id|flags
op_assign
id|C_COMMAND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
(braket
l_int|13
)braket
op_amp
id|LAPB_C
)paren
(brace
op_star
id|flags
op_assign
id|C_RESPONSE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dama
op_ne
l_int|NULL
)paren
op_star
id|dama
op_assign
op_complement
id|buf
(braket
l_int|13
)braket
op_amp
id|DAMA_FLAG
suffix:semicolon
multiline_comment|/* Copy to, from */
r_if
c_cond
(paren
id|dest
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|dest
comma
id|buf
op_plus
l_int|0
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|src
comma
id|buf
op_plus
l_int|7
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_sub_assign
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
id|digi-&gt;lastrepeat
op_assign
op_minus
l_int|1
suffix:semicolon
id|digi-&gt;ndigi
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|buf
(braket
op_minus
l_int|1
)braket
op_amp
id|LAPB_E
)paren
)paren
(brace
r_if
c_cond
(paren
id|d
op_ge
id|AX25_MAX_DIGIS
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Max of 6 digis */
r_if
c_cond
(paren
id|len
OL
l_int|7
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Short packet */
r_if
c_cond
(paren
id|digi
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|digi-&gt;calls
(braket
id|d
)braket
comma
id|buf
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|digi-&gt;ndigi
op_assign
id|d
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|6
)braket
op_amp
id|AX25_REPEATED
)paren
(brace
id|digi-&gt;repeated
(braket
id|d
)braket
op_assign
l_int|1
suffix:semicolon
id|digi-&gt;lastrepeat
op_assign
id|d
suffix:semicolon
)brace
r_else
(brace
id|digi-&gt;repeated
(braket
id|d
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_sub_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Assemble an AX.25 header from the bits&n; */
DECL|function|build_ax25_addr
r_int
id|build_ax25_addr
c_func
(paren
r_int
r_char
op_star
id|buf
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|d
comma
r_int
id|flag
comma
r_int
id|modulus
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|dest
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
(paren
id|LAPB_E
op_or
id|LAPB_C
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_eq
id|C_COMMAND
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|LAPB_C
suffix:semicolon
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|src
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
(paren
id|LAPB_E
op_or
id|LAPB_C
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|SSSID_SPARE
suffix:semicolon
r_if
c_cond
(paren
id|modulus
op_eq
id|MODULUS
)paren
(brace
id|buf
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
)brace
r_else
(brace
id|buf
(braket
l_int|6
)braket
op_or_assign
id|ESSID_SPARE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flag
op_eq
id|C_RESPONSE
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|LAPB_C
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fast path the normal digiless path&n;&t; */
r_if
c_cond
(paren
id|d
op_eq
l_int|NULL
op_logical_or
id|d-&gt;ndigi
op_eq
l_int|0
)paren
(brace
id|buf
(braket
l_int|6
)braket
op_or_assign
id|LAPB_E
suffix:semicolon
r_return
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
)brace
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
r_while
c_loop
(paren
id|ct
OL
id|d-&gt;ndigi
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
op_amp
id|d-&gt;calls
(braket
id|ct
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;repeated
(braket
id|ct
)braket
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_REPEATED
suffix:semicolon
r_else
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_REPEATED
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_E
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|ct
op_increment
suffix:semicolon
)brace
id|buf
(braket
op_minus
l_int|1
)braket
op_or_assign
id|LAPB_E
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|size_ax25_addr
r_int
id|size_ax25_addr
c_func
(paren
id|ax25_digi
op_star
id|dp
)paren
(brace
r_if
c_cond
(paren
id|dp
op_eq
l_int|NULL
)paren
r_return
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
r_return
id|AX25_ADDR_LEN
op_star
(paren
l_int|2
op_plus
id|dp-&gt;ndigi
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Reverse Digipeat List. May not pass both parameters as same struct&n; */
DECL|function|ax25_digi_invert
r_void
id|ax25_digi_invert
c_func
(paren
id|ax25_digi
op_star
id|in
comma
id|ax25_digi
op_star
id|out
)paren
(brace
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Invert the digipeaters */
r_while
c_loop
(paren
id|ct
OL
id|in-&gt;ndigi
)paren
(brace
id|out-&gt;calls
(braket
id|ct
)braket
op_assign
id|in-&gt;calls
(braket
id|in-&gt;ndigi
op_minus
id|ct
op_minus
l_int|1
)braket
suffix:semicolon
id|out-&gt;repeated
(braket
id|ct
)braket
op_assign
l_int|0
suffix:semicolon
id|ct
op_increment
suffix:semicolon
)brace
multiline_comment|/* Copy ndigis */
id|out-&gt;ndigi
op_assign
id|in-&gt;ndigi
suffix:semicolon
multiline_comment|/* Finish off */
id|out-&gt;lastrepeat
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;:::FIXME:::&n; *&t;This is ****NOT**** the right approach. Not all drivers do kiss. We&n; *&t;need a driver level request to switch duplex mode, that does either&n; *&t;SCC changing, PI config or KISS as required.&n; *&n; *&t;Not to mention this request isnt currently reliable.&n; */
DECL|function|ax25_kiss_cmd
r_void
id|ax25_kiss_cmd
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
r_char
id|cmd
comma
r_int
r_char
id|param
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;device
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|2
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;sk
op_assign
id|ax25-&gt;sk
suffix:semicolon
id|ax25-&gt;sk-&gt;wmem_alloc
op_add_assign
id|skb-&gt;truesize
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_AX25
)paren
suffix:semicolon
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|cmd
suffix:semicolon
op_star
id|p
op_assign
id|param
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
comma
id|ax25-&gt;device
comma
id|SOPRI_NORMAL
)paren
suffix:semicolon
)brace
DECL|function|ax25_dama_on
r_void
id|ax25_dama_on
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_int
id|count
op_assign
id|ax25_dev_is_dama_slave
c_func
(paren
id|ax25-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
op_logical_and
id|ax25-&gt;sk-&gt;debug
)paren
id|printk
c_func
(paren
l_string|&quot;ax25_dama_on: DAMA on&bslash;n&quot;
)paren
suffix:semicolon
id|ax25_kiss_cmd
c_func
(paren
id|ax25
comma
l_int|5
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_dama_off
r_void
id|ax25_dama_off
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_int
id|count
op_assign
id|ax25_dev_is_dama_slave
c_func
(paren
id|ax25-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
op_logical_and
id|ax25-&gt;sk-&gt;debug
)paren
id|printk
c_func
(paren
l_string|&quot;ax25_dama_off: DAMA off&bslash;n&quot;
)paren
suffix:semicolon
id|ax25_kiss_cmd
c_func
(paren
id|ax25
comma
l_int|5
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
