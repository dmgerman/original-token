multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The IP forwarding functionality.&n; *&t;&t;&n; * Authors:&t;see ip.c&n; *&n; * Fixes:&n; *&t;&t;Many&t;&t;:&t;Split from ip.c , see ip_input.c for &n; *&t;&t;&t;&t;&t;history.&n; *&t;&t;Dave Gregorich&t;:&t;NULL ip_rt_put fix for multicast &n; *&t;&t;&t;&t;&t;routing.&n; *&t;&t;Jos Vos&t;&t;:&t;Add call_out_firewall before sending,&n; *&t;&t;&t;&t;&t;use output device for accounting.&n; *&t;&t;Jos Vos&t;&t;:&t;Call forward firewall after routing&n; *&t;&t;&t;&t;&t;(always use output device).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;linux/ip_fw.h&gt;
macro_line|#ifdef CONFIG_IP_MASQUERADE
macro_line|#include &lt;net/ip_masq.h&gt;
macro_line|#endif
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#ifdef CONFIG_IP_TRANSPARENT_PROXY
multiline_comment|/*&n; *&t;Check the packet against our socket administration to see&n; *&t;if it is related to a connection on our system.&n; *&t;Needed for transparent proxying.&n; */
DECL|function|ip_chksock
r_int
id|ip_chksock
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_switch
c_cond
(paren
id|skb-&gt;nh.iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_ICMP
suffix:colon
r_return
id|icmp_chkaddr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_case
id|IPPROTO_TCP
suffix:colon
r_return
id|tcp_chkaddr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
r_return
id|udp_chkaddr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|ip_forward
r_int
id|ip_forward
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|device
op_star
id|dev2
suffix:semicolon
multiline_comment|/* Output device */
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
multiline_comment|/* Our header */
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route we use */
r_struct
id|ip_options
op_star
id|opt
op_assign
op_amp
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_FIREWALL) || defined(CONFIG_IP_MASQUERADE)
r_int
id|fw_res
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;According to the RFC, we must first decrease the TTL field. If&n;&t; *&t;that reaches zero, we must reply an ICMP control message telling&n;&t; *&t;that the packet&squot;s lifetime expired.&n;&t; */
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
macro_line|#ifdef CONFIG_TRANSPARENT_PROXY
r_if
c_cond
(paren
id|ip_chk_sock
c_func
(paren
id|skb
)paren
)paren
r_return
id|ip_local_deliver
c_func
(paren
id|skb
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ip_decrease_ttl
c_func
(paren
id|iph
)paren
op_le
l_int|0
)paren
(brace
multiline_comment|/* Tell the sender its packet died... */
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_TIME_EXCEEDED
comma
id|ICMP_EXC_TTL
comma
l_int|0
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;is_strictroute
op_logical_and
(paren
id|rt-&gt;rt_flags
op_amp
id|RTF_GATEWAY
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Strict routing permits no gatewaying&n;&t;&t; */
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_SR_FAILED
comma
l_int|0
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Having picked a route we can now send the frame out&n;&t; *&t;after asking the firewall permission to do so.&n;&t; */
id|skb-&gt;priority
op_assign
id|rt-&gt;u.dst.priority
suffix:semicolon
id|dev2
op_assign
id|rt-&gt;u.dst.dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;In IP you never have to forward a frame on the interface that it &n;&t; *&t;arrived upon. We now generate an ICMP HOST REDIRECT giving the route&n;&t; *&t;we calculated.&n;&t; */
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_DOREDIRECT
op_logical_and
op_logical_neg
id|opt-&gt;srr
)paren
id|ip_rt_send_redirect
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We now may allocate a new buffer, and copy the datagram into it.&n;&t; * If the indicated interface is up and running, kick it.&n;&t; */
r_if
c_cond
(paren
id|dev2-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|dev2-&gt;mtu
op_logical_and
(paren
id|ntohs
c_func
(paren
id|iph-&gt;frag_off
)paren
op_amp
id|IP_DF
)paren
)paren
(brace
id|ip_statistics.IpFragFails
op_increment
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_FRAG_NEEDED
comma
id|htonl
c_func
(paren
id|dev2-&gt;mtu
)paren
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_NAT
)paren
(brace
r_if
c_cond
(paren
id|ip_do_nat
c_func
(paren
id|skb
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IP_MASQUERADE
r_if
c_cond
(paren
op_logical_neg
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_amp
id|IPSKB_MASQUERADED
)paren
)paren
(brace
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_VALVE
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PKT_FILTERED
comma
l_int|0
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
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n;&t;&t;&t; *&t;Check that any ICMP packets are not for a &n;&t;&t;&t; *&t;masqueraded connection.  If so rewrite them&n;&t;&t;&t; *&t;and skip the firewall checks&n;&t;&t;&t; */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
)paren
(brace
r_if
c_cond
(paren
(paren
id|fw_res
op_assign
id|ip_fw_masq_icmp
c_func
(paren
op_amp
id|skb
comma
id|dev2
)paren
)paren
OL
l_int|0
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
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fw_res
)paren
multiline_comment|/* ICMP matched - skip firewall */
r_goto
id|skip_call_fw_firewall
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rt-&gt;rt_flags
op_amp
id|RTCF_MASQ
)paren
r_goto
id|skip_call_fw_firewall
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FIREWALL
id|fw_res
op_assign
id|call_fw_firewall
c_func
(paren
id|PF_INET
comma
id|dev2
comma
id|iph
comma
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|fw_res
)paren
(brace
r_case
id|FW_ACCEPT
suffix:colon
r_case
id|FW_MASQUERADE
suffix:colon
r_break
suffix:semicolon
r_case
id|FW_REJECT
suffix:colon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_HOST_UNREACH
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* fall thru */
r_default
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_IP_MASQUERADE
)brace
id|skip_call_fw_firewall
suffix:colon
multiline_comment|/*&n;&t;&t; * If this fragment needs masquerading, make it so...&n;&t;&t; * (Don&squot;t masquerade de-masqueraded fragments)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|flags
op_amp
id|IPSKB_MASQUERADED
)paren
op_logical_and
(paren
id|fw_res
op_eq
id|FW_MASQUERADE
op_logical_or
id|rt-&gt;rt_flags
op_amp
id|RTCF_MASQ
)paren
)paren
(brace
r_if
c_cond
(paren
id|ip_fw_masquerade
c_func
(paren
op_amp
id|skb
comma
id|dev2
)paren
OL
l_int|0
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
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|dev2-&gt;hard_header_len
op_logical_or
id|skb_cloned
c_func
(paren
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
(paren
id|dev2-&gt;hard_header_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
id|NETDEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nIP: No memory available for IP forward&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|skb
op_assign
id|skb2
suffix:semicolon
id|iph
op_assign
id|skb2-&gt;nh.iph
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FIREWALL
r_if
c_cond
(paren
(paren
id|fw_res
op_assign
id|call_out_firewall
c_func
(paren
id|PF_INET
comma
id|dev2
comma
id|iph
comma
l_int|NULL
)paren
)paren
OL
id|FW_ACCEPT
)paren
(brace
multiline_comment|/* FW_ACCEPT and FW_MASQUERADE are treated equal:&n;&t;&t;&t;   masquerading is only supported via forward rules */
r_if
c_cond
(paren
id|fw_res
op_eq
id|FW_REJECT
)paren
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_HOST_UNREACH
comma
l_int|0
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|ip_statistics.IpForwDatagrams
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;optlen
)paren
id|ip_forward_options
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ip_send
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
