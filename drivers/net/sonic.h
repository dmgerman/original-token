multiline_comment|/*&n; * Helpfile for sonic.c&n; *&n; * (C) Waldorf Electronics, Germany&n; * Written by Andreas Busse&n; *&n; * NOTE: most of the structure definitions here are endian dependent.&n; * If you want to use this driver on big endian machines, the data&n; * and pad structure members must be exchanged. Also, the structures&n; * need to be changed accordingly to the bus size. &n; *&n; */
macro_line|#ifndef SONIC_H
DECL|macro|SONIC_H
mdefine_line|#define SONIC_H
multiline_comment|/*&n; * Macros to access SONIC registers&n; */
DECL|macro|SONIC_READ
mdefine_line|#define SONIC_READ(reg) &bslash;&n;&t;*((volatile unsigned int *)base_addr+reg)
DECL|macro|SONIC_WRITE
mdefine_line|#define SONIC_WRITE(reg,val) &bslash;&n;&t;*((volatile unsigned int *)base_addr+reg) = val
multiline_comment|/*&n; * SONIC register offsets&n; */
DECL|macro|SONIC_CMD
mdefine_line|#define SONIC_CMD              0x00
DECL|macro|SONIC_DCR
mdefine_line|#define SONIC_DCR              0x01
DECL|macro|SONIC_RCR
mdefine_line|#define SONIC_RCR              0x02
DECL|macro|SONIC_TCR
mdefine_line|#define SONIC_TCR              0x03
DECL|macro|SONIC_IMR
mdefine_line|#define SONIC_IMR              0x04
DECL|macro|SONIC_ISR
mdefine_line|#define SONIC_ISR              0x05
DECL|macro|SONIC_UTDA
mdefine_line|#define SONIC_UTDA             0x06
DECL|macro|SONIC_CTDA
mdefine_line|#define SONIC_CTDA             0x07
DECL|macro|SONIC_URDA
mdefine_line|#define SONIC_URDA             0x0d
DECL|macro|SONIC_CRDA
mdefine_line|#define SONIC_CRDA             0x0e
DECL|macro|SONIC_EOBC
mdefine_line|#define SONIC_EOBC             0x13
DECL|macro|SONIC_URRA
mdefine_line|#define SONIC_URRA             0x14
DECL|macro|SONIC_RSA
mdefine_line|#define SONIC_RSA              0x15
DECL|macro|SONIC_REA
mdefine_line|#define SONIC_REA              0x16
DECL|macro|SONIC_RRP
mdefine_line|#define SONIC_RRP              0x17
DECL|macro|SONIC_RWP
mdefine_line|#define SONIC_RWP              0x18
DECL|macro|SONIC_RSC
mdefine_line|#define SONIC_RSC              0x2b
DECL|macro|SONIC_CEP
mdefine_line|#define SONIC_CEP              0x21
DECL|macro|SONIC_CAP2
mdefine_line|#define SONIC_CAP2             0x22
DECL|macro|SONIC_CAP1
mdefine_line|#define SONIC_CAP1             0x23
DECL|macro|SONIC_CAP0
mdefine_line|#define SONIC_CAP0             0x24
DECL|macro|SONIC_CE
mdefine_line|#define SONIC_CE               0x25
DECL|macro|SONIC_CDP
mdefine_line|#define SONIC_CDP              0x26
DECL|macro|SONIC_CDC
mdefine_line|#define SONIC_CDC              0x27
DECL|macro|SONIC_WT0
mdefine_line|#define SONIC_WT0              0x29
DECL|macro|SONIC_WT1
mdefine_line|#define SONIC_WT1              0x2a
DECL|macro|SONIC_SR
mdefine_line|#define SONIC_SR               0x28
multiline_comment|/* test-only registers */
DECL|macro|SONIC_TPS
mdefine_line|#define SONIC_TPS&t;&t;0x08
DECL|macro|SONIC_TFC
mdefine_line|#define SONIC_TFC&t;&t;0x09
DECL|macro|SONIC_TSA0
mdefine_line|#define SONIC_TSA0&t;&t;0x0a
DECL|macro|SONIC_TSA1
mdefine_line|#define SONIC_TSA1&t;&t;0x0b
DECL|macro|SONIC_TFS
mdefine_line|#define SONIC_TFS&t;&t;0x0c
DECL|macro|SONIC_CRBA0
mdefine_line|#define SONIC_CRBA0&t;&t;0x0f
DECL|macro|SONIC_CRBA1
mdefine_line|#define SONIC_CRBA1&t;&t;0x10
DECL|macro|SONIC_RBWC0
mdefine_line|#define SONIC_RBWC0&t;&t;0x11
DECL|macro|SONIC_RBWC1
mdefine_line|#define SONIC_RBWC1&t;&t;0x12
DECL|macro|SONIC_TTDA
mdefine_line|#define SONIC_TTDA&t;&t;0x20
DECL|macro|SONIC_MDT
mdefine_line|#define SONIC_MDT&t;&t;0x2f
DECL|macro|SONIC_TRBA0
mdefine_line|#define SONIC_TRBA0&t;&t;0x19
DECL|macro|SONIC_TRBA1
mdefine_line|#define SONIC_TRBA1&t;&t;0x1a
DECL|macro|SONIC_TBWC0
mdefine_line|#define SONIC_TBWC0&t;&t;0x1b
DECL|macro|SONIC_TBWC1
mdefine_line|#define SONIC_TBWC1&t;&t;0x1c
DECL|macro|SONIC_LLFA
mdefine_line|#define SONIC_LLFA&t;&t;0x1f
DECL|macro|SONIC_ADDR0
mdefine_line|#define SONIC_ADDR0&t;&t;0x1d
DECL|macro|SONIC_ADDR1
mdefine_line|#define SONIC_ADDR1&t;&t;0x1e
multiline_comment|/*&n; * Error counters&n; */
DECL|macro|SONIC_CRCT
mdefine_line|#define SONIC_CRCT              0x2c
DECL|macro|SONIC_FAET
mdefine_line|#define SONIC_FAET              0x2d
DECL|macro|SONIC_MPT
mdefine_line|#define SONIC_MPT               0x2e
multiline_comment|/*&n; * SONIC command bits&n; */
DECL|macro|SONIC_CR_LCAM
mdefine_line|#define SONIC_CR_LCAM           0x0200
DECL|macro|SONIC_CR_RRRA
mdefine_line|#define SONIC_CR_RRRA           0x0100
DECL|macro|SONIC_CR_RST
mdefine_line|#define SONIC_CR_RST            0x0080
DECL|macro|SONIC_CR_ST
mdefine_line|#define SONIC_CR_ST             0x0020
DECL|macro|SONIC_CR_STP
mdefine_line|#define SONIC_CR_STP            0x0010
DECL|macro|SONIC_CR_RXEN
mdefine_line|#define SONIC_CR_RXEN           0x0008
DECL|macro|SONIC_CR_RXDIS
mdefine_line|#define SONIC_CR_RXDIS          0x0004
DECL|macro|SONIC_CR_TXP
mdefine_line|#define SONIC_CR_TXP            0x0002
DECL|macro|SONIC_CR_HTX
mdefine_line|#define SONIC_CR_HTX            0x0001
multiline_comment|/*&n; * SONIC data configuration bits&n; */
DECL|macro|SONIC_DCR_EXBUS
mdefine_line|#define SONIC_DCR_EXBUS         0x8000
DECL|macro|SONIC_DCR_LBR
mdefine_line|#define SONIC_DCR_LBR           0x2000
DECL|macro|SONIC_DCR_PO1
mdefine_line|#define SONIC_DCR_PO1           0x1000
DECL|macro|SONIC_DCR_PO0
mdefine_line|#define SONIC_DCR_PO0           0x0800
DECL|macro|SONIC_DCR_SBUS
mdefine_line|#define SONIC_DCR_SBUS          0x0400
DECL|macro|SONIC_DCR_USR1
mdefine_line|#define SONIC_DCR_USR1          0x0200
DECL|macro|SONIC_DCR_USR0
mdefine_line|#define SONIC_DCR_USR0          0x0100
DECL|macro|SONIC_DCR_WC1
mdefine_line|#define SONIC_DCR_WC1           0x0080
DECL|macro|SONIC_DCR_WC0
mdefine_line|#define SONIC_DCR_WC0           0x0040
DECL|macro|SONIC_DCR_DW
mdefine_line|#define SONIC_DCR_DW            0x0020
DECL|macro|SONIC_DCR_BMS
mdefine_line|#define SONIC_DCR_BMS           0x0010
DECL|macro|SONIC_DCR_RFT1
mdefine_line|#define SONIC_DCR_RFT1          0x0008
DECL|macro|SONIC_DCR_RFT0
mdefine_line|#define SONIC_DCR_RFT0          0x0004
DECL|macro|SONIC_DCR_TFT1
mdefine_line|#define SONIC_DCR_TFT1          0x0002
DECL|macro|SONIC_DCR_TFT0
mdefine_line|#define SONIC_DCR_TFT0          0x0001
multiline_comment|/*&n; * Constants for the SONIC receive control register.&n; */
DECL|macro|SONIC_RCR_ERR
mdefine_line|#define SONIC_RCR_ERR           0x8000
DECL|macro|SONIC_RCR_RNT
mdefine_line|#define SONIC_RCR_RNT           0x4000
DECL|macro|SONIC_RCR_BRD
mdefine_line|#define SONIC_RCR_BRD           0x2000
DECL|macro|SONIC_RCR_PRO
mdefine_line|#define SONIC_RCR_PRO           0x1000
DECL|macro|SONIC_RCR_AMC
mdefine_line|#define SONIC_RCR_AMC           0x0800
DECL|macro|SONIC_RCR_LB1
mdefine_line|#define SONIC_RCR_LB1           0x0400
DECL|macro|SONIC_RCR_LB0
mdefine_line|#define SONIC_RCR_LB0           0x0200
DECL|macro|SONIC_RCR_MC
mdefine_line|#define SONIC_RCR_MC            0x0100
DECL|macro|SONIC_RCR_BC
mdefine_line|#define SONIC_RCR_BC            0x0080
DECL|macro|SONIC_RCR_LPKT
mdefine_line|#define SONIC_RCR_LPKT          0x0040
DECL|macro|SONIC_RCR_CRS
mdefine_line|#define SONIC_RCR_CRS           0x0020
DECL|macro|SONIC_RCR_COL
mdefine_line|#define SONIC_RCR_COL           0x0010
DECL|macro|SONIC_RCR_CRCR
mdefine_line|#define SONIC_RCR_CRCR          0x0008
DECL|macro|SONIC_RCR_FAER
mdefine_line|#define SONIC_RCR_FAER          0x0004
DECL|macro|SONIC_RCR_LBK
mdefine_line|#define SONIC_RCR_LBK           0x0002
DECL|macro|SONIC_RCR_PRX
mdefine_line|#define SONIC_RCR_PRX           0x0001
DECL|macro|SONIC_RCR_LB_OFF
mdefine_line|#define SONIC_RCR_LB_OFF        0
DECL|macro|SONIC_RCR_LB_MAC
mdefine_line|#define SONIC_RCR_LB_MAC        SONIC_RCR_LB0
DECL|macro|SONIC_RCR_LB_ENDEC
mdefine_line|#define SONIC_RCR_LB_ENDEC      SONIC_RCR_LB1
DECL|macro|SONIC_RCR_LB_TRANS
mdefine_line|#define SONIC_RCR_LB_TRANS      (SONIC_RCR_LB0 | SONIC_RCR_LB1)
multiline_comment|/* default RCR setup */
DECL|macro|SONIC_RCR_DEFAULT
mdefine_line|#define SONIC_RCR_DEFAULT       (SONIC_RCR_BRD)
multiline_comment|/*&n; * SONIC Transmit Control register bits&n; */
DECL|macro|SONIC_TCR_PINTR
mdefine_line|#define SONIC_TCR_PINTR         0x8000
DECL|macro|SONIC_TCR_POWC
mdefine_line|#define SONIC_TCR_POWC          0x4000
DECL|macro|SONIC_TCR_CRCI
mdefine_line|#define SONIC_TCR_CRCI          0x2000
DECL|macro|SONIC_TCR_EXDIS
mdefine_line|#define SONIC_TCR_EXDIS         0x1000
DECL|macro|SONIC_TCR_EXD
mdefine_line|#define SONIC_TCR_EXD           0x0400
DECL|macro|SONIC_TCR_DEF
mdefine_line|#define SONIC_TCR_DEF           0x0200
DECL|macro|SONIC_TCR_NCRS
mdefine_line|#define SONIC_TCR_NCRS          0x0100
DECL|macro|SONIC_TCR_CRLS
mdefine_line|#define SONIC_TCR_CRLS          0x0080
DECL|macro|SONIC_TCR_EXC
mdefine_line|#define SONIC_TCR_EXC           0x0040
DECL|macro|SONIC_TCR_PMB
mdefine_line|#define SONIC_TCR_PMB           0x0008
DECL|macro|SONIC_TCR_FU
mdefine_line|#define SONIC_TCR_FU            0x0004
DECL|macro|SONIC_TCR_BCM
mdefine_line|#define SONIC_TCR_BCM           0x0002
DECL|macro|SONIC_TCR_PTX
mdefine_line|#define SONIC_TCR_PTX           0x0001
DECL|macro|SONIC_TCR_DEFAULT
mdefine_line|#define SONIC_TCR_DEFAULT       0x0000
multiline_comment|/* &n; * Constants for the SONIC_INTERRUPT_MASK and&n; * SONIC_INTERRUPT_STATUS registers.&n; */
DECL|macro|SONIC_INT_BR
mdefine_line|#define SONIC_INT_BR&t;&t;0x4000
DECL|macro|SONIC_INT_HBL
mdefine_line|#define SONIC_INT_HBL&t;&t;0x2000
DECL|macro|SONIC_INT_LCD
mdefine_line|#define SONIC_INT_LCD           0x1000
DECL|macro|SONIC_INT_PINT
mdefine_line|#define SONIC_INT_PINT          0x0800
DECL|macro|SONIC_INT_PKTRX
mdefine_line|#define SONIC_INT_PKTRX         0x0400
DECL|macro|SONIC_INT_TXDN
mdefine_line|#define SONIC_INT_TXDN          0x0200
DECL|macro|SONIC_INT_TXER
mdefine_line|#define SONIC_INT_TXER          0x0100
DECL|macro|SONIC_INT_TC
mdefine_line|#define SONIC_INT_TC            0x0080
DECL|macro|SONIC_INT_RDE
mdefine_line|#define SONIC_INT_RDE           0x0040
DECL|macro|SONIC_INT_RBE
mdefine_line|#define SONIC_INT_RBE           0x0020
DECL|macro|SONIC_INT_RBAE
mdefine_line|#define SONIC_INT_RBAE&t;&t;0x0010
DECL|macro|SONIC_INT_CRC
mdefine_line|#define SONIC_INT_CRC&t;&t;0x0008
DECL|macro|SONIC_INT_FAE
mdefine_line|#define SONIC_INT_FAE&t;&t;0x0004
DECL|macro|SONIC_INT_MP
mdefine_line|#define SONIC_INT_MP&t;&t;0x0002
DECL|macro|SONIC_INT_RFO
mdefine_line|#define SONIC_INT_RFO&t;&t;0x0001
multiline_comment|/*&n; * The interrupts we allow.&n; */
DECL|macro|SONIC_IMR_DEFAULT
mdefine_line|#define SONIC_IMR_DEFAULT&t;(SONIC_INT_BR | &bslash;&n;&t;&t;&t;&t;SONIC_INT_LCD | &bslash;&n;                                SONIC_INT_PINT | &bslash;&n;                                SONIC_INT_PKTRX | &bslash;&n;                                SONIC_INT_TXDN | &bslash;&n;                                SONIC_INT_TXER | &bslash;&n;                                SONIC_INT_RDE | &bslash;&n;                                SONIC_INT_RBE | &bslash;&n;                                SONIC_INT_RBAE | &bslash;&n;                                SONIC_INT_CRC | &bslash;&n;                                SONIC_INT_FAE | &bslash;&n;                                SONIC_INT_MP)
DECL|macro|SONIC_END_OF_LINKS
mdefine_line|#define&t;SONIC_END_OF_LINKS&t;0x0001
multiline_comment|/*&n; * structure definitions&n; */
r_typedef
r_struct
(brace
DECL|member|rx_bufadr_l
id|u32
id|rx_bufadr_l
suffix:semicolon
multiline_comment|/* receive buffer ptr */
DECL|member|rx_bufadr_h
id|u32
id|rx_bufadr_h
suffix:semicolon
DECL|member|rx_bufsize_l
id|u32
id|rx_bufsize_l
suffix:semicolon
multiline_comment|/* no. of words in the receive buffer */
DECL|member|rx_bufsize_h
id|u32
id|rx_bufsize_h
suffix:semicolon
DECL|typedef|sonic_rr_t
)brace
id|sonic_rr_t
suffix:semicolon
multiline_comment|/*&n; * Sonic receive descriptor. Receive descriptors are&n; * kept in a linked list of these structures.&n; */
r_typedef
r_struct
(brace
DECL|member|rx_status
id|u16
id|rx_status
suffix:semicolon
multiline_comment|/* status after reception of a packet */
DECL|member|pad0
id|u16
id|pad0
suffix:semicolon
DECL|member|rx_pktlen
id|u16
id|rx_pktlen
suffix:semicolon
multiline_comment|/* length of the packet incl. CRC */
DECL|member|pad1
id|u16
id|pad1
suffix:semicolon
multiline_comment|/*&n;   * Pointers to the location in the receive buffer area (RBA)&n;   * where the packet resides. A packet is always received into&n;   * a contiguous piece of memory.&n;   */
DECL|member|rx_pktptr_l
id|u16
id|rx_pktptr_l
suffix:semicolon
DECL|member|pad2
id|u16
id|pad2
suffix:semicolon
DECL|member|rx_pktptr_h
id|u16
id|rx_pktptr_h
suffix:semicolon
DECL|member|pad3
id|u16
id|pad3
suffix:semicolon
DECL|member|rx_seqno
id|u16
id|rx_seqno
suffix:semicolon
multiline_comment|/* sequence no. */
DECL|member|pad4
id|u16
id|pad4
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* link to next RDD (end if EOL bit set) */
DECL|member|pad5
id|u16
id|pad5
suffix:semicolon
multiline_comment|/*&n;   * Owner of this descriptor, 0= driver, 1=sonic&n;   */
DECL|member|in_use
id|u16
id|in_use
suffix:semicolon
DECL|member|pad6
id|u16
id|pad6
suffix:semicolon
DECL|member|rda_next
id|caddr_t
id|rda_next
suffix:semicolon
multiline_comment|/* pointer to next RD */
DECL|typedef|sonic_rd_t
)brace
id|sonic_rd_t
suffix:semicolon
multiline_comment|/*&n; * Describes a Transmit Descriptor&n; */
r_typedef
r_struct
(brace
DECL|member|tx_status
id|u16
id|tx_status
suffix:semicolon
multiline_comment|/* status after transmission of a packet */
DECL|member|pad0
id|u16
id|pad0
suffix:semicolon
DECL|member|tx_config
id|u16
id|tx_config
suffix:semicolon
multiline_comment|/* transmit configuration for this packet */
DECL|member|pad1
id|u16
id|pad1
suffix:semicolon
DECL|member|tx_pktsize
id|u16
id|tx_pktsize
suffix:semicolon
multiline_comment|/* size of the packet to be transmitted */
DECL|member|pad2
id|u16
id|pad2
suffix:semicolon
DECL|member|tx_frag_count
id|u16
id|tx_frag_count
suffix:semicolon
multiline_comment|/* no. of fragments */
DECL|member|pad3
id|u16
id|pad3
suffix:semicolon
DECL|member|tx_frag_ptr_l
id|u16
id|tx_frag_ptr_l
suffix:semicolon
DECL|member|pad4
id|u16
id|pad4
suffix:semicolon
DECL|member|tx_frag_ptr_h
id|u16
id|tx_frag_ptr_h
suffix:semicolon
DECL|member|pad5
id|u16
id|pad5
suffix:semicolon
DECL|member|tx_frag_size
id|u16
id|tx_frag_size
suffix:semicolon
DECL|member|pad6
id|u16
id|pad6
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* ptr to next descriptor */
DECL|member|pad7
id|u16
id|pad7
suffix:semicolon
DECL|typedef|sonic_td_t
)brace
id|sonic_td_t
suffix:semicolon
multiline_comment|/*&n; * Describes an entry in the CAM Descriptor Area.&n; */
r_typedef
r_struct
(brace
DECL|member|cam_entry_pointer
id|u16
id|cam_entry_pointer
suffix:semicolon
DECL|member|pad
id|u16
id|pad
suffix:semicolon
DECL|member|cam_frag2
id|u16
id|cam_frag2
suffix:semicolon
DECL|member|pad2
id|u16
id|pad2
suffix:semicolon
DECL|member|cam_frag1
id|u16
id|cam_frag1
suffix:semicolon
DECL|member|pad1
id|u16
id|pad1
suffix:semicolon
DECL|member|cam_frag0
id|u16
id|cam_frag0
suffix:semicolon
DECL|member|pad0
id|u16
id|pad0
suffix:semicolon
DECL|typedef|sonic_cd_t
)brace
id|sonic_cd_t
suffix:semicolon
DECL|macro|CAM_DESCRIPTORS
mdefine_line|#define CAM_DESCRIPTORS 16
r_typedef
r_struct
(brace
DECL|member|cam_desc
id|sonic_cd_t
id|cam_desc
(braket
id|CAM_DESCRIPTORS
)braket
suffix:semicolon
DECL|member|cam_enable
id|u16
id|cam_enable
suffix:semicolon
DECL|member|pad
id|u16
id|pad
suffix:semicolon
DECL|typedef|sonic_cda_t
)brace
id|sonic_cda_t
suffix:semicolon
macro_line|#endif /* SONIC_H */
eof