multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the IP module.&n; *&n; * Version:&t;@(#)ip.h&t;1.0.2&t;05/07/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _IP_H
DECL|macro|_IP_H
mdefine_line|#define _IP_H
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _SNMP_H
macro_line|#include &quot;snmp.h&quot;
macro_line|#endif
macro_line|#include &quot;sock.h&quot;&t;/* struct sock */
multiline_comment|/* IP flags. */
DECL|macro|IP_CE
mdefine_line|#define IP_CE&t;&t;0x8000&t;&t;/* Flag: &quot;Congestion&quot;&t;&t;*/
DECL|macro|IP_DF
mdefine_line|#define IP_DF&t;&t;0x4000&t;&t;/* Flag: &quot;Don&squot;t Fragment&quot;&t;*/
DECL|macro|IP_MF
mdefine_line|#define IP_MF&t;&t;0x2000&t;&t;/* Flag: &quot;More Fragments&quot;&t;*/
DECL|macro|IP_OFFSET
mdefine_line|#define IP_OFFSET&t;0x1FFF&t;&t;/* &quot;Fragment Offset&quot; part&t;*/
DECL|macro|IP_FRAG_TIME
mdefine_line|#define IP_FRAG_TIME&t;(30 * HZ)&t;&t;/* fragment lifetime&t;*/
macro_line|#ifdef CONFIG_IP_MULTICAST
r_extern
r_void
id|ip_mc_dropsocket
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_dropdevice
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_procinfo
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|macro|MULTICAST
mdefine_line|#define MULTICAST(x)&t;(IN_MULTICAST(htonl(x)))
macro_line|#endif
multiline_comment|/* Describe an IP fragment. */
DECL|struct|ipfrag
r_struct
id|ipfrag
(brace
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* offset of fragment in IP datagram&t;*/
DECL|member|end
r_int
id|end
suffix:semicolon
multiline_comment|/* last byte of data in datagram&t;*/
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* length of this fragment&t;&t;*/
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* complete received fragment&t;&t;*/
DECL|member|ptr
r_int
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* pointer into real fragment data&t;*/
DECL|member|next
r_struct
id|ipfrag
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list pointers&t;&t;&t;*/
DECL|member|prev
r_struct
id|ipfrag
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Describe an entry in the &quot;incomplete datagrams&quot; queue. */
DECL|struct|ipq
r_struct
id|ipq
(brace
DECL|member|mac
r_int
r_char
op_star
id|mac
suffix:semicolon
multiline_comment|/* pointer to MAC header&t;&t;*/
DECL|member|iph
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
multiline_comment|/* pointer to IP header&t;&t;&t;*/
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* total length of original datagram&t;*/
DECL|member|ihlen
r_int
id|ihlen
suffix:semicolon
multiline_comment|/* length of the IP header&t;&t;*/
DECL|member|maclen
r_int
id|maclen
suffix:semicolon
multiline_comment|/* length of the MAC header&t;&t;*/
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* when will this queue expire?&t;&t;*/
DECL|member|fragments
r_struct
id|ipfrag
op_star
id|fragments
suffix:semicolon
multiline_comment|/* linked list of received fragments&t;*/
DECL|member|next
r_struct
id|ipq
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list pointers&t;&t;&t;*/
DECL|member|prev
r_struct
id|ipq
op_star
id|prev
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device - for icmp replies */
)brace
suffix:semicolon
r_extern
r_int
id|backoff
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|ip_print
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|ip_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|ip_route_check
c_func
(paren
r_int
r_int
id|daddr
)paren
suffix:semicolon
r_extern
r_int
id|ip_build_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_struct
id|device
op_star
op_star
id|dev
comma
r_int
id|type
comma
r_struct
id|options
op_star
id|opt
comma
r_int
id|len
comma
r_int
id|tos
comma
r_int
id|ttl
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip_compute_csum
c_func
(paren
r_int
r_char
op_star
id|buff
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ip_rcv
c_func
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
comma
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_extern
r_void
id|ip_send_check
c_func
(paren
r_struct
id|iphdr
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|ip_id_count
suffix:semicolon
r_extern
r_void
id|ip_queue_xmit
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|free
)paren
suffix:semicolon
r_extern
r_int
id|ip_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|ip_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_void
id|ip_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|ip_mib
id|ip_statistics
suffix:semicolon
macro_line|#endif&t;/* _IP_H */
eof
