multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The options processing module for ip.c&n; *&n; * Version:&t;$Id: ip_options.c,v 1.12 1997/10/10 22:41:08 davem Exp $&n; *&n; * Authors:&t;A.N.Kuznetsov&n; *&t;&t;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
multiline_comment|/* &n; * Write options to IP header, record destination address to&n; * source route option, address of outgoing interface&n; * (we should already know it, so that this  function is allowed be&n; * called only after routing decision) and timestamp,&n; * if we originate this datagram.&n; *&n; * daddr is real destination address, next hop is recorded in IP header.&n; * saddr is address of outgoing interface.&n; */
DECL|function|ip_options_build
r_void
id|ip_options_build
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_options
op_star
id|opt
comma
id|u32
id|daddr
comma
r_struct
id|rtable
op_star
id|rt
comma
r_int
id|is_frag
)paren
(brace
r_int
r_char
op_star
id|iph
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
id|memcpy
c_func
(paren
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
comma
id|opt
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|iph
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
comma
id|opt-&gt;__data
comma
id|opt-&gt;optlen
)paren
suffix:semicolon
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
id|opt-&gt;is_data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;srr
)paren
id|memcpy
c_func
(paren
id|iph
op_plus
id|opt-&gt;srr
op_plus
id|iph
(braket
id|opt-&gt;srr
op_plus
l_int|1
)braket
op_minus
l_int|4
comma
op_amp
id|daddr
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_frag
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;rr_needaddr
)paren
id|ip_rt_get_source
c_func
(paren
id|iph
op_plus
id|opt-&gt;rr
op_plus
id|iph
(braket
id|opt-&gt;rr
op_plus
l_int|2
)braket
op_minus
l_int|5
comma
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;ts_needaddr
)paren
id|ip_rt_get_source
c_func
(paren
id|iph
op_plus
id|opt-&gt;ts
op_plus
id|iph
(braket
id|opt-&gt;ts
op_plus
l_int|2
)braket
op_minus
l_int|9
comma
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;ts_needtime
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|__u32
id|midtime
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|midtime
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
id|memcpy
c_func
(paren
id|iph
op_plus
id|opt-&gt;ts
op_plus
id|iph
(braket
id|opt-&gt;ts
op_plus
l_int|2
)braket
op_minus
l_int|5
comma
op_amp
id|midtime
comma
l_int|4
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;rr
)paren
(brace
id|memset
c_func
(paren
id|iph
op_plus
id|opt-&gt;rr
comma
id|IPOPT_NOP
comma
id|iph
(braket
id|opt-&gt;rr
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|opt-&gt;rr
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;rr_needaddr
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;ts
)paren
(brace
id|memset
c_func
(paren
id|iph
op_plus
id|opt-&gt;ts
comma
id|IPOPT_NOP
comma
id|iph
(braket
id|opt-&gt;ts
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|opt-&gt;ts
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;ts_needaddr
op_assign
id|opt-&gt;ts_needtime
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Provided (sopt, skb) points to received options,&n; * build in dopt compiled option set appropriate for answering.&n; * i.e. invert SRR option, copy anothers,&n; * and grab room in RR/TS options.&n; *&n; * NOTE: dopt cannot point to skb.&n; */
DECL|function|ip_options_echo
r_int
id|ip_options_echo
c_func
(paren
r_struct
id|ip_options
op_star
id|dopt
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ip_options
op_star
id|sopt
suffix:semicolon
r_int
r_char
op_star
id|sptr
comma
op_star
id|dptr
suffix:semicolon
r_int
id|soffset
comma
id|doffset
suffix:semicolon
r_int
id|optlen
suffix:semicolon
id|u32
id|daddr
suffix:semicolon
macro_line|#if 111
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;no skb in ip_options_echo&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
id|memset
c_func
(paren
id|dopt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
id|dopt-&gt;is_data
op_assign
l_int|1
suffix:semicolon
id|sopt
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
r_if
c_cond
(paren
id|sopt-&gt;optlen
op_eq
l_int|0
)paren
(brace
id|dopt-&gt;optlen
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sptr
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
id|dptr
op_assign
id|dopt-&gt;__data
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;dst
)paren
id|daddr
op_assign
(paren
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
)paren
op_member_access_from_pointer
id|rt_spec_dst
suffix:semicolon
r_else
id|daddr
op_assign
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|sopt-&gt;rr
)paren
(brace
id|optlen
op_assign
id|sptr
(braket
id|sopt-&gt;rr
op_plus
l_int|1
)braket
suffix:semicolon
id|soffset
op_assign
id|sptr
(braket
id|sopt-&gt;rr
op_plus
l_int|2
)braket
suffix:semicolon
id|dopt-&gt;rr
op_assign
id|dopt-&gt;optlen
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|sptr
op_plus
id|sopt-&gt;rr
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sopt-&gt;rr_needaddr
op_logical_and
id|soffset
op_le
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|soffset
op_plus
l_int|3
OG
id|optlen
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dptr
(braket
l_int|2
)braket
op_assign
id|soffset
op_plus
l_int|4
suffix:semicolon
id|dopt-&gt;rr_needaddr
op_assign
l_int|1
suffix:semicolon
)brace
id|dptr
op_add_assign
id|optlen
suffix:semicolon
id|dopt-&gt;optlen
op_add_assign
id|optlen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sopt-&gt;ts
)paren
(brace
id|optlen
op_assign
id|sptr
(braket
id|sopt-&gt;ts
op_plus
l_int|1
)braket
suffix:semicolon
id|soffset
op_assign
id|sptr
(braket
id|sopt-&gt;ts
op_plus
l_int|2
)braket
suffix:semicolon
id|dopt-&gt;ts
op_assign
id|dopt-&gt;optlen
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|sptr
op_plus
id|sopt-&gt;ts
comma
id|optlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|soffset
op_le
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|sopt-&gt;ts_needaddr
)paren
(brace
r_if
c_cond
(paren
id|soffset
op_plus
l_int|3
OG
id|optlen
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dopt-&gt;ts_needaddr
op_assign
l_int|1
suffix:semicolon
id|soffset
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sopt-&gt;ts_needtime
)paren
(brace
r_if
c_cond
(paren
id|soffset
op_plus
l_int|3
OG
id|optlen
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dopt-&gt;ts_needtime
op_assign
l_int|1
suffix:semicolon
id|soffset
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|timestamp
op_star
)paren
(paren
id|dptr
op_plus
l_int|1
)paren
)paren
op_member_access_from_pointer
id|flags
op_eq
id|IPOPT_TS_PRESPEC
)paren
(brace
id|__u32
id|addr
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|addr
comma
id|sptr
op_plus
id|soffset
op_minus
l_int|9
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_addr_type
c_func
(paren
id|addr
)paren
op_eq
id|RTN_UNICAST
)paren
(brace
id|dopt-&gt;ts_needtime
op_assign
l_int|0
suffix:semicolon
id|dopt-&gt;ts_needaddr
op_assign
l_int|0
suffix:semicolon
id|soffset
op_sub_assign
l_int|8
suffix:semicolon
)brace
)brace
id|dptr
(braket
l_int|2
)braket
op_assign
id|soffset
suffix:semicolon
)brace
id|dptr
op_add_assign
id|optlen
suffix:semicolon
id|dopt-&gt;optlen
op_add_assign
id|optlen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sopt-&gt;srr
)paren
(brace
r_int
r_char
op_star
id|start
op_assign
id|sptr
op_plus
id|sopt-&gt;srr
suffix:semicolon
id|u32
id|faddr
suffix:semicolon
id|optlen
op_assign
id|start
(braket
l_int|1
)braket
suffix:semicolon
id|soffset
op_assign
id|start
(braket
l_int|2
)braket
suffix:semicolon
id|doffset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|soffset
OG
id|optlen
)paren
id|soffset
op_assign
id|optlen
op_plus
l_int|1
suffix:semicolon
id|soffset
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|soffset
OG
l_int|3
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|faddr
comma
op_amp
id|start
(braket
id|soffset
op_minus
l_int|1
)braket
comma
l_int|4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|soffset
op_sub_assign
l_int|4
comma
id|doffset
op_assign
l_int|4
suffix:semicolon
id|soffset
OG
l_int|3
suffix:semicolon
id|soffset
op_sub_assign
l_int|4
comma
id|doffset
op_add_assign
l_int|4
)paren
id|memcpy
c_func
(paren
op_amp
id|dptr
(braket
id|doffset
op_minus
l_int|1
)braket
comma
op_amp
id|start
(braket
id|soffset
op_minus
l_int|1
)braket
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * RFC1812 requires to fix illegal source routes.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|skb-&gt;nh.iph-&gt;saddr
comma
op_amp
id|start
(braket
id|soffset
op_plus
l_int|3
)braket
comma
l_int|4
)paren
op_eq
l_int|0
)paren
id|doffset
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|doffset
OG
l_int|3
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|start
(braket
id|doffset
op_minus
l_int|1
)braket
comma
op_amp
id|daddr
comma
l_int|4
)paren
suffix:semicolon
id|dopt-&gt;faddr
op_assign
id|faddr
suffix:semicolon
id|dptr
(braket
l_int|0
)braket
op_assign
id|start
(braket
l_int|0
)braket
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_assign
id|doffset
op_plus
l_int|3
suffix:semicolon
id|dptr
(braket
l_int|2
)braket
op_assign
l_int|4
suffix:semicolon
id|dptr
op_add_assign
id|doffset
op_plus
l_int|3
suffix:semicolon
id|dopt-&gt;srr
op_assign
id|dopt-&gt;optlen
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|dopt-&gt;optlen
op_add_assign
id|doffset
op_plus
l_int|3
suffix:semicolon
id|dopt-&gt;is_strictroute
op_assign
id|sopt-&gt;is_strictroute
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|dopt-&gt;optlen
op_amp
l_int|3
)paren
(brace
op_star
id|dptr
op_increment
op_assign
id|IPOPT_END
suffix:semicolon
id|dopt-&gt;optlen
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Options &quot;fragmenting&quot;, just fill options not&n; *&t;allowed in fragments with NOOPs.&n; *&t;Simple and stupid 8), but the most efficient way.&n; */
DECL|function|ip_options_fragment
r_void
id|ip_options_fragment
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
op_star
id|optptr
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
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
r_int
id|l
op_assign
id|opt-&gt;optlen
suffix:semicolon
r_int
id|optlen
suffix:semicolon
r_while
c_loop
(paren
id|l
OG
l_int|0
)paren
(brace
r_switch
c_cond
(paren
op_star
id|optptr
)paren
(brace
r_case
id|IPOPT_END
suffix:colon
r_return
suffix:semicolon
r_case
id|IPOPT_NOOP
suffix:colon
id|l
op_decrement
suffix:semicolon
id|optptr
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|optlen
op_assign
id|optptr
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|optlen
id|l
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IPOPT_COPIED
c_func
(paren
op_star
id|optptr
)paren
)paren
id|memset
c_func
(paren
id|optptr
comma
id|IPOPT_NOOP
comma
id|optlen
)paren
suffix:semicolon
id|l
op_sub_assign
id|optlen
suffix:semicolon
id|optptr
op_add_assign
id|optlen
suffix:semicolon
)brace
id|opt-&gt;ts
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;rr
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;rr_needaddr
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;ts_needaddr
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;ts_needtime
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Verify options and fill pointers in struct options.&n; * Caller should clear *opt, and set opt-&gt;data.&n; * If opt == NULL, then skb-&gt;data should point to IP header.&n; */
DECL|function|ip_options_compile
r_int
id|ip_options_compile
c_func
(paren
r_struct
id|ip_options
op_star
id|opt
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|l
suffix:semicolon
r_int
r_char
op_star
id|iph
suffix:semicolon
r_int
r_char
op_star
id|optptr
suffix:semicolon
r_int
id|optlen
suffix:semicolon
r_int
r_char
op_star
id|pp_ptr
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
id|skb
ques
c_cond
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
)paren
(brace
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
id|memset
c_func
(paren
id|opt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
id|opt-&gt;optlen
op_assign
(paren
(paren
r_struct
id|iphdr
op_star
)paren
id|iph
)paren
op_member_access_from_pointer
id|ihl
op_star
l_int|4
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|optptr
op_assign
id|iph
op_plus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|opt-&gt;is_data
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|optptr
op_assign
id|opt-&gt;is_data
ques
c_cond
id|opt-&gt;__data
suffix:colon
(paren
r_int
r_char
op_star
)paren
op_amp
(paren
id|skb-&gt;nh.iph
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|iph
op_assign
id|optptr
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|l
op_assign
id|opt-&gt;optlen
suffix:semicolon
id|l
OG
l_int|0
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
op_star
id|optptr
)paren
(brace
r_case
id|IPOPT_END
suffix:colon
r_for
c_loop
(paren
id|optptr
op_increment
comma
id|l
op_decrement
suffix:semicolon
id|l
OG
l_int|0
suffix:semicolon
id|l
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|optptr
op_ne
id|IPOPT_END
)paren
(brace
op_star
id|optptr
op_assign
id|IPOPT_END
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_goto
id|eol
suffix:semicolon
r_case
id|IPOPT_NOOP
suffix:colon
id|l
op_decrement
suffix:semicolon
id|optptr
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|optlen
op_assign
id|optptr
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|optlen
id|l
)paren
(brace
id|pp_ptr
op_assign
id|optptr
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_switch
c_cond
(paren
op_star
id|optptr
)paren
(brace
r_case
id|IPOPT_SSRR
suffix:colon
r_case
id|IPOPT_LSRR
suffix:colon
r_if
c_cond
(paren
id|optlen
OL
l_int|3
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|1
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
OL
l_int|4
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* NB: cf RFC-1812 5.2.4.1 */
r_if
c_cond
(paren
id|opt-&gt;srr
)paren
(brace
id|pp_ptr
op_assign
id|optptr
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
op_ne
l_int|4
op_logical_or
id|optlen
OL
l_int|7
op_logical_or
(paren
(paren
id|optlen
op_minus
l_int|3
)paren
op_amp
l_int|3
)paren
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|1
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|opt-&gt;faddr
comma
op_amp
id|optptr
(braket
l_int|3
)braket
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optlen
OG
l_int|7
)paren
id|memmove
c_func
(paren
op_amp
id|optptr
(braket
l_int|3
)braket
comma
op_amp
id|optptr
(braket
l_int|7
)braket
comma
id|optlen
op_minus
l_int|7
)paren
suffix:semicolon
)brace
id|opt-&gt;is_strictroute
op_assign
(paren
id|optptr
(braket
l_int|0
)braket
op_eq
id|IPOPT_SSRR
)paren
suffix:semicolon
id|opt-&gt;srr
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPOPT_RR
suffix:colon
r_if
c_cond
(paren
id|opt-&gt;rr
)paren
(brace
id|pp_ptr
op_assign
id|optptr
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optlen
OL
l_int|3
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|1
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
OL
l_int|4
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
op_le
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
op_plus
l_int|3
OG
id|optlen
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
)paren
(brace
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
l_int|1
)braket
comma
op_amp
id|rt-&gt;rt_spec_dst
comma
l_int|4
)paren
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
id|optptr
(braket
l_int|2
)braket
op_add_assign
l_int|4
suffix:semicolon
id|opt-&gt;rr_needaddr
op_assign
l_int|1
suffix:semicolon
)brace
id|opt-&gt;rr
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPOPT_TIMESTAMP
suffix:colon
r_if
c_cond
(paren
id|opt-&gt;ts
)paren
(brace
id|pp_ptr
op_assign
id|optptr
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optlen
OL
l_int|4
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|1
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
OL
l_int|5
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
op_le
id|optlen
)paren
(brace
r_struct
id|timestamp
op_star
id|ts
op_assign
(paren
r_struct
id|timestamp
op_star
)paren
(paren
id|optptr
op_plus
l_int|1
)paren
suffix:semicolon
id|__u32
op_star
id|timeptr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ts-&gt;ptr
op_plus
l_int|3
OG
id|ts-&gt;len
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ts-&gt;flags
)paren
(brace
r_case
id|IPOPT_TS_TSONLY
suffix:colon
id|opt-&gt;ts
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|timeptr
op_assign
(paren
id|__u32
op_star
)paren
op_amp
id|optptr
(braket
id|ts-&gt;ptr
op_minus
l_int|1
)braket
suffix:semicolon
id|opt-&gt;ts_needtime
op_assign
l_int|1
suffix:semicolon
id|ts-&gt;ptr
op_add_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPOPT_TS_TSANDADDR
suffix:colon
r_if
c_cond
(paren
id|ts-&gt;ptr
op_plus
l_int|7
OG
id|ts-&gt;len
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|opt-&gt;ts
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|optptr
(braket
id|ts-&gt;ptr
op_minus
l_int|1
)braket
comma
op_amp
id|rt-&gt;rt_spec_dst
comma
l_int|4
)paren
suffix:semicolon
id|timeptr
op_assign
(paren
id|__u32
op_star
)paren
op_amp
id|optptr
(braket
id|ts-&gt;ptr
op_plus
l_int|3
)braket
suffix:semicolon
)brace
id|opt-&gt;ts_needaddr
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;ts_needtime
op_assign
l_int|1
suffix:semicolon
id|ts-&gt;ptr
op_add_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPOPT_TS_PRESPEC
suffix:colon
r_if
c_cond
(paren
id|ts-&gt;ptr
op_plus
l_int|7
OG
id|ts-&gt;len
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|2
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|opt-&gt;ts
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
(brace
id|u32
id|addr
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|addr
comma
op_amp
id|optptr
(braket
id|ts-&gt;ptr
op_minus
l_int|1
)braket
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_addr_type
c_func
(paren
id|addr
)paren
op_eq
id|RTN_UNICAST
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|timeptr
op_assign
(paren
id|__u32
op_star
)paren
op_amp
id|optptr
(braket
id|ts-&gt;ptr
op_plus
l_int|3
)braket
suffix:semicolon
)brace
id|opt-&gt;ts_needaddr
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;ts_needtime
op_assign
l_int|1
suffix:semicolon
id|ts-&gt;ptr
op_add_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|3
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timeptr
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|__u32
id|midtime
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|midtime
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
id|memcpy
c_func
(paren
id|timeptr
comma
op_amp
id|midtime
comma
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|timestamp
op_star
id|ts
op_assign
(paren
r_struct
id|timestamp
op_star
)paren
(paren
id|optptr
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ts-&gt;overflow
op_eq
l_int|15
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|3
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|opt-&gt;ts
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|ts-&gt;overflow
op_increment
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|IPOPT_RA
suffix:colon
r_if
c_cond
(paren
id|optlen
OL
l_int|4
)paren
(brace
id|pp_ptr
op_assign
id|optptr
op_plus
l_int|1
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|optptr
(braket
l_int|2
)braket
op_eq
l_int|0
op_logical_and
id|optptr
(braket
l_int|3
)braket
op_eq
l_int|0
)paren
id|opt-&gt;router_alert
op_assign
id|optptr
op_minus
id|iph
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPOPT_SEC
suffix:colon
r_case
id|IPOPT_SID
suffix:colon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|pp_ptr
op_assign
id|optptr
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|l
op_sub_assign
id|optlen
suffix:semicolon
id|optptr
op_add_assign
id|optlen
suffix:semicolon
)brace
id|eol
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|pp_ptr
)paren
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_PARAMETERPROB
comma
l_int|0
comma
id|pp_ptr
op_minus
id|iph
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Undo all the changes done by ip_options_compile().&n; */
DECL|function|ip_options_undo
r_void
id|ip_options_undo
c_func
(paren
r_struct
id|ip_options
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;srr
)paren
(brace
r_int
r_char
op_star
id|optptr
op_assign
id|opt-&gt;__data
op_plus
id|opt-&gt;srr
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|optptr
op_plus
l_int|7
comma
id|optptr
op_plus
l_int|3
comma
id|optptr
(braket
l_int|1
)braket
op_minus
l_int|7
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|optptr
op_plus
l_int|3
comma
op_amp
id|opt-&gt;faddr
comma
l_int|4
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;rr_needaddr
)paren
(brace
r_int
r_char
op_star
id|optptr
op_assign
id|opt-&gt;__data
op_plus
id|opt-&gt;rr
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
id|memset
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
l_int|1
)braket
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
id|optptr
(braket
l_int|2
)braket
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;ts
)paren
(brace
r_int
r_char
op_star
id|optptr
op_assign
id|opt-&gt;__data
op_plus
id|opt-&gt;ts
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;ts_needtime
)paren
(brace
id|memset
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
l_int|1
)braket
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
id|optptr
(braket
l_int|2
)braket
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;ts_needaddr
)paren
(brace
id|memset
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
l_int|1
)braket
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
id|optptr
(braket
l_int|2
)braket
op_sub_assign
l_int|4
suffix:semicolon
)brace
)brace
)brace
DECL|function|ip_options_get
r_int
id|ip_options_get
c_func
(paren
r_struct
id|ip_options
op_star
op_star
id|optp
comma
r_int
r_char
op_star
id|data
comma
r_int
id|optlen
comma
r_int
id|user
)paren
(brace
r_struct
id|ip_options
op_star
id|opt
suffix:semicolon
id|opt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
(paren
(paren
id|optlen
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|opt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|optlen
)paren
(brace
r_if
c_cond
(paren
id|user
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|opt-&gt;__data
comma
id|data
comma
id|optlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|opt-&gt;__data
comma
id|data
comma
id|optlen
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|optlen
op_amp
l_int|3
)paren
id|opt-&gt;__data
(braket
id|optlen
op_increment
)braket
op_assign
id|IPOPT_END
suffix:semicolon
id|opt-&gt;optlen
op_assign
id|optlen
suffix:semicolon
id|opt-&gt;is_data
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;is_setbyuser
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|optlen
op_logical_and
id|ip_options_compile
c_func
(paren
id|opt
comma
l_int|NULL
)paren
)paren
(brace
id|kfree_s
c_func
(paren
id|opt
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
op_plus
id|optlen
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|optp
op_assign
id|opt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_forward_options
r_void
id|ip_forward_options
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
r_int
r_char
op_star
id|optptr
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
r_int
r_char
op_star
id|raw
op_assign
id|skb-&gt;nh.raw
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
id|raw
op_plus
id|opt-&gt;rr
suffix:semicolon
id|ip_rt_get_source
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
id|rt
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
id|raw
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
id|rt-&gt;rt_dst
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
id|ip_rt_get_source
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
id|rt
)paren
suffix:semicolon
id|skb-&gt;nh.iph-&gt;daddr
op_assign
id|rt-&gt;rt_dst
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
id|KERN_CRIT
l_string|&quot;ip_forward(): Argh! Destination lost!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;ts_needaddr
)paren
(brace
id|optptr
op_assign
id|raw
op_plus
id|opt-&gt;ts
suffix:semicolon
id|ip_rt_get_source
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
id|rt
)paren
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
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
id|skb-&gt;nh.iph
)paren
suffix:semicolon
)brace
)brace
DECL|function|ip_options_rcv_srr
r_int
id|ip_options_rcv_srr
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
r_int
id|srrspace
comma
id|srrptr
suffix:semicolon
id|u32
id|nexthop
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_int
r_char
op_star
id|optptr
op_assign
id|skb-&gt;nh.raw
op_plus
id|opt-&gt;srr
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
r_struct
id|rtable
op_star
id|rt2
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;srr
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_type
op_eq
id|RTN_UNICAST
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;is_strictroute
)paren
r_return
l_int|0
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_PARAMETERPROB
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rt-&gt;rt_type
op_ne
id|RTN_LOCAL
)paren
r_return
op_minus
id|EINVAL
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
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_PARAMETERPROB
comma
l_int|0
comma
id|opt-&gt;srr
op_plus
l_int|2
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|nexthop
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
id|skb-&gt;dst
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
id|ip_route_input
c_func
(paren
id|skb
comma
id|nexthop
comma
id|iph-&gt;saddr
comma
id|iph-&gt;tos
comma
id|skb-&gt;dev
)paren
suffix:semicolon
id|rt2
op_assign
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
(paren
id|rt2-&gt;rt_type
op_ne
id|RTN_UNICAST
op_logical_and
id|rt2-&gt;rt_type
op_ne
id|RTN_LOCAL
)paren
)paren
(brace
id|ip_rt_put
c_func
(paren
id|rt2
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt2-&gt;rt_type
op_ne
id|RTN_LOCAL
)paren
r_break
suffix:semicolon
multiline_comment|/* Superfast 8) loopback forward */
id|memcpy
c_func
(paren
op_amp
id|iph-&gt;daddr
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
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srrptr
op_le
id|srrspace
)paren
(brace
id|opt-&gt;srr_is_hit
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;is_changed
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
