multiline_comment|/* pack_type.c - implements raw packet sockets. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: pack_type.c,v 0.8.4.3 1992/12/12 19:25:04 bir7 Exp $ */
multiline_comment|/* $Log: pack_type.c,v $&n; * Revision 0.8.4.3  1992/12/12  19:25:04  bir7&n; * Cleaned up Log messages.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; *&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;eth.h&quot;
r_extern
r_int
id|arp_rcv
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
DECL|variable|arp_packet_type
r_static
r_struct
id|packet_type
id|arp_packet_type
op_assign
(brace
id|NET16
c_func
(paren
id|ETHERTYPE_ARP
)paren
comma
l_int|0
comma
multiline_comment|/* copy */
id|arp_rcv
comma
l_int|NULL
comma
l_int|NULL
multiline_comment|/* next */
)brace
suffix:semicolon
r_extern
r_int
id|ip_rcv
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
DECL|variable|ip_packet_type
r_static
r_struct
id|packet_type
id|ip_packet_type
op_assign
(brace
id|NET16
c_func
(paren
id|ETHERTYPE_IP
)paren
comma
l_int|0
comma
multiline_comment|/* copy */
id|ip_rcv
comma
l_int|NULL
comma
op_amp
id|arp_packet_type
)brace
suffix:semicolon
DECL|variable|ptype_base
r_struct
id|packet_type
op_star
id|ptype_base
op_assign
op_amp
id|ip_packet_type
suffix:semicolon
eof
