multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the Ethernet IEE 802.3 interface.&n; *&n; * Version:&t;@(#)if_ether.h&t;1.0.1&t;03/15/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ETHER_H
DECL|macro|_LINUX_IF_ETHER_H
mdefine_line|#define _LINUX_IF_ETHER_H
multiline_comment|/* IEEE 802.3 Ethernet magic constants. */
DECL|macro|ETH_ALEN
mdefine_line|#define ETH_ALEN&t;6&t;&t;/* #bytes in eth addr&t;&t;*/
DECL|macro|ETH_HLEN
mdefine_line|#define ETH_HLEN&t;14&t;&t;/* #bytes in eth header&t;&t;*/
DECL|macro|ETH_ZLEN
mdefine_line|#define ETH_ZLEN&t;64&t;&t;/* min #bytes in frame&t;&t;*/
DECL|macro|ETH_FLEN
mdefine_line|#define ETH_FLEN&t;1536&t;&t;/* max #bytes in frame&t;&t;*/
DECL|macro|ETH_DLEN
mdefine_line|#define ETH_DLEN&t;(ETH_FLEN - ETH_HLEN)&t;/* max #bytes of data&t;*/
multiline_comment|/* These are the defined Ethernet Protocol ID&squot;s. */
DECL|macro|ETH_P_LOOP
mdefine_line|#define ETH_P_LOOP&t;0x0060&t;&t;/* Ethernet Loopback packet&t;*/
DECL|macro|ETH_P_ECHO
mdefine_line|#define ETH_P_ECHO&t;0x0200&t;&t;/* Ethernet Echo packet&t;&t;*/
DECL|macro|ETH_P_PUP
mdefine_line|#define ETH_P_PUP&t;0x0400&t;&t;/* Xerox PUP packet&t;&t;*/
DECL|macro|ETH_P_IP
mdefine_line|#define ETH_P_IP&t;0x0800&t;&t;/* Internet Protocol packet&t;*/
DECL|macro|ETH_P_ARP
mdefine_line|#define ETH_P_ARP&t;0x0806&t;&t;/* Address Resolution packet&t;*/
DECL|macro|ETH_P_RARP
mdefine_line|#define ETH_P_RARP      0x8035&t;&t;/* Reverse Addr Res packet&t;*/
DECL|macro|ETH_P_X25
mdefine_line|#define ETH_P_X25&t;0x0805&t;&t;/* CCITT X.25&t;&t;&t;*/
DECL|macro|ETH_P_IPX
mdefine_line|#define ETH_P_IPX&t;0x8137&t;&t;/* IPX over DIX&t;&t;&t;*/
DECL|macro|ETH_P_802_3
mdefine_line|#define ETH_P_802_3&t;0x0001&t;&t;/* Dummy type for 802.3 frames  */
DECL|macro|ETH_P_AX25
mdefine_line|#define ETH_P_AX25&t;0x0002&t;&t;/* Dummy protocol id for AX.25  */
DECL|macro|ETH_P_ALL
mdefine_line|#define ETH_P_ALL&t;0x0003&t;&t;/* Every packet (be careful!!!) */
multiline_comment|/* Define the Ethernet Broadcast Address (48 bits set to &quot;1&quot;). */
DECL|macro|ETH_A_BCAST
mdefine_line|#define ETH_A_BCAST     &quot;&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&bslash;377&quot;
multiline_comment|/* This is an Ethernet frame header. */
DECL|struct|ethhdr
r_struct
id|ethhdr
(brace
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination eth addr&t;*/
DECL|member|h_source
r_int
r_char
id|h_source
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* source ether addr&t;*/
DECL|member|h_proto
r_int
r_int
id|h_proto
suffix:semicolon
multiline_comment|/* packet type ID field&t;*/
)brace
suffix:semicolon
multiline_comment|/* This is the complete Ethernet frame. */
DECL|struct|ethframe
r_struct
id|ethframe
(brace
DECL|member|f_hdr
r_struct
id|ethhdr
id|f_hdr
suffix:semicolon
multiline_comment|/* frame header&t;&t;*/
DECL|member|f_data
r_char
id|f_data
(braket
id|ETH_DLEN
)braket
suffix:semicolon
multiline_comment|/* frame data (variable)*/
)brace
suffix:semicolon
multiline_comment|/* Receiver modes */
DECL|macro|ETH_MODE_MONITOR
mdefine_line|#define ETH_MODE_MONITOR&t;1&t;/* Monitor mode - no receive&t;*/
DECL|macro|ETH_MODE_PHYS
mdefine_line|#define ETH_MODE_PHYS&t;&t;2&t;/* Physical address receive only */
DECL|macro|ETH_MODE_BCAST
mdefine_line|#define ETH_MODE_BCAST&t;&t;3&t;/* Broadcast receive + mode 2&t;*/
DECL|macro|ETH_MODE_MCAST
mdefine_line|#define ETH_MODE_MCAST&t;&t;4&t;/* Multicast receive + mode 3&t;*/
DECL|macro|ETH_MODE_PROMISC
mdefine_line|#define ETH_MODE_PROMISC&t;5&t;/* Promiscuous mode - receive all */
multiline_comment|/* Ethernet statistics collection data. */
DECL|struct|enet_statistics
r_struct
id|enet_statistics
(brace
DECL|member|rx_packets
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received&t;*/
DECL|member|tx_packets
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted&t;*/
DECL|member|rx_errors
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received&t;&t;*/
DECL|member|tx_errors
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems&t;*/
DECL|member|rx_dropped
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers&t;*/
DECL|member|tx_dropped
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux&t;*/
DECL|member|multicast
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received&t;*/
DECL|member|collisions
r_int
id|collisions
suffix:semicolon
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver ring buff overflow&t;*/
DECL|member|rx_crc_errors
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* recved pkt with crc error&t;*/
DECL|member|rx_frame_errors
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* recv&squot;d frame alignment error */
DECL|member|rx_fifo_errors
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* recv&squot;r fifo overrun&t;&t;*/
DECL|member|rx_missed_errors
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet&t;*/
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
macro_line|#endif&t;/* _LINUX_IF_ETHER_H */
eof
