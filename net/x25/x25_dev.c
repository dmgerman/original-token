multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;Started coding.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_X25) || defined(CONFIG_X25_MODULE)
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;&t;/* For TIOCINQ/OUTQ */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;net/x25.h&gt;
DECL|function|x25_receive_data
r_static
r_int
id|x25_receive_data
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|x25_neigh
op_star
id|neigh
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_int
r_int
id|frametype
suffix:semicolon
r_int
r_int
id|lci
suffix:semicolon
r_if
c_cond
(paren
id|call_in_firewall
c_func
(paren
id|PF_X25
comma
id|skb-&gt;dev
comma
id|skb-&gt;data
comma
l_int|NULL
comma
op_amp
id|skb
)paren
op_ne
id|FW_ACCEPT
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
id|frametype
op_assign
id|skb-&gt;data
(braket
l_int|2
)braket
suffix:semicolon
id|lci
op_assign
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_amp
l_int|0xF00
)paren
op_plus
(paren
(paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_lshift
l_int|0
)paren
op_amp
l_int|0x0FF
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;LCI of zero is always for us, and its always a link control&n;&t; *&t;frame.&n;&t; */
r_if
c_cond
(paren
id|lci
op_eq
l_int|0
)paren
(brace
id|x25_link_control
c_func
(paren
id|skb
comma
id|neigh
comma
id|frametype
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Find an existing socket.&n;&t; */
r_if
c_cond
(paren
(paren
id|sk
op_assign
id|x25_find_socket
c_func
(paren
id|lci
comma
id|neigh
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|x25_process_rx_frame
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Is is a Call Request ? if so process it.&n;&t; */
r_if
c_cond
(paren
id|frametype
op_eq
id|X25_CALL_REQUEST
)paren
r_return
id|x25_rx_call_request
c_func
(paren
id|skb
comma
id|neigh
comma
id|lci
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Its not a Call Request, nor is it a control frame, throw it awa&n;&t; */
multiline_comment|/*&n;&t;x25_transmit_clear_request(neigh, lci, 0x0D);&n;*/
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
DECL|function|x25_lapb_receive_frame
r_int
id|x25_lapb_receive_frame
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
id|packet_type
op_star
id|ptype
)paren
(brace
r_struct
id|x25_neigh
op_star
id|neigh
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Packet received from unrecognised device, throw it away.&n;&t; */
r_if
c_cond
(paren
(paren
id|neigh
op_assign
id|x25_get_neigh
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;X.25: unknown neighbour - %s&bslash;n&quot;
comma
id|dev-&gt;name
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
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_return
id|x25_receive_data
c_func
(paren
id|skb
comma
id|neigh
)paren
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|x25_link_established
c_func
(paren
id|neigh
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
r_case
l_int|0x02
suffix:colon
id|x25_link_terminated
c_func
(paren
id|neigh
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
r_case
l_int|0x03
suffix:colon
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
r_default
suffix:colon
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
)brace
DECL|function|x25_llc_receive_frame
r_int
id|x25_llc_receive_frame
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
id|packet_type
op_star
id|ptype
)paren
(brace
r_struct
id|x25_neigh
op_star
id|neigh
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Packet received from unrecognised device, throw it away.&n;&t; */
r_if
c_cond
(paren
(paren
id|neigh
op_assign
id|x25_get_neigh
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;X.25: unknown_neighbour - %s&bslash;n&quot;
comma
id|dev-&gt;name
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
r_return
id|x25_receive_data
c_func
(paren
id|skb
comma
id|neigh
)paren
suffix:semicolon
)brace
DECL|function|x25_establish_link
r_void
id|x25_establish_link
c_func
(paren
r_struct
id|x25_neigh
op_star
id|neigh
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_switch
c_cond
(paren
id|neigh-&gt;dev-&gt;type
)paren
(brace
r_case
id|ARPHRD_X25
suffix:colon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|1
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;x25_dev: out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0x01
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
r_case
id|ARPHRD_ETHER
suffix:colon
r_return
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|x25_terminate_link
r_void
id|x25_terminate_link
c_func
(paren
r_struct
id|x25_neigh
op_star
id|neigh
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_switch
c_cond
(paren
id|neigh-&gt;dev-&gt;type
)paren
(brace
r_case
id|ARPHRD_X25
suffix:colon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
l_int|1
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;x25_dev: out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
r_case
id|ARPHRD_ETHER
suffix:colon
r_return
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|x25_send_frame
r_void
id|x25_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|x25_neigh
op_star
id|neigh
)paren
(brace
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_switch
c_cond
(paren
id|neigh-&gt;dev-&gt;type
)paren
(brace
r_case
id|ARPHRD_X25
suffix:colon
id|dptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
r_case
id|ARPHRD_ETHER
suffix:colon
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
macro_line|#endif
r_default
suffix:colon
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
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_X25
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
