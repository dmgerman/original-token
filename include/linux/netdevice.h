multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Interfaces handler.&n; *&n; * Version:&t;@(#)dev.h&t;1.0.10&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@cesdis.gsfc.nasa.gov&gt;&n; *&t;&t;Alan Cox, &lt;Alan.Cox@linux.org&gt;&n; *&t;&t;Bjorn Ekwall. &lt;bj0rn@blox.se&gt;&n; *              Pekka Riikonen &lt;priikone@poseidon.pspt.fi&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;Moved to /usr/include/linux for NET3&n; */
macro_line|#ifndef _LINUX_NETDEVICE_H
DECL|macro|_LINUX_NETDEVICE_H
mdefine_line|#define _LINUX_NETDEVICE_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_packet.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NET_PROFILE
macro_line|#include &lt;net/profile.h&gt;
macro_line|#endif
r_struct
id|divert_blk
suffix:semicolon
DECL|macro|NET_XMIT_SUCCESS
mdefine_line|#define NET_XMIT_SUCCESS&t;0
DECL|macro|NET_XMIT_DROP
mdefine_line|#define NET_XMIT_DROP&t;&t;1&t;/* skb dropped&t;&t;&t;*/
DECL|macro|NET_XMIT_CN
mdefine_line|#define NET_XMIT_CN&t;&t;2&t;/* congestion notification&t;*/
DECL|macro|NET_XMIT_POLICED
mdefine_line|#define NET_XMIT_POLICED&t;3&t;/* skb is shot by police&t;*/
DECL|macro|NET_XMIT_BYPASS
mdefine_line|#define NET_XMIT_BYPASS&t;&t;4&t;/* packet does not leave via dequeue;&n;&t;&t;&t;&t;&t;   (TC use only - dev_queue_xmit&n;&t;&t;&t;&t;&t;   returns this as NET_XMIT_SUCCESS) */
multiline_comment|/* Backlog congestion levels */
DECL|macro|NET_RX_SUCCESS
mdefine_line|#define NET_RX_SUCCESS&t;&t;0   /* keep &squot;em coming, baby */
DECL|macro|NET_RX_CN_LOW
mdefine_line|#define NET_RX_CN_LOW&t;&t;1   /* storm alert, just in case */
DECL|macro|NET_RX_CN_MOD
mdefine_line|#define NET_RX_CN_MOD&t;&t;2   /* Storm on its way! */
DECL|macro|NET_RX_CN_HIGH
mdefine_line|#define NET_RX_CN_HIGH&t;&t;5   /* The storm is here */
DECL|macro|NET_RX_DROP
mdefine_line|#define NET_RX_DROP&t;&t;-1  /* packet dropped */
DECL|macro|NET_RX_BAD
mdefine_line|#define NET_RX_BAD&t;&t;-2  /* packet dropped due to kernel error */
DECL|macro|net_xmit_errno
mdefine_line|#define net_xmit_errno(e)&t;((e) != NET_XMIT_CN ? -ENOBUFS : 0)
macro_line|#endif
DECL|macro|MAX_ADDR_LEN
mdefine_line|#define MAX_ADDR_LEN&t;7&t;&t;/* Largest hardware address length */
multiline_comment|/*&n; *&t;Compute the worst case header length according to the protocols&n; *&t;used.&n; */
macro_line|#if !defined(CONFIG_AX25) &amp;&amp; !defined(CONFIG_AX25_MODULE) &amp;&amp; !defined(CONFIG_TR)
DECL|macro|LL_MAX_HEADER
mdefine_line|#define LL_MAX_HEADER&t;32
macro_line|#else
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
DECL|macro|LL_MAX_HEADER
mdefine_line|#define LL_MAX_HEADER&t;96
macro_line|#else
DECL|macro|LL_MAX_HEADER
mdefine_line|#define LL_MAX_HEADER&t;48
macro_line|#endif
macro_line|#endif
macro_line|#if !defined(CONFIG_NET_IPIP) &amp;&amp; &bslash;&n;    !defined(CONFIG_IPV6) &amp;&amp; !defined(CONFIG_IPV6_MODULE)
DECL|macro|MAX_HEADER
mdefine_line|#define MAX_HEADER LL_MAX_HEADER
macro_line|#else
DECL|macro|MAX_HEADER
mdefine_line|#define MAX_HEADER (LL_MAX_HEADER + 48)
macro_line|#endif
multiline_comment|/*&n; *&t;Network device statistics. Akin to the 2.0 ether stats but&n; *&t;with byte counters.&n; */
DECL|struct|net_device_stats
r_struct
id|net_device_stats
(brace
DECL|member|rx_packets
r_int
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received&t;*/
DECL|member|tx_packets
r_int
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted&t;*/
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
multiline_comment|/* total bytes received &t;*/
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
multiline_comment|/* total bytes transmitted&t;*/
DECL|member|rx_errors
r_int
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received&t;&t;*/
DECL|member|tx_errors
r_int
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems&t;*/
DECL|member|rx_dropped
r_int
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers&t;*/
DECL|member|tx_dropped
r_int
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux&t;*/
DECL|member|multicast
r_int
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received&t;*/
DECL|member|collisions
r_int
r_int
id|collisions
suffix:semicolon
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver ring buff overflow&t;*/
DECL|member|rx_crc_errors
r_int
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* recved pkt with crc error&t;*/
DECL|member|rx_frame_errors
r_int
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* recv&squot;d frame alignment error */
DECL|member|rx_fifo_errors
r_int
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* recv&squot;r fifo overrun&t;&t;*/
DECL|member|rx_missed_errors
r_int
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet&t;*/
multiline_comment|/* detailed tx_errors */
DECL|member|tx_aborted_errors
r_int
r_int
id|tx_aborted_errors
suffix:semicolon
DECL|member|tx_carrier_errors
r_int
r_int
id|tx_carrier_errors
suffix:semicolon
DECL|member|tx_fifo_errors
r_int
r_int
id|tx_fifo_errors
suffix:semicolon
DECL|member|tx_heartbeat_errors
r_int
r_int
id|tx_heartbeat_errors
suffix:semicolon
DECL|member|tx_window_errors
r_int
r_int
id|tx_window_errors
suffix:semicolon
multiline_comment|/* for cslip etc */
DECL|member|rx_compressed
r_int
r_int
id|rx_compressed
suffix:semicolon
DECL|member|tx_compressed
r_int
r_int
id|tx_compressed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Media selection options. */
r_enum
(brace
DECL|enumerator|IF_PORT_UNKNOWN
id|IF_PORT_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|IF_PORT_10BASE2
id|IF_PORT_10BASE2
comma
DECL|enumerator|IF_PORT_10BASET
id|IF_PORT_10BASET
comma
DECL|enumerator|IF_PORT_AUI
id|IF_PORT_AUI
comma
DECL|enumerator|IF_PORT_100BASET
id|IF_PORT_100BASET
comma
DECL|enumerator|IF_PORT_100BASETX
id|IF_PORT_100BASETX
comma
DECL|enumerator|IF_PORT_100BASEFX
id|IF_PORT_100BASEFX
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_const
r_char
op_star
id|if_port_text
(braket
)braket
suffix:semicolon
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_struct
id|neighbour
suffix:semicolon
r_struct
id|neigh_parms
suffix:semicolon
r_struct
id|sk_buff
suffix:semicolon
DECL|struct|netif_rx_stats
r_struct
id|netif_rx_stats
(brace
DECL|member|total
r_int
id|total
suffix:semicolon
DECL|member|dropped
r_int
id|dropped
suffix:semicolon
DECL|member|time_squeeze
r_int
id|time_squeeze
suffix:semicolon
DECL|member|throttled
r_int
id|throttled
suffix:semicolon
DECL|member|fastroute_hit
r_int
id|fastroute_hit
suffix:semicolon
DECL|member|fastroute_success
r_int
id|fastroute_success
suffix:semicolon
DECL|member|fastroute_defer
r_int
id|fastroute_defer
suffix:semicolon
DECL|member|fastroute_deferred_out
r_int
id|fastroute_deferred_out
suffix:semicolon
DECL|member|fastroute_latency_reduction
r_int
id|fastroute_latency_reduction
suffix:semicolon
DECL|member|cpu_collision
r_int
id|cpu_collision
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__aligned__
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|netif_rx_stats
id|netdev_rx_stat
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;We tag multicasts with these structures.&n; */
DECL|struct|dev_mc_list
r_struct
id|dev_mc_list
(brace
DECL|member|next
r_struct
id|dev_mc_list
op_star
id|next
suffix:semicolon
DECL|member|dmi_addr
id|__u8
id|dmi_addr
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|dmi_addrlen
r_int
r_char
id|dmi_addrlen
suffix:semicolon
DECL|member|dmi_users
r_int
id|dmi_users
suffix:semicolon
DECL|member|dmi_gusers
r_int
id|dmi_gusers
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hh_cache
r_struct
id|hh_cache
(brace
DECL|member|hh_next
r_struct
id|hh_cache
op_star
id|hh_next
suffix:semicolon
multiline_comment|/* Next entry&t;&t;&t;     */
DECL|member|hh_refcnt
id|atomic_t
id|hh_refcnt
suffix:semicolon
multiline_comment|/* number of users                   */
DECL|member|hh_type
r_int
r_int
id|hh_type
suffix:semicolon
multiline_comment|/* protocol identifier, f.e ETH_P_IP */
DECL|member|hh_len
r_int
id|hh_len
suffix:semicolon
multiline_comment|/* length of header */
DECL|member|hh_output
r_int
(paren
op_star
id|hh_output
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|hh_lock
id|rwlock_t
id|hh_lock
suffix:semicolon
multiline_comment|/* cached hardware header; allow for machine alignment needs.        */
DECL|member|hh_data
r_int
r_int
id|hh_data
(braket
l_int|16
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* These flag bits are private to the generic network queueing&n; * layer, they may not be explicitly referenced by any other&n; * code.&n; */
DECL|enum|netdev_state_t
r_enum
id|netdev_state_t
(brace
DECL|enumerator|__LINK_STATE_XOFF
id|__LINK_STATE_XOFF
op_assign
l_int|0
comma
DECL|enumerator|__LINK_STATE_START
id|__LINK_STATE_START
comma
DECL|enumerator|__LINK_STATE_PRESENT
id|__LINK_STATE_PRESENT
comma
DECL|enumerator|__LINK_STATE_SCHED
id|__LINK_STATE_SCHED
comma
DECL|enumerator|__LINK_STATE_NOCARRIER
id|__LINK_STATE_NOCARRIER
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure holds at boot time configured netdevice settings. They&n; * are then used in the device probing. &n; */
DECL|struct|netdev_boot_setup
r_struct
id|netdev_boot_setup
(brace
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|map
r_struct
id|ifmap
id|map
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NETDEV_BOOT_SETUP_MAX
mdefine_line|#define NETDEV_BOOT_SETUP_MAX 8
multiline_comment|/*&n; *&t;The DEVICE structure.&n; *&t;Actually, this whole structure is a big mistake.  It mixes I/O&n; *&t;data with strictly &quot;high-level&quot; data, and it has to know about&n; *&t;almost every data structure used in the INET module.&n; *&n; *&t;FIXME: cleanup struct net_device such that network protocol info&n; *&t;moves out.&n; */
DECL|struct|net_device
r_struct
id|net_device
(brace
multiline_comment|/*&n;&t; * This is the first field of the &quot;visible&quot; part of this structure&n;&t; * (i.e. as seen by users in the &quot;Space.c&quot; file).  It is the name&n;&t; * the interface.&n;&t; */
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *&t;I/O specific fields&n;&t; *&t;FIXME: Merge these and struct ifmap into one&n;&t; */
DECL|member|rmem_end
r_int
r_int
id|rmem_end
suffix:semicolon
multiline_comment|/* shmem &quot;recv&quot; end&t;*/
DECL|member|rmem_start
r_int
r_int
id|rmem_start
suffix:semicolon
multiline_comment|/* shmem &quot;recv&quot; start&t;*/
DECL|member|mem_end
r_int
r_int
id|mem_end
suffix:semicolon
multiline_comment|/* shared mem end&t;*/
DECL|member|mem_start
r_int
r_int
id|mem_start
suffix:semicolon
multiline_comment|/* shared mem start&t;*/
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
multiline_comment|/* device I/O address&t;*/
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* device IRQ number&t;*/
multiline_comment|/*&n;&t; *&t;Some hardware also needs these fields, but they are not&n;&t; *&t;part of the usual set specified in Space.c.&n;&t; */
DECL|member|if_port
r_int
r_char
id|if_port
suffix:semicolon
multiline_comment|/* Selectable AUI, TP,..*/
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
multiline_comment|/* DMA channel&t;&t;*/
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
multiline_comment|/* The device initialization function. Called only once. */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* ------- Fields preinitialized in Space.c finish here ------- */
DECL|member|next_sched
r_struct
id|net_device
op_star
id|next_sched
suffix:semicolon
multiline_comment|/* Interface index. Unique device identifier&t;*/
DECL|member|ifindex
r_int
id|ifindex
suffix:semicolon
DECL|member|iflink
r_int
id|iflink
suffix:semicolon
DECL|member|get_stats
r_struct
id|net_device_stats
op_star
(paren
op_star
id|get_stats
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|get_wireless_stats
r_struct
id|iw_statistics
op_star
(paren
op_star
id|get_wireless_stats
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This marks the end of the &quot;visible&quot; part of the structure. All&n;&t; * fields hereafter are internal to the system, and may change at&n;&t; * will (read: may be cleaned up at will).&n;&t; */
multiline_comment|/* These may be needed for future network-power-down code. */
DECL|member|trans_start
r_int
r_int
id|trans_start
suffix:semicolon
multiline_comment|/* Time (in jiffies) of last Tx&t;*/
DECL|member|last_rx
r_int
r_int
id|last_rx
suffix:semicolon
multiline_comment|/* Time of last Rx&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* interface flags (a la BSD)&t;*/
DECL|member|gflags
r_int
r_int
id|gflags
suffix:semicolon
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* interface MTU value&t;&t;*/
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* interface hardware type&t;*/
DECL|member|hard_header_len
r_int
r_int
id|hard_header_len
suffix:semicolon
multiline_comment|/* hardware hdr length&t;*/
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* pointer to private data&t;*/
DECL|member|master
r_struct
id|net_device
op_star
id|master
suffix:semicolon
multiline_comment|/* Pointer to master device of a group,&n;&t;&t;&t;&t;&t;  * which this device is member of.&n;&t;&t;&t;&t;&t;  */
multiline_comment|/* Interface address info. */
DECL|member|broadcast
r_int
r_char
id|broadcast
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* hw bcast add&t;*/
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* make dev_addr aligned to 8 bytes */
DECL|member|dev_addr
r_int
r_char
id|dev_addr
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* hw address&t;*/
DECL|member|addr_len
r_int
r_char
id|addr_len
suffix:semicolon
multiline_comment|/* hardware address length&t;*/
DECL|member|mc_list
r_struct
id|dev_mc_list
op_star
id|mc_list
suffix:semicolon
multiline_comment|/* Multicast mac addresses&t;*/
DECL|member|mc_count
r_int
id|mc_count
suffix:semicolon
multiline_comment|/* Number of installed mcasts&t;*/
DECL|member|promiscuity
r_int
id|promiscuity
suffix:semicolon
DECL|member|allmulti
r_int
id|allmulti
suffix:semicolon
DECL|member|watchdog_timeo
r_int
id|watchdog_timeo
suffix:semicolon
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
multiline_comment|/* Protocol specific pointers */
DECL|member|atalk_ptr
r_void
op_star
id|atalk_ptr
suffix:semicolon
multiline_comment|/* AppleTalk link &t;*/
DECL|member|ip_ptr
r_void
op_star
id|ip_ptr
suffix:semicolon
multiline_comment|/* IPv4 specific data&t;*/
DECL|member|dn_ptr
r_void
op_star
id|dn_ptr
suffix:semicolon
multiline_comment|/* DECnet specific data */
DECL|member|ip6_ptr
r_void
op_star
id|ip6_ptr
suffix:semicolon
multiline_comment|/* IPv6 specific data */
DECL|member|ec_ptr
r_void
op_star
id|ec_ptr
suffix:semicolon
multiline_comment|/* Econet specific data&t;*/
DECL|member|qdisc
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
DECL|member|qdisc_sleeping
r_struct
id|Qdisc
op_star
id|qdisc_sleeping
suffix:semicolon
DECL|member|qdisc_list
r_struct
id|Qdisc
op_star
id|qdisc_list
suffix:semicolon
DECL|member|qdisc_ingress
r_struct
id|Qdisc
op_star
id|qdisc_ingress
suffix:semicolon
DECL|member|tx_queue_len
r_int
r_int
id|tx_queue_len
suffix:semicolon
multiline_comment|/* Max frames per queue allowed */
multiline_comment|/* hard_start_xmit synchronizer */
DECL|member|xmit_lock
id|spinlock_t
id|xmit_lock
suffix:semicolon
multiline_comment|/* cpu id of processor entered to hard_start_xmit or -1,&n;&t;   if nobody entered there.&n;&t; */
DECL|member|xmit_lock_owner
r_int
id|xmit_lock_owner
suffix:semicolon
multiline_comment|/* device queue lock */
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
multiline_comment|/* Number of references to this device */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* The flag marking that device is unregistered, but held by an user */
DECL|member|deadbeaf
r_int
id|deadbeaf
suffix:semicolon
multiline_comment|/* New style devices allow asynchronous destruction;&n;&t;   netdevice_unregister for old style devices blocks until&n;&t;   the last user will dereference this device.&n;&t; */
DECL|member|new_style
r_int
id|new_style
suffix:semicolon
multiline_comment|/* Called after device is detached from network. */
DECL|member|uninit
r_void
(paren
op_star
id|uninit
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Called after last user reference disappears. */
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Pointers to interface service routines.&t;*/
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|hard_start_xmit
r_int
(paren
op_star
id|hard_start_xmit
)paren
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
DECL|member|hard_header
r_int
(paren
op_star
id|hard_header
)paren
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
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|rebuild_header
r_int
(paren
op_star
id|rebuild_header
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|macro|HAVE_MULTICAST
mdefine_line|#define HAVE_MULTICAST&t;&t;&t; 
DECL|member|set_multicast_list
r_void
(paren
op_star
id|set_multicast_list
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|HAVE_SET_MAC_ADDR
mdefine_line|#define HAVE_SET_MAC_ADDR  &t;&t; 
DECL|member|set_mac_address
r_int
(paren
op_star
id|set_mac_address
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|HAVE_PRIVATE_IOCTL
mdefine_line|#define HAVE_PRIVATE_IOCTL
DECL|member|do_ioctl
r_int
(paren
op_star
id|do_ioctl
)paren
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
DECL|macro|HAVE_SET_CONFIG
mdefine_line|#define HAVE_SET_CONFIG
DECL|member|set_config
r_int
(paren
op_star
id|set_config
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifmap
op_star
id|map
)paren
suffix:semicolon
DECL|macro|HAVE_HEADER_CACHE
mdefine_line|#define HAVE_HEADER_CACHE
DECL|member|hard_header_cache
r_int
(paren
op_star
id|hard_header_cache
)paren
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|hh_cache
op_star
id|hh
)paren
suffix:semicolon
DECL|member|header_cache_update
r_void
(paren
op_star
id|header_cache_update
)paren
(paren
r_struct
id|hh_cache
op_star
id|hh
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_char
op_star
id|haddr
)paren
suffix:semicolon
DECL|macro|HAVE_CHANGE_MTU
mdefine_line|#define HAVE_CHANGE_MTU
DECL|member|change_mtu
r_int
(paren
op_star
id|change_mtu
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
suffix:semicolon
DECL|macro|HAVE_TX_TIMEOUT
mdefine_line|#define HAVE_TX_TIMEOUT
DECL|member|tx_timeout
r_void
(paren
op_star
id|tx_timeout
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|hard_header_parse
r_int
(paren
op_star
id|hard_header_parse
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|haddr
)paren
suffix:semicolon
DECL|member|neigh_setup
r_int
(paren
op_star
id|neigh_setup
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|neigh_parms
op_star
)paren
suffix:semicolon
DECL|member|accept_fastpath
r_int
(paren
op_star
id|accept_fastpath
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|dst_entry
op_star
)paren
suffix:semicolon
multiline_comment|/* bridge stuff */
DECL|member|br_port
r_struct
id|net_bridge_port
op_star
id|br_port
suffix:semicolon
macro_line|#ifdef CONFIG_NET_FASTROUTE
DECL|macro|NETDEV_FASTROUTE_HMASK
mdefine_line|#define NETDEV_FASTROUTE_HMASK 0xF
multiline_comment|/* Semi-private data. Keep it at the end of device struct. */
DECL|member|fastpath_lock
id|rwlock_t
id|fastpath_lock
suffix:semicolon
DECL|member|fastpath
r_struct
id|dst_entry
op_star
id|fastpath
(braket
id|NETDEV_FASTROUTE_HMASK
op_plus
l_int|1
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_DIVERT
multiline_comment|/* this will get initialized at each interface type init routine */
DECL|member|divert
r_struct
id|divert_blk
op_star
id|divert
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
)brace
suffix:semicolon
DECL|struct|packet_type
r_struct
id|packet_type
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* This is really htons(ether_type).&t;*/
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* NULL is wildcarded here&t;&t;*/
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* Private to the packet type&t;&t;*/
DECL|member|next
r_struct
id|packet_type
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
r_extern
r_struct
id|net_device
id|loopback_dev
suffix:semicolon
multiline_comment|/* The loopback */
r_extern
r_struct
id|net_device
op_star
id|dev_base
suffix:semicolon
multiline_comment|/* All devices */
r_extern
id|rwlock_t
id|dev_base_lock
suffix:semicolon
multiline_comment|/* Device list lock */
r_extern
r_int
id|netdev_boot_setup_add
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|ifmap
op_star
id|map
)paren
suffix:semicolon
r_extern
r_int
id|netdev_boot_setup_check
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|dev_getbyhwaddr
c_func
(paren
r_int
r_int
id|type
comma
r_char
op_star
id|hwaddr
)paren
suffix:semicolon
r_extern
r_void
id|dev_add_pack
c_func
(paren
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_extern
r_void
id|dev_remove_pack
c_func
(paren
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_extern
r_int
id|dev_get
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|dev_get_by_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|__dev_get_by_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|dev_alloc
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_extern
r_int
id|dev_alloc_name
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|dev_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|dev_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|dev_queue_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|register_netdevice
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|unregister_netdevice
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_netdevice_notifier
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
id|unregister_netdevice_notifier
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
id|dev_new_index
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|dev_get_by_index
c_func
(paren
r_int
id|ifindex
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|__dev_get_by_index
c_func
(paren
r_int
id|ifindex
)paren
suffix:semicolon
r_extern
r_int
id|dev_restart
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|typedef|gifconf_func_t
r_typedef
r_int
id|gifconf_func_t
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|bufptr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|register_gifconf
c_func
(paren
r_int
r_int
id|family
comma
id|gifconf_func_t
op_star
id|gifconf
)paren
suffix:semicolon
DECL|function|unregister_gifconf
r_static
r_inline
r_int
id|unregister_gifconf
c_func
(paren
r_int
r_int
id|family
)paren
(brace
r_return
id|register_gifconf
c_func
(paren
id|family
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Incoming packets are placed on per-cpu queues so that&n; * no locking is needed.&n; */
DECL|struct|softnet_data
r_struct
id|softnet_data
(brace
DECL|member|throttle
r_int
id|throttle
suffix:semicolon
DECL|member|cng_level
r_int
id|cng_level
suffix:semicolon
DECL|member|avg_blog
r_int
id|avg_blog
suffix:semicolon
DECL|member|input_pkt_queue
r_struct
id|sk_buff_head
id|input_pkt_queue
suffix:semicolon
DECL|member|output_queue
r_struct
id|net_device
op_star
id|output_queue
suffix:semicolon
DECL|member|completion_queue
r_struct
id|sk_buff
op_star
id|completion_queue
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|softnet_data
id|softnet_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|HAVE_NETIF_QUEUE
mdefine_line|#define HAVE_NETIF_QUEUE
DECL|function|__netif_schedule
r_static
r_inline
r_void
id|__netif_schedule
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|__LINK_STATE_SCHED
comma
op_amp
id|dev-&gt;state
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dev-&gt;next_sched
op_assign
id|softnet_data
(braket
id|cpu
)braket
dot
id|output_queue
suffix:semicolon
id|softnet_data
(braket
id|cpu
)braket
dot
id|output_queue
op_assign
id|dev
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|cpu
comma
id|NET_TX_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|netif_schedule
r_static
r_inline
r_void
id|netif_schedule
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|__LINK_STATE_XOFF
comma
op_amp
id|dev-&gt;state
)paren
)paren
id|__netif_schedule
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|netif_start_queue
r_static
r_inline
r_void
id|netif_start_queue
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|clear_bit
c_func
(paren
id|__LINK_STATE_XOFF
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
DECL|function|netif_wake_queue
r_static
r_inline
r_void
id|netif_wake_queue
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|__LINK_STATE_XOFF
comma
op_amp
id|dev-&gt;state
)paren
)paren
id|__netif_schedule
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|netif_stop_queue
r_static
r_inline
r_void
id|netif_stop_queue
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|set_bit
c_func
(paren
id|__LINK_STATE_XOFF
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
DECL|function|netif_queue_stopped
r_static
r_inline
r_int
id|netif_queue_stopped
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|__LINK_STATE_XOFF
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
DECL|function|netif_running
r_static
r_inline
r_int
id|netif_running
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|__LINK_STATE_START
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
multiline_comment|/* Use this variant when it is known for sure that it&n; * is executing from interrupt context.&n; */
DECL|function|dev_kfree_skb_irq
r_static
r_inline
r_void
id|dev_kfree_skb_irq
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|skb-&gt;users
)paren
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|skb-&gt;next
op_assign
id|softnet_data
(braket
id|cpu
)braket
dot
id|completion_queue
suffix:semicolon
id|softnet_data
(braket
id|cpu
)braket
dot
id|completion_queue
op_assign
id|skb
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|cpu
comma
id|NET_TX_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Use this variant in places where it could be invoked&n; * either from interrupt or non-interrupt context.&n; */
DECL|function|dev_kfree_skb_any
r_static
r_inline
r_void
id|dev_kfree_skb_any
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|in_irq
c_func
(paren
)paren
)paren
id|dev_kfree_skb_irq
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_extern
r_void
id|net_call_rx_atomic
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
DECL|macro|HAVE_NETIF_RX
mdefine_line|#define HAVE_NETIF_RX 1
r_extern
r_int
id|netif_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|dev_ioctl
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
r_int
id|dev_change_flags
c_func
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dev_queue_xmit_nit
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
r_extern
r_void
id|dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|netdev_nit
suffix:semicolon
DECL|function|dev_init_buffers
r_static
r_inline
r_void
id|dev_init_buffers
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* DO NOTHING */
)brace
r_extern
r_int
id|netdev_finish_unregister
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|dev_put
r_static
r_inline
r_void
id|dev_put
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|dev-&gt;refcnt
)paren
)paren
id|netdev_finish_unregister
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|macro|__dev_put
mdefine_line|#define __dev_put(dev) atomic_dec(&amp;(dev)-&gt;refcnt)
DECL|macro|dev_hold
mdefine_line|#define dev_hold(dev) atomic_inc(&amp;(dev)-&gt;refcnt)
multiline_comment|/* Carrier loss detection, dial on demand. The functions netif_carrier_on&n; * and _off may be called from IRQ context, but it is caller&n; * who is responsible for serialization of these calls.&n; */
DECL|function|netif_carrier_ok
r_static
r_inline
r_int
id|netif_carrier_ok
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
op_logical_neg
id|test_bit
c_func
(paren
id|__LINK_STATE_NOCARRIER
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__netdev_watchdog_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|netif_carrier_on
r_static
r_inline
r_void
id|netif_carrier_on
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|clear_bit
c_func
(paren
id|__LINK_STATE_NOCARRIER
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
)paren
id|__netdev_watchdog_up
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|netif_carrier_off
r_static
r_inline
r_void
id|netif_carrier_off
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|set_bit
c_func
(paren
id|__LINK_STATE_NOCARRIER
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
multiline_comment|/* Hot-plugging. */
DECL|function|netif_device_present
r_static
r_inline
r_int
id|netif_device_present
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|__LINK_STATE_PRESENT
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
)brace
DECL|function|netif_device_detach
r_static
r_inline
r_void
id|netif_device_detach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|__LINK_STATE_PRESENT
comma
op_amp
id|dev-&gt;state
)paren
op_logical_and
id|netif_running
c_func
(paren
id|dev
)paren
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|netif_device_attach
r_static
r_inline
r_void
id|netif_device_attach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|__LINK_STATE_PRESENT
comma
op_amp
id|dev-&gt;state
)paren
op_logical_and
id|netif_running
c_func
(paren
id|dev
)paren
)paren
(brace
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|__netdev_watchdog_up
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* These functions live elsewhere (drivers/net/net_init.c, but related) */
r_extern
r_void
id|ether_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|fddi_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|tr_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|fc_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|fc_freedev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ether_config
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifmap
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* Support for loadable net-drivers */
r_extern
r_int
id|register_netdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|unregister_netdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_trdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|unregister_trdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_fcdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|unregister_fcdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Functions used for multicast support */
r_extern
r_void
id|dev_mc_upload
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|dev_mc_delete
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|alen
comma
r_int
id|all
)paren
suffix:semicolon
r_extern
r_int
id|dev_mc_add
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|alen
comma
r_int
id|newonly
)paren
suffix:semicolon
r_extern
r_void
id|dev_mc_discard
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|dev_set_promiscuity
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|inc
)paren
suffix:semicolon
r_extern
r_void
id|dev_set_allmulti
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|inc
)paren
suffix:semicolon
r_extern
r_void
id|netdev_state_change
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Load a device via the kmod */
r_extern
r_void
id|dev_load
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|dev_mcast_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|netdev_register_fc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
(paren
op_star
id|stimul
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
)paren
suffix:semicolon
r_extern
r_void
id|netdev_unregister_fc
c_func
(paren
r_int
id|bit
)paren
suffix:semicolon
r_extern
r_int
id|netdev_max_backlog
suffix:semicolon
r_extern
r_int
r_int
id|netdev_fc_xoff
suffix:semicolon
r_extern
id|atomic_t
id|netdev_dropping
suffix:semicolon
r_extern
r_int
id|netdev_set_master
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|net_device
op_star
id|master
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_FASTROUTE
r_extern
r_int
id|netdev_fastroute
suffix:semicolon
r_extern
r_int
id|netdev_fastroute_obstacles
suffix:semicolon
r_extern
r_void
id|dev_clear_fastroute
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_DEV_H */
eof
