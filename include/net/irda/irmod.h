multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irmod.h&n; * Version:       0.3&n; * Description:   IrDA module and utilities functions&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Dec 15 13:58:52 1997&n; * Modified at:   Thu Feb 11 15:14:30 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *&n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charg.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRMOD_H
DECL|macro|IRMOD_H
mdefine_line|#define IRMOD_H
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
DECL|macro|IRMGR_IOC_MAGIC
mdefine_line|#define IRMGR_IOC_MAGIC &squot;m&squot;
DECL|macro|IRMGR_IOCTNPC
mdefine_line|#define IRMGR_IOCTNPC     _IO(IRMGR_IOC_MAGIC, 1)
DECL|macro|IRMGR_IOC_MAXNR
mdefine_line|#define IRMGR_IOC_MAXNR   1 
multiline_comment|/*&n; *  Events that we pass to the user space manager&n; */
r_typedef
r_enum
(brace
DECL|enumerator|EVENT_DEVICE_DISCOVERED
id|EVENT_DEVICE_DISCOVERED
op_assign
l_int|0
comma
DECL|enumerator|EVENT_REQUEST_MODULE
id|EVENT_REQUEST_MODULE
comma
DECL|enumerator|EVENT_IRLAN_START
id|EVENT_IRLAN_START
comma
DECL|enumerator|EVENT_IRLAN_STOP
id|EVENT_IRLAN_STOP
comma
DECL|enumerator|EVENT_IRLPT_START
id|EVENT_IRLPT_START
comma
DECL|enumerator|EVENT_IRLPT_STOP
id|EVENT_IRLPT_STOP
comma
multiline_comment|/* &t;EVENT_IROBEX_INIT, */
DECL|enumerator|EVENT_IROBEX_START
id|EVENT_IROBEX_START
comma
DECL|enumerator|EVENT_IROBEX_STOP
id|EVENT_IROBEX_STOP
comma
DECL|enumerator|EVENT_IRDA_STOP
id|EVENT_IRDA_STOP
comma
DECL|enumerator|EVENT_NEED_PROCESS_CONTEXT
id|EVENT_NEED_PROCESS_CONTEXT
comma
DECL|typedef|IRMGR_EVENT
)brace
id|IRMGR_EVENT
suffix:semicolon
multiline_comment|/*&n; *  Event information passed to the IrManager daemon process&n; */
DECL|struct|irmanager_event
r_struct
id|irmanager_event
(brace
DECL|member|event
id|IRMGR_EVENT
id|event
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|info
r_char
id|info
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|service
r_int
id|service
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|TODO_CALLBACK
r_typedef
r_void
(paren
op_star
id|TODO_CALLBACK
)paren
(paren
r_void
op_star
id|self
comma
id|__u32
id|param
)paren
suffix:semicolon
multiline_comment|/*&n; *  Same as irmanager_event but this one can be queued and inclueds some&n; *  addtional information&n; */
DECL|struct|irda_event
r_struct
id|irda_event
(brace
DECL|member|q
id|QUEUE
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|event
r_struct
id|irmanager_event
id|event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Funtions with needs to be called with a process context&n; */
DECL|struct|irda_todo
r_struct
id|irda_todo
(brace
DECL|member|q
id|QUEUE
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|self
r_void
op_star
id|self
suffix:semicolon
DECL|member|callback
id|TODO_CALLBACK
id|callback
suffix:semicolon
DECL|member|param
id|__u32
id|param
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Main structure for the IrDA device (not much here :-)&n; */
DECL|struct|irda_cb
r_struct
id|irda_cb
(brace
DECL|member|dev
r_struct
id|miscdevice
id|dev
suffix:semicolon
DECL|member|wait_queue
r_struct
id|wait_queue
op_star
id|wait_queue
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|event_queue
id|QUEUE
op_star
id|event_queue
suffix:semicolon
multiline_comment|/* Events queued for the irmanager */
DECL|member|todo_queue
id|QUEUE
op_star
id|todo_queue
suffix:semicolon
multiline_comment|/* Todo list */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|irda_call
r_char
id|irda_call
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 6 call + SSID (shifted ascii!) */
DECL|typedef|irda_address
)brace
id|irda_address
suffix:semicolon
DECL|struct|sockaddr_irda
r_struct
id|sockaddr_irda
(brace
DECL|member|sirda_family
r_int
id|sirda_family
suffix:semicolon
DECL|member|sirda_call
id|irda_address
id|sirda_call
suffix:semicolon
DECL|member|sirda_ndigis
r_int
id|sirda_ndigis
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  This type is used by the protocols that transmit 16 bits words in &n; *  little endian format. A little endian machine stores MSB of word in&n; *  byte[1] and LSB in byte[0]. A big endian machine stores MSB in byte[0] &n; *  and LSB in byte[1].&n; */
r_typedef
r_union
(brace
DECL|member|word
id|__u16
id|word
suffix:semicolon
DECL|member|byte
id|__u8
id|byte
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|__u16_host_order
)brace
id|__u16_host_order
suffix:semicolon
multiline_comment|/*&n; *  Information monitored by some layers&n; */
DECL|struct|irda_statistics
r_struct
id|irda_statistics
(brace
DECL|member|rx_packets
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received       */
DECL|member|tx_packets
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted    */
DECL|member|rx_errors
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received         */
DECL|member|tx_errors
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems     */
DECL|member|rx_dropped
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers    */
DECL|member|tx_dropped
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux  */
DECL|member|rx_compressed
r_int
id|rx_compressed
suffix:semicolon
DECL|member|tx_compressed
r_int
id|tx_compressed
suffix:semicolon
DECL|member|rx_bytes
r_int
id|rx_bytes
suffix:semicolon
multiline_comment|/* total bytes received         */
DECL|member|tx_bytes
r_int
id|tx_bytes
suffix:semicolon
multiline_comment|/* total bytes transmitted      */
DECL|member|multicast
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received   */
DECL|member|collisions
r_int
id|collisions
suffix:semicolon
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver ring buff overflow  */
DECL|member|rx_crc_errors
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* recved pkt with crc error    */
DECL|member|rx_frame_errors
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* recv&squot;d frame alignment error */
DECL|member|rx_fifo_errors
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* recv&squot;r fifo overrun          */
DECL|member|rx_missed_errors
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet       */
multiline_comment|/* detailed tx_errors */
DECL|member|tx_aborted_errors
r_int
id|tx_aborted_errors
suffix:semicolon
DECL|member|tx_carrier_errors
r_int
id|tx_carrier_errors
suffix:semicolon
DECL|member|tx_fifo_errors
r_int
id|tx_fifo_errors
suffix:semicolon
DECL|member|tx_heartbeat_errors
r_int
id|tx_heartbeat_errors
suffix:semicolon
DECL|member|tx_window_errors
r_int
id|tx_window_errors
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|NO_CHANGE
id|NO_CHANGE
comma
DECL|enumerator|LOCKED
id|LOCKED
comma
DECL|enumerator|UNLOCKED
id|UNLOCKED
comma
DECL|typedef|LOCK_STATUS
)brace
id|LOCK_STATUS
suffix:semicolon
multiline_comment|/* Misc status information */
r_typedef
r_enum
(brace
DECL|enumerator|STATUS_OK
id|STATUS_OK
comma
DECL|enumerator|STATUS_ABORTED
id|STATUS_ABORTED
comma
DECL|enumerator|STATUS_NO_ACTIVITY
id|STATUS_NO_ACTIVITY
comma
DECL|enumerator|STATUS_NOISY
id|STATUS_NOISY
comma
DECL|enumerator|STATUS_REMOTE
id|STATUS_REMOTE
comma
DECL|typedef|LINK_STATUS
)brace
id|LINK_STATUS
suffix:semicolon
r_typedef
r_enum
(brace
multiline_comment|/* FIXME check the two first reason codes */
DECL|enumerator|LAP_DISC_INDICATION
id|LAP_DISC_INDICATION
op_assign
l_int|1
comma
multiline_comment|/* Received a disconnect request from peer */
DECL|enumerator|LAP_NO_RESPONSE
id|LAP_NO_RESPONSE
comma
multiline_comment|/* To many retransmits without response */
DECL|enumerator|LAP_RESET_INDICATION
id|LAP_RESET_INDICATION
comma
multiline_comment|/* To many retransmits, or invalid nr/ns */
DECL|enumerator|LAP_FOUND_NONE
id|LAP_FOUND_NONE
comma
multiline_comment|/* No devices were discovered */
DECL|enumerator|LAP_MEDIA_BUSY
id|LAP_MEDIA_BUSY
comma
DECL|enumerator|LAP_PRIMARY_CONFLICT
id|LAP_PRIMARY_CONFLICT
comma
DECL|typedef|LAP_REASON
)brace
id|LAP_REASON
suffix:semicolon
multiline_comment|/*  &n; *  IrLMP disconnect reasons. The order is very important, since they &n; *  correspond to disconnect reasons sent in IrLMP disconnect frames, so&n; *  please do not touch :-)&n; */
r_typedef
r_enum
(brace
DECL|enumerator|LM_USER_REQUEST
id|LM_USER_REQUEST
op_assign
l_int|1
comma
multiline_comment|/* User request */
DECL|enumerator|LM_LAP_DISCONNECT
id|LM_LAP_DISCONNECT
comma
multiline_comment|/* Unexpected IrLAP disconnect */
DECL|enumerator|LM_CONNECT_FAILURE
id|LM_CONNECT_FAILURE
comma
multiline_comment|/* Failed to establish IrLAP connection */
DECL|enumerator|LM_LAP_RESET
id|LM_LAP_RESET
comma
multiline_comment|/* IrLAP reset */
DECL|enumerator|LM_INIT_DISCONNECT
id|LM_INIT_DISCONNECT
comma
multiline_comment|/* Link Management initiated disconnect */
DECL|enumerator|LM_LSAP_NOTCONN
id|LM_LSAP_NOTCONN
comma
multiline_comment|/* Data delivered on unconnected LSAP */
DECL|enumerator|LM_NON_RESP_CLIENT
id|LM_NON_RESP_CLIENT
comma
multiline_comment|/* Non responsive LM-MUX client */
DECL|enumerator|LM_NO_AVAIL_CLIENT
id|LM_NO_AVAIL_CLIENT
comma
multiline_comment|/* No available LM-MUX client */
DECL|enumerator|LM_CONN_HALF_OPEN
id|LM_CONN_HALF_OPEN
comma
multiline_comment|/* Connection is half open */
DECL|enumerator|LM_BAD_SOURCE_ADDR
id|LM_BAD_SOURCE_ADDR
comma
multiline_comment|/* Illegal source address (i.e 0x00) */
DECL|typedef|LM_REASON
)brace
id|LM_REASON
suffix:semicolon
DECL|macro|LM_UNKNOWN
mdefine_line|#define LM_UNKNOWN 0xff       /* Unspecified disconnect reason */
multiline_comment|/*&n; *  IrLMP character code values&n; */
DECL|macro|CS_ASCII
mdefine_line|#define CS_ASCII       0x00
DECL|macro|CS_ISO_8859_1
mdefine_line|#define&t;CS_ISO_8859_1  0x01
DECL|macro|CS_ISO_8859_2
mdefine_line|#define&t;CS_ISO_8859_2  0x02
DECL|macro|CS_ISO_8859_3
mdefine_line|#define&t;CS_ISO_8859_3  0x03
DECL|macro|CS_ISO_8859_4
mdefine_line|#define&t;CS_ISO_8859_4  0x04
DECL|macro|CS_ISO_8859_5
mdefine_line|#define&t;CS_ISO_8859_5  0x05
DECL|macro|CS_ISO_8859_6
mdefine_line|#define&t;CS_ISO_8859_6  0x06
DECL|macro|CS_ISO_8859_7
mdefine_line|#define&t;CS_ISO_8859_7  0x07
DECL|macro|CS_ISO_8859_8
mdefine_line|#define&t;CS_ISO_8859_8  0x08
DECL|macro|CS_ISO_8859_9
mdefine_line|#define&t;CS_ISO_8859_9  0x09
DECL|macro|CS_UNICODE
mdefine_line|#define CS_UNICODE     0xff
multiline_comment|/*&n; * The DISCOVERY structure is used for both discovery requests and responses&n; */
DECL|macro|DISCOVERY
mdefine_line|#define DISCOVERY struct discovery_t
DECL|struct|discovery_t
r_struct
id|discovery_t
(brace
DECL|member|queue
id|QUEUE
id|queue
suffix:semicolon
multiline_comment|/* Must be first! */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Which link the device was discovered */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Remote device address */
DECL|member|condition
id|LAP_REASON
id|condition
suffix:semicolon
multiline_comment|/* More info about the discovery */
DECL|member|hint
id|__u8
id|hint
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Discovery hint bits */
DECL|member|charset
id|__u8
id|charset
suffix:semicolon
DECL|member|info
r_char
id|info
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Usually the name of the device */
DECL|member|info_len
id|__u8
id|info_len
suffix:semicolon
multiline_comment|/* Length of device info field */
DECL|member|gen_addr_bit
r_int
id|gen_addr_bit
suffix:semicolon
multiline_comment|/* Need to generate a new device address? */
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots to use when discovering */
)brace
suffix:semicolon
DECL|enumerator|FLOW_STOP
DECL|enumerator|FLOW_START
DECL|typedef|LOCAL_FLOW
r_typedef
r_enum
(brace
id|FLOW_STOP
comma
id|FLOW_START
)brace
id|LOCAL_FLOW
suffix:semicolon
multiline_comment|/*&n; *  Notify structure used between transport and link management layers&n; */
DECL|struct|notify_t
r_struct
id|notify_t
(brace
DECL|member|data_indication
r_void
(paren
op_star
id|data_indication
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|udata_indication
r_void
(paren
op_star
id|udata_indication
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|connect_confirm
r_void
(paren
op_star
id|connect_confirm
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|max_sdu_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|connect_indication
r_void
(paren
op_star
id|connect_indication
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|max_sdu_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|disconnect_indication
r_void
(paren
op_star
id|disconnect_indication
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|flow_indication
r_void
(paren
op_star
id|flow_indication
)paren
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
DECL|member|instance
r_void
op_star
id|instance
suffix:semicolon
multiline_comment|/* Layer instance pointer */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Name of layer */
)brace
suffix:semicolon
DECL|macro|NOTIFY_MAX_NAME
mdefine_line|#define NOTIFY_MAX_NAME 16
r_int
id|irmod_init_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irmod_cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_inline
r_int
id|irda_lock
c_func
(paren
r_int
op_star
id|lock
)paren
suffix:semicolon
r_inline
r_int
id|irda_unlock
c_func
(paren
r_int
op_star
id|lock
)paren
suffix:semicolon
r_void
id|irda_notify_init
c_func
(paren
r_struct
id|notify_t
op_star
id|notify
)paren
suffix:semicolon
r_void
id|irda_execute_as_process
c_func
(paren
r_void
op_star
id|self
comma
id|TODO_CALLBACK
id|callback
comma
id|__u32
id|param
)paren
suffix:semicolon
r_void
id|irmanager_notify
c_func
(paren
r_struct
id|irmanager_event
op_star
id|event
)paren
suffix:semicolon
r_extern
r_void
id|irda_proc_modcount
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
