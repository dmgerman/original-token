multiline_comment|/*&n; * This is a module which is used for rejecting packets.&n; * Added support for customized reject packets (Jozsef Kadlecsik).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
r_struct
id|in_device
suffix:semicolon
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_REJECT.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
multiline_comment|/* Send RST reply */
DECL|function|send_reset
r_static
r_void
id|send_reset
c_func
(paren
r_struct
id|sk_buff
op_star
id|oldskb
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_struct
id|tcphdr
op_star
id|otcph
comma
op_star
id|tcph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_int
r_int
id|otcplen
suffix:semicolon
r_int
id|needs_ack
suffix:semicolon
multiline_comment|/* IP header checks: fragment, too short. */
r_if
c_cond
(paren
id|oldskb-&gt;nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_OFFSET
)paren
op_logical_or
id|oldskb-&gt;len
OL
(paren
id|oldskb-&gt;nh.iph-&gt;ihl
op_lshift
l_int|2
)paren
op_plus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
r_return
suffix:semicolon
id|otcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|oldskb-&gt;nh.iph
op_plus
id|oldskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
id|otcplen
op_assign
id|oldskb-&gt;len
op_minus
id|oldskb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* No RST for RST. */
r_if
c_cond
(paren
id|otcph-&gt;rst
)paren
r_return
suffix:semicolon
multiline_comment|/* Check checksum. */
r_if
c_cond
(paren
id|tcp_v4_check
c_func
(paren
id|otcph
comma
id|otcplen
comma
id|oldskb-&gt;nh.iph-&gt;saddr
comma
id|oldskb-&gt;nh.iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|otcph
comma
id|otcplen
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* Copy skb (even if skb is about to be dropped, we can&squot;t just&n;           clone it because there may be other things, such as tcpdump,&n;           interested in it) */
id|nskb
op_assign
id|skb_copy
c_func
(paren
id|oldskb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
r_return
suffix:semicolon
multiline_comment|/* This packet will not be the same as the other: clear nf fields */
id|nf_conntrack_put
c_func
(paren
id|nskb-&gt;nfct
)paren
suffix:semicolon
id|nskb-&gt;nfct
op_assign
l_int|NULL
suffix:semicolon
id|nskb-&gt;nfcache
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|nskb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
id|nskb-&gt;nh.iph
op_plus
id|nskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;daddr
op_assign
id|xchg
c_func
(paren
op_amp
id|nskb-&gt;nh.iph-&gt;saddr
comma
id|nskb-&gt;nh.iph-&gt;daddr
)paren
suffix:semicolon
id|tcph-&gt;source
op_assign
id|xchg
c_func
(paren
op_amp
id|tcph-&gt;dest
comma
id|tcph-&gt;source
)paren
suffix:semicolon
multiline_comment|/* Truncate to length (no data) */
id|tcph-&gt;doff
op_assign
r_sizeof
(paren
r_struct
id|tcphdr
)paren
op_div
l_int|4
suffix:semicolon
id|skb_trim
c_func
(paren
id|nskb
comma
id|nskb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
op_plus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
)paren
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|nskb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcph-&gt;ack
)paren
(brace
id|needs_ack
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;seq
op_assign
id|otcph-&gt;ack_seq
suffix:semicolon
id|tcph-&gt;ack_seq
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|needs_ack
op_assign
l_int|1
suffix:semicolon
id|tcph-&gt;ack_seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|otcph-&gt;seq
)paren
op_plus
id|otcph-&gt;syn
op_plus
id|otcph-&gt;fin
op_plus
id|otcplen
op_minus
(paren
id|otcph-&gt;doff
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|tcph-&gt;seq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset flags */
(paren
(paren
id|u_int8_t
op_star
)paren
id|tcph
)paren
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;rst
op_assign
l_int|1
suffix:semicolon
id|tcph-&gt;ack
op_assign
id|needs_ack
suffix:semicolon
id|tcph-&gt;window
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;urg_ptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Adjust TCP checksum */
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;check
op_assign
id|tcp_v4_check
c_func
(paren
id|tcph
comma
r_sizeof
(paren
r_struct
id|tcphdr
)paren
comma
id|nskb-&gt;nh.iph-&gt;saddr
comma
id|nskb-&gt;nh.iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
comma
r_sizeof
(paren
r_struct
id|tcphdr
)paren
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* Adjust IP TTL, DF */
id|nskb-&gt;nh.iph-&gt;ttl
op_assign
id|MAXTTL
suffix:semicolon
multiline_comment|/* Set DF, id = 0 */
id|nskb-&gt;nh.iph-&gt;frag_off
op_assign
id|htons
c_func
(paren
id|IP_DF
)paren
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Adjust IP checksum */
id|nskb-&gt;nh.iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|nskb-&gt;nh.iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|nskb-&gt;nh.iph
comma
id|nskb-&gt;nh.iph-&gt;ihl
)paren
suffix:semicolon
multiline_comment|/* Routing */
r_if
c_cond
(paren
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|nskb-&gt;nh.iph-&gt;daddr
comma
id|nskb-&gt;nh.iph-&gt;saddr
comma
id|RT_TOS
c_func
(paren
id|nskb-&gt;nh.iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
l_int|0
)paren
op_ne
l_int|0
)paren
r_goto
id|free_nskb
suffix:semicolon
id|dst_release
c_func
(paren
id|nskb-&gt;dst
)paren
suffix:semicolon
id|nskb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* &quot;Never happens&quot; */
r_if
c_cond
(paren
id|nskb-&gt;len
OG
id|nskb-&gt;dst-&gt;pmtu
)paren
r_goto
id|free_nskb
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_INET
comma
id|NF_IP_LOCAL_OUT
comma
id|nskb
comma
l_int|NULL
comma
id|nskb-&gt;dst-&gt;dev
comma
id|ip_finish_output
)paren
suffix:semicolon
r_return
suffix:semicolon
id|free_nskb
suffix:colon
id|kfree_skb
c_func
(paren
id|nskb
)paren
suffix:semicolon
)brace
DECL|function|reject
r_static
r_int
r_int
id|reject
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_const
r_struct
id|ipt_reject_info
op_star
id|reject
op_assign
id|targinfo
suffix:semicolon
multiline_comment|/* WARNING: This code causes reentry within iptables.&n;&t;   This means that the iptables jump stack is now crap.  We&n;&t;   must return an absolute verdict. --RR */
r_switch
c_cond
(paren
id|reject-&gt;with
)paren
(brace
r_case
id|IPT_ICMP_NET_UNREACHABLE
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_NET_UNREACH
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_HOST_UNREACHABLE
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_HOST_UNREACH
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_PROT_UNREACHABLE
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PROT_UNREACH
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_PORT_UNREACHABLE
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PORT_UNREACH
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_NET_PROHIBITED
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_NET_ANO
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_HOST_PROHIBITED
suffix:colon
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_HOST_ANO
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_ICMP_ECHOREPLY
suffix:colon
(brace
r_struct
id|icmphdr
op_star
id|icmph
op_assign
(paren
r_struct
id|icmphdr
op_star
)paren
(paren
(paren
id|u_int32_t
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
op_plus
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
)paren
suffix:semicolon
r_int
r_int
id|datalen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* Not non-head frags, or truncated */
r_if
c_cond
(paren
(paren
(paren
id|ntohs
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;frag_off
)paren
op_amp
id|IP_OFFSET
)paren
op_eq
l_int|0
)paren
op_logical_and
id|datalen
op_ge
l_int|4
)paren
(brace
multiline_comment|/* Usually I don&squot;t like cut &amp; pasting code,&n;                           but dammit, my party is starting in 45&n;                           mins! --RR */
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
id|datalen
suffix:semicolon
id|icmp_reply
c_func
(paren
op_amp
id|icmp_param
comma
op_star
id|pskb
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|IPT_TCP_RESET
suffix:colon
id|send_reset
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NF_DROP
suffix:semicolon
)brace
DECL|function|find_ping_match
r_static
r_inline
r_int
id|find_ping_match
c_func
(paren
r_const
r_struct
id|ipt_entry_match
op_star
id|m
)paren
(brace
r_const
r_struct
id|ipt_icmp
op_star
id|icmpinfo
op_assign
(paren
r_const
r_struct
id|ipt_icmp
op_star
)paren
id|m-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|m-&gt;u.kernel.match-&gt;name
comma
l_string|&quot;icmp&quot;
)paren
op_eq
l_int|0
op_logical_and
id|icmpinfo-&gt;type
op_eq
id|ICMP_ECHO
op_logical_and
op_logical_neg
(paren
id|icmpinfo-&gt;invflags
op_amp
id|IPT_ICMP_INV
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check
r_static
r_int
id|check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ipt_reject_info
op_star
id|rejinfo
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_icmp
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: targinfosize %u != 0&bslash;n&quot;
comma
id|targinfosize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Only allow these for packet filtering. */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;filter&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: bad table `%s&squot;.&bslash;n&quot;
comma
id|tablename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_FORWARD
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_OUT
)paren
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: bad hook mask %X&bslash;n&quot;
comma
id|hook_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rejinfo-&gt;with
op_eq
id|IPT_ICMP_ECHOREPLY
)paren
(brace
multiline_comment|/* Must specify that it&squot;s an ICMP ping packet. */
r_if
c_cond
(paren
id|e-&gt;ip.proto
op_ne
id|IPPROTO_ICMP
op_logical_or
(paren
id|e-&gt;ip.invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: ECHOREPLY illegal for non-icmp&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must contain ICMP match. */
r_if
c_cond
(paren
id|IPT_MATCH_ITERATE
c_func
(paren
id|e
comma
id|find_ping_match
)paren
op_eq
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: ECHOREPLY illegal for non-ping&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|rejinfo-&gt;with
op_eq
id|IPT_TCP_RESET
)paren
(brace
multiline_comment|/* Must specify that it&squot;s a TCP packet */
r_if
c_cond
(paren
id|e-&gt;ip.proto
op_ne
id|IPPROTO_TCP
op_logical_or
(paren
id|e-&gt;ip.invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;REJECT: TCP_RESET illegal for non-tcp&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipt_reject_reg
r_static
r_struct
id|ipt_target
id|ipt_reject_reg
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;REJECT&quot;
comma
id|reject
comma
id|check
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_reject_reg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_reject_reg
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
