macro_line|#ifndef _NDISC_H
DECL|macro|_NDISC_H
mdefine_line|#define _NDISC_H
multiline_comment|/*&n; *&t;Neighbor Cache Entry States (7.3.2.)&n; */
multiline_comment|/*&n; *&t;The lsb is set for states that have a timer associated&n; */
DECL|macro|NUD_NONE
mdefine_line|#define NUD_NONE&t;0x00
DECL|macro|NUD_INCOMPLETE
mdefine_line|#define NUD_INCOMPLETE&t;0x11
DECL|macro|NUD_REACHABLE
mdefine_line|#define NUD_REACHABLE&t;0x20
DECL|macro|NUD_STALE
mdefine_line|#define NUD_STALE&t;0x30
DECL|macro|NUD_DELAY
mdefine_line|#define NUD_DELAY&t;0x41
DECL|macro|NUD_PROBE
mdefine_line|#define NUD_PROBE&t;0x51
DECL|macro|NUD_FAILED
mdefine_line|#define NUD_FAILED&t;0x60&t;/* neighbour discovery failed&t;*/
DECL|macro|NUD_IN_TIMER
mdefine_line|#define NUD_IN_TIMER&t;0x01
DECL|macro|NDISC_QUEUE_LEN
mdefine_line|#define NDISC_QUEUE_LEN&t;3
DECL|macro|NCF_NOARP
mdefine_line|#define NCF_NOARP&t;&t;0x0100&t;/* no ARP needed on this device */
DECL|macro|NCF_SUBNET
mdefine_line|#define NCF_SUBNET&t;&t;0x0200  /* NC entry for subnet&t;&t;*/
DECL|macro|NCF_INVALID
mdefine_line|#define NCF_INVALID&t;&t;0x0400
DECL|macro|NCF_DELAY_EXPIRED
mdefine_line|#define NCF_DELAY_EXPIRED&t;0x0800&t;/* time to move to PROBE&t;*/
DECL|macro|NCF_ROUTER
mdefine_line|#define NCF_ROUTER&t;&t;0x1000&t;/* neighbour is a router&t;*/
DECL|macro|NCF_HHVALID
mdefine_line|#define NCF_HHVALID&t;&t;0x2000&t;/* Hardware header is valid&t;*/
multiline_comment|/*&n; *&t;ICMP codes for neighbour discovery messages&n; */
DECL|macro|NDISC_ROUTER_SOLICITATION
mdefine_line|#define NDISC_ROUTER_SOLICITATION&t;133
DECL|macro|NDISC_ROUTER_ADVERTISEMENT
mdefine_line|#define NDISC_ROUTER_ADVERTISEMENT&t;134
DECL|macro|NDISC_NEIGHBOUR_SOLICITATION
mdefine_line|#define NDISC_NEIGHBOUR_SOLICITATION&t;135
DECL|macro|NDISC_NEIGHBOUR_ADVERTISEMENT
mdefine_line|#define NDISC_NEIGHBOUR_ADVERTISEMENT&t;136
DECL|macro|NDISC_REDIRECT
mdefine_line|#define NDISC_REDIRECT&t;&t;&t;137
multiline_comment|/*&n; *&t;ndisc options&n; */
DECL|macro|ND_OPT_SOURCE_LL_ADDR
mdefine_line|#define ND_OPT_SOURCE_LL_ADDR&t;&t;1
DECL|macro|ND_OPT_TARGET_LL_ADDR
mdefine_line|#define ND_OPT_TARGET_LL_ADDR&t;&t;2
DECL|macro|ND_OPT_PREFIX_INFO
mdefine_line|#define ND_OPT_PREFIX_INFO&t;&t;3
DECL|macro|ND_OPT_REDIRECT_HDR
mdefine_line|#define ND_OPT_REDIRECT_HDR&t;&t;4
DECL|macro|ND_OPT_MTU
mdefine_line|#define ND_OPT_MTU&t;&t;&t;5
DECL|macro|MAX_RTR_SOLICITATION_DELAY
mdefine_line|#define MAX_RTR_SOLICITATION_DELAY&t;HZ
DECL|macro|RECHABLE_TIME
mdefine_line|#define RECHABLE_TIME&t;&t;&t;(30*HZ)
DECL|macro|RETRANS_TIMER
mdefine_line|#define RETRANS_TIMER&t;&t;&t;HZ
DECL|macro|MIN_RANDOM_FACTOR
mdefine_line|#define MIN_RANDOM_FACTOR&t;&t;(1/2)
DECL|macro|MAX_RANDOM_FACTOR
mdefine_line|#define MAX_RANDOM_FACTOR&t;&t;(3/2)
DECL|macro|REACH_RANDOM_INTERVAL
mdefine_line|#define REACH_RANDOM_INTERVAL&t;&t;(60*60*HZ)&t;/* 1 hour */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; *&t;neighbour cache entry&n; *&t;used by neighbour discovery module&n; */
DECL|struct|nd_neigh
r_struct
id|nd_neigh
(brace
DECL|member|neigh
r_struct
id|neighbour
id|neigh
suffix:semicolon
DECL|member|ndn_addr
r_struct
id|in6_addr
id|ndn_addr
suffix:semicolon
multiline_comment|/* next hop addr */
DECL|member|ndn_plen
id|__u8
id|ndn_plen
comma
multiline_comment|/* prefix len&t; */
DECL|member|ndn_type
id|ndn_type
comma
multiline_comment|/* {unicast, multicast} */
DECL|member|ndn_nud_state
id|ndn_nud_state
comma
DECL|member|ndn_probes
id|ndn_probes
suffix:semicolon
DECL|member|ndn_expires
r_int
r_int
id|ndn_expires
suffix:semicolon
multiline_comment|/* timer expires at&t;*/
DECL|macro|ndn_refcnt
mdefine_line|#define ndn_refcnt&t;&t;neigh.refcnt
DECL|macro|ndn_tstamp
mdefine_line|#define ndn_tstamp&t;&t;neigh.lastused
DECL|macro|ndn_dev
mdefine_line|#define ndn_dev&t;&t;&t;neigh.dev
DECL|macro|ndn_flags
mdefine_line|#define ndn_flags&t;&t;neigh.flags
DECL|macro|ndn_ha
mdefine_line|#define ndn_ha&t;&t;&t;neigh.ha
)brace
suffix:semicolon
DECL|struct|nd_msg
r_struct
id|nd_msg
(brace
DECL|member|icmph
r_struct
id|icmp6hdr
id|icmph
suffix:semicolon
DECL|member|target
r_struct
id|in6_addr
id|target
suffix:semicolon
r_struct
(brace
DECL|member|opt_type
id|__u8
id|opt_type
suffix:semicolon
DECL|member|opt_len
id|__u8
id|opt_len
suffix:semicolon
DECL|member|link_addr
id|__u8
id|link_addr
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|opt
)brace
id|opt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ra_msg
r_struct
id|ra_msg
(brace
DECL|member|icmph
r_struct
id|icmp6hdr
id|icmph
suffix:semicolon
DECL|member|reachable_time
id|__u32
id|reachable_time
suffix:semicolon
DECL|member|retrans_timer
id|__u32
id|retrans_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ndisc_statistics
r_struct
id|ndisc_statistics
(brace
DECL|member|allocs
id|__u32
id|allocs
suffix:semicolon
multiline_comment|/* allocated entries&t;&t;*/
DECL|member|free_delayed
id|__u32
id|free_delayed
suffix:semicolon
multiline_comment|/* zombie entries&t;&t;*/
DECL|member|snt_probes_ucast
id|__u32
id|snt_probes_ucast
suffix:semicolon
multiline_comment|/* ns probes sent (ucast)&t;*/
DECL|member|snt_probes_mcast
id|__u32
id|snt_probes_mcast
suffix:semicolon
multiline_comment|/* ns probes sent (mcast)&t;*/
DECL|member|rcv_probes_ucast
id|__u32
id|rcv_probes_ucast
suffix:semicolon
multiline_comment|/* ns probes rcv  (ucast)&t;*/
DECL|member|rcv_probes_mcast
id|__u32
id|rcv_probes_mcast
suffix:semicolon
multiline_comment|/* ns probes rcv  (mcast)&t;*/
DECL|member|rcv_upper_conf
id|__u32
id|rcv_upper_conf
suffix:semicolon
multiline_comment|/* confirmations from upper layers */
DECL|member|res_failed
id|__u32
id|res_failed
suffix:semicolon
multiline_comment|/* address resolution failures&t;*/
)brace
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|ndisc_find_neigh
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_validate
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_init
c_func
(paren
r_struct
id|net_proto_family
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_struct
id|neighbour
op_star
id|ndisc_get_neigh
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ndisc_rcv
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
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_struct
id|ipv6_options
op_star
id|opt
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_event_send
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_send_ns
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|in6_addr
op_star
id|solicit
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_struct
id|in6_addr
op_star
id|saddr
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_send_rs
c_func
(paren
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
)paren
suffix:semicolon
r_extern
r_int
id|ndisc_eth_resolv
c_func
(paren
r_int
r_char
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_forwarding_on
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_forwarding_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ndisc_send_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|in6_addr
op_star
id|target
)paren
suffix:semicolon
r_struct
id|rt6_info
op_star
id|dflt_rt_lookup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nd_rand_seed
suffix:semicolon
r_extern
r_int
r_int
id|ipv6_random
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;IGMP&n; */
r_extern
r_void
id|igmp6_init
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
id|igmp6_event_query
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|icmp6hdr
op_star
id|hdr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|igmp6_event_report
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|icmp6hdr
op_star
id|hdr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
