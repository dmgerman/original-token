multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the TCP module.&n; *&n; * Version:&t;@(#)tcp.h&t;1.0.5&t;05/23/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _TCP_H
DECL|macro|_TCP_H
mdefine_line|#define _TCP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
DECL|macro|NETHDR_SIZE
mdefine_line|#define NETHDR_SIZE&t;sizeof(struct ipv6hdr)
macro_line|#else
DECL|macro|NETHDR_SIZE
mdefine_line|#define NETHDR_SIZE&t;sizeof(struct iphdr) + 40
macro_line|#endif
multiline_comment|/*&n; * 40 is maximal IP options size&n; * 4  is TCP option size (MSS)&n; */
DECL|macro|MAX_SYN_SIZE
mdefine_line|#define MAX_SYN_SIZE&t;(NETHDR_SIZE + sizeof(struct tcphdr) + 4 + MAX_HEADER + 15)
DECL|macro|MAX_FIN_SIZE
mdefine_line|#define MAX_FIN_SIZE&t;(NETHDR_SIZE + sizeof(struct tcphdr) + MAX_HEADER + 15)
DECL|macro|MAX_ACK_SIZE
mdefine_line|#define MAX_ACK_SIZE&t;(NETHDR_SIZE + sizeof(struct tcphdr) + MAX_HEADER + 15)
DECL|macro|MAX_RESET_SIZE
mdefine_line|#define MAX_RESET_SIZE&t;(NETHDR_SIZE + sizeof(struct tcphdr) + MAX_HEADER + 15)
DECL|macro|MAX_WINDOW
mdefine_line|#define MAX_WINDOW&t;32767&t;&t;/* Never offer a window over 32767 without using&n;&t;&t;&t;&t;&t;   window scaling (not yet supported). Some poor&n;&t;&t;&t;&t;&t;   stacks do signed 16bit maths! */
DECL|macro|MIN_WINDOW
mdefine_line|#define MIN_WINDOW&t;2048
DECL|macro|MAX_ACK_BACKLOG
mdefine_line|#define MAX_ACK_BACKLOG&t;2
DECL|macro|MAX_DELAY_ACK
mdefine_line|#define MAX_DELAY_ACK&t;2
DECL|macro|MIN_WRITE_SPACE
mdefine_line|#define MIN_WRITE_SPACE&t;2048
DECL|macro|TCP_WINDOW_DIFF
mdefine_line|#define TCP_WINDOW_DIFF&t;2048
multiline_comment|/* urg_data states */
DECL|macro|URG_VALID
mdefine_line|#define URG_VALID&t;0x0100
DECL|macro|URG_NOTYET
mdefine_line|#define URG_NOTYET&t;0x0200
DECL|macro|URG_READ
mdefine_line|#define URG_READ&t;0x0400
DECL|macro|TCP_RETR1
mdefine_line|#define TCP_RETR1&t;7&t;/*&n;&t;&t;&t;&t; * This is how many retries it does before it&n;&t;&t;&t;&t; * tries to figure out if the gateway is&n;&t;&t;&t;&t; * down.&n;&t;&t;&t;&t; */
DECL|macro|TCP_RETR2
mdefine_line|#define TCP_RETR2&t;15&t;/*&n;&t;&t;&t;&t; * This should take at least&n;&t;&t;&t;&t; * 90 minutes to time out.&n;&t;&t;&t;&t; */
DECL|macro|TCP_TIMEOUT_LEN
mdefine_line|#define TCP_TIMEOUT_LEN&t;(15*60*HZ) /* should be about 15 mins&t;&t;*/
DECL|macro|TCP_TIMEWAIT_LEN
mdefine_line|#define TCP_TIMEWAIT_LEN (60*HZ) /* how long to wait to successfully &n;&t;&t;&t;&t;  * close the socket, about 60 seconds&t;*/
DECL|macro|TCP_FIN_TIMEOUT
mdefine_line|#define TCP_FIN_TIMEOUT (3*60*HZ) /* BSD style FIN_WAIT2 deadlock breaker */
DECL|macro|TCP_ACK_TIME
mdefine_line|#define TCP_ACK_TIME&t;(3*HZ)&t;/* time to delay before sending an ACK&t;*/
DECL|macro|TCP_DONE_TIME
mdefine_line|#define TCP_DONE_TIME&t;(5*HZ/2)/* maximum time to wait before actually&n;&t;&t;&t;&t; * destroying a socket&t;&t;&t;*/
DECL|macro|TCP_WRITE_TIME
mdefine_line|#define TCP_WRITE_TIME&t;(30*HZ)&t;/* initial time to wait for an ACK,&n;&t;&t;&t;         * after last transmit&t;&t;&t;*/
DECL|macro|TCP_TIMEOUT_INIT
mdefine_line|#define TCP_TIMEOUT_INIT (3*HZ)&t;/* RFC 1122 initial timeout value&t;*/
DECL|macro|TCP_SYN_RETRIES
mdefine_line|#define TCP_SYN_RETRIES&t; 10&t;/* number of times to retry opening a&n;&t;&t;&t;&t; * connection &t;(TCP_RETR2-....)&t;*/
DECL|macro|TCP_PROBEWAIT_LEN
mdefine_line|#define TCP_PROBEWAIT_LEN (1*HZ)/* time to wait between probes when&n;&t;&t;&t;&t; * I&squot;ve got something to write and&n;&t;&t;&t;&t; * there is no window&t;&t;&t;*/
DECL|macro|TCP_KEEPALIVE_TIME
mdefine_line|#define TCP_KEEPALIVE_TIME (180*60*HZ)&t;/* two hours */
DECL|macro|TCP_KEEPALIVE_PROBES
mdefine_line|#define TCP_KEEPALIVE_PROBES&t;9&t;/* Max of 9 keepalive probes&t;*/
DECL|macro|TCP_KEEPALIVE_PERIOD
mdefine_line|#define TCP_KEEPALIVE_PERIOD (75*HZ)&t;/* period of keepalive check&t;*/
DECL|macro|TCP_NO_CHECK
mdefine_line|#define TCP_NO_CHECK&t;0&t;/* turn to one if you want the default&n;&t;&t;&t;&t; * to be no checksum&t;&t;&t;*/
DECL|macro|TCP_SYNACK_PERIOD
mdefine_line|#define TCP_SYNACK_PERIOD&t;(HZ/2)
multiline_comment|/*&n; *&t;TCP option&n; */
DECL|macro|TCPOPT_NOP
mdefine_line|#define TCPOPT_NOP&t;&t;1&t;/* Padding */
DECL|macro|TCPOPT_EOL
mdefine_line|#define TCPOPT_EOL&t;&t;0&t;/* End of options */
DECL|macro|TCPOPT_MSS
mdefine_line|#define TCPOPT_MSS&t;&t;2&t;/* Segment size negotiating */
multiline_comment|/*&n; *&t;We don&squot;t use these yet, but they are for PAWS and big windows&n; */
DECL|macro|TCPOPT_WINDOW
mdefine_line|#define TCPOPT_WINDOW&t;&t;3&t;/* Window scaling */
DECL|macro|TCPOPT_TIMESTAMP
mdefine_line|#define TCPOPT_TIMESTAMP&t;8&t;/* Better RTT estimations/PAWS */
multiline_comment|/*&n; *     TCP option lengths&n; */
DECL|macro|TCPOLEN_MSS
mdefine_line|#define TCPOLEN_MSS            4
DECL|macro|TCPOLEN_WINDOW
mdefine_line|#define TCPOLEN_WINDOW         3
DECL|macro|TCPOLEN_TIMESTAMP
mdefine_line|#define TCPOLEN_TIMESTAMP      10
multiline_comment|/*&n; *&t;TCP Vegas constants&n; */
DECL|macro|TCP_VEGAS_ALPHA
mdefine_line|#define TCP_VEGAS_ALPHA&t;&t;2&t;/*  v_cong_detect_top_nseg */
DECL|macro|TCP_VEGAS_BETA
mdefine_line|#define TCP_VEGAS_BETA&t;&t;4&t;/*  v_cong_detect_bot_nseg */
DECL|macro|TCP_VEGAS_GAMMA
mdefine_line|#define TCP_VEGAS_GAMMA&t;&t;1&t;/*  v_exp_inc_nseg&t;   */
r_struct
id|open_request
suffix:semicolon
DECL|struct|or_calltable
r_struct
id|or_calltable
(brace
DECL|member|rtx_syn_ack
r_void
(paren
op_star
id|rtx_syn_ack
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|open_request
op_star
id|req
)paren
suffix:semicolon
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|open_request
op_star
id|req
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|open_request
r_struct
id|open_request
(brace
DECL|member|dl_next
r_struct
id|open_request
op_star
id|dl_next
suffix:semicolon
DECL|member|dl_prev
r_struct
id|open_request
op_star
id|dl_prev
suffix:semicolon
DECL|member|rcv_isn
id|__u32
id|rcv_isn
suffix:semicolon
DECL|member|snt_isn
id|__u32
id|snt_isn
suffix:semicolon
DECL|member|mss
id|__u16
id|mss
suffix:semicolon
DECL|member|rmt_port
id|__u16
id|rmt_port
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|retrans
r_int
id|retrans
suffix:semicolon
DECL|member|class
r_struct
id|or_calltable
op_star
r_class
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcp_v4_open_req
r_struct
id|tcp_v4_open_req
(brace
DECL|member|req
r_struct
id|open_request
id|req
suffix:semicolon
DECL|member|loc_addr
id|__u32
id|loc_addr
suffix:semicolon
DECL|member|rmt_addr
id|__u32
id|rmt_addr
suffix:semicolon
DECL|member|opt
r_struct
id|options
op_star
id|opt
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|struct|tcp_v6_open_req
r_struct
id|tcp_v6_open_req
(brace
DECL|member|req
r_struct
id|open_request
id|req
suffix:semicolon
DECL|member|loc_addr
r_struct
id|in6_addr
id|loc_addr
suffix:semicolon
DECL|member|rmt_addr
r_struct
id|in6_addr
id|rmt_addr
suffix:semicolon
DECL|member|opt
r_struct
id|ipv6_options
op_star
id|opt
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Pointers to address related TCP functions&n; *&t;(i.e. things that depend on the address family)&n; */
DECL|struct|tcp_func
r_struct
id|tcp_func
(brace
DECL|member|build_net_header
r_int
(paren
op_star
id|build_net_header
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
DECL|member|queue_xmit
r_void
(paren
op_star
id|queue_xmit
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|free
)paren
suffix:semicolon
DECL|member|send_check
r_void
(paren
op_star
id|send_check
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|tcphdr
op_star
id|th
comma
r_int
id|len
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|rebuild_header
r_int
(paren
op_star
id|rebuild_header
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
DECL|member|conn_request
r_int
(paren
op_star
id|conn_request
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
comma
r_void
op_star
id|opt
comma
id|__u32
id|isn
)paren
suffix:semicolon
DECL|member|syn_recv_sock
r_struct
id|sock
op_star
(paren
op_star
id|syn_recv_sock
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
comma
r_struct
id|open_request
op_star
id|req
)paren
suffix:semicolon
DECL|member|init_sequence
id|__u32
(paren
op_star
id|init_sequence
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
DECL|member|get_sock
r_struct
id|sock
op_star
(paren
op_star
id|get_sock
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcphdr
op_star
id|th
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
id|optlen
)paren
suffix:semicolon
DECL|member|addr2sockaddr
r_void
(paren
op_star
id|addr2sockaddr
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
)paren
suffix:semicolon
DECL|member|sockaddr_len
r_int
id|sockaddr_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The next routines deal with comparing 32 bit unsigned ints&n; * and worry about wraparound (automatic with unsigned arithmetic).&n; */
DECL|function|before
r_extern
id|__inline
r_int
id|before
c_func
(paren
id|__u32
id|seq1
comma
id|__u32
id|seq2
)paren
(brace
r_return
(paren
id|__s32
)paren
(paren
id|seq1
op_minus
id|seq2
)paren
OL
l_int|0
suffix:semicolon
)brace
DECL|function|after
r_extern
id|__inline
r_int
id|after
c_func
(paren
id|__u32
id|seq1
comma
id|__u32
id|seq2
)paren
(brace
r_return
(paren
id|__s32
)paren
(paren
id|seq2
op_minus
id|seq1
)paren
OL
l_int|0
suffix:semicolon
)brace
multiline_comment|/* is s2&lt;=s1&lt;=s3 ? */
DECL|function|between
r_extern
id|__inline
r_int
id|between
c_func
(paren
id|__u32
id|seq1
comma
id|__u32
id|seq2
comma
id|__u32
id|seq3
)paren
(brace
r_return
(paren
id|after
c_func
(paren
id|seq1
op_plus
l_int|1
comma
id|seq2
)paren
op_logical_and
id|before
c_func
(paren
id|seq1
comma
id|seq3
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|proto
id|tcp_prot
suffix:semicolon
r_extern
r_struct
id|tcp_mib
id|tcp_statistics
suffix:semicolon
r_extern
r_void
id|tcp_v4_err
c_func
(paren
r_int
id|type
comma
r_int
id|code
comma
r_int
r_char
op_star
id|header
comma
id|__u32
id|info
comma
id|__u32
id|daddr
comma
id|__u32
id|saddr
comma
r_struct
id|inet_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_extern
r_void
id|tcp_shutdown
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
r_extern
r_int
id|tcp_v4_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|options
op_star
id|opt
comma
id|__u32
id|daddr
comma
r_int
r_int
id|len
comma
id|__u32
id|saddr
comma
r_int
id|redo
comma
r_struct
id|inet_protocol
op_star
id|protocol
)paren
suffix:semicolon
r_extern
r_int
id|tcp_do_sendmsg
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|iovlen
comma
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|len
comma
r_int
id|nonblock
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|tcp_ioctl
c_func
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
r_extern
r_int
id|tcp_rcv_state_process
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
comma
r_struct
id|tcphdr
op_star
id|th
comma
r_void
op_star
id|opt
comma
id|__u16
id|len
)paren
suffix:semicolon
r_extern
r_void
id|tcp_rcv_established
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
comma
r_struct
id|tcphdr
op_star
id|th
comma
id|__u16
id|len
)paren
suffix:semicolon
r_extern
r_void
id|tcp_close
c_func
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
r_extern
r_struct
id|sock
op_star
id|tcp_accept
c_func
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
r_extern
r_int
id|tcp_select
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
r_extern
r_int
id|tcp_getsockopt
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
id|optname
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
r_int
id|tcp_setsockopt
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
r_extern
r_void
id|tcp_set_keepalive
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|tcp_recvmsg
c_func
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
id|nonblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
suffix:semicolon
r_extern
r_int
id|tcp_parse_options
c_func
(paren
r_struct
id|tcphdr
op_star
id|th
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;TCP v4 functions exported for the inet6 API&n; */
r_extern
r_int
id|tcp_v4_rebuild_header
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
id|tcp_v4_build_header
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
id|tcp_v4_send_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|tcphdr
op_star
id|th
comma
r_int
id|len
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|tcp_v4_conn_request
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
comma
r_void
op_star
id|ptr
comma
id|__u32
id|isn
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|tcp_v4_syn_recv_sock
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
comma
r_struct
id|open_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|tcp_v4_backlog_rcv
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
id|tcp_v4_connect
c_func
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
r_extern
r_void
id|tcp_read_wakeup
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_write_xmit
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_time_wait
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_do_retransmit
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* tcp_output.c */
r_extern
r_void
id|tcp_send_probe0
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_send_partial
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_write_wakeup
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_send_fin
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
id|tcp_send_synack
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tcp_send_skb
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_send_ack
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
id|tcp_send_delayed_ack
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|max_timeout
)paren
suffix:semicolon
multiline_comment|/* tcp_input.c */
r_extern
r_void
id|tcp_cache_zap
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CONFIG_IP_TRANSPARENT_PROXY */
r_extern
r_int
id|tcp_chkaddr
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* tcp_timer.c */
DECL|macro|tcp_reset_msl_timer
mdefine_line|#define     tcp_reset_msl_timer(x,y,z)&t;net_reset_timer(x,y,z)
r_extern
r_void
id|tcp_reset_xmit_timer
c_func
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
id|tcp_clear_xmit_timer
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcp_timer_is_set
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tcp_init_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_clear_xmit_timers
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_retransmit_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tcp_delack_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tcp_probe_timer
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;TCP slow timer&n; */
r_extern
r_struct
id|timer_list
id|tcp_slow_timer
suffix:semicolon
DECL|struct|tcp_sl_timer
r_struct
id|tcp_sl_timer
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|period
r_int
r_int
id|period
suffix:semicolon
DECL|member|last
r_int
r_int
id|last
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TCP_SLT_SYNACK
mdefine_line|#define TCP_SLT_SYNACK&t;&t;0
DECL|macro|TCP_SLT_KEEPALIVE
mdefine_line|#define TCP_SLT_KEEPALIVE&t;1
DECL|macro|TCP_SLT_MAX
mdefine_line|#define TCP_SLT_MAX&t;&t;2
r_extern
r_struct
id|tcp_sl_timer
id|tcp_slt_array
(braket
id|TCP_SLT_MAX
)braket
suffix:semicolon
DECL|function|tcp_raise_window
r_static
id|__inline__
r_int
r_int
id|tcp_raise_window
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_int
id|cur_win
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;         * compute the actual window i.e. &n;         * old_window - received_bytes_on_that_win&n;&t; */
id|cur_win
op_assign
id|tp-&gt;rcv_wup
op_minus
(paren
id|tp-&gt;rcv_nxt
op_minus
id|tp-&gt;rcv_wnd
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;We need to send an ack right away if&n;&t; *&t;our rcv window is blocking the sender and &n;&t; *&t;we have more free space to offer.&n;&t; */
r_if
c_cond
(paren
id|cur_win
OL
(paren
id|sk-&gt;mss
op_lshift
l_int|1
)paren
)paren
id|res
op_assign
l_int|1
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_extern
r_int
r_int
id|tcp_select_window
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n; * List all states of a TCP socket that can be viewed as a &quot;connected&quot;&n; * state.  This now includes TCP_SYN_RECV, although I am not yet fully&n; * convinced that this is the solution for the &squot;getpeername(2)&squot;&n; * problem. Thanks to Stephen A. Wood &lt;saw@cebaf.gov&gt;  -FvK&n; */
DECL|function|tcp_connected
r_extern
id|__inline
r_const
r_int
id|tcp_connected
c_func
(paren
r_const
r_int
id|state
)paren
(brace
r_return
id|state
op_eq
id|TCP_ESTABLISHED
op_logical_or
id|state
op_eq
id|TCP_CLOSE_WAIT
op_logical_or
id|state
op_eq
id|TCP_FIN_WAIT1
op_logical_or
id|state
op_eq
id|TCP_FIN_WAIT2
op_logical_or
id|state
op_eq
id|TCP_SYN_RECV
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate(/check) TCP checksum&n; */
DECL|function|tcp_v4_check
r_static
id|__inline__
id|u16
id|tcp_v4_check
c_func
(paren
r_struct
id|tcphdr
op_star
id|th
comma
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|base
)paren
(brace
r_return
id|csum_tcpudp_magic
c_func
(paren
id|saddr
comma
id|daddr
comma
id|len
comma
id|IPPROTO_TCP
comma
id|base
)paren
suffix:semicolon
)brace
DECL|macro|STATE_TRACE
macro_line|#undef STATE_TRACE
macro_line|#ifdef STATE_TRACE
DECL|variable|statename
r_static
r_char
op_star
id|statename
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#endif
DECL|function|tcp_set_state
r_static
id|__inline__
r_void
id|tcp_set_state
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|state
)paren
(brace
r_struct
id|tcp_opt
op_star
id|tp
op_assign
op_amp
id|sk-&gt;tp_pinfo.af_tcp
suffix:semicolon
r_int
id|oldstate
op_assign
id|sk-&gt;state
suffix:semicolon
id|sk-&gt;state
op_assign
id|state
suffix:semicolon
macro_line|#ifdef STATE_TRACE
r_if
c_cond
(paren
id|sk-&gt;debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TCP sk=%p, State %s -&gt; %s&bslash;n&quot;
comma
id|sk
comma
id|statename
(braket
id|oldstate
)braket
comma
id|statename
(braket
id|state
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|TCP_ESTABLISHED
suffix:colon
r_if
c_cond
(paren
id|oldstate
op_ne
id|TCP_ESTABLISHED
)paren
(brace
id|tcp_statistics.TcpCurrEstab
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TCP_CLOSE
suffix:colon
id|tcp_cache_zap
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Should be about 2 rtt&squot;s */
id|net_reset_timer
c_func
(paren
id|sk
comma
id|TIME_DONE
comma
id|min
c_func
(paren
id|tp-&gt;srtt
op_star
l_int|2
comma
id|TCP_DONE_TIME
)paren
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|oldstate
op_eq
id|TCP_ESTABLISHED
)paren
id|tcp_statistics.TcpCurrEstab
op_decrement
suffix:semicolon
)brace
)brace
DECL|function|tcp_synq_unlink
r_extern
id|__inline__
r_void
id|tcp_synq_unlink
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|open_request
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;dl_next
op_eq
id|req
)paren
(brace
id|tp-&gt;syn_wait_queue
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|req-&gt;dl_prev-&gt;dl_next
op_assign
id|req-&gt;dl_next
suffix:semicolon
id|req-&gt;dl_next-&gt;dl_prev
op_assign
id|req-&gt;dl_prev
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;syn_wait_queue
op_eq
id|req
)paren
(brace
id|tp-&gt;syn_wait_queue
op_assign
id|req-&gt;dl_next
suffix:semicolon
)brace
)brace
id|req-&gt;dl_prev
op_assign
id|req-&gt;dl_next
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|tcp_synq_queue
r_extern
id|__inline__
r_void
id|tcp_synq_queue
c_func
(paren
r_struct
id|tcp_opt
op_star
id|tp
comma
r_struct
id|open_request
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tp-&gt;syn_wait_queue
)paren
(brace
id|req-&gt;dl_next
op_assign
id|req
suffix:semicolon
id|req-&gt;dl_prev
op_assign
id|req
suffix:semicolon
id|tp-&gt;syn_wait_queue
op_assign
id|req
suffix:semicolon
)brace
r_else
(brace
r_struct
id|open_request
op_star
id|list
op_assign
id|tp-&gt;syn_wait_queue
suffix:semicolon
id|req-&gt;dl_next
op_assign
id|list
suffix:semicolon
id|req-&gt;dl_prev
op_assign
id|list-&gt;dl_prev
suffix:semicolon
id|list-&gt;dl_prev-&gt;dl_next
op_assign
id|req
suffix:semicolon
id|list-&gt;dl_prev
op_assign
id|req
suffix:semicolon
)brace
)brace
r_extern
r_void
id|__tcp_inc_slow_timer
c_func
(paren
r_struct
id|tcp_sl_timer
op_star
id|slt
)paren
suffix:semicolon
DECL|function|tcp_inc_slow_timer
r_extern
id|__inline__
r_void
id|tcp_inc_slow_timer
c_func
(paren
r_int
id|timer
)paren
(brace
r_struct
id|tcp_sl_timer
op_star
id|slt
op_assign
op_amp
id|tcp_slt_array
(braket
id|timer
)braket
suffix:semicolon
r_if
c_cond
(paren
id|slt-&gt;count
op_eq
l_int|0
)paren
(brace
id|__tcp_inc_slow_timer
c_func
(paren
id|slt
)paren
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|slt-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|tcp_dec_slow_timer
r_extern
id|__inline__
r_void
id|tcp_dec_slow_timer
c_func
(paren
r_int
id|timer
)paren
(brace
r_struct
id|tcp_sl_timer
op_star
id|slt
op_assign
op_amp
id|tcp_slt_array
(braket
id|timer
)braket
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|slt-&gt;count
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* _TCP_H */
eof
