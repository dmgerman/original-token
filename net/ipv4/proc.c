multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  It is mainly used for debugging and&n; *&t;&t;statistics.&n; *&n; * Version:&t;@(#)proc.c&t;1.0.5&t;05/27/93&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Gerald J. Heim, &lt;heim@peanuts.informatik.uni-tuebingen.de&gt;&n; *&t;&t;Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;&n; *&t;&t;Erik Schoenfelder, &lt;schoenfr@ibr.cs.tu-bs.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;UDP sockets show the rxqueue/txqueue&n; *&t;&t;&t;&t;&t;using hint flag for the netinfo.&n; *&t;Pauline Middelink&t;:&t;identd support&n; *&t;&t;Alan Cox&t;:&t;Make /proc safer.&n; *&t;Erik Schoenfelder&t;:&t;/proc/net/snmp&n; *&t;&t;Alan Cox&t;:&t;Handle dead sockets properly.&n; *&t;Gerhard Koerting&t;:&t;Show both timers&n; *&t;&t;Alan Cox&t;:&t;Allow inode to be NULL (kernel socket)&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/un.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/raw.h&gt;
multiline_comment|/*&n; * Get__netinfo returns the length of that string.&n; *&n; * KNOWN BUGS&n; *  As in get_unix_netinfo, the buffer might be too small. If this&n; *  happens, get__netinfo returns only part of the available infos.&n; */
r_static
r_int
DECL|function|get__netinfo
id|get__netinfo
c_func
(paren
r_struct
id|proto
op_star
id|pro
comma
r_char
op_star
id|buffer
comma
r_int
id|format
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_struct
id|sock
op_star
id|sp
suffix:semicolon
r_struct
id|tcp_opt
op_star
id|tp
suffix:semicolon
r_int
id|timer_active
comma
id|timer_active1
comma
id|timer_active2
suffix:semicolon
r_int
r_int
id|timer_expires
suffix:semicolon
r_int
r_int
id|dest
comma
id|src
suffix:semicolon
r_int
r_int
id|destp
comma
id|srcp
suffix:semicolon
r_int
id|len
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_char
id|tmpbuf
(braket
l_int|129
)braket
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|128
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-127s&bslash;n&quot;
comma
l_string|&quot;  sl  local_address rem_address   st tx_queue &quot;
l_string|&quot;rx_queue tr tm-&gt;when retrnsmt   uid  timeout inode&quot;
)paren
suffix:semicolon
id|pos
op_assign
l_int|128
suffix:semicolon
multiline_comment|/*&n; *&t;This was very pretty but didn&squot;t work when a socket is destroyed&n; *&t;at the wrong moment (eg a syn recv socket getting a reset), or&n; *&t;a memory timer destroy. Instead of playing with timers we just&n; *&t;concede defeat and cli().&n; */
id|SOCKHASH_LOCK
c_func
(paren
)paren
suffix:semicolon
id|sp
op_assign
id|pro-&gt;sklist_next
suffix:semicolon
r_while
c_loop
(paren
id|sp
op_ne
(paren
r_struct
id|sock
op_star
)paren
id|pro
)paren
(brace
id|pos
op_add_assign
l_int|128
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
r_goto
id|next
suffix:semicolon
id|tp
op_assign
op_amp
(paren
id|sp-&gt;tp_pinfo.af_tcp
)paren
suffix:semicolon
id|dest
op_assign
id|sp-&gt;daddr
suffix:semicolon
id|src
op_assign
id|sp-&gt;saddr
suffix:semicolon
id|destp
op_assign
id|sp-&gt;dummy_th.dest
suffix:semicolon
id|srcp
op_assign
id|sp-&gt;dummy_th.source
suffix:semicolon
multiline_comment|/* Since we are Little Endian we need to swap the bytes :-( */
id|destp
op_assign
id|ntohs
c_func
(paren
id|destp
)paren
suffix:semicolon
id|srcp
op_assign
id|ntohs
c_func
(paren
id|srcp
)paren
suffix:semicolon
id|timer_active1
op_assign
id|del_timer
c_func
(paren
op_amp
id|sp-&gt;retransmit_timer
)paren
suffix:semicolon
id|timer_active2
op_assign
id|del_timer
c_func
(paren
op_amp
id|sp-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_active1
)paren
id|sp-&gt;retransmit_timer.expires
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_active2
)paren
id|sp-&gt;timer.expires
op_assign
l_int|0
suffix:semicolon
id|timer_active
op_assign
l_int|0
suffix:semicolon
id|timer_expires
op_assign
(paren
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|timer_active1
op_logical_and
id|sp-&gt;retransmit_timer.expires
OL
id|timer_expires
)paren
(brace
id|timer_active
op_assign
id|timer_active1
suffix:semicolon
id|timer_expires
op_assign
id|sp-&gt;retransmit_timer.expires
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timer_active2
op_logical_and
id|sp-&gt;timer.expires
OL
id|timer_expires
)paren
(brace
id|timer_active
op_assign
id|timer_active2
suffix:semicolon
id|timer_expires
op_assign
id|sp-&gt;timer.expires
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|tmpbuf
comma
l_string|&quot;%4d: %08lX:%04X %08lX:%04X&quot;
l_string|&quot; %02X %08X:%08X %02X:%08lX %08X %5d %8d %ld&quot;
comma
id|i
comma
id|src
comma
id|srcp
comma
id|dest
comma
id|destp
comma
id|sp-&gt;state
comma
id|format
op_eq
l_int|0
ques
c_cond
id|sp-&gt;write_seq
op_minus
id|tp-&gt;snd_una
suffix:colon
id|sp-&gt;wmem_alloc
comma
id|format
op_eq
l_int|0
ques
c_cond
id|tp-&gt;rcv_nxt
op_minus
id|sp-&gt;copied_seq
suffix:colon
id|sp-&gt;rmem_alloc
comma
id|timer_active
comma
id|timer_expires
op_minus
id|jiffies
comma
(paren
r_int
)paren
id|sp-&gt;retransmits
comma
id|sp-&gt;socket
ques
c_cond
id|sp-&gt;socket-&gt;inode-&gt;i_uid
suffix:colon
l_int|0
comma
id|timer_active
ques
c_cond
id|sp-&gt;timeout
suffix:colon
l_int|0
comma
id|sp-&gt;socket
ques
c_cond
id|sp-&gt;socket-&gt;inode-&gt;i_ino
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_active1
)paren
id|add_timer
c_func
(paren
op_amp
id|sp-&gt;retransmit_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_active2
)paren
id|add_timer
c_func
(paren
op_amp
id|sp-&gt;timer
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-127s&bslash;n&quot;
comma
id|tmpbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
id|next
suffix:colon
id|sp
op_assign
id|sp-&gt;sklist_next
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|SOCKHASH_UNLOCK
c_func
(paren
)paren
suffix:semicolon
id|begin
op_assign
id|len
op_minus
(paren
id|pos
op_minus
id|offset
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|tcp_get_info
r_int
id|tcp_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_return
id|get__netinfo
c_func
(paren
op_amp
id|tcp_prot
comma
id|buffer
comma
l_int|0
comma
id|start
comma
id|offset
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|udp_get_info
r_int
id|udp_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_return
id|get__netinfo
c_func
(paren
op_amp
id|udp_prot
comma
id|buffer
comma
l_int|1
comma
id|start
comma
id|offset
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|raw_get_info
r_int
id|raw_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_return
id|get__netinfo
c_func
(paren
op_amp
id|raw_prot
comma
id|buffer
comma
l_int|1
comma
id|start
comma
id|offset
comma
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Report socket allocation statistics [mea@utu.fi]&n; */
DECL|function|afinet_get_info
r_int
id|afinet_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
multiline_comment|/* From  net/socket.c  */
r_extern
r_int
id|socket_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|proto
id|packet_prot
suffix:semicolon
r_int
id|len
op_assign
id|socket_get_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;TCP: inuse %d highest %d&bslash;n&quot;
comma
id|tcp_prot.inuse
comma
id|tcp_prot.highestinuse
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;UDP: inuse %d highest %d&bslash;n&quot;
comma
id|udp_prot.inuse
comma
id|udp_prot.highestinuse
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;RAW: inuse %d highest %d&bslash;n&quot;
comma
id|raw_prot.inuse
comma
id|raw_prot.highestinuse
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;PAC: inuse %d highest %d&bslash;n&quot;
comma
id|packet_prot.inuse
comma
id|packet_prot.highestinuse
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Called from the PROCfs module. This outputs /proc/net/snmp.&n; */
DECL|function|snmp_get_info
r_int
id|snmp_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_extern
r_struct
id|tcp_mib
id|tcp_statistics
suffix:semicolon
r_extern
r_struct
id|udp_mib
id|udp_statistics
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/*&n;  extern unsigned long tcp_rx_miss, tcp_rx_hit1,tcp_rx_hit2;&n;*/
id|len
op_assign
id|sprintf
(paren
id|buffer
comma
l_string|&quot;Ip: Forwarding DefaultTTL InReceives InHdrErrors InAddrErrors ForwDatagrams InUnknownProtos InDiscards InDelivers OutRequests OutDiscards OutNoRoutes ReasmTimeout ReasmReqds ReasmOKs ReasmFails FragOKs FragFails FragCreates&bslash;n&quot;
l_string|&quot;Ip: %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu&bslash;n&quot;
comma
id|ip_statistics.IpForwarding
comma
id|ip_statistics.IpDefaultTTL
comma
id|ip_statistics.IpInReceives
comma
id|ip_statistics.IpInHdrErrors
comma
id|ip_statistics.IpInAddrErrors
comma
id|ip_statistics.IpForwDatagrams
comma
id|ip_statistics.IpInUnknownProtos
comma
id|ip_statistics.IpInDiscards
comma
id|ip_statistics.IpInDelivers
comma
id|ip_statistics.IpOutRequests
comma
id|ip_statistics.IpOutDiscards
comma
id|ip_statistics.IpOutNoRoutes
comma
id|ip_statistics.IpReasmTimeout
comma
id|ip_statistics.IpReasmReqds
comma
id|ip_statistics.IpReasmOKs
comma
id|ip_statistics.IpReasmFails
comma
id|ip_statistics.IpFragOKs
comma
id|ip_statistics.IpFragFails
comma
id|ip_statistics.IpFragCreates
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Icmp: InMsgs InErrors InDestUnreachs InTimeExcds InParmProbs InSrcQuenchs InRedirects InEchos InEchoReps InTimestamps InTimestampReps InAddrMasks InAddrMaskReps OutMsgs OutErrors OutDestUnreachs OutTimeExcds OutParmProbs OutSrcQuenchs OutRedirects OutEchos OutEchoReps OutTimestamps OutTimestampReps OutAddrMasks OutAddrMaskReps&bslash;n&quot;
l_string|&quot;Icmp: %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu&bslash;n&quot;
comma
id|icmp_statistics.IcmpInMsgs
comma
id|icmp_statistics.IcmpInErrors
comma
id|icmp_statistics.IcmpInDestUnreachs
comma
id|icmp_statistics.IcmpInTimeExcds
comma
id|icmp_statistics.IcmpInParmProbs
comma
id|icmp_statistics.IcmpInSrcQuenchs
comma
id|icmp_statistics.IcmpInRedirects
comma
id|icmp_statistics.IcmpInEchos
comma
id|icmp_statistics.IcmpInEchoReps
comma
id|icmp_statistics.IcmpInTimestamps
comma
id|icmp_statistics.IcmpInTimestampReps
comma
id|icmp_statistics.IcmpInAddrMasks
comma
id|icmp_statistics.IcmpInAddrMaskReps
comma
id|icmp_statistics.IcmpOutMsgs
comma
id|icmp_statistics.IcmpOutErrors
comma
id|icmp_statistics.IcmpOutDestUnreachs
comma
id|icmp_statistics.IcmpOutTimeExcds
comma
id|icmp_statistics.IcmpOutParmProbs
comma
id|icmp_statistics.IcmpOutSrcQuenchs
comma
id|icmp_statistics.IcmpOutRedirects
comma
id|icmp_statistics.IcmpOutEchos
comma
id|icmp_statistics.IcmpOutEchoReps
comma
id|icmp_statistics.IcmpOutTimestamps
comma
id|icmp_statistics.IcmpOutTimestampReps
comma
id|icmp_statistics.IcmpOutAddrMasks
comma
id|icmp_statistics.IcmpOutAddrMaskReps
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Tcp: RtoAlgorithm RtoMin RtoMax MaxConn ActiveOpens PassiveOpens AttemptFails EstabResets CurrEstab InSegs OutSegs RetransSegs&bslash;n&quot;
l_string|&quot;Tcp: %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu&bslash;n&quot;
comma
id|tcp_statistics.TcpRtoAlgorithm
comma
id|tcp_statistics.TcpRtoMin
comma
id|tcp_statistics.TcpRtoMax
comma
id|tcp_statistics.TcpMaxConn
comma
id|tcp_statistics.TcpActiveOpens
comma
id|tcp_statistics.TcpPassiveOpens
comma
id|tcp_statistics.TcpAttemptFails
comma
id|tcp_statistics.TcpEstabResets
comma
id|tcp_statistics.TcpCurrEstab
comma
id|tcp_statistics.TcpInSegs
comma
id|tcp_statistics.TcpOutSegs
comma
id|tcp_statistics.TcpRetransSegs
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Udp: InDatagrams NoPorts InErrors OutDatagrams&bslash;nUdp: %lu %lu %lu %lu&bslash;n&quot;
comma
id|udp_statistics.UdpInDatagrams
comma
id|udp_statistics.UdpNoPorts
comma
id|udp_statistics.UdpInErrors
comma
id|udp_statistics.UdpOutDatagrams
)paren
suffix:semicolon
multiline_comment|/*&t;&n;&t;  len += sprintf( buffer + len,&n;&t;  &t;&quot;TCP fast path RX:  H2: %ul H1: %ul L: %ul&bslash;n&quot;,&n;&t;  &t;&t;tcp_rx_hit2,tcp_rx_hit1,tcp_rx_miss);&n;*/
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
