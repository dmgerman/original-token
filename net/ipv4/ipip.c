multiline_comment|/*&n; *&t;Linux NET3:&t;IP/IP protocol decoder. &n; *&n; *&t;Authors:&n; *&t;&t;Sam Lantinga (slouken@cs.ucdavis.edu)  02/01/95&n; *&n; *&t;Fixes:&n; *&t;&t;Alan Cox&t;:&t;Merged and made usable non modular (its so tiny its silly as&n; *&t;&t;&t;&t;&t;a module taking up 2 pages).&n; *&t;&t;Alan Cox&t;: &t;Fixed bug with 1.3.18 and IPIP not working (now needs to set skb-&gt;h.iph)&n; *&t;&t;&t;&t;&t;to keep ip_forward happy.&n; *&t;&t;Alan Cox&t;:&t;More fixes for 1.3.21, and firewall fix. Maybe this will work soon 8).&n; *&t;&t;Kai Schulte&t;:&t;Fixed #defines for IP_FIREWALL-&gt;FIREWALL&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;linux/config.h&gt;&t;/* For CONFIG_FIREWALL */
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
multiline_comment|/*&n; *&t;The IPIP protocol driver.&n; *&n; *&t;On entry here&n; *&t;&t;skb-&gt;data is the original IP header&n; *&t;&t;skb-&gt;ip_hdr points to the initial IP header.&n; *&t;&t;skb-&gt;h.raw points at the new header.&n; */
DECL|function|ipip_rcv
r_int
id|ipip_rcv
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
id|options
op_star
id|opt
comma
id|__u32
id|daddr
comma
r_int
r_int
id|len
comma
id|__u32
id|saddr
comma
r_int
id|redo
comma
r_struct
id|inet_protocol
op_star
id|protocol
)paren
(brace
macro_line|#ifdef CONFIG_FIREWALL
r_int
id|err
suffix:semicolon
macro_line|#endif
multiline_comment|/* Don&squot;t unlink in the middle of a turnaround */
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#ifdef TUNNEL_DEBUG
id|printk
c_func
(paren
l_string|&quot;ipip_rcv: got a packet!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Discard the original IP header&n;&t; */
id|skb_pull
c_func
(paren
id|skb
comma
(paren
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
)paren
op_member_access_from_pointer
id|ihl
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adjust pointers&n;&t; */
id|skb-&gt;h.iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;ip_hdr
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|memset
c_func
(paren
id|skb-&gt;proto_priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|options
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;If you want to add LZ compressed IP or things like that here,&n;&t; *&t;and in drivers/net/tunnel.c are the places to add.&n;&t; */
multiline_comment|/* skb=lzw_uncompress(skb); */
multiline_comment|/*&n;&t; *&t;Feed it to the IP layer.&n;&t; */
id|ip_rcv
c_func
(paren
id|skb
comma
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|ipip_protocol
r_static
r_struct
id|inet_protocol
id|ipip_protocol
op_assign
(brace
id|ipip_rcv
comma
multiline_comment|/* IPIP handler          */
macro_line|#if 0
l_int|NULL
comma
multiline_comment|/* Will be UDP fraglist handler */
macro_line|#endif
l_int|NULL
comma
multiline_comment|/* TUNNEL error control    */
l_int|0
comma
multiline_comment|/* next                 */
id|IPPROTO_IPIP
comma
multiline_comment|/* protocol ID          */
l_int|0
comma
multiline_comment|/* copy                 */
l_int|NULL
comma
multiline_comment|/* data                 */
l_string|&quot;IPIP&quot;
multiline_comment|/* name                 */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;And now the modules code and kernel interface.&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|inet_add_protocol
c_func
(paren
op_amp
id|ipip_protocol
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
r_if
c_cond
(paren
id|inet_del_protocol
c_func
(paren
op_amp
id|ipip_protocol
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;ipip close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
