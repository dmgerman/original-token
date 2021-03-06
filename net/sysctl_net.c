multiline_comment|/* -*- linux-c -*-&n; * sysctl_net.c: sysctl interface to net subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net directories for each protocol family. [MS]&n; *&n; * $Log: sysctl_net.c,v $&n; * Revision 1.2  1996/05/08  20:24:40  shaver&n; * Added bits for NET_BRIDGE and the NET_IPV4_ARP stuff and&n; * NET_IPV4_IP_FORWARD.&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#ifdef CONFIG_INET
r_extern
id|ctl_table
id|ipv4_table
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IPX
r_extern
id|ctl_table
id|ipx_table
(braket
)braket
suffix:semicolon
macro_line|#endif
r_extern
id|ctl_table
id|core_table
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_UNIX
r_extern
id|ctl_table
id|unix_table
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET
r_extern
id|ctl_table
id|ether_table
(braket
)braket
comma
id|e802_table
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IPV6
r_extern
id|ctl_table
id|ipv6_table
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TR
r_extern
id|ctl_table
id|tr_table
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ECONET
r_extern
id|ctl_table
id|econet_table
(braket
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|net_table
id|ctl_table
id|net_table
(braket
)braket
op_assign
(brace
(brace
id|NET_CORE
comma
l_string|&quot;core&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|core_table
)brace
comma
macro_line|#ifdef CONFIG_UNIX
(brace
id|NET_UNIX
comma
l_string|&quot;unix&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|unix_table
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NET
(brace
id|NET_802
comma
l_string|&quot;802&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|e802_table
)brace
comma
(brace
id|NET_ETHER
comma
l_string|&quot;ethernet&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ether_table
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_INET
(brace
id|NET_IPV4
comma
l_string|&quot;ipv4&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipv4_table
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IPX
(brace
id|NET_IPX
comma
l_string|&quot;ipx&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipx_table
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IPV6
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
macro_line|#endif
macro_line|#ifdef CONFIG_TR
(brace
id|NET_TR
comma
l_string|&quot;token-ring&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|tr_table
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ECONET
(brace
id|NET_ECONET
comma
l_string|&quot;econet&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|econet_table
)brace
comma
macro_line|#endif
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
