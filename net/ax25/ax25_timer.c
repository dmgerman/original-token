multiline_comment|/*&n; *&t;AX.25 release 036&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;AX.25 028a&t;Jonathan(G4KLX)&t;New state machine based on SDL diagrams.&n; *&t;AX.25 028b&t;Jonathan(G4KLX)&t;Extracted AX25 control block from the&n; *&t;&t;&t;&t;&t;sock structure.&n; *&t;AX.25 029&t;Alan(GW4PTS)&t;Switched to KA9Q constant names.&n; *&t;AX.25 031&t;Joerg(DL1BKE)&t;Added DAMA support&n; *&t;AX.25 032&t;Joerg(DL1BKE)&t;Fixed DAMA timeout bug&n; *&t;AX.25 033&t;Jonathan(G4KLX)&t;Modularisation functions.&n; *&t;AX.25 035&t;Frederic(F1OAT)&t;Support for pseudo-digipeating.&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split Standard and DAMA code into seperate files.&n; *&t;&t;&t;Joerg(DL1BKE)&t;Fixed DAMA Slave. We are *required* to start with&n; *&t;&t;&t;&t;&t;standard AX.25 mode.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
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
id|ax25_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Linux set timer&n; */
DECL|function|ax25_set_timer
r_void
id|ax25_set_timer
c_func
(paren
id|ax25_cb
op_star
id|ax25
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
id|ax25-&gt;timer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
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
id|ax25_timer
suffix:semicolon
id|ax25-&gt;timer.expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ax25-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;AX.25 TIMER &n; *&n; *&t;This routine is called every 100ms. Decrement timer by this&n; *&t;amount - if expired then process the event.&n; */
DECL|function|ax25_timer
r_static
r_void
id|ax25_timer
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
id|ax25_std_timer
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
id|ax25_ds_timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25_std_timer
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
macro_line|#endif
eof
