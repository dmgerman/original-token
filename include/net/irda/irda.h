multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Mon May 10 09:51:13 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef NET_IRDA_H
DECL|macro|NET_IRDA_H
mdefine_line|#define NET_IRDA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE 
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|ALIGN
mdefine_line|#define ALIGN __attribute__((aligned))
DECL|macro|PACK
mdefine_line|#define PACK __attribute__((packed))
macro_line|#ifdef CONFIG_IRDA_DEBUG
r_extern
id|__u32
id|irda_debug
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
DECL|macro|IRDA_DEBUG_LEVEL
mdefine_line|#define IRDA_DEBUG_LEVEL 0
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (irda_debug &gt;= (n)) printk(KERN_DEBUG args)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func) &bslash;&n;if(!(expr)) { &bslash;&n;        printk( &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;,&bslash;&n;        #expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;        ##func}
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func)
macro_line|#endif /* CONFIG_IRDA_DEBUG */
DECL|macro|WARNING
mdefine_line|#define WARNING(args...) printk(KERN_WARNING args)
DECL|macro|MESSAGE
mdefine_line|#define MESSAGE(args...) printk(KERN_INFO args)
DECL|macro|ERROR
mdefine_line|#define ERROR(args...)   printk(KERN_ERR args)
DECL|macro|MSECS_TO_JIFFIES
mdefine_line|#define MSECS_TO_JIFFIES(ms) (ms*HZ/1000)
multiline_comment|/*&n; *  Magic numbers used by Linux/IR. Random numbers which must be unique to &n; *  give the best protection&n; */
DECL|macro|IRTTY_MAGIC
mdefine_line|#define IRTTY_MAGIC        0x2357
DECL|macro|LAP_MAGIC
mdefine_line|#define LAP_MAGIC          0x1357
DECL|macro|LMP_MAGIC
mdefine_line|#define LMP_MAGIC          0x4321
DECL|macro|LMP_LSAP_MAGIC
mdefine_line|#define LMP_LSAP_MAGIC     0x69333
DECL|macro|LMP_LAP_MAGIC
mdefine_line|#define LMP_LAP_MAGIC      0x3432
DECL|macro|IRDA_DEVICE_MAGIC
mdefine_line|#define IRDA_DEVICE_MAGIC  0x63454
DECL|macro|IAS_MAGIC
mdefine_line|#define IAS_MAGIC          0x007
DECL|macro|TTP_MAGIC
mdefine_line|#define TTP_MAGIC          0x241169
DECL|macro|TTP_TSAP_MAGIC
mdefine_line|#define TTP_TSAP_MAGIC     0x4345
DECL|macro|IROBEX_MAGIC
mdefine_line|#define IROBEX_MAGIC       0x341324
DECL|macro|HB_MAGIC
mdefine_line|#define HB_MAGIC           0x64534
DECL|macro|IRLAN_MAGIC
mdefine_line|#define IRLAN_MAGIC        0x754
DECL|macro|IAS_OBJECT_MAGIC
mdefine_line|#define IAS_OBJECT_MAGIC   0x34234
DECL|macro|IAS_ATTRIB_MAGIC
mdefine_line|#define IAS_ATTRIB_MAGIC   0x45232
DECL|macro|IAS_DEVICE_ID
mdefine_line|#define IAS_DEVICE_ID 0x5342 
DECL|macro|IAS_PNP_ID
mdefine_line|#define IAS_PNP_ID    0xd342
DECL|macro|IAS_OBEX_ID
mdefine_line|#define IAS_OBEX_ID   0x34323
DECL|macro|IAS_IRLAN_ID
mdefine_line|#define IAS_IRLAN_ID  0x34234
DECL|macro|IAS_IRCOMM_ID
mdefine_line|#define IAS_IRCOMM_ID 0x2343
DECL|macro|IAS_IRLPT_ID
mdefine_line|#define IAS_IRLPT_ID  0x9876
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
multiline_comment|/* IrDA Socket */
r_struct
id|tsap_cb
suffix:semicolon
DECL|struct|irda_sock
r_struct
id|irda_sock
(brace
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* my local address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* peer address */
DECL|member|ias_obj
r_struct
id|ias_object
op_star
id|ias_obj
suffix:semicolon
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
multiline_comment|/* TSAP used by this connection */
DECL|member|dtsap_sel
id|__u8
id|dtsap_sel
suffix:semicolon
multiline_comment|/* remote TSAP address */
DECL|member|stsap_sel
id|__u8
id|stsap_sel
suffix:semicolon
multiline_comment|/* local TSAP address */
DECL|member|max_sdu_size_rx
id|__u32
id|max_sdu_size_rx
suffix:semicolon
DECL|member|max_sdu_size_tx
id|__u32
id|max_sdu_size_tx
suffix:semicolon
DECL|member|max_data_size
id|__u32
id|max_data_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|qos_tx
r_struct
id|qos_info
id|qos_tx
suffix:semicolon
DECL|member|mask
id|__u16
id|mask
suffix:semicolon
multiline_comment|/* Hint bits mask */
DECL|member|hints
id|__u16
id|hints
suffix:semicolon
multiline_comment|/* Hint bits */
DECL|member|ckey
id|__u32
id|ckey
suffix:semicolon
multiline_comment|/* IrLMP client handle */
DECL|member|skey
id|__u32
id|skey
suffix:semicolon
multiline_comment|/* IrLMP service handle */
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots to use for discovery */
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|ias_wait
id|wait_queue_head_t
id|ias_wait
suffix:semicolon
multiline_comment|/* Wait for LM-IAS answer */
DECL|member|tx_flow
id|LOCAL_FLOW
id|tx_flow
suffix:semicolon
DECL|member|rx_flow
id|LOCAL_FLOW
id|rx_flow
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
DECL|enumerator|LOCK_NO_CHANGE
id|LOCK_NO_CHANGE
comma
DECL|enumerator|LOCK_LOCKED
id|LOCK_LOCKED
comma
DECL|enumerator|LOCK_UNLOCKED
id|LOCK_UNLOCKED
comma
DECL|typedef|LOCK_STATUS
)brace
id|LOCK_STATUS
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
multiline_comment|/*&n; *  Notify structure used between transport and link management layers&n; */
DECL|struct|notify_t
r_struct
id|notify_t
(brace
DECL|member|data_indication
r_int
(paren
op_star
id|data_indication
)paren
(paren
r_void
op_star
id|priv
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
r_int
(paren
op_star
id|udata_indication
)paren
(paren
r_void
op_star
id|priv
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
id|__u32
id|max_sdu_size
comma
id|__u8
id|max_header_size
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
id|__u32
id|max_sdu_size
comma
id|__u8
id|max_header_size
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
macro_line|#endif /* NET_IRDA_H */
eof
