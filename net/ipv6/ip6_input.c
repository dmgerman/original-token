multiline_comment|/*&n; *&t;IPv6 input&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&t;Ian P. Morris&t;&t;&lt;I.P.Morris@soton.ac.uk&gt;&n; *&n; *&t;$Id: ip6_input.c,v 1.6 1997/05/11 16:06:52 davem Exp $&n; *&n; *&t;Based in linux/net/ipv4/ip_input.c&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/rawv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
r_static
r_int
id|ipv6_dest_opt
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb_ptr
comma
r_struct
id|device
op_star
id|dev
comma
id|__u8
op_star
id|nhptr
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
DECL|struct|hdrtype_proc
r_struct
id|hdrtype_proc
(brace
DECL|member|type
id|u8
id|type
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
op_star
comma
r_struct
id|device
op_star
id|dev
comma
id|__u8
op_star
id|ptr
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
DECL|variable|hdrproc_lst
)brace
id|hdrproc_lst
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t;TODO&n;&n;&t;{NEXTHDR_HOP,&t;&t;ipv6_hop_by_hop}&n;&t;{NEXTHDR_ROUTING,&t;ipv6_routing_header},&n;   */
(brace
id|NEXTHDR_FRAGMENT
comma
id|ipv6_reassembly
)brace
comma
(brace
id|NEXTHDR_DEST
comma
id|ipv6_dest_opt
)brace
comma
multiline_comment|/*&t;&n;&t;{NEXTHDR_AUTH,&t;&t;ipv6_auth_hdr},&n;&t;{NEXTHDR_ESP,&t;&t;ipv6_esp_hdr},&n;    */
(brace
id|NEXTHDR_MAX
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/* New header structures */
DECL|struct|ipv6_tlvtype
r_struct
id|ipv6_tlvtype
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipv6_destopt_hdr
r_struct
id|ipv6_destopt_hdr
(brace
DECL|member|nexthdr
id|u8
id|nexthdr
suffix:semicolon
DECL|member|hdrlen
id|u8
id|hdrlen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tlvtype_proc
r_struct
id|tlvtype_proc
(brace
DECL|member|type
id|u8
id|type
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
id|dev
comma
id|__u8
op_star
id|ptr
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;these functions do NOT update skb-&gt;h.raw&n;&t; */
DECL|variable|tlvprocdestopt_lst
)brace
id|tlvprocdestopt_lst
(braket
)braket
op_assign
(brace
(brace
l_int|255
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|ip6_dstopt_unknown
r_static
r_int
id|ip6_dstopt_unknown
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipv6_tlvtype
op_star
id|hdr
)paren
(brace
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_int
id|pos
suffix:semicolon
multiline_comment|/*&n;&t; *&t;unkown destination option type&n;&t; */
id|pos
op_assign
(paren
id|__u8
op_star
)paren
id|skb-&gt;h.raw
op_minus
(paren
id|__u8
op_star
)paren
id|skb-&gt;nh.raw
suffix:semicolon
multiline_comment|/* I think this is correct please check - IPM */
r_switch
c_cond
(paren
(paren
id|hdr-&gt;type
op_amp
l_int|0xC0
)paren
op_rshift
l_int|6
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* ignore */
id|skb-&gt;h.raw
op_add_assign
id|hdr-&gt;len
op_plus
l_int|2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* drop packet */
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* send ICMP PARM PROB regardless and drop packet */
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_PARAMPROB
comma
id|ICMPV6_UNK_OPTION
comma
id|pos
comma
id|skb-&gt;dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Send ICMP if not a multicast address and drop packet */
id|daddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
id|daddr
)paren
op_amp
id|IPV6_ADDR_MULTICAST
)paren
)paren
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_PARAMPROB
comma
id|ICMPV6_UNK_OPTION
comma
id|pos
comma
id|skb-&gt;dev
)paren
suffix:semicolon
)brace
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip6_parse_tlv
r_static
r_int
id|ip6_parse_tlv
c_func
(paren
r_struct
id|tlvtype_proc
op_star
id|procs
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
comma
id|__u8
op_star
id|nhptr
comma
r_struct
id|ipv6_options
op_star
id|opt
comma
r_void
op_star
id|lastopt
)paren
(brace
r_struct
id|ipv6_tlvtype
op_star
id|hdr
suffix:semicolon
r_struct
id|tlvtype_proc
op_star
id|curr
suffix:semicolon
r_while
c_loop
(paren
(paren
id|hdr
op_assign
(paren
r_struct
id|ipv6_tlvtype
op_star
)paren
id|skb-&gt;h.raw
)paren
op_ne
id|lastopt
)paren
(brace
r_switch
c_cond
(paren
id|hdr-&gt;type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* TLV encoded Pad1 */
id|skb-&gt;h.raw
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* TLV encoded PadN */
id|skb-&gt;h.raw
op_add_assign
id|hdr-&gt;len
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Other TLV code so scan list */
r_for
c_loop
(paren
id|curr
op_assign
id|procs
suffix:semicolon
id|curr-&gt;type
op_ne
l_int|255
suffix:semicolon
id|curr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|curr-&gt;type
op_eq
(paren
id|hdr-&gt;type
)paren
)paren
(brace
id|curr
op_member_access_from_pointer
id|func
c_func
(paren
id|skb
comma
id|dev
comma
id|nhptr
comma
id|opt
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
id|hdr-&gt;len
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|curr-&gt;type
op_eq
l_int|255
)paren
(brace
r_if
c_cond
(paren
id|ip6_dstopt_unknown
c_func
(paren
id|skb
comma
id|hdr
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ipv6_dest_opt
r_static
r_int
id|ipv6_dest_opt
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb_ptr
comma
r_struct
id|device
op_star
id|dev
comma
id|__u8
op_star
id|nhptr
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|skb_ptr
suffix:semicolon
r_struct
id|ipv6_destopt_hdr
op_star
id|hdr
op_assign
(paren
r_struct
id|ipv6_destopt_hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|lastopt
op_assign
id|skb-&gt;h.raw
op_plus
id|hdr-&gt;hdrlen
op_plus
r_sizeof
(paren
r_struct
id|ipv6_destopt_hdr
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
r_sizeof
(paren
r_struct
id|ipv6_destopt_hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip6_parse_tlv
c_func
(paren
id|tlvprocdestopt_lst
comma
id|skb
comma
id|dev
comma
id|nhptr
comma
id|opt
comma
id|lastopt
)paren
)paren
id|res
op_assign
id|hdr-&gt;nexthdr
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
id|hdr-&gt;hdrlen
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|ipv6_rcv
r_int
id|ipv6_rcv
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
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
suffix:semicolon
r_int
id|pkt_len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_OTHERHOST
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
op_logical_or
id|hdr-&gt;version
op_ne
l_int|6
)paren
r_goto
id|err
suffix:semicolon
id|pkt_len
op_assign
id|ntohs
c_func
(paren
id|hdr-&gt;payload_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
OG
id|skb-&gt;len
)paren
r_goto
id|err
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|pkt_len
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
suffix:semicolon
id|ip6_route_input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|ipv6_statistics.Ip6InHdrErrors
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;0 - deliver&n; *&t;1 - block&n; */
DECL|function|icmpv6_filter
r_static
id|__inline__
r_int
id|icmpv6_filter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|icmp6hdr
op_star
id|icmph
suffix:semicolon
r_struct
id|raw6_opt
op_star
id|opt
suffix:semicolon
id|opt
op_assign
op_amp
id|sk-&gt;tp_pinfo.tp_raw
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
(paren
id|skb-&gt;nh.ipv6h
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|test_bit
c_func
(paren
id|icmph-&gt;icmp6_type
comma
op_amp
id|opt-&gt;filter
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;demultiplex raw sockets.&n; *&t;(should consider queueing the skb in the sock receive_queue&n; *&t;without calling rawv6.c)&n; */
DECL|function|ipv6_raw_deliver
r_static
r_struct
id|sock
op_star
id|ipv6_raw_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipv6_options
op_star
id|opt
comma
r_int
id|nexthdr
comma
r_int
id|len
)paren
(brace
r_struct
id|in6_addr
op_star
id|saddr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
comma
op_star
id|sk2
suffix:semicolon
id|__u8
id|hash
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|daddr
op_assign
id|saddr
op_plus
l_int|1
suffix:semicolon
id|hash
op_assign
id|nexthdr
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
id|sk
op_assign
id|raw_v6_htable
(braket
id|hash
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The first socket found will be delivered after&n;&t; *&t;delivery to transport protocols.&n;&t; */
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|sk
op_assign
id|raw_v6_lookup
c_func
(paren
id|sk
comma
id|nexthdr
comma
id|daddr
comma
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
id|sk2
op_assign
id|sk
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sk2
op_assign
id|raw_v6_lookup
c_func
(paren
id|sk2-&gt;next
comma
id|nexthdr
comma
id|daddr
comma
id|saddr
)paren
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|buff
suffix:semicolon
r_if
c_cond
(paren
id|nexthdr
op_eq
id|IPPROTO_ICMPV6
op_logical_and
id|icmpv6_filter
c_func
(paren
id|sk2
comma
id|skb
)paren
)paren
r_continue
suffix:semicolon
id|buff
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|buff-&gt;sk
op_assign
id|sk2
suffix:semicolon
id|rawv6_rcv
c_func
(paren
id|buff
comma
id|skb-&gt;dev
comma
id|saddr
comma
id|daddr
comma
id|opt
comma
id|len
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sk
op_logical_and
id|nexthdr
op_eq
id|IPPROTO_ICMPV6
op_logical_and
id|icmpv6_filter
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
id|sk
op_assign
l_int|NULL
suffix:semicolon
r_return
id|sk
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Deliver the packet to the host&n; */
DECL|function|ip6_input
r_int
id|ip6_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ipv6_options
op_star
id|opt
op_assign
(paren
r_struct
id|ipv6_options
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_struct
id|inet6_protocol
op_star
id|ipprot
suffix:semicolon
r_struct
id|hdrtype_proc
op_star
id|hdrt
suffix:semicolon
r_struct
id|sock
op_star
id|raw_sk
suffix:semicolon
id|__u8
op_star
id|nhptr
suffix:semicolon
r_int
id|nexthdr
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|u8
id|hash
suffix:semicolon
r_int
id|len
suffix:semicolon
id|skb-&gt;h.raw
op_add_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Parse extension headers&n;&t; */
id|nexthdr
op_assign
id|hdr-&gt;nexthdr
suffix:semicolon
id|nhptr
op_assign
op_amp
id|hdr-&gt;nexthdr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;check for extension headers&n;&t; */
id|st_loop
suffix:colon
r_for
c_loop
(paren
id|hdrt
op_assign
id|hdrproc_lst
suffix:semicolon
id|hdrt-&gt;type
op_ne
id|NEXTHDR_MAX
suffix:semicolon
id|hdrt
op_increment
)paren
(brace
r_if
c_cond
(paren
id|hdrt-&gt;type
op_eq
id|nexthdr
)paren
(brace
r_if
c_cond
(paren
(paren
id|nexthdr
op_assign
id|hdrt
op_member_access_from_pointer
id|func
c_func
(paren
op_amp
id|skb
comma
id|skb-&gt;dev
comma
id|nhptr
comma
id|opt
)paren
)paren
)paren
(brace
id|nhptr
op_assign
id|skb-&gt;h.raw
suffix:semicolon
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_goto
id|st_loop
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|len
op_assign
id|skb-&gt;tail
op_minus
id|skb-&gt;h.raw
suffix:semicolon
id|raw_sk
op_assign
id|ipv6_raw_deliver
c_func
(paren
id|skb
comma
id|opt
comma
id|nexthdr
comma
id|len
)paren
suffix:semicolon
id|hash
op_assign
id|nexthdr
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ipprot
op_assign
(paren
r_struct
id|inet6_protocol
op_star
)paren
id|inet6_protos
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
(paren
r_struct
id|inet6_protocol
op_star
)paren
id|ipprot-&gt;next
)paren
(brace
r_struct
id|sk_buff
op_star
id|buff
op_assign
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|ipprot-&gt;protocol
op_ne
id|nexthdr
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ipprot-&gt;copy
op_logical_or
id|raw_sk
)paren
id|buff
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|ipprot
op_member_access_from_pointer
id|handler
c_func
(paren
id|buff
comma
id|skb-&gt;dev
comma
op_amp
id|hdr-&gt;saddr
comma
op_amp
id|hdr-&gt;daddr
comma
id|opt
comma
id|len
comma
l_int|0
comma
id|ipprot
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raw_sk
)paren
(brace
id|skb-&gt;sk
op_assign
id|raw_sk
suffix:semicolon
id|rawv6_rcv
c_func
(paren
id|skb
comma
id|skb-&gt;dev
comma
op_amp
id|hdr-&gt;saddr
comma
op_amp
id|hdr-&gt;daddr
comma
id|opt
comma
id|len
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;not found: send ICMP parameter problem back&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
macro_line|#if IP6_DEBUG &gt;= 2
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;proto not found %d&bslash;n&quot;
comma
id|nexthdr
)paren
suffix:semicolon
macro_line|#endif
id|offset
op_assign
id|nhptr
op_minus
(paren
id|u8
op_star
)paren
id|hdr
suffix:semicolon
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_PARAMPROB
comma
id|ICMPV6_UNK_NEXTHDR
comma
id|offset
comma
id|skb-&gt;dev
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip6_mc_input
r_int
id|ip6_mc_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|hdr
suffix:semicolon
r_int
id|deliver
op_assign
l_int|0
suffix:semicolon
r_int
id|discard
op_assign
l_int|1
suffix:semicolon
id|hdr
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_chk_mcast_addr
c_func
(paren
id|skb-&gt;dev
comma
op_amp
id|hdr-&gt;daddr
)paren
)paren
id|deliver
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|ipv6_config.multicast_route
)paren
(brace
r_int
id|addr_type
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|hdr-&gt;daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
(paren
id|IPV6_ADDR_LOOPBACK
op_or
id|IPV6_ADDR_LINKLOCAL
)paren
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|deliver
)paren
(brace
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
)brace
r_else
(brace
id|discard
op_assign
l_int|0
suffix:semicolon
id|skb2
op_assign
id|skb
suffix:semicolon
)brace
id|dst
op_member_access_from_pointer
id|output
c_func
(paren
id|skb2
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|deliver
)paren
(brace
id|discard
op_assign
l_int|0
suffix:semicolon
id|ip6_input
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|discard
)paren
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof