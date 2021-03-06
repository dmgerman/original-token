macro_line|#ifndef _NET_DN_ROUTE_H
DECL|macro|_NET_DN_ROUTE_H
mdefine_line|#define _NET_DN_ROUTE_H
multiline_comment|/******************************************************************************&n;    (c) 1995-1998 E.M. Serrat&t;&t;emserrat@geocities.com&n;    &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;*******************************************************************************/
r_extern
r_struct
id|sk_buff
op_star
id|dn_alloc_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|size
comma
r_int
id|pri
)paren
suffix:semicolon
r_extern
r_int
id|dn_route_output
c_func
(paren
r_struct
id|dst_entry
op_star
op_star
id|pprt
comma
id|dn_address
id|dst
comma
id|dn_address
id|src
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|dn_cache_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|dn_cache_getroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|dn_rt_cache_flush
c_func
(paren
r_int
id|delay
)paren
suffix:semicolon
multiline_comment|/* Masks for flags field */
DECL|macro|DN_RT_F_PID
mdefine_line|#define DN_RT_F_PID 0x07 /* Mask for packet type                      */
DECL|macro|DN_RT_F_PF
mdefine_line|#define DN_RT_F_PF  0x80 /* Padding Follows                           */
DECL|macro|DN_RT_F_VER
mdefine_line|#define DN_RT_F_VER 0x40 /* Version =0 discard packet if ==1          */
DECL|macro|DN_RT_F_IE
mdefine_line|#define DN_RT_F_IE  0x20 /* Intra Ethernet, Reserved in short pkt     */
DECL|macro|DN_RT_F_RTS
mdefine_line|#define DN_RT_F_RTS 0x10 /* Packet is being returned to sender        */
DECL|macro|DN_RT_F_RQR
mdefine_line|#define DN_RT_F_RQR 0x08 /* Return packet to sender upon non-delivery */
multiline_comment|/* Mask for types of routing packets */
DECL|macro|DN_RT_PKT_MSK
mdefine_line|#define DN_RT_PKT_MSK   0x06
multiline_comment|/* Types of routing packets */
DECL|macro|DN_RT_PKT_SHORT
mdefine_line|#define DN_RT_PKT_SHORT 0x02 /* Short routing packet */
DECL|macro|DN_RT_PKT_LONG
mdefine_line|#define DN_RT_PKT_LONG  0x06 /* Long routing packet  */
multiline_comment|/* Mask for control/routing selection */
DECL|macro|DN_RT_PKT_CNTL
mdefine_line|#define DN_RT_PKT_CNTL  0x01 /* Set to 1 if a control packet  */
multiline_comment|/* Types of control packets */
DECL|macro|DN_RT_CNTL_MSK
mdefine_line|#define DN_RT_CNTL_MSK  0x0f /* Mask for control packets      */
DECL|macro|DN_RT_PKT_INIT
mdefine_line|#define DN_RT_PKT_INIT  0x01 /* Initialisation packet         */
DECL|macro|DN_RT_PKT_VERI
mdefine_line|#define DN_RT_PKT_VERI  0x03 /* Verification Message          */
DECL|macro|DN_RT_PKT_HELO
mdefine_line|#define DN_RT_PKT_HELO  0x05 /* Hello and Test Message        */
DECL|macro|DN_RT_PKT_L1RT
mdefine_line|#define DN_RT_PKT_L1RT  0x07 /* Level 1 Routing Message       */
DECL|macro|DN_RT_PKT_L2RT
mdefine_line|#define DN_RT_PKT_L2RT  0x09 /* Level 2 Routing Message       */
DECL|macro|DN_RT_PKT_ERTH
mdefine_line|#define DN_RT_PKT_ERTH  0x0b /* Ethernet Router Hello         */
DECL|macro|DN_RT_PKT_EEDH
mdefine_line|#define DN_RT_PKT_EEDH  0x0d /* Ethernet EndNode Hello        */
multiline_comment|/* Values for info field in hello message */
DECL|macro|DN_RT_INFO_TYPE
mdefine_line|#define DN_RT_INFO_TYPE 0x03 /* Type mask                     */
DECL|macro|DN_RT_INFO_L1RT
mdefine_line|#define DN_RT_INFO_L1RT 0x02 /* L1 Router                     */
DECL|macro|DN_RT_INFO_L2RT
mdefine_line|#define DN_RT_INFO_L2RT 0x01 /* L2 Router                     */
DECL|macro|DN_RT_INFO_ENDN
mdefine_line|#define DN_RT_INFO_ENDN 0x03 /* EndNode                       */
DECL|macro|DN_RT_INFO_VERI
mdefine_line|#define DN_RT_INFO_VERI 0x04 /* Verification Reqd.            */
DECL|macro|DN_RT_INFO_RJCT
mdefine_line|#define DN_RT_INFO_RJCT 0x08 /* Reject Flag, Reserved         */
DECL|macro|DN_RT_INFO_VFLD
mdefine_line|#define DN_RT_INFO_VFLD 0x10 /* Verification Failed, Reserved */
DECL|macro|DN_RT_INFO_NOML
mdefine_line|#define DN_RT_INFO_NOML 0x20 /* No Multicast traffic accepted */
DECL|macro|DN_RT_INFO_BLKR
mdefine_line|#define DN_RT_INFO_BLKR 0x40 /* Blocking Requested            */
multiline_comment|/*&n; * The key structure is what we used to look up the route.&n; * The rt_saddr &amp; rt_daddr entries are the same as key.saddr &amp; key.daddr&n; * except for local input routes, where the rt_saddr = key.daddr and&n; * rt_daddr = key.saddr to allow the route to be used for returning&n; * packets to the originating host.&n; */
DECL|struct|dn_route
r_struct
id|dn_route
(brace
r_union
(brace
DECL|member|dst
r_struct
id|dst_entry
id|dst
suffix:semicolon
DECL|member|rt_next
r_struct
id|dn_route
op_star
id|rt_next
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
r_struct
(brace
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
DECL|member|iif
r_int
id|iif
suffix:semicolon
DECL|member|oif
r_int
id|oif
suffix:semicolon
DECL|member|fwmark
id|u32
id|fwmark
suffix:semicolon
DECL|member|key
)brace
id|key
suffix:semicolon
DECL|member|rt_saddr
r_int
r_int
id|rt_saddr
suffix:semicolon
DECL|member|rt_daddr
r_int
r_int
id|rt_daddr
suffix:semicolon
DECL|member|rt_type
r_int
r_char
id|rt_type
suffix:semicolon
DECL|member|rt_scope
r_int
r_char
id|rt_scope
suffix:semicolon
DECL|member|rt_protocol
r_int
r_char
id|rt_protocol
suffix:semicolon
DECL|member|rt_table
r_int
r_char
id|rt_table
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|dn_route_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_route_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
DECL|function|dn_rt_send
r_static
r_inline
r_void
id|dn_rt_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_rt_finish_output
r_static
r_inline
r_void
id|dn_rt_finish_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|dst
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
op_logical_and
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_LOOPBACK
)paren
)paren
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hard_header
op_logical_or
(paren
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ETH_P_DNA_RT
comma
id|dst
comma
l_int|NULL
comma
id|skb-&gt;len
)paren
op_ge
l_int|0
)paren
)paren
id|dn_rt_send
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_nsp_send
r_static
r_inline
r_void
id|dn_nsp_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|skb-&gt;sk
suffix:semicolon
r_struct
id|dn_scp
op_star
id|scp
op_assign
op_amp
id|sk-&gt;protinfo.dn
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|scp-&gt;stamp
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dst
op_assign
id|sk-&gt;dst_cache
)paren
op_logical_and
op_logical_neg
id|dst-&gt;obsolete
)paren
(brace
id|try_again
suffix:colon
id|skb-&gt;dst
op_assign
id|dst_clone
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dst
op_member_access_from_pointer
id|output
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dst_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|sk-&gt;dst_cache
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn_route_output
c_func
(paren
op_amp
id|sk-&gt;dst_cache
comma
id|dn_saddr2dn
c_func
(paren
op_amp
id|scp-&gt;peer
)paren
comma
id|dn_saddr2dn
c_func
(paren
op_amp
id|scp-&gt;addr
)paren
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|dst
op_assign
id|sk-&gt;dst_cache
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
)brace
id|sk-&gt;err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
macro_line|#endif /* _NET_DN_ROUTE_H */
eof
