multiline_comment|/* sunbmac.h: Defines for the Sun &quot;Big MAC&quot; 100baseT ethernet cards.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SUNBMAC_H
DECL|macro|_SUNBMAC_H
mdefine_line|#define _SUNBMAC_H
multiline_comment|/* QEC global registers. */
DECL|struct|qe_globreg
r_struct
id|qe_globreg
(brace
DECL|member|ctrl
r_volatile
r_int
r_int
id|ctrl
suffix:semicolon
multiline_comment|/* Control                  */
DECL|member|stat
r_volatile
r_int
r_int
id|stat
suffix:semicolon
multiline_comment|/* Status                   */
DECL|member|psize
r_volatile
r_int
r_int
id|psize
suffix:semicolon
multiline_comment|/* Packet Size              */
DECL|member|msize
r_volatile
r_int
r_int
id|msize
suffix:semicolon
multiline_comment|/* Local-mem size (64K)     */
DECL|member|rsize
r_volatile
r_int
r_int
id|rsize
suffix:semicolon
multiline_comment|/* Receive partition size   */
DECL|member|tsize
r_volatile
r_int
r_int
id|tsize
suffix:semicolon
multiline_comment|/* Transmit partition size  */
)brace
suffix:semicolon
DECL|macro|GLOB_CTRL_MMODE
mdefine_line|#define GLOB_CTRL_MMODE       0x40000000 /* MACE qec mode            */
DECL|macro|GLOB_CTRL_BMODE
mdefine_line|#define GLOB_CTRL_BMODE       0x10000000 /* BigMAC qec mode          */
DECL|macro|GLOB_CTRL_EPAR
mdefine_line|#define GLOB_CTRL_EPAR        0x00000020 /* Enable parity            */
DECL|macro|GLOB_CTRL_ACNTRL
mdefine_line|#define GLOB_CTRL_ACNTRL      0x00000018 /* SBUS arbitration control */
DECL|macro|GLOB_CTRL_B64
mdefine_line|#define GLOB_CTRL_B64         0x00000004 /* 64 byte dvma bursts      */
DECL|macro|GLOB_CTRL_B32
mdefine_line|#define GLOB_CTRL_B32         0x00000002 /* 32 byte dvma bursts      */
DECL|macro|GLOB_CTRL_B16
mdefine_line|#define GLOB_CTRL_B16         0x00000000 /* 16 byte dvma bursts      */
DECL|macro|GLOB_CTRL_RESET
mdefine_line|#define GLOB_CTRL_RESET       0x00000001 /* Reset the QEC            */
DECL|macro|GLOB_STAT_TX
mdefine_line|#define GLOB_STAT_TX          0x00000008 /* BigMAC Transmit IRQ      */
DECL|macro|GLOB_STAT_RX
mdefine_line|#define GLOB_STAT_RX          0x00000004 /* BigMAC Receive IRQ       */
DECL|macro|GLOB_STAT_BM
mdefine_line|#define GLOB_STAT_BM          0x00000002 /* BigMAC Global IRQ        */
DECL|macro|GLOB_STAT_ER
mdefine_line|#define GLOB_STAT_ER          0x00000001 /* BigMAC Error IRQ         */
DECL|macro|GLOB_PSIZE_2048
mdefine_line|#define GLOB_PSIZE_2048       0x00       /* 2k packet size           */
DECL|macro|GLOB_PSIZE_4096
mdefine_line|#define GLOB_PSIZE_4096       0x01       /* 4k packet size           */
DECL|macro|GLOB_PSIZE_6144
mdefine_line|#define GLOB_PSIZE_6144       0x10       /* 6k packet size           */
DECL|macro|GLOB_PSIZE_8192
mdefine_line|#define GLOB_PSIZE_8192       0x11       /* 8k packet size           */
multiline_comment|/* QEC BigMAC channel registers. */
DECL|struct|qe_creg
r_struct
id|qe_creg
(brace
DECL|member|ctrl
r_volatile
r_int
r_int
id|ctrl
suffix:semicolon
multiline_comment|/* Control                     */
DECL|member|stat
r_volatile
r_int
r_int
id|stat
suffix:semicolon
multiline_comment|/* Status                      */
DECL|member|rxds
r_volatile
r_int
r_int
id|rxds
suffix:semicolon
multiline_comment|/* RX descriptor ring ptr      */
DECL|member|txds
r_volatile
r_int
r_int
id|txds
suffix:semicolon
multiline_comment|/* TX descriptor ring ptr      */
DECL|member|rimask
r_volatile
r_int
r_int
id|rimask
suffix:semicolon
multiline_comment|/* RX Interrupt Mask           */
DECL|member|timask
r_volatile
r_int
r_int
id|timask
suffix:semicolon
multiline_comment|/* TX Interrupt Mask           */
DECL|member|qmask
r_volatile
r_int
r_int
id|qmask
suffix:semicolon
multiline_comment|/* QEC Error Interrupt Mask    */
DECL|member|bmask
r_volatile
r_int
r_int
id|bmask
suffix:semicolon
multiline_comment|/* BigMAC Error Interrupt Mask */
DECL|member|rxwbufptr
r_volatile
r_int
r_int
id|rxwbufptr
suffix:semicolon
multiline_comment|/* Local memory rx write ptr   */
DECL|member|rxrbufptr
r_volatile
r_int
r_int
id|rxrbufptr
suffix:semicolon
multiline_comment|/* Local memory rx read ptr    */
DECL|member|txwbufptr
r_volatile
r_int
r_int
id|txwbufptr
suffix:semicolon
multiline_comment|/* Local memory tx write ptr   */
DECL|member|txrbufptr
r_volatile
r_int
r_int
id|txrbufptr
suffix:semicolon
multiline_comment|/* Local memory tx read ptr    */
DECL|member|ccnt
r_volatile
r_int
r_int
id|ccnt
suffix:semicolon
multiline_comment|/* Collision Counter           */
)brace
suffix:semicolon
DECL|macro|CREG_CTRL_TWAKEUP
mdefine_line|#define CREG_CTRL_TWAKEUP     0x00000001  /* Transmitter Wakeup, &squot;go&squot;. */
DECL|macro|CREG_STAT_BERROR
mdefine_line|#define CREG_STAT_BERROR      0x80000000  /* BigMAC error              */
DECL|macro|CREG_STAT_TXIRQ
mdefine_line|#define CREG_STAT_TXIRQ       0x00200000  /* Transmit Interrupt        */
DECL|macro|CREG_STAT_TXDERROR
mdefine_line|#define CREG_STAT_TXDERROR    0x00080000  /* TX Descriptor is bogus    */
DECL|macro|CREG_STAT_TXLERR
mdefine_line|#define CREG_STAT_TXLERR      0x00040000  /* Late Transmit Error       */
DECL|macro|CREG_STAT_TXPERR
mdefine_line|#define CREG_STAT_TXPERR      0x00020000  /* Transmit Parity Error     */
DECL|macro|CREG_STAT_TXSERR
mdefine_line|#define CREG_STAT_TXSERR      0x00010000  /* Transmit SBUS error ack   */
DECL|macro|CREG_STAT_RXIRQ
mdefine_line|#define CREG_STAT_RXIRQ       0x00000020  /* Receive Interrupt         */
DECL|macro|CREG_STAT_RXDROP
mdefine_line|#define CREG_STAT_RXDROP      0x00000010  /* Dropped a RX&squot;d packet     */
DECL|macro|CREG_STAT_RXSMALL
mdefine_line|#define CREG_STAT_RXSMALL     0x00000008  /* Receive buffer too small  */
DECL|macro|CREG_STAT_RXLERR
mdefine_line|#define CREG_STAT_RXLERR      0x00000004  /* Receive Late Error        */
DECL|macro|CREG_STAT_RXPERR
mdefine_line|#define CREG_STAT_RXPERR      0x00000002  /* Receive Parity Error      */
DECL|macro|CREG_STAT_RXSERR
mdefine_line|#define CREG_STAT_RXSERR      0x00000001  /* Receive SBUS Error ACK    */
DECL|macro|CREG_STAT_ERRORS
mdefine_line|#define CREG_STAT_ERRORS      (CREG_STAT_BERROR|CREG_STAT_TXDERROR|CREG_STAT_TXLERR|   &bslash;&n;                               CREG_STAT_TXPERR|CREG_STAT_TXSERR|CREG_STAT_RXDROP|     &bslash;&n;                               CREG_STAT_RXSMALL|CREG_STAT_RXLERR|CREG_STAT_RXPERR|    &bslash;&n;                               CREG_STAT_RXSERR)
DECL|macro|CREG_QMASK_TXDERROR
mdefine_line|#define CREG_QMASK_TXDERROR   0x00080000  /* TXD error                 */
DECL|macro|CREG_QMASK_TXLERR
mdefine_line|#define CREG_QMASK_TXLERR     0x00040000  /* TX late error             */
DECL|macro|CREG_QMASK_TXPERR
mdefine_line|#define CREG_QMASK_TXPERR     0x00020000  /* TX parity error           */
DECL|macro|CREG_QMASK_TXSERR
mdefine_line|#define CREG_QMASK_TXSERR     0x00010000  /* TX sbus error ack         */
DECL|macro|CREG_QMASK_RXDROP
mdefine_line|#define CREG_QMASK_RXDROP     0x00000010  /* RX drop                   */
DECL|macro|CREG_QMASK_RXBERROR
mdefine_line|#define CREG_QMASK_RXBERROR   0x00000008  /* RX buffer error           */
DECL|macro|CREG_QMASK_RXLEERR
mdefine_line|#define CREG_QMASK_RXLEERR    0x00000004  /* RX late error             */
DECL|macro|CREG_QMASK_RXPERR
mdefine_line|#define CREG_QMASK_RXPERR     0x00000002  /* RX parity error           */
DECL|macro|CREG_QMASK_RXSERR
mdefine_line|#define CREG_QMASK_RXSERR     0x00000001  /* RX sbus error ack         */
DECL|struct|BIG_MAC_regs
r_struct
id|BIG_MAC_regs
(brace
DECL|member|xif_cfg
r_volatile
r_int
r_int
id|xif_cfg
suffix:semicolon
multiline_comment|/* XIF config register                */
DECL|member|_unused
r_volatile
r_int
r_int
id|_unused
(braket
l_int|63
)braket
suffix:semicolon
multiline_comment|/* Reserved...                        */
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* Status register, clear on read     */
DECL|member|imask
r_volatile
r_int
r_int
id|imask
suffix:semicolon
multiline_comment|/* Interrupt mask register            */
DECL|member|_unused2
r_volatile
r_int
r_int
id|_unused2
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Reserved...                        */
DECL|member|tx_swreset
r_volatile
r_int
r_int
id|tx_swreset
suffix:semicolon
multiline_comment|/* Transmitter software reset         */
DECL|member|tx_cfg
r_volatile
r_int
r_int
id|tx_cfg
suffix:semicolon
multiline_comment|/* Transmitter config register        */
DECL|member|ipkt_gap1
r_volatile
r_int
r_int
id|ipkt_gap1
suffix:semicolon
multiline_comment|/* Inter-packet gap 1                 */
DECL|member|ipkt_gap2
r_volatile
r_int
r_int
id|ipkt_gap2
suffix:semicolon
multiline_comment|/* Inter-packet gap 2                 */
DECL|member|attempt_limit
r_volatile
r_int
r_int
id|attempt_limit
suffix:semicolon
multiline_comment|/* Transmit attempt limit             */
DECL|member|stime
r_volatile
r_int
r_int
id|stime
suffix:semicolon
multiline_comment|/* Transmit slot time                 */
DECL|member|preamble_len
r_volatile
r_int
r_int
id|preamble_len
suffix:semicolon
multiline_comment|/* Size of transmit preamble          */
DECL|member|preamble_pattern
r_volatile
r_int
r_int
id|preamble_pattern
suffix:semicolon
multiline_comment|/* Pattern for transmit preamble      */
DECL|member|tx_sframe_delim
r_volatile
r_int
r_int
id|tx_sframe_delim
suffix:semicolon
multiline_comment|/* Transmit delimiter                 */
DECL|member|jsize
r_volatile
r_int
r_int
id|jsize
suffix:semicolon
multiline_comment|/* Toe jam...                         */
DECL|member|tx_pkt_max
r_volatile
r_int
r_int
id|tx_pkt_max
suffix:semicolon
multiline_comment|/* Transmit max pkt size              */
DECL|member|tx_pkt_min
r_volatile
r_int
r_int
id|tx_pkt_min
suffix:semicolon
multiline_comment|/* Transmit min pkt size              */
DECL|member|peak_attempt
r_volatile
r_int
r_int
id|peak_attempt
suffix:semicolon
multiline_comment|/* Count of transmit peak attempts    */
DECL|member|dt_ctr
r_volatile
r_int
r_int
id|dt_ctr
suffix:semicolon
multiline_comment|/* Transmit defer timer               */
DECL|member|nc_ctr
r_volatile
r_int
r_int
id|nc_ctr
suffix:semicolon
multiline_comment|/* Transmit normal-collision counter  */
DECL|member|fc_ctr
r_volatile
r_int
r_int
id|fc_ctr
suffix:semicolon
multiline_comment|/* Transmit first-collision counter   */
DECL|member|ex_ctr
r_volatile
r_int
r_int
id|ex_ctr
suffix:semicolon
multiline_comment|/* Transmit excess-collision counter  */
DECL|member|lt_ctr
r_volatile
r_int
r_int
id|lt_ctr
suffix:semicolon
multiline_comment|/* Transmit late-collision counter    */
DECL|member|rand_seed
r_volatile
r_int
r_int
id|rand_seed
suffix:semicolon
multiline_comment|/* Transmit random number seed        */
DECL|member|tx_smachine
r_volatile
r_int
r_int
id|tx_smachine
suffix:semicolon
multiline_comment|/* Transmit state machine             */
DECL|member|_unused3
r_volatile
r_int
r_int
id|_unused3
(braket
l_int|44
)braket
suffix:semicolon
multiline_comment|/* Reserved                           */
DECL|member|rx_swreset
r_volatile
r_int
r_int
id|rx_swreset
suffix:semicolon
multiline_comment|/* Receiver software reset            */
DECL|member|rx_cfg
r_volatile
r_int
r_int
id|rx_cfg
suffix:semicolon
multiline_comment|/* Receiver config register           */
DECL|member|rx_pkt_max
r_volatile
r_int
r_int
id|rx_pkt_max
suffix:semicolon
multiline_comment|/* Receive max pkt size               */
DECL|member|rx_pkt_min
r_volatile
r_int
r_int
id|rx_pkt_min
suffix:semicolon
multiline_comment|/* Receive min pkt size               */
DECL|member|mac_addr2
r_volatile
r_int
r_int
id|mac_addr2
suffix:semicolon
multiline_comment|/* Ether address register 2           */
DECL|member|mac_addr1
r_volatile
r_int
r_int
id|mac_addr1
suffix:semicolon
multiline_comment|/* Ether address register 1           */
DECL|member|mac_addr0
r_volatile
r_int
r_int
id|mac_addr0
suffix:semicolon
multiline_comment|/* Ether address register 0           */
DECL|member|fr_ctr
r_volatile
r_int
r_int
id|fr_ctr
suffix:semicolon
multiline_comment|/* Receive frame receive counter      */
DECL|member|gle_ctr
r_volatile
r_int
r_int
id|gle_ctr
suffix:semicolon
multiline_comment|/* Receive giant-length error counter */
DECL|member|unale_ctr
r_volatile
r_int
r_int
id|unale_ctr
suffix:semicolon
multiline_comment|/* Receive unaligned error counter    */
DECL|member|rcrce_ctr
r_volatile
r_int
r_int
id|rcrce_ctr
suffix:semicolon
multiline_comment|/* Receive CRC error counter          */
DECL|member|rx_smachine
r_volatile
r_int
r_int
id|rx_smachine
suffix:semicolon
multiline_comment|/* Receiver state machine             */
DECL|member|rx_cvalid
r_volatile
r_int
r_int
id|rx_cvalid
suffix:semicolon
multiline_comment|/* Receiver code violation            */
DECL|member|_unused4
r_volatile
r_int
r_int
id|_unused4
suffix:semicolon
multiline_comment|/* Reserved...                        */
DECL|member|htable3
r_volatile
r_int
r_int
id|htable3
suffix:semicolon
multiline_comment|/* Hash table 3                       */
DECL|member|htable2
r_volatile
r_int
r_int
id|htable2
suffix:semicolon
multiline_comment|/* Hash table 2                       */
DECL|member|htable1
r_volatile
r_int
r_int
id|htable1
suffix:semicolon
multiline_comment|/* Hash table 1                       */
DECL|member|htable0
r_volatile
r_int
r_int
id|htable0
suffix:semicolon
multiline_comment|/* Hash table 0                       */
DECL|member|afilter2
r_volatile
r_int
r_int
id|afilter2
suffix:semicolon
multiline_comment|/* Address filter 2                   */
DECL|member|afilter1
r_volatile
r_int
r_int
id|afilter1
suffix:semicolon
multiline_comment|/* Address filter 1                   */
DECL|member|afilter0
r_volatile
r_int
r_int
id|afilter0
suffix:semicolon
multiline_comment|/* Address filter 0                   */
DECL|member|afilter_mask
r_volatile
r_int
r_int
id|afilter_mask
suffix:semicolon
multiline_comment|/* Address filter mask                */
)brace
suffix:semicolon
multiline_comment|/* BigMac XIF config register. */
DECL|macro|BIGMAC_XCFG_ODENABLE
mdefine_line|#define BIGMAC_XCFG_ODENABLE   0x00000001 /* Output driver enable                     */
DECL|macro|BIGMAC_XCFG_RESV
mdefine_line|#define BIGMAC_XCFG_RESV       0x00000002 /* Reserved, write always as 1              */
DECL|macro|BIGMAC_XCFG_MLBACK
mdefine_line|#define BIGMAC_XCFG_MLBACK     0x00000004 /* Loopback-mode MII enable                 */
DECL|macro|BIGMAC_XCFG_SMODE
mdefine_line|#define BIGMAC_XCFG_SMODE      0x00000008 /* Enable serial mode                       */
multiline_comment|/* BigMAC status register. */
DECL|macro|BIGMAC_STAT_GOTFRAME
mdefine_line|#define BIGMAC_STAT_GOTFRAME   0x00000001 /* Received a frame                         */
DECL|macro|BIGMAC_STAT_RCNTEXP
mdefine_line|#define BIGMAC_STAT_RCNTEXP    0x00000002 /* Receive frame counter expired            */
DECL|macro|BIGMAC_STAT_ACNTEXP
mdefine_line|#define BIGMAC_STAT_ACNTEXP    0x00000004 /* Align-error counter expired              */
DECL|macro|BIGMAC_STAT_CCNTEXP
mdefine_line|#define BIGMAC_STAT_CCNTEXP    0x00000008 /* CRC-error counter expired                */
DECL|macro|BIGMAC_STAT_LCNTEXP
mdefine_line|#define BIGMAC_STAT_LCNTEXP    0x00000010 /* Length-error counter expired             */
DECL|macro|BIGMAC_STAT_RFIFOVF
mdefine_line|#define BIGMAC_STAT_RFIFOVF    0x00000020 /* Receive FIFO overflow                    */
DECL|macro|BIGMAC_STAT_CVCNTEXP
mdefine_line|#define BIGMAC_STAT_CVCNTEXP   0x00000040 /* Code-violation counter expired           */
DECL|macro|BIGMAC_STAT_SENTFRAME
mdefine_line|#define BIGMAC_STAT_SENTFRAME  0x00000100 /* Transmitted a frame                      */
DECL|macro|BIGMAC_STAT_TFIFO_UND
mdefine_line|#define BIGMAC_STAT_TFIFO_UND  0x00000200 /* Transmit FIFO underrun                   */
DECL|macro|BIGMAC_STAT_MAXPKTERR
mdefine_line|#define BIGMAC_STAT_MAXPKTERR  0x00000400 /* Max-packet size error                    */
DECL|macro|BIGMAC_STAT_NCNTEXP
mdefine_line|#define BIGMAC_STAT_NCNTEXP    0x00000800 /* Normal-collision counter expired         */
DECL|macro|BIGMAC_STAT_ECNTEXP
mdefine_line|#define BIGMAC_STAT_ECNTEXP    0x00001000 /* Excess-collision counter expired         */
DECL|macro|BIGMAC_STAT_LCCNTEXP
mdefine_line|#define BIGMAC_STAT_LCCNTEXP   0x00002000 /* Late-collision counter expired           */
DECL|macro|BIGMAC_STAT_FCNTEXP
mdefine_line|#define BIGMAC_STAT_FCNTEXP    0x00004000 /* First-collision counter expired          */
DECL|macro|BIGMAC_STAT_DTIMEXP
mdefine_line|#define BIGMAC_STAT_DTIMEXP    0x00008000 /* Defer-timer expired                      */
multiline_comment|/* BigMAC interrupt mask register. */
DECL|macro|BIGMAC_IMASK_GOTFRAME
mdefine_line|#define BIGMAC_IMASK_GOTFRAME  0x00000001 /* Received a frame                         */
DECL|macro|BIGMAC_IMASK_RCNTEXP
mdefine_line|#define BIGMAC_IMASK_RCNTEXP   0x00000002 /* Receive frame counter expired            */
DECL|macro|BIGMAC_IMASK_ACNTEXP
mdefine_line|#define BIGMAC_IMASK_ACNTEXP   0x00000004 /* Align-error counter expired              */
DECL|macro|BIGMAC_IMASK_CCNTEXP
mdefine_line|#define BIGMAC_IMASK_CCNTEXP   0x00000008 /* CRC-error counter expired                */
DECL|macro|BIGMAC_IMASK_LCNTEXP
mdefine_line|#define BIGMAC_IMASK_LCNTEXP   0x00000010 /* Length-error counter expired             */
DECL|macro|BIGMAC_IMASK_RFIFOVF
mdefine_line|#define BIGMAC_IMASK_RFIFOVF   0x00000020 /* Receive FIFO overflow                    */
DECL|macro|BIGMAC_IMASK_CVCNTEXP
mdefine_line|#define BIGMAC_IMASK_CVCNTEXP  0x00000040 /* Code-violation counter expired           */
DECL|macro|BIGMAC_IMASK_SENTFRAME
mdefine_line|#define BIGMAC_IMASK_SENTFRAME 0x00000100 /* Transmitted a frame                      */
DECL|macro|BIGMAC_IMASK_TFIFO_UND
mdefine_line|#define BIGMAC_IMASK_TFIFO_UND 0x00000200 /* Transmit FIFO underrun                   */
DECL|macro|BIGMAC_IMASK_MAXPKTERR
mdefine_line|#define BIGMAC_IMASK_MAXPKTERR 0x00000400 /* Max-packet size error                    */
DECL|macro|BIGMAC_IMASK_NCNTEXP
mdefine_line|#define BIGMAC_IMASK_NCNTEXP   0x00000800 /* Normal-collision counter expired         */
DECL|macro|BIGMAC_IMASK_ECNTEXP
mdefine_line|#define BIGMAC_IMASK_ECNTEXP   0x00001000 /* Excess-collision counter expired         */
DECL|macro|BIGMAC_IMASK_LCCNTEXP
mdefine_line|#define BIGMAC_IMASK_LCCNTEXP  0x00002000 /* Late-collision counter expired           */
DECL|macro|BIGMAC_IMASK_FCNTEXP
mdefine_line|#define BIGMAC_IMASK_FCNTEXP   0x00004000 /* First-collision counter expired          */
DECL|macro|BIGMAC_IMASK_DTIMEXP
mdefine_line|#define BIGMAC_IMASK_DTIMEXP   0x00008000 /* Defer-timer expired                      */
multiline_comment|/* BigMac transmit config register. */
DECL|macro|BIGMAC_TXCFG_ENABLE
mdefine_line|#define BIGMAC_TXCFG_ENABLE    0x00000001 /* Enable the transmitter                   */
DECL|macro|BIGMAC_TXCFG_FIFO
mdefine_line|#define BIGMAC_TXCFG_FIFO      0x00000010 /* Default tx fthresh...                    */
DECL|macro|BIGMAC_TXCFG_SMODE
mdefine_line|#define BIGMAC_TXCFG_SMODE     0x00000020 /* Enable slow transmit mode                */
DECL|macro|BIGMAC_TXCFG_CIGN
mdefine_line|#define BIGMAC_TXCFG_CIGN      0x00000040 /* Ignore transmit collisions               */
DECL|macro|BIGMAC_TXCFG_FCSOFF
mdefine_line|#define BIGMAC_TXCFG_FCSOFF    0x00000080 /* Do not emit FCS                          */
DECL|macro|BIGMAC_TXCFG_DBACKOFF
mdefine_line|#define BIGMAC_TXCFG_DBACKOFF  0x00000100 /* Disable backoff                          */
DECL|macro|BIGMAC_TXCFG_FULLDPLX
mdefine_line|#define BIGMAC_TXCFG_FULLDPLX  0x00000200 /* Enable full-duplex                       */
multiline_comment|/* BigMac receive config register. */
DECL|macro|BIGMAC_RXCFG_ENABLE
mdefine_line|#define BIGMAC_RXCFG_ENABLE    0x00000001 /* Enable the receiver                      */
DECL|macro|BIGMAC_RXCFG_FIFO
mdefine_line|#define BIGMAC_RXCFG_FIFO      0x0000000e /* Default rx fthresh...                    */
DECL|macro|BIGMAC_RXCFG_PSTRIP
mdefine_line|#define BIGMAC_RXCFG_PSTRIP    0x00000020 /* Pad byte strip enable                    */
DECL|macro|BIGMAC_RXCFG_PMISC
mdefine_line|#define BIGMAC_RXCFG_PMISC     0x00000040 /* Enable promiscous mode                   */
DECL|macro|BIGMAC_RXCFG_DERR
mdefine_line|#define BIGMAC_RXCFG_DERR      0x00000080 /* Disable error checking                   */
DECL|macro|BIGMAC_RXCFG_DCRCS
mdefine_line|#define BIGMAC_RXCFG_DCRCS     0x00000100 /* Disable CRC stripping                    */
DECL|macro|BIGMAC_RXCFG_ME
mdefine_line|#define BIGMAC_RXCFG_ME        0x00000200 /* Receive packets addressed to me          */
DECL|macro|BIGMAC_RXCFG_PGRP
mdefine_line|#define BIGMAC_RXCFG_PGRP      0x00000400 /* Enable promisc group mode                */
DECL|macro|BIGMAC_RXCFG_HENABLE
mdefine_line|#define BIGMAC_RXCFG_HENABLE   0x00000800 /* Enable the hash filter                   */
DECL|macro|BIGMAC_RXCFG_AENABLE
mdefine_line|#define BIGMAC_RXCFG_AENABLE   0x00001000 /* Enable the address filter                */
multiline_comment|/* The BigMAC PHY transceiver.  Not nearly as sophisticated as the happy meal&n; * one.  But it does have the &quot;bit banger&quot;, oh baby.&n; */
DECL|struct|bmac_tcvr
r_struct
id|bmac_tcvr
(brace
DECL|member|tcvr_pal
r_int
r_int
id|tcvr_pal
suffix:semicolon
DECL|member|mgmt_pal
r_int
r_int
id|mgmt_pal
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Frame commands. */
DECL|macro|FRAME_WRITE
mdefine_line|#define FRAME_WRITE           0x50020000
DECL|macro|FRAME_READ
mdefine_line|#define FRAME_READ            0x60020000
multiline_comment|/* Tranceiver registers. */
DECL|macro|TCVR_PAL_SERIAL
mdefine_line|#define TCVR_PAL_SERIAL       0x00000001 /* Enable serial mode              */
DECL|macro|TCVR_PAL_EXTLBACK
mdefine_line|#define TCVR_PAL_EXTLBACK     0x00000002 /* Enable external loopback        */
DECL|macro|TCVR_PAL_MSENSE
mdefine_line|#define TCVR_PAL_MSENSE       0x00000004 /* Media sense                     */
DECL|macro|TCVR_PAL_LTENABLE
mdefine_line|#define TCVR_PAL_LTENABLE     0x00000008 /* Link test enable                */
DECL|macro|TCVR_PAL_LTSTATUS
mdefine_line|#define TCVR_PAL_LTSTATUS     0x00000010 /* Link test status  (P1 only)     */
multiline_comment|/* Management PAL. */
DECL|macro|MGMT_PAL_DCLOCK
mdefine_line|#define MGMT_PAL_DCLOCK       0x00000001 /* Data clock                      */
DECL|macro|MGMT_PAL_OENAB
mdefine_line|#define MGMT_PAL_OENAB        0x00000002 /* Output enabler                  */
DECL|macro|MGMT_PAL_MDIO
mdefine_line|#define MGMT_PAL_MDIO         0x00000004 /* MDIO Data/attached              */
DECL|macro|MGMT_PAL_TIMEO
mdefine_line|#define MGMT_PAL_TIMEO        0x00000008 /* Transmit enable timeout error   */
DECL|macro|MGMT_PAL_EXT_MDIO
mdefine_line|#define MGMT_PAL_EXT_MDIO     MGMT_PAL_MDIO
DECL|macro|MGMT_PAL_INT_MDIO
mdefine_line|#define MGMT_PAL_INT_MDIO     MGMT_PAL_TIMEO
multiline_comment|/* Here are some PHY addresses. */
DECL|macro|BIGMAC_PHY_EXTERNAL
mdefine_line|#define BIGMAC_PHY_EXTERNAL   0 /* External transceiver */
DECL|macro|BIGMAC_PHY_INTERNAL
mdefine_line|#define BIGMAC_PHY_INTERNAL   1 /* Internal transceiver */
multiline_comment|/* PHY registers */
DECL|macro|BIGMAC_BMCR
mdefine_line|#define BIGMAC_BMCR           0x00 /* Basic mode control register&t;*/
DECL|macro|BIGMAC_BMSR
mdefine_line|#define BIGMAC_BMSR           0x01 /* Basic mode status register&t;*/
multiline_comment|/* BMCR bits */
DECL|macro|BMCR_ISOLATE
mdefine_line|#define BMCR_ISOLATE            0x0400  /* Disconnect DP83840 from MII */
DECL|macro|BMCR_PDOWN
mdefine_line|#define BMCR_PDOWN              0x0800  /* Powerdown the DP83840       */
DECL|macro|BMCR_ANENABLE
mdefine_line|#define BMCR_ANENABLE           0x1000  /* Enable auto negotiation     */
DECL|macro|BMCR_SPEED100
mdefine_line|#define BMCR_SPEED100           0x2000  /* Select 100Mbps              */
DECL|macro|BMCR_LOOPBACK
mdefine_line|#define BMCR_LOOPBACK           0x4000  /* TXD loopback bits           */
DECL|macro|BMCR_RESET
mdefine_line|#define BMCR_RESET              0x8000  /* Reset the DP83840           */
multiline_comment|/* BMSR bits */
DECL|macro|BMSR_ERCAP
mdefine_line|#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
DECL|macro|BMSR_JCD
mdefine_line|#define BMSR_JCD                0x0002  /* Jabber detected             */
DECL|macro|BMSR_LSTATUS
mdefine_line|#define BMSR_LSTATUS            0x0004  /* Link status                 */
multiline_comment|/* Ring descriptors and such, same as Quad Ethernet. */
DECL|struct|be_rxd
r_struct
id|be_rxd
(brace
DECL|member|rx_flags
r_int
r_int
id|rx_flags
suffix:semicolon
DECL|member|rx_addr
r_int
r_int
id|rx_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RXD_OWN
mdefine_line|#define RXD_OWN      0x80000000 /* Ownership.      */
DECL|macro|RXD_UPDATE
mdefine_line|#define RXD_UPDATE   0x10000000 /* Being Updated?  */
DECL|macro|RXD_LENGTH
mdefine_line|#define RXD_LENGTH   0x000007ff /* Packet Length.  */
DECL|struct|be_txd
r_struct
id|be_txd
(brace
DECL|member|tx_flags
r_int
r_int
id|tx_flags
suffix:semicolon
DECL|member|tx_addr
r_int
r_int
id|tx_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TXD_OWN
mdefine_line|#define TXD_OWN      0x80000000 /* Ownership.      */
DECL|macro|TXD_SOP
mdefine_line|#define TXD_SOP      0x40000000 /* Start Of Packet */
DECL|macro|TXD_EOP
mdefine_line|#define TXD_EOP      0x20000000 /* End Of Packet   */
DECL|macro|TXD_UPDATE
mdefine_line|#define TXD_UPDATE   0x10000000 /* Being Updated?  */
DECL|macro|TXD_LENGTH
mdefine_line|#define TXD_LENGTH   0x000007ff /* Packet Length.  */
DECL|macro|TX_RING_MAXSIZE
mdefine_line|#define TX_RING_MAXSIZE   256
DECL|macro|RX_RING_MAXSIZE
mdefine_line|#define RX_RING_MAXSIZE   256
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE      256
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE      256
DECL|macro|NEXT_RX
mdefine_line|#define NEXT_RX(num)       (((num) + 1) &amp; (RX_RING_SIZE - 1))
DECL|macro|NEXT_TX
mdefine_line|#define NEXT_TX(num)       (((num) + 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|PREV_RX
mdefine_line|#define PREV_RX(num)       (((num) - 1) &amp; (RX_RING_SIZE - 1))
DECL|macro|PREV_TX
mdefine_line|#define PREV_TX(num)       (((num) - 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL(bp)                                    &bslash;&n;        (((bp)-&gt;tx_old &lt;= (bp)-&gt;tx_new) ?                     &bslash;&n;&t;  (bp)-&gt;tx_old + (TX_RING_SIZE - 1) - (bp)-&gt;tx_new :  &bslash;&n;&t;&t;&t;    (bp)-&gt;tx_old - (bp)-&gt;tx_new - 1)
DECL|macro|SUN4C_TX_BUFFS_AVAIL
mdefine_line|#define SUN4C_TX_BUFFS_AVAIL(bp)                                    &bslash;&n;        (((bp)-&gt;tx_old &lt;= (bp)-&gt;tx_new) ?                           &bslash;&n;&t;  (bp)-&gt;tx_old + (SUN4C_TX_RING_SIZE - 1) - (bp)-&gt;tx_new :  &bslash;&n;&t;  (bp)-&gt;tx_old - (bp)-&gt;tx_new - (TX_RING_SIZE - SUN4C_TX_RING_SIZE))
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  128
DECL|macro|RX_BUF_ALLOC_SIZE
mdefine_line|#define RX_BUF_ALLOC_SIZE  (ETH_FRAME_LEN + (64 * 3))
DECL|struct|bmac_init_block
r_struct
id|bmac_init_block
(brace
DECL|member|be_rxd
r_struct
id|be_rxd
id|be_rxd
(braket
id|RX_RING_MAXSIZE
)braket
suffix:semicolon
DECL|member|be_txd
r_struct
id|be_txd
id|be_txd
(braket
id|TX_RING_MAXSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bib_offset
mdefine_line|#define bib_offset(mem, elem) &bslash;&n;((__u32)((unsigned long)(&amp;(((struct bmac_init_block *)0)-&gt;mem[elem]))))
DECL|macro|SUN4C_PKT_BUF_SZ
mdefine_line|#define SUN4C_PKT_BUF_SZ&t;1546
DECL|macro|SUN4C_RX_BUFF_SIZE
mdefine_line|#define SUN4C_RX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|macro|SUN4C_TX_BUFF_SIZE
mdefine_line|#define SUN4C_TX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|macro|SUN4C_RX_RING_SIZE
mdefine_line|#define SUN4C_RX_RING_SIZE&t;16
DECL|macro|SUN4C_TX_RING_SIZE
mdefine_line|#define SUN4C_TX_RING_SIZE&t;16
DECL|struct|bigmac_buffers
r_struct
id|bigmac_buffers
(brace
DECL|member|tx_buf
r_char
id|tx_buf
(braket
id|SUN4C_TX_RING_SIZE
)braket
(braket
id|SUN4C_TX_BUFF_SIZE
)braket
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Align rx_buf for copy_and_sum(). */
DECL|member|rx_buf
r_char
id|rx_buf
(braket
id|SUN4C_RX_RING_SIZE
)braket
(braket
id|SUN4C_RX_BUFF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bbuf_offset
mdefine_line|#define bbuf_offset(mem, elem) &bslash;&n;((__u32)((unsigned long)(&amp;(((struct bigmac_buffers *)0)-&gt;mem[elem][0]))))
multiline_comment|/* Now software state stuff. */
DECL|enum|bigmac_transceiver
r_enum
id|bigmac_transceiver
(brace
DECL|enumerator|external
id|external
op_assign
l_int|0
comma
DECL|enumerator|internal
id|internal
op_assign
l_int|1
comma
DECL|enumerator|none
id|none
op_assign
l_int|2
comma
)brace
suffix:semicolon
multiline_comment|/* Timer state engine. */
DECL|enum|bigmac_timer_state
r_enum
id|bigmac_timer_state
(brace
DECL|enumerator|ltrywait
id|ltrywait
op_assign
l_int|1
comma
multiline_comment|/* Forcing try of all modes, from fastest to slowest. */
DECL|enumerator|asleep
id|asleep
op_assign
l_int|2
comma
multiline_comment|/* Timer inactive.                                    */
)brace
suffix:semicolon
DECL|struct|bigmac
r_struct
id|bigmac
(brace
DECL|member|gregs
r_struct
id|qe_globreg
op_star
id|gregs
suffix:semicolon
multiline_comment|/* QEC Global Registers               */
DECL|member|creg
r_struct
id|qe_creg
op_star
id|creg
suffix:semicolon
multiline_comment|/* QEC BigMAC Channel Registers       */
DECL|member|bregs
r_struct
id|BIG_MAC_regs
op_star
id|bregs
suffix:semicolon
multiline_comment|/* BigMAC Registers                   */
DECL|member|tregs
r_struct
id|bmac_tcvr
op_star
id|tregs
suffix:semicolon
multiline_comment|/* BigMAC Transceiver                 */
DECL|member|bmac_block
r_struct
id|bmac_init_block
op_star
id|bmac_block
suffix:semicolon
multiline_comment|/* RX and TX descriptors              */
DECL|member|bblock_dvma
id|__u32
id|bblock_dvma
suffix:semicolon
multiline_comment|/* RX and TX descriptors              */
DECL|member|rx_skbs
r_struct
id|sk_buff
op_star
id|rx_skbs
(braket
id|RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_skbs
r_struct
id|sk_buff
op_star
id|tx_skbs
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|rx_new
DECL|member|tx_new
DECL|member|rx_old
DECL|member|tx_old
r_int
id|rx_new
comma
id|tx_new
comma
id|rx_old
comma
id|tx_old
suffix:semicolon
DECL|member|sun4c_buffers
r_struct
id|bigmac_buffers
op_star
id|sun4c_buffers
suffix:semicolon
DECL|member|s4c_buf_dvma
id|__u32
id|s4c_buf_dvma
suffix:semicolon
DECL|member|board_rev
r_int
id|board_rev
suffix:semicolon
multiline_comment|/* BigMAC board revision.             */
DECL|member|tcvr_type
r_enum
id|bigmac_transceiver
id|tcvr_type
suffix:semicolon
DECL|member|bigmac_bursts
r_int
r_int
id|bigmac_bursts
suffix:semicolon
DECL|member|paddr
r_int
r_int
id|paddr
suffix:semicolon
DECL|member|sw_bmsr
r_int
r_int
id|sw_bmsr
suffix:semicolon
multiline_comment|/* SW copy of PHY BMSR               */
DECL|member|sw_bmcr
r_int
r_int
id|sw_bmcr
suffix:semicolon
multiline_comment|/* SW copy of PHY BMCR               */
DECL|member|bigmac_timer
r_struct
id|timer_list
id|bigmac_timer
suffix:semicolon
DECL|member|timer_state
r_enum
id|bigmac_timer_state
id|timer_state
suffix:semicolon
DECL|member|timer_ticks
r_int
r_int
id|timer_ticks
suffix:semicolon
DECL|member|enet_stats
r_struct
id|enet_statistics
id|enet_stats
suffix:semicolon
DECL|member|qec_sbus_dev
r_struct
id|linux_sbus_device
op_star
id|qec_sbus_dev
suffix:semicolon
DECL|member|bigmac_sbus_dev
r_struct
id|linux_sbus_device
op_star
id|bigmac_sbus_dev
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|next_module
r_struct
id|bigmac
op_star
id|next_module
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We use this to acquire receive skb&squot;s that we can DMA directly into. */
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64 - 1)) &amp; ~(64 - 1)) - (unsigned long)(addr))
DECL|function|big_mac_alloc_skb
r_static
r_inline
r_struct
id|sk_buff
op_star
id|big_mac_alloc_skb
c_func
(paren
r_int
r_int
id|length
comma
r_int
id|gfp_flags
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|length
op_plus
l_int|64
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|offset
op_assign
id|ALIGNED_RX_SKB_ADDR
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|offset
)paren
suffix:semicolon
)brace
)brace
r_return
id|skb
suffix:semicolon
)brace
macro_line|#endif /* !(_SUNBMAC_H) */
eof
