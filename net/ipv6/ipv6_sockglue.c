multiline_comment|/*&n; *&t;IPv6 BSD socket options interface&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Based on linux/net/ipv4/ip_sockglue.c&n; *&n; *&t;$Id: ipv6_sockglue.c,v 1.15 1997/10/29 20:27:54 kuznet Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&t;FIXME: Make the setsockopt code POSIX compliant: That is&n; *&n; *&t;o&t;Return -EINVAL for setsockopt of short lengths&n; *&t;o&t;Truncate getsockopt returns&n; *&t;o&t;Return an optlen of the truncated length if need be&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|ipv6_statistics
r_struct
id|ipv6_mib
id|ipv6_statistics
op_assign
initialization_block
suffix:semicolon
DECL|variable|ipv6_packet_type
r_struct
id|packet_type
id|ipv6_packet_type
op_assign
(brace
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
comma
l_int|NULL
comma
multiline_comment|/* All devices */
id|ipv6_rcv
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;addrconf module should be notifyed of a device going up&n; */
DECL|variable|ipv6_dev_notf
r_static
r_struct
id|notifier_block
id|ipv6_dev_notf
op_assign
(brace
id|addrconf_notify
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|function|ipv6_setsockopt
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
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6
suffix:semicolon
r_int
id|val
comma
id|err
suffix:semicolon
r_int
id|retv
op_assign
op_minus
id|ENOPROTOOPT
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ne
id|SOL_IPV6
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optval
op_eq
l_int|NULL
)paren
(brace
id|val
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|optval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|IPV6_ADDRFORM
suffix:colon
r_if
c_cond
(paren
id|val
op_eq
id|PF_INET
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;protocol
op_ne
id|IPPROTO_UDP
op_logical_and
id|sk-&gt;protocol
op_ne
id|IPPROTO_TCP
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
id|retv
op_assign
id|ENOTCONN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|np-&gt;daddr
)paren
op_amp
id|IPV6_ADDR_MAPPED
)paren
)paren
(brace
id|retv
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;protocol
op_eq
id|IPPROTO_TCP
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
(paren
id|sk-&gt;tp_pinfo.af_tcp
)paren
suffix:semicolon
id|sk-&gt;prot
op_assign
op_amp
id|tcp_prot
suffix:semicolon
id|tp-&gt;af_specific
op_assign
op_amp
id|ipv4_specific
suffix:semicolon
id|sk-&gt;socket-&gt;ops
op_assign
op_amp
id|inet_stream_ops
suffix:semicolon
id|sk-&gt;family
op_assign
id|AF_INET
suffix:semicolon
)brace
r_else
(brace
id|sk-&gt;prot
op_assign
op_amp
id|udp_prot
suffix:semicolon
id|sk-&gt;socket-&gt;ops
op_assign
op_amp
id|inet_dgram_ops
suffix:semicolon
)brace
id|retv
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|retv
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPV6_PKTINFO
suffix:colon
id|np-&gt;rxinfo
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPLIMIT
suffix:colon
id|np-&gt;rxhlim
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_UNICAST_HOPS
suffix:colon
r_if
c_cond
(paren
id|val
OG
l_int|255
)paren
id|retv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|np-&gt;hop_limit
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_HOPS
suffix:colon
r_if
c_cond
(paren
id|val
OG
l_int|255
)paren
id|retv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|np-&gt;mcast_hops
op_assign
id|val
suffix:semicolon
id|retv
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_LOOP
suffix:colon
id|np-&gt;mc_loop
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_MULTICAST_IF
suffix:colon
(brace
r_struct
id|in6_addr
id|addr
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|addr
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
op_amp
id|addr
)paren
)paren
(brace
id|np-&gt;oif
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_struct
id|inet6_ifaddr
op_star
id|ifp
suffix:semicolon
id|ifp
op_assign
id|ipv6_chk_addr
c_func
(paren
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifp
op_eq
l_int|NULL
)paren
(brace
id|retv
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|np-&gt;oif
op_assign
id|ifp-&gt;idev-&gt;dev
suffix:semicolon
)brace
id|retv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|IPV6_ADD_MEMBERSHIP
suffix:colon
r_case
id|IPV6_DROP_MEMBERSHIP
suffix:colon
(brace
r_struct
id|ipv6_mreq
id|mreq
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|mreq
comma
id|optval
comma
r_sizeof
(paren
r_struct
id|ipv6_mreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mreq.ipv6mr_ifindex
op_eq
l_int|0
)paren
(brace
macro_line|#if 0
r_struct
id|in6_addr
id|mcast
suffix:semicolon
r_struct
id|dest_entry
op_star
id|dc
suffix:semicolon
id|ipv6_addr_set
c_func
(paren
op_amp
id|mcast
comma
id|__constant_htonl
c_func
(paren
l_int|0xff000000
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|dc
op_assign
id|ipv6_dst_route
c_func
(paren
op_amp
id|mcast
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dc
)paren
(brace
id|dev
op_assign
id|dc-&gt;rt.rt_dev
suffix:semicolon
id|ipv6_dst_unlock
c_func
(paren
id|dc
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|mreq.ipv6mr_ifindex
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|optname
op_eq
id|IPV6_ADD_MEMBERSHIP
)paren
id|retv
op_assign
id|ipv6_sock_mc_join
c_func
(paren
id|sk
comma
id|dev
comma
op_amp
id|mreq.ipv6mr_multiaddr
)paren
suffix:semicolon
r_else
id|retv
op_assign
id|ipv6_sock_mc_drop
c_func
(paren
id|sk
comma
id|dev
comma
op_amp
id|mreq.ipv6mr_multiaddr
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
id|out
suffix:colon
r_return
id|retv
suffix:semicolon
)brace
DECL|function|ipv6_getsockopt
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
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
multiline_comment|/*&n; *&t;sysctl registration functions defined in sysctl_net_ipv6.c&n; */
r_extern
r_void
id|ipv6_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|ipv6_init
c_func
(paren
r_void
)paren
)paren
(brace
id|dev_add_pack
c_func
(paren
op_amp
id|ipv6_packet_type
)paren
suffix:semicolon
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
id|ipv6_sysctl_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|register_netdevice_notifier
c_func
(paren
op_amp
id|ipv6_dev_notf
)paren
suffix:semicolon
id|ip6_route_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|ipv6_cleanup
r_void
id|ipv6_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|ipv6_dev_notf
)paren
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|ipv6_packet_type
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|ipv6_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ip6_route_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ndisc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|addrconf_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
