multiline_comment|/*&n; *&t;AX.25 release 031&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 1.2.1 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;AX.25 028a&t;Jonathan(G4KLX)&t;New state machine based on SDL diagrams.&n; *&t;AX.25 029&t;Alan(GW4PTS)&t;Switched to KA9Q constant names.&n; *&t;&t;&t;Jonathan(G4KLX)&t;Only poll when window is full.&n; *&t;AX.25 030&t;Jonathan(G4KLX)&t;Added fragmentation to ax25_output.&n; *&t;&t;&t;&t;&t;Added support for extended AX.25.&n; *&t;AX.25 031&t;Joerg(DL1BKE)&t;Added DAMA support&n; *&n; *&t;&t;&t;Joerg(DL1BKE)&t;Modified fragmenter to fragment vanilla &n; *&t;&t;&t;&t;&t;AX.25 I-Frames. Added PACLEN parameter.&n; *&t;&t;&t;Joerg(DL1BKE)&t;Fixed a problem with buffer allocation&n; *&t;&t;&t;&t;&t;for fragments.&n; */
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
multiline_comment|/*&n; * All outgoing AX.25 I frames pass via this routine. Therefore this is&n; * where the fragmentation of frames takes place.&n; */
DECL|function|ax25_output
r_void
id|ax25_output
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
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_int
id|frontlen
comma
id|mtu
comma
id|len
comma
id|fragno
comma
id|ka9qfrag
comma
id|first
op_assign
l_int|1
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * dl1bke 960301: We use the new PACLEN parameter as MTU of the AX.25 layer.&n;&t; *                This will (hopefully) allow user programs to write() data&n;&t; *                w/o having to think of the maximal amount of data we can&n;&t; *&t;&t;  send with one call. It&squot;s called PACLEN to (1) avoid confusion&n;&t; *&t;&t;  with (IP) MTU and (2) TAPR calls this PACLEN, too ;-)&n;&t; */
id|mtu
op_assign
id|ax25-&gt;paclen
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;len
op_minus
l_int|1
)paren
OG
id|mtu
)paren
(brace
r_switch
c_cond
(paren
op_star
id|skb-&gt;data
)paren
(brace
r_case
id|AX25_P_SEGMENT
suffix:colon
multiline_comment|/* this is an error, but... */
id|printk
c_func
(paren
l_string|&quot;ax25_output(): woops, fragmentation of fragment?!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* okay, let&squot;s fragment it further (tss, tss...) */
r_case
id|AX25_P_NETROM
suffix:colon
multiline_comment|/* err, is this a good idea? */
r_case
id|AX25_P_IP
suffix:colon
id|mtu
op_sub_assign
l_int|2
suffix:semicolon
multiline_comment|/* Allow for fragment control info */
id|ka9qfrag
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ka9qfrag
op_assign
l_int|0
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* skip PID */
r_break
suffix:semicolon
)brace
id|fragno
op_assign
id|skb-&gt;len
op_div
id|mtu
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_mod
id|mtu
op_eq
l_int|0
)paren
id|fragno
op_decrement
suffix:semicolon
id|frontlen
op_assign
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Address space + CTRL */
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
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
multiline_comment|/* &n;&t;&t;&t; * do _not_ use sock_alloc_send_skb, our socket may have&n;&t;&t;&t; * sk-&gt;shutdown set...&n;&t;&t;&t; *&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|alloc_skb
c_func
(paren
id|mtu
op_plus
l_int|2
op_plus
id|frontlen
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ax25_output(): alloc_skb returned NULL&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_device_locked
c_func
(paren
id|skb
)paren
)paren
id|skb_device_unlock
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skbn-&gt;sk
op_assign
id|skb-&gt;sk
suffix:semicolon
r_if
c_cond
(paren
id|skbn-&gt;sk
)paren
id|atomic_add
c_func
(paren
id|skbn-&gt;truesize
comma
op_amp
id|skbn-&gt;sk-&gt;wmem_alloc
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|skbn-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skbn-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|len
op_assign
(paren
id|mtu
OG
id|skb-&gt;len
)paren
ques
c_cond
id|skb-&gt;len
suffix:colon
id|mtu
suffix:semicolon
r_if
c_cond
(paren
id|ka9qfrag
op_eq
l_int|1
)paren
(brace
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
op_plus
l_int|2
)paren
suffix:semicolon
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
id|p
op_assign
id|skb_push
c_func
(paren
id|skbn
comma
l_int|2
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|AX25_P_SEGMENT
suffix:semicolon
op_star
id|p
op_assign
id|fragno
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
(brace
op_star
id|p
op_or_assign
id|SEG_FIRST
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
op_plus
l_int|1
)paren
suffix:semicolon
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
id|p
op_assign
id|skb_push
c_func
(paren
id|skbn
comma
l_int|1
)paren
suffix:semicolon
op_star
id|p
op_assign
id|AX25_P_TEXT
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;write_queue
comma
id|skbn
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
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
r_else
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
r_if
c_cond
(paren
id|ax25-&gt;state
op_eq
id|AX25_STATE_3
op_logical_or
id|ax25-&gt;state
op_eq
id|AX25_STATE_4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;dama_slave
)paren
multiline_comment|/* bke 960114: we aren&squot;t allowed to transmit */
id|ax25_kick
c_func
(paren
id|ax25
)paren
suffix:semicolon
multiline_comment|/* in DAMA mode unless we received a Poll */
)brace
)brace
multiline_comment|/* &n; *  This procedure is passed a buffer descriptor for an iframe. It builds&n; *  the rest of the control part of the frame and then writes it out.&n; */
DECL|function|ax25_send_iframe
r_static
r_void
id|ax25_send_iframe
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
id|ax25-&gt;modulus
op_eq
id|MODULUS
)paren
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
id|PF
suffix:colon
l_int|0
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|ax25-&gt;vs
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
id|ax25-&gt;vs
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
id|EPF
suffix:colon
l_int|0
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
id|ax25_transmit_buffer
c_func
(paren
id|ax25
comma
id|skb
comma
id|C_COMMAND
)paren
suffix:semicolon
)brace
DECL|function|ax25_kick
r_void
id|ax25_kick
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
id|ax25-&gt;timer
)paren
suffix:semicolon
id|start
op_assign
(paren
id|skb_peek
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|ax25-&gt;va
suffix:colon
id|ax25-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|ax25-&gt;va
op_plus
id|ax25-&gt;window
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25-&gt;condition
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
id|ax25-&gt;write_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|ax25-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Transmit data until either we&squot;re out of data to send or&n;&t;&t; * the window is full. Send a poll on the final I frame if&n;&t;&t; * the window is filled.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Dequeue the frame and copy it.&n;&t;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;write_queue
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
id|ax25-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|next
op_assign
(paren
id|ax25-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
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
id|ax25-&gt;write_queue
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
multiline_comment|/*&n;&t;&t;&t; * Transmit the frame copy.&n;&t;&t;&t; * bke 960114: do not set the Poll bit on the last frame&n;&t;&t;&t; * in DAMA mode.&n;&t;&t;&t; */
id|ax25_send_iframe
c_func
(paren
id|ax25
comma
id|skbn
comma
(paren
id|last
op_logical_and
op_logical_neg
id|ax25-&gt;dama_slave
)paren
ques
c_cond
id|POLLON
suffix:colon
id|POLLOFF
)paren
suffix:semicolon
id|ax25-&gt;vs
op_assign
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Requeue the original data frame.&n;&t;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
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
id|ax25-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|ax25-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;t1timer
op_eq
l_int|0
)paren
(brace
id|ax25-&gt;t3timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
)brace
id|ax25_set_timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|ax25_transmit_buffer
r_void
id|ax25_transmit_buffer
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
id|type
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;device
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
)paren
(brace
id|ax25-&gt;sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|ax25-&gt;sk-&gt;err
op_assign
id|ENETUNREACH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;sk-&gt;dead
)paren
id|ax25-&gt;sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
id|ax25-&gt;sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|size_ax25_addr
c_func
(paren
id|ax25-&gt;digipeat
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ax25_transmit_buffer: not enough room for digi-peaters&bslash;n&quot;
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
r_return
suffix:semicolon
)brace
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|size_ax25_addr
c_func
(paren
id|ax25-&gt;digipeat
)paren
)paren
suffix:semicolon
id|build_ax25_addr
c_func
(paren
id|ptr
comma
op_amp
id|ax25-&gt;source_addr
comma
op_amp
id|ax25-&gt;dest_addr
comma
id|ax25-&gt;digipeat
comma
id|type
comma
id|ax25-&gt;modulus
)paren
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|ax25_queue_xmit
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
multiline_comment|/*&n; * The following routines are taken from page 170 of the 7th ARRL Computer&n; * Networking Conference paper, as is the whole state machine.&n; */
DECL|function|ax25_nr_error_recovery
r_void
id|ax25_nr_error_recovery
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|ax25_establish_data_link
r_void
id|ax25_establish_data_link
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|ax25-&gt;n2count
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
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|SABM
comma
id|POLLON
comma
id|C_COMMAND
)paren
suffix:semicolon
)brace
r_else
(brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|SABME
comma
id|POLLON
comma
id|C_COMMAND
)paren
suffix:semicolon
)brace
id|ax25-&gt;t3timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t2timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|ax25_transmit_enquiry
r_void
id|ax25_transmit_enquiry
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
id|ax25-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RNR
comma
id|POLLON
comma
id|C_COMMAND
)paren
suffix:semicolon
r_else
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RR
comma
id|POLLON
comma
id|C_COMMAND
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|ax25_enquiry_response
r_void
id|ax25_enquiry_response
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
id|ax25-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RNR
comma
id|POLLON
comma
id|C_RESPONSE
)paren
suffix:semicolon
r_else
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RR
comma
id|POLLON
comma
id|C_RESPONSE
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
)brace
DECL|function|ax25_timeout_response
r_void
id|ax25_timeout_response
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
id|ax25-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RNR
comma
id|POLLOFF
comma
id|C_RESPONSE
)paren
suffix:semicolon
r_else
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|RR
comma
id|POLLOFF
comma
id|C_RESPONSE
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
)brace
DECL|function|ax25_check_iframes_acked
r_void
id|ax25_check_iframes_acked
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
r_if
c_cond
(paren
id|ax25-&gt;vs
op_eq
id|nr
)paren
(brace
id|ax25_frames_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
suffix:semicolon
id|ax25_calculate_rtt
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t3timer
op_assign
id|ax25-&gt;t3
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ax25-&gt;va
op_ne
id|nr
)paren
(brace
id|ax25_frames_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;dl1bke 960114: shouldn&squot;t ax25/dama_check_need_response reside as&n; *                static inline void ...() in ax25.h, should it? ;-)&n; */
DECL|function|ax25_check_need_response
r_void
id|ax25_check_need_response
c_func
(paren
id|ax25_cb
op_star
id|ax25
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
op_logical_neg
id|ax25-&gt;dama_slave
op_logical_and
id|type
op_eq
id|C_COMMAND
op_logical_and
id|pf
)paren
id|ax25_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;dl1bke 960114: transmit I frames on DAMA poll&n; */
DECL|function|dama_enquiry_response
r_void
id|dama_enquiry_response
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_cb
op_star
id|ax25o
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
)paren
)paren
(brace
id|ax25_requeue_frames
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_kick
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25-&gt;state
op_eq
id|AX25_STATE_2
op_logical_or
id|skb_peek
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|ax25_t1_timeout
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
id|ax25-&gt;t3timer
op_assign
id|ax25-&gt;t3
suffix:semicolon
multiline_comment|/* The FLEXNET DAMA master implementation refuses to send us ANY */
multiline_comment|/* I frame for this connection if we send a REJ here, probably   */
multiline_comment|/* due to it&squot;s frame collector scheme? A simple RR or  RNR will  */
multiline_comment|/* invoke the retransmission, and in fact REJs are superflous    */
multiline_comment|/* in DAMA mode anyway...&t;&t;&t;&t;&t; */
macro_line|#if 0
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|REJECT_CONDITION
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|REJ
comma
id|POLLOFF
comma
id|C_RESPONSE
)paren
suffix:semicolon
r_else
macro_line|#endif&t;
id|ax25_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
multiline_comment|/* Note that above response to the poll could be sent behind the  */
multiline_comment|/* transmissions of the other channels as well... This version    */
multiline_comment|/* gives better performance on FLEXNET nodes. (Why, Gunter?)&t;  */
r_for
c_loop
(paren
id|ax25o
op_assign
id|ax25_list
suffix:semicolon
id|ax25o
op_ne
l_int|NULL
suffix:semicolon
id|ax25o
op_assign
id|ax25o-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ax25o-&gt;device
op_ne
id|ax25-&gt;device
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25o-&gt;state
op_eq
id|AX25_STATE_2
)paren
(brace
id|ax25_t1_timeout
c_func
(paren
id|ax25o
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ax25o-&gt;dama_slave
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25o-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
)paren
op_logical_and
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_3
op_logical_or
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_4
op_logical_and
id|ax25o-&gt;t1timer
op_eq
l_int|0
)paren
)paren
)paren
(brace
id|ax25_requeue_frames
c_func
(paren
id|ax25o
)paren
suffix:semicolon
id|ax25_kick
c_func
(paren
id|ax25o
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25o-&gt;state
op_eq
id|AX25_STATE_2
op_logical_or
id|skb_peek
c_func
(paren
op_amp
id|ax25o-&gt;ack_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|ax25_t1_timeout
c_func
(paren
id|ax25o
)paren
suffix:semicolon
)brace
id|ax25o-&gt;t3timer
op_assign
id|ax25o-&gt;t3
suffix:semicolon
)brace
)brace
DECL|function|dama_check_need_response
r_void
id|dama_check_need_response
c_func
(paren
id|ax25_cb
op_star
id|ax25
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
id|ax25-&gt;dama_slave
op_logical_and
id|type
op_eq
id|C_COMMAND
op_logical_and
id|pf
)paren
id|dama_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|dama_establish_data_link
r_void
id|dama_establish_data_link
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t3timer
op_assign
id|ax25-&gt;t3
suffix:semicolon
id|ax25-&gt;t2timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
