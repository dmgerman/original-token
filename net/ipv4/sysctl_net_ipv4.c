multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_ipv4.c: sysctl interface to net IPV4 subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|ipv4_table
id|ctl_table
id|ipv4_table
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
