multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_rose.c: sysctl interface to net Rose subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/rose directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;net/rose.h&gt;
DECL|variable|min_timer
r_static
r_int
id|min_timer
(braket
)braket
op_assign
(brace
l_int|1
op_star
id|PR_SLOWHZ
)brace
suffix:semicolon
DECL|variable|max_timer
r_static
r_int
id|max_timer
(braket
)braket
op_assign
(brace
l_int|300
op_star
id|PR_SLOWHZ
)brace
suffix:semicolon
DECL|variable|min_idle
r_static
r_int
id|min_idle
(braket
)braket
op_assign
(brace
l_int|0
op_star
id|PR_SLOWHZ
)brace
suffix:semicolon
DECL|variable|max_idle
r_static
r_int
id|max_idle
(braket
)braket
op_assign
(brace
l_int|65535
op_star
id|PR_SLOWHZ
)brace
suffix:semicolon
DECL|variable|min_route
r_static
r_int
id|min_route
(braket
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|max_route
r_static
r_int
id|max_route
(braket
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|rose_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|rose_table_header
suffix:semicolon
DECL|variable|rose_table
r_static
id|ctl_table
id|rose_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ROSE_RESTART_REQUEST_TIMEOUT
comma
l_string|&quot;restart_request_timeout&quot;
comma
op_amp
id|sysctl_rose_restart_request_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_CALL_REQUEST_TIMEOUT
comma
l_string|&quot;call_request_timeout&quot;
comma
op_amp
id|sysctl_rose_call_request_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_RESET_REQUEST_TIMEOUT
comma
l_string|&quot;reset_request_timeout&quot;
comma
op_amp
id|sysctl_rose_reset_request_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_CLEAR_REQUEST_TIMEOUT
comma
l_string|&quot;clear_request_timeout&quot;
comma
op_amp
id|sysctl_rose_clear_request_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_NO_ACTIVITY_TIMEOUT
comma
l_string|&quot;no_activity_timeout&quot;
comma
op_amp
id|sysctl_rose_no_activity_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_idle
comma
op_amp
id|max_idle
)brace
comma
(brace
id|NET_ROSE_ACK_HOLD_BACK_TIMEOUT
comma
l_string|&quot;acknowledge_hold_back_timeout&quot;
comma
op_amp
id|sysctl_rose_ack_hold_back_timeout
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_ROUTING_CONTROL
comma
l_string|&quot;routing_control&quot;
comma
op_amp
id|sysctl_rose_routing_control
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
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_route
comma
op_amp
id|max_route
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|rose_dir_table
r_static
id|ctl_table
id|rose_dir_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ROSE
comma
l_string|&quot;rose&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|rose_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|rose_root_table
r_static
id|ctl_table
id|rose_root_table
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
id|rose_dir_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|rose_register_sysctl
r_void
id|rose_register_sysctl
c_func
(paren
r_void
)paren
(brace
id|rose_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|rose_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|rose_unregister_sysctl
r_void
id|rose_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|rose_table_header
)paren
suffix:semicolon
)brace
eof