multiline_comment|/* ip.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: ip.h,v 0.8.4.1 1992/11/10 00:17:18 bir7 Exp $ */
multiline_comment|/* $Log: ip.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and $Log: ip.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *.&n; * */
macro_line|#ifndef _TCP_IP_H
DECL|macro|_TCP_IP_H
mdefine_line|#define _TCP_IP_H
macro_line|#include &quot;dev.h&quot;
macro_line|#include &lt;linux/sock_ioctl.h&gt;
multiline_comment|/* #include &lt;netinet/protocols.h&gt;*/
macro_line|#include &lt;netinet/in.h&gt;
DECL|struct|rtable
r_struct
id|rtable
(brace
DECL|member|net
r_int
r_int
id|net
suffix:semicolon
DECL|member|router
r_int
r_int
id|router
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|next
r_struct
id|rtable
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|route
r_struct
id|route
(brace
DECL|member|route_size
r_char
id|route_size
suffix:semicolon
DECL|member|pointer
r_char
id|pointer
suffix:semicolon
DECL|member|route
r_int
r_int
id|route
(braket
id|MAX_ROUTE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|timestamp
r_struct
id|timestamp
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|ptr
r_int
r_char
id|ptr
suffix:semicolon
r_union
(brace
r_int
r_char
id|flags
suffix:colon
l_int|4
comma
id|overflow
suffix:colon
l_int|4
suffix:semicolon
DECL|member|full_char
r_int
r_char
id|full_char
suffix:semicolon
DECL|member|x
)brace
id|x
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
(braket
l_int|9
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|options
r_struct
id|options
(brace
DECL|member|record_route
r_struct
id|route
id|record_route
suffix:semicolon
DECL|member|loose_route
r_struct
id|route
id|loose_route
suffix:semicolon
DECL|member|strict_route
r_struct
id|route
id|strict_route
suffix:semicolon
DECL|member|tstamp
r_struct
id|timestamp
id|tstamp
suffix:semicolon
DECL|member|security
r_int
r_int
id|security
suffix:semicolon
DECL|member|compartment
r_int
r_int
id|compartment
suffix:semicolon
DECL|member|handling
r_int
r_int
id|handling
suffix:semicolon
DECL|member|stream
r_int
r_int
id|stream
suffix:semicolon
DECL|member|tcc
r_int
id|tcc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_header
r_struct
id|ip_header
(brace
DECL|member|ihl
DECL|member|version
r_int
r_char
id|ihl
suffix:colon
l_int|4
comma
id|version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|tos
r_int
r_char
id|tos
suffix:semicolon
DECL|member|tot_len
r_int
r_int
id|tot_len
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|frag_off
r_int
r_int
id|frag_off
suffix:semicolon
DECL|member|ttl
r_int
r_char
id|ttl
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|check
r_int
r_int
id|check
suffix:semicolon
DECL|member|saddr
r_int
r_int
id|saddr
suffix:semicolon
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/*The options start here. */
)brace
suffix:semicolon
DECL|macro|IPOPT_END
mdefine_line|#define IPOPT_END 0
DECL|macro|IPOPT_NOOP
mdefine_line|#define IPOPT_NOOP 1
DECL|macro|IPOPT_SEC
mdefine_line|#define IPOPT_SEC 130
DECL|macro|IPOPT_LSRR
mdefine_line|#define IPOPT_LSRR 131
DECL|macro|IPOPT_SSRR
mdefine_line|#define IPOPT_SSRR 137
DECL|macro|IPOPT_RR
mdefine_line|#define IPOPT_RR 7
DECL|macro|IPOPT_SID
mdefine_line|#define IPOPT_SID 136
DECL|macro|IPOPT_TIMESTAMP
mdefine_line|#define IPOPT_TIMESTAMP 68
DECL|macro|IP_LOOPBACK_ADDR
mdefine_line|#define IP_LOOPBACK_ADDR 0x0100007f
r_static
r_inline
r_int
r_int
DECL|function|net16
id|net16
c_func
(paren
r_int
r_int
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;xchgb %%cl,%%ch&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
(paren
id|x
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|net32
id|net32
c_func
(paren
r_int
r_int
id|x
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;xchgb %%cl,%%ch&bslash;n&quot;
l_string|&quot;&bslash;t roll $16,%%ecx&bslash;n&quot;
l_string|&quot;&bslash;t xchgb %%cl,%%ch&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
(paren
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/* change the name of this. */
DECL|macro|MAX_IP_PROTOS
mdefine_line|#define MAX_IP_PROTOS 32 /* Must be a power of 2 */
multiline_comment|/* This is used to register protocols. */
DECL|struct|ip_protocol
r_struct
id|ip_protocol
(brace
DECL|member|handler
r_int
(paren
op_star
id|handler
)paren
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
id|options
op_star
id|opt
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
id|redo
comma
r_struct
id|ip_protocol
op_star
id|protocol
)paren
suffix:semicolon
DECL|member|err_handler
r_void
(paren
op_star
id|err_handler
)paren
(paren
r_int
id|err
comma
r_int
r_char
op_star
id|buff
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|saddr
comma
r_struct
id|ip_protocol
op_star
id|ipprot
)paren
suffix:semicolon
DECL|member|next
r_struct
id|ip_protocol
op_star
id|next
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|copy
r_int
r_char
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ip_protocol
op_star
id|ip_protocol_base
suffix:semicolon
r_extern
r_struct
id|ip_protocol
op_star
id|ip_protos
(braket
id|MAX_IP_PROTOS
)braket
suffix:semicolon
DECL|macro|MAX_IP_ADDRES
mdefine_line|#define MAX_IP_ADDRES 5
r_extern
r_int
r_int
id|ip_addr
(braket
id|MAX_IP_ADDRES
)braket
suffix:semicolon
DECL|macro|MY_IP_ADDR
mdefine_line|#define MY_IP_ADDR ip_addr[0];
r_int
id|my_ip_addr
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#include &quot;eth.h&quot;
r_void
id|print_iph
(paren
r_struct
id|ip_header
op_star
)paren
suffix:semicolon
r_void
id|print_eth
(paren
r_struct
id|enet_header
op_star
)paren
suffix:semicolon
r_int
id|ip_set_dev
(paren
r_struct
id|ip_config
op_star
)paren
suffix:semicolon
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
)paren
suffix:semicolon
r_void
id|ip_queue_xmit
(paren
r_volatile
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
r_void
id|ip_retransmit
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|all
)paren
suffix:semicolon
r_int
id|ip_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|buff
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
r_void
id|add_ip_protocol
(paren
r_struct
id|ip_protocol
op_star
)paren
suffix:semicolon
r_int
id|delete_ip_protocol
(paren
r_struct
id|ip_protocol
op_star
)paren
suffix:semicolon
r_int
id|ip_handoff
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_int
r_int
id|ip_compute_csum
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
r_int
id|ip_addr_match
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|add_route
(paren
r_struct
id|rtable
op_star
id|rt
)paren
suffix:semicolon
r_void
id|ip_route_check
(paren
r_int
r_int
id|daddr
)paren
suffix:semicolon
macro_line|#endif
eof