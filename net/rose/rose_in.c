multiline_comment|/*&n; *&t;Rose release 001&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.0 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;Rose 001&t;Jonathan(G4KLX)&t;Cloned from nr_in.c&n; */
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
macro_line|#include &lt;net/ip.h&gt;&t;&t;&t;/* For ip_rcv */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/rose.h&gt;
DECL|function|rose_queue_rx_frame
r_static
r_int
id|rose_queue_rx_frame
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
comma
r_int
id|more
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbo
comma
op_star
id|skbn
op_assign
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|more
)paren
(brace
id|sk-&gt;protinfo.rose-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;frag_queue
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|more
op_logical_and
id|sk-&gt;protinfo.rose-&gt;fraglen
OG
l_int|0
)paren
(brace
multiline_comment|/* End of fragment */
id|sk-&gt;protinfo.rose-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;frag_queue
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|alloc_skb
c_func
(paren
id|sk-&gt;protinfo.rose-&gt;fraglen
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|skbn-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb_set_owner_r
c_func
(paren
id|skbn
comma
id|sk
)paren
suffix:semicolon
id|skbn-&gt;h.raw
op_assign
id|skbn-&gt;data
suffix:semicolon
id|skbo
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;frag_queue
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
id|skbo-&gt;len
)paren
comma
id|skbo-&gt;data
comma
id|skbo-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skbo
comma
id|FREE_READ
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skbo
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;protinfo.rose-&gt;frag_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb_pull
c_func
(paren
id|skbo
comma
id|ROSE_MIN_LEN
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
id|skbo-&gt;len
)paren
comma
id|skbo-&gt;data
comma
id|skbo-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skbo
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
id|sk-&gt;protinfo.rose-&gt;fraglen
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 1, Awaiting Call Accepted State.&n; * The handling of the timer(s) is in file rose_timer.c.&n; * Handling of state 0 and connection release is in af_rose.c.&n; */
DECL|function|rose_state1_machine
r_static
r_int
id|rose_state1_machine
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
comma
r_int
id|frametype
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_CALL_ACCEPTED
suffix:colon
id|sk-&gt;protinfo.rose-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;va
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_3
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_0
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
id|ECONNREFUSED
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* XXX */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;rose: unknown %02X in state 1&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 2, Awaiting Clear Confirmation State.&n; * The handling of the timer(s) is in file rose_timer.c&n; * Handling of state 0 and connection release is in af_rose.c.&n; */
DECL|function|rose_state2_machine
r_static
r_int
id|rose_state2_machine
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
comma
r_int
id|frametype
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
r_case
id|ROSE_CLEAR_CONFIRMATION
suffix:colon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_0
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* XXX */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;rose: unknown %02X in state 2&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 3, Connected State.&n; * The handling of the timer(s) is in file rose_timer.c&n; * Handling of state 0 and connection release is in af_rose.c.&n; */
DECL|function|rose_state3_machine
r_static
r_int
id|rose_state3_machine
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
comma
r_int
id|frametype
comma
r_int
id|ns
comma
r_int
id|nr
comma
r_int
id|q
comma
r_int
id|d
comma
r_int
id|m
)paren
(brace
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_RESET_REQUEST
suffix:colon
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RESET_CONFIRMATION
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;va
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_0
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_RR
suffix:colon
r_case
id|ROSE_RNR
suffix:colon
r_if
c_cond
(paren
id|frametype
op_eq
id|ROSE_RNR
)paren
(brace
id|sk-&gt;protinfo.rose-&gt;condition
op_or_assign
id|PEER_RX_BUSY_CONDITION
suffix:semicolon
)brace
r_else
(brace
id|sk-&gt;protinfo.rose-&gt;condition
op_and_assign
op_complement
id|PEER_RX_BUSY_CONDITION
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rose_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RESET_REQUEST
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;va
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_4
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
id|sk-&gt;protinfo.rose-&gt;t2
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
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
id|rose_check_iframes_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ROSE_DATA
suffix:colon
multiline_comment|/* XXX */
id|sk-&gt;protinfo.rose-&gt;condition
op_and_assign
op_complement
id|PEER_RX_BUSY_CONDITION
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RESET_REQUEST
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;va
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_4
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
id|sk-&gt;protinfo.rose-&gt;t2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
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
id|rose_check_iframes_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ns
op_eq
id|sk-&gt;protinfo.rose-&gt;vr
)paren
(brace
r_if
c_cond
(paren
id|rose_queue_rx_frame
c_func
(paren
id|sk
comma
id|skb
comma
id|m
)paren
op_eq
l_int|0
)paren
(brace
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
(paren
id|sk-&gt;protinfo.rose-&gt;vr
op_plus
l_int|1
)paren
op_mod
id|ROSE_MODULUS
suffix:semicolon
id|queued
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|sk-&gt;protinfo.rose-&gt;condition
op_or_assign
id|OWN_RX_BUSY_CONDITION
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t; * If the window is full, ack the frame, else start the&n;&t;&t;&t; * acknowledge hold back timer.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|sk-&gt;protinfo.rose-&gt;vl
op_plus
id|ROSE_DEFAULT_WINDOW
)paren
op_mod
id|ROSE_MODULUS
)paren
op_eq
id|sk-&gt;protinfo.rose-&gt;vr
)paren
(brace
id|sk-&gt;protinfo.rose-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|rose_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|sk-&gt;protinfo.rose-&gt;condition
op_or_assign
id|ACK_PENDING_CONDITION
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
id|sk-&gt;protinfo.rose-&gt;hb
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;rose: unknown %02X in state 3&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|queued
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 4, Awaiting Reset Confirmation State.&n; * The handling of the timer(s) is in file rose_timer.c&n; * Handling of state 0 and connection release is in af_rose.c.&n; */
DECL|function|rose_state4_machine
r_static
r_int
id|rose_state4_machine
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
comma
r_int
id|frametype
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_RESET_CONFIRMATION
suffix:colon
r_case
id|ROSE_RESET_REQUEST
suffix:colon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;va
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.rose-&gt;state
op_assign
id|ROSE_STATE_0
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* XXX */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;rose: unknown %02X in state 4&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Higher level upcall for a LAPB frame */
DECL|function|rose_process_rx_frame
r_int
id|rose_process_rx_frame
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
r_int
id|queued
op_assign
l_int|0
comma
id|frametype
comma
id|ns
comma
id|nr
comma
id|q
comma
id|d
comma
id|m
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;state
op_eq
id|ROSE_STATE_0
)paren
r_return
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|frametype
op_assign
id|rose_decode
c_func
(paren
id|skb
comma
op_amp
id|ns
comma
op_amp
id|nr
comma
op_amp
id|q
comma
op_amp
id|d
comma
op_amp
id|m
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sk-&gt;protinfo.rose-&gt;state
)paren
(brace
r_case
id|ROSE_STATE_1
suffix:colon
id|queued
op_assign
id|rose_state1_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_STATE_2
suffix:colon
id|queued
op_assign
id|rose_state2_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_STATE_3
suffix:colon
id|queued
op_assign
id|rose_state3_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
comma
id|ns
comma
id|nr
comma
id|q
comma
id|d
comma
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_STATE_4
suffix:colon
id|queued
op_assign
id|rose_state4_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rose_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|queued
suffix:semicolon
)brace
macro_line|#endif
eof