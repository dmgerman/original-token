multiline_comment|/*********************************************************************&n; *                &n; *                &n; * Filename:      irlap_event.h&n; * Version:       0.1&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Aug 16 00:59:29 1997&n; * Modified at:   Tue Dec 21 11:20:30 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef IRLAP_EVENT_H
DECL|macro|IRLAP_EVENT_H
mdefine_line|#define IRLAP_EVENT_H
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/discovery.h&gt;
r_struct
id|irlap_cb
suffix:semicolon
multiline_comment|/* IrLAP States */
r_typedef
r_enum
(brace
DECL|enumerator|LAP_NDM
id|LAP_NDM
comma
multiline_comment|/* Normal disconnected mode */
DECL|enumerator|LAP_QUERY
id|LAP_QUERY
comma
DECL|enumerator|LAP_REPLY
id|LAP_REPLY
comma
DECL|enumerator|LAP_CONN
id|LAP_CONN
comma
multiline_comment|/* Connect indication */
DECL|enumerator|LAP_SETUP
id|LAP_SETUP
comma
multiline_comment|/* Setting up connection */
DECL|enumerator|LAP_OFFLINE
id|LAP_OFFLINE
comma
multiline_comment|/* A really boring state */
DECL|enumerator|LAP_XMIT_P
id|LAP_XMIT_P
comma
DECL|enumerator|LAP_PCLOSE
id|LAP_PCLOSE
comma
DECL|enumerator|LAP_NRM_P
id|LAP_NRM_P
comma
multiline_comment|/* Normal response mode as primary */
DECL|enumerator|LAP_RESET_WAIT
id|LAP_RESET_WAIT
comma
DECL|enumerator|LAP_RESET
id|LAP_RESET
comma
DECL|enumerator|LAP_NRM_S
id|LAP_NRM_S
comma
multiline_comment|/* Normal response mode as secondary */
DECL|enumerator|LAP_XMIT_S
id|LAP_XMIT_S
comma
DECL|enumerator|LAP_SCLOSE
id|LAP_SCLOSE
comma
DECL|enumerator|LAP_RESET_CHECK
id|LAP_RESET_CHECK
comma
DECL|typedef|IRLAP_STATE
)brace
id|IRLAP_STATE
suffix:semicolon
multiline_comment|/* IrLAP Events */
r_typedef
r_enum
(brace
multiline_comment|/* Services events */
DECL|enumerator|DISCOVERY_REQUEST
id|DISCOVERY_REQUEST
comma
DECL|enumerator|CONNECT_REQUEST
id|CONNECT_REQUEST
comma
DECL|enumerator|CONNECT_RESPONSE
id|CONNECT_RESPONSE
comma
DECL|enumerator|DISCONNECT_REQUEST
id|DISCONNECT_REQUEST
comma
DECL|enumerator|DATA_REQUEST
id|DATA_REQUEST
comma
DECL|enumerator|RESET_REQUEST
id|RESET_REQUEST
comma
DECL|enumerator|RESET_RESPONSE
id|RESET_RESPONSE
comma
multiline_comment|/* Send events */
DECL|enumerator|SEND_I_CMD
id|SEND_I_CMD
comma
DECL|enumerator|SEND_UI_FRAME
id|SEND_UI_FRAME
comma
multiline_comment|/* Receive events */
DECL|enumerator|RECV_DISCOVERY_XID_CMD
id|RECV_DISCOVERY_XID_CMD
comma
DECL|enumerator|RECV_DISCOVERY_XID_RSP
id|RECV_DISCOVERY_XID_RSP
comma
DECL|enumerator|RECV_SNRM_CMD
id|RECV_SNRM_CMD
comma
DECL|enumerator|RECV_TEST_CMD
id|RECV_TEST_CMD
comma
DECL|enumerator|RECV_TEST_RSP
id|RECV_TEST_RSP
comma
DECL|enumerator|RECV_UA_RSP
id|RECV_UA_RSP
comma
DECL|enumerator|RECV_DM_RSP
id|RECV_DM_RSP
comma
DECL|enumerator|RECV_RD_RSP
id|RECV_RD_RSP
comma
DECL|enumerator|RECV_I_CMD
id|RECV_I_CMD
comma
DECL|enumerator|RECV_I_RSP
id|RECV_I_RSP
comma
DECL|enumerator|RECV_UI_FRAME
id|RECV_UI_FRAME
comma
DECL|enumerator|RECV_FRMR_RSP
id|RECV_FRMR_RSP
comma
DECL|enumerator|RECV_RR_CMD
id|RECV_RR_CMD
comma
DECL|enumerator|RECV_RR_RSP
id|RECV_RR_RSP
comma
DECL|enumerator|RECV_RNR_CMD
id|RECV_RNR_CMD
comma
DECL|enumerator|RECV_RNR_RSP
id|RECV_RNR_RSP
comma
DECL|enumerator|RECV_REJ_CMD
id|RECV_REJ_CMD
comma
DECL|enumerator|RECV_REJ_RSP
id|RECV_REJ_RSP
comma
DECL|enumerator|RECV_SREJ_CMD
id|RECV_SREJ_CMD
comma
DECL|enumerator|RECV_SREJ_RSP
id|RECV_SREJ_RSP
comma
DECL|enumerator|RECV_DISC_CMD
id|RECV_DISC_CMD
comma
multiline_comment|/* Timer events */
DECL|enumerator|SLOT_TIMER_EXPIRED
id|SLOT_TIMER_EXPIRED
comma
DECL|enumerator|QUERY_TIMER_EXPIRED
id|QUERY_TIMER_EXPIRED
comma
DECL|enumerator|FINAL_TIMER_EXPIRED
id|FINAL_TIMER_EXPIRED
comma
DECL|enumerator|POLL_TIMER_EXPIRED
id|POLL_TIMER_EXPIRED
comma
DECL|enumerator|DISCOVERY_TIMER_EXPIRED
id|DISCOVERY_TIMER_EXPIRED
comma
DECL|enumerator|WD_TIMER_EXPIRED
id|WD_TIMER_EXPIRED
comma
DECL|enumerator|BACKOFF_TIMER_EXPIRED
id|BACKOFF_TIMER_EXPIRED
comma
DECL|typedef|IRLAP_EVENT
)brace
id|IRLAP_EVENT
suffix:semicolon
multiline_comment|/*&n; *  Various things used by the IrLAP state machine&n; */
DECL|struct|irlap_info
r_struct
id|irlap_info
(brace
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
multiline_comment|/* Connection address */
DECL|member|control
id|__u8
id|control
suffix:semicolon
multiline_comment|/* Frame type */
DECL|member|cmd
id|__u8
id|cmd
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|pf
r_int
id|pf
suffix:semicolon
multiline_comment|/* Poll/final bit set */
DECL|member|nr
id|__u8
id|nr
suffix:semicolon
multiline_comment|/* Sequence number of next frame expected */
DECL|member|ns
id|__u8
id|ns
suffix:semicolon
multiline_comment|/* Sequence number of frame sent */
DECL|member|S
r_int
id|S
suffix:semicolon
multiline_comment|/* Number of slots */
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* Random chosen slot */
DECL|member|s
r_int
id|s
suffix:semicolon
multiline_comment|/* Current slot */
DECL|member|discovery
id|discovery_t
op_star
id|discovery
suffix:semicolon
multiline_comment|/* Discovery information */
)brace
suffix:semicolon
r_extern
r_const
r_char
op_star
id|irlap_state
(braket
)braket
suffix:semicolon
r_void
id|irlap_do_event
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
id|IRLAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|irlap_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|irlap_next_state
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
id|IRLAP_STATE
id|state
)paren
suffix:semicolon
r_void
id|irlap_print_event
c_func
(paren
id|IRLAP_EVENT
id|event
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#endif
eof
