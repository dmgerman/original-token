multiline_comment|/*&n; *&t;Device handling code&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_device.c,v 1.2 2000/02/24 19:48:06 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|function|br_dev_do_ioctl
r_static
r_int
id|br_dev_do_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|rq
comma
r_int
id|cmd
)paren
(brace
r_int
r_int
id|args
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCDEVPRIVATE
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|rq-&gt;ifr_data
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|args
comma
id|data
comma
l_int|4
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|br_ioctl
c_func
(paren
id|dev-&gt;priv
comma
id|args
(braket
l_int|0
)braket
comma
id|args
(braket
l_int|1
)braket
comma
id|args
(braket
l_int|2
)braket
comma
id|args
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
DECL|function|br_dev_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|br_dev_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
id|br
op_assign
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|br-&gt;statistics
suffix:semicolon
)brace
DECL|function|__br_dev_xmit
r_static
r_int
id|__br_dev_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
r_char
op_star
id|dest
suffix:semicolon
r_struct
id|net_bridge_fdb_entry
op_star
id|dst
suffix:semicolon
id|br
op_assign
id|dev-&gt;priv
suffix:semicolon
id|br-&gt;statistics.tx_packets
op_increment
suffix:semicolon
id|br-&gt;statistics.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|dest
op_assign
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|dest
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
(brace
id|br_flood
c_func
(paren
id|br
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dst
op_assign
id|br_fdb_get
c_func
(paren
id|br
comma
id|dest
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|br_forward
c_func
(paren
id|dst-&gt;dst
comma
id|skb
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|br_flood
c_func
(paren
id|br
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_dev_xmit
r_static
r_int
id|br_dev_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|br
op_assign
id|dev-&gt;priv
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|ret
op_assign
id|__br_dev_xmit
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|br_dev_open
r_static
r_int
id|br_dev_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|br
op_assign
id|dev-&gt;priv
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_enable_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_dev_set_multicast_list
r_static
r_void
id|br_dev_set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|br_dev_stop
r_static
r_int
id|br_dev_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
id|br
op_assign
id|dev-&gt;priv
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_disable_bridge
c_func
(paren
id|br
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_dev_accept_fastpath
r_static
r_int
id|br_dev_accept_fastpath
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|br_dev_setup
r_void
id|br_dev_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|memset
c_func
(paren
id|dev-&gt;dev_addr
comma
l_int|0
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|br_dev_do_ioctl
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|br_dev_get_stats
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|br_dev_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
id|br_dev_open
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|br_dev_set_multicast_list
suffix:semicolon
id|dev-&gt;stop
op_assign
id|br_dev_stop
suffix:semicolon
id|dev-&gt;accept_fastpath
op_assign
id|br_dev_accept_fastpath
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
