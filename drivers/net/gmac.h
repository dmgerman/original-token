multiline_comment|/*&n; * Definitions for the GMAC ethernet chip, used in the&n; * Apple G4 powermac.&n; */
multiline_comment|/* Register offsets */
DECL|macro|INTR_STATUS
mdefine_line|#define&t;INTR_STATUS&t;&t;0x000c
DECL|macro|INTR_DISABLE
mdefine_line|#define INTR_DISABLE&t;&t;0x0010
DECL|macro|INTR_ACK
mdefine_line|#define INTR_ACK&t;&t;0x0014
DECL|macro|SW_RESET
mdefine_line|#define SW_RESET&t;&t;0x1010
DECL|macro|TXDMA_KICK
mdefine_line|#define TXDMA_KICK&t;&t;0x2000
DECL|macro|TXDMA_CONFIG
mdefine_line|#define TXDMA_CONFIG&t;&t;0x2004
DECL|macro|TXDMA_BASE_LOW
mdefine_line|#define TXDMA_BASE_LOW&t;&t;0x2008
DECL|macro|TXDMA_BASE_HIGH
mdefine_line|#define TXDMA_BASE_HIGH&t;&t;0x200c
DECL|macro|TXDMA_STATE_MACH
mdefine_line|#define TXDMA_STATE_MACH&t;0x2028
DECL|macro|TXDMA_COMPLETE
mdefine_line|#define TXDMA_COMPLETE&t;&t;0x2100
DECL|macro|RXDMA_CONFIG
mdefine_line|#define RXDMA_CONFIG&t;&t;0x4000
DECL|macro|RXDMA_BASE_LOW
mdefine_line|#define RXDMA_BASE_LOW&t;&t;0x4004
DECL|macro|RXDMA_BASE_HIGH
mdefine_line|#define RXDMA_BASE_HIGH&t;&t;0x4008
DECL|macro|RXDMA_KICK
mdefine_line|#define RXDMA_KICK&t;&t;0x4100
DECL|macro|MACPAUSE
mdefine_line|#define MACPAUSE&t;&t;0x6008
DECL|macro|TXMAC_STATUS
mdefine_line|#define TXMAC_STATUS&t;&t;0x6010
DECL|macro|TXMAC_CONFIG
mdefine_line|#define TXMAC_CONFIG&t;&t;0x6030
DECL|macro|RXMAC_CONFIG
mdefine_line|#define RXMAC_CONFIG&t;&t;0x6034
DECL|macro|MACCNTL_CONFIG
mdefine_line|#define MACCNTL_CONFIG&t;&t;0x6038
DECL|macro|XIF_CONFIG
mdefine_line|#define XIF_CONFIG&t;&t;0x603c
DECL|macro|IPG0
mdefine_line|#define IPG0&t;&t;&t;0x6040
DECL|macro|IPG1
mdefine_line|#define IPG1&t;&t;&t;0x6044
DECL|macro|IPG2
mdefine_line|#define IPG2&t;&t;&t;0x6048
DECL|macro|SLOTTIME
mdefine_line|#define SLOTTIME&t;&t;0x604c
DECL|macro|MINFRAMESIZE
mdefine_line|#define MINFRAMESIZE&t;&t;0x6050
DECL|macro|MAXFRAMESIZE
mdefine_line|#define MAXFRAMESIZE&t;&t;0x6054
DECL|macro|PASIZE
mdefine_line|#define PASIZE&t;&t;&t;0x6058
DECL|macro|JAMSIZE
mdefine_line|#define JAMSIZE&t;&t;&t;0x605c
DECL|macro|ATTEMPT_LIMIT
mdefine_line|#define ATTEMPT_LIMIT&t;&t;0x6060
DECL|macro|MACCNTL_TYPE
mdefine_line|#define MACCNTL_TYPE&t;&t;0x6064
DECL|macro|MAC_ADDR_0
mdefine_line|#define MAC_ADDR_0&t;&t;0x6080
DECL|macro|MAC_ADDR_1
mdefine_line|#define MAC_ADDR_1&t;&t;0x6084
DECL|macro|MAC_ADDR_2
mdefine_line|#define MAC_ADDR_2&t;&t;0x6088
DECL|macro|MAC_ADDR_3
mdefine_line|#define MAC_ADDR_3&t;&t;0x608c
DECL|macro|MAC_ADDR_4
mdefine_line|#define MAC_ADDR_4&t;&t;0x6090
DECL|macro|MAC_ADDR_5
mdefine_line|#define MAC_ADDR_5&t;&t;0x6094
DECL|macro|MAC_ADDR_6
mdefine_line|#define MAC_ADDR_6&t;&t;0x6098
DECL|macro|MAC_ADDR_7
mdefine_line|#define MAC_ADDR_7&t;&t;0x609c
DECL|macro|MAC_ADDR_8
mdefine_line|#define MAC_ADDR_8&t;&t;0x60a0
DECL|macro|MAC_ADDR_FILTER_0
mdefine_line|#define MAC_ADDR_FILTER_0&t;0x60a4
DECL|macro|MAC_ADDR_FILTER_1
mdefine_line|#define MAC_ADDR_FILTER_1&t;0x60a8
DECL|macro|MAC_ADDR_FILTER_2
mdefine_line|#define MAC_ADDR_FILTER_2&t;0x60ac
DECL|macro|MAC_ADDR_FILTER_MASK21
mdefine_line|#define MAC_ADDR_FILTER_MASK21&t;0x60b0
DECL|macro|MAC_ADDR_FILTER_MASK0
mdefine_line|#define MAC_ADDR_FILTER_MASK0&t;0x60b4
DECL|macro|MAC_HASHTABLE
mdefine_line|#define MAC_HASHTABLE&t;&t;0x60c0
DECL|macro|RANSEED
mdefine_line|#define RANSEED&t;&t;&t;0x6130
DECL|macro|MIFFRAME
mdefine_line|#define MIFFRAME&t;&t;0x620c
DECL|macro|MIFCONFIG
mdefine_line|#define MIFCONFIG&t;&t;0x6210
DECL|macro|MIFINTMASK
mdefine_line|#define MIFINTMASK&t;&t;0x6214
DECL|macro|MIFSTATUS
mdefine_line|#define MIFSTATUS&t;&t;0x6218
DECL|macro|DATAPATHMODE
mdefine_line|#define DATAPATHMODE&t;&t;0x9050
multiline_comment|/* -- 0x000C&t;R-C&t;Global Interrupt status. &n; * d: 0x00000000&t;bits 0-6 cleared on read (C)&n; */
DECL|macro|GMAC_IRQ_TX_INT_ME
mdefine_line|#define GMAC_IRQ_TX_INT_ME&t;0x00000001&t;/* C Frame with INT_ME bit set in fifo */
DECL|macro|GMAC_IRQ_TX_ALL
mdefine_line|#define GMAC_IRQ_TX_ALL&t;&t;0x00000002&t;/* C TX descriptor ring empty */
DECL|macro|GMAC_IRQ_TX_DONE
mdefine_line|#define GMAC_IRQ_TX_DONE&t;0x00000004&t;/* C moved from host to TX fifo */
DECL|macro|GMAC_IRQ_RX_DONE
mdefine_line|#define GMAC_IRQ_RX_DONE&t;0x00000010&t;/* C moved from RX fifo to host */
DECL|macro|GMAC_IRQ_RX_NO_BUF
mdefine_line|#define GMAC_IRQ_RX_NO_BUF&t;0x00000020&t;/* C No RX buffer available */
DECL|macro|GMAC_IRQ_RX_TAG_ERR
mdefine_line|#define GMAC_IRQ_RX_TAG_ERR&t;0x00000040&t;/* C RX tag error */
DECL|macro|GMAC_IRQ_PCS
mdefine_line|#define GMAC_IRQ_PCS&t;&t;0x00002000&t;/* PCS interrupt ? */
DECL|macro|GMAC_IRQ_MAC_TX
mdefine_line|#define GMAC_IRQ_MAC_TX&t;&t;0x00004000&t;/* MAC tx register set */
DECL|macro|GMAC_IRQ_MAC_RX
mdefine_line|#define GMAC_IRQ_MAC_RX&t;&t;0x00008000&t;/* MAC rx register set  */
DECL|macro|GMAC_IRQ_MAC_CTRL
mdefine_line|#define GMAC_IRQ_MAC_CTRL&t;0x00010000&t;/* MAC control register set  */
DECL|macro|GMAC_IRQ_MIF
mdefine_line|#define GMAC_IRQ_MIF&t;&t;0x00020000&t;/* MIF status register set */
DECL|macro|GMAC_IRQ_BUS_ERROR
mdefine_line|#define GMAC_IRQ_BUS_ERROR&t;0x00040000&t;/* Bus error status register set */
DECL|macro|GMAC_IRQ_TX_COMP
mdefine_line|#define GMAC_IRQ_TX_COMP&t;0xfff80000&t;/* TX completion mask */
multiline_comment|/* -- 0x6210&t;RW&t;MIF config reg&n; */
DECL|macro|GMAC_MIF_CFGPS
mdefine_line|#define&t;GMAC_MIF_CFGPS&t;&t;&t;0x00000001&t;/* PHY Select */
DECL|macro|GMAC_MIF_CFGPE
mdefine_line|#define&t;GMAC_MIF_CFGPE&t;&t;&t;0x00000002&t;/* Poll Enable */
DECL|macro|GMAC_MIF_CFGBB
mdefine_line|#define&t;GMAC_MIF_CFGBB&t;&t;&t;0x00000004&t;/* Bit Bang Enable */
DECL|macro|GMAC_MIF_CFGPR_MASK
mdefine_line|#define&t;GMAC_MIF_CFGPR_MASK&t;&t;0x000000f8&t;/* Poll Register address */
DECL|macro|GMAC_MIF_CFGPR_SHIFT
mdefine_line|#define&t;GMAC_MIF_CFGPR_SHIFT&t;&t;3
DECL|macro|GMAC_MIF_CFGM0
mdefine_line|#define&t;GMAC_MIF_CFGM0&t;&t;&t;0x00000100&t;/* MDIO_0 Data / MDIO_0 attached */
DECL|macro|GMAC_MIF_CFGM1
mdefine_line|#define&t;GMAC_MIF_CFGM1&t;&t;&t;0x00000200&t;/* MDIO_1 Data / MDIO_1 attached */
DECL|macro|GMAC_MIF_CFGPD_MASK
mdefine_line|#define&t;GMAC_MIF_CFGPD_MASK&t;&t;0x00007c00&t;/* Poll Device PHY address */
DECL|macro|GMAC_MIF_CFGPD_SHIFT
mdefine_line|#define&t;GMAC_MIF_CFGPD_SHIFT&t;&t;10
DECL|macro|GMAC_MIF_POLL_DELAY
mdefine_line|#define&t;GMAC_MIF_POLL_DELAY&t;&t;200
DECL|macro|GMAC_INTERNAL_PHYAD
mdefine_line|#define&t;GMAC_INTERNAL_PHYAD&t;&t;1&t;&t;/* PHY address for int. transceiver */
DECL|macro|GMAC_EXTERNAL_PHYAD
mdefine_line|#define&t;GMAC_EXTERNAL_PHYAD&t;&t;0&t;&t;/* PHY address for ext. transceiver */
multiline_comment|/* -- 0x6214&t;RW&t;MIF interrupt mask reg&n; *&t;&t;&t;same as basic/status Register&n; */
multiline_comment|/* -- 0x6214&t;RW&t;MIF basic/status reg&n; *&t;&t;&t;The Basic portion of this register indicates the last&n; *&t;&t;&t;value of the register read indicated in the POLL REG field&n; *&t;&t;&t;of the Configuration Register.&n; *&t;&t;&t;The Status portion indicates bit(s) that have changed.&n; *&t;&t;&t;The MIF Mask register is corresponding to this register in&n; *&t;&t;&t;terms of the bit(s) that need to be masked for generating&n; *&t;&t;&t;interrupt on the MIF Interrupt Bit of the Global Status Rgister.&n; */
DECL|macro|GMAC_MIF_STATUS
mdefine_line|#define&t;GMAC_MIF_STATUS&t;&t;&t;0x0000ffff&t;/* 0-15 : Status */
DECL|macro|GMAC_MIF_BASIC
mdefine_line|#define&t;GMAC_MIF_BASIC&t;&t;&t;0xffff0000&t;/* 16-31 : Basic register */
eof
