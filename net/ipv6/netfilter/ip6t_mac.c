multiline_comment|/* Kernel module to match MAC address parameters. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_mac.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
r_static
r_int
DECL|function|match
id|match
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|matchinfo
comma
r_int
id|offset
comma
r_const
r_void
op_star
id|hdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_const
r_struct
id|ip6t_mac_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
multiline_comment|/* Is mac pointer valid? */
r_return
(paren
id|skb-&gt;mac.raw
op_ge
id|skb-&gt;head
op_logical_and
id|skb-&gt;mac.raw
OL
id|skb-&gt;head
op_plus
id|skb-&gt;len
op_minus
id|ETH_HLEN
multiline_comment|/* If so, compare... */
op_logical_and
(paren
(paren
id|memcmp
c_func
(paren
id|skb-&gt;mac.ethernet-&gt;h_source
comma
id|info-&gt;srcaddr
comma
id|ETH_ALEN
)paren
op_eq
l_int|0
)paren
op_xor
id|info-&gt;invert
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ipt_mac_checkentry
id|ipt_mac_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_ip6
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_if
c_cond
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP6_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP6_LOCAL_IN
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ipt_mac: only valid for PRE_ROUTING or LOCAL_IN.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|matchsize
op_ne
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_mac_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|mac_match
r_static
r_struct
id|ip6t_match
id|mac_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;mac&quot;
comma
op_amp
id|match
comma
op_amp
id|ipt_mac_checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|ip6t_register_match
c_func
(paren
op_amp
id|mac_match
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ip6t_unregister_match
c_func
(paren
op_amp
id|mac_match
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
