multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Interfaces handler.&n; *&n; * Version:&t;@(#)dev.h&t;1.0.10&t;08/12/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Donald J. Becker, &lt;becker@super.org&gt;&n; *&t;&t;Alan Cox, &lt;A.Cox@swansea.ac.uk&gt;&n; *&t;&t;Bjorn Ekwall. &lt;bj0rn@blox.se&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;Moved to /usr/include/linux for NET3&n; */
macro_line|#ifndef _LINUX_NETDEVICE_H
DECL|macro|_LINUX_NETDEVICE_H
mdefine_line|#define _LINUX_NETDEVICE_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/* for future expansion when we will have different priorities. */
DECL|macro|DEV_NUMBUFFS
mdefine_line|#define DEV_NUMBUFFS&t;3
DECL|macro|MAX_ADDR_LEN
mdefine_line|#define MAX_ADDR_LEN&t;7
macro_line|#ifndef CONFIG_AX25
DECL|macro|MAX_HEADER
mdefine_line|#define MAX_HEADER&t;32&t;&t;/* We really need about 18 worst case .. so 32 is aligned */
macro_line|#else
DECL|macro|MAX_HEADER
mdefine_line|#define MAX_HEADER&t;96&t;&t;/* AX.25 + NetROM */
macro_line|#endif
DECL|macro|IS_MYADDR
mdefine_line|#define IS_MYADDR&t;1&t;&t;/* address is (one of) our own&t;*/
DECL|macro|IS_LOOPBACK
mdefine_line|#define IS_LOOPBACK&t;2&t;&t;/* address is for LOOPBACK&t;*/
DECL|macro|IS_BROADCAST
mdefine_line|#define IS_BROADCAST&t;3&t;&t;/* address is a valid broadcast&t;*/
DECL|macro|IS_INVBCAST
mdefine_line|#define IS_INVBCAST&t;4&t;&t;/* Wrong netmask bcast not for us (unused)*/
DECL|macro|IS_MULTICAST
mdefine_line|#define IS_MULTICAST&t;5&t;&t;/* Multicast IP address */
multiline_comment|/*&n; *&t;We tag these structures with multicasts.&n; */
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
r_char
id|dmi_addr
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
DECL|member|dmi_addrlen
r_int
r_int
id|dmi_addrlen
suffix:semicolon
DECL|member|dmi_users
r_int
r_int
id|dmi_users
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The DEVICE structure.&n; * Actually, this whole structure is a big mistake.  It mixes I/O&n; * data with strictly &quot;high-level&quot; data, and it has to know about&n; * almost every data structure used in the INET module.  &n; */
DECL|struct|device
r_struct
id|device
(brace
multiline_comment|/*&n;   * This is the first field of the &quot;visible&quot; part of this structure&n;   * (i.e. as seen by users in the &quot;Space.c&quot; file).  It is the name&n;   * the interface.&n;   */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* I/O specific fields - FIXME: Merge these and struct ifmap into one */
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
multiline_comment|/* sahared mem end&t;*/
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
r_char
id|irq
suffix:semicolon
multiline_comment|/* device IRQ number&t;*/
multiline_comment|/* Low-level status flags. */
DECL|member|start
r_volatile
r_int
r_char
id|start
comma
multiline_comment|/* start an operation&t;*/
DECL|member|interrupt
id|interrupt
suffix:semicolon
multiline_comment|/* interrupt arrived&t;*/
DECL|member|tbusy
r_int
r_int
id|tbusy
suffix:semicolon
multiline_comment|/* transmitter busy must be long for bitops */
DECL|member|next
r_struct
id|device
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
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Some hardware also needs these fields, but they are not part of the&n;     usual set specified in Space.c. */
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
DECL|member|get_stats
r_struct
id|enet_statistics
op_star
(paren
op_star
id|get_stats
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;   * This marks the end of the &quot;visible&quot; part of the structure. All&n;   * fields hereafter are internal to the system, and may change at&n;   * will (read: may be cleaned up at will).&n;   */
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
multiline_comment|/* Time of last Rx&t;&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* interface flags (a la BSD)&t;*/
DECL|member|family
r_int
r_int
id|family
suffix:semicolon
multiline_comment|/* address family ID (AF_INET)&t;*/
DECL|member|metric
r_int
r_int
id|metric
suffix:semicolon
multiline_comment|/* routing metric (not used)&t;*/
DECL|member|mtu
r_int
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
DECL|member|pa_addr
r_int
r_int
id|pa_addr
suffix:semicolon
multiline_comment|/* protocol address&t;&t;*/
DECL|member|pa_brdaddr
r_int
r_int
id|pa_brdaddr
suffix:semicolon
multiline_comment|/* protocol broadcast addr&t;*/
DECL|member|pa_dstaddr
r_int
r_int
id|pa_dstaddr
suffix:semicolon
multiline_comment|/* protocol P-P other side addr&t;*/
DECL|member|pa_mask
r_int
r_int
id|pa_mask
suffix:semicolon
multiline_comment|/* protocol netmask&t;&t;*/
DECL|member|pa_alen
r_int
r_int
id|pa_alen
suffix:semicolon
multiline_comment|/* protocol address length&t;*/
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
DECL|member|ip_mc_list
r_struct
id|ip_mc_list
op_star
id|ip_mc_list
suffix:semicolon
multiline_comment|/* IP multicast filter chain    */
multiline_comment|/* For load balancing driver pair support */
DECL|member|pkt_queue
r_int
r_int
id|pkt_queue
suffix:semicolon
multiline_comment|/* Packets queued */
DECL|member|slave
r_struct
id|device
op_star
id|slave
suffix:semicolon
multiline_comment|/* Slave device */
multiline_comment|/* Pointer to the interface buffers. */
DECL|member|buffs
r_struct
id|sk_buff_head
id|buffs
(braket
id|DEV_NUMBUFFS
)braket
suffix:semicolon
multiline_comment|/* Pointers to interface service routines. */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|device
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
id|device
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
id|device
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
id|device
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
r_void
op_star
id|eth
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|raddr
comma
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
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
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
id|device
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
id|device
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
id|device
op_star
id|dev
comma
r_struct
id|ifmap
op_star
id|map
)paren
suffix:semicolon
DECL|member|header_cache
r_void
(paren
op_star
id|header_cache
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
)paren
suffix:semicolon
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
multiline_comment|/* This is really htons(ether_type). */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
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
id|device
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
DECL|member|next
r_struct
id|packet_type
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/notifier.h&gt;
multiline_comment|/* Used by dev_rint */
DECL|macro|IN_SKBUFF
mdefine_line|#define IN_SKBUFF&t;1
r_extern
r_volatile
r_char
id|in_bh
suffix:semicolon
r_extern
r_struct
id|device
id|loopback_dev
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|dev_base
suffix:semicolon
r_extern
r_struct
id|packet_type
op_star
id|ptype_base
(braket
l_int|16
)braket
suffix:semicolon
r_extern
r_int
id|ip_addr_match
c_func
(paren
r_int
r_int
id|addr1
comma
r_int
r_int
id|addr2
)paren
suffix:semicolon
r_extern
r_int
id|ip_chk_addr
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|ip_dev_check
c_func
(paren
r_int
r_int
id|daddr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip_my_addr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip_get_mask
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|device
op_star
id|ip_dev_find
c_func
(paren
r_int
r_int
id|addr
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
r_struct
id|device
op_star
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
r_int
id|dev_open
c_func
(paren
r_struct
id|device
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
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|dev_queue_xmit
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
r_int
id|pri
)paren
suffix:semicolon
DECL|macro|HAVE_NETIF_RX
mdefine_line|#define HAVE_NETIF_RX 1
r_extern
r_void
id|netif_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* The old interface to netif_rx(). */
r_extern
r_int
id|dev_rint
c_func
(paren
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
id|flags
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|dev_transmit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|in_net_bh
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|net_bh
c_func
(paren
r_void
op_star
id|tmp
)paren
suffix:semicolon
r_extern
r_void
id|dev_tint
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|dev_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
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
r_void
id|dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Locking protection for page faults during outputs to devices unloaded during the fault */
r_extern
r_int
id|dev_lockct
suffix:semicolon
multiline_comment|/*&n; *&t;These two dont currently need to be interrupt safe&n; *&t;but they may do soon. Do it properly anyway.&n; */
DECL|function|dev_lock_list
r_extern
id|__inline__
r_void
id|dev_lock_list
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|dev_lockct
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dev_unlock_list
r_extern
id|__inline__
r_void
id|dev_unlock_list
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|dev_lockct
op_decrement
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This almost never occurs, isnt in performance critical paths&n; *&t;and we can thus be relaxed about it&n; */
DECL|function|dev_lock_wait
r_extern
id|__inline__
r_void
id|dev_lock_wait
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|dev_lockct
)paren
(brace
id|schedule
c_func
(paren
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
id|device
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
id|device
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
id|device
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
id|device
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
id|device
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
multiline_comment|/* Functions used for multicast support */
r_extern
r_void
id|dev_mc_upload
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
id|dev_mc_delete
c_func
(paren
r_struct
id|device
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
r_void
id|dev_mc_add
c_func
(paren
r_struct
id|device
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
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* This is the wrong place but it&squot;ll do for the moment */
r_extern
r_void
id|ip_mc_allhost
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_DEV_H */
eof
