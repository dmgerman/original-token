multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the ARP (RFC 826) protocol.&n; *&n; * Version:&t;@(#)if_arp.h&t;1.0.1&t;04/16/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988&n; *&t;&t;Portions taken from the KA9Q/NOS (v2.00m PA0GRI) source.&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ARP_H
DECL|macro|_LINUX_IF_ARP_H
mdefine_line|#define _LINUX_IF_ARP_H
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
mdefine_line|#define&t;ARPHRD_IEEE802&t;6&t;&t;/* IEEE 802.2 Ethernet- huh?&t;*/
DECL|macro|ARPHRD_ARCNET
mdefine_line|#define&t;ARPHRD_ARCNET&t;7&t;&t;/* ARCnet&t;&t;&t;*/
DECL|macro|ARPHRD_APPLETLK
mdefine_line|#define&t;ARPHRD_APPLETLK&t;8&t;&t;/* APPLEtalk&t;&t;&t;*/
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
macro_line|#endif&t;/* _LINUX_IF_ARP_H */
eof
