macro_line|#ifndef _LINUX_INETDEVICE_H
DECL|macro|_LINUX_INETDEVICE_H
mdefine_line|#define _LINUX_INETDEVICE_H
multiline_comment|/* IPv4 specific flags. They are initialized from global sysctl variables,&n;   when IPv4 is initialized.&n; */
DECL|macro|IFF_IP_FORWARD
mdefine_line|#define IFF_IP_FORWARD&t;&t;1
DECL|macro|IFF_IP_PROXYARP
mdefine_line|#define IFF_IP_PROXYARP&t;&t;2
DECL|macro|IFF_IP_RXREDIRECTS
mdefine_line|#define IFF_IP_RXREDIRECTS&t;4
DECL|macro|IFF_IP_TXREDIRECTS
mdefine_line|#define IFF_IP_TXREDIRECTS&t;8
DECL|macro|IFF_IP_SHAREDMEDIA
mdefine_line|#define IFF_IP_SHAREDMEDIA&t;0x10
DECL|macro|IFF_IP_MFORWARD
mdefine_line|#define IFF_IP_MFORWARD&t;&t;0x20
DECL|macro|IFF_IP_RPFILTER
mdefine_line|#define IFF_IP_RPFILTER&t;&t;0x40
macro_line|#ifdef __KERNEL__
DECL|struct|in_device
r_struct
id|in_device
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|ifa_list
r_struct
id|in_ifaddr
op_star
id|ifa_list
suffix:semicolon
multiline_comment|/* IP ifaddr chain&t;&t;*/
DECL|member|mc_list
r_struct
id|ip_mc_list
op_star
id|mc_list
suffix:semicolon
multiline_comment|/* IP multicast filter chain    */
DECL|member|mr_v1_seen
r_int
r_int
id|mr_v1_seen
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|arp_parms
r_struct
id|neigh_parms
op_star
id|arp_parms
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IN_DEV_RPFILTER
mdefine_line|#define IN_DEV_RPFILTER(in_dev)&t;(ipv4_config.rfc1812_filter &amp;&amp; ((in_dev)-&gt;flags&amp;IFF_IP_RPFILTER))
DECL|macro|IN_DEV_MFORWARD
mdefine_line|#define IN_DEV_MFORWARD(in_dev)&t;(ipv4_config.multicast_route &amp;&amp; ((in_dev)-&gt;flags&amp;IFF_IP_MFORWARD))
DECL|macro|IN_DEV_PROXY_ARP
mdefine_line|#define IN_DEV_PROXY_ARP(in_dev)&t;(ipv4_config.proxy_arp || (in_dev)-&gt;flags&amp;IFF_IP_PROXYARP)
DECL|macro|IN_DEV_FORWARD
mdefine_line|#define IN_DEV_FORWARD(in_dev)&t;&t;(IS_ROUTER || ((in_dev)-&gt;flags&amp;IFF_IP_FORWARD))
DECL|macro|IN_DEV_SHARED_MEDIA
mdefine_line|#define IN_DEV_SHARED_MEDIA(in_dev)&t;(ipv4_config.rfc1620_redirects || (in_dev)-&gt;flags&amp;IFF_IP_SHAREDMEDIA)
DECL|macro|IN_DEV_RX_REDIRECTS
mdefine_line|#define IN_DEV_RX_REDIRECTS(in_dev)&t;(ipv4_config.accept_redirects || (in_dev)-&gt;flags&amp;IFF_IP_RXREDIRECTS)
DECL|macro|IN_DEV_TX_REDIRECTS
mdefine_line|#define IN_DEV_TX_REDIRECTS(in_dev)&t;(/*ipv4_config.send_redirects ||*/ (in_dev)-&gt;flags&amp;IFF_IP_TXREDIRECTS)
DECL|struct|in_ifaddr
r_struct
id|in_ifaddr
(brace
DECL|member|ifa_next
r_struct
id|in_ifaddr
op_star
id|ifa_next
suffix:semicolon
DECL|member|ifa_dev
r_struct
id|in_device
op_star
id|ifa_dev
suffix:semicolon
DECL|member|ifa_local
id|u32
id|ifa_local
suffix:semicolon
DECL|member|ifa_address
id|u32
id|ifa_address
suffix:semicolon
DECL|member|ifa_mask
id|u32
id|ifa_mask
suffix:semicolon
DECL|member|ifa_broadcast
id|u32
id|ifa_broadcast
suffix:semicolon
DECL|member|ifa_anycast
id|u32
id|ifa_anycast
suffix:semicolon
DECL|member|ifa_scope
r_int
r_char
id|ifa_scope
suffix:semicolon
DECL|member|ifa_flags
r_int
r_char
id|ifa_flags
suffix:semicolon
DECL|member|ifa_prefixlen
r_int
r_char
id|ifa_prefixlen
suffix:semicolon
DECL|member|ifa_label
r_char
id|ifa_label
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_inetaddr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_int
id|unregister_inetaddr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|ip_dev_find
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|in_ifaddr
op_star
id|inet_addr_onlink
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|a
comma
id|u32
id|b
)paren
suffix:semicolon
r_extern
r_int
id|devinet_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devinet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|in_device
op_star
id|inetdev_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|in_device
op_star
id|inetdev_by_index
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
id|u32
id|inet_select_addr
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|dst
comma
r_int
id|scope
)paren
suffix:semicolon
r_extern
r_struct
id|in_ifaddr
op_star
id|inet_ifa_byprefix
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|prefix
comma
id|u32
id|mask
)paren
suffix:semicolon
r_extern
r_int
id|inet_add_bootp_addr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|inet_del_bootp_addr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|inet_ifa_match
r_extern
id|__inline__
r_int
id|inet_ifa_match
c_func
(paren
id|u32
id|addr
comma
r_struct
id|in_ifaddr
op_star
id|ifa
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|addr
op_xor
id|ifa-&gt;ifa_address
)paren
op_amp
id|ifa-&gt;ifa_mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check if a mask is acceptable.&n; */
DECL|function|bad_mask
r_extern
id|__inline__
r_int
id|bad_mask
c_func
(paren
id|u32
id|mask
comma
id|u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_amp
(paren
id|mask
op_assign
op_complement
id|mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|mask
op_assign
id|ntohl
c_func
(paren
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
(paren
id|mask
op_plus
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|for_primary_ifa
mdefine_line|#define for_primary_ifa(in_dev)&t;{ struct in_ifaddr *ifa; &bslash;&n;  for (ifa = (in_dev)-&gt;ifa_list; ifa &amp;&amp; !(ifa-&gt;ifa_flags&amp;IFA_F_SECONDARY); ifa = ifa-&gt;ifa_next)
DECL|macro|for_ifa
mdefine_line|#define for_ifa(in_dev)&t;{ struct in_ifaddr *ifa; &bslash;&n;  for (ifa = (in_dev)-&gt;ifa_list; ifa; ifa = ifa-&gt;ifa_next)
DECL|macro|endfor_ifa
mdefine_line|#define endfor_ifa(in_dev) }
macro_line|#endif /* __KERNEL__ */
DECL|function|inet_make_mask
r_extern
id|__inline__
id|__u32
id|inet_make_mask
c_func
(paren
r_int
id|logmask
)paren
(brace
r_if
c_cond
(paren
id|logmask
)paren
r_return
id|htonl
c_func
(paren
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
l_int|32
op_minus
id|logmask
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inet_mask_len
r_extern
id|__inline__
r_int
id|inet_mask_len
c_func
(paren
id|__u32
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_assign
id|ntohl
c_func
(paren
id|mask
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|32
op_minus
id|ffz
c_func
(paren
op_complement
id|mask
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_INETDEVICE_H */
eof