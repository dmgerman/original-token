multiline_comment|/*&n; *&t;Linux NET3:&t;Internet Gateway Management Protocol  [IGMP]&n; *&n; *&t;Authors:&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&t;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Fixes:&n; *&t;&n; *&t;&t;Alan Cox&t;:&t;Added lots of __inline__ to optimise&n; *&t;&t;&t;&t;&t;the memory usage of all the tiny little&n; *&t;&t;&t;&t;&t;functions.&n; *&t;&t;Alan Cox&t;:&t;Dumped the header building experiment.&n; *&t;&t;Alan Cox&t;:&t;Minor tweaks ready for multicast routing&n; *&t;&t;&t;&t;&t;and extended IGMP protocol.&n; *&t;&t;Alan Cox&t;:&t;Removed a load of inline directives. Gcc 2.5.8&n; *&t;&t;&t;&t;&t;writes utterly bogus code otherwise (sigh)&n; *&t;&t;&t;&t;&t;fixed IGMP loopback to behave in the manner&n; *&t;&t;&t;&t;&t;desired by mrouted, fixed the fact it has been&n; *&t;&t;&t;&t;&t;broken since 1.3.6 and cleaned up a few minor&n; *&t;&t;&t;&t;&t;points.&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#ifdef CONFIG_IP_MULTICAST
multiline_comment|/*&n; *&t;Timer management&n; */
DECL|function|igmp_stop_timer
r_static
r_void
id|igmp_stop_timer
c_func
(paren
r_struct
id|ip_mc_list
op_star
id|im
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|im-&gt;timer
)paren
suffix:semicolon
id|im-&gt;tm_running
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|random
r_extern
id|__inline__
r_int
id|random
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|seed
op_assign
l_int|152L
suffix:semicolon
id|seed
op_assign
id|seed
op_star
l_int|69069L
op_plus
l_int|1
suffix:semicolon
r_return
id|seed
op_xor
id|jiffies
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Inlined as its only called once.&n; */
DECL|function|igmp_start_timer
r_static
r_void
id|igmp_start_timer
c_func
(paren
r_struct
id|ip_mc_list
op_star
id|im
)paren
(brace
r_int
id|tv
suffix:semicolon
r_if
c_cond
(paren
id|im-&gt;tm_running
)paren
(brace
r_return
suffix:semicolon
)brace
id|tv
op_assign
id|random
c_func
(paren
)paren
op_mod
(paren
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Pick a number any number 8) */
id|im-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|tv
suffix:semicolon
id|im-&gt;tm_running
op_assign
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|im-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send an IGMP report.&n; */
DECL|macro|MAX_IGMP_SIZE
mdefine_line|#define MAX_IGMP_SIZE (sizeof(struct igmphdr)+sizeof(struct iphdr)+64)
DECL|function|igmp_send_report
r_static
r_void
id|igmp_send_report
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|address
comma
r_int
id|type
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|MAX_IGMP_SIZE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_struct
id|igmphdr
op_star
id|ih
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
suffix:semicolon
)brace
id|tmp
op_assign
id|ip_build_header
c_func
(paren
id|skb
comma
id|INADDR_ANY
comma
id|address
comma
op_amp
id|dev
comma
id|IPPROTO_IGMP
comma
l_int|NULL
comma
l_int|28
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ih
op_assign
(paren
r_struct
id|igmphdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|igmphdr
)paren
)paren
suffix:semicolon
id|ih-&gt;type
op_assign
id|IGMP_HOST_MEMBERSHIP_REPORT
suffix:semicolon
id|ih-&gt;code
op_assign
l_int|0
suffix:semicolon
id|ih-&gt;csum
op_assign
l_int|0
suffix:semicolon
id|ih-&gt;group
op_assign
id|address
suffix:semicolon
id|ih-&gt;csum
op_assign
id|ip_compute_csum
c_func
(paren
(paren
r_void
op_star
)paren
id|ih
comma
r_sizeof
(paren
r_struct
id|igmphdr
)paren
)paren
suffix:semicolon
multiline_comment|/* Checksum fill */
id|ip_queue_xmit
c_func
(paren
l_int|NULL
comma
id|dev
comma
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|igmp_timer_expire
r_static
r_void
id|igmp_timer_expire
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|im
op_assign
(paren
r_struct
id|ip_mc_list
op_star
)paren
id|data
suffix:semicolon
id|igmp_stop_timer
c_func
(paren
id|im
)paren
suffix:semicolon
id|igmp_send_report
c_func
(paren
id|im-&gt;interface
comma
id|im-&gt;multiaddr
comma
id|IGMP_HOST_MEMBERSHIP_REPORT
)paren
suffix:semicolon
)brace
DECL|function|igmp_init_timer
r_static
r_void
id|igmp_init_timer
c_func
(paren
r_struct
id|ip_mc_list
op_star
id|im
)paren
(brace
id|im-&gt;tm_running
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|im-&gt;timer
)paren
suffix:semicolon
id|im-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|im
suffix:semicolon
id|im-&gt;timer.function
op_assign
op_amp
id|igmp_timer_expire
suffix:semicolon
)brace
DECL|function|igmp_heard_report
r_static
r_void
id|igmp_heard_report
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|im
suffix:semicolon
r_for
c_loop
(paren
id|im
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|im
op_ne
l_int|NULL
suffix:semicolon
id|im
op_assign
id|im-&gt;next
)paren
r_if
c_cond
(paren
id|im-&gt;multiaddr
op_eq
id|address
)paren
(brace
id|igmp_stop_timer
c_func
(paren
id|im
)paren
suffix:semicolon
)brace
)brace
DECL|function|igmp_heard_query
r_static
r_void
id|igmp_heard_query
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|im
suffix:semicolon
r_for
c_loop
(paren
id|im
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|im
op_ne
l_int|NULL
suffix:semicolon
id|im
op_assign
id|im-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|im-&gt;tm_running
op_logical_and
id|im-&gt;multiaddr
op_ne
id|IGMP_ALL_HOSTS
)paren
(brace
id|igmp_start_timer
c_func
(paren
id|im
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;Map a multicast IP onto multicast MAC for type ethernet.&n; */
DECL|function|ip_mc_map
r_extern
id|__inline__
r_void
id|ip_mc_map
c_func
(paren
r_int
r_int
id|addr
comma
r_char
op_star
id|buf
)paren
(brace
id|addr
op_assign
id|ntohl
c_func
(paren
id|addr
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x01
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x5e
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
id|addr
op_amp
l_int|0xFF
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|addr
op_amp
l_int|0xFF
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|addr
op_amp
l_int|0x7F
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Add a filter to a device&n; */
DECL|function|ip_mc_filter_add
r_void
id|ip_mc_filter_add
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_char
id|buf
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Only do ethernet now */
id|ip_mc_map
c_func
(paren
id|addr
comma
id|buf
)paren
suffix:semicolon
id|dev_mc_add
c_func
(paren
id|dev
comma
id|buf
comma
id|ETH_ALEN
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a filter from a device&n; */
DECL|function|ip_mc_filter_del
r_void
id|ip_mc_filter_del
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_char
id|buf
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_ne
id|ARPHRD_ETHER
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Only do ethernet now */
id|ip_mc_map
c_func
(paren
id|addr
comma
id|buf
)paren
suffix:semicolon
id|dev_mc_delete
c_func
(paren
id|dev
comma
id|buf
comma
id|ETH_ALEN
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|igmp_group_dropped
r_extern
id|__inline__
r_void
id|igmp_group_dropped
c_func
(paren
r_struct
id|ip_mc_list
op_star
id|im
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|im-&gt;timer
)paren
suffix:semicolon
id|igmp_send_report
c_func
(paren
id|im-&gt;interface
comma
id|im-&gt;multiaddr
comma
id|IGMP_HOST_LEAVE_MESSAGE
)paren
suffix:semicolon
id|ip_mc_filter_del
c_func
(paren
id|im-&gt;interface
comma
id|im-&gt;multiaddr
)paren
suffix:semicolon
)brace
DECL|function|igmp_group_added
r_extern
id|__inline__
r_void
id|igmp_group_added
c_func
(paren
r_struct
id|ip_mc_list
op_star
id|im
)paren
(brace
id|igmp_init_timer
c_func
(paren
id|im
)paren
suffix:semicolon
id|ip_mc_filter_add
c_func
(paren
id|im-&gt;interface
comma
id|im-&gt;multiaddr
)paren
suffix:semicolon
id|igmp_send_report
c_func
(paren
id|im-&gt;interface
comma
id|im-&gt;multiaddr
comma
id|IGMP_HOST_MEMBERSHIP_REPORT
)paren
suffix:semicolon
)brace
DECL|function|igmp_rcv
r_int
id|igmp_rcv
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
id|options
op_star
id|opt
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
id|redo
comma
r_struct
id|inet_protocol
op_star
id|protocol
)paren
(brace
multiline_comment|/* This basically follows the spec line by line -- see RFC1112 */
r_struct
id|igmphdr
op_star
id|ih
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Mrouted needs to able to query local interfaces. So&n;&t; *&t;report for the device this was sent at. (Which can&n;&t; *&t;be the loopback this time)&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_LOOPBACK
)paren
(brace
id|dev
op_assign
id|ip_dev_find
c_func
(paren
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|dev
op_assign
op_amp
id|loopback_dev
suffix:semicolon
)brace
)brace
id|ih
op_assign
(paren
r_struct
id|igmphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
template_param
l_int|1
op_logical_or
id|ip_compute_csum
c_func
(paren
(paren
r_void
op_star
)paren
id|skb-&gt;h.raw
comma
r_sizeof
(paren
r_struct
id|igmphdr
)paren
)paren
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
r_if
c_cond
(paren
id|ih-&gt;type
op_eq
id|IGMP_HOST_MEMBERSHIP_QUERY
op_logical_and
id|daddr
op_eq
id|IGMP_ALL_HOSTS
)paren
(brace
id|igmp_heard_query
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ih-&gt;type
op_eq
id|IGMP_HOST_MEMBERSHIP_REPORT
op_logical_and
id|daddr
op_eq
id|ih-&gt;group
)paren
(brace
id|igmp_heard_report
c_func
(paren
id|dev
comma
id|ih-&gt;group
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; *&t;Multicast list managers&n; */
multiline_comment|/*&n; *&t;A socket has joined a multicast group on device dev.&n; */
DECL|function|ip_mc_inc_group
r_static
r_void
id|ip_mc_inc_group
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|i
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|i-&gt;multiaddr
op_eq
id|addr
)paren
(brace
id|i-&gt;users
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|i
op_assign
(paren
r_struct
id|ip_mc_list
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|i
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
r_return
suffix:semicolon
)brace
id|i-&gt;users
op_assign
l_int|1
suffix:semicolon
id|i-&gt;interface
op_assign
id|dev
suffix:semicolon
id|i-&gt;multiaddr
op_assign
id|addr
suffix:semicolon
id|i-&gt;next
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|igmp_group_added
c_func
(paren
id|i
)paren
suffix:semicolon
id|dev-&gt;ip_mc_list
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A socket has left a multicast group on device dev&n; */
DECL|function|ip_mc_dec_group
r_static
r_void
id|ip_mc_dec_group
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|ip_mc_list
op_star
op_star
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_amp
(paren
id|dev-&gt;ip_mc_list
)paren
suffix:semicolon
(paren
op_star
id|i
)paren
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
op_amp
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|multiaddr
op_eq
id|addr
)paren
(brace
r_if
c_cond
(paren
op_decrement
(paren
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|users
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_else
(brace
r_struct
id|ip_mc_list
op_star
id|tmp
op_assign
op_star
id|i
suffix:semicolon
id|igmp_group_dropped
c_func
(paren
id|tmp
)paren
suffix:semicolon
op_star
id|i
op_assign
(paren
op_star
id|i
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|kfree_s
c_func
(paren
id|tmp
comma
r_sizeof
(paren
op_star
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; *&t;Device going down: Clean up.&n; */
DECL|function|ip_mc_drop_device
r_void
id|ip_mc_drop_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|i
suffix:semicolon
r_struct
id|ip_mc_list
op_star
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|i
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
id|j
)paren
(brace
id|j
op_assign
id|i-&gt;next
suffix:semicolon
id|kfree_s
c_func
(paren
id|i
comma
r_sizeof
(paren
op_star
id|i
)paren
)paren
suffix:semicolon
)brace
id|dev-&gt;ip_mc_list
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Device going up. Make sure it is in all hosts&n; */
DECL|function|ip_mc_allhost
r_void
id|ip_mc_allhost
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ip_mc_list
op_star
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|i
op_ne
l_int|NULL
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
r_if
c_cond
(paren
id|i-&gt;multiaddr
op_eq
id|IGMP_ALL_HOSTS
)paren
(brace
r_return
suffix:semicolon
)brace
id|i
op_assign
(paren
r_struct
id|ip_mc_list
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|i
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
r_return
suffix:semicolon
)brace
id|i-&gt;users
op_assign
l_int|1
suffix:semicolon
id|i-&gt;interface
op_assign
id|dev
suffix:semicolon
id|i-&gt;multiaddr
op_assign
id|IGMP_ALL_HOSTS
suffix:semicolon
id|i-&gt;tm_running
op_assign
l_int|0
suffix:semicolon
id|i-&gt;next
op_assign
id|dev-&gt;ip_mc_list
suffix:semicolon
id|dev-&gt;ip_mc_list
op_assign
id|i
suffix:semicolon
id|ip_mc_filter_add
c_func
(paren
id|i-&gt;interface
comma
id|i-&gt;multiaddr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Join a socket to a group&n; */
DECL|function|ip_mc_join_group
r_int
id|ip_mc_join_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|unused
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MULTICAST
c_func
(paren
id|addr
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
)paren
(brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|sk-&gt;ip_mc_list
op_assign
(paren
r_struct
id|ip_mc_socklist
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sk-&gt;ip_mc_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sk-&gt;ip_mc_list
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
op_star
id|sk-&gt;ip_mc_list
)paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IP_MAX_MEMBERSHIPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list-&gt;multiaddr
(braket
id|i
)braket
op_eq
id|addr
op_logical_and
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
op_eq
id|dev
)paren
(brace
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
id|unused
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|unused
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|sk-&gt;ip_mc_list-&gt;multiaddr
(braket
id|unused
)braket
op_assign
id|addr
suffix:semicolon
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|unused
)braket
op_assign
id|dev
suffix:semicolon
id|ip_mc_inc_group
c_func
(paren
id|dev
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Ask a socket to leave a group.&n; */
DECL|function|ip_mc_leave_group
r_int
id|ip_mc_leave_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MULTICAST
c_func
(paren
id|addr
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
)paren
(brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IP_MAX_MEMBERSHIPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list-&gt;multiaddr
(braket
id|i
)braket
op_eq
id|addr
op_logical_and
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
op_eq
id|dev
)paren
(brace
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ip_mc_dec_group
c_func
(paren
id|dev
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A socket is closing.&n; */
DECL|function|ip_mc_drop_socket
r_void
id|ip_mc_drop_socket
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IP_MAX_MEMBERSHIPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
)paren
(brace
id|ip_mc_dec_group
c_func
(paren
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
comma
id|sk-&gt;ip_mc_list-&gt;multiaddr
(braket
id|i
)braket
)paren
suffix:semicolon
id|sk-&gt;ip_mc_list-&gt;multidev
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|kfree_s
c_func
(paren
id|sk-&gt;ip_mc_list
comma
r_sizeof
(paren
op_star
id|sk-&gt;ip_mc_list
)paren
)paren
suffix:semicolon
id|sk-&gt;ip_mc_list
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
