multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;TIMER - implementation of software timers for IP.&n; *&n; * Version:&t;$Id: timer.c,v 1.14 1998/11/07 11:55:43 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;&n; *&t;&t;Florian La Roche, &lt;flla@stud.uni-sb.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;To avoid destroying a wait queue as we use it&n; *&t;&t;&t;&t;&t;we defer destruction until the destroy timer goes&n; *&t;&t;&t;&t;&t;off.&n; *&t;&t;Alan Cox&t;:&t;Destroy socket doesn&squot;t write a status value to the&n; *&t;&t;&t;&t;&t;socket buffer _AFTER_ freeing it! Also sock ensures&n; *&t;&t;&t;&t;&t;the socket will get removed BEFORE this is called&n; *&t;&t;&t;&t;&t;otherwise if the timer TIME_DESTROY occurs inside&n; *&t;&t;&t;&t;&t;of inet_bh() with this socket being handled it goes&n; *&t;&t;&t;&t;&t;BOOM! Have to stop timer going off if net_bh is&n; *&t;&t;&t;&t;&t;active or the destroy causes crashes.&n; *&t;&t;Alan Cox&t;:&t;Cleaned up unused code.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/arp.h&gt;
DECL|function|net_delete_timer
r_void
id|net_delete_timer
(paren
r_struct
id|sock
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;timer.prev
)paren
(brace
id|del_timer
(paren
op_amp
id|t-&gt;timer
)paren
suffix:semicolon
)brace
id|t-&gt;timeout
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|net_reset_timer
r_void
id|net_reset_timer
(paren
r_struct
id|sock
op_star
id|t
comma
r_int
id|timeout
comma
r_int
r_int
id|len
)paren
(brace
id|t-&gt;timeout
op_assign
id|timeout
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|t-&gt;timer
comma
id|jiffies
op_plus
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we will only be called whenever we need to do&n; * something, but we must be sure to process all of the&n; * sockets that need it.&n; */
DECL|function|net_timer
r_void
id|net_timer
(paren
r_int
r_int
id|data
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
id|data
suffix:semicolon
r_int
id|why
op_assign
id|sk-&gt;timeout
suffix:semicolon
multiline_comment|/* Only process if socket is not in use. */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sock_readers
)paren
)paren
(brace
multiline_comment|/* Try again later. */
id|sk-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|20
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Always see if we need to send an ack. */
r_if
c_cond
(paren
id|sk-&gt;tp_pinfo.af_tcp.delayed_acks
op_logical_and
op_logical_neg
id|sk-&gt;zapped
)paren
(brace
id|sk-&gt;prot-&gt;read_wakeup
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we need to figure out why the socket was on the timer. */
r_switch
c_cond
(paren
id|why
)paren
(brace
r_case
id|TIME_DONE
suffix:colon
multiline_comment|/* If the socket hasn&squot;t been closed off, re-try a bit later. */
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
(brace
id|net_reset_timer
c_func
(paren
id|sk
comma
id|TIME_DONE
comma
id|TCP_DONE_TIME
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSE
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;non CLOSE socket in time_done&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|destroy_sock
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_DESTROY
suffix:colon
multiline_comment|/* We&squot;ve waited for a while for all the memory associated with&n;&t;&t;&t; * the socket to be freed.&n;&t;&t;&t; */
id|destroy_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_CLOSE
suffix:colon
multiline_comment|/* We&squot;ve waited long enough, close the socket. */
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_CLOSE
)paren
suffix:semicolon
id|sk-&gt;shutdown
op_assign
id|SHUTDOWN_MASK
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
id|net_reset_timer
(paren
id|sk
comma
id|TIME_DONE
comma
id|TCP_DONE_TIME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* I want to see these... */
id|printk
(paren
l_string|&quot;net_timer: timer expired - reason %d is unknown&bslash;n&quot;
comma
id|why
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof
