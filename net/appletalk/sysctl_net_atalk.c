multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_atalk.c: sysctl interface to net Appletalk subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/atalk directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|atalk_table
id|ctl_table
id|atalk_table
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
