multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The IP forwarding functionality.&n; *&t;&t;&n; * Authors:&t;see ip.c&n; *&n; * Fixes:&n; *&t;&t;Many&t;&t;:&t;Split from ip.c , see ip_input.c for history.&n; */
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
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;linux/ip_fw.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#ifdef CONFIG_IP_FORWARD
macro_line|#ifdef CONFIG_IP_MROUTE
multiline_comment|/*&n; * &t;Encapsulate a packet by attaching a valid IPIP header to it.&n; *&t;This avoids tunnel drivers and other mess and gives us the speed so&n; *&t;important for multicast video.&n; */
DECL|function|ip_encap
r_static
r_void
id|ip_encap
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
comma
r_struct
id|device
op_star
id|out
comma
id|__u32
id|daddr
)paren
(brace
multiline_comment|/*&n;&t; *&t;There is space for the IPIP header and MAC left.&n;&t; *&n;&t; *&t;Firstly push down and install the IPIP header.&n;&t; */
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
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|65515
)paren
(brace
id|len
op_assign
l_int|65515
suffix:semicolon
)brace
id|iph-&gt;version
op_assign
l_int|4
suffix:semicolon
id|iph-&gt;tos
op_assign
id|skb-&gt;ip_hdr-&gt;tos
suffix:semicolon
id|iph-&gt;ttl
op_assign
id|skb-&gt;ip_hdr-&gt;ttl
suffix:semicolon
id|iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|daddr
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|out-&gt;pa_addr
suffix:semicolon
id|iph-&gt;protocol
op_assign
id|IPPROTO_IPIP
suffix:semicolon
id|iph-&gt;ihl
op_assign
l_int|5
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|iph-&gt;id
op_assign
id|htons
c_func
(paren
id|ip_id_count
op_increment
)paren
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|out
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;raddr
op_assign
id|daddr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now add the physical header (driver will push it down).&n;&t; */
r_if
c_cond
(paren
id|out-&gt;hard_header
op_logical_and
id|out
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|out
comma
id|ETH_P_IP
comma
l_int|NULL
comma
l_int|NULL
comma
id|len
)paren
OL
l_int|0
)paren
id|skb-&gt;arp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Read to queue for transmission.&n;&t; */
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Forward an IP datagram to its next destination.&n; */
DECL|function|ip_forward
r_int
id|ip_forward
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
r_int
id|is_frag
comma
id|__u32
id|target_addr
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
id|sk_buff
op_star
id|skb2
suffix:semicolon
multiline_comment|/* Output packet */
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Route we use */
r_int
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* Data pointer */
r_int
r_int
id|raddr
suffix:semicolon
multiline_comment|/* Router IP address */
r_struct
id|options
op_star
id|opt
op_assign
(paren
r_struct
id|options
op_star
)paren
id|skb-&gt;proto_priv
suffix:semicolon
r_struct
id|hh_cache
op_star
id|hh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|encap
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Encap length */
macro_line|#ifdef CONFIG_FIREWALL
r_int
id|fw_res
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Forwarding result */
macro_line|#ifdef CONFIG_IP_MASQUERADE&t;
r_struct
id|sk_buff
op_star
id|skb_in
op_assign
id|skb
suffix:semicolon
multiline_comment|/* So we can remember if the masquerader did some swaps */
macro_line|#endif
multiline_comment|/* &n;&t; *&t;See if we are allowed to forward this.&n; &t; *&t;Note: demasqueraded fragments are always &squot;back&squot;warded.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|is_frag
op_amp
l_int|4
)paren
)paren
(brace
id|fw_res
op_assign
id|call_fw_firewall
c_func
(paren
id|PF_INET
comma
id|skb
comma
id|skb-&gt;h.iph
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
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* fall thru */
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t; *&t;According to the RFC, we must first decrease the TTL field. If&n;&t; *&t;that reaches zero, we must reply an ICMP control message telling&n;&t; *&t;that the packet&squot;s lifetime expired.&n;&t; *&n;&t; *&t;Exception:&n;&t; *&t;We may not generate an ICMP for an ICMP. icmp_send does the&n;&t; *&t;enforcement of this so we can forget it here. It is however&n;&t; *&t;sometimes VERY important.&n;&t; */
id|iph
op_assign
id|skb-&gt;h.iph
suffix:semicolon
id|iph-&gt;ttl
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Re-compute the IP header checksum.&n;&t; *&t;This is inefficient. We know what has happened to the header&n;&t; *&t;and could thus adjust the checksum as Phil Karn does in KA9Q&n;&t; */
id|iph-&gt;check
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;check
)paren
op_plus
l_int|0x0100
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iph-&gt;check
op_amp
l_int|0xFF00
)paren
op_eq
l_int|0
)paren
id|iph-&gt;check
op_increment
suffix:semicolon
multiline_comment|/* carry overflow */
id|iph-&gt;check
op_assign
id|htons
c_func
(paren
id|iph-&gt;check
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;ttl
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
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
op_logical_neg
(paren
id|is_frag
op_amp
l_int|8
)paren
)paren
(brace
macro_line|#endif&t;
multiline_comment|/*&n;&t;&t; * OK, the packet is still valid.  Fetch its destination address,&n;&t;&t; * and give it to the IP sender for further processing.&n;&t;&t; */
id|rt
op_assign
id|ip_rt_route
c_func
(paren
id|target_addr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Tell the sender its packet cannot be delivered. Again&n;&t;&t;&t; *&t;ICMP is screened later.&n;&t;&t;&t; */
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_NET_UNREACH
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Gosh.  Not only is the packet valid; we even know how to&n;&t;&t; * forward it onto its final destination.  Can we say this&n;&t;&t; * is being plain lucky?&n;&t;&t; * If the router told us that there is no GW, use the dest.&n;&t;&t; * IP address itself- we seem to be connected directly...&n;&t;&t; */
id|raddr
op_assign
id|rt-&gt;rt_gateway
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t; *&t;Strict routing permits no gatewaying&n;&t;&t;&t; */
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
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
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Having picked a route we can now send the frame out.&n;&t;&t; */
id|dev2
op_assign
id|rt-&gt;rt_dev
suffix:semicolon
id|hh
op_assign
id|rt-&gt;rt_hh
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;In IP you never have to forward a frame on the interface that it &n;&t;&t; *&t;arrived upon. We now generate an ICMP HOST REDIRECT giving the route&n;&t;&t; *&t;we calculated.&n;&t;&t; */
macro_line|#ifndef CONFIG_IP_NO_ICMP_REDIRECT
r_if
c_cond
(paren
id|dev
op_eq
id|dev2
op_logical_and
op_logical_neg
(paren
(paren
id|iph-&gt;saddr
op_xor
id|iph-&gt;daddr
)paren
op_amp
id|dev-&gt;pa_mask
)paren
op_logical_and
(paren
id|rt-&gt;rt_flags
op_amp
id|RTF_MODIFIED
)paren
op_logical_and
op_logical_neg
id|opt-&gt;srr
)paren
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_REDIRECT
comma
id|ICMP_REDIR_HOST
comma
id|raddr
comma
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IP_MROUTE
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *&t;Multicast route forward. Routing is already done&n;&t;&t; */
id|dev2
op_assign
id|skb-&gt;dev
suffix:semicolon
id|raddr
op_assign
id|skb-&gt;raddr
suffix:semicolon
r_if
c_cond
(paren
id|is_frag
op_amp
l_int|16
)paren
(brace
multiline_comment|/* VIFF_TUNNEL mode */
id|encap
op_assign
l_int|20
suffix:semicolon
)brace
id|rt
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif&t;
multiline_comment|/*&n;&t; * We now may allocate a new buffer, and copy the datagram into it.&n;&t; * If the indicated interface is up and running, kick it.&n;&t; */
r_if
c_cond
(paren
id|dev2-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
macro_line|#ifdef CONFIG_IP_MASQUERADE
multiline_comment|/*&n;&t;&t; * If this fragment needs masquerading, make it so...&n;&t;&t; * (Dont masquerade de-masqueraded fragments)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|is_frag
op_amp
l_int|4
)paren
op_logical_and
id|fw_res
op_eq
id|FW_MASQUERADE
)paren
id|ip_fw_masquerade
c_func
(paren
op_amp
id|skb
comma
id|dev2
)paren
suffix:semicolon
macro_line|#endif
id|IS_SKB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_plus
id|encap
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
comma
id|dev
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
op_minus
id|encap
OL
id|dev2-&gt;hard_header_len
)paren
(brace
id|skb2
op_assign
id|alloc_skb
c_func
(paren
id|dev2-&gt;hard_header_len
op_plus
id|skb-&gt;len
op_plus
id|encap
op_plus
l_int|15
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
macro_line|#else
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
)paren
(brace
id|skb2
op_assign
id|alloc_skb
c_func
(paren
id|dev2-&gt;hard_header_len
op_plus
id|skb-&gt;len
op_plus
l_int|15
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
macro_line|#endif&t;&t;
multiline_comment|/*&n;&t;&t;&t; *&t;This is rare and since IP is tolerant of network failures&n;&t;&t;&t; *&t;quite harmless.&n;&t;&t;&t; */
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
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|IS_SKB
c_func
(paren
id|skb2
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Add the physical headers.&n;&t;&t;&t; */
id|skb2-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
id|is_frag
op_amp
l_int|16
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
(paren
id|encap
op_plus
id|dev-&gt;hard_header_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
suffix:semicolon
multiline_comment|/* 16 byte aligned IP headers are good */
id|ip_encap
c_func
(paren
id|skb2
comma
id|skb-&gt;len
comma
id|dev2
comma
id|raddr
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif&t;&t;&t;
id|ip_send
c_func
(paren
id|rt
comma
id|skb2
comma
id|raddr
comma
id|skb-&gt;len
comma
id|dev2
comma
id|dev2-&gt;pa_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;We have to copy the bytes over as the new header wouldn&squot;t fit&n;&t;&t;&t; *&t;the old buffer. This should be very rare.&n;&t;&t;&t; */
id|ptr
op_assign
id|skb_put
c_func
(paren
id|skb2
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|skb2-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb2-&gt;h.raw
op_assign
id|ptr
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Copy the packet data into the new buffer.&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|ptr
comma
id|skb-&gt;h.raw
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb2-&gt;proto_priv
comma
id|skb-&gt;proto_priv
comma
r_sizeof
(paren
id|skb-&gt;proto_priv
)paren
)paren
suffix:semicolon
id|iph
op_assign
id|skb2-&gt;ip_hdr
op_assign
id|skb2-&gt;h.iph
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* &n;&t;&t;&t; *&t;Build a new MAC header. &n;&t;&t;&t; */
id|skb2
op_assign
id|skb
suffix:semicolon
id|skb2-&gt;dev
op_assign
id|dev2
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MROUTE
r_if
c_cond
(paren
id|is_frag
op_amp
l_int|16
)paren
(brace
id|ip_encap
c_func
(paren
id|skb
comma
id|skb-&gt;len
comma
id|dev2
comma
id|raddr
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#endif
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;raddr
op_assign
id|raddr
suffix:semicolon
r_if
c_cond
(paren
id|hh
)paren
(brace
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
id|dev2-&gt;hard_header_len
)paren
comma
id|hh-&gt;hh_data
comma
id|dev2-&gt;hard_header_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hh-&gt;hh_uptodate
)paren
(brace
macro_line|#if RT_CACHE_DEBUG &gt;= 2
id|printk
c_func
(paren
l_string|&quot;ip_forward: hh miss %08x via %08x&bslash;n&quot;
comma
id|target_addr
comma
id|rt-&gt;rt_gateway
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;&t;&t;
id|skb-&gt;arp
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dev2-&gt;hard_header
)paren
(brace
r_if
c_cond
(paren
id|dev2
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev2
comma
id|ETH_P_IP
comma
l_int|NULL
comma
l_int|NULL
comma
id|skb-&gt;len
)paren
OL
l_int|0
)paren
(brace
id|skb-&gt;arp
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IP_MROUTE
)brace
macro_line|#endif&t;&t;&t;
id|ip_statistics.IpForwDatagrams
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;optlen
)paren
(brace
r_int
r_char
op_star
id|optptr
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;rr_needaddr
)paren
(brace
id|optptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|iph
op_plus
id|opt-&gt;rr
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|optptr
(braket
id|optptr
(braket
l_int|2
)braket
op_minus
l_int|5
)braket
comma
op_amp
id|dev2-&gt;pa_addr
comma
l_int|4
)paren
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;srr_is_hit
)paren
(brace
r_int
id|srrptr
comma
id|srrspace
suffix:semicolon
id|optptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|iph
op_plus
id|opt-&gt;srr
suffix:semicolon
r_for
c_loop
(paren
id|srrptr
op_assign
id|optptr
(braket
l_int|2
)braket
comma
id|srrspace
op_assign
id|optptr
(braket
l_int|1
)braket
suffix:semicolon
id|srrptr
op_le
id|srrspace
suffix:semicolon
id|srrptr
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|srrptr
op_plus
l_int|3
OG
id|srrspace
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|target_addr
comma
op_amp
id|optptr
(braket
id|srrptr
op_minus
l_int|1
)braket
comma
l_int|4
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srrptr
op_plus
l_int|3
op_le
id|srrspace
)paren
(brace
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|optptr
(braket
id|srrptr
op_minus
l_int|1
)braket
comma
op_amp
id|dev2-&gt;pa_addr
comma
l_int|4
)paren
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|target_addr
suffix:semicolon
id|optptr
(braket
l_int|2
)braket
op_assign
id|srrptr
op_plus
l_int|4
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;ip_forward(): Argh! Destination lost!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;ts_needaddr
)paren
(brace
id|optptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|iph
op_plus
id|opt-&gt;ts
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|optptr
(braket
id|optptr
(braket
l_int|2
)braket
op_minus
l_int|9
)braket
comma
op_amp
id|dev2-&gt;pa_addr
comma
l_int|4
)paren
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;is_changed
)paren
(brace
id|opt-&gt;is_changed
op_assign
l_int|0
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * ANK:  this is point of &quot;no return&quot;, we cannot send an ICMP,&n; *       because we changed SRR option.&n; */
multiline_comment|/*&n;&t;&t; *&t;See if it needs fragmenting. Note in ip_rcv we tagged&n;&t;&t; *&t;the fragment type. This must be right so that&n;&t;&t; *&t;the fragmenter does the right thing.&n;&t;&t; */
r_if
c_cond
(paren
id|skb2-&gt;len
OG
id|dev2-&gt;mtu
op_plus
id|dev2-&gt;hard_header_len
)paren
(brace
id|ip_fragment
c_func
(paren
l_int|NULL
comma
id|skb2
comma
id|dev2
comma
id|is_frag
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb2
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef CONFIG_IP_ACCT&t;&t;
multiline_comment|/*&n;&t;&t;&t; *&t;Count mapping we shortcut&n;&t;&t;&t; */
id|ip_fw_chk
c_func
(paren
id|iph
comma
id|dev
comma
id|ip_acct_chain
comma
id|IP_FW_F_ACCEPT
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;
multiline_comment|/*&n;&t;&t;&t; *&t;Map service types to priority. We lie about&n;&t;&t;&t; *&t;throughput being low priority, but it&squot;s a good&n;&t;&t;&t; *&t;choice to help improve general usage.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|iph-&gt;tos
op_amp
id|IPTOS_LOWDELAY
)paren
(brace
id|dev_queue_xmit
c_func
(paren
id|skb2
comma
id|dev2
comma
id|SOPRI_INTERACTIVE
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|iph-&gt;tos
op_amp
id|IPTOS_THROUGHPUT
)paren
(brace
id|dev_queue_xmit
c_func
(paren
id|skb2
comma
id|dev2
comma
id|SOPRI_BACKGROUND
)paren
suffix:semicolon
)brace
r_else
id|dev_queue_xmit
c_func
(paren
id|skb2
comma
id|dev2
comma
id|SOPRI_NORMAL
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Tell the caller if their buffer is free.&n;&t; */
r_if
c_cond
(paren
id|skb
op_eq
id|skb2
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_MASQUERADE&t;
multiline_comment|/*&n;&t; *&t;The original is free. Free our copy and&n;&t; *&t;tell the caller not to free.&n;&t; */
r_if
c_cond
(paren
id|skb
op_ne
id|skb_in
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb_in
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof