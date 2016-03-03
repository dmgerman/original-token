multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Pseudo-driver for the loopback interface.&n; *&n; * Version:&t;@(#)loopback.c&t;1.0.4b&t;08/16/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@cesdis.gsfc.nasa.gov&gt;&n; *&n; *&t;&t;Alan Cox&t;:&t;Fixed oddments for NET3.014&n; *&t;&t;Alan Cox&t;:&t;Rejig for NET3.029 snap #3&n; *&t;&t;Alan Cox&t;: &t;Fixed NET3.029 bugs and sped up&n; *&t;&t;Larry McVoy&t;:&t;Tiny tweak to double performance&n; *&t;&t;Alan Cox&t;:&t;Backed out LMV&squot;s tweak - the linux mm&n; *&t;&t;&t;&t;&t;can&squot;t take it...&n; *              Michael Griffith:       Don&squot;t bother computing the checksums&n; *                                      on packets received on the loopback&n; *                                      interface.&n; *&t;&t;Alexey Kuznetsov:&t;Potential hang under some extreme&n; *&t;&t;&t;&t;&t;cases removed.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;&t;/* For the statistics structure. */
macro_line|#include &lt;linux/if_arp.h&gt;&t;/* For ARPHRD_ETHER */
DECL|macro|LOOPBACK_OVERHEAD
mdefine_line|#define LOOPBACK_OVERHEAD (128 + MAX_HEADER + 16 + 16)
multiline_comment|/*&n; * The higher levels take care of making this non-reentrant (it&squot;s&n; * called with bh&squot;s disabled).&n; */
DECL|function|loopback_xmit
r_static
r_int
id|loopback_xmit
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
id|net_device_stats
op_star
id|stats
op_assign
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Optimise so buffers with skb-&gt;free=1 are not copied but&n;&t; *&t;instead are lobbed from tx queue to rx queue &n;&t; */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|skb-&gt;users
)paren
op_ne
l_int|1
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
id|kfree_skb
c_func
(paren
id|skb2
)paren
suffix:semicolon
r_return
l_int|0
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
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
macro_line|#ifndef LOOPBACK_MUST_CHECKSUM
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
macro_line|#endif
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|stats-&gt;rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|stats-&gt;tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|stats-&gt;rx_packets
op_increment
suffix:semicolon
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_stats
r_static
r_struct
id|net_device_stats
op_star
id|get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
)brace
multiline_comment|/* Initialize the rest of the LOOPBACK device. */
DECL|function|loopback_init
r_int
id|__init
id|loopback_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;mtu
op_assign
id|PAGE_SIZE
op_minus
id|LOOPBACK_OVERHEAD
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|loopback_xmit
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|eth_header
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
id|eth_header_cache
suffix:semicolon
id|dev-&gt;header_cache_update
op_assign
id|eth_header_cache_update
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|ETH_HLEN
suffix:semicolon
multiline_comment|/* 14&t;&t;&t;*/
id|dev-&gt;addr_len
op_assign
id|ETH_ALEN
suffix:semicolon
multiline_comment|/* 6&t;&t;&t;*/
id|dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_LOOPBACK
suffix:semicolon
multiline_comment|/* 0x0001&t;&t;*/
id|dev-&gt;rebuild_header
op_assign
id|eth_rebuild_header
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_LOOPBACK
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
id|net_device_stats
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|get_stats
suffix:semicolon
r_if
c_cond
(paren
id|num_physpages
op_ge
(paren
(paren
l_int|128
op_star
l_int|1024
op_star
l_int|1024
)paren
op_rshift
id|PAGE_SHIFT
)paren
)paren
id|dev-&gt;mtu
op_assign
l_int|4096
op_star
l_int|4
op_minus
id|LOOPBACK_OVERHEAD
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fill in the generic fields of the device structure. &n;&t; */
id|dev_init_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
eof
