multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Pseudo-driver for the loopback interface.&n; *&n; * Version:&t;@(#)loopback.c&t;1.0.4b&t;08/16/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@cesdis.gsfc.nasa.gov&gt;&n; *&n; *&t;&t;Alan Cox&t;:&t;Fixed oddments for NET3.014&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;&t;/* For the statistics structure. */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_static
r_int
DECL|function|loopback_xmit
id|loopback_xmit
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
id|enet_statistics
op_star
id|stats
op_assign
(paren
r_struct
id|enet_statistics
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|done
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
op_logical_or
id|dev
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tbusy
op_ne
l_int|0
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|stats-&gt;tx_errors
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: Optimise so buffers with skb-&gt;free=1 are not copied but&n;     instead are lobbed from tx queue to rx queue */
id|done
op_assign
id|dev_rint
c_func
(paren
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|done
op_ne
l_int|1
)paren
(brace
id|done
op_assign
id|dev_rint
c_func
(paren
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
)brace
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
macro_line|#if 1
id|__asm__
c_func
(paren
l_string|&quot;cmpl $0,_intr_count&bslash;n&bslash;t&quot;
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;movl _bh_active,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;testl _bh_mask,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;incl _intr_count&bslash;n&bslash;t&quot;
l_string|&quot;call _do_bottom_half&bslash;n&bslash;t&quot;
l_string|&quot;decl _intr_count&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|enet_statistics
op_star
DECL|function|get_stats
id|get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|enet_statistics
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
)brace
DECL|function|loopback_open
r_static
r_int
id|loopback_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|dev-&gt;flags
op_or_assign
id|IFF_LOOPBACK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize the rest of the LOOPBACK device. */
r_int
DECL|function|loopback_init
id|loopback_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|2000
suffix:semicolon
multiline_comment|/* MTU&t;&t;&t;*/
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|loopback_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if 1
id|dev-&gt;hard_header
op_assign
id|eth_header
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
id|dev-&gt;type
op_assign
id|ARPHRD_ETHER
suffix:semicolon
multiline_comment|/* 0x0001&t;&t;*/
id|dev-&gt;type_trans
op_assign
id|eth_type_trans
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|eth_rebuild_header
suffix:semicolon
id|dev-&gt;open
op_assign
id|loopback_open
suffix:semicolon
macro_line|#else
id|dev-&gt;hard_header_length
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* loopback_type (0)&t;*/
id|dev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;type_trans
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
id|IFF_LOOPBACK
op_or
id|IFF_BROADCAST
suffix:semicolon
id|dev-&gt;family
op_assign
id|AF_INET
suffix:semicolon
macro_line|#ifdef CONFIG_INET    
id|dev-&gt;pa_addr
op_assign
id|in_aton
c_func
(paren
l_string|&quot;127.0.0.1&quot;
)paren
suffix:semicolon
id|dev-&gt;pa_brdaddr
op_assign
id|in_aton
c_func
(paren
l_string|&quot;127.255.255.255&quot;
)paren
suffix:semicolon
id|dev-&gt;pa_mask
op_assign
id|in_aton
c_func
(paren
l_string|&quot;255.0.0.0&quot;
)paren
suffix:semicolon
id|dev-&gt;pa_alen
op_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif  
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|enet_statistics
)paren
comma
id|GFP_KERNEL
)paren
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
id|enet_statistics
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|get_stats
suffix:semicolon
multiline_comment|/* Fill in the generic fields of the device structure. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DEV_NUMBUFFS
suffix:semicolon
id|i
op_increment
)paren
id|skb_queue_head_init
c_func
(paren
op_amp
id|dev-&gt;buffs
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
eof
