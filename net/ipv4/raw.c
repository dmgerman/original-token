multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;RAW - implementation of IP &quot;raw&quot; sockets.&n; *&n; * Version:&t;$Id: raw.c,v 1.39 1998/11/08 11:17:04 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;verify_area() fixed up&n; *&t;&t;Alan Cox&t;:&t;ICMP error handling&n; *&t;&t;Alan Cox&t;:&t;EMSGSIZE if you send too big a packet&n; *&t;&t;Alan Cox&t;: &t;Now uses generic datagrams and shared skbuff&n; *&t;&t;&t;&t;&t;library. No more peek crashes, no more backlogs&n; *&t;&t;Alan Cox&t;:&t;Checks sk-&gt;broadcast.&n; *&t;&t;Alan Cox&t;:&t;Uses skb_free_datagram/skb_copy_datagram&n; *&t;&t;Alan Cox&t;:&t;Raw passes ip options too&n; *&t;&t;Alan Cox&t;:&t;Setsocketopt added&n; *&t;&t;Alan Cox&t;:&t;Fixed error return for broadcasts&n; *&t;&t;Alan Cox&t;:&t;Removed wake_up calls&n; *&t;&t;Alan Cox&t;:&t;Use ttl/tos&n; *&t;&t;Alan Cox&t;:&t;Cleaned up old debugging&n; *&t;&t;Alan Cox&t;:&t;Use new kernel side addresses&n; *&t;Arnt Gulbrandsen&t;:&t;Fixed MSG_DONTROUTE in raw sockets.&n; *&t;&t;Alan Cox&t;:&t;BSD style RAW socket demultiplexing.&n; *&t;&t;Alan Cox&t;:&t;Beginnings of mrouted support.&n; *&t;&t;Alan Cox&t;:&t;Added IP_HDRINCL option.&n; *&t;&t;Alan Cox&t;:&t;Skip broadcast check if BSDism set.&n; *&t;&t;David S. Miller&t;:&t;New socket lookup architecture.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
macro_line|#include &lt;net/raw.h&gt;
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
DECL|variable|raw_v4_htable
r_struct
id|sock
op_star
id|raw_v4_htable
(braket
id|RAWV4_HTABLE_SIZE
)braket
suffix:semicolon
DECL|function|raw_v4_hash
r_static
r_void
id|raw_v4_hash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sock
op_star
op_star
id|skp
suffix:semicolon
r_int
id|num
op_assign
id|sk-&gt;num
suffix:semicolon
id|num
op_and_assign
(paren
id|RAWV4_HTABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|skp
op_assign
op_amp
id|raw_v4_htable
(braket
id|num
)braket
suffix:semicolon
id|SOCKHASH_LOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
id|sk-&gt;next
op_assign
op_star
id|skp
suffix:semicolon
op_star
id|skp
op_assign
id|sk
suffix:semicolon
id|sk-&gt;hashent
op_assign
id|num
suffix:semicolon
id|SOCKHASH_UNLOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|raw_v4_unhash
r_static
r_void
id|raw_v4_unhash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sock
op_star
op_star
id|skp
suffix:semicolon
r_int
id|num
op_assign
id|sk-&gt;num
suffix:semicolon
id|num
op_and_assign
(paren
id|RAWV4_HTABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|skp
op_assign
op_amp
id|raw_v4_htable
(braket
id|num
)braket
suffix:semicolon
id|SOCKHASH_LOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|skp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|skp
op_eq
id|sk
)paren
(brace
op_star
id|skp
op_assign
id|sk-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skp
op_assign
op_amp
(paren
(paren
op_star
id|skp
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|SOCKHASH_UNLOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|raw_v4_rehash
r_static
r_void
id|raw_v4_rehash
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sock
op_star
op_star
id|skp
suffix:semicolon
r_int
id|num
op_assign
id|sk-&gt;num
suffix:semicolon
r_int
id|oldnum
op_assign
id|sk-&gt;hashent
suffix:semicolon
id|num
op_and_assign
(paren
id|RAWV4_HTABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|skp
op_assign
op_amp
id|raw_v4_htable
(braket
id|oldnum
)braket
suffix:semicolon
id|SOCKHASH_LOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|skp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_star
id|skp
op_eq
id|sk
)paren
(brace
op_star
id|skp
op_assign
id|sk-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skp
op_assign
op_amp
(paren
(paren
op_star
id|skp
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|sk-&gt;next
op_assign
id|raw_v4_htable
(braket
id|num
)braket
suffix:semicolon
id|raw_v4_htable
(braket
id|num
)braket
op_assign
id|sk
suffix:semicolon
id|sk-&gt;hashent
op_assign
id|num
suffix:semicolon
id|SOCKHASH_UNLOCK_WRITE
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Grumble... icmp and ip_input want to get at this... */
DECL|function|raw_v4_lookup
r_struct
id|sock
op_star
id|raw_v4_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|num
comma
r_int
r_int
id|raddr
comma
r_int
r_int
id|laddr
comma
r_int
id|dif
)paren
(brace
r_struct
id|sock
op_star
id|s
op_assign
id|sk
suffix:semicolon
id|SOCKHASH_LOCK_READ
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|sk
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
id|s-&gt;num
op_eq
id|num
)paren
op_logical_and
op_logical_neg
(paren
id|s-&gt;dead
op_logical_and
(paren
id|s-&gt;state
op_eq
id|TCP_CLOSE
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|s-&gt;daddr
op_logical_and
id|s-&gt;daddr
op_ne
id|raddr
)paren
op_logical_and
op_logical_neg
(paren
id|s-&gt;rcv_saddr
op_logical_and
id|s-&gt;rcv_saddr
op_ne
id|laddr
)paren
op_logical_and
op_logical_neg
(paren
id|s-&gt;bound_dev_if
op_logical_and
id|s-&gt;bound_dev_if
op_ne
id|dif
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* gotcha */
)brace
id|SOCKHASH_UNLOCK_READ
c_func
(paren
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|raw_err
r_void
id|raw_err
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
r_int
id|type
op_assign
id|skb-&gt;h.icmph-&gt;type
suffix:semicolon
r_int
id|code
op_assign
id|skb-&gt;h.icmph-&gt;code
suffix:semicolon
id|u32
id|info
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|harderr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Report error on raw socket, if:&n;&t;   1. User requested ip_recverr.&n;&t;   2. Socket is connected (otherwise the error indication&n;&t;      is useless without ip_recverr and error is hard.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;ip_recverr
op_logical_and
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_default
suffix:colon
r_case
id|ICMP_TIME_EXCEEDED
suffix:colon
id|err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_SOURCE_QUENCH
suffix:colon
r_return
suffix:semicolon
r_case
id|ICMP_PARAMETERPROB
suffix:colon
id|err
op_assign
id|EPROTO
suffix:semicolon
id|info
op_assign
id|ntohl
c_func
(paren
id|skb-&gt;h.icmph-&gt;un.gateway
)paren
op_rshift
l_int|24
suffix:semicolon
id|harderr
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMP_DEST_UNREACH
suffix:colon
id|err
op_assign
id|EHOSTUNREACH
suffix:semicolon
r_if
c_cond
(paren
id|code
OG
id|NR_ICMP_UNREACH
)paren
r_break
suffix:semicolon
id|err
op_assign
id|icmp_err_convert
(braket
id|code
)braket
dot
id|errno
suffix:semicolon
id|harderr
op_assign
id|icmp_err_convert
(braket
id|code
)braket
dot
id|fatal
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
id|ICMP_FRAG_NEEDED
)paren
(brace
id|harderr
op_assign
(paren
id|sk-&gt;ip_pmtudisc
op_ne
id|IP_PMTUDISC_DONT
)paren
suffix:semicolon
id|err
op_assign
id|EMSGSIZE
suffix:semicolon
id|info
op_assign
id|ntohs
c_func
(paren
id|skb-&gt;h.icmph-&gt;un.frag.mtu
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sk-&gt;ip_recverr
)paren
id|ip_icmp_error
c_func
(paren
id|sk
comma
id|skb
comma
id|err
comma
l_int|0
comma
id|info
comma
(paren
id|u8
op_star
)paren
(paren
id|skb-&gt;h.icmph
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;ip_recverr
op_logical_or
id|harderr
)paren
(brace
id|sk-&gt;err
op_assign
id|err
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
)brace
DECL|function|raw_rcv_skb
r_static
r_int
id|raw_rcv_skb
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
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ip_statistics.IpInDelivers
op_increment
suffix:semicolon
r_return
l_int|0
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
)paren
(brace
multiline_comment|/* Now we need to copy this into memory. */
id|skb_trim
c_func
(paren
id|skb
comma
id|ntohs
c_func
(paren
id|skb-&gt;nh.iph-&gt;tot_len
)paren
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
id|raw_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|rawfakehdr
r_struct
id|rawfakehdr
(brace
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
DECL|member|saddr
id|u32
id|saddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Send a RAW IP packet.&n; */
multiline_comment|/*&n; *&t;Callback support is trivial for SOCK_RAW&n; */
DECL|function|raw_getfrag
r_static
r_int
id|raw_getfrag
c_func
(paren
r_const
r_void
op_star
id|p
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
id|rawfakehdr
op_star
id|rfh
op_assign
(paren
r_struct
id|rawfakehdr
op_star
)paren
id|p
suffix:semicolon
r_return
id|memcpy_fromiovecend
c_func
(paren
id|to
comma
id|rfh-&gt;iov
comma
id|offset
comma
id|fraglen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;IPPROTO_RAW needs extra work.&n; */
DECL|function|raw_getrawfrag
r_static
r_int
id|raw_getrawfrag
c_func
(paren
r_const
r_void
op_star
id|p
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
id|rawfakehdr
op_star
id|rfh
op_assign
(paren
r_struct
id|rawfakehdr
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
id|memcpy_fromiovecend
c_func
(paren
id|to
comma
id|rfh-&gt;iov
comma
id|offset
comma
id|fraglen
)paren
)paren
r_return
op_minus
id|EFAULT
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
r_if
c_cond
(paren
op_logical_neg
id|iph-&gt;saddr
)paren
id|iph-&gt;saddr
op_assign
id|rfh-&gt;saddr
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
multiline_comment|/* This is right as you can&squot;t frag&n;&t;&t;&t;&t;&t;&t;   RAW packets */
multiline_comment|/*&n;&t; &t; *&t;Deliberate breach of modularity to keep &n;&t; &t; *&t;ip_build_xmit clean (well less messy).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|iph-&gt;id
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_sendmsg
r_static
r_int
id|raw_sendmsg
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
)paren
(brace
r_struct
id|ipcm_cookie
id|ipc
suffix:semicolon
r_struct
id|rawfakehdr
id|rfh
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
l_int|NULL
suffix:semicolon
r_int
id|free
op_assign
l_int|0
suffix:semicolon
id|u32
id|daddr
suffix:semicolon
id|u8
id|tos
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* This check is ONLY to check for arithmetic overflow&n;&t;   on integer(!) len. Not more! Real check will be made&n;&t;   in ip_build_xmit --ANK&n;&n;&t;   BTW socket.c -&gt; af_*.c -&gt; ... make multiple&n;&t;   invalid conversions size_t -&gt; int. We MUST repair it f.e.&n;&t;   by replacing all of them with size_t and revise all&n;&t;   the places sort of len += sizeof(struct iphdr)&n;&t;   If len was ULONG_MAX-10 it would be cathastrophe  --ANK&n;&t; */
r_if
c_cond
(paren
id|len
template_param
l_int|0xFFFF
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check the flags.&n;&t; */
r_if
c_cond
(paren
id|msg-&gt;msg_flags
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
id|msg-&gt;msg_flags
op_amp
op_complement
(paren
id|MSG_DONTROUTE
op_or
id|MSG_DONTWAIT
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get and verify the address. &n;&t; */
r_if
c_cond
(paren
id|msg-&gt;msg_namelen
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|usin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_namelen
OL
r_sizeof
(paren
op_star
id|usin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|usin-&gt;sin_family
op_ne
id|AF_INET
)paren
(brace
r_static
r_int
id|complained
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|complained
op_increment
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s forgot to set AF_INET in raw sendmsg. Fix it!&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usin-&gt;sin_family
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|daddr
op_assign
id|usin-&gt;sin_addr.s_addr
suffix:semicolon
multiline_comment|/* ANK: I did not forget to get protocol from port field.&n;&t;&t; * I just do not know, who uses this weirdness.&n;&t;&t; * IP_HDRINCL is much more convenient.&n;&t;&t; */
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
id|daddr
op_assign
id|sk-&gt;daddr
suffix:semicolon
)brace
id|ipc.addr
op_assign
id|sk-&gt;saddr
suffix:semicolon
id|ipc.opt
op_assign
l_int|NULL
suffix:semicolon
id|ipc.oif
op_assign
id|sk-&gt;bound_dev_if
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_controllen
)paren
(brace
r_int
id|tmp
op_assign
id|ip_cmsg_send
c_func
(paren
id|msg
comma
op_amp
id|ipc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_return
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt
)paren
id|free
op_assign
l_int|1
suffix:semicolon
)brace
id|rfh.saddr
op_assign
id|ipc.addr
suffix:semicolon
id|ipc.addr
op_assign
id|daddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipc.opt
)paren
id|ipc.opt
op_assign
id|sk-&gt;opt
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Linux does not mangle headers on raw sockets,&n;&t;&t; * so that IP options + IP_HDRINCL is non-sense.&n;&t;&t; */
r_if
c_cond
(paren
id|sk-&gt;ip_hdrincl
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|ipc.opt-&gt;srr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|daddr
)paren
r_goto
id|done
suffix:semicolon
id|daddr
op_assign
id|ipc.opt-&gt;faddr
suffix:semicolon
)brace
)brace
id|tos
op_assign
id|RT_TOS
c_func
(paren
id|sk-&gt;ip_tos
)paren
op_or
id|sk-&gt;localroute
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_flags
op_amp
id|MSG_DONTROUTE
)paren
id|tos
op_or_assign
id|RTO_ONLINK
suffix:semicolon
r_if
c_cond
(paren
id|MULTICAST
c_func
(paren
id|daddr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ipc.oif
)paren
id|ipc.oif
op_assign
id|sk-&gt;ip_mc_index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rfh.saddr
)paren
id|rfh.saddr
op_assign
id|sk-&gt;ip_mc_addr
suffix:semicolon
)brace
id|err
op_assign
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|daddr
comma
id|rfh.saddr
comma
id|tos
comma
id|ipc.oif
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_BROADCAST
op_logical_and
op_logical_neg
id|sk-&gt;broadcast
)paren
r_goto
id|done
suffix:semicolon
id|rfh.iov
op_assign
id|msg-&gt;msg_iov
suffix:semicolon
id|rfh.saddr
op_assign
id|rt-&gt;rt_src
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipc.addr
)paren
id|ipc.addr
op_assign
id|rt-&gt;rt_dst
suffix:semicolon
id|err
op_assign
id|ip_build_xmit
c_func
(paren
id|sk
comma
id|sk-&gt;ip_hdrincl
ques
c_cond
id|raw_getrawfrag
suffix:colon
id|raw_getfrag
comma
op_amp
id|rfh
comma
id|len
comma
op_amp
id|ipc
comma
id|rt
comma
id|msg-&gt;msg_flags
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|free
)paren
id|kfree
c_func
(paren
id|ipc.opt
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
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
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* Observation: when raw_close is called, processes have&n;&t;   no access to socket anymore. But net still has.&n;&t;   Step one, detach it from networking:&n;&n;&t;   A. Remove from hash tables.&n;&t; */
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|raw_v4_unhash
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   B. Raw sockets may have direct kernel refereneces. Kill them.&n;&t; */
id|ip_ra_control
c_func
(paren
id|sk
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* In this point socket cannot receive new packets anymore */
multiline_comment|/* But we still have packets pending on receive&n;&t;   queue and probably, our own packets waiting in device queues.&n;&t;   sock_destroy will drain receive queue, but transmitted&n;&t;   packets will delay socket destruction.&n;&t;   Set sk-&gt;dead=1 in order to prevent wakeups, when these&n;&t;   packet will be freed.&n;&t; */
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
id|destroy_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* That&squot;s all. No races here. */
)brace
multiline_comment|/* This gets rid of all the nasties in af_inet. -DaveM */
DECL|function|raw_bind
r_static
r_int
id|raw_bind
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
(brace
r_struct
id|sockaddr_in
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|uaddr
suffix:semicolon
r_int
id|chk_addr_ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSE
)paren
op_logical_or
(paren
id|addr_len
OL
r_sizeof
(paren
r_struct
id|sockaddr_in
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|chk_addr_ret
op_assign
id|inet_addr_type
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sin_addr.s_addr
op_ne
l_int|0
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_LOCAL
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_MULTICAST
op_logical_and
id|chk_addr_ret
op_ne
id|RTN_BROADCAST
)paren
(brace
macro_line|#ifdef CONFIG_IP_TRANSPARENT_PROXY
multiline_comment|/* Superuser may bind to any address to allow transparent proxying. */
r_if
c_cond
(paren
id|chk_addr_ret
op_ne
id|RTN_UNICAST
op_logical_or
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
macro_line|#endif
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
)brace
id|sk-&gt;rcv_saddr
op_assign
id|sk-&gt;saddr
op_assign
id|addr-&gt;sin_addr.s_addr
suffix:semicolon
r_if
c_cond
(paren
id|chk_addr_ret
op_eq
id|RTN_MULTICAST
op_logical_or
id|chk_addr_ret
op_eq
id|RTN_BROADCAST
)paren
(brace
id|sk-&gt;saddr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Use device */
id|dst_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|sk-&gt;dst_cache
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This should be easy, if there is something there&n; *&t;we return it, otherwise we block.&n; */
DECL|function|raw_recvmsg
r_int
id|raw_recvmsg
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
id|noblock
comma
r_int
id|flags
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
r_struct
id|sockaddr_in
op_star
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|msg-&gt;msg_name
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
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_ERRQUEUE
)paren
r_return
id|ip_recv_error
c_func
(paren
id|sk
comma
id|msg
comma
id|len
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
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|copied
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
id|copied
op_assign
id|len
suffix:semicolon
)brace
id|err
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|done
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
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;ip_cmsg_flags
)paren
id|ip_cmsg_recv
c_func
(paren
id|msg
comma
id|skb
)paren
suffix:semicolon
id|done
suffix:colon
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
(paren
id|err
ques
c_cond
suffix:colon
id|copied
)paren
suffix:semicolon
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
r_struct
id|raw_opt
op_star
id|tp
op_assign
op_amp
(paren
id|sk-&gt;tp_pinfo.tp_raw4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;num
op_eq
id|IPPROTO_ICMP
)paren
id|memset
c_func
(paren
op_amp
id|tp-&gt;filter
comma
l_int|0
comma
r_sizeof
(paren
id|tp-&gt;filter
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_seticmpfilter
r_static
r_int
id|raw_seticmpfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|optlen
OG
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
)paren
id|optlen
op_assign
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sk-&gt;tp_pinfo.tp_raw4.filter
comma
id|optval
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_geticmpfilter
r_static
r_int
id|raw_geticmpfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
)paren
id|len
op_assign
r_sizeof
(paren
r_struct
id|icmp_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|optval
comma
op_amp
id|sk-&gt;tp_pinfo.tp_raw4.filter
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_setsockopt
r_static
r_int
id|raw_setsockopt
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
(brace
r_if
c_cond
(paren
id|level
op_ne
id|SOL_RAW
)paren
r_return
id|ip_setsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|ICMP_FILTER
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;num
op_ne
id|IPPROTO_ICMP
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|raw_seticmpfilter
c_func
(paren
id|sk
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
DECL|function|raw_getsockopt
r_static
r_int
id|raw_getsockopt
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
(brace
r_if
c_cond
(paren
id|level
op_ne
id|SOL_RAW
)paren
r_return
id|ip_getsockopt
c_func
(paren
id|sk
comma
id|level
comma
id|optname
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|optname
)paren
(brace
r_case
id|ICMP_FILTER
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;num
op_ne
id|IPPROTO_ICMP
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|raw_geticmpfilter
c_func
(paren
id|sk
comma
id|optval
comma
id|optlen
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
op_minus
id|ENOPROTOOPT
suffix:semicolon
)brace
DECL|variable|raw_prot
r_struct
id|proto
id|raw_prot
op_assign
(brace
(paren
r_struct
id|sock
op_star
)paren
op_amp
id|raw_prot
comma
multiline_comment|/* sklist_next */
(paren
r_struct
id|sock
op_star
)paren
op_amp
id|raw_prot
comma
multiline_comment|/* sklist_prev */
id|raw_close
comma
multiline_comment|/* close */
id|udp_connect
comma
multiline_comment|/* connect */
l_int|NULL
comma
multiline_comment|/* accept */
l_int|NULL
comma
multiline_comment|/* retransmit */
l_int|NULL
comma
multiline_comment|/* write_wakeup */
l_int|NULL
comma
multiline_comment|/* read_wakeup */
id|datagram_poll
comma
multiline_comment|/* poll */
macro_line|#ifdef CONFIG_IP_MROUTE
id|ipmr_ioctl
comma
multiline_comment|/* ioctl */
macro_line|#else
l_int|NULL
comma
multiline_comment|/* ioctl */
macro_line|#endif
id|raw_init
comma
multiline_comment|/* init */
l_int|NULL
comma
multiline_comment|/* destroy */
l_int|NULL
comma
multiline_comment|/* shutdown */
id|raw_setsockopt
comma
multiline_comment|/* setsockopt */
id|raw_getsockopt
comma
multiline_comment|/* getsockopt */
id|raw_sendmsg
comma
multiline_comment|/* sendmsg */
id|raw_recvmsg
comma
multiline_comment|/* recvmsg */
id|raw_bind
comma
multiline_comment|/* bind */
id|raw_rcv_skb
comma
multiline_comment|/* backlog_rcv */
id|raw_v4_hash
comma
multiline_comment|/* hash */
id|raw_v4_unhash
comma
multiline_comment|/* unhash */
id|raw_v4_rehash
comma
multiline_comment|/* rehash */
l_int|NULL
comma
multiline_comment|/* good_socknum */
l_int|NULL
comma
multiline_comment|/* verify_bind */
l_int|128
comma
multiline_comment|/* max_header */
l_int|0
comma
multiline_comment|/* retransmits */
l_string|&quot;RAW&quot;
comma
multiline_comment|/* name */
l_int|0
comma
multiline_comment|/* inuse */
l_int|0
multiline_comment|/* highestinuse */
)brace
suffix:semicolon
eof
