multiline_comment|/*&n; *  linux/net/netsyms.c&n; *&n; *  Symbol table for the linux networking subsystem. Moved here to&n; *  make life simpler in ksyms.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#ifdef CONFIG_BRIDGE
macro_line|#include &lt;net/br.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_INET
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/scm.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
r_extern
r_struct
id|net_proto_family
id|inet_family_ops
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
r_extern
r_int
id|tcp_tw_death_row_slot
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/scm.h&gt;
macro_line|#if&t;defined(CONFIG_ULTRA)&t;||&t;defined(CONFIG_WD80x3)&t;&t;|| &bslash;&n;&t;defined(CONFIG_EL2)&t;||&t;defined(CONFIG_NE2000)&t;&t;|| &bslash;&n;&t;defined(CONFIG_E2100)&t;||&t;defined(CONFIG_HPLAN_PLUS)&t;|| &bslash;&n;&t;defined(CONFIG_HPLAN)&t;||&t;defined(CONFIG_AC3200)&t;&t;|| &bslash;&n;&t;defined(CONFIG_ES3210)
macro_line|#include &quot;../drivers/net/8390.h&quot;
macro_line|#endif
r_extern
r_int
(paren
op_star
id|rarp_ioctl_hook
)paren
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_MODULE
r_extern
r_struct
id|datalink_proto
op_star
id|make_EII_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|datalink_proto
op_star
id|make_8023_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|destroy_EII_client
c_func
(paren
r_struct
id|datalink_proto
op_star
)paren
suffix:semicolon
r_extern
r_void
id|destroy_8023_client
c_func
(paren
r_struct
id|datalink_proto
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATALK_MODULE
macro_line|#include &lt;net/sock.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_int
id|sysctl_max_syn_backlog
suffix:semicolon
macro_line|#endif
DECL|variable|dev_lockct
id|EXPORT_SYMBOL
c_func
(paren
id|dev_lockct
)paren
suffix:semicolon
multiline_comment|/* Skbuff symbols. */
DECL|variable|skb_over_panic
id|EXPORT_SYMBOL
c_func
(paren
id|skb_over_panic
)paren
suffix:semicolon
DECL|variable|skb_under_panic
id|EXPORT_SYMBOL
c_func
(paren
id|skb_under_panic
)paren
suffix:semicolon
multiline_comment|/* Socket layer registration */
DECL|variable|sock_register
id|EXPORT_SYMBOL
c_func
(paren
id|sock_register
)paren
suffix:semicolon
DECL|variable|sock_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|sock_unregister
)paren
suffix:semicolon
multiline_comment|/* Socket layer support routines */
DECL|variable|memcpy_fromiovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromiovec
)paren
suffix:semicolon
DECL|variable|memcpy_tokerneliovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_tokerneliovec
)paren
suffix:semicolon
DECL|variable|sock_create
id|EXPORT_SYMBOL
c_func
(paren
id|sock_create
)paren
suffix:semicolon
DECL|variable|sock_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|sock_alloc
)paren
suffix:semicolon
DECL|variable|sock_release
id|EXPORT_SYMBOL
c_func
(paren
id|sock_release
)paren
suffix:semicolon
DECL|variable|sock_setsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|sock_setsockopt
)paren
suffix:semicolon
DECL|variable|sock_getsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|sock_getsockopt
)paren
suffix:semicolon
DECL|variable|sock_sendmsg
id|EXPORT_SYMBOL
c_func
(paren
id|sock_sendmsg
)paren
suffix:semicolon
DECL|variable|sock_recvmsg
id|EXPORT_SYMBOL
c_func
(paren
id|sock_recvmsg
)paren
suffix:semicolon
DECL|variable|sk_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|sk_alloc
)paren
suffix:semicolon
DECL|variable|sk_free
id|EXPORT_SYMBOL
c_func
(paren
id|sk_free
)paren
suffix:semicolon
DECL|variable|sock_wake_async
id|EXPORT_SYMBOL
c_func
(paren
id|sock_wake_async
)paren
suffix:semicolon
DECL|variable|sock_alloc_send_skb
id|EXPORT_SYMBOL
c_func
(paren
id|sock_alloc_send_skb
)paren
suffix:semicolon
DECL|variable|sock_init_data
id|EXPORT_SYMBOL
c_func
(paren
id|sock_init_data
)paren
suffix:semicolon
DECL|variable|sock_no_dup
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_dup
)paren
suffix:semicolon
DECL|variable|sock_no_release
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_release
)paren
suffix:semicolon
DECL|variable|sock_no_bind
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_bind
)paren
suffix:semicolon
DECL|variable|sock_no_connect
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_connect
)paren
suffix:semicolon
DECL|variable|sock_no_socketpair
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_socketpair
)paren
suffix:semicolon
DECL|variable|sock_no_accept
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_accept
)paren
suffix:semicolon
DECL|variable|sock_no_getname
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_getname
)paren
suffix:semicolon
DECL|variable|sock_no_poll
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_poll
)paren
suffix:semicolon
DECL|variable|sock_no_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_ioctl
)paren
suffix:semicolon
DECL|variable|sock_no_listen
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_listen
)paren
suffix:semicolon
DECL|variable|sock_no_shutdown
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_shutdown
)paren
suffix:semicolon
DECL|variable|sock_no_getsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_getsockopt
)paren
suffix:semicolon
DECL|variable|sock_no_setsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_setsockopt
)paren
suffix:semicolon
DECL|variable|sock_no_fcntl
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_fcntl
)paren
suffix:semicolon
DECL|variable|sock_no_sendmsg
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_sendmsg
)paren
suffix:semicolon
DECL|variable|sock_no_recvmsg
id|EXPORT_SYMBOL
c_func
(paren
id|sock_no_recvmsg
)paren
suffix:semicolon
DECL|variable|sock_rfree
id|EXPORT_SYMBOL
c_func
(paren
id|sock_rfree
)paren
suffix:semicolon
DECL|variable|sock_wfree
id|EXPORT_SYMBOL
c_func
(paren
id|sock_wfree
)paren
suffix:semicolon
DECL|variable|skb_recv_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_recv_datagram
)paren
suffix:semicolon
DECL|variable|skb_free_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_free_datagram
)paren
suffix:semicolon
DECL|variable|skb_copy_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy_datagram
)paren
suffix:semicolon
DECL|variable|skb_copy_datagram_iovec
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy_datagram_iovec
)paren
suffix:semicolon
DECL|variable|skb_realloc_headroom
id|EXPORT_SYMBOL
c_func
(paren
id|skb_realloc_headroom
)paren
suffix:semicolon
DECL|variable|datagram_poll
id|EXPORT_SYMBOL
c_func
(paren
id|datagram_poll
)paren
suffix:semicolon
DECL|variable|put_cmsg
id|EXPORT_SYMBOL
c_func
(paren
id|put_cmsg
)paren
suffix:semicolon
DECL|variable|net_families
id|EXPORT_SYMBOL
c_func
(paren
id|net_families
)paren
suffix:semicolon
DECL|variable|sock_kmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|sock_kmalloc
)paren
suffix:semicolon
DECL|variable|sock_kfree_s
id|EXPORT_SYMBOL
c_func
(paren
id|sock_kfree_s
)paren
suffix:semicolon
DECL|variable|skb_queue_lock
id|EXPORT_SYMBOL
c_func
(paren
id|skb_queue_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FILTER
DECL|variable|sk_run_filter
id|EXPORT_SYMBOL
c_func
(paren
id|sk_run_filter
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|neigh_table_init
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_table_init
)paren
suffix:semicolon
DECL|variable|neigh_table_clear
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_table_clear
)paren
suffix:semicolon
DECL|variable|__neigh_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|__neigh_lookup
)paren
suffix:semicolon
DECL|variable|neigh_resolve_output
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_resolve_output
)paren
suffix:semicolon
DECL|variable|neigh_connected_output
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_connected_output
)paren
suffix:semicolon
DECL|variable|neigh_update
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_update
)paren
suffix:semicolon
DECL|variable|__neigh_event_send
id|EXPORT_SYMBOL
c_func
(paren
id|__neigh_event_send
)paren
suffix:semicolon
DECL|variable|neigh_event_ns
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_event_ns
)paren
suffix:semicolon
DECL|variable|neigh_ifdown
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_ifdown
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARPD
DECL|variable|neigh_app_ns
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_app_ns
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|neigh_sysctl_register
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_sysctl_register
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|pneigh_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|pneigh_lookup
)paren
suffix:semicolon
DECL|variable|pneigh_enqueue
id|EXPORT_SYMBOL
c_func
(paren
id|pneigh_enqueue
)paren
suffix:semicolon
DECL|variable|neigh_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_destroy
)paren
suffix:semicolon
DECL|variable|neigh_parms_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_parms_alloc
)paren
suffix:semicolon
DECL|variable|neigh_parms_release
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_parms_release
)paren
suffix:semicolon
DECL|variable|neigh_rand_reach_time
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_rand_reach_time
)paren
suffix:semicolon
multiline_comment|/*&t;dst_entry&t;*/
DECL|variable|dst_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|dst_alloc
)paren
suffix:semicolon
DECL|variable|__dst_free
id|EXPORT_SYMBOL
c_func
(paren
id|__dst_free
)paren
suffix:semicolon
DECL|variable|dst_total
id|EXPORT_SYMBOL
c_func
(paren
id|dst_total
)paren
suffix:semicolon
DECL|variable|dst_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|dst_destroy
)paren
suffix:semicolon
multiline_comment|/*&t;misc. support routines */
DECL|variable|net_ratelimit
id|EXPORT_SYMBOL
c_func
(paren
id|net_ratelimit
)paren
suffix:semicolon
DECL|variable|net_random
id|EXPORT_SYMBOL
c_func
(paren
id|net_random
)paren
suffix:semicolon
DECL|variable|net_srandom
id|EXPORT_SYMBOL
c_func
(paren
id|net_srandom
)paren
suffix:semicolon
multiline_comment|/* Needed by smbfs.o */
DECL|variable|__scm_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|__scm_destroy
)paren
suffix:semicolon
DECL|variable|__scm_send
id|EXPORT_SYMBOL
c_func
(paren
id|__scm_send
)paren
suffix:semicolon
multiline_comment|/* Needed by unix.o */
DECL|variable|scm_fp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|scm_fp_dup
)paren
suffix:semicolon
DECL|variable|max_files
id|EXPORT_SYMBOL
c_func
(paren
id|max_files
)paren
suffix:semicolon
DECL|variable|do_mknod
id|EXPORT_SYMBOL
c_func
(paren
id|do_mknod
)paren
suffix:semicolon
DECL|variable|memcpy_toiovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_toiovec
)paren
suffix:semicolon
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_MODULE
DECL|variable|make_8023_client
id|EXPORT_SYMBOL
c_func
(paren
id|make_8023_client
)paren
suffix:semicolon
DECL|variable|destroy_8023_client
id|EXPORT_SYMBOL
c_func
(paren
id|destroy_8023_client
)paren
suffix:semicolon
DECL|variable|make_EII_client
id|EXPORT_SYMBOL
c_func
(paren
id|make_EII_client
)paren
suffix:semicolon
DECL|variable|destroy_EII_client
id|EXPORT_SYMBOL
c_func
(paren
id|destroy_EII_client
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|sklist_destroy_socket
id|EXPORT_SYMBOL
c_func
(paren
id|sklist_destroy_socket
)paren
suffix:semicolon
DECL|variable|sklist_insert_socket
id|EXPORT_SYMBOL
c_func
(paren
id|sklist_insert_socket
)paren
suffix:semicolon
DECL|variable|scm_detach_fds
id|EXPORT_SYMBOL
c_func
(paren
id|scm_detach_fds
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BRIDGE 
DECL|variable|br_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|br_ioctl
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_INET
multiline_comment|/* Internet layer registration */
DECL|variable|inet_add_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_add_protocol
)paren
suffix:semicolon
DECL|variable|inet_del_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_del_protocol
)paren
suffix:semicolon
DECL|variable|rarp_ioctl_hook
id|EXPORT_SYMBOL
c_func
(paren
id|rarp_ioctl_hook
)paren
suffix:semicolon
DECL|variable|init_etherdev
id|EXPORT_SYMBOL
c_func
(paren
id|init_etherdev
)paren
suffix:semicolon
DECL|variable|ip_route_output
id|EXPORT_SYMBOL
c_func
(paren
id|ip_route_output
)paren
suffix:semicolon
DECL|variable|icmp_send
id|EXPORT_SYMBOL
c_func
(paren
id|icmp_send
)paren
suffix:semicolon
DECL|variable|ip_options_compile
id|EXPORT_SYMBOL
c_func
(paren
id|ip_options_compile
)paren
suffix:semicolon
DECL|variable|arp_send
id|EXPORT_SYMBOL
c_func
(paren
id|arp_send
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SHAPER_MODULE
DECL|variable|arp_broken_ops
id|EXPORT_SYMBOL
c_func
(paren
id|arp_broken_ops
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|ip_id_count
id|EXPORT_SYMBOL
c_func
(paren
id|ip_id_count
)paren
suffix:semicolon
DECL|variable|ip_send_check
id|EXPORT_SYMBOL
c_func
(paren
id|ip_send_check
)paren
suffix:semicolon
DECL|variable|ip_fragment
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fragment
)paren
suffix:semicolon
DECL|variable|inet_family_ops
id|EXPORT_SYMBOL
c_func
(paren
id|inet_family_ops
)paren
suffix:semicolon
DECL|variable|in_aton
id|EXPORT_SYMBOL
c_func
(paren
id|in_aton
)paren
suffix:semicolon
DECL|variable|ip_mc_inc_group
id|EXPORT_SYMBOL
c_func
(paren
id|ip_mc_inc_group
)paren
suffix:semicolon
DECL|variable|ip_mc_dec_group
id|EXPORT_SYMBOL
c_func
(paren
id|ip_mc_dec_group
)paren
suffix:semicolon
DECL|variable|__ip_finish_output
id|EXPORT_SYMBOL
c_func
(paren
id|__ip_finish_output
)paren
suffix:semicolon
DECL|variable|inet_dgram_ops
id|EXPORT_SYMBOL
c_func
(paren
id|inet_dgram_ops
)paren
suffix:semicolon
DECL|variable|ip_cmsg_recv
id|EXPORT_SYMBOL
c_func
(paren
id|ip_cmsg_recv
)paren
suffix:semicolon
DECL|variable|__release_sock
id|EXPORT_SYMBOL
c_func
(paren
id|__release_sock
)paren
suffix:semicolon
multiline_comment|/* needed for ip_gre -cw */
DECL|variable|ip_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|ip_statistics
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6_MODULE
multiline_comment|/* inet functions common to v4 and v6 */
DECL|variable|inet_stream_ops
id|EXPORT_SYMBOL
c_func
(paren
id|inet_stream_ops
)paren
suffix:semicolon
DECL|variable|inet_release
id|EXPORT_SYMBOL
c_func
(paren
id|inet_release
)paren
suffix:semicolon
DECL|variable|inet_stream_connect
id|EXPORT_SYMBOL
c_func
(paren
id|inet_stream_connect
)paren
suffix:semicolon
DECL|variable|inet_dgram_connect
id|EXPORT_SYMBOL
c_func
(paren
id|inet_dgram_connect
)paren
suffix:semicolon
DECL|variable|inet_accept
id|EXPORT_SYMBOL
c_func
(paren
id|inet_accept
)paren
suffix:semicolon
DECL|variable|inet_poll
id|EXPORT_SYMBOL
c_func
(paren
id|inet_poll
)paren
suffix:semicolon
DECL|variable|inet_listen
id|EXPORT_SYMBOL
c_func
(paren
id|inet_listen
)paren
suffix:semicolon
DECL|variable|inet_shutdown
id|EXPORT_SYMBOL
c_func
(paren
id|inet_shutdown
)paren
suffix:semicolon
DECL|variable|inet_setsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|inet_setsockopt
)paren
suffix:semicolon
DECL|variable|inet_getsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|inet_getsockopt
)paren
suffix:semicolon
DECL|variable|inet_sendmsg
id|EXPORT_SYMBOL
c_func
(paren
id|inet_sendmsg
)paren
suffix:semicolon
DECL|variable|inet_recvmsg
id|EXPORT_SYMBOL
c_func
(paren
id|inet_recvmsg
)paren
suffix:semicolon
multiline_comment|/* Socket demultiplexing. */
DECL|variable|tcp_good_socknum
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_good_socknum
)paren
suffix:semicolon
DECL|variable|tcp_established_hash
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_established_hash
)paren
suffix:semicolon
DECL|variable|tcp_listening_hash
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_listening_hash
)paren
suffix:semicolon
DECL|variable|tcp_bound_hash
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_bound_hash
)paren
suffix:semicolon
DECL|variable|udp_good_socknum
id|EXPORT_SYMBOL
c_func
(paren
id|udp_good_socknum
)paren
suffix:semicolon
DECL|variable|udp_hash
id|EXPORT_SYMBOL
c_func
(paren
id|udp_hash
)paren
suffix:semicolon
DECL|variable|destroy_sock
id|EXPORT_SYMBOL
c_func
(paren
id|destroy_sock
)paren
suffix:semicolon
DECL|variable|ip_queue_xmit
id|EXPORT_SYMBOL
c_func
(paren
id|ip_queue_xmit
)paren
suffix:semicolon
DECL|variable|memcpy_fromiovecend
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromiovecend
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_fromiovecend
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_fromiovecend
)paren
suffix:semicolon
DECL|variable|net_timer
id|EXPORT_SYMBOL
c_func
(paren
id|net_timer
)paren
suffix:semicolon
multiline_comment|/* UDP/TCP exported functions for TCPv6 */
DECL|variable|sock_rspace
id|EXPORT_SYMBOL
c_func
(paren
id|sock_rspace
)paren
suffix:semicolon
DECL|variable|udp_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|udp_ioctl
)paren
suffix:semicolon
DECL|variable|udp_connect
id|EXPORT_SYMBOL
c_func
(paren
id|udp_connect
)paren
suffix:semicolon
DECL|variable|udp_sendmsg
id|EXPORT_SYMBOL
c_func
(paren
id|udp_sendmsg
)paren
suffix:semicolon
DECL|variable|tcp_close
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_close
)paren
suffix:semicolon
DECL|variable|tcp_accept
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_accept
)paren
suffix:semicolon
DECL|variable|tcp_write_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_write_wakeup
)paren
suffix:semicolon
DECL|variable|tcp_read_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_read_wakeup
)paren
suffix:semicolon
DECL|variable|tcp_write_space
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_write_space
)paren
suffix:semicolon
DECL|variable|tcp_poll
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_poll
)paren
suffix:semicolon
DECL|variable|tcp_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_ioctl
)paren
suffix:semicolon
DECL|variable|tcp_shutdown
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_shutdown
)paren
suffix:semicolon
DECL|variable|tcp_setsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_setsockopt
)paren
suffix:semicolon
DECL|variable|tcp_getsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_getsockopt
)paren
suffix:semicolon
DECL|variable|tcp_recvmsg
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_recvmsg
)paren
suffix:semicolon
DECL|variable|tcp_send_synack
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_send_synack
)paren
suffix:semicolon
DECL|variable|tcp_check_req
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_check_req
)paren
suffix:semicolon
DECL|variable|tcp_reset_xmit_timer
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_reset_xmit_timer
)paren
suffix:semicolon
DECL|variable|tcp_parse_options
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_parse_options
)paren
suffix:semicolon
DECL|variable|tcp_rcv_established
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_rcv_established
)paren
suffix:semicolon
DECL|variable|tcp_init_xmit_timers
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_init_xmit_timers
)paren
suffix:semicolon
DECL|variable|tcp_clear_xmit_timers
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_clear_xmit_timers
)paren
suffix:semicolon
DECL|variable|tcp_slt_array
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_slt_array
)paren
suffix:semicolon
DECL|variable|__tcp_inc_slow_timer
id|EXPORT_SYMBOL
c_func
(paren
id|__tcp_inc_slow_timer
)paren
suffix:semicolon
DECL|variable|tcp_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_statistics
)paren
suffix:semicolon
DECL|variable|tcp_rcv_state_process
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_rcv_state_process
)paren
suffix:semicolon
DECL|variable|tcp_timewait_state_process
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_timewait_state_process
)paren
suffix:semicolon
DECL|variable|tcp_do_sendmsg
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_do_sendmsg
)paren
suffix:semicolon
DECL|variable|tcp_v4_rebuild_header
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_rebuild_header
)paren
suffix:semicolon
DECL|variable|tcp_v4_send_check
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_send_check
)paren
suffix:semicolon
DECL|variable|tcp_v4_conn_request
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_conn_request
)paren
suffix:semicolon
DECL|variable|tcp_create_openreq_child
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_create_openreq_child
)paren
suffix:semicolon
DECL|variable|tcp_bucket_create
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_bucket_create
)paren
suffix:semicolon
DECL|variable|tcp_bucket_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_bucket_unlock
)paren
suffix:semicolon
DECL|variable|tcp_v4_syn_recv_sock
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_syn_recv_sock
)paren
suffix:semicolon
DECL|variable|tcp_v4_do_rcv
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_do_rcv
)paren
suffix:semicolon
DECL|variable|tcp_v4_connect
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_v4_connect
)paren
suffix:semicolon
DECL|variable|inet_addr_type
id|EXPORT_SYMBOL
c_func
(paren
id|inet_addr_type
)paren
suffix:semicolon
DECL|variable|net_reset_timer
id|EXPORT_SYMBOL
c_func
(paren
id|net_reset_timer
)paren
suffix:semicolon
DECL|variable|net_delete_timer
id|EXPORT_SYMBOL
c_func
(paren
id|net_delete_timer
)paren
suffix:semicolon
DECL|variable|udp_prot
id|EXPORT_SYMBOL
c_func
(paren
id|udp_prot
)paren
suffix:semicolon
DECL|variable|tcp_prot
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_prot
)paren
suffix:semicolon
DECL|variable|tcp_openreq_cachep
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_openreq_cachep
)paren
suffix:semicolon
DECL|variable|ipv4_specific
id|EXPORT_SYMBOL
c_func
(paren
id|ipv4_specific
)paren
suffix:semicolon
DECL|variable|tcp_simple_retransmit
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_simple_retransmit
)paren
suffix:semicolon
DECL|variable|tcp_transmit_skb
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_transmit_skb
)paren
suffix:semicolon
DECL|variable|tcp_connect
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_connect
)paren
suffix:semicolon
DECL|variable|tcp_make_synack
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_make_synack
)paren
suffix:semicolon
DECL|variable|tcp_tw_death_row_slot
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_tw_death_row_slot
)paren
suffix:semicolon
DECL|variable|tcp_sync_mss
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_sync_mss
)paren
suffix:semicolon
DECL|variable|net_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|net_statistics
)paren
suffix:semicolon
DECL|variable|xrlim_allow
id|EXPORT_SYMBOL
c_func
(paren
id|xrlim_allow
)paren
suffix:semicolon
DECL|variable|tcp_write_xmit
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_write_xmit
)paren
suffix:semicolon
DECL|variable|dev_loopback_xmit
id|EXPORT_SYMBOL
c_func
(paren
id|dev_loopback_xmit
)paren
suffix:semicolon
DECL|variable|tcp_regs
id|EXPORT_SYMBOL
c_func
(paren
id|tcp_regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|sysctl_max_syn_backlog
id|EXPORT_SYMBOL
c_func
(paren
id|sysctl_max_syn_backlog
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_NETLINK
DECL|variable|netlink_set_err
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_set_err
)paren
suffix:semicolon
DECL|variable|netlink_broadcast
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_broadcast
)paren
suffix:semicolon
DECL|variable|netlink_unicast
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_unicast
)paren
suffix:semicolon
DECL|variable|netlink_kernel_create
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_kernel_create
)paren
suffix:semicolon
DECL|variable|netlink_dump_start
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_dump_start
)paren
suffix:semicolon
DECL|variable|netlink_ack
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_ack
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_NETLINK_DEV) || defined(CONFIG_NETLINK_DEV_MODULE)
DECL|variable|netlink_attach
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_attach
)paren
suffix:semicolon
DECL|variable|netlink_detach
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_detach
)paren
suffix:semicolon
DECL|variable|netlink_post
id|EXPORT_SYMBOL
c_func
(paren
id|netlink_post
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_RTNETLINK
DECL|variable|rtattr_parse
id|EXPORT_SYMBOL
c_func
(paren
id|rtattr_parse
)paren
suffix:semicolon
DECL|variable|rtnetlink_links
id|EXPORT_SYMBOL
c_func
(paren
id|rtnetlink_links
)paren
suffix:semicolon
DECL|variable|__rta_fill
id|EXPORT_SYMBOL
c_func
(paren
id|__rta_fill
)paren
suffix:semicolon
DECL|variable|rtnetlink_dump_ifinfo
id|EXPORT_SYMBOL
c_func
(paren
id|rtnetlink_dump_ifinfo
)paren
suffix:semicolon
DECL|variable|rtnl_wlockct
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl_wlockct
)paren
suffix:semicolon
DECL|variable|rtnl
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl
)paren
suffix:semicolon
DECL|variable|neigh_delete
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_delete
)paren
suffix:semicolon
DECL|variable|neigh_add
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_add
)paren
suffix:semicolon
DECL|variable|neigh_dump_info
id|EXPORT_SYMBOL
c_func
(paren
id|neigh_dump_info
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|dev_set_allmulti
id|EXPORT_SYMBOL
c_func
(paren
id|dev_set_allmulti
)paren
suffix:semicolon
DECL|variable|dev_set_promiscuity
id|EXPORT_SYMBOL
c_func
(paren
id|dev_set_promiscuity
)paren
suffix:semicolon
DECL|variable|sklist_remove_socket
id|EXPORT_SYMBOL
c_func
(paren
id|sklist_remove_socket
)paren
suffix:semicolon
DECL|variable|rtnl_wait
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl_wait
)paren
suffix:semicolon
DECL|variable|rtnl_rlockct
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl_rlockct
)paren
suffix:semicolon
DECL|variable|rtnl_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl_lock
)paren
suffix:semicolon
DECL|variable|rtnl_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|rtnl_unlock
)paren
suffix:semicolon
DECL|variable|sock_wmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|sock_wmalloc
)paren
suffix:semicolon
DECL|variable|sock_rmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|sock_rmalloc
)paren
suffix:semicolon
macro_line|#if&t;defined(CONFIG_ULTRA)&t;||&t;defined(CONFIG_WD80x3)&t;&t;|| &bslash;&n;&t;defined(CONFIG_EL2)&t;||&t;defined(CONFIG_NE2000)&t;&t;|| &bslash;&n;&t;defined(CONFIG_E2100)&t;||&t;defined(CONFIG_HPLAN_PLUS)&t;|| &bslash;&n;&t;defined(CONFIG_HPLAN)&t;||&t;defined(CONFIG_AC3200)&t;&t;|| &bslash;&n;&t;defined(CONFIG_ES3210)
multiline_comment|/* If 8390 NIC support is built in, we will need these. */
DECL|variable|ei_open
id|EXPORT_SYMBOL
c_func
(paren
id|ei_open
)paren
suffix:semicolon
DECL|variable|ei_close
id|EXPORT_SYMBOL
c_func
(paren
id|ei_close
)paren
suffix:semicolon
DECL|variable|ei_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|ei_interrupt
)paren
suffix:semicolon
DECL|variable|ethdev_init
id|EXPORT_SYMBOL
c_func
(paren
id|ethdev_init
)paren
suffix:semicolon
DECL|variable|NS8390_init
id|EXPORT_SYMBOL
c_func
(paren
id|NS8390_init
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TR
DECL|variable|tr_setup
id|EXPORT_SYMBOL
c_func
(paren
id|tr_setup
)paren
suffix:semicolon
DECL|variable|tr_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|tr_type_trans
)paren
suffix:semicolon
DECL|variable|register_trdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_trdev
)paren
suffix:semicolon
DECL|variable|unregister_trdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_trdev
)paren
suffix:semicolon
DECL|variable|init_trdev
id|EXPORT_SYMBOL
c_func
(paren
id|init_trdev
)paren
suffix:semicolon
DECL|variable|tr_freedev
id|EXPORT_SYMBOL
c_func
(paren
id|tr_freedev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Used by at least ipip.c.  */
DECL|variable|ipv4_config
id|EXPORT_SYMBOL
c_func
(paren
id|ipv4_config
)paren
suffix:semicolon
DECL|variable|dev_open
id|EXPORT_SYMBOL
c_func
(paren
id|dev_open
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_INET */
multiline_comment|/* Device callback registration */
DECL|variable|register_netdevice_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|register_netdevice_notifier
)paren
suffix:semicolon
DECL|variable|unregister_netdevice_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_netdevice_notifier
)paren
suffix:semicolon
multiline_comment|/* support for loadable net drivers */
macro_line|#ifdef CONFIG_NET
DECL|variable|loopback_dev
id|EXPORT_SYMBOL
c_func
(paren
id|loopback_dev
)paren
suffix:semicolon
DECL|variable|register_netdevice
id|EXPORT_SYMBOL
c_func
(paren
id|register_netdevice
)paren
suffix:semicolon
DECL|variable|unregister_netdevice
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_netdevice
)paren
suffix:semicolon
DECL|variable|register_netdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_netdev
)paren
suffix:semicolon
DECL|variable|unregister_netdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_netdev
)paren
suffix:semicolon
DECL|variable|ether_setup
id|EXPORT_SYMBOL
c_func
(paren
id|ether_setup
)paren
suffix:semicolon
DECL|variable|dev_new_index
id|EXPORT_SYMBOL
c_func
(paren
id|dev_new_index
)paren
suffix:semicolon
DECL|variable|dev_get_by_index
id|EXPORT_SYMBOL
c_func
(paren
id|dev_get_by_index
)paren
suffix:semicolon
DECL|variable|eth_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|eth_type_trans
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FDDI
DECL|variable|fddi_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|fddi_type_trans
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FDDI */
DECL|variable|eth_copy_and_sum
id|EXPORT_SYMBOL
c_func
(paren
id|eth_copy_and_sum
)paren
suffix:semicolon
DECL|variable|alloc_skb
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_skb
)paren
suffix:semicolon
DECL|variable|__kfree_skb
id|EXPORT_SYMBOL
c_func
(paren
id|__kfree_skb
)paren
suffix:semicolon
DECL|variable|skb_clone
id|EXPORT_SYMBOL
c_func
(paren
id|skb_clone
)paren
suffix:semicolon
DECL|variable|skb_copy
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy
)paren
suffix:semicolon
DECL|variable|netif_rx
id|EXPORT_SYMBOL
c_func
(paren
id|netif_rx
)paren
suffix:semicolon
DECL|variable|dev_add_pack
id|EXPORT_SYMBOL
c_func
(paren
id|dev_add_pack
)paren
suffix:semicolon
DECL|variable|dev_remove_pack
id|EXPORT_SYMBOL
c_func
(paren
id|dev_remove_pack
)paren
suffix:semicolon
DECL|variable|dev_get
id|EXPORT_SYMBOL
c_func
(paren
id|dev_get
)paren
suffix:semicolon
DECL|variable|dev_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|dev_alloc
)paren
suffix:semicolon
DECL|variable|dev_alloc_name
id|EXPORT_SYMBOL
c_func
(paren
id|dev_alloc_name
)paren
suffix:semicolon
DECL|variable|dev_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|dev_ioctl
)paren
suffix:semicolon
DECL|variable|dev_queue_xmit
id|EXPORT_SYMBOL
c_func
(paren
id|dev_queue_xmit
)paren
suffix:semicolon
DECL|variable|netdev_dropping
id|EXPORT_SYMBOL
c_func
(paren
id|netdev_dropping
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_FASTROUTE
DECL|variable|dev_fastroute_stat
id|EXPORT_SYMBOL
c_func
(paren
id|dev_fastroute_stat
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
DECL|variable|netdev_register_fc
id|EXPORT_SYMBOL
c_func
(paren
id|netdev_register_fc
)paren
suffix:semicolon
DECL|variable|netdev_unregister_fc
id|EXPORT_SYMBOL
c_func
(paren
id|netdev_unregister_fc
)paren
suffix:semicolon
DECL|variable|netdev_fc_xoff
id|EXPORT_SYMBOL
c_func
(paren
id|netdev_fc_xoff
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|dev_base
id|EXPORT_SYMBOL
c_func
(paren
id|dev_base
)paren
suffix:semicolon
DECL|variable|dev_close
id|EXPORT_SYMBOL
c_func
(paren
id|dev_close
)paren
suffix:semicolon
DECL|variable|dev_mc_add
id|EXPORT_SYMBOL
c_func
(paren
id|dev_mc_add
)paren
suffix:semicolon
DECL|variable|arp_find
id|EXPORT_SYMBOL
c_func
(paren
id|arp_find
)paren
suffix:semicolon
DECL|variable|n_tty_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|n_tty_ioctl
)paren
suffix:semicolon
DECL|variable|tty_register_ldisc
id|EXPORT_SYMBOL
c_func
(paren
id|tty_register_ldisc
)paren
suffix:semicolon
DECL|variable|kill_fasync
id|EXPORT_SYMBOL
c_func
(paren
id|kill_fasync
)paren
suffix:semicolon
DECL|variable|ip_rcv
id|EXPORT_SYMBOL
c_func
(paren
id|ip_rcv
)paren
suffix:semicolon
DECL|variable|arp_rcv
id|EXPORT_SYMBOL
c_func
(paren
id|arp_rcv
)paren
suffix:semicolon
DECL|variable|dev_mc_delete
id|EXPORT_SYMBOL
c_func
(paren
id|dev_mc_delete
)paren
suffix:semicolon
DECL|variable|if_port_text
id|EXPORT_SYMBOL
c_func
(paren
id|if_port_text
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE) 
macro_line|#include&lt;linux/if_ltalk.h&gt;
DECL|variable|ltalk_setup
id|EXPORT_SYMBOL
c_func
(paren
id|ltalk_setup
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DLCI_MODULE
r_extern
r_int
(paren
op_star
id|dlci_ioctl_hook
)paren
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|variable|dlci_ioctl_hook
id|EXPORT_SYMBOL
c_func
(paren
id|dlci_ioctl_hook
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Packet scheduler modules want these. */
DECL|variable|qdisc_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_destroy
)paren
suffix:semicolon
DECL|variable|qdisc_reset
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_reset
)paren
suffix:semicolon
DECL|variable|qdisc_restart
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_restart
)paren
suffix:semicolon
DECL|variable|qdisc_head
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_head
)paren
suffix:semicolon
DECL|variable|qdisc_create_dflt
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_create_dflt
)paren
suffix:semicolon
DECL|variable|noop_qdisc
id|EXPORT_SYMBOL
c_func
(paren
id|noop_qdisc
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_SCHED
DECL|variable|pfifo_qdisc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|pfifo_qdisc_ops
)paren
suffix:semicolon
DECL|variable|register_qdisc
id|EXPORT_SYMBOL
c_func
(paren
id|register_qdisc
)paren
suffix:semicolon
DECL|variable|unregister_qdisc
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_qdisc
)paren
suffix:semicolon
DECL|variable|qdisc_get_rtab
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_get_rtab
)paren
suffix:semicolon
DECL|variable|qdisc_put_rtab
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_put_rtab
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
DECL|variable|qdisc_new_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_new_estimator
)paren
suffix:semicolon
DECL|variable|qdisc_kill_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_kill_estimator
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_POLICE
DECL|variable|tcf_police
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police
)paren
suffix:semicolon
DECL|variable|tcf_police_locate
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_locate
)paren
suffix:semicolon
DECL|variable|tcf_police_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_destroy
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RTNETLINK
DECL|variable|tcf_police_dump
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_dump
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS
DECL|variable|register_tcf_proto_ops
id|EXPORT_SYMBOL
c_func
(paren
id|register_tcf_proto_ops
)paren
suffix:semicolon
DECL|variable|unregister_tcf_proto_ops
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_tcf_proto_ops
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|register_gifconf
id|EXPORT_SYMBOL
c_func
(paren
id|register_gifconf
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_NET */
eof
