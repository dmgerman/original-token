multiline_comment|/*********************************************************************&n; *                &n; *                &n; * Filename:      qos.c&n; * Version:       1.0&n; * Description:   IrLAP QoS parameter negotiation&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Sep  9 00:00:26 1997&n; * Modified at:   Tue Nov 16 09:50:19 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/parameters.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
macro_line|#include &lt;net/irda/irlap_comp.h&gt;
macro_line|#include &quot;../../drivers/net/zlib.h&quot;
DECL|macro|CI_BZIP2
mdefine_line|#define CI_BZIP2  27 /* Random pick */
macro_line|#endif
r_static
r_int
id|irlap_param_baud_rate
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_link_disconnect
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|parm
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_max_turn_time
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_data_size
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_window_size
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_additional_bofs
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|parm
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|irlap_param_min_turn_time
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
DECL|variable|min_turn_time
id|__u32
id|min_turn_time
(braket
)braket
op_assign
(brace
l_int|10000
comma
l_int|5000
comma
l_int|1000
comma
l_int|500
comma
l_int|100
comma
l_int|50
comma
l_int|10
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* us */
DECL|variable|baud_rates
id|__u32
id|baud_rates
(braket
)braket
op_assign
(brace
l_int|2400
comma
l_int|9600
comma
l_int|19200
comma
l_int|38400
comma
l_int|57600
comma
l_int|115200
comma
l_int|576000
comma
l_int|1152000
comma
l_int|4000000
comma
l_int|16000000
)brace
suffix:semicolon
multiline_comment|/* bps */
DECL|variable|data_size
id|__u32
id|data_size
(braket
)braket
op_assign
(brace
l_int|64
comma
l_int|128
comma
l_int|256
comma
l_int|512
comma
l_int|1024
comma
l_int|2048
)brace
suffix:semicolon
multiline_comment|/* bytes */
DECL|variable|add_bofs
id|__u32
id|add_bofs
(braket
)braket
op_assign
(brace
l_int|48
comma
l_int|24
comma
l_int|12
comma
l_int|5
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* bytes */
DECL|variable|max_turn_time
id|__u32
id|max_turn_time
(braket
)braket
op_assign
(brace
l_int|500
comma
l_int|250
comma
l_int|100
comma
l_int|50
)brace
suffix:semicolon
multiline_comment|/* ms */
DECL|variable|link_disc_time
id|__u32
id|link_disc_time
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|8
comma
l_int|12
comma
l_int|16
comma
l_int|20
comma
l_int|25
comma
l_int|30
comma
l_int|40
)brace
suffix:semicolon
multiline_comment|/* secs */
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
DECL|variable|compression
id|__u32
id|compression
(braket
)braket
op_assign
(brace
id|CI_BZIP2
comma
id|CI_DEFLATE
comma
id|CI_DEFLATE_DRAFT
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|pi_minor_call_table_type_0
r_static
id|pi_minor_info_t
id|pi_minor_call_table_type_0
(braket
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
)brace
comma
multiline_comment|/* 01 */
(brace
id|irlap_param_baud_rate
comma
id|PV_INTEGER
op_or
id|PV_LITTLE_ENDIAN
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
multiline_comment|/* 08 */
(brace
id|irlap_param_link_disconnect
comma
id|PV_INT_8_BITS
)brace
)brace
suffix:semicolon
DECL|variable|pi_minor_call_table_type_1
r_static
id|pi_minor_info_t
id|pi_minor_call_table_type_1
(braket
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
multiline_comment|/* 82 */
(brace
id|irlap_param_max_turn_time
comma
id|PV_INT_8_BITS
)brace
comma
multiline_comment|/* 83 */
(brace
id|irlap_param_data_size
comma
id|PV_INT_8_BITS
)brace
comma
multiline_comment|/* 84 */
(brace
id|irlap_param_window_size
comma
id|PV_INT_8_BITS
)brace
comma
multiline_comment|/* 85 */
(brace
id|irlap_param_additional_bofs
comma
id|PV_INT_8_BITS
)brace
comma
multiline_comment|/* 86 */
(brace
id|irlap_param_min_turn_time
comma
id|PV_INT_8_BITS
)brace
comma
)brace
suffix:semicolon
DECL|variable|pi_major_call_table
r_static
id|pi_major_info_t
id|pi_major_call_table
(braket
)braket
op_assign
(brace
(brace
id|pi_minor_call_table_type_0
comma
l_int|9
)brace
comma
(brace
id|pi_minor_call_table_type_1
comma
l_int|7
)brace
comma
)brace
suffix:semicolon
DECL|variable|irlap_param_info
r_static
id|pi_param_info_t
id|irlap_param_info
op_assign
(brace
id|pi_major_call_table
comma
l_int|2
comma
l_int|0x7f
comma
l_int|7
)brace
suffix:semicolon
multiline_comment|/*&n; * Function irda_qos_compute_intersection (qos, new)&n; *&n; *    Compute the intersection of the old QoS capabilites with new ones&n; *&n; */
DECL|function|irda_qos_compute_intersection
r_void
id|irda_qos_compute_intersection
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
comma
r_struct
id|qos_info
op_star
r_new
)paren
(brace
id|ASSERT
c_func
(paren
id|qos
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
r_new
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Apply */
id|qos-&gt;baud_rate.bits
op_and_assign
r_new
op_member_access_from_pointer
id|baud_rate.bits
suffix:semicolon
id|qos-&gt;window_size.bits
op_and_assign
r_new
op_member_access_from_pointer
id|window_size.bits
suffix:semicolon
id|qos-&gt;min_turn_time.bits
op_and_assign
r_new
op_member_access_from_pointer
id|min_turn_time.bits
suffix:semicolon
id|qos-&gt;max_turn_time.bits
op_and_assign
r_new
op_member_access_from_pointer
id|max_turn_time.bits
suffix:semicolon
id|qos-&gt;data_size.bits
op_and_assign
r_new
op_member_access_from_pointer
id|data_size.bits
suffix:semicolon
id|qos-&gt;link_disc_time.bits
op_and_assign
r_new
op_member_access_from_pointer
id|link_disc_time.bits
suffix:semicolon
id|qos-&gt;additional_bofs.bits
op_and_assign
r_new
op_member_access_from_pointer
id|additional_bofs.bits
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
id|qos-&gt;compression.bits
op_and_assign
r_new
op_member_access_from_pointer
id|compression.bits
suffix:semicolon
macro_line|#endif
id|irda_qos_bits_to_value
c_func
(paren
id|qos
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_init_max_qos_capabilies (qos)&n; *&n; *    The purpose of this function is for layers and drivers to be able to&n; *    set the maximum QoS possible and then &quot;and in&quot; their own limitations&n; * &n; */
DECL|function|irda_init_max_qos_capabilies
r_void
id|irda_init_max_qos_capabilies
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
)paren
(brace
multiline_comment|/* &n;&t; *  These are the maximum supported values as specified on pages&n;&t; *  39-43 in IrLAP&n;&t; */
multiline_comment|/* LSB is first byte, MSB is second byte */
id|qos-&gt;baud_rate.bits
op_assign
l_int|0x01ff
suffix:semicolon
id|qos-&gt;window_size.bits
op_assign
l_int|0x7f
suffix:semicolon
id|qos-&gt;min_turn_time.bits
op_assign
l_int|0xff
suffix:semicolon
id|qos-&gt;max_turn_time.bits
op_assign
l_int|0x0f
suffix:semicolon
id|qos-&gt;data_size.bits
op_assign
l_int|0x3f
suffix:semicolon
id|qos-&gt;link_disc_time.bits
op_assign
l_int|0xff
suffix:semicolon
id|qos-&gt;additional_bofs.bits
op_assign
l_int|0xff
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION&t;
id|qos-&gt;compression.bits
op_assign
l_int|0x03
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Function irlap_negotiate (qos_device, qos_session, skb)&n; *&n; *    Negotiate QoS values, not really that much negotiation :-)&n; *    We just set the QoS capabilities for the peer station&n; *&n; */
DECL|function|irlap_qos_negotiate
r_int
id|irlap_qos_negotiate
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ret
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
r_int
id|comp_seen
op_assign
id|FALSE
suffix:semicolon
macro_line|#endif
id|ret
op_assign
id|irda_param_extract_all
c_func
(paren
id|self
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
r_if
c_cond
(paren
op_logical_neg
id|comp_seen
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(), Compression not seen!&bslash;n&quot;
)paren
suffix:semicolon
id|self-&gt;qos_tx.compression.bits
op_assign
l_int|0x00
suffix:semicolon
id|self-&gt;qos_rx.compression.bits
op_assign
l_int|0x00
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Convert the negotiated bits to values */
id|irda_qos_bits_to_value
c_func
(paren
op_amp
id|self-&gt;qos_tx
)paren
suffix:semicolon
id|irda_qos_bits_to_value
c_func
(paren
op_amp
id|self-&gt;qos_rx
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting BAUD_RATE to %d bps.&bslash;n&quot;
comma
id|self-&gt;qos_tx.baud_rate.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting DATA_SIZE to %d bytes&bslash;n&quot;
comma
id|self-&gt;qos_tx.data_size.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting WINDOW_SIZE to %d&bslash;n&quot;
comma
id|self-&gt;qos_tx.window_size.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting XBOFS to %d&bslash;n&quot;
comma
id|self-&gt;qos_tx.additional_bofs.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting MAX_TURN_TIME to %d ms.&bslash;n&quot;
comma
id|self-&gt;qos_tx.max_turn_time.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting MIN_TURN_TIME to %d usecs.&bslash;n&quot;
comma
id|self-&gt;qos_tx.min_turn_time.value
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting LINK_DISC to %d secs.&bslash;n&quot;
comma
id|self-&gt;qos_tx.link_disc_time.value
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Setting COMPRESSION to %d&bslash;n&quot;
comma
id|self-&gt;qos_tx.compression.value
)paren
suffix:semicolon
macro_line|#endif&t;
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_insert_negotiation_params (qos, fp)&n; *&n; *    Insert QoS negotiaion pararameters into frame&n; *&n; */
DECL|function|irlap_insert_qos_negotiation_params
r_int
id|irlap_insert_qos_negotiation_params
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* Insert data rate */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_BAUD_RATE
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert max turnaround time */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_MAX_TURN_TIME
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert data size */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_DATA_SIZE
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert window size */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_WINDOW_SIZE
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert additional BOFs */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_ADD_BOFS
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert minimum turnaround time */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_MIN_TURN_TIME
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* Insert link disconnect/threshold time */
id|ret
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|PI_LINK_DISC
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|irlap_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|ret
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_baud_rate (instance, param, get)&n; *&n; *    Negotiate data-rate&n; *&n; */
DECL|function|irlap_param_baud_rate
r_static
r_int
id|irlap_param_baud_rate
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
id|__u16
id|final
suffix:semicolon
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
id|param-&gt;pv.i
op_assign
id|self-&gt;qos_rx.baud_rate.bits
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), baud rate = 0x%02x&bslash;n&quot;
comma
id|param-&gt;pv.i
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* &n;&t;&t; *  Stations must agree on baud rate, so calculate&n;&t;&t; *  intersection &n;&t;&t; */
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Requested BAUD_RATE: 0x%04x&bslash;n&quot;
comma
id|param-&gt;pv.s
)paren
suffix:semicolon
id|final
op_assign
id|param-&gt;pv.s
op_amp
id|self-&gt;qos_rx.baud_rate.bits
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Final BAUD_RATE: 0x%04x&bslash;n&quot;
comma
id|final
)paren
suffix:semicolon
id|self-&gt;qos_tx.baud_rate.bits
op_assign
id|final
suffix:semicolon
id|self-&gt;qos_rx.baud_rate.bits
op_assign
id|final
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_link_disconnect (instance, param, get)&n; *&n; *    Negotiate link disconnect/threshold time. &n; *&n; */
DECL|function|irlap_param_link_disconnect
r_static
r_int
id|irlap_param_link_disconnect
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
id|__u16
id|final
suffix:semicolon
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.link_disc_time.bits
suffix:semicolon
r_else
(brace
multiline_comment|/*  &n;&t;&t; *  Stations must agree on link disconnect/threshold &n;&t;&t; *  time.&n;&t;&t; */
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;LINK_DISC: %02x&bslash;n&quot;
comma
id|param-&gt;pv.b
)paren
suffix:semicolon
id|final
op_assign
id|param-&gt;pv.b
op_amp
id|self-&gt;qos_rx.link_disc_time.bits
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;Final LINK_DISC: %02x&bslash;n&quot;
comma
id|final
)paren
suffix:semicolon
id|self-&gt;qos_tx.link_disc_time.bits
op_assign
id|final
suffix:semicolon
id|self-&gt;qos_rx.link_disc_time.bits
op_assign
id|final
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_max_turn_time (instance, param, get)&n; *&n; *    Negotiate the maximum turnaround time. This is a type 1 parameter and&n; *    will be negotiated independently for each station&n; *&n; */
DECL|function|irlap_param_max_turn_time
r_static
r_int
id|irlap_param_max_turn_time
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.max_turn_time.bits
suffix:semicolon
r_else
id|self-&gt;qos_tx.max_turn_time.bits
op_assign
id|param-&gt;pv.b
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_data_size (instance, param, get)&n; *&n; *    Negotiate the data size. This is a type 1 parameter and&n; *    will be negotiated independently for each station&n; *&n; */
DECL|function|irlap_param_data_size
r_static
r_int
id|irlap_param_data_size
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.data_size.bits
suffix:semicolon
r_else
id|self-&gt;qos_tx.data_size.bits
op_assign
id|param-&gt;pv.b
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_window_size (instance, param, get)&n; *&n; *    Negotiate the window size. This is a type 1 parameter and&n; *    will be negotiated independently for each station&n; *&n; */
DECL|function|irlap_param_window_size
r_static
r_int
id|irlap_param_window_size
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.window_size.bits
suffix:semicolon
r_else
id|self-&gt;qos_tx.window_size.bits
op_assign
id|param-&gt;pv.b
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_additional_bofs (instance, param, get)&n; *&n; *    Negotiate additional BOF characters. This is a type 1 parameter and&n; *    will be negotiated independently for each station.&n; */
DECL|function|irlap_param_additional_bofs
r_static
r_int
id|irlap_param_additional_bofs
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.additional_bofs.bits
suffix:semicolon
r_else
id|self-&gt;qos_tx.additional_bofs.bits
op_assign
id|param-&gt;pv.b
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_param_min_turn_time (instance, param, get)&n; *&n; *    Negotiate the minimum turn around time. This is a type 1 parameter and&n; *    will be negotiated independently for each station&n; */
DECL|function|irlap_param_min_turn_time
r_static
r_int
id|irlap_param_min_turn_time
c_func
(paren
r_void
op_star
id|instance
comma
id|param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.b
op_assign
id|self-&gt;qos_rx.min_turn_time.bits
suffix:semicolon
r_else
id|self-&gt;qos_tx.min_turn_time.bits
op_assign
id|param-&gt;pv.b
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|byte_value
id|__u32
id|byte_value
c_func
(paren
id|__u8
id|byte
comma
id|__u32
op_star
id|array
)paren
(brace
r_int
id|index
suffix:semicolon
id|ASSERT
c_func
(paren
id|array
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|byte
)paren
suffix:semicolon
r_return
id|index_value
c_func
(paren
id|index
comma
id|array
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function msb_index (word)&n; *&n; *    Returns index to most significant bit (MSB) in word&n; *&n; */
DECL|function|msb_index
r_int
id|msb_index
(paren
id|__u16
id|word
)paren
(brace
id|__u16
id|msb
op_assign
l_int|0x8000
suffix:semicolon
r_int
id|index
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* Current MSB */
r_while
c_loop
(paren
id|msb
)paren
(brace
r_if
c_cond
(paren
id|word
op_amp
id|msb
)paren
r_break
suffix:semicolon
multiline_comment|/* Found it! */
id|msb
op_rshift_assign
l_int|1
suffix:semicolon
id|index
op_decrement
suffix:semicolon
)brace
r_return
id|index
suffix:semicolon
)brace
multiline_comment|/*&n; * Function value_index (value, array)&n; *&n; *    Returns the index to the value in the specified array&n; */
DECL|function|value_index
r_int
id|value_index
c_func
(paren
id|__u32
id|value
comma
id|__u32
op_star
id|array
)paren
(brace
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|array
(braket
id|i
)braket
op_eq
id|value
)paren
r_break
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * Function index_value (index, array)&n; *&n; *    Returns value to index in array, easy!&n; *&n; */
DECL|function|index_value
id|__u32
id|index_value
c_func
(paren
r_int
id|index
comma
id|__u32
op_star
id|array
)paren
(brace
r_return
id|array
(braket
id|index
)braket
suffix:semicolon
)brace
DECL|function|irda_qos_bits_to_value
r_void
id|irda_qos_bits_to_value
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
)paren
(brace
r_int
id|index
suffix:semicolon
id|ASSERT
c_func
(paren
id|qos
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;baud_rate.bits
)paren
suffix:semicolon
id|qos-&gt;baud_rate.value
op_assign
id|baud_rates
(braket
id|index
)braket
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;data_size.bits
)paren
suffix:semicolon
id|qos-&gt;data_size.value
op_assign
id|data_size
(braket
id|index
)braket
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;window_size.bits
)paren
suffix:semicolon
id|qos-&gt;window_size.value
op_assign
id|index
op_plus
l_int|1
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;min_turn_time.bits
)paren
suffix:semicolon
id|qos-&gt;min_turn_time.value
op_assign
id|min_turn_time
(braket
id|index
)braket
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;max_turn_time.bits
)paren
suffix:semicolon
id|qos-&gt;max_turn_time.value
op_assign
id|max_turn_time
(braket
id|index
)braket
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;link_disc_time.bits
)paren
suffix:semicolon
id|qos-&gt;link_disc_time.value
op_assign
id|link_disc_time
(braket
id|index
)braket
suffix:semicolon
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;additional_bofs.bits
)paren
suffix:semicolon
id|qos-&gt;additional_bofs.value
op_assign
id|add_bofs
(braket
id|index
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
id|index
op_assign
id|msb_index
c_func
(paren
id|qos-&gt;compression.bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
l_int|0
)paren
id|qos-&gt;compression.value
op_assign
id|compression
(braket
id|index
)braket
suffix:semicolon
r_else
id|qos-&gt;compression.value
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
eof
