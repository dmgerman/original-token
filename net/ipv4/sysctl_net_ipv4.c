multiline_comment|/*&n; * sysctl_net_ipv4.c: sysctl interface to net IPV4 subsystem.&n; *&n; * $Id: sysctl_net_ipv4.c,v 1.47 2000/10/19 15:51:02 davem Exp $&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
multiline_comment|/* From af_inet.c */
r_extern
r_int
id|sysctl_ip_nonlocal_bind
suffix:semicolon
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_echo_ignore_all
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_echo_ignore_broadcasts
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_ignore_bogus_error_responses
suffix:semicolon
multiline_comment|/* From ip_fragment.c */
r_extern
r_int
id|sysctl_ipfrag_low_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ipfrag_high_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ipfrag_time
suffix:semicolon
multiline_comment|/* From ip_output.c */
r_extern
r_int
id|sysctl_ip_dynaddr
suffix:semicolon
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_destunreach_time
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_timeexceed_time
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_paramprob_time
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_echoreply_time
suffix:semicolon
multiline_comment|/* From igmp.c */
r_extern
r_int
id|sysctl_igmp_max_memberships
suffix:semicolon
multiline_comment|/* From inetpeer.c */
r_extern
r_int
id|inet_peer_threshold
suffix:semicolon
r_extern
r_int
id|inet_peer_minttl
suffix:semicolon
r_extern
r_int
id|inet_peer_maxttl
suffix:semicolon
r_extern
r_int
id|inet_peer_gc_mintime
suffix:semicolon
r_extern
r_int
id|inet_peer_gc_maxtime
suffix:semicolon
DECL|variable|tcp_retr1_max
r_static
r_int
id|tcp_retr1_max
op_assign
l_int|255
suffix:semicolon
DECL|variable|ip_local_port_range_min
r_static
r_int
id|ip_local_port_range_min
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|ip_local_port_range_max
r_static
r_int
id|ip_local_port_range_max
(braket
)braket
op_assign
(brace
l_int|65535
comma
l_int|65535
)brace
suffix:semicolon
DECL|variable|ipv4_config
r_struct
id|ipv4_config
id|ipv4_config
suffix:semicolon
r_extern
id|ctl_table
id|ipv4_route_table
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
r_static
DECL|function|ipv4_sysctl_forward
r_int
id|ipv4_sysctl_forward
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|val
op_assign
id|ipv4_devconf.forwarding
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|proc_dointvec
c_func
(paren
id|ctl
comma
id|write
comma
id|filp
comma
id|buffer
comma
id|lenp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
op_logical_and
id|ipv4_devconf.forwarding
op_ne
id|val
)paren
id|inet_forward_change
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ipv4_sysctl_forward_strategy
r_static
r_int
id|ipv4_sysctl_forward_strategy
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
(brace
r_int
r_new
suffix:semicolon
r_if
c_cond
(paren
id|newlen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
r_new
comma
(paren
r_int
op_star
)paren
id|newval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
id|ipv4_devconf.forwarding
)paren
id|inet_forward_change
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* caller does change again and handles handles oldval */
)brace
DECL|variable|ipv4_table
id|ctl_table
id|ipv4_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPV4_TCP_TIMESTAMPS
comma
l_string|&quot;tcp_timestamps&quot;
comma
op_amp
id|sysctl_tcp_timestamps
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_WINDOW_SCALING
comma
l_string|&quot;tcp_window_scaling&quot;
comma
op_amp
id|sysctl_tcp_window_scaling
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_SACK
comma
l_string|&quot;tcp_sack&quot;
comma
op_amp
id|sysctl_tcp_sack
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_RETRANS_COLLAPSE
comma
l_string|&quot;tcp_retrans_collapse&quot;
comma
op_amp
id|sysctl_tcp_retrans_collapse
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_FORWARD
comma
l_string|&quot;ip_forward&quot;
comma
op_amp
id|ipv4_devconf.forwarding
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
id|ipv4_sysctl_forward
comma
op_amp
id|ipv4_sysctl_forward_strategy
)brace
comma
(brace
id|NET_IPV4_DEFAULT_TTL
comma
l_string|&quot;ip_default_ttl&quot;
comma
op_amp
id|sysctl_ip_default_ttl
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_AUTOCONFIG
comma
l_string|&quot;ip_autoconfig&quot;
comma
op_amp
id|ipv4_config.autoconfig
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_NO_PMTU_DISC
comma
l_string|&quot;ip_no_pmtu_disc&quot;
comma
op_amp
id|ipv4_config.no_pmtu_disc
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_NONLOCAL_BIND
comma
l_string|&quot;ip_nonlocal_bind&quot;
comma
op_amp
id|sysctl_ip_nonlocal_bind
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_SYN_RETRIES
comma
l_string|&quot;tcp_syn_retries&quot;
comma
op_amp
id|sysctl_tcp_syn_retries
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_SYNACK_RETRIES
comma
l_string|&quot;tcp_synack_retries&quot;
comma
op_amp
id|sysctl_tcp_synack_retries
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_MAX_ORPHANS
comma
l_string|&quot;tcp_max_orphans&quot;
comma
op_amp
id|sysctl_tcp_max_orphans
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_MAX_TW_BUCKETS
comma
l_string|&quot;tcp_max_tw_buckets&quot;
comma
op_amp
id|sysctl_tcp_max_tw_buckets
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_IPFRAG_HIGH_THRESH
comma
l_string|&quot;ipfrag_high_thresh&quot;
comma
op_amp
id|sysctl_ipfrag_high_thresh
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_IPFRAG_LOW_THRESH
comma
l_string|&quot;ipfrag_low_thresh&quot;
comma
op_amp
id|sysctl_ipfrag_low_thresh
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_DYNADDR
comma
l_string|&quot;ip_dynaddr&quot;
comma
op_amp
id|sysctl_ip_dynaddr
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_IPFRAG_TIME
comma
l_string|&quot;ipfrag_time&quot;
comma
op_amp
id|sysctl_ipfrag_time
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_TCP_KEEPALIVE_TIME
comma
l_string|&quot;tcp_keepalive_time&quot;
comma
op_amp
id|sysctl_tcp_keepalive_time
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_TCP_KEEPALIVE_PROBES
comma
l_string|&quot;tcp_keepalive_probes&quot;
comma
op_amp
id|sysctl_tcp_keepalive_probes
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_KEEPALIVE_INTVL
comma
l_string|&quot;tcp_keepalive_intvl&quot;
comma
op_amp
id|sysctl_tcp_keepalive_intvl
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_TCP_RETRIES1
comma
l_string|&quot;tcp_retries1&quot;
comma
op_amp
id|sysctl_tcp_retries1
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
l_int|NULL
comma
op_amp
id|tcp_retr1_max
)brace
comma
(brace
id|NET_IPV4_TCP_RETRIES2
comma
l_string|&quot;tcp_retries2&quot;
comma
op_amp
id|sysctl_tcp_retries2
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_TCP_FIN_TIMEOUT
comma
l_string|&quot;tcp_fin_timeout&quot;
comma
op_amp
id|sysctl_tcp_fin_timeout
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
macro_line|#ifdef CONFIG_SYN_COOKIES
(brace
id|NET_TCP_SYNCOOKIES
comma
l_string|&quot;tcp_syncookies&quot;
comma
op_amp
id|sysctl_tcp_syncookies
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
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
id|NET_TCP_TW_RECYCLE
comma
l_string|&quot;tcp_tw_recycle&quot;
comma
op_amp
id|sysctl_tcp_tw_recycle
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_ABORT_ON_OVERFLOW
comma
l_string|&quot;tcp_abort_on_overflow&quot;
comma
op_amp
id|sysctl_tcp_abort_on_overflow
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_STDURG
comma
l_string|&quot;tcp_stdurg&quot;
comma
op_amp
id|sysctl_tcp_stdurg
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_RFC1337
comma
l_string|&quot;tcp_rfc1337&quot;
comma
op_amp
id|sysctl_tcp_rfc1337
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_MAX_SYN_BACKLOG
comma
l_string|&quot;tcp_max_syn_backlog&quot;
comma
op_amp
id|sysctl_max_syn_backlog
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_LOCAL_PORT_RANGE
comma
l_string|&quot;ip_local_port_range&quot;
comma
op_amp
id|sysctl_local_port_range
comma
r_sizeof
(paren
id|sysctl_local_port_range
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
id|ip_local_port_range_min
comma
id|ip_local_port_range_max
)brace
comma
(brace
id|NET_IPV4_ICMP_ECHO_IGNORE_ALL
comma
l_string|&quot;icmp_echo_ignore_all&quot;
comma
op_amp
id|sysctl_icmp_echo_ignore_all
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS
comma
l_string|&quot;icmp_echo_ignore_broadcasts&quot;
comma
op_amp
id|sysctl_icmp_echo_ignore_broadcasts
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES
comma
l_string|&quot;icmp_ignore_bogus_error_responses&quot;
comma
op_amp
id|sysctl_icmp_ignore_bogus_error_responses
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_DESTUNREACH_RATE
comma
l_string|&quot;icmp_destunreach_rate&quot;
comma
op_amp
id|sysctl_icmp_destunreach_time
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_TIMEEXCEED_RATE
comma
l_string|&quot;icmp_timeexceed_rate&quot;
comma
op_amp
id|sysctl_icmp_timeexceed_time
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_PARAMPROB_RATE
comma
l_string|&quot;icmp_paramprob_rate&quot;
comma
op_amp
id|sysctl_icmp_paramprob_time
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ICMP_ECHOREPLY_RATE
comma
l_string|&quot;icmp_echoreply_rate&quot;
comma
op_amp
id|sysctl_icmp_echoreply_time
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_ROUTE
comma
l_string|&quot;route&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ipv4_route_table
)brace
comma
macro_line|#ifdef CONFIG_IP_MULTICAST
(brace
id|NET_IPV4_IGMP_MAX_MEMBERSHIPS
comma
l_string|&quot;igmp_max_memberships&quot;
comma
op_amp
id|sysctl_igmp_max_memberships
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
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
id|NET_IPV4_INET_PEER_THRESHOLD
comma
l_string|&quot;inet_peer_threshold&quot;
comma
op_amp
id|inet_peer_threshold
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
id|proc_dointvec
)brace
comma
(brace
id|NET_IPV4_INET_PEER_MINTTL
comma
l_string|&quot;inet_peer_minttl&quot;
comma
op_amp
id|inet_peer_minttl
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_INET_PEER_MAXTTL
comma
l_string|&quot;inet_peer_maxttl&quot;
comma
op_amp
id|inet_peer_maxttl
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_INET_PEER_GC_MINTIME
comma
l_string|&quot;inet_peer_gc_mintime&quot;
comma
op_amp
id|inet_peer_gc_mintime
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_IPV4_INET_PEER_GC_MAXTIME
comma
l_string|&quot;inet_peer_gc_maxtime&quot;
comma
op_amp
id|inet_peer_gc_maxtime
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
id|proc_dointvec_jiffies
comma
op_amp
id|sysctl_jiffies
)brace
comma
(brace
id|NET_TCP_ORPHAN_RETRIES
comma
l_string|&quot;tcp_orphan_retries&quot;
comma
op_amp
id|sysctl_tcp_orphan_retries
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_FACK
comma
l_string|&quot;tcp_fack&quot;
comma
op_amp
id|sysctl_tcp_fack
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_REORDERING
comma
l_string|&quot;tcp_reordering&quot;
comma
op_amp
id|sysctl_tcp_reordering
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
id|proc_dointvec
)brace
comma
macro_line|#ifdef CONFIG_INET_ECN
(brace
id|NET_TCP_ECN
comma
l_string|&quot;tcp_ecn&quot;
comma
op_amp
id|sysctl_tcp_ecn
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
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
id|NET_TCP_DSACK
comma
l_string|&quot;tcp_dsack&quot;
comma
op_amp
id|sysctl_tcp_dsack
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_MEM
comma
l_string|&quot;tcp_mem&quot;
comma
op_amp
id|sysctl_tcp_mem
comma
r_sizeof
(paren
id|sysctl_tcp_mem
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_WMEM
comma
l_string|&quot;tcp_wmem&quot;
comma
op_amp
id|sysctl_tcp_wmem
comma
r_sizeof
(paren
id|sysctl_tcp_wmem
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_RMEM
comma
l_string|&quot;tcp_rmem&quot;
comma
op_amp
id|sysctl_tcp_rmem
comma
r_sizeof
(paren
id|sysctl_tcp_rmem
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_APP_WIN
comma
l_string|&quot;tcp_app_win&quot;
comma
op_amp
id|sysctl_tcp_app_win
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
id|proc_dointvec
)brace
comma
(brace
id|NET_TCP_ADV_WIN_SCALE
comma
l_string|&quot;tcp_adv_win_scale&quot;
comma
op_amp
id|sysctl_tcp_adv_win_scale
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
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
eof
