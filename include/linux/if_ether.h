multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the Ethernet IEEE 802.3 interface.&n; *&n; * Version:&t;@(#)if_ether.h&t;1.0.1a&t;02/08/94&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@super.org&gt;&n; *&t;&t;Alan Cox, &lt;alan@cymru.net&gt;&n; *&t;&t;Steve Whitehouse, &lt;gw7rrm@eeshack3.swan.ac.uk&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ETHER_H
DECL|macro|_LINUX_IF_ETHER_H
mdefine_line|#define _LINUX_IF_ETHER_H
multiline_comment|/* IEEE 802.3 Ethernet magic constants.  The frame sizes omit the preamble&n;   and FCS/CRC (frame check sequence). */
DECL|macro|ETH_ALEN
mdefine_line|#define ETH_ALEN&t;6&t;&t;/* Octets in one ethernet addr&t; */
DECL|macro|ETH_HLEN
mdefine_line|#define ETH_HLEN&t;14&t;&t;/* Total octets in header.&t; */
DECL|macro|ETH_ZLEN
mdefine_line|#define ETH_ZLEN&t;60&t;&t;/* Min. octets in frame sans FCS */
DECL|macro|ETH_DATA_LEN
mdefine_line|#define ETH_DATA_LEN&t;1500&t;&t;/* Max. octets in payload&t; */
DECL|macro|ETH_FRAME_LEN
mdefine_line|#define ETH_FRAME_LEN&t;1514&t;&t;/* Max. octets in frame sans FCS */
multiline_comment|/* These are the defined Ethernet Protocol ID&squot;s. */
DECL|macro|ETH_P_LOOP
mdefine_line|#define ETH_P_LOOP&t;0x0060&t;&t;/* Ethernet Loopback packet&t;*/
DECL|macro|ETH_P_ECHO
mdefine_line|#define ETH_P_ECHO&t;0x0200&t;&t;/* Ethernet Echo packet&t;&t;*/
DECL|macro|ETH_P_PUP
mdefine_line|#define ETH_P_PUP&t;0x0400&t;&t;/* Xerox PUP packet&t;&t;*/
DECL|macro|ETH_P_IP
mdefine_line|#define ETH_P_IP&t;0x0800&t;&t;/* Internet Protocol packet&t;*/
DECL|macro|ETH_P_X25
mdefine_line|#define ETH_P_X25&t;0x0805&t;&t;/* CCITT X.25&t;&t;&t;*/
DECL|macro|ETH_P_ARP
mdefine_line|#define ETH_P_ARP&t;0x0806&t;&t;/* Address Resolution packet&t;*/
DECL|macro|ETH_P_BPQ
mdefine_line|#define&t;ETH_P_BPQ&t;0x08FF&t;&t;/* G8BPQ AX.25 Ethernet Packet&t;[ NOT AN OFFICIALLY REGISTERED ID ] */
DECL|macro|ETH_P_DEC
mdefine_line|#define ETH_P_DEC       0x6000          /* DEC Assigned proto           */
DECL|macro|ETH_P_DNA_DL
mdefine_line|#define ETH_P_DNA_DL    0x6001          /* DEC DNA Dump/Load            */
DECL|macro|ETH_P_DNA_RC
mdefine_line|#define ETH_P_DNA_RC    0x6002          /* DEC DNA Remote Console       */
DECL|macro|ETH_P_DNA_RT
mdefine_line|#define ETH_P_DNA_RT    0x6003          /* DEC DNA Routing              */
DECL|macro|ETH_P_LAT
mdefine_line|#define ETH_P_LAT       0x6004          /* DEC LAT                      */
DECL|macro|ETH_P_DIAG
mdefine_line|#define ETH_P_DIAG      0x6005          /* DEC Diagnostics              */
DECL|macro|ETH_P_CUST
mdefine_line|#define ETH_P_CUST      0x6006          /* DEC Customer use             */
DECL|macro|ETH_P_SCA
mdefine_line|#define ETH_P_SCA       0x6007          /* DEC Systems Comms Arch       */
DECL|macro|ETH_P_RARP
mdefine_line|#define ETH_P_RARP      0x8035&t;&t;/* Reverse Addr Res packet&t;*/
DECL|macro|ETH_P_ATALK
mdefine_line|#define ETH_P_ATALK&t;0x809B&t;&t;/* Appletalk DDP&t;&t;*/
DECL|macro|ETH_P_AARP
mdefine_line|#define ETH_P_AARP&t;0x80F3&t;&t;/* Appletalk AARP&t;&t;*/
DECL|macro|ETH_P_IPX
mdefine_line|#define ETH_P_IPX&t;0x8137&t;&t;/* IPX over DIX&t;&t;&t;*/
DECL|macro|ETH_P_IPV6
mdefine_line|#define ETH_P_IPV6&t;0x86DD&t;&t;/* IPv6 over bluebook&t;&t;*/
multiline_comment|/*&n; *&t;Non DIX types. Won&squot;t clash for 1500 types.&n; */
DECL|macro|ETH_P_802_3
mdefine_line|#define ETH_P_802_3&t;0x0001&t;&t;/* Dummy type for 802.3 frames  */
DECL|macro|ETH_P_AX25
mdefine_line|#define ETH_P_AX25&t;0x0002&t;&t;/* Dummy protocol id for AX.25  */
DECL|macro|ETH_P_ALL
mdefine_line|#define ETH_P_ALL&t;0x0003&t;&t;/* Every packet (be careful!!!) */
DECL|macro|ETH_P_802_2
mdefine_line|#define ETH_P_802_2&t;0x0004&t;&t;/* 802.2 frames &t;&t;*/
DECL|macro|ETH_P_SNAP
mdefine_line|#define ETH_P_SNAP&t;0x0005&t;&t;/* Internal only&t;&t;*/
DECL|macro|ETH_P_DDCMP
mdefine_line|#define ETH_P_DDCMP     0x0006          /* DEC DDCMP: Internal only     */
DECL|macro|ETH_P_WAN_PPP
mdefine_line|#define ETH_P_WAN_PPP   0x0007          /* Dummy type for WAN PPP frames*/
DECL|macro|ETH_P_PPP_MP
mdefine_line|#define ETH_P_PPP_MP    0x0008          /* Dummy type for PPP MP frames */
DECL|macro|ETH_P_LOCALTALK
mdefine_line|#define ETH_P_LOCALTALK 0x0009&t;&t;/* Localtalk pseudeo type &t;*/
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
