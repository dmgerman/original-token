multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;RAW - implementation of IP &quot;raw&quot; sockets.&n; *&n; * Version:&t;@(#)raw.c&t;1.0.4&t;05/25/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;verify_area() fixed up&n; *&t;&t;Alan Cox&t;:&t;ICMP error handling&n; *&t;&t;Alan Cox&t;:&t;EMSGSIZE if you send too big a packet&n; *&t;&t;Alan Cox&t;: &t;Now uses generic datagrams and shared skbuff&n; *&t;&t;&t;&t;&t;library. No more peek crashes, no more backlogs&n; *&t;&t;Alan Cox&t;:&t;Checks sk-&gt;broadcast.&n; *&t;&t;Alan Cox&t;:&t;Uses skb_free_datagram/skb_copy_datagram&n; *&t;&t;Alan Cox&t;:&t;Raw passes ip options too&n; *&t;&t;Alan Cox&t;:&t;Setsocketopt added&n; *&t;&t;Alan Cox&t;:&t;Fixed error return for broadcasts&n; *&t;&t;Alan Cox&t;:&t;Removed wake_up calls&n; *&t;&t;Alan Cox&t;:&t;Use ttl/tos&n; *&t;&t;Alan Cox&t;:&t;Cleaned up old debugging&n; *&t;&t;Alan Cox&t;:&t;Use new kernel side addresses&n; *&t;Arnt Gulbrandsen&t;:&t;Fixed MSG_DONTROUTE in raw sockets.&n; *&t;&t;Alan Cox&t;:&t;BSD style RAW socket demultiplexing.&n; *&t;&t;Alan Cox&t;:&t;Beginnings of mrouted support.&n; *&t;&t;Alan Cox&t;:&t;Added IP_HDRINCL option.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#ifdef CONFIG_IP_MROUTE
DECL|variable|mroute_socket
r_struct
id|sock
op_star
id|mroute_socket
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|function|min
r_static
r_inline
r_int
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
OL
id|b
)paren
r_return
id|a
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Raw_err does not currently get called by the icmp module - FIXME:&n; */
DECL|function|raw_err
r_void
id|raw_err
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
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|protocol-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* This is meaningless in raw sockets. */
r_if
c_cond
(paren
id|type
op_eq
id|ICMP_SOURCE_QUENCH
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;cong_window
OG
l_int|1
)paren
id|sk-&gt;cong_window
op_assign
id|sk-&gt;cong_window
op_div
l_int|2
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|ICMP_PARAMETERPROB
)paren
(brace
id|sk-&gt;err
op_assign
id|EPROTO
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|code
OL
l_int|13
)paren
(brace
id|sk-&gt;err
op_assign
id|icmp_err_convert
(braket
id|code
op_amp
l_int|0xff
)braket
dot
id|errno
suffix:semicolon
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This should be the easiest of all, all we do is&n; *&t;copy it into a buffer. All demultiplexing is done&n; *&t;in ip.c&n; */
DECL|function|raw_rcv
r_int
id|raw_rcv
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
id|device
op_star
id|dev
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
)paren
(brace
multiline_comment|/* Now we need to copy this into memory. */
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|ntohs
c_func
(paren
id|skb-&gt;ip_hdr-&gt;tot_len
)paren
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
(paren
r_int
r_char
op_star
)paren
id|skb-&gt;ip_hdr
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;saddr
op_assign
id|daddr
suffix:semicolon
id|skb-&gt;daddr
op_assign
id|saddr
suffix:semicolon
multiline_comment|/* Charge it to the socket. */
r_if
c_cond
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
OL
l_int|0
)paren
(brace
id|ip_statistics.IpInDiscards
op_increment
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ip_statistics.IpInDelivers
op_increment
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send a RAW IP packet.&n; */
multiline_comment|/*&n; *&t;Callback support is trivial for SOCK_RAW&n; */
DECL|function|raw_getfrag
r_static
r_void
id|raw_getfrag
c_func
(paren
r_const
r_void
op_star
id|p
comma
id|__u32
id|saddr
comma
r_char
op_star
id|to
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|fraglen
)paren
(brace
id|memcpy_fromfs
c_func
(paren
id|to
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|p
op_plus
id|offset
comma
id|fraglen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;IPPROTO_RAW needs extra work.&n; */
DECL|function|raw_getrawfrag
r_static
r_void
id|raw_getrawfrag
c_func
(paren
r_const
r_void
op_star
id|p
comma
id|__u32
id|saddr
comma
r_char
op_star
id|to
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|fraglen
)paren
(brace
id|memcpy_fromfs
c_func
(paren
id|to
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|p
op_plus
id|offset
comma
id|fraglen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|to
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|saddr
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|fraglen
)paren
suffix:semicolon
multiline_comment|/* This is right as you cant frag&n;&t;&t;&t;&t;&t;   RAW packets */
multiline_comment|/*&n;&t; &t; *&t;Deliberate breach of modularity to keep &n;&t; &t; *&t;ip_build_xmit clean (well less messy).&n;&t;&t; */
id|iph-&gt;id
op_assign
id|htons
c_func
(paren
id|ip_id_count
op_increment
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
suffix:semicolon
)brace
)brace
DECL|function|raw_sendto
r_static
r_int
id|raw_sendto
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_const
r_int
r_char
op_star
id|from
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
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
id|addr_len
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check the flags. Only MSG_DONTROUTE is permitted.&n;&t; */
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_OOB
)paren
multiline_comment|/* Mirror BSD error message compatibility */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
id|MSG_DONTROUTE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get and verify the address. &n;&t; */
r_if
c_cond
(paren
id|usin
)paren
(brace
r_if
c_cond
(paren
id|addr_len
OL
r_sizeof
(paren
id|sin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sin
comma
id|usin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sin.sin_family
op_logical_and
id|sin.sin_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_port
op_assign
id|sk-&gt;protocol
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|sk-&gt;daddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sin.sin_port
op_eq
l_int|0
)paren
id|sin.sin_port
op_assign
id|sk-&gt;protocol
suffix:semicolon
r_if
c_cond
(paren
id|sin.sin_addr.s_addr
op_eq
id|INADDR_ANY
)paren
id|sin.sin_addr.s_addr
op_assign
id|ip_my_addr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;broadcast
op_eq
l_int|0
op_logical_and
id|ip_chk_addr
c_func
(paren
id|sin.sin_addr.s_addr
)paren
op_eq
id|IS_BROADCAST
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;ip_hdrincl
)paren
(brace
id|err
op_assign
id|ip_build_xmit
c_func
(paren
id|sk
comma
id|raw_getrawfrag
comma
id|from
comma
id|len
comma
id|sin.sin_addr.s_addr
comma
id|flags
comma
id|sin.sin_port
)paren
suffix:semicolon
)brace
r_else
id|err
op_assign
id|ip_build_xmit
c_func
(paren
id|sk
comma
id|raw_getfrag
comma
id|from
comma
id|len
comma
id|sin.sin_addr.s_addr
comma
id|flags
comma
id|sin.sin_port
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
id|len
suffix:semicolon
)brace
DECL|function|raw_write
r_static
r_int
id|raw_write
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_const
r_int
r_char
op_star
id|buff
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
(brace
r_return
id|raw_sendto
c_func
(paren
id|sk
comma
id|buff
comma
id|len
comma
id|noblock
comma
id|flags
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|raw_close
r_static
r_void
id|raw_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|timeout
)paren
(brace
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MROUTE&t;
r_if
c_cond
(paren
id|sk
op_eq
id|mroute_socket
)paren
(brace
id|mroute_close
c_func
(paren
id|sk
)paren
suffix:semicolon
id|mroute_socket
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif&t;
)brace
DECL|function|raw_init
r_static
r_int
id|raw_init
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This should be easy, if there is something there&n; *&t;we return it, otherwise we block.&n; */
DECL|function|raw_recvfrom
r_int
id|raw_recvfrom
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|to
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
r_struct
id|sockaddr_in
op_star
id|sin
comma
r_int
op_star
id|addr_len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_OOB
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;shutdown
op_amp
id|RCV_SHUTDOWN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
op_star
id|addr_len
op_assign
r_sizeof
(paren
op_star
id|sin
)paren
suffix:semicolon
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|copied
op_assign
id|min
c_func
(paren
id|len
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|skb_copy_datagram
c_func
(paren
id|skb
comma
l_int|0
comma
id|to
comma
id|copied
)paren
suffix:semicolon
id|sk-&gt;stamp
op_assign
id|skb-&gt;stamp
suffix:semicolon
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|sin
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|skb-&gt;daddr
suffix:semicolon
)brace
id|skb_free_datagram
c_func
(paren
id|skb
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
id|copied
)paren
suffix:semicolon
)brace
DECL|function|raw_read
r_int
id|raw_read
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|buff
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
(brace
r_return
id|raw_recvfrom
c_func
(paren
id|sk
comma
id|buff
comma
id|len
comma
id|noblock
comma
id|flags
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|raw_prot
r_struct
id|proto
id|raw_prot
op_assign
(brace
id|sock_wmalloc
comma
id|sock_rmalloc
comma
id|sock_wfree
comma
id|sock_rfree
comma
id|sock_rspace
comma
id|sock_wspace
comma
id|raw_close
comma
id|raw_read
comma
id|raw_write
comma
id|raw_sendto
comma
id|raw_recvfrom
comma
id|ip_build_header
comma
id|udp_connect
comma
l_int|NULL
comma
id|ip_queue_xmit
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|datagram_select
comma
macro_line|#ifdef CONFIG_IP_MROUTE&t;
id|ipmr_ioctl
comma
macro_line|#else
l_int|NULL
comma
macro_line|#endif&t;&t;
id|raw_init
comma
l_int|NULL
comma
id|ip_setsockopt
comma
id|ip_getsockopt
comma
l_int|128
comma
l_int|0
comma
l_string|&quot;RAW&quot;
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|NULL
comma
)brace
)brace
suffix:semicolon
eof
