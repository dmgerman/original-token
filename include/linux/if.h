multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the INET interface module.&n; *&n; * Version:&t;@(#)if.h&t;1.0.2&t;04/18/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1982-1988&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_H
DECL|macro|_LINUX_IF_H
mdefine_line|#define _LINUX_IF_H
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* for &quot;caddr_t&quot; et al&t;&t;*/
macro_line|#include &lt;linux/socket.h&gt;&t;&t;/* for &quot;struct sockaddr&quot; et al&t;*/
multiline_comment|/* Structure defining a queue for a network interface. */
DECL|struct|ifnet
r_struct
id|ifnet
(brace
DECL|member|if_name
r_char
op_star
id|if_name
suffix:semicolon
multiline_comment|/* name, e.g. ``en&squot;&squot; or ``lo&squot;&squot;&t;*/
DECL|member|if_unit
r_int
id|if_unit
suffix:semicolon
multiline_comment|/* sub-unit for device driver&t;*/
DECL|member|if_mtu
r_int
id|if_mtu
suffix:semicolon
multiline_comment|/* maximum transmission unit&t;*/
DECL|member|if_flags
r_int
id|if_flags
suffix:semicolon
multiline_comment|/* up/down, broadcast, etc.&t;*/
DECL|member|if_timer
r_int
id|if_timer
suffix:semicolon
multiline_comment|/* time &squot;til if_watchdog called&t;*/
DECL|member|if_metric
r_int
id|if_metric
suffix:semicolon
multiline_comment|/* routing metric (not used)&t;*/
DECL|member|if_addrlist
r_struct
id|ifaddr
op_star
id|if_addrlist
suffix:semicolon
multiline_comment|/* linked list of addrs per if&t;*/
DECL|struct|ifqueue
r_struct
id|ifqueue
(brace
macro_line|#ifdef not_yet_in_linux
DECL|member|ifq_head
r_struct
id|mbuf
op_star
id|ifq_head
suffix:semicolon
DECL|member|ifq_tail
r_struct
id|mbuf
op_star
id|ifq_tail
suffix:semicolon
DECL|member|ifq_len
r_int
id|ifq_len
suffix:semicolon
DECL|member|ifq_maxlen
r_int
id|ifq_maxlen
suffix:semicolon
DECL|member|ifq_drops
r_int
id|ifq_drops
suffix:semicolon
macro_line|#endif
DECL|member|if_snd
)brace
id|if_snd
suffix:semicolon
multiline_comment|/* output queue&t;&t;&t;*/
multiline_comment|/* Procedure handles. */
DECL|member|if_init
r_int
(paren
op_star
id|if_init
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* init routine&t;&t;&t;*/
DECL|member|if_output
r_int
(paren
op_star
id|if_output
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* output routine&t;&t;*/
DECL|member|if_ioctl
r_int
(paren
op_star
id|if_ioctl
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* ioctl routine&t;&t;*/
DECL|member|if_reset
r_int
(paren
op_star
id|if_reset
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* bus reset routine&t;&t;*/
DECL|member|if_watchdog
r_int
(paren
op_star
id|if_watchdog
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* timer routine&t;&t;*/
multiline_comment|/* Generic interface statistics. */
DECL|member|if_ipackets
r_int
id|if_ipackets
suffix:semicolon
multiline_comment|/* packets recv&squot;d on interface&t;*/
DECL|member|if_ierrors
r_int
id|if_ierrors
suffix:semicolon
multiline_comment|/* input errors on interface&t;*/
DECL|member|if_opackets
r_int
id|if_opackets
suffix:semicolon
multiline_comment|/* packets sent on interface&t;*/
DECL|member|if_oerrors
r_int
id|if_oerrors
suffix:semicolon
multiline_comment|/* output errors on interface&t;*/
DECL|member|if_collisions
r_int
id|if_collisions
suffix:semicolon
multiline_comment|/* collisions on CSMA i&squot;faces&t;*/
multiline_comment|/* Linked list: pointer to next interface. */
DECL|member|if_next
r_struct
id|ifnet
op_star
id|if_next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Standard interface flags. */
DECL|macro|IFF_UP
mdefine_line|#define&t;IFF_UP&t;&t;0x1&t;&t;/* interface is up&t;&t;*/
DECL|macro|IFF_BROADCAST
mdefine_line|#define&t;IFF_BROADCAST&t;0x2&t;&t;/* broadcast address valid&t;*/
DECL|macro|IFF_DEBUG
mdefine_line|#define&t;IFF_DEBUG&t;0x4&t;&t;/* turn on debugging&t;&t;*/
DECL|macro|IFF_LOOPBACK
mdefine_line|#define&t;IFF_LOOPBACK&t;0x8&t;&t;/* is a loopback net&t;&t;*/
DECL|macro|IFF_POINTOPOINT
mdefine_line|#define&t;IFF_POINTOPOINT&t;0x10&t;&t;/* interface is has p-p link&t;*/
DECL|macro|IFF_NOTRAILERS
mdefine_line|#define&t;IFF_NOTRAILERS&t;0x20&t;&t;/* avoid use of trailers&t;*/
DECL|macro|IFF_RUNNING
mdefine_line|#define&t;IFF_RUNNING&t;0x40&t;&t;/* resources allocated&t;&t;*/
DECL|macro|IFF_NOARP
mdefine_line|#define&t;IFF_NOARP&t;0x80&t;&t;/* no ARP protocol&t;&t;*/
multiline_comment|/* These are not yet used: */
DECL|macro|IFF_PROMISC
mdefine_line|#define&t;IFF_PROMISC&t;0x100&t;&t;/* recve all packets&t;&t;*/
DECL|macro|IFF_ALLMULTI
mdefine_line|#define&t;IFF_ALLMULTI&t;0x200&t;&t;/* recve all multicast packets&t;*/
multiline_comment|/*&n; * The ifaddr structure contains information about one address&n; * of an interface.  They are maintained by the different address&n; * families, are allocated and attached when an address is set,&n; * and are linked together so all addresses for an interface can&n; * be located.&n; */
DECL|struct|ifaddr
r_struct
id|ifaddr
(brace
DECL|member|ifa_addr
r_struct
id|sockaddr
id|ifa_addr
suffix:semicolon
multiline_comment|/* address of interface&t;&t;*/
r_union
(brace
DECL|member|ifu_broadaddr
r_struct
id|sockaddr
id|ifu_broadaddr
suffix:semicolon
DECL|member|ifu_dstaddr
r_struct
id|sockaddr
id|ifu_dstaddr
suffix:semicolon
DECL|member|ifa_ifu
)brace
id|ifa_ifu
suffix:semicolon
DECL|member|ifa_ifp
r_struct
id|iface
op_star
id|ifa_ifp
suffix:semicolon
multiline_comment|/* back-pointer to interface&t;*/
DECL|member|ifa_next
r_struct
id|ifaddr
op_star
id|ifa_next
suffix:semicolon
multiline_comment|/* next address for interface&t;*/
)brace
suffix:semicolon
DECL|macro|ifa_broadaddr
mdefine_line|#define&t;ifa_broadaddr&t;ifa_ifu.ifu_broadaddr&t;/* broadcast address&t;*/
DECL|macro|ifa_dstaddr
mdefine_line|#define&t;ifa_dstaddr&t;ifa_ifu.ifu_dstaddr&t;/* other end of link&t;*/
multiline_comment|/*&n; * Interface request structure used for socket&n; * ioctl&squot;s.  All interface ioctl&squot;s must have parameter&n; * definitions which begin with ifr_name.  The&n; * remainder may be interface specific.&n; */
DECL|struct|ifreq
r_struct
id|ifreq
(brace
DECL|macro|IFHWADDRLEN
mdefine_line|#define IFHWADDRLEN&t;6
DECL|macro|IFNAMSIZ
mdefine_line|#define&t;IFNAMSIZ&t;16
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;en0&quot; */
DECL|member|ifrn_hwaddr
r_char
id|ifrn_hwaddr
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
r_union
(brace
DECL|member|ifru_addr
r_struct
id|sockaddr
id|ifru_addr
suffix:semicolon
DECL|member|ifru_dstaddr
r_struct
id|sockaddr
id|ifru_dstaddr
suffix:semicolon
DECL|member|ifru_broadaddr
r_struct
id|sockaddr
id|ifru_broadaddr
suffix:semicolon
DECL|member|ifru_netmask
r_struct
id|sockaddr
id|ifru_netmask
suffix:semicolon
DECL|member|ifru_flags
r_int
id|ifru_flags
suffix:semicolon
DECL|member|ifru_metric
r_int
id|ifru_metric
suffix:semicolon
DECL|member|ifru_mtu
r_int
id|ifru_mtu
suffix:semicolon
DECL|member|ifru_data
id|caddr_t
id|ifru_data
suffix:semicolon
DECL|member|ifr_ifru
)brace
id|ifr_ifru
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifr_name
mdefine_line|#define ifr_name&t;ifr_ifrn.ifrn_name&t;/* interface name &t;*/
DECL|macro|ifr_hwaddr
mdefine_line|#define ifr_hwaddr&t;ifr_ifrn.ifrn_hwaddr&t;/* interface hardware   */
DECL|macro|ifr_addr
mdefine_line|#define&t;ifr_addr&t;ifr_ifru.ifru_addr&t;/* address&t;&t;*/
DECL|macro|ifr_dstaddr
mdefine_line|#define&t;ifr_dstaddr&t;ifr_ifru.ifru_dstaddr&t;/* other end of p-p lnk&t;*/
DECL|macro|ifr_broadaddr
mdefine_line|#define&t;ifr_broadaddr&t;ifr_ifru.ifru_broadaddr&t;/* broadcast address&t;*/
DECL|macro|ifr_netmask
mdefine_line|#define&t;ifr_netmask&t;ifr_ifru.ifru_netmask&t;/* interface net mask&t;*/
DECL|macro|ifr_flags
mdefine_line|#define&t;ifr_flags&t;ifr_ifru.ifru_flags&t;/* flags&t;&t;*/
DECL|macro|ifr_metric
mdefine_line|#define&t;ifr_metric&t;ifr_ifru.ifru_metric&t;/* metric&t;&t;*/
DECL|macro|ifr_mtu
mdefine_line|#define&t;ifr_mtu&t;&t;ifr_ifru.ifru_mtu&t;/* mtu&t;&t;&t;*/
DECL|macro|ifr_data
mdefine_line|#define&t;ifr_data&t;ifr_ifru.ifru_data&t;/* for use by interface&t;*/
multiline_comment|/*&n; * Structure used in SIOCGIFCONF request.&n; * Used to retrieve interface configuration&n; * for machine (useful for programs which&n; * must know all networks accessible).&n; */
DECL|struct|ifconf
r_struct
id|ifconf
(brace
DECL|member|ifc_len
r_int
id|ifc_len
suffix:semicolon
multiline_comment|/* size of buffer&t;*/
r_union
(brace
DECL|member|ifcu_buf
id|caddr_t
id|ifcu_buf
suffix:semicolon
DECL|member|ifcu_req
r_struct
id|ifreq
op_star
id|ifcu_req
suffix:semicolon
DECL|member|ifc_ifcu
)brace
id|ifc_ifcu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifc_buf
mdefine_line|#define&t;ifc_buf&t;ifc_ifcu.ifcu_buf&t;&t;/* buffer address&t;*/
DECL|macro|ifc_req
mdefine_line|#define&t;ifc_req&t;ifc_ifcu.ifcu_req&t;&t;/* array of structures&t;*/
multiline_comment|/* BSD UNIX expects to find these here, so here we go: */
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#endif /* _NET_IF_H */
eof
