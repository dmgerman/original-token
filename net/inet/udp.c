multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The User Datagram Protocol (UDP).&n; *&n; * Version:&t;@(#)udp.c&t;1.0.13&t;06/02/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;verify_area() calls&n; *&t;&t;Alan Cox&t;: &t;stopped close while in use off icmp&n; *&t;&t;&t;&t;&t;messages. Not a fix but a botch that&n; *&t;&t;&t;&t;&t;for udp at least is &squot;valid&squot;.&n; *&t;&t;Alan Cox&t;:&t;Fixed icmp handling properly&n; *&t;&t;Alan Cox&t;: &t;Correct error for oversized datagrams&n; *&t;&t;Alan Cox&t;:&t;Tidied select() semantics. &n; *&t;&t;Alan Cox&t;:&t;udp_err() fixed properly, also now &n; *&t;&t;&t;&t;&t;select and read wake correctly on errors&n; *&t;&t;Alan Cox&t;:&t;udp_send verify_area moved to avoid mem leak&n; *&t;&t;Alan Cox&t;:&t;UDP can count its memory&n; *&t;&t;Alan Cox&t;:&t;send to an uknown connection causes&n; *&t;&t;&t;&t;&t;an ECONNREFUSED off the icmp, but&n; *&t;&t;&t;&t;&t;does NOT close.&n; *&t;&t;Alan Cox&t;:&t;Switched to new sk_buff handlers. No more backlog!&n; *&t;&t;Alan Cox&t;:&t;Using generic datagram code. Even smaller and the PEEK&n; *&t;&t;&t;&t;&t;bug no longer crashes it.&n; *&t;&t;Fred Van Kempen&t;: &t;Net2e support for sk-&gt;broadcast.&n; *&t;&t;Alan Cox&t;:&t;Uses skb_free_datagram&n; *&t;&t;Alan Cox&t;:&t;Added get/set sockopt support.&n; *&t;&t;Alan Cox&t;:&t;Broadcasting without option set returns EACCES.&n; *&t;&t;Alan Cox&t;:&t;No wakeup calls. Instead we now use the callbacks.&n; *&t;&t;Alan Cox&t;:&t;Use ip_tos and ip_ttl&n; *&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;inet.h&quot;
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;skbuff.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &quot;udp.h&quot;
macro_line|#include &quot;icmp.h&quot;
DECL|macro|min
mdefine_line|#define min(a,b)&t;((a)&lt;(b)?(a):(b))
r_static
r_void
DECL|function|print_udp
id|print_udp
c_func
(paren
r_struct
id|udphdr
op_star
id|uh
)paren
(brace
r_if
c_cond
(paren
id|inet_debug
op_ne
id|DBG_UDP
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|uh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(NULL)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;UDP: source = %d, dest = %d&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|uh-&gt;source
)paren
comma
id|ntohs
c_func
(paren
id|uh-&gt;dest
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;     len = %d, check = %d&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|uh-&gt;len
)paren
comma
id|ntohs
c_func
(paren
id|uh-&gt;check
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called by the ICMP module when it gets some&n; * sort of error condition.  If err &lt; 0 then the socket should&n; * be closed and the error returned to the user.  If err &gt; 0&n; * it&squot;s just the icmp type &lt;&lt; 8 | icmp code.  &n; * Header points to the ip header of the error packet. We move&n; * on past this. Then (as it used to claim before adjustment)&n; * header points to the first 8 bytes of the udp header.  We need&n; * to find the appropriate port.&n; */
r_void
DECL|function|udp_err
id|udp_err
c_func
(paren
r_int
id|err
comma
r_int
r_char
op_star
id|header
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|saddr
comma
r_struct
id|inet_protocol
op_star
id|protocol
)paren
(brace
r_struct
id|udphdr
op_star
id|th
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|iphdr
op_star
id|ip
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|header
suffix:semicolon
id|header
op_add_assign
l_int|4
op_star
id|ip-&gt;ihl
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|header
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: err(err=%d, header=%X, daddr=%X, saddr=%X, protocl=%X)&bslash;n&bslash;&n;sport=%d,dport=%d&quot;
comma
id|err
comma
id|header
comma
id|daddr
comma
id|saddr
comma
id|protocol
comma
(paren
r_int
)paren
id|th-&gt;source
comma
(paren
r_int
)paren
id|th-&gt;dest
)paren
)paren
suffix:semicolon
id|sk
op_assign
id|get_sock
c_func
(paren
op_amp
id|udp_prot
comma
id|th-&gt;source
comma
id|daddr
comma
id|th-&gt;dest
comma
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* No socket for error */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
multiline_comment|/* As per the calling spec */
(brace
id|sk-&gt;err
op_assign
op_minus
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
multiline_comment|/* User process wakes to see error */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
op_amp
l_int|0xff00
op_eq
(paren
id|ICMP_SOURCE_QUENCH
op_lshift
l_int|8
)paren
)paren
(brace
multiline_comment|/* Slow down! */
r_if
c_cond
(paren
id|sk-&gt;cong_window
OG
l_int|1
)paren
id|sk-&gt;cong_window
op_assign
id|sk-&gt;cong_window
op_div
l_int|2
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sk-&gt;err
op_assign
id|icmp_err_convert
(braket
id|err
op_amp
l_int|0xff
)braket
dot
id|errno
suffix:semicolon
multiline_comment|/* It&squot;s only fatal if we have connected to them. */
r_if
c_cond
(paren
id|icmp_err_convert
(braket
id|err
op_amp
l_int|0xff
)braket
dot
id|fatal
op_logical_and
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
)paren
(brace
id|sk-&gt;err
op_assign
id|ECONNREFUSED
suffix:semicolon
)brace
id|sk
op_member_access_from_pointer
id|error_report
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|udp_check
id|udp_check
c_func
(paren
r_struct
id|udphdr
op_star
id|uh
comma
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: check(uh=%X, len = %d, saddr = %X, daddr = %X)&bslash;n&quot;
comma
id|uh
comma
id|len
comma
id|saddr
comma
id|daddr
)paren
)paren
suffix:semicolon
id|print_udp
c_func
(paren
id|uh
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;&bslash;t addl %%ecx,%%ebx&bslash;n&quot;
l_string|&quot;&bslash;t adcl %%edx,%%ebx&bslash;n&quot;
l_string|&quot;&bslash;t adcl $0, %%ebx&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;c&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;d&quot;
(paren
(paren
id|ntohs
c_func
(paren
id|len
)paren
op_lshift
l_int|16
)paren
op_plus
id|IPPROTO_UDP
op_star
l_int|256
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;bx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|3
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;&bslash;tclc&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;&bslash;t lodsl&bslash;n&quot;
l_string|&quot;&bslash;t adcl %%eax, %%ebx&bslash;n&quot;
l_string|&quot;&bslash;t loop 1b&bslash;n&quot;
l_string|&quot;&bslash;t adcl $0, %%ebx&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=S&quot;
(paren
id|uh
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;c&quot;
(paren
id|len
op_div
l_int|4
)paren
comma
l_string|&quot;1&quot;
(paren
id|uh
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;bx&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert from 32 bits to 16 bits. */
id|__asm__
c_func
(paren
l_string|&quot;&bslash;t movl %%ebx, %%ecx&bslash;n&quot;
l_string|&quot;&bslash;t shrl $16,%%ecx&bslash;n&quot;
l_string|&quot;&bslash;t addw %%cx, %%bx&bslash;n&quot;
l_string|&quot;&bslash;t adcw $0, %%bx&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
multiline_comment|/* Check for an extra word. */
r_if
c_cond
(paren
(paren
id|len
op_amp
l_int|2
)paren
op_ne
l_int|0
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;&bslash;t lodsw&bslash;n&quot;
l_string|&quot;&bslash;t addw %%ax,%%bx&bslash;n&quot;
l_string|&quot;&bslash;t adcw $0, %%bx&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=S&quot;
(paren
id|uh
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|uh
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;ax&quot;
comma
l_string|&quot;bx&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Now check for the extra byte. */
r_if
c_cond
(paren
(paren
id|len
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;&bslash;t lodsb&bslash;n&quot;
l_string|&quot;&bslash;t movb $0,%%ah&bslash;n&quot;
l_string|&quot;&bslash;t addw %%ax,%%bx&bslash;n&quot;
l_string|&quot;&bslash;t adcw $0, %%bx&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;S&quot;
(paren
id|uh
)paren
suffix:colon
l_string|&quot;si&quot;
comma
l_string|&quot;ax&quot;
comma
l_string|&quot;bx&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* We only want the bottom 16 bits, but we never cleared the top 16. */
r_return
(paren
op_complement
id|sum
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
r_static
r_void
DECL|function|udp_send_check
id|udp_send_check
c_func
(paren
r_struct
id|udphdr
op_star
id|uh
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_int
id|len
comma
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|uh-&gt;check
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_logical_and
id|sk-&gt;no_check
)paren
r_return
suffix:semicolon
id|uh-&gt;check
op_assign
id|udp_check
c_func
(paren
id|uh
comma
id|len
comma
id|saddr
comma
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uh-&gt;check
op_eq
l_int|0
)paren
id|uh-&gt;check
op_assign
l_int|0xffff
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_send
id|udp_send
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr_in
op_star
id|sin
comma
r_int
r_char
op_star
id|from
comma
r_int
id|len
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
r_int
r_char
op_star
id|buff
suffix:semicolon
r_int
r_int
id|saddr
suffix:semicolon
r_int
id|size
comma
id|tmp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: send(dst=%s:%d buff=%X len=%d)&bslash;n&quot;
comma
id|in_ntoa
c_func
(paren
id|sin-&gt;sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|sin-&gt;sin_port
)paren
comma
id|from
comma
id|len
)paren
)paren
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Allocate a copy of the packet. */
id|size
op_assign
r_sizeof
(paren
r_struct
id|sk_buff
)paren
op_plus
id|sk-&gt;prot-&gt;max_header
op_plus
id|len
suffix:semicolon
id|skb
op_assign
id|sk-&gt;prot
op_member_access_from_pointer
id|wmalloc
c_func
(paren
id|sk
comma
id|size
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
id|size
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* to avoid changing sk-&gt;saddr */
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now build the IP and MAC header. */
id|buff
op_assign
id|skb-&gt;data
suffix:semicolon
id|saddr
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: &gt;&gt; IP_Header: %X -&gt; %X dev=%X prot=%X len=%d&bslash;n&quot;
comma
id|saddr
comma
id|sin-&gt;sin_addr.s_addr
comma
id|dev
comma
id|IPPROTO_UDP
comma
id|skb-&gt;mem_len
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|sk-&gt;prot
op_member_access_from_pointer
id|build_header
c_func
(paren
id|skb
comma
id|saddr
comma
id|sin-&gt;sin_addr.s_addr
comma
op_amp
id|dev
comma
id|IPPROTO_UDP
comma
id|sk-&gt;opt
comma
id|skb-&gt;mem_len
comma
id|sk-&gt;ip_tos
comma
id|sk-&gt;ip_ttl
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
multiline_comment|/* So memory is freed correctly */
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
(brace
id|sk-&gt;prot
op_member_access_from_pointer
id|wfree
c_func
(paren
id|sk
comma
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
id|buff
op_add_assign
id|tmp
suffix:semicolon
id|saddr
op_assign
id|dev-&gt;pa_addr
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: &gt;&gt; MAC+IP len=%d&bslash;n&quot;
comma
id|tmp
)paren
)paren
suffix:semicolon
id|skb-&gt;len
op_assign
id|tmp
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
op_plus
id|len
suffix:semicolon
multiline_comment|/* len + UDP + IP + MAC */
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Fill in the UDP header. */
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|buff
suffix:semicolon
id|uh-&gt;len
op_assign
id|htons
c_func
(paren
id|len
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
)paren
suffix:semicolon
id|uh-&gt;source
op_assign
id|sk-&gt;dummy_th.source
suffix:semicolon
id|uh-&gt;dest
op_assign
id|sin-&gt;sin_port
suffix:semicolon
id|buff
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|uh
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Copy the user data. */
id|memcpy_fromfs
c_func
(paren
id|buff
comma
id|from
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Set up the UDP checksum. */
id|udp_send_check
c_func
(paren
id|uh
comma
id|saddr
comma
id|sin-&gt;sin_addr.s_addr
comma
id|skb-&gt;len
op_minus
id|tmp
comma
id|sk
)paren
suffix:semicolon
multiline_comment|/* Send the datagram to the interface. */
id|sk-&gt;prot
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|sk
comma
id|dev
comma
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_sendto
id|udp_sendto
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|from
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
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: sendto(len=%d, flags=%X)&bslash;n&quot;
comma
id|len
comma
id|flags
)paren
)paren
suffix:semicolon
multiline_comment|/* Check the flags. */
r_if
c_cond
(paren
id|flags
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Get and verify the address. */
r_if
c_cond
(paren
id|usin
)paren
(brace
r_if
c_cond
(paren
id|addr_len
OL
r_sizeof
(paren
id|sin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|usin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
op_amp
id|sin
comma
id|usin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sin.sin_family
op_logical_and
id|sin.sin_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sin.sin_port
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
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
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_port
op_assign
id|sk-&gt;dummy_th.dest
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|sk-&gt;daddr
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;broadcast
op_logical_and
id|chk_addr
c_func
(paren
id|sin.sin_addr.s_addr
)paren
op_eq
id|IS_BROADCAST
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/* Must turn broadcast on first */
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Send the packet. */
id|tmp
op_assign
id|udp_send
c_func
(paren
id|sk
comma
op_amp
id|sin
comma
id|from
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* The datagram has been sent off.  Release the socket. */
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
r_static
r_int
DECL|function|udp_write
id|udp_write
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
)paren
(brace
r_return
id|udp_sendto
c_func
(paren
id|sk
comma
id|buff
comma
id|len
comma
id|noblock
comma
id|flags
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|udp_ioctl
id|udp_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DDIOCSDBG
suffix:colon
(brace
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|val
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
l_int|0
suffix:colon
id|inet_debug
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|inet_debug
op_assign
id|DBG_UDP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|TIOCOUTQ
suffix:colon
(brace
r_int
r_int
id|amount
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|amount
op_assign
id|sk-&gt;prot
op_member_access_from_pointer
id|wspace
c_func
(paren
id|sk
)paren
multiline_comment|/*/2*/
suffix:semicolon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
id|amount
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|TIOCINQ
suffix:colon
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_int
id|amount
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|amount
op_assign
l_int|0
suffix:semicolon
id|skb
op_assign
id|sk-&gt;rqueue
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * We will only return the amount&n;&t;&t;&t;&t; * of this packet since that is all&n;&t;&t;&t;&t; * that will be read.&n;&t;&t;&t;&t; */
id|amount
op_assign
id|skb-&gt;len
suffix:semicolon
)brace
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
id|amount
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This should be easy, if there is something there we&bslash;&n; * return it, otherwise we block.&n; */
r_int
DECL|function|udp_recvfrom
id|udp_recvfrom
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|to
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
r_struct
id|sockaddr_in
op_star
id|sin
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
id|er
suffix:semicolon
multiline_comment|/*&n;   * This will pick up errors that occured while the program&n;   * was doing something else.&n;   */
r_if
c_cond
(paren
id|sk-&gt;err
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|sk-&gt;err
suffix:semicolon
id|sk-&gt;err
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
(brace
id|er
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|addr_len
comma
r_sizeof
(paren
op_star
id|addr_len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
(brace
r_return
id|er
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
r_sizeof
(paren
op_star
id|sin
)paren
comma
id|addr_len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sin
)paren
(brace
id|er
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|sin
comma
r_sizeof
(paren
op_star
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
(brace
r_return
id|er
suffix:semicolon
)brace
)brace
id|er
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
(brace
r_return
id|er
suffix:semicolon
)brace
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
id|er
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
id|er
suffix:semicolon
)brace
id|copied
op_assign
id|min
c_func
(paren
id|len
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* FIXME : should use udp header size info value */
id|skb_copy_datagram
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
id|to
comma
id|copied
)paren
suffix:semicolon
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|sin
)paren
(brace
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
id|addr.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|addr.sin_port
op_assign
id|skb-&gt;h.uh-&gt;source
suffix:semicolon
id|addr.sin_addr.s_addr
op_assign
id|skb-&gt;daddr
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|sin
comma
op_amp
id|addr
comma
r_sizeof
(paren
op_star
id|sin
)paren
)paren
suffix:semicolon
)brace
id|skb_free_datagram
c_func
(paren
id|skb
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
)brace
r_int
DECL|function|udp_read
id|udp_read
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
)paren
(brace
r_return
id|udp_recvfrom
c_func
(paren
id|sk
comma
id|buff
comma
id|len
comma
id|noblock
comma
id|flags
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_int
DECL|function|udp_connect
id|udp_connect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|er
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
OL
r_sizeof
(paren
id|sin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|er
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|usin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
(brace
r_return
id|er
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
op_amp
id|sin
comma
id|usin
comma
r_sizeof
(paren
id|sin
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sin.sin_family
op_logical_and
id|sin.sin_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;broadcast
op_logical_and
id|chk_addr
c_func
(paren
id|sin.sin_addr.s_addr
)paren
op_eq
id|IS_BROADCAST
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/* Must turn broadcast on first */
id|sk-&gt;daddr
op_assign
id|sin.sin_addr.s_addr
suffix:semicolon
id|sk-&gt;dummy_th.dest
op_assign
id|sin.sin_port
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|udp_close
id|udp_close
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
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;dead
)paren
id|destroy_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_else
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/* All we need to do is get the socket, and then do a checksum. */
r_int
DECL|function|udp_rcv
id|udp_rcv
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
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
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
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|skb-&gt;h.uh
suffix:semicolon
id|sk
op_assign
id|get_sock
c_func
(paren
op_amp
id|udp_prot
comma
id|uh-&gt;dest
comma
id|saddr
comma
id|uh-&gt;source
comma
id|daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|chk_addr
c_func
(paren
id|daddr
)paren
op_eq
id|IS_MYADDR
)paren
(brace
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PORT_UNREACH
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Hmm.  We got an UDP broadcast to a port to which we&n;&t; * don&squot;t wanna listen.  The only thing we can do now is&n;&t; * to ignore the packet... -FvK&n;&t; */
id|skb-&gt;sk
op_assign
l_int|NULL
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
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uh-&gt;check
op_logical_and
id|udp_check
c_func
(paren
id|uh
comma
id|len
comma
id|saddr
comma
id|daddr
)paren
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;UDP: bad checksum&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
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
l_int|0
suffix:semicolon
)brace
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;len
op_assign
id|len
suffix:semicolon
multiline_comment|/* These are supposed to be switched. */
id|skb-&gt;daddr
op_assign
id|saddr
suffix:semicolon
id|skb-&gt;saddr
op_assign
id|daddr
suffix:semicolon
multiline_comment|/* Charge it to the socket. */
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
op_plus
id|skb-&gt;mem_len
op_ge
id|sk-&gt;rcvbuf
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sk-&gt;rmem_alloc
op_add_assign
id|skb-&gt;mem_len
suffix:semicolon
multiline_comment|/* At this point we should print the thing out. */
id|DPRINTF
c_func
(paren
(paren
id|DBG_UDP
comma
l_string|&quot;&lt;&lt; &bslash;n&quot;
)paren
)paren
suffix:semicolon
id|print_udp
c_func
(paren
id|uh
)paren
suffix:semicolon
multiline_comment|/* Now add it to the data chain and wake things up. */
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;rqueue
comma
id|skb
)paren
suffix:semicolon
id|skb-&gt;len
op_assign
id|len
op_minus
r_sizeof
(paren
op_star
id|uh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|sk
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|udp_prot
r_struct
id|proto
id|udp_prot
op_assign
(brace
id|sock_wmalloc
comma
id|sock_rmalloc
comma
id|sock_wfree
comma
id|sock_rfree
comma
id|sock_rspace
comma
id|sock_wspace
comma
id|udp_close
comma
id|udp_read
comma
id|udp_write
comma
id|udp_sendto
comma
id|udp_recvfrom
comma
id|ip_build_header
comma
id|udp_connect
comma
l_int|NULL
comma
id|ip_queue_xmit
comma
id|ip_retransmit
comma
l_int|NULL
comma
l_int|NULL
comma
id|udp_rcv
comma
id|datagram_select
comma
id|udp_ioctl
comma
l_int|NULL
comma
l_int|NULL
comma
id|ip_setsockopt
comma
id|ip_getsockopt
comma
l_int|128
comma
l_int|0
comma
(brace
l_int|NULL
comma
)brace
comma
l_string|&quot;UDP&quot;
)brace
suffix:semicolon
eof
