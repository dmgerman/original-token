multiline_comment|/*&n; * pt.h: Linux device driver for the Gracilis PackeTwin&n; * Copyright (C) 1995 Craig Small VK2XLZ (vk2xlz@vk2xlz.ampr.org.)&n; *&n; * Please read the notice appearing at the top of the file pt.c&n; */
DECL|macro|DMA_BUFF_SIZE
mdefine_line|#define DMA_BUFF_SIZE 2200
DECL|macro|ON
mdefine_line|#define ON 1
DECL|macro|OFF
mdefine_line|#define OFF 0
multiline_comment|/* Register offset info, specific to the PT&n; * E.g., to read the data port on channel A, use&n; *  inportb(pichan[dev].base + CHANA + DATA)&n; */
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
mdefine_line|#define DMAEN   0x8 /* Offset off DMA Enable register */
multiline_comment|/* Timer chip offsets */
DECL|macro|TMR0
mdefine_line|#define TMR0    0x4 /* Offset of timer 0 register */
DECL|macro|TMR1
mdefine_line|#define TMR1    0x5 /* Offset of timer 1 register */
DECL|macro|TMR2
mdefine_line|#define TMR2    0x6 /* Offset of timer 2 register */
DECL|macro|TMRCMD
mdefine_line|#define TMRCMD  0x7 /* Offset of timer command register */
DECL|macro|INT_REG
mdefine_line|#define INT_REG&t;0x8
DECL|macro|TMR1CLR
mdefine_line|#define TMR1CLR 0x9
DECL|macro|TMR2CLR
mdefine_line|#define TMR2CLR 0xa
multiline_comment|/* Interrupt register equates */
DECL|macro|PT_SCC_MSK
mdefine_line|#define PT_SCC_MSK&t;0x1
DECL|macro|PT_TMR1_MSK
mdefine_line|#define PT_TMR1_MSK&t;0x2
DECL|macro|PT_TMR2_MSK
mdefine_line|#define PT_TMR2_MSK&t;0x4
multiline_comment|/* Serial/interrupt register equates */
DECL|macro|PT_DTRA_ON
mdefine_line|#define PT_DTRA_ON&t;0x1
DECL|macro|PT_DTRB_ON
mdefine_line|#define PT_DTRB_ON&t;0x2
DECL|macro|PT_EXTCLKA
mdefine_line|#define PT_EXTCLKA&t;0x4
DECL|macro|PT_EXTCLKB
mdefine_line|#define PT_EXTCLKB&t;0x8
DECL|macro|PT_LOOPA_ON
mdefine_line|#define PT_LOOPA_ON&t;0x10
DECL|macro|PT_LOOPB_ON
mdefine_line|#define PT_LOOPB_ON&t;0x20
DECL|macro|PT_EI
mdefine_line|#define PT_EI&t;&t;0x80
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
multiline_comment|/* Write registers */
DECL|macro|DMA_CFG
mdefine_line|#define DMA_CFG&t;&t;0x08
DECL|macro|SERIAL_CFG
mdefine_line|#define SERIAL_CFG&t;0x09
DECL|macro|INT_CFG
mdefine_line|#define INT_CFG&t;&t;0x09&t;/* shares with serial config */
DECL|macro|DMA_CLR_FF
mdefine_line|#define DMA_CLR_FF&t;0x0a
DECL|macro|SINGLE
mdefine_line|#define SINGLE 3686400
DECL|macro|DOUBLE
mdefine_line|#define DOUBLE 7372800
DECL|macro|XTAL
mdefine_line|#define XTAL   ((long) 6144000L)
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
DECL|struct|pt_req
r_struct
id|pt_req
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
multiline_comment|/* SCC Interrupt vectors, if we have set &squot;status low&squot; */
DECL|macro|CHBTxIV
mdefine_line|#define CHBTxIV&t;&t;0x00
DECL|macro|CHBEXTIV
mdefine_line|#define CHBEXTIV&t;0x02
DECL|macro|CHBRxIV
mdefine_line|#define CHBRxIV&t;&t;0x04
DECL|macro|CHBSRCIV
mdefine_line|#define CHBSRCIV&t;0x06
DECL|macro|CHATxIV
mdefine_line|#define CHATxIV&t;&t;0x08
DECL|macro|CHAEXTIV
mdefine_line|#define CHAEXTIV&t;0x0a
DECL|macro|CHARxIV
mdefine_line|#define CHARxIV&t;&t;0x0c
DECL|macro|CHASRCIV
mdefine_line|#define CHASRCIV&t;0x0e
macro_line|#ifdef __KERNEL__
multiline_comment|/* Information that needs to be kept for each channel. */
DECL|struct|pt_local
r_struct
id|pt_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
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
multiline_comment|/* Size of rcvbuf &t;&t;&t;*/
DECL|member|rcp
r_char
op_star
id|rcp
suffix:semicolon
multiline_comment|/* Pointer into rcvbuf &t;&t;&t;*/
DECL|member|sndq
r_struct
id|sk_buff_head
id|sndq
suffix:semicolon
multiline_comment|/* Packets awaiting transmission &t;*/
DECL|member|sndcnt
r_int
id|sndcnt
suffix:semicolon
multiline_comment|/* Number of packets on sndq &t;&t;*/
DECL|member|sndbuf
r_struct
id|sk_buff
op_star
id|sndbuf
suffix:semicolon
multiline_comment|/* Current buffer being transmitted&t;*/
DECL|member|txdmabuf
r_char
op_star
id|txdmabuf
suffix:semicolon
multiline_comment|/* Transmit DMA buffer &t;&t;&t;*/
DECL|member|txptr
r_char
op_star
id|txptr
suffix:semicolon
multiline_comment|/* Used by B port tx &t;&t;&t;*/
DECL|member|txcnt
r_int
id|txcnt
suffix:semicolon
DECL|member|tstate
r_char
id|tstate
suffix:semicolon
multiline_comment|/* Transmitter state &t;&t;&t;*/
DECL|macro|IDLE
mdefine_line|#define IDLE    0       /* Transmitter off, no data pending &t;&t;*/
DECL|macro|ACTIVE
mdefine_line|#define ACTIVE  1       /* Transmitter on, sending data &t;&t;*/
DECL|macro|UNDERRUN
mdefine_line|#define UNDERRUN 2      /* Transmitter on, flushing CRC&t;&t;&t;*/
DECL|macro|FLAGOUT
mdefine_line|#define FLAGOUT 3       /* CRC sent - attempt to start next frame&t;*/
DECL|macro|DEFER
mdefine_line|#define DEFER 4         /* Receive Active - DEFER Transmit&t;&t;*/
DECL|macro|ST_TXDELAY
mdefine_line|#define ST_TXDELAY 5    /* Sending leading flags&t;&t;&t;*/
DECL|macro|CRCOUT
mdefine_line|#define CRCOUT 6
DECL|member|rstate
r_char
id|rstate
suffix:semicolon
multiline_comment|/* Set when !DCD goes to 0 (TRUE)&t;&t;*/
multiline_comment|/* Normal state is ACTIVE if Receive enabled */
DECL|macro|RXERROR
mdefine_line|#define RXERROR 2       /* Error -- Aborting current Frame&t;&t;*/
DECL|macro|RXABORT
mdefine_line|#define RXABORT 3       /* ABORT sequence detected&t;&t;&t;*/
DECL|macro|TOOBIG
mdefine_line|#define TOOBIG 4        /* too large a frame to store&t;&t;&t;*/
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
DECL|member|saved_RR0
r_char
id|saved_RR0
suffix:semicolon
multiline_comment|/* The saved version of RR) that we compare with */
DECL|member|nrzi
r_int
id|nrzi
suffix:semicolon
multiline_comment|/* Do we use NRZI (or NRZ) */
)brace
suffix:semicolon
macro_line|#endif
eof
