multiline_comment|/* linux/net/inet/rarp.c&n; *&n; * Copyright (C) 1994 by Ross Martin&n; * Based on linux/net/inet/arp.c, Copyright (C) 1994 by Florian La Roche&n; *&n; * $Id: rarp.c,v 1.21 1997/10/27 09:13:16 geert Exp $&n; *&n; * This module implements the Reverse Address Resolution Protocol &n; * (RARP, RFC 903), which is used to convert low level addresses such&n; * as ethernet addresses into high level addresses such as IP addresses.&n; * The most common use of RARP is as a means for a diskless workstation &n; * to discover its IP address during a network boot.&n; *&n; **&n; ***&t;WARNING:::::::::::::::::::::::::::::::::WARNING&n; ****&n; *****&t;SUN machines seem determined to boot solely from the person who&n; ****&t;answered their RARP query. NEVER add a SUN to your RARP table&n; ***&t;unless you have all the rest to boot the box from it. &n; **&n; * &n; * Currently, only ethernet address -&gt; IP address is likely to work.&n; * (Is RARP ever used for anything else?)&n; *&n; * This code is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Fixes&n; *&t;Alan Cox&t;:&t;Rarp delete on device down needed as&n; *&t;&t;&t;&t;reported by Walter Wolfgang.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/rarp.h&gt;
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
r_extern
r_int
(paren
op_star
id|rarp_ioctl_hook
)paren
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;This structure defines the RARP mapping cache. As long as we make &n; *&t;changes in this structure, we keep interrupts off.&n; */
DECL|struct|rarp_table
r_struct
id|rarp_table
(brace
DECL|member|next
r_struct
id|rarp_table
op_star
id|next
suffix:semicolon
multiline_comment|/* Linked entry list           */
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* ip address of entry         */
DECL|member|ha
r_int
r_char
id|ha
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* Hardware address            */
DECL|member|hlen
r_int
r_char
id|hlen
suffix:semicolon
multiline_comment|/* Length of hardware address  */
DECL|member|htype
r_int
r_char
id|htype
suffix:semicolon
multiline_comment|/* Type of hardware in use     */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device the entry is tied to */
)brace
suffix:semicolon
DECL|variable|rarp_tables
r_struct
id|rarp_table
op_star
id|rarp_tables
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|rarp_rcv
c_func
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
DECL|variable|rarp_packet_type
r_static
r_struct
id|packet_type
id|rarp_packet_type
op_assign
(brace
l_int|0
comma
multiline_comment|/* Should be: __constant_htons(ETH_P_RARP) - but this _doesn&squot;t_ come out constant! */
l_int|0
comma
multiline_comment|/* copy */
id|rarp_rcv
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|initflag
r_static
r_int
id|initflag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n; *&t;Release the memory for this entry.&n; */
DECL|function|rarp_release_entry
r_static
r_inline
r_void
id|rarp_release_entry
c_func
(paren
r_struct
id|rarp_table
op_star
id|entry
)paren
(brace
id|kfree_s
c_func
(paren
id|entry
comma
r_sizeof
(paren
r_struct
id|rarp_table
)paren
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Delete a RARP mapping entry in the cache.&n; */
DECL|function|rarp_destroy
r_static
r_void
id|rarp_destroy
c_func
(paren
r_int
r_int
id|ip_addr
)paren
(brace
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_struct
id|rarp_table
op_star
op_star
id|pentry
suffix:semicolon
id|start_bh_atomic
c_func
(paren
)paren
suffix:semicolon
id|pentry
op_assign
op_amp
id|rarp_tables
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
op_star
id|pentry
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;ip
op_eq
id|ip_addr
)paren
(brace
op_star
id|pentry
op_assign
id|entry-&gt;next
suffix:semicolon
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
id|rarp_release_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pentry
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Flush a device.&n; */
DECL|function|rarp_destroy_dev
r_static
r_void
id|rarp_destroy_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_struct
id|rarp_table
op_star
op_star
id|pentry
suffix:semicolon
id|start_bh_atomic
c_func
(paren
)paren
suffix:semicolon
id|pentry
op_assign
op_amp
id|rarp_tables
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
op_star
id|pentry
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;dev
op_eq
id|dev
)paren
(brace
op_star
id|pentry
op_assign
id|entry-&gt;next
suffix:semicolon
id|rarp_release_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
r_else
id|pentry
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
id|end_bh_atomic
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rarp_device_event
r_static
r_int
id|rarp_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_if
c_cond
(paren
id|event
op_ne
id|NETDEV_DOWN
)paren
(brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
id|rarp_destroy_dev
c_func
(paren
(paren
r_struct
id|device
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Called once when data first added to rarp cache with ioctl.&n; */
DECL|variable|rarp_dev_notifier
r_static
r_struct
id|notifier_block
id|rarp_dev_notifier
op_assign
initialization_block
suffix:semicolon
DECL|variable|rarp_pkt_inited
r_static
r_int
id|rarp_pkt_inited
op_assign
l_int|0
suffix:semicolon
DECL|function|rarp_init_pkt
r_static
r_void
id|rarp_init_pkt
(paren
r_void
)paren
(brace
multiline_comment|/* Register the packet type */
id|rarp_packet_type.type
op_assign
id|htons
c_func
(paren
id|ETH_P_RARP
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|rarp_packet_type
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|rarp_dev_notifier
)paren
suffix:semicolon
id|rarp_pkt_inited
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|rarp_end_pkt
r_static
r_void
id|rarp_end_pkt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rarp_pkt_inited
)paren
(brace
r_return
suffix:semicolon
)brace
id|dev_remove_pack
c_func
(paren
op_amp
id|rarp_packet_type
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|rarp_dev_notifier
)paren
suffix:semicolon
id|rarp_pkt_inited
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Receive an arp request by the device layer.  Maybe it should be &n; *&t;rewritten to use the incoming packet for the reply. The current &n; *&t;&quot;overhead&quot; time isn&squot;t that high...&n; */
DECL|function|rarp_rcv
r_static
r_int
id|rarp_rcv
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
id|pt
)paren
(brace
multiline_comment|/*&n; *&t;We shouldn&squot;t use this type conversion. Check later.&n; */
r_struct
id|arphdr
op_star
id|rarp
op_assign
(paren
r_struct
id|arphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_int
r_char
op_star
id|rarp_ptr
op_assign
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|arphdr
)paren
)paren
suffix:semicolon
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
op_assign
id|dev-&gt;ip_ptr
suffix:semicolon
r_int
id|sip
comma
id|tip
suffix:semicolon
r_int
r_char
op_star
id|sha
comma
op_star
id|tha
suffix:semicolon
multiline_comment|/* s for &quot;source&quot;, t for &quot;target&quot; */
multiline_comment|/*&n; *&t;If this test doesn&squot;t pass, it&squot;s not IP, or we should ignore it anyway&n; */
r_if
c_cond
(paren
id|rarp-&gt;ar_hln
op_ne
id|dev-&gt;addr_len
op_logical_or
id|dev-&gt;type
op_ne
id|ntohs
c_func
(paren
id|rarp-&gt;ar_hrd
)paren
op_logical_or
id|dev-&gt;flags
op_amp
id|IFF_NOARP
op_logical_or
op_logical_neg
id|in_dev
op_logical_or
op_logical_neg
id|in_dev-&gt;ifa_list
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
multiline_comment|/*&n; *&t;If it&squot;s not a RARP request, delete it.&n; */
r_if
c_cond
(paren
id|rarp-&gt;ar_op
op_ne
id|htons
c_func
(paren
id|ARPOP_RREQUEST
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
multiline_comment|/*&n; *&t;For now we will only deal with IP addresses.&n; */
r_if
c_cond
(paren
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
(paren
id|rarp-&gt;ar_pro
op_ne
id|htons
c_func
(paren
id|AX25_P_IP
)paren
op_logical_and
id|dev-&gt;type
op_eq
id|ARPHRD_AX25
)paren
op_logical_or
macro_line|#endif
(paren
id|rarp-&gt;ar_pro
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
op_logical_and
id|dev-&gt;type
op_ne
id|ARPHRD_AX25
)paren
op_logical_or
id|rarp-&gt;ar_pln
op_ne
l_int|4
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;This packet is not for us. Remove it. &n;&t;&t; */
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
multiline_comment|/*&n; *&t;Extract variable width fields&n; */
id|sha
op_assign
id|rarp_ptr
suffix:semicolon
id|rarp_ptr
op_add_assign
id|dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sip
comma
id|rarp_ptr
comma
l_int|4
)paren
suffix:semicolon
id|rarp_ptr
op_add_assign
l_int|4
suffix:semicolon
id|tha
op_assign
id|rarp_ptr
suffix:semicolon
id|rarp_ptr
op_add_assign
id|dev-&gt;addr_len
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tip
comma
id|rarp_ptr
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Process entry. Use tha for table lookup according to RFC903.&n; */
r_for
c_loop
(paren
id|entry
op_assign
id|rarp_tables
suffix:semicolon
id|entry
op_ne
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|entry-&gt;ha
comma
id|tha
comma
id|rarp-&gt;ar_hln
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_ne
l_int|NULL
)paren
(brace
id|sip
op_assign
id|entry-&gt;ip
suffix:semicolon
id|arp_send
c_func
(paren
id|ARPOP_RREPLY
comma
id|ETH_P_RARP
comma
id|sip
comma
id|dev
comma
id|in_dev-&gt;ifa_list-&gt;ifa_address
comma
id|sha
comma
id|dev-&gt;dev_addr
comma
id|sha
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
multiline_comment|/*&n; *&t;Set (create) a RARP cache entry.&n; */
DECL|function|rarp_req_set
r_static
r_int
id|rarp_req_set
c_func
(paren
r_struct
id|arpreq
op_star
id|req
)paren
(brace
r_struct
id|arpreq
id|r
suffix:semicolon
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|si
suffix:semicolon
r_int
id|htype
comma
id|hlen
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|r
comma
id|req
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; *&t;We only understand about IP addresses... &n;&t; */
r_if
c_cond
(paren
id|r.arp_pa.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPFNOSUPPORT
suffix:semicolon
r_switch
c_cond
(paren
id|r.arp_ha.sa_family
)paren
(brace
r_case
id|ARPHRD_ETHER
suffix:colon
id|htype
op_assign
id|ARPHRD_ETHER
suffix:semicolon
id|hlen
op_assign
id|ETH_ALEN
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
r_case
id|ARPHRD_AX25
suffix:colon
id|htype
op_assign
id|ARPHRD_AX25
suffix:semicolon
id|hlen
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EPFNOSUPPORT
suffix:semicolon
)brace
id|si
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|r.arp_pa
suffix:semicolon
id|ip
op_assign
id|si-&gt;sin_addr.s_addr
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;RARP: SETRARP: requested PA is 0.0.0.0 !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Is it reachable directly ?&n; */
id|err
op_assign
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|ip
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
(paren
id|RTCF_LOCAL
op_or
id|RTCF_BROADCAST
op_or
id|RTCF_MULTICAST
op_or
id|RTCF_DNAT
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dev
op_assign
id|rt-&gt;u.dst.dev
suffix:semicolon
multiline_comment|/*&n; *&t;Is there an existing entry for this address?  Find out...&n; */
r_for
c_loop
(paren
id|entry
op_assign
id|rarp_tables
suffix:semicolon
id|entry
op_ne
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
r_if
c_cond
(paren
id|entry-&gt;ip
op_eq
id|ip
)paren
r_break
suffix:semicolon
multiline_comment|/*&n; *&t;If no entry was found, create a new one.&n; */
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|entry
op_assign
(paren
r_struct
id|rarp_table
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rarp_table
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|initflag
)paren
(brace
id|rarp_init_pkt
c_func
(paren
)paren
suffix:semicolon
id|initflag
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Block interrupts until table modification is finished */
id|cli
c_func
(paren
)paren
suffix:semicolon
id|entry-&gt;next
op_assign
id|rarp_tables
suffix:semicolon
id|rarp_tables
op_assign
id|entry
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|entry-&gt;ip
op_assign
id|ip
suffix:semicolon
id|entry-&gt;hlen
op_assign
id|hlen
suffix:semicolon
id|entry-&gt;htype
op_assign
id|htype
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|entry-&gt;ha
comma
op_amp
id|r.arp_ha.sa_data
comma
id|hlen
)paren
suffix:semicolon
id|entry-&gt;dev
op_assign
id|dev
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t unlink if we have entries to serve. */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *        Get a RARP cache entry.&n; */
DECL|function|rarp_req_get
r_static
r_int
id|rarp_req_get
c_func
(paren
r_struct
id|arpreq
op_star
id|req
)paren
(brace
r_struct
id|arpreq
id|r
suffix:semicolon
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|si
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n; *&t;We only understand about IP addresses...&n; */
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|r
comma
id|req
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|r.arp_pa.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPFNOSUPPORT
suffix:semicolon
multiline_comment|/*&n; *        Is there an existing entry for this address?&n; */
id|si
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|r.arp_pa
suffix:semicolon
id|ip
op_assign
id|si-&gt;sin_addr.s_addr
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|rarp_tables
suffix:semicolon
id|entry
op_ne
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
r_if
c_cond
(paren
id|entry-&gt;ip
op_eq
id|ip
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/*&n; *        We found it; copy into structure.&n; */
id|memcpy
c_func
(paren
id|r.arp_ha.sa_data
comma
op_amp
id|entry-&gt;ha
comma
id|entry-&gt;hlen
)paren
suffix:semicolon
id|r.arp_ha.sa_family
op_assign
id|entry-&gt;htype
suffix:semicolon
multiline_comment|/*&n; *        Copy the information back&n; */
r_return
id|copy_to_user
c_func
(paren
id|req
comma
op_amp
id|r
comma
r_sizeof
(paren
id|r
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle a RARP layer I/O control request.&n; */
DECL|function|rarp_ioctl
r_int
id|rarp_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|arpreq
id|r
suffix:semicolon
r_struct
id|sockaddr_in
op_star
id|si
suffix:semicolon
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCDRARP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|r
comma
id|arg
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|r.arp_pa.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPFNOSUPPORT
suffix:semicolon
id|si
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|r.arp_pa
suffix:semicolon
id|rarp_destroy
c_func
(paren
id|si-&gt;sin_addr.s_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SIOCGRARP
suffix:colon
r_return
id|rarp_req_get
c_func
(paren
(paren
r_struct
id|arpreq
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCSRARP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|rarp_req_set
c_func
(paren
(paren
r_struct
id|arpreq
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*NOTREACHED*/
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|rarp_get_info
r_int
id|rarp_get_info
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
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|rarp_table
op_star
id|entry
suffix:semicolon
r_char
id|ipbuffer
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|netip
suffix:semicolon
r_if
c_cond
(paren
id|initflag
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;RARP disabled until entries added to cache.&bslash;n&quot;
)paren
suffix:semicolon
id|pos
op_add_assign
id|size
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;IP address       HW type             HW address&bslash;n&quot;
)paren
suffix:semicolon
id|pos
op_add_assign
id|size
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|rarp_tables
suffix:semicolon
id|entry
op_ne
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|netip
op_assign
id|htonl
c_func
(paren
id|entry-&gt;ip
)paren
suffix:semicolon
multiline_comment|/* switch to network order */
id|sprintf
c_func
(paren
id|ipbuffer
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
(paren
r_int
r_int
)paren
(paren
id|netip
op_rshift
l_int|24
)paren
op_amp
l_int|255
comma
(paren
r_int
r_int
)paren
(paren
id|netip
op_rshift
l_int|16
)paren
op_amp
l_int|255
comma
(paren
r_int
r_int
)paren
(paren
id|netip
op_rshift
l_int|8
)paren
op_amp
l_int|255
comma
(paren
r_int
r_int
)paren
(paren
id|netip
)paren
op_amp
l_int|255
)paren
suffix:semicolon
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-17s%-20s%02x:%02x:%02x:%02x:%02x:%02x&bslash;n&quot;
comma
id|ipbuffer
comma
l_string|&quot;10Mbps Ethernet&quot;
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|2
)braket
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|3
)braket
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|4
)braket
comma
(paren
r_int
r_int
)paren
id|entry-&gt;ha
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
)brace
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
multiline_comment|/* Ending slop */
r_return
id|len
suffix:semicolon
)brace
DECL|variable|proc_net_rarp
r_struct
id|proc_dir_entry
id|proc_net_rarp
op_assign
(brace
id|PROC_NET_RARP
comma
l_int|4
comma
l_string|&quot;rarp&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_net_inode_operations
comma
id|rarp_get_info
)brace
suffix:semicolon
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|rarp_init
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_register
c_func
(paren
op_amp
id|proc_net_rarp
)paren
suffix:semicolon
macro_line|#endif
id|rarp_ioctl_hook
op_assign
id|rarp_ioctl
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|rarp_init
c_func
(paren
)paren
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
r_struct
id|rarp_table
op_star
id|rt
comma
op_star
id|rt_next
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_unregister
c_func
(paren
id|PROC_NET_RARP
)paren
suffix:semicolon
macro_line|#endif
id|rarp_ioctl_hook
op_assign
l_int|NULL
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Destroy the RARP-table */
id|rt
op_assign
id|rarp_tables
suffix:semicolon
id|rarp_tables
op_assign
l_int|NULL
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ... and free it. */
r_for
c_loop
(paren
suffix:semicolon
id|rt
op_ne
l_int|NULL
suffix:semicolon
id|rt
op_assign
id|rt_next
)paren
(brace
id|rt_next
op_assign
id|rt-&gt;next
suffix:semicolon
id|rarp_release_entry
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
id|rarp_end_pkt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
