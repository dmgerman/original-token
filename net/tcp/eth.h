multiline_comment|/* eth.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
macro_line|#ifndef _TCP_ETH_H
DECL|macro|_TCP_ETH_H
mdefine_line|#define _TCP_ETH_H
DECL|macro|ETHER_MIN_LEN
mdefine_line|#define ETHER_MIN_LEN 64
DECL|macro|ETHER_ADDR_LEN
mdefine_line|#define ETHER_ADDR_LEN 6
DECL|macro|ETHERTYPE_ARP
mdefine_line|#define ETHERTYPE_ARP 0x806
DECL|macro|ETHERTYPE_IP
mdefine_line|#define ETHERTYPE_IP  0x800
DECL|macro|ETHER_TYPE
mdefine_line|#define ETHER_TYPE 1
multiline_comment|/* Reciever modes */
DECL|macro|ETH_MODE_MONITOR
mdefine_line|#define ETH_MODE_MONITOR&t;&t;1&t;/* Monitor mode - no receive */
DECL|macro|ETH_MODE_PHYSICAL
mdefine_line|#define ETH_MODE_PHYSICAL&t;&t;2&t;/* Physical address receive only */
DECL|macro|ETH_MODE_BROADCAST
mdefine_line|#define ETH_MODE_BROADCAST&t;&t;3&t;/* Broadcast receive + mode 2 */
DECL|macro|ETH_MODE_MULTICAST
mdefine_line|#define ETH_MODE_MULTICAST&t;&t;4&t;/* Multicast receive + mode 3 */
DECL|macro|ETH_MODE_PROMISCUOUS
mdefine_line|#define ETH_MODE_PROMISCUOUS&t;&t;5&t;/* Promiscuous mode - receive all */
DECL|macro|WD_RX_SAVE_ERRORS
mdefine_line|#define WD_RX_SAVE_ERRORS&t;1&t;/* save error packets */
DECL|macro|WD_RX_RUNT
mdefine_line|#define WD_RX_RUNT&t;&t;2&t;/* accept runt packets */
DECL|macro|WD_RX_BROAD
mdefine_line|#define WD_RX_BROAD&t;&t;4&t;/* accept broadcast packets */
DECL|macro|WD_RX_MULTI
mdefine_line|#define WD_RX_MULTI&t;&t;8&t;/* accept multicast packets */
DECL|macro|WD_RX_PROM
mdefine_line|#define WD_RX_PROM&t;&t;0x10&t;/* accept all packets */
DECL|macro|WD_RX_MON
mdefine_line|#define WD_RX_MON&t;&t;0x20&t;/* monitor mode (just count packets) */
DECL|macro|NET16
mdefine_line|#define NET16(x) (((x&amp;0xff)&lt;&lt;8)|((x&gt;&gt;8)&amp;0xff))
DECL|struct|enet_header
r_struct
id|enet_header
(brace
DECL|member|daddr
r_int
r_char
id|daddr
(braket
id|ETHER_ADDR_LEN
)braket
suffix:semicolon
DECL|member|saddr
r_int
r_char
id|saddr
(braket
id|ETHER_ADDR_LEN
)braket
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ETHER_HEADER
mdefine_line|#define ETHER_HEADER sizeof(struct enet_header)
DECL|struct|enet_statistics
r_struct
id|enet_statistics
(brace
DECL|member|rx_packets
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received */
DECL|member|tx_packets
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted */
DECL|member|rx_errors
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received */
DECL|member|tx_errors
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems */
DECL|member|rx_dropped
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers */
DECL|member|tx_dropped
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux */
DECL|member|collisions
r_int
id|collisions
suffix:semicolon
multiline_comment|/* total number of collisions */
DECL|member|multicast
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received */
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver overwrote ring buffer in card */
DECL|member|rx_crc_errors
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* received packet with crc error */
DECL|member|rx_frame_errors
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* received frame alignment error */
DECL|member|rx_fifo_errors
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* receiver fifo overrun */
DECL|member|rx_missed_errors
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet */
multiline_comment|/* detailed tx_errors */
DECL|member|tx_aborted_errors
r_int
id|tx_aborted_errors
suffix:semicolon
DECL|member|tx_carrier_errors
r_int
id|tx_carrier_errors
suffix:semicolon
DECL|member|tx_fifo_errors
r_int
id|tx_fifo_errors
suffix:semicolon
DECL|member|tx_heartbeat_errors
r_int
id|tx_heartbeat_errors
suffix:semicolon
DECL|member|tx_window_errors
r_int
id|tx_window_errors
suffix:semicolon
)brace
suffix:semicolon
r_void
id|print_eth
c_func
(paren
r_struct
id|enet_header
op_star
id|eth
)paren
suffix:semicolon
r_int
id|eth_hard_header
(paren
r_int
r_char
op_star
id|buff
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|saddr
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|eth_rebuild_header
c_func
(paren
r_void
op_star
id|eth
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|eth_add_arp
(paren
r_int
r_int
id|addr
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
r_int
id|eth_type_trans
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
eof
