multiline_comment|/*****************************************************************************&n;* sdla_fr.h&t;Sangoma frame relay firmware API definitions.&n;*&n;* Author:&t;Jaspreet Singh  &lt;jaspreet@sangoma.com&gt;&n;*&t;&t;Gene Kozin&t;&lt;74604.152@compuserve.com&gt;&n;*&n;* Copyright:&t;(c) 1995-1996 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Oct 12, 1997&t;Jaspreet Singh&t;Added FR_READ_DLCI_IB_MAPPING&n;* Jul 21, 1997 &t;Jaspreet Singh&t;Changed FRRES_TOO_LONG and FRRES_TOO_MANY to &n;*&t;&t;&t;&t;0x05 and 0x06 respectively.&n;* Dec 23, 1996&t;Gene Kozin&t;v2.0&n;* Apr 29, 1996&t;Gene Kozin&t;v1.0 (merged version S502 &amp; S508 definitions).&n;* Sep 26, 1995&t;Gene Kozin&t;Initial version.&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLA_FR_H
DECL|macro|_SDLA_FR_H
mdefine_line|#define&t;_SDLA_FR_H
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
multiline_comment|/* Adapter memory layout */
DECL|macro|FR_MB_VECTOR
mdefine_line|#define&t;FR_MB_VECTOR&t;0xE000&t;/* mailbox window vector */
DECL|macro|FR502_RX_VECTOR
mdefine_line|#define&t;FR502_RX_VECTOR&t;0xA000&t;/* S502 direct receive window vector */
DECL|macro|FR502_MBOX_OFFS
mdefine_line|#define&t;FR502_MBOX_OFFS&t;0xF60&t;/* S502 mailbox offset */
DECL|macro|FR508_MBOX_OFFS
mdefine_line|#define&t;FR508_MBOX_OFFS&t;0&t;/* S508 mailbox offset */
DECL|macro|FR502_FLAG_OFFS
mdefine_line|#define&t;FR502_FLAG_OFFS&t;0x1FF0&t;/* S502 status flags offset */
DECL|macro|FR508_FLAG_OFFS
mdefine_line|#define&t;FR508_FLAG_OFFS&t;0x1000&t;/* S508 status flags offset */
DECL|macro|FR502_RXMB_OFFS
mdefine_line|#define&t;FR502_RXMB_OFFS&t;0x900&t;/* S502 direct receive mailbox offset */
DECL|macro|FR508_TXBC_OFFS
mdefine_line|#define&t;FR508_TXBC_OFFS&t;0x1100&t;/* S508 Tx buffer info offset */
DECL|macro|FR508_RXBC_OFFS
mdefine_line|#define&t;FR508_RXBC_OFFS&t;0x1120&t;/* S508 Rx buffer info offset */
multiline_comment|/* Important constants */
DECL|macro|FR502_MAX_DATA
mdefine_line|#define FR502_MAX_DATA&t;4096&t;/* maximum data buffer length */
DECL|macro|FR508_MAX_DATA
mdefine_line|#define FR508_MAX_DATA&t;4080&t;/* maximum data buffer length */
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/*----------------------------------------------------------------------------&n; * Frame relay command block.&n; */
DECL|struct|fr_cmd
r_typedef
r_struct
id|fr_cmd
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
r_int
id|dlci
id|PACKED
suffix:semicolon
multiline_comment|/* DLCI number */
DECL|member|PACKED
r_int
r_char
id|attr
id|PACKED
suffix:semicolon
multiline_comment|/* FECN, BECN, DE and C/R bits */
DECL|member|PACKED
r_int
r_int
id|rxlost1
id|PACKED
suffix:semicolon
multiline_comment|/* frames discarded at int. level */
DECL|member|PACKED
r_int
r_int
id|rxlost2
id|PACKED
suffix:semicolon
multiline_comment|/* frames discarded at app. level */
DECL|member|PACKED
r_int
r_char
id|rsrv
(braket
l_int|2
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|typedef|fr_cmd_t
)brace
id|fr_cmd_t
suffix:semicolon
multiline_comment|/* &squot;command&squot; field defines */
DECL|macro|FR_WRITE
mdefine_line|#define&t;FR_WRITE&t;&t;0x01
DECL|macro|FR_READ
mdefine_line|#define&t;FR_READ&t;&t;&t;0x02
DECL|macro|FR_ISSUE_IS_FRAME
mdefine_line|#define&t;FR_ISSUE_IS_FRAME&t;0x03
DECL|macro|FR_SET_CONFIG
mdefine_line|#define FR_SET_CONFIG&t;&t;0x10
DECL|macro|FR_READ_CONFIG
mdefine_line|#define FR_READ_CONFIG&t;&t;0x11
DECL|macro|FR_COMM_DISABLE
mdefine_line|#define FR_COMM_DISABLE&t;&t;0x12
DECL|macro|FR_COMM_ENABLE
mdefine_line|#define FR_COMM_ENABLE&t;&t;0x13
DECL|macro|FR_READ_STATUS
mdefine_line|#define FR_READ_STATUS&t;&t;0x14
DECL|macro|FR_READ_STATISTICS
mdefine_line|#define FR_READ_STATISTICS&t;0x15
DECL|macro|FR_FLUSH_STATISTICS
mdefine_line|#define FR_FLUSH_STATISTICS&t;0x16
DECL|macro|FR_LIST_ACTIVE_DLCI
mdefine_line|#define&t;FR_LIST_ACTIVE_DLCI&t;0x17
DECL|macro|FR_FLUSH_DATA_BUFFERS
mdefine_line|#define FR_FLUSH_DATA_BUFFERS&t;0x18
DECL|macro|FR_ADD_DLCI
mdefine_line|#define&t;FR_ADD_DLCI&t;&t;0x20
DECL|macro|FR_DELETE_DLCI
mdefine_line|#define&t;FR_DELETE_DLCI&t;&t;0x21
DECL|macro|FR_ACTIVATE_DLCI
mdefine_line|#define&t;FR_ACTIVATE_DLCI&t;0x22
DECL|macro|FR_DEACTIVATE_DLCI
mdefine_line|#define&t;FR_DEACTIVATE_DLCI&t;0x22
DECL|macro|FR_READ_MODEM_STATUS
mdefine_line|#define FR_READ_MODEM_STATUS&t;0x30
DECL|macro|FR_SET_MODEM_STATUS
mdefine_line|#define FR_SET_MODEM_STATUS&t;0x31
DECL|macro|FR_READ_ERROR_STATS
mdefine_line|#define FR_READ_ERROR_STATS&t;0x32
DECL|macro|FR_FLUSH_ERROR_STATS
mdefine_line|#define FR_FLUSH_ERROR_STATS&t;0x33
DECL|macro|FR_READ_DLCI_IB_MAPPING
mdefine_line|#define FR_READ_DLCI_IB_MAPPING 0x34
DECL|macro|FR_READ_CODE_VERSION
mdefine_line|#define FR_READ_CODE_VERSION&t;0x40
DECL|macro|FR_SET_INTR_MODE
mdefine_line|#define&t;FR_SET_INTR_MODE&t;0x50
DECL|macro|FR_READ_INTR_MODE
mdefine_line|#define&t;FR_READ_INTR_MODE&t;0x51
multiline_comment|/* &squot;result&squot; field defines */
DECL|macro|FRRES_OK
mdefine_line|#define FRRES_OK&t;&t;0x00&t;/* command executed successfully */
DECL|macro|FRRES_DISABLED
mdefine_line|#define&t;FRRES_DISABLED&t;&t;0x01&t;/* communications not enabled */
DECL|macro|FRRES_INOPERATIVE
mdefine_line|#define&t;FRRES_INOPERATIVE&t;0x02&t;/* channel inoperative */
DECL|macro|FRRES_DLCI_INACTIVE
mdefine_line|#define&t;FRRES_DLCI_INACTIVE&t;0x03&t;/* DLCI is inactive */
DECL|macro|FRRES_DLCI_INVALID
mdefine_line|#define&t;FRRES_DLCI_INVALID&t;0x04&t;/* DLCI is not configured */
DECL|macro|FRRES_TOO_LONG
mdefine_line|#define&t;FRRES_TOO_LONG&t;&t;0x05
DECL|macro|FRRES_TOO_MANY
mdefine_line|#define&t;FRRES_TOO_MANY&t;&t;0x06
DECL|macro|FRRES_CIR_OVERFLOW
mdefine_line|#define&t;FRRES_CIR_OVERFLOW&t;0x07&t;/* Tx throughput has exceeded CIR */
DECL|macro|FRRES_BUFFER_OVERFLOW
mdefine_line|#define&t;FRRES_BUFFER_OVERFLOW&t;0x08
DECL|macro|FRRES_MODEM_FAILURE
mdefine_line|#define&t;FRRES_MODEM_FAILURE&t;0x10&t;/* DCD and/or CTS dropped */
DECL|macro|FRRES_CHANNEL_DOWN
mdefine_line|#define&t;FRRES_CHANNEL_DOWN&t;0x11&t;/* channel became inoperative */
DECL|macro|FRRES_CHANNEL_UP
mdefine_line|#define&t;FRRES_CHANNEL_UP&t;0x12&t;/* channel became operative */
DECL|macro|FRRES_DLCI_CHANGE
mdefine_line|#define&t;FRRES_DLCI_CHANGE&t;0x13&t;/* DLCI status (or number) changed */
DECL|macro|FRRES_DLCI_MISMATCH
mdefine_line|#define&t;FRRES_DLCI_MISMATCH&t;0x14
DECL|macro|FRRES_INVALID_CMD
mdefine_line|#define&t;FRRES_INVALID_CMD&t;0x1F&t;/* invalid command */
multiline_comment|/* &squot;attr&squot; field defines */
DECL|macro|FRATTR_
mdefine_line|#define&t;FRATTR_
multiline_comment|/*----------------------------------------------------------------------------&n; * Frame relay mailbox.&n; *&t;This structure is located at offset FR50?_MBOX_OFFS into FR_MB_VECTOR.&n; *&t;For S502 it is also located at offset FR502_RXMB_OFFS into&n; *&t;FR502_RX_VECTOR.&n; */
DECL|struct|fr_mbox
r_typedef
r_struct
id|fr_mbox
(brace
DECL|member|PACKED
r_int
r_char
id|opflag
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: execution flag */
DECL|member|PACKED
id|fr_cmd_t
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
DECL|typedef|fr_mbox_t
)brace
id|fr_mbox_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S502 frame relay status flags.&n; *&t;This structure is located at offset FR502_FLAG_OFFS into FR_MB_VECTOR.&n; */
DECL|struct|fr502_flags
r_typedef
r_struct
id|fr502_flags
(brace
DECL|member|PACKED
r_int
r_char
id|rsrv1
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: */
DECL|member|PACKED
r_int
r_char
id|tx_ready
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: Tx buffer available */
DECL|member|PACKED
r_int
r_char
id|rx_ready
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: Rx frame available */
DECL|member|PACKED
r_int
r_char
id|event
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: asynchronous event */
DECL|member|PACKED
r_int
r_char
id|mstatus
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: modem status */
DECL|member|PACKED
r_int
r_char
id|rsrv2
(braket
l_int|8
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: */
DECL|member|PACKED
r_int
r_char
id|iflag
id|PACKED
suffix:semicolon
multiline_comment|/* 0Dh: interrupt flag */
DECL|member|PACKED
r_int
r_char
id|imask
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: interrupt mask */
DECL|typedef|fr502_flags_t
)brace
id|fr502_flags_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S508 frame relay status flags.&n; *&t;This structure is located at offset FR508_FLAG_OFFS into FR_MB_VECTOR.&n; */
DECL|struct|fr508_flags
r_typedef
r_struct
id|fr508_flags
(brace
DECL|member|PACKED
r_int
r_char
id|rsrv1
(braket
l_int|3
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: reserved */
DECL|member|PACKED
r_int
r_char
id|event
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: asynchronous event */
DECL|member|PACKED
r_int
r_char
id|mstatus
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: modem status */
DECL|member|PACKED
r_int
r_char
id|rsrv2
(braket
l_int|11
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: reserved */
DECL|member|PACKED
r_int
r_char
id|iflag
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: interrupt flag */
DECL|member|PACKED
r_int
r_char
id|imask
id|PACKED
suffix:semicolon
multiline_comment|/* 11h: interrupt mask */
DECL|member|PACKED
r_int
r_int
id|tse_offs
id|PACKED
suffix:semicolon
multiline_comment|/* 12h: Tx status element */
DECL|member|PACKED
r_int
r_int
id|dlci
id|PACKED
suffix:semicolon
multiline_comment|/* 16h: DLCI NUMBER */
DECL|typedef|fr508_flags_t
)brace
id|fr508_flags_t
suffix:semicolon
multiline_comment|/* &squot;event&squot; field defines */
DECL|macro|FR_EVENT_STATUS
mdefine_line|#define&t;FR_EVENT_STATUS&t;&t;0x01&t;/* channel status change ??? */
DECL|macro|FR_EVENT_DLC_STATUS
mdefine_line|#define&t;FR_EVENT_DLC_STATUS&t;0x02&t;/* DLC status change */
DECL|macro|FR_EVENT_BAD_DLCI
mdefine_line|#define&t;FR_EVENT_BAD_DLCI&t;0x04&t;/* FSR included wrong DLCI */
DECL|macro|FR_EVENT_LINK_DOWN
mdefine_line|#define&t;FR_EVENT_LINK_DOWN&t;0x40&t;/* DCD or CTS low */
multiline_comment|/* &squot;mstatus&squot; field defines */
DECL|macro|FR_MDM_DCD
mdefine_line|#define&t;FR_MDM_DCD&t;&t;0x08&t;/* mdm_status: DCD */
DECL|macro|FR_MDM_CTS
mdefine_line|#define&t;FR_MDM_CTS&t;&t;0x20&t;/* mdm_status: CTS */
multiline_comment|/* &squot;iflag&squot; &amp; &squot;imask&squot; fields defines */
DECL|macro|FR_INTR_RXRDY
mdefine_line|#define&t;FR_INTR_RXRDY&t;&t;0x01&t;/* Rx ready */
DECL|macro|FR_INTR_TXRDY
mdefine_line|#define&t;FR_INTR_TXRDY&t;&t;0x02&t;/* Tx ready */
DECL|macro|FR_INTR_MODEM
mdefine_line|#define&t;FR_INTR_MODEM&t;&t;0x04&t;/* modem status change (DCD, CTS) */
DECL|macro|FR_INTR_READY
mdefine_line|#define&t;FR_INTR_READY&t;&t;0x08&t;/* interface command completed */
DECL|macro|FR_INTR_DLC
mdefine_line|#define&t;FR_INTR_DLC&t;&t;0x10&t;/* DLC status change */
DECL|macro|FR_INTR_TIMER
mdefine_line|#define&t;FR_INTR_TIMER&t;&t;0x20&t;/* millisecond timer */
multiline_comment|/*----------------------------------------------------------------------------&n; * Receive Buffer Configuration Info. S508 only!&n; *&t;This structure is located at offset FR508_RXBC_OFFS into FR_MB_VECTOR.&n; */
DECL|struct|fr_buf_info
r_typedef
r_struct
id|fr_buf_info
(brace
DECL|member|PACKED
r_int
r_int
id|rse_num
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: number of status elements */
DECL|member|PACKED
r_int
r_int
id|rse_base
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: receive status array base */
DECL|member|PACKED
r_int
r_int
id|rse_next
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: next status element */
DECL|member|PACKED
r_int
r_int
id|buf_base
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah: rotational buffer base */
DECL|member|PACKED
r_int
r_int
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh:  */
DECL|member|PACKED
r_int
r_int
id|buf_top
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: rotational buffer top */
DECL|typedef|fr_buf_info_t
)brace
id|fr_buf_info_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Buffer Status Element. S508 only!&n; *&t;Array of structures of this type is located at offset defined by the&n; *&t;&squot;rse_base&squot; field of the frBufInfo_t structure into absolute adapter&n; *&t;memory address space.&n; */
DECL|struct|fr_buf_ctl
r_typedef
r_struct
id|fr_buf_ctl
(brace
DECL|member|PACKED
r_int
r_char
id|flag
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: ready flag */
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: frame length */
DECL|member|PACKED
r_int
r_int
id|dlci
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: DLCI */
DECL|member|PACKED
r_int
r_char
id|attr
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: FECN/BECN/DE/CR */
DECL|member|PACKED
r_int
r_int
id|tmstamp
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: time stamp */
DECL|member|PACKED
r_int
r_int
id|rsrv
(braket
l_int|2
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|member|PACKED
r_int
r_int
id|offset
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch: buffer absolute address */
DECL|typedef|fr_buf_ctl_t
)brace
id|fr_buf_ctl_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Global Configuration Block. Passed to FR_SET_CONFIG command when dlci == 0.&n; */
DECL|struct|fr_conf
r_typedef
r_struct
id|fr_conf
(brace
DECL|member|PACKED
r_int
r_int
id|station
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: CPE/Node */
DECL|member|PACKED
r_int
r_int
id|options
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: configuration options */
DECL|member|PACKED
r_int
r_int
id|kbps
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: baud rate in kbps */
DECL|member|PACKED
r_int
r_int
id|port
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: RS-232/V.35 */
DECL|member|PACKED
r_int
r_int
id|mtu
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: max. transmit length */
DECL|member|PACKED
r_int
r_int
id|t391
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah:  */
DECL|member|PACKED
r_int
r_int
id|t392
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch:  */
DECL|member|PACKED
r_int
r_int
id|n391
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh:  */
DECL|member|PACKED
r_int
r_int
id|n392
id|PACKED
suffix:semicolon
multiline_comment|/* 10h:  */
DECL|member|PACKED
r_int
r_int
id|n393
id|PACKED
suffix:semicolon
multiline_comment|/* 12h:  */
DECL|member|PACKED
r_int
r_int
id|cir_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 14h:  */
DECL|member|PACKED
r_int
r_int
id|bc_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 16h:  */
DECL|member|PACKED
r_int
r_int
id|be_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 18h:  */
DECL|member|PACKED
r_int
r_int
id|cir_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ah:  */
DECL|member|PACKED
r_int
r_int
id|bc_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ch:  */
DECL|member|PACKED
r_int
r_int
id|be_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 1Eh:  */
DECL|member|PACKED
r_int
r_int
id|dlci
(braket
l_int|0
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 20h:  */
DECL|typedef|fr_conf_t
)brace
id|fr_conf_t
suffix:semicolon
multiline_comment|/* &squot;station_type&squot; defines */
DECL|macro|FRCFG_STATION_CPE
mdefine_line|#define&t;FRCFG_STATION_CPE&t;0
DECL|macro|FRCFG_STATION_NODE
mdefine_line|#define&t;FRCFG_STATION_NODE&t;1
multiline_comment|/* &squot;conf_flags&squot; defines */
DECL|macro|FRCFG_IGNORE_TX_CIR
mdefine_line|#define&t;FRCFG_IGNORE_TX_CIR&t;0x0001
DECL|macro|FRCFG_IGNORE_RX_CIR
mdefine_line|#define&t;FRCFG_IGNORE_RX_CIR&t;0x0002
DECL|macro|FRCFG_DONT_RETRANSMIT
mdefine_line|#define&t;FRCFG_DONT_RETRANSMIT&t;0x0004
DECL|macro|FRCFG_IGNORE_CBS
mdefine_line|#define&t;FRCFG_IGNORE_CBS&t;0x0008
DECL|macro|FRCFG_THROUGHPUT
mdefine_line|#define&t;FRCFG_THROUGHPUT&t;0x0010&t;/* enable throughput calculation */
DECL|macro|FRCFG_DIRECT_RX
mdefine_line|#define&t;FRCFG_DIRECT_RX&t;&t;0x0080&t;/* enable direct receive buffer */
DECL|macro|FRCFG_AUTO_CONFIG
mdefine_line|#define&t;FRCFG_AUTO_CONFIG&t;0x8000&t;/* enable  auto DLCI configuration */
multiline_comment|/* &squot;baud_rate&squot; defines */
DECL|macro|FRCFG_BAUD_1200
mdefine_line|#define&t;FRCFG_BAUD_1200&t;&t;12
DECL|macro|FRCFG_BAUD_2400
mdefine_line|#define&t;FRCFG_BAUD_2400&t;&t;24
DECL|macro|FRCFG_BAUD_4800
mdefine_line|#define&t;FRCFG_BAUD_4800&t;&t;48
DECL|macro|FRCFG_BAUD_9600
mdefine_line|#define&t;FRCFG_BAUD_9600&t;&t;96
DECL|macro|FRCFG_BAUD_19200
mdefine_line|#define&t;FRCFG_BAUD_19200&t;19
DECL|macro|FRCFG_BAUD_38400
mdefine_line|#define&t;FRCFG_BAUD_38400&t;38
DECL|macro|FRCFG_BAUD_56000
mdefine_line|#define&t;FRCFG_BAUD_56000&t;56
DECL|macro|FRCFG_BAUD_64000
mdefine_line|#define&t;FRCFG_BAUD_64000&t;64
DECL|macro|FRCFG_BAUD_128000
mdefine_line|#define&t;FRCFG_BAUD_128000&t;128
multiline_comment|/* &squot;port_mode&squot; defines */
DECL|macro|FRCFG_MODE_EXT_CLK
mdefine_line|#define&t;FRCFG_MODE_EXT_CLK&t;0x0000
DECL|macro|FRCFG_MODE_INT_CLK
mdefine_line|#define&t;FRCFG_MODE_INT_CLK&t;0x0001
DECL|macro|FRCFG_MODE_V35
mdefine_line|#define&t;FRCFG_MODE_V35&t;&t;0x0000&t;/* S508 only */
DECL|macro|FRCFG_MODE_RS232
mdefine_line|#define&t;FRCFG_MODE_RS232&t;0x0002&t;/* S508 only */
multiline_comment|/*----------------------------------------------------------------------------&n; * Channel configuration.&n; *&t;This structure is passed to the FR_SET_CONFIG command when dlci != 0.&n; */
DECL|struct|fr_dlc_conf
r_typedef
r_struct
id|fr_dlc_conf
(brace
DECL|member|PACKED
r_int
r_int
id|conf_flags
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: configuration bits */
DECL|member|PACKED
r_int
r_int
id|cir_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 02h:  */
DECL|member|PACKED
r_int
r_int
id|bc_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 04h:  */
DECL|member|PACKED
r_int
r_int
id|be_fwd
id|PACKED
suffix:semicolon
multiline_comment|/* 06h:  */
DECL|member|PACKED
r_int
r_int
id|cir_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|member|PACKED
r_int
r_int
id|bc_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah:  */
DECL|member|PACKED
r_int
r_int
id|be_bwd
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch:  */
DECL|typedef|fr_dlc_conf_t
)brace
id|fr_dlc_conf_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S502 interrupt mode control block.&n; *&t;This structure is passed to the FR_SET_INTR_FLAGS and returned by the&n; *&t;FR_READ_INTR_FLAGS commands.&n; */
DECL|struct|fr502_intr_ctl
r_typedef
r_struct
id|fr502_intr_ctl
(brace
DECL|member|PACKED
r_int
r_char
id|mode
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: interrupt enable flags */
DECL|member|PACKED
r_int
r_int
id|tx_len
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: required Tx buffer size */
DECL|typedef|fr502_intr_ctl_t
)brace
id|fr502_intr_ctl_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * S508 interrupt mode control block.&n; *&t;This structure is passed to the FR_SET_INTR_FLAGS and returned by the&n; *&t;FR_READ_INTR_FLAGS commands.&n; */
DECL|struct|fr508_intr_ctl
r_typedef
r_struct
id|fr508_intr_ctl
(brace
DECL|member|PACKED
r_int
r_char
id|mode
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: interrupt enable flags */
DECL|member|PACKED
r_int
r_int
id|tx_len
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: required Tx buffer size */
DECL|member|PACKED
r_int
r_char
id|irq
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: IRQ level to activate */
DECL|member|PACKED
r_int
r_char
id|flags
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: ?? */
DECL|member|PACKED
r_int
r_int
id|timeout
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: ms, for timer interrupt */
DECL|typedef|fr508_intr_ctl_t
)brace
id|fr508_intr_ctl_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Channel status.&n; *&t;This structure is returned by the FR_READ_STATUS command.&n; */
DECL|struct|fr_dlc_Status
r_typedef
r_struct
id|fr_dlc_Status
(brace
DECL|member|PACKED
r_int
r_char
id|status
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: link/DLCI status */
r_struct
(brace
DECL|member|PACKED
r_int
r_int
id|dlci
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: DLCI number */
DECL|member|PACKED
r_int
r_char
id|status
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: DLCI status */
DECL|member|PACKED
)brace
id|circuit
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
DECL|typedef|fr_dlc_status_t
)brace
id|fr_dlc_status_t
suffix:semicolon
multiline_comment|/* &squot;status&squot; defines */
DECL|macro|FR_LINK_INOPER
mdefine_line|#define&t;FR_LINK_INOPER&t;0x00&t;&t;/* for global status (DLCI == 0) */
DECL|macro|FR_LINK_OPER
mdefine_line|#define&t;FR_LINK_OPER&t;0x01
DECL|macro|FR_DLCI_DELETED
mdefine_line|#define&t;FR_DLCI_DELETED&t;0x01&t;&t;/* for circuit status (DLCI != 0) */
DECL|macro|FR_DLCI_ACTIVE
mdefine_line|#define&t;FR_DLCI_ACTIVE&t;0x02
DECL|macro|FR_DLCI_WAITING
mdefine_line|#define&t;FR_DLCI_WAITING&t;0x04
DECL|macro|FR_DLCI_NEW
mdefine_line|#define&t;FR_DLCI_NEW&t;0x08
DECL|macro|FR_DLCI_REPORT
mdefine_line|#define&t;FR_DLCI_REPORT&t;0x40
multiline_comment|/*----------------------------------------------------------------------------&n; * Global Statistics Block.&n; *&t;This structure is returned by the FR_READ_STATISTICS command when&n; *&t;dcli == 0.&n; */
DECL|struct|fr_link_stat
r_typedef
r_struct
id|fr_link_stat
(brace
DECL|member|PACKED
r_int
r_int
id|rx_too_long
id|PACKED
suffix:semicolon
multiline_comment|/* 00h:  */
DECL|member|PACKED
r_int
r_int
id|rx_dropped
id|PACKED
suffix:semicolon
multiline_comment|/* 02h:  */
DECL|member|PACKED
r_int
r_int
id|rx_dropped2
id|PACKED
suffix:semicolon
multiline_comment|/* 04h:  */
DECL|member|PACKED
r_int
r_int
id|rx_bad_dlci
id|PACKED
suffix:semicolon
multiline_comment|/* 06h:  */
DECL|member|PACKED
r_int
r_int
id|rx_bad_format
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|member|PACKED
r_int
r_int
id|retransmitted
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah:  */
DECL|member|PACKED
r_int
r_int
id|cpe_tx_FSE
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch:  */
DECL|member|PACKED
r_int
r_int
id|cpe_tx_LIV
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh:  */
DECL|member|PACKED
r_int
r_int
id|cpe_rx_FSR
id|PACKED
suffix:semicolon
multiline_comment|/* 10h:  */
DECL|member|PACKED
r_int
r_int
id|cpe_rx_LIV
id|PACKED
suffix:semicolon
multiline_comment|/* 12h:  */
DECL|member|PACKED
r_int
r_int
id|node_rx_FSE
id|PACKED
suffix:semicolon
multiline_comment|/* 14h:  */
DECL|member|PACKED
r_int
r_int
id|node_rx_LIV
id|PACKED
suffix:semicolon
multiline_comment|/* 16h:  */
DECL|member|PACKED
r_int
r_int
id|node_tx_FSR
id|PACKED
suffix:semicolon
multiline_comment|/* 18h:  */
DECL|member|PACKED
r_int
r_int
id|node_tx_LIV
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ah:  */
DECL|member|PACKED
r_int
r_int
id|rx_ISF_err
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ch:  */
DECL|member|PACKED
r_int
r_int
id|rx_unsolicited
id|PACKED
suffix:semicolon
multiline_comment|/* 1Eh:  */
DECL|member|PACKED
r_int
r_int
id|rx_SSN_err
id|PACKED
suffix:semicolon
multiline_comment|/* 20h:  */
DECL|member|PACKED
r_int
r_int
id|rx_RSN_err
id|PACKED
suffix:semicolon
multiline_comment|/* 22h:  */
DECL|member|PACKED
r_int
r_int
id|T391_timeouts
id|PACKED
suffix:semicolon
multiline_comment|/* 24h:  */
DECL|member|PACKED
r_int
r_int
id|T392_timeouts
id|PACKED
suffix:semicolon
multiline_comment|/* 26h:  */
DECL|member|PACKED
r_int
r_int
id|N392_reached
id|PACKED
suffix:semicolon
multiline_comment|/* 28h:  */
DECL|member|PACKED
r_int
r_int
id|cpe_SSN_RSN
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ah:  */
DECL|member|PACKED
r_int
r_int
id|current_SSN
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ch:  */
DECL|member|PACKED
r_int
r_int
id|current_RSN
id|PACKED
suffix:semicolon
multiline_comment|/* 2Eh:  */
DECL|member|PACKED
r_int
r_int
id|curreny_T391
id|PACKED
suffix:semicolon
multiline_comment|/* 30h:  */
DECL|member|PACKED
r_int
r_int
id|current_T392
id|PACKED
suffix:semicolon
multiline_comment|/* 32h:  */
DECL|member|PACKED
r_int
r_int
id|current_N392
id|PACKED
suffix:semicolon
multiline_comment|/* 34h:  */
DECL|member|PACKED
r_int
r_int
id|current_N393
id|PACKED
suffix:semicolon
multiline_comment|/* 36h:  */
DECL|typedef|fr_link_stat_t
)brace
id|fr_link_stat_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * DLCI statistics.&n; *&t;This structure is returned by the FR_READ_STATISTICS command when&n; *&t;dlci != 0.&n; */
DECL|struct|fr_dlci_stat
r_typedef
r_struct
id|fr_dlci_stat
(brace
DECL|member|PACKED
r_int
r_int
id|tx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 00h:  */
DECL|member|PACKED
r_int
r_int
id|tx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 04h:  */
DECL|member|PACKED
r_int
r_int
id|rx_frames
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|member|PACKED
r_int
r_int
id|rx_bytes
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch:  */
DECL|member|PACKED
r_int
r_int
id|rx_dropped
id|PACKED
suffix:semicolon
multiline_comment|/* 10h:  */
DECL|member|PACKED
r_int
r_int
id|rx_inactive
id|PACKED
suffix:semicolon
multiline_comment|/* 14h:  */
DECL|member|PACKED
r_int
r_int
id|rx_exceed_CIR
id|PACKED
suffix:semicolon
multiline_comment|/* 18h:  */
DECL|member|PACKED
r_int
r_int
id|rx_DE_set
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ch:  */
DECL|member|PACKED
r_int
r_int
id|tx_throughput
id|PACKED
suffix:semicolon
multiline_comment|/* 20h:  */
DECL|member|PACKED
r_int
r_int
id|tx_calc_timer
id|PACKED
suffix:semicolon
multiline_comment|/* 24h:  */
DECL|member|PACKED
r_int
r_int
id|rx_throughput
id|PACKED
suffix:semicolon
multiline_comment|/* 28h:  */
DECL|member|PACKED
r_int
r_int
id|rx_calc_timer
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ch:  */
DECL|typedef|fr_dlci_stat_t
)brace
id|fr_dlci_stat_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Communications error statistics.&n; *&t;This structure is returned by the FR_READ_ERROR_STATS command.&n; */
DECL|struct|fr_comm_stat
r_typedef
r_struct
id|fr_comm_stat
(brace
DECL|member|PACKED
r_int
r_char
id|rx_overruns
id|PACKED
suffix:semicolon
multiline_comment|/* 00h:  */
DECL|member|PACKED
r_int
r_char
id|rx_bad_crc
id|PACKED
suffix:semicolon
multiline_comment|/* 01h:  */
DECL|member|PACKED
r_int
r_char
id|rx_aborts
id|PACKED
suffix:semicolon
multiline_comment|/* 02h:  */
DECL|member|PACKED
r_int
r_char
id|rx_too_long
id|PACKED
suffix:semicolon
multiline_comment|/* 03h:  */
DECL|member|PACKED
r_int
r_char
id|tx_aborts
id|PACKED
suffix:semicolon
multiline_comment|/* 04h:  */
DECL|member|PACKED
r_int
r_char
id|tx_underruns
id|PACKED
suffix:semicolon
multiline_comment|/* 05h:  */
DECL|member|PACKED
r_int
r_char
id|tx_missed_undr
id|PACKED
suffix:semicolon
multiline_comment|/* 06h:  */
DECL|member|PACKED
r_int
r_char
id|dcd_dropped
id|PACKED
suffix:semicolon
multiline_comment|/* 07h:  */
DECL|member|PACKED
r_int
r_char
id|cts_dropped
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|typedef|fr_comm_stat_t
)brace
id|fr_comm_stat_t
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * Defines for the FR_ISSUE_IS_FRAME command.&n; */
DECL|macro|FR_ISF_LVE
mdefine_line|#define&t;FR_ISF_LVE&t;2&t;&t;/* issue Link Verification Enquiry */
DECL|macro|FR_ISF_FSE
mdefine_line|#define&t;FR_ISF_FSE&t;3&t;&t;/* issue Full Status Enquiry */
macro_line|#ifdef&t;&t;_MSC_
macro_line|#  pragma&t;pack()
macro_line|#endif
macro_line|#endif&t;/* _SDLA_FR_H */
eof
