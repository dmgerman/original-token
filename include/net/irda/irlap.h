multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlap.h&n; * Version:       0.8&n; * Description:   An IrDA LAP driver for Linux&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Aug  4 20:40:53 1997&n; * Modified at:   Fri Dec 10 13:21:17 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLAP_H
DECL|macro|IRLAP_H
mdefine_line|#define IRLAP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/ppp-comp.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;net/irda/irlap_event.h&gt;
DECL|macro|CONFIG_IRDA_DYNAMIC_WINDOW
mdefine_line|#define CONFIG_IRDA_DYNAMIC_WINDOW 1
DECL|macro|LAP_RELIABLE
mdefine_line|#define LAP_RELIABLE   1
DECL|macro|LAP_UNRELIABLE
mdefine_line|#define LAP_UNRELIABLE 0
DECL|macro|LAP_ADDR_HEADER
mdefine_line|#define LAP_ADDR_HEADER 1  /* IrLAP Address Header */
DECL|macro|LAP_CTRL_HEADER
mdefine_line|#define LAP_CTRL_HEADER 1  /* IrLAP Control Header */
DECL|macro|LAP_COMP_HEADER
mdefine_line|#define LAP_COMP_HEADER 1  /* IrLAP Compression Header */
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
DECL|macro|LAP_MAX_HEADER
macro_line|#  define LAP_MAX_HEADER  (LAP_ADDR_HEADER + LAP_CTRL_HEADER + LAP_COMP_HEADER)
DECL|macro|IRDA_COMPRESSED
macro_line|#  define IRDA_COMPRESSED 1
DECL|macro|IRDA_NORMAL
macro_line|#  define IRDA_NORMAL     0
macro_line|#else
DECL|macro|LAP_MAX_HEADER
mdefine_line|#define LAP_MAX_HEADER (LAP_ADDR_HEADER + LAP_CTRL_HEADER)
macro_line|#endif
DECL|macro|BROADCAST
mdefine_line|#define BROADCAST  0xffffffff /* Broadcast device address */
DECL|macro|CBROADCAST
mdefine_line|#define CBROADCAST 0xfe       /* Connection broadcast address */
DECL|macro|XID_FORMAT
mdefine_line|#define XID_FORMAT 0x01       /* Discovery XID format */
DECL|macro|LAP_WINDOW_SIZE
mdefine_line|#define LAP_WINDOW_SIZE 8
DECL|macro|LAP_MAX_QUEUE
mdefine_line|#define LAP_MAX_QUEUE  10
DECL|macro|NR_EXPECTED
mdefine_line|#define NR_EXPECTED     1
DECL|macro|NR_UNEXPECTED
mdefine_line|#define NR_UNEXPECTED   0
DECL|macro|NR_INVALID
mdefine_line|#define NR_INVALID     -1
DECL|macro|NS_EXPECTED
mdefine_line|#define NS_EXPECTED     1
DECL|macro|NS_UNEXPECTED
mdefine_line|#define NS_UNEXPECTED   0
DECL|macro|NS_INVALID
mdefine_line|#define NS_INVALID     -1
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
multiline_comment|/*  &n; *  Just some shortcuts (may give you strange compiler errors if you change &n; *  them :-)&n; */
DECL|macro|irda_compress
mdefine_line|#define irda_compress    (*self-&gt;compessor.cp-&gt;compress)
DECL|macro|irda_comp_free
mdefine_line|#define irda_comp_free   (*self-&gt;compressor.cp-&gt;comp_free)
DECL|macro|irda_decompress
mdefine_line|#define irda_decompress  (*self-&gt;decompressor.cp-&gt;decompress)
DECL|macro|irda_decomp_free
mdefine_line|#define irda_decomp_free (*self-&gt;decompressor.cp-&gt;decomp_free)
DECL|macro|irda_incomp
mdefine_line|#define irda_incomp      (*self-&gt;decompressor.cp-&gt;incomp)
DECL|struct|irda_compressor
r_struct
id|irda_compressor
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
DECL|member|cp
r_struct
id|compressor
op_star
id|cp
suffix:semicolon
DECL|member|state
r_void
op_star
id|state
suffix:semicolon
multiline_comment|/* Not used by IrDA */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Main structure of IrLAP */
DECL|struct|irlap_cb
r_struct
id|irlap_cb
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Connection state */
DECL|member|state
r_volatile
id|IRLAP_STATE
id|state
suffix:semicolon
multiline_comment|/* Current state */
multiline_comment|/* Timers used by IrLAP */
DECL|member|query_timer
r_struct
id|timer_list
id|query_timer
suffix:semicolon
DECL|member|slot_timer
r_struct
id|timer_list
id|slot_timer
suffix:semicolon
DECL|member|discovery_timer
r_struct
id|timer_list
id|discovery_timer
suffix:semicolon
DECL|member|final_timer
r_struct
id|timer_list
id|final_timer
suffix:semicolon
DECL|member|poll_timer
r_struct
id|timer_list
id|poll_timer
suffix:semicolon
DECL|member|wd_timer
r_struct
id|timer_list
id|wd_timer
suffix:semicolon
DECL|member|backoff_timer
r_struct
id|timer_list
id|backoff_timer
suffix:semicolon
multiline_comment|/* Media busy stuff */
DECL|member|media_busy_timer
r_struct
id|timer_list
id|media_busy_timer
suffix:semicolon
DECL|member|media_busy
r_int
id|media_busy
suffix:semicolon
multiline_comment|/* Timeouts which will be different with different turn time */
DECL|member|slot_timeout
r_int
id|slot_timeout
suffix:semicolon
DECL|member|poll_timeout
r_int
id|poll_timeout
suffix:semicolon
DECL|member|final_timeout
r_int
id|final_timeout
suffix:semicolon
DECL|member|wd_timeout
r_int
id|wd_timeout
suffix:semicolon
DECL|member|txq
r_struct
id|sk_buff_head
id|txq
suffix:semicolon
multiline_comment|/* Frames to be transmitted */
DECL|member|txq_ultra
r_struct
id|sk_buff_head
id|txq_ultra
suffix:semicolon
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
multiline_comment|/* Connection address */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source device address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Destination device address */
DECL|member|retry_count
r_int
id|retry_count
suffix:semicolon
multiline_comment|/* Times tried to establish connection */
DECL|member|add_wait
r_int
id|add_wait
suffix:semicolon
multiline_comment|/* True if we are waiting for frame */
DECL|member|connect_pending
id|__u8
id|connect_pending
suffix:semicolon
DECL|member|disconnect_pending
id|__u8
id|disconnect_pending
suffix:semicolon
multiline_comment|/*  To send a faster RR if tx queue empty */
macro_line|#ifdef CONFIG_IRDA_FAST_RR
DECL|member|fast_RR_timeout
r_int
id|fast_RR_timeout
suffix:semicolon
DECL|member|fast_RR
r_int
id|fast_RR
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_FAST_RR */
DECL|member|N1
r_int
id|N1
suffix:semicolon
multiline_comment|/* N1 * F-timer = Negitiated link disconnect warning threshold */
DECL|member|N2
r_int
id|N2
suffix:semicolon
multiline_comment|/* N2 * F-timer = Negitiated link disconnect time */
DECL|member|N3
r_int
id|N3
suffix:semicolon
multiline_comment|/* Connection retry count */
DECL|member|local_busy
r_int
id|local_busy
suffix:semicolon
DECL|member|remote_busy
r_int
id|remote_busy
suffix:semicolon
DECL|member|xmitflag
r_int
id|xmitflag
suffix:semicolon
DECL|member|vs
id|__u8
id|vs
suffix:semicolon
multiline_comment|/* Next frame to be sent */
DECL|member|vr
id|__u8
id|vr
suffix:semicolon
multiline_comment|/* Next frame to be received */
DECL|member|va
id|__u8
id|va
suffix:semicolon
multiline_comment|/* Last frame acked */
DECL|member|window
r_int
id|window
suffix:semicolon
multiline_comment|/* Nr of I-frames allowed to send */
DECL|member|window_size
r_int
id|window_size
suffix:semicolon
multiline_comment|/* Current negotiated window size */
macro_line|#ifdef CONFIG_IRDA_DYNAMIC_WINDOW
DECL|member|line_capacity
id|__u32
id|line_capacity
suffix:semicolon
multiline_comment|/* Number of bytes allowed to send */
DECL|member|bytes_left
id|__u32
id|bytes_left
suffix:semicolon
multiline_comment|/* Number of bytes still allowed to transmit */
macro_line|#endif /* CONFIG_IRDA_DYNAMIC_WINDOW */
DECL|member|wx_list
r_struct
id|sk_buff_head
id|wx_list
suffix:semicolon
DECL|member|ack_required
id|__u8
id|ack_required
suffix:semicolon
multiline_comment|/* XID parameters */
DECL|member|S
id|__u8
id|S
suffix:semicolon
multiline_comment|/* Number of slots */
DECL|member|slot
id|__u8
id|slot
suffix:semicolon
multiline_comment|/* Random chosen slot */
DECL|member|s
id|__u8
id|s
suffix:semicolon
multiline_comment|/* Current slot */
DECL|member|frame_sent
r_int
id|frame_sent
suffix:semicolon
multiline_comment|/* Have we sent reply? */
DECL|member|discovery_log
id|hashbin_t
op_star
id|discovery_log
suffix:semicolon
DECL|member|discovery_cmd
id|discovery_t
op_star
id|discovery_cmd
suffix:semicolon
DECL|member|speed
id|__u32
id|speed
suffix:semicolon
DECL|member|qos_tx
r_struct
id|qos_info
id|qos_tx
suffix:semicolon
multiline_comment|/* QoS requested by peer */
DECL|member|qos_rx
r_struct
id|qos_info
id|qos_rx
suffix:semicolon
multiline_comment|/* QoS requested by self */
DECL|member|qos_dev
r_struct
id|qos_info
op_star
id|qos_dev
suffix:semicolon
multiline_comment|/* QoS supported by device */
DECL|member|notify
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* Callbacks to IrLMP */
DECL|member|mtt_required
r_int
id|mtt_required
suffix:semicolon
multiline_comment|/* Minumum turnaround time required */
DECL|member|xbofs_delay
r_int
id|xbofs_delay
suffix:semicolon
multiline_comment|/* Nr of XBOF&squot;s used to MTT */
DECL|member|bofs_count
r_int
id|bofs_count
suffix:semicolon
multiline_comment|/* Negotiated extra BOFs */
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
DECL|member|compressor
r_struct
id|irda_compressor
id|compressor
suffix:semicolon
DECL|member|decompressor
r_struct
id|irda_compressor
id|decompressor
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_COMPRESSION */
)brace
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|irlap
suffix:semicolon
multiline_comment|/* &n; *  Function prototypes &n; */
r_int
id|irlap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlap_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|irlap_cb
op_star
id|irlap_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
r_void
id|irlap_close
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_connect_request
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
id|__u32
id|daddr
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|sniff
)paren
suffix:semicolon
r_void
id|irlap_connect_response
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
suffix:semicolon
r_void
id|irlap_connect_indication
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
suffix:semicolon
r_void
id|irlap_connect_confirm
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|irlap_data_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
id|unreliable
)paren
suffix:semicolon
r_void
id|irlap_data_request
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
id|unreliable
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_ULTRA
r_void
id|irlap_unitdata_request
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlap_unitdata_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_ULTRA */
r_void
id|irlap_disconnect_request
c_func
(paren
r_struct
id|irlap_cb
op_star
)paren
suffix:semicolon
r_void
id|irlap_disconnect_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
id|LAP_REASON
id|reason
)paren
suffix:semicolon
r_void
id|irlap_status_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|quality_of_link
)paren
suffix:semicolon
r_void
id|irlap_test_request
c_func
(paren
id|__u8
op_star
id|info
comma
r_int
id|len
)paren
suffix:semicolon
r_void
id|irlap_discovery_request
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
id|discovery_t
op_star
id|discovery
)paren
suffix:semicolon
r_void
id|irlap_discovery_confirm
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
id|hashbin_t
op_star
id|discovery_log
)paren
suffix:semicolon
r_void
id|irlap_discovery_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
id|discovery_t
op_star
id|discovery
)paren
suffix:semicolon
r_void
id|irlap_reset_indication
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_reset_confirm
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlap_update_nr_received
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|nr
)paren
suffix:semicolon
r_int
id|irlap_validate_nr_received
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|nr
)paren
suffix:semicolon
r_int
id|irlap_validate_ns_received
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|ns
)paren
suffix:semicolon
r_int
id|irlap_generate_rand_time_slot
c_func
(paren
r_int
id|S
comma
r_int
id|s
)paren
suffix:semicolon
r_void
id|irlap_initiate_connection_state
c_func
(paren
r_struct
id|irlap_cb
op_star
)paren
suffix:semicolon
r_void
id|irlap_flush_all_queues
c_func
(paren
r_struct
id|irlap_cb
op_star
)paren
suffix:semicolon
r_void
id|irlap_change_speed
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
id|__u32
id|speed
comma
r_int
id|now
)paren
suffix:semicolon
r_void
id|irlap_wait_min_turn_around
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|qos_info
op_star
)paren
suffix:semicolon
r_void
id|irlap_init_qos_capabilities
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_struct
id|qos_info
op_star
)paren
suffix:semicolon
r_void
id|irlap_apply_default_connection_parameters
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_apply_connection_parameters
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_set_local_busy
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
DECL|macro|IRLAP_GET_HEADER_SIZE
mdefine_line|#define IRLAP_GET_HEADER_SIZE(self) 2 /* Will be different when we get VFIR */
DECL|macro|IRLAP_GET_TX_QUEUE_LEN
mdefine_line|#define IRLAP_GET_TX_QUEUE_LEN(self) skb_queue_len(&amp;self-&gt;txq)
macro_line|#endif
eof
