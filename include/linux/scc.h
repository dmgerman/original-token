macro_line|#ifndef&t;_SCC_H
DECL|macro|_SCC_H
mdefine_line|#define&t;_SCC_H
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
multiline_comment|/* Constants */
DECL|macro|MAXSCC
mdefine_line|#define MAXSCC&t;&t;4&t;/* number of max. supported chips */
DECL|macro|MAX_IBUFS
mdefine_line|#define MAX_IBUFS&t;300&t;/* change this if you run out of memory */
DECL|macro|BUFSIZE
mdefine_line|#define BUFSIZE&t;  &t;64&t;/* must not exceed 4096 */
DECL|macro|TPS
mdefine_line|#define TPS&t;&t;25&t;/* scc_timer(): 25  Ticks Per Second */
DECL|macro|SCC_TIMER
mdefine_line|#define SCC_TIMER&t;3
DECL|macro|SCC_PARANOIA_CHECK
mdefine_line|#define SCC_PARANOIA_CHECK&t;/* tell the user if something is going wrong */
multiline_comment|/* ioctl() commands */
multiline_comment|/* !!! NEW VALUES !!! */
DECL|macro|TIOCSCCINI
mdefine_line|#define TIOCSCCINI&t;0x5470&t;&t;/* init driver */
DECL|macro|TIOCCHANINI
mdefine_line|#define TIOCCHANINI&t;0x5471&t;&t;/* init channel */
DECL|macro|TIOCGKISS
mdefine_line|#define TIOCGKISS&t;0x5472&t;&t;/* get kiss parameter */
DECL|macro|TIOCSKISS
mdefine_line|#define TIOCSKISS&t;0x5473&t;&t;/* set kiss parameter */
DECL|macro|TIOCSCCSTAT
mdefine_line|#define TIOCSCCSTAT&t;0x5474&t;&t;/* get scc status */
multiline_comment|/* magic number */
DECL|macro|SCC_MAGIC
mdefine_line|#define SCC_MAGIC&t;0x8530&t;&t;/* ;-) */
multiline_comment|/* KISS protocol flags */
DECL|macro|FEND
mdefine_line|#define FEND&t;192
DECL|macro|FESC
mdefine_line|#define FESC&t;219
DECL|macro|TFEND
mdefine_line|#define TFEND&t;220
DECL|macro|TFESC
mdefine_line|#define TFESC&t;221
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
DECL|macro|PARAM_SLIP
mdefine_line|#define PARAM_SLIP&t;19
DECL|macro|PARAM_RETURN
mdefine_line|#define PARAM_RETURN&t;255&t;/* reset kiss mode */
DECL|macro|TIMER_OFF
mdefine_line|#define TIMER_OFF&t;65535U&t;/* to switch off timers */
DECL|macro|NO_SUCH_PARAM
mdefine_line|#define NO_SUCH_PARAM&t;65534U&t;/* param not implemented */
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
DECL|macro|TX_ON
mdefine_line|#define TX_ON&t;&t;1&t;/* command for scc_key_trx() */
DECL|macro|TX_OFF
mdefine_line|#define TX_OFF&t;&t;0&t;/* dto */
multiline_comment|/* Buffer management */
DECL|macro|BT_RECEIVE
mdefine_line|#define BT_RECEIVE  1&t;&t;/* buffer allocated by receive */
DECL|macro|BT_TRANSMIT
mdefine_line|#define BT_TRANSMIT 2&t;&t;/* buffer allocated by transmit */
DECL|macro|QUEUE_THRES
mdefine_line|#define QUEUE_THRES MAX_IBUFS/20&t;/* maximum amount of packets being queued */
DECL|macro|QUEUE_HYST
mdefine_line|#define QUEUE_HYST  3&t;&t;&t;/* leave QUEUE_HYST packets untouched */
DECL|macro|NULLBUF
mdefine_line|#define NULLBUF  (struct mbuf *)0
DECL|macro|NULLBUFP
mdefine_line|#define NULLBUFP (struct mbuf **)0
DECL|typedef|io_port
r_typedef
r_int
r_int
id|io_port
suffix:semicolon
multiline_comment|/* type definition for an &squot;io port address&squot; */
DECL|typedef|ioaddr
r_typedef
r_int
r_int
id|ioaddr
suffix:semicolon
multiline_comment|/* old def */
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
multiline_comment|/* some nasty macros (esp. Expired) */
DECL|macro|TIMER_STOPPED
mdefine_line|#define TIMER_STOPPED 65535U
DECL|macro|Running
mdefine_line|#define Running(k) (scc-&gt;k != TIMER_STOPPED)
DECL|macro|Expired
mdefine_line|#define Expired(k) (scc-&gt;k != TIMER_STOPPED) &amp;&amp; (!(scc-&gt;k) || (--(scc-&gt;k) == 0))
DECL|macro|Stop_Timer
mdefine_line|#define Stop_Timer(k) scc-&gt;k = TIMER_STOPPED
multiline_comment|/* Basic message buffer structure */
DECL|struct|mbuf
r_struct
id|mbuf
(brace
DECL|member|next
r_struct
id|mbuf
op_star
id|next
suffix:semicolon
multiline_comment|/* Links mbufs belonging to single packets */
DECL|member|anext
r_struct
id|mbuf
op_star
id|anext
suffix:semicolon
multiline_comment|/* Links packets on queues */
DECL|member|type
r_char
id|type
suffix:semicolon
multiline_comment|/* who allocated this buffer? */
DECL|member|time_out
r_int
r_int
id|time_out
suffix:semicolon
multiline_comment|/* buffer time out */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of associated data buffer */
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
multiline_comment|/* Reference count */
DECL|member|dup
r_struct
id|mbuf
op_star
id|dup
suffix:semicolon
multiline_comment|/* Pointer to duplicated mbuf */
DECL|member|data
r_char
id|data
(braket
id|BUFSIZE
)braket
suffix:semicolon
multiline_comment|/* Active working pointers */
DECL|member|cnt
r_int
id|cnt
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sccbuf
r_struct
id|sccbuf
(brace
DECL|member|bp
r_struct
id|mbuf
op_star
id|bp
suffix:semicolon
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* Delay after XMTR OFF */
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
multiline_comment|/* Minimal offtime after MAXKEYUP timeout */
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
multiline_comment|/* group ID for AX.25 TX interlocking */
DECL|member|not_slip
r_int
r_char
id|not_slip
suffix:semicolon
multiline_comment|/* set to zero: use SLIP instead of KISS */
DECL|member|softdcd
r_int
r_char
id|softdcd
suffix:semicolon
multiline_comment|/* use DPLL instead of DCD pin for carrier detect */
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
multiline_comment|/* Number of Frames Actally Received */
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
DECL|member|tx_kiss_state
r_char
id|tx_kiss_state
suffix:semicolon
multiline_comment|/* state of the kiss interpreter */
DECL|member|rx_kiss_state
r_char
id|rx_kiss_state
suffix:semicolon
multiline_comment|/* state of the kiss encoder */
DECL|member|tx_queued
r_int
id|tx_queued
suffix:semicolon
multiline_comment|/* tx frames enqueued */
DECL|member|rx_queued
r_int
id|rx_queued
suffix:semicolon
multiline_comment|/* rx frames enqueued */
DECL|member|rx_alloc
r_int
r_int
id|rx_alloc
suffix:semicolon
multiline_comment|/* allocated rx_buffers */
DECL|member|tx_alloc
r_int
r_int
id|tx_alloc
suffix:semicolon
multiline_comment|/* allocated tx_buffers */
DECL|member|used_buf
r_int
r_int
id|used_buf
suffix:semicolon
multiline_comment|/* used buffers (should be rx_alloc+tx_alloc) */
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
DECL|struct|ioctl_command
r_struct
id|ioctl_command
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* one of the KISS-Commands devined above */
DECL|member|param
r_int
id|param
suffix:semicolon
multiline_comment|/* KISS-Param */
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
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* link to tty control structure */
DECL|member|tty_opened
r_int
r_char
id|tty_opened
suffix:semicolon
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
DECL|member|rxbuf
r_char
id|rxbuf
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/* Rx frame buffer max framesize * 2 */
DECL|member|rxbufcnt
r_int
id|rxbufcnt
suffix:semicolon
multiline_comment|/* Rx frame counter */
DECL|member|sndq
r_struct
id|mbuf
op_star
id|sndq
suffix:semicolon
multiline_comment|/* tx: Packets awaiting transmission */
DECL|member|tbp
r_struct
id|mbuf
op_star
id|tbp
suffix:semicolon
multiline_comment|/* tx: Transmit mbuf being sent */
DECL|member|sndq1
r_struct
id|mbuf
op_star
id|sndq1
suffix:semicolon
multiline_comment|/* Pointer to mbuf currently under construction */
DECL|member|sndq2
r_struct
id|mbuf
op_star
id|sndq2
suffix:semicolon
multiline_comment|/* Pointer to mbuf currently under construction */
multiline_comment|/*&t;unsigned char &t;&t;*xmit_buf;&n;&t;int&t;&t;&t;xmit_head;&n;&t;int&t;&t;&t;xmit_tail;&n;&t;int&t;&t;&t;xmit_cnt;*/
multiline_comment|/* Timer */
DECL|member|t_dwait
r_int
r_int
id|t_dwait
suffix:semicolon
multiline_comment|/* wait time (DWAIT) */
DECL|member|t_slot
r_int
r_int
id|t_slot
suffix:semicolon
multiline_comment|/* channel sample frequency */
DECL|member|t_txdel
r_int
r_int
id|t_txdel
suffix:semicolon
multiline_comment|/* TX delay */
DECL|member|t_tail
r_int
r_int
id|t_tail
suffix:semicolon
multiline_comment|/* tail time */
DECL|member|t_maxk
r_int
r_int
id|t_maxk
suffix:semicolon
multiline_comment|/* max. key up */
DECL|member|t_min
r_int
r_int
id|t_min
suffix:semicolon
multiline_comment|/* minimal key up */
DECL|member|t_idle
r_int
r_int
id|t_idle
suffix:semicolon
multiline_comment|/* */
DECL|member|t_mbusy
r_int
r_int
id|t_mbusy
suffix:semicolon
multiline_comment|/* time until defer if channel busy */
)brace
suffix:semicolon
multiline_comment|/* 8530 Serial Communications Controller Register definitions */
DECL|macro|FLAG
mdefine_line|#define&t;FLAG&t;0x7e
multiline_comment|/* Write Register 0 */
DECL|macro|R0
mdefine_line|#define&t;R0&t;0&t;&t;/* Register selects */
DECL|macro|R1
mdefine_line|#define&t;R1&t;1
DECL|macro|R2
mdefine_line|#define&t;R2&t;2
DECL|macro|R3
mdefine_line|#define&t;R3&t;3
DECL|macro|R4
mdefine_line|#define&t;R4&t;4
DECL|macro|R5
mdefine_line|#define&t;R5&t;5
DECL|macro|R6
mdefine_line|#define&t;R6&t;6
DECL|macro|R7
mdefine_line|#define&t;R7&t;7
DECL|macro|R8
mdefine_line|#define&t;R8&t;8
DECL|macro|R9
mdefine_line|#define&t;R9&t;9
DECL|macro|R10
mdefine_line|#define&t;R10&t;10
DECL|macro|R11
mdefine_line|#define&t;R11&t;11
DECL|macro|R12
mdefine_line|#define&t;R12&t;12
DECL|macro|R13
mdefine_line|#define&t;R13&t;13
DECL|macro|R14
mdefine_line|#define&t;R14&t;14
DECL|macro|R15
mdefine_line|#define&t;R15&t;15
DECL|macro|NULLCODE
mdefine_line|#define&t;NULLCODE&t;0&t;/* Null Code */
DECL|macro|POINT_HIGH
mdefine_line|#define&t;POINT_HIGH&t;0x8&t;/* Select upper half of registers */
DECL|macro|RES_EXT_INT
mdefine_line|#define&t;RES_EXT_INT&t;0x10&t;/* Reset Ext. Status Interrupts */
DECL|macro|SEND_ABORT
mdefine_line|#define&t;SEND_ABORT&t;0x18&t;/* HDLC Abort */
DECL|macro|RES_RxINT_FC
mdefine_line|#define&t;RES_RxINT_FC&t;0x20&t;/* Reset RxINT on First Character */
DECL|macro|RES_Tx_P
mdefine_line|#define&t;RES_Tx_P&t;0x28&t;/* Reset TxINT Pending */
DECL|macro|ERR_RES
mdefine_line|#define&t;ERR_RES&t;&t;0x30&t;/* Error Reset */
DECL|macro|RES_H_IUS
mdefine_line|#define&t;RES_H_IUS&t;0x38&t;/* Reset highest IUS */
DECL|macro|RES_Rx_CRC
mdefine_line|#define&t;RES_Rx_CRC&t;0x40&t;/* Reset Rx CRC Checker */
DECL|macro|RES_Tx_CRC
mdefine_line|#define&t;RES_Tx_CRC&t;0x80&t;/* Reset Tx CRC Checker */
DECL|macro|RES_EOM_L
mdefine_line|#define&t;RES_EOM_L&t;0xC0&t;/* Reset EOM latch */
multiline_comment|/* Write Register 1 */
DECL|macro|EXT_INT_ENAB
mdefine_line|#define&t;EXT_INT_ENAB&t;0x1&t;/* Ext Int Enable */
DECL|macro|TxINT_ENAB
mdefine_line|#define&t;TxINT_ENAB&t;0x2&t;/* Tx Int Enable */
DECL|macro|PAR_SPEC
mdefine_line|#define&t;PAR_SPEC&t;0x4&t;/* Parity is special condition */
DECL|macro|RxINT_DISAB
mdefine_line|#define&t;RxINT_DISAB&t;0&t;/* Rx Int Disable */
DECL|macro|RxINT_FCERR
mdefine_line|#define&t;RxINT_FCERR&t;0x8&t;/* Rx Int on First Character Only or Error */
DECL|macro|INT_ALL_Rx
mdefine_line|#define&t;INT_ALL_Rx&t;0x10&t;/* Int on all Rx Characters or error */
DECL|macro|INT_ERR_Rx
mdefine_line|#define&t;INT_ERR_Rx&t;0x18&t;/* Int on error only */
DECL|macro|WT_RDY_RT
mdefine_line|#define&t;WT_RDY_RT&t;0x20&t;/* Wait/Ready on R/T */
DECL|macro|WT_FN_RDYFN
mdefine_line|#define&t;WT_FN_RDYFN&t;0x40&t;/* Wait/FN/Ready FN */
DECL|macro|WT_RDY_ENAB
mdefine_line|#define&t;WT_RDY_ENAB&t;0x80&t;/* Wait/Ready Enable */
multiline_comment|/* Write Register 2 (Interrupt Vector) */
multiline_comment|/* Write Register 3 */
DECL|macro|RxENABLE
mdefine_line|#define&t;RxENABLE&t;0x1&t;/* Rx Enable */
DECL|macro|SYNC_L_INH
mdefine_line|#define&t;SYNC_L_INH&t;0x2&t;/* Sync Character Load Inhibit */
DECL|macro|ADD_SM
mdefine_line|#define&t;ADD_SM&t;&t;0x4&t;/* Address Search Mode (SDLC) */
DECL|macro|RxCRC_ENAB
mdefine_line|#define&t;RxCRC_ENAB&t;0x8&t;/* Rx CRC Enable */
DECL|macro|ENT_HM
mdefine_line|#define&t;ENT_HM&t;&t;0x10&t;/* Enter Hunt Mode */
DECL|macro|AUTO_ENAB
mdefine_line|#define&t;AUTO_ENAB&t;0x20&t;/* Auto Enables */
DECL|macro|Rx5
mdefine_line|#define&t;Rx5&t;&t;0x0&t;/* Rx 5 Bits/Character */
DECL|macro|Rx7
mdefine_line|#define&t;Rx7&t;&t;0x40&t;/* Rx 7 Bits/Character */
DECL|macro|Rx6
mdefine_line|#define&t;Rx6&t;&t;0x80&t;/* Rx 6 Bits/Character */
DECL|macro|Rx8
mdefine_line|#define&t;Rx8&t;&t;0xc0&t;/* Rx 8 Bits/Character */
multiline_comment|/* Write Register 4 */
DECL|macro|PAR_ENA
mdefine_line|#define&t;PAR_ENA&t;&t;0x1&t;/* Parity Enable */
DECL|macro|PAR_EVEN
mdefine_line|#define&t;PAR_EVEN&t;0x2&t;/* Parity Even/Odd* */
DECL|macro|SYNC_ENAB
mdefine_line|#define&t;SYNC_ENAB&t;0&t;/* Sync Modes Enable */
DECL|macro|SB1
mdefine_line|#define&t;SB1&t;&t;0x4&t;/* 1 stop bit/char */
DECL|macro|SB15
mdefine_line|#define&t;SB15&t;&t;0x8&t;/* 1.5 stop bits/char */
DECL|macro|SB2
mdefine_line|#define&t;SB2&t;&t;0xc&t;/* 2 stop bits/char */
DECL|macro|MONSYNC
mdefine_line|#define&t;MONSYNC&t;&t;0&t;/* 8 Bit Sync character */
DECL|macro|BISYNC
mdefine_line|#define&t;BISYNC&t;&t;0x10&t;/* 16 bit sync character */
DECL|macro|SDLC
mdefine_line|#define&t;SDLC&t;&t;0x20&t;/* SDLC Mode (01111110 Sync Flag) */
DECL|macro|EXTSYNC
mdefine_line|#define&t;EXTSYNC&t;&t;0x30&t;/* External Sync Mode */
DECL|macro|X1CLK
mdefine_line|#define&t;X1CLK&t;&t;0x0&t;/* x1 clock mode */
DECL|macro|X16CLK
mdefine_line|#define&t;X16CLK&t;&t;0x40&t;/* x16 clock mode */
DECL|macro|X32CLK
mdefine_line|#define&t;X32CLK&t;&t;0x80&t;/* x32 clock mode */
DECL|macro|X64CLK
mdefine_line|#define&t;X64CLK&t;&t;0xC0&t;/* x64 clock mode */
multiline_comment|/* Write Register 5 */
DECL|macro|TxCRC_ENAB
mdefine_line|#define&t;TxCRC_ENAB&t;0x1&t;/* Tx CRC Enable */
DECL|macro|RTS
mdefine_line|#define&t;RTS&t;&t;0x2&t;/* RTS */
DECL|macro|SDLC_CRC
mdefine_line|#define&t;SDLC_CRC&t;0x4&t;/* SDLC/CRC-16 */
DECL|macro|TxENAB
mdefine_line|#define&t;TxENAB&t;&t;0x8&t;/* Tx Enable */
DECL|macro|SND_BRK
mdefine_line|#define&t;SND_BRK&t;&t;0x10&t;/* Send Break */
DECL|macro|Tx5
mdefine_line|#define&t;Tx5&t;&t;0x0&t;/* Tx 5 bits (or less)/character */
DECL|macro|Tx7
mdefine_line|#define&t;Tx7&t;&t;0x20&t;/* Tx 7 bits/character */
DECL|macro|Tx6
mdefine_line|#define&t;Tx6&t;&t;0x40&t;/* Tx 6 bits/character */
DECL|macro|Tx8
mdefine_line|#define&t;Tx8&t;&t;0x60&t;/* Tx 8 bits/character */
DECL|macro|DTR
mdefine_line|#define&t;DTR&t;&t;0x80&t;/* DTR */
multiline_comment|/* Write Register 6 (Sync bits 0-7/SDLC Address Field) */
multiline_comment|/* Write Register 7 (Sync bits 8-15/SDLC 01111110) */
multiline_comment|/* Write Register 8 (transmit buffer) */
multiline_comment|/* Write Register 9 (Master interrupt control) */
DECL|macro|VIS
mdefine_line|#define&t;VIS&t;1&t;/* Vector Includes Status */
DECL|macro|NV
mdefine_line|#define&t;NV&t;2&t;/* No Vector */
DECL|macro|DLC
mdefine_line|#define&t;DLC&t;4&t;/* Disable Lower Chain */
DECL|macro|MIE
mdefine_line|#define&t;MIE&t;8&t;/* Master Interrupt Enable */
DECL|macro|STATHI
mdefine_line|#define&t;STATHI&t;0x10&t;/* Status high */
DECL|macro|NORESET
mdefine_line|#define&t;NORESET&t;0&t;/* No reset on write to R9 */
DECL|macro|CHRB
mdefine_line|#define&t;CHRB&t;0x40&t;/* Reset channel B */
DECL|macro|CHRA
mdefine_line|#define&t;CHRA&t;0x80&t;/* Reset channel A */
DECL|macro|FHWRES
mdefine_line|#define&t;FHWRES&t;0xc0&t;/* Force hardware reset */
multiline_comment|/* Write Register 10 (misc control bits) */
DECL|macro|BIT6
mdefine_line|#define&t;BIT6&t;1&t;/* 6 bit/8bit sync */
DECL|macro|LOOPMODE
mdefine_line|#define&t;LOOPMODE 2&t;/* SDLC Loop mode */
DECL|macro|ABUNDER
mdefine_line|#define&t;ABUNDER&t;4&t;/* Abort/flag on SDLC xmit underrun */
DECL|macro|MARKIDLE
mdefine_line|#define&t;MARKIDLE 8&t;/* Mark/flag on idle */
DECL|macro|GAOP
mdefine_line|#define&t;GAOP&t;0x10&t;/* Go active on poll */
DECL|macro|NRZ
mdefine_line|#define&t;NRZ&t;0&t;/* NRZ mode */
DECL|macro|NRZI
mdefine_line|#define&t;NRZI&t;0x20&t;/* NRZI mode */
DECL|macro|FM1
mdefine_line|#define&t;FM1&t;0x40&t;/* FM1 (transition = 1) */
DECL|macro|FM0
mdefine_line|#define&t;FM0&t;0x60&t;/* FM0 (transition = 0) */
DECL|macro|CRCPS
mdefine_line|#define&t;CRCPS&t;0x80&t;/* CRC Preset I/O */
multiline_comment|/* Write Register 11 (Clock Mode control) */
DECL|macro|TRxCXT
mdefine_line|#define&t;TRxCXT&t;0&t;/* TRxC = Xtal output */
DECL|macro|TRxCTC
mdefine_line|#define&t;TRxCTC&t;1&t;/* TRxC = Transmit clock */
DECL|macro|TRxCBR
mdefine_line|#define&t;TRxCBR&t;2&t;/* TRxC = BR Generator Output */
DECL|macro|TRxCDP
mdefine_line|#define&t;TRxCDP&t;3&t;/* TRxC = DPLL output */
DECL|macro|TRxCOI
mdefine_line|#define&t;TRxCOI&t;4&t;/* TRxC O/I */
DECL|macro|TCRTxCP
mdefine_line|#define&t;TCRTxCP&t;0&t;/* Transmit clock = RTxC pin */
DECL|macro|TCTRxCP
mdefine_line|#define&t;TCTRxCP&t;8&t;/* Transmit clock = TRxC pin */
DECL|macro|TCBR
mdefine_line|#define&t;TCBR&t;0x10&t;/* Transmit clock = BR Generator output */
DECL|macro|TCDPLL
mdefine_line|#define&t;TCDPLL&t;0x18&t;/* Transmit clock = DPLL output */
DECL|macro|RCRTxCP
mdefine_line|#define&t;RCRTxCP&t;0&t;/* Receive clock = RTxC pin */
DECL|macro|RCTRxCP
mdefine_line|#define&t;RCTRxCP&t;0x20&t;/* Receive clock = TRxC pin */
DECL|macro|RCBR
mdefine_line|#define&t;RCBR&t;0x40&t;/* Receive clock = BR Generator output */
DECL|macro|RCDPLL
mdefine_line|#define&t;RCDPLL&t;0x60&t;/* Receive clock = DPLL output */
DECL|macro|RTxCX
mdefine_line|#define&t;RTxCX&t;0x80&t;/* RTxC Xtal/No Xtal */
multiline_comment|/* Write Register 12 (lower byte of baud rate generator time constant) */
multiline_comment|/* Write Register 13 (upper byte of baud rate generator time constant) */
multiline_comment|/* Write Register 14 (Misc control bits) */
DECL|macro|BRENABL
mdefine_line|#define&t;BRENABL&t;1&t;/* Baud rate generator enable */
DECL|macro|BRSRC
mdefine_line|#define&t;BRSRC&t;2&t;/* Baud rate generator source */
DECL|macro|DTRREQ
mdefine_line|#define&t;DTRREQ&t;4&t;/* DTR/Request function */
DECL|macro|AUTOECHO
mdefine_line|#define&t;AUTOECHO 8&t;/* Auto Echo */
DECL|macro|LOOPBAK
mdefine_line|#define&t;LOOPBAK&t;0x10&t;/* Local loopback */
DECL|macro|SEARCH
mdefine_line|#define&t;SEARCH&t;0x20&t;/* Enter search mode */
DECL|macro|RMC
mdefine_line|#define&t;RMC&t;0x40&t;/* Reset missing clock */
DECL|macro|DISDPLL
mdefine_line|#define&t;DISDPLL&t;0x60&t;/* Disable DPLL */
DECL|macro|SSBR
mdefine_line|#define&t;SSBR&t;0x80&t;/* Set DPLL source = BR generator */
DECL|macro|SSRTxC
mdefine_line|#define&t;SSRTxC&t;0xa0&t;/* Set DPLL source = RTxC */
DECL|macro|SFMM
mdefine_line|#define&t;SFMM&t;0xc0&t;/* Set FM mode */
DECL|macro|SNRZI
mdefine_line|#define&t;SNRZI&t;0xe0&t;/* Set NRZI mode */
multiline_comment|/* Write Register 15 (external/status interrupt control) */
DECL|macro|ZCIE
mdefine_line|#define&t;ZCIE&t;2&t;/* Zero count IE */
DECL|macro|DCDIE
mdefine_line|#define&t;DCDIE&t;8&t;/* DCD IE */
DECL|macro|SYNCIE
mdefine_line|#define&t;SYNCIE&t;0x10&t;/* Sync/hunt IE */
DECL|macro|CTSIE
mdefine_line|#define&t;CTSIE&t;0x20&t;/* CTS IE */
DECL|macro|TxUIE
mdefine_line|#define&t;TxUIE&t;0x40&t;/* Tx Underrun/EOM IE */
DECL|macro|BRKIE
mdefine_line|#define&t;BRKIE&t;0x80&t;/* Break/Abort IE */
multiline_comment|/* Read Register 0 */
DECL|macro|Rx_CH_AV
mdefine_line|#define&t;Rx_CH_AV&t;0x1&t;/* Rx Character Available */
DECL|macro|ZCOUNT
mdefine_line|#define&t;ZCOUNT&t;&t;0x2&t;/* Zero count */
DECL|macro|Tx_BUF_EMP
mdefine_line|#define&t;Tx_BUF_EMP&t;0x4&t;/* Tx Buffer empty */
DECL|macro|DCD
mdefine_line|#define&t;DCD&t;&t;0x8&t;/* DCD */
DECL|macro|SYNC_HUNT
mdefine_line|#define&t;SYNC_HUNT&t;0x10&t;/* Sync/hunt */
DECL|macro|CTS
mdefine_line|#define&t;CTS&t;&t;0x20&t;/* CTS */
DECL|macro|TxEOM
mdefine_line|#define&t;TxEOM&t;&t;0x40&t;/* Tx underrun */
DECL|macro|BRK_ABRT
mdefine_line|#define&t;BRK_ABRT&t;0x80&t;/* Break/Abort */
multiline_comment|/* Read Register 1 */
DECL|macro|ALL_SNT
mdefine_line|#define&t;ALL_SNT&t;&t;0x1&t;/* All sent */
multiline_comment|/* Residue Data for 8 Rx bits/char programmed */
DECL|macro|RES3
mdefine_line|#define&t;RES3&t;&t;0x8&t;/* 0/3 */
DECL|macro|RES4
mdefine_line|#define&t;RES4&t;&t;0x4&t;/* 0/4 */
DECL|macro|RES5
mdefine_line|#define&t;RES5&t;&t;0xc&t;/* 0/5 */
DECL|macro|RES6
mdefine_line|#define&t;RES6&t;&t;0x2&t;/* 0/6 */
DECL|macro|RES7
mdefine_line|#define&t;RES7&t;&t;0xa&t;/* 0/7 */
DECL|macro|RES8
mdefine_line|#define&t;RES8&t;&t;0x6&t;/* 0/8 */
DECL|macro|RES18
mdefine_line|#define&t;RES18&t;&t;0xe&t;/* 1/8 */
DECL|macro|RES28
mdefine_line|#define&t;RES28&t;&t;0x0&t;/* 2/8 */
multiline_comment|/* Special Rx Condition Interrupts */
DECL|macro|PAR_ERR
mdefine_line|#define&t;PAR_ERR&t;&t;0x10&t;/* Parity error */
DECL|macro|Rx_OVR
mdefine_line|#define&t;Rx_OVR&t;&t;0x20&t;/* Rx Overrun Error */
DECL|macro|CRC_ERR
mdefine_line|#define&t;CRC_ERR&t;&t;0x40&t;/* CRC/Framing Error */
DECL|macro|END_FR
mdefine_line|#define&t;END_FR&t;&t;0x80&t;/* End of Frame (SDLC) */
multiline_comment|/* Read Register 2 (channel B only) - Interrupt vector */
DECL|macro|VECTOR_MASK
mdefine_line|#define VECTOR_MASK&t;0x06
DECL|macro|TXINT
mdefine_line|#define TXINT   0x00
DECL|macro|EXINT
mdefine_line|#define EXINT   0x02
DECL|macro|RXINT
mdefine_line|#define RXINT   0x04
DECL|macro|SPINT
mdefine_line|#define SPINT   0x06
multiline_comment|/* Read Register 3 (interrupt pending register) ch a only */
DECL|macro|CHBEXT
mdefine_line|#define&t;CHBEXT&t;0x1&t;&t;/* Channel B Ext/Stat IP */
DECL|macro|CHBTxIP
mdefine_line|#define&t;CHBTxIP&t;0x2&t;&t;/* Channel B Tx IP */
DECL|macro|CHBRxIP
mdefine_line|#define&t;CHBRxIP&t;0x4&t;&t;/* Channel B Rx IP */
DECL|macro|CHAEXT
mdefine_line|#define&t;CHAEXT&t;0x8&t;&t;/* Channel A Ext/Stat IP */
DECL|macro|CHATxIP
mdefine_line|#define&t;CHATxIP&t;0x10&t;&t;/* Channel A Tx IP */
DECL|macro|CHARxIP
mdefine_line|#define&t;CHARxIP&t;0x20&t;&t;/* Channel A Rx IP */
multiline_comment|/* Read Register 8 (receive data register) */
multiline_comment|/* Read Register 10  (misc status bits) */
DECL|macro|ONLOOP
mdefine_line|#define&t;ONLOOP&t;2&t;&t;/* On loop */
DECL|macro|LOOPSEND
mdefine_line|#define&t;LOOPSEND 0x10&t;&t;/* Loop sending */
DECL|macro|CLK2MIS
mdefine_line|#define&t;CLK2MIS&t;0x40&t;&t;/* Two clocks missing */
DECL|macro|CLK1MIS
mdefine_line|#define&t;CLK1MIS&t;0x80&t;&t;/* One clock missing */
multiline_comment|/* Read Register 12 (lower byte of baud rate generator constant) */
multiline_comment|/* Read Register 13 (upper byte of baud rate generator constant) */
multiline_comment|/* Read Register 15 (value of WR 15) */
multiline_comment|/* 8536 register definitions */
DECL|macro|CIO_MICR
mdefine_line|#define CIO_MICR&t;0x00&t;/* Master interrupt control register */
DECL|macro|CIO_MCCR
mdefine_line|#define CIO_MCCR&t;0x01&t;/* Master configuration control register */
DECL|macro|CIO_CTMS1
mdefine_line|#define CIO_CTMS1&t;0x1c&t;/* Counter/timer mode specification #1 */
DECL|macro|CIO_CTMS2
mdefine_line|#define CIO_CTMS2&t;0x1d&t;/* Counter/timer mode specification #2 */
DECL|macro|CIO_CTMS3
mdefine_line|#define CIO_CTMS3&t;0x1e&t;/* Counter/timer mode specification #3 */
DECL|macro|CIO_IVR
mdefine_line|#define CIO_IVR &t;0x04&t;/* Interrupt vector register */
DECL|macro|CIO_CSR1
mdefine_line|#define CIO_CSR1&t;0x0a&t;/* Command and status register CTC #1 */
DECL|macro|CIO_CSR2
mdefine_line|#define CIO_CSR2&t;0x0b&t;/* Command and status register CTC #2 */
DECL|macro|CIO_CSR3
mdefine_line|#define CIO_CSR3&t;0x0c&t;/* Command and status register CTC #3 */
DECL|macro|CIO_CT1MSB
mdefine_line|#define CIO_CT1MSB&t;0x16&t;/* CTC #1 Timer constant - MSB */
DECL|macro|CIO_CT1LSB
mdefine_line|#define CIO_CT1LSB&t;0x17&t;/* CTC #1 Timer constant - LSB */
DECL|macro|CIO_CT2MSB
mdefine_line|#define CIO_CT2MSB&t;0x18&t;/* CTC #2 Timer constant - MSB */
DECL|macro|CIO_CT2LSB
mdefine_line|#define CIO_CT2LSB&t;0x19&t;/* CTC #2 Timer constant - LSB */
DECL|macro|CIO_CT3MSB
mdefine_line|#define CIO_CT3MSB&t;0x1a&t;/* CTC #3 Timer constant - MSB */
DECL|macro|CIO_CT3LSB
mdefine_line|#define CIO_CT3LSB&t;0x1b&t;/* CTC #3 Timer constant - LSB */
DECL|macro|CIO_PDCA
mdefine_line|#define CIO_PDCA&t;0x23&t;/* Port A data direction control */
DECL|macro|CIO_PDCB
mdefine_line|#define CIO_PDCB&t;0x2b&t;/* Port B data direction control */
DECL|macro|CIO_GCB
mdefine_line|#define CIO_GCB &t;0x04&t;/* CTC Gate command bit */
DECL|macro|CIO_TCB
mdefine_line|#define CIO_TCB &t;0x02&t;/* CTC Trigger command bit */
DECL|macro|CIO_IE
mdefine_line|#define CIO_IE&t;&t;0xc0&t;/* CTC Interrupt enable (set) */
DECL|macro|CIO_CIP
mdefine_line|#define CIO_CIP &t;0x20&t;/* CTC Clear interrupt pending */
DECL|macro|CIO_IP
mdefine_line|#define CIO_IP&t;&t;0x20&t;/* CTC Interrupt pending */
multiline_comment|/* 8580/85180/85280 Enhanced SCC register definitions */
multiline_comment|/* Write Register 7&squot; (SDLC/HDLC Programmable Enhancements) */
DECL|macro|AUTOTXF
mdefine_line|#define AUTOTXF&t;0x01&t;&t;/* Auto Tx Flag */
DECL|macro|AUTOEOM
mdefine_line|#define AUTOEOM 0x02&t;&t;/* Auto EOM Latch Reset */
DECL|macro|AUTORTS
mdefine_line|#define AUTORTS&t;0x04&t;&t;/* Auto RTS */
DECL|macro|TXDNRZI
mdefine_line|#define TXDNRZI 0x08&t;&t;/* TxD Pulled High in SDLC NRZI mode */
DECL|macro|FASTDTR
mdefine_line|#define FASTDTR 0x10&t;&t;/* Fast DTR/REQ Mode */
DECL|macro|CRCCBCR
mdefine_line|#define CRCCBCR&t;0x20&t;&t;/* CRC Check Bytes Completely Received */
DECL|macro|EXTRDEN
mdefine_line|#define EXTRDEN&t;0x40&t;&t;/* Extended Read Enabled */
multiline_comment|/* Write Register 15 (external/status interrupt control) */
DECL|macro|SHDLCE
mdefine_line|#define SHDLCE&t;1&t;&t;/* SDLC/HDLC Enhancements Enable */
DECL|macro|FIFOE
mdefine_line|#define FIFOE&t;4&t;&t;/* FIFO Enable */
multiline_comment|/* Read Register 6 (frame status FIFO) */
DECL|macro|BCLSB
mdefine_line|#define BCLSB&t;0xff&t;&t;/* LSB of 14 bits count */
multiline_comment|/* Read Register 7 (frame status FIFO) */
DECL|macro|BCMSB
mdefine_line|#define BCMSB&t;0x3f&t;&t;/* MSB of 14 bits count */
DECL|macro|FDA
mdefine_line|#define FDA&t;0x40&t;&t;/* FIFO Data Available Status */
DECL|macro|FOY
mdefine_line|#define FOY&t;0x80&t;&t;/* FIFO Overflow Status */
multiline_comment|/* global functions */
r_extern
r_int
id|scc_init
c_func
(paren
r_int
id|kmem_start
)paren
suffix:semicolon
macro_line|#endif&t;/* _SCC_H */
eof
