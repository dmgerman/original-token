multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_ax25.c: sysctl interface to net AX.25 subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ax25 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|ax25_table
id|ctl_table
id|ax25_table
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
