multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the AF_INET socket handler.&n; *&n; * Version:&t;@(#)sock.h&t;1.0.4&t;05/13/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Corey Minyard &lt;wf-rch!minyard@relay.EU.net&gt;&n; *&t;&t;Florian La Roche &lt;flla@stud.uni-sb.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;Volatiles in skbuff pointers. See&n; *&t;&t;&t;&t;&t;skbuff comments. May be overdone,&n; *&t;&t;&t;&t;&t;better to prove they can be removed&n; *&t;&t;&t;&t;&t;than the reverse.&n; *&t;&t;Alan Cox&t;:&t;Added a zapped field for tcp to note&n; *&t;&t;&t;&t;&t;a socket is reset and must stay shut up&n; *&t;&t;Alan Cox&t;:&t;New fields for options&n; *&t;Pauline Middelink&t;:&t;identd support&n; *&t;&t;Alan Cox&t;:&t;Eliminate low level recv/recvfrom&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _SOCK_H
DECL|macro|_SOCK_H
mdefine_line|#define _SOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ip.h&gt;&t;&t;/* struct options */
macro_line|#include &lt;linux/in.h&gt;&t;&t;/* struct sockaddr_in */
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
macro_line|#include &lt;linux/in6.h&gt;&t;&t;/* struct sockaddr_in6 */
macro_line|#include &lt;linux/ipv6.h&gt;&t;&t;/* dest_cache, inet6_options */
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;&t;/* struct ipv6_mc_socklist */
macro_line|#endif
macro_line|#include &lt;linux/tcp.h&gt;&t;&t;/* struct tcphdr */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;&t;/* struct sk_buff */
macro_line|#include &lt;net/protocol.h&gt;&t;&t;/* struct inet_protocol */
macro_line|#ifdef CONFIG_AX25
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#ifdef CONFIG_NETROM
macro_line|#include &lt;net/netrom.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CONFIG_IPX) || defined(CONFIG_IPX_MODULE)
macro_line|#include &lt;net/ipx.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE)
macro_line|#include &lt;linux/atalk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/igmp.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* Think big (also on some systems a byte is faster) */
DECL|macro|SOCK_ARRAY_SIZE
mdefine_line|#define SOCK_ARRAY_SIZE&t;256
multiline_comment|/*&n; *&t;The AF_UNIX specific socket options&n; */
DECL|struct|unix_opt
r_struct
id|unix_opt
(brace
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|locks
r_int
id|locks
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|readsem
r_struct
id|semaphore
id|readsem
suffix:semicolon
DECL|member|other
r_struct
id|sock
op_star
id|other
suffix:semicolon
DECL|member|marksweep
r_int
id|marksweep
suffix:semicolon
DECL|macro|MARKED
mdefine_line|#define MARKED&t;&t;&t;1
DECL|member|inflight
r_int
id|inflight
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;IP packet socket options&n; */
DECL|struct|inet_packet_opt
r_struct
id|inet_packet_opt
(brace
DECL|member|notifier
r_struct
id|notifier_block
id|notifier
suffix:semicolon
multiline_comment|/* Used when bound */
DECL|member|bound_dev
r_struct
id|device
op_star
id|bound_dev
suffix:semicolon
DECL|member|dev_stamp
r_int
r_int
id|dev_stamp
suffix:semicolon
DECL|member|prot_hook
r_struct
id|packet_type
op_star
id|prot_hook
suffix:semicolon
DECL|member|device_name
r_char
id|device_name
(braket
l_int|15
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Once the IPX ncpd patches are in these are going into protinfo&n; */
macro_line|#if defined(CONFIG_IPX) || defined(CONFIG_IPX_MODULE)
DECL|struct|ipx_opt
r_struct
id|ipx_opt
(brace
DECL|member|dest_addr
id|ipx_address
id|dest_addr
suffix:semicolon
DECL|member|intrfc
id|ipx_interface
op_star
id|intrfc
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_INTERN
DECL|member|node
r_int
r_char
id|node
(braket
id|IPX_NODE_LEN
)braket
suffix:semicolon
macro_line|#endif
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* &n; * To handle asynchronous messages from the NetWare server, we have to&n; * know the connection this socket belongs to. &n; */
DECL|member|ncp_server
r_struct
id|ncp_server
op_star
id|ncp_server
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|struct|ipv6_pinfo
r_struct
id|ipv6_pinfo
(brace
DECL|member|saddr
r_struct
id|in6_addr
id|saddr
suffix:semicolon
DECL|member|rcv_saddr
r_struct
id|in6_addr
id|rcv_saddr
suffix:semicolon
DECL|member|daddr
r_struct
id|in6_addr
id|daddr
suffix:semicolon
DECL|member|flow_lbl
id|__u32
id|flow_lbl
suffix:semicolon
DECL|member|priority
id|__u8
id|priority
suffix:semicolon
DECL|member|hop_limit
id|__u8
id|hop_limit
suffix:semicolon
DECL|member|mcast_hops
id|__u8
id|mcast_hops
suffix:semicolon
multiline_comment|/* sockopt flags */
DECL|member|recvsrcrt
id|__u8
id|recvsrcrt
suffix:colon
l_int|1
comma
DECL|member|rxinfo
id|rxinfo
suffix:colon
l_int|1
comma
DECL|member|mc_loop
id|mc_loop
suffix:colon
l_int|1
comma
DECL|member|unused
id|unused
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* device for outgoing mcast packets */
DECL|member|mc_if
r_struct
id|device
op_star
id|mc_if
suffix:semicolon
DECL|member|ipv6_mc_list
r_struct
id|ipv6_mc_socklist
op_star
id|ipv6_mc_list
suffix:semicolon
multiline_comment|/* &n;&t; * destination cache entry pointer&n;&t; * contains a pointer to neighbour cache&n;&t; * and other info related to network level &n;&t; * (ex. PMTU)&n;&t; */
DECL|member|dest
r_struct
id|dest_entry
op_star
id|dest
suffix:semicolon
DECL|member|dc_sernum
id|__u32
id|dc_sernum
suffix:semicolon
DECL|member|opt
r_struct
id|ipv6_options
op_star
id|opt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raw6_opt
r_struct
id|raw6_opt
(brace
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
multiline_comment|/* perform checksum */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* checksum offset  */
DECL|member|filter
r_struct
id|icmp6_filter
id|filter
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* IPV6 */
DECL|struct|tcp_opt
r_struct
id|tcp_opt
(brace
multiline_comment|/*&n; *&t;RFC793 variables by their proper names. This means you can&n; *&t;read the code and the spec side by side (and laugh ...)&n; *&t;See RFC793 and RFC1122. The RFC writes these in capitals.&n; */
DECL|member|rcv_nxt
id|__u32
id|rcv_nxt
suffix:semicolon
multiline_comment|/* What we want to receive next &t;*/
DECL|member|rcv_up
id|__u32
id|rcv_up
suffix:semicolon
multiline_comment|/* The urgent point (may not be valid) &t;*/
DECL|member|rcv_wnd
id|__u32
id|rcv_wnd
suffix:semicolon
multiline_comment|/* Current receiver window&t;&t;*/
DECL|member|snd_nxt
id|__u32
id|snd_nxt
suffix:semicolon
multiline_comment|/* Next sequence we send&t;&t;*/
DECL|member|snd_una
id|__u32
id|snd_una
suffix:semicolon
multiline_comment|/* First byte we want an ack for&t;*/
DECL|member|snd_up
id|__u32
id|snd_up
suffix:semicolon
multiline_comment|/* Outgoing urgent pointer&t;&t;*/
DECL|member|snd_wl1
id|__u32
id|snd_wl1
suffix:semicolon
multiline_comment|/* Sequence for window update&t;&t;*/
DECL|member|snd_wl2
id|__u32
id|snd_wl2
suffix:semicolon
multiline_comment|/* Ack sequence for update&t;&t;*/
DECL|member|rcv_wup
id|__u32
id|rcv_wup
suffix:semicolon
multiline_comment|/* rcv_nxt on last window update sent&t;*/
DECL|member|srtt
id|__u32
id|srtt
suffix:semicolon
multiline_comment|/* smothed round trip time &lt;&lt; 3&t;&t;*/
DECL|member|mdev
id|__u32
id|mdev
suffix:semicolon
multiline_comment|/* medium deviation&t;&t;&t;*/
DECL|member|rto
id|__u32
id|rto
suffix:semicolon
multiline_comment|/* retransmit timeout&t;&t;&t;*/
DECL|member|backoff
id|__u32
id|backoff
suffix:semicolon
multiline_comment|/* backoff&t;&t;&t;&t;*/
multiline_comment|/*&n; *&t;Slow start and congestion control (see also Nagle, and Karn &amp; Partridge)&n; */
DECL|member|snd_cwnd
id|__u32
id|snd_cwnd
suffix:semicolon
multiline_comment|/* Sending congestion window&t;&t;*/
DECL|member|snd_ssthresh
id|__u32
id|snd_ssthresh
suffix:semicolon
multiline_comment|/* Slow start size threshold&t;&t;*/
multiline_comment|/*&n; *&t;Timers used by the TCP protocol layer&n; */
DECL|member|delack_timer
r_struct
id|timer_list
id|delack_timer
suffix:semicolon
multiline_comment|/* Ack delay &t;*/
DECL|member|idle_timer
r_struct
id|timer_list
id|idle_timer
suffix:semicolon
multiline_comment|/* Idle watch &t;*/
DECL|member|completion_timer
r_struct
id|timer_list
id|completion_timer
suffix:semicolon
multiline_comment|/* Up/Down timer */
DECL|member|probe_timer
r_struct
id|timer_list
id|probe_timer
suffix:semicolon
multiline_comment|/* Probes&t;*/
DECL|member|retransmit_timer
r_struct
id|timer_list
id|retransmit_timer
suffix:semicolon
multiline_comment|/* Resend (no ack) */
DECL|member|basertt
id|__u32
id|basertt
suffix:semicolon
multiline_comment|/* Vegas baseRTT */
DECL|member|delayed_acks
id|__u8
id|delayed_acks
suffix:semicolon
DECL|member|dup_acks
id|__u8
id|dup_acks
suffix:semicolon
DECL|member|lrcvtime
id|__u32
id|lrcvtime
suffix:semicolon
multiline_comment|/* timestamp of last received data packet  */
DECL|member|rcv_tstamp
id|__u32
id|rcv_tstamp
suffix:semicolon
multiline_comment|/* timestamp of last received packet  */
DECL|member|iat_mdev
id|__u32
id|iat_mdev
suffix:semicolon
multiline_comment|/* interarrival time medium deviation */
DECL|member|iat
id|__u32
id|iat
suffix:semicolon
multiline_comment|/* interarrival time */
DECL|member|ato
id|__u32
id|ato
suffix:semicolon
multiline_comment|/* delayed ack timeout */
DECL|member|high_seq
id|__u32
id|high_seq
suffix:semicolon
multiline_comment|/*&n; *&t;new send pointers&n; */
DECL|member|send_head
r_struct
id|sk_buff
op_star
id|send_head
suffix:semicolon
DECL|member|retrans_head
r_struct
id|sk_buff
op_star
id|retrans_head
suffix:semicolon
multiline_comment|/* retrans head can be &n;&t;&t;&t;&t;&t;&t; * different to the head of&n;&t;&t;&t;&t;&t;&t; * write queue if we are doing&n;&t;&t;&t;&t;&t;&t; * fast retransmit&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * pending events&n; */
DECL|member|pending
id|__u8
id|pending
suffix:semicolon
multiline_comment|/*&n; *&t;Header prediction flags&n; *&t;0x5?10 &lt;&lt; 16 + snd_wnd in net byte order&n; */
DECL|member|pred_flags
id|__u32
id|pred_flags
suffix:semicolon
DECL|member|snd_wnd
id|__u32
id|snd_wnd
suffix:semicolon
multiline_comment|/* The window we expect to receive */
DECL|member|probes_out
id|__u32
id|probes_out
suffix:semicolon
multiline_comment|/* unanswered 0 window probes&t;   */
DECL|member|syn_wait_queue
r_struct
id|open_request
op_star
id|syn_wait_queue
suffix:semicolon
DECL|member|af_specific
r_struct
id|tcp_func
op_star
id|af_specific
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure really needs to be cleaned up.&n; * Most of it is for TCP, and not used by any of&n; * the other protocols.&n; */
multiline_comment|/*&n; * The idea is to start moving to a newer struct gradualy&n; * &n; * IMHO the newer struct should have the following format:&n; * &n; *&t;struct sock {&n; *&t;&t;sockmem [mem, proto, callbacks]&n; *&n; *&t;&t;union or struct {&n; *&t;&t;&t;netrom;&n; *&t;&t;&t;ax_25;&n; *&t;&t;} ll_pinfo;&n; *&t;&n; *&t;&t;union {&n; *&t;&t;&t;ipv4;&n; *&t;&t;&t;ipv6;&n; *&t;&t;&t;ipx;&n; *&t;&t;} net_pinfo;&n; *&n; *&t;&t;union {&n; *&t;&t;&t;tcp;&n; *&t;&t;&t;udp;&n; *&t;&t;&t;spx;&n; *&t;&t;} tp_pinfo;&n; *&n; *&t;}&n; */
multiline_comment|/*&n; *  TCP will start to use the new protinfo while *still using the old* fields &n; */
DECL|struct|sock
r_struct
id|sock
(brace
DECL|member|opt
r_struct
id|options
op_star
id|opt
suffix:semicolon
DECL|member|wmem_alloc
id|atomic_t
id|wmem_alloc
suffix:semicolon
DECL|member|rmem_alloc
id|atomic_t
id|rmem_alloc
suffix:semicolon
DECL|member|allocation
r_int
r_int
id|allocation
suffix:semicolon
multiline_comment|/* Allocation mode */
DECL|member|write_seq
id|__u32
id|write_seq
suffix:semicolon
DECL|member|copied_seq
id|__u32
id|copied_seq
suffix:semicolon
DECL|member|fin_seq
id|__u32
id|fin_seq
suffix:semicolon
DECL|member|syn_seq
id|__u32
id|syn_seq
suffix:semicolon
DECL|member|urg_seq
id|__u32
id|urg_seq
suffix:semicolon
DECL|member|urg_data
id|__u32
id|urg_data
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* user count */
DECL|member|delayed_acks
r_int
r_char
id|delayed_acks
comma
DECL|member|dup_acks
id|dup_acks
suffix:semicolon
multiline_comment|/*&n;   *&t;Not all are volatile, but some are, so we&n;   * &t;might as well say they all are.&n;   */
DECL|member|dead
r_volatile
r_char
id|dead
comma
DECL|member|urginline
id|urginline
comma
DECL|member|intr
id|intr
comma
DECL|member|blog
id|blog
comma
DECL|member|done
id|done
comma
DECL|member|reuse
id|reuse
comma
DECL|member|keepopen
id|keepopen
comma
DECL|member|linger
id|linger
comma
DECL|member|destroy
id|destroy
comma
DECL|member|ack_timed
id|ack_timed
comma
DECL|member|no_check
id|no_check
comma
DECL|member|zapped
id|zapped
comma
multiline_comment|/* In ax25 &amp; ipx means not linked */
DECL|member|broadcast
id|broadcast
comma
DECL|member|nonagle
id|nonagle
comma
DECL|member|bsdism
id|bsdism
suffix:semicolon
DECL|member|lingertime
r_int
r_int
id|lingertime
suffix:semicolon
DECL|member|proc
r_int
id|proc
suffix:semicolon
DECL|member|next
r_struct
id|sock
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|sock
op_star
id|prev
suffix:semicolon
multiline_comment|/* Doubly linked chain.. */
DECL|member|pair
r_struct
id|sock
op_star
id|pair
suffix:semicolon
DECL|member|send_head
r_struct
id|sk_buff
op_star
id|send_head
suffix:semicolon
DECL|member|send_tail
r_struct
id|sk_buff
op_star
id|send_tail
suffix:semicolon
DECL|member|back_log
r_struct
id|sk_buff_head
id|back_log
suffix:semicolon
DECL|member|partial
r_struct
id|sk_buff
op_star
id|partial
suffix:semicolon
DECL|member|partial_timer
r_struct
id|timer_list
id|partial_timer
suffix:semicolon
DECL|member|retransmits
id|atomic_t
id|retransmits
suffix:semicolon
DECL|member|write_queue
r_struct
id|sk_buff_head
id|write_queue
comma
DECL|member|receive_queue
id|receive_queue
comma
DECL|member|out_of_order_queue
id|out_of_order_queue
suffix:semicolon
DECL|member|family
r_int
r_int
id|family
suffix:semicolon
DECL|member|prot
r_struct
id|proto
op_star
id|prot
suffix:semicolon
DECL|member|sleep
r_struct
id|wait_queue
op_star
op_star
id|sleep
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Sending source */
DECL|member|rcv_saddr
id|__u32
id|rcv_saddr
suffix:semicolon
multiline_comment|/* Bound address */
DECL|member|max_unacked
r_int
r_int
id|max_unacked
suffix:semicolon
DECL|member|bytes_rcv
r_int
r_int
id|bytes_rcv
suffix:semicolon
multiline_comment|/*&n; *&t;mss is min(mtu, max_window) &n; */
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
multiline_comment|/* mss negotiated in the syn&squot;s */
DECL|member|mss
r_int
r_int
id|mss
suffix:semicolon
multiline_comment|/* current eff. mss - can change */
DECL|member|user_mss
r_int
r_int
id|user_mss
suffix:semicolon
multiline_comment|/* mss requested by user in ioctl */
DECL|member|max_window
r_int
r_int
id|max_window
suffix:semicolon
DECL|member|window_clamp
r_int
r_int
id|window_clamp
suffix:semicolon
DECL|member|ssthresh
r_int
r_int
id|ssthresh
suffix:semicolon
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
DECL|member|cong_window
r_int
r_int
id|cong_window
suffix:semicolon
DECL|member|cong_count
r_int
r_int
id|cong_count
suffix:semicolon
DECL|member|packets_out
id|atomic_t
id|packets_out
suffix:semicolon
DECL|member|shutdown
r_int
r_int
id|shutdown
suffix:semicolon
DECL|member|window
r_int
r_int
id|window
suffix:semicolon
multiline_comment|/* used by netrom/ax.25 */
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
r_union
(brace
DECL|member|af_inet6
r_struct
id|ipv6_pinfo
id|af_inet6
suffix:semicolon
DECL|member|net_pinfo
)brace
id|net_pinfo
suffix:semicolon
macro_line|#endif
r_union
(brace
DECL|member|af_tcp
r_struct
id|tcp_opt
id|af_tcp
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|member|tp_raw
r_struct
id|raw6_opt
id|tp_raw
suffix:semicolon
macro_line|#endif
DECL|member|tp_pinfo
)brace
id|tp_pinfo
suffix:semicolon
multiline_comment|/*&n; *&t;currently backoff isn&squot;t used, but I&squot;m maintaining it in case&n; *&t;we want to go back to a backoff formula that needs it&n; */
multiline_comment|/* &n;&t;unsigned short&t;&t;backoff;&n; */
DECL|member|err
DECL|member|err_soft
r_int
id|err
comma
id|err_soft
suffix:semicolon
multiline_comment|/* Soft holds errors that don&squot;t&n;&t;&t;&t;&t;&t;&t;   cause failure but are the cause&n;&t;&t;&t;&t;&t;&t;   of a persistent failure not just&n;&t;&t;&t;&t;&t;&t;   &squot;timed out&squot; */
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|state
r_volatile
r_int
r_char
id|state
suffix:semicolon
DECL|member|ack_backlog
r_int
r_char
id|ack_backlog
suffix:semicolon
DECL|member|max_ack_backlog
r_int
r_char
id|max_ack_backlog
suffix:semicolon
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
DECL|member|debug
r_int
r_char
id|debug
suffix:semicolon
DECL|member|rcvbuf
r_int
id|rcvbuf
suffix:semicolon
DECL|member|sndbuf
r_int
id|sndbuf
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|localroute
r_int
r_char
id|localroute
suffix:semicolon
multiline_comment|/* Route locally only */
macro_line|#ifdef CONFIG_AX25
DECL|member|ax25
id|ax25_cb
op_star
id|ax25
suffix:semicolon
macro_line|#ifdef CONFIG_NETROM
DECL|member|nr
id|nr_cb
op_star
id|nr
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *&t;This is where all the private (optional) areas that don&squot;t&n; *&t;overlap will eventually live. &n; */
r_union
(brace
DECL|member|af_unix
r_struct
id|unix_opt
id|af_unix
suffix:semicolon
macro_line|#if defined(CONFIG_ATALK) || defined(CONFIG_ATALK_MODULE)
DECL|member|af_at
r_struct
id|atalk_sock
id|af_at
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_IPX) || defined(CONFIG_IPX_MODULE)
DECL|member|af_ipx
r_struct
id|ipx_opt
id|af_ipx
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_INET
DECL|member|af_packet
r_struct
id|inet_packet_opt
id|af_packet
suffix:semicolon
macro_line|#ifdef CONFIG_NUTCP&t;&t;
DECL|member|af_tcp
r_struct
id|tcp_opt
id|af_tcp
suffix:semicolon
macro_line|#endif&t;&t;
macro_line|#endif
DECL|member|protinfo
)brace
id|protinfo
suffix:semicolon
multiline_comment|/* &n; *&t;IP &squot;private area&squot; or will be eventually &n; */
DECL|member|ip_ttl
r_int
id|ip_ttl
suffix:semicolon
multiline_comment|/* TTL setting */
DECL|member|ip_tos
r_int
id|ip_tos
suffix:semicolon
multiline_comment|/* TOS */
DECL|member|dummy_th
r_struct
id|tcphdr
id|dummy_th
suffix:semicolon
DECL|member|keepalive_timer
r_struct
id|timer_list
id|keepalive_timer
suffix:semicolon
multiline_comment|/* TCP keepalive hack */
DECL|member|retransmit_timer
r_struct
id|timer_list
id|retransmit_timer
suffix:semicolon
multiline_comment|/* TCP retransmit timer */
DECL|member|delack_timer
r_struct
id|timer_list
id|delack_timer
suffix:semicolon
multiline_comment|/* TCP delayed ack timer */
DECL|member|ip_xmit_timeout
r_int
id|ip_xmit_timeout
suffix:semicolon
multiline_comment|/* Why the timeout is running */
DECL|member|ip_route_cache
r_struct
id|rtable
op_star
id|ip_route_cache
suffix:semicolon
multiline_comment|/* Cached output route */
DECL|member|ip_hdrincl
r_int
r_char
id|ip_hdrincl
suffix:semicolon
multiline_comment|/* Include headers ? */
macro_line|#ifdef CONFIG_IP_MULTICAST  
DECL|member|ip_mc_ttl
r_int
id|ip_mc_ttl
suffix:semicolon
multiline_comment|/* Multicasting TTL */
DECL|member|ip_mc_loop
r_int
id|ip_mc_loop
suffix:semicolon
multiline_comment|/* Loopback */
DECL|member|ip_mc_name
r_char
id|ip_mc_name
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
multiline_comment|/* Multicast device name */
DECL|member|ip_mc_list
r_struct
id|ip_mc_socklist
op_star
id|ip_mc_list
suffix:semicolon
multiline_comment|/* Group array */
macro_line|#endif  
multiline_comment|/*&n; *&t;This part is used for the timeout functions (timer.c). &n; */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* What are we waiting for? */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* This is the TIME_WAIT/receive timer&n;&t;&t;&t;&t;&t; * when we are doing IP&n;&t;&t;&t;&t;&t; */
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
multiline_comment|/*&n;  *&t;Identd &n;  */
DECL|member|socket
r_struct
id|socket
op_star
id|socket
suffix:semicolon
multiline_comment|/*&n;   *&t;Callbacks &n;   */
DECL|member|state_change
r_void
(paren
op_star
id|state_change
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|data_ready
r_void
(paren
op_star
id|data_ready
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|bytes
)paren
suffix:semicolon
DECL|member|write_space
r_void
(paren
op_star
id|write_space
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|error_report
r_void
(paren
op_star
id|error_report
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|backlog_rcv
r_int
(paren
op_star
id|backlog_rcv
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n; *&t;Inet protocol options&n; */
r_struct
id|inet_options
(brace
id|__u8
id|version
suffix:semicolon
r_union
(brace
r_struct
id|options
id|opt_v4
suffix:semicolon
r_struct
id|ipv6_options
id|opt_v6
suffix:semicolon
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;IP protocol blocks we attach to sockets.&n; *&t;socket layer -&gt; transport layer interface&n; *&t;transport -&gt; network interface is defined by struct inet_proto&n; */
DECL|struct|proto
r_struct
id|proto
(brace
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
DECL|member|connect
r_int
(paren
op_star
id|connect
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
suffix:semicolon
DECL|member|accept
r_struct
id|sock
op_star
(paren
op_star
id|accept
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|retransmit
r_void
(paren
op_star
id|retransmit
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|all
)paren
suffix:semicolon
DECL|member|write_wakeup
r_void
(paren
op_star
id|write_wakeup
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|read_wakeup
r_void
(paren
op_star
id|read_wakeup
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|select
r_int
(paren
op_star
id|select
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|which
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|destroy
r_int
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|how
)paren
suffix:semicolon
DECL|member|setsockopt
r_int
(paren
op_star
id|setsockopt
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
DECL|member|getsockopt
r_int
(paren
op_star
id|getsockopt
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|option
)paren
suffix:semicolon
DECL|member|sendmsg
r_int
(paren
op_star
id|sendmsg
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|recvmsg
r_int
(paren
op_star
id|recvmsg
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
suffix:semicolon
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
suffix:semicolon
DECL|member|backlog_rcv
r_int
(paren
op_star
id|backlog_rcv
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|max_header
r_int
r_int
id|max_header
suffix:semicolon
DECL|member|retransmits
r_int
r_int
id|retransmits
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|inuse
DECL|member|highestinuse
r_int
id|inuse
comma
id|highestinuse
suffix:semicolon
DECL|member|sock_array
r_struct
id|sock
op_star
op_star
id|sock_array
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TIME_WRITE
mdefine_line|#define TIME_WRITE&t;1&t;/* Not yet used */
DECL|macro|TIME_RETRANS
mdefine_line|#define TIME_RETRANS&t;2&t;/* Retransmit timer */
DECL|macro|TIME_DACK
mdefine_line|#define TIME_DACK&t;3&t;/* Delayed ack timer */
DECL|macro|TIME_CLOSE
mdefine_line|#define TIME_CLOSE&t;4
DECL|macro|TIME_KEEPOPEN
mdefine_line|#define TIME_KEEPOPEN&t;5
DECL|macro|TIME_DESTROY
mdefine_line|#define TIME_DESTROY&t;6
DECL|macro|TIME_DONE
mdefine_line|#define TIME_DONE&t;7&t;/* Used to absorb those last few packets */
DECL|macro|TIME_PROBE0
mdefine_line|#define TIME_PROBE0&t;8
multiline_comment|/*&n; *&t;About 10 seconds &n; */
DECL|macro|SOCK_DESTROY_TIME
mdefine_line|#define SOCK_DESTROY_TIME (10*HZ)
multiline_comment|/*&n; *&t;Sockets 0-1023 can&squot;t be bound to unless you are superuser &n; */
DECL|macro|PROT_SOCK
mdefine_line|#define PROT_SOCK&t;1024
DECL|macro|SHUTDOWN_MASK
mdefine_line|#define SHUTDOWN_MASK&t;3
DECL|macro|RCV_SHUTDOWN
mdefine_line|#define RCV_SHUTDOWN&t;1
DECL|macro|SEND_SHUTDOWN
mdefine_line|#define SEND_SHUTDOWN&t;2
multiline_comment|/*&n; * Used by processes to &quot;lock&quot; a socket state, so that&n; * interrupts and bottom half handlers won&squot;t change it&n; * from under us. It essentially blocks any incoming&n; * packets, so that we won&squot;t get any new data or any&n; * packets that change the state of the socket.&n; *&n; * Note the &squot;barrier()&squot; calls: gcc may not move a lock&n; * &quot;downwards&quot; or a unlock &quot;upwards&quot; when optimizing.&n; */
r_extern
r_void
id|__release_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|function|lock_sock
r_static
r_inline
r_void
id|lock_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
macro_line|#if 0
multiline_comment|/* debugging code: the test isn&squot;t even 100% correct, but it can catch bugs */
multiline_comment|/* Note that a double lock is ok in theory - it&squot;s just _usually_ a bug */
r_if
c_cond
(paren
id|sk-&gt;users
)paren
(brace
id|__label__
id|here
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;double lock on socket at %p&bslash;n&quot;
comma
op_logical_and
id|here
)paren
suffix:semicolon
id|here
suffix:colon
)brace
macro_line|#endif
id|sk-&gt;users
op_increment
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|release_sock
r_static
r_inline
r_void
id|release_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* debugging code: remove me when ok */
r_if
c_cond
(paren
id|sk-&gt;users
op_eq
l_int|0
)paren
(brace
id|__label__
id|here
suffix:semicolon
id|sk-&gt;users
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;trying to unlock unlocked socket at %p&bslash;n&quot;
comma
op_logical_and
id|here
)paren
suffix:semicolon
id|here
suffix:colon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|sk-&gt;users
op_assign
id|sk-&gt;users
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
id|__release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This might not be the most apropriate place for this two&t; &n; *&t;but since they are used by a lot of the net related code&n; *&t;at least they get declared on a include that is common to all&n; */
DECL|function|min
r_static
id|__inline__
r_int
id|min
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|a
OG
id|b
)paren
id|a
op_assign
id|b
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
DECL|function|max
r_static
id|__inline__
r_int
id|max
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|a
OL
id|b
)paren
id|a
op_assign
id|b
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
r_extern
r_struct
id|sock
op_star
id|sk_alloc
c_func
(paren
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|sk_free
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|destroy_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_new_socknum
c_func
(paren
r_struct
id|proto
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|inet_put_sock
c_func
(paren
r_int
r_int
comma
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|get_sock
c_func
(paren
r_struct
id|proto
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|get_sock_mcast
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|get_sock_raw
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|sock_wmalloc
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|sock_rmalloc
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|sock_wfree
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|sock_rfree
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sock_rspace
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sock_wspace
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|sock_setsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|op
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|sock_getsockopt
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|level
comma
r_int
id|op
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|sock_alloc_send_skb
c_func
(paren
r_struct
id|sock
op_star
id|skb
comma
r_int
r_int
id|size
comma
r_int
r_int
id|fallback
comma
r_int
id|noblock
comma
r_int
op_star
id|errcode
)paren
suffix:semicolon
multiline_comment|/*&n; * &t;Queue a received datagram if it will fit. Stream and sequenced&n; *&t;protocols can&squot;t normally use this as they need to fit buffers in&n; *&t;and play with them.&n; *&n; * &t;Inlined as it&squot;s very short and called for pretty much every&n; *&t;packet ever received.&n; */
DECL|function|sock_queue_rcv_skb
r_extern
id|__inline__
r_int
id|sock_queue_rcv_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
op_plus
id|skb-&gt;truesize
op_ge
id|sk-&gt;rcvbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|atomic_add
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|sk-&gt;rmem_alloc
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|sk
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__sock_queue_rcv_skb
r_extern
id|__inline__
r_int
id|__sock_queue_rcv_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
op_plus
id|skb-&gt;truesize
op_ge
id|sk-&gt;rcvbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|atomic_add
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|sk-&gt;rmem_alloc
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|__skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|sk
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Recover an error report and clear atomically&n; */
DECL|function|sock_error
r_extern
id|__inline__
r_int
id|sock_error
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|err
op_assign
id|xchg
c_func
(paren
op_amp
id|sk-&gt;err
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
id|err
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Declarations from timer.c &n; */
r_extern
r_struct
id|sock
op_star
id|timer_base
suffix:semicolon
r_extern
r_void
id|net_delete_timer
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|net_reset_timer
(paren
r_struct
id|sock
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|net_timer
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* &n; *&t;Enable debug/info messages &n; */
DECL|macro|NETDEBUG
mdefine_line|#define NETDEBUG(x)&t;do { } while (0)
macro_line|#endif&t;/* _SOCK_H */
eof
