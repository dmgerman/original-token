multiline_comment|/*&n; *&t;Linux INET6 implementation&n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&n; *&n; *&t;$Id: ipv6.h,v 1.5 1997/03/18 18:24:10 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _NET_IPV6_H
DECL|macro|_NET_IPV6_H
mdefine_line|#define _NET_IPV6_H
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/flow.h&gt;
multiline_comment|/*&n; *&t;NextHeader field of IPv6 header&n; */
DECL|macro|NEXTHDR_HOP
mdefine_line|#define NEXTHDR_HOP&t;&t;0&t;/* Hop-by-hop option header. */
DECL|macro|NEXTHDR_TCP
mdefine_line|#define NEXTHDR_TCP&t;&t;6&t;/* TCP segment. */
DECL|macro|NEXTHDR_UDP
mdefine_line|#define NEXTHDR_UDP&t;&t;17&t;/* UDP message. */
DECL|macro|NEXTHDR_IPV6
mdefine_line|#define NEXTHDR_IPV6&t;&t;41&t;/* IPv6 in IPv6 */
DECL|macro|NEXTHDR_ROUTING
mdefine_line|#define NEXTHDR_ROUTING&t;&t;43&t;/* Routing header. */
DECL|macro|NEXTHDR_FRAGMENT
mdefine_line|#define NEXTHDR_FRAGMENT&t;44&t;/* Fragmentation/reassembly header. */
DECL|macro|NEXTHDR_ESP
mdefine_line|#define NEXTHDR_ESP&t;&t;50&t;/* Encapsulating security payload. */
DECL|macro|NEXTHDR_AUTH
mdefine_line|#define NEXTHDR_AUTH&t;&t;51&t;/* Authentication header. */
DECL|macro|NEXTHDR_ICMP
mdefine_line|#define NEXTHDR_ICMP&t;&t;58&t;/* ICMP for IPv6. */
DECL|macro|NEXTHDR_NONE
mdefine_line|#define NEXTHDR_NONE&t;&t;59&t;/* No next header */
DECL|macro|NEXTHDR_DEST
mdefine_line|#define NEXTHDR_DEST&t;&t;60&t;/* Destination options header. */
DECL|macro|NEXTHDR_MAX
mdefine_line|#define NEXTHDR_MAX&t;&t;255
DECL|macro|IPV6_DEFAULT_HOPLIMIT
mdefine_line|#define IPV6_DEFAULT_HOPLIMIT   64
DECL|macro|IPV6_DEFAULT_MCASTHOPS
mdefine_line|#define IPV6_DEFAULT_MCASTHOPS&t;1
multiline_comment|/*&n; *&t;Addr type&n; *&t;&n; *&t;type&t;-&t;unicast | multicast | anycast&n; *&t;scope&t;-&t;local&t;| site&t;    | global&n; *&t;v4&t;-&t;compat&n; *&t;v4mapped&n; *&t;any&n; *&t;loopback&n; */
DECL|macro|IPV6_ADDR_ANY
mdefine_line|#define IPV6_ADDR_ANY&t;&t;0x0000U
DECL|macro|IPV6_ADDR_UNICAST
mdefine_line|#define IPV6_ADDR_UNICAST      &t;0x0001U&t;
DECL|macro|IPV6_ADDR_MULTICAST
mdefine_line|#define IPV6_ADDR_MULTICAST    &t;0x0002U&t;
DECL|macro|IPV6_ADDR_ANYCAST
mdefine_line|#define IPV6_ADDR_ANYCAST&t;0x0004U
DECL|macro|IPV6_ADDR_LOOPBACK
mdefine_line|#define IPV6_ADDR_LOOPBACK&t;0x0010U
DECL|macro|IPV6_ADDR_LINKLOCAL
mdefine_line|#define IPV6_ADDR_LINKLOCAL&t;0x0020U
DECL|macro|IPV6_ADDR_SITELOCAL
mdefine_line|#define IPV6_ADDR_SITELOCAL&t;0x0040U
DECL|macro|IPV6_ADDR_COMPATv4
mdefine_line|#define IPV6_ADDR_COMPATv4&t;0x0080U
DECL|macro|IPV6_ADDR_SCOPE_MASK
mdefine_line|#define IPV6_ADDR_SCOPE_MASK&t;0x00f0U
DECL|macro|IPV6_ADDR_MAPPED
mdefine_line|#define IPV6_ADDR_MAPPED&t;0x1000U
DECL|macro|IPV6_ADDR_RESERVED
mdefine_line|#define IPV6_ADDR_RESERVED&t;0x2000U&t;/* reserved address space */
multiline_comment|/*&n; *&t;fragmentation header&n; */
DECL|struct|frag_hdr
r_struct
id|frag_hdr
(brace
DECL|member|nexthdr
r_int
r_char
id|nexthdr
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|frag_off
r_int
r_int
id|frag_off
suffix:semicolon
DECL|member|identification
id|__u32
id|identification
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;net/sock.h&gt;
r_extern
r_struct
id|ipv6_mib
id|ipv6_statistics
suffix:semicolon
DECL|struct|ipv6_config
r_struct
id|ipv6_config
(brace
DECL|member|forwarding
r_int
id|forwarding
suffix:semicolon
DECL|member|hop_limit
r_int
id|hop_limit
suffix:semicolon
DECL|member|accept_ra
r_int
id|accept_ra
suffix:semicolon
DECL|member|accept_redirects
r_int
id|accept_redirects
suffix:semicolon
DECL|member|nd_max_mcast_solicit
r_int
id|nd_max_mcast_solicit
suffix:semicolon
DECL|member|nd_max_ucast_solicit
r_int
id|nd_max_ucast_solicit
suffix:semicolon
DECL|member|nd_retrans_time
r_int
id|nd_retrans_time
suffix:semicolon
DECL|member|nd_base_reachable_time
r_int
id|nd_base_reachable_time
suffix:semicolon
DECL|member|nd_delay_probe_time
r_int
id|nd_delay_probe_time
suffix:semicolon
DECL|member|autoconf
r_int
id|autoconf
suffix:semicolon
DECL|member|dad_transmits
r_int
id|dad_transmits
suffix:semicolon
DECL|member|rtr_solicits
r_int
id|rtr_solicits
suffix:semicolon
DECL|member|rtr_solicit_interval
r_int
id|rtr_solicit_interval
suffix:semicolon
DECL|member|rtr_solicit_delay
r_int
id|rtr_solicit_delay
suffix:semicolon
DECL|member|rt_cache_timeout
r_int
id|rt_cache_timeout
suffix:semicolon
DECL|member|rt_gc_period
r_int
id|rt_gc_period
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ipv6_config
id|ipv6_config
suffix:semicolon
DECL|struct|ipv6_frag
r_struct
id|ipv6_frag
(brace
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|fhdr
r_struct
id|frag_hdr
op_star
id|fhdr
suffix:semicolon
DECL|member|next
r_struct
id|ipv6_frag
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Equivalent of ipv4 struct ipq&n; */
DECL|struct|frag_queue
r_struct
id|frag_queue
(brace
DECL|member|next
r_struct
id|frag_queue
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|frag_queue
op_star
id|prev
suffix:semicolon
DECL|member|id
id|__u32
id|id
suffix:semicolon
multiline_comment|/* fragment id&t;&t;*/
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* expire timer&t;&t;*/
DECL|member|fragments
r_struct
id|ipv6_frag
op_star
id|fragments
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|last_in
id|__u8
id|last_in
suffix:semicolon
multiline_comment|/* has last segment arrived? */
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|nhptr
id|__u8
op_star
id|nhptr
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ipv6_routing_header
c_func
(paren
r_struct
id|sk_buff
op_star
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
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_reassembly
c_func
(paren
r_struct
id|sk_buff
op_star
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
)paren
suffix:semicolon
DECL|macro|IPV6_FRAG_TIMEOUT
mdefine_line|#define IPV6_FRAG_TIMEOUT&t;(60*HZ)&t;&t;/* 60 seconds */
multiline_comment|/*&n; *&t;Function prototype for build_xmit&n; */
DECL|typedef|inet_getfrag_t
r_typedef
r_int
(paren
op_star
id|inet_getfrag_t
)paren
(paren
r_const
r_void
op_star
id|data
comma
r_struct
id|in6_addr
op_star
id|addr
comma
r_char
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_addr_type
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
DECL|function|ipv6_addr_scope
r_extern
id|__inline__
r_int
id|ipv6_addr_scope
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
id|ipv6_addr_type
c_func
(paren
id|addr
)paren
op_amp
id|IPV6_ADDR_SCOPE_MASK
suffix:semicolon
)brace
DECL|function|ipv6_addr_cmp
r_extern
id|__inline__
r_int
id|ipv6_addr_cmp
c_func
(paren
r_struct
id|in6_addr
op_star
id|a1
comma
r_struct
id|in6_addr
op_star
id|a2
)paren
(brace
r_return
id|memcmp
c_func
(paren
(paren
r_void
op_star
)paren
id|a1
comma
(paren
r_void
op_star
)paren
id|a2
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_copy
r_extern
id|__inline__
r_void
id|ipv6_addr_copy
c_func
(paren
r_struct
id|in6_addr
op_star
id|a1
comma
r_struct
id|in6_addr
op_star
id|a2
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|a1
comma
(paren
r_void
op_star
)paren
id|a2
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef __HAVE_ARCH_ADDR_SET
DECL|function|ipv6_addr_set
r_extern
id|__inline__
r_void
id|ipv6_addr_set
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
id|__u32
id|w1
comma
id|__u32
id|w2
comma
id|__u32
id|w3
comma
id|__u32
id|w4
)paren
(brace
id|addr-&gt;s6_addr32
(braket
l_int|0
)braket
op_assign
id|w1
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_assign
id|w2
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_assign
id|w3
suffix:semicolon
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
op_assign
id|w4
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ipv6_addr_any
r_extern
id|__inline__
r_int
id|ipv6_addr_any
c_func
(paren
r_struct
id|in6_addr
op_star
id|a
)paren
(brace
r_return
(paren
(paren
id|a-&gt;s6_addr32
(braket
l_int|0
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|1
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|2
)braket
op_or
id|a-&gt;s6_addr32
(braket
l_int|3
)braket
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|gfp_any
r_extern
id|__inline__
r_int
id|gfp_any
c_func
(paren
r_void
)paren
(brace
r_int
id|pri
op_assign
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|intr_count
)paren
id|pri
op_assign
id|GFP_ATOMIC
suffix:semicolon
r_return
id|pri
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Prototypes exported by ipv6&n; */
multiline_comment|/*&n; *&t;rcv function (called from netdevice level)&n; */
r_extern
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
suffix:semicolon
multiline_comment|/*&n; *&t;upper-layer output functions&n; */
r_extern
r_int
id|ip6_xmit
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
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|ip6_nd_hdr
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
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_int
id|proto
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ip6_build_xmit
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|inet_getfrag_t
id|getfrag
comma
r_const
r_void
op_star
id|data
comma
r_struct
id|flowi
op_star
id|fl
comma
r_int
r_int
id|length
comma
r_struct
id|ipv6_options
op_star
id|opt
comma
r_int
id|hlimit
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;skb processing functions&n; */
r_extern
r_int
id|ip6_forward
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|ip6_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|ip6_mc_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Extension header (options) processing&n; */
r_extern
r_int
id|ipv6opt_bld_rthdr
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
r_struct
id|in6_addr
op_star
id|addr
comma
r_int
id|proto
)paren
suffix:semicolon
r_extern
r_int
id|ipv6opt_srcrt_co
c_func
(paren
r_struct
id|sockaddr_in6
op_star
id|sin6
comma
r_int
id|len
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|ipv6opt_srcrt_cl
c_func
(paren
r_struct
id|sockaddr_in6
op_star
id|sin6
comma
r_int
id|num_addrs
comma
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
r_extern
r_int
id|ipv6opt_srt_tosin
c_func
(paren
r_struct
id|ipv6_options
op_star
id|opt
comma
r_struct
id|sockaddr_in6
op_star
id|sin6
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|ipv6opt_free
c_func
(paren
r_struct
id|ipv6_options
op_star
id|opt
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;socket options (ipv6_sockglue.c)&n; */
r_extern
r_int
id|ipv6_setsockopt
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
id|ipv6_getsockopt
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
id|ipv6_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
