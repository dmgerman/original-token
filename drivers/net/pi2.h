DECL|macro|DMA_BUFF_SIZE
mdefine_line|#define DMA_BUFF_SIZE 2200
multiline_comment|/* Network statistics, with the same names as &squot;struct enet_statistics&squot;. */
DECL|macro|netstats
mdefine_line|#define netstats enet_statistics
DECL|macro|ON
mdefine_line|#define ON 1
DECL|macro|OFF
mdefine_line|#define OFF 0
multiline_comment|/* Register offset info, specific to the PI&n; * E.g., to read the data port on channel A, use&n; *  inportb(pichan[dev].base + CHANA + DATA)&n; */
DECL|macro|CHANB
mdefine_line|#define CHANB   0   /* Base of channel B regs */
DECL|macro|CHANA
mdefine_line|#define CHANA   2   /* Base of channel A regs */
multiline_comment|/* 8530 ports on each channel */
DECL|macro|CTL
mdefine_line|#define CTL 0
DECL|macro|DATA
mdefine_line|#define DATA    1
DECL|macro|DMAEN
mdefine_line|#define DMAEN   0x4 /* Offset off DMA Enable register */
multiline_comment|/* Timer chip offsets */
DECL|macro|TMR0
mdefine_line|#define TMR0    0x8 /* Offset of timer 0 register */
DECL|macro|TMR1
mdefine_line|#define TMR1    0x9 /* Offset of timer 1 register */
DECL|macro|TMR2
mdefine_line|#define TMR2    0xA /* Offset of timer 2 register */
DECL|macro|TMRCMD
mdefine_line|#define TMRCMD  0xB /* Offset of timer command register */
multiline_comment|/* Timer chip equates */
DECL|macro|SC0
mdefine_line|#define SC0 0x00 /* Select counter 0 */
DECL|macro|SC1
mdefine_line|#define SC1 0x40 /* Select counter 1 */
DECL|macro|SC2
mdefine_line|#define SC2 0x80 /* Select counter 2 */
DECL|macro|CLATCH
mdefine_line|#define CLATCH  0x00 /* Counter latching operation */
DECL|macro|MSB
mdefine_line|#define MSB 0x20 /* Read/load MSB only */
DECL|macro|LSB
mdefine_line|#define LSB 0x10 /* Read/load LSB only */
DECL|macro|LSB_MSB
mdefine_line|#define LSB_MSB 0x30 /* Read/load LSB, then MSB */
DECL|macro|MODE0
mdefine_line|#define MODE0   0x00 /* Interrupt on terminal count */
DECL|macro|MODE1
mdefine_line|#define MODE1   0x02 /* Programmable one shot */
DECL|macro|MODE2
mdefine_line|#define MODE2   0x04 /* Rate generator */
DECL|macro|MODE3
mdefine_line|#define MODE3   0x06 /* Square wave rate generator */
DECL|macro|MODE4
mdefine_line|#define MODE4   0x08 /* Software triggered strobe */
DECL|macro|MODE5
mdefine_line|#define MODE5   0x0a /* Hardware triggered strobe */
DECL|macro|BCD
mdefine_line|#define BCD 0x01 /* BCD counter */
multiline_comment|/* DMA controller registers */
DECL|macro|DMA_STAT
mdefine_line|#define DMA_STAT    8   /* DMA controller status register */
DECL|macro|DMA_CMD
mdefine_line|#define DMA_CMD     8   /* DMA controller command register */
DECL|macro|DMA_MASK
mdefine_line|#define DMA_MASK        10  /* DMA controller mask register */
DECL|macro|DMA_MODE
mdefine_line|#define DMA_MODE        11  /* DMA controller mode register */
DECL|macro|DMA_RESETFF
mdefine_line|#define DMA_RESETFF 12  /* DMA controller first/last flip flop  */
multiline_comment|/* DMA data */
DECL|macro|DMA_DISABLE
mdefine_line|#define DMA_DISABLE (0x04)  /* Disable channel n */
DECL|macro|DMA_ENABLE
mdefine_line|#define DMA_ENABLE  (0x00)  /* Enable channel n */
multiline_comment|/* Single transfers, incr. address, auto init, writes, ch. n */
DECL|macro|DMA_RX_MODE
mdefine_line|#define DMA_RX_MODE (0x54)
multiline_comment|/* Single transfers, incr. address, no auto init, reads, ch. n */
DECL|macro|DMA_TX_MODE
mdefine_line|#define DMA_TX_MODE (0x48)
DECL|macro|SINGLE
mdefine_line|#define SINGLE 3686400
DECL|macro|DOUBLE
mdefine_line|#define DOUBLE 7372800
DECL|macro|SIOCGPIPARAM
mdefine_line|#define SIOCGPIPARAM&t;&t;0x5000&t;/* get PI parameters */
DECL|macro|SIOCSPIPARAM
mdefine_line|#define SIOCSPIPARAM&t;&t;0x5001&t;/* set */
DECL|macro|SIOCGPIBAUD
mdefine_line|#define SIOCGPIBAUD&t;&t;0x5002&t;/* get only baud rate */
DECL|macro|SIOCSPIBAUD
mdefine_line|#define SIOCSPIBAUD&t;&t;0x5003&t;
DECL|macro|SIOCGPIDMA
mdefine_line|#define SIOCGPIDMA&t;&t;0x5004&t;/* get only DMA */
DECL|macro|SIOCSPIDMA
mdefine_line|#define SIOCSPIDMA&t;&t;0x5005&t;
DECL|macro|SIOCGPIIRQ
mdefine_line|#define SIOCGPIIRQ&t;&t;0x5006&t;/* get only IRQ */
DECL|macro|SIOCSPIIRQ
mdefine_line|#define SIOCSPIIRQ&t;&t;0x5007&t;
DECL|struct|pi_req
r_struct
id|pi_req
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
DECL|member|clockmode
r_int
id|clockmode
suffix:semicolon
DECL|member|txdelay
r_int
id|txdelay
suffix:semicolon
DECL|member|persist
r_int
r_char
id|persist
suffix:semicolon
DECL|member|slotime
r_int
id|slotime
suffix:semicolon
DECL|member|squeldelay
r_int
id|squeldelay
suffix:semicolon
DECL|member|dmachan
r_int
id|dmachan
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Information that needs to be kept for each channel. */
DECL|struct|pi_local
r_struct
id|pi_local
(brace
DECL|member|stats
r_struct
id|netstats
id|stats
suffix:semicolon
multiline_comment|/* %%%dp*/
DECL|member|open_time
r_int
id|open_time
suffix:semicolon
multiline_comment|/* Useless example local info. */
DECL|member|xtal
r_int
r_int
id|xtal
suffix:semicolon
DECL|member|rcvbuf
r_struct
id|mbuf
op_star
id|rcvbuf
suffix:semicolon
multiline_comment|/* Buffer for current rx packet */
DECL|member|rxdmabuf1
r_struct
id|mbuf
op_star
id|rxdmabuf1
suffix:semicolon
multiline_comment|/* DMA rx buffer */
DECL|member|rxdmabuf2
r_struct
id|mbuf
op_star
id|rxdmabuf2
suffix:semicolon
multiline_comment|/* DMA rx buffer */
DECL|member|bufsiz
r_int
id|bufsiz
suffix:semicolon
multiline_comment|/* Size of rcvbuf */
DECL|member|rcp
r_char
op_star
id|rcp
suffix:semicolon
multiline_comment|/* Pointer into rcvbuf */
DECL|member|sndq
r_struct
id|sk_buff_head
id|sndq
suffix:semicolon
multiline_comment|/* Packets awaiting transmission */
DECL|member|sndcnt
r_int
id|sndcnt
suffix:semicolon
multiline_comment|/* Number of packets on sndq */
DECL|member|sndbuf
r_struct
id|sk_buff
op_star
id|sndbuf
suffix:semicolon
multiline_comment|/* Current buffer being transmitted */
DECL|member|txdmabuf
r_char
op_star
id|txdmabuf
suffix:semicolon
multiline_comment|/* Transmit DMA buffer */
DECL|member|txptr
r_char
op_star
id|txptr
suffix:semicolon
multiline_comment|/* Used by B port tx */
DECL|member|txcnt
r_int
id|txcnt
suffix:semicolon
DECL|member|tstate
r_char
id|tstate
suffix:semicolon
multiline_comment|/* Transmitter state */
DECL|macro|IDLE
mdefine_line|#define IDLE    0       /* Transmitter off, no data pending */
DECL|macro|ACTIVE
mdefine_line|#define ACTIVE  1       /* Transmitter on, sending data */
DECL|macro|UNDERRUN
mdefine_line|#define UNDERRUN 2      /* Transmitter on, flushing CRC */
DECL|macro|FLAGOUT
mdefine_line|#define FLAGOUT 3       /* CRC sent - attempt to start next frame */
DECL|macro|DEFER
mdefine_line|#define DEFER 4         /* Receive Active - DEFER Transmit */
DECL|macro|ST_TXDELAY
mdefine_line|#define ST_TXDELAY 5    /* Sending leading flags */
DECL|macro|CRCOUT
mdefine_line|#define CRCOUT 6
DECL|member|rstate
r_char
id|rstate
suffix:semicolon
multiline_comment|/* Set when !DCD goes to 0 (TRUE) */
multiline_comment|/* Normal state is ACTIVE if Receive enabled */
DECL|macro|RXERROR
mdefine_line|#define RXERROR 2       /* Error -- Aborting current Frame */
DECL|macro|RXABORT
mdefine_line|#define RXABORT 3       /* ABORT sequence detected */
DECL|macro|TOOBIG
mdefine_line|#define TOOBIG 4        /* too large a frame to store */
DECL|member|dev
r_int
id|dev
suffix:semicolon
multiline_comment|/* Device number */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/* Base of I/O registers */
DECL|member|cardbase
r_int
id|cardbase
suffix:semicolon
multiline_comment|/* Base address of card */
DECL|member|stata
r_int
id|stata
suffix:semicolon
multiline_comment|/* address of Channel A status regs */
DECL|member|statb
r_int
id|statb
suffix:semicolon
multiline_comment|/* address of Channel B status regs */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* Line speed, bps */
DECL|member|clockmode
r_int
id|clockmode
suffix:semicolon
multiline_comment|/* tapr 9600 modem clocking option */
DECL|member|txdelay
r_int
id|txdelay
suffix:semicolon
multiline_comment|/* Transmit Delay 10 ms/cnt */
DECL|member|persist
r_int
r_char
id|persist
suffix:semicolon
multiline_comment|/* Persistence (0-255) as a % */
DECL|member|slotime
r_int
id|slotime
suffix:semicolon
multiline_comment|/* Delay to wait on persistence hit */
DECL|member|squeldelay
r_int
id|squeldelay
suffix:semicolon
multiline_comment|/* Delay after XMTR OFF for squelch tail */
DECL|member|iface
r_struct
id|iface
op_star
id|iface
suffix:semicolon
multiline_comment|/* Associated interface */
DECL|member|dmachan
r_int
id|dmachan
suffix:semicolon
multiline_comment|/* DMA channel for this port */
)brace
suffix:semicolon
macro_line|#endif
eof
