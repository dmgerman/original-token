multiline_comment|/*&n; *  linux/version.c&n; *&n; *  Copyright (C) 1992  Theodore Ts&squot;o&n; *&n; *  May be freely distributed as part of Linux.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &quot;./version.h&quot;
DECL|variable|system_utsname
r_struct
id|new_utsname
id|system_utsname
op_assign
(brace
id|UTS_SYSNAME
comma
id|UTS_NODENAME
comma
id|UTS_RELEASE
comma
id|UTS_VERSION
comma
id|UTS_MACHINE
comma
id|UTS_DOMAINNAME
)brace
suffix:semicolon
DECL|variable|linux_banner
r_char
op_star
id|linux_banner
op_assign
l_string|&quot;Linux version &quot;
id|UTS_RELEASE
l_string|&quot; (&quot;
id|LINUX_COMPILE_BY
l_string|&quot;@&quot;
id|LINUX_COMPILE_HOST
l_string|&quot;) (&quot;
id|LINUX_COMPILER
l_string|&quot;) &quot;
id|UTS_VERSION
l_string|&quot;&bslash;n&quot;
suffix:semicolon
eof
