multiline_comment|/* sunhme.h: Definitions for Sparc HME/BigMac 10/100baseT ethernet driver.&n; *           Also known as the &quot;Happy Meal&quot;.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _SUNHME_H
DECL|macro|_SUNHME_H
mdefine_line|#define _SUNHME_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Happy Meal global registers. */
DECL|struct|hmeal_gregs
r_struct
id|hmeal_gregs
(brace
DECL|member|sw_reset
r_volatile
r_int
r_int
id|sw_reset
suffix:semicolon
multiline_comment|/* Software Reset  */
DECL|member|cfg
r_volatile
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* Config Register */
DECL|member|_padding
r_volatile
r_int
r_int
id|_padding
(braket
l_int|62
)braket
suffix:semicolon
multiline_comment|/* Unused          */
DECL|member|stat
r_volatile
r_int
r_int
id|stat
suffix:semicolon
multiline_comment|/* Status          */
DECL|member|imask
r_volatile
r_int
r_int
id|imask
suffix:semicolon
multiline_comment|/* Interrupt Mask  */
)brace
suffix:semicolon
multiline_comment|/* Global reset register. */
DECL|macro|GREG_RESET_ETX
mdefine_line|#define GREG_RESET_ETX         0x01
DECL|macro|GREG_RESET_ERX
mdefine_line|#define GREG_RESET_ERX         0x02
DECL|macro|GREG_RESET_ALL
mdefine_line|#define GREG_RESET_ALL         0x03
multiline_comment|/* Global config register. */
DECL|macro|GREG_CFG_BURSTMSK
mdefine_line|#define GREG_CFG_BURSTMSK      0x03
DECL|macro|GREG_CFG_BURST16
mdefine_line|#define GREG_CFG_BURST16       0x00
DECL|macro|GREG_CFG_BURST32
mdefine_line|#define GREG_CFG_BURST32       0x01
DECL|macro|GREG_CFG_BURST64
mdefine_line|#define GREG_CFG_BURST64       0x02
DECL|macro|GREG_CFG_64BIT
mdefine_line|#define GREG_CFG_64BIT         0x04
DECL|macro|GREG_CFG_PARITY
mdefine_line|#define GREG_CFG_PARITY        0x08
DECL|macro|GREG_CFG_RESV
mdefine_line|#define GREG_CFG_RESV          0x10
multiline_comment|/* Global status register. */
DECL|macro|GREG_STAT_GOTFRAME
mdefine_line|#define GREG_STAT_GOTFRAME     0x00000001 /* Received a frame                         */
DECL|macro|GREG_STAT_RCNTEXP
mdefine_line|#define GREG_STAT_RCNTEXP      0x00000002 /* Receive frame counter expired            */
DECL|macro|GREG_STAT_ACNTEXP
mdefine_line|#define GREG_STAT_ACNTEXP      0x00000004 /* Align-error counter expired              */
DECL|macro|GREG_STAT_CCNTEXP
mdefine_line|#define GREG_STAT_CCNTEXP      0x00000008 /* CRC-error counter expired                */
DECL|macro|GREG_STAT_LCNTEXP
mdefine_line|#define GREG_STAT_LCNTEXP      0x00000010 /* Length-error counter expired             */
DECL|macro|GREG_STAT_RFIFOVF
mdefine_line|#define GREG_STAT_RFIFOVF      0x00000020 /* Receive FIFO overflow                    */
DECL|macro|GREG_STAT_CVCNTEXP
mdefine_line|#define GREG_STAT_CVCNTEXP     0x00000040 /* Code-violation counter expired           */
DECL|macro|GREG_STAT_STSTERR
mdefine_line|#define GREG_STAT_STSTERR      0x00000080 /* Test error in XIF for SQE                */
DECL|macro|GREG_STAT_SENTFRAME
mdefine_line|#define GREG_STAT_SENTFRAME    0x00000100 /* Transmitted a frame                      */
DECL|macro|GREG_STAT_TFIFO_UND
mdefine_line|#define GREG_STAT_TFIFO_UND    0x00000200 /* Transmit FIFO underrun                   */
DECL|macro|GREG_STAT_MAXPKTERR
mdefine_line|#define GREG_STAT_MAXPKTERR    0x00000400 /* Max-packet size error                    */
DECL|macro|GREG_STAT_NCNTEXP
mdefine_line|#define GREG_STAT_NCNTEXP      0x00000800 /* Normal-collision counter expired         */
DECL|macro|GREG_STAT_ECNTEXP
mdefine_line|#define GREG_STAT_ECNTEXP      0x00001000 /* Excess-collision counter expired         */
DECL|macro|GREG_STAT_LCCNTEXP
mdefine_line|#define GREG_STAT_LCCNTEXP     0x00002000 /* Late-collision counter expired           */
DECL|macro|GREG_STAT_FCNTEXP
mdefine_line|#define GREG_STAT_FCNTEXP      0x00004000 /* First-collision counter expired          */
DECL|macro|GREG_STAT_DTIMEXP
mdefine_line|#define GREG_STAT_DTIMEXP      0x00008000 /* Defer-timer expired                      */
DECL|macro|GREG_STAT_RXTOHOST
mdefine_line|#define GREG_STAT_RXTOHOST     0x00010000 /* Moved from receive-FIFO to host memory   */
DECL|macro|GREG_STAT_NORXD
mdefine_line|#define GREG_STAT_NORXD        0x00020000 /* No more receive descriptors              */
DECL|macro|GREG_STAT_RXERR
mdefine_line|#define GREG_STAT_RXERR        0x00040000 /* Error during receive dma                 */
DECL|macro|GREG_STAT_RXLATERR
mdefine_line|#define GREG_STAT_RXLATERR     0x00080000 /* Late error during receive dma            */
DECL|macro|GREG_STAT_RXPERR
mdefine_line|#define GREG_STAT_RXPERR       0x00100000 /* Parity error during receive dma          */
DECL|macro|GREG_STAT_RXTERR
mdefine_line|#define GREG_STAT_RXTERR       0x00200000 /* Tag error during receive dma             */
DECL|macro|GREG_STAT_EOPERR
mdefine_line|#define GREG_STAT_EOPERR       0x00400000 /* Transmit descriptor did not have EOP set */
DECL|macro|GREG_STAT_MIFIRQ
mdefine_line|#define GREG_STAT_MIFIRQ       0x00800000 /* MIF is signaling an interrupt condition  */
DECL|macro|GREG_STAT_HOSTTOTX
mdefine_line|#define GREG_STAT_HOSTTOTX     0x01000000 /* Moved from host memory to transmit-FIFO  */
DECL|macro|GREG_STAT_TXALL
mdefine_line|#define GREG_STAT_TXALL        0x02000000 /* Transmitted all packets in the tx-fifo   */
DECL|macro|GREG_STAT_TXEACK
mdefine_line|#define GREG_STAT_TXEACK       0x04000000 /* Error during transmit dma                */
DECL|macro|GREG_STAT_TXLERR
mdefine_line|#define GREG_STAT_TXLERR       0x08000000 /* Late error during transmit dma           */
DECL|macro|GREG_STAT_TXPERR
mdefine_line|#define GREG_STAT_TXPERR       0x10000000 /* Parity error during transmit dma         */
DECL|macro|GREG_STAT_TXTERR
mdefine_line|#define GREG_STAT_TXTERR       0x20000000 /* Tag error during transmit dma            */
DECL|macro|GREG_STAT_SLVERR
mdefine_line|#define GREG_STAT_SLVERR       0x40000000 /* PIO access got an error                  */
DECL|macro|GREG_STAT_SLVPERR
mdefine_line|#define GREG_STAT_SLVPERR      0x80000000 /* PIO access got a parity error            */
multiline_comment|/* All interesting error conditions. */
DECL|macro|GREG_STAT_ERRORS
mdefine_line|#define GREG_STAT_ERRORS       0xfc7efefc
multiline_comment|/* Global interrupt mask register. */
DECL|macro|GREG_IMASK_GOTFRAME
mdefine_line|#define GREG_IMASK_GOTFRAME    0x00000001 /* Received a frame                         */
DECL|macro|GREG_IMASK_RCNTEXP
mdefine_line|#define GREG_IMASK_RCNTEXP     0x00000002 /* Receive frame counter expired            */
DECL|macro|GREG_IMASK_ACNTEXP
mdefine_line|#define GREG_IMASK_ACNTEXP     0x00000004 /* Align-error counter expired              */
DECL|macro|GREG_IMASK_CCNTEXP
mdefine_line|#define GREG_IMASK_CCNTEXP     0x00000008 /* CRC-error counter expired                */
DECL|macro|GREG_IMASK_LCNTEXP
mdefine_line|#define GREG_IMASK_LCNTEXP     0x00000010 /* Length-error counter expired             */
DECL|macro|GREG_IMASK_RFIFOVF
mdefine_line|#define GREG_IMASK_RFIFOVF     0x00000020 /* Receive FIFO overflow                    */
DECL|macro|GREG_IMASK_CVCNTEXP
mdefine_line|#define GREG_IMASK_CVCNTEXP    0x00000040 /* Code-violation counter expired           */
DECL|macro|GREG_IMASK_STSTERR
mdefine_line|#define GREG_IMASK_STSTERR     0x00000080 /* Test error in XIF for SQE                */
DECL|macro|GREG_IMASK_SENTFRAME
mdefine_line|#define GREG_IMASK_SENTFRAME   0x00000100 /* Transmitted a frame                      */
DECL|macro|GREG_IMASK_TFIFO_UND
mdefine_line|#define GREG_IMASK_TFIFO_UND   0x00000200 /* Transmit FIFO underrun                   */
DECL|macro|GREG_IMASK_MAXPKTERR
mdefine_line|#define GREG_IMASK_MAXPKTERR   0x00000400 /* Max-packet size error                    */
DECL|macro|GREG_IMASK_NCNTEXP
mdefine_line|#define GREG_IMASK_NCNTEXP     0x00000800 /* Normal-collision counter expired         */
DECL|macro|GREG_IMASK_ECNTEXP
mdefine_line|#define GREG_IMASK_ECNTEXP     0x00001000 /* Excess-collision counter expired         */
DECL|macro|GREG_IMASK_LCCNTEXP
mdefine_line|#define GREG_IMASK_LCCNTEXP    0x00002000 /* Late-collision counter expired           */
DECL|macro|GREG_IMASK_FCNTEXP
mdefine_line|#define GREG_IMASK_FCNTEXP     0x00004000 /* First-collision counter expired          */
DECL|macro|GREG_IMASK_DTIMEXP
mdefine_line|#define GREG_IMASK_DTIMEXP     0x00008000 /* Defer-timer expired                      */
DECL|macro|GREG_IMASK_RXTOHOST
mdefine_line|#define GREG_IMASK_RXTOHOST    0x00010000 /* Moved from receive-FIFO to host memory   */
DECL|macro|GREG_IMASK_NORXD
mdefine_line|#define GREG_IMASK_NORXD       0x00020000 /* No more receive descriptors              */
DECL|macro|GREG_IMASK_RXERR
mdefine_line|#define GREG_IMASK_RXERR       0x00040000 /* Error during receive dma                 */
DECL|macro|GREG_IMASK_RXLATERR
mdefine_line|#define GREG_IMASK_RXLATERR    0x00080000 /* Late error during receive dma            */
DECL|macro|GREG_IMASK_RXPERR
mdefine_line|#define GREG_IMASK_RXPERR      0x00100000 /* Parity error during receive dma          */
DECL|macro|GREG_IMASK_RXTERR
mdefine_line|#define GREG_IMASK_RXTERR      0x00200000 /* Tag error during receive dma             */
DECL|macro|GREG_IMASK_EOPERR
mdefine_line|#define GREG_IMASK_EOPERR      0x00400000 /* Transmit descriptor did not have EOP set */
DECL|macro|GREG_IMASK_MIFIRQ
mdefine_line|#define GREG_IMASK_MIFIRQ      0x00800000 /* MIF is signaling an interrupt condition  */
DECL|macro|GREG_IMASK_HOSTTOTX
mdefine_line|#define GREG_IMASK_HOSTTOTX    0x01000000 /* Moved from host memory to transmit-FIFO  */
DECL|macro|GREG_IMASK_TXALL
mdefine_line|#define GREG_IMASK_TXALL       0x02000000 /* Transmitted all packets in the tx-fifo   */
DECL|macro|GREG_IMASK_TXEACK
mdefine_line|#define GREG_IMASK_TXEACK      0x04000000 /* Error during transmit dma                */
DECL|macro|GREG_IMASK_TXLERR
mdefine_line|#define GREG_IMASK_TXLERR      0x08000000 /* Late error during transmit dma           */
DECL|macro|GREG_IMASK_TXPERR
mdefine_line|#define GREG_IMASK_TXPERR      0x10000000 /* Parity error during transmit dma         */
DECL|macro|GREG_IMASK_TXTERR
mdefine_line|#define GREG_IMASK_TXTERR      0x20000000 /* Tag error during transmit dma            */
DECL|macro|GREG_IMASK_SLVERR
mdefine_line|#define GREG_IMASK_SLVERR      0x40000000 /* PIO access got an error                  */
DECL|macro|GREG_IMASK_SLVPERR
mdefine_line|#define GREG_IMASK_SLVPERR     0x80000000 /* PIO access got a parity error            */
multiline_comment|/* Happy Meal external transmitter registers. */
DECL|struct|hmeal_etxregs
r_struct
id|hmeal_etxregs
(brace
DECL|member|tx_pnding
r_volatile
r_int
r_int
id|tx_pnding
suffix:semicolon
multiline_comment|/* Transmit pending/wakeup register */
DECL|member|cfg
r_volatile
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* Transmit config register         */
DECL|member|tx_ring
r_volatile
r_int
r_int
id|tx_ring
suffix:semicolon
multiline_comment|/* Transmit ring pointer            */
DECL|member|tx_bbase
r_volatile
r_int
r_int
id|tx_bbase
suffix:semicolon
multiline_comment|/* Transmit buffer base             */
DECL|member|tx_bdisp
r_volatile
r_int
r_int
id|tx_bdisp
suffix:semicolon
multiline_comment|/* Transmit buffer displacement     */
DECL|member|tx_fifo_wptr
r_volatile
r_int
r_int
id|tx_fifo_wptr
suffix:semicolon
multiline_comment|/* FIFO write ptr                   */
DECL|member|tx_fifo_swptr
r_volatile
r_int
r_int
id|tx_fifo_swptr
suffix:semicolon
multiline_comment|/* FIFO write ptr (shadow register) */
DECL|member|tx_fifo_rptr
r_volatile
r_int
r_int
id|tx_fifo_rptr
suffix:semicolon
multiline_comment|/* FIFO read ptr                    */
DECL|member|tx_fifo_srptr
r_volatile
r_int
r_int
id|tx_fifo_srptr
suffix:semicolon
multiline_comment|/* FIFO read ptr (shadow register)  */
DECL|member|tx_fifo_pcnt
r_volatile
r_int
r_int
id|tx_fifo_pcnt
suffix:semicolon
multiline_comment|/* FIFO packet counter              */
DECL|member|smachine
r_volatile
r_int
r_int
id|smachine
suffix:semicolon
multiline_comment|/* Transmitter state machine        */
DECL|member|tx_rsize
r_volatile
r_int
r_int
id|tx_rsize
suffix:semicolon
multiline_comment|/* Ring descriptor size             */
DECL|member|tx_bptr
r_volatile
r_int
r_int
id|tx_bptr
suffix:semicolon
multiline_comment|/* Transmit data buffer ptr         */
)brace
suffix:semicolon
multiline_comment|/* ETX transmit pending register. */
DECL|macro|ETX_TP_DMAWAKEUP
mdefine_line|#define ETX_TP_DMAWAKEUP         0x00000001 /* Restart transmit dma             */
multiline_comment|/* ETX config register. */
DECL|macro|ETX_CFG_DMAENABLE
mdefine_line|#define ETX_CFG_DMAENABLE        0x00000001 /* Enable transmit dma              */
DECL|macro|ETX_CFG_FIFOTHRESH
mdefine_line|#define ETX_CFG_FIFOTHRESH       0x000003fe /* Transmit FIFO threshold          */
DECL|macro|ETX_CFG_IRQDAFTER
mdefine_line|#define ETX_CFG_IRQDAFTER        0x00000400 /* Interrupt after TX-FIFO drained  */
DECL|macro|ETX_CFG_IRQDBEFORE
mdefine_line|#define ETX_CFG_IRQDBEFORE       0x00000000 /* Interrupt before TX-FIFO drained */
DECL|macro|ETX_RSIZE_SHIFT
mdefine_line|#define ETX_RSIZE_SHIFT          4
multiline_comment|/* Happy Meal external receiver registers. */
DECL|struct|hmeal_erxregs
r_struct
id|hmeal_erxregs
(brace
DECL|member|cfg
r_volatile
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* Receiver config register         */
DECL|member|rx_ring
r_volatile
r_int
r_int
id|rx_ring
suffix:semicolon
multiline_comment|/* Receiver ring ptr                */
DECL|member|rx_bptr
r_volatile
r_int
r_int
id|rx_bptr
suffix:semicolon
multiline_comment|/* Receiver buffer ptr              */
DECL|member|rx_fifo_wptr
r_volatile
r_int
r_int
id|rx_fifo_wptr
suffix:semicolon
multiline_comment|/* FIFO write ptr                   */
DECL|member|rx_fifo_swptr
r_volatile
r_int
r_int
id|rx_fifo_swptr
suffix:semicolon
multiline_comment|/* FIFO write ptr (shadow register) */
DECL|member|rx_fifo_rptr
r_volatile
r_int
r_int
id|rx_fifo_rptr
suffix:semicolon
multiline_comment|/* FIFO read ptr                    */
DECL|member|rx_fifo_srptr
r_volatile
r_int
r_int
id|rx_fifo_srptr
suffix:semicolon
multiline_comment|/* FIFO read ptr (shadow register)  */
DECL|member|smachine
r_volatile
r_int
r_int
id|smachine
suffix:semicolon
multiline_comment|/* Receiver state machine           */
)brace
suffix:semicolon
multiline_comment|/* ERX config register. */
DECL|macro|ERX_CFG_DMAENABLE
mdefine_line|#define ERX_CFG_DMAENABLE    0x00000001 /* Enable receive DMA        */
DECL|macro|ERX_CFG_RESV1
mdefine_line|#define ERX_CFG_RESV1        0x00000006 /* Unused...                 */
DECL|macro|ERX_CFG_BYTEOFFSET
mdefine_line|#define ERX_CFG_BYTEOFFSET   0x00000038 /* Receive first byte offset */
DECL|macro|ERX_CFG_RESV2
mdefine_line|#define ERX_CFG_RESV2        0x000001c0 /* Unused...                 */
DECL|macro|ERX_CFG_SIZE32
mdefine_line|#define ERX_CFG_SIZE32       0x00000000 /* Receive ring size == 32   */
DECL|macro|ERX_CFG_SIZE64
mdefine_line|#define ERX_CFG_SIZE64       0x00000200 /* Receive ring size == 64   */
DECL|macro|ERX_CFG_SIZE128
mdefine_line|#define ERX_CFG_SIZE128      0x00000400 /* Receive ring size == 128  */
DECL|macro|ERX_CFG_SIZE256
mdefine_line|#define ERX_CFG_SIZE256      0x00000600 /* Receive ring size == 256  */
DECL|macro|ERX_CFG_RESV3
mdefine_line|#define ERX_CFG_RESV3        0x0000f800 /* Unused...                 */
DECL|macro|ERX_CFG_CSUMSTART
mdefine_line|#define ERX_CFG_CSUMSTART    0x007f0000 /* Offset of checksum start  */
multiline_comment|/* I&squot;d like a Big Mac, small fries, small coke, and SparcLinux please. */
DECL|struct|hmeal_bigmacregs
r_struct
id|hmeal_bigmacregs
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
l_int|129
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
multiline_comment|/* Jam size                           */
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
DECL|member|_unused2
r_volatile
r_int
r_int
id|_unused2
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
DECL|member|_unused3
r_volatile
r_int
r_int
id|_unused3
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
mdefine_line|#define BIGMAC_XCFG_ODENABLE  0x00000001 /* Output driver enable         */
DECL|macro|BIGMAC_XCFG_XLBACK
mdefine_line|#define BIGMAC_XCFG_XLBACK    0x00000002 /* Loopback-mode XIF enable     */
DECL|macro|BIGMAC_XCFG_MLBACK
mdefine_line|#define BIGMAC_XCFG_MLBACK    0x00000004 /* Loopback-mode MII enable     */
DECL|macro|BIGMAC_XCFG_MIIDISAB
mdefine_line|#define BIGMAC_XCFG_MIIDISAB  0x00000008 /* MII receive buffer disable   */
DECL|macro|BIGMAC_XCFG_SQENABLE
mdefine_line|#define BIGMAC_XCFG_SQENABLE  0x00000010 /* SQE test enable              */
DECL|macro|BIGMAC_XCFG_SQETWIN
mdefine_line|#define BIGMAC_XCFG_SQETWIN   0x000003e0 /* SQE time window              */
DECL|macro|BIGMAC_XCFG_LANCE
mdefine_line|#define BIGMAC_XCFG_LANCE     0x00000010 /* Lance mode enable            */
DECL|macro|BIGMAC_XCFG_LIPG0
mdefine_line|#define BIGMAC_XCFG_LIPG0     0x000003e0 /* Lance mode IPG0              */
multiline_comment|/* BigMac transmit config register. */
DECL|macro|BIGMAC_TXCFG_ENABLE
mdefine_line|#define BIGMAC_TXCFG_ENABLE   0x00000001 /* Enable the transmitter       */
DECL|macro|BIGMAC_TXCFG_SMODE
mdefine_line|#define BIGMAC_TXCFG_SMODE    0x00000020 /* Enable slow transmit mode    */
DECL|macro|BIGMAC_TXCFG_CIGN
mdefine_line|#define BIGMAC_TXCFG_CIGN     0x00000040 /* Ignore transmit collisions   */
DECL|macro|BIGMAC_TXCFG_FCSOFF
mdefine_line|#define BIGMAC_TXCFG_FCSOFF   0x00000080 /* Do not emit FCS              */
DECL|macro|BIGMAC_TXCFG_DBACKOFF
mdefine_line|#define BIGMAC_TXCFG_DBACKOFF 0x00000100 /* Disable backoff              */
DECL|macro|BIGMAC_TXCFG_FULLDPLX
mdefine_line|#define BIGMAC_TXCFG_FULLDPLX 0x00000200 /* Enable full-duplex           */
DECL|macro|BIGMAC_TXCFG_DGIVEUP
mdefine_line|#define BIGMAC_TXCFG_DGIVEUP  0x00000400 /* Don&squot;t give up on transmits   */
multiline_comment|/* BigMac receive config register. */
DECL|macro|BIGMAC_RXCFG_ENABLE
mdefine_line|#define BIGMAC_RXCFG_ENABLE   0x00000001 /* Enable the receiver             */
DECL|macro|BIGMAC_RXCFG_PSTRIP
mdefine_line|#define BIGMAC_RXCFG_PSTRIP   0x00000020 /* Pad byte strip enable           */
DECL|macro|BIGMAC_RXCFG_PMISC
mdefine_line|#define BIGMAC_RXCFG_PMISC    0x00000040 /* Enable promiscous mode          */
DECL|macro|BIGMAC_RXCFG_DERR
mdefine_line|#define BIGMAC_RXCFG_DERR     0x00000080 /* Disable error checking          */
DECL|macro|BIGMAC_RXCFG_DCRCS
mdefine_line|#define BIGMAC_RXCFG_DCRCS    0x00000100 /* Disable CRC stripping           */
DECL|macro|BIGMAC_RXCFG_ME
mdefine_line|#define BIGMAC_RXCFG_ME       0x00000200 /* Receive packets addressed to me */
DECL|macro|BIGMAC_RXCFG_PGRP
mdefine_line|#define BIGMAC_RXCFG_PGRP     0x00000400 /* Enable promisc group mode       */
DECL|macro|BIGMAC_RXCFG_HENABLE
mdefine_line|#define BIGMAC_RXCFG_HENABLE  0x00000800 /* Enable the hash filter          */
DECL|macro|BIGMAC_RXCFG_AENABLE
mdefine_line|#define BIGMAC_RXCFG_AENABLE  0x00001000 /* Enable the address filter       */
multiline_comment|/* These are the &quot;Management Interface&quot; (ie. MIF) registers of the transceiver. */
DECL|struct|hmeal_tcvregs
r_struct
id|hmeal_tcvregs
(brace
DECL|member|bb_clock
r_volatile
r_int
r_int
id|bb_clock
suffix:semicolon
multiline_comment|/* Bit bang clock register          */
DECL|member|bb_data
r_volatile
r_int
r_int
id|bb_data
suffix:semicolon
multiline_comment|/* Bit bang data register           */
DECL|member|bb_oenab
r_volatile
r_int
r_int
id|bb_oenab
suffix:semicolon
multiline_comment|/* Bit bang output enable           */
DECL|member|frame
r_volatile
r_int
r_int
id|frame
suffix:semicolon
multiline_comment|/* Frame control/data register      */
DECL|member|cfg
r_volatile
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* MIF config register              */
DECL|member|int_mask
r_volatile
r_int
r_int
id|int_mask
suffix:semicolon
multiline_comment|/* MIF interrupt mask               */
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* MIF status                       */
DECL|member|smachine
r_volatile
r_int
r_int
id|smachine
suffix:semicolon
multiline_comment|/* MIF state machine                */
)brace
suffix:semicolon
multiline_comment|/* Frame commands. */
DECL|macro|FRAME_WRITE
mdefine_line|#define FRAME_WRITE           0x50020000
DECL|macro|FRAME_READ
mdefine_line|#define FRAME_READ            0x60020000
multiline_comment|/* Transceiver config register */
DECL|macro|TCV_CFG_PSELECT
mdefine_line|#define TCV_CFG_PSELECT       0x00000001 /* Select PHY                      */
DECL|macro|TCV_CFG_PENABLE
mdefine_line|#define TCV_CFG_PENABLE       0x00000002 /* Enable MIF polling              */
DECL|macro|TCV_CFG_BENABLE
mdefine_line|#define TCV_CFG_BENABLE       0x00000004 /* Enable the &quot;bit banger&quot; oh baby */
DECL|macro|TCV_CFG_PREGADDR
mdefine_line|#define TCV_CFG_PREGADDR      0x000000f8 /* Address of poll register        */
DECL|macro|TCV_CFG_MDIO0
mdefine_line|#define TCV_CFG_MDIO0         0x00000100 /* MDIO zero, data/attached        */
DECL|macro|TCV_CFG_MDIO1
mdefine_line|#define TCV_CFG_MDIO1         0x00000200 /* MDIO one,  data/attached        */
DECL|macro|TCV_CFG_PDADDR
mdefine_line|#define TCV_CFG_PDADDR        0x00007c00 /* Device PHY address polling      */
multiline_comment|/* Here are some PHY addresses. */
DECL|macro|TCV_PADDR_ETX
mdefine_line|#define TCV_PADDR_ETX         0          /* Internal transceiver            */
DECL|macro|TCV_PADDR_ITX
mdefine_line|#define TCV_PADDR_ITX         1          /* External transceiver            */
multiline_comment|/* Transceiver status register */
DECL|macro|TCV_STAT_BASIC
mdefine_line|#define TCV_STAT_BASIC        0xffff0000 /* The &quot;basic&quot; part                */
DECL|macro|TCV_STAT_NORMAL
mdefine_line|#define TCV_STAT_NORMAL       0x0000ffff /* The &quot;non-basic&quot; part            */
multiline_comment|/* Inside the Happy Meal transceiver is the physical layer, they use an&n; * implementations for National Semiconductor, part number DP83840VCE.&n; * You can retrieve the data sheets and programming docs for this beast&n; * from http://www.national.com/&n; *&n; * The DP83840 is capable of both 10 and 100Mbps ethernet, in both&n; * half and full duplex mode.  It also supports auto negotiation.&n; *&n; * But.... THIS THING IS A PAIN IN THE ASS TO PROGRAM!&n; * Debugging eeprom burnt code is more fun than programming this chip!&n; */
multiline_comment|/* First, the DP83840 register numbers. */
DECL|macro|DP83840_BMCR
mdefine_line|#define DP83840_BMCR            0x00        /* Basic mode control register */
DECL|macro|DP83840_BMSR
mdefine_line|#define DP83840_BMSR            0x01        /* Basic mode status register  */
DECL|macro|DP83840_PHYSID1
mdefine_line|#define DP83840_PHYSID1         0x02        /* PHYS ID 1                   */
DECL|macro|DP83840_PHYSID2
mdefine_line|#define DP83840_PHYSID2         0x03        /* PHYS ID 2                   */
DECL|macro|DP83840_ADVERTISE
mdefine_line|#define DP83840_ADVERTISE       0x04        /* Advertisement control reg   */
DECL|macro|DP83840_LPA
mdefine_line|#define DP83840_LPA             0x05        /* Link partner ability reg    */
DECL|macro|DP83840_EXPANSION
mdefine_line|#define DP83840_EXPANSION       0x06        /* Expansion register          */
DECL|macro|DP83840_DCOUNTER
mdefine_line|#define DP83840_DCOUNTER        0x12        /* Disconnect counter          */
DECL|macro|DP83840_FCSCOUNTER
mdefine_line|#define DP83840_FCSCOUNTER      0x13        /* False carrier counter       */
DECL|macro|DP83840_NWAYTEST
mdefine_line|#define DP83840_NWAYTEST        0x14        /* N-way auto-neg test reg     */
DECL|macro|DP83840_RERRCOUNTER
mdefine_line|#define DP83840_RERRCOUNTER     0x15        /* Receive error counter       */
DECL|macro|DP83840_SREVISION
mdefine_line|#define DP83840_SREVISION       0x16        /* Silicon revision            */
DECL|macro|DP83840_CSCONFIG
mdefine_line|#define DP83840_CSCONFIG        0x17        /* CS configuration            */
DECL|macro|DP83840_LBRERROR
mdefine_line|#define DP83840_LBRERROR        0x18        /* Lpback, rx, bypass error    */
DECL|macro|DP83840_PHYADDR
mdefine_line|#define DP83840_PHYADDR         0x19        /* PHY address                 */
DECL|macro|DP83840_RESERVED
mdefine_line|#define DP83840_RESERVED        0x1a        /* Unused...                   */
DECL|macro|DP83840_TPISTATUS
mdefine_line|#define DP83840_TPISTATUS       0x1b        /* TPI status for 10mbps       */
DECL|macro|DP83840_NCONFIG
mdefine_line|#define DP83840_NCONFIG         0x1c        /* Network interface config    */
multiline_comment|/* Basic mode control register. */
DECL|macro|BMCR_RESV
mdefine_line|#define BMCR_RESV               0x007f  /* Unused...                   */
DECL|macro|BMCR_CTST
mdefine_line|#define BMCR_CTST               0x0080  /* Collision test              */
DECL|macro|BMCR_FULLDPLX
mdefine_line|#define BMCR_FULLDPLX           0x0100  /* Full duplex                 */
DECL|macro|BMCR_ANRESTART
mdefine_line|#define BMCR_ANRESTART          0x0200  /* Auto negotiation restart    */
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
multiline_comment|/* Basic mode status register. */
DECL|macro|BMSR_ERCAP
mdefine_line|#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
DECL|macro|BMSR_JCD
mdefine_line|#define BMSR_JCD                0x0002  /* Jabber detected             */
DECL|macro|BMSR_LSTATUS
mdefine_line|#define BMSR_LSTATUS            0x0004  /* Link status                 */
DECL|macro|BMSR_ANEGCAPABLE
mdefine_line|#define BMSR_ANEGCAPABLE        0x0008  /* Able to do auto-negotiation */
DECL|macro|BMSR_RFAULT
mdefine_line|#define BMSR_RFAULT             0x0010  /* Remote fault detected       */
DECL|macro|BMSR_ANEGCOMPLETE
mdefine_line|#define BMSR_ANEGCOMPLETE       0x0020  /* Auto-negotiation complete   */
DECL|macro|BMSR_RESV
mdefine_line|#define BMSR_RESV               0x07c0  /* Unused...                   */
DECL|macro|BMSR_10HALF
mdefine_line|#define BMSR_10HALF             0x0800  /* Can do 10mbps, half-duplex  */
DECL|macro|BMSR_10FULL
mdefine_line|#define BMSR_10FULL             0x1000  /* Can do 10mbps, full-duplex  */
DECL|macro|BMSR_100HALF
mdefine_line|#define BMSR_100HALF            0x2000  /* Can do 100mbps, half-duplex */
DECL|macro|BMSR_100FULL
mdefine_line|#define BMSR_100FULL            0x4000  /* Can do 100mbps, full-duplex */
DECL|macro|BMSR_100BASE4
mdefine_line|#define BMSR_100BASE4           0x8000  /* Can do 100mbps, 4k packets  */
multiline_comment|/* Advertisement control register. */
DECL|macro|ADVERTISE_SLCT
mdefine_line|#define ADVERTISE_SLCT          0x001f  /* Selector bits               */
DECL|macro|ADVERTISE_CSMA
mdefine_line|#define ADVERTISE_CSMA          0x0001  /* Only selector supported     */
DECL|macro|ADVERTISE_10HALF
mdefine_line|#define ADVERTISE_10HALF        0x0020  /* Try for 10mbps half-duplex  */
DECL|macro|ADVERTISE_10FULL
mdefine_line|#define ADVERTISE_10FULL        0x0040  /* Try for 10mbps full-duplex  */
DECL|macro|ADVERTISE_100HALF
mdefine_line|#define ADVERTISE_100HALF       0x0080  /* Try for 100mbps half-duplex */
DECL|macro|ADVERTISE_100FULL
mdefine_line|#define ADVERTISE_100FULL       0x0100  /* Try for 100mbps full-duplex */
DECL|macro|ADVERTISE_100BASE4
mdefine_line|#define ADVERTISE_100BASE4      0x0200  /* Try for 100mbps 4k packets  */
DECL|macro|ADVERTISE_RESV
mdefine_line|#define ADVERTISE_RESV          0x1c00  /* Unused...                   */
DECL|macro|ADVERTISE_RFAULT
mdefine_line|#define ADVERTISE_RFAULT        0x2000  /* Say we can detect faults    */
DECL|macro|ADVERTISE_LPACK
mdefine_line|#define ADVERTISE_LPACK         0x4000  /* Ack link partners response  */
DECL|macro|ADVERTISE_NPAGE
mdefine_line|#define ADVERTISE_NPAGE         0x8000  /* Next page bit               */
DECL|macro|ADVERTISE_ALL
mdefine_line|#define ADVERTISE_ALL (ADVERTISE_10HALF | ADVERTISE_10FULL | &bslash;&n;                       ADVERTISE_100HALF | ADVERTISE_100FULL)
multiline_comment|/* Link partner ability register. */
DECL|macro|LPA_SLCT
mdefine_line|#define LPA_SLCT                0x001f  /* Same as advertise selector  */
DECL|macro|LPA_10HALF
mdefine_line|#define LPA_10HALF              0x0020  /* Can do 10mbps half-duplex   */
DECL|macro|LPA_10FULL
mdefine_line|#define LPA_10FULL              0x0040  /* Can do 10mbps full-duplex   */
DECL|macro|LPA_100HALF
mdefine_line|#define LPA_100HALF             0x0080  /* Can do 100mbps half-duplex  */
DECL|macro|LPA_100FULL
mdefine_line|#define LPA_100FULL             0x0100  /* Can do 100mbps full-duplex  */
DECL|macro|LPA_100BASE4
mdefine_line|#define LPA_100BASE4            0x0200  /* Can do 100mbps 4k packets   */
DECL|macro|LPA_RESV
mdefine_line|#define LPA_RESV                0x1c00  /* Unused...                   */
DECL|macro|LPA_RFAULT
mdefine_line|#define LPA_RFAULT              0x2000  /* Link partner faulted        */
DECL|macro|LPA_LPACK
mdefine_line|#define LPA_LPACK               0x4000  /* Link partner acked us       */
DECL|macro|LPA_NPAGE
mdefine_line|#define LPA_NPAGE               0x8000  /* Next page bit               */
multiline_comment|/* Expansion register for auto-negotiation. */
DECL|macro|EXPANSION_NWAY
mdefine_line|#define EXPANSION_NWAY          0x0001  /* Can do N-way auto-nego      */
DECL|macro|EXPANSION_LCWP
mdefine_line|#define EXPANSION_LCWP          0x0002  /* Got new RX page code word   */
DECL|macro|EXPANSION_ENABLENPAGE
mdefine_line|#define EXPANSION_ENABLENPAGE   0x0004  /* This enables npage words    */
DECL|macro|EXPANSION_NPCAPABLE
mdefine_line|#define EXPANSION_NPCAPABLE     0x0008  /* Link partner supports npage */
DECL|macro|EXPANSION_MFAULTS
mdefine_line|#define EXPANSION_MFAULTS       0x0010  /* Multiple faults detected    */
DECL|macro|EXPANSION_RESV
mdefine_line|#define EXPANSION_RESV          0xffe0  /* Unused...                   */
multiline_comment|/* N-way test register. */
DECL|macro|NWAYTEST_RESV1
mdefine_line|#define NWAYTEST_RESV1          0x00ff  /* Unused...                   */
DECL|macro|NWAYTEST_LOOPBACK
mdefine_line|#define NWAYTEST_LOOPBACK       0x0100  /* Enable loopback for N-way   */
DECL|macro|NWAYTEST_RESV2
mdefine_line|#define NWAYTEST_RESV2          0xfe00  /* Unused...                   */
multiline_comment|/* The Carrier Sense config register. */
DECL|macro|CSCONFIG_RESV1
mdefine_line|#define CSCONFIG_RESV1          0x0001  /* Unused...                   */
DECL|macro|CSCONFIG_LED4
mdefine_line|#define CSCONFIG_LED4           0x0002  /* Pin for full-dplx LED4      */
DECL|macro|CSCONFIG_LED1
mdefine_line|#define CSCONFIG_LED1           0x0004  /* Pin for conn-status LED1    */
DECL|macro|CSCONFIG_RESV2
mdefine_line|#define CSCONFIG_RESV2          0x0008  /* Unused...                   */
DECL|macro|CSCONFIG_TCVDISAB
mdefine_line|#define CSCONFIG_TCVDISAB       0x0010  /* Turns off the transceiver   */
DECL|macro|CSCONFIG_DFBYPASS
mdefine_line|#define CSCONFIG_DFBYPASS       0x0020  /* Bypass disconnect function  */
DECL|macro|CSCONFIG_GLFORCE
mdefine_line|#define CSCONFIG_GLFORCE        0x0040  /* Good link force for 100mbps */
DECL|macro|CSCONFIG_CLKTRISTATE
mdefine_line|#define CSCONFIG_CLKTRISTATE    0x0080  /* Tristate 25m clock          */
DECL|macro|CSCONFIG_RESV3
mdefine_line|#define CSCONFIG_RESV3          0x0700  /* Unused...                   */
DECL|macro|CSCONFIG_ENCODE
mdefine_line|#define CSCONFIG_ENCODE         0x0800  /* 1=MLT-3, 0=binary           */
DECL|macro|CSCONFIG_RENABLE
mdefine_line|#define CSCONFIG_RENABLE        0x1000  /* Repeater mode enable        */
DECL|macro|CSCONFIG_TCDISABLE
mdefine_line|#define CSCONFIG_TCDISABLE      0x2000  /* Disable timeout counter     */
DECL|macro|CSCONFIG_RESV4
mdefine_line|#define CSCONFIG_RESV4          0x4000  /* Unused...                   */
DECL|macro|CSCONFIG_NDISABLE
mdefine_line|#define CSCONFIG_NDISABLE       0x8000  /* Disable NRZI                */
multiline_comment|/* Loopback, receive, bypass error register. */
DECL|macro|LBRERROR_EBUFFER
mdefine_line|#define LBRERROR_EBUFFER        0x0001  /* Show elasticity buf errors  */
DECL|macro|LBRERROR_PACKET
mdefine_line|#define LBRERROR_PACKET         0x0002  /* Show packet errors          */
DECL|macro|LBRERROR_LINK
mdefine_line|#define LBRERROR_LINK           0x0004  /* Show link errors            */
DECL|macro|LBRERROR_END
mdefine_line|#define LBRERROR_END            0x0008  /* Show premature end errors   */
DECL|macro|LBRERROR_CODE
mdefine_line|#define LBRERROR_CODE           0x0010  /* Show code errors            */
DECL|macro|LBRERROR_RESV1
mdefine_line|#define LBRERROR_RESV1          0x00e0  /* Unused...                   */
DECL|macro|LBRERROR_LBACK
mdefine_line|#define LBRERROR_LBACK          0x0300  /* Remote and twister loopback */
DECL|macro|LBRERROR_10TX
mdefine_line|#define LBRERROR_10TX           0x0400  /* Transceiver loopback 10mbps */
DECL|macro|LBRERROR_ENDEC
mdefine_line|#define LBRERROR_ENDEC          0x0800  /* ENDEC loopback 10mbps       */
DECL|macro|LBRERROR_ALIGN
mdefine_line|#define LBRERROR_ALIGN          0x1000  /* Bypass symbol alignment     */
DECL|macro|LBRERROR_SCRAMBLER
mdefine_line|#define LBRERROR_SCRAMBLER      0x2000  /* Bypass (de)scrambler        */
DECL|macro|LBRERROR_ENCODER
mdefine_line|#define LBRERROR_ENCODER        0x4000  /* Bypass 4B5B/5B4B encoders   */
DECL|macro|LBRERROR_BEBUF
mdefine_line|#define LBRERROR_BEBUF          0x8000  /* Bypass elasticity buffers   */
multiline_comment|/* Physical address register. */
DECL|macro|PHYADDR_ADDRESS
mdefine_line|#define PHYADDR_ADDRESS         0x001f  /* The address itself          */
DECL|macro|PHYADDR_DISCONNECT
mdefine_line|#define PHYADDR_DISCONNECT      0x0020  /* Disconnect status           */
DECL|macro|PHYADDR_10MBPS
mdefine_line|#define PHYADDR_10MBPS          0x0040  /* 1=10mbps, 0=100mbps         */
DECL|macro|PHYADDR_RESV
mdefine_line|#define PHYADDR_RESV            0xff80  /* Unused...                   */
multiline_comment|/* TPI status register for 10mbps. */
DECL|macro|TPISTATUS_RESV1
mdefine_line|#define TPISTATUS_RESV1         0x01ff  /* Unused...                   */
DECL|macro|TPISTATUS_SERIAL
mdefine_line|#define TPISTATUS_SERIAL        0x0200  /* Enable 10mbps serial mode   */
DECL|macro|TPISTATUS_RESV2
mdefine_line|#define TPISTATUS_RESV2         0xfc00  /* Unused...                   */
multiline_comment|/* Network interface config register. */
DECL|macro|NCONFIG_JENABLE
mdefine_line|#define NCONFIG_JENABLE         0x0001  /* Jabber enable               */
DECL|macro|NCONFIG_RESV1
mdefine_line|#define NCONFIG_RESV1           0x0002  /* Unused...                   */
DECL|macro|NCONFIG_SQUELCH
mdefine_line|#define NCONFIG_SQUELCH         0x0004  /* Use low squelch             */
DECL|macro|NCONFIG_UTP
mdefine_line|#define NCONFIG_UTP             0x0008  /* 1=UTP, 0=STP                */
DECL|macro|NCONFIG_HBEAT
mdefine_line|#define NCONFIG_HBEAT           0x0010  /* Heart-beat enable           */
DECL|macro|NCONFIG_LDISABLE
mdefine_line|#define NCONFIG_LDISABLE        0x0020  /* Disable the link            */
DECL|macro|NCONFIG_RESV2
mdefine_line|#define NCONFIG_RESV2           0xffc0  /* Unused...                   */
multiline_comment|/* Happy Meal descriptor rings and such.&n; * All descriptor rings must be aligned on a 2K boundry.&n; * All receive buffers must be 64 byte aligned.&n; */
DECL|struct|happy_meal_rxd
r_struct
id|happy_meal_rxd
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
DECL|macro|RXFLAG_OWN
mdefine_line|#define RXFLAG_OWN         0x80000000 /* 1 = hardware, 0 = software */
DECL|macro|RXFLAG_OVERFLOW
mdefine_line|#define RXFLAG_OVERFLOW    0x40000000 /* 1 = buffer overflow        */
DECL|macro|RXFLAG_SIZE
mdefine_line|#define RXFLAG_SIZE        0x3fff0000 /* Size of the buffer         */
DECL|macro|RXFLAG_CSUM
mdefine_line|#define RXFLAG_CSUM        0x0000ffff /* HW computed checksum       */
DECL|struct|happy_meal_txd
r_struct
id|happy_meal_txd
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
DECL|macro|TXFLAG_OWN
mdefine_line|#define TXFLAG_OWN         0x80000000 /* 1 = hardware, 0 = software */
DECL|macro|TXFLAG_SOP
mdefine_line|#define TXFLAG_SOP         0x40000000 /* 1 = start of packet        */
DECL|macro|TXFLAG_EOP
mdefine_line|#define TXFLAG_EOP         0x20000000 /* 1 = end of packet          */
DECL|macro|TXFLAG_CSENABLE
mdefine_line|#define TXFLAG_CSENABLE    0x10000000 /* 1 = enable hw-checksums    */
DECL|macro|TXFLAG_CSLOCATION
mdefine_line|#define TXFLAG_CSLOCATION  0x0ff00000 /* Where to stick the csum    */
DECL|macro|TXFLAG_CSBUFBEGIN
mdefine_line|#define TXFLAG_CSBUFBEGIN  0x000fc000 /* Where to begin checksum    */
DECL|macro|TXFLAG_SIZE
mdefine_line|#define TXFLAG_SIZE        0x00003fff /* Size of the packet         */
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE       32         /* Must be &gt;16 and &lt;255, multiple of 16  */
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE       32         /* see ERX_CFG_SIZE* for possible values */
DECL|macro|TX_RING_MAXSIZE
mdefine_line|#define TX_RING_MAXSIZE    256
DECL|macro|RX_RING_MAXSIZE
mdefine_line|#define RX_RING_MAXSIZE    256
multiline_comment|/* 34 byte offset for checksum computation.  This works because ip_input() will clear out&n; * the skb-&gt;csum and skb-&gt;ip_summed fields and recompute the csum if IP options are&n; * present in the header.  34 == (ethernet header len) + sizeof(struct iphdr)&n; */
DECL|macro|ERX_CFG_DEFAULT
mdefine_line|#define ERX_CFG_DEFAULT(off) (ERX_CFG_DMAENABLE|((off)&lt;&lt;3)|ERX_CFG_SIZE32|(0x22&lt;&lt;16))
DECL|macro|NEXT_RX
mdefine_line|#define NEXT_RX(num)       (((num) + 1) &amp; (RX_RING_SIZE - 1))
DECL|macro|NEXT_TX
mdefine_line|#define NEXT_TX(num)       (((num) + 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|PREV_RX
mdefine_line|#define PREV_RX(num)       (((num) - 1) &amp; (RX_RING_SIZE - 1))
DECL|macro|PREV_TX
mdefine_line|#define PREV_TX(num)       (((num) - 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL(hp)                                    &bslash;&n;        (((hp)-&gt;tx_old &lt;= (hp)-&gt;tx_new) ?                     &bslash;&n;&t;  (hp)-&gt;tx_old + (TX_RING_SIZE - 1) - (hp)-&gt;tx_new :  &bslash;&n;&t;&t;&t;    (hp)-&gt;tx_old - (hp)-&gt;tx_new - 1)
DECL|macro|RX_OFFSET
mdefine_line|#define RX_OFFSET          2
DECL|macro|RX_BUF_ALLOC_SIZE
mdefine_line|#define RX_BUF_ALLOC_SIZE  (ETH_FRAME_LEN + RX_OFFSET + (64 * 3))
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  128
DECL|struct|hmeal_init_block
r_struct
id|hmeal_init_block
(brace
DECL|member|happy_meal_rxd
r_struct
id|happy_meal_rxd
id|happy_meal_rxd
(braket
id|RX_RING_MAXSIZE
)braket
suffix:semicolon
DECL|member|happy_meal_txd
r_struct
id|happy_meal_txd
id|happy_meal_txd
(braket
id|TX_RING_MAXSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hblock_offset
mdefine_line|#define hblock_offset(mem, elem) &bslash;&n;((__u32)((unsigned long)(&amp;(((struct hmeal_init_block *)0)-&gt;mem[elem]))))
DECL|macro|SUN4C_PKT_BUF_SZ
mdefine_line|#define SUN4C_PKT_BUF_SZ&t;1546
DECL|macro|SUN4C_RX_BUFF_SIZE
mdefine_line|#define SUN4C_RX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|macro|SUN4C_TX_BUFF_SIZE
mdefine_line|#define SUN4C_TX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|struct|hmeal_buffers
r_struct
id|hmeal_buffers
(brace
DECL|member|tx_buf
r_char
id|tx_buf
(braket
id|TX_RING_SIZE
)braket
(braket
id|SUN4C_TX_BUFF_SIZE
)braket
suffix:semicolon
DECL|member|rx_buf
r_char
id|rx_buf
(braket
id|RX_RING_SIZE
)braket
(braket
id|SUN4C_RX_BUFF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hbuf_offset
mdefine_line|#define hbuf_offset(mem, elem) &bslash;&n;((__u32)((unsigned long)(&amp;(((struct hmeal_buffers *)0)-&gt;mem[elem][0]))))
multiline_comment|/* Now software state stuff. */
DECL|enum|happy_transceiver
r_enum
id|happy_transceiver
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
DECL|enum|happy_timer_state
r_enum
id|happy_timer_state
(brace
DECL|enumerator|arbwait
id|arbwait
op_assign
l_int|0
comma
multiline_comment|/* Waiting for auto negotiation to complete.          */
DECL|enumerator|lupwait
id|lupwait
op_assign
l_int|1
comma
multiline_comment|/* Auto-neg complete, awaiting link-up status.        */
DECL|enumerator|ltrywait
id|ltrywait
op_assign
l_int|2
comma
multiline_comment|/* Forcing try of all modes, from fastest to slowest. */
DECL|enumerator|asleep
id|asleep
op_assign
l_int|3
comma
multiline_comment|/* Time inactive.                                     */
)brace
suffix:semicolon
multiline_comment|/* Happy happy, joy joy! */
DECL|struct|happy_meal
r_struct
id|happy_meal
(brace
DECL|member|gregs
r_struct
id|hmeal_gregs
op_star
id|gregs
suffix:semicolon
multiline_comment|/* Happy meal global registers       */
DECL|member|etxregs
r_struct
id|hmeal_etxregs
op_star
id|etxregs
suffix:semicolon
multiline_comment|/* External transmitter regs         */
DECL|member|erxregs
r_struct
id|hmeal_erxregs
op_star
id|erxregs
suffix:semicolon
multiline_comment|/* External receiver regs            */
DECL|member|bigmacregs
r_struct
id|hmeal_bigmacregs
op_star
id|bigmacregs
suffix:semicolon
multiline_comment|/* I said NO SOLARIS with my bigmac! */
DECL|member|tcvregs
r_struct
id|hmeal_tcvregs
op_star
id|tcvregs
suffix:semicolon
multiline_comment|/* MIF transceiver regs              */
DECL|member|happy_block
r_struct
id|hmeal_init_block
op_star
id|happy_block
suffix:semicolon
multiline_comment|/* RX and TX descriptors (CPU addr)  */
DECL|member|hblock_dvma
id|__u32
id|hblock_dvma
suffix:semicolon
multiline_comment|/* DVMA visible address happy block  */
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
multiline_comment|/* We may use this for Ultra as well, will have to see, maybe not. */
DECL|member|sun4c_buffers
r_struct
id|hmeal_buffers
op_star
id|sun4c_buffers
suffix:semicolon
multiline_comment|/* CPU visible address.              */
DECL|member|s4c_buf_dvma
id|__u32
id|s4c_buf_dvma
suffix:semicolon
multiline_comment|/* DVMA visible address.             */
DECL|member|happy_flags
r_int
r_int
id|happy_flags
suffix:semicolon
multiline_comment|/* Driver state flags                */
DECL|member|tcvr_type
r_enum
id|happy_transceiver
id|tcvr_type
suffix:semicolon
multiline_comment|/* Kind of transceiver in use        */
DECL|member|happy_bursts
r_int
r_int
id|happy_bursts
suffix:semicolon
multiline_comment|/* Get your mind out of the gutter   */
DECL|member|paddr
r_int
r_int
id|paddr
suffix:semicolon
multiline_comment|/* PHY address for transceiver       */
DECL|member|hm_revision
r_int
r_int
id|hm_revision
suffix:semicolon
multiline_comment|/* Happy meal revision               */
DECL|member|sw_bmcr
r_int
r_int
id|sw_bmcr
suffix:semicolon
multiline_comment|/* SW copy of BMCR                   */
DECL|member|sw_bmsr
r_int
r_int
id|sw_bmsr
suffix:semicolon
multiline_comment|/* SW copy of BMSR                   */
DECL|member|sw_physid1
r_int
r_int
id|sw_physid1
suffix:semicolon
multiline_comment|/* SW copy of PHYSID1                */
DECL|member|sw_physid2
r_int
r_int
id|sw_physid2
suffix:semicolon
multiline_comment|/* SW copy of PHYSID2                */
DECL|member|sw_advertise
r_int
r_int
id|sw_advertise
suffix:semicolon
multiline_comment|/* SW copy of ADVERTISE              */
DECL|member|sw_lpa
r_int
r_int
id|sw_lpa
suffix:semicolon
multiline_comment|/* SW copy of LPA                    */
DECL|member|sw_expansion
r_int
r_int
id|sw_expansion
suffix:semicolon
multiline_comment|/* SW copy of EXPANSION              */
DECL|member|sw_csconfig
r_int
r_int
id|sw_csconfig
suffix:semicolon
multiline_comment|/* SW copy of CSCONFIG               */
DECL|member|auto_speed
r_int
r_int
id|auto_speed
suffix:semicolon
multiline_comment|/* Auto-nego link speed              */
DECL|member|forced_speed
r_int
r_int
id|forced_speed
suffix:semicolon
multiline_comment|/* Force mode link speed             */
DECL|member|poll_data
r_int
r_int
id|poll_data
suffix:semicolon
multiline_comment|/* MIF poll data                     */
DECL|member|poll_flag
r_int
r_int
id|poll_flag
suffix:semicolon
multiline_comment|/* MIF poll flag                     */
DECL|member|linkcheck
r_int
r_int
id|linkcheck
suffix:semicolon
multiline_comment|/* Have we checked the link yet?     */
DECL|member|lnkup
r_int
r_int
id|lnkup
suffix:semicolon
multiline_comment|/* Is the link up as far as we know? */
DECL|member|lnkdown
r_int
r_int
id|lnkdown
suffix:semicolon
multiline_comment|/* Trying to force the link down?    */
DECL|member|lnkcnt
r_int
r_int
id|lnkcnt
suffix:semicolon
multiline_comment|/* Counter for link-up attempts.     */
DECL|member|happy_timer
r_struct
id|timer_list
id|happy_timer
suffix:semicolon
multiline_comment|/* To watch the link when coming up. */
DECL|member|timer_state
r_enum
id|happy_timer_state
id|timer_state
suffix:semicolon
multiline_comment|/* State of the auto-neg timer.      */
DECL|member|timer_ticks
r_int
r_int
id|timer_ticks
suffix:semicolon
multiline_comment|/* Number of clicks at each state.   */
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
multiline_comment|/* Statistical counters              */
DECL|member|happy_sbus_dev
r_struct
id|linux_sbus_device
op_star
id|happy_sbus_dev
suffix:semicolon
multiline_comment|/* ;-)                               */
macro_line|#ifdef CONFIG_PCI
DECL|member|happy_pci_dev
r_struct
id|pci_dev
op_star
id|happy_pci_dev
suffix:semicolon
macro_line|#endif
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Backpointer                       */
DECL|member|next_module
r_struct
id|happy_meal
op_star
id|next_module
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Here are the happy flags. */
DECL|macro|HFLAG_POLL
mdefine_line|#define HFLAG_POLL                0x00000001      /* We are doing MIF polling          */
DECL|macro|HFLAG_FENABLE
mdefine_line|#define HFLAG_FENABLE             0x00000002      /* The MII frame is enabled          */
DECL|macro|HFLAG_LANCE
mdefine_line|#define HFLAG_LANCE               0x00000004      /* We are using lance-mode           */
DECL|macro|HFLAG_RXENABLE
mdefine_line|#define HFLAG_RXENABLE            0x00000008      /* Receiver is enabled               */
DECL|macro|HFLAG_AUTO
mdefine_line|#define HFLAG_AUTO                0x00000010      /* Using auto-negotiation, 0 = force */
DECL|macro|HFLAG_FULL
mdefine_line|#define HFLAG_FULL                0x00000020      /* Full duplex enable                */
DECL|macro|HFLAG_MACFULL
mdefine_line|#define HFLAG_MACFULL             0x00000040      /* Using full duplex in the MAC      */
DECL|macro|HFLAG_POLLENABLE
mdefine_line|#define HFLAG_POLLENABLE          0x00000080      /* Actually try MIF polling          */
DECL|macro|HFLAG_RXCV
mdefine_line|#define HFLAG_RXCV                0x00000100      /* XXX RXCV ENABLE                   */
DECL|macro|HFLAG_INIT
mdefine_line|#define HFLAG_INIT                0x00000200      /* Init called at least once         */
DECL|macro|HFLAG_LINKUP
mdefine_line|#define HFLAG_LINKUP              0x00000400      /* 1 = Link is up                    */
DECL|macro|HFLAG_PCI
mdefine_line|#define HFLAG_PCI                 0x00000800      /* PCI based Happy Meal              */
DECL|macro|HFLAG_20_21
mdefine_line|#define HFLAG_20_21  (HFLAG_POLLENABLE | HFLAG_FENABLE)
DECL|macro|HFLAG_NOT_A0
mdefine_line|#define HFLAG_NOT_A0 (HFLAG_POLLENABLE | HFLAG_FENABLE | HFLAG_LANCE | HFLAG_RXCV)
multiline_comment|/* We use this to acquire receive skb&squot;s that we can DMA directly into. */
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64 - 1)) &amp; ~(64 - 1)) - (unsigned long)(addr))
DECL|function|happy_meal_alloc_skb
r_static
r_inline
r_struct
id|sk_buff
op_star
id|happy_meal_alloc_skb
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
multiline_comment|/* Register/DMA access stuff, used to cope with differences between&n; * PCI and SBUS happy meals.&n; */
DECL|function|kva_to_hva
r_extern
r_inline
id|u32
id|kva_to_hva
c_func
(paren
r_struct
id|happy_meal
op_star
id|hp
comma
r_char
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|hp-&gt;happy_flags
op_amp
id|HFLAG_PCI
)paren
(brace
r_return
(paren
id|u32
)paren
id|virt_to_bus
c_func
(paren
(paren
r_volatile
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
r_return
(paren
id|u32
)paren
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|hme_read32
r_extern
r_inline
r_int
r_int
id|hme_read32
c_func
(paren
r_struct
id|happy_meal
op_star
id|hp
comma
r_volatile
r_int
r_int
op_star
id|reg
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|hp-&gt;happy_flags
op_amp
id|HFLAG_PCI
)paren
(brace
r_return
id|readl
c_func
(paren
(paren
r_int
r_int
)paren
id|reg
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
r_return
op_star
id|reg
suffix:semicolon
)brace
DECL|function|hme_write32
r_extern
r_inline
r_void
id|hme_write32
c_func
(paren
r_struct
id|happy_meal
op_star
id|hp
comma
r_volatile
r_int
r_int
op_star
id|reg
comma
r_int
r_int
id|val
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|hp-&gt;happy_flags
op_amp
id|HFLAG_PCI
)paren
(brace
id|writel
c_func
(paren
id|val
comma
(paren
r_int
r_int
)paren
id|reg
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
op_star
id|reg
op_assign
id|val
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
DECL|function|pcihme_write_rxd
r_extern
r_inline
r_void
id|pcihme_write_rxd
c_func
(paren
r_struct
id|happy_meal_rxd
op_star
id|rp
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|stwa
op_mod
l_int|3
comma
(braket
op_mod
l_int|0
)braket
op_mod
l_int|2
id|stwa
op_mod
l_int|4
comma
(braket
op_mod
l_int|1
)braket
op_mod
l_int|2
"&quot;"
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rp-&gt;rx_addr
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|rp-&gt;rx_flags
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
DECL|function|pcihme_write_txd
r_extern
r_inline
r_void
id|pcihme_write_txd
c_func
(paren
r_struct
id|happy_meal_txd
op_star
id|tp
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|stwa
op_mod
l_int|3
comma
(braket
op_mod
l_int|0
)braket
op_mod
l_int|2
id|stwa
op_mod
l_int|4
comma
(braket
op_mod
l_int|1
)braket
op_mod
l_int|2
"&quot;"
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|tp-&gt;tx_addr
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|tp-&gt;tx_flags
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PL
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* !(_SUNHME_H) */
eof
