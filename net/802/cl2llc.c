multiline_comment|/*&n; * NET&t;&t;An implementation of the IEEE 802.2 LLC protocol for the&n; *&t;&t;LINUX operating system.  LLC is implemented as a set of &n; *&t;&t;state machines and callbacks for higher networking layers.&n; *&n; *&t;&t;Class 2 llc algorithm.&n; *&t;&t;Pseudocode interpreter, transition table lookup,&n; *&t;&t;&t;data_request &amp; indicate primitives...&n; *&n; *&t;&t;Code for initialization, termination, registration and &n; *&t;&t;MAC layer glue.&n; *&n; *&t;&t;Copyright Tim Alpaerts, &n; *&t;&t;&t;&lt;Tim_Alpaerts@toyota-motor-europe.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Changes&n; *&t;&t;Alan Cox&t;:&t;Chainsawed into Linux format&n; *&t;&t;&t;&t;&t;Modified to use llc_ names&n; *&n; *&t;This file must be processed by sed before it can be compiled.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/p8022.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;pseudo/pseudocode.h&quot;
macro_line|#include &quot;transit/pdutr.h&quot;
macro_line|#include &quot;transit/timertr.h&quot;
macro_line|#include &lt;net/llc_frame.h&gt;
macro_line|#include &lt;net/llc.h&gt;
multiline_comment|/*&n; *&t;Data_request() is called by the client to present a data unit&n; *&t;to the llc for transmission.&n; *&t;In the future this function should also check if the transmit window&n; *&t;allows the sending of another pdu, and if not put the skb on the atq&n; *&t;for deferred sending.&n; */
DECL|function|llc_data_request
r_int
id|llc_data_request
c_func
(paren
id|llcptr
id|lp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
(paren
id|lp-&gt;dev-&gt;hard_header_len
op_plus
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cl2llc: data_request() not enough headroom in skb&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lp-&gt;state
op_ne
id|NORMAL
)paren
op_logical_and
(paren
id|lp-&gt;state
op_ne
id|BUSY
)paren
op_logical_and
(paren
id|lp-&gt;state
op_ne
id|REJECT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cl2llc: data_request() while no llc connection&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp-&gt;remote_busy
)paren
(brace
multiline_comment|/* if the remote llc is BUSY, */
id|ADD_TO_ATQ
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* save skb in the await transmit queue */
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *&t;Else proceed with xmit &n;&t;&t; */
r_switch
c_cond
(paren
id|lp-&gt;state
)paren
(brace
r_case
id|NORMAL
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;p_flag
)paren
(brace
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|NORMAL2
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
)brace
r_else
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|NORMAL1
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BUSY
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;p_flag
)paren
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|BUSY2
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
r_else
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|BUSY1
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REJECT
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;p_flag
)paren
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|REJECT2
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
r_else
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|REJECT1
comma
id|skb
comma
id|NO_FRAME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
id|lp
op_member_access_from_pointer
id|llc_event
c_func
(paren
id|lp
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; *&t;Disconnect_request() requests that the llc to terminate a connection&n; */
DECL|function|disconnect_request
r_void
id|disconnect_request
c_func
(paren
id|llcptr
id|lp
)paren
(brace
r_if
c_cond
(paren
(paren
id|lp-&gt;state
op_eq
id|NORMAL
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|BUSY
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|REJECT
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|AWAIT
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|AWAIT_BUSY
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|AWAIT_REJECT
)paren
)paren
(brace
id|lp-&gt;state
op_assign
id|D_CONN
suffix:semicolon
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|SH1
comma
l_int|NULL
comma
id|NO_FRAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
id|lp
op_member_access_from_pointer
id|llc_event
c_func
(paren
id|lp
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; &t;&t; *&t;lp may be invalid after the callback&n;&t;&t; */
)brace
)brace
multiline_comment|/*&n; *&t;Connect_request() requests that the llc to start a connection&n; */
DECL|function|connect_request
r_void
id|connect_request
c_func
(paren
id|llcptr
id|lp
)paren
(brace
r_if
c_cond
(paren
id|lp-&gt;state
op_eq
id|ADM
)paren
(brace
id|lp-&gt;state
op_assign
id|SETUP
suffix:semicolon
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|ADM1
comma
l_int|NULL
comma
id|NO_FRAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
id|lp
op_member_access_from_pointer
id|llc_event
c_func
(paren
id|lp
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; &t;&t; *&t;lp may be invalid after the callback&n;&t;&t; */
)brace
)brace
multiline_comment|/*&n; *&t;Interpret_pseudo_code() executes the actions in the connection component&n; *&t;state transition table. Table 4 in document on p88.&n; *&n; *&t;If this function is called to handle an incomming pdu, skb will point&n; *&t;to the buffer with the pdu and type will contain the decoded pdu type.&n; *&n; *&t;If called by data_request skb points to an skb that was skb_alloc-ed by &n; *&t;the llc client to hold the information unit to be transmitted, there is&n; *&t;no valid type in this case.  &n; *&n; *&t;If called because a timer expired no skb is passed, and there is no &n; *&t;type.&n; */
DECL|function|llc_interpret_pseudo_code
r_void
id|llc_interpret_pseudo_code
c_func
(paren
id|llcptr
id|lp
comma
r_int
id|pc_label
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
id|type
)paren
(brace
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* program counter in pseudo code array */
r_char
id|p_flag_received
suffix:semicolon
id|frameptr
id|fr
suffix:semicolon
r_int
id|resend_count
suffix:semicolon
multiline_comment|/* number of pdus resend by llc_resend_ipdu() */
r_int
id|ack_count
suffix:semicolon
multiline_comment|/* number of pdus acknowledged */
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
(brace
id|fr
op_assign
(paren
id|frameptr
)paren
id|skb-&gt;data
suffix:semicolon
)brace
r_else
id|fr
op_assign
l_int|NULL
suffix:semicolon
id|pc
op_assign
id|pseudo_code_idx
(braket
id|pc_label
)braket
suffix:semicolon
r_while
c_loop
(paren
id|pseudo_code
(braket
id|pc
)braket
)paren
(brace
r_switch
c_cond
(paren
id|pseudo_code
(braket
id|pc
)braket
)paren
(brace
r_case
l_int|9
suffix:colon
r_if
c_cond
(paren
(paren
id|type
op_ne
id|I_CMD
)paren
op_logical_or
(paren
id|fr-&gt;i_hdr.i_pflag
op_assign
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|lp-&gt;remote_busy
op_assign
l_int|0
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|BUSY_TIMER
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lp-&gt;state
op_eq
id|NORMAL
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|REJECT
)paren
op_logical_or
(paren
id|lp-&gt;state
op_eq
id|BUSY
)paren
)paren
(brace
id|skb2
op_assign
id|llc_pull_from_atq
c_func
(paren
id|lp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_ne
l_int|NULL
)paren
id|llc_start_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
r_while
c_loop
(paren
id|skb2
op_ne
l_int|NULL
)paren
(brace
id|llc_sendipdu
c_func
(paren
id|lp
comma
id|I_CMD
comma
l_int|0
comma
id|skb2
)paren
suffix:semicolon
id|skb2
op_assign
id|llc_pull_from_atq
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|lp-&gt;state
op_assign
id|NORMAL
suffix:semicolon
multiline_comment|/* needed to eliminate connect_response() */
id|lp-&gt;llc_mode
op_assign
id|MODE_ABM
suffix:semicolon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_CONN_INDICATION
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|lp-&gt;llc_mode
op_assign
id|MODE_ABM
suffix:semicolon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_CONN_CONFIRM
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
id|lp-&gt;inc_skb
op_assign
id|skb
suffix:semicolon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_DATA_INDIC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|lp-&gt;llc_mode
op_assign
id|MODE_ADM
suffix:semicolon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_DISC_INDICATION
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|70
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_RESET_INDIC_LOC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|71
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_RESET_INDIC_REM
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_RST_CONFIRM
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|66
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_FRMR_RECV
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|67
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_FRMR_SENT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|68
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_REMOTE_BUSY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|69
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_REMOTE_NOTBUSY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|DISC_CMD
comma
id|lp-&gt;f_flag
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|DM_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|lp-&gt;frmr_info_fld.cntl1
op_assign
id|fr-&gt;pdu_cntl.byte1
suffix:semicolon
id|lp-&gt;frmr_info_fld.cntl2
op_assign
id|fr-&gt;pdu_cntl.byte2
suffix:semicolon
id|lp-&gt;frmr_info_fld.vs
op_assign
id|lp-&gt;vs
suffix:semicolon
id|lp-&gt;frmr_info_fld.vr_cr
op_assign
id|lp-&gt;vr
suffix:semicolon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|FRMR_RSP
comma
l_int|0
comma
l_int|5
comma
(paren
r_char
op_star
)paren
op_amp
id|lp-&gt;frmr_info_fld
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|FRMR_RSP
comma
l_int|0
comma
l_int|5
comma
(paren
r_char
op_star
)paren
op_amp
id|lp-&gt;frmr_info_fld
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|FRMR_RSP
comma
id|lp-&gt;p_flag
comma
l_int|5
comma
(paren
r_char
op_star
)paren
op_amp
id|lp-&gt;frmr_info_fld
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|llc_sendipdu
c_func
(paren
id|lp
comma
id|I_CMD
comma
l_int|1
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
suffix:colon
id|resend_count
op_assign
id|llc_resend_ipdu
c_func
(paren
id|lp
comma
id|fr-&gt;i_hdr.nr
comma
id|I_CMD
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|18
suffix:colon
id|resend_count
op_assign
id|llc_resend_ipdu
c_func
(paren
id|lp
comma
id|fr-&gt;i_hdr.nr
comma
id|I_CMD
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resend_count
op_eq
l_int|0
)paren
(brace
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_CMD
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|19
suffix:colon
id|llc_sendipdu
c_func
(paren
id|lp
comma
id|I_CMD
comma
l_int|0
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|20
suffix:colon
id|resend_count
op_assign
id|llc_resend_ipdu
c_func
(paren
id|lp
comma
id|fr-&gt;i_hdr.nr
comma
id|I_CMD
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|21
suffix:colon
id|resend_count
op_assign
id|llc_resend_ipdu
c_func
(paren
id|lp
comma
id|fr-&gt;i_hdr.nr
comma
id|I_CMD
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resend_count
op_eq
l_int|0
)paren
(brace
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|22
suffix:colon
id|resend_count
op_assign
id|llc_resend_ipdu
c_func
(paren
id|lp
comma
id|fr-&gt;i_hdr.nr
comma
id|I_RSP
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|23
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|REJ_CMD
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|REJ_RSP
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
r_if
c_cond
(paren
id|IS_RSP
c_func
(paren
id|fr
)paren
)paren
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|REJ_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|REJ_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|26
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_CMD
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|27
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_RSP
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|28
suffix:colon
r_if
c_cond
(paren
id|IS_RSP
c_func
(paren
id|fr
)paren
)paren
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|29
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;remote_busy
op_eq
l_int|0
)paren
(brace
id|lp-&gt;remote_busy
op_assign
l_int|1
suffix:semicolon
id|llc_start_timer
c_func
(paren
id|lp
comma
id|BUSY_TIMER
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_REMOTE_BUSY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lp-&gt;timer_state
(braket
id|BUSY_TIMER
)braket
op_eq
id|TIMER_IDLE
)paren
(brace
id|llc_start_timer
c_func
(paren
id|lp
comma
id|BUSY_TIMER
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|30
suffix:colon
r_if
c_cond
(paren
id|IS_RSP
c_func
(paren
id|fr
)paren
)paren
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RNR_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|31
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_CMD
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_CMD
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_RSP
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|34
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_RSP
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|35
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|36
suffix:colon
r_if
c_cond
(paren
id|IS_RSP
c_func
(paren
id|fr
)paren
)paren
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|RR_RSP
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|37
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|SABME_CMD
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|lp-&gt;f_flag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|UA_RSP
comma
id|lp-&gt;f_flag
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|39
suffix:colon
id|lp-&gt;s_flag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|40
suffix:colon
id|lp-&gt;s_flag
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|41
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;timer_state
(braket
id|P_TIMER
)braket
op_eq
id|TIMER_RUNNING
)paren
(brace
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|P_TIMER
)paren
suffix:semicolon
)brace
id|llc_start_timer
c_func
(paren
id|lp
comma
id|P_TIMER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;p_flag
op_eq
l_int|0
)paren
(brace
id|lp-&gt;retry_count
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;p_flag
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|44
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;timer_state
(braket
id|ACK_TIMER
)braket
op_eq
id|TIMER_IDLE
)paren
id|llc_start_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|42
suffix:colon
id|llc_start_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|43
suffix:colon
id|llc_start_timer
c_func
(paren
id|lp
comma
id|REJ_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|45
suffix:colon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|46
suffix:colon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
id|lp-&gt;p_flag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;data_flag
op_eq
l_int|2
)paren
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|REJ_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|47
suffix:colon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|REJ_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48
suffix:colon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|P_TIMER
)paren
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|REJ_TIMER
)paren
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|BUSY_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|49
suffix:colon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|P_TIMER
)paren
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|REJ_TIMER
)paren
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|BUSY_TIMER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|ack_count
op_assign
id|llc_free_acknowledged_skbs
c_func
(paren
id|lp
comma
(paren
r_int
r_char
)paren
id|fr-&gt;s_hdr.nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack_count
OG
l_int|0
)paren
(brace
id|lp-&gt;retry_count
op_assign
l_int|0
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|lp-&gt;rtq
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n; &t;&t;&t;&t;&t;&t; *&t;Re-transmit queue not empty &n;&t;&t;&t;&t;&t;&t; */
id|llc_start_timer
c_func
(paren
id|lp
comma
id|ACK_TIMER
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|51
suffix:colon
r_if
c_cond
(paren
id|IS_UFRAME
c_func
(paren
id|fr
)paren
)paren
id|p_flag_received
op_assign
id|fr-&gt;u_hdr.u_pflag
suffix:semicolon
r_else
id|p_flag_received
op_assign
id|fr-&gt;i_hdr.i_pflag
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fr-&gt;pdu_hdr.ssap
op_amp
l_int|0x01
)paren
op_logical_and
(paren
id|p_flag_received
)paren
)paren
(brace
id|lp-&gt;p_flag
op_assign
l_int|0
suffix:semicolon
id|llc_stop_timer
c_func
(paren
id|lp
comma
id|P_TIMER
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|52
suffix:colon
id|lp-&gt;data_flag
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|53
suffix:colon
id|lp-&gt;data_flag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|54
suffix:colon
id|lp-&gt;data_flag
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|55
suffix:colon
r_if
c_cond
(paren
id|lp-&gt;data_flag
op_eq
l_int|0
)paren
id|lp-&gt;data_flag
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|56
suffix:colon
id|lp-&gt;p_flag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57
suffix:colon
id|lp-&gt;p_flag
op_assign
id|lp-&gt;f_flag
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|58
suffix:colon
id|lp-&gt;remote_busy
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|59
suffix:colon
id|lp-&gt;retry_count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|60
suffix:colon
id|lp-&gt;retry_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|61
suffix:colon
id|lp-&gt;vr
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|62
suffix:colon
id|lp-&gt;vr
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|63
suffix:colon
id|lp-&gt;vs
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|64
suffix:colon
id|lp-&gt;vs
op_assign
id|fr-&gt;i_hdr.nr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|65
suffix:colon
r_if
c_cond
(paren
id|IS_UFRAME
c_func
(paren
id|fr
)paren
)paren
id|lp-&gt;f_flag
op_assign
id|fr-&gt;u_hdr.u_pflag
suffix:semicolon
r_else
id|lp-&gt;f_flag
op_assign
id|fr-&gt;i_hdr.i_pflag
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
id|pc
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Process_otype2_frame will handle incoming frames&n; *&t;for 802.2 Type 2 Procedure.&n; */
DECL|function|llc_process_otype2_frame
r_void
id|llc_process_otype2_frame
c_func
(paren
id|llcptr
id|lp
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
id|type
)paren
(brace
r_int
id|idx
suffix:semicolon
multiline_comment|/*&t;index in transition table */
r_int
id|pc_label
suffix:semicolon
multiline_comment|/*&t;action to perform, from tr tbl */
r_int
id|validation
suffix:semicolon
multiline_comment|/*&t;result of validate_seq_nos */
r_int
id|p_flag_received
suffix:semicolon
multiline_comment|/*&t;p_flag in received frame */
id|frameptr
id|fr
suffix:semicolon
id|fr
op_assign
(paren
id|frameptr
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|IS_UFRAME
c_func
(paren
id|fr
)paren
)paren
id|p_flag_received
op_assign
id|fr-&gt;u_hdr.u_pflag
suffix:semicolon
r_else
id|p_flag_received
op_assign
id|fr-&gt;i_hdr.i_pflag
suffix:semicolon
r_switch
c_cond
(paren
id|lp-&gt;state
)paren
(brace
multiline_comment|/*&t;Compute index in transition table: */
r_case
id|ADM
suffix:colon
id|idx
op_assign
id|type
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|p_flag_received
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONN
suffix:colon
r_case
id|RESET_WAIT
suffix:colon
r_case
id|RESET_CHECK
suffix:colon
r_case
id|ERROR
suffix:colon
id|idx
op_assign
id|type
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SETUP
suffix:colon
r_case
id|RESET
suffix:colon
r_case
id|D_CONN
suffix:colon
id|idx
op_assign
id|type
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|lp-&gt;p_flag
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NORMAL
suffix:colon
r_case
id|BUSY
suffix:colon
r_case
id|REJECT
suffix:colon
r_case
id|AWAIT
suffix:colon
r_case
id|AWAIT_BUSY
suffix:colon
r_case
id|AWAIT_REJECT
suffix:colon
id|validation
op_assign
id|llc_validate_seq_nos
c_func
(paren
id|lp
comma
id|fr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|validation
OG
l_int|3
)paren
id|type
op_assign
id|BAD_FRAME
suffix:semicolon
id|idx
op_assign
id|type
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|validation
op_amp
l_int|1
)paren
id|idx
op_assign
id|idx
op_plus
l_int|1
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|p_flag_received
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|lp-&gt;p_flag
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;llc_proc: bad state&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|pdutr_offset
(braket
id|lp-&gt;state
)braket
suffix:semicolon
id|lp-&gt;state
op_assign
id|pdutr_entry
(braket
id|idx
op_plus
l_int|1
)braket
suffix:semicolon
id|pc_label
op_assign
id|pdutr_entry
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pc_label
op_ne
l_int|0
)paren
(brace
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|pc_label
comma
id|skb
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
id|lp
op_member_access_from_pointer
id|llc_event
c_func
(paren
id|lp
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; &t;&t; *&t;lp may no longer be valid after this point. Be&n;&t;&t; *&t;careful what is added!&n;&t;&t; */
)brace
)brace
DECL|function|llc_timer_expired
r_void
id|llc_timer_expired
c_func
(paren
id|llcptr
id|lp
comma
r_int
id|t
)paren
(brace
r_int
id|idx
suffix:semicolon
multiline_comment|/* index in transition table&t;*/
r_int
id|pc_label
suffix:semicolon
multiline_comment|/* action to perform, from tr tbl */
id|lp-&gt;timer_state
(braket
id|t
)braket
op_assign
id|TIMER_EXPIRED
suffix:semicolon
id|idx
op_assign
id|lp-&gt;state
suffix:semicolon
multiline_comment|/* Compute index in transition table: */
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|2
)paren
op_plus
id|t
suffix:semicolon
id|idx
op_assign
id|idx
op_lshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;retry_count
op_ge
id|lp-&gt;n2
)paren
id|idx
op_assign
id|idx
op_plus
l_int|1
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|lp-&gt;s_flag
suffix:semicolon
id|idx
op_assign
(paren
id|idx
op_lshift
l_int|1
)paren
op_plus
id|lp-&gt;p_flag
suffix:semicolon
id|idx
op_assign
id|idx
op_lshift
l_int|1
suffix:semicolon
multiline_comment|/* 2 bytes per entry: action &amp; newstate */
id|pc_label
op_assign
id|timertr_entry
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pc_label
op_ne
l_int|0
)paren
(brace
id|llc_interpret_pseudo_code
c_func
(paren
id|lp
comma
id|pc_label
comma
l_int|NULL
comma
id|NO_FRAME
)paren
suffix:semicolon
id|lp-&gt;state
op_assign
id|timertr_entry
(braket
id|idx
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|lp-&gt;timer_state
(braket
id|t
)braket
op_assign
id|TIMER_IDLE
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
id|lp
op_member_access_from_pointer
id|llc_event
c_func
(paren
id|lp
)paren
suffix:semicolon
id|lp-&gt;llc_callbacks
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; &t; *&t;And lp may have vanished in the event callback&n; &t; */
)brace
eof
