multiline_comment|/*&n; *&t;NET/ROM release 006&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;NET/ROM 001&t;Jonathan(G4KLX)&t;Cloned from ax25_timer.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_NETROM) || defined(CONFIG_NETROM_MODULE)
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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
r_static
r_void
id|nr_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Linux set timer&n; */
DECL|function|nr_set_timer
r_void
id|nr_set_timer
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
id|nr_timer
suffix:semicolon
id|sk-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;NET/ROM TIMER &n; *&n; *&t;This routine is called every 100ms. Decrement timer by this&n; *&t;amount - if expired then process the event.&n; */
DECL|function|nr_timer
r_static
r_void
id|nr_timer
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
id|sk-&gt;protinfo.nr-&gt;state
)paren
(brace
r_case
id|NR_STATE_0
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
id|nr_destroy_socket
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
id|NR_STATE_3
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
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_OWN_RX_BUSY
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;vl
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_INFOACK
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Check for frames to transmit.&n;&t;&t;&t; */
id|nr_kick
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
id|sk-&gt;protinfo.nr-&gt;t2timer
OG
l_int|0
op_logical_and
op_decrement
id|sk-&gt;protinfo.nr-&gt;t2timer
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;state
op_eq
id|NR_STATE_3
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|NR_COND_ACK_PENDING
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
id|nr_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;t4timer
OG
l_int|0
op_logical_and
op_decrement
id|sk-&gt;protinfo.nr-&gt;t4timer
op_eq
l_int|0
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;t1timer
op_eq
l_int|0
op_logical_or
op_decrement
id|sk-&gt;protinfo.nr-&gt;t1timer
OG
l_int|0
)paren
(brace
id|nr_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;state
)paren
(brace
r_case
id|NR_STATE_1
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;n2count
op_eq
id|sk-&gt;protinfo.nr-&gt;n2
)paren
(brace
id|nr_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;state
op_assign
id|NR_STATE_0
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
)brace
r_else
(brace
id|sk-&gt;protinfo.nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_CONNREQ
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NR_STATE_2
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;n2count
op_eq
id|sk-&gt;protinfo.nr-&gt;n2
)paren
(brace
id|nr_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;state
op_assign
id|NR_STATE_0
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
)brace
r_else
(brace
id|sk-&gt;protinfo.nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_DISCREQ
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NR_STATE_3
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;n2count
op_eq
id|sk-&gt;protinfo.nr-&gt;n2
)paren
(brace
id|nr_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;state
op_assign
id|NR_STATE_0
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
)brace
r_else
(brace
id|sk-&gt;protinfo.nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_requeue_frames
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
id|sk-&gt;protinfo.nr-&gt;t1
suffix:semicolon
id|nr_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
