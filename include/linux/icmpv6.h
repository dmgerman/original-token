macro_line|#ifndef _LINUX_ICMPV6_H
DECL|macro|_LINUX_ICMPV6_H
mdefine_line|#define _LINUX_ICMPV6_H
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|struct|icmpv6hdr
r_struct
id|icmpv6hdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|checksum
id|__u16
id|checksum
suffix:semicolon
r_union
(brace
DECL|struct|icmpv6_echo
r_struct
id|icmpv6_echo
(brace
DECL|member|identifier
id|__u16
id|identifier
suffix:semicolon
DECL|member|sequence
id|__u16
id|sequence
suffix:semicolon
DECL|member|u_echo
)brace
id|u_echo
suffix:semicolon
DECL|member|pointer
id|__u32
id|pointer
suffix:semicolon
DECL|member|mtu
id|__u32
id|mtu
suffix:semicolon
DECL|member|unused
id|__u32
id|unused
suffix:semicolon
DECL|struct|icmpv6_nd_advt
r_struct
id|icmpv6_nd_advt
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved
id|__u32
id|reserved
suffix:colon
l_int|5
comma
DECL|member|override
id|override
suffix:colon
l_int|1
comma
DECL|member|solicited
id|solicited
suffix:colon
l_int|1
comma
DECL|member|router
id|router
suffix:colon
l_int|1
comma
DECL|member|reserved2
id|reserved2
suffix:colon
l_int|24
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|__u32
id|router
suffix:colon
l_int|1
comma
id|solicited
suffix:colon
l_int|1
comma
id|override
suffix:colon
l_int|1
comma
id|reserved
suffix:colon
l_int|29
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif&t;&t;&t;&t;&t;&t;
DECL|member|u_nd_advt
)brace
id|u_nd_advt
suffix:semicolon
DECL|struct|icmpv6_nd_ra
r_struct
id|icmpv6_nd_ra
(brace
DECL|member|hop_limit
id|__u8
id|hop_limit
suffix:semicolon
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|6
comma
DECL|member|other
id|other
suffix:colon
l_int|1
comma
DECL|member|managed
id|managed
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|member|managed
id|__u8
id|managed
suffix:colon
l_int|1
comma
DECL|member|other
id|other
suffix:colon
l_int|1
comma
DECL|member|reserved
id|reserved
suffix:colon
l_int|6
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|rt_lifetime
id|__u16
id|rt_lifetime
suffix:semicolon
DECL|member|u_nd_ra
)brace
id|u_nd_ra
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|macro|icmp6_identifier
mdefine_line|#define icmp6_identifier&t;u.u_echo.identifier
DECL|macro|icmp6_sequence
mdefine_line|#define icmp6_sequence&t;&t;u.u_echo.sequence
DECL|macro|icmp6_pointer
mdefine_line|#define icmp6_pointer&t;&t;u.pointer
DECL|macro|icmp6_mtu
mdefine_line|#define icmp6_mtu&t;&t;u.mtu
DECL|macro|icmp6_unused
mdefine_line|#define icmp6_unused&t;&t;u.unused
DECL|macro|icmp6_router
mdefine_line|#define icmp6_router&t;&t;u.u_nd_advt.router
DECL|macro|icmp6_solicited
mdefine_line|#define icmp6_solicited&t;&t;u.u_nd_advt.solicited
DECL|macro|icmp6_override
mdefine_line|#define icmp6_override&t;&t;u.u_nd_advt.override
DECL|macro|icmp6_ndiscreserved
mdefine_line|#define icmp6_ndiscreserved&t;u.u_nd_advt.reserved
DECL|macro|icmp6_hop_limit
mdefine_line|#define icmp6_hop_limit&t;&t;u.u_nd_ra.hop_limit
DECL|macro|icmp6_addrconf_managed
mdefine_line|#define icmp6_addrconf_managed&t;u.u_nd_ra.managed
DECL|macro|icmp6_addrconf_other
mdefine_line|#define icmp6_addrconf_other&t;u.u_nd_ra.other
DECL|macro|icmp6_rt_lifetime
mdefine_line|#define icmp6_rt_lifetime&t;u.u_nd_ra.rt_lifetime
)brace
suffix:semicolon
DECL|macro|ICMPV6_DEST_UNREACH
mdefine_line|#define ICMPV6_DEST_UNREACH&t;&t;1
DECL|macro|ICMPV6_PKT_TOOBIG
mdefine_line|#define ICMPV6_PKT_TOOBIG&t;&t;2
DECL|macro|ICMPV6_TIME_EXCEEDED
mdefine_line|#define ICMPV6_TIME_EXCEEDED&t;&t;3
DECL|macro|ICMPV6_PARAMETER_PROB
mdefine_line|#define ICMPV6_PARAMETER_PROB&t;&t;4
DECL|macro|ICMPV6_ECHO_REQUEST
mdefine_line|#define ICMPV6_ECHO_REQUEST&t;&t;128
DECL|macro|ICMPV6_ECHO_REPLY
mdefine_line|#define ICMPV6_ECHO_REPLY&t;&t;129
DECL|macro|ICMPV6_MEMBERSHIP_QUERY
mdefine_line|#define ICMPV6_MEMBERSHIP_QUERY&t;&t;130
DECL|macro|ICMPV6_MEMBERSHIP_REPORT
mdefine_line|#define ICMPV6_MEMBERSHIP_REPORT       &t;131
DECL|macro|ICMPV6_MEMBERSHIP_REDUCTION
mdefine_line|#define ICMPV6_MEMBERSHIP_REDUCTION    &t;132
multiline_comment|/*&n; *&t;Codes for Destination Unreachable&n; */
DECL|macro|ICMPV6_NOROUTE
mdefine_line|#define ICMPV6_NOROUTE&t;&t;&t;0
DECL|macro|ICMPV6_ADM_PROHIBITED
mdefine_line|#define ICMPV6_ADM_PROHIBITED&t;&t;1
DECL|macro|ICMPV6_NOT_NEIGHBOUR
mdefine_line|#define ICMPV6_NOT_NEIGHBOUR&t;&t;2
DECL|macro|ICMPV6_ADDR_UNREACH
mdefine_line|#define ICMPV6_ADDR_UNREACH&t;&t;3
DECL|macro|ICMPV6_PORT_UNREACH
mdefine_line|#define ICMPV6_PORT_UNREACH&t;&t;4
multiline_comment|/*&n; *&t;Codes for Time Exceeded&n; */
DECL|macro|ICMPV6_EXC_HOPLIMIT
mdefine_line|#define ICMPV6_EXC_HOPLIMIT&t;&t;0
DECL|macro|ICMPV6_EXC_FRAGTIME
mdefine_line|#define ICMPV6_EXC_FRAGTIME&t;&t;1
multiline_comment|/*&n; *&t;Codes for Parameter Problem&n; */
DECL|macro|ICMPV6_HDR_FIELD
mdefine_line|#define ICMPV6_HDR_FIELD&t;&t;0
DECL|macro|ICMPV6_UNK_NEXTHDR
mdefine_line|#define ICMPV6_UNK_NEXTHDR&t;&t;1
DECL|macro|ICMPV6_UNK_OPTION
mdefine_line|#define ICMPV6_UNK_OPTION&t;&t;2
multiline_comment|/*&n; *&t;constants for (set|get)sockopt&n; */
DECL|macro|ICMPV6_FILTER
mdefine_line|#define ICMPV6_FILTER&t;&t;&t;1
multiline_comment|/*&n; *&t;ICMPV6 filter&n; */
DECL|macro|ICMPV6_FILTER_BLOCK
mdefine_line|#define ICMPV6_FILTER_BLOCK&t;&t;1
DECL|macro|ICMPV6_FILTER_PASS
mdefine_line|#define ICMPV6_FILTER_PASS&t;&t;2
DECL|macro|ICMPV6_FILTER_BLOCKOTHERS
mdefine_line|#define ICMPV6_FILTER_BLOCKOTHERS&t;3
DECL|macro|ICMPV6_FILTER_PASSONLY
mdefine_line|#define ICMPV6_FILTER_PASSONLY&t;&t;4
DECL|struct|icmp6_filter
r_struct
id|icmp6_filter
(brace
DECL|member|data
id|__u32
id|data
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_extern
r_void
id|icmpv6_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
r_int
id|code
comma
id|__u32
id|info
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|icmpv6_init
c_func
(paren
r_struct
id|net_proto_family
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_int
id|icmpv6_err_convert
c_func
(paren
r_int
id|type
comma
r_int
id|code
comma
r_int
op_star
id|err
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof