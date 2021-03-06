multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Cloned from ax25_in.c&n; *&t;&t;&t;Joerg(DL1BKE)&t;Fixed it.&n; *&t;AX.25 037&t;Jonathan(G4KLX)&t;New timer architecture.&n; *&t;&t;&t;Joerg(DL1BKE)&t;ax25-&gt;n2count never got reset&n; */
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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; *&t;State machine for state 1, Awaiting Connection State.&n; *&t;The handling of the timer(s) is in file ax25_ds_timer.c.&n; *&t;Handling of state 0 and connection release is in ax25.c.&n; */
DECL|function|ax25_ds_state1_machine
r_static
r_int
id|ax25_ds_state1_machine
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
id|frametype
comma
r_int
id|pf
comma
r_int
id|type
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|AX25_SABM
suffix:colon
id|ax25-&gt;modulus
op_assign
id|AX25_MODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_WINDOW
)braket
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_SABME
suffix:colon
id|ax25-&gt;modulus
op_assign
id|AX25_EMODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_EWINDOW
)braket
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DISC
suffix:colon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DM
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_UA
suffix:colon
id|ax25_calculate_rtt
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_stop_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_3
suffix:semicolon
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
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
id|TCP_ESTABLISHED
suffix:semicolon
multiline_comment|/* For WAIT_SABM connections we will produce an accept ready socket here */
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
)brace
id|ax25_dama_on
c_func
(paren
id|ax25
)paren
suffix:semicolon
multiline_comment|/* according to DK4EG&#xfffd;s spec we are required to&n;&t;&t;&t; * send a RR RESPONSE FINAL NR=0. &n;&t;&t;&t; */
id|ax25_std_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DM
suffix:colon
r_if
c_cond
(paren
id|pf
)paren
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ECONNREFUSED
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|pf
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_SABM
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 2, Awaiting Release State.&n; *&t;The handling of the timer(s) is in file ax25_ds_timer.c&n; *&t;Handling of state 0 and connection release is in ax25.c.&n; */
DECL|function|ax25_ds_state2_machine
r_static
r_int
id|ax25_ds_state2_machine
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
id|frametype
comma
r_int
id|pf
comma
r_int
id|type
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|AX25_SABM
suffix:colon
r_case
id|AX25_SABME
suffix:colon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DISC
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DISC
suffix:colon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DM
suffix:colon
r_case
id|AX25_UA
suffix:colon
r_if
c_cond
(paren
id|pf
)paren
(brace
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_I
suffix:colon
r_case
id|AX25_REJ
suffix:colon
r_case
id|AX25_RNR
suffix:colon
r_case
id|AX25_RR
suffix:colon
r_if
c_cond
(paren
id|pf
)paren
(brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DISC
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 3, Connected State.&n; *&t;The handling of the timer(s) is in file ax25_timer.c&n; *&t;Handling of state 0 and connection release is in ax25.c.&n; */
DECL|function|ax25_ds_state3_machine
r_static
r_int
id|ax25_ds_state3_machine
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
id|frametype
comma
r_int
id|ns
comma
r_int
id|nr
comma
r_int
id|pf
comma
r_int
id|type
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
id|AX25_SABM
suffix:colon
r_case
id|AX25_SABME
suffix:colon
r_if
c_cond
(paren
id|frametype
op_eq
id|AX25_SABM
)paren
(brace
id|ax25-&gt;modulus
op_assign
id|AX25_MODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_WINDOW
)braket
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;modulus
op_assign
id|AX25_EMODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_EWINDOW
)braket
suffix:semicolon
)brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
id|ax25_stop_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|ax25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|ax25_requeue_frames
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_dama_on
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DISC
suffix:colon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_UA
comma
id|pf
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_DM
suffix:colon
id|ax25_dama_off
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ECONNRESET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_RR
suffix:colon
r_case
id|AX25_RNR
suffix:colon
r_if
c_cond
(paren
id|frametype
op_eq
id|AX25_RR
)paren
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_PEER_RX_BUSY
suffix:semicolon
r_else
id|ax25-&gt;condition
op_or_assign
id|AX25_COND_PEER_RX_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|ax25_validate_nr
c_func
(paren
id|ax25
comma
id|nr
)paren
)paren
(brace
r_if
c_cond
(paren
id|ax25_check_iframes_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
)paren
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|AX25_COMMAND
op_logical_and
id|pf
)paren
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_else
(brace
id|ax25_ds_nr_error_recovery
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_REJ
suffix:colon
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_PEER_RX_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|ax25_validate_nr
c_func
(paren
id|ax25
comma
id|nr
)paren
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;va
op_ne
id|nr
)paren
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
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
id|ax25_stop_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_requeue_frames
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|AX25_COMMAND
op_logical_and
id|pf
)paren
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_else
(brace
id|ax25_ds_nr_error_recovery
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_I
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ax25_validate_nr
c_func
(paren
id|ax25
comma
id|nr
)paren
)paren
(brace
id|ax25_ds_nr_error_recovery
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_PEER_RX_BUSY
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
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ax25_check_iframes_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
)paren
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_OWN_RX_BUSY
)paren
(brace
r_if
c_cond
(paren
id|pf
)paren
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ns
op_eq
id|ax25-&gt;vr
)paren
(brace
id|ax25-&gt;vr
op_assign
(paren
id|ax25-&gt;vr
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
id|queued
op_assign
id|ax25_rx_iframe
c_func
(paren
id|ax25
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_OWN_RX_BUSY
)paren
id|ax25-&gt;vr
op_assign
id|ns
suffix:semicolon
multiline_comment|/* ax25-&gt;vr - 1 */
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_REJECT
suffix:semicolon
r_if
c_cond
(paren
id|pf
)paren
(brace
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_ACK_PENDING
)paren
)paren
(brace
id|ax25-&gt;condition
op_or_assign
id|AX25_COND_ACK_PENDING
suffix:semicolon
id|ax25_start_t2timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_REJECT
)paren
(brace
r_if
c_cond
(paren
id|pf
)paren
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;condition
op_or_assign
id|AX25_COND_REJECT
suffix:semicolon
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_ACK_PENDING
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|AX25_FRMR
suffix:colon
r_case
id|AX25_ILLEGAL
suffix:colon
id|ax25_ds_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|queued
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Higher level upcall for a LAPB frame&n; */
DECL|function|ax25_ds_frame_in
r_int
id|ax25_ds_frame_in
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
id|pf
suffix:semicolon
id|frametype
op_assign
id|ax25_decode
c_func
(paren
id|ax25
comma
id|skb
comma
op_amp
id|ns
comma
op_amp
id|nr
comma
op_amp
id|pf
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;state
)paren
(brace
r_case
id|AX25_STATE_1
suffix:colon
id|queued
op_assign
id|ax25_ds_state1_machine
c_func
(paren
id|ax25
comma
id|skb
comma
id|frametype
comma
id|pf
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_STATE_2
suffix:colon
id|queued
op_assign
id|ax25_ds_state2_machine
c_func
(paren
id|ax25
comma
id|skb
comma
id|frametype
comma
id|pf
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_STATE_3
suffix:colon
id|queued
op_assign
id|ax25_ds_state3_machine
c_func
(paren
id|ax25
comma
id|skb
comma
id|frametype
comma
id|ns
comma
id|nr
comma
id|pf
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|queued
suffix:semicolon
)brace
eof
