multiline_comment|/* Masquerading compatibility layer.&n;&n;   Note that there are no restrictions on other programs binding to&n;   ports 61000:65095 (in 2.0 and 2.2 they get EADDRINUSE).  Just DONT&n;   DO IT.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;net/route.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_conntrack_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_conntrack_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
r_int
r_int
DECL|function|do_masquerade
id|do_masquerade
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|ip_nat_info
op_star
id|info
suffix:semicolon
r_enum
id|ip_conntrack_info
id|ctinfo
suffix:semicolon
r_struct
id|ip_conntrack
op_star
id|ct
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
multiline_comment|/* Sorry, only ICMP, TCP and UDP. */
r_if
c_cond
(paren
id|iph-&gt;protocol
op_ne
id|IPPROTO_ICMP
op_logical_and
id|iph-&gt;protocol
op_ne
id|IPPROTO_TCP
op_logical_and
id|iph-&gt;protocol
op_ne
id|IPPROTO_UDP
)paren
r_return
id|NF_DROP
suffix:semicolon
multiline_comment|/* Feed it to connection tracking; in fact we&squot;re in NF_IP_FORWARD,&n;           but connection tracking doesn&squot;t expect that */
id|ret
op_assign
id|ip_conntrack_in
c_func
(paren
id|NF_IP_POST_ROUTING
comma
id|pskb
comma
id|dev
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|NF_ACCEPT
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_in returned %u.&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ct
op_assign
id|ip_conntrack_get
c_func
(paren
op_star
id|pskb
comma
op_amp
id|ctinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ct
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_in set to invalid conntrack.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|info
op_assign
op_amp
id|ct-&gt;nat.info
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Setup the masquerade, if not already */
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;initialized
)paren
(brace
id|u_int32_t
id|newsrc
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|ip_nat_multi_range
id|range
suffix:semicolon
multiline_comment|/* Pass 0 instead of saddr, since it&squot;s going to be changed&n;&t;&t;   anyway. */
r_if
c_cond
(paren
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|iph-&gt;daddr
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipnat_rule_masquerade: Can&squot;t reroute.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|newsrc
op_assign
id|inet_select_addr
c_func
(paren
id|rt-&gt;u.dst.dev
comma
id|rt-&gt;rt_gateway
comma
id|RT_SCOPE_UNIVERSE
)paren
suffix:semicolon
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
id|range
op_assign
(paren
(paren
r_struct
id|ip_nat_multi_range
)paren
(brace
l_int|1
comma
(brace
(brace
id|IP_NAT_RANGE_MAP_IPS
op_or
id|IP_NAT_RANGE_PROTO_SPECIFIED
comma
id|newsrc
comma
id|newsrc
comma
(brace
id|htons
c_func
(paren
l_int|61000
)paren
)brace
comma
(brace
id|htons
c_func
(paren
l_int|65095
)paren
)brace
)brace
)brace
)brace
)paren
suffix:semicolon
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|range
comma
id|NF_IP_POST_ROUTING
)paren
suffix:semicolon
id|place_in_hashes
c_func
(paren
id|ct
comma
id|info
)paren
suffix:semicolon
id|info-&gt;initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|DEBUGP
c_func
(paren
l_string|&quot;Masquerading already done on this conn.&bslash;n&quot;
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|do_bindings
c_func
(paren
id|ct
comma
id|ctinfo
comma
id|info
comma
id|NF_IP_POST_ROUTING
comma
id|pskb
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|check_for_demasq
id|check_for_demasq
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|ip_conntrack_tuple
id|tuple
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|ip_conntrack_protocol
op_star
id|protocol
suffix:semicolon
r_struct
id|ip_conntrack_tuple_hash
op_star
id|h
suffix:semicolon
r_enum
id|ip_conntrack_info
id|ctinfo
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|protocol
op_assign
id|find_proto
c_func
(paren
id|iph-&gt;protocol
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t feed packets to conntrack system unless we know&n;           they&squot;re part of an connection already established by an&n;           explicit masq command. */
r_switch
c_cond
(paren
id|iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_ICMP
suffix:colon
multiline_comment|/* ICMP errors. */
r_if
c_cond
(paren
id|icmp_error_track
c_func
(paren
op_star
id|pskb
)paren
)paren
(brace
multiline_comment|/* If it is valid, tranlsate it */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfct
)paren
(brace
r_struct
id|ip_conntrack
op_star
id|ct
op_assign
(paren
r_struct
id|ip_conntrack
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfct-&gt;master
suffix:semicolon
r_enum
id|ip_conntrack_dir
id|dir
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfct
op_minus
id|ct-&gt;infos
op_ge
id|IP_CT_IS_REPLY
)paren
id|dir
op_assign
id|IP_CT_DIR_REPLY
suffix:semicolon
r_else
id|dir
op_assign
id|IP_CT_DIR_ORIGINAL
suffix:semicolon
id|icmp_reply_translation
c_func
(paren
op_star
id|pskb
comma
id|ct
comma
id|NF_IP_PRE_ROUTING
comma
id|dir
)paren
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Fall thru... */
r_case
id|IPPROTO_TCP
suffix:colon
r_case
id|IPPROTO_UDP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|get_tuple
c_func
(paren
id|iph
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
comma
op_amp
id|tuple
comma
id|protocol
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_fw_compat_masq: Couldn&squot;t get tuple&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Not ours... */
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|h
op_assign
id|ip_conntrack_find_get
c_func
(paren
op_amp
id|tuple
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* MUST be found, and MUST be reply. */
r_if
c_cond
(paren
id|h
op_logical_and
id|DIRECTION
c_func
(paren
id|h
)paren
op_eq
l_int|1
)paren
(brace
id|ret
op_assign
id|ip_conntrack_in
c_func
(paren
id|NF_IP_PRE_ROUTING
comma
id|pskb
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Put back the reference gained from find_get */
id|nf_conntrack_put
c_func
(paren
op_amp
id|h-&gt;ctrack-&gt;infos
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|NF_ACCEPT
)paren
(brace
r_struct
id|ip_conntrack
op_star
id|ct
suffix:semicolon
id|ct
op_assign
id|ip_conntrack_get
c_func
(paren
op_star
id|pskb
comma
op_amp
id|ctinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ct
)paren
(brace
r_struct
id|ip_nat_info
op_star
id|info
op_assign
op_amp
id|ct-&gt;nat.info
suffix:semicolon
id|do_bindings
c_func
(paren
id|ct
comma
id|ctinfo
comma
id|info
comma
id|NF_IP_PRE_ROUTING
comma
id|pskb
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;ip_fw_compat_masq: conntrack&quot;
l_string|&quot; didn&squot;t like&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|h
)paren
multiline_comment|/* Put back the reference gained from find_get */
id|nf_conntrack_put
c_func
(paren
op_amp
id|h-&gt;ctrack-&gt;infos
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|NF_ACCEPT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ip_fw_masq_timeouts
r_int
id|ip_fw_masq_timeouts
c_func
(paren
r_void
op_star
id|user
comma
r_int
id|len
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Sorry: masquerading timeouts set 5DAYS/2MINS/60SECS&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|masq_proto_name
r_static
r_const
r_char
op_star
id|masq_proto_name
c_func
(paren
id|u_int16_t
id|protonum
)paren
(brace
r_switch
c_cond
(paren
id|protonum
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
r_return
l_string|&quot;TCP&quot;
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
r_return
l_string|&quot;UDP&quot;
suffix:semicolon
r_case
id|IPPROTO_ICMP
suffix:colon
r_return
l_string|&quot;ICMP&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;MORE-CAFFIENE-FOR-RUSTY&quot;
suffix:semicolon
)brace
)brace
r_static
r_int
r_int
DECL|function|print_masq
id|print_masq
c_func
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
(brace
r_char
id|temp
(braket
l_int|129
)braket
suffix:semicolon
multiline_comment|/* This is for backwards compatibility, but ick!.&n;&t;   We should never export jiffies to userspace.&n;&t;*/
id|sprintf
c_func
(paren
id|temp
comma
l_string|&quot;%s %08X:%04X %08X:%04X %04X %08X %6d %6d %7lu&quot;
comma
id|masq_proto_name
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.protonum
)paren
comma
id|ntohl
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.src.ip
)paren
comma
id|ntohs
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.src.u.all
)paren
comma
id|ntohl
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.ip
)paren
comma
id|ntohs
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|0
)braket
dot
id|tuple.dst.u.all
)paren
comma
id|ntohs
c_func
(paren
id|conntrack-&gt;tuplehash
(braket
l_int|1
)braket
dot
id|tuple.dst.u.all
)paren
comma
multiline_comment|/* Sorry, no init_seq, delta or previous_delta (yet). */
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|conntrack-&gt;timeout.expires
op_minus
id|jiffies
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-127s&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns true when finished. */
r_static
r_int
DECL|function|masq_iterate
id|masq_iterate
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple_hash
op_star
id|hash
comma
r_char
op_star
id|buffer
comma
id|off_t
id|offset
comma
id|off_t
op_star
id|upto
comma
r_int
r_int
op_star
id|len
comma
r_int
r_int
id|maxlen
)paren
(brace
r_int
r_int
id|newlen
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|hash-&gt;ctrack
)paren
suffix:semicolon
multiline_comment|/* Only count originals */
r_if
c_cond
(paren
id|DIRECTION
c_func
(paren
id|hash
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|upto
)paren
op_increment
OL
id|offset
)paren
r_return
l_int|0
suffix:semicolon
id|newlen
op_assign
id|print_masq
c_func
(paren
id|buffer
op_plus
op_star
id|len
comma
id|hash-&gt;ctrack
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|len
op_plus
id|newlen
OG
id|maxlen
)paren
r_return
l_int|1
suffix:semicolon
r_else
op_star
id|len
op_add_assign
id|newlen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Everything in the hash is masqueraded. */
r_static
r_int
DECL|function|masq_procinfo
id|masq_procinfo
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
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|upto
op_assign
l_int|0
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* Traverse hash; print originals then reply. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ip_conntrack_htable_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|LIST_FIND
c_func
(paren
op_amp
id|ip_conntrack_hash
(braket
id|i
)braket
comma
id|masq_iterate
comma
r_struct
id|ip_conntrack_tuple_hash
op_star
comma
id|buffer
comma
id|offset
comma
op_amp
id|upto
comma
op_amp
id|len
comma
id|length
)paren
)paren
r_break
suffix:semicolon
)brace
id|READ_UNLOCK
c_func
(paren
op_amp
id|ip_conntrack_lock
)paren
suffix:semicolon
multiline_comment|/* `start&squot; hack - see fs/proc/generic.c line ~165 */
op_star
id|start
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|upto
op_minus
id|offset
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|masq_init
r_int
id|__init
id|masq_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ip_conntrack_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
id|ip_nat_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|proc_net_create
c_func
(paren
l_string|&quot;ip_masquerade&quot;
comma
l_int|0
comma
id|masq_procinfo
)paren
suffix:semicolon
r_else
id|ip_conntrack_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|masq_cleanup
r_void
id|masq_cleanup
c_func
(paren
r_void
)paren
(brace
id|ip_nat_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ip_conntrack_cleanup
c_func
(paren
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;ip_masquerade&quot;
)paren
suffix:semicolon
)brace
eof
