multiline_comment|/* dev.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: dev.h,v 0.8.4.1 1992/11/10 00:17:18 bir7 Exp $ */
multiline_comment|/* $Log: dev.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and $Log: dev.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *.&n; * */
macro_line|#ifndef _TCP_DEV_H
DECL|macro|_TCP_DEV_H
mdefine_line|#define _TCP_DEV_H
multiline_comment|/* for future expansion when we will have different priorities. */
DECL|macro|DEV_NUMBUFFS
mdefine_line|#define DEV_NUMBUFFS 3
DECL|macro|MAX_ADDR_LEN
mdefine_line|#define MAX_ADDR_LEN 6
DECL|macro|MAX_HEADER
mdefine_line|#define MAX_HEADER 14
DECL|macro|MAX_ROUTE
mdefine_line|#define MAX_ROUTE 16
DECL|struct|device
r_struct
id|device
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|rmem_end
r_int
r_int
id|rmem_end
suffix:semicolon
DECL|member|rmem_start
r_int
r_int
id|rmem_start
suffix:semicolon
DECL|member|mem_end
r_int
r_int
id|mem_end
suffix:semicolon
DECL|member|mem_start
r_int
r_int
id|mem_start
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|start
r_int
r_char
id|start
suffix:colon
l_int|1
comma
DECL|member|tbusy
id|tbusy
suffix:colon
l_int|1
comma
DECL|member|loopback
id|loopback
suffix:colon
l_int|1
comma
DECL|member|interrupt
id|interrupt
suffix:colon
l_int|1
comma
DECL|member|up
id|up
suffix:colon
l_int|1
suffix:semicolon
DECL|member|next
r_struct
id|device
op_star
id|next
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|trans_start
r_int
r_int
id|trans_start
suffix:semicolon
DECL|member|buffs
r_struct
id|sk_buff
op_star
id|buffs
(braket
id|DEV_NUMBUFFS
)braket
suffix:semicolon
DECL|member|backlog
r_struct
id|sk_buff
op_star
id|backlog
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|hard_start_xmit
r_int
(paren
op_star
id|hard_start_xmit
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
)paren
suffix:semicolon
DECL|member|hard_header
r_int
(paren
op_star
id|hard_header
)paren
(paren
r_int
r_char
op_star
id|buff
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|saddr
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|add_arp
r_void
(paren
op_star
id|add_arp
)paren
(paren
r_int
r_int
id|addr
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|queue_xmit
r_void
(paren
op_star
id|queue_xmit
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
r_int
id|pri
)paren
suffix:semicolon
DECL|member|rebuild_header
r_int
(paren
op_star
id|rebuild_header
)paren
(paren
r_void
op_star
id|eth
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|type_trans
r_int
r_int
(paren
op_star
id|type_trans
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
)paren
suffix:semicolon
DECL|member|send_packet
r_void
(paren
op_star
id|send_packet
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
)paren
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|hard_header_len
r_int
r_int
id|hard_header_len
suffix:semicolon
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
DECL|member|broadcast
r_int
r_char
id|broadcast
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|dev_addr
r_int
r_char
id|dev_addr
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|addr_len
r_int
r_char
id|addr_len
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|dev_base
suffix:semicolon
DECL|struct|packet_type
r_struct
id|packet_type
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* This is really NET16(ether_type) other devices&n;&t;&t;&t;   will have to translate appropriately. */
DECL|member|copy
r_int
r_int
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|func
r_int
(paren
op_star
id|func
)paren
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
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|next
r_struct
id|packet_type
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used by dev_rint */
DECL|macro|IN_SKBUFF
mdefine_line|#define IN_SKBUFF 1
r_extern
r_struct
id|packet_type
op_star
id|ptype_base
suffix:semicolon
r_void
id|dev_queue_xmit
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
r_int
id|pri
)paren
suffix:semicolon
r_int
id|dev_rint
(paren
r_int
r_char
op_star
id|buff
comma
r_int
r_int
id|len
comma
r_int
id|flags
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
r_int
id|dev_tint
(paren
r_int
r_char
op_star
id|buff
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|dev_add_pack
(paren
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_void
id|dev_remove_pack
(paren
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_struct
id|device
op_star
id|get_dev
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif
eof
