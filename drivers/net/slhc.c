multiline_comment|/*&n; * Routines to compress and uncompress tcp packets (for transmission&n; * over low speed serial lines).&n; *&n; * Copyright (c) 1989 Regents of the University of California.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by the University of California, Berkeley.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; *&t;Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:&n; *&t;- Initial distribution.&n; *&n; *&n; * modified for KA9Q Internet Software Package by&n; * Katie Stevens (dkstevens@ucdavis.edu)&n; * University of California, Davis&n; * Computing Services&n; *&t;- 01-31-90&t;initial adaptation (from 1.19)&n; *&t;PPP.05&t;02-15-90 [ks]&n; *&t;PPP.08&t;05-02-90 [ks]&t;use PPP protocol field to signal compression&n; *&t;PPP.15&t;09-90&t; [ks]&t;improve mbuf handling&n; *&t;PPP.16&t;11-02&t; [karn]&t;substantially rewritten to use NOS facilities&n; *&n; *&t;- Feb 1991&t;Bill_Simpson@um.cc.umich.edu&n; *&t;&t;&t;variable number of conversation slots&n; *&t;&t;&t;allow zero or one slots&n; *&t;&t;&t;separate routines&n; *&t;&t;&t;status display&n; *&n; *&n; *&t;This module is a difficult issue. Its clearly inet code but its also clearly&n; *&t;driver code belonging close to PPP and SLIP&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_INET
multiline_comment|/* Entire module is for IP only */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;icmp.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;slhc.h&quot;
DECL|macro|DPRINT
mdefine_line|#define DPRINT(x)
DECL|variable|last_retran
r_int
id|last_retran
suffix:semicolon
r_static
r_int
r_char
op_star
id|encode
c_func
(paren
r_int
r_char
op_star
id|cp
comma
r_int
id|n
)paren
suffix:semicolon
r_static
r_int
id|decode
c_func
(paren
r_int
r_char
op_star
op_star
id|cpp
)paren
suffix:semicolon
r_static
r_int
r_char
op_star
id|put16
c_func
(paren
r_int
r_char
op_star
id|cp
comma
r_int
r_int
id|x
)paren
suffix:semicolon
r_static
r_int
r_int
id|pull16
c_func
(paren
r_int
r_char
op_star
op_star
id|cpp
)paren
suffix:semicolon
r_extern
r_int
id|ip_csum
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
suffix:semicolon
multiline_comment|/* Initialize compression data structure&n; *&t;slots must be in range 0 to 255 (zero meaning no compression)&n; */
r_struct
id|slcompress
op_star
DECL|function|slhc_init
id|slhc_init
c_func
(paren
r_int
id|rslots
comma
r_int
id|tslots
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
r_struct
id|cstate
op_star
id|ts
suffix:semicolon
r_struct
id|slcompress
op_star
id|comp
suffix:semicolon
id|comp
op_assign
(paren
r_struct
id|slcompress
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|slcompress
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|comp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|slcompress
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rslots
OG
l_int|0
op_logical_and
id|rslots
OL
l_int|256
)paren
(brace
id|comp-&gt;rstate
op_assign
(paren
r_struct
id|cstate
op_star
)paren
id|kmalloc
c_func
(paren
id|rslots
op_star
r_sizeof
(paren
r_struct
id|cstate
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp-&gt;rstate
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|comp-&gt;rstate
comma
l_int|0
comma
id|rslots
op_star
r_sizeof
(paren
r_struct
id|cstate
)paren
)paren
suffix:semicolon
id|comp-&gt;rslot_limit
op_assign
id|rslots
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tslots
OG
l_int|0
op_logical_and
id|tslots
OL
l_int|256
)paren
(brace
id|comp-&gt;tstate
op_assign
(paren
r_struct
id|cstate
op_star
)paren
id|kmalloc
c_func
(paren
id|tslots
op_star
r_sizeof
(paren
r_struct
id|cstate
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp-&gt;tstate
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|comp-&gt;tstate
comma
l_int|0
comma
id|rslots
op_star
r_sizeof
(paren
r_struct
id|cstate
)paren
)paren
suffix:semicolon
id|comp-&gt;tslot_limit
op_assign
id|tslots
op_minus
l_int|1
suffix:semicolon
)brace
id|comp-&gt;xmit_oldest
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;xmit_current
op_assign
l_int|255
suffix:semicolon
id|comp-&gt;recv_current
op_assign
l_int|255
suffix:semicolon
multiline_comment|/*&n;&t; * don&squot;t accept any packets with implicit index until we get&n;&t; * one with an explicit index.  Otherwise the uncompress code&n;&t; * will try to use connection 255, which is almost certainly&n;&t; * out of range&n;&t; */
id|comp-&gt;flags
op_or_assign
id|SLF_TOSS
suffix:semicolon
r_if
c_cond
(paren
id|tslots
OG
l_int|0
)paren
(brace
id|ts
op_assign
id|comp-&gt;tstate
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|comp-&gt;tslot_limit
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|ts
(braket
id|i
)braket
dot
id|cs_this
op_assign
id|i
suffix:semicolon
id|ts
(braket
id|i
)braket
dot
id|next
op_assign
op_amp
(paren
id|ts
(braket
id|i
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|ts
(braket
l_int|0
)braket
dot
id|next
op_assign
op_amp
(paren
id|ts
(braket
id|comp-&gt;tslot_limit
)braket
)paren
suffix:semicolon
id|ts
(braket
l_int|0
)braket
dot
id|cs_this
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|comp
suffix:semicolon
)brace
multiline_comment|/* Free a compression data structure */
r_void
DECL|function|slhc_free
id|slhc_free
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
(brace
r_if
c_cond
(paren
id|comp
op_eq
id|NULLSLCOMPR
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|comp-&gt;rstate
op_ne
id|NULLSLSTATE
)paren
id|kfree
c_func
(paren
id|comp-&gt;rstate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comp-&gt;tstate
op_ne
id|NULLSLSTATE
)paren
id|kfree
c_func
(paren
id|comp-&gt;tstate
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
multiline_comment|/* Put a short in host order into a char array in network order */
r_static
r_int
r_char
op_star
DECL|function|put16
id|put16
c_func
(paren
r_int
r_char
op_star
id|cp
comma
r_int
r_int
id|x
)paren
(brace
op_star
id|cp
op_increment
op_assign
id|x
op_rshift
l_int|8
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|x
suffix:semicolon
r_return
id|cp
suffix:semicolon
)brace
multiline_comment|/* Encode a number */
r_int
r_char
op_star
DECL|function|encode
id|encode
c_func
(paren
r_int
r_char
op_star
id|cp
comma
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|n
op_ge
l_int|256
op_logical_or
id|n
op_eq
l_int|0
)paren
(brace
op_star
id|cp
op_increment
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|put16
c_func
(paren
id|cp
comma
id|n
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|cp
op_increment
op_assign
id|n
suffix:semicolon
)brace
r_return
id|cp
suffix:semicolon
)brace
multiline_comment|/* Pull a 16-bit integer in host order from buffer in network byte order */
r_static
r_int
r_int
DECL|function|pull16
id|pull16
c_func
(paren
r_int
r_char
op_star
op_star
id|cpp
)paren
(brace
r_int
id|rval
suffix:semicolon
id|rval
op_assign
op_star
(paren
op_star
id|cpp
)paren
op_increment
suffix:semicolon
id|rval
op_lshift_assign
l_int|8
suffix:semicolon
id|rval
op_or_assign
op_star
(paren
op_star
id|cpp
)paren
op_increment
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
multiline_comment|/* Decode a number */
r_int
DECL|function|decode
id|decode
c_func
(paren
r_int
r_char
op_star
op_star
id|cpp
)paren
(brace
r_register
r_int
id|x
suffix:semicolon
id|x
op_assign
op_star
(paren
op_star
id|cpp
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
(brace
r_return
id|pull16
c_func
(paren
id|cpp
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* pull16 returns -1 on error */
)brace
r_else
(brace
r_return
id|x
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* -1 if PULLCHAR returned error */
)brace
)brace
multiline_comment|/* &n; * icp and isize are the original packet.&n; * ocp is a place to put a copy if necessary.&n; * cpp is initially a pointer to icp.  If the copy is used,&n; *    change it to ocp.&n; */
r_int
DECL|function|slhc_compress
id|slhc_compress
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
comma
r_int
r_char
op_star
id|ocp
comma
r_int
r_char
op_star
op_star
id|cpp
comma
r_int
id|compress_cid
)paren
(brace
r_register
r_struct
id|cstate
op_star
id|ocs
op_assign
op_amp
(paren
id|comp-&gt;tstate
(braket
id|comp-&gt;xmit_oldest
)braket
)paren
suffix:semicolon
r_register
r_struct
id|cstate
op_star
id|lcs
op_assign
id|ocs
suffix:semicolon
r_register
r_struct
id|cstate
op_star
id|cs
op_assign
id|lcs-&gt;next
suffix:semicolon
r_register
r_int
r_int
id|deltaS
comma
id|deltaA
suffix:semicolon
r_register
r_int
id|changes
op_assign
l_int|0
suffix:semicolon
r_int
id|hlen
suffix:semicolon
r_int
r_char
id|new_seq
(braket
l_int|16
)braket
suffix:semicolon
r_register
r_int
r_char
op_star
id|cp
op_assign
id|new_seq
suffix:semicolon
r_struct
id|iphdr
op_star
id|ip
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
comma
op_star
id|oth
suffix:semicolon
id|ip
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|icp
suffix:semicolon
multiline_comment|/* Bail if this packet isn&squot;t TCP, or is an IP fragment */
r_if
c_cond
(paren
id|ip-&gt;protocol
op_ne
id|IPPROTO_TCP
op_logical_or
(paren
id|ntohs
c_func
(paren
id|ip-&gt;frag_off
)paren
op_amp
l_int|0x1fff
)paren
op_logical_or
(paren
id|ip-&gt;frag_off
op_amp
l_int|32
)paren
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: noncomp 1 %d %d %d&bslash;n&quot;
comma
id|ip-&gt;protocol
comma
id|ntohs
c_func
(paren
id|ip-&gt;frag_off
)paren
comma
id|ip-&gt;frag_off
)paren
)paren
suffix:semicolon
multiline_comment|/* Send as regular IP */
r_if
c_cond
(paren
id|ip-&gt;protocol
op_ne
id|IPPROTO_TCP
)paren
(brace
id|comp-&gt;sls_o_nontcp
op_increment
suffix:semicolon
)brace
r_else
id|comp-&gt;sls_o_tcp
op_increment
suffix:semicolon
r_return
id|isize
suffix:semicolon
)brace
multiline_comment|/* Extract TCP header */
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|ip
)paren
op_plus
id|ip-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|hlen
op_assign
id|ip-&gt;ihl
op_star
l_int|4
op_plus
id|th-&gt;doff
op_star
l_int|4
suffix:semicolon
multiline_comment|/*  Bail if the TCP packet isn&squot;t `compressible&squot; (i.e., ACK isn&squot;t set or&n;&t; *  some other control bit is set).&n;&t; */
r_if
c_cond
(paren
id|th-&gt;syn
op_logical_or
id|th-&gt;fin
op_logical_or
id|th-&gt;rst
op_logical_or
op_logical_neg
(paren
id|th-&gt;ack
)paren
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: noncomp 2 %x %x %d %d %d %d&bslash;n&quot;
comma
id|ip
comma
id|th
comma
id|th-&gt;syn
comma
id|th-&gt;fin
comma
id|th-&gt;rst
comma
id|th-&gt;ack
)paren
)paren
suffix:semicolon
multiline_comment|/* TCP connection stuff; send as regular IP */
id|comp-&gt;sls_o_tcp
op_increment
suffix:semicolon
r_return
id|isize
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Packet is compressible -- we&squot;re going to send either a&n;&t; * COMPRESSED_TCP or UNCOMPRESSED_TCP packet.  Either way,&n;&t; * we need to locate (or create) the connection state.&n;&t; *&n;&t; * States are kept in a circularly linked list with&n;&t; * xmit_oldest pointing to the end of the list.  The&n;&t; * list is kept in lru order by moving a state to the&n;&t; * head of the list whenever it is referenced.  Since&n;&t; * the list is short and, empirically, the connection&n;&t; * we want is almost always near the front, we locate&n;&t; * states via linear search.  If we don&squot;t find a state&n;&t; * for the datagram, the oldest state is (re-)used.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|ip-&gt;saddr
op_eq
id|cs-&gt;cs_ip.saddr
op_logical_and
id|ip-&gt;daddr
op_eq
id|cs-&gt;cs_ip.daddr
op_logical_and
id|th-&gt;source
op_eq
id|cs-&gt;cs_tcp.source
op_logical_and
id|th-&gt;dest
op_eq
id|cs-&gt;cs_tcp.dest
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
multiline_comment|/* if current equal oldest, at end of list */
r_if
c_cond
(paren
id|cs
op_eq
id|ocs
)paren
r_break
suffix:semicolon
id|lcs
op_assign
id|cs
suffix:semicolon
id|cs
op_assign
id|cs-&gt;next
suffix:semicolon
id|comp-&gt;sls_o_searches
op_increment
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;&t; * Didn&squot;t find it -- re-use oldest cstate.  Send an&n;&t; * uncompressed packet that tells the other side what&n;&t; * connection number we&squot;re using for this conversation.&n;&t; *&n;&t; * Note that since the state list is circular, the oldest&n;&t; * state points to the newest and we only need to set&n;&t; * xmit_oldest to update the lru linkage.&n;&t; */
id|comp-&gt;sls_o_misses
op_increment
suffix:semicolon
id|comp-&gt;xmit_oldest
op_assign
id|lcs-&gt;cs_this
suffix:semicolon
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: not found&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|uncompressed
suffix:semicolon
id|found
suffix:colon
multiline_comment|/*&n;&t; * Found it -- move to the front on the connection list.&n;&t; */
r_if
c_cond
(paren
id|lcs
op_eq
id|ocs
)paren
(brace
multiline_comment|/* found at most recently used */
)brace
r_else
r_if
c_cond
(paren
id|cs
op_eq
id|ocs
)paren
(brace
multiline_comment|/* found at least recently used */
id|comp-&gt;xmit_oldest
op_assign
id|lcs-&gt;cs_this
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* more than 2 elements */
id|lcs-&gt;next
op_assign
id|cs-&gt;next
suffix:semicolon
id|cs-&gt;next
op_assign
id|ocs-&gt;next
suffix:semicolon
id|ocs-&gt;next
op_assign
id|cs
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure that only what we expect to change changed.&n;&t; * Check the following:&n;&t; * IP protocol version, header length &amp; type of service.&n;&t; * The &quot;Don&squot;t fragment&quot; bit.&n;&t; * The time-to-live field.&n;&t; * The TCP header length.&n;&t; * IP options, if any.&n;&t; * TCP options, if any.&n;&t; * If any of these things are different between the previous &amp;&n;&t; * current datagram, we send the current datagram `uncompressed&squot;.&n;&t; */
id|oth
op_assign
op_amp
id|cs-&gt;cs_tcp
suffix:semicolon
r_if
c_cond
(paren
id|last_retran
op_logical_or
id|ip-&gt;version
op_ne
id|cs-&gt;cs_ip.version
op_logical_or
id|ip-&gt;ihl
op_ne
id|cs-&gt;cs_ip.ihl
op_logical_or
id|ip-&gt;tos
op_ne
id|cs-&gt;cs_ip.tos
op_logical_or
(paren
id|ip-&gt;frag_off
op_amp
l_int|64
)paren
op_ne
(paren
id|cs-&gt;cs_ip.frag_off
op_amp
l_int|64
)paren
op_logical_or
id|ip-&gt;ttl
op_ne
id|cs-&gt;cs_ip.ttl
op_logical_or
id|th-&gt;doff
op_ne
id|cs-&gt;cs_tcp.doff
op_logical_or
(paren
id|ip-&gt;ihl
OG
l_int|5
op_logical_and
id|memcmp
c_func
(paren
id|ip
op_plus
l_int|1
comma
id|cs-&gt;cs_ipopt
comma
(paren
(paren
id|ip-&gt;ihl
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
op_ne
l_int|0
)paren
op_logical_or
(paren
id|th-&gt;doff
OG
l_int|5
op_logical_and
id|memcmp
c_func
(paren
id|th
op_plus
l_int|1
comma
id|cs-&gt;cs_tcpopt
comma
(paren
(paren
id|th-&gt;doff
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
op_ne
l_int|0
)paren
)paren
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: incompat&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|uncompressed
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Figure out which of the changing fields changed.  The&n;&t; * receiver expects changes in the order: urgent, window,&n;&t; * ack, seq (the order minimizes the number of temporaries&n;&t; * needed in this section of code).&n;&t; */
r_if
c_cond
(paren
id|th-&gt;urg
)paren
(brace
id|deltaS
op_assign
id|ntohs
c_func
(paren
id|th-&gt;urg_ptr
)paren
suffix:semicolon
id|cp
op_assign
id|encode
c_func
(paren
id|cp
comma
id|deltaS
)paren
suffix:semicolon
id|changes
op_or_assign
id|NEW_U
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|th-&gt;urg_ptr
op_ne
id|oth-&gt;urg_ptr
)paren
(brace
multiline_comment|/* argh! URG not set but urp changed -- a sensible&n;&t;&t; * implementation should never do this but RFC793&n;&t;&t; * doesn&squot;t prohibit the change so we have to deal&n;&t;&t; * with it. */
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: urg incompat&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|uncompressed
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|deltaS
op_assign
id|ntohs
c_func
(paren
id|th-&gt;window
)paren
op_minus
id|ntohs
c_func
(paren
id|oth-&gt;window
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|cp
op_assign
id|encode
c_func
(paren
id|cp
comma
id|deltaS
)paren
suffix:semicolon
id|changes
op_or_assign
id|NEW_W
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|deltaA
op_assign
id|ntohl
c_func
(paren
id|th-&gt;ack_seq
)paren
op_minus
id|ntohl
c_func
(paren
id|oth-&gt;ack_seq
)paren
)paren
op_ne
l_int|0L
)paren
(brace
r_if
c_cond
(paren
id|deltaA
OG
l_int|0x0000ffff
)paren
(brace
r_goto
id|uncompressed
suffix:semicolon
)brace
id|cp
op_assign
id|encode
c_func
(paren
id|cp
comma
id|deltaA
)paren
suffix:semicolon
id|changes
op_or_assign
id|NEW_A
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|deltaS
op_assign
id|ntohl
c_func
(paren
id|th-&gt;seq
)paren
op_minus
id|ntohl
c_func
(paren
id|oth-&gt;seq
)paren
)paren
op_ne
l_int|0L
)paren
(brace
r_if
c_cond
(paren
id|deltaS
OG
l_int|0x0000ffff
)paren
(brace
r_goto
id|uncompressed
suffix:semicolon
)brace
id|cp
op_assign
id|encode
c_func
(paren
id|cp
comma
id|deltaS
)paren
suffix:semicolon
id|changes
op_or_assign
id|NEW_S
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|changes
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Nothing changed. If this packet contains data and the&n;&t;&t; * last one didn&squot;t, this is probably a data packet following&n;&t;&t; * an ack (normal on an interactive connection) and we send&n;&t;&t; * it compressed.  Otherwise it&squot;s probably a retransmit,&n;&t;&t; * retransmitted ack or window probe.  Send it uncompressed&n;&t;&t; * in case the other side missed the compressed version.&n;&t;&t; */
r_if
c_cond
(paren
id|ip-&gt;tot_len
op_ne
id|cs-&gt;cs_ip.tot_len
op_logical_and
id|ntohs
c_func
(paren
id|cs-&gt;cs_ip.tot_len
)paren
op_eq
id|hlen
)paren
(brace
r_break
suffix:semicolon
)brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: retrans&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|uncompressed
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPECIAL_I
suffix:colon
r_case
id|SPECIAL_D
suffix:colon
multiline_comment|/* actual changes match one of our special case encodings --&n;&t;&t; * send packet uncompressed.&n;&t;&t; */
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: special&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|uncompressed
suffix:semicolon
r_case
id|NEW_S
op_or
id|NEW_A
suffix:colon
r_if
c_cond
(paren
id|deltaS
op_eq
id|deltaA
op_logical_and
id|deltaS
op_eq
id|ntohs
c_func
(paren
id|cs-&gt;cs_ip.tot_len
)paren
op_minus
id|hlen
)paren
(brace
multiline_comment|/* special case for echoed terminal traffic */
id|changes
op_assign
id|SPECIAL_I
suffix:semicolon
id|cp
op_assign
id|new_seq
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NEW_S
suffix:colon
r_if
c_cond
(paren
id|deltaS
op_eq
id|ntohs
c_func
(paren
id|cs-&gt;cs_ip.tot_len
)paren
op_minus
id|hlen
)paren
(brace
multiline_comment|/* special case for data xfer */
id|changes
op_assign
id|SPECIAL_D
suffix:semicolon
id|cp
op_assign
id|new_seq
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|deltaS
op_assign
id|ntohs
c_func
(paren
id|ip-&gt;id
)paren
op_minus
id|ntohs
c_func
(paren
id|cs-&gt;cs_ip.id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deltaS
op_ne
l_int|1
)paren
(brace
id|cp
op_assign
id|encode
c_func
(paren
id|cp
comma
id|deltaS
)paren
suffix:semicolon
id|changes
op_or_assign
id|NEW_I
suffix:semicolon
)brace
r_if
c_cond
(paren
id|th-&gt;psh
)paren
(brace
id|changes
op_or_assign
id|TCP_PUSH_BIT
suffix:semicolon
)brace
multiline_comment|/* Grab the cksum before we overwrite it below.  Then update our&n;&t; * state with this packet&squot;s header.&n;&t; */
id|deltaA
op_assign
id|ntohs
c_func
(paren
id|th-&gt;check
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_ip
comma
id|ip
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_tcp
comma
id|th
comma
l_int|20
)paren
suffix:semicolon
multiline_comment|/* We want to use the original packet as our compressed packet.&n;&t; * (cp - new_seq) is the number of bytes we need for compressed&n;&t; * sequence numbers.  In addition we need one byte for the change&n;&t; * mask, one for the connection id and two for the tcp checksum.&n;&t; * So, (cp - new_seq) + 4 bytes of header are needed.&n;&t; */
id|deltaS
op_assign
id|cp
op_minus
id|new_seq
suffix:semicolon
r_if
c_cond
(paren
id|compress_cid
op_eq
l_int|0
op_logical_or
id|comp-&gt;xmit_current
op_ne
id|cs-&gt;cs_this
)paren
(brace
id|cp
op_assign
id|ocp
suffix:semicolon
op_star
id|cpp
op_assign
id|ocp
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|changes
op_or
id|NEW_C
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|cs-&gt;cs_this
suffix:semicolon
id|comp-&gt;xmit_current
op_assign
id|cs-&gt;cs_this
suffix:semicolon
)brace
r_else
(brace
id|cp
op_assign
id|ocp
suffix:semicolon
op_star
id|cpp
op_assign
id|ocp
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|changes
suffix:semicolon
)brace
id|cp
op_assign
id|put16
c_func
(paren
id|cp
comma
(paren
r_int
)paren
id|deltaA
)paren
suffix:semicolon
multiline_comment|/* Write TCP checksum */
multiline_comment|/* deltaS is now the size of the change section of the compressed header */
id|DPRINT
c_func
(paren
(paren
l_string|&quot;comp: %x %x %x %d %d&bslash;n&quot;
comma
id|icp
comma
id|cp
comma
id|new_seq
comma
id|hlen
comma
id|deltaS
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cp
comma
id|new_seq
comma
id|deltaS
)paren
suffix:semicolon
multiline_comment|/* Write list of deltas */
id|memcpy
c_func
(paren
id|cp
op_plus
id|deltaS
comma
id|icp
op_plus
id|hlen
comma
id|isize
op_minus
id|hlen
)paren
suffix:semicolon
id|comp-&gt;sls_o_compressed
op_increment
suffix:semicolon
id|ocp
(braket
l_int|0
)braket
op_or_assign
id|SL_TYPE_COMPRESSED_TCP
suffix:semicolon
r_return
id|isize
op_minus
id|hlen
op_plus
id|deltaS
op_plus
(paren
id|cp
op_minus
id|ocp
)paren
suffix:semicolon
multiline_comment|/* Update connection state cs &amp; send uncompressed packet (i.e.,&n;&t; * a regular ip/tcp packet but with the &squot;conversation id&squot; we hope&n;&t; * to use on future compressed packets in the protocol field).&n;&t; */
id|uncompressed
suffix:colon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_ip
comma
id|ip
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_tcp
comma
id|th
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;ihl
OG
l_int|5
)paren
id|memcpy
c_func
(paren
id|cs-&gt;cs_ipopt
comma
id|ip
op_plus
l_int|1
comma
(paren
(paren
id|ip-&gt;ihl
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|th-&gt;doff
OG
l_int|5
)paren
id|memcpy
c_func
(paren
id|cs-&gt;cs_tcpopt
comma
id|th
op_plus
l_int|1
comma
(paren
(paren
id|th-&gt;doff
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
id|comp-&gt;xmit_current
op_assign
id|cs-&gt;cs_this
suffix:semicolon
id|comp-&gt;sls_o_uncompressed
op_increment
suffix:semicolon
id|memcpy
c_func
(paren
id|ocp
comma
id|icp
comma
id|isize
)paren
suffix:semicolon
op_star
id|cpp
op_assign
id|ocp
suffix:semicolon
id|ocp
(braket
l_int|9
)braket
op_assign
id|cs-&gt;cs_this
suffix:semicolon
id|ocp
(braket
l_int|0
)braket
op_or_assign
id|SL_TYPE_UNCOMPRESSED_TCP
suffix:semicolon
r_return
id|isize
suffix:semicolon
)brace
r_int
DECL|function|slhc_uncompress
id|slhc_uncompress
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
)paren
(brace
r_register
r_int
id|changes
suffix:semicolon
r_int
id|x
suffix:semicolon
r_register
r_struct
id|tcphdr
op_star
id|thp
suffix:semicolon
r_register
r_struct
id|iphdr
op_star
id|ip
suffix:semicolon
r_register
r_struct
id|cstate
op_star
id|cs
suffix:semicolon
r_int
id|len
comma
id|hdrlen
suffix:semicolon
r_int
r_char
op_star
id|cp
op_assign
id|icp
suffix:semicolon
multiline_comment|/* We&squot;ve got a compressed packet; read the change byte */
id|comp-&gt;sls_i_compressed
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isize
OL
l_int|3
)paren
(brace
id|comp-&gt;sls_i_error
op_increment
suffix:semicolon
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: runt&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|changes
op_assign
op_star
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_C
)paren
(brace
multiline_comment|/* Make sure the state index is in range, then grab the state.&n;&t;&t; * If we have a good state index, clear the &squot;discard&squot; flag.&n;&t;&t; */
id|x
op_assign
op_star
id|cp
op_increment
suffix:semicolon
multiline_comment|/* Read conn index */
r_if
c_cond
(paren
id|x
template_param
id|comp-&gt;rslot_limit
)paren
(brace
r_goto
id|bad
suffix:semicolon
)brace
id|comp-&gt;flags
op_and_assign
op_complement
id|SLF_TOSS
suffix:semicolon
id|comp-&gt;recv_current
op_assign
id|x
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* this packet has an implicit state index.  If we&squot;ve&n;&t;&t; * had a line error since the last time we got an&n;&t;&t; * explicit state index, we have to toss the packet. */
r_if
c_cond
(paren
id|comp-&gt;flags
op_amp
id|SLF_TOSS
)paren
(brace
id|comp-&gt;sls_i_tossed
op_increment
suffix:semicolon
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: toss&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|cs
op_assign
op_amp
id|comp-&gt;rstate
(braket
id|comp-&gt;recv_current
)braket
suffix:semicolon
id|thp
op_assign
op_amp
id|cs-&gt;cs_tcp
suffix:semicolon
id|ip
op_assign
op_amp
id|cs-&gt;cs_ip
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_assign
id|pull16
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Read the TCP checksum */
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad tcp chk&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|thp-&gt;check
op_assign
id|htons
c_func
(paren
id|x
)paren
suffix:semicolon
id|thp-&gt;psh
op_assign
(paren
id|changes
op_amp
id|TCP_PUSH_BIT
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* &n; * we can use the same number for the length of the saved header and&n; * the current one, because the packet wouldn&squot;t have been sent&n; * as compressed unless the options were the same as the previous one&n; */
id|hdrlen
op_assign
id|ip-&gt;ihl
op_star
l_int|4
op_plus
id|thp-&gt;doff
op_star
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|changes
op_amp
id|SPECIALS_MASK
)paren
(brace
r_case
id|SPECIAL_I
suffix:colon
multiline_comment|/* Echoed terminal traffic */
(brace
r_register
r_int
id|i
suffix:semicolon
id|i
op_assign
id|ntohs
c_func
(paren
id|ip-&gt;tot_len
)paren
op_minus
id|hdrlen
suffix:semicolon
id|thp-&gt;ack_seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|thp-&gt;ack_seq
)paren
op_plus
id|i
)paren
suffix:semicolon
id|thp-&gt;seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|thp-&gt;seq
)paren
op_plus
id|i
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SPECIAL_D
suffix:colon
multiline_comment|/* Unidirectional data */
id|thp-&gt;seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|thp-&gt;seq
)paren
op_plus
id|ntohs
c_func
(paren
id|ip-&gt;tot_len
)paren
op_minus
id|hdrlen
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_U
)paren
(brace
id|thp-&gt;urg
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_assign
id|decode
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad U&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|thp-&gt;urg_ptr
op_assign
id|htons
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
r_else
id|thp-&gt;urg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_W
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
id|decode
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad W&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|thp-&gt;window
op_assign
id|htons
c_func
(paren
id|ntohs
c_func
(paren
id|thp-&gt;window
)paren
op_plus
id|x
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_A
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
id|decode
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad A&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|thp-&gt;ack_seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|thp-&gt;ack_seq
)paren
op_plus
id|x
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_S
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
id|decode
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad S&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|thp-&gt;seq
op_assign
id|htonl
c_func
(paren
id|ntohl
c_func
(paren
id|thp-&gt;seq
)paren
op_plus
id|x
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|changes
op_amp
id|NEW_I
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
id|decode
c_func
(paren
op_amp
id|cp
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: bad I&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|ip-&gt;id
op_assign
id|htons
(paren
id|ntohs
(paren
id|ip-&gt;id
)paren
op_plus
id|x
)paren
suffix:semicolon
)brace
r_else
id|ip-&gt;id
op_assign
id|htons
(paren
id|ntohs
(paren
id|ip-&gt;id
)paren
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At this point, cp points to the first byte of data in the&n;&t; * packet.  Put the reconstructed TCP and IP headers back on the&n;&t; * packet.  Recalculate IP checksum (but not TCP checksum).&n;&t; */
id|len
op_assign
id|isize
op_minus
(paren
id|cp
op_minus
id|icp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_goto
id|bad
suffix:semicolon
id|len
op_add_assign
id|hdrlen
suffix:semicolon
id|ip-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
id|ip-&gt;check
op_assign
l_int|0
suffix:semicolon
id|DPRINT
c_func
(paren
(paren
l_string|&quot;uncomp: %d %d %d %d&bslash;n&quot;
comma
id|cp
op_minus
id|icp
comma
id|hdrlen
comma
id|isize
comma
id|len
)paren
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|icp
op_plus
id|hdrlen
comma
id|cp
comma
id|len
op_minus
id|hdrlen
)paren
suffix:semicolon
id|cp
op_assign
id|icp
suffix:semicolon
id|memcpy
c_func
(paren
id|cp
comma
id|ip
comma
l_int|20
)paren
suffix:semicolon
id|cp
op_add_assign
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;ihl
OG
l_int|5
)paren
(brace
id|memcpy
c_func
(paren
id|cp
comma
id|cs-&gt;cs_ipopt
comma
(paren
(paren
id|ip-&gt;ihl
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
id|cp
op_add_assign
(paren
(paren
id|ip-&gt;ihl
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
suffix:semicolon
)brace
(paren
(paren
r_struct
id|iphdr
op_star
)paren
id|icp
)paren
op_member_access_from_pointer
id|check
op_assign
id|ip_csum
c_func
(paren
(paren
r_struct
id|iphdr
op_star
)paren
id|icp
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cp
comma
id|thp
comma
l_int|20
)paren
suffix:semicolon
id|cp
op_add_assign
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|thp-&gt;doff
OG
l_int|5
)paren
(brace
id|memcpy
c_func
(paren
id|cp
comma
id|cs-&gt;cs_tcpopt
comma
(paren
(paren
id|thp-&gt;doff
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
id|cp
op_add_assign
(paren
(paren
id|thp-&gt;doff
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet_debug
op_eq
id|DBG_SLIP
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;runcomp: change %x len %d&bslash;n&quot;
comma
id|changes
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
id|bad
suffix:colon
id|comp-&gt;sls_i_error
op_increment
suffix:semicolon
r_return
id|slhc_toss
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
r_int
DECL|function|slhc_remember
id|slhc_remember
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
)paren
(brace
r_register
r_struct
id|cstate
op_star
id|cs
suffix:semicolon
r_int
id|ip_len
suffix:semicolon
r_struct
id|iphdr
op_star
id|ip
suffix:semicolon
r_struct
id|tcphdr
op_star
id|thp
suffix:semicolon
r_int
r_char
id|index
suffix:semicolon
r_if
c_cond
(paren
id|isize
OL
l_int|20
)paren
(brace
multiline_comment|/* The packet is shorter than a legal IP header */
id|comp-&gt;sls_i_runt
op_increment
suffix:semicolon
r_return
id|slhc_toss
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
multiline_comment|/* Sneak a peek at the IP header&squot;s IHL field to find its length */
id|ip_len
op_assign
(paren
id|icp
(braket
l_int|0
)braket
op_amp
l_int|0xf
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ip_len
OL
l_int|20
)paren
(brace
multiline_comment|/* The IP header length field is too small */
id|comp-&gt;sls_i_runt
op_increment
suffix:semicolon
r_return
id|slhc_toss
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
id|index
op_assign
id|icp
(braket
l_int|9
)braket
suffix:semicolon
id|icp
(braket
l_int|9
)braket
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|ip
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|icp
suffix:semicolon
r_if
c_cond
(paren
id|ip_csum
c_func
(paren
id|ip
)paren
)paren
(brace
multiline_comment|/* Bad IP header checksum; discard */
id|comp-&gt;sls_i_badcheck
op_increment
suffix:semicolon
r_return
id|slhc_toss
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
id|thp
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|ip
)paren
op_plus
id|ip-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
id|comp-&gt;rslot_limit
)paren
(brace
id|comp-&gt;sls_i_error
op_increment
suffix:semicolon
r_return
id|slhc_toss
c_func
(paren
id|comp
)paren
suffix:semicolon
)brace
multiline_comment|/* Update local state */
id|cs
op_assign
op_amp
id|comp-&gt;rstate
(braket
id|comp-&gt;recv_current
op_assign
id|index
)braket
suffix:semicolon
id|comp-&gt;flags
op_and_assign
op_complement
id|SLF_TOSS
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_ip
comma
id|ip
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|cs-&gt;cs_tcp
comma
id|thp
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;ihl
OG
l_int|5
)paren
id|memcpy
c_func
(paren
id|cs-&gt;cs_ipopt
comma
id|ip
op_plus
l_int|1
comma
(paren
(paren
id|ip-&gt;ihl
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thp-&gt;doff
OG
l_int|5
)paren
id|memcpy
c_func
(paren
id|cs-&gt;cs_tcpopt
comma
id|thp
op_plus
l_int|1
comma
(paren
(paren
id|thp-&gt;doff
)paren
op_minus
l_int|5
)paren
op_star
l_int|4
)paren
suffix:semicolon
id|cs-&gt;cs_hsize
op_assign
id|ip-&gt;ihl
op_star
l_int|2
op_plus
id|thp-&gt;doff
op_star
l_int|2
suffix:semicolon
multiline_comment|/* Put headers back on packet&n;&t; * Neither header checksum is recalculated&n;&t; */
id|comp-&gt;sls_i_uncompressed
op_increment
suffix:semicolon
r_return
id|isize
suffix:semicolon
)brace
r_int
DECL|function|slhc_toss
id|slhc_toss
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
(brace
r_if
c_cond
(paren
id|comp
op_eq
id|NULLSLCOMPR
)paren
r_return
l_int|0
suffix:semicolon
id|comp-&gt;flags
op_or_assign
id|SLF_TOSS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slhc_i_status
r_void
id|slhc_i_status
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
(brace
r_if
c_cond
(paren
id|comp
op_ne
id|NULLSLCOMPR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;t%ld Cmp, %ld Uncmp, %ld Bad, %ld Tossed&bslash;n&quot;
comma
id|comp-&gt;sls_i_compressed
comma
id|comp-&gt;sls_i_uncompressed
comma
id|comp-&gt;sls_i_error
comma
id|comp-&gt;sls_i_tossed
)paren
suffix:semicolon
)brace
)brace
DECL|function|slhc_o_status
r_void
id|slhc_o_status
c_func
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
(brace
r_if
c_cond
(paren
id|comp
op_ne
id|NULLSLCOMPR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;t%ld Cmp, %ld Uncmp, %ld AsIs, %ld NotTCP&bslash;n&quot;
comma
id|comp-&gt;sls_o_compressed
comma
id|comp-&gt;sls_o_uncompressed
comma
id|comp-&gt;sls_o_tcp
comma
id|comp-&gt;sls_o_nontcp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%10ld Searches, %10ld Misses&bslash;n&quot;
comma
id|comp-&gt;sls_o_searches
comma
id|comp-&gt;sls_o_misses
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_INET */
eof
