multiline_comment|/* sunqe.h: Definitions for the Sun QuadEthernet driver.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SUNQE_H
DECL|macro|_SUNQE_H
mdefine_line|#define _SUNQE_H
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
multiline_comment|/* In MACE mode, there are four qe channels.  Each channel has it&squot;s own&n; * status bits in the QEC status register.  This macro picks out the&n; * ones you want.&n; */
DECL|macro|GLOB_STAT_PER_QE
mdefine_line|#define GLOB_STAT_PER_QE(status, channel) (((status) &gt;&gt; ((channel) * 4)) &amp; 0xf)
multiline_comment|/* The following registers are for per-qe channel information/status. */
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
multiline_comment|/* Control                   */
DECL|member|stat
r_volatile
r_int
r_int
id|stat
suffix:semicolon
multiline_comment|/* Status                    */
DECL|member|rxds
r_volatile
r_int
r_int
id|rxds
suffix:semicolon
multiline_comment|/* RX descriptor ring ptr    */
DECL|member|txds
r_volatile
r_int
r_int
id|txds
suffix:semicolon
multiline_comment|/* TX descriptor ring ptr    */
DECL|member|rimask
r_volatile
r_int
r_int
id|rimask
suffix:semicolon
multiline_comment|/* RX Interrupt Mask         */
DECL|member|timask
r_volatile
r_int
r_int
id|timask
suffix:semicolon
multiline_comment|/* TX Interrupt Mask         */
DECL|member|qmask
r_volatile
r_int
r_int
id|qmask
suffix:semicolon
multiline_comment|/* QEC Error Interrupt Mask  */
DECL|member|mmask
r_volatile
r_int
r_int
id|mmask
suffix:semicolon
multiline_comment|/* MACE Error Interrupt Mask */
DECL|member|rxwbufptr
r_volatile
r_int
r_int
id|rxwbufptr
suffix:semicolon
multiline_comment|/* Local memory rx write ptr */
DECL|member|rxrbufptr
r_volatile
r_int
r_int
id|rxrbufptr
suffix:semicolon
multiline_comment|/* Local memory rx read ptr  */
DECL|member|txwbufptr
r_volatile
r_int
r_int
id|txwbufptr
suffix:semicolon
multiline_comment|/* Local memory tx write ptr */
DECL|member|txrbufptr
r_volatile
r_int
r_int
id|txrbufptr
suffix:semicolon
multiline_comment|/* Local memory tx read ptr  */
DECL|member|ccnt
r_volatile
r_int
r_int
id|ccnt
suffix:semicolon
multiline_comment|/* Collision Counter         */
DECL|member|pipg
r_volatile
r_int
r_int
id|pipg
suffix:semicolon
multiline_comment|/* Inter-Frame Gap           */
)brace
suffix:semicolon
DECL|macro|CREG_CTRL_RXOFF
mdefine_line|#define CREG_CTRL_RXOFF       0x00000004  /* Disable this qe&squot;s receiver*/
DECL|macro|CREG_CTRL_RESET
mdefine_line|#define CREG_CTRL_RESET       0x00000002  /* Reset this qe channel     */
DECL|macro|CREG_CTRL_TWAKEUP
mdefine_line|#define CREG_CTRL_TWAKEUP     0x00000001  /* Transmitter Wakeup, &squot;go&squot;. */
DECL|macro|CREG_STAT_EDEFER
mdefine_line|#define CREG_STAT_EDEFER      0x10000000  /* Excessive Defers          */
DECL|macro|CREG_STAT_CLOSS
mdefine_line|#define CREG_STAT_CLOSS       0x08000000  /* Carrier Loss              */
DECL|macro|CREG_STAT_ERETRIES
mdefine_line|#define CREG_STAT_ERETRIES    0x04000000  /* More than 16 retries      */
DECL|macro|CREG_STAT_LCOLL
mdefine_line|#define CREG_STAT_LCOLL       0x02000000  /* Late TX Collision         */
DECL|macro|CREG_STAT_FUFLOW
mdefine_line|#define CREG_STAT_FUFLOW      0x01000000  /* FIFO Underflow            */
DECL|macro|CREG_STAT_JERROR
mdefine_line|#define CREG_STAT_JERROR      0x00800000  /* Jabber Error              */
DECL|macro|CREG_STAT_BERROR
mdefine_line|#define CREG_STAT_BERROR      0x00400000  /* Babble Error              */
DECL|macro|CREG_STAT_TXIRQ
mdefine_line|#define CREG_STAT_TXIRQ       0x00200000  /* Transmit Interrupt        */
DECL|macro|CREG_STAT_CCOFLOW
mdefine_line|#define CREG_STAT_CCOFLOW     0x00100000  /* TX Coll-counter Overflow  */
DECL|macro|CREG_STAT_TXDERROR
mdefine_line|#define CREG_STAT_TXDERROR    0x00080000  /* TX Descriptor is bogus    */
DECL|macro|CREG_STAT_TXLERR
mdefine_line|#define CREG_STAT_TXLERR      0x00040000  /* Late Transmit Error       */
DECL|macro|CREG_STAT_TXPERR
mdefine_line|#define CREG_STAT_TXPERR      0x00020000  /* Transmit Parity Error     */
DECL|macro|CREG_STAT_TXSERR
mdefine_line|#define CREG_STAT_TXSERR      0x00010000  /* Transmit SBUS error ack   */
DECL|macro|CREG_STAT_RCCOFLOW
mdefine_line|#define CREG_STAT_RCCOFLOW    0x00001000  /* RX Coll-counter Overflow  */
DECL|macro|CREG_STAT_RUOFLOW
mdefine_line|#define CREG_STAT_RUOFLOW     0x00000800  /* Runt Counter Overflow     */
DECL|macro|CREG_STAT_MCOFLOW
mdefine_line|#define CREG_STAT_MCOFLOW     0x00000400  /* Missed Counter Overflow   */
DECL|macro|CREG_STAT_RXFOFLOW
mdefine_line|#define CREG_STAT_RXFOFLOW    0x00000200  /* RX FIFO Overflow          */
DECL|macro|CREG_STAT_RLCOLL
mdefine_line|#define CREG_STAT_RLCOLL      0x00000100  /* RX Late Collision         */
DECL|macro|CREG_STAT_FCOFLOW
mdefine_line|#define CREG_STAT_FCOFLOW     0x00000080  /* Frame Counter Overflow    */
DECL|macro|CREG_STAT_CECOFLOW
mdefine_line|#define CREG_STAT_CECOFLOW    0x00000040  /* CRC Error-counter Overflow*/
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
mdefine_line|#define CREG_STAT_ERRORS      (CREG_STAT_EDEFER|CREG_STAT_CLOSS|CREG_STAT_ERETRIES|     &bslash;&n;&t;&t;&t;       CREG_STAT_LCOLL|CREG_STAT_FUFLOW|CREG_STAT_JERROR|       &bslash;&n;&t;&t;&t;       CREG_STAT_BERROR|CREG_STAT_CCOFLOW|CREG_STAT_TXDERROR|   &bslash;&n;&t;&t;&t;       CREG_STAT_TXLERR|CREG_STAT_TXPERR|CREG_STAT_TXSERR|      &bslash;&n;&t;&t;&t;       CREG_STAT_RCCOFLOW|CREG_STAT_RUOFLOW|CREG_STAT_MCOFLOW| &bslash;&n;&t;&t;&t;       CREG_STAT_RXFOFLOW|CREG_STAT_RLCOLL|CREG_STAT_FCOFLOW|   &bslash;&n;&t;&t;&t;       CREG_STAT_CECOFLOW|CREG_STAT_RXDROP|CREG_STAT_RXSMALL|   &bslash;&n;&t;&t;&t;       CREG_STAT_RXLERR|CREG_STAT_RXPERR|CREG_STAT_RXSERR)
DECL|macro|CREG_QMASK_COFLOW
mdefine_line|#define CREG_QMASK_COFLOW     0x00100000  /* CollCntr overflow         */
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
DECL|macro|CREG_MMASK_EDEFER
mdefine_line|#define CREG_MMASK_EDEFER     0x10000000  /* Excess defer              */
DECL|macro|CREG_MMASK_CLOSS
mdefine_line|#define CREG_MMASK_CLOSS      0x08000000  /* Carrier loss              */
DECL|macro|CREG_MMASK_ERETRY
mdefine_line|#define CREG_MMASK_ERETRY     0x04000000  /* Excess retry              */
DECL|macro|CREG_MMASK_LCOLL
mdefine_line|#define CREG_MMASK_LCOLL      0x02000000  /* Late collision error      */
DECL|macro|CREG_MMASK_UFLOW
mdefine_line|#define CREG_MMASK_UFLOW      0x01000000  /* Underflow                 */
DECL|macro|CREG_MMASK_JABBER
mdefine_line|#define CREG_MMASK_JABBER     0x00800000  /* Jabber error              */
DECL|macro|CREG_MMASK_BABBLE
mdefine_line|#define CREG_MMASK_BABBLE     0x00400000  /* Babble error              */
DECL|macro|CREG_MMASK_OFLOW
mdefine_line|#define CREG_MMASK_OFLOW      0x00000800  /* Overflow                  */
DECL|macro|CREG_MMASK_RXCOLL
mdefine_line|#define CREG_MMASK_RXCOLL     0x00000400  /* RX Coll-Cntr overflow     */
DECL|macro|CREG_MMASK_RPKT
mdefine_line|#define CREG_MMASK_RPKT       0x00000200  /* Runt pkt overflow         */
DECL|macro|CREG_MMASK_MPKT
mdefine_line|#define CREG_MMASK_MPKT       0x00000100  /* Missed pkt overflow       */
DECL|macro|CREG_PIPG_TENAB
mdefine_line|#define CREG_PIPG_TENAB       0x00000020  /* Enable Throttle           */
DECL|macro|CREG_PIPG_MMODE
mdefine_line|#define CREG_PIPG_MMODE       0x00000010  /* Manual Mode               */
DECL|macro|CREG_PIPG_WMASK
mdefine_line|#define CREG_PIPG_WMASK       0x0000000f  /* SBUS Wait Mask            */
multiline_comment|/* Per-channel AMD 79C940 MACE registers. */
DECL|struct|qe_mregs
r_struct
id|qe_mregs
(brace
DECL|member|rxfifo
r_volatile
r_int
r_char
id|rxfifo
suffix:semicolon
multiline_comment|/* Receive FIFO                   */
DECL|member|txfifo
r_volatile
r_int
r_char
id|txfifo
suffix:semicolon
multiline_comment|/* Transmit FIFO                  */
DECL|member|txfcntl
r_volatile
r_int
r_char
id|txfcntl
suffix:semicolon
multiline_comment|/* Transmit Frame Control         */
DECL|member|txfstat
r_volatile
r_int
r_char
id|txfstat
suffix:semicolon
multiline_comment|/* Transmit Frame Status          */
DECL|member|txrcnt
r_volatile
r_int
r_char
id|txrcnt
suffix:semicolon
multiline_comment|/* Transmit Retry Count           */
DECL|member|rxfcntl
r_volatile
r_int
r_char
id|rxfcntl
suffix:semicolon
multiline_comment|/* Receive Frame Control          */
DECL|member|rxfstat
r_volatile
r_int
r_char
id|rxfstat
suffix:semicolon
multiline_comment|/* Receive Frame Status           */
DECL|member|ffcnt
r_volatile
r_int
r_char
id|ffcnt
suffix:semicolon
multiline_comment|/* FIFO Frame Count               */
DECL|member|ireg
r_volatile
r_int
r_char
id|ireg
suffix:semicolon
multiline_comment|/* Interrupt Register             */
DECL|member|imask
r_volatile
r_int
r_char
id|imask
suffix:semicolon
multiline_comment|/* Interrupt Mask                 */
DECL|member|poll
r_volatile
r_int
r_char
id|poll
suffix:semicolon
multiline_comment|/* POLL Register                  */
DECL|member|bconfig
r_volatile
r_int
r_char
id|bconfig
suffix:semicolon
multiline_comment|/* BIU Config                     */
DECL|member|fconfig
r_volatile
r_int
r_char
id|fconfig
suffix:semicolon
multiline_comment|/* FIFO Config                    */
DECL|member|mconfig
r_volatile
r_int
r_char
id|mconfig
suffix:semicolon
multiline_comment|/* MAC Config                     */
DECL|member|plsconfig
r_volatile
r_int
r_char
id|plsconfig
suffix:semicolon
multiline_comment|/* PLS Config                     */
DECL|member|phyconfig
r_volatile
r_int
r_char
id|phyconfig
suffix:semicolon
multiline_comment|/* PHY Config                     */
DECL|member|chipid1
r_volatile
r_int
r_char
id|chipid1
suffix:semicolon
multiline_comment|/* Chip-ID, low bits              */
DECL|member|chipid2
r_volatile
r_int
r_char
id|chipid2
suffix:semicolon
multiline_comment|/* Chip-ID, high bits             */
DECL|member|iaconfig
r_volatile
r_int
r_char
id|iaconfig
suffix:semicolon
multiline_comment|/* Internal Address Config        */
DECL|member|_unused0
r_volatile
r_int
r_char
id|_unused0
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|filter
r_volatile
r_int
r_char
id|filter
suffix:semicolon
multiline_comment|/* Logical Address Filter         */
DECL|member|ethaddr
r_volatile
r_int
r_char
id|ethaddr
suffix:semicolon
multiline_comment|/* Our Ethernet Address           */
DECL|member|_unused1
r_volatile
r_int
r_char
id|_unused1
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|_unused2
r_volatile
r_int
r_char
id|_unused2
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|mpcnt
r_volatile
r_int
r_char
id|mpcnt
suffix:semicolon
multiline_comment|/* Missed Packet Count            */
DECL|member|_unused3
r_volatile
r_int
r_char
id|_unused3
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|rpcnt
r_volatile
r_int
r_char
id|rpcnt
suffix:semicolon
multiline_comment|/* Runt Packet Count              */
DECL|member|rccnt
r_volatile
r_int
r_char
id|rccnt
suffix:semicolon
multiline_comment|/* RX Collision Count             */
DECL|member|_unused4
r_volatile
r_int
r_char
id|_unused4
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|utest
r_volatile
r_int
r_char
id|utest
suffix:semicolon
multiline_comment|/* User Test                      */
DECL|member|rtest1
r_volatile
r_int
r_char
id|rtest1
suffix:semicolon
multiline_comment|/* Reserved Test 1                */
DECL|member|rtest2
r_volatile
r_int
r_char
id|rtest2
suffix:semicolon
multiline_comment|/* Reserved Test 2                */
)brace
suffix:semicolon
DECL|macro|MREGS_TXFCNTL_DRETRY
mdefine_line|#define MREGS_TXFCNTL_DRETRY        0x80 /* Retry disable                  */
DECL|macro|MREGS_TXFCNTL_DFCS
mdefine_line|#define MREGS_TXFCNTL_DFCS          0x08 /* Disable TX FCS                 */
DECL|macro|MREGS_TXFCNTL_AUTOPAD
mdefine_line|#define MREGS_TXFCNTL_AUTOPAD       0x01 /* TX auto pad                    */
DECL|macro|MREGS_TXFSTAT_VALID
mdefine_line|#define MREGS_TXFSTAT_VALID         0x80 /* TX valid                       */
DECL|macro|MREGS_TXFSTAT_UNDERFLOW
mdefine_line|#define MREGS_TXFSTAT_UNDERFLOW     0x40 /* TX underflow                   */
DECL|macro|MREGS_TXFSTAT_LCOLL
mdefine_line|#define MREGS_TXFSTAT_LCOLL         0x20 /* TX late collision              */
DECL|macro|MREGS_TXFSTAT_MRETRY
mdefine_line|#define MREGS_TXFSTAT_MRETRY        0x10 /* TX &gt; 1 retries                 */
DECL|macro|MREGS_TXFSTAT_ORETRY
mdefine_line|#define MREGS_TXFSTAT_ORETRY        0x08 /* TX 1 retry                     */
DECL|macro|MREGS_TXFSTAT_PDEFER
mdefine_line|#define MREGS_TXFSTAT_PDEFER        0x04 /* TX pkt deferred                */
DECL|macro|MREGS_TXFSTAT_CLOSS
mdefine_line|#define MREGS_TXFSTAT_CLOSS         0x02 /* TX carrier lost                */
DECL|macro|MREGS_TXFSTAT_RERROR
mdefine_line|#define MREGS_TXFSTAT_RERROR        0x01 /* TX retry error                 */
DECL|macro|MREGS_TXRCNT_EDEFER
mdefine_line|#define MREGS_TXRCNT_EDEFER         0x80 /* TX Excess defers               */
DECL|macro|MREGS_TXRCNT_CMASK
mdefine_line|#define MREGS_TXRCNT_CMASK          0x0f /* TX retry count                 */
DECL|macro|MREGS_RXFCNTL_LOWLAT
mdefine_line|#define MREGS_RXFCNTL_LOWLAT        0x08 /* RX low latency                 */
DECL|macro|MREGS_RXFCNTL_AREJECT
mdefine_line|#define MREGS_RXFCNTL_AREJECT       0x04 /* RX addr match rej              */
DECL|macro|MREGS_RXFCNTL_AUTOSTRIP
mdefine_line|#define MREGS_RXFCNTL_AUTOSTRIP     0x01 /* RX auto strip                  */
DECL|macro|MREGS_RXFSTAT_OVERFLOW
mdefine_line|#define MREGS_RXFSTAT_OVERFLOW      0x80 /* RX overflow                    */
DECL|macro|MREGS_RXFSTAT_LCOLL
mdefine_line|#define MREGS_RXFSTAT_LCOLL         0x40 /* RX late collision              */
DECL|macro|MREGS_RXFSTAT_FERROR
mdefine_line|#define MREGS_RXFSTAT_FERROR        0x20 /* RX framing error               */
DECL|macro|MREGS_RXFSTAT_FCSERROR
mdefine_line|#define MREGS_RXFSTAT_FCSERROR      0x10 /* RX FCS error                   */
DECL|macro|MREGS_RXFSTAT_RBCNT
mdefine_line|#define MREGS_RXFSTAT_RBCNT         0x0f /* RX msg byte count              */
DECL|macro|MREGS_FFCNT_RX
mdefine_line|#define MREGS_FFCNT_RX              0xf0 /* RX FIFO frame cnt              */
DECL|macro|MREGS_FFCNT_TX
mdefine_line|#define MREGS_FFCNT_TX              0x0f /* TX FIFO frame cnt              */
DECL|macro|MREGS_IREG_JABBER
mdefine_line|#define MREGS_IREG_JABBER           0x80 /* IRQ Jabber error               */
DECL|macro|MREGS_IREG_BABBLE
mdefine_line|#define MREGS_IREG_BABBLE           0x40 /* IRQ Babble error               */
DECL|macro|MREGS_IREG_COLL
mdefine_line|#define MREGS_IREG_COLL             0x20 /* IRQ Collision error            */
DECL|macro|MREGS_IREG_RCCO
mdefine_line|#define MREGS_IREG_RCCO             0x10 /* IRQ Collision cnt overflow     */
DECL|macro|MREGS_IREG_RPKTCO
mdefine_line|#define MREGS_IREG_RPKTCO           0x08 /* IRQ Runt packet count overflow */
DECL|macro|MREGS_IREG_MPKTCO
mdefine_line|#define MREGS_IREG_MPKTCO           0x04 /* IRQ missed packet cnt overflow */
DECL|macro|MREGS_IREG_RXIRQ
mdefine_line|#define MREGS_IREG_RXIRQ            0x02 /* IRQ RX&squot;d a packet              */
DECL|macro|MREGS_IREG_TXIRQ
mdefine_line|#define MREGS_IREG_TXIRQ            0x01 /* IRQ TX&squot;d a packet              */
DECL|macro|MREGS_IMASK_BABBLE
mdefine_line|#define MREGS_IMASK_BABBLE          0x40 /* IMASK Babble errors            */
DECL|macro|MREGS_IMASK_COLL
mdefine_line|#define MREGS_IMASK_COLL            0x20 /* IMASK Collision errors         */
DECL|macro|MREGS_IMASK_MPKTCO
mdefine_line|#define MREGS_IMASK_MPKTCO          0x04 /* IMASK Missed pkt cnt overflow  */
DECL|macro|MREGS_IMASK_RXIRQ
mdefine_line|#define MREGS_IMASK_RXIRQ           0x02 /* IMASK RX interrupts            */
DECL|macro|MREGS_IMASK_TXIRQ
mdefine_line|#define MREGS_IMASK_TXIRQ           0x01 /* IMASK TX interrupts            */
DECL|macro|MREGS_POLL_TXVALID
mdefine_line|#define MREGS_POLL_TXVALID          0x80 /* TX is valid                    */
DECL|macro|MREGS_POLL_TDTR
mdefine_line|#define MREGS_POLL_TDTR             0x40 /* TX data transfer request       */
DECL|macro|MREGS_POLL_RDTR
mdefine_line|#define MREGS_POLL_RDTR             0x20 /* RX data transfer request       */
DECL|macro|MREGS_BCONFIG_BSWAP
mdefine_line|#define MREGS_BCONFIG_BSWAP         0x40 /* Byte Swap                      */
DECL|macro|MREGS_BCONFIG_4TS
mdefine_line|#define MREGS_BCONFIG_4TS           0x00 /* 4byte transmit start point     */
DECL|macro|MREGS_BCONFIG_16TS
mdefine_line|#define MREGS_BCONFIG_16TS          0x10 /* 16byte transmit start point    */
DECL|macro|MREGS_BCONFIG_64TS
mdefine_line|#define MREGS_BCONFIG_64TS          0x20 /* 64byte transmit start point    */
DECL|macro|MREGS_BCONFIG_112TS
mdefine_line|#define MREGS_BCONFIG_112TS         0x30 /* 112byte transmit start point   */
DECL|macro|MREGS_BCONFIG_RESET
mdefine_line|#define MREGS_BCONFIG_RESET         0x01 /* SW-Reset the MACE              */
DECL|macro|MREGS_FCONFIG_TXF8
mdefine_line|#define MREGS_FCONFIG_TXF8          0x00 /* TX fifo 8 write cycles         */
DECL|macro|MREGS_FCONFIG_TXF32
mdefine_line|#define MREGS_FCONFIG_TXF32         0x80 /* TX fifo 32 write cycles        */
DECL|macro|MREGS_FCONFIG_TXF16
mdefine_line|#define MREGS_FCONFIG_TXF16         0x40 /* TX fifo 16 write cycles        */
DECL|macro|MREGS_FCONFIG_RXF64
mdefine_line|#define MREGS_FCONFIG_RXF64         0x20 /* RX fifo 64 write cycles        */
DECL|macro|MREGS_FCONFIG_RXF32
mdefine_line|#define MREGS_FCONFIG_RXF32         0x10 /* RX fifo 32 write cycles        */
DECL|macro|MREGS_FCONFIG_RXF16
mdefine_line|#define MREGS_FCONFIG_RXF16         0x00 /* RX fifo 16 write cycles        */
DECL|macro|MREGS_FCONFIG_TFWU
mdefine_line|#define MREGS_FCONFIG_TFWU          0x08 /* TX fifo watermark update       */
DECL|macro|MREGS_FCONFIG_RFWU
mdefine_line|#define MREGS_FCONFIG_RFWU          0x04 /* RX fifo watermark update       */
DECL|macro|MREGS_FCONFIG_TBENAB
mdefine_line|#define MREGS_FCONFIG_TBENAB        0x02 /* TX burst enable                */
DECL|macro|MREGS_FCONFIG_RBENAB
mdefine_line|#define MREGS_FCONFIG_RBENAB        0x01 /* RX burst enable                */
DECL|macro|MREGS_MCONFIG_PROMISC
mdefine_line|#define MREGS_MCONFIG_PROMISC       0x80 /* Promiscuous mode enable        */
DECL|macro|MREGS_MCONFIG_TPDDISAB
mdefine_line|#define MREGS_MCONFIG_TPDDISAB      0x40 /* TX 2part deferral enable       */
DECL|macro|MREGS_MCONFIG_MBAENAB
mdefine_line|#define MREGS_MCONFIG_MBAENAB       0x20 /* Modified backoff enable        */
DECL|macro|MREGS_MCONFIG_RPADISAB
mdefine_line|#define MREGS_MCONFIG_RPADISAB      0x08 /* RX physical addr disable       */
DECL|macro|MREGS_MCONFIG_RBDISAB
mdefine_line|#define MREGS_MCONFIG_RBDISAB       0x04 /* RX broadcast disable           */
DECL|macro|MREGS_MCONFIG_TXENAB
mdefine_line|#define MREGS_MCONFIG_TXENAB        0x02 /* Enable transmitter             */
DECL|macro|MREGS_MCONFIG_RXENAB
mdefine_line|#define MREGS_MCONFIG_RXENAB        0x01 /* Enable receiver                */
DECL|macro|MREGS_PLSCONFIG_TXMS
mdefine_line|#define MREGS_PLSCONFIG_TXMS        0x08 /* TX mode select                 */
DECL|macro|MREGS_PLSCONFIG_GPSI
mdefine_line|#define MREGS_PLSCONFIG_GPSI        0x06 /* Use GPSI connector             */
DECL|macro|MREGS_PLSCONFIG_DAI
mdefine_line|#define MREGS_PLSCONFIG_DAI         0x04 /* Use DAI connector              */
DECL|macro|MREGS_PLSCONFIG_TP
mdefine_line|#define MREGS_PLSCONFIG_TP          0x02 /* Use TwistedPair connector      */
DECL|macro|MREGS_PLSCONFIG_AUI
mdefine_line|#define MREGS_PLSCONFIG_AUI         0x00 /* Use AUI connector              */
DECL|macro|MREGS_PLSCONFIG_IOENAB
mdefine_line|#define MREGS_PLSCONFIG_IOENAB      0x01 /* PLS I/O enable                 */
DECL|macro|MREGS_PHYCONFIG_LSTAT
mdefine_line|#define MREGS_PHYCONFIG_LSTAT       0x80 /* Link status                    */
DECL|macro|MREGS_PHYCONFIG_LTESTDIS
mdefine_line|#define MREGS_PHYCONFIG_LTESTDIS    0x40 /* Disable link test logic        */
DECL|macro|MREGS_PHYCONFIG_RXPOLARITY
mdefine_line|#define MREGS_PHYCONFIG_RXPOLARITY  0x20 /* RX polarity                    */
DECL|macro|MREGS_PHYCONFIG_APCDISAB
mdefine_line|#define MREGS_PHYCONFIG_APCDISAB    0x10 /* AutoPolarityCorrect disab      */
DECL|macro|MREGS_PHYCONFIG_LTENAB
mdefine_line|#define MREGS_PHYCONFIG_LTENAB      0x08 /* Select low threshold           */
DECL|macro|MREGS_PHYCONFIG_AUTO
mdefine_line|#define MREGS_PHYCONFIG_AUTO        0x04 /* Connector port auto-sel        */
DECL|macro|MREGS_PHYCONFIG_RWU
mdefine_line|#define MREGS_PHYCONFIG_RWU         0x02 /* Remote WakeUp                  */
DECL|macro|MREGS_PHYCONFIG_AW
mdefine_line|#define MREGS_PHYCONFIG_AW          0x01 /* Auto Wakeup                    */
DECL|macro|MREGS_IACONFIG_ACHNGE
mdefine_line|#define MREGS_IACONFIG_ACHNGE       0x80 /* Do address change              */
DECL|macro|MREGS_IACONFIG_PARESET
mdefine_line|#define MREGS_IACONFIG_PARESET      0x04 /* Physical address reset         */
DECL|macro|MREGS_IACONFIG_LARESET
mdefine_line|#define MREGS_IACONFIG_LARESET      0x02 /* Logical address reset          */
DECL|macro|MREGS_UTEST_RTRENAB
mdefine_line|#define MREGS_UTEST_RTRENAB         0x80 /* Enable resv test register      */
DECL|macro|MREGS_UTEST_RTRDISAB
mdefine_line|#define MREGS_UTEST_RTRDISAB        0x40 /* Disab resv test register       */
DECL|macro|MREGS_UTEST_RPACCEPT
mdefine_line|#define MREGS_UTEST_RPACCEPT        0x20 /* Accept runt packets            */
DECL|macro|MREGS_UTEST_FCOLL
mdefine_line|#define MREGS_UTEST_FCOLL           0x10 /* Force collision status         */
DECL|macro|MREGS_UTEST_FCSENAB
mdefine_line|#define MREGS_UTEST_FCSENAB         0x08 /* Enable FCS on RX               */
DECL|macro|MREGS_UTEST_INTLOOPM
mdefine_line|#define MREGS_UTEST_INTLOOPM        0x06 /* Intern lpback w/MENDEC         */
DECL|macro|MREGS_UTEST_INTLOOP
mdefine_line|#define MREGS_UTEST_INTLOOP         0x04 /* Intern lpback                  */
DECL|macro|MREGS_UTEST_EXTLOOP
mdefine_line|#define MREGS_UTEST_EXTLOOP         0x02 /* Extern lpback                  */
DECL|macro|MREGS_UTEST_NOLOOP
mdefine_line|#define MREGS_UTEST_NOLOOP          0x00 /* No loopback                    */
DECL|struct|qe_rxd
r_struct
id|qe_rxd
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
DECL|struct|qe_txd
r_struct
id|qe_txd
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
mdefine_line|#define TX_BUFFS_AVAIL(qp)                                    &bslash;&n;        (((qp)-&gt;tx_old &lt;= (qp)-&gt;tx_new) ?                     &bslash;&n;&t;  (qp)-&gt;tx_old + (TX_RING_SIZE - 1) - (qp)-&gt;tx_new :  &bslash;&n;&t;&t;&t;    (qp)-&gt;tx_old - (qp)-&gt;tx_new - 1)
DECL|macro|SUN4C_TX_BUFFS_AVAIL
mdefine_line|#define SUN4C_TX_BUFFS_AVAIL(qp)                                    &bslash;&n;        (((qp)-&gt;tx_old &lt;= (qp)-&gt;tx_new) ?                           &bslash;&n;&t;  (qp)-&gt;tx_old + (SUN4C_TX_RING_SIZE - 1) - (qp)-&gt;tx_new :  &bslash;&n;&t;  (qp)-&gt;tx_old - (qp)-&gt;tx_new - (TX_RING_SIZE - SUN4C_TX_RING_SIZE))
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  128
DECL|macro|RX_BUF_ALLOC_SIZE
mdefine_line|#define RX_BUF_ALLOC_SIZE  (ETH_FRAME_LEN + (64 * 3))
DECL|struct|qe_init_block
r_struct
id|qe_init_block
(brace
DECL|member|qe_rxd
r_struct
id|qe_rxd
id|qe_rxd
(braket
id|RX_RING_MAXSIZE
)braket
suffix:semicolon
DECL|member|qe_txd
r_struct
id|qe_txd
id|qe_txd
(braket
id|TX_RING_MAXSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|sunqe
suffix:semicolon
DECL|struct|sunqec
r_struct
id|sunqec
(brace
DECL|member|gregs
r_struct
id|qe_globreg
op_star
id|gregs
suffix:semicolon
multiline_comment|/* QEC Global Registers         */
DECL|member|qes
r_struct
id|sunqe
op_star
id|qes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qec_bursts
r_int
r_int
id|qec_bursts
suffix:semicolon
DECL|member|qec_sbus_dev
r_struct
id|linux_sbus_device
op_star
id|qec_sbus_dev
suffix:semicolon
DECL|member|next_module
r_struct
id|sunqec
op_star
id|next_module
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUN4C_PKT_BUF_SZ
mdefine_line|#define SUN4C_PKT_BUF_SZ&t;1544
DECL|macro|SUN4C_RX_BUFF_SIZE
mdefine_line|#define SUN4C_RX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|macro|SUN4C_TX_BUFF_SIZE
mdefine_line|#define SUN4C_TX_BUFF_SIZE&t;SUN4C_PKT_BUF_SZ
DECL|macro|SUN4C_RX_RING_SIZE
mdefine_line|#define SUN4C_RX_RING_SIZE&t;16
DECL|macro|SUN4C_TX_RING_SIZE
mdefine_line|#define SUN4C_TX_RING_SIZE&t;16
DECL|struct|sunqe_buffers
r_struct
id|sunqe_buffers
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
DECL|macro|SUN4C_NEXT_RX
mdefine_line|#define SUN4C_NEXT_RX(num)&t;(((num) + 1) &amp; (SUN4C_RX_RING_SIZE - 1))
DECL|macro|SUN4C_NEXT_TX
mdefine_line|#define SUN4C_NEXT_TX(num)&t;(((num) + 1) &amp; (SUN4C_TX_RING_SIZE - 1))
DECL|macro|SUN4C_PREV_RX
mdefine_line|#define SUN4C_PREV_RX(num)&t;(((num) - 1) &amp; (SUN4C_RX_RING_SIZE - 1))
DECL|macro|SUN4C_PREV_TX
mdefine_line|#define SUN4C_PREV_TX(num)&t;(((num) - 1) &amp; (SUN4C_TX_RING_SIZE - 1))
DECL|struct|sunqe
r_struct
id|sunqe
(brace
DECL|member|qcregs
r_struct
id|qe_creg
op_star
id|qcregs
suffix:semicolon
multiline_comment|/* QEC per-channel Registers      */
DECL|member|mregs
r_struct
id|qe_mregs
op_star
id|mregs
suffix:semicolon
multiline_comment|/* Per-channel MACE Registers     */
DECL|member|qe_block
r_struct
id|qe_init_block
op_star
id|qe_block
suffix:semicolon
multiline_comment|/* RX and TX descriptors          */
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
id|sunqe_buffers
op_star
id|sun4c_buffers
suffix:semicolon
DECL|member|parent
r_struct
id|sunqec
op_star
id|parent
suffix:semicolon
DECL|member|enet_stats
r_struct
id|enet_statistics
id|enet_stats
suffix:semicolon
multiline_comment|/* Statistical counters               */
DECL|member|qe_sbusdev
r_struct
id|linux_sbus_device
op_star
id|qe_sbusdev
suffix:semicolon
multiline_comment|/* QE&squot;s SBUS device struct            */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* QE&squot;s netdevice struct              */
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* Who am I?                          */
)brace
suffix:semicolon
multiline_comment|/* We use this to acquire receive skb&squot;s that we can DMA directly into. */
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64 - 1)) &amp; ~(64 - 1)) - (unsigned long)(addr))
DECL|function|qe_alloc_skb
r_static
r_inline
r_struct
id|sk_buff
op_star
id|qe_alloc_skb
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
macro_line|#endif /* !(_SUNQE_H) */
eof
