multiline_comment|/*&n; *&t;Ethertap: A network device for bouncing packets via user space&n; *&n; *&t;This is a very simple ethernet driver. It bounces ethernet frames&n; *&t;to user space on /dev/tap0-&gt;/dev/tap15 and expects ethernet frames&n; *&t;to be written back to it. By default it does not ARP. If you turn ARP&n; *&t;on it will attempt to ARP the user space and reply to ARPS from the&n; *&t;user space.&n; *&n; *&t;As this is an ethernet device you can use it for appletalk, IPX etc&n; *&t;even for building bridging tunnels.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
multiline_comment|/*&n; *&t;Index to functions.&n; */
r_int
id|ethertap_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ethertap_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ethertap_start_xmit
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
)paren
suffix:semicolon
r_static
r_int
id|ethertap_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|ethertap_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ethertap_rx
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETHERTAP_MC
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|ethertap_debug
r_static
r_int
id|ethertap_debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|tap_map
r_static
r_struct
id|device
op_star
id|tap_map
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Returns the tap device for a given netlink */
multiline_comment|/*&n; *&t;Board-specific info in dev-&gt;priv.&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|nl
r_struct
id|sock
op_star
id|nl
suffix:semicolon
macro_line|#ifdef CONFIG_ETHERTAP_MC
DECL|member|groups
id|__u32
id|groups
suffix:semicolon
macro_line|#endif
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;To call this a probe is a bit misleading, however for real&n; *&t;hardware it would have to check what was present.&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|ethertap_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
l_string|&quot;&bslash;xFE&bslash;xFD&bslash;x00&bslash;x00&bslash;x00&bslash;x00&quot;
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_amp
l_int|0xf
)paren
id|ethertap_debug
op_assign
id|dev-&gt;mem_start
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Initialize the device structure.&n;&t; */
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|net_local
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The tap specific entries in the device structure.&n;&t; */
id|dev-&gt;open
op_assign
id|ethertap_open
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|ethertap_start_xmit
suffix:semicolon
id|dev-&gt;stop
op_assign
id|ethertap_close
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|ethertap_get_stats
suffix:semicolon
macro_line|#ifdef CONFIG_ETHERTAP_MC
id|dev-&gt;set_multicast_list
op_assign
id|set_multicast_list
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Setup the generic properties&n;&t; */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|16
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_NOARP
suffix:semicolon
id|tap_map
(braket
id|dev-&gt;base_addr
)braket
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Open/initialize the board.&n; */
DECL|function|ethertap_open
r_static
r_int
id|ethertap_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|ethertap_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Doing ethertap_open()...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lp-&gt;nl
op_assign
id|netlink_kernel_create
c_func
(paren
id|dev-&gt;base_addr
comma
id|ethertap_rx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;nl
op_eq
l_int|NULL
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ETHERTAP_MC
DECL|function|ethertap_mc_hash
r_static
r_int
id|ethertap_mc_hash
c_func
(paren
id|__u8
op_star
id|dest
)paren
(brace
r_int
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|0
)braket
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|1
)braket
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|2
)braket
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|3
)braket
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|4
)braket
suffix:semicolon
id|idx
op_xor_assign
id|dest
(braket
l_int|5
)braket
suffix:semicolon
r_return
l_int|1U
op_lshift
(paren
id|idx
op_amp
l_int|0x1F
)paren
suffix:semicolon
)brace
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|groups
op_assign
op_complement
l_int|0
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
(paren
id|IFF_NOARP
op_or
id|IFF_PROMISC
op_or
id|IFF_ALLMULTI
)paren
)paren
)paren
(brace
r_struct
id|dev_mc_list
op_star
id|dmi
suffix:semicolon
id|groups
op_assign
id|ethertap_mc_hash
c_func
(paren
id|dev-&gt;broadcast
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dmi
op_assign
id|dev-&gt;mc_list
suffix:semicolon
id|dmi
suffix:semicolon
id|dmi
op_assign
id|dmi-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dmi-&gt;dmi_addrlen
op_ne
l_int|6
)paren
r_continue
suffix:semicolon
id|groups
op_or_assign
id|ethertap_mc_hash
c_func
(paren
id|dmi-&gt;dmi_addr
)paren
suffix:semicolon
)brace
)brace
id|lp-&gt;groups
op_assign
id|groups
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;nl
)paren
id|lp-&gt;nl-&gt;protinfo.af_netlink.groups
op_assign
id|groups
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;We transmit by throwing the packet at netlink. We have to clone&n; *&t;it for 2.0 so that we dev_kfree_skb() the locked original.&n; */
DECL|function|ethertap_start_xmit
r_static
r_int
id|ethertap_start_xmit
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
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
macro_line|#ifdef CONFIG_ETHERTAP_MC
r_struct
id|ethhdr
op_star
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s : bug --- xmit with head&lt;2&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Make the same thing, which loopback does. */
r_if
c_cond
(paren
id|skb_shared
c_func
(paren
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb
suffix:semicolon
id|skb
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* Clone the buffer */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb2
)paren
suffix:semicolon
)brace
multiline_comment|/* ... but do not orphan it here, netlink does it in any case. */
id|lp-&gt;stats.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
macro_line|#ifndef CONFIG_ETHERTAP_MC
id|netlink_broadcast
c_func
(paren
id|lp-&gt;nl
comma
id|skb
comma
l_int|0
comma
op_complement
l_int|0
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_NOARP
)paren
(brace
id|netlink_broadcast
c_func
(paren
id|lp-&gt;nl
comma
id|skb
comma
l_int|0
comma
op_complement
l_int|0
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|eth-&gt;h_dest
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/* Unicast packet */
id|__u32
id|pid
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|pid
comma
id|eth-&gt;h_dest
op_plus
l_int|2
comma
l_int|4
)paren
suffix:semicolon
id|netlink_unicast
c_func
(paren
id|lp-&gt;nl
comma
id|skb
comma
id|ntohl
c_func
(paren
id|pid
)paren
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
)brace
r_else
id|netlink_broadcast
c_func
(paren
id|lp-&gt;nl
comma
id|skb
comma
l_int|0
comma
id|ethertap_mc_hash
c_func
(paren
id|eth-&gt;h_dest
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethertap_rx_skb
r_static
id|__inline__
r_int
id|ethertap_rx_skb
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
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
macro_line|#ifdef CONFIG_ETHERTAP_MC
r_struct
id|ethhdr
op_star
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
(paren
id|skb-&gt;data
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#endif
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|16
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s : rx len = %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|NETLINK_CREDS
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|uid
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s : user %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|NETLINK_CREDS
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|uid
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ETHERTAP_MC
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
(paren
id|IFF_NOARP
op_or
id|IFF_PROMISC
)paren
)paren
)paren
(brace
r_int
id|drop
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|eth-&gt;h_dest
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ethertap_mc_hash
c_func
(paren
id|eth-&gt;h_dest
)paren
op_amp
id|lp-&gt;groups
)paren
)paren
id|drop
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|eth-&gt;h_dest
comma
id|dev-&gt;dev_addr
comma
l_int|6
)paren
op_ne
l_int|0
)paren
id|drop
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|drop
)paren
(brace
r_if
c_cond
(paren
id|ethertap_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s : not for us&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|skb_shared
c_func
(paren
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb
suffix:semicolon
id|skb
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* Clone the buffer */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb2
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb2
)paren
suffix:semicolon
)brace
r_else
id|skb_orphan
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|memset
c_func
(paren
id|skb-&gt;cb
comma
l_int|0
comma
r_sizeof
(paren
id|skb-&gt;cb
)paren
)paren
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|lp-&gt;stats.rx_bytes
op_add_assign
id|len
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The typical workload of the driver:&n; *&t;Handle the ether interface interrupts.&n; *&n; *&t;(In this case handle the packets posted from user space..)&n; */
DECL|function|ethertap_rx
r_static
r_void
id|ethertap_rx
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|tap_map
(braket
id|sk-&gt;protocol
)braket
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ethertap: bad unit!&bslash;n&quot;
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ethertap_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;%s: ethertap_rx()&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
op_ne
l_int|NULL
)paren
id|ethertap_rx_skb
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|ethertap_close
r_static
r_int
id|ethertap_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|lp-&gt;nl
suffix:semicolon
r_if
c_cond
(paren
id|ethertap_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Shutting down.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
(brace
id|lp-&gt;nl
op_assign
l_int|NULL
suffix:semicolon
id|sock_release
c_func
(paren
id|sk-&gt;socket
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ethertap_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|ethertap_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|unit
r_static
r_int
id|unit
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|unit
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|devicename
r_static
r_char
id|devicename
(braket
l_int|9
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|dev_ethertap
r_static
r_struct
id|device
id|dev_ethertap
op_assign
(brace
id|devicename
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|ethertap_probe
)brace
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|dev_ethertap.base_addr
op_assign
id|unit
op_plus
id|NETLINK_TAPBASE
suffix:semicolon
id|sprintf
c_func
(paren
id|devicename
comma
l_string|&quot;tap%d&quot;
comma
id|unit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_get
c_func
(paren
id|devicename
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s already loaded.&bslash;n&quot;
comma
id|devicename
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_ethertap
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|tap_map
(braket
id|dev_ethertap.base_addr
)braket
op_assign
l_int|NULL
suffix:semicolon
id|unregister_netdev
c_func
(paren
op_amp
id|dev_ethertap
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Free up the private structure.&n;&t; */
id|kfree
c_func
(paren
id|dev_ethertap.priv
)paren
suffix:semicolon
id|dev_ethertap.priv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* gets re-allocated by ethertap_probe */
)brace
macro_line|#endif /* MODULE */
eof
