multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the IP router interface.&n; *&n; * Version:&t;@(#)route.h&t;1.0.3&t;05/27/93&n; *&n; * Authors:&t;Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988&n; *&t;&t;for the purposes of compatibility only.&n; *&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_ROUTE_H
DECL|macro|_LINUX_ROUTE_H
mdefine_line|#define _LINUX_ROUTE_H
macro_line|#include &lt;linux/if.h&gt;
multiline_comment|/* This structure gets passed by the SIOCADDRT and SIOCDELRT calls. */
DECL|struct|rtentry
r_struct
id|rtentry
(brace
DECL|member|rt_pad1
r_int
r_int
id|rt_pad1
suffix:semicolon
DECL|member|rt_dst
r_struct
id|sockaddr
id|rt_dst
suffix:semicolon
multiline_comment|/* target address&t;&t;*/
DECL|member|rt_gateway
r_struct
id|sockaddr
id|rt_gateway
suffix:semicolon
multiline_comment|/* gateway addr (RTF_GATEWAY)&t;*/
DECL|member|rt_genmask
r_struct
id|sockaddr
id|rt_genmask
suffix:semicolon
multiline_comment|/* target network mask (IP)&t;*/
DECL|member|rt_flags
r_int
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_pad2
r_int
id|rt_pad2
suffix:semicolon
DECL|member|rt_pad3
r_int
r_int
id|rt_pad3
suffix:semicolon
DECL|member|rt_tos
r_int
r_char
id|rt_tos
suffix:semicolon
DECL|member|rt_class
r_int
r_char
id|rt_class
suffix:semicolon
DECL|member|rt_pad4
r_int
id|rt_pad4
suffix:semicolon
DECL|member|rt_metric
r_int
id|rt_metric
suffix:semicolon
multiline_comment|/* +1 for binary compatibility!&t;*/
DECL|member|rt_dev
r_char
op_star
id|rt_dev
suffix:semicolon
multiline_comment|/* forcing the device at add&t;*/
DECL|member|rt_mtu
r_int
r_int
id|rt_mtu
suffix:semicolon
multiline_comment|/* per route MTU/Window &t;*/
macro_line|#ifndef __KERNEL__
DECL|macro|rt_mss
mdefine_line|#define rt_mss&t;rt_mtu&t;&t;&t;/* Compatibility :-(            */
macro_line|#endif
DECL|member|rt_window
r_int
r_int
id|rt_window
suffix:semicolon
multiline_comment|/* Window clamping &t;&t;*/
DECL|member|rt_irtt
r_int
r_int
id|rt_irtt
suffix:semicolon
multiline_comment|/* Initial RTT&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|RTF_UP
mdefine_line|#define&t;RTF_UP&t;&t;0x0001&t;&t;/* route usable&t;&t;  &t;*/
DECL|macro|RTF_GATEWAY
mdefine_line|#define&t;RTF_GATEWAY&t;0x0002&t;&t;/* destination is a gateway&t;*/
DECL|macro|RTF_HOST
mdefine_line|#define&t;RTF_HOST&t;0x0004&t;&t;/* host entry (net otherwise)&t;*/
DECL|macro|RTF_REINSTATE
mdefine_line|#define RTF_REINSTATE&t;0x0008&t;&t;/* reinstate route after tmout&t;*/
DECL|macro|RTF_DYNAMIC
mdefine_line|#define&t;RTF_DYNAMIC&t;0x0010&t;&t;/* created dyn. (by redirect)&t;*/
DECL|macro|RTF_MODIFIED
mdefine_line|#define&t;RTF_MODIFIED&t;0x0020&t;&t;/* modified dyn. (by redirect)&t;*/
DECL|macro|RTF_MTU
mdefine_line|#define RTF_MTU&t;&t;0x0040&t;&t;/* specific MTU for this route&t;*/
DECL|macro|RTF_MSS
mdefine_line|#define RTF_MSS&t;&t;RTF_MTU&t;&t;/* Compatibility :-(&t;&t;*/
DECL|macro|RTF_WINDOW
mdefine_line|#define RTF_WINDOW&t;0x0080&t;&t;/* per route window clamping&t;*/
DECL|macro|RTF_IRTT
mdefine_line|#define RTF_IRTT&t;0x0100&t;&t;/* Initial round trip time&t;*/
DECL|macro|RTF_REJECT
mdefine_line|#define RTF_REJECT&t;0x0200&t;&t;/* Reject route&t;&t;&t;*/
DECL|macro|RTF_STATIC
mdefine_line|#define&t;RTF_STATIC&t;0x0400&t;&t;/* Manually injected route&t;*/
DECL|macro|RTF_XRESOLVE
mdefine_line|#define&t;RTF_XRESOLVE&t;0x0800&t;&t;/* External resolver&t;&t;*/
DECL|macro|RTF_NOFORWARD
mdefine_line|#define RTF_NOFORWARD   0x1000&t;&t;/* Forwarding inhibited&t;&t;*/
DECL|macro|RTF_THROW
mdefine_line|#define RTF_THROW&t;0x2000&t;&t;/* Go to next class&t;&t;*/
DECL|macro|RTF_NOPMTUDISC
mdefine_line|#define RTF_NOPMTUDISC  0x4000&t;&t;/* Do not send packets with DF&t;*/
multiline_comment|/* Bad idea. IPv6 should not use broken IPv4 interface */
DECL|macro|RTF_ADDRCONF
mdefine_line|#define RTF_ADDRCONF&t;0x0800&t;&t;/* announced on link prefix&t;  */
DECL|macro|RTF_INVALID
mdefine_line|#define RTF_INVALID&t;0x1000
DECL|macro|RTF_DCACHE
mdefine_line|#define RTF_DCACHE&t;0x2000
DECL|macro|RTF_DEFAULT
mdefine_line|#define RTF_DEFAULT&t;0x4000&t;&t;/* Route is a default route&t;  */
DECL|macro|RTF_NEXTHOP
mdefine_line|#define RTF_NEXTHOP&t;0x8000&t;&t;/* Non gateway route with nexthop */
DECL|macro|RTF_MAGIC
mdefine_line|#define RTF_MAGIC&t;0x10000&t;&t;/* Route added/deleted authomatically,&n;&t;&t;&t;&t;&t; * when interface changes its state.&n;&t;&t;&t;&t;&t; */
DECL|macro|RTCF_VALVE
mdefine_line|#define RTCF_VALVE&t;0x00200000
DECL|macro|RTCF_MASQ
mdefine_line|#define RTCF_MASQ&t;0x00400000
DECL|macro|RTCF_NAT
mdefine_line|#define RTCF_NAT&t;0x00800000
DECL|macro|RTCF_DOREDIRECT
mdefine_line|#define RTCF_DOREDIRECT 0x01000000
DECL|macro|RTCF_LOG
mdefine_line|#define RTCF_LOG&t;0x02000000
DECL|macro|RTCF_DIRECTSRC
mdefine_line|#define RTCF_DIRECTSRC&t;0x04000000
DECL|macro|RTF_LOCAL
mdefine_line|#define RTF_LOCAL&t;0x80000000
DECL|macro|RTF_INTERFACE
mdefine_line|#define RTF_INTERFACE&t;0x40000000
DECL|macro|RTF_MULTICAST
mdefine_line|#define RTF_MULTICAST&t;0x20000000
DECL|macro|RTF_BROADCAST
mdefine_line|#define RTF_BROADCAST&t;0x10000000
DECL|macro|RTF_NAT
mdefine_line|#define RTF_NAT&t;&t;0x08000000
DECL|macro|RTF_ADDRCLASSMASK
mdefine_line|#define RTF_ADDRCLASSMASK&t;0xF8000000
DECL|macro|RT_ADDRCLASS
mdefine_line|#define RT_ADDRCLASS(flags)&t;((__u32)flags&gt;&gt;23)
DECL|macro|RT_TOS
mdefine_line|#define RT_TOS(tos)&t;&t;((tos)&amp;IPTOS_TOS_MASK)
DECL|macro|RT_LOCALADDR
mdefine_line|#define RT_LOCALADDR(flags)&t;((flags&amp;RTF_ADDRCLASSMASK) == (RTF_LOCAL|RTF_INTERFACE))
DECL|macro|RT_CLASS_UNSPEC
mdefine_line|#define RT_CLASS_UNSPEC&t;&t;0
DECL|macro|RT_CLASS_DEFAULT
mdefine_line|#define RT_CLASS_DEFAULT&t;253
DECL|macro|RT_CLASS_MAIN
mdefine_line|#define RT_CLASS_MAIN&t;&t;254
DECL|macro|RT_CLASS_LOCAL
mdefine_line|#define RT_CLASS_LOCAL&t;&t;255
DECL|macro|RT_CLASS_MAX
mdefine_line|#define RT_CLASS_MAX&t;&t;255
macro_line|#ifdef _LINUX_IN_H &t;/* hack to check that in.h included */
multiline_comment|/*&n; *&t;This structure is passed from the kernel to user space by netlink&n; *&t;routing/device announcements&n; */
DECL|struct|in_rtmsg
r_struct
id|in_rtmsg
(brace
DECL|member|rtmsg_prefix
r_struct
id|in_addr
id|rtmsg_prefix
suffix:semicolon
DECL|member|rtmsg_gateway
r_struct
id|in_addr
id|rtmsg_gateway
suffix:semicolon
DECL|member|rtmsg_flags
r_int
id|rtmsg_flags
suffix:semicolon
DECL|member|rtmsg_mtu
r_int
r_int
id|rtmsg_mtu
suffix:semicolon
DECL|member|rtmsg_window
r_int
r_int
id|rtmsg_window
suffix:semicolon
DECL|member|rtmsg_rtt
r_int
r_int
id|rtmsg_rtt
suffix:semicolon
DECL|member|rtmsg_metric
r_int
id|rtmsg_metric
suffix:semicolon
DECL|member|rtmsg_tos
r_int
r_char
id|rtmsg_tos
suffix:semicolon
DECL|member|rtmsg_class
r_int
r_char
id|rtmsg_class
suffix:semicolon
DECL|member|rtmsg_prefixlen
r_int
r_char
id|rtmsg_prefixlen
suffix:semicolon
DECL|member|rtmsg_reserved
r_int
r_char
id|rtmsg_reserved
suffix:semicolon
DECL|member|rtmsg_ifindex
r_int
id|rtmsg_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|in_ifmsg
r_struct
id|in_ifmsg
(brace
DECL|member|ifmsg_lladdr
r_struct
id|sockaddr
id|ifmsg_lladdr
suffix:semicolon
DECL|member|ifmsg_prefix
r_struct
id|in_addr
id|ifmsg_prefix
suffix:semicolon
DECL|member|ifmsg_brd
r_struct
id|in_addr
id|ifmsg_brd
suffix:semicolon
DECL|member|ifmsg_flags
r_int
id|ifmsg_flags
suffix:semicolon
DECL|member|ifmsg_mtu
r_int
r_int
id|ifmsg_mtu
suffix:semicolon
DECL|member|ifmsg_metric
r_int
id|ifmsg_metric
suffix:semicolon
DECL|member|ifmsg_prefixlen
r_int
r_char
id|ifmsg_prefixlen
suffix:semicolon
DECL|member|ifmsg_reserved
r_int
r_char
id|ifmsg_reserved
suffix:semicolon
DECL|member|ifmsg_index
r_int
id|ifmsg_index
suffix:semicolon
DECL|member|ifmsg_name
r_char
id|ifmsg_name
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|rtrule_actions
r_enum
id|rtrule_actions
(brace
DECL|enumerator|RTP_GO
id|RTP_GO
comma
DECL|enumerator|RTP_NAT
id|RTP_NAT
comma
DECL|enumerator|RTP_DROP
id|RTP_DROP
comma
DECL|enumerator|RTP_UNREACHABLE
id|RTP_UNREACHABLE
comma
DECL|enumerator|RTP_PROHIBIT
id|RTP_PROHIBIT
comma
DECL|enumerator|RTP_MASQUERADE
id|RTP_MASQUERADE
)brace
suffix:semicolon
DECL|macro|RTRF_LOG
mdefine_line|#define RTRF_LOG&t;&t;1&t;/* Log route creations&t;&t;*/
DECL|macro|RTRF_VALVE
mdefine_line|#define RTRF_VALVE&t;&t;2&t;/* One-way route&t;&t;*/
DECL|struct|in_rtrulemsg
r_struct
id|in_rtrulemsg
(brace
DECL|member|rtrmsg_src
r_struct
id|in_addr
id|rtrmsg_src
suffix:semicolon
DECL|member|rtrmsg_dst
r_struct
id|in_addr
id|rtrmsg_dst
suffix:semicolon
DECL|member|rtrmsg_srcmap
r_struct
id|in_addr
id|rtrmsg_srcmap
suffix:semicolon
DECL|member|rtrmsg_ifindex
r_int
id|rtrmsg_ifindex
suffix:semicolon
DECL|member|rtrmsg_srclen
r_int
r_char
id|rtrmsg_srclen
suffix:semicolon
DECL|member|rtrmsg_dstlen
r_int
r_char
id|rtrmsg_dstlen
suffix:semicolon
DECL|member|rtrmsg_tos
r_int
r_char
id|rtrmsg_tos
suffix:semicolon
DECL|member|rtrmsg_class
r_int
r_char
id|rtrmsg_class
suffix:semicolon
DECL|member|rtrmsg_flags
r_int
r_char
id|rtrmsg_flags
suffix:semicolon
DECL|member|rtrmsg_action
r_int
r_char
id|rtrmsg_action
suffix:semicolon
DECL|member|rtrmsg_preference
r_int
r_char
id|rtrmsg_preference
suffix:semicolon
DECL|member|rtrmsg_rtmsgs
r_int
r_char
id|rtrmsg_rtmsgs
suffix:semicolon
DECL|member|rtrmsg_rtmsg
r_struct
id|in_rtmsg
id|rtrmsg_rtmsg
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|in_rtctlmsg
r_struct
id|in_rtctlmsg
(brace
DECL|member|rtcmsg_flags
r_int
id|rtcmsg_flags
suffix:semicolon
DECL|member|rtcmsg_delay
r_int
id|rtcmsg_delay
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTCTL_ECHO
mdefine_line|#define RTCTL_ECHO&t;1&t;/* Echo route changes */
DECL|macro|RTCTL_FLUSH
mdefine_line|#define RTCTL_FLUSH&t;2&t;/* Send flush updates */
DECL|macro|RTCTL_ACK
mdefine_line|#define RTCTL_ACK&t;4&t;/* Send acks&t;      */
DECL|macro|RTCTL_DELAY
mdefine_line|#define RTCTL_DELAY&t;8&t;/* Set netlink delay  */
DECL|macro|RTCTL_OWNER
mdefine_line|#define RTCTL_OWNER&t;0x10&t;/* Set netlink reader */
macro_line|#endif
DECL|macro|RTMSG_ACK
mdefine_line|#define RTMSG_ACK&t;&t;NLMSG_ACK
DECL|macro|RTMSG_OVERRUN
mdefine_line|#define RTMSG_OVERRUN&t;&t;NLMSG_OVERRUN
DECL|macro|RTMSG_NEWDEVICE
mdefine_line|#define RTMSG_NEWDEVICE&t;&t;0x11
DECL|macro|RTMSG_DELDEVICE
mdefine_line|#define RTMSG_DELDEVICE&t;&t;0x12
DECL|macro|RTMSG_NEWROUTE
mdefine_line|#define RTMSG_NEWROUTE&t;&t;0x21
DECL|macro|RTMSG_DELROUTE
mdefine_line|#define RTMSG_DELROUTE&t;&t;0x22
DECL|macro|RTMSG_NEWRULE
mdefine_line|#define RTMSG_NEWRULE&t;&t;0x31
DECL|macro|RTMSG_DELRULE
mdefine_line|#define RTMSG_DELRULE&t;&t;0x32
DECL|macro|RTMSG_CONTROL
mdefine_line|#define RTMSG_CONTROL&t;&t;0x40
DECL|macro|RTMSG_AR_FAILED
mdefine_line|#define RTMSG_AR_FAILED&t;&t;0x51&t;/* Address Resolution failed&t;*/
macro_line|#endif&t;/* _LINUX_ROUTE_H */
eof
