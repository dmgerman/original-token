multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_core.c: sysctl interface to net core subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/core directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
r_extern
id|__u32
id|sysctl_wmem_max
suffix:semicolon
r_extern
id|__u32
id|sysctl_rmem_max
suffix:semicolon
r_extern
id|__u32
id|sysctl_wmem_default
suffix:semicolon
r_extern
id|__u32
id|sysctl_rmem_default
suffix:semicolon
DECL|variable|core_table
id|ctl_table
id|core_table
(braket
)braket
op_assign
(brace
(brace
id|NET_CORE_WMEM_MAX
comma
l_string|&quot;wmem_max&quot;
comma
op_amp
id|sysctl_wmem_max
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
id|NET_CORE_RMEM_MAX
comma
l_string|&quot;rmem_max&quot;
comma
op_amp
id|sysctl_rmem_max
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
id|NET_CORE_WMEM_DEFAULT
comma
l_string|&quot;wmem_default&quot;
comma
op_amp
id|sysctl_wmem_default
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
id|NET_CORE_RMEM_DEFAULT
comma
l_string|&quot;rmem_default&quot;
comma
op_amp
id|sysctl_rmem_default
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
)brace
suffix:semicolon
eof
