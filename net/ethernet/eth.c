multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Ethernet-type device handling.&n; *&n; * Version:&t;@(#)eth.c&t;1.0.7&t;05/25/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;&n; *&t;&t;Florian  La Roche, &lt;rzsfl@rz.uni-sb.de&gt;&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; * &n; * Fixes:&n; *&t;&t;Mr Linux&t;: Arp problems&n; *&t;&t;Alan Cox&t;: Generic queue tidyup (very tiny here)&n; *&t;&t;Alan Cox&t;: eth_header ntohs should be htons&n; *&t;&t;Alan Cox&t;: eth_rebuild_header missing an htons and&n; *&t;&t;&t;&t;  minor other things.&n; *&t;&t;Tegge&t;&t;: Arp bug fixes. &n; *&t;&t;Florian&t;&t;: Removed many unnecessary functions, code cleanup&n; *&t;&t;&t;&t;  and changes for new arp and skbuff.&n; *&t;&t;Alan Cox&t;: Redid header building to reflect new format.&n; *&t;&t;Alan Cox&t;: ARP only when compiled with CONFIG_INET&n; *&t;&t;Greg Page&t;: 802.2 and SNAP stuff.&n; *&t;&t;Alan Cox&t;: MAC layer pointers/new format.&n; *&t;&t;Paul Gortmaker&t;: eth_copy_and_sum shouldn&squot;t csum padding.&n; *&t;&t;Alan Cox&t;: Protect against forwarding explosions with&n; *&t;&t;&t;&t;  older network drivers and IFF_ALLMULTI.&n; *&t;Christer Weinigel&t;: Better rebuild header message.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
DECL|function|eth_setup
r_void
id|eth_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_struct
id|device
op_star
id|d
op_assign
id|dev_base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
op_logical_or
op_logical_neg
op_star
id|str
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|d
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
id|d-&gt;name
)paren
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
id|d-&gt;irq
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
id|d-&gt;base_addr
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|2
)paren
id|d-&gt;mem_start
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|3
)paren
id|d-&gt;mem_end
op_assign
id|ints
(braket
l_int|4
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
id|d
op_assign
id|d-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t; Create the Ethernet MAC header for an arbitrary protocol layer &n; *&n; *&t;saddr=NULL&t;means use device source address&n; *&t;daddr=NULL&t;means leave destination address (eg unresolved arp)&n; */
DECL|function|eth_header
r_int
id|eth_header
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
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
(brace
r_struct
id|ethhdr
op_star
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|ETH_HLEN
)paren
suffix:semicolon
multiline_comment|/* &n;&t; *&t;Set the protocol type. For a packet of type ETH_P_802_3 we put the length&n;&t; *&t;in here instead. It is up to the 802.2 layer to carry protocol information.&n;&t; */
r_if
c_cond
(paren
id|type
op_ne
id|ETH_P_802_3
)paren
(brace
id|eth-&gt;h_proto
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
)brace
r_else
id|eth-&gt;h_proto
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Set the source hardware address. &n;&t; */
r_if
c_cond
(paren
id|saddr
)paren
(brace
id|memcpy
c_func
(paren
id|eth-&gt;h_source
comma
id|saddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|eth-&gt;h_source
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Anyway, the loopback-device should never use this function... &n;&t; */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_LOOPBACK
)paren
(brace
id|memset
c_func
(paren
id|eth-&gt;h_dest
comma
l_int|0
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|daddr
)paren
(brace
id|memcpy
c_func
(paren
id|eth-&gt;h_dest
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
r_return
op_minus
id|dev-&gt;hard_header_len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Rebuild the Ethernet MAC header. This is called after an ARP&n; *&t;(or in future other address resolution) has completed on this&n; *&t;sk_buff. We now let ARP fill in the other fields.&n; */
DECL|function|eth_rebuild_header
r_int
id|eth_rebuild_header
c_func
(paren
r_void
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
id|dst
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ethhdr
op_star
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|buff
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Only ARP/IP is currently supported&n;&t; */
r_if
c_cond
(paren
id|eth-&gt;h_proto
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: unable to resolve type %X addresses.&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|eth-&gt;h_proto
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth-&gt;h_source
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Try to get ARP to resolve the header.&n;&t; */
macro_line|#ifdef CONFIG_INET&t; 
r_return
id|arp_find
c_func
(paren
id|eth-&gt;h_dest
comma
id|dst
comma
id|dev
comma
id|dev-&gt;pa_addr
comma
id|skb
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif&t;
)brace
multiline_comment|/*&n; *&t;Determine the packet&squot;s protocol ID. The rule here is that we &n; *&t;assume 802.3 if the type field is short enough to be a length.&n; *&t;This is normal practice and works for any &squot;now in use&squot; protocol.&n; */
DECL|function|eth_type_trans
r_int
r_int
id|eth_type_trans
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
)paren
(brace
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
r_int
r_char
op_star
id|rawp
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|eth
op_assign
id|skb-&gt;mac.ethernet
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eth-&gt;h_dest
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|eth-&gt;h_dest
comma
id|dev-&gt;broadcast
comma
id|ETH_ALEN
)paren
op_eq
l_int|0
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
)brace
r_else
id|skb-&gt;pkt_type
op_assign
id|PACKET_MULTICAST
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;This ALLMULTI check should be redundant by 1.4&n;&t; *&t;so don&squot;t forget to remove it.&n;&t; */
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
(paren
id|IFF_PROMISC
op_or
id|IFF_ALLMULTI
)paren
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|eth-&gt;h_dest
comma
id|dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|eth-&gt;h_proto
)paren
op_ge
l_int|1536
)paren
r_return
id|eth-&gt;h_proto
suffix:semicolon
id|rawp
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; *&t;This is a magic hack to spot IPX packets. Older Novell breaks&n;&t; *&t;the protocol design and runs IPX over 802.3 without an 802.2 LLC&n;&t; *&t;layer. We look for FFFF which isn&squot;t a used 802.2 SSAP/DSAP. This&n;&t; *&t;won&squot;t work for fault tolerant netware but does for the rest.&n;&t; */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|rawp
op_eq
l_int|0xFFFF
)paren
r_return
id|htons
c_func
(paren
id|ETH_P_802_3
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Real 802.2 LLC&n;&t; */
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Upper level calls this function to bind hardware header cache entry.&n; * If the call is successful, then corresponding Address Resolution Protocol&n; * (maybe, not ARP) takes responsibility for updating cache content.&n; */
DECL|function|eth_header_cache_bind
r_void
id|eth_header_cache_bind
c_func
(paren
r_struct
id|hh_cache
op_star
op_star
id|hhp
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|htype
comma
id|__u32
id|daddr
)paren
(brace
r_struct
id|hh_cache
op_star
id|hh
suffix:semicolon
r_if
c_cond
(paren
id|htype
op_ne
id|ETH_P_IP
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;eth_header_cache_bind: %04x cache is not implemented&bslash;n&quot;
comma
id|htype
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arp_bind_cache
c_func
(paren
id|hhp
comma
id|dev
comma
id|htype
comma
id|daddr
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hh
op_assign
op_star
id|hhp
)paren
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|hh-&gt;hh_data
op_plus
l_int|6
comma
id|dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|hh-&gt;hh_data
(braket
l_int|12
)braket
op_assign
id|htype
op_rshift
l_int|8
suffix:semicolon
id|hh-&gt;hh_data
(braket
l_int|13
)braket
op_assign
id|htype
op_amp
l_int|0xFF
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called by Address Resolution module to notify changes in address.&n; */
DECL|function|eth_header_cache_update
r_void
id|eth_header_cache_update
c_func
(paren
r_struct
id|hh_cache
op_star
id|hh
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_char
op_star
id|haddr
)paren
(brace
r_if
c_cond
(paren
id|hh-&gt;hh_type
op_ne
id|ETH_P_IP
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;eth_header_cache_update: %04x cache is not implemented&bslash;n&quot;
comma
id|hh-&gt;hh_type
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|hh-&gt;hh_data
comma
id|haddr
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|hh-&gt;hh_uptodate
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Copy from an ethernet device memory space to an sk_buff while checksumming if IP&n; */
DECL|function|eth_copy_and_sum
r_void
id|eth_copy_and_sum
c_func
(paren
r_struct
id|sk_buff
op_star
id|dest
comma
r_int
r_char
op_star
id|src
comma
r_int
id|length
comma
r_int
id|base
)paren
(brace
macro_line|#ifdef CONFIG_IP_ROUTER
id|memcpy
c_func
(paren
id|dest-&gt;data
comma
id|src
comma
id|length
)paren
suffix:semicolon
macro_line|#else
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_int
id|ip_length
suffix:semicolon
id|IS_SKB
c_func
(paren
id|dest
)paren
suffix:semicolon
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|dest-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|eth-&gt;h_proto
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|dest-&gt;data
comma
id|src
comma
id|length
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We have to watch for padded packets. The csum doesn&squot;t include the&n;&t; * padding, and there is no point in copying the padding anyway.&n;&t; * We have to use the smaller of length and ip_length because it&n;&t; * can happen that ip_length &gt; length.&n;&t; */
id|memcpy
c_func
(paren
id|dest-&gt;data
comma
id|src
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
id|ETH_HLEN
)paren
suffix:semicolon
multiline_comment|/* ethernet is always &gt;= 34 */
id|length
op_sub_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
id|ETH_HLEN
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|src
op_plus
id|ETH_HLEN
)paren
suffix:semicolon
id|ip_length
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
multiline_comment|/* Also watch out for bogons - min IP size is 8 (rfc-1042) */
r_if
c_cond
(paren
(paren
id|ip_length
op_le
id|length
)paren
op_logical_and
(paren
id|ip_length
OG
l_int|7
)paren
)paren
id|length
op_assign
id|ip_length
suffix:semicolon
id|dest-&gt;csum
op_assign
id|csum_partial_copy
c_func
(paren
id|src
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
id|ETH_HLEN
comma
id|dest-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_plus
id|ETH_HLEN
comma
id|length
comma
id|base
)paren
suffix:semicolon
id|dest-&gt;ip_summed
op_assign
l_int|1
suffix:semicolon
macro_line|#endif&t;
)brace
eof
