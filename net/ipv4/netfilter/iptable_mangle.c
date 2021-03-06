multiline_comment|/*&n; * This is the 1999 rewrite of IP Firewalling, aiming for kernel 2.3.x.&n; *&n; * Copyright (C) 1999 Paul `Rusty&squot; Russell &amp; Michael J. Neuling&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|macro|MANGLE_VALID_HOOKS
mdefine_line|#define MANGLE_VALID_HOOKS ((1 &lt;&lt; NF_IP_PRE_ROUTING) | (1 &lt;&lt; NF_IP_LOCAL_OUT))
multiline_comment|/* Standard entry. */
DECL|struct|ipt_standard
r_struct
id|ipt_standard
(brace
DECL|member|entry
r_struct
id|ipt_entry
id|entry
suffix:semicolon
DECL|member|target
r_struct
id|ipt_standard_target
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipt_error_target
r_struct
id|ipt_error_target
(brace
DECL|member|target
r_struct
id|ipt_entry_target
id|target
suffix:semicolon
DECL|member|errorname
r_char
id|errorname
(braket
id|IPT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipt_error
r_struct
id|ipt_error
(brace
DECL|member|entry
r_struct
id|ipt_entry
id|entry
suffix:semicolon
DECL|member|target
r_struct
id|ipt_error_target
id|target
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|repl
r_struct
id|ipt_replace
id|repl
suffix:semicolon
DECL|member|entries
r_struct
id|ipt_standard
id|entries
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|term
r_struct
id|ipt_error
id|term
suffix:semicolon
DECL|variable|__initdata
)brace
id|initial_table
id|__initdata
op_assign
(brace
(brace
l_string|&quot;mangle&quot;
comma
id|MANGLE_VALID_HOOKS
comma
l_int|3
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
op_star
l_int|2
op_plus
r_sizeof
(paren
r_struct
id|ipt_error
)paren
comma
(brace
(braket
id|NF_IP_PRE_ROUTING
)braket
l_int|0
comma
(braket
id|NF_IP_LOCAL_OUT
)braket
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
)brace
comma
(brace
(braket
id|NF_IP_PRE_ROUTING
)braket
l_int|0
comma
(braket
id|NF_IP_LOCAL_OUT
)braket
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
)brace
comma
l_int|0
comma
l_int|NULL
comma
(brace
)brace
)brace
comma
(brace
multiline_comment|/* PRE_ROUTING */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
r_sizeof
(paren
r_struct
id|ipt_standard_target
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* LOCAL_OUT */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
r_sizeof
(paren
r_struct
id|ipt_standard_target
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
)brace
comma
multiline_comment|/* ERROR */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_error
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
r_sizeof
(paren
r_struct
id|ipt_error_target
)paren
comma
id|IPT_ERROR_TARGET
)brace
)brace
comma
(brace
)brace
)brace
comma
l_string|&quot;ERROR&quot;
)brace
)brace
)brace
suffix:semicolon
DECL|variable|packet_mangler
r_static
r_struct
id|ipt_table
id|packet_mangler
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;mangle&quot;
comma
op_amp
id|initial_table.repl
comma
id|MANGLE_VALID_HOOKS
comma
id|RW_LOCK_UNLOCKED
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* The work comes in here from netfilter.c. */
r_static
r_int
r_int
DECL|function|ipt_hook
id|ipt_hook
c_func
(paren
r_int
r_int
id|hook
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
r_return
id|ipt_do_table
c_func
(paren
id|pskb
comma
id|hook
comma
id|in
comma
id|out
comma
op_amp
id|packet_mangler
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: change in oif may mean change in hh_len.  Check and realloc&n;   --RR */
r_static
r_int
DECL|function|route_me_harder
id|route_me_harder
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|rt_key
id|key
op_assign
(brace
id|dst
suffix:colon
id|iph-&gt;daddr
comma
id|src
suffix:colon
id|iph-&gt;saddr
comma
id|oif
suffix:colon
id|skb-&gt;sk
ques
c_cond
id|skb-&gt;sk-&gt;bound_dev_if
suffix:colon
l_int|0
comma
id|tos
suffix:colon
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
id|fwmark
suffix:colon
id|skb-&gt;nfmark
macro_line|#endif
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|key
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;route_me_harder: No more route.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Drop old route. */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|ipt_local_out_hook
id|ipt_local_out_hook
c_func
(paren
r_int
r_int
id|hook
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|u_int8_t
id|tos
suffix:semicolon
id|u_int32_t
id|saddr
comma
id|daddr
suffix:semicolon
r_int
r_int
id|nfmark
suffix:semicolon
multiline_comment|/* root is playing with raw sockets. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ipt_hook: happy cracking.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Save things which could affect route */
id|nfmark
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
suffix:semicolon
id|saddr
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
suffix:semicolon
id|daddr
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
suffix:semicolon
id|tos
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
suffix:semicolon
id|ret
op_assign
id|ipt_do_table
c_func
(paren
id|pskb
comma
id|hook
comma
id|in
comma
id|out
comma
op_amp
id|packet_mangler
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Reroute for ANY change. */
r_if
c_cond
(paren
id|ret
op_ne
id|NF_DROP
op_logical_and
id|ret
op_ne
id|NF_STOLEN
op_logical_and
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
op_ne
id|saddr
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
op_ne
id|daddr
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
op_ne
id|nfmark
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
op_ne
id|tos
)paren
)paren
r_return
id|route_me_harder
c_func
(paren
op_star
id|pskb
)paren
op_eq
l_int|0
ques
c_cond
id|ret
suffix:colon
id|NF_DROP
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ipt_ops
r_static
r_struct
id|nf_hook_ops
id|ipt_ops
(braket
)braket
op_assign
(brace
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|ipt_hook
comma
id|PF_INET
comma
id|NF_IP_PRE_ROUTING
comma
id|NF_IP_PRI_MANGLE
)brace
comma
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|ipt_local_out_hook
comma
id|PF_INET
comma
id|NF_IP_LOCAL_OUT
comma
id|NF_IP_PRI_MANGLE
)brace
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
r_int
id|ret
suffix:semicolon
multiline_comment|/* Register table */
id|ret
op_assign
id|ipt_register_table
c_func
(paren
op_amp
id|packet_mangler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* Register hooks */
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ipt_ops
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|cleanup_table
suffix:semicolon
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ipt_ops
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|cleanup_hook0
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|cleanup_hook0
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ipt_ops
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|cleanup_table
suffix:colon
id|ipt_unregister_table
c_func
(paren
op_amp
id|packet_mangler
)paren
suffix:semicolon
r_return
id|ret
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
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|ipt_ops
)paren
op_div
r_sizeof
(paren
r_struct
id|nf_hook_ops
)paren
suffix:semicolon
id|i
op_increment
)paren
id|nf_unregister_hook
c_func
(paren
op_amp
id|ipt_ops
(braket
id|i
)braket
)paren
suffix:semicolon
id|ipt_unregister_table
c_func
(paren
op_amp
id|packet_mangler
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
