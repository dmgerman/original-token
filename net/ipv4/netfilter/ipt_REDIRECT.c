multiline_comment|/* Redirect.  Simple mapping which alters dst to a local IP address. */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* FIXME: Take multiple ranges --RR */
r_static
r_int
DECL|function|redirect_check
id|redirect_check
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
l_string|&quot;redirect_check: bad table `%s&squot;.&bslash;n&quot;
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
l_string|&quot;redirect_check: size %u.&bslash;n&quot;
comma
id|targinfosize
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
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;redirect_check: bad hooks %x.&bslash;n&quot;
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
l_string|&quot;redirect_check: bad MAP_IPS.&bslash;n&quot;
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
l_string|&quot;redirect_check: bad rangesize %u.&bslash;n&quot;
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
DECL|function|redirect_target
id|redirect_target
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
id|u_int32_t
id|newdst
suffix:semicolon
r_const
r_struct
id|ip_nat_multi_range
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
r_struct
id|ip_nat_multi_range
id|newrange
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
op_logical_or
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
)paren
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
multiline_comment|/* Local packets: make them go to loopback */
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
)paren
id|newdst
op_assign
id|htonl
c_func
(paren
l_int|0x7F000001
)paren
suffix:semicolon
r_else
multiline_comment|/* Grab first address on interface. */
id|newdst
op_assign
(paren
(paren
(paren
r_struct
id|in_device
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev-&gt;ip_ptr
)paren
op_member_access_from_pointer
id|ifa_list-&gt;ifa_local
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
id|newdst
comma
id|newdst
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
DECL|variable|redirect_reg
r_static
r_struct
id|ipt_target
id|redirect_reg
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;REDIRECT&quot;
comma
id|redirect_target
comma
id|redirect_check
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
id|ipt_register_target
c_func
(paren
op_amp
id|redirect_reg
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|redirect_reg
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
