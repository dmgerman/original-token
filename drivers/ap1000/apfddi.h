multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
DECL|macro|BUFFER_MEM
mdefine_line|#define BUFFER_MEM&t;0x40000
DECL|macro|CSR0
mdefine_line|#define CSR0&t;&t;0x60000
DECL|macro|CSR1
mdefine_line|#define CSR1&t;&t;0x60004
DECL|macro|PLC
mdefine_line|#define PLC&t;&t;0x60080
DECL|macro|FORMAC
mdefine_line|#define FORMAC&t;&t;0x60200
DECL|macro|FIFO
mdefine_line|#define FIFO&t;&t;0x68000
multiline_comment|/* Size of buffer memory */
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;32768&t;&t;/* words; 128kB */
multiline_comment|/* Bits in CSR0 */
DECL|macro|CS0_INT_REQ
mdefine_line|#define CS0_INT_REQ&t;0x8000&t;&t;/* board interrupt request asserted */
DECL|macro|CS0_MAC_IRQ
mdefine_line|#define CS0_MAC_IRQ&t;0x4000&t;&t;/* FORMAC is requesting interrupt */
DECL|macro|CS0_PHY_IRQ
mdefine_line|#define CS0_PHY_IRQ&t;0x2000&t;&t;/* PLC is requesting interrupt */
DECL|macro|CS0_LED2
mdefine_line|#define CS0_LED2&t;0x1000&t;&t;/* turn on led 2 */
DECL|macro|CS0_DO_IRQ
mdefine_line|#define CS0_DO_IRQ&t;0x0200&t;&t;/* request interrupt */
DECL|macro|CS0_INT_ENABLE
mdefine_line|#define CS0_INT_ENABLE&t;0x0100&t;&t;/* enable interrupt requests */
DECL|macro|CS0_DMA_ENABLE
mdefine_line|#define CS0_DMA_ENABLE&t;0x0080&t;&t;/* enable DMA requests */
DECL|macro|CS0_DMA_RECV
mdefine_line|#define CS0_DMA_RECV&t;0x0040&t;&t;/* DMA requests are in receive dirn. */
DECL|macro|CS0_LED1
mdefine_line|#define CS0_LED1&t;0x0010&t;&t;/* turn on led 1 */
DECL|macro|CS0_LED0
mdefine_line|#define CS0_LED0&t;0x0008&t;&t;/* turn on led 0 (red) */
DECL|macro|CS0_HREQ
mdefine_line|#define CS0_HREQ&t;0x0007&t;&t;/* host request to FORMAC */
DECL|macro|CS0_HREQ_WSPEC
mdefine_line|#define CS0_HREQ_WSPEC&t;0x0002&t;&t;/* write special frames */
DECL|macro|CS0_HREQ_RECV
mdefine_line|#define CS0_HREQ_RECV&t;0x0003&t;&t;/* read receive queue */
DECL|macro|CS0_HREQ_WS
mdefine_line|#define CS0_HREQ_WS&t;0x0004&t;&t;/* write synchronous queue */
DECL|macro|CS0_HREQ_WA0
mdefine_line|#define CS0_HREQ_WA0&t;0x0005&t;&t;/* write async queue 0 */
DECL|macro|CS0_HREQ_WA1
mdefine_line|#define CS0_HREQ_WA1&t;0x0006&t;&t;/* write async queue 1 */
DECL|macro|CS0_HREQ_WA2
mdefine_line|#define CS0_HREQ_WA2&t;0x0007&t;&t;/* write async queue 2 */
multiline_comment|/* Bits in CSR1 */
DECL|macro|CS1_THIS_QAF
mdefine_line|#define CS1_THIS_QAF&t;0x0800&t;&t;/* this queue almost full */
DECL|macro|CS1_FIFO_TAG
mdefine_line|#define CS1_FIFO_TAG&t;0x0400&t;&t;/* tag of word at head of fifo */
DECL|macro|CS1_BUF_RD_TAG
mdefine_line|#define CS1_BUF_RD_TAG&t;0x0200&t;&t;/* tag of last word read from buffer */
DECL|macro|CS1_BUF_WR_TAG
mdefine_line|#define CS1_BUF_WR_TAG&t;0x0100&t;&t;/* tag to write to buffer */
DECL|macro|CS1_TAGMODE
mdefine_line|#define CS1_TAGMODE&t;0x0080&t;&t;/* enable tag mode */
DECL|macro|CS1_RESET_MAC
mdefine_line|#define CS1_RESET_MAC&t;0x0040&t;&t;/* reset FORMAC and PLC */
DECL|macro|CS1_RESET_FIFO
mdefine_line|#define CS1_RESET_FIFO&t;0x0020&t;&t;/* reset FIFO */
DECL|macro|CS1_CLEAR_QAF
mdefine_line|#define CS1_CLEAR_QAF&t;0x0010&t;&t;/* clear queue-almost-full bits */
DECL|macro|CS1_FIFO_LEVEL
mdefine_line|#define CS1_FIFO_LEVEL&t;0x0007&t;&t;/* # words in FIFO (0 - 4) */
multiline_comment|/*&n; * FDDI Frame Control values.&n; */
DECL|macro|FDDI_SMT
mdefine_line|#define FDDI_SMT&t;&t;0x41
DECL|macro|FDDI_SMT_NSA
mdefine_line|#define FDDI_SMT_NSA&t;&t;0x4f
DECL|macro|FDDI_FC_LLC
mdefine_line|#define FDDI_FC_LLC&t;&t;0x50
DECL|macro|FDDI_FC_LLC_MASK
mdefine_line|#define FDDI_FC_LLC_MASK&t;0xf0
multiline_comment|/*&n; * Unnumbered LLC format commands&n; */
DECL|macro|LLC_UI
mdefine_line|#define LLC_UI&t;&t;0x3
DECL|macro|LLC_UI_P
mdefine_line|#define LLC_UI_P&t;0x13
DECL|macro|LLC_DISC
mdefine_line|#define LLC_DISC&t;0x43
DECL|macro|LLC_DISC_P
mdefine_line|#define&t;LLC_DISC_P&t;0x53
DECL|macro|LLC_UA
mdefine_line|#define LLC_UA&t;&t;0x63
DECL|macro|LLC_UA_P
mdefine_line|#define LLC_UA_P&t;0x73
DECL|macro|LLC_TEST
mdefine_line|#define LLC_TEST&t;0xe3
DECL|macro|LLC_TEST_P
mdefine_line|#define LLC_TEST_P&t;0xf3
DECL|macro|LLC_FRMR
mdefine_line|#define LLC_FRMR&t;0x87
DECL|macro|LLC_FRMR_P
mdefine_line|#define&t;LLC_FRMR_P&t;0x97
DECL|macro|LLC_DM
mdefine_line|#define LLC_DM&t;&t;0x0f
DECL|macro|LLC_DM_P
mdefine_line|#define&t;LLC_DM_P&t;0x1f
DECL|macro|LLC_XID
mdefine_line|#define LLC_XID&t;&t;0xaf
DECL|macro|LLC_XID_P
mdefine_line|#define LLC_XID_P&t;0xbf
DECL|macro|LLC_SABME
mdefine_line|#define LLC_SABME&t;0x6f
DECL|macro|LLC_SABME_P
mdefine_line|#define LLC_SABME_P&t;0x7f
multiline_comment|/*&n; * Supervisory LLC commands&n; */
DECL|macro|LLC_RR
mdefine_line|#define&t;LLC_RR&t;&t;0x01
DECL|macro|LLC_RNR
mdefine_line|#define&t;LLC_RNR&t;&t;0x05
DECL|macro|LLC_REJ
mdefine_line|#define&t;LLC_REJ&t;&t;0x09
multiline_comment|/*&n; * Info format - dummy only&n; */
DECL|macro|LLC_INFO
mdefine_line|#define&t;LLC_INFO&t;0x00
multiline_comment|/*&n; * ISO PDTR 10178 contains among others&n; */
DECL|macro|LLC_X25_LSAP
mdefine_line|#define LLC_X25_LSAP&t;0x7e
DECL|macro|LLC_SNAP_LSAP
mdefine_line|#define LLC_SNAP_LSAP&t;0xaa
DECL|macro|LLC_ISO_LSAP
mdefine_line|#define LLC_ISO_LSAP&t;0xfe
multiline_comment|/*&n; * Structure of the FDDI MAC header.&n; */
DECL|struct|fddi_header
r_struct
id|fddi_header
(brace
DECL|member|fddi_fc
id|u_char
id|fddi_fc
suffix:semicolon
multiline_comment|/* frame control field */
DECL|member|fddi_dhost
id|u_char
id|fddi_dhost
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* destination address */
DECL|member|fddi_shost
id|u_char
id|fddi_shost
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* source address */
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of LLC/SNAP header.&n; */
DECL|struct|llc_header
r_struct
id|llc_header
(brace
DECL|member|llc_dsap
id|u_char
id|llc_dsap
suffix:semicolon
DECL|member|llc_ssap
id|u_char
id|llc_ssap
suffix:semicolon
DECL|member|snap_control
id|u_char
id|snap_control
suffix:semicolon
DECL|member|snap_org_code
id|u_char
id|snap_org_code
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|snap_ether_type
id|u_short
id|snap_ether_type
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDDI_HDRLEN
mdefine_line|#define FDDI_HDRLEN&t;13&t;/* sizeof(struct fddi_header) */
DECL|macro|LLC_SNAPLEN
mdefine_line|#define LLC_SNAPLEN&t;8&t;/* bytes for LLC/SNAP header */
DECL|macro|FDDI_HARDHDR_LEN
mdefine_line|#define FDDI_HARDHDR_LEN 28     /* Hard header size */
DECL|macro|FDDIMTU
mdefine_line|#define FDDIMTU&t;&t;4352
multiline_comment|/* Types of loopback we can do. */
r_typedef
r_enum
(brace
DECL|enumerator|loop_none
id|loop_none
comma
DECL|enumerator|loop_formac
id|loop_formac
comma
DECL|enumerator|loop_plc_lm
id|loop_plc_lm
comma
DECL|enumerator|loop_plc_eb
id|loop_plc_eb
comma
DECL|enumerator|loop_pdx
id|loop_pdx
DECL|typedef|LoopbackType
)brace
id|LoopbackType
suffix:semicolon
multiline_comment|/* Offset from fifo for writing word with tag. */
DECL|macro|FIFO_TAG
mdefine_line|#define FIFO_TAG&t;0x80
DECL|macro|MAX_FRAME_LEN
mdefine_line|#define MAX_FRAME_LEN&t;4500
r_void
id|set_ring_op
c_func
(paren
r_int
id|up
)paren
suffix:semicolon
r_void
id|rmt_event
c_func
(paren
r_int
id|st
)paren
suffix:semicolon
r_void
id|set_cf_join
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|apfddi_device
suffix:semicolon
r_extern
r_struct
id|net_device_stats
op_star
id|apfddi_stats
suffix:semicolon
eof
