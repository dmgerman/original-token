multiline_comment|/*&n; *&t;LAPB release 002&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;LAPB 001&t;Jonathan Naylor&t;Started Coding&n; *&t;LAPB 002&t;Jonathan Naylor&t;New timer architecture.&n; */
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
r_static
r_void
id|lapb_t1timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|lapb_t2timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|lapb_start_t1timer
r_void
id|lapb_start_t1timer
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|lapb-&gt;t1timer
)paren
suffix:semicolon
id|lapb-&gt;t1timer.data
op_assign
(paren
r_int
r_int
)paren
id|lapb
suffix:semicolon
id|lapb-&gt;t1timer.function
op_assign
op_amp
id|lapb_t1timer_expiry
suffix:semicolon
id|lapb-&gt;t1timer.expires
op_assign
id|jiffies
op_plus
id|lapb-&gt;t1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|lapb-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|lapb_start_t2timer
r_void
id|lapb_start_t2timer
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|lapb-&gt;t2timer
)paren
suffix:semicolon
id|lapb-&gt;t2timer.data
op_assign
(paren
r_int
r_int
)paren
id|lapb
suffix:semicolon
id|lapb-&gt;t2timer.function
op_assign
op_amp
id|lapb_t2timer_expiry
suffix:semicolon
id|lapb-&gt;t2timer.expires
op_assign
id|jiffies
op_plus
id|lapb-&gt;t2
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|lapb-&gt;t2timer
)paren
suffix:semicolon
)brace
DECL|function|lapb_stop_t1timer
r_void
id|lapb_stop_t1timer
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|lapb-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|lapb_stop_t2timer
r_void
id|lapb_stop_t2timer
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|lapb-&gt;t2timer
)paren
suffix:semicolon
)brace
DECL|function|lapb_t1timer_running
r_int
id|lapb_t1timer_running
c_func
(paren
id|lapb_cb
op_star
id|lapb
)paren
(brace
r_return
id|timer_pending
c_func
(paren
op_amp
id|lapb-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|lapb_t2timer_expiry
r_static
r_void
id|lapb_t2timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|lapb_cb
op_star
id|lapb
op_assign
(paren
id|lapb_cb
op_star
)paren
id|param
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;condition
op_amp
id|LAPB_ACK_PENDING_CONDITION
)paren
(brace
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
id|lapb_timeout_response
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
)brace
DECL|function|lapb_t1timer_expiry
r_static
r_void
id|lapb_t1timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|lapb_cb
op_star
id|lapb
op_assign
(paren
id|lapb_cb
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|lapb-&gt;state
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;If we are a DCE, keep going DM .. DM .. DM&n;&t;&t; */
r_case
id|LAPB_STATE_0
suffix:colon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_DCE
)paren
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|LAPB_POLLOFF
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Awaiting connection state, send SABM(E), up to N2 times.&n;&t;&t; */
r_case
id|LAPB_STATE_1
suffix:colon
r_if
c_cond
(paren
id|lapb-&gt;n2count
op_eq
id|lapb-&gt;n2
)paren
(brace
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_TIMEDOUT
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;n2count
op_increment
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
l_string|&quot;lapb: (%p) S1 TX SABME(1)&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_SABME
comma
id|LAPB_POLLON
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
l_string|&quot;lapb: (%p) S1 TX SABM(1)&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_SABM
comma
id|LAPB_POLLON
comma
id|LAPB_COMMAND
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Awaiting disconnection state, send DISC, up to N2 times.&n;&t;&t; */
r_case
id|LAPB_STATE_2
suffix:colon
r_if
c_cond
(paren
id|lapb-&gt;n2count
op_eq
id|lapb-&gt;n2
)paren
(brace
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_disconnect_confirmation
c_func
(paren
id|lapb
comma
id|LAPB_TIMEDOUT
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;n2count
op_increment
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 TX DISC(1)&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DISC
comma
id|LAPB_POLLON
comma
id|LAPB_COMMAND
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Data transfer state, restransmit I frames, up to N2 times.&n;&t;&t; */
r_case
id|LAPB_STATE_3
suffix:colon
r_if
c_cond
(paren
id|lapb-&gt;n2count
op_eq
id|lapb-&gt;n2
)paren
(brace
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_TIMEDOUT
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;n2count
op_increment
suffix:semicolon
id|lapb_requeue_frames
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Frame reject state, restransmit FRMR frames, up to N2 times.&n;&t;&t; */
r_case
id|LAPB_STATE_4
suffix:colon
r_if
c_cond
(paren
id|lapb-&gt;n2count
op_eq
id|lapb-&gt;n2
)paren
(brace
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_TIMEDOUT
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;token
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;n2count
op_increment
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
