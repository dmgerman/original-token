multiline_comment|/*&n; *&t;Linux NET3:&t;IP/IP protocol decoder. &n; *&n; *&t;Authors:&n; *&t;&t;Sam Lantinga (slouken@cs.ucdavis.edu)  02/01/95&n; *&n; *&t;Fixes:&n; *&t;&t;Alan Cox&t;:&t;Merged and made usable non modular (its so tiny its silly as&n; *&t;&t;&t;&t;&t;a module taking up 2 pages).&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
multiline_comment|/*&n; * NB. we must include the kernel idenfication string in to install the module.&n; */
macro_line|#if ( defined(CONFIG_NET_IPIP) &amp;&amp; defined(CONFIG_IP_FORWARD)) || defined(MODULE)
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|variable|kernel_version
r_static
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT
macro_line|#endif 
multiline_comment|/*&n; *&t;The driver.&n; */
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
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
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
r_if
c_cond
(paren
id|ip_forward
c_func
(paren
id|skb
comma
id|dev
comma
l_int|0
comma
id|daddr
comma
l_int|0
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
)brace
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
l_int|NULL
comma
multiline_comment|/* Will be UDP fraglist handler */
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
macro_line|#endif
eof
