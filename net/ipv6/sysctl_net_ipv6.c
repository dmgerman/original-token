multiline_comment|/*&n; * sysctl_net_ipv6.c: sysctl interface to net IPV6 subsystem.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
DECL|variable|ipv6_hop_limit
r_int
id|ipv6_hop_limit
op_assign
id|IPV6_DEFAULT_HOPLIMIT
suffix:semicolon
DECL|function|ipv6_sysctl_forwarding
r_int
id|ipv6_sysctl_forwarding
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|val
op_assign
id|ipv6_forwarding
suffix:semicolon
r_int
id|retv
suffix:semicolon
id|retv
op_assign
id|proc_dointvec
c_func
(paren
id|ctl
comma
id|write
comma
id|filp
comma
id|buffer
comma
id|lenp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
)paren
(brace
r_if
c_cond
(paren
id|ipv6_forwarding
op_logical_and
id|val
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sysctl: IPv6 forwarding enabled&bslash;n&quot;
)paren
suffix:semicolon
id|ndisc_forwarding_on
c_func
(paren
)paren
suffix:semicolon
id|addrconf_forwarding_on
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_forwarding
op_eq
l_int|0
op_logical_and
id|val
)paren
(brace
id|ndisc_forwarding_off
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|retv
suffix:semicolon
)brace
DECL|variable|ipv6_table
id|ctl_table
id|ipv6_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPV6_FORWARDING
comma
l_string|&quot;ipv6_forwarding&quot;
comma
op_amp
id|ipv6_forwarding
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|ipv6_sysctl_forwarding
)brace
comma
(brace
id|NET_IPV6_HOPLIMIT
comma
l_string|&quot;ipv6_hop_limit&quot;
comma
op_amp
id|ipv6_hop_limit
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|ipv6_sysctl_header
r_static
r_struct
id|ctl_table_header
op_star
id|ipv6_sysctl_header
suffix:semicolon
DECL|variable|ipv6_root_table
r_static
r_struct
id|ctl_table
id|ipv6_root_table
(braket
)braket
suffix:semicolon
DECL|variable|ipv6_net_table
r_static
r_struct
id|ctl_table
id|ipv6_net_table
(braket
)braket
suffix:semicolon
DECL|variable|ipv6_root_table
id|ctl_table
id|ipv6_root_table
(braket
)braket
op_assign
(brace
(brace
id|CTL_NET
comma
l_string|&quot;net&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipv6_net_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ipv6_net_table
id|ctl_table
id|ipv6_net_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPV6
comma
l_string|&quot;ipv6&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipv6_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|ipv6_sysctl_register
r_void
id|ipv6_sysctl_register
c_func
(paren
r_void
)paren
(brace
id|ipv6_sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|ipv6_root_table
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ipv6_sysctl_unregister
r_void
id|ipv6_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|ipv6_sysctl_header
)paren
suffix:semicolon
)brace
macro_line|#endif
eof