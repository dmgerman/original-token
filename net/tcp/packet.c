multiline_comment|/* packet.c - implements raw packet sockets. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;../kern_sock.h&quot; /* for PRINTK */
r_extern
r_struct
id|proto
id|raw_prot
suffix:semicolon
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
(paren
id|a
)paren
suffix:semicolon
r_return
(paren
id|b
)paren
suffix:semicolon
)brace
multiline_comment|/* this should be the easiest of all, all we do is copy it into&n;   a buffer. */
r_int
DECL|function|packet_rcv
id|packet_rcv
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
r_volatile
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|sk
op_assign
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
multiline_comment|/* now see if we are in use. */
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;inuse
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* drop any packets if we can&squot;t currently deal with them.&n;&t;   Assume that the other end will retransmit if it was&n;&t;   important. */
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|free_skb
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
id|sti
(paren
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
multiline_comment|/* charge it too the socket. */
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
op_plus
id|skb-&gt;mem_len
op_ge
id|SK_RMEM_MAX
)paren
(brace
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|free_skb
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|sk-&gt;rmem_alloc
op_add_assign
id|skb-&gt;mem_len
suffix:semicolon
multiline_comment|/* now just put it onto the queue. */
r_if
c_cond
(paren
id|sk-&gt;rqueue
op_eq
l_int|NULL
)paren
(brace
id|sk-&gt;rqueue
op_assign
id|skb
suffix:semicolon
id|skb-&gt;next
op_assign
id|skb
suffix:semicolon
id|skb-&gt;prev
op_assign
id|skb
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;next
op_assign
id|sk-&gt;rqueue
suffix:semicolon
id|skb-&gt;prev
op_assign
id|sk-&gt;rqueue-&gt;prev
suffix:semicolon
id|skb-&gt;prev-&gt;next
op_assign
id|skb
suffix:semicolon
id|skb-&gt;next-&gt;prev
op_assign
id|skb
suffix:semicolon
)brace
id|wake_up
(paren
id|sk-&gt;sleep
)paren
suffix:semicolon
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* this will do terrible things if len + ipheader + devheader &gt; dev-&gt;mtu */
r_static
r_int
DECL|function|packet_sendto
id|packet_sendto
(paren
r_volatile
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
multiline_comment|/* check the flags. */
r_if
c_cond
(paren
id|flags
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* get and verify the address. */
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
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|verify_area
(paren
id|usin
comma
r_sizeof
(paren
id|saddr
)paren
)paren
suffix:semicolon
id|memcpy_fromfs
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
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|skb
op_assign
id|sk-&gt;prot-&gt;wmalloc
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
op_plus
id|sk-&gt;prot-&gt;max_header
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* this shouldn&squot;t happen, but it could. */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|PRINTK
(paren
l_string|&quot;packet_sendto: write buffer full?&bslash;n&quot;
)paren
suffix:semicolon
id|print_sk
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
)brace
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
op_plus
id|sk-&gt;prot-&gt;max_header
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|saddr.sa_data
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|get_dev
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
id|sk-&gt;prot-&gt;wfree
(paren
id|sk
comma
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENXIO
)paren
suffix:semicolon
)brace
id|verify_area
(paren
id|from
comma
id|len
)paren
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
id|dev-&gt;up
)paren
id|dev-&gt;queue_xmit
(paren
id|skb
comma
id|dev
comma
id|sk-&gt;priority
)paren
suffix:semicolon
r_else
id|free_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|packet_write
id|packet_write
(paren
r_volatile
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
(paren
id|packet_sendto
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
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|packet_close
id|packet_close
(paren
r_volatile
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
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|packet_init
id|packet_init
(paren
r_volatile
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
id|kmalloc
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
(paren
op_minus
id|ENOMEM
)paren
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
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* we need to remember this somewhere. */
id|sk-&gt;pair
op_assign
(paren
r_volatile
r_struct
id|sock
op_star
)paren
id|p
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|packet_recvfrom
id|packet_recvfrom
(paren
r_volatile
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
multiline_comment|/* this should be easy, if there is something there we&n;&t;   return it, otherwise we block. */
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
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
(brace
id|verify_area
(paren
id|addr_len
comma
r_sizeof
(paren
op_star
id|addr_len
)paren
)paren
suffix:semicolon
id|put_fs_long
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
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|sk-&gt;rqueue
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|noblock
)paren
(brace
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
)brace
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;rqueue
op_eq
l_int|NULL
)paren
(brace
id|interruptible_sleep_on
(paren
id|sk-&gt;sleep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
r_return
(paren
op_minus
id|ERESTARTSYS
)paren
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
id|skb
op_assign
id|sk-&gt;rqueue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MSG_PEEK
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;next
op_eq
id|skb
)paren
(brace
id|sk-&gt;rqueue
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|sk-&gt;rqueue
op_assign
id|sk-&gt;rqueue
op_member_access_from_pointer
id|next
suffix:semicolon
id|skb-&gt;prev-&gt;next
op_assign
id|skb-&gt;next
suffix:semicolon
id|skb-&gt;next-&gt;prev
op_assign
id|skb-&gt;prev
suffix:semicolon
)brace
)brace
id|copied
op_assign
id|min
(paren
id|len
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|verify_area
(paren
id|to
comma
id|copied
)paren
suffix:semicolon
id|memcpy_tofs
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
multiline_comment|/* copy the address. */
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
(paren
id|addr.sa_data
comma
id|skb-&gt;dev-&gt;name
comma
l_int|14
)paren
suffix:semicolon
id|verify_area
(paren
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MSG_PEEK
)paren
)paren
(brace
id|free_skb
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
id|copied
)paren
suffix:semicolon
)brace
r_int
DECL|function|packet_read
id|packet_read
(paren
r_volatile
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
(paren
id|packet_recvfrom
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
)paren
suffix:semicolon
)brace
r_int
id|udp_connect
(paren
r_volatile
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
suffix:semicolon
r_int
id|udp_select
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
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
id|udp_select
comma
l_int|NULL
comma
id|packet_init
comma
l_int|128
comma
l_int|0
comma
(brace
l_int|NULL
comma
)brace
)brace
suffix:semicolon
eof
