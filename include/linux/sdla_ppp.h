multiline_comment|/*****************************************************************************&n;* sdla_ppp.h&t;Sangoma PPP firmware API definitions.&n;*&n;* Author:&t;Gene Kozin&t;&lt;74604.152@compuserve.com&gt;&n;*&n;* Copyright:&t;(c) 1995-1997 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jan 06, 1997&t;Gene Kozin&t;v2.0&n;* Apr 11, 1996&t;Gene Kozin&t;Initial version.&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLA_PPP_H
DECL|macro|_SDLA_PPP_H
mdefine_line|#define&t;_SDLA_PPP_H
multiline_comment|/*----------------------------------------------------------------------------&n; * Notes:&n; * ------&n; * 1. All structures defined in this file are byte-alined.  To ensure&n; *    portability of this code between different platforms and compilers, one&n; *    of the following defines must be defined before including this file:&n; *&n; *&t;Compiler&t;Platform&t;Define&t;&t;Use option&n; *&t;--------&t;--------&t;------&t;&t;----------&n; *&t;GNU C&t;&t;Linux&t;&t;_GNUC_&t;&t;-&n; *&t;Microsoft C&t;DOS/Windows&t;_MSC_&t;&t;-&n; */
macro_line|#ifdef&t;&t;_GNUC_
macro_line|#  ifndef&t;PACKED
DECL|macro|PACKED
macro_line|#    define&t;PACKED&t;__attribute__((packed))
macro_line|#  endif&t;/* PACKED */
macro_line|#else
DECL|macro|PACKED
macro_line|#  define&t;PACKED
macro_line|#endif
macro_line|#ifdef&t;&t;_MSC_
macro_line|#  pragma&t;pack(1)
macro_line|#endif
multiline_comment|/* Adapter memory layout and important constants */
DECL|macro|PPP502_MB_VECT
mdefine_line|#define&t;PPP502_MB_VECT&t;0xA000&t;/* mailbox window vector */
DECL|macro|PPP502_MB_OFFS
mdefine_line|#define&t;PPP502_MB_OFFS&t;0x1C00&t;/* mailbox offset */
DECL|macro|PPP502_FLG_OFFS
mdefine_line|#define&t;PPP502_FLG_OFFS&t;0&t;/* status flags offset */
DECL|macro|PPP502_BUF_OFFS
mdefine_line|#define&t;PPP502_BUF_OFFS&t;0x0010&t;/* buffer info block offset */
DECL|macro|PPP508_MB_VECT
mdefine_line|#define&t;PPP508_MB_VECT&t;0xE000&t;/* mailbox window vector */
DECL|macro|PPP508_MB_OFFS
mdefine_line|#define&t;PPP508_MB_OFFS&t;0&t;/* mailbox offset */
DECL|macro|PPP508_FLG_OFFS
mdefine_line|#define&t;PPP508_FLG_OFFS&t;0x1000&t;/* status flags offset */
DECL|macro|PPP508_BUF_OFFS
mdefine_line|#define&t;PPP508_BUF_OFFS&t;0x1100&t;/* buffer info block offset */
DECL|macro|PPP_MAX_DATA
mdefine_line|#define PPP_MAX_DATA&t;1008&t;/* command block data buffer length */
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP Command Block.&n; */
DECL|struct|ppp_cmd
r_typedef
r_struct
id|ppp_cmd
(brace
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* command code */
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* length of data buffer */
DECL|member|PACKED
r_int
r_char
id|result
id|PACKED
suffix:semicolon
multiline_comment|/* return code */
DECL|member|PACKED
r_int
r_char
id|rsrv
(braket
l_int|11
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|typedef|ppp_cmd_t
)brace
id|ppp_cmd_t
suffix:semicolon
multiline_comment|/* &squot;command&squot; field defines */
DECL|macro|PPP_READ_CODE_VERSION
mdefine_line|#define PPP_READ_CODE_VERSION&t;0x10&t;/* configuration commands */
DECL|macro|PPP_SET_CONFIG
mdefine_line|#define PPP_SET_CONFIG&t;&t;0x05
DECL|macro|PPP_READ_CONFIG
mdefine_line|#define PPP_READ_CONFIG&t;&t;0x06
DECL|macro|PPP_SET_INTR_FLAGS
mdefine_line|#define&t;PPP_SET_INTR_FLAGS&t;0x20
DECL|macro|PPP_READ_INTR_FLAGS
mdefine_line|#define&t;PPP_READ_INTR_FLAGS&t;0x21
DECL|macro|PPP_SET_INBOUND_AUTH
mdefine_line|#define&t;PPP_SET_INBOUND_AUTH&t;0x30
DECL|macro|PPP_SET_OUTBOUND_AUTH
mdefine_line|#define&t;PPP_SET_OUTBOUND_AUTH&t;0x31
DECL|macro|PPP_GET_CONNECTION_INFO
mdefine_line|#define&t;PPP_GET_CONNECTION_INFO&t;0x32
DECL|macro|PPP_COMM_ENABLE
mdefine_line|#define PPP_COMM_ENABLE&t;&t;0x03&t;/* operational commands */
DECL|macro|PPP_COMM_DISABLE
mdefine_line|#define PPP_COMM_DISABLE&t;0x04
DECL|macro|PPP_SEND_SIGN_FRAME
mdefine_line|#define&t;PPP_SEND_SIGN_FRAME&t;0x23
DECL|macro|PPP_READ_SIGN_RESPONSE
mdefine_line|#define&t;PPP_READ_SIGN_RESPONSE&t;0x24
DECL|macro|PPP_DATALINE_MONITOR
mdefine_line|#define&t;PPP_DATALINE_MONITOR&t;0x33
DECL|macro|PPP_READ_STATISTICS
mdefine_line|#define PPP_READ_STATISTICS&t;0x07&t;/* statistics commands */
DECL|macro|PPP_FLUSH_STATISTICS
mdefine_line|#define PPP_FLUSH_STATISTICS&t;0x08
DECL|macro|PPP_READ_ERROR_STATS
mdefine_line|#define PPP_READ_ERROR_STATS&t;0x09
DECL|macro|PPP_FLUSH_ERROR_STATS
mdefine_line|#define PPP_FLUSH_ERROR_STATS&t;0x0A
DECL|macro|PPP_READ_PACKET_STATS
mdefine_line|#define PPP_READ_PACKET_STATS&t;0x12
DECL|macro|PPP_FLUSH_PACKET_STATS
mdefine_line|#define PPP_FLUSH_PACKET_STATS&t;0x13
DECL|macro|PPP_READ_LCP_STATS
mdefine_line|#define PPP_READ_LCP_STATS&t;0x14
DECL|macro|PPP_FLUSH_LCP_STATS
mdefine_line|#define PPP_FLUSH_LCP_STATS&t;0x15
DECL|macro|PPP_READ_LPBK_STATS
mdefine_line|#define PPP_READ_LPBK_STATS&t;0x16
DECL|macro|PPP_FLUSH_LPBK_STATS
mdefine_line|#define PPP_FLUSH_LPBK_STATS&t;0x17
DECL|macro|PPP_READ_IPCP_STATS
mdefine_line|#define PPP_READ_IPCP_STATS&t;0x18
DECL|macro|PPP_FLUSH_IPCP_STATS
mdefine_line|#define PPP_FLUSH_IPCP_STATS&t;0x19
DECL|macro|PPP_READ_IPXCP_STATS
mdefine_line|#define PPP_READ_IPXCP_STATS&t;0x1A
DECL|macro|PPP_FLUSH_IPXCP_STATS
mdefine_line|#define PPP_FLUSH_IPXCP_STATS&t;0x1B
DECL|macro|PPP_READ_PAP_STATS
mdefine_line|#define PPP_READ_PAP_STATS&t;0x1C
DECL|macro|PPP_FLUSH_PAP_STATS
mdefine_line|#define PPP_FLUSH_PAP_STATS&t;0x1D
DECL|macro|PPP_READ_CHAP_STATS
mdefine_line|#define PPP_READ_CHAP_STATS&t;0x1E
DECL|macro|PPP_FLUSH_CHAP_STATS
mdefine_line|#define PPP_FLUSH_CHAP_STATS&t;0x1F
multiline_comment|/* &squot;result&squot; field defines */
DECL|macro|PPPRES_OK
mdefine_line|#define PPPRES_OK&t;&t;0x00&t;/* command executed successfully */
DECL|macro|PPPRES_INVALID_STATE
mdefine_line|#define&t;PPPRES_INVALID_STATE&t;0x09&t;/* invalid command in this context */
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP Mailbox.&n; *&t;This structure is located at offset PPP???_MB_OFFS into PPP???_MB_VECT&n; */
DECL|struct|ppp_mbox
r_typedef
r_struct
id|ppp_mbox
(brace
DECL|member|PACKED
r_int
r_char
id|flag
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: command execution flag */
DECL|member|PACKED
id|ppp_cmd_t
id|cmd
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: command block */
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: variable length data buffer */
DECL|typedef|ppp_mbox_t
)brace
id|ppp_mbox_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP Status Flags.&n; *&t;This structure is located at offset PPP???_FLG_OFFS into&n; *&t;PPP???_MB_VECT.&n; */
DECL|struct|ppp_flags
r_typedef
r_struct
id|ppp_flags
(brace
DECL|member|PACKED
r_int
r_char
id|iflag
id|PACKED
suffix:semicolon
multiline_comment|/* 00: interrupt flag */
DECL|member|PACKED
r_int
r_char
id|imask
id|PACKED
suffix:semicolon
multiline_comment|/* 01: interrupt mask */
DECL|member|PACKED
r_int
r_char
id|resrv
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|mstatus
id|PACKED
suffix:semicolon
multiline_comment|/* 03: modem status */
DECL|member|PACKED
r_int
r_char
id|lcp_state
id|PACKED
suffix:semicolon
multiline_comment|/* 04: LCP state */
DECL|member|PACKED
r_int
r_char
id|ppp_phase
id|PACKED
suffix:semicolon
multiline_comment|/* 05: PPP phase */
DECL|member|PACKED
r_int
r_char
id|ip_state
id|PACKED
suffix:semicolon
multiline_comment|/* 06: IPCP state */
DECL|member|PACKED
r_int
r_char
id|ipx_state
id|PACKED
suffix:semicolon
multiline_comment|/* 07: IPXCP state */
DECL|member|PACKED
r_int
r_char
id|pap_state
id|PACKED
suffix:semicolon
multiline_comment|/* 08: PAP state */
DECL|member|PACKED
r_int
r_char
id|chap_state
id|PACKED
suffix:semicolon
multiline_comment|/* 09: CHAP state */
DECL|member|PACKED
r_int
r_int
id|disc_cause
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: disconnection cause */
DECL|typedef|ppp_flags_t
)brace
id|ppp_flags_t
suffix:semicolon
multiline_comment|/* &squot;iflag&squot; defines */
DECL|macro|PPP_INTR_RXRDY
mdefine_line|#define&t;PPP_INTR_RXRDY&t;&t;0x01&t;/* Rx ready */
DECL|macro|PPP_INTR_TXRDY
mdefine_line|#define&t;PPP_INTR_TXRDY&t;&t;0x02&t;/* Tx ready */
DECL|macro|PPP_INTR_MODEM
mdefine_line|#define&t;PPP_INTR_MODEM&t;&t;0x04&t;/* modem status change (DCD, CTS) */
DECL|macro|PPP_INTR_CMD
mdefine_line|#define&t;PPP_INTR_CMD&t;&t;0x08&t;/* interface command completed */
DECL|macro|PPP_INTR_DISC
mdefine_line|#define&t;PPP_INTR_DISC&t;&t;0x10&t;/* data link disconnected */
DECL|macro|PPP_INTR_OPEN
mdefine_line|#define&t;PPP_INTR_OPEN&t;&t;0x20&t;/* data link open */
DECL|macro|PPP_INTR_DROP_DTR
mdefine_line|#define&t;PPP_INTR_DROP_DTR&t;0x40&t;/* DTR drop timeout expired */
multiline_comment|/* &squot;mstatus&squot; defines */
DECL|macro|PPP_MDM_DCD
mdefine_line|#define&t;PPP_MDM_DCD&t;&t;0x08&t;/* mdm_status: DCD */
DECL|macro|PPP_MDM_CTS
mdefine_line|#define&t;PPP_MDM_CTS&t;&t;0x20&t;/* mdm_status: CTS */
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP Buffer Info.&n; *&t;This structure is located at offset PPP502_BUF_OFFS into&n; *&t;PPP502_MB_VECT.&n; */
DECL|struct|ppp502_buf_info
r_typedef
r_struct
id|ppp502_buf_info
(brace
DECL|member|PACKED
r_int
r_int
id|txb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 00: number of transmit buffers */
DECL|member|PACKED
r_int
r_int
id|txb_offs
id|PACKED
suffix:semicolon
multiline_comment|/* 02: offset of the buffer ctl. */
DECL|member|PACKED
r_int
r_char
id|rsrv1
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|rxb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 08: number of receive buffers */
DECL|member|PACKED
r_int
r_int
id|rxb_offs
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: offset of the buffer ctl. */
DECL|member|PACKED
r_int
r_char
id|rsrv2
(braket
l_int|2
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|rxb_next
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: index of the next buffer */
DECL|typedef|ppp502_buf_info_t
)brace
id|ppp502_buf_info_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * PPP Buffer Info.&n; *&t;This structure is located at offset PPP508_BUF_OFFS into&n; *&t;PPP508_MB_VECT.&n; */
DECL|struct|ppp508_buf_info
r_typedef
r_struct
id|ppp508_buf_info
(brace
DECL|member|PACKED
r_int
r_int
id|txb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 00: number of transmit buffers */
DECL|member|PACKED
r_int
r_int
id|txb_ptr
id|PACKED
suffix:semicolon
multiline_comment|/* 02: pointer to the buffer ctl. */
DECL|member|PACKED
r_int
r_char
id|rsrv1
(braket
l_int|26
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|rxb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 20: number of receive buffers */
DECL|member|PACKED
r_int
r_int
id|rxb_ptr
id|PACKED
suffix:semicolon
multiline_comment|/* 22: pointer to the buffer ctl. */
DECL|member|PACKED
r_int
r_int
id|rxb1_ptr
id|PACKED
suffix:semicolon
multiline_comment|/* 26: pointer to the first buf.ctl. */
DECL|member|PACKED
r_int
r_int
id|rxb_base
id|PACKED
suffix:semicolon
multiline_comment|/* 2A: pointer to the buffer base */
DECL|member|PACKED
r_int
r_char
id|rsrv2
(braket
l_int|2
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|rxb_end
id|PACKED
suffix:semicolon
multiline_comment|/* 30: pointer to the buffer end */
DECL|typedef|ppp508_buf_info_t
)brace
id|ppp508_buf_info_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Transmit/Receive Buffer Control Block.&n; */
DECL|struct|ppp_buf_ctl
r_typedef
r_struct
id|ppp_buf_ctl
(brace
DECL|member|PACKED
r_int
r_char
id|flag
id|PACKED
suffix:semicolon
multiline_comment|/* 00: &squot;buffer ready&squot; flag */
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* 01: length of data */
DECL|member|PACKED
r_int
r_char
id|reserved1
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 03: */
DECL|member|PACKED
r_int
r_char
id|proto
id|PACKED
suffix:semicolon
multiline_comment|/* 04: protocol */
DECL|member|PACKED
r_int
r_int
id|timestamp
id|PACKED
suffix:semicolon
multiline_comment|/* 05: time stamp (Rx only) */
DECL|member|PACKED
r_int
r_char
id|reserved2
(braket
l_int|5
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 07: */
r_union
(brace
DECL|member|o_p
r_int
r_int
id|o_p
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 1C: buffer offset &amp; page (S502) */
DECL|member|ptr
r_int
r_int
id|ptr
suffix:semicolon
multiline_comment|/* 1C: buffer pointer (S508) */
DECL|member|PACKED
)brace
id|buf
id|PACKED
suffix:semicolon
DECL|typedef|ppp_buf_ctl_t
)brace
id|ppp_buf_ctl_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S502 Adapter Configuration Block (passed to the PPP_SET_CONFIG command).&n; */
DECL|struct|ppp502_conf
r_typedef
r_struct
id|ppp502_conf
(brace
DECL|member|PACKED
r_int
r_char
id|line_speed
id|PACKED
suffix:semicolon
multiline_comment|/* 00: 0 - external clk. */
DECL|member|PACKED
r_int
r_int
id|txbuf_num
id|PACKED
suffix:semicolon
multiline_comment|/* 01: number of Tx buffers */
DECL|member|PACKED
r_int
r_int
id|conf_flags
id|PACKED
suffix:semicolon
multiline_comment|/* 03: configuration bits */
DECL|member|PACKED
r_int
r_int
id|mtu_local
id|PACKED
suffix:semicolon
multiline_comment|/* 05: local MTU */
DECL|member|PACKED
r_int
r_int
id|mtu_remote
id|PACKED
suffix:semicolon
multiline_comment|/* 07: remote MTU */
DECL|member|PACKED
r_int
r_int
id|restart_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 09: restart timer */
DECL|member|PACKED
r_int
r_int
id|auth_rsrt_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 0B: authentication timer */
DECL|member|PACKED
r_int
r_int
id|auth_wait_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 0D: authentication timer */
DECL|member|PACKED
r_int
r_int
id|mdm_fail_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 0F: modem failure timer */
DECL|member|PACKED
r_int
r_int
id|dtr_drop_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 11: DTR drop timer */
DECL|member|PACKED
r_int
r_int
id|connect_tmout
id|PACKED
suffix:semicolon
multiline_comment|/* 13: connection timeout */
DECL|member|PACKED
r_int
r_int
id|conf_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 15: max. retry */
DECL|member|PACKED
r_int
r_int
id|term_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 17: max. retry */
DECL|member|PACKED
r_int
r_int
id|fail_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 19: max. retry */
DECL|member|PACKED
r_int
r_int
id|auth_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 1B: max. retry */
DECL|member|PACKED
r_int
r_char
id|auth_options
id|PACKED
suffix:semicolon
multiline_comment|/* 1D: authentication opt. */
DECL|member|PACKED
r_int
r_char
id|ip_options
id|PACKED
suffix:semicolon
multiline_comment|/* 1E: IP options */
DECL|member|PACKED
r_int
r_char
id|ip_local
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 1F: local IP address */
DECL|member|PACKED
r_int
r_char
id|ip_remote
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 23: remote IP address */
DECL|member|PACKED
r_int
r_char
id|ipx_options
id|PACKED
suffix:semicolon
multiline_comment|/* 27: IPX options */
DECL|member|PACKED
r_int
r_char
id|ipx_netno
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 28: IPX net number */
DECL|member|PACKED
r_int
r_char
id|ipx_local
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 2C: local IPX node number*/
DECL|member|PACKED
r_int
r_char
id|ipx_remote
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 32: remote IPX node num.*/
DECL|member|PACKED
r_int
r_char
id|ipx_router
(braket
l_int|48
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 38: IPX router name*/
DECL|typedef|ppp502_conf_t
)brace
id|ppp502_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S508 Adapter Configuration Block (passed to the PPP_SET_CONFIG command).&n; */
DECL|struct|ppp508_conf
r_typedef
r_struct
id|ppp508_conf
(brace
DECL|member|PACKED
r_int
r_int
id|line_speed
id|PACKED
suffix:semicolon
multiline_comment|/* 00: baud rate, bps */
DECL|member|PACKED
r_int
r_int
id|txbuf_percent
id|PACKED
suffix:semicolon
multiline_comment|/* 04: % of Tx buffer */
DECL|member|PACKED
r_int
r_int
id|conf_flags
id|PACKED
suffix:semicolon
multiline_comment|/* 06: configuration bits */
DECL|member|PACKED
r_int
r_int
id|mtu_local
id|PACKED
suffix:semicolon
multiline_comment|/* 08: local MTU */
DECL|member|PACKED
r_int
r_int
id|mtu_remote
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: remote MTU */
DECL|member|PACKED
r_int
r_int
id|restart_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: restart timer */
DECL|member|PACKED
r_int
r_int
id|auth_rsrt_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: authentication timer */
DECL|member|PACKED
r_int
r_int
id|auth_wait_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 10: authentication timer */
DECL|member|PACKED
r_int
r_int
id|mdm_fail_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 12: modem failure timer */
DECL|member|PACKED
r_int
r_int
id|dtr_drop_tmr
id|PACKED
suffix:semicolon
multiline_comment|/* 14: DTR drop timer */
DECL|member|PACKED
r_int
r_int
id|connect_tmout
id|PACKED
suffix:semicolon
multiline_comment|/* 16: connection timeout */
DECL|member|PACKED
r_int
r_int
id|conf_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 18: max. retry */
DECL|member|PACKED
r_int
r_int
id|term_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 1A: max. retry */
DECL|member|PACKED
r_int
r_int
id|fail_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 1C: max. retry */
DECL|member|PACKED
r_int
r_int
id|auth_retry
id|PACKED
suffix:semicolon
multiline_comment|/* 1E: max. retry */
DECL|member|PACKED
r_int
r_char
id|auth_options
id|PACKED
suffix:semicolon
multiline_comment|/* 20: authentication opt. */
DECL|member|PACKED
r_int
r_char
id|ip_options
id|PACKED
suffix:semicolon
multiline_comment|/* 21: IP options */
DECL|member|PACKED
r_int
r_char
id|ip_local
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 22: local IP address */
DECL|member|PACKED
r_int
r_char
id|ip_remote
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 26: remote IP address */
DECL|member|PACKED
r_int
r_char
id|ipx_options
id|PACKED
suffix:semicolon
multiline_comment|/* 2A: IPX options */
DECL|member|PACKED
r_int
r_char
id|ipx_netno
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 2B: IPX net number */
DECL|member|PACKED
r_int
r_char
id|ipx_local
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 2F: local IPX node number*/
DECL|member|PACKED
r_int
r_char
id|ipx_remote
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 35: remote IPX node num.*/
DECL|member|PACKED
r_int
r_char
id|ipx_router
(braket
l_int|48
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 3B: IPX router name*/
DECL|member|PACKED
r_int
r_int
id|alt_cpu_clock
id|PACKED
suffix:semicolon
multiline_comment|/* 6B:  */
DECL|typedef|ppp508_conf_t
)brace
id|ppp508_conf_t
suffix:semicolon
multiline_comment|/* &squot;line_speed&squot; field */
DECL|macro|PPP_BITRATE_1200
mdefine_line|#define&t;PPP_BITRATE_1200&t;0x01
DECL|macro|PPP_BITRATE_2400
mdefine_line|#define&t;PPP_BITRATE_2400&t;0x02
DECL|macro|PPP_BITRATE_4800
mdefine_line|#define&t;PPP_BITRATE_4800&t;0x03
DECL|macro|PPP_BITRATE_9600
mdefine_line|#define&t;PPP_BITRATE_9600&t;0x04
DECL|macro|PPP_BITRATE_19200
mdefine_line|#define&t;PPP_BITRATE_19200&t;0x05
DECL|macro|PPP_BITRATE_38400
mdefine_line|#define&t;PPP_BITRATE_38400&t;0x06
DECL|macro|PPP_BITRATE_45000
mdefine_line|#define&t;PPP_BITRATE_45000&t;0x07
DECL|macro|PPP_BITRATE_56000
mdefine_line|#define&t;PPP_BITRATE_56000&t;0x08
DECL|macro|PPP_BITRATE_64000
mdefine_line|#define&t;PPP_BITRATE_64000&t;0x09
DECL|macro|PPP_BITRATE_74000
mdefine_line|#define&t;PPP_BITRATE_74000&t;0x0A
DECL|macro|PPP_BITRATE_112000
mdefine_line|#define&t;PPP_BITRATE_112000&t;0x0B
DECL|macro|PPP_BITRATE_128000
mdefine_line|#define&t;PPP_BITRATE_128000&t;0x0C
DECL|macro|PPP_BITRATE_156000
mdefine_line|#define&t;PPP_BITRATE_156000&t;0x0D
multiline_comment|/* Defines for the &squot;conf_flags&squot; field */
DECL|macro|PPP_IGNORE_TX_ABORT
mdefine_line|#define&t;PPP_IGNORE_TX_ABORT&t;0x01&t;/* don&squot;t re-transmit aborted frames */
DECL|macro|PPP_ENABLE_TX_STATS
mdefine_line|#define&t;PPP_ENABLE_TX_STATS&t;0x02&t;/* enable Tx statistics */
DECL|macro|PPP_ENABLE_RX_STATS
mdefine_line|#define&t;PPP_ENABLE_RX_STATS&t;0x04&t;/* enable Rx statistics */
DECL|macro|PPP_ENABLE_TIMESTAMP
mdefine_line|#define&t;PPP_ENABLE_TIMESTAMP&t;0x08&t;/* enable timestamp */
multiline_comment|/* &squot;ip_options&squot; defines */
DECL|macro|PPP_LOCAL_IP_LOCAL
mdefine_line|#define&t;PPP_LOCAL_IP_LOCAL&t;0x01
DECL|macro|PPP_LOCAL_IP_REMOTE
mdefine_line|#define&t;PPP_LOCAL_IP_REMOTE&t;0x02
DECL|macro|PPP_REMOTE_IP_LOCAL
mdefine_line|#define&t;PPP_REMOTE_IP_LOCAL&t;0x04
DECL|macro|PPP_REMOTE_IP_REMOTE
mdefine_line|#define&t;PPP_REMOTE_IP_REMOTE&t;0x08
multiline_comment|/* &squot;ipx_options&squot; defines */
DECL|macro|PPP_REMOTE_IPX_NETNO
mdefine_line|#define&t;PPP_REMOTE_IPX_NETNO&t;0x01
DECL|macro|PPP_REMOTE_IPX_LOCAL
mdefine_line|#define&t;PPP_REMOTE_IPX_LOCAL&t;0x02
DECL|macro|PPP_REMOTE_IPX_REMOTE
mdefine_line|#define&t;PPP_REMOTE_IPX_REMOTE&t;0x04
DECL|macro|PPP_IPX_ROUTE_RIP_SAP
mdefine_line|#define&t;PPP_IPX_ROUTE_RIP_SAP&t;0x08
DECL|macro|PPP_IPX_ROUTE_NLSP
mdefine_line|#define&t;PPP_IPX_ROUTE_NLSP&t;0x10
DECL|macro|PPP_IPX_ROUTE_DEFAULT
mdefine_line|#define&t;PPP_IPX_ROUTE_DEFAULT&t;0x20
DECL|macro|PPP_IPX_CONF_COMPLETE
mdefine_line|#define&t;PPP_IPX_CONF_COMPLETE&t;0x40
DECL|macro|PPP_IPX_ENABLE
mdefine_line|#define&t;PPP_IPX_ENABLE&t;&t;0x80
multiline_comment|/*----------------------------------------------------------------------------&n; * S502 Adapter Configuration Block (returned by the PPP_READ_CONFIG command).&n; */
DECL|struct|ppp502_get_conf
r_typedef
r_struct
id|ppp502_get_conf
(brace
DECL|member|PACKED
id|ppp502_conf_t
id|conf
id|PACKED
suffix:semicolon
multiline_comment|/* 00: requested config. */
DECL|member|PACKED
r_int
r_int
id|txb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 68: number of Tx buffers */
DECL|member|PACKED
r_int
r_int
id|rxb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 6A: number of Rx buffers */
DECL|typedef|ppp502_get_conf_t
)brace
id|ppp502_get_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S508 Adapter Configuration Block (returned by the PPP_READ_CONFIG command).&n; */
DECL|struct|ppp508_get_conf
r_typedef
r_struct
id|ppp508_get_conf
(brace
DECL|member|PACKED
r_int
r_int
id|bps
id|PACKED
suffix:semicolon
multiline_comment|/* 00: baud rate, bps */
DECL|member|PACKED
id|ppp508_conf_t
id|conf
id|PACKED
suffix:semicolon
multiline_comment|/* 04: requested config. */
DECL|member|PACKED
r_int
r_int
id|txb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 6F: number of Tx buffers */
DECL|member|PACKED
r_int
r_int
id|rxb_num
id|PACKED
suffix:semicolon
multiline_comment|/* 71: number of Rx buffers */
DECL|typedef|ppp508_get_conf_t
)brace
id|ppp508_get_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S502 Operational Statistics (returned by the PPP_READ_STATISTIC command).&n; */
DECL|struct|ppp502_Stats
r_typedef
r_struct
id|ppp502_Stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_lost_intr
id|PACKED
suffix:semicolon
multiline_comment|/* 00: */
DECL|member|PACKED
r_int
r_int
id|rx_lost_buff
id|PACKED
suffix:semicolon
multiline_comment|/* 02: */
DECL|member|PACKED
r_int
r_int
id|tx_abort
id|PACKED
suffix:semicolon
multiline_comment|/* 04: */
DECL|member|PACKED
r_int
r_int
id|tx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 06: */
DECL|member|PACKED
r_int
r_int
id|tx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: */
DECL|member|PACKED
r_int
r_int
id|rx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: */
DECL|member|PACKED
r_int
r_int
id|rx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 12: */
DECL|typedef|ppp502_Stats_t
)brace
id|ppp502_Stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S508 Operational Statistics (returned by the PPP_READ_STATISTIC command).&n; */
DECL|struct|ppp508_stats
r_typedef
r_struct
id|ppp508_stats
(brace
DECL|member|PACKED
r_int
r_int
id|reserved1
id|PACKED
suffix:semicolon
multiline_comment|/* 00: */
DECL|member|PACKED
r_int
r_int
id|rx_bad_len
id|PACKED
suffix:semicolon
multiline_comment|/* 02: */
DECL|member|PACKED
r_int
r_int
id|reserved2
id|PACKED
suffix:semicolon
multiline_comment|/* 04: */
DECL|member|PACKED
r_int
r_int
id|tx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 06: */
DECL|member|PACKED
r_int
r_int
id|tx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: */
DECL|member|PACKED
r_int
r_int
id|rx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: */
DECL|member|PACKED
r_int
r_int
id|rx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 12: */
DECL|typedef|ppp508_stats_t
)brace
id|ppp508_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Adapter Error Statistics (returned by the PPP_READ_ERROR_STATS command).&n; */
DECL|struct|ppp_err_stats
r_typedef
r_struct
id|ppp_err_stats
(brace
DECL|member|PACKED
r_int
r_char
id|rx_overrun
id|PACKED
suffix:semicolon
multiline_comment|/* 00: Rx overrun errors */
DECL|member|PACKED
r_int
r_char
id|rx_bad_crc
id|PACKED
suffix:semicolon
multiline_comment|/* 01: Rx CRC errors */
DECL|member|PACKED
r_int
r_char
id|rx_abort
id|PACKED
suffix:semicolon
multiline_comment|/* 02: Rx aborted frames */
DECL|member|PACKED
r_int
r_char
id|rx_lost
id|PACKED
suffix:semicolon
multiline_comment|/* 03: Rx frames lost */
DECL|member|PACKED
r_int
r_char
id|tx_abort
id|PACKED
suffix:semicolon
multiline_comment|/* 04: Tx aborted frames */
DECL|member|PACKED
r_int
r_char
id|tx_underrun
id|PACKED
suffix:semicolon
multiline_comment|/* 05: Tx underrun errors */
DECL|member|PACKED
r_int
r_char
id|tx_missed_intr
id|PACKED
suffix:semicolon
multiline_comment|/* 06: Tx underruns missed */
DECL|member|PACKED
r_int
r_char
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 07: Tx underruns missed */
DECL|member|PACKED
r_int
r_char
id|dcd_trans
id|PACKED
suffix:semicolon
multiline_comment|/* 08: DCD transitions */
DECL|member|PACKED
r_int
r_char
id|cts_trans
id|PACKED
suffix:semicolon
multiline_comment|/* 09: CTS transitions */
DECL|typedef|ppp_err_stats_t
)brace
id|ppp_err_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Packet Statistics (returned by the PPP_READ_PACKET_STATS command).&n; */
DECL|struct|ppp_pkt_stats
r_typedef
r_struct
id|ppp_pkt_stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_bad_header
id|PACKED
suffix:semicolon
multiline_comment|/* 00: */
DECL|member|PACKED
r_int
r_int
id|rx_prot_unknwn
id|PACKED
suffix:semicolon
multiline_comment|/* 02: */
DECL|member|PACKED
r_int
r_int
id|rx_too_large
id|PACKED
suffix:semicolon
multiline_comment|/* 04: */
DECL|member|PACKED
r_int
r_int
id|rx_lcp
id|PACKED
suffix:semicolon
multiline_comment|/* 06: */
DECL|member|PACKED
r_int
r_int
id|tx_lcp
id|PACKED
suffix:semicolon
multiline_comment|/* 08: */
DECL|member|PACKED
r_int
r_int
id|rx_ipcp
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: */
DECL|member|PACKED
r_int
r_int
id|tx_ipcp
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: */
DECL|member|PACKED
r_int
r_int
id|rx_ipxcp
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: */
DECL|member|PACKED
r_int
r_int
id|tx_ipxcp
id|PACKED
suffix:semicolon
multiline_comment|/* 10: */
DECL|member|PACKED
r_int
r_int
id|rx_pap
id|PACKED
suffix:semicolon
multiline_comment|/* 12: */
DECL|member|PACKED
r_int
r_int
id|tx_pap
id|PACKED
suffix:semicolon
multiline_comment|/* 14: */
DECL|member|PACKED
r_int
r_int
id|rx_chap
id|PACKED
suffix:semicolon
multiline_comment|/* 16: */
DECL|member|PACKED
r_int
r_int
id|tx_chap
id|PACKED
suffix:semicolon
multiline_comment|/* 18: */
DECL|member|PACKED
r_int
r_int
id|rx_lqr
id|PACKED
suffix:semicolon
multiline_comment|/* 1A: */
DECL|member|PACKED
r_int
r_int
id|tx_lqr
id|PACKED
suffix:semicolon
multiline_comment|/* 1C: */
DECL|member|PACKED
r_int
r_int
id|rx_ip
id|PACKED
suffix:semicolon
multiline_comment|/* 1E: */
DECL|member|PACKED
r_int
r_int
id|tx_ip
id|PACKED
suffix:semicolon
multiline_comment|/* 20: */
DECL|member|PACKED
r_int
r_int
id|rx_ipx
id|PACKED
suffix:semicolon
multiline_comment|/* 22: */
DECL|member|PACKED
r_int
r_int
id|tx_ipx
id|PACKED
suffix:semicolon
multiline_comment|/* 24: */
DECL|typedef|ppp_pkt_stats_t
)brace
id|ppp_pkt_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * LCP Statistics (returned by the PPP_READ_LCP_STATS command).&n; */
DECL|struct|ppp_lcp_stats
r_typedef
r_struct
id|ppp_lcp_stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_unknown
id|PACKED
suffix:semicolon
multiline_comment|/* 00: unknown LCP type */
DECL|member|PACKED
r_int
r_int
id|rx_conf_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 02: Configure-Request */
DECL|member|PACKED
r_int
r_int
id|rx_conf_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 04: Configure-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_conf_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 06: Configure-Nak */
DECL|member|PACKED
r_int
r_int
id|rx_conf_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 08: Configure-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_term_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: Terminate-Request */
DECL|member|PACKED
r_int
r_int
id|rx_term_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: Terminate-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_code_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: Code-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_proto_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 10: Protocol-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_echo_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 12: Echo-Request */
DECL|member|PACKED
r_int
r_int
id|rx_echo_reply
id|PACKED
suffix:semicolon
multiline_comment|/* 14: Echo-Reply */
DECL|member|PACKED
r_int
r_int
id|rx_disc_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 16: Discard-Request */
DECL|member|PACKED
r_int
r_int
id|tx_conf_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 18: Configure-Request */
DECL|member|PACKED
r_int
r_int
id|tx_conf_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 1A: Configure-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_conf_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 1C: Configure-Nak */
DECL|member|PACKED
r_int
r_int
id|tx_conf_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 1E: Configure-Reject */
DECL|member|PACKED
r_int
r_int
id|tx_term_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 20: Terminate-Request */
DECL|member|PACKED
r_int
r_int
id|tx_term_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 22: Terminate-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_code_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 24: Code-Reject */
DECL|member|PACKED
r_int
r_int
id|tx_proto_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 26: Protocol-Reject */
DECL|member|PACKED
r_int
r_int
id|tx_echo_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 28: Echo-Request */
DECL|member|PACKED
r_int
r_int
id|tx_echo_reply
id|PACKED
suffix:semicolon
multiline_comment|/* 2A: Echo-Reply */
DECL|member|PACKED
r_int
r_int
id|tx_disc_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 2E: Discard-Request */
DECL|member|PACKED
r_int
r_int
id|rx_too_large
id|PACKED
suffix:semicolon
multiline_comment|/* 30: packets too large */
DECL|member|PACKED
r_int
r_int
id|rx_ack_inval
id|PACKED
suffix:semicolon
multiline_comment|/* 32: invalid Conf-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_rej_inval
id|PACKED
suffix:semicolon
multiline_comment|/* 34: invalid Conf-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_rej_badid
id|PACKED
suffix:semicolon
multiline_comment|/* 36: Conf-Reject w/bad ID */
DECL|typedef|ppp_lcp_stats_t
)brace
id|ppp_lcp_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Loopback Error Statistics (returned by the PPP_READ_LPBK_STATS command).&n; */
DECL|struct|ppp_lpbk_stats
r_typedef
r_struct
id|ppp_lpbk_stats
(brace
DECL|member|PACKED
r_int
r_int
id|conf_magic
id|PACKED
suffix:semicolon
multiline_comment|/* 00:  */
DECL|member|PACKED
r_int
r_int
id|loc_echo_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 02:  */
DECL|member|PACKED
r_int
r_int
id|rem_echo_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 04:  */
DECL|member|PACKED
r_int
r_int
id|loc_echo_reply
id|PACKED
suffix:semicolon
multiline_comment|/* 06:  */
DECL|member|PACKED
r_int
r_int
id|rem_echo_reply
id|PACKED
suffix:semicolon
multiline_comment|/* 08:  */
DECL|member|PACKED
r_int
r_int
id|loc_disc_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0A:  */
DECL|member|PACKED
r_int
r_int
id|rem_disc_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0C:  */
DECL|member|PACKED
r_int
r_int
id|echo_tx_collsn
id|PACKED
suffix:semicolon
multiline_comment|/* 0E:  */
DECL|member|PACKED
r_int
r_int
id|echo_rx_collsn
id|PACKED
suffix:semicolon
multiline_comment|/* 10:  */
DECL|typedef|ppp_lpbk_stats_t
)brace
id|ppp_lpbk_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Protocol Statistics (returned by the PPP_READ_IPCP_STATS and&n; * PPP_READ_IPXCP_STATS commands).&n; */
DECL|struct|ppp_prot_stats
r_typedef
r_struct
id|ppp_prot_stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_unknown
id|PACKED
suffix:semicolon
multiline_comment|/* 00: unknown type */
DECL|member|PACKED
r_int
r_int
id|rx_conf_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 02: Configure-Request */
DECL|member|PACKED
r_int
r_int
id|rx_conf_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 04: Configure-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_conf_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 06: Configure-Nak */
DECL|member|PACKED
r_int
r_int
id|rx_conf_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 08: Configure-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_term_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: Terminate-Request */
DECL|member|PACKED
r_int
r_int
id|rx_term_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: Terminate-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_code_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: Code-Reject */
DECL|member|PACKED
r_int
r_int
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 10: */
DECL|member|PACKED
r_int
r_int
id|tx_conf_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 12: Configure-Request */
DECL|member|PACKED
r_int
r_int
id|tx_conf_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 14: Configure-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_conf_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 16: Configure-Nak */
DECL|member|PACKED
r_int
r_int
id|tx_conf_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 18: Configure-Reject */
DECL|member|PACKED
r_int
r_int
id|tx_term_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 1A: Terminate-Request */
DECL|member|PACKED
r_int
r_int
id|tx_term_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 1C: Terminate-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_code_rej
id|PACKED
suffix:semicolon
multiline_comment|/* 1E: Code-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_too_large
id|PACKED
suffix:semicolon
multiline_comment|/* 20: packets too large */
DECL|member|PACKED
r_int
r_int
id|rx_ack_inval
id|PACKED
suffix:semicolon
multiline_comment|/* 22: invalid Conf-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_rej_inval
id|PACKED
suffix:semicolon
multiline_comment|/* 24: invalid Conf-Reject */
DECL|member|PACKED
r_int
r_int
id|rx_rej_badid
id|PACKED
suffix:semicolon
multiline_comment|/* 26: Conf-Reject w/bad ID */
DECL|typedef|ppp_prot_stats_t
)brace
id|ppp_prot_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * PAP Statistics (returned by the PPP_READ_PAP_STATS command).&n; */
DECL|struct|ppp_pap_stats
r_typedef
r_struct
id|ppp_pap_stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_unknown
id|PACKED
suffix:semicolon
multiline_comment|/* 00: unknown type */
DECL|member|PACKED
r_int
r_int
id|rx_auth_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 02: Authenticate-Request */
DECL|member|PACKED
r_int
r_int
id|rx_auth_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 04: Authenticate-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_auth_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 06: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 08: */
DECL|member|PACKED
r_int
r_int
id|tx_auth_rqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: Authenticate-Request */
DECL|member|PACKED
r_int
r_int
id|tx_auth_ack
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: Authenticate-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_auth_nak
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|rx_too_large
id|PACKED
suffix:semicolon
multiline_comment|/* 10: packets too large */
DECL|member|PACKED
r_int
r_int
id|rx_bad_peerid
id|PACKED
suffix:semicolon
multiline_comment|/* 12: invalid peer ID */
DECL|member|PACKED
r_int
r_int
id|rx_bad_passwd
id|PACKED
suffix:semicolon
multiline_comment|/* 14: invalid password */
DECL|typedef|ppp_pap_stats_t
)brace
id|ppp_pap_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * CHAP Statistics (returned by the PPP_READ_CHAP_STATS command).&n; */
DECL|struct|ppp_chap_stats
r_typedef
r_struct
id|ppp_chap_stats
(brace
DECL|member|PACKED
r_int
r_int
id|rx_unknown
id|PACKED
suffix:semicolon
multiline_comment|/* 00: unknown type */
DECL|member|PACKED
r_int
r_int
id|rx_challenge
id|PACKED
suffix:semicolon
multiline_comment|/* 02: Authenticate-Request */
DECL|member|PACKED
r_int
r_int
id|rx_response
id|PACKED
suffix:semicolon
multiline_comment|/* 04: Authenticate-Ack */
DECL|member|PACKED
r_int
r_int
id|rx_success
id|PACKED
suffix:semicolon
multiline_comment|/* 06: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|rx_failure
id|PACKED
suffix:semicolon
multiline_comment|/* 08: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 0A: */
DECL|member|PACKED
r_int
r_int
id|tx_challenge
id|PACKED
suffix:semicolon
multiline_comment|/* 0C: Authenticate-Request */
DECL|member|PACKED
r_int
r_int
id|tx_response
id|PACKED
suffix:semicolon
multiline_comment|/* 0E: Authenticate-Ack */
DECL|member|PACKED
r_int
r_int
id|tx_success
id|PACKED
suffix:semicolon
multiline_comment|/* 10: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|tx_failure
id|PACKED
suffix:semicolon
multiline_comment|/* 12: Authenticate-Nak */
DECL|member|PACKED
r_int
r_int
id|rx_too_large
id|PACKED
suffix:semicolon
multiline_comment|/* 14: packets too large */
DECL|member|PACKED
r_int
r_int
id|rx_bad_peerid
id|PACKED
suffix:semicolon
multiline_comment|/* 16: invalid peer ID */
DECL|member|PACKED
r_int
r_int
id|rx_bad_passwd
id|PACKED
suffix:semicolon
multiline_comment|/* 18: invalid password */
DECL|member|PACKED
r_int
r_int
id|rx_bad_md5
id|PACKED
suffix:semicolon
multiline_comment|/* 1A: invalid MD5 format */
DECL|member|PACKED
r_int
r_int
id|rx_bad_resp
id|PACKED
suffix:semicolon
multiline_comment|/* 1C: invalid response */
DECL|typedef|ppp_chap_stats_t
)brace
id|ppp_chap_stats_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Connection Information (returned by the PPP_GET_CONNECTION_INFO command).&n; */
DECL|struct|ppp_conn_info
r_typedef
r_struct
id|ppp_conn_info
(brace
DECL|member|PACKED
r_int
r_int
id|remote_mru
id|PACKED
suffix:semicolon
multiline_comment|/* 00:  */
DECL|member|PACKED
r_int
r_char
id|ip_options
id|PACKED
suffix:semicolon
multiline_comment|/* 02:  */
DECL|member|PACKED
r_int
r_char
id|ip_local
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 03:  */
DECL|member|PACKED
r_int
r_char
id|ip_remote
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 07:  */
DECL|member|PACKED
r_int
r_char
id|ipx_options
id|PACKED
suffix:semicolon
multiline_comment|/* 0B:  */
DECL|member|PACKED
r_int
r_char
id|ipx_network
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 0C:  */
DECL|member|PACKED
r_int
r_char
id|ipx_local
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 10:  */
DECL|member|PACKED
r_int
r_char
id|ipx_remote
(braket
l_int|6
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 16:  */
DECL|member|PACKED
r_int
r_char
id|ipx_router
(braket
l_int|48
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 1C:  */
DECL|member|PACKED
r_int
r_char
id|auth_status
id|PACKED
suffix:semicolon
multiline_comment|/* 4C:  */
DECL|member|PACKED
r_int
r_char
id|peer_id
(braket
l_int|0
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 4D:  */
DECL|typedef|ppp_conn_info_t
)brace
id|ppp_conn_info_t
suffix:semicolon
macro_line|#ifdef&t;&t;_MSC_
macro_line|#  pragma&t;pack()
macro_line|#endif
macro_line|#endif&t;/* _SDLA_PPP_H */
eof
