multiline_comment|/*&n; *&t;common UDP/RAW code&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;$Id: datagram.c,v 1.11 1997/05/03 00:58:25 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
DECL|function|datagram_recv_ctl
r_int
id|datagram_recv_ctl
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
r_struct
id|sk_buff
op_star
id|skb
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
r_if
c_cond
(paren
id|np-&gt;rxinfo
)paren
(brace
r_struct
id|in6_pktinfo
id|src_info
suffix:semicolon
id|src_info.ipi6_ifindex
op_assign
id|skb-&gt;dev-&gt;ifindex
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|src_info.ipi6_addr
comma
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_RXINFO
comma
r_sizeof
(paren
id|src_info
)paren
comma
op_amp
id|src_info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;rxhlim
)paren
(brace
r_int
id|hlim
op_assign
id|skb-&gt;nh.ipv6h-&gt;hop_limit
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_HOPLIMIT
comma
r_sizeof
(paren
id|hlim
)paren
comma
op_amp
id|hlim
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;srcrt
)paren
(brace
r_int
id|hdrlen
op_assign
r_sizeof
(paren
r_struct
id|rt0_hdr
)paren
op_plus
(paren
id|opt-&gt;srcrt-&gt;hdrlen
op_lshift
l_int|3
)paren
suffix:semicolon
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_IPV6
comma
id|IPV6_RXSRCRT
comma
id|hdrlen
comma
id|opt-&gt;srcrt
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|datagram_send_ctl
r_int
id|datagram_send_ctl
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|device
op_star
op_star
id|src_dev
comma
r_struct
id|in6_addr
op_star
op_star
id|src_addr
comma
r_struct
id|ipv6_options
op_star
id|opt
comma
r_int
op_star
id|hlimit
)paren
(brace
r_struct
id|in6_pktinfo
op_star
id|src_info
suffix:semicolon
r_struct
id|cmsghdr
op_star
id|cmsg
suffix:semicolon
r_struct
id|ipv6_rt_hdr
op_star
id|rthdr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cmsg
op_assign
id|CMSG_FIRSTHDR
c_func
(paren
id|msg
)paren
suffix:semicolon
id|cmsg
suffix:semicolon
id|cmsg
op_assign
id|CMSG_NXTHDR
c_func
(paren
id|msg
comma
id|cmsg
)paren
)paren
(brace
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_level
op_ne
id|SOL_IPV6
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cmsg_level %d&bslash;n&quot;
comma
id|cmsg-&gt;cmsg_level
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmsg-&gt;cmsg_type
)paren
(brace
r_case
id|IPV6_TXINFO
suffix:colon
r_if
c_cond
(paren
id|cmsg-&gt;cmsg_len
OL
(paren
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|in6_pktinfo
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|src_info
op_assign
(paren
r_struct
id|in6_pktinfo
op_star
)paren
id|cmsg-&gt;cmsg_data
suffix:semicolon
r_if
c_cond
(paren
id|src_info-&gt;ipi6_ifindex
)paren
(brace
r_int
id|index
op_assign
id|src_info-&gt;ipi6_ifindex
suffix:semicolon
op_star
id|src_dev
op_assign
id|dev_get_by_index
c_func
(paren
id|index
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ipv6_addr_any
c_func
(paren
op_amp
id|src_info-&gt;ipi6_addr
)paren
)paren
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
id|src_info-&gt;ipi6_addr
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
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
op_star
id|src_addr
op_assign
op_amp
id|src_info-&gt;ipi6_addr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPV6_RXSRCRT
suffix:colon
id|len
op_assign
id|cmsg-&gt;cmsg_len
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
suffix:semicolon
multiline_comment|/* validate option length */
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
r_struct
id|ipv6_rt_hdr
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|rthdr
op_assign
(paren
r_struct
id|ipv6_rt_hdr
op_star
)paren
id|cmsg-&gt;cmsg_data
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;TYPE 0&n;&t;&t;&t; */
r_if
c_cond
(paren
id|rthdr-&gt;type
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|rthdr-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
OL
id|len
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
multiline_comment|/* segments left must also match */
r_if
c_cond
(paren
(paren
id|rthdr-&gt;hdrlen
op_rshift
l_int|1
)paren
op_ne
id|rthdr-&gt;segments_left
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
id|opt-&gt;opt_nflen
op_add_assign
(paren
(paren
id|rthdr-&gt;hdrlen
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|opt-&gt;srcrt
op_assign
id|rthdr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPV6_HOPLIMIT
suffix:colon
id|len
op_assign
id|cmsg-&gt;cmsg_len
suffix:semicolon
id|len
op_sub_assign
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_f
suffix:semicolon
)brace
op_star
id|hlimit
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|cmsg-&gt;cmsg_data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;invalid cmsg type: %d&bslash;n&quot;
comma
id|cmsg-&gt;cmsg_type
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
id|exit_f
suffix:colon
r_return
id|err
suffix:semicolon
)brace
eof
