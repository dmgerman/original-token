multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;PACKET - implements raw packet sockets.&n; *&n; * Version:&t;@(#)packet.c&t;1.0.6&t;05/25/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&t;&n; *&t;&t;Alan Cox&t;:&t;verify_area() now used correctly&n; *&t;&t;Alan Cox&t;:&t;new skbuff lists, look ma no backlogs!&n; *&t;&t;Alan Cox&t;:&t;tidied skbuff lists.&n; *&t;&t;Alan Cox&t;:&t;Now uses generic datagram routines I&n; *&t;&t;&t;&t;&t;added. Also fixed the peek/read crash&n; *&t;&t;&t;&t;&t;from all old Linux datagram code.&n; *&t;&t;Alan Cox&t;:&t;Uses the improved datagram code.&n; *&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &quot;inet.h&quot;
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;skbuff.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;udp.h&quot;
macro_line|#include &quot;raw.h&quot;
r_static
r_int
r_int
DECL|function|min
id|min
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|a
OL
id|b
)paren
r_return
id|a
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/* This should be the easiest of all, all we do is copy it into a buffer. */
r_int
DECL|function|packet_rcv
id|packet_rcv
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
id|packet_type
op_star
id|pt
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|pt-&gt;data
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;len
op_add_assign
id|dev-&gt;hard_header_len
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
multiline_comment|/* Charge it too the socket. */
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
id|FREE_READ
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
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;rqueue
comma
id|skb
)paren
suffix:semicolon
id|wake_up
c_func
(paren
id|sk-&gt;sleep
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
multiline_comment|/* This will do terrible things if len + ipheader + devheader &gt; dev-&gt;mtu */
r_static
r_int
DECL|function|packet_sendto
id|packet_sendto
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
id|sockaddr
id|saddr
suffix:semicolon
r_int
id|err
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
id|saddr
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
id|saddr
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
id|saddr
comma
id|usin
comma
r_sizeof
(paren
id|saddr
)paren
)paren
suffix:semicolon
)brace
r_else
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
multiline_comment|/* Find the device first to size check it */
id|saddr.sa_data
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|dev_get
c_func
(paren
id|saddr.sa_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|dev-&gt;mtu
)paren
(brace
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
multiline_comment|/* Now allocate the buffer, knowing 4K pagelimits wont break this line */
id|skb
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|sk-&gt;prot
op_member_access_from_pointer
id|wmalloc
c_func
(paren
id|sk
comma
id|len
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* This shouldn&squot;t happen, but it could. */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
id|DBG_PKT
comma
l_string|&quot;packet_sendto: write buffer full?&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Fill it in */
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
id|len
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|memcpy_fromfs
(paren
id|skb
op_plus
l_int|1
comma
id|from
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;len
op_assign
id|len
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
id|dev
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|skb
comma
id|dev
comma
id|sk-&gt;priority
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|packet_write
id|packet_write
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
id|packet_sendto
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
r_static
r_void
DECL|function|packet_close
id|packet_close
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
id|dev_remove_pack
c_func
(paren
(paren
r_struct
id|packet_type
op_star
)paren
id|sk-&gt;pair
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
(paren
r_void
op_star
)paren
id|sk-&gt;pair
comma
r_sizeof
(paren
r_struct
id|packet_type
)paren
)paren
suffix:semicolon
id|sk-&gt;pair
op_assign
l_int|NULL
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|packet_init
id|packet_init
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|packet_type
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|packet_type
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p-&gt;func
op_assign
id|packet_rcv
suffix:semicolon
id|p-&gt;type
op_assign
id|sk-&gt;num
suffix:semicolon
id|p-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|sk
suffix:semicolon
id|dev_add_pack
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* We need to remember this somewhere. */
id|sk-&gt;pair
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This should be easy, if there is something there&n; * we return it, otherwise we block.&n; */
r_int
DECL|function|packet_recvfrom
id|packet_recvfrom
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
r_struct
id|sockaddr
op_star
id|saddr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|saddr
op_assign
(paren
r_struct
id|sockaddr
op_star
)paren
id|sin
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
id|sk-&gt;shutdown
op_amp
id|RCV_SHUTDOWN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
(brace
id|err
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
r_sizeof
(paren
op_star
id|saddr
)paren
comma
id|addr_len
)paren
suffix:semicolon
)brace
id|err
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
id|err
)paren
(brace
r_return
id|err
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
id|min
c_func
(paren
id|len
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|to
comma
id|skb
op_plus
l_int|1
comma
id|copied
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t use skb_copy_datagram here: We can&squot;t get frag chains */
multiline_comment|/* Copy the address. */
r_if
c_cond
(paren
id|saddr
)paren
(brace
r_struct
id|sockaddr
id|addr
suffix:semicolon
id|addr.sa_family
op_assign
id|skb-&gt;dev-&gt;type
suffix:semicolon
id|memcpy
c_func
(paren
id|addr.sa_data
comma
id|skb-&gt;dev-&gt;name
comma
l_int|14
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|saddr
comma
r_sizeof
(paren
op_star
id|saddr
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|saddr
comma
op_amp
id|addr
comma
r_sizeof
(paren
op_star
id|saddr
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
multiline_comment|/* Its either been used up, or its a peek_copy anyway */
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
DECL|function|packet_read
id|packet_read
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
id|packet_recvfrom
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
DECL|variable|packet_prot
r_struct
id|proto
id|packet_prot
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
id|packet_close
comma
id|packet_read
comma
id|packet_write
comma
id|packet_sendto
comma
id|packet_recvfrom
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
l_int|NULL
comma
id|datagram_select
comma
l_int|NULL
comma
id|packet_init
comma
l_int|NULL
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
l_string|&quot;PACKET&quot;
)brace
suffix:semicolon
eof