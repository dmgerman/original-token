multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_unix.c: sysctl interface to net af_unix subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/unix directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|unix_table
id|ctl_table
id|unix_table
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
