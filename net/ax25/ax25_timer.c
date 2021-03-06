multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;AX.25 028a&t;Jonathan(G4KLX)&t;New state machine based on SDL diagrams.&n; *&t;AX.25 028b&t;Jonathan(G4KLX)&t;Extracted AX25 control block from the&n; *&t;&t;&t;&t;&t;sock structure.&n; *&t;AX.25 029&t;Alan(GW4PTS)&t;Switched to KA9Q constant names.&n; *&t;AX.25 031&t;Joerg(DL1BKE)&t;Added DAMA support&n; *&t;AX.25 032&t;Joerg(DL1BKE)&t;Fixed DAMA timeout bug&n; *&t;AX.25 033&t;Jonathan(G4KLX)&t;Modularisation functions.&n; *&t;AX.25 035&t;Frederic(F1OAT)&t;Support for pseudo-digipeating.&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split Standard and DAMA code into separate files.&n; *&t;&t;&t;Joerg(DL1BKE)&t;Fixed DAMA Slave. We are *required* to start with&n; *&t;&t;&t;&t;&t;standard AX.25 mode.&n; *&t;AX.25 037&t;Jonathan(G4KLX)&t;New timer architecture.&n; *                      Tomi(OH2BNS)    Fixed heartbeat expiry (check ax25_dev).&n; */
macro_line|#include &lt;linux/config.h&gt;
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
r_static
r_void
id|ax25_heartbeat_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|ax25_t1timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|ax25_t2timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|ax25_t3timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|ax25_idletimer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|ax25_start_heartbeat
r_void
id|ax25_start_heartbeat
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;timer
)paren
suffix:semicolon
id|ax25-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25
suffix:semicolon
id|ax25-&gt;timer.function
op_assign
op_amp
id|ax25_heartbeat_expiry
suffix:semicolon
id|ax25-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_start_t1timer
r_void
id|ax25_start_t1timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t1timer
)paren
suffix:semicolon
id|ax25-&gt;t1timer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25
suffix:semicolon
id|ax25-&gt;t1timer.function
op_assign
op_amp
id|ax25_t1timer_expiry
suffix:semicolon
id|ax25-&gt;t1timer.expires
op_assign
id|jiffies
op_plus
id|ax25-&gt;t1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_start_t2timer
r_void
id|ax25_start_t2timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t2timer
)paren
suffix:semicolon
id|ax25-&gt;t2timer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25
suffix:semicolon
id|ax25-&gt;t2timer.function
op_assign
op_amp
id|ax25_t2timer_expiry
suffix:semicolon
id|ax25-&gt;t2timer.expires
op_assign
id|jiffies
op_plus
id|ax25-&gt;t2
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;t2timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_start_t3timer
r_void
id|ax25_start_t3timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t3timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;t3
OG
l_int|0
)paren
(brace
id|ax25-&gt;t3timer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25
suffix:semicolon
id|ax25-&gt;t3timer.function
op_assign
op_amp
id|ax25_t3timer_expiry
suffix:semicolon
id|ax25-&gt;t3timer.expires
op_assign
id|jiffies
op_plus
id|ax25-&gt;t3
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;t3timer
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_start_idletimer
r_void
id|ax25_start_idletimer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;idletimer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;idle
OG
l_int|0
)paren
(brace
id|ax25-&gt;idletimer.data
op_assign
(paren
r_int
r_int
)paren
id|ax25
suffix:semicolon
id|ax25-&gt;idletimer.function
op_assign
op_amp
id|ax25_idletimer_expiry
suffix:semicolon
id|ax25-&gt;idletimer.expires
op_assign
id|jiffies
op_plus
id|ax25-&gt;idle
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;idletimer
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_stop_heartbeat
r_void
id|ax25_stop_heartbeat
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_stop_t1timer
r_void
id|ax25_stop_t1timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_stop_t2timer
r_void
id|ax25_stop_t2timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t2timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_stop_t3timer
r_void
id|ax25_stop_t3timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;t3timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_stop_idletimer
r_void
id|ax25_stop_idletimer
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ax25-&gt;idletimer
)paren
suffix:semicolon
)brace
DECL|function|ax25_t1timer_running
r_int
id|ax25_t1timer_running
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_return
id|timer_pending
c_func
(paren
op_amp
id|ax25-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|ax25_display_timer
r_int
r_int
id|ax25_display_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
id|timer
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|timer-&gt;expires
op_minus
id|jiffies
suffix:semicolon
)brace
DECL|function|ax25_heartbeat_expiry
r_static
r_void
id|ax25_heartbeat_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|ax25_cb
op_star
id|ax25
op_assign
(paren
id|ax25_cb
op_star
)paren
id|param
suffix:semicolon
r_int
id|proto
op_assign
id|AX25_PROTO_STD_SIMPLEX
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev
)paren
id|proto
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|proto
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_heartbeat_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_ds_heartbeat_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25_std_heartbeat_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|ax25_t1timer_expiry
r_static
r_void
id|ax25_t1timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|ax25_cb
op_star
id|ax25
op_assign
(paren
id|ax25_cb
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_t1timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_std_t1timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|ax25_t2timer_expiry
r_static
r_void
id|ax25_t2timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|ax25_cb
op_star
id|ax25
op_assign
(paren
id|ax25_cb
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_t2timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_std_t2timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|ax25_t3timer_expiry
r_static
r_void
id|ax25_t3timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|ax25_cb
op_star
id|ax25
op_assign
(paren
id|ax25_cb
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_t3timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_ds_t3timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25_std_t3timer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|ax25_idletimer_expiry
r_static
r_void
id|ax25_idletimer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|ax25_cb
op_star
id|ax25
op_assign
(paren
id|ax25_cb
op_star
)paren
id|param
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_idletimer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_ds_idletimer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25_std_idletimer_expiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
eof
