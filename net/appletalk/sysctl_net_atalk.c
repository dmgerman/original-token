multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_atalk.c: sysctl interface to net AppleTalk subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/atalk directory entry (empty =) ). [MS]&n; * Dynamic registration, added aarp entries. (5/30/97 Chris Horn)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
r_extern
r_int
id|sysctl_aarp_expiry_time
suffix:semicolon
r_extern
r_int
id|sysctl_aarp_tick_time
suffix:semicolon
r_extern
r_int
id|sysctl_aarp_retransmit_limit
suffix:semicolon
r_extern
r_int
id|sysctl_aarp_resolve_time
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|atalk_table
r_static
id|ctl_table
id|atalk_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ATALK_AARP_EXPIRY_TIME
comma
l_string|&quot;aarp-expiry-time&quot;
comma
op_amp
id|sysctl_aarp_expiry_time
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
id|proc_dointvec_jiffies
)brace
comma
(brace
id|NET_ATALK_AARP_TICK_TIME
comma
l_string|&quot;aarp-tick-time&quot;
comma
op_amp
id|sysctl_aarp_tick_time
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
id|proc_dointvec_jiffies
)brace
comma
(brace
id|NET_ATALK_AARP_RETRANSMIT_LIMIT
comma
l_string|&quot;aarp-retransmit-limit&quot;
comma
op_amp
id|sysctl_aarp_retransmit_limit
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
id|NET_ATALK_AARP_RESOLVE_TIME
comma
l_string|&quot;aarp-resolve-time&quot;
comma
op_amp
id|sysctl_aarp_resolve_time
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
id|proc_dointvec_jiffies
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|atalk_dir_table
r_static
id|ctl_table
id|atalk_dir_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ATALK
comma
l_string|&quot;appletalk&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|atalk_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|atalk_root_table
r_static
id|ctl_table
id|atalk_root_table
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
id|atalk_dir_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|atalk_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|atalk_table_header
suffix:semicolon
DECL|function|atalk_register_sysctl
r_void
id|atalk_register_sysctl
c_func
(paren
r_void
)paren
(brace
id|atalk_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|atalk_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|atalk_unregister_sysctl
r_void
id|atalk_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|atalk_table_header
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|atalk_register_sysctl
r_void
id|atalk_register_sysctl
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|atalk_unregister_sysctl
r_void
id|atalk_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
