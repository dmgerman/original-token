multiline_comment|/*&n; *&t;AX.25 release 036&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Cloned from ax25_out.c and ax25_subr.c.&n; *&t;&t;&t;Joerg(DL1BKE)&t;Changed ax25_ds_enquiry_response(),&n; *&t;&t;&t;&t;&t;fixed ax25_dama_on() and ax25_dama_off().&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_AX25_DAMA_SLAVE)
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
DECL|function|ax25_ds_nr_error_recovery
r_void
id|ax25_ds_nr_error_recovery
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_ds_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;dl1bke 960114: transmit I frames on DAMA poll&n; */
DECL|function|ax25_ds_enquiry_response
r_void
id|ax25_ds_enquiry_response
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_cb
op_star
id|ax25o
suffix:semicolon
multiline_comment|/* Please note that neither DK4EG&#xfffd;s nor DG2FEF&#xfffd;s&n;&t; * DAMA spec mention the following behaviour as seen&n;&t; * with TheFirmware:&n;&t; *&n;&t; * &t;DB0ACH-&gt;DL1BKE &lt;RR C P R0&gt; [DAMA]&n;&t; *&t;DL1BKE-&gt;DB0ACH &lt;I NR=0 NS=0&gt;&n;&t; *&t;DL1BKE-7-&gt;DB0PRA-6 DB0ACH &lt;I C S3 R5&gt;&n;&t; *&t;DL1BKE-&gt;DB0ACH &lt;RR R F R0&gt;&n;&t; *&n;&t; * The Flexnet DAMA Master implementation apparently&n;&t; * insists on the &quot;proper&quot; AX.25 behaviour:&n;&t; *&n;&t; * &t;DB0ACH-&gt;DL1BKE &lt;RR C P R0&gt; [DAMA]&n;&t; *&t;DL1BKE-&gt;DB0ACH &lt;RR R F R0&gt;&n;&t; *&t;DL1BKE-&gt;DB0ACH &lt;I NR=0 NS=0&gt;&n;&t; *&t;DL1BKE-7-&gt;DB0PRA-6 DB0ACH &lt;I C S3 R5&gt;&n;&t; *&n;&t; * Flexnet refuses to send us *any* I frame if we send&n;&t; * a REJ in case AX25_COND_REJECT is set. It is superfluous in &n;&t; * this mode anyway (a RR or RNR invokes the retransmission).&n;&t; * Is this a Flexnet bug?&n;&t; */
id|ax25_std_enquiry_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_PEER_RX_BUSY
)paren
)paren
(brace
id|ax25_requeue_frames
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_kick
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25-&gt;state
op_eq
id|AX25_STATE_2
op_logical_or
id|skb_peek
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
op_ne
l_int|NULL
)paren
id|ax25_ds_t1_timeout
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t3timer
op_assign
id|ax25-&gt;t3
suffix:semicolon
id|ax25_ds_set_timer
c_func
(paren
id|ax25-&gt;ax25_dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ax25o
op_assign
id|ax25_list
suffix:semicolon
id|ax25o
op_ne
l_int|NULL
suffix:semicolon
id|ax25o
op_assign
id|ax25o-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ax25o
op_eq
id|ax25
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ax25o-&gt;ax25_dev
op_ne
id|ax25-&gt;ax25_dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25o-&gt;state
op_eq
id|AX25_STATE_2
)paren
(brace
id|ax25_ds_t1_timeout
c_func
(paren
id|ax25o
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ax25o-&gt;condition
op_amp
id|AX25_COND_PEER_RX_BUSY
)paren
op_logical_and
id|ax25o-&gt;state
op_eq
id|AX25_STATE_3
)paren
(brace
id|ax25_requeue_frames
c_func
(paren
id|ax25o
)paren
suffix:semicolon
id|ax25_kick
c_func
(paren
id|ax25o
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ax25o-&gt;state
op_eq
id|AX25_STATE_1
op_logical_or
id|ax25o-&gt;state
op_eq
id|AX25_STATE_2
op_logical_or
id|skb_peek
c_func
(paren
op_amp
id|ax25o-&gt;ack_queue
)paren
op_ne
l_int|NULL
)paren
id|ax25_ds_t1_timeout
c_func
(paren
id|ax25o
)paren
suffix:semicolon
id|ax25o-&gt;t3timer
op_assign
id|ax25o-&gt;t3
suffix:semicolon
)brace
)brace
DECL|function|ax25_ds_establish_data_link
r_void
id|ax25_ds_establish_data_link
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25-&gt;condition
op_and_assign
id|AX25_COND_DAMA_MODE
suffix:semicolon
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t3timer
op_assign
id|ax25-&gt;t3
suffix:semicolon
id|ax25-&gt;t2timer
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;t1timer
op_assign
id|ax25-&gt;t1
op_assign
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;:::FIXME:::&n; *&t;This is a kludge. Not all drivers recognize kiss commands. &n; *&t;We need a driver level  request to switch duplex mode, that does &n; *&t;either SCC changing, PI config or KISS as required. Currently&n; *&t;this request isn&squot;t reliable.&n; */
DECL|function|ax25_kiss_cmd
r_static
r_void
id|ax25_kiss_cmd
c_func
(paren
id|ax25_dev
op_star
id|ax25_dev
comma
r_int
r_char
id|cmd
comma
r_int
r_char
id|param
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|ax25_dev-&gt;dev
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|2
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|cmd
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|param
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ax25_dev-&gt;dev
suffix:semicolon
id|skb-&gt;priority
op_assign
id|SOPRI_NORMAL
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_AX25
)paren
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A nasty problem arises if we count the number of DAMA connections&n; *&t;wrong, especially when connections on the device already existed&n; *&t;and our network node (or the sysop) decides to turn on DAMA Master&n; *&t;mode. We thus flag the &squot;real&squot; slave connections with &n; *&t;ax25-&gt;dama_slave=1 and look on every disconnect if still slave&n; *&t;connections exist.&n; */
DECL|function|ax25_check_dama_slave
r_static
r_int
id|ax25_check_dama_slave
c_func
(paren
id|ax25_dev
op_star
id|ax25_dev
)paren
(brace
id|ax25_cb
op_star
id|ax25
suffix:semicolon
r_for
c_loop
(paren
id|ax25
op_assign
id|ax25_list
suffix:semicolon
id|ax25
op_ne
l_int|NULL
suffix:semicolon
id|ax25
op_assign
id|ax25-&gt;next
)paren
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev
op_eq
id|ax25_dev
op_logical_and
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_DAMA_MODE
)paren
op_logical_and
id|ax25-&gt;state
OG
id|AX25_STATE_1
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ax25_dev_dama_on
r_void
id|ax25_dev_dama_on
c_func
(paren
id|ax25_dev
op_star
id|ax25_dev
)paren
(brace
r_if
c_cond
(paren
id|ax25_dev
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ax25_dev-&gt;dama.slave
op_eq
l_int|0
)paren
id|ax25_kiss_cmd
c_func
(paren
id|ax25_dev
comma
l_int|5
comma
l_int|1
)paren
suffix:semicolon
id|ax25_dev-&gt;dama.slave
op_assign
l_int|1
suffix:semicolon
id|ax25_ds_set_timer
c_func
(paren
id|ax25_dev
)paren
suffix:semicolon
)brace
DECL|function|ax25_dev_dama_off
r_void
id|ax25_dev_dama_off
c_func
(paren
id|ax25_dev
op_star
id|ax25_dev
)paren
(brace
r_if
c_cond
(paren
id|ax25_dev
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ax25_dev-&gt;dama.slave
op_logical_and
op_logical_neg
id|ax25_check_dama_slave
c_func
(paren
id|ax25_dev
)paren
)paren
(brace
id|ax25_kiss_cmd
c_func
(paren
id|ax25_dev
comma
l_int|5
comma
l_int|0
)paren
suffix:semicolon
id|ax25_dev-&gt;dama.slave
op_assign
l_int|0
suffix:semicolon
id|ax25_ds_del_timer
c_func
(paren
id|ax25_dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_dama_on
r_void
id|ax25_dama_on
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_dev_dama_on
c_func
(paren
id|ax25-&gt;ax25_dev
)paren
suffix:semicolon
id|ax25-&gt;condition
op_or_assign
id|AX25_COND_DAMA_MODE
suffix:semicolon
)brace
DECL|function|ax25_dama_off
r_void
id|ax25_dama_off
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_dev_dama_off
c_func
(paren
id|ax25-&gt;ax25_dev
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_DAMA_MODE
suffix:semicolon
)brace
macro_line|#endif
eof