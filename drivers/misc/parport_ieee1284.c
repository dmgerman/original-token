multiline_comment|/* $Id: parport_ieee1284.c,v 1.4 1997/10/19 21:37:21 philip Exp $&n; * IEEE-1284 implementation for parport.&n; *&n; * Authors: Phil Blundell &lt;Philip.Blundell@pobox.com&gt;&n; *          Carsten Gross &lt;carsten@sol.wohnheim.uni-ulm.de&gt;&n; *&t;    Jose Renau &lt;renau@acm.org&gt;&n; */
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* Wait for Status line(s) to change in 35 ms - see IEEE1284-1994 page 24 to&n; * 25 for this. After this time we can create a timeout because the&n; * peripheral doesn&squot;t conform to IEEE1284.  We want to save CPU time: we are&n; * waiting a maximum time of 500 us busy (this is for speed).  If there is&n; * not the right answer in this time, we call schedule and other processes&n; * are able to eat the time up to 40ms.&n; */
DECL|function|parport_wait_peripheral
r_int
id|parport_wait_peripheral
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|result
)paren
(brace
r_int
id|counter
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_for
c_loop
(paren
id|counter
op_assign
l_int|0
suffix:semicolon
id|counter
OL
l_int|20
suffix:semicolon
id|counter
op_increment
)paren
(brace
id|status
op_assign
id|parport_read_status
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|mask
)paren
op_eq
id|result
)paren
r_return
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
l_int|25
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resched_needed
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
l_int|4
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait for 40ms */
id|status
op_assign
id|parport_read_status
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
(paren
(paren
id|status
op_amp
id|mask
)paren
op_eq
id|result
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Test if the peripheral is IEEE 1284 compliant.&n; * return values are:&n; *   0 - handshake failed; peripheral is not compliant (or none present)&n; *   1 - handshake OK; IEEE1284 peripheral present but no data available&n; *   2 - handshake OK; IEEE1284 peripheral and data available&n; */
DECL|function|parport_ieee1284_nibble_mode_ok
r_int
id|parport_ieee1284_nibble_mode_ok
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mode
)paren
(brace
id|parport_write_data
c_func
(paren
id|port
comma
id|mode
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
multiline_comment|/* nSelectIn high, nAutoFd low */
id|parport_write_control
c_func
(paren
id|port
comma
(paren
id|parport_read_control
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|8
)paren
op_or
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parport_wait_peripheral
c_func
(paren
id|port
comma
l_int|0x78
comma
l_int|0x38
)paren
)paren
(brace
id|parport_write_control
c_func
(paren
id|port
comma
(paren
id|parport_read_control
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|2
)paren
op_or
l_int|8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* nStrobe low */
id|parport_write_control
c_func
(paren
id|port
comma
id|parport_read_control
c_func
(paren
id|port
)paren
op_or
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Strobe wait */
multiline_comment|/* nStrobe high */
id|parport_write_control
c_func
(paren
id|port
comma
id|parport_read_control
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* nAutoFd low */
id|parport_write_control
c_func
(paren
id|port
comma
id|parport_read_control
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|2
)paren
suffix:semicolon
r_return
(paren
id|parport_wait_peripheral
c_func
(paren
id|port
comma
l_int|0x20
comma
l_int|0
)paren
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
)brace
eof
