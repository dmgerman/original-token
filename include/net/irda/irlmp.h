multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlmp.h&n; * Version:       0.3&n; * Description:   IrDA Link Management Protocol (LMP) layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 17 20:54:32 1997&n; * Modified at:   Mon Dec  7 21:11:32 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli &lt;dagb@cs.uit.no&gt;, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLMP_H
DECL|macro|IRLMP_H
mdefine_line|#define IRLMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;irmod.h&quot;
macro_line|#include &quot;qos.h&quot;
macro_line|#include &quot;irlap.h&quot;
macro_line|#include &quot;irlmp_event.h&quot;
macro_line|#include &quot;irqueue.h&quot;
multiline_comment|/* LSAP-SEL&squot;s */
DECL|macro|LSAP_MASK
mdefine_line|#define LSAP_MASK     0x7f
DECL|macro|LSAP_IAS
mdefine_line|#define LSAP_IAS      0x00
DECL|macro|LSAP_ANY
mdefine_line|#define LSAP_ANY      0xff
multiline_comment|/* Predefined LSAPs used by the various servers */
DECL|macro|TSAP_IRLAN
mdefine_line|#define TSAP_IRLAN    0x05
DECL|macro|LSAP_IRLPT
mdefine_line|#define LSAP_IRLPT    0x06
DECL|macro|TSAP_IROBEX
mdefine_line|#define TSAP_IROBEX   0x07
DECL|macro|TSAP_IRCOMM
mdefine_line|#define TSAP_IRCOMM   0x08
DECL|macro|LMP_HEADER
mdefine_line|#define LMP_HEADER          2    /* Dest LSAP + Source LSAP */
DECL|macro|LMP_CONTROL_HEADER
mdefine_line|#define LMP_CONTROL_HEADER  4
DECL|macro|LMP_MAX_HEADER
mdefine_line|#define LMP_MAX_HEADER      (LAP_HEADER+LMP_HEADER)
DECL|macro|LM_MAX_CONNECTIONS
mdefine_line|#define LM_MAX_CONNECTIONS  10
multiline_comment|/* Hint bit positions for first hint byte */
DECL|macro|HINT_PNP
mdefine_line|#define HINT_PNP         0x01
DECL|macro|HINT_PDA
mdefine_line|#define HINT_PDA         0x02
DECL|macro|HINT_COMPUTER
mdefine_line|#define HINT_COMPUTER    0x04
DECL|macro|HINT_PRINTER
mdefine_line|#define HINT_PRINTER     0x08
DECL|macro|HINT_MODEM
mdefine_line|#define HINT_MODEM       0x10
DECL|macro|HINT_FAX
mdefine_line|#define HINT_FAX         0x20
DECL|macro|HINT_LAN
mdefine_line|#define HINT_LAN         0x40
DECL|macro|HINT_EXTENSION
mdefine_line|#define HINT_EXTENSION   0x80
multiline_comment|/* Hint bit positions for second hint byte (first extension byte) */
DECL|macro|HINT_TELEPHONY
mdefine_line|#define HINT_TELEPHONY   0x01
DECL|macro|HINT_FILE_SERVER
mdefine_line|#define HINT_FILE_SERVER 0x02
DECL|macro|HINT_COMM
mdefine_line|#define HINT_COMM        0x04
DECL|macro|HINT_MESSAGE
mdefine_line|#define HINT_MESSAGE     0x08
DECL|macro|HINT_HTTP
mdefine_line|#define HINT_HTTP        0x10
DECL|macro|HINT_OBEX
mdefine_line|#define HINT_OBEX        0x20
r_typedef
r_enum
(brace
DECL|enumerator|S_PNP
id|S_PNP
comma
DECL|enumerator|S_PDA
id|S_PDA
comma
DECL|enumerator|S_COMPUTER
id|S_COMPUTER
comma
DECL|enumerator|S_PRINTER
id|S_PRINTER
comma
DECL|enumerator|S_MODEM
id|S_MODEM
comma
DECL|enumerator|S_FAX
id|S_FAX
comma
DECL|enumerator|S_LAN
id|S_LAN
comma
DECL|enumerator|S_TELEPHONY
id|S_TELEPHONY
comma
DECL|enumerator|S_COMM
id|S_COMM
comma
DECL|enumerator|S_OBEX
id|S_OBEX
comma
DECL|typedef|SERVICE
)brace
id|SERVICE
suffix:semicolon
DECL|macro|S_END
mdefine_line|#define S_END 0xff
DECL|macro|CLIENT
mdefine_line|#define CLIENT 1
DECL|macro|SERVER
mdefine_line|#define SERVER 2
DECL|typedef|DISCOVERY_CALLBACK
r_typedef
r_void
(paren
op_star
id|DISCOVERY_CALLBACK
)paren
(paren
id|DISCOVERY
op_star
)paren
suffix:semicolon
DECL|struct|irlmp_registration
r_struct
id|irlmp_registration
(brace
DECL|member|queue
id|QUEUE
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|service
r_int
id|service
suffix:semicolon
multiline_comment|/* LAN, OBEX, COMM etc. */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* Client or server or both */
DECL|member|discovery_callback
id|DISCOVERY_CALLBACK
id|discovery_callback
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|lap_cb
suffix:semicolon
multiline_comment|/* Forward decl. */
multiline_comment|/*&n; *  Information about each logical LSAP connection&n; */
DECL|struct|lsap_cb
r_struct
id|lsap_cb
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
DECL|member|connected
r_int
id|connected
suffix:semicolon
DECL|member|persistent
r_int
id|persistent
suffix:semicolon
DECL|member|stats
r_struct
id|irda_statistics
id|stats
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Source (this) LSAP address */
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* Destination LSAP address (if connected) */
DECL|member|tmp_skb
r_struct
id|sk_buff
op_star
id|tmp_skb
suffix:semicolon
multiline_comment|/* Store skb here while connecting */
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
DECL|member|lsap_state
id|IRLMP_STATE
id|lsap_state
suffix:semicolon
multiline_comment|/* Connection state */
DECL|member|notify
r_struct
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* Indication/Confirm entry points */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS for this connection */
DECL|member|lap
r_struct
id|lap_cb
op_star
id|lap
suffix:semicolon
multiline_comment|/* Pointer to LAP connection structure */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Information about each registred IrLAP layer&n; */
DECL|struct|lap_cb
r_struct
id|lap_cb
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
DECL|member|reason
r_int
id|reason
suffix:semicolon
multiline_comment|/* LAP disconnect reason */
DECL|member|lap_state
id|IRLMP_STATE
id|lap_state
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* Instance of IrLAP layer */
DECL|member|lsaps
id|hashbin_t
op_star
id|lsaps
suffix:semicolon
multiline_comment|/* LSAP associated with this link */
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
DECL|member|cachelog
id|hashbin_t
op_star
id|cachelog
suffix:semicolon
multiline_comment|/* Discovered devices for this link */
DECL|member|qos
r_struct
id|qos_info
op_star
id|qos
suffix:semicolon
multiline_comment|/* LAP QoS for this session */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Used for caching the last slsap-&gt;dlsap-&gt;handle mapping&n; */
r_typedef
r_struct
(brace
DECL|member|valid
r_int
id|valid
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
DECL|typedef|CACHE_ENTRY
)brace
id|CACHE_ENTRY
suffix:semicolon
multiline_comment|/*&n; *  Main structure for IrLMP&n; */
DECL|struct|irlmp_cb
r_struct
id|irlmp_cb
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|conflict_flag
id|__u8
id|conflict_flag
suffix:semicolon
multiline_comment|/* int discovery; */
DECL|member|discovery_rsp
id|DISCOVERY
id|discovery_rsp
suffix:semicolon
multiline_comment|/* Discovery response to use by IrLAP */
DECL|member|discovery_cmd
id|DISCOVERY
id|discovery_cmd
suffix:semicolon
multiline_comment|/* Discovery command to use by IrLAP */
DECL|member|free_lsap_sel
r_int
id|free_lsap_sel
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_CACHE_LAST_LSAP
DECL|member|cache
id|CACHE_ENTRY
id|cache
suffix:semicolon
multiline_comment|/* Caching last slsap-&gt;dlsap-&gt;handle mapping */
macro_line|#endif
DECL|member|discovery_timer
r_struct
id|timer_list
id|discovery_timer
suffix:semicolon
DECL|member|links
id|hashbin_t
op_star
id|links
suffix:semicolon
multiline_comment|/* IrLAP connection table */
DECL|member|unconnected_lsaps
id|hashbin_t
op_star
id|unconnected_lsaps
suffix:semicolon
DECL|member|registry
id|hashbin_t
op_star
id|registry
suffix:semicolon
DECL|member|hint
id|__u8
id|hint
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Hint bits */
)brace
suffix:semicolon
multiline_comment|/* Prototype declarations */
r_int
id|irlmp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|lsap_cb
op_star
id|irlmp_open_lsap
c_func
(paren
id|__u8
id|slsap
comma
r_struct
id|notify_t
op_star
id|notify
)paren
suffix:semicolon
r_void
id|irlmp_close_lsap
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlmp_register_layer
c_func
(paren
r_int
id|service
comma
r_int
id|type
comma
r_int
id|do_discovery
comma
id|DISCOVERY_CALLBACK
)paren
suffix:semicolon
r_void
id|irlmp_unregister_layer
c_func
(paren
r_int
id|service
comma
r_int
id|type
)paren
suffix:semicolon
r_void
id|irlmp_register_irlap
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
id|__u32
id|saddr
comma
r_struct
id|notify_t
op_star
)paren
suffix:semicolon
r_void
id|irlmp_unregister_irlap
c_func
(paren
id|__u32
id|saddr
)paren
suffix:semicolon
r_void
id|irlmp_connect_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
id|__u8
id|dlsap_sel
comma
id|__u32
id|daddr
comma
r_struct
id|qos_info
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_connect_indication
c_func
(paren
r_struct
id|lsap_cb
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
id|irlmp_connect_response
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_connect_confirm
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_disconnect_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|irlmp_disconnect_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|irlmp_discovery_confirm
c_func
(paren
r_struct
id|lap_cb
op_star
comma
id|hashbin_t
op_star
id|discovery_log
)paren
suffix:semicolon
r_void
id|irlmp_discovery_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
id|DISCOVERY
op_star
id|discovery
)paren
suffix:semicolon
r_void
id|irlmp_discovery_request
c_func
(paren
r_int
id|nslots
)paren
suffix:semicolon
id|DISCOVERY
op_star
id|irlmp_get_discovery_response
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_data_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_udata_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_data_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_udata_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_status_request
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_status_indication
c_func
(paren
id|LINK_STATUS
id|link
comma
id|LOCK_STATUS
id|lock
)paren
suffix:semicolon
r_int
id|irlmp_slsap_inuse
c_func
(paren
id|__u8
id|slsap
)paren
suffix:semicolon
id|__u8
id|irlmp_find_free_slsap
c_func
(paren
r_void
)paren
suffix:semicolon
id|LM_REASON
id|irlmp_convert_lap_reason
c_func
(paren
id|LAP_REASON
)paren
suffix:semicolon
r_extern
r_struct
id|irlmp_cb
op_star
id|irlmp
suffix:semicolon
macro_line|#endif
eof
