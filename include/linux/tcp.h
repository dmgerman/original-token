multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the TCP protocol.&n; *&n; * Version:&t;@(#)tcp.h&t;1.0.2&t;04/28/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_TCP_H
DECL|macro|_LINUX_TCP_H
mdefine_line|#define _LINUX_TCP_H
DECL|macro|HEADER_SIZE
mdefine_line|#define HEADER_SIZE&t;64&t;&t;/* maximum header size&t;&t;*/
DECL|struct|tcphdr
r_struct
id|tcphdr
(brace
DECL|member|source
r_int
r_int
id|source
suffix:semicolon
DECL|member|dest
r_int
r_int
id|dest
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
DECL|member|ack_seq
r_int
r_int
id|ack_seq
suffix:semicolon
DECL|member|res1
r_int
r_int
id|res1
suffix:colon
l_int|4
comma
DECL|member|doff
id|doff
suffix:colon
l_int|4
comma
DECL|member|fin
id|fin
suffix:colon
l_int|1
comma
DECL|member|syn
id|syn
suffix:colon
l_int|1
comma
DECL|member|rst
id|rst
suffix:colon
l_int|1
comma
DECL|member|psh
id|psh
suffix:colon
l_int|1
comma
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
DECL|member|urg
id|urg
suffix:colon
l_int|1
comma
DECL|member|res2
id|res2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|window
r_int
r_int
id|window
suffix:semicolon
DECL|member|check
r_int
r_int
id|check
suffix:semicolon
DECL|member|urg_ptr
r_int
r_int
id|urg_ptr
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCP_ESTABLISHED
id|TCP_ESTABLISHED
op_assign
l_int|1
comma
DECL|enumerator|TCP_SYN_SENT
id|TCP_SYN_SENT
comma
DECL|enumerator|TCP_SYN_RECV
id|TCP_SYN_RECV
comma
macro_line|#if 0
id|TCP_CLOSING
comma
multiline_comment|/* not a valid state, just a seperator so we can use&n;&t;&t;  &lt; tcp_closing or &gt; tcp_closing for checks. */
macro_line|#endif
DECL|enumerator|TCP_FIN_WAIT1
id|TCP_FIN_WAIT1
comma
DECL|enumerator|TCP_FIN_WAIT2
id|TCP_FIN_WAIT2
comma
DECL|enumerator|TCP_TIME_WAIT
id|TCP_TIME_WAIT
comma
DECL|enumerator|TCP_CLOSE
id|TCP_CLOSE
comma
DECL|enumerator|TCP_CLOSE_WAIT
id|TCP_CLOSE_WAIT
comma
DECL|enumerator|TCP_LAST_ACK
id|TCP_LAST_ACK
comma
DECL|enumerator|TCP_LISTEN
id|TCP_LISTEN
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_TCP_H */
eof