multiline_comment|/* $Id: scc.h,v 1.26 1996/10/09 16:35:56 jreuter Exp jreuter $ */
macro_line|#ifndef&t;_SCC_H
DECL|macro|_SCC_H
mdefine_line|#define&t;_SCC_H
macro_line|#include &lt;linux/if_ether.h&gt;
multiline_comment|/* selection of hardware types */
DECL|macro|PA0HZP
mdefine_line|#define PA0HZP&t;&t;0x00&t;/* hardware type for PA0HZP SCC card and compatible */
DECL|macro|EAGLE
mdefine_line|#define EAGLE         &t;0x01    /* hardware type for EAGLE card */
DECL|macro|PC100
mdefine_line|#define PC100&t;&t;0x02&t;/* hardware type for PC100 card */
DECL|macro|PRIMUS
mdefine_line|#define PRIMUS&t;&t;0x04&t;/* hardware type for PRIMUS-PC (DG9BL) card */
DECL|macro|DRSI
mdefine_line|#define DRSI&t;&t;0x08&t;/* hardware type for DRSI PC*Packet card */
DECL|macro|BAYCOM
mdefine_line|#define BAYCOM&t;&t;0x10&t;/* hardware type for BayCom (U)SCC */
multiline_comment|/* Paranoia check... */
DECL|macro|SCC_PARANOIA_CHECK
mdefine_line|#define SCC_PARANOIA_CHECK&t;/* tell the user if something is going wrong */
multiline_comment|/* DEV ioctl() commands */
DECL|macro|SIOCSCCRESERVED
mdefine_line|#define SIOCSCCRESERVED (SIOCDEVPRIVATE+0)
DECL|macro|SIOCSCCCFG
mdefine_line|#define SIOCSCCCFG&t;(SIOCDEVPRIVATE+1)
DECL|macro|SIOCSCCINI
mdefine_line|#define SIOCSCCINI&t;(SIOCDEVPRIVATE+2)
DECL|macro|SIOCSCCCHANINI
mdefine_line|#define SIOCSCCCHANINI&t;(SIOCDEVPRIVATE+3)
DECL|macro|SIOCSCCSMEM
mdefine_line|#define SIOCSCCSMEM&t;(SIOCDEVPRIVATE+4)
DECL|macro|SIOCSCCGKISS
mdefine_line|#define SIOCSCCGKISS&t;(SIOCDEVPRIVATE+5)
DECL|macro|SIOCSCCSKISS
mdefine_line|#define SIOCSCCSKISS&t;(SIOCDEVPRIVATE+6)
DECL|macro|SIOCSCCGSTAT
mdefine_line|#define SIOCSCCGSTAT&t;(SIOCDEVPRIVATE+7)
multiline_comment|/* magic number */
DECL|macro|SCC_MAGIC
mdefine_line|#define SCC_MAGIC&t;0x8530&t;&t;/* ;-) */
multiline_comment|/* KISS state machine */
DECL|macro|KISS_IDLE
mdefine_line|#define&t;KISS_IDLE&t;0
DECL|macro|KISS_DATA
mdefine_line|#define KISS_DATA&t;1
DECL|macro|KISS_ESCAPE
mdefine_line|#define KISS_ESCAPE&t;2
DECL|macro|KISS_RXFRAME
mdefine_line|#define KISS_RXFRAME&t;3
multiline_comment|/* Device parameter control (from WAMPES) */
DECL|macro|PARAM_TXDELAY
mdefine_line|#define&t;PARAM_TXDELAY&t;1
DECL|macro|PARAM_PERSIST
mdefine_line|#define&t;PARAM_PERSIST&t;2
DECL|macro|PARAM_SLOTTIME
mdefine_line|#define&t;PARAM_SLOTTIME&t;3
DECL|macro|PARAM_TXTAIL
mdefine_line|#define&t;PARAM_TXTAIL&t;4
DECL|macro|PARAM_FULLDUP
mdefine_line|#define&t;PARAM_FULLDUP&t;5
DECL|macro|PARAM_SOFTDCD
mdefine_line|#define PARAM_SOFTDCD&t;6&t;/* was: PARAM_HW */
DECL|macro|PARAM_MUTE
mdefine_line|#define PARAM_MUTE&t;7&t;/* ??? */
DECL|macro|PARAM_DTR
mdefine_line|#define PARAM_DTR       8
DECL|macro|PARAM_RTS
mdefine_line|#define PARAM_RTS&t;9
DECL|macro|PARAM_SPEED
mdefine_line|#define PARAM_SPEED     10
DECL|macro|PARAM_ENDDELAY
mdefine_line|#define PARAM_ENDDELAY&t;11&t;/* ??? */
DECL|macro|PARAM_GROUP
mdefine_line|#define PARAM_GROUP     12
DECL|macro|PARAM_IDLE
mdefine_line|#define PARAM_IDLE      13
DECL|macro|PARAM_MIN
mdefine_line|#define PARAM_MIN       14
DECL|macro|PARAM_MAXKEY
mdefine_line|#define&t;PARAM_MAXKEY&t;15
DECL|macro|PARAM_WAIT
mdefine_line|#define PARAM_WAIT      16
DECL|macro|PARAM_MAXDEFER
mdefine_line|#define PARAM_MAXDEFER&t;17
DECL|macro|PARAM_TX
mdefine_line|#define PARAM_TX        18
DECL|macro|PARAM_HWEVENT
mdefine_line|#define PARAM_HWEVENT&t;31
DECL|macro|PARAM_RETURN
mdefine_line|#define PARAM_RETURN&t;255&t;/* reset kiss mode */
multiline_comment|/* fulldup parameter */
DECL|macro|KISS_DUPLEX_HALF
mdefine_line|#define KISS_DUPLEX_HALF&t;0&t;/* normal CSMA operation */
DECL|macro|KISS_DUPLEX_FULL
mdefine_line|#define KISS_DUPLEX_FULL&t;1&t;/* fullduplex, key down trx after transmission */
DECL|macro|KISS_DUPLEX_LINK
mdefine_line|#define KISS_DUPLEX_LINK&t;2&t;/* fullduplex, key down trx after &squot;idletime&squot; sec */
DECL|macro|KISS_DUPLEX_OPTIMA
mdefine_line|#define KISS_DUPLEX_OPTIMA&t;3&t;/* fullduplex, let the protocol layer control the hw */
multiline_comment|/* misc. parameters */
DECL|macro|TIMER_OFF
mdefine_line|#define TIMER_OFF&t;65535U&t;/* to switch off timers */
DECL|macro|NO_SUCH_PARAM
mdefine_line|#define NO_SUCH_PARAM&t;65534U&t;/* param not implemented */
multiline_comment|/* HWEVENT parameter */
DECL|macro|HWEV_DCD_ON
mdefine_line|#define HWEV_DCD_ON&t;0
DECL|macro|HWEV_DCD_OFF
mdefine_line|#define HWEV_DCD_OFF&t;1
DECL|macro|HWEV_ALL_SENT
mdefine_line|#define HWEV_ALL_SENT&t;2
multiline_comment|/* channel grouping */
DECL|macro|RXGROUP
mdefine_line|#define RXGROUP&t;&t;0x100&t;/* if set, only tx when all channels clear */
DECL|macro|TXGROUP
mdefine_line|#define TXGROUP&t;&t;0x200&t;/* if set, don&squot;t transmit simultaneously */
multiline_comment|/* Tx/Rx clock sources */
DECL|macro|CLK_DPLL
mdefine_line|#define CLK_DPLL&t;0&t;/* normal halfduplex operation */
DECL|macro|CLK_EXTERNAL
mdefine_line|#define CLK_EXTERNAL&t;1&t;/* external clocking (G3RUH/DF9IC modems) */
DECL|macro|CLK_DIVIDER
mdefine_line|#define CLK_DIVIDER&t;2&t;/* Rx = DPLL, Tx = divider (fullduplex with */
multiline_comment|/* modems without clock regeneration */
multiline_comment|/* Tx state */
DECL|macro|TXS_IDLE
mdefine_line|#define TXS_IDLE&t;0&t;/* Transmitter off, no data pending */
DECL|macro|TXS_BUSY
mdefine_line|#define TXS_BUSY&t;1&t;/* waiting for permission to send / tailtime */
DECL|macro|TXS_ACTIVE
mdefine_line|#define TXS_ACTIVE&t;2&t;/* Transmitter on, sending data */
DECL|macro|TXS_NEWFRAME
mdefine_line|#define TXS_NEWFRAME&t;3&t;/* reset CRC and send (next) frame */
DECL|macro|TXS_IDLE2
mdefine_line|#define TXS_IDLE2&t;4&t;/* Transmitter on, no data pending */
DECL|macro|TXS_WAIT
mdefine_line|#define TXS_WAIT&t;5&t;/* Waiting for Mintime to expire */
DECL|macro|TXS_TIMEOUT
mdefine_line|#define TXS_TIMEOUT&t;6&t;/* We had a transmission timeout */
DECL|macro|TX_ON
mdefine_line|#define TX_ON&t;&t;1&t;/* command for scc_key_trx() */
DECL|macro|TX_OFF
mdefine_line|#define TX_OFF&t;&t;0&t;/* dto */
multiline_comment|/* Vector masks in RR2B */
DECL|macro|VECTOR_MASK
mdefine_line|#define VECTOR_MASK&t;0x06
DECL|macro|TXINT
mdefine_line|#define TXINT&t;&t;0x00
DECL|macro|EXINT
mdefine_line|#define EXINT&t;&t;0x02
DECL|macro|RXINT
mdefine_line|#define RXINT&t;&t;0x04
DECL|macro|SPINT
mdefine_line|#define SPINT&t;&t;0x06
DECL|typedef|io_port
r_typedef
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* type definition for an &squot;io port address&squot; */
macro_line|#ifdef SCC_DELAY
DECL|macro|Inb
mdefine_line|#define Inb(port)&t;inb_p(port)
DECL|macro|Outb
mdefine_line|#define Outb(port, val)&t;outb_p(val, port)
macro_line|#else
DECL|macro|Inb
mdefine_line|#define Inb(port)&t;inb(port)
DECL|macro|Outb
mdefine_line|#define Outb(port, val)&t;outb(val, port)
macro_line|#endif
DECL|macro|TIMER_OFF
mdefine_line|#define TIMER_OFF 65535U
multiline_comment|/* SCC channel control structure for KISS */
DECL|struct|scc_kiss
r_struct
id|scc_kiss
(brace
DECL|member|txdelay
r_int
r_char
id|txdelay
suffix:semicolon
multiline_comment|/* Transmit Delay 10 ms/cnt */
DECL|member|persist
r_int
r_char
id|persist
suffix:semicolon
multiline_comment|/* Persistence (0-255) as a % */
DECL|member|slottime
r_int
r_char
id|slottime
suffix:semicolon
multiline_comment|/* Delay to wait on persistence hit */
DECL|member|tailtime
r_int
r_char
id|tailtime
suffix:semicolon
multiline_comment|/* Delay after last byte written */
DECL|member|fulldup
r_int
r_char
id|fulldup
suffix:semicolon
multiline_comment|/* Full Duplex mode 0=CSMA 1=DUP 2=ALWAYS KEYED */
DECL|member|waittime
r_int
r_char
id|waittime
suffix:semicolon
multiline_comment|/* Waittime before any transmit attempt */
DECL|member|maxkeyup
r_int
r_int
id|maxkeyup
suffix:semicolon
multiline_comment|/* Maximum time to transmit (seconds) */
DECL|member|mintime
r_int
r_char
id|mintime
suffix:semicolon
multiline_comment|/* Minimal offtime after MAXKEYUP timeout (seconds) */
DECL|member|idletime
r_int
r_int
id|idletime
suffix:semicolon
multiline_comment|/* Maximum idle time in ALWAYS KEYED mode (seconds) */
DECL|member|maxdefer
r_int
r_int
id|maxdefer
suffix:semicolon
multiline_comment|/* Timer for CSMA channel busy limit */
DECL|member|tx_inhibit
r_int
r_char
id|tx_inhibit
suffix:semicolon
multiline_comment|/* Transmit is not allowed when set */
DECL|member|group
r_int
r_char
id|group
suffix:semicolon
multiline_comment|/* Group ID for AX.25 TX interlocking */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* &squot;normal&squot; or &squot;hwctrl&squot; mode (unused) */
DECL|member|softdcd
r_int
r_char
id|softdcd
suffix:semicolon
multiline_comment|/* Use DPLL instead of DCD pin for carrier detect */
)brace
suffix:semicolon
multiline_comment|/* SCC statistical information */
DECL|struct|scc_stat
r_struct
id|scc_stat
(brace
DECL|member|rxints
r_int
id|rxints
suffix:semicolon
multiline_comment|/* Receiver interrupts */
DECL|member|txints
r_int
id|txints
suffix:semicolon
multiline_comment|/* Transmitter interrupts */
DECL|member|exints
r_int
id|exints
suffix:semicolon
multiline_comment|/* External/status interrupts */
DECL|member|spints
r_int
id|spints
suffix:semicolon
multiline_comment|/* Special receiver interrupts */
DECL|member|txframes
r_int
id|txframes
suffix:semicolon
multiline_comment|/* Packets sent */
DECL|member|rxframes
r_int
id|rxframes
suffix:semicolon
multiline_comment|/* Number of Frames Actually Received */
DECL|member|rxerrs
r_int
id|rxerrs
suffix:semicolon
multiline_comment|/* CRC Errors */
DECL|member|txerrs
r_int
id|txerrs
suffix:semicolon
multiline_comment|/* KISS errors */
DECL|member|nospace
r_int
r_int
id|nospace
suffix:semicolon
multiline_comment|/* &quot;Out of buffers&quot; */
DECL|member|rx_over
r_int
r_int
id|rx_over
suffix:semicolon
multiline_comment|/* Receiver Overruns */
DECL|member|tx_under
r_int
r_int
id|tx_under
suffix:semicolon
multiline_comment|/* Transmitter Underruns */
DECL|member|tx_state
r_int
r_int
id|tx_state
suffix:semicolon
multiline_comment|/* Transmitter state */
DECL|member|tx_queued
r_int
id|tx_queued
suffix:semicolon
multiline_comment|/* tx frames enqueued */
DECL|member|maxqueue
r_int
r_int
id|maxqueue
suffix:semicolon
multiline_comment|/* allocated tx_buffers */
DECL|member|bufsize
r_int
r_int
id|bufsize
suffix:semicolon
multiline_comment|/* used buffersize */
)brace
suffix:semicolon
DECL|struct|scc_modem
r_struct
id|scc_modem
(brace
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* Line speed, bps */
DECL|member|clocksrc
r_char
id|clocksrc
suffix:semicolon
multiline_comment|/* 0 = DPLL, 1 = external, 2 = divider */
DECL|member|nrz
r_char
id|nrz
suffix:semicolon
multiline_comment|/* NRZ instead of NRZI */
)brace
suffix:semicolon
DECL|struct|scc_kiss_cmd
r_struct
id|scc_kiss_cmd
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* one of the KISS-Commands defined above */
DECL|member|param
r_int
id|param
suffix:semicolon
multiline_comment|/* KISS-Param */
)brace
suffix:semicolon
DECL|struct|scc_hw_config
r_struct
id|scc_hw_config
(brace
DECL|member|data_a
id|io_port
id|data_a
suffix:semicolon
multiline_comment|/* data port channel A */
DECL|member|ctrl_a
id|io_port
id|ctrl_a
suffix:semicolon
multiline_comment|/* control port channel A */
DECL|member|data_b
id|io_port
id|data_b
suffix:semicolon
multiline_comment|/* data port channel B */
DECL|member|ctrl_b
id|io_port
id|ctrl_b
suffix:semicolon
multiline_comment|/* control port channel B */
DECL|member|vector_latch
id|io_port
id|vector_latch
suffix:semicolon
multiline_comment|/* INTACK-Latch (#) */
DECL|member|special
id|io_port
id|special
suffix:semicolon
multiline_comment|/* special function port */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* clock */
DECL|member|option
r_char
id|option
suffix:semicolon
multiline_comment|/* command for function port */
DECL|member|brand
r_char
id|brand
suffix:semicolon
multiline_comment|/* hardware type */
DECL|member|escc
r_char
id|escc
suffix:semicolon
multiline_comment|/* use ext. features of a 8580/85180/85280 */
)brace
suffix:semicolon
multiline_comment|/* (#) only one INTACK latch allowed. */
DECL|struct|scc_mem_config
r_struct
id|scc_mem_config
(brace
DECL|member|dummy
r_int
r_int
id|dummy
suffix:semicolon
DECL|member|bufsize
r_int
r_int
id|bufsize
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* SCC channel structure */
DECL|struct|scc_channel
r_struct
id|scc_channel
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic word */
DECL|member|init
r_int
id|init
suffix:semicolon
multiline_comment|/* channel exists? */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* link to device control structure */
DECL|member|dev_stat
r_struct
id|enet_statistics
id|dev_stat
suffix:semicolon
multiline_comment|/* device statistics */
DECL|member|brand
r_char
id|brand
suffix:semicolon
multiline_comment|/* manufacturer of the board */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* used clock */
DECL|member|ctrl
id|io_port
id|ctrl
suffix:semicolon
multiline_comment|/* I/O address of CONTROL register */
DECL|member|data
id|io_port
id|data
suffix:semicolon
multiline_comment|/* I/O address of DATA register */
DECL|member|special
id|io_port
id|special
suffix:semicolon
multiline_comment|/* I/O address of special function port */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* Number of Interrupt */
DECL|member|option
r_char
id|option
suffix:semicolon
DECL|member|enhanced
r_char
id|enhanced
suffix:semicolon
multiline_comment|/* Enhanced SCC support */
DECL|member|wreg
r_int
r_char
id|wreg
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Copy of last written value in WRx */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* Copy of R0 at last external interrupt */
DECL|member|kiss
r_struct
id|scc_kiss
id|kiss
suffix:semicolon
multiline_comment|/* control structure for KISS params */
DECL|member|stat
r_struct
id|scc_stat
id|stat
suffix:semicolon
multiline_comment|/* statistical information */
DECL|member|modem
r_struct
id|scc_modem
id|modem
suffix:semicolon
multiline_comment|/* modem information */
DECL|member|tx_next_buff
r_struct
id|sk_buff
op_star
id|tx_next_buff
suffix:semicolon
multiline_comment|/* next tx buffer */
DECL|member|rx_buff
r_struct
id|sk_buff
op_star
id|rx_buff
suffix:semicolon
multiline_comment|/* pointer to frame currently received */
DECL|member|tx_buff
r_struct
id|sk_buff
op_star
id|tx_buff
suffix:semicolon
multiline_comment|/* pointer to frame currently transmitted */
multiline_comment|/* Timer */
DECL|member|tx_t
r_struct
id|timer_list
id|tx_t
suffix:semicolon
multiline_comment|/* tx timer for this channel */
DECL|member|tx_wdog
r_struct
id|timer_list
id|tx_wdog
suffix:semicolon
multiline_comment|/* tx watchdogs */
)brace
suffix:semicolon
r_int
id|scc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
