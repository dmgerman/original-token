multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the TCP module.&n; *&n; * Version:&t;@(#)tcp.h&t;1.0.5&t;05/23/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _TCP_H
DECL|macro|_TCP_H
mdefine_line|#define _TCP_H
macro_line|#include &lt;linux/tcp.h&gt;
DECL|macro|MAX_SYN_SIZE
mdefine_line|#define MAX_SYN_SIZE&t;44 + MAX_HEADER
DECL|macro|MAX_FIN_SIZE
mdefine_line|#define MAX_FIN_SIZE&t;40 + MAX_HEADER
DECL|macro|MAX_ACK_SIZE
mdefine_line|#define MAX_ACK_SIZE&t;40 + MAX_HEADER
DECL|macro|MAX_RESET_SIZE
mdefine_line|#define MAX_RESET_SIZE&t;40 + MAX_HEADER
DECL|macro|MAX_WINDOW
mdefine_line|#define MAX_WINDOW&t;16384
DECL|macro|MIN_WINDOW
mdefine_line|#define MIN_WINDOW&t;2048
DECL|macro|MAX_ACK_BACKLOG
mdefine_line|#define MAX_ACK_BACKLOG&t;2
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
mdefine_line|#define TCP_FIN_TIMEOUT (3*60*HZ) /* BSD style FIN_WAIT2 deadlock breaker */&t;&t;&t;&t;  
DECL|macro|TCP_ACK_TIME
mdefine_line|#define TCP_ACK_TIME&t;(3*HZ)&t;/* time to delay before sending an ACK&t;*/
DECL|macro|TCP_DONE_TIME
mdefine_line|#define TCP_DONE_TIME&t;250&t;/* maximum time to wait before actually&n;&t;&t;&t;&t; * destroying a socket&t;&t;&t;*/
DECL|macro|TCP_WRITE_TIME
mdefine_line|#define TCP_WRITE_TIME&t;3000&t;/* initial time to wait for an ACK,&n;&t;&t;&t;         * after last transmit&t;&t;&t;*/
DECL|macro|TCP_TIMEOUT_INIT
mdefine_line|#define TCP_TIMEOUT_INIT (3*HZ)&t;/* RFC 1122 initial timeout value&t;*/
DECL|macro|TCP_SYN_RETRIES
mdefine_line|#define TCP_SYN_RETRIES&t; 10&t;/* number of times to retry opening a&n;&t;&t;&t;&t; * connection &t;(TCP_RETR2-....)&t;*/
DECL|macro|TCP_PROBEWAIT_LEN
mdefine_line|#define TCP_PROBEWAIT_LEN 100&t;/* time to wait between probes when&n;&t;&t;&t;&t; * I&squot;ve got something to write and&n;&t;&t;&t;&t; * there is no window&t;&t;&t;*/
DECL|macro|TCP_NO_CHECK
mdefine_line|#define TCP_NO_CHECK&t;0&t;/* turn to one if you want the default&n;&t;&t;&t;&t; * to be no checksum&t;&t;&t;*/
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
multiline_comment|/*&n; * The next routines deal with comparing 32 bit unsigned ints&n; * and worry about wraparound (automatic with unsigned arithmetic).&n; */
DECL|function|before
r_extern
id|__inline
r_int
id|before
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
r_return
(paren
r_int
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
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
r_return
(paren
r_int
)paren
(paren
id|seq1
op_minus
id|seq2
)paren
OG
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
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
comma
r_int
r_int
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
multiline_comment|/*&n; * List all states of a TCP socket that can be viewed as a &quot;connected&quot;&n; * state.  This now includes TCP_SYN_RECV, although I am not yet fully&n; * convinced that this is the solution for the &squot;getpeername(2)&squot;&n; * problem. Thanks to Stephen A. Wood &lt;saw@cebaf.gov&gt;  -FvK&n; */
r_extern
id|__inline
r_const
r_int
DECL|function|tcp_connected
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
r_extern
r_struct
id|proto
id|tcp_prot
suffix:semicolon
r_extern
r_void
id|tcp_err
c_func
(paren
r_int
id|err
comma
r_int
r_char
op_star
id|header
comma
r_int
r_int
id|daddr
comma
r_int
r_int
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
id|tcp_rcv
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
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
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
id|tcp_select_window
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
id|tcp_send_check
c_func
(paren
r_struct
id|tcphdr
op_star
id|th
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
id|len
comma
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|tcp_send_probe0
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
id|tcp_enqueue_partial
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|tcp_dequeue_partial
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tcp_cache_zap
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* _TCP_H */
eof
