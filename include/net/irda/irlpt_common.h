multiline_comment|/*********************************************************************&n; *&n; * Filename:      irlpt_common.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Thomas Davis, &lt;ratbert@radiks.net&gt;&n; * Created at:    Sat Feb 21 18:54:38 1998&n; * Modified at:   Sun Mar  8 23:44:19 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Sources:&t;  irlan.c&n; *&n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;,&n; *&t;&t;&t;   Dag Brattli,  &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     I, Thomas Davis, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLPT_COMMON_H
DECL|macro|IRLPT_COMMON_H
mdefine_line|#define IRLPT_COMMON_H
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
r_extern
r_char
op_star
id|irlpt_service_type
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_port_type
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_connected
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_reasons
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_client_fsm_state
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_server_fsm_state
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|irlpt_fsm_event
(braket
)braket
suffix:semicolon
r_extern
id|wait_queue_head_t
id|lpt_wait
suffix:semicolon
r_extern
r_struct
id|irlpt_cb
op_star
id|irlpt_find_handle
c_func
(paren
r_int
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_void
id|irlpt_flow_control
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
id|ssize_t
id|irlpt_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
suffix:semicolon
r_extern
id|ssize_t
id|irlpt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|noidea
)paren
suffix:semicolon
r_extern
id|loff_t
id|irlpt_seek
c_func
(paren
r_struct
id|file
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|irlpt_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
id|u_int
id|irlpt_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
multiline_comment|/* FSM definitions */
r_typedef
r_enum
(brace
DECL|enumerator|IRLPT_CLIENT_IDLE
id|IRLPT_CLIENT_IDLE
comma
DECL|enumerator|IRLPT_CLIENT_QUERY
id|IRLPT_CLIENT_QUERY
comma
DECL|enumerator|IRLPT_CLIENT_READY
id|IRLPT_CLIENT_READY
comma
DECL|enumerator|IRLPT_CLIENT_WAITI
id|IRLPT_CLIENT_WAITI
comma
DECL|enumerator|IRLPT_CLIENT_CONN
id|IRLPT_CLIENT_CONN
comma
DECL|typedef|IRLPT_CLIENT_STATE
)brace
id|IRLPT_CLIENT_STATE
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|IRLPT_SERVER_IDLE
id|IRLPT_SERVER_IDLE
comma
DECL|enumerator|IRLPT_SERVER_CONN
id|IRLPT_SERVER_CONN
comma
DECL|typedef|IRLPT_SERVER_STATE
)brace
id|IRLPT_SERVER_STATE
suffix:semicolon
multiline_comment|/* IrLPT Events */
r_typedef
r_enum
(brace
DECL|enumerator|QUERY_REMOTE_IAS
id|QUERY_REMOTE_IAS
comma
DECL|enumerator|IAS_PROVIDER_AVAIL
id|IAS_PROVIDER_AVAIL
comma
DECL|enumerator|IAS_PROVIDER_NOT_AVAIL
id|IAS_PROVIDER_NOT_AVAIL
comma
DECL|enumerator|LAP_DISCONNECT
id|LAP_DISCONNECT
comma
DECL|enumerator|LMP_CONNECT
id|LMP_CONNECT
comma
DECL|enumerator|LMP_DISCONNECT
id|LMP_DISCONNECT
comma
DECL|enumerator|LMP_CONNECT_INDICATION
id|LMP_CONNECT_INDICATION
comma
DECL|enumerator|LMP_DISCONNECT_INDICATION
id|LMP_DISCONNECT_INDICATION
comma
DECL|enumerator|IRLPT_DISCOVERY_INDICATION
id|IRLPT_DISCOVERY_INDICATION
comma
DECL|enumerator|IRLPT_CONNECT_REQUEST
id|IRLPT_CONNECT_REQUEST
comma
DECL|enumerator|IRLPT_DISCONNECT_REQUEST
id|IRLPT_DISCONNECT_REQUEST
comma
DECL|enumerator|CLIENT_DATA_INDICATION
id|CLIENT_DATA_INDICATION
comma
DECL|typedef|IRLPT_EVENT
)brace
id|IRLPT_EVENT
suffix:semicolon
DECL|struct|irlpt_info
r_struct
id|irlpt_info
(brace
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Command packet types */
DECL|macro|IRLPT_MAX_PACKET
mdefine_line|#define IRLPT_MAX_PACKET 1024
DECL|macro|IRLPT_MAX_HEADER
mdefine_line|#define IRLPT_MAX_HEADER LMP_MAX_HEADER
DECL|macro|IRLPT_MAX_DEVICES
mdefine_line|#define IRLPT_MAX_DEVICES 3
DECL|macro|IRLPT_MAGIC
mdefine_line|#define IRLPT_MAGIC 0x0755
r_typedef
r_enum
(brace
DECL|enumerator|IRLPT_DISCONNECTED
id|IRLPT_DISCONNECTED
comma
DECL|enumerator|IRLPT_WAITING
id|IRLPT_WAITING
comma
DECL|enumerator|IRLPT_CONNECTED
id|IRLPT_CONNECTED
comma
DECL|enumerator|IRLPT_FLUSHED
id|IRLPT_FLUSHED
comma
DECL|typedef|IRLPT_SERVER_STATUS
)brace
id|IRLPT_SERVER_STATUS
suffix:semicolon
DECL|macro|IRLPT_LSAP
mdefine_line|#define IRLPT_LSAP      0x09
DECL|macro|PI_SERVICE_TYPE
mdefine_line|#define PI_SERVICE_TYPE&t;0x00
DECL|macro|IRLPT_UNKNOWN
mdefine_line|#define IRLPT_UNKNOWN         0x00            /* not defined yet. */
DECL|macro|IRLPT_THREE_WIRE_RAW
mdefine_line|#define IRLPT_THREE_WIRE_RAW  0x01&t;&t;/* bit 0 */
DECL|macro|IRLPT_THREE_WIRE
mdefine_line|#define IRLPT_THREE_WIRE      0x02&t;&t;/* bit 1 */
DECL|macro|IRLPT_NINE_WIRE
mdefine_line|#define IRLPT_NINE_WIRE&t;      0x04&t;&t;/* bit 2 */
DECL|macro|IRLPT_CENTRONICS
mdefine_line|#define IRLPT_CENTRONICS      0x08&t;&t;/* bit 3 */
DECL|macro|IRLPT_SERVER_MODE
mdefine_line|#define IRLPT_SERVER_MODE     0xFF            /* our own flag */
DECL|macro|PI_PORT_TYPE
mdefine_line|#define PI_PORT_TYPE&t;0x01
DECL|macro|IRLPT_SERIAL
mdefine_line|#define IRLPT_SERIAL&t;0x01&t;&t;/* bit 0 */
DECL|macro|IRLPT_PARALLEL
mdefine_line|#define IRLPT_PARALLEL&t;0x02&t;&t;/* bit 1 */
DECL|macro|PI_PORT_NAME
mdefine_line|#define PI_PORT_NAME&t;0x02
DECL|macro|PI_CRITICAL
mdefine_line|#define PI_CRITICAL&t;0x80
DECL|struct|irlpt_cb
r_struct
id|irlpt_cb
(brace
DECL|member|queue
id|QUEUE
id|queue
suffix:semicolon
multiline_comment|/* must be first. */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic used to detect corruption of &n;&t;&t;&t;&t;   the struct */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* address of remote printer */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* my local address. */
DECL|member|retry_timer
r_struct
id|timer_list
id|retry_timer
suffix:semicolon
DECL|member|state
r_int
r_volatile
id|state
suffix:semicolon
multiline_comment|/* Current state of IrCOMM layer */
DECL|member|open_retries
r_int
id|open_retries
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
multiline_comment|/* flag to prevent re-use */
DECL|member|ifname
r_char
id|ifname
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* name of the allocated instance, &n;&t;&t;&t;&t;   and registered device. */
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
multiline_comment|/* lmp handle */
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* remote LSAP selector address */
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* local LSAP selectoraddress */
DECL|member|servicetype
id|__u8
id|servicetype
suffix:semicolon
multiline_comment|/* Type of remote service, ie THREE_WIRE_RAW */
DECL|member|porttype
id|__u8
id|porttype
suffix:semicolon
multiline_comment|/* type of remote port. */
DECL|member|ir_dev
r_struct
id|miscdevice
id|ir_dev
suffix:semicolon
multiline_comment|/* used to register the misc device. */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* open count */
DECL|member|max_data_size
r_int
id|max_data_size
suffix:semicolon
multiline_comment|/* max frame size we can send */
DECL|member|max_header_size
r_int
id|max_header_size
suffix:semicolon
multiline_comment|/* how much header space is needed */
DECL|member|pkt_count
r_int
id|pkt_count
suffix:semicolon
multiline_comment|/* how many packets are queued up */
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
multiline_comment|/* wait queues */
DECL|member|write_wait
id|wait_queue_head_t
id|write_wait
suffix:semicolon
DECL|member|ex_wait
id|wait_queue_head_t
id|ex_wait
suffix:semicolon
multiline_comment|/* this is used to remove the printer when it&squot;s gone */
DECL|member|lpt_timer
r_struct
id|timer_list
id|lpt_timer
suffix:semicolon
DECL|member|timeout
r_void
(paren
op_star
id|timeout
)paren
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|do_event
r_void
(paren
op_star
id|do_event
)paren
(paren
r_struct
id|irlpt_cb
op_star
id|self
comma
id|IRLPT_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlpt_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* this is used by the server side of the system */
DECL|member|connected
id|IRLPT_SERVER_STATE
id|connected
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:semicolon
DECL|member|service_LSAP
r_int
id|service_LSAP
suffix:semicolon
DECL|member|rx_queue
r_struct
id|sk_buff_head
id|rx_queue
suffix:semicolon
multiline_comment|/* read buffer queue */
)brace
suffix:semicolon
multiline_comment|/* Debug function */
r_void
id|irlpt_dump_buffer
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
