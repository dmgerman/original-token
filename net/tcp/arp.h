multiline_comment|/* arp.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: arp.h,v 0.8.4.3 1992/12/03 19:54:12 bir7 Exp $ */
multiline_comment|/* $Log: arp.h,v $&n; * Revision 0.8.4.3  1992/12/03  19:54:12  bir7&n; * Added paranoid queue checking.&n; *&n; * Revision 0.8.4.2  1992/11/15  14:55:30  bir7&n; * make arp_q global so sock.c can mess with it.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and $Log: arp.h,v $&n; * Revision 0.8.4.3  1992/12/03  19:54:12  bir7&n; * Added paranoid queue checking.&n; *&n; * Revision 0.8.4.2  1992/11/15  14:55:30  bir7&n; * make arp_q global so sock.c can mess with it.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *.&n; * */
macro_line|#ifndef _TCP_ARP_H
DECL|macro|_TCP_ARP_H
mdefine_line|#define _TCP_ARP_H
DECL|struct|arp
r_struct
id|arp
(brace
DECL|member|hrd
r_int
r_int
id|hrd
suffix:semicolon
DECL|member|pro
r_int
r_int
id|pro
suffix:semicolon
DECL|member|hlen
r_int
r_char
id|hlen
suffix:semicolon
DECL|member|plen
r_int
r_char
id|plen
suffix:semicolon
DECL|member|op
r_int
r_int
id|op
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arp_table
r_struct
id|arp_table
(brace
DECL|member|next
r_struct
id|arp_table
op_star
id|next
suffix:semicolon
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
DECL|member|hlen
r_int
r_char
id|hlen
suffix:semicolon
DECL|member|hard
r_int
r_char
id|hard
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|arp_q
r_struct
id|sk_buff
op_star
id|arp_q
suffix:semicolon
r_int
id|arp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
r_void
id|arp_snd
(paren
r_int
r_int
comma
r_struct
id|device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|arp_find
(paren
r_int
r_char
op_star
comma
r_int
r_int
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|arp_add_broad
(paren
r_int
r_int
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|arp_destroy
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|arp_add
(paren
r_int
r_int
id|addr
comma
r_int
r_char
op_star
id|haddr
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|arp_queue
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|macro|ARP_TABLE_SIZE
mdefine_line|#define ARP_TABLE_SIZE 16
DECL|macro|ARP_IP_PROT
mdefine_line|#define ARP_IP_PROT ETHERTYPE_IP
DECL|macro|ARP_REQUEST
mdefine_line|#define ARP_REQUEST 1
DECL|macro|ARP_REPLY
mdefine_line|#define ARP_REPLY 2
DECL|macro|ARP_TIMEOUT
mdefine_line|#define ARP_TIMEOUT 8640000 /* about 8 hours. */
DECL|macro|ARP_RES_TIME
mdefine_line|#define ARP_RES_TIME 250 /* 2.5 seconds. */
DECL|macro|ARP_QUEUE_MAGIC
mdefine_line|#define ARP_QUEUE_MAGIC 0x0432447A
macro_line|#endif
eof
