multiline_comment|/*&n; * slip.h&t;Define the SLIP device driver interface and constants.&n; *&n; * NOTE:&t;THIS FILE WILL BE MOVED TO THE LINUX INCLUDE DIRECTORY&n; *&t;&t;AS SOON AS POSSIBLE!&n; *&n; * Version:&t;@(#)slip.h&t;1.2.0&t;03/28/93&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;: &t;Added slip mtu field.&n; *&t;&t;Matt Dillon&t;:&t;Printable slip (borrowed from net2e)&n; *&t;&t;Alan Cox&t;:&t;Added SL_SLIP_LOTS&n; * &t;Dmitry Gorodchanin      :       A lot of changes in the &squot;struct slip&squot;&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_SLIP_H
DECL|macro|_LINUX_SLIP_H
mdefine_line|#define _LINUX_SLIP_H
multiline_comment|/* SLIP configuration. */
macro_line|#ifndef SL_SLIP_LOTS
DECL|macro|SL_NRUNIT
mdefine_line|#define SL_NRUNIT&t;4&t;&t;/* number of SLIP channels&t;*/
macro_line|#else
DECL|macro|SL_NRUNIT
mdefine_line|#define SL_NRUNIT&t;16
macro_line|#endif
DECL|macro|SL_MTU
mdefine_line|#define SL_MTU&t;&t;296&t;&t;/* 296; I am used to 600- FvK&t;*/
multiline_comment|/* SLIP protocol characters. */
DECL|macro|END
mdefine_line|#define END             0300&t;&t;/* indicates end of frame&t;*/
DECL|macro|ESC
mdefine_line|#define ESC             0333&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|ESC_END
mdefine_line|#define ESC_END         0334&t;&t;/* ESC ESC_END means END &squot;data&squot;&t;*/
DECL|macro|ESC_ESC
mdefine_line|#define ESC_ESC         0335&t;&t;/* ESC ESC_ESC means ESC &squot;data&squot;&t;*/
DECL|struct|slip
r_struct
id|slip
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Various fields. */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;&t;*/
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
macro_line|#if defined(CONFIG_INET)
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
multiline_comment|/* for header compression &t;*/
DECL|member|cbuff
r_int
r_char
op_star
id|cbuff
suffix:semicolon
multiline_comment|/* compression buffer&t;&t;*/
macro_line|#endif
multiline_comment|/* These are pointers to the malloc()ed frame buffers. */
DECL|member|rbuff
r_int
r_char
op_star
id|rbuff
suffix:semicolon
multiline_comment|/* receiver buffer&t;&t;*/
DECL|member|rcount
r_int
id|rcount
suffix:semicolon
multiline_comment|/* received chars counter       */
DECL|member|xbuff
r_int
r_char
op_star
id|xbuff
suffix:semicolon
multiline_comment|/* transmitter buffer&t;&t;*/
DECL|member|xhead
r_int
r_char
op_star
id|xhead
suffix:semicolon
multiline_comment|/* pointer to next byte to XMIT */
DECL|member|xleft
r_int
id|xleft
suffix:semicolon
multiline_comment|/* bytes left in XMIT queue     */
multiline_comment|/* SLIP interface statistics. */
DECL|member|rx_packets
r_int
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* inbound frames counter&t;*/
DECL|member|tx_packets
r_int
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* outbound frames counter      */
DECL|member|rx_errors
r_int
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* Parity, etc. errors          */
DECL|member|tx_errors
r_int
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* Palnned stuff                */
DECL|member|rx_dropped
r_int
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* No memory for skb            */
DECL|member|tx_dropped
r_int
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* When MTU change              */
DECL|member|rx_over_errors
r_int
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* Frame bigger then SLIP buf.  */
multiline_comment|/* Detailed SLIP statistics. */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* Our mtu (to spot changes!)   */
DECL|member|buffsize
r_int
id|buffsize
suffix:semicolon
multiline_comment|/* Max buffers sizes            */
macro_line|#ifdef CONFIG_SLIP_MODE_SLIP6
DECL|member|xdata
DECL|member|xbits
r_int
id|xdata
comma
id|xbits
suffix:semicolon
multiline_comment|/* 6 bit slip controls &t;&t;*/
macro_line|#endif
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* Flag values/ mode etc&t;*/
DECL|macro|SLF_INUSE
mdefine_line|#define SLF_INUSE&t;0&t;&t;/* Channel in use               */
DECL|macro|SLF_ESCAPE
mdefine_line|#define SLF_ESCAPE&t;1               /* ESC received                 */
DECL|macro|SLF_ERROR
mdefine_line|#define SLF_ERROR&t;2               /* Parity, etc. error           */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* SLIP mode&t;&t;&t;*/
DECL|macro|SL_MODE_SLIP
mdefine_line|#define SL_MODE_SLIP&t;0
DECL|macro|SL_MODE_CSLIP
mdefine_line|#define SL_MODE_CSLIP&t;1
DECL|macro|SL_MODE_SLIP6
mdefine_line|#define SL_MODE_SLIP6&t;2&t;&t;/* Matt Dillon&squot;s printable slip */
DECL|macro|SL_MODE_CSLIP6
mdefine_line|#define SL_MODE_CSLIP6&t;(SL_MODE_SLIP6|SL_MODE_CSLIP)
DECL|macro|SL_MODE_AX25
mdefine_line|#define SL_MODE_AX25&t;4
DECL|macro|SL_MODE_ADAPTIVE
mdefine_line|#define SL_MODE_ADAPTIVE 8
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_INET
macro_line|#ifdef CONFIG_SLIP_ADAPTIVE
DECL|macro|SL_MODE_DEFAULT
mdefine_line|#define SL_MODE_DEFAULT&t;SL_MODE_ADAPTIVE
macro_line|#else  /* !CONFIG_SLIP_ADAPTIVE */
macro_line|#ifdef CONFIG_SLIP_COMPRESSED
DECL|macro|SL_MODE_DEFAULT
mdefine_line|#define SL_MODE_DEFAULT (SL_MODE_CSLIP | SL_MODE_ADAPTIVE)
macro_line|#else  /* !CONFIG_SLIP_COMPRESSED */
DECL|macro|SL_MODE_DEFAULT
mdefine_line|#define SL_MODE_DEFAULT SL_MODE_SLIP
macro_line|#endif /* CONFIG_SLIP_COMPRESSED */
macro_line|#endif /* CONFIG_SLIP_ADAPTIVE */
macro_line|#else  /* !CONFIG_INET */
DECL|macro|SL_MODE_DEFAULT
mdefine_line|#define SL_MODE_DEFAULT SL_MODE_SLIP
macro_line|#endif /* CONFIG_INET */
DECL|macro|SLIP_MAGIC
mdefine_line|#define SLIP_MAGIC 0x5302
r_extern
r_int
id|slip_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_SLIP.H */
eof
