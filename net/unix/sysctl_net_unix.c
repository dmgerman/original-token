multiline_comment|/*&n; * NET3:&t;Sysctl interface to net af_unix subsystem.&n; *&n; * Authors:&t;Mike Shaver.&n; *&n; *&t;&t;Added /proc/sys/net/unix directory entry (empty =) ).&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
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
