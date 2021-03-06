multiline_comment|/*&n; *&t;ipddp.c: IP to Appletalk-IP Encapsulation driver for Linux&n; *&t;&t; Appletalk-IP to IP Decapsulation driver for Linux&n; *&n; *&t;Authors:&n; *      - DDP-IP Encap by: Bradford W. Johnson &lt;johns393@maroon.tc.umn.edu&gt;&n; *&t;- DDP-IP Decap by: Jay Schulist &lt;jschlst@turbolinux.com&gt;&n; *&n; *&t;Derived from:&n; *&t;- Almost all code already existed in net/appletalk/ddp.c I just&n; *&t;  moved/reorginized it into a driver file. Original IP-over-DDP code&n; *&t;  was done by Bradford W. Johnson &lt;johns393@maroon.tc.umn.edu&gt;&n; *      - skeleton.c: A network driver outline for linux.&n; *        Written 1993-94 by Donald Becker.&n; *&t;- dummy.c: A dummy net driver. By Nick Holloway.&n; *&t;- MacGate: A user space Daemon for Appletalk-IP Decap for&n; *&t;  Linux by Jay Schulist &lt;jschlst@turbolinux.com&gt;&n; *&n; *      Copyright 1993 United States Government as represented by the&n; *      Director, National Security Agency.&n; *&n; *      This software may be used and distributed according to the terms&n; *      of the GNU Public License, incorporated herein by reference.&n; */
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;ipddp.c:v0.01 8/28/97 Bradford W. Johnson &lt;johns393@maroon.tc.umn.edu&gt;&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/atalk.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ipddp.h&quot;&t;&t;/* Our stuff */
DECL|variable|ipddp_route_list
r_static
r_struct
id|ipddp_route
op_star
id|ipddp_route_list
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_IPDDP_ENCAP
DECL|variable|ipddp_mode
r_static
r_int
id|ipddp_mode
op_assign
id|IPDDP_ENCAP
suffix:semicolon
macro_line|#else
DECL|variable|ipddp_mode
r_static
r_int
id|ipddp_mode
op_assign
id|IPDDP_DECAP
suffix:semicolon
macro_line|#endif
multiline_comment|/* Use 0 for production, 1 for verification, 2 for debug, 3 for verbose debug */
macro_line|#ifndef IPDDP_DEBUG
DECL|macro|IPDDP_DEBUG
mdefine_line|#define IPDDP_DEBUG 1
macro_line|#endif
DECL|variable|ipddp_debug
r_static
r_int
r_int
id|ipddp_debug
op_assign
id|IPDDP_DEBUG
suffix:semicolon
multiline_comment|/* Index to functions, as function prototypes. */
r_static
r_int
id|ipddp_xmit
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
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|ipddp_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ipddp_create
c_func
(paren
r_struct
id|ipddp_route
op_star
id|new_rt
)paren
suffix:semicolon
r_static
r_int
id|ipddp_delete
c_func
(paren
r_struct
id|ipddp_route
op_star
id|rt
)paren
suffix:semicolon
r_static
r_struct
id|ipddp_route
op_star
id|ipddp_find_route
c_func
(paren
r_struct
id|ipddp_route
op_star
id|rt
)paren
suffix:semicolon
r_static
r_int
id|ipddp_ioctl
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
id|ifr
comma
r_int
id|cmd
)paren
suffix:semicolon
DECL|function|ipddp_init
r_static
r_int
id|__init
id|ipddp_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_static
r_int
id|version_printed
op_assign
l_int|0
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipddp_debug
op_logical_and
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
multiline_comment|/* Let the user now what mode we are in */
r_if
c_cond
(paren
id|ipddp_mode
op_eq
id|IPDDP_ENCAP
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Appletalk-IP Encap. mode by Bradford W. Johnson &lt;johns393@maroon.tc.umn.edu&gt;&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipddp_mode
op_eq
id|IPDDP_DECAP
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Appletalk-IP Decap. mode by Jay Schulist &lt;jschlst@turbolinux.com&gt;&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* Fill in the device structure with ethernet-generic values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Initalize the device structure. */
id|dev-&gt;hard_start_xmit
op_assign
id|ipddp_xmit
suffix:semicolon
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;priv
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
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|ipddp_get_stats
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|ipddp_ioctl
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_IPDDP
suffix:semicolon
multiline_comment|/* IP over DDP tunnel */
id|dev-&gt;mtu
op_assign
l_int|585
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_NOARP
suffix:semicolon
multiline_comment|/*&n;         *      The worst case header we will need is currently a&n;         *      ethernet header (14 bytes) and a ddp header (sizeof ddpehdr+1)&n;         *      We send over SNAP so that takes another 8 bytes.&n;         */
id|dev-&gt;hard_header_len
op_assign
l_int|14
op_plus
l_int|8
op_plus
r_sizeof
(paren
r_struct
id|ddpehdr
)paren
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the current statistics. This may be called with the card open or closed.&n; */
DECL|function|ipddp_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|ipddp_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;priv
suffix:semicolon
)brace
multiline_comment|/*&n; * Transmit LLAP/ELAP frame using aarp_send_ddp.&n; */
DECL|function|ipddp_xmit
r_static
r_int
id|ipddp_xmit
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
id|u32
id|paddr
op_assign
(paren
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
)paren
op_member_access_from_pointer
id|rt_gateway
suffix:semicolon
r_struct
id|ddpehdr
op_star
id|ddp
suffix:semicolon
r_struct
id|ipddp_route
op_star
id|rt
suffix:semicolon
r_struct
id|at_addr
op_star
id|our_addr
suffix:semicolon
multiline_comment|/*&n;         * Find appropriate route to use, based only on IP number.&n;         */
r_for
c_loop
(paren
id|rt
op_assign
id|ipddp_route_list
suffix:semicolon
id|rt
op_ne
l_int|NULL
suffix:semicolon
id|rt
op_assign
id|rt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|rt-&gt;ip
op_eq
id|paddr
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rt
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|our_addr
op_assign
id|atalk_find_dev_addr
c_func
(paren
id|rt-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipddp_mode
op_eq
id|IPDDP_DECAP
)paren
(brace
multiline_comment|/* &n;&t;&t; * Pull off the excess room that should not be there.&n;&t;&t; * This is due to a hard-header problem. This is the&n;&t;&t; * quick fix for now though, till it breaks.&n;&t;&t; */
id|skb_pull
c_func
(paren
id|skb
comma
l_int|35
op_minus
(paren
r_sizeof
(paren
r_struct
id|ddpehdr
)paren
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the Extended DDP header */
id|ddp
op_assign
(paren
r_struct
id|ddpehdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|ddp-&gt;deh_len
op_assign
id|skb-&gt;len
suffix:semicolon
id|ddp-&gt;deh_hops
op_assign
l_int|1
suffix:semicolon
id|ddp-&gt;deh_pad
op_assign
l_int|0
suffix:semicolon
id|ddp-&gt;deh_sum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;         * For Localtalk we need aarp_send_ddp to strip the&n;         * long DDP header and place a shot DDP header on it.&n;         */
r_if
c_cond
(paren
id|rt-&gt;dev-&gt;type
op_eq
id|ARPHRD_LOCALTLK
)paren
(brace
id|ddp-&gt;deh_dnet
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME more hops?? */
id|ddp-&gt;deh_snet
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|ddp-&gt;deh_dnet
op_assign
id|rt-&gt;at.s_net
suffix:semicolon
multiline_comment|/* FIXME more hops?? */
id|ddp-&gt;deh_snet
op_assign
id|our_addr-&gt;s_net
suffix:semicolon
)brace
id|ddp-&gt;deh_dnode
op_assign
id|rt-&gt;at.s_node
suffix:semicolon
id|ddp-&gt;deh_snode
op_assign
id|our_addr-&gt;s_node
suffix:semicolon
id|ddp-&gt;deh_dport
op_assign
l_int|72
suffix:semicolon
id|ddp-&gt;deh_sport
op_assign
l_int|72
suffix:semicolon
op_star
(paren
(paren
id|__u8
op_star
)paren
(paren
id|ddp
op_plus
l_int|1
)paren
)paren
op_assign
l_int|22
suffix:semicolon
multiline_comment|/* ddp type = IP */
op_star
(paren
(paren
id|__u16
op_star
)paren
id|ddp
)paren
op_assign
id|ntohs
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|ddp
)paren
)paren
suffix:semicolon
multiline_comment|/* fix up length field */
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_ATALK
)paren
suffix:semicolon
multiline_comment|/* Protocol has changed */
(paren
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|tx_packets
op_increment
suffix:semicolon
(paren
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|aarp_send_ddp
c_func
(paren
id|rt-&gt;dev
comma
id|skb
comma
op_amp
id|rt-&gt;at
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a routing entry. We first verify that the&n; * record does not already exist. If it does we return -EEXIST&n; */
DECL|function|ipddp_create
r_static
r_int
id|ipddp_create
c_func
(paren
r_struct
id|ipddp_route
op_star
id|new_rt
)paren
(brace
r_struct
id|ipddp_route
op_star
id|rt
op_assign
(paren
r_struct
id|ipddp_route
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rt
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|ipddp_route
op_star
id|test
suffix:semicolon
r_if
c_cond
(paren
id|rt
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rt-&gt;ip
op_assign
id|new_rt-&gt;ip
suffix:semicolon
id|rt-&gt;at
op_assign
id|new_rt-&gt;at
suffix:semicolon
id|rt-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|rt-&gt;dev
op_assign
id|atrtr_get_dev
c_func
(paren
op_amp
id|rt-&gt;at
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;dev
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENETUNREACH
)paren
suffix:semicolon
)brace
id|test
op_assign
id|ipddp_find_route
c_func
(paren
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
op_ne
l_int|NULL
)paren
(brace
r_return
(paren
op_minus
id|EEXIST
)paren
suffix:semicolon
)brace
id|rt-&gt;next
op_assign
id|ipddp_route_list
suffix:semicolon
id|ipddp_route_list
op_assign
id|rt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a route, we only delete a FULL match.&n; * If route does not exist we return -ENOENT.&n; */
DECL|function|ipddp_delete
r_static
r_int
id|ipddp_delete
c_func
(paren
r_struct
id|ipddp_route
op_star
id|rt
)paren
(brace
r_struct
id|ipddp_route
op_star
op_star
id|r
op_assign
op_amp
id|ipddp_route_list
suffix:semicolon
r_struct
id|ipddp_route
op_star
id|tmp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
op_star
id|r
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;ip
op_eq
id|rt-&gt;ip
op_logical_and
id|tmp-&gt;at.s_net
op_eq
id|rt-&gt;at.s_net
op_logical_and
id|tmp-&gt;at.s_node
op_eq
id|rt-&gt;at.s_node
)paren
(brace
op_star
id|r
op_assign
id|tmp-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|r
op_assign
op_amp
id|tmp-&gt;next
suffix:semicolon
)brace
r_return
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a routing entry, we only return a FULL match&n; */
DECL|function|ipddp_find_route
r_static
r_struct
id|ipddp_route
op_star
id|ipddp_find_route
c_func
(paren
r_struct
id|ipddp_route
op_star
id|rt
)paren
(brace
r_struct
id|ipddp_route
op_star
id|f
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|ipddp_route_list
suffix:semicolon
id|f
op_ne
l_int|NULL
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;ip
op_eq
id|rt-&gt;ip
op_logical_and
id|f-&gt;at.s_net
op_eq
id|rt-&gt;at.s_net
op_logical_and
id|f-&gt;at.s_node
op_eq
id|rt-&gt;at.s_node
)paren
(brace
r_return
(paren
id|f
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ipddp_ioctl
r_static
r_int
id|ipddp_ioctl
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
id|ifr
comma
r_int
id|cmd
)paren
(brace
r_struct
id|ipddp_route
op_star
id|rt
op_assign
(paren
r_struct
id|ipddp_route
op_star
)paren
id|ifr-&gt;ifr_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCADDIPDDPRT
suffix:colon
r_return
(paren
id|ipddp_create
c_func
(paren
id|rt
)paren
)paren
suffix:semicolon
r_case
id|SIOCFINDIPDDPRT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|rt
comma
id|ipddp_find_route
c_func
(paren
id|rt
)paren
comma
r_sizeof
(paren
r_struct
id|ipddp_route
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|SIOCDELIPDDPRT
suffix:colon
r_return
(paren
id|ipddp_delete
c_func
(paren
id|rt
)paren
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|variable|dev_ipddp
r_static
r_struct
id|net_device
id|dev_ipddp
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ipddp_mode
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|ipddp_init_module
r_static
r_int
id|__init
id|ipddp_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|dev_ipddp.init
op_assign
id|ipddp_init
suffix:semicolon
id|err
op_assign
id|dev_alloc_name
c_func
(paren
op_amp
id|dev_ipddp
comma
l_string|&quot;ipddp%d&quot;
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
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_ipddp
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipddp_cleanup_module
r_static
r_void
id|__exit
id|ipddp_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
op_amp
id|dev_ipddp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev_ipddp.priv
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dev_ipddp
comma
l_int|0
comma
r_sizeof
(paren
id|dev_ipddp
)paren
)paren
suffix:semicolon
id|dev_ipddp.init
op_assign
id|ipddp_init
suffix:semicolon
)brace
DECL|variable|ipddp_init_module
id|module_init
c_func
(paren
id|ipddp_init_module
)paren
suffix:semicolon
DECL|variable|ipddp_cleanup_module
id|module_exit
c_func
(paren
id|ipddp_cleanup_module
)paren
suffix:semicolon
eof
