multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan.h&n; * Version:       0.1&n; * Description:   IrDA LAN access layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:37 1997&n; * Modified at:   Thu Oct 29 13:23:11 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli &lt;dagb@cs.uit.no&gt;, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLAN_H
DECL|macro|IRLAN_H
mdefine_line|#define IRLAN_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;irqueue.h&quot;
macro_line|#include &quot;irttp.h&quot;
DECL|macro|IRLAN_MTU
mdefine_line|#define IRLAN_MTU 1518
multiline_comment|/* Command packet types */
DECL|macro|CMD_GET_PROVIDER_INFO
mdefine_line|#define CMD_GET_PROVIDER_INFO   0
DECL|macro|CMD_GET_MEDIA_CHAR
mdefine_line|#define CMD_GET_MEDIA_CHAR      1
DECL|macro|CMD_OPEN_DATA_CHANNEL
mdefine_line|#define CMD_OPEN_DATA_CHANNEL   2
DECL|macro|CMD_CLOSE_DATA_CHAN
mdefine_line|#define CMD_CLOSE_DATA_CHAN     3
DECL|macro|CMD_RECONNECT_DATA_CHAN
mdefine_line|#define CMD_RECONNECT_DATA_CHAN 4
DECL|macro|CMD_FILTER_OPERATION
mdefine_line|#define CMD_FILTER_OPERATION    5
multiline_comment|/* Some responses */
DECL|macro|RSP_SUCCESS
mdefine_line|#define RSP_SUCCESS                 0
DECL|macro|RSP_INSUFFICIENT_RESOURCES
mdefine_line|#define RSP_INSUFFICIENT_RESOURCES  1
DECL|macro|RSP_INVALID_COMMAND_FORMAT
mdefine_line|#define RSP_INVALID_COMMAND_FORMAT  2
DECL|macro|RSP_COMMAND_NOT_SUPPORTED
mdefine_line|#define RSP_COMMAND_NOT_SUPPORTED   3
DECL|macro|RSP_PARAM_NOT_SUPPORTED
mdefine_line|#define RSP_PARAM_NOT_SUPPORTED     4
DECL|macro|RSP_VALUE_NOT_SUPPORTED
mdefine_line|#define RSP_VALUE_NOT_SUPPORTED     5
DECL|macro|RSP_NOT_OPEN
mdefine_line|#define RSP_NOT_OPEN                6
DECL|macro|RSP_AUTHENTICATION_REQUIRED
mdefine_line|#define RSP_AUTHENTICATION_REQUIRED 7
DECL|macro|RSP_INVALID_PASSWORD
mdefine_line|#define RSP_INVALID_PASSWORD        8
DECL|macro|RSP_PROTOCOL_ERROR
mdefine_line|#define RSP_PROTOCOL_ERROR          9
DECL|macro|RSP_ASYNCHRONOUS_ERROR
mdefine_line|#define RSP_ASYNCHRONOUS_ERROR    255
multiline_comment|/* Media types */
DECL|macro|MEDIA_802_3
mdefine_line|#define MEDIA_802_3 1
DECL|macro|MEDIA_802_5
mdefine_line|#define MEDIA_802_5 2
multiline_comment|/* Filter parameters */
DECL|macro|DATA_CHAN
mdefine_line|#define DATA_CHAN 1
DECL|macro|FILTER_TYPE
mdefine_line|#define FILTER_TYPE 2
DECL|macro|FILTER_MODE
mdefine_line|#define FILTER_MODE 3
multiline_comment|/* Filter types */
DECL|macro|IR_DIRECTED
mdefine_line|#define IR_DIRECTED   1
DECL|macro|IR_FUNCTIONAL
mdefine_line|#define IR_FUNCTIONAL 2
DECL|macro|IR_GROUP
mdefine_line|#define IR_GROUP      3
DECL|macro|IR_MAC_FRAME
mdefine_line|#define IR_MAC_FRAME  4
DECL|macro|IR_MULTICAST
mdefine_line|#define IR_MULTICAST  5
DECL|macro|IR_BROADCAST
mdefine_line|#define IR_BROADCAST  6
DECL|macro|IR_IPX_SOCKET
mdefine_line|#define IR_IPX_SOCKET 7
multiline_comment|/* Filter modes */
DECL|macro|ALL
mdefine_line|#define ALL    1
DECL|macro|FILTER
mdefine_line|#define FILTER 2
DECL|macro|NONE
mdefine_line|#define NONE   3
multiline_comment|/* Filter operations */
DECL|macro|GET
mdefine_line|#define GET     1
DECL|macro|CLEAR
mdefine_line|#define CLEAR   2
DECL|macro|ADD
mdefine_line|#define ADD     3
DECL|macro|REMOVE
mdefine_line|#define REMOVE  4
DECL|macro|DYNAMIC
mdefine_line|#define DYNAMIC 5
multiline_comment|/* Access types */
DECL|macro|DIRECT
mdefine_line|#define DIRECT 1
DECL|macro|PEER
mdefine_line|#define PEER   2
DECL|macro|HOSTED
mdefine_line|#define HOSTED 3
DECL|macro|IRLAN_MAX_HEADER
mdefine_line|#define IRLAN_MAX_HEADER (TTP_HEADER+LMP_HEADER+LAP_HEADER)
multiline_comment|/*&n; *  IrLAN client subclass&n; */
DECL|struct|irlan_client_cb
r_struct
id|irlan_client_cb
(brace
multiline_comment|/*&n;&t; *  Client fields&n;&t; */
DECL|member|open_retries
r_int
id|open_retries
suffix:semicolon
DECL|member|reconnect_key
id|__u8
id|reconnect_key
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|key_len
id|__u8
id|key_len
suffix:semicolon
DECL|member|unicast_open
r_int
id|unicast_open
suffix:semicolon
DECL|member|broadcast_open
r_int
id|broadcast_open
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IrLAN servers subclass&n; */
DECL|struct|irlan_server_cb
r_struct
id|irlan_server_cb
(brace
multiline_comment|/*&n;&t; *  Store some values here which are used by the irlan_server to parse&n;&t; *  FILTER_OPERATIONs&n;&t; */
DECL|member|data_chan
r_int
id|data_chan
suffix:semicolon
DECL|member|filter_type
r_int
id|filter_type
suffix:semicolon
DECL|member|filter_mode
r_int
id|filter_mode
suffix:semicolon
DECL|member|filter_operation
r_int
id|filter_operation
suffix:semicolon
DECL|member|filter_entry
r_int
id|filter_entry
suffix:semicolon
DECL|member|mac_address
id|__u8
id|mac_address
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Generated MAC address for peer device */
)brace
suffix:semicolon
multiline_comment|/*&n; *  IrLAN super class&n; */
DECL|struct|irlan_cb
r_struct
id|irlan_cb
(brace
DECL|member|queue
id|QUEUE
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|ifname
r_char
id|ifname
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Ethernet device structure*/
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source devcie address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Destination device address */
DECL|member|connected
r_int
id|connected
suffix:semicolon
multiline_comment|/* TTP layer ready to exchange ether frames */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Current state of IrLAN layer */
DECL|member|media
r_int
id|media
suffix:semicolon
DECL|member|tsap_ctrl
r_struct
id|tsap_cb
op_star
id|tsap_ctrl
suffix:semicolon
DECL|member|tsap_data
r_struct
id|tsap_cb
op_star
id|tsap_data
suffix:semicolon
DECL|member|use_udata
r_int
id|use_udata
suffix:semicolon
multiline_comment|/* Use Unit Data transfers */
DECL|member|dtsap_sel_data
id|__u8
id|dtsap_sel_data
suffix:semicolon
multiline_comment|/* Destination data TSAP selector */
DECL|member|stsap_sel_data
id|__u8
id|stsap_sel_data
suffix:semicolon
multiline_comment|/* Source data TSAP selector */
DECL|member|dtsap_sel_ctrl
id|__u8
id|dtsap_sel_ctrl
suffix:semicolon
multiline_comment|/* Destination ctrl TSAP selector */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* Client or server */
r_union
(brace
DECL|member|client
r_struct
id|irlan_client_cb
id|client
suffix:semicolon
DECL|member|server
r_struct
id|irlan_server_cb
id|server
suffix:semicolon
DECL|member|t
)brace
id|t
suffix:semicolon
multiline_comment|/* void (*irlan_dev_init)(struct irlan_cb *); */
multiline_comment|/* &n;         *  Used by extract_params, placed here for now to avoid placing &n;         *  them on the stack. FIXME: remove these!&n;         */
DECL|member|name
r_char
id|name
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|value
r_char
id|value
(braket
l_int|1016
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|irlan_cb
op_star
id|irlan_open
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlan_get_provider_info
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_get_unicast_addr
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_get_media_char
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_open_data_channel
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlan_set_multicast_filter
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
r_void
id|irlan_set_broadcast_filter
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
r_void
id|irlan_open_unicast_addr
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|insert_byte_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
id|__u8
id|value
)paren
suffix:semicolon
r_int
id|insert_string_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
)paren
suffix:semicolon
r_int
id|insert_array_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|name
comma
id|__u8
op_star
id|value
comma
id|__u16
id|value_len
)paren
suffix:semicolon
r_int
id|insert_param
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|param
comma
r_int
id|type
comma
r_char
op_star
id|value_char
comma
id|__u8
id|value_byte
comma
id|__u16
id|value_short
)paren
suffix:semicolon
r_int
id|irlan_get_response_param
c_func
(paren
id|__u8
op_star
id|buf
comma
r_char
op_star
id|name
comma
r_char
op_star
id|value
comma
r_int
op_star
id|len
)paren
suffix:semicolon
r_void
id|print_ret_code
c_func
(paren
id|__u8
id|code
)paren
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|irlan
suffix:semicolon
macro_line|#endif
eof
