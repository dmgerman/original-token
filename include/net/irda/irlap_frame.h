multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlap_frame.h&n; * Version:       0.9&n; * Description:   IrLAP frame declarations&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Aug 19 10:27:26 1997&n; * Modified at:   Tue Dec 21 11:10:12 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;,&n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef IRLAP_FRAME_H
DECL|macro|IRLAP_FRAME_H
mdefine_line|#define IRLAP_FRAME_H
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
multiline_comment|/* Frame types and templates */
DECL|macro|INVALID
mdefine_line|#define INVALID   0xff
multiline_comment|/* Unnumbered (U) commands */
DECL|macro|SNRM_CMD
mdefine_line|#define SNRM_CMD  0x83 /* Set Normal Response Mode */
DECL|macro|DISC_CMD
mdefine_line|#define DISC_CMD  0x43 /* Disconnect */
DECL|macro|XID_CMD
mdefine_line|#define XID_CMD   0x2f /* Exchange Station Identification */
DECL|macro|TEST_CMD
mdefine_line|#define TEST_CMD  0xe3 /* Test */
multiline_comment|/* Unnumbered responses */
DECL|macro|RNRM_RSP
mdefine_line|#define RNRM_RSP  0x83 /* Request Normal Response Mode */
DECL|macro|UA_RSP
mdefine_line|#define UA_RSP    0x63 /* Unnumbered Acknowledgement */
DECL|macro|FRMR_RSP
mdefine_line|#define FRMR_RSP  0x87 /* Frame Reject */
DECL|macro|DM_RSP
mdefine_line|#define DM_RSP    0x0f /* Disconnect Mode */
DECL|macro|RD_RSP
mdefine_line|#define RD_RSP    0x43 /* Request Disconnection */
DECL|macro|XID_RSP
mdefine_line|#define XID_RSP   0xaf /* Exchange Station Identification */
DECL|macro|TEST_RSP
mdefine_line|#define TEST_RSP  0xe3 /* Test frame */
multiline_comment|/* Supervisory (S) */
DECL|macro|RR
mdefine_line|#define RR        0x01 /* Receive Ready */
DECL|macro|REJ
mdefine_line|#define REJ       0x09 /* Reject */
DECL|macro|RNR
mdefine_line|#define RNR       0x05 /* Receive Not Ready */
DECL|macro|SREJ
mdefine_line|#define SREJ      0x0d /* Selective Reject */
multiline_comment|/* Information (I) */
DECL|macro|I_FRAME
mdefine_line|#define I_FRAME   0x00 /* Information Format */
DECL|macro|UI_FRAME
mdefine_line|#define UI_FRAME  0x03 /* Unnumbered Information */
DECL|macro|CMD_FRAME
mdefine_line|#define CMD_FRAME 0x01
DECL|macro|RSP_FRAME
mdefine_line|#define RSP_FRAME 0x00
DECL|macro|PF_BIT
mdefine_line|#define PF_BIT    0x10 /* Poll/final bit */
DECL|struct|xid_frame
r_struct
id|xid_frame
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
DECL|member|ident
id|__u8
id|ident
suffix:semicolon
multiline_comment|/* Should always be XID_FORMAT */
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
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
multiline_comment|/* Discovery flags */
DECL|member|slotnr
id|__u8
id|slotnr
suffix:semicolon
DECL|member|version
id|__u8
id|version
suffix:semicolon
DECL|variable|PACK
)brace
id|PACK
suffix:semicolon
DECL|struct|test_frame
r_struct
id|test_frame
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
DECL|variable|PACK
)brace
id|PACK
suffix:semicolon
DECL|struct|ua_frame
r_struct
id|ua_frame
(brace
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source device address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Dest device address */
DECL|variable|PACK
)brace
id|PACK
suffix:semicolon
DECL|struct|i_frame
r_struct
id|i_frame
(brace
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:semicolon
DECL|variable|PACK
)brace
id|PACK
suffix:semicolon
DECL|struct|snrm_frame
r_struct
id|snrm_frame
(brace
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|ncaddr
id|__u8
id|ncaddr
suffix:semicolon
DECL|variable|PACK
)brace
id|PACK
suffix:semicolon
r_void
id|irlap_send_discovery_xid_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|S
comma
id|__u8
id|s
comma
id|__u8
id|command
comma
id|discovery_t
op_star
id|discovery
)paren
suffix:semicolon
r_void
id|irlap_send_snrm_frame
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
id|irlap_send_test_frame
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
id|sk_buff
op_star
id|cmd
)paren
suffix:semicolon
r_void
id|irlap_send_ua_response_frame
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
id|irlap_send_dm_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_send_rd_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_send_disc_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irlap_send_rr_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|command
)paren
suffix:semicolon
r_void
id|irlap_send_data_primary
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
id|irlap_send_data_primary_poll
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
id|irlap_send_data_secondary
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
id|irlap_send_data_secondary_final
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
id|irlap_resend_rejected_frames
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
r_int
id|command
)paren
suffix:semicolon
r_void
id|irlap_resend_rejected_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|command
)paren
suffix:semicolon
r_void
id|irlap_send_i_frame
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
id|command
)paren
suffix:semicolon
r_void
id|irlap_send_ui_frame
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
comma
id|__u8
id|caddr
comma
r_int
id|command
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#endif
eof
