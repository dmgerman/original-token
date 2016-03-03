macro_line|#ifndef _SK_MCA_INCLUDE_
DECL|macro|_SK_MCA_INCLUDE_
mdefine_line|#define _SK_MCA_INCLUDE_
macro_line|#ifdef _SK_MCA_DRIVER_
multiline_comment|/* Adapter ID&squot;s */
DECL|macro|SKNET_MCA_ID
mdefine_line|#define SKNET_MCA_ID 0x6afd
DECL|macro|SKNET_JUNIOR_MCA_ID
mdefine_line|#define SKNET_JUNIOR_MCA_ID 0x6be9
multiline_comment|/* media enumeration - defined in a way that it fits onto the MC2+&squot;s&n;   POS registers... */
DECL|enumerator|Media_10Base2
DECL|enumerator|Media_10BaseT
r_typedef
r_enum
(brace
id|Media_10Base2
comma
id|Media_10BaseT
comma
DECL|enumerator|Media_10Base5
DECL|enumerator|Media_Unknown
DECL|enumerator|Media_Count
DECL|typedef|skmca_medium
id|Media_10Base5
comma
id|Media_Unknown
comma
id|Media_Count
)brace
id|skmca_medium
suffix:semicolon
multiline_comment|/* private structure */
r_typedef
r_struct
(brace
DECL|member|slot
r_int
r_int
id|slot
suffix:semicolon
multiline_comment|/* MCA-Slot-#                       */
DECL|member|macbase
r_int
r_int
id|macbase
suffix:semicolon
multiline_comment|/* base address of MAC address PROM */
DECL|member|ioregaddr
r_int
r_int
id|ioregaddr
suffix:semicolon
multiline_comment|/* address of I/O-register (Lo)     */
DECL|member|ctrladdr
r_int
r_int
id|ctrladdr
suffix:semicolon
multiline_comment|/* address of control/stat register */
DECL|member|cmdaddr
r_int
r_int
id|cmdaddr
suffix:semicolon
multiline_comment|/* address of I/O-command register  */
DECL|member|nextrx
r_int
id|nextrx
suffix:semicolon
multiline_comment|/* index of next RX descriptor to&n;                                      be read                          */
DECL|member|nexttxput
r_int
id|nexttxput
suffix:semicolon
multiline_comment|/* index of next free TX descriptor */
DECL|member|nexttxdone
r_int
id|nexttxdone
suffix:semicolon
multiline_comment|/* index of next TX descriptor to &n;                                      be finished                      */
DECL|member|txbusy
r_int
id|txbusy
suffix:semicolon
multiline_comment|/* # of busy TX descriptors         */
DECL|member|stat
r_struct
id|enet_statistics
id|stat
suffix:semicolon
multiline_comment|/* packet statistics            */
DECL|member|realirq
r_int
id|realirq
suffix:semicolon
multiline_comment|/* memorizes actual IRQ, even when &n;                                      currently not allocated          */
DECL|member|medium
id|skmca_medium
id|medium
suffix:semicolon
multiline_comment|/* physical cannector               */
DECL|typedef|skmca_priv
)brace
id|skmca_priv
suffix:semicolon
multiline_comment|/* card registers: control/status register bits */
DECL|macro|CTRL_ADR_DATA
mdefine_line|#define CTRL_ADR_DATA      0      /* Bit 0 = 0 -&gt;access data register  */
DECL|macro|CTRL_ADR_RAP
mdefine_line|#define CTRL_ADR_RAP       1      /* Bit 0 = 1 -&gt;access RAP register   */
DECL|macro|CTRL_RW_WRITE
mdefine_line|#define CTRL_RW_WRITE      0      /* Bit 1 = 0 -&gt;write register        */
DECL|macro|CTRL_RW_READ
mdefine_line|#define CTRL_RW_READ       2      /* Bit 1 = 1 -&gt;read register         */
DECL|macro|CTRL_RESET_ON
mdefine_line|#define CTRL_RESET_ON      0      /* Bit 3 = 0 -&gt;reset board           */
DECL|macro|CTRL_RESET_OFF
mdefine_line|#define CTRL_RESET_OFF     8      /* Bit 3 = 1 -&gt;no reset of board     */
DECL|macro|STAT_ADR_DATA
mdefine_line|#define STAT_ADR_DATA      0      /* Bit 0 of ctrl register read back  */
DECL|macro|STAT_ADR_RAP
mdefine_line|#define STAT_ADR_RAP       1
DECL|macro|STAT_RW_WRITE
mdefine_line|#define STAT_RW_WRITE      0      /* Bit 1 of ctrl register read back  */
DECL|macro|STAT_RW_READ
mdefine_line|#define STAT_RW_READ       2
DECL|macro|STAT_RESET_ON
mdefine_line|#define STAT_RESET_ON      0      /* Bit 3 of ctrl register read back  */
DECL|macro|STAT_RESET_OFF
mdefine_line|#define STAT_RESET_OFF     8
DECL|macro|STAT_IRQ_ACT
mdefine_line|#define STAT_IRQ_ACT       0      /* interrupt pending                 */
DECL|macro|STAT_IRQ_NOACT
mdefine_line|#define STAT_IRQ_NOACT     16     /* no interrupt pending              */
DECL|macro|STAT_IO_NOBUSY
mdefine_line|#define STAT_IO_NOBUSY     0      /* no transfer busy                  */
DECL|macro|STAT_IO_BUSY
mdefine_line|#define STAT_IO_BUSY       32     /* transfer busy                     */
multiline_comment|/* I/O command register bits */
DECL|macro|IOCMD_GO
mdefine_line|#define IOCMD_GO           128    /* Bit 7 = 1 -&gt; start register xfer  */
multiline_comment|/* LANCE registers */
DECL|macro|LANCE_CSR0
mdefine_line|#define LANCE_CSR0         0      /* Status/Control                    */
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR           0x8000 /* general error flag                */
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL          0x4000 /* transmitter timeout               */
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR          0x2000 /* collision error                   */
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS          0x1000 /* lost Rx block                     */
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR          0x0800 /* memory access error               */
DECL|macro|CSR0_RINT
mdefine_line|#define CSR0_RINT          0x0400 /* receiver interrupt                */
DECL|macro|CSR0_TINT
mdefine_line|#define CSR0_TINT          0x0200 /* transmitter interrupt             */
DECL|macro|CSR0_IDON
mdefine_line|#define CSR0_IDON          0x0100 /* initialization done               */
DECL|macro|CSR0_INTR
mdefine_line|#define CSR0_INTR          0x0080 /* general interrupt flag            */
DECL|macro|CSR0_INEA
mdefine_line|#define CSR0_INEA          0x0040 /* interrupt enable                  */
DECL|macro|CSR0_RXON
mdefine_line|#define CSR0_RXON          0x0020 /* receiver enabled                  */
DECL|macro|CSR0_TXON
mdefine_line|#define CSR0_TXON          0x0010 /* transmitter enabled               */
DECL|macro|CSR0_TDMD
mdefine_line|#define CSR0_TDMD          0x0008 /* force transmission now            */
DECL|macro|CSR0_STOP
mdefine_line|#define CSR0_STOP          0x0004 /* stop LANCE                        */
DECL|macro|CSR0_STRT
mdefine_line|#define CSR0_STRT          0x0002 /* start LANCE                       */
DECL|macro|CSR0_INIT
mdefine_line|#define CSR0_INIT          0x0001 /* read initialization block         */          
DECL|macro|LANCE_CSR1
mdefine_line|#define LANCE_CSR1         1      /* addr bit 0..15 of initialization  */
DECL|macro|LANCE_CSR2
mdefine_line|#define LANCE_CSR2         2      /*          16..23 block             */
DECL|macro|LANCE_CSR3
mdefine_line|#define LANCE_CSR3         3      /* Bus control                       */
DECL|macro|CSR3_BCON_HOLD
mdefine_line|#define CSR3_BCON_HOLD     0      /* Bit 0 = 0 -&gt; BM1,BM0,HOLD         */
DECL|macro|CSR3_BCON_BUSRQ
mdefine_line|#define CSR3_BCON_BUSRQ    1      /* Bit 0 = 1 -&gt; BUSAK0,BYTE,BUSRQ    */
DECL|macro|CSR3_ALE_HIGH
mdefine_line|#define CSR3_ALE_HIGH      0      /* Bit 1 = 0 -&gt; ALE asserted high    */
DECL|macro|CSR3_ALE_LOW
mdefine_line|#define CSR3_ALE_LOW       2      /* Bit 1 = 1 -&gt; ALE asserted low     */
DECL|macro|CSR3_BSWAP_OFF
mdefine_line|#define CSR3_BSWAP_OFF     0      /* Bit 2 = 0 -&gt; no byte swap         */
DECL|macro|CSR3_BSWAP_ON
mdefine_line|#define CSR3_BSWAP_ON      0      /* Bit 2 = 1 -&gt; byte swap            */
multiline_comment|/* LANCE structures */
r_typedef
r_struct
multiline_comment|/* LANCE initialization block        */
(brace
DECL|member|Mode
id|u16
id|Mode
suffix:semicolon
multiline_comment|/* mode flags                        */
DECL|member|PAdr
id|u8
id|PAdr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* MAC address                       */
DECL|member|LAdrF
id|u8
id|LAdrF
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Multicast filter                  */
DECL|member|RdrP
id|u32
id|RdrP
suffix:semicolon
multiline_comment|/* Receive descriptor                */
DECL|member|TdrP
id|u32
id|TdrP
suffix:semicolon
multiline_comment|/* Transmit descriptor               */
DECL|typedef|LANCE_InitBlock
)brace
id|LANCE_InitBlock
suffix:semicolon
multiline_comment|/* Mode flags init block */
DECL|macro|LANCE_INIT_PROM
mdefine_line|#define LANCE_INIT_PROM    0x8000 /* enable promiscous mode            */
DECL|macro|LANCE_INIT_INTL
mdefine_line|#define LANCE_INIT_INTL    0x0040 /* internal loopback                 */
DECL|macro|LANCE_INIT_DRTY
mdefine_line|#define LANCE_INIT_DRTY    0x0020 /* disable retry                     */
DECL|macro|LANCE_INIT_COLL
mdefine_line|#define LANCE_INIT_COLL    0x0010 /* force collision                   */
DECL|macro|LANCE_INIT_DTCR
mdefine_line|#define LANCE_INIT_DTCR    0x0008 /* disable transmit CRC              */
DECL|macro|LANCE_INIT_LOOP
mdefine_line|#define LANCE_INIT_LOOP    0x0004 /* loopback                          */
DECL|macro|LANCE_INIT_DTX
mdefine_line|#define LANCE_INIT_DTX     0x0002 /* disable transmitter               */
DECL|macro|LANCE_INIT_DRX
mdefine_line|#define LANCE_INIT_DRX     0x0001 /* disable receiver                  */
r_typedef
r_struct
multiline_comment|/* LANCE Tx descriptor               */
(brace
DECL|member|LowAddr
id|u16
id|LowAddr
suffix:semicolon
multiline_comment|/* bit 0..15 of address              */
DECL|member|Flags
id|u16
id|Flags
suffix:semicolon
multiline_comment|/* bit 16..23 of address + Flags     */
DECL|member|Len
id|u16
id|Len
suffix:semicolon
multiline_comment|/* 2s complement of packet length    */
DECL|member|Status
id|u16
id|Status
suffix:semicolon
multiline_comment|/* Result of transmission            */
DECL|typedef|LANCE_TxDescr
)brace
id|LANCE_TxDescr
suffix:semicolon
DECL|macro|TXDSCR_FLAGS_OWN
mdefine_line|#define TXDSCR_FLAGS_OWN   0x8000 /* LANCE owns descriptor             */
DECL|macro|TXDSCR_FLAGS_ERR
mdefine_line|#define TXDSCR_FLAGS_ERR   0x4000 /* summary error flag                */
DECL|macro|TXDSCR_FLAGS_MORE
mdefine_line|#define TXDSCR_FLAGS_MORE  0x1000 /* more than one retry needed?       */
DECL|macro|TXDSCR_FLAGS_ONE
mdefine_line|#define TXDSCR_FLAGS_ONE   0x0800 /* one retry?                        */
DECL|macro|TXDSCR_FLAGS_DEF
mdefine_line|#define TXDSCR_FLAGS_DEF   0x0400 /* transmission deferred?            */
DECL|macro|TXDSCR_FLAGS_STP
mdefine_line|#define TXDSCR_FLAGS_STP   0x0200 /* first packet in chain?            */
DECL|macro|TXDSCR_FLAGS_ENP
mdefine_line|#define TXDSCR_FLAGS_ENP   0x0100 /* last packet in chain?             */
DECL|macro|TXDSCR_STATUS_BUFF
mdefine_line|#define TXDSCR_STATUS_BUFF 0x8000 /* buffer error?                     */
DECL|macro|TXDSCR_STATUS_UFLO
mdefine_line|#define TXDSCR_STATUS_UFLO 0x4000 /* silo underflow during transmit?   */
DECL|macro|TXDSCR_STATUS_LCOL
mdefine_line|#define TXDSCR_STATUS_LCOL 0x1000 /* late collision?                   */
DECL|macro|TXDSCR_STATUS_LCAR
mdefine_line|#define TXDSCR_STATUS_LCAR 0x0800 /* loss of carrier?                  */
DECL|macro|TXDSCR_STATUS_RTRY
mdefine_line|#define TXDSCR_STATUS_RTRY 0x0400 /* retry error?                      */
r_typedef
r_struct
multiline_comment|/* LANCE Rx descriptor               */
(brace
DECL|member|LowAddr
id|u16
id|LowAddr
suffix:semicolon
multiline_comment|/* bit 0..15 of address              */
DECL|member|Flags
id|u16
id|Flags
suffix:semicolon
multiline_comment|/* bit 16..23 of address + Flags     */
DECL|member|MaxLen
id|u16
id|MaxLen
suffix:semicolon
multiline_comment|/* 2s complement of buffer length    */
DECL|member|Len
id|u16
id|Len
suffix:semicolon
multiline_comment|/* packet length                     */
DECL|typedef|LANCE_RxDescr
)brace
id|LANCE_RxDescr
suffix:semicolon
DECL|macro|RXDSCR_FLAGS_OWN
mdefine_line|#define RXDSCR_FLAGS_OWN   0x8000 /* LANCE owns descriptor             */
DECL|macro|RXDSCR_FLAGS_ERR
mdefine_line|#define RXDSCR_FLAGS_ERR   0x4000 /* summary error flag                */
DECL|macro|RXDSCR_FLAGS_FRAM
mdefine_line|#define RXDSCR_FLAGS_FRAM  0x2000 /* framing error flag                */
DECL|macro|RXDSCR_FLAGS_OFLO
mdefine_line|#define RXDSCR_FLAGS_OFLO  0x1000 /* FIFO overflow?                    */
DECL|macro|RXDSCR_FLAGS_CRC
mdefine_line|#define RXDSCR_FLAGS_CRC   0x0800 /* CRC error?                        */
DECL|macro|RXDSCR_FLAGS_BUFF
mdefine_line|#define RXDSCR_FLAGS_BUFF  0x0400 /* buffer error?                     */
DECL|macro|RXDSCR_FLAGS_STP
mdefine_line|#define RXDSCR_FLAGS_STP   0x0200 /* first packet in chain?            */
DECL|macro|RXDCSR_FLAGS_ENP
mdefine_line|#define RXDCSR_FLAGS_ENP   0x0100 /* last packet in chain?             */
multiline_comment|/* RAM layout */
DECL|macro|TXCOUNT
mdefine_line|#define TXCOUNT            4      /* length of TX descriptor queue     */
DECL|macro|LTXCOUNT
mdefine_line|#define LTXCOUNT           2      /* log2 of it                        */
DECL|macro|RXCOUNT
mdefine_line|#define RXCOUNT            4      /* length of RX descriptor queue     */
DECL|macro|LRXCOUNT
mdefine_line|#define LRXCOUNT           2      /* log2 of it                        */
DECL|macro|RAM_INITBASE
mdefine_line|#define RAM_INITBASE       0      /* LANCE init block                  */
DECL|macro|RAM_TXBASE
mdefine_line|#define RAM_TXBASE         24     /* Start of TX descriptor queue      */
DECL|macro|RAM_RXBASE
mdefine_line|#define RAM_RXBASE         &bslash;&n;(RAM_TXBASE + (TXCOUNT * 8))      /* Start of RX descriptor queue      */
DECL|macro|RAM_DATABASE
mdefine_line|#define RAM_DATABASE       &bslash;&n;(RAM_RXBASE + (RXCOUNT * 8))      /* Start of data area for frames     */
DECL|macro|RAM_BUFSIZE
mdefine_line|#define RAM_BUFSIZE        1580   /* max. frame size - should never be&n;                                     reached                           */
macro_line|#endif /* _SK_MCA_DRIVER_ */
r_extern
r_int
id|skmca_probe
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
macro_line|#endif /* _SK_MCA_INCLUDE_ */
eof
