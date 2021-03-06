multiline_comment|/* Compatibility framework for ipchains and ipfwadm support; designed&n;   to look as much like the 2.2 infrastructure as possible. */
r_struct
id|notifier_block
suffix:semicolon
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/compat_firewall.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_core.h&gt;
multiline_comment|/* Theoretically, we could one day use 2.4 helpers, but for now it&n;   just confuses depmod --RR */
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|variable|fwops
r_static
r_struct
id|firewall_ops
op_star
id|fwops
suffix:semicolon
multiline_comment|/* From ip_fw_compat_redir.c */
r_extern
r_int
r_int
id|do_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|dev
comma
id|u_int16_t
id|redirpt
)paren
suffix:semicolon
r_extern
r_void
id|check_for_redirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|check_for_unredirect
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* From ip_fw_compat_masq.c */
r_extern
r_int
r_int
id|do_masquerade
c_func
(paren
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
id|dev
)paren
suffix:semicolon
r_extern
r_int
r_int
id|check_for_masq_error
c_func
(paren
r_struct
id|sk_buff
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|check_for_demasq
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|masq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|masq_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* They call these; we do what they want. */
DECL|function|register_firewall
r_int
id|register_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
(brace
r_if
c_cond
(paren
id|pf
op_ne
id|PF_INET
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempt to register non-IP firewall module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fwops
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempt to register multiple firewall modules.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|fwops
op_assign
id|fw
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_firewall
r_int
id|unregister_firewall
c_func
(paren
r_int
id|pf
comma
r_struct
id|firewall_ops
op_star
id|fw
)paren
(brace
id|fwops
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|confirm_connection
id|confirm_connection
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
id|skb-&gt;nfct
)paren
(brace
r_struct
id|ip_conntrack
op_star
id|ct
op_assign
(paren
r_struct
id|ip_conntrack
op_star
)paren
id|skb-&gt;nfct-&gt;master
suffix:semicolon
multiline_comment|/* ctinfo is the index of the nfct inside the conntrack */
r_enum
id|ip_conntrack_info
id|ctinfo
op_assign
id|skb-&gt;nfct
op_minus
id|ct-&gt;infos
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ctinfo
op_eq
id|IP_CT_NEW
op_logical_or
id|ctinfo
op_eq
id|IP_CT_RELATED
)paren
op_logical_and
op_logical_neg
(paren
id|ct-&gt;status
op_amp
id|IPS_CONFIRMED
)paren
)paren
id|ip_conntrack_confirm
c_func
(paren
id|ct
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
r_int
DECL|function|fw_in
id|fw_in
c_func
(paren
r_int
r_int
id|hooknum
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
id|ret
op_assign
id|FW_BLOCK
suffix:semicolon
id|u_int16_t
id|redirpt
suffix:semicolon
multiline_comment|/* Assume worse case: any hook could change packet */
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfcache
op_or_assign
id|NFC_UNKNOWN
op_or
id|NFC_ALTERED
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
r_switch
c_cond
(paren
id|hooknum
)paren
(brace
r_case
id|NF_IP_PRE_ROUTING
suffix:colon
r_if
c_cond
(paren
id|fwops-&gt;fw_acct_in
)paren
id|fwops
op_member_access_from_pointer
id|fw_acct_in
c_func
(paren
id|fwops
comma
id|PF_INET
comma
(paren
r_struct
id|net_device
op_star
)paren
id|in
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
comma
op_amp
id|redirpt
comma
id|pskb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
)paren
(brace
op_star
id|pskb
op_assign
id|ip_ct_gather_frags
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|pskb
)paren
r_return
id|NF_STOLEN
suffix:semicolon
)brace
id|ret
op_assign
id|fwops
op_member_access_from_pointer
id|fw_input
c_func
(paren
id|fwops
comma
id|PF_INET
comma
(paren
r_struct
id|net_device
op_star
)paren
id|in
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
comma
op_amp
id|redirpt
comma
id|pskb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_IP_FORWARD
suffix:colon
multiline_comment|/* Connection will only be set if it was&n;                   demasqueraded: if so, skip forward chain. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfct
)paren
id|ret
op_assign
id|FW_ACCEPT
suffix:semicolon
r_else
id|ret
op_assign
id|fwops
op_member_access_from_pointer
id|fw_forward
c_func
(paren
id|fwops
comma
id|PF_INET
comma
(paren
r_struct
id|net_device
op_star
)paren
id|out
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
comma
op_amp
id|redirpt
comma
id|pskb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_IP_POST_ROUTING
suffix:colon
id|ret
op_assign
id|fwops
op_member_access_from_pointer
id|fw_output
c_func
(paren
id|fwops
comma
id|PF_INET
comma
(paren
r_struct
id|net_device
op_star
)paren
id|out
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
comma
op_amp
id|redirpt
comma
id|pskb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|FW_ACCEPT
op_logical_or
id|ret
op_eq
id|FW_SKIP
)paren
(brace
r_if
c_cond
(paren
id|fwops-&gt;fw_acct_out
)paren
id|fwops
op_member_access_from_pointer
id|fw_acct_out
c_func
(paren
id|fwops
comma
id|PF_INET
comma
(paren
r_struct
id|net_device
op_star
)paren
id|in
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.raw
comma
op_amp
id|redirpt
comma
id|pskb
)paren
suffix:semicolon
id|confirm_connection
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
id|FW_REJECT
suffix:colon
(brace
multiline_comment|/* Alexey says:&n;&t;&t; *&n;&t;&t; * Generally, routing is THE FIRST thing to make, when&n;&t;&t; * packet enters IP stack. Before packet is routed you&n;&t;&t; * cannot call any service routines from IP stack.  */
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
op_ne
l_int|NULL
op_logical_or
id|ip_route_input
c_func
(paren
op_star
id|pskb
comma
id|iph-&gt;daddr
comma
id|iph-&gt;saddr
comma
id|iph-&gt;tos
comma
(paren
r_struct
id|net_device
op_star
)paren
id|in
)paren
op_eq
l_int|0
)paren
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PORT_UNREACH
comma
l_int|0
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
r_case
id|FW_ACCEPT
suffix:colon
r_case
id|FW_SKIP
suffix:colon
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
)paren
(brace
id|check_for_demasq
c_func
(paren
id|pskb
)paren
suffix:semicolon
id|check_for_redirect
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
)paren
(brace
id|check_for_unredirect
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
multiline_comment|/* Handle ICMP errors from client here */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
op_logical_and
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfct
)paren
id|check_for_masq_error
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
r_case
id|FW_MASQUERADE
suffix:colon
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_FORWARD
)paren
r_return
id|do_masquerade
c_func
(paren
id|pskb
comma
id|out
)paren
suffix:semicolon
r_else
r_return
id|NF_ACCEPT
suffix:semicolon
r_case
id|FW_REDIRECT
suffix:colon
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
)paren
r_return
id|do_redirect
c_func
(paren
op_star
id|pskb
comma
id|in
comma
id|redirpt
)paren
suffix:semicolon
r_else
r_return
id|NF_ACCEPT
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* FW_BLOCK */
r_return
id|NF_DROP
suffix:semicolon
)brace
)brace
DECL|function|fw_confirm
r_static
r_int
r_int
id|fw_confirm
c_func
(paren
r_int
r_int
id|hooknum
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
id|confirm_connection
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_extern
r_int
id|ip_fw_ctl
c_func
(paren
r_int
id|optval
comma
r_void
op_star
id|user
comma
r_int
r_int
id|len
)paren
suffix:semicolon
DECL|function|sock_fn
r_static
r_int
id|sock_fn
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|optval
comma
r_void
op_star
id|user
comma
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
op_minus
id|ip_fw_ctl
c_func
(paren
id|optval
comma
id|user
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|preroute_ops
r_static
r_struct
id|nf_hook_ops
id|preroute_ops
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|fw_in
comma
id|PF_INET
comma
id|NF_IP_PRE_ROUTING
comma
id|NF_IP_PRI_FILTER
)brace
suffix:semicolon
DECL|variable|postroute_ops
r_static
r_struct
id|nf_hook_ops
id|postroute_ops
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|fw_in
comma
id|PF_INET
comma
id|NF_IP_POST_ROUTING
comma
id|NF_IP_PRI_FILTER
)brace
suffix:semicolon
DECL|variable|forward_ops
r_static
r_struct
id|nf_hook_ops
id|forward_ops
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|fw_in
comma
id|PF_INET
comma
id|NF_IP_FORWARD
comma
id|NF_IP_PRI_FILTER
)brace
suffix:semicolon
DECL|variable|local_in_ops
r_static
r_struct
id|nf_hook_ops
id|local_in_ops
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|fw_confirm
comma
id|PF_INET
comma
id|NF_IP_LOCAL_IN
comma
id|NF_IP_PRI_LAST
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|sock_ops
r_static
r_struct
id|nf_sockopt_ops
id|sock_ops
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|PF_INET
comma
l_int|64
comma
l_int|64
op_plus
l_int|1024
op_plus
l_int|1
comma
op_amp
id|sock_fn
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_extern
r_int
id|ipfw_init_or_cleanup
c_func
(paren
r_int
id|init
)paren
suffix:semicolon
DECL|function|init_or_cleanup
r_static
r_int
id|init_or_cleanup
c_func
(paren
r_int
id|init
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init
)paren
r_goto
id|cleanup
suffix:semicolon
id|ret
op_assign
id|nf_register_sockopt
c_func
(paren
op_amp
id|sock_ops
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
id|cleanup_nothing
suffix:semicolon
id|ret
op_assign
id|ipfw_init_or_cleanup
c_func
(paren
l_int|1
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
id|cleanup_sockopt
suffix:semicolon
id|ret
op_assign
id|masq_init
c_func
(paren
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
id|cleanup_ipfw
suffix:semicolon
id|nf_register_hook
c_func
(paren
op_amp
id|preroute_ops
)paren
suffix:semicolon
id|nf_register_hook
c_func
(paren
op_amp
id|postroute_ops
)paren
suffix:semicolon
id|nf_register_hook
c_func
(paren
op_amp
id|forward_ops
)paren
suffix:semicolon
id|nf_register_hook
c_func
(paren
op_amp
id|local_in_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|cleanup
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|preroute_ops
)paren
suffix:semicolon
id|nf_unregister_hook
c_func
(paren
op_amp
id|postroute_ops
)paren
suffix:semicolon
id|nf_unregister_hook
c_func
(paren
op_amp
id|forward_ops
)paren
suffix:semicolon
id|nf_unregister_hook
c_func
(paren
op_amp
id|local_in_ops
)paren
suffix:semicolon
id|masq_cleanup
c_func
(paren
)paren
suffix:semicolon
id|cleanup_ipfw
suffix:colon
id|ipfw_init_or_cleanup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|cleanup_sockopt
suffix:colon
id|nf_unregister_sockopt
c_func
(paren
op_amp
id|sock_ops
)paren
suffix:semicolon
id|cleanup_nothing
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
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
id|init_or_cleanup
c_func
(paren
l_int|1
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
id|init_or_cleanup
c_func
(paren
l_int|0
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
