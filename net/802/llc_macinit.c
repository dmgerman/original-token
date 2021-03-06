multiline_comment|/*&n; * NET&t;&t;An implementation of the IEEE 802.2 LLC protocol for the&n; *&t;&t;LINUX operating system.  LLC is implemented as a set of&n; *&t;&t;state machines and callbacks for higher networking layers.&n; *&n; *&t;&t;Code for initialization, termination, registration and&n; *&t;&t;MAC layer glue.&n; *&n; *&t;&t;Written by Tim Alpaerts, Tim_Alpaerts@toyota-motor-europe.com&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Changes&n; *&t;&t;Alan Cox&t;:&t;Chainsawed to Linux format&n; *&t;&t;&t;&t;&t;Added llc_ to names&n; *&t;&t;&t;&t;&t;Started restructuring handlers&n; *&n; *              Horst von Brand :      Add #include &lt;linux/string.h&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/p8022.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/llc_frame.h&gt;
macro_line|#include &lt;net/llc.h&gt;
multiline_comment|/*&n; *&t;All incoming frames pass thru mac_data_indicate().&n; *&t;On entry the llc structure related to the frame is passed as parameter. &n; *&t;The received sk_buffs with pdus other than I_CMD and I_RSP&n; *&t;are freed by mac_data_indicate() after processing,&n; *&t;the I pdu buffers are freed by the cl2llc client when it no longer needs&n; *&t;the skb.&n;*/
DECL|function|llc_mac_data_indicate
r_int
id|llc_mac_data_indicate
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
r_int
id|ll
suffix:semicolon
multiline_comment|/* logical length == 802.3 length field */
r_int
r_char
id|p_flag
suffix:semicolon
r_int
r_char
id|type
suffix:semicolon
id|frameptr
id|fr
suffix:semicolon
r_int
id|free
op_assign
l_int|1
suffix:semicolon
id|lp-&gt;inc_skb
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Truncate buffer to true 802.3 length&n;&t; *&t;[FIXME: move to 802.2 demux]&n;&t; */
id|ll
op_assign
op_star
(paren
id|skb-&gt;data
op_minus
l_int|2
)paren
op_star
l_int|256
op_plus
op_star
(paren
id|skb-&gt;data
op_minus
l_int|1
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|ll
)paren
suffix:semicolon
id|fr
op_assign
(paren
id|frameptr
)paren
id|skb-&gt;data
suffix:semicolon
id|type
op_assign
id|llc_decode_frametype
c_func
(paren
id|fr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_le
id|FRMR_RSP
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;PDU is of the type 2 set&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|lp-&gt;llc_mode
op_eq
id|MODE_ABM
)paren
op_logical_or
(paren
id|type
op_eq
id|SABME_CMD
)paren
)paren
id|llc_process_otype2_frame
c_func
(paren
id|lp
comma
id|skb
comma
id|type
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *&t;PDU belongs to type 1 set&n;&t;&t; */
id|p_flag
op_assign
id|fr-&gt;u_hdr.u_pflag
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|TEST_CMD
suffix:colon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|TEST_RSP
comma
l_int|0
comma
id|ll
op_minus
l_int|3
comma
id|fr-&gt;u_hdr.u_info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TEST_RSP
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_TEST_INDICATION
suffix:semicolon
id|lp-&gt;inc_skb
op_assign
id|skb
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XID_CMD
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; *&t;Basic format XID is handled by LLC itself&n;&t;&t;&t;&t; *&t;Doc 5.4.1.1.2 p 48/49&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|ll
op_eq
l_int|6
)paren
op_logical_and
(paren
id|fr-&gt;u_hdr.u_info
(braket
l_int|0
)braket
op_eq
l_int|0x81
)paren
)paren
(brace
id|lp-&gt;k
op_assign
id|fr-&gt;u_hdr.u_info
(braket
l_int|2
)braket
suffix:semicolon
id|llc_sendpdu
c_func
(paren
id|lp
comma
id|XID_RSP
comma
id|fr-&gt;u_hdr.u_pflag
comma
id|ll
op_minus
l_int|3
comma
id|fr-&gt;u_hdr.u_info
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XID_RSP
suffix:colon
r_if
c_cond
(paren
id|ll
op_eq
l_int|6
op_logical_and
id|fr-&gt;u_hdr.u_info
(braket
l_int|0
)braket
op_eq
l_int|0x81
)paren
(brace
id|lp-&gt;k
op_assign
id|fr-&gt;u_hdr.u_info
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_XID_INDICATION
suffix:semicolon
id|lp-&gt;inc_skb
op_assign
id|skb
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_CMD
suffix:colon
id|lp-&gt;llc_callbacks
op_or_assign
id|LLC_UI_DATA
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
id|lp-&gt;inc_skb
op_assign
id|skb
suffix:semicolon
id|free
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/*&n;&t;&t;&t;&t; *&t;All other type 1 pdus ignored for now&n;&t;&t;&t;&t; */
)brace
)brace
r_if
c_cond
(paren
id|free
op_logical_and
(paren
op_logical_neg
(paren
id|IS_IFRAME
c_func
(paren
id|fr
)paren
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;No auto free for I pdus&n;&t;&t; */
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp-&gt;llc_callbacks
)paren
(brace
r_if
c_cond
(paren
id|lp-&gt;llc_event
op_ne
l_int|NULL
)paren
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
multiline_comment|/*&n; *&t;Create an LLC client. As it is the job of the caller to clean up&n; *&t;LLC&squot;s on device down, the device list must be locked before this call.&n; */
DECL|function|register_cl2llc_client
r_int
id|register_cl2llc_client
c_func
(paren
id|llcptr
id|lp
comma
r_const
r_char
op_star
id|device
comma
r_void
(paren
op_star
id|event
)paren
(paren
id|llcptr
)paren
comma
id|u8
op_star
id|rmac
comma
id|u8
id|ssap
comma
id|u8
id|dsap
)paren
(brace
r_char
id|eye_init
(braket
)braket
op_assign
l_string|&quot;LLC&bslash;0&quot;
suffix:semicolon
id|memset
c_func
(paren
id|lp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|lp
)paren
)paren
suffix:semicolon
id|lp-&gt;dev
op_assign
id|__dev_get_by_name
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|lp-&gt;eye
comma
id|eye_init
comma
r_sizeof
(paren
id|lp-&gt;eye
)paren
)paren
suffix:semicolon
id|lp-&gt;rw
op_assign
l_int|1
suffix:semicolon
id|lp-&gt;k
op_assign
l_int|127
suffix:semicolon
id|lp-&gt;n1
op_assign
l_int|1490
suffix:semicolon
id|lp-&gt;n2
op_assign
l_int|10
suffix:semicolon
id|lp-&gt;timer_interval
(braket
id|P_TIMER
)braket
op_assign
id|HZ
suffix:semicolon
multiline_comment|/* 1 sec */
id|lp-&gt;timer_interval
(braket
id|REJ_TIMER
)braket
op_assign
id|HZ
op_div
l_int|8
suffix:semicolon
id|lp-&gt;timer_interval
(braket
id|ACK_TIMER
)braket
op_assign
id|HZ
op_div
l_int|8
suffix:semicolon
id|lp-&gt;timer_interval
(braket
id|BUSY_TIMER
)braket
op_assign
id|HZ
op_star
l_int|2
suffix:semicolon
id|lp-&gt;local_sap
op_assign
id|ssap
suffix:semicolon
id|lp-&gt;llc_event
op_assign
id|event
suffix:semicolon
id|memcpy
c_func
(paren
id|lp-&gt;remote_mac
comma
id|rmac
comma
r_sizeof
(paren
id|lp-&gt;remote_mac
)paren
)paren
suffix:semicolon
id|lp-&gt;state
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;llc_mode
op_assign
id|MODE_ADM
suffix:semicolon
id|lp-&gt;remote_sap
op_assign
id|dsap
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|lp-&gt;atq
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|lp-&gt;rtq
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_cl2llc_client
r_void
id|unregister_cl2llc_client
c_func
(paren
id|llcptr
id|lp
)paren
(brace
id|llc_cancel_timers
c_func
(paren
id|lp
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|kfree
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
DECL|variable|register_cl2llc_client
id|EXPORT_SYMBOL
c_func
(paren
id|register_cl2llc_client
)paren
suffix:semicolon
DECL|variable|unregister_cl2llc_client
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_cl2llc_client
)paren
suffix:semicolon
DECL|variable|llc_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|llc_data_request
)paren
suffix:semicolon
DECL|variable|llc_unit_data_request
id|EXPORT_SYMBOL
c_func
(paren
id|llc_unit_data_request
)paren
suffix:semicolon
DECL|variable|llc_test_request
id|EXPORT_SYMBOL
c_func
(paren
id|llc_test_request
)paren
suffix:semicolon
DECL|variable|llc_xid_request
id|EXPORT_SYMBOL
c_func
(paren
id|llc_xid_request
)paren
suffix:semicolon
DECL|variable|llc_mac_data_indicate
id|EXPORT_SYMBOL
c_func
(paren
id|llc_mac_data_indicate
)paren
suffix:semicolon
DECL|variable|llc_cancel_timers
id|EXPORT_SYMBOL
c_func
(paren
id|llc_cancel_timers
)paren
suffix:semicolon
DECL|macro|ALL_TYPES_8022
mdefine_line|#define ALL_TYPES_8022 0
DECL|function|llc_init
r_static
r_int
id|__init
id|llc_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;IEEE 802.2 LLC for Linux 2.1 (c) 1996 Tim Alpaerts&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|llc_init
id|module_init
c_func
(paren
id|llc_init
)paren
suffix:semicolon
eof
