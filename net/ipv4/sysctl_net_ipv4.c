multiline_comment|/*&n; * sysctl_net_ipv4.c: sysctl interface to net IPV4 subsystem.&n; *&n; * $Id: sysctl_net_ipv4.c,v 1.23 1997/12/13 21:52:57 kuznet Exp $&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
multiline_comment|/*&n; *&t;TCP configuration parameters&n; */
DECL|macro|TCP_PMTU_DISC
mdefine_line|#define TCP_PMTU_DISC&t;0x00000001&t;/* perform PMTU discovery&t;  */
DECL|macro|TCP_CONG_AVOID
mdefine_line|#define TCP_CONG_AVOID&t;0x00000002&t;/* congestion avoidance algorithm */
DECL|macro|TCP_DELAY_ACKS
mdefine_line|#define TCP_DELAY_ACKS&t;0x00000003&t;/* delayed ack stategy&t;&t;  */
macro_line|#if 0
r_static
r_int
id|boolean_min
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|boolean_max
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_echo_ignore_all
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_echo_ignore_broadcasts
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
multiline_comment|/* From ip_masq.c */
r_extern
r_int
id|sysctl_ip_masq_debug
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_cong_avoidance
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_hoe_retransmits
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_sack
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_tsack
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_timestamps
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_window_scaling
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_keepalive_time
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_keepalive_probes
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_max_ka_probes
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_retries1
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_retries2
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_max_delay_acks
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_fin_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_syncookies
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_syn_retries
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_stdurg
suffix:semicolon
r_extern
r_int
id|sysctl_tcp_syn_taildrop
suffix:semicolon
r_extern
r_int
id|sysctl_max_syn_backlog
suffix:semicolon
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_sourcequench_time
suffix:semicolon
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
DECL|variable|tcp_retr1_max
r_int
id|tcp_retr1_max
op_assign
l_int|255
suffix:semicolon
r_extern
r_int
id|tcp_sysctl_congavoid
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
suffix:semicolon
DECL|variable|ipv4_config
r_struct
id|ipv4_config
id|ipv4_config
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|ipv4_def_router_config
r_struct
id|ipv4_config
id|ipv4_def_router_config
op_assign
(brace
l_int|0
comma
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
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|ipv4_def_host_config
r_struct
id|ipv4_config
id|ipv4_def_host_config
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
)brace
suffix:semicolon
r_static
DECL|function|ipv4_sysctl_forwarding
r_int
id|ipv4_sysctl_forwarding
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
id|IS_ROUTER
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
id|IS_ROUTER
op_ne
id|val
)paren
(brace
r_if
c_cond
(paren
id|IS_ROUTER
)paren
id|ipv4_config
op_assign
id|ipv4_def_router_config
suffix:semicolon
r_else
id|ipv4_config
op_assign
id|ipv4_def_host_config
suffix:semicolon
id|rt_cache_flush
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
DECL|function|ipv4_sysctl_rtcache_flush
r_int
id|ipv4_sysctl_rtcache_flush
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
r_if
c_cond
(paren
id|write
)paren
(brace
id|rt_cache_flush
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|ipv4_table
id|ctl_table
id|ipv4_table
(braket
)braket
op_assign
(brace
(brace
id|NET_IPV4_TCP_HOE_RETRANSMITS
comma
l_string|&quot;tcp_hoe_retransmits&quot;
comma
op_amp
id|sysctl_tcp_hoe_retransmits
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
id|NET_IPV4_TCP_TSACK
comma
l_string|&quot;tcp_tsack&quot;
comma
op_amp
id|sysctl_tcp_tsack
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
id|NET_IPV4_TCP_VEGAS_CONG_AVOID
comma
l_string|&quot;tcp_vegas_cong_avoid&quot;
comma
op_amp
id|sysctl_tcp_cong_avoidance
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
id|tcp_sysctl_congavoid
)brace
comma
(brace
id|NET_IPV4_FORWARDING
comma
l_string|&quot;ip_forwarding&quot;
comma
op_amp
id|ip_statistics.IpForwarding
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
id|ipv4_sysctl_forwarding
)brace
comma
(brace
id|NET_IPV4_DEFAULT_TTL
comma
l_string|&quot;ip_default_ttl&quot;
comma
op_amp
id|ip_statistics.IpDefaultTTL
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
id|NET_IPV4_RFC1812_FILTER
comma
l_string|&quot;ip_rfc1812_filter&quot;
comma
op_amp
id|ipv4_config.rfc1812_filter
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
id|NET_IPV4_LOG_MARTIANS
comma
l_string|&quot;ip_log_martians&quot;
comma
op_amp
id|ipv4_config.log_martians
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
id|NET_IPV4_SOURCE_ROUTE
comma
l_string|&quot;ip_source_route&quot;
comma
op_amp
id|ipv4_config.source_route
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
id|NET_IPV4_SEND_REDIRECTS
comma
l_string|&quot;ip_send_redirects&quot;
comma
op_amp
id|ipv4_config.send_redirects
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
id|NET_IPV4_BOOTP_RELAY
comma
l_string|&quot;ip_bootp_relay&quot;
comma
op_amp
id|ipv4_config.bootp_relay
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
id|NET_IPV4_PROXY_ARP
comma
l_string|&quot;ip_proxy_arp&quot;
comma
op_amp
id|ipv4_config.proxy_arp
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
id|NET_IPV4_ACCEPT_REDIRECTS
comma
l_string|&quot;ip_accept_redirects&quot;
comma
op_amp
id|ipv4_config.accept_redirects
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
id|NET_IPV4_SECURE_REDIRECTS
comma
l_string|&quot;ip_secure_redirects&quot;
comma
op_amp
id|ipv4_config.secure_redirects
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
id|NET_IPV4_RFC1620_REDIRECTS
comma
l_string|&quot;ip_rfc1620_redirects&quot;
comma
op_amp
id|ipv4_config.rfc1620_redirects
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
id|NET_IPV4_RTCACHE_FLUSH
comma
l_string|&quot;ip_rtcache_flush&quot;
comma
l_int|NULL
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
id|ipv4_sysctl_rtcache_flush
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
id|NET_IPV4_IP_DYNADDR
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
macro_line|#ifdef CONFIG_IP_MASQUERADE
(brace
id|NET_IPV4_IP_MASQ_DEBUG
comma
l_string|&quot;ip_masq_debug&quot;
comma
op_amp
id|sysctl_ip_masq_debug
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
)brace
comma
(brace
id|NET_IPV4_TCP_MAX_KA_PROBES
comma
l_string|&quot;tcp_max_ka_probes&quot;
comma
op_amp
id|sysctl_tcp_max_ka_probes
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
id|NET_IPV4_TCP_MAX_DELAY_ACKS
comma
l_string|&quot;tcp_max_delay_acks&quot;
comma
op_amp
id|sysctl_tcp_max_delay_acks
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
id|NET_TCP_SYN_TAILDROP
comma
l_string|&quot;tcp_syn_taildrop&quot;
comma
op_amp
id|sysctl_tcp_syn_taildrop
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
id|proc_dointvec
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
id|NET_IPV4_ICMP_SOURCEQUENCH_RATE
comma
l_string|&quot;icmp_sourcequench_rate&quot;
comma
op_amp
id|sysctl_icmp_sourcequench_time
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
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
eof
