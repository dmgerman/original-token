multiline_comment|/*&n; *&t;UDP over IPv6&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Based on linux/ipv4/udp.c&n; *&n; *&t;$Id: udp.c,v 1.6 1996/10/16 18:34:16 roque Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ipv6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
DECL|variable|udp_stats_in6
r_struct
id|udp_mib
id|udp_stats_in6
suffix:semicolon
multiline_comment|/*&n; *&n; */
DECL|function|udpv6_connect
r_int
id|udpv6_connect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|usin
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|uaddr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_struct
id|dest_entry
op_star
id|dest
suffix:semicolon
r_struct
id|ipv6_pinfo
op_star
id|np
suffix:semicolon
r_struct
id|inet6_ifaddr
op_star
id|ifa
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
OL
r_sizeof
(paren
op_star
id|usin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|usin-&gt;sin6_family
op_logical_and
id|usin-&gt;sin6_family
op_ne
id|AF_INET6
)paren
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|usin-&gt;sin6_addr
)paren
suffix:semicolon
id|np
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_ANY
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;connect to self&n;&t;&t; */
id|usin-&gt;sin6_addr.s6_addr
(braket
l_int|15
)braket
op_assign
l_int|0x01
suffix:semicolon
)brace
id|daddr
op_assign
op_amp
id|usin-&gt;sin6_addr
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_MAPPED
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|err
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|daddr-&gt;s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
id|err
op_assign
id|udp_connect
c_func
(paren
id|sk
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|sin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;daddr
comma
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;saddr
)paren
)paren
(brace
id|ipv6_addr_set
c_func
(paren
op_amp
id|np-&gt;saddr
comma
l_int|0
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0x0000ffff
)paren
comma
id|sk-&gt;saddr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
)paren
)paren
(brace
id|ipv6_addr_set
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
comma
l_int|0
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0x0000ffff
)paren
comma
id|sk-&gt;rcv_saddr
)paren
suffix:semicolon
)brace
)brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;daddr
comma
id|daddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for a route to destination an obtain the&n;&t; *&t;destination cache for it.&n;&t; */
id|dest
op_assign
id|ipv6_dst_route
c_func
(paren
id|daddr
comma
l_int|NULL
comma
id|sk-&gt;localroute
ques
c_cond
id|RTI_GATEWAY
suffix:colon
l_int|0
)paren
suffix:semicolon
id|np-&gt;dest
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|dest
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENETUNREACH
suffix:semicolon
multiline_comment|/* get the source adddress used in the apropriate device */
id|ifa
op_assign
id|ipv6_get_saddr
c_func
(paren
(paren
r_struct
id|rt6_info
op_star
)paren
id|dest
comma
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;saddr
)paren
)paren
(brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;saddr
comma
op_amp
id|ifa-&gt;addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
)paren
)paren
(brace
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
comma
op_amp
id|ifa-&gt;addr
)paren
suffix:semicolon
id|sk-&gt;rcv_saddr
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
id|sk-&gt;dummy_th.dest
op_assign
id|usin-&gt;sin6_port
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|udpv6_close
r_static
r_void
id|udpv6_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|timeout
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
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;dest
)paren
(brace
id|ipv6_dst_unlock
c_func
(paren
id|np-&gt;dest
)paren
suffix:semicolon
)brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|destroy_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;This should be easy, if there is something there we&n; * &t;return it, otherwise we block.&n; */
DECL|function|udpv6_recvmsg
r_int
id|udpv6_recvmsg
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_int
id|truesize
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check any passed addresses&n;&t; */
r_if
c_cond
(paren
id|addr_len
)paren
op_star
id|addr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;From here the generic datagram does a lot of the work. Come&n;&t; *&t;the finished NET3, it will do _ALL_ the work!&n;&t; */
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|truesize
op_assign
id|skb-&gt;tail
op_minus
id|skb-&gt;h.raw
op_minus
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
id|copied
op_assign
id|min
c_func
(paren
id|len
comma
id|truesize
)paren
suffix:semicolon
multiline_comment|/*&n;  &t; *&t;FIXME : should use udp header size info value &n;  &t; */
id|err
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|sk-&gt;stamp
op_assign
id|skb-&gt;stamp
suffix:semicolon
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|msg-&gt;msg_name
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|sin6
suffix:semicolon
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
id|sin6-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|sin6-&gt;sin6_port
op_assign
id|skb-&gt;h.uh-&gt;source
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|ipv6_addr_set
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
comma
l_int|0
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0xffff
)paren
comma
id|skb-&gt;daddr
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
op_amp
id|sin6-&gt;sin6_addr
comma
op_amp
id|skb-&gt;ipv6_hdr-&gt;saddr
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
id|msg-&gt;msg_control
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|datagram_recv_ctl
c_func
(paren
id|sk
comma
id|msg
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|copied
op_assign
id|err
suffix:semicolon
)brace
)brace
)brace
)brace
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
)brace
DECL|function|udpv6_err
r_void
id|udpv6_err
c_func
(paren
r_int
id|type
comma
r_int
id|code
comma
r_int
r_char
op_star
id|buff
comma
id|__u32
id|info
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
id|inet6_protocol
op_star
id|protocol
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
r_int
id|err
suffix:semicolon
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|buff
suffix:semicolon
id|sk
op_assign
id|inet6_get_sock
c_func
(paren
op_amp
id|udpv6_prot
comma
id|daddr
comma
id|saddr
comma
id|uh-&gt;source
comma
id|uh-&gt;dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;icmp for unkown sock&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|icmpv6_err_convert
c_func
(paren
id|type
comma
id|code
comma
op_amp
id|err
)paren
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;bsdism
op_logical_and
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
r_return
suffix:semicolon
)brace
id|sk-&gt;err
op_assign
id|err
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
id|sk-&gt;err_soft
op_assign
id|err
suffix:semicolon
)brace
DECL|function|udpv6_queue_rcv_skb
r_static
r_inline
r_int
id|udpv6_queue_rcv_skb
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
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|udp_stats_in6.UdpInErrors
op_increment
suffix:semicolon
id|ipv6_statistics.Ip6InDiscards
op_increment
suffix:semicolon
id|ipv6_statistics.Ip6InDelivers
op_decrement
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|udp_stats_in6.UdpInDatagrams
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|udpv6_rcv
r_int
id|udpv6_rcv
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
comma
r_int
id|redo
comma
r_struct
id|inet6_protocol
op_star
id|protocol
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
r_int
id|ulen
suffix:semicolon
multiline_comment|/*&n;&t; *&t;check if the address is ours...&n;&t; *&t;I believe that this is being done in IP layer&n;&t; */
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|skb-&gt;h.uh
suffix:semicolon
id|ipv6_statistics.Ip6InDelivers
op_increment
suffix:semicolon
id|ulen
op_assign
id|ntohs
c_func
(paren
id|uh-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ulen
OG
id|len
op_logical_or
id|len
OL
r_sizeof
(paren
op_star
id|uh
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;UDP: short packet: %d/%d&bslash;n&quot;
comma
id|ulen
comma
id|len
)paren
suffix:semicolon
id|udp_stats_in6.UdpInErrors
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
r_if
c_cond
(paren
id|uh-&gt;check
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;IPv6: udp checksum is 0&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|discard
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|skb-&gt;ip_summed
)paren
(brace
r_case
id|CHECKSUM_NONE
suffix:colon
id|skb-&gt;csum
op_assign
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|uh
comma
id|len
comma
l_int|0
)paren
suffix:semicolon
r_case
id|CHECKSUM_HW
suffix:colon
r_if
c_cond
(paren
id|csum_ipv6_magic
c_func
(paren
id|saddr
comma
id|daddr
comma
id|len
comma
id|IPPROTO_UDP
comma
id|skb-&gt;csum
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;IPv6: udp checksum error&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|discard
suffix:semicolon
)brace
)brace
id|len
op_assign
id|ulen
suffix:semicolon
multiline_comment|/* &n;&t; *&t;Multicast receive code &n;&t; */
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
id|daddr
)paren
op_amp
id|IPV6_ADDR_MULTICAST
)paren
(brace
r_struct
id|sock
op_star
id|sk2
suffix:semicolon
r_int
id|lport
suffix:semicolon
id|lport
op_assign
id|ntohs
c_func
(paren
id|uh-&gt;dest
)paren
suffix:semicolon
id|sk
op_assign
id|udpv6_prot.sock_array
(braket
id|lport
op_amp
(paren
id|SOCK_ARRAY_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|sk
op_assign
id|inet6_get_sock_mcast
c_func
(paren
id|sk
comma
id|lport
comma
id|uh-&gt;source
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
id|inet6_get_sock_mcast
c_func
(paren
id|sk2-&gt;next
comma
id|lport
comma
id|uh-&gt;source
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
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|buff
)paren
OL
l_int|0
)paren
(brace
id|buff-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|buff
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk
op_logical_or
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
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
multiline_comment|/* Unicast */
multiline_comment|/* &n;&t; * check socket cache ... must talk to Alan about his plans&n;&t; * for sock caches... i&squot;ll skip this for now.&n;&t; */
id|sk
op_assign
id|inet6_get_sock
c_func
(paren
op_amp
id|udpv6_prot
comma
id|daddr
comma
id|saddr
comma
id|uh-&gt;dest
comma
id|uh-&gt;source
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
id|udp_stats_in6.UdpNoPorts
op_increment
suffix:semicolon
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_DEST_UNREACH
comma
id|ICMPV6_PORT_UNREACH
comma
l_int|0
comma
id|dev
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* deliver */
r_if
c_cond
(paren
id|sk-&gt;users
)paren
(brace
id|__skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;back_log
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|udpv6_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|discard
suffix:colon
id|udp_stats_in6.UdpInErrors
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
multiline_comment|/*&n; *&t;Sending&n; */
DECL|struct|udpv6fakehdr
r_struct
id|udpv6fakehdr
(brace
DECL|member|uh
r_struct
id|udphdr
id|uh
suffix:semicolon
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
DECL|member|wcheck
id|__u32
id|wcheck
suffix:semicolon
DECL|member|pl_len
id|__u32
id|pl_len
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;with checksum&n; */
DECL|function|udpv6_getfrag
r_static
r_int
id|udpv6_getfrag
c_func
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
id|buff
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|udpv6fakehdr
op_star
id|udh
op_assign
(paren
r_struct
id|udpv6fakehdr
op_star
)paren
id|data
suffix:semicolon
r_char
op_star
id|dst
suffix:semicolon
r_int
id|final
op_assign
l_int|0
suffix:semicolon
r_int
id|clen
op_assign
id|len
suffix:semicolon
id|dst
op_assign
id|buff
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|offset
op_sub_assign
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
)brace
r_else
(brace
id|dst
op_add_assign
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
id|final
op_assign
l_int|1
suffix:semicolon
id|clen
op_sub_assign
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
)brace
id|udh-&gt;wcheck
op_assign
id|csum_partial_copy_fromiovecend
c_func
(paren
id|dst
comma
id|udh-&gt;iov
comma
id|offset
comma
id|clen
comma
id|udh-&gt;wcheck
)paren
suffix:semicolon
r_if
c_cond
(paren
id|final
)paren
(brace
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
id|udh-&gt;wcheck
op_assign
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|udh
comma
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
id|udh-&gt;wcheck
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udh-&gt;daddr
)paren
(brace
id|daddr
op_assign
id|udh-&gt;daddr
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;use packet destination address&n;&t;&t;&t; *&t;this should improve cache locality&n;&t;&t;&t; */
id|daddr
op_assign
id|addr
op_plus
l_int|1
suffix:semicolon
)brace
id|udh-&gt;uh.check
op_assign
id|csum_ipv6_magic
c_func
(paren
id|addr
comma
id|daddr
comma
id|udh-&gt;pl_len
comma
id|IPPROTO_UDP
comma
id|udh-&gt;wcheck
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udh-&gt;uh.check
op_eq
l_int|0
)paren
id|udh-&gt;uh.check
op_assign
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|buff
comma
id|udh
comma
r_sizeof
(paren
r_struct
id|udphdr
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|udpv6_sendmsg
r_static
r_int
id|udpv6_sendmsg
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|ulen
comma
r_int
id|noblock
comma
r_int
id|flags
)paren
(brace
r_struct
id|ipv6_options
id|opt_space
suffix:semicolon
r_struct
id|udpv6fakehdr
id|udh
suffix:semicolon
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6
suffix:semicolon
r_struct
id|sockaddr_in6
op_star
id|sin6
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|ipv6_options
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|addr_len
op_assign
id|msg-&gt;msg_namelen
suffix:semicolon
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|saddr
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
op_assign
id|ulen
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
id|MSG_DONTROUTE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sin6
)paren
(brace
r_if
c_cond
(paren
id|addr_len
OL
r_sizeof
(paren
op_star
id|sin6
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sin6-&gt;sin6_family
op_logical_and
id|sin6-&gt;sin6_family
op_ne
id|AF_INET6
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sin6-&gt;sin6_port
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|udh.uh.dest
op_assign
id|sin6-&gt;sin6_port
suffix:semicolon
id|daddr
op_assign
op_amp
id|sin6-&gt;sin6_addr
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;dest
op_logical_and
id|ipv6_addr_cmp
c_func
(paren
id|daddr
comma
op_amp
id|np-&gt;daddr
)paren
)paren
(brace
id|ipv6_dst_unlock
c_func
(paren
id|np-&gt;dest
)paren
suffix:semicolon
id|np-&gt;dest
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|udh.uh.dest
op_assign
id|sk-&gt;dummy_th.dest
suffix:semicolon
id|daddr
op_assign
op_amp
id|sk-&gt;net_pinfo.af_inet6.daddr
suffix:semicolon
)brace
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_MAPPED
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|daddr-&gt;s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
r_return
id|udp_sendmsg
c_func
(paren
id|sk
comma
id|msg
comma
id|len
comma
id|noblock
comma
id|flags
)paren
suffix:semicolon
)brace
id|udh.daddr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_control
)paren
(brace
id|opt
op_assign
op_amp
id|opt_space
suffix:semicolon
id|memset
c_func
(paren
id|opt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipv6_options
)paren
)paren
suffix:semicolon
id|err
op_assign
id|datagram_send_ctl
c_func
(paren
id|msg
comma
op_amp
id|dev
comma
op_amp
id|saddr
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;invalid msg_control&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;srcrt
)paren
(brace
id|udh.daddr
op_assign
id|daddr
suffix:semicolon
)brace
)brace
id|udh.uh.source
op_assign
id|sk-&gt;dummy_th.source
suffix:semicolon
id|udh.uh.len
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
id|udh.uh.check
op_assign
l_int|0
suffix:semicolon
id|udh.iov
op_assign
id|msg-&gt;msg_iov
suffix:semicolon
id|udh.wcheck
op_assign
l_int|0
suffix:semicolon
id|udh.pl_len
op_assign
id|len
suffix:semicolon
id|err
op_assign
id|ipv6_build_xmit
c_func
(paren
id|sk
comma
id|udpv6_getfrag
comma
op_amp
id|udh
comma
id|daddr
comma
id|len
comma
id|saddr
comma
id|dev
comma
id|opt
comma
id|IPPROTO_UDP
comma
id|noblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|udp_stats_in6.UdpOutDatagrams
op_increment
suffix:semicolon
r_return
id|ulen
suffix:semicolon
)brace
DECL|variable|udpv6_protocol
r_static
r_struct
id|inet6_protocol
id|udpv6_protocol
op_assign
(brace
id|udpv6_rcv
comma
multiline_comment|/* UDP handler&t;&t;*/
id|udpv6_err
comma
multiline_comment|/* UDP error control&t;*/
l_int|NULL
comma
multiline_comment|/* next&t;&t;&t;*/
id|IPPROTO_UDP
comma
multiline_comment|/* protocol ID&t;&t;*/
l_int|0
comma
multiline_comment|/* copy&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* data&t;&t;&t;*/
l_string|&quot;UDPv6&quot;
multiline_comment|/* name&t;&t;&t;*/
)brace
suffix:semicolon
DECL|variable|udpv6_prot
r_struct
id|proto
id|udpv6_prot
op_assign
(brace
id|udpv6_close
comma
id|udpv6_connect
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|datagram_select
comma
id|udp_ioctl
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|ipv6_setsockopt
comma
id|ipv6_getsockopt
comma
id|udpv6_sendmsg
comma
id|udpv6_recvmsg
comma
l_int|NULL
comma
multiline_comment|/* No special bind function */
id|udpv6_queue_rcv_skb
comma
l_int|128
comma
l_int|0
comma
l_string|&quot;UDP&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|udpv6_init
r_void
id|udpv6_init
c_func
(paren
r_void
)paren
(brace
id|inet6_add_protocol
c_func
(paren
op_amp
id|udpv6_protocol
)paren
suffix:semicolon
)brace
eof
