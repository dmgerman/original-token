multiline_comment|/*&n; *&t;NET3:&t;Implementation of the ICMP protocol layer. &n; *&t;&n; *&t;&t;Alan Cox, &lt;alan@cymru.net&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Some of the function names and the icmp unreach table for this&n; *&t;module were derived from [icmp.c 1.0.11 06/02/93] by&n; *&t;Ross Biro, Fred N. van Kempen, Mark Evans, Alan Cox, Gerhard Koerting.&n; *&t;Other than that this module is a complete rewrite.&n; *&n; *&t;Fixes:&n; *&t;&t;Mike Shaver&t;:&t;RFC1122 checks.&n; *&n; *&n; *&n; * RFC1122 Status: (boy, are there a lot of rules for ICMP)&n; *  3.2.2 (Generic ICMP stuff)&n; *   MUST discard messages of unknown type. (OK)&n; *   MUST copy at least the first 8 bytes from the offending packet&n; *     when sending ICMP errors. (OK)&n; *   MUST pass received ICMP errors up to protocol level. (OK)&n; *   SHOULD send ICMP errors with TOS == 0. (OK)&n; *   MUST NOT send ICMP errors in reply to:&n; *     ICMP errors (OK)&n; *     Broadcast/multicast datagrams (OK)&n; *     MAC broadcasts (OK)&n; *     Non-initial fragments (OK)&n; *     Datagram with a source address that isn&squot;t a single host. (OK)&n; *  3.2.2.1 (Destination Unreachable)&n; *   All the rules govern the IP layer, and are dealt with in ip.c, not here.&n; *  3.2.2.2 (Redirect)&n; *   Host SHOULD NOT send ICMP_REDIRECTs.  (OK)&n; *   MUST update routing table in response to host or network redirects. &n; *     (host OK, network NOT YET) [Intentionally -- AC]&n; *   SHOULD drop redirects if they&squot;re not from directly connected gateway&n; *     (OK -- we drop it if it&squot;s not from our old gateway, which is close&n; *      enough)&n; * 3.2.2.3 (Source Quench)&n; *   MUST pass incoming SOURCE_QUENCHs to transport layer (OK)&n; *   Other requirements are dealt with at the transport layer.&n; * 3.2.2.4 (Time Exceeded)&n; *   MUST pass TIME_EXCEEDED to transport layer (OK)&n; *   Other requirements dealt with at IP (generating TIME_EXCEEDED).&n; * 3.2.2.5 (Parameter Problem)&n; *   SHOULD generate these, but it doesn&squot;t say for what.  So we&squot;re OK. =)&n; *   MUST pass received PARAMPROBLEM to transport layer (NOT YET)&n; *   &t;[Solaris 2.X seems to assert EPROTO when this occurs] -- AC&n; * 3.2.2.6 (Echo Request/Reply)&n; *   MUST reply to ECHO_REQUEST, and give app to do ECHO stuff (OK, OK)&n; *   MAY discard broadcast ECHO_REQUESTs. (We don&squot;t, but that&squot;s OK.)&n; *   MUST reply using same source address as the request was sent to.&n; *     We&squot;re OK for unicast ECHOs, and it doesn&squot;t say anything about&n; *     how to handle broadcast ones, since it&squot;s optional.&n; *   MUST copy data from REQUEST to REPLY (OK)&n; *     unless it would require illegal fragmentation (N/A)&n; *   MUST pass REPLYs to transport/user layer (OK)&n; *   MUST use any provided source route (reversed) for REPLY. (NOT YET)&n; * 3.2.2.7 (Information Request/Reply)&n; *   MUST NOT implement this. (I guess that means silently discard...?) (OK)&n; * 3.2.2.8 (Timestamp Request/Reply)&n; *   MAY implement (OK)&n; *   SHOULD be in-kernel for &quot;minimum variability&quot; (OK)&n; *   MAY discard broadcast REQUESTs.  (OK, but see source for inconsistency)&n; *   MUST reply using same source address as the request was sent to. (OK)&n; *   MUST reverse source route, as per ECHO (NOT YET)&n; *   MUST pass REPLYs to transport/user layer (requires RAW, just like ECHO) (OK)&n; *   MUST update clock for timestamp at least 15 times/sec (OK)&n; *   MUST be &quot;correct within a few minutes&quot; (OK)&n; * 3.2.2.9 (Address Mask Request/Reply)&n; *   MAY implement (OK)&n; *   MUST send a broadcast REQUEST if using this system to set netmask&n; *     (OK... we don&squot;t use it)&n; *   MUST discard received REPLYs if not using this system (OK)&n; *   MUST NOT send replies unless specifically made agent for this sort&n; *     of thing. (OK)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
DECL|macro|min
mdefine_line|#define min(a,b)&t;((a)&lt;(b)?(a):(b))
multiline_comment|/*&n; *&t;Statistics&n; */
DECL|variable|icmp_statistics
r_struct
id|icmp_mib
id|icmp_statistics
suffix:semicolon
multiline_comment|/* An array of errno for error messages from dest unreach. */
multiline_comment|/* RFC 1122: 3.2.2.1 States that NET_UNREACH, HOS_UNREACH and SR_FAIELD MUST be considered &squot;transient errrs&squot;. */
DECL|variable|icmp_err_convert
r_struct
id|icmp_err
id|icmp_err_convert
(braket
)braket
op_assign
(brace
(brace
id|ENETUNREACH
comma
l_int|0
)brace
comma
multiline_comment|/*&t;ICMP_NET_UNREACH&t;*/
(brace
id|EHOSTUNREACH
comma
l_int|0
)brace
comma
multiline_comment|/*&t;ICMP_HOST_UNREACH&t;*/
(brace
id|ENOPROTOOPT
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_PROT_UNREACH&t;*/
(brace
id|ECONNREFUSED
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_PORT_UNREACH&t;*/
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
multiline_comment|/*&t;ICMP_FRAG_NEEDED&t;*/
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
multiline_comment|/*&t;ICMP_SR_FAILED&t;&t;*/
(brace
id|ENETUNREACH
comma
l_int|1
)brace
comma
multiline_comment|/* &t;ICMP_NET_UNKNOWN&t;*/
(brace
id|EHOSTDOWN
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_HOST_UNKNOWN&t;*/
(brace
id|ENONET
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_HOST_ISOLATED&t;*/
(brace
id|ENETUNREACH
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_NET_ANO&t;&t;*/
(brace
id|EHOSTUNREACH
comma
l_int|1
)brace
comma
multiline_comment|/*&t;ICMP_HOST_ANO&t;&t;*/
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
comma
multiline_comment|/*&t;ICMP_NET_UNR_TOS&t;*/
(brace
id|EOPNOTSUPP
comma
l_int|0
)brace
multiline_comment|/*&t;ICMP_HOST_UNR_TOS&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;A spare long used to speed up statistics udpating&n; */
DECL|variable|dummy
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/*&n; *&t;ICMP control array. This specifies what to do with each ICMP.&n; */
DECL|struct|icmp_control
r_struct
id|icmp_control
(brace
DECL|member|output
r_int
r_int
op_star
id|output
suffix:semicolon
multiline_comment|/* Address to increment on output */
DECL|member|input
r_int
r_int
op_star
id|input
suffix:semicolon
multiline_comment|/* Address to increment on input */
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
multiline_comment|/* This ICMP is classed as an error message */
)brace
suffix:semicolon
DECL|variable|icmp_pointers
r_static
r_struct
id|icmp_control
id|icmp_pointers
(braket
l_int|19
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Build xmit assembly blocks&n; */
DECL|struct|icmp_bxm
r_struct
id|icmp_bxm
(brace
DECL|member|data_ptr
r_void
op_star
id|data_ptr
suffix:semicolon
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
DECL|member|icmph
r_struct
id|icmphdr
id|icmph
suffix:semicolon
DECL|member|csum
r_int
r_int
id|csum
suffix:semicolon
DECL|member|replyopts
r_struct
id|options
id|replyopts
suffix:semicolon
DECL|member|optbuf
r_int
r_char
id|optbuf
(braket
l_int|40
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The ICMP socket. This is the most convenient way to flow control&n; *&t;our ICMP output as well as maintain a clean interface throughout&n; *&t;all layers. All Socketless IP sends will soon be gone.&n; */
DECL|variable|icmp_socket
r_struct
id|socket
id|icmp_socket
suffix:semicolon
multiline_comment|/*&n; *&t;Send an ICMP frame.&n; */
multiline_comment|/*&n; *&t;Maintain the counters used in the SNMP statistics for outgoing ICMP&n; */
DECL|function|icmp_out_count
r_static
r_void
id|icmp_out_count
c_func
(paren
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
id|type
OG
l_int|18
)paren
(brace
r_return
suffix:semicolon
)brace
(paren
op_star
id|icmp_pointers
(braket
id|type
)braket
dot
id|output
)paren
op_increment
suffix:semicolon
id|icmp_statistics.IcmpOutMsgs
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Checksum each fragment, and on the first include the headers and final checksum.&n; */
DECL|function|icmp_glue_bits
r_static
r_void
id|icmp_glue_bits
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
r_struct
id|icmp_bxm
op_star
id|icmp_param
op_assign
(paren
r_struct
id|icmp_bxm
op_star
)paren
id|p
suffix:semicolon
r_struct
id|icmphdr
op_star
id|icmph
suffix:semicolon
r_int
r_int
id|csum
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|icmp_param-&gt;csum
op_assign
id|csum_partial_copy
c_func
(paren
id|icmp_param-&gt;data_ptr
op_plus
id|offset
op_minus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
comma
id|to
comma
id|fraglen
comma
id|icmp_param-&gt;csum
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;First fragment includes header. Note that we&squot;ve done&n;&t; *&t;the other fragments first, so that we get the checksum&n;&t; *&t;for the whole packet here.&n;&t; */
id|csum
op_assign
id|csum_partial_copy
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|icmp_param-&gt;icmph
comma
id|to
comma
r_sizeof
(paren
r_struct
id|icmphdr
)paren
comma
id|icmp_param-&gt;csum
)paren
suffix:semicolon
id|csum
op_assign
id|csum_partial_copy
c_func
(paren
id|icmp_param-&gt;data_ptr
comma
id|to
op_plus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
comma
id|fraglen
op_minus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
comma
id|csum
)paren
suffix:semicolon
id|icmph
op_assign
(paren
r_struct
id|icmphdr
op_star
)paren
id|to
suffix:semicolon
id|icmph-&gt;checksum
op_assign
id|csum_fold
c_func
(paren
id|csum
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Driving logic for building and sending ICMP messages.&n; */
DECL|function|icmp_build_xmit
r_static
r_void
id|icmp_build_xmit
c_func
(paren
r_struct
id|icmp_bxm
op_star
id|icmp_param
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|icmp_socket.data
suffix:semicolon
id|icmp_param-&gt;icmph.checksum
op_assign
l_int|0
suffix:semicolon
id|icmp_param-&gt;csum
op_assign
l_int|0
suffix:semicolon
id|icmp_out_count
c_func
(paren
id|icmp_param-&gt;icmph.type
)paren
suffix:semicolon
id|ip_build_xmit
c_func
(paren
id|sk
comma
id|icmp_glue_bits
comma
id|icmp_param
comma
id|icmp_param-&gt;data_len
op_plus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
comma
id|daddr
comma
id|saddr
comma
op_amp
id|icmp_param-&gt;replyopts
comma
l_int|0
comma
id|IPPROTO_ICMP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send an ICMP message in response to a situation&n; *&n; *&t;RFC 1122: 3.2.2&t;MUST send at least the IP header and 8 bytes of header. MAY send more (we don&squot;t).&n; *&t;&t;&t;MUST NOT change this header information.&n; *&t;&t;&t;MUST NOT reply to a multicast/broadcast IP address.&n; *&t;&t;&t;MUST NOT reply to a multicast/broadcast MAC address.&n; *&t;&t;&t;MUST reply to only the first fragment.&n; */
DECL|function|icmp_send
r_void
id|icmp_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb_in
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
r_int
id|info
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|icmphdr
op_star
id|icmph
suffix:semicolon
r_int
id|atype
suffix:semicolon
r_struct
id|icmp_bxm
id|icmp_param
suffix:semicolon
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Find the original header&n;&t; */
id|iph
op_assign
id|skb_in-&gt;ip_hdr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;No replies to physical multicast/broadcast&n;&t; */
r_if
c_cond
(paren
id|skb_in-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Now check at the protocol level&n;&t; */
id|atype
op_assign
id|ip_chk_addr
c_func
(paren
id|iph-&gt;daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atype
op_eq
id|IS_BROADCAST
op_logical_or
id|atype
op_eq
id|IS_MULTICAST
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Only reply to fragment 0. We byte re-order the constant&n;&t; *&t;mask for efficiency.&n;&t; */
r_if
c_cond
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_OFFSET
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* &n;&t; *&t;If we send an ICMP error to an ICMP error a mess would result..&n;&t; */
r_if
c_cond
(paren
id|icmp_pointers
(braket
id|type
)braket
dot
id|error
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;We are an error, check if we are replying to an ICMP error&n;&t;&t; */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
)paren
(brace
id|icmph
op_assign
(paren
r_struct
id|icmphdr
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|iph
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Assume any unknown ICMP type is an error. This isn&squot;t&n;&t;&t;&t; *&t;specified by the RFC, but think about it..&n;&t;&t;&t; */
r_if
c_cond
(paren
id|icmph-&gt;type
OG
l_int|18
op_logical_or
id|icmp_pointers
(braket
id|icmph-&gt;type
)braket
dot
id|error
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; *&t;Tell our driver what to send&n;&t; */
id|saddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|saddr
op_ne
id|dev-&gt;pa_addr
op_logical_and
id|ip_chk_addr
c_func
(paren
id|saddr
)paren
op_ne
id|IS_MYADDR
)paren
(brace
id|saddr
op_assign
id|dev-&gt;pa_addr
suffix:semicolon
)brace
id|icmp_param.icmph.type
op_assign
id|type
suffix:semicolon
id|icmp_param.icmph.code
op_assign
id|code
suffix:semicolon
id|icmp_param.icmph.un.gateway
op_assign
id|info
suffix:semicolon
id|icmp_param.data_ptr
op_assign
id|iph
suffix:semicolon
id|icmp_param.data_len
op_assign
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
op_plus
l_int|8
suffix:semicolon
multiline_comment|/* RFC says return header + 8 bytes */
multiline_comment|/*&n;&t; *&t;Set it to build.&n;&t; */
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
op_amp
id|icmp_param.replyopts
comma
l_int|NULL
comma
id|saddr
comma
id|iph-&gt;saddr
comma
id|skb_in
)paren
op_eq
l_int|0
)paren
id|icmp_build_xmit
c_func
(paren
op_amp
id|icmp_param
comma
id|saddr
comma
id|iph-&gt;saddr
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Handle ICMP_DEST_UNREACH, ICMP_TIME_EXCEED, and ICMP_QUENCH. &n; */
DECL|function|icmp_unreach
r_static
r_void
id|icmp_unreach
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_int
id|hash
suffix:semicolon
r_struct
id|inet_protocol
op_star
id|ipprot
suffix:semicolon
r_int
r_char
op_star
id|dp
suffix:semicolon
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
id|dp
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
)paren
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icmph-&gt;type
op_eq
id|ICMP_DEST_UNREACH
)paren
(brace
r_switch
c_cond
(paren
id|icmph-&gt;code
op_amp
l_int|15
)paren
(brace
r_case
id|ICMP_NET_UNREACH
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMP_HOST_UNREACH
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMP_PROT_UNREACH
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ICMP: %s:%d: protocol unreachable.&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|iph-&gt;daddr
)paren
comma
id|ntohs
c_func
(paren
id|iph-&gt;protocol
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_PORT_UNREACH
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMP_FRAG_NEEDED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ICMP: %s: fragmentation needed and DF set.&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_SR_FAILED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ICMP: %s: Source Route Failed.&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|icmph-&gt;code
OG
l_int|12
)paren
(brace
multiline_comment|/* Invalid type */
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Throw it at our lower layers&n;&t; *&n;&t; *&t;RFC 1122: 3.2.2 MUST extract the protocol ID from the passed header.&n;&t; *&t;RFC 1122: 3.2.2.1 MUST pass ICMP unreach messages to the transport layer.&n;&t; *&t;RFC 1122: 3.2.2.2 MUST pass ICMP time expired messages to transport layer.&n;&t; */
multiline_comment|/*&n;&t; *&t;Get the protocol(s). &n;&t; */
id|hash
op_assign
id|iph-&gt;protocol
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;This can&squot;t change while we are doing it. &n;&t; *&n;&t; *&t;FIXME: Deliver to appropriate raw sockets too.&n;&t; */
id|ipprot
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|inet_protos
(braket
id|hash
)braket
suffix:semicolon
r_while
c_loop
(paren
id|ipprot
op_ne
l_int|NULL
)paren
(brace
r_struct
id|inet_protocol
op_star
id|nextip
suffix:semicolon
id|nextip
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|ipprot-&gt;next
suffix:semicolon
multiline_comment|/* &n;&t;&t; *&t;Pass it off to everyone who wants it. &n;&t;&t; */
multiline_comment|/* RFC1122: OK. Passes appropriate ICMP errors to the */
multiline_comment|/* appropriate protocol layer (MUST), as per 3.2.2. */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|ipprot-&gt;protocol
op_logical_and
id|ipprot-&gt;err_handler
)paren
(brace
id|ipprot
op_member_access_from_pointer
id|err_handler
c_func
(paren
id|icmph-&gt;type
comma
id|icmph-&gt;code
comma
id|dp
comma
id|iph-&gt;daddr
comma
id|iph-&gt;saddr
comma
id|ipprot
)paren
suffix:semicolon
)brace
id|ipprot
op_assign
id|nextip
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle ICMP_REDIRECT. &n; */
DECL|function|icmp_redirect
r_static
r_void
id|icmp_redirect
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
id|source
comma
id|__u32
id|daddr
comma
r_int
id|len
)paren
(brace
macro_line|#ifndef CONFIG_IP_FORWARD
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
macro_line|#endif
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get the copied header of the packet that caused the redirect&n;&t; */
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
id|ip
op_assign
id|iph-&gt;daddr
suffix:semicolon
macro_line|#ifdef CONFIG_IP_FORWARD
multiline_comment|/*&n;&t; *&t;We are a router. Routers should not respond to ICMP_REDIRECT messages.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;icmp: ICMP redirect from %s on %s ignored.&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|source
)paren
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#else&t;
r_switch
c_cond
(paren
id|icmph-&gt;code
op_amp
l_int|7
)paren
(brace
r_case
id|ICMP_REDIR_NET
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *&t;This causes a problem with subnetted networks. What we should do&n;&t;&t;&t; *&t;is use ICMP_ADDRESS to get the subnet mask of the problem route&n;&t;&t;&t; *&t;and set both. But we don&squot;t..&n;&t;&t;&t; */
macro_line|#ifdef not_a_good_idea
id|ip_rt_add
c_func
(paren
(paren
id|RTF_DYNAMIC
op_or
id|RTF_MODIFIED
op_or
id|RTF_GATEWAY
)paren
comma
id|ip
comma
l_int|0
comma
id|icmph-&gt;un.gateway
comma
id|dev
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|ICMP_REDIR_HOST
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *&t;Add better route to host.&n;&t;&t;&t; *&t;But first check that the redirect&n;&t;&t;&t; *&t;comes from the old gateway..&n;&t;&t;&t; *&t;And make sure it&squot;s an ok host address&n;&t;&t;&t; *&t;(not some confused thing sending our&n;&t;&t;&t; *&t;address)&n;&t;&t;&t; */
id|rt
op_assign
id|ip_rt_route
c_func
(paren
id|ip
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rt
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_gateway
op_ne
id|source
op_logical_or
(paren
(paren
id|icmph-&gt;un.gateway
op_xor
id|dev-&gt;pa_addr
)paren
op_amp
id|dev-&gt;pa_mask
)paren
op_logical_or
id|ip_chk_addr
c_func
(paren
id|icmph-&gt;un.gateway
)paren
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ICMP redirect from %s&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|source
)paren
)paren
suffix:semicolon
id|ip_rt_add
c_func
(paren
(paren
id|RTF_DYNAMIC
op_or
id|RTF_MODIFIED
op_or
id|RTF_HOST
op_or
id|RTF_GATEWAY
)paren
comma
id|ip
comma
l_int|0
comma
id|icmph-&gt;un.gateway
comma
id|dev
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_REDIR_NETTOS
suffix:colon
r_case
id|ICMP_REDIR_HOSTTOS
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ICMP: cannot handle TOS redirects yet!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#endif  &t;
multiline_comment|/*&n;  &t; *&t;Discard the original packet&n;  &t; */
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle ICMP_ECHO (&quot;ping&quot;) requests. &n; *&n; *&t;RFC 1122: 3.2.2.6 MUST have an echo server that answers ICMP echo requests.&n; *&t;RFC 1122: 3.2.2.6 Data received in the ICMP_ECHO request MUST be included in the reply.&n; *&t;See also WRT handling of options once they are done and working.&n; */
DECL|function|icmp_echo
r_static
r_void
id|icmp_echo
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
(brace
r_struct
id|icmp_bxm
id|icmp_param
suffix:semicolon
id|icmp_param.icmph
op_assign
op_star
id|icmph
suffix:semicolon
id|icmp_param.icmph.type
op_assign
id|ICMP_ECHOREPLY
suffix:semicolon
id|icmp_param.data_ptr
op_assign
(paren
id|icmph
op_plus
l_int|1
)paren
suffix:semicolon
id|icmp_param.data_len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
op_amp
id|icmp_param.replyopts
comma
l_int|NULL
comma
id|daddr
comma
id|saddr
comma
id|skb
)paren
op_eq
l_int|0
)paren
id|icmp_build_xmit
c_func
(paren
op_amp
id|icmp_param
comma
id|daddr
comma
id|saddr
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle ICMP Timestamp requests. &n; *&t;RFC 1122: 3.2.2.8 MAY implement ICMP timestamp requests.&n; *&t;&t;  SHOULD be in the kernel for minimum random latency.&n; *&t;&t;  MUST be accurate to a few minutes.&n; *&t;&t;  MUST be updated at least at 15Hz.&n; */
DECL|function|icmp_timestamp
r_static
r_void
id|icmp_timestamp
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
(brace
id|__u32
id|times
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* So the new timestamp works on ALPHA&squot;s.. */
r_struct
id|icmp_bxm
id|icmp_param
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Too short.&n;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|12
)paren
(brace
id|icmp_statistics.IcmpInErrors
op_increment
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
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Fill in the current time as ms since midnight UT: &n;&t; */
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|times
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
(paren
id|tv.tv_sec
op_mod
l_int|86400
)paren
op_star
l_int|1000
op_plus
id|tv.tv_usec
op_div
l_int|1000
)paren
suffix:semicolon
)brace
id|times
(braket
l_int|2
)braket
op_assign
id|times
(braket
l_int|1
)braket
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|times
(braket
l_int|0
)braket
comma
id|icmph
op_plus
l_int|1
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Incoming stamp */
id|icmp_param.icmph
op_assign
op_star
id|icmph
suffix:semicolon
id|icmp_param.icmph.type
op_assign
id|ICMP_TIMESTAMPREPLY
suffix:semicolon
id|icmp_param.icmph.code
op_assign
l_int|0
suffix:semicolon
id|icmp_param.data_ptr
op_assign
op_amp
id|times
suffix:semicolon
id|icmp_param.data_len
op_assign
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
op_amp
id|icmp_param.replyopts
comma
l_int|NULL
comma
id|daddr
comma
id|saddr
comma
id|skb
)paren
op_eq
l_int|0
)paren
id|icmp_build_xmit
c_func
(paren
op_amp
id|icmp_param
comma
id|daddr
comma
id|saddr
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Handle ICMP_ADDRESS_MASK requests.  (RFC950)&n; *&n; * RFC1122 (3.2.2.9).  A host MUST only send replies to &n; * ADDRESS_MASK requests if it&squot;s been configured as an address mask &n; * agent.  Receiving a request doesn&squot;t constitute implicit permission to &n; * act as one. Of course, implementing this correctly requires (SHOULD) &n; * a way to turn the functionality on and off.  Another one for sysctl(), &n; * I guess. -- MS &n; * Botched with a CONFIG option for now - Linus add scts sysctl please.. &n; */
DECL|function|icmp_address
r_static
r_void
id|icmp_address
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
(brace
macro_line|#ifdef CONFIG_IP_ADDR_AGENT
id|__u32
id|answer
suffix:semicolon
r_struct
id|icmp_bxm
id|icmp_param
suffix:semicolon
id|icmp_param.icmph.type
op_assign
id|ICMP_ADDRESSREPLY
suffix:semicolon
id|icmp_param.icmph.code
op_assign
l_int|0
suffix:semicolon
id|icmp_param.icmph.un.echo.id
op_assign
id|icmph-&gt;un.echo.id
suffix:semicolon
id|icmp_param.icmph.un.echo.sequence
op_assign
id|icmph-&gt;un.echo.sequence
suffix:semicolon
id|icmp_param.data_ptr
op_assign
op_amp
id|dev-&gt;pa_mask
suffix:semicolon
id|icmp_param.data_len
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|ip_options_echo
c_func
(paren
op_amp
id|icmp_param.replyopts
comma
l_int|NULL
comma
id|daddr
comma
id|saddr
comma
id|skb
)paren
op_eq
l_int|0
)paren
id|icmp_build_xmit
c_func
(paren
op_amp
id|icmp_param
comma
id|daddr
comma
id|saddr
)paren
suffix:semicolon
macro_line|#endif&t;
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
DECL|function|icmp_discard
r_static
r_void
id|icmp_discard
c_func
(paren
r_struct
id|icmphdr
op_star
id|icmph
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
comma
r_int
id|len
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Deal with incoming ICMP packets. &n; */
DECL|function|icmp_rcv
r_int
id|icmp_rcv
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
(brace
r_struct
id|icmphdr
op_star
id|icmph
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|icmp_statistics.IcmpInMsgs
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Validate the packet&n;  &t; */
r_if
c_cond
(paren
id|ip_compute_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|icmph
comma
id|len
)paren
)paren
(brace
multiline_comment|/* Failed checksum! */
id|icmp_statistics.IcmpInErrors
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ICMP: failed checksum from %s!&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|saddr
)paren
)paren
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
multiline_comment|/*&n;&t; *&t;18 is the highest &squot;known&squot; icmp type. Anything else is a mystery&n;&t; *&n;&t; *&t;RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently discarded.&n;&t; */
r_if
c_cond
(paren
id|icmph-&gt;type
OG
l_int|18
)paren
(brace
id|icmp_statistics.IcmpInErrors
op_increment
suffix:semicolon
multiline_comment|/* Is this right - or do we ignore ? */
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
multiline_comment|/*&n;&t; *&t;Parse the ICMP message &n;&t; */
r_if
c_cond
(paren
id|daddr
op_ne
id|dev-&gt;pa_addr
op_logical_and
id|ip_chk_addr
c_func
(paren
id|daddr
)paren
op_eq
id|IS_BROADCAST
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;RFC 1122: 3.2.2.6 An ICMP_ECHO to broadcast MAY be silently ignored (we don&squot;t as it is used&n;&t;&t; *&t;by some network mapping tools).&n;&t;&t; *&t;RFC 1122: 3.2.2.8 An ICMP_TIMESTAMP MAY be silently discarded if to broadcast/multicast.&n;&t;&t; */
r_if
c_cond
(paren
id|icmph-&gt;type
op_ne
id|ICMP_ECHO
)paren
(brace
id|icmp_statistics.IcmpInErrors
op_increment
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
id|daddr
op_assign
id|dev-&gt;pa_addr
suffix:semicolon
)brace
id|len
op_sub_assign
r_sizeof
(paren
r_struct
id|icmphdr
)paren
suffix:semicolon
(paren
op_star
id|icmp_pointers
(braket
id|icmph-&gt;type
)braket
dot
id|input
)paren
op_increment
suffix:semicolon
(paren
id|icmp_pointers
(braket
id|icmph-&gt;type
)braket
dot
id|handler
)paren
(paren
id|icmph
comma
id|skb
comma
id|skb-&gt;dev
comma
id|saddr
comma
id|daddr
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This table is the definition of how we handle ICMP.&n; */
DECL|variable|icmp_pointers
r_static
r_struct
id|icmp_control
id|icmp_pointers
(braket
l_int|19
)braket
op_assign
(brace
multiline_comment|/* ECHO REPLY (0) */
(brace
op_amp
id|icmp_statistics.IcmpOutEchoReps
comma
op_amp
id|icmp_statistics.IcmpInEchoReps
comma
id|icmp_discard
comma
l_int|0
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
multiline_comment|/* DEST UNREACH (3) */
(brace
op_amp
id|icmp_statistics.IcmpOutDestUnreachs
comma
op_amp
id|icmp_statistics.IcmpInDestUnreachs
comma
id|icmp_unreach
comma
l_int|1
)brace
comma
multiline_comment|/* SOURCE QUENCH (4) */
(brace
op_amp
id|icmp_statistics.IcmpOutSrcQuenchs
comma
op_amp
id|icmp_statistics.IcmpInSrcQuenchs
comma
id|icmp_unreach
comma
l_int|1
)brace
comma
multiline_comment|/* REDIRECT (5) */
(brace
op_amp
id|icmp_statistics.IcmpOutRedirects
comma
op_amp
id|icmp_statistics.IcmpInRedirects
comma
id|icmp_redirect
comma
l_int|1
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
multiline_comment|/* ECHO (8) */
(brace
op_amp
id|icmp_statistics.IcmpOutEchos
comma
op_amp
id|icmp_statistics.IcmpInEchos
comma
id|icmp_echo
comma
l_int|0
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
(brace
op_amp
id|dummy
comma
op_amp
id|icmp_statistics.IcmpInErrors
comma
id|icmp_discard
comma
l_int|1
)brace
comma
multiline_comment|/* TIME EXCEEDED (11) */
(brace
op_amp
id|icmp_statistics.IcmpOutTimeExcds
comma
op_amp
id|icmp_statistics.IcmpInTimeExcds
comma
id|icmp_unreach
comma
l_int|1
)brace
comma
multiline_comment|/* PARAMETER PROBLEM (12) */
multiline_comment|/* FIXME: RFC1122 3.2.2.5 - MUST pass PARAM_PROB messages to transport layer */
(brace
op_amp
id|icmp_statistics.IcmpOutParmProbs
comma
op_amp
id|icmp_statistics.IcmpInParmProbs
comma
id|icmp_discard
comma
l_int|1
)brace
comma
multiline_comment|/* TIMESTAMP (13) */
(brace
op_amp
id|icmp_statistics.IcmpOutTimestamps
comma
op_amp
id|icmp_statistics.IcmpInTimestamps
comma
id|icmp_timestamp
comma
l_int|0
)brace
comma
multiline_comment|/* TIMESTAMP REPLY (14) */
(brace
op_amp
id|icmp_statistics.IcmpOutTimestampReps
comma
op_amp
id|icmp_statistics.IcmpInTimestampReps
comma
id|icmp_discard
comma
l_int|0
)brace
comma
multiline_comment|/* INFO (15) */
(brace
op_amp
id|dummy
comma
op_amp
id|dummy
comma
id|icmp_discard
comma
l_int|0
)brace
comma
multiline_comment|/* INFO REPLY (16) */
(brace
op_amp
id|dummy
comma
op_amp
id|dummy
comma
id|icmp_discard
comma
l_int|0
)brace
comma
multiline_comment|/* ADDR MASK (17) */
(brace
op_amp
id|icmp_statistics.IcmpOutAddrMasks
comma
op_amp
id|icmp_statistics.IcmpInAddrMasks
comma
id|icmp_address
comma
l_int|0
)brace
comma
multiline_comment|/* ADDR MASK REPLY (18) */
(brace
op_amp
id|icmp_statistics.IcmpOutAddrMaskReps
comma
op_amp
id|icmp_statistics.IcmpInAddrMaskReps
comma
id|icmp_discard
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|icmp_init
r_void
id|icmp_init
c_func
(paren
r_struct
id|proto_ops
op_star
id|ops
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_int
id|err
suffix:semicolon
id|icmp_socket.type
op_assign
id|SOCK_RAW
suffix:semicolon
id|icmp_socket.ops
op_assign
id|ops
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ops
op_member_access_from_pointer
id|create
c_func
(paren
op_amp
id|icmp_socket
comma
id|IPPROTO_ICMP
)paren
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to create the ICMP control socket (%d,%d,%p,%p).&bslash;n&quot;
comma
op_minus
id|err
comma
id|current-&gt;euid
comma
id|current
comma
op_amp
id|init_task
)paren
suffix:semicolon
)brace
id|sk
op_assign
id|icmp_socket.data
suffix:semicolon
id|sk-&gt;allocation
op_assign
id|GFP_ATOMIC
suffix:semicolon
id|sk-&gt;num
op_assign
l_int|256
suffix:semicolon
multiline_comment|/* Don&squot;t receive any data */
)brace
eof
