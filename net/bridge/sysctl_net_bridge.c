multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_bridge.c: sysctl interface to net bridge subsystem.&n; *&n; * Begun June 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/bridge directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|bridge_table
id|ctl_table
id|bridge_table
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
