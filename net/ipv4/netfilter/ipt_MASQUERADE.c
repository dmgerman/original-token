multiline_comment|/* Masquerade.  Simple mapping which alters range to a local IP address&n;   (depending on route). */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* Lock protects masq region inside conntrack */
r_static
id|DECLARE_RWLOCK
c_func
(paren
id|masq_lock
)paren
suffix:semicolon
multiline_comment|/* FIXME: Multiple targets. --RR */
r_static
r_int
DECL|function|masquerade_check
id|masquerade_check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ip_nat_multi_range
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;nat&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;masquerade_check: bad table `%s&squot;.&bslash;n&quot;
comma
id|table
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|mr
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;masquerade_check: size %u != %u.&bslash;n&quot;
comma
id|targinfosize
comma
r_sizeof
(paren
op_star
id|mr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hook_mask
op_amp
op_complement
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;masquerade_check: bad hooks %x.&bslash;n&quot;
comma
id|hook_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|flags
op_amp
id|IP_NAT_RANGE_MAP_IPS
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;masquerade_check: bad MAP_IPS.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mr-&gt;rangesize
op_ne
l_int|1
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;masquerade_check: bad rangesize %u.&bslash;n&quot;
comma
id|mr-&gt;rangesize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|masquerade_target
id|masquerade_target
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
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
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_struct
id|ip_conntrack
op_star
id|ct
suffix:semicolon
r_enum
id|ip_conntrack_info
id|ctinfo
suffix:semicolon
r_const
r_struct
id|ip_nat_multi_range
op_star
id|mr
suffix:semicolon
r_struct
id|ip_nat_multi_range
id|newrange
suffix:semicolon
id|u_int32_t
id|newsrc
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
)paren
suffix:semicolon
multiline_comment|/* FIXME: For the moment, don&squot;t do local packets, breaks&n;&t;   testsuite for 2.3.49 --RR */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
id|ct
op_assign
id|ip_conntrack_get
c_func
(paren
op_star
id|pskb
comma
op_amp
id|ctinfo
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|ct
op_logical_and
(paren
id|ctinfo
op_eq
id|IP_CT_NEW
op_logical_or
id|ctinfo
op_eq
id|IP_CT_RELATED
)paren
)paren
suffix:semicolon
id|mr
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
comma
l_int|0
comma
id|RT_TOS
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
id|out-&gt;ifindex
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Shouldn&squot;t happen */
id|printk
c_func
(paren
l_string|&quot;MASQUERADE: No route: Rusty&squot;s brain broke!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|newsrc
op_assign
id|rt-&gt;rt_src
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;newsrc = %u.%u.%u.%u&bslash;n&quot;
comma
id|IP_PARTS
c_func
(paren
id|newsrc
)paren
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|masq_lock
)paren
suffix:semicolon
id|ct-&gt;nat.masq_index
op_assign
id|out-&gt;ifindex
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|masq_lock
)paren
suffix:semicolon
multiline_comment|/* Transfer from original range. */
id|newrange
op_assign
(paren
(paren
r_struct
id|ip_nat_multi_range
)paren
(brace
l_int|1
comma
(brace
(brace
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|flags
op_or
id|IP_NAT_RANGE_MAP_IPS
comma
id|newsrc
comma
id|newsrc
comma
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|min
comma
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|max
)brace
)brace
)brace
)paren
suffix:semicolon
multiline_comment|/* Hand modified range to generic setup. */
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|newrange
comma
id|hooknum
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|device_cmp
id|device_cmp
c_func
(paren
r_const
r_struct
id|ip_conntrack
op_star
id|i
comma
r_void
op_star
id|ifindex
)paren
(brace
r_int
id|ret
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|masq_lock
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|i-&gt;nat.masq_index
op_eq
(paren
r_int
)paren
(paren
r_int
)paren
id|ifindex
)paren
suffix:semicolon
id|READ_UNLOCK
c_func
(paren
op_amp
id|masq_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|masq_device_event
r_int
id|masq_device_event
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_DOWN
)paren
(brace
multiline_comment|/* Device was downed.  Search entire table for&n;&t;&t;   conntracks which were associated with that device,&n;&t;&t;   and forget them. */
id|IP_NF_ASSERT
c_func
(paren
id|dev-&gt;ifindex
op_ne
l_int|0
)paren
suffix:semicolon
id|ip_ct_selective_cleanup
c_func
(paren
id|device_cmp
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|dev-&gt;ifindex
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|masq_dev_notifier
r_static
r_struct
id|notifier_block
id|masq_dev_notifier
op_assign
(brace
id|masq_device_event
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|masquerade
r_static
r_struct
id|ipt_target
id|masquerade
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;MASQUERADE&quot;
comma
id|masquerade_target
comma
id|masquerade_check
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
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ipt_register_target
c_func
(paren
op_amp
id|masquerade
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Register for device down reports */
id|register_netdevice_notifier
c_func
(paren
op_amp
id|masq_dev_notifier
)paren
suffix:semicolon
)brace
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|masquerade
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|masq_dev_notifier
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
