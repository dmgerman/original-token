multiline_comment|/* Internet Control Message Protocol (ICMP) icmp.c */
multiline_comment|/*&n;    Copyright (C) 1992  Bob Harris&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author of tcpip package may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;&n;    The author of this file may be reached at rth@sparta.com or Sparta, Inc.&n;    7926 Jones Branch Dr. Suite 900, McLean Va 22102.&n;*/
multiline_comment|/* $Id: icmp.c,v 0.8.4.2 1992/11/10 10:38:48 bir7 Exp $ */
multiline_comment|/* $Log: icmp.c,v $&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.3  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and &n; *&n; */
multiline_comment|/* modified by Ross Biro bir7@leland.stanford.edu to do more than just&n;   echo responses. */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;&t;/* kfree_s */
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;../kern_sock.h&quot; /* for PRINTK */
macro_line|#include &quot;icmp.h&quot;
DECL|macro|min
mdefine_line|#define min(a,b) ((a)&lt;(b)?(a):(b))
multiline_comment|/* an array of errno for error messages from dest unreach. */
DECL|variable|icmp_err_convert
r_struct
id|icmp_err
id|icmp_err_convert
(braket
)braket
op_assign
(brace
(brace
id|ENETUNREACH
comma
l_int|1
)brace
comma
(brace
id|EHOSTUNREACH
comma
l_int|1
)brace
comma
(brace
id|ENOPROTOOPT
comma
l_int|1
)brace
comma
(brace
id|ECONNREFUSED
comma
l_int|1
)brace
comma
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
(brace
id|ENETUNREACH
comma
l_int|1
)brace
comma
(brace
id|EHOSTDOWN
comma
l_int|1
)brace
comma
(brace
id|ENONET
comma
l_int|1
)brace
comma
(brace
id|ENETUNREACH
comma
l_int|1
)brace
comma
(brace
id|EHOSTUNREACH
comma
l_int|1
)brace
comma
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
)brace
suffix:semicolon
r_void
DECL|function|print_icmph
id|print_icmph
(paren
r_struct
id|icmp_header
op_star
id|icmph
)paren
(brace
id|PRINTK
(paren
l_string|&quot;  type = %d, code = %d, checksum = %X&bslash;n&quot;
comma
id|icmph-&gt;type
comma
id|icmph-&gt;code
comma
id|icmph-&gt;checksum
)paren
suffix:semicolon
id|PRINTK
(paren
l_string|&quot; gateway = %X&bslash;n&quot;
comma
id|icmph-&gt;un.gateway
)paren
suffix:semicolon
)brace
multiline_comment|/* sends an icmp message in response to a packet. */
r_void
DECL|function|icmp_reply
id|icmp_reply
(paren
r_struct
id|sk_buff
op_star
id|skb_in
comma
r_int
id|type
comma
r_int
id|code
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|ip_header
op_star
id|iph
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_struct
id|icmp_header
op_star
id|icmph
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* get some memory for the replay. */
id|len
op_assign
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
l_int|8
multiline_comment|/* amount of header to return. */
op_plus
r_sizeof
(paren
r_struct
id|icmp_header
)paren
op_plus
l_int|64
multiline_comment|/* enough for an ip header. */
op_plus
id|dev-&gt;hard_header_len
suffix:semicolon
id|skb
op_assign
id|kmalloc
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
id|len
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* find the ip header. */
id|iph
op_assign
(paren
r_struct
id|ip_header
op_star
)paren
(paren
id|skb_in
op_plus
l_int|1
)paren
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|ip_header
op_star
)paren
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
op_plus
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
multiline_comment|/* Build Layer 2-3 headers for message back to source */
id|offset
op_assign
id|ip_build_header
c_func
(paren
id|skb
comma
id|iph-&gt;daddr
comma
id|iph-&gt;saddr
comma
op_amp
id|dev
comma
id|IPPROTO_ICMP
comma
l_int|NULL
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Readjust length according to actual IP header size */
id|skb-&gt;len
op_assign
id|offset
op_plus
r_sizeof
(paren
r_struct
id|icmp_header
)paren
op_plus
l_int|8
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmp_header
op_star
)paren
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|skb
op_plus
l_int|1
)paren
op_plus
id|offset
)paren
suffix:semicolon
id|icmph-&gt;type
op_assign
id|type
suffix:semicolon
id|icmph-&gt;code
op_assign
id|code
suffix:semicolon
id|icmph-&gt;checksum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we don&squot;t need to compute this. */
id|icmph-&gt;un.gateway
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* might as well 0 it. */
id|memcpy
(paren
id|icmph
op_plus
l_int|1
comma
id|iph
op_plus
l_int|1
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* send it and free it. */
id|ip_queue_xmit
(paren
l_int|NULL
comma
id|dev
comma
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* deals with incoming icmp packets. */
r_int
DECL|function|icmp_rcv
id|icmp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb1
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
(brace
r_int
id|size
comma
id|offset
suffix:semicolon
r_struct
id|icmp_header
op_star
id|icmph
comma
op_star
id|icmphr
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|buff
suffix:semicolon
multiline_comment|/* drop broadcast packets.  */
r_if
c_cond
(paren
(paren
id|daddr
op_amp
l_int|0xff000000
)paren
op_eq
l_int|0
op_logical_or
(paren
id|daddr
op_amp
l_int|0xff000000
)paren
op_eq
l_int|0xff000000
)paren
(brace
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|buff
op_assign
id|skb1-&gt;h.raw
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmp_header
op_star
)paren
id|buff
suffix:semicolon
multiline_comment|/* Validate the packet first */
r_if
c_cond
(paren
id|icmph-&gt;checksum
)paren
(brace
multiline_comment|/* Checksums Enabled? */
r_if
c_cond
(paren
id|ip_compute_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|icmph
comma
id|len
)paren
)paren
(brace
multiline_comment|/* Failed checksum! */
id|PRINTK
c_func
(paren
l_string|&quot;&bslash;nICMP ECHO failed checksum!&quot;
)paren
suffix:semicolon
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|print_icmph
c_func
(paren
id|icmph
)paren
suffix:semicolon
multiline_comment|/* Parse the ICMP message */
r_switch
c_cond
(paren
id|icmph-&gt;type
)paren
(brace
r_case
id|ICMP_DEST_UNREACH
suffix:colon
r_case
id|ICMP_SOURCE_QUENCH
suffix:colon
(brace
r_struct
id|ip_header
op_star
id|iph
suffix:semicolon
r_struct
id|ip_protocol
op_star
id|ipprot
suffix:semicolon
r_int
r_char
id|hash
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|icmph-&gt;type
op_lshift
l_int|8
op_or
id|icmph-&gt;code
suffix:semicolon
multiline_comment|/* we need to cause the socket to be closed and the error message&n;&t;      to be set appropriately. */
id|iph
op_assign
(paren
r_struct
id|ip_header
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* get the protocol(s) */
id|hash
op_assign
id|iph-&gt;protocol
op_amp
(paren
id|MAX_IP_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ipprot
op_assign
id|ip_protos
(braket
id|hash
)braket
suffix:semicolon
id|ipprot
op_ne
l_int|NULL
suffix:semicolon
id|ipprot
op_assign
id|ipprot-&gt;next
)paren
(brace
multiline_comment|/* pass it off to everyone who wants it. */
id|ipprot-&gt;err_handler
(paren
id|err
comma
(paren
r_int
r_char
op_star
)paren
id|iph
op_plus
l_int|4
op_star
id|iph-&gt;ihl
comma
id|iph-&gt;daddr
comma
id|iph-&gt;saddr
comma
id|ipprot
)paren
suffix:semicolon
)brace
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_case
id|ICMP_REDIRECT
suffix:colon
(brace
multiline_comment|/* we need to put a new route in the routing table. */
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* we will add a new route. */
r_struct
id|ip_header
op_star
id|iph
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|ip_header
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
id|rt
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|rt
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt
op_ne
l_int|NULL
)paren
(brace
id|rt-&gt;net
op_assign
id|iph-&gt;daddr
suffix:semicolon
multiline_comment|/* assume class C network.  Technically this is incorrect,&n;&t;&t;   but will give it a try. */
r_if
c_cond
(paren
(paren
id|icmph-&gt;code
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
id|rt-&gt;net
op_and_assign
l_int|0x00ffffff
suffix:semicolon
id|rt-&gt;dev
op_assign
id|dev
suffix:semicolon
id|rt-&gt;router
op_assign
id|icmph-&gt;un.gateway
suffix:semicolon
id|add_route
(paren
id|rt
)paren
suffix:semicolon
)brace
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_case
id|ICMP_ECHO
suffix:colon
multiline_comment|/* Allocate an sk_buff response buffer (assume 64 byte IP header) */
id|size
op_assign
r_sizeof
(paren
r_struct
id|sk_buff
)paren
op_plus
id|dev-&gt;hard_header_len
op_plus
l_int|64
op_plus
id|len
suffix:semicolon
id|skb
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
id|size
suffix:semicolon
multiline_comment|/* Build Layer 2-3 headers for message back to source */
id|offset
op_assign
id|ip_build_header
c_func
(paren
id|skb
comma
id|daddr
comma
id|saddr
comma
op_amp
id|dev
comma
id|IPPROTO_ICMP
comma
id|opt
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
(brace
multiline_comment|/* Problems building header */
id|PRINTK
c_func
(paren
l_string|&quot;&bslash;nCould not build IP Header for ICMP ECHO Response&quot;
)paren
suffix:semicolon
id|kfree_s
(paren
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* just toss the received packet */
)brace
multiline_comment|/* Readjust length according to actual IP header size */
id|skb-&gt;len
op_assign
id|offset
op_plus
id|len
suffix:semicolon
multiline_comment|/* Build ICMP_ECHO Response message */
id|icmphr
op_assign
(paren
r_struct
id|icmp_header
op_star
)paren
(paren
(paren
r_char
op_star
)paren
(paren
id|skb
op_plus
l_int|1
)paren
op_plus
id|offset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|icmphr
comma
(paren
r_char
op_star
)paren
id|icmph
comma
id|len
)paren
suffix:semicolon
id|icmphr-&gt;type
op_assign
id|ICMP_ECHOREPLY
suffix:semicolon
id|icmphr-&gt;code
op_assign
l_int|0
suffix:semicolon
id|icmphr-&gt;checksum
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|icmph-&gt;checksum
)paren
(brace
multiline_comment|/* Calculate Checksum */
id|icmphr-&gt;checksum
op_assign
id|ip_compute_csum
c_func
(paren
(paren
r_void
op_star
)paren
id|icmphr
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* Ship it out - free it when done */
id|ip_queue_xmit
c_func
(paren
(paren
r_volatile
r_struct
id|sock
op_star
)paren
l_int|NULL
comma
id|dev
comma
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|PRINTK
c_func
(paren
l_string|&quot;&bslash;nUnsupported ICMP type = x%x&quot;
comma
id|icmph-&gt;type
)paren
suffix:semicolon
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* just toss the packet */
)brace
multiline_comment|/* should be unecessary, but just in case. */
id|skb1-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
(paren
id|skb1
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* just toss the packet */
)brace
eof
