multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Implementation of the Transmission Control Protocol(TCP).&n; *&n; * Version:&t;@(#)tcp.c&t;1.0.16&t;05/25/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Florian La Roche, &lt;flla@stud.uni-sb.de&gt;&n; *&t;&t;Charles Hedrick, &lt;hedrick@klinzhai.rutgers.edu&gt;&n; *&t;&t;Linus Torvalds, &lt;torvalds@cs.helsinki.fi&gt;&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&t;&t;Matthew Dillon, &lt;dillon@apollo.west.oic.com&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; */
macro_line|#include &lt;net/tcp.h&gt;
r_static
r_void
id|tcp_sltimer_handler
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|tcp_syn_recv_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|tcp_keepalive
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|variable|tcp_slow_timer
r_struct
id|timer_list
id|tcp_slow_timer
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|tcp_sltimer_handler
comma
)brace
suffix:semicolon
DECL|variable|tcp_slt_array
r_struct
id|tcp_sl_timer
id|tcp_slt_array
(braket
id|TCP_SLT_MAX
)braket
op_assign
(brace
(brace
l_int|0
comma
id|TCP_SYNACK_PERIOD
comma
l_int|0
comma
id|tcp_syn_recv_timer
)brace
comma
multiline_comment|/* SYNACK&t;*/
(brace
l_int|0
comma
id|TCP_KEEPALIVE_PERIOD
comma
l_int|0
comma
id|tcp_keepalive
)brace
multiline_comment|/* KEEPALIVE&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Using different timers for retransmit, delayed acks and probes&n; * We may wish use just one timer maintaining a list of expire jiffies &n; * to optimize.&n; */
DECL|function|tcp_init_xmit_timers
r_void
id|tcp_init_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|sk-&gt;tp_pinfo.af_tcp.retransmit_timer
)paren
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.retransmit_timer.function
op_assign
op_amp
id|tcp_retransmit_timer
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.retransmit_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|sk-&gt;tp_pinfo.af_tcp.delack_timer
)paren
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.delack_timer.function
op_assign
op_amp
id|tcp_delack_timer
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.delack_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|sk-&gt;tp_pinfo.af_tcp.probe_timer
)paren
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.probe_timer.function
op_assign
op_amp
id|tcp_probe_timer
suffix:semicolon
id|sk-&gt;tp_pinfo.af_tcp.probe_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Reset the retransmission timer&n; */
DECL|function|tcp_reset_xmit_timer
r_void
id|tcp_reset_xmit_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|what
comma
r_int
r_int
id|when
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|when
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;xmit_timer &lt;= 0 - timer:%d when:%lx&bslash;n&quot;
comma
id|what
comma
id|when
)paren
suffix:semicolon
id|when
op_assign
id|HZ
op_div
l_int|50
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|what
)paren
(brace
r_case
id|TIME_RETRANS
suffix:colon
multiline_comment|/*&n;&t;&t; * When seting the transmit timer the probe timer &n;&t;&t; * should not be set.&n;&t;&t; * The delayed ack timer can be set if we are changing the&n;&t;&t; * retransmit timer when removing acked frames.&n;&t;&t; */
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;probe_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
suffix:semicolon
id|tp-&gt;retransmit_timer.expires
op_assign
id|jiffies
op_plus
id|when
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_DACK
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
suffix:semicolon
id|tp-&gt;delack_timer.expires
op_assign
id|jiffies
op_plus
id|when
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_PROBE0
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;probe_timer
)paren
suffix:semicolon
id|tp-&gt;probe_timer.expires
op_assign
id|jiffies
op_plus
id|when
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tp-&gt;probe_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_WRITE
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bug: tcp_reset_xmit_timer TIME_WRITE&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bug: unknown timer value&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcp_clear_xmit_timer
r_void
id|tcp_clear_xmit_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|what
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_switch
c_cond
(paren
id|what
)paren
(brace
r_case
id|TIME_RETRANS
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_DACK
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_PROBE0
suffix:colon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;probe_timer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bug: unknown timer value&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcp_timer_is_set
r_int
id|tcp_timer_is_set
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|what
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_switch
c_cond
(paren
id|what
)paren
(brace
r_case
id|TIME_RETRANS
suffix:colon
r_return
id|tp-&gt;retransmit_timer.next
op_ne
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_DACK
suffix:colon
r_return
id|tp-&gt;delack_timer.next
op_ne
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIME_PROBE0
suffix:colon
r_return
id|tp-&gt;probe_timer.next
op_ne
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bug: unknown timer value&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcp_clear_xmit_timers
r_void
id|tcp_clear_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;retransmit_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;delack_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|tp-&gt;probe_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A write timeout has occurred. Process the after effects. BROKEN (badly)&n; */
DECL|function|tcp_write_timeout
r_static
r_int
id|tcp_write_timeout
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
multiline_comment|/*&n;&t; *&t;Look for a &squot;soft&squot; timeout.&n;&t; */
r_if
c_cond
(paren
(paren
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
op_logical_and
id|sk-&gt;retransmits
op_logical_and
op_logical_neg
(paren
id|sk-&gt;retransmits
op_amp
l_int|7
)paren
)paren
op_logical_or
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
op_logical_and
id|sk-&gt;retransmits
OG
id|TCP_RETR1
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Attempt to recover if arp has changed (unlikely!) or&n;&t;&t; *&t;a route has shifted (not supported prior to 1.3).&n;&t;&t; */
id|ip_rt_advice
c_func
(paren
op_amp
id|sk-&gt;ip_route_cache
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Have we tried to SYN too many times (repent repent 8))&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;retransmits
OG
id|TCP_SYN_RETRIES
op_logical_and
id|sk-&gt;state
op_eq
id|TCP_SYN_SENT
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;err_soft
)paren
(brace
id|sk-&gt;err
op_assign
id|sk-&gt;err_soft
suffix:semicolon
)brace
r_else
id|sk-&gt;err
op_assign
id|ETIMEDOUT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;syn timeout&bslash;n&quot;
)paren
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tcp_clear_xmit_timers
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tcp_statistics.TcpAttemptFails
op_increment
suffix:semicolon
multiline_comment|/* Is this right ??? - FIXME - */
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_CLOSE
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t FIN, we got nothing back */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Has it gone just too far ?&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;retransmits
OG
id|TCP_RETR2
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;err_soft
)paren
(brace
id|sk-&gt;err
op_assign
id|sk-&gt;err_soft
suffix:semicolon
)brace
r_else
id|sk-&gt;err
op_assign
id|ETIMEDOUT
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
id|tcp_clear_xmit_timers
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Time wait the socket &n;&t;&t; */
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_FIN_WAIT1
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_FIN_WAIT2
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_CLOSING
)paren
(brace
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_TIME_WAIT
)paren
suffix:semicolon
id|tcp_reset_msl_timer
(paren
id|sk
comma
id|TIME_CLOSE
comma
id|TCP_TIMEWAIT_LEN
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Clean up time.&n;&t;&t;&t; */
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_CLOSE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|tcp_delack_timer
r_void
id|tcp_delack_timer
c_func
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
r_if
c_cond
(paren
id|sk-&gt;zapped
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;delayed_acks
)paren
(brace
id|tcp_read_wakeup
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcp_probe_timer
r_void
id|tcp_probe_timer
c_func
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
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;zapped
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;users
)paren
(brace
multiline_comment|/* &n;&t;&t; * Try again in second &n;&t;&t; */
id|tcp_reset_xmit_timer
c_func
(paren
id|sk
comma
id|TIME_PROBE0
comma
id|HZ
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;*WARNING* RFC 1122 forbids this&n;&t; *&t;FIXME: We ought not to do it, Solaris 2.5 actually has fixing&n;&t; *&t;this behaviour in Solaris down as a bug fix. [AC]&n;&t; */
r_if
c_cond
(paren
id|tp-&gt;probes_out
OG
id|TCP_RETR2
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;err_soft
)paren
(brace
id|sk-&gt;err
op_assign
id|sk-&gt;err_soft
suffix:semicolon
)brace
r_else
id|sk-&gt;err
op_assign
id|ETIMEDOUT
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Time wait the socket &n;&t;&t; */
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_FIN_WAIT1
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_FIN_WAIT2
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_CLOSING
)paren
(brace
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_TIME_WAIT
)paren
suffix:semicolon
id|tcp_reset_msl_timer
(paren
id|sk
comma
id|TIME_CLOSE
comma
id|TCP_TIMEWAIT_LEN
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Clean up time.&n;&t;&t;&t; */
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_CLOSE
)paren
suffix:semicolon
)brace
)brace
id|tcp_send_probe0
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|tcp_keepopen_proc
r_static
id|__inline__
r_int
id|tcp_keepopen_proc
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
op_logical_or
id|sk-&gt;state
op_eq
id|TCP_CLOSE_WAIT
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
id|__u32
id|elapsed
op_assign
id|jiffies
op_minus
id|tp-&gt;rcv_tstamp
suffix:semicolon
r_if
c_cond
(paren
id|elapsed
op_ge
id|TCP_KEEPALIVE_TIME
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;probes_out
OG
id|TCP_KEEPALIVE_PROBES
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;err_soft
)paren
(brace
id|sk-&gt;err
op_assign
id|sk-&gt;err_soft
suffix:semicolon
)brace
r_else
id|sk-&gt;err
op_assign
id|ETIMEDOUT
suffix:semicolon
id|tcp_set_state
c_func
(paren
id|sk
comma
id|TCP_CLOSE
)paren
suffix:semicolon
)brace
r_else
(brace
id|tp-&gt;probes_out
op_increment
suffix:semicolon
id|tp-&gt;pending
op_assign
id|TIME_KEEPOPEN
suffix:semicolon
id|tcp_write_wakeup
c_func
(paren
id|sk
)paren
suffix:semicolon
id|res
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check all sockets for keepalive timer&n; *&t;Called every 75 seconds&n; *&t;This timer is started by af_inet init routine and is constantly&n; *&t;running.&n; *&n; *&t;It might be better to maintain a count of sockets that need it using&n; *&t;setsockopt/tcp_destroy_sk and only set the timer when needed.&n; */
multiline_comment|/*&n; *&t;don&squot;t send over 5 keepopens at a time to avoid burstiness &n; *&t;on big servers [AC]&n; */
DECL|macro|MAX_KA_PROBES
mdefine_line|#define MAX_KA_PROBES&t;5
DECL|function|tcp_keepalive
r_static
r_void
id|tcp_keepalive
c_func
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
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SOCK_ARRAY_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sk
op_assign
id|tcp_prot.sock_array
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;keepopen
)paren
(brace
id|count
op_add_assign
id|tcp_keepopen_proc
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
id|MAX_KA_PROBES
)paren
r_return
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;The TCP retransmit timer. This lacks a few small details.&n; *&n; *&t;1. &t;An initial rtt timeout on the probe0 should cause what we can&n; *&t;&t;of the first write queue buffer to be split and sent.&n; *&t;2.&t;On a &squot;major timeout&squot; as defined by RFC1122 we shouldn&squot;t report&n; *&t;&t;ETIMEDOUT if we know an additional &squot;soft&squot; error caused this.&n; *&t;&t;tcp_err should save a &squot;soft error&squot; for us.&n; *&t;[Unless someone has broken it then it does, except for one 2.0 &n; *&t;broken case of a send when the route/device is directly unreachable,&n; *&t;and we error but should retry! - FIXME] [AC]&n; */
DECL|function|tcp_retransmit_timer
r_void
id|tcp_retransmit_timer
c_func
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
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
multiline_comment|/*&n;&t; *&t;We are reset. We will send no more retransmits.&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;zapped
)paren
(brace
id|tcp_clear_xmit_timer
c_func
(paren
id|sk
comma
id|TIME_RETRANS
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Clear delay ack timer&n;&t; */
id|tcp_clear_xmit_timer
c_func
(paren
id|sk
comma
id|TIME_DACK
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Retransmission&n;&t; */
id|tp-&gt;retrans_head
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;retransmits
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &n;&t;&t; * remember window where we lost &n;&t;&t; * &quot;one half of the current window but at least 2 segments&quot;&n;&t;&t; */
id|sk-&gt;ssthresh
op_assign
id|max
c_func
(paren
id|sk-&gt;cong_window
op_rshift
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|sk-&gt;cong_count
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;cong_window
op_assign
l_int|1
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|sk-&gt;retransmits
)paren
suffix:semicolon
id|tcp_do_retransmit
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Increase the timeout each time we retransmit.  Note that&n;&t; * we do not increase the rtt estimate.  rto is initialized&n;&t; * from rtt, but increases here.  Jacobson (SIGCOMM 88) suggests&n;&t; * that doubling rto each time is the least we can get away with.&n;&t; * In KA9Q, Karn uses this for the first few times, and then&n;&t; * goes to quadratic.  netBSD doubles, but only goes up to *64,&n;&t; * and clamps at 1 to 64 sec afterwards.  Note that 120 sec is&n;&t; * defined in the protocol as the maximum possible RTT.  I guess&n;&t; * we&squot;ll have to use something other than TCP to talk to the&n;&t; * University of Mars.&n;&t; *&n;&t; * PAWS allows us longer timeouts and large windows, so once&n;&t; * implemented ftp to mars will work nicely. We will have to fix&n;&t; * the 120 second clamps though!&n;&t; */
id|tp-&gt;backoff
op_increment
suffix:semicolon
id|tp-&gt;rto
op_assign
id|min
c_func
(paren
id|tp-&gt;rto
op_lshift
l_int|1
comma
l_int|120
op_star
id|HZ
)paren
suffix:semicolon
id|tcp_reset_xmit_timer
c_func
(paren
id|sk
comma
id|TIME_RETRANS
comma
id|tp-&gt;rto
)paren
suffix:semicolon
id|tcp_write_timeout
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Slow timer for SYN-RECV sockets&n; */
DECL|function|tcp_syn_recv_timer
r_static
r_void
id|tcp_syn_recv_timer
c_func
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
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SOCK_ARRAY_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sk
op_assign
id|tcp_prot.sock_array
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|sk
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
op_logical_and
op_logical_neg
id|sk-&gt;users
op_logical_and
id|tp-&gt;syn_wait_queue
)paren
(brace
r_struct
id|open_request
op_star
id|req
suffix:semicolon
id|req
op_assign
id|tp-&gt;syn_wait_queue
suffix:semicolon
r_while
c_loop
(paren
id|tp-&gt;syn_wait_queue
op_logical_and
(paren
(paren
(paren
r_int
)paren
(paren
id|req-&gt;expires
op_minus
id|now
)paren
)paren
op_le
l_int|0
)paren
)paren
(brace
r_struct
id|open_request
op_star
id|conn
suffix:semicolon
id|conn
op_assign
id|req
suffix:semicolon
id|req
op_assign
id|req-&gt;dl_next
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;sk
op_logical_and
id|conn-&gt;sk-&gt;state
OG
id|TCP_SYN_RECV
)paren
r_continue
suffix:semicolon
id|tcp_synq_unlink
c_func
(paren
id|tp
comma
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;retrans
op_ge
id|TCP_RETR1
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;syn_recv: &quot;
l_string|&quot;too many retransmits&bslash;n&quot;
)paren
suffix:semicolon
(paren
op_star
id|conn
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|destructor
)paren
(paren
id|conn
)paren
suffix:semicolon
id|tcp_dec_slow_timer
c_func
(paren
id|TCP_SLT_SYNACK
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conn
)paren
suffix:semicolon
)brace
r_else
(brace
id|__u32
id|timeo
suffix:semicolon
(paren
op_star
id|conn
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|rtx_syn_ack
)paren
(paren
id|sk
comma
id|conn
)paren
suffix:semicolon
id|conn-&gt;retrans
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;syn_ack rtx %d&bslash;n&quot;
comma
id|conn-&gt;retrans
)paren
suffix:semicolon
id|timeo
op_assign
id|min
c_func
(paren
(paren
id|TCP_TIMEOUT_INIT
op_lshift
id|conn-&gt;retrans
)paren
comma
l_int|120
op_star
id|HZ
)paren
suffix:semicolon
id|conn-&gt;expires
op_assign
id|now
op_plus
id|timeo
suffix:semicolon
id|tcp_synq_queue
c_func
(paren
id|tp
comma
id|conn
)paren
suffix:semicolon
)brace
)brace
)brace
id|sk
op_assign
id|sk-&gt;next
suffix:semicolon
)brace
)brace
)brace
DECL|function|tcp_sltimer_handler
r_void
id|tcp_sltimer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|tcp_sl_timer
op_star
id|slt
op_assign
id|tcp_slt_array
suffix:semicolon
r_int
r_int
id|next
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TCP_SLT_MAX
suffix:semicolon
id|i
op_increment
comma
id|slt
op_increment
)paren
(brace
r_if
c_cond
(paren
id|slt-&gt;count
)paren
(brace
r_int
id|trigger
suffix:semicolon
id|trigger
op_assign
id|slt-&gt;period
op_minus
(paren
(paren
r_int
)paren
(paren
id|now
op_minus
id|slt-&gt;last
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trigger
op_le
l_int|0
)paren
(brace
(paren
op_star
id|slt-&gt;handler
)paren
(paren
(paren
r_int
r_int
)paren
id|slt
)paren
suffix:semicolon
id|slt-&gt;last
op_assign
id|now
suffix:semicolon
id|trigger
op_assign
id|slt-&gt;period
suffix:semicolon
)brace
id|next
op_assign
id|min
c_func
(paren
id|next
comma
id|trigger
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|next
op_ne
op_complement
l_int|0UL
)paren
(brace
id|tcp_slow_timer.expires
op_assign
id|now
op_plus
id|next
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tcp_slow_timer
)paren
suffix:semicolon
)brace
)brace
eof
