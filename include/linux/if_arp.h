multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the ARP (RFC 826) protocol.&n; *&n; * Version:&t;@(#)if_arp.h&t;1.0.1&t;04/16/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988&n; *&t;&t;Portions taken from the KA9Q/NOS (v2.00m PA0GRI) source.&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Florian La Roche,&n; *&t;&t;Jonathan Layes &lt;layes@loran.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ARP_H
DECL|macro|_LINUX_IF_ARP_H
mdefine_line|#define _LINUX_IF_ARP_H
macro_line|#include &lt;linux/netdevice.h&gt;
multiline_comment|/* ARP protocol HARDWARE identifiers. */
DECL|macro|ARPHRD_NETROM
mdefine_line|#define ARPHRD_NETROM&t;0&t;&t;/* from KA9Q: NET/ROM pseudo&t;*/
DECL|macro|ARPHRD_ETHER
mdefine_line|#define ARPHRD_ETHER &t;1&t;&t;/* Ethernet 10Mbps&t;&t;*/
DECL|macro|ARPHRD_EETHER
mdefine_line|#define&t;ARPHRD_EETHER&t;2&t;&t;/* Experimental Ethernet&t;*/
DECL|macro|ARPHRD_AX25
mdefine_line|#define&t;ARPHRD_AX25&t;3&t;&t;/* AX.25 Level 2&t;&t;*/
DECL|macro|ARPHRD_PRONET
mdefine_line|#define&t;ARPHRD_PRONET&t;4&t;&t;/* PROnet token ring&t;&t;*/
DECL|macro|ARPHRD_CHAOS
mdefine_line|#define&t;ARPHRD_CHAOS&t;5&t;&t;/* Chaosnet&t;&t;&t;*/
DECL|macro|ARPHRD_IEEE802
mdefine_line|#define&t;ARPHRD_IEEE802&t;6&t;&t;/* IEEE 802.2 Ethernet/TR/TB&t;*/
DECL|macro|ARPHRD_ARCNET
mdefine_line|#define&t;ARPHRD_ARCNET&t;7&t;&t;/* ARCnet&t;&t;&t;*/
DECL|macro|ARPHRD_APPLETLK
mdefine_line|#define&t;ARPHRD_APPLETLK&t;8&t;&t;/* APPLEtalk&t;&t;&t;*/
DECL|macro|ARPHRD_DLCI
mdefine_line|#define ARPHRD_DLCI&t;15&t;&t;/* Frame Relay DLCI&t;&t;*/
DECL|macro|ARPHRD_METRICOM
mdefine_line|#define ARPHRD_METRICOM&t;23&t;&t;/* Metricom STRIP (new IANA id)&t;*/
multiline_comment|/* Dummy types for non ARP hardware */
DECL|macro|ARPHRD_SLIP
mdefine_line|#define ARPHRD_SLIP&t;256
DECL|macro|ARPHRD_CSLIP
mdefine_line|#define ARPHRD_CSLIP&t;257
DECL|macro|ARPHRD_SLIP6
mdefine_line|#define ARPHRD_SLIP6&t;258
DECL|macro|ARPHRD_CSLIP6
mdefine_line|#define ARPHRD_CSLIP6&t;259
DECL|macro|ARPHRD_RSRVD
mdefine_line|#define ARPHRD_RSRVD&t;260&t;&t;/* Notional KISS type &t;&t;*/
DECL|macro|ARPHRD_ADAPT
mdefine_line|#define ARPHRD_ADAPT&t;264
DECL|macro|ARPHRD_ROSE
mdefine_line|#define ARPHRD_ROSE&t;270
DECL|macro|ARPHRD_X25
mdefine_line|#define ARPHRD_X25&t;271&t;&t;/* CCITT X.25&t;&t;&t;*/
DECL|macro|ARPHRD_PPP
mdefine_line|#define ARPHRD_PPP&t;512
DECL|macro|ARPHRD_TUNNEL
mdefine_line|#define ARPHRD_TUNNEL&t;768&t;&t;/* IPIP tunnel&t;&t;&t;*/
DECL|macro|ARPHRD_TUNNEL6
mdefine_line|#define ARPHRD_TUNNEL6&t;769&t;&t;/* IPIP6 tunnel&t;&t;&t;*/
DECL|macro|ARPHRD_FRAD
mdefine_line|#define ARPHRD_FRAD&t;770&t;&t;/* Frame Relay Access Device&t;*/
DECL|macro|ARPHRD_SKIP
mdefine_line|#define ARPHRD_SKIP&t;771&t;&t;/* SKIP vif&t;&t;&t;*/
DECL|macro|ARPHRD_LOOPBACK
mdefine_line|#define ARPHRD_LOOPBACK&t;772&t;&t;/* Loopback device&t;&t;*/
DECL|macro|ARPHRD_LOCALTLK
mdefine_line|#define ARPHRD_LOCALTLK 773&t;&t;/* Localtalk device&t;&t;*/
DECL|macro|ARPHRD_SIT
mdefine_line|#define ARPHRD_SIT&t;776&t;&t;/* sit0 device - IPv6-in-IPv4&t;*/
multiline_comment|/* ARP protocol opcodes. */
DECL|macro|ARPOP_REQUEST
mdefine_line|#define&t;ARPOP_REQUEST&t;1&t;&t;/* ARP request&t;&t;&t;*/
DECL|macro|ARPOP_REPLY
mdefine_line|#define&t;ARPOP_REPLY&t;2&t;&t;/* ARP reply&t;&t;&t;*/
DECL|macro|ARPOP_RREQUEST
mdefine_line|#define&t;ARPOP_RREQUEST&t;3&t;&t;/* RARP request&t;&t;&t;*/
DECL|macro|ARPOP_RREPLY
mdefine_line|#define&t;ARPOP_RREPLY&t;4&t;&t;/* RARP reply&t;&t;&t;*/
multiline_comment|/* ARP ioctl request. */
DECL|struct|arpreq
r_struct
id|arpreq
(brace
DECL|member|arp_pa
r_struct
id|sockaddr
id|arp_pa
suffix:semicolon
multiline_comment|/* protocol address&t;&t;*/
DECL|member|arp_ha
r_struct
id|sockaddr
id|arp_ha
suffix:semicolon
multiline_comment|/* hardware address&t;&t;*/
DECL|member|arp_flags
r_int
id|arp_flags
suffix:semicolon
multiline_comment|/* flags&t;&t;&t;*/
DECL|member|arp_netmask
r_struct
id|sockaddr
id|arp_netmask
suffix:semicolon
multiline_comment|/* netmask (only for proxy arps) */
DECL|member|arp_dev
r_char
id|arp_dev
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpreq_old
r_struct
id|arpreq_old
(brace
DECL|member|arp_pa
r_struct
id|sockaddr
id|arp_pa
suffix:semicolon
multiline_comment|/* protocol address&t;&t;*/
DECL|member|arp_ha
r_struct
id|sockaddr
id|arp_ha
suffix:semicolon
multiline_comment|/* hardware address&t;&t;*/
DECL|member|arp_flags
r_int
id|arp_flags
suffix:semicolon
multiline_comment|/* flags&t;&t;&t;*/
DECL|member|arp_netmask
r_struct
id|sockaddr
id|arp_netmask
suffix:semicolon
multiline_comment|/* netmask (only for proxy arps) */
)brace
suffix:semicolon
multiline_comment|/* ARP Flag values. */
DECL|macro|ATF_COM
mdefine_line|#define ATF_COM&t;&t;0x02&t;&t;/* completed entry (ha valid)&t;*/
DECL|macro|ATF_PERM
mdefine_line|#define&t;ATF_PERM&t;0x04&t;&t;/* permanent entry&t;&t;*/
DECL|macro|ATF_PUBL
mdefine_line|#define&t;ATF_PUBL&t;0x08&t;&t;/* publish entry&t;&t;*/
DECL|macro|ATF_USETRAILERS
mdefine_line|#define&t;ATF_USETRAILERS&t;0x10&t;&t;/* has requested trailers&t;*/
DECL|macro|ATF_NETMASK
mdefine_line|#define ATF_NETMASK     0x20            /* want to use a netmask (only&n;&t;&t;&t;&t;&t;   for proxy entries) */
multiline_comment|/*&n; *&t;This structure defines an ethernet arp header.&n; */
DECL|struct|arphdr
r_struct
id|arphdr
(brace
DECL|member|ar_hrd
r_int
r_int
id|ar_hrd
suffix:semicolon
multiline_comment|/* format of hardware address&t;*/
DECL|member|ar_pro
r_int
r_int
id|ar_pro
suffix:semicolon
multiline_comment|/* format of protocol address&t;*/
DECL|member|ar_hln
r_int
r_char
id|ar_hln
suffix:semicolon
multiline_comment|/* length of hardware address&t;*/
DECL|member|ar_pln
r_int
r_char
id|ar_pln
suffix:semicolon
multiline_comment|/* length of protocol address&t;*/
DECL|member|ar_op
r_int
r_int
id|ar_op
suffix:semicolon
multiline_comment|/* ARP opcode (command)&t;&t;*/
macro_line|#if 0
multiline_comment|/*&n;&t;  *&t; Ethernet looks like this : This bit is variable sized however...&n;&t;  */
r_int
r_char
id|ar_sha
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* sender hardware address&t;*/
r_int
r_char
id|ar_sip
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* sender IP address&t;&t;*/
r_int
r_char
id|ar_tha
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* target hardware address&t;*/
r_int
r_char
id|ar_tip
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* target IP address&t;&t;*/
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Support for the user space arp daemon, arpd */
DECL|macro|ARPD_UPDATE
mdefine_line|#define ARPD_UPDATE&t;0x01
DECL|macro|ARPD_LOOKUP
mdefine_line|#define ARPD_LOOKUP&t;0x02
DECL|macro|ARPD_FLUSH
mdefine_line|#define ARPD_FLUSH&t;0x03
DECL|struct|arpd_request
r_struct
id|arpd_request
(brace
DECL|member|req
r_int
r_int
id|req
suffix:semicolon
multiline_comment|/* request type */
DECL|member|ip
id|__u32
id|ip
suffix:semicolon
multiline_comment|/* ip address of entry */
DECL|member|dev
r_int
r_int
id|dev
suffix:semicolon
multiline_comment|/* Device entry is tied to */
DECL|member|stamp
r_int
r_int
id|stamp
suffix:semicolon
DECL|member|updated
r_int
r_int
id|updated
suffix:semicolon
DECL|member|ha
r_int
r_char
id|ha
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* Hardware address */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IF_ARP_H */
eof
