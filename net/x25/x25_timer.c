multiline_comment|/*&n; *&t;X.25 Packet Layer release 001&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;Started coding.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_X25) || defined(CONFIG_X25_MODULE)
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
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/x25.h&gt;
r_static
r_void
id|x25_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Linux set/reset timer routines&n; */
DECL|function|x25_set_timer
r_void
id|x25_set_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
r_int
id|flags
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
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sk-&gt;timer.next
op_assign
id|sk-&gt;timer.prev
op_assign
l_int|NULL
suffix:semicolon
id|sk-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|sk-&gt;timer.function
op_assign
op_amp
id|x25_timer
suffix:semicolon
id|sk-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|100
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_reset_timer
r_static
r_void
id|x25_reset_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
r_int
id|flags
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
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sk-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|sk-&gt;timer.function
op_assign
op_amp
id|x25_timer
suffix:semicolon
id|sk-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|100
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;X.25 TIMER &n; *&n; *&t;This routine is called every second. Decrement timer by this&n; *&t;amount - if expired then process the event.&n; */
DECL|function|x25_timer
r_static
r_void
id|x25_timer
c_func
(paren
r_int
r_int
id|param
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|sk-&gt;protinfo.x25-&gt;state
)paren
(brace
r_case
id|X25_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
id|sk-&gt;destroy
op_logical_or
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
op_logical_and
id|sk-&gt;dead
)paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|x25_destroy_socket
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_STATE_3
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Check for the state of the receive buffer.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
OL
(paren
id|sk-&gt;rcvbuf
op_div
l_int|2
)paren
op_logical_and
(paren
id|sk-&gt;protinfo.x25-&gt;condition
op_amp
id|X25_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|sk-&gt;protinfo.x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_OWN_RX_BUSY
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_ACK_PENDING
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;vl
op_assign
id|sk-&gt;protinfo.x25-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;timer
op_assign
l_int|0
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RR
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Check for frames to transmit.&n;&t;&t;&t; */
id|x25_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.x25-&gt;timer
op_eq
l_int|0
op_logical_or
op_decrement
id|sk-&gt;protinfo.x25-&gt;timer
OG
l_int|0
)paren
(brace
id|x25_reset_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Timer has expired, it may have been T2, T21, T22, or T23. We can tell&n;&t; * by the state machine state.&n;&t; */
r_switch
c_cond
(paren
id|sk-&gt;protinfo.x25-&gt;state
)paren
(brace
r_case
id|X25_STATE_3
suffix:colon
multiline_comment|/* T2 */
r_if
c_cond
(paren
id|sk-&gt;protinfo.x25-&gt;condition
op_amp
id|X25_COND_ACK_PENDING
)paren
(brace
id|sk-&gt;protinfo.x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_ACK_PENDING
suffix:semicolon
id|x25_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_STATE_1
suffix:colon
multiline_comment|/* T21 */
r_case
id|X25_STATE_4
suffix:colon
multiline_comment|/* T22 */
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_REQUEST
)paren
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;state
op_assign
id|X25_STATE_2
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;timer
op_assign
id|sk-&gt;protinfo.x25-&gt;t23
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_STATE_2
suffix:colon
multiline_comment|/* T23 */
id|x25_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.x25-&gt;state
op_assign
id|X25_STATE_0
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
id|ETIMEDOUT
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
)brace
id|x25_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
