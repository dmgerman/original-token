multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_ax25.c: sysctl interface to net AX.25 subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ax25 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
DECL|variable|min_ax25
r_static
r_int
id|min_ax25
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
op_star
id|PR_SLOWHZ
comma
l_int|1
op_star
id|PR_SLOWHZ
comma
l_int|0
op_star
id|PR_SLOWHZ
comma
l_int|0
op_star
id|PR_SLOWHZ
comma
l_int|1
comma
l_int|1
comma
l_int|0x00
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|max_ax25
r_static
r_int
id|max_ax25
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|7
comma
l_int|63
comma
l_int|30
op_star
id|PR_SLOWHZ
comma
l_int|20
op_star
id|PR_SLOWHZ
comma
l_int|3600
op_star
id|PR_SLOWHZ
comma
l_int|65535
op_star
id|PR_SLOWHZ
comma
l_int|31
comma
l_int|512
comma
l_int|0x03
comma
l_int|20
)brace
suffix:semicolon
DECL|variable|ax25_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|ax25_table_header
suffix:semicolon
DECL|variable|ax25_table
r_static
id|ctl_table
id|ax25_table
(braket
id|AX25_MAX_DEVICES
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|ax25_dir_table
r_static
id|ctl_table
id|ax25_dir_table
(braket
)braket
op_assign
(brace
(brace
id|NET_AX25
comma
l_string|&quot;ax25&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ax25_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ax25_root_table
r_static
id|ctl_table
id|ax25_root_table
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
id|ax25_dir_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|ax25_register_sysctl
r_void
id|ax25_register_sysctl
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
id|memset
c_func
(paren
id|ax25_table
comma
l_int|0x00
comma
(paren
id|AX25_MAX_DEVICES
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
id|ctl_table
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|AX25_MAX_DEVICES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ax25_device
(braket
id|i
)braket
dot
id|dev
op_ne
l_int|NULL
)paren
(brace
id|ax25_table
(braket
id|n
)braket
dot
id|ctl_name
op_assign
id|n
op_plus
l_int|1
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|procname
op_assign
id|ax25_device
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|data
op_assign
op_amp
id|ax25_device
(braket
id|i
)braket
dot
id|values
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|maxlen
op_assign
id|AX25_MAX_VALUES
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|mode
op_assign
l_int|0644
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|child
op_assign
l_int|NULL
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|de
op_assign
l_int|NULL
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|extra1
op_assign
op_amp
id|min_ax25
suffix:semicolon
id|ax25_table
(braket
id|n
)braket
dot
id|extra2
op_assign
op_amp
id|max_ax25
suffix:semicolon
id|n
op_increment
suffix:semicolon
)brace
)brace
id|ax25_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|ax25_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ax25_unregister_sysctl
r_void
id|ax25_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|ax25_table_header
)paren
suffix:semicolon
)brace
eof
