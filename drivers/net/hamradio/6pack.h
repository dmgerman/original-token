multiline_comment|/*&n; * 6pack.h&t;Define the 6pack device driver interface and constants.&n; *&n; * NOTE:&t;THIS FILE WILL BE MOVED TO THE LINUX INCLUDE DIRECTORY&n; *&t;&t;AS SOON AS POSSIBLE!&n; *&n; * Version:&t;@(#)6pack.h&t;0.3.0&t;04/07/98&n; *&n; * Fixes:&n; *&n; * Author:&t;Andreas K&#xfffd;nsgen &lt;ajk@iehk.rwth-aachen.de&gt;&n; *&n; *&t;&t;This file is derived from slip.h, written by&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_6PACK_H
DECL|macro|_LINUX_6PACK_H
mdefine_line|#define _LINUX_6PACK_H
DECL|macro|SIXPACK_VERSION
mdefine_line|#define SIXPACK_VERSION    &quot;Revision: 0.3.0&quot;
macro_line|#ifdef __KERNEL__
multiline_comment|/* sixpack priority commands */
DECL|macro|SIXP_SEOF
mdefine_line|#define SIXP_SEOF&t;0x40&t;/* start and end of a 6pack frame */
DECL|macro|SIXP_TX_URUN
mdefine_line|#define SIXP_TX_URUN&t;0x48&t;/* transmit overrun */
DECL|macro|SIXP_RX_ORUN
mdefine_line|#define SIXP_RX_ORUN&t;0x50&t;/* receive overrun */
DECL|macro|SIXP_RX_BUF_OVL
mdefine_line|#define SIXP_RX_BUF_OVL&t;0x58&t;/* receive buffer overflow */
DECL|macro|SIXP_CHKSUM
mdefine_line|#define SIXP_CHKSUM&t;0xFF&t;/* valid checksum of a 6pack frame */
multiline_comment|/* masks to get certain bits out of the status bytes sent by the TNC */
DECL|macro|SIXP_CMD_MASK
mdefine_line|#define SIXP_CMD_MASK&t;&t;0xC0
DECL|macro|SIXP_CHN_MASK
mdefine_line|#define SIXP_CHN_MASK&t;&t;0x07
DECL|macro|SIXP_PRIO_CMD_MASK
mdefine_line|#define SIXP_PRIO_CMD_MASK&t;0x80
DECL|macro|SIXP_STD_CMD_MASK
mdefine_line|#define SIXP_STD_CMD_MASK&t;0x40
DECL|macro|SIXP_PRIO_DATA_MASK
mdefine_line|#define SIXP_PRIO_DATA_MASK&t;0x38
DECL|macro|SIXP_TX_MASK
mdefine_line|#define SIXP_TX_MASK&t;&t;0x20
DECL|macro|SIXP_RX_MASK
mdefine_line|#define SIXP_RX_MASK&t;&t;0x10
DECL|macro|SIXP_RX_DCD_MASK
mdefine_line|#define SIXP_RX_DCD_MASK&t;0x18
DECL|macro|SIXP_LEDS_ON
mdefine_line|#define SIXP_LEDS_ON&t;&t;0x78
DECL|macro|SIXP_LEDS_OFF
mdefine_line|#define SIXP_LEDS_OFF&t;&t;0x60
DECL|macro|SIXP_CON
mdefine_line|#define SIXP_CON&t;&t;0x08
DECL|macro|SIXP_STA
mdefine_line|#define SIXP_STA&t;&t;0x10
DECL|macro|SIXP_FOUND_TNC
mdefine_line|#define SIXP_FOUND_TNC&t;&t;0xe9
DECL|macro|SIXP_CON_ON
mdefine_line|#define SIXP_CON_ON&t;&t;0x68
DECL|macro|SIXP_DCD_MASK
mdefine_line|#define SIXP_DCD_MASK&t;&t;0x08
DECL|macro|SIXP_DAMA_OFF
mdefine_line|#define SIXP_DAMA_OFF&t;&t;0
multiline_comment|/* default level 2 parameters */
DECL|macro|SIXP_TXDELAY
mdefine_line|#define SIXP_TXDELAY&t;&t;&t;25&t;/* in 10 ms */
DECL|macro|SIXP_PERSIST
mdefine_line|#define SIXP_PERSIST&t;&t;&t;50&t;/* in 256ths */
DECL|macro|SIXP_SLOTTIME
mdefine_line|#define SIXP_SLOTTIME&t;&t;&t;10&t;/* in 10 ms */
DECL|macro|SIXP_INIT_RESYNC_TIMEOUT
mdefine_line|#define SIXP_INIT_RESYNC_TIMEOUT&t;150&t;/* in 10 ms */
DECL|macro|SIXP_RESYNC_TIMEOUT
mdefine_line|#define SIXP_RESYNC_TIMEOUT&t;&t;500&t;/* in 10 ms */
multiline_comment|/* 6pack configuration. */
DECL|macro|SIXP_NRUNIT
mdefine_line|#define SIXP_NRUNIT&t;&t;&t;256&t;/* MAX number of 6pack channels */
DECL|macro|SIXP_MTU
mdefine_line|#define SIXP_MTU&t;&t;&t;256&t;/* Default MTU */
DECL|enum|sixpack_flags
r_enum
id|sixpack_flags
(brace
DECL|enumerator|SIXPF_INUSE
id|SIXPF_INUSE
comma
multiline_comment|/* Channel in use&t;*/
DECL|enumerator|SIXPF_ERROR
id|SIXPF_ERROR
comma
multiline_comment|/* Parity, etc. error&t;*/
)brace
suffix:semicolon
DECL|struct|sixpack
r_struct
id|sixpack
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
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
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
DECL|member|raw_buf
r_int
r_char
id|raw_buf
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cooked_buf
r_int
r_char
id|cooked_buf
(braket
l_int|400
)braket
suffix:semicolon
DECL|member|rx_count
r_int
r_int
id|rx_count
suffix:semicolon
DECL|member|rx_count_cooked
r_int
r_int
id|rx_count_cooked
suffix:semicolon
multiline_comment|/* 6pack interface statistics. */
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
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
multiline_comment|/* inbound bytes counter        */
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
multiline_comment|/* outboud bytes counter        */
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
multiline_comment|/* Planned stuff                */
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
multiline_comment|/* Frame bigger then 6pack buf. */
multiline_comment|/* Detailed 6pack statistics. */
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
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flag values/ mode etc&t;*/
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* 6pack mode&t;&t;&t;*/
multiline_comment|/* 6pack stuff */
DECL|member|tx_delay
r_int
r_char
id|tx_delay
suffix:semicolon
DECL|member|persistance
r_int
r_char
id|persistance
suffix:semicolon
DECL|member|slottime
r_int
r_char
id|slottime
suffix:semicolon
DECL|member|duplex
r_int
r_char
id|duplex
suffix:semicolon
DECL|member|led_state
r_int
r_char
id|led_state
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|status1
r_int
r_char
id|status1
suffix:semicolon
DECL|member|status2
r_int
r_char
id|status2
suffix:semicolon
DECL|member|tx_enable
r_int
r_char
id|tx_enable
suffix:semicolon
DECL|member|tnc_ok
r_int
r_char
id|tnc_ok
suffix:semicolon
multiline_comment|/*  unsigned char retval; */
DECL|member|tx_t
r_struct
id|timer_list
id|tx_t
suffix:semicolon
DECL|member|resync_t
r_struct
id|timer_list
id|resync_t
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct sixpack */
multiline_comment|/* should later be moved to include/net/ax25.h */
DECL|macro|AX25_6PACK_HEADER_LEN
mdefine_line|#define AX25_6PACK_HEADER_LEN 0
DECL|macro|SIXPACK_MAGIC
mdefine_line|#define SIXPACK_MAGIC 0x5304
r_extern
r_int
id|sixpack_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_6PACK.H */
eof
