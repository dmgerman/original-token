multiline_comment|/* FTP extension for IP connection tracking. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_ftp.h&gt;
DECL|variable|ip_ftp_lock
id|DECLARE_LOCK
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
DECL|variable|ip_conntrack_ftp
r_struct
id|module
op_star
id|ip_conntrack_ftp
op_assign
id|THIS_MODULE
suffix:semicolon
DECL|macro|SERVER_STRING
mdefine_line|#define SERVER_STRING &quot;227 Entering Passive Mode (&quot;
DECL|macro|CLIENT_STRING
mdefine_line|#define CLIENT_STRING &quot;PORT &quot;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|IP_PARTS_NATIVE
mdefine_line|#define IP_PARTS_NATIVE(n)&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;24)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;16)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&gt;&gt;8)&amp;0xFF,&t;&t;&t;&bslash;&n;(unsigned int)((n)&amp;0xFF)
DECL|macro|IP_PARTS
mdefine_line|#define IP_PARTS(n) IP_PARTS_NATIVE(ntohl(n))
r_static
r_struct
(brace
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|plen
r_int
id|plen
suffix:semicolon
DECL|member|term
r_char
id|term
suffix:semicolon
DECL|variable|search
)brace
id|search
(braket
l_int|2
)braket
op_assign
(brace
(braket
id|IP_CT_FTP_PORT
)braket
(brace
id|CLIENT_STRING
comma
r_sizeof
(paren
id|CLIENT_STRING
)paren
op_minus
l_int|1
comma
l_char|&squot;&bslash;r&squot;
)brace
comma
(braket
id|IP_CT_FTP_PASV
)braket
(brace
id|SERVER_STRING
comma
r_sizeof
(paren
id|SERVER_STRING
)paren
op_minus
l_int|1
comma
l_char|&squot;)&squot;
)brace
)brace
suffix:semicolon
multiline_comment|/* Returns 0, or length of numbers */
DECL|function|try_number
r_static
r_int
id|try_number
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
comma
r_char
id|term
)paren
(brace
id|u_int32_t
id|i
comma
id|len
suffix:semicolon
multiline_comment|/* Keep data pointing at next char. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|dlen
suffix:semicolon
id|len
op_increment
comma
id|data
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|data
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|data
op_le
l_char|&squot;9&squot;
)paren
(brace
id|array
(braket
id|i
)braket
op_assign
id|array
(braket
id|i
)braket
op_star
l_int|10
op_plus
op_star
id|data
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;,&squot;
)paren
id|i
op_increment
suffix:semicolon
r_else
(brace
multiline_comment|/* Unexpected character; true if it&squot;s the&n;&t;&t;&t;   terminator and we&squot;re finished. */
r_if
c_cond
(paren
op_star
id|data
op_eq
id|term
op_logical_and
id|i
op_eq
l_int|5
)paren
r_return
id|len
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Char %u (got %u nums) `%u&squot; unexpected&bslash;n&quot;
comma
id|len
comma
id|i
comma
op_star
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return 1 for match, 0 for accept, -1 for partial. */
DECL|function|find_pattern
r_static
r_int
id|find_pattern
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|dlen
comma
r_const
r_char
op_star
id|pattern
comma
r_int
id|plen
comma
r_char
id|term
comma
r_int
r_int
op_star
id|numoff
comma
r_int
r_int
op_star
id|numlen
comma
id|u_int32_t
id|array
(braket
l_int|6
)braket
)paren
(brace
r_if
c_cond
(paren
id|dlen
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dlen
OL
id|plen
)paren
(brace
multiline_comment|/* Short packet: try for partial? */
r_if
c_cond
(paren
id|strnicmp
c_func
(paren
id|data
comma
id|pattern
comma
id|dlen
)paren
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strnicmp
c_func
(paren
id|data
comma
id|pattern
comma
id|plen
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#if 0
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: string mismatch&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|plen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DEBUGFTP
c_func
(paren
l_string|&quot;ftp:char %u `%c&squot;(%u) vs `%c&squot;(%u)&bslash;n&quot;
comma
id|i
comma
id|data
(braket
id|i
)braket
comma
id|data
(braket
id|i
)braket
comma
id|pattern
(braket
id|i
)braket
comma
id|pattern
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|numoff
op_assign
id|plen
suffix:semicolon
op_star
id|numlen
op_assign
id|try_number
c_func
(paren
id|data
op_plus
id|plen
comma
id|dlen
op_minus
id|plen
comma
id|array
comma
id|term
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|numlen
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* FIXME: This should be in userspace.  Later. */
DECL|function|help
r_static
r_int
id|help
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|len
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
multiline_comment|/* tcplen not negative guarenteed by ip_conntrack_tcp.c */
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_const
r_char
op_star
id|data
op_assign
(paren
r_const
r_char
op_star
)paren
id|tcph
op_plus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|tcplen
op_assign
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|datalen
op_assign
id|tcplen
op_minus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
id|u_int32_t
id|old_seq_aft_nl
suffix:semicolon
r_int
id|old_seq_aft_nl_set
suffix:semicolon
id|u_int32_t
id|array
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_int
r_int
id|matchlen
comma
id|matchoff
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|t
suffix:semicolon
r_struct
id|ip_ct_ftp
op_star
id|info
op_assign
op_amp
id|ct-&gt;help.ct_ftp_info
suffix:semicolon
multiline_comment|/* Until there&squot;s been traffic both ways, don&squot;t look in packets. */
r_if
c_cond
(paren
id|ctinfo
op_ne
id|IP_CT_ESTABLISHED
op_logical_and
id|ctinfo
op_ne
id|IP_CT_ESTABLISHED
op_plus
id|IP_CT_IS_REPLY
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: Conntrackinfo = %u&bslash;n&quot;
comma
id|ctinfo
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Not whole TCP header? */
r_if
c_cond
(paren
id|tcplen
OL
r_sizeof
(paren
r_struct
id|tcphdr
)paren
op_logical_or
id|tcplen
OL
id|tcph-&gt;doff
op_star
l_int|4
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp: tcplen = %u&bslash;n&quot;
comma
(paren
r_int
)paren
id|tcplen
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Checksum invalid?  Ignore. */
multiline_comment|/* FIXME: Source route IP option packets --RR */
r_if
c_cond
(paren
id|tcp_v4_check
c_func
(paren
id|tcph
comma
id|tcplen
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
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
id|tcplen
comma
l_int|0
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ftp_help: bad csum: %p %u %u.%u.%u.%u %u.%u.%u.%u&bslash;n&quot;
comma
id|tcph
comma
id|tcplen
comma
id|IP_PARTS
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|IP_PARTS
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
id|old_seq_aft_nl_set
op_assign
id|info-&gt;seq_aft_nl_set
(braket
id|dir
)braket
suffix:semicolon
id|old_seq_aft_nl
op_assign
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: datalen %u&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|datalen
OG
l_int|0
)paren
op_logical_and
(paren
id|data
(braket
id|datalen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: datalen %u ends in &bslash;&bslash;n&bslash;n&quot;
comma
id|datalen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_seq_aft_nl_set
op_logical_or
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
comma
id|old_seq_aft_nl
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: updating nl to %u&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
)paren
suffix:semicolon
id|info-&gt;seq_aft_nl
(braket
id|dir
)braket
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|datalen
suffix:semicolon
id|info-&gt;seq_aft_nl_set
(braket
id|dir
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_seq_aft_nl_set
op_logical_or
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_ne
id|old_seq_aft_nl
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_ftp_help: wrong seq pos %s(%u)&bslash;n&quot;
comma
id|old_seq_aft_nl_set
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;(UNSET) &quot;
comma
id|old_seq_aft_nl
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|find_pattern
c_func
(paren
id|data
comma
id|datalen
comma
id|search
(braket
id|dir
)braket
dot
id|pattern
comma
id|search
(braket
id|dir
)braket
dot
id|plen
comma
id|search
(braket
id|dir
)braket
dot
id|term
comma
op_amp
id|matchoff
comma
op_amp
id|matchlen
comma
id|array
)paren
)paren
(brace
r_case
op_minus
l_int|1
suffix:colon
multiline_comment|/* partial */
multiline_comment|/* We don&squot;t usually drop packets.  After all, this is&n;&t;&t;   connection tracking, not packet filtering.&n;&t;&t;   However, it is neccessary for accurate tracking in&n;&t;&t;   this case. */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;conntrack_ftp: partial %u+%u&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|datalen
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* no match */
id|DEBUGP
c_func
(paren
l_string|&quot;ip_conntrack_ftp_help: no match&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: match `%.*s&squot; (%u bytes at %u)&bslash;n&quot;
comma
(paren
r_int
)paren
id|matchlen
comma
id|data
op_plus
id|matchoff
comma
id|matchlen
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|matchoff
)paren
suffix:semicolon
multiline_comment|/* Update the ftp info */
id|LOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|htonl
c_func
(paren
(paren
id|array
(braket
l_int|0
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|array
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|array
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|array
(braket
l_int|3
)braket
)paren
op_eq
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
(brace
id|info-&gt;is_ftp
op_assign
l_int|1
suffix:semicolon
id|info-&gt;seq
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|matchoff
suffix:semicolon
id|info-&gt;len
op_assign
id|matchlen
suffix:semicolon
id|info-&gt;ftptype
op_assign
id|dir
suffix:semicolon
id|info-&gt;port
op_assign
id|array
(braket
l_int|4
)braket
op_lshift
l_int|8
op_or
id|array
(braket
l_int|5
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Enrico Scholz&squot;s passive FTP to partially RNAT&squot;d ftp&n;&t;&t;   server: it really wants us to connect to a&n;&t;&t;   different IP address.  Simply don&squot;t record it for&n;&t;&t;   NAT. */
id|DEBUGP
c_func
(paren
l_string|&quot;conntrack_ftp: NOT RECORDING: %u,%u,%u,%u != %u.%u.%u.%u&bslash;n&quot;
comma
id|array
(braket
l_int|0
)braket
comma
id|array
(braket
l_int|1
)braket
comma
id|array
(braket
l_int|2
)braket
comma
id|array
(braket
l_int|3
)braket
comma
id|NIPQUAD
c_func
(paren
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
)paren
suffix:semicolon
)brace
id|t
op_assign
(paren
(paren
r_struct
id|ip_conntrack_tuple
)paren
(brace
(brace
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple.src.ip
comma
(brace
l_int|0
)brace
)brace
comma
(brace
id|htonl
c_func
(paren
(paren
id|array
(braket
l_int|0
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|array
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|array
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|array
(braket
l_int|3
)braket
)paren
comma
(brace
id|htons
c_func
(paren
id|array
(braket
l_int|4
)braket
op_lshift
l_int|8
op_or
id|array
(braket
l_int|5
)braket
)paren
)brace
comma
id|IPPROTO_TCP
)brace
)brace
)paren
suffix:semicolon
id|ip_conntrack_expect_related
c_func
(paren
id|ct
comma
op_amp
id|t
)paren
suffix:semicolon
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_ftp_lock
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Returns TRUE if it wants to help this connection (tuple is the&n;   tuple of REPLY packets from server). */
DECL|function|ftp_will_help
r_static
r_int
id|ftp_will_help
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|rtuple
)paren
(brace
r_return
(paren
id|rtuple-&gt;dst.protonum
op_eq
id|IPPROTO_TCP
op_logical_and
id|rtuple-&gt;src.u.tcp.port
op_eq
id|__constant_htons
c_func
(paren
l_int|21
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ftp
r_static
r_struct
id|ip_conntrack_helper
id|ftp
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
id|ftp_will_help
comma
id|help
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
r_return
id|ip_conntrack_helper_register
c_func
(paren
op_amp
id|ftp
)paren
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
id|ip_conntrack_helper_unregister
c_func
(paren
op_amp
id|ftp
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
