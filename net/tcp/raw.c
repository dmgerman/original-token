multiline_comment|/* raw.c - implements raw ip sockets. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: raw.c,v 0.8.4.6 1992/11/18 15:38:03 bir7 Exp $ */
multiline_comment|/* $Log: raw.c,v $&n; * Revision 0.8.4.6  1992/11/18  15:38:03  bir7&n; * Works now.&n; *&n; *&n; * Revision 0.8.4.4  1992/11/17  09:27:07  bir7&n; * Fixed error in header building.&n; *&n; * Revision 0.8.4.3  1992/11/16  16:13:40  bir7&n; * Added debuggin information.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.3  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and &n; * */
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
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;../kern_sock.h&quot; /* for PRINTK */
macro_line|#ifdef PRINTK
DECL|macro|PRINTK
macro_line|#undef PRINTK
macro_line|#endif
DECL|macro|RAW_DEBUG
macro_line|#undef RAW_DEBUG
macro_line|#ifdef RAW_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK printk
macro_line|#else
DECL|macro|PRINTK
mdefine_line|#define PRINTK dummy_routine
macro_line|#endif
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
DECL|function|raw_rcv
id|raw_rcv
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
id|ip_protocol
op_star
id|protocol
)paren
(brace
r_volatile
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;raw_rcv (skb=%X, dev=%X, opt=%X, daddr=%X,&bslash;n&quot;
l_string|&quot;         len=%d, saddr=%X, redo=%d, protocol=%X)&bslash;n&quot;
comma
id|skb
comma
id|dev
comma
id|opt
comma
id|daddr
comma
id|len
comma
id|saddr
comma
id|redo
comma
id|protocol
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
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
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
id|sk
op_assign
id|protocol-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
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
multiline_comment|/* now we need to copy this into memory. */
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;len
op_assign
id|len
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;saddr
op_assign
id|daddr
suffix:semicolon
id|skb-&gt;daddr
op_assign
id|saddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|redo
)paren
(brace
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
id|PRINTK
(paren
l_string|&quot;raw_rcv adding to backlog. &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;back_log
op_eq
l_int|NULL
)paren
(brace
id|sk-&gt;back_log
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
id|sk-&gt;back_log
suffix:semicolon
id|skb-&gt;prev
op_assign
id|sk-&gt;back_log-&gt;prev
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
id|sti
c_func
(paren
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
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|kfree_skb
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
DECL|function|raw_sendto
id|raw_sendto
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
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|tmp
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;raw_sendto (sk=%X, from=%X, len=%d, noblock=%d, flags=%X,&bslash;n&quot;
l_string|&quot;            usin=%X, addr_len = %d)&bslash;n&quot;
comma
id|sk
comma
id|from
comma
id|len
comma
id|noblock
comma
id|flags
comma
id|usin
comma
id|addr_len
)paren
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
id|sin
)paren
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/*&t;verify_area (usin, sizeof (sin));*/
id|memcpy_fromfs
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
(paren
op_minus
id|EINVAL
)paren
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
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_port
op_assign
id|sk-&gt;protocol
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|sk-&gt;daddr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sin.sin_port
op_eq
l_int|0
)paren
id|sin.sin_port
op_assign
id|sk-&gt;protocol
suffix:semicolon
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
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
multiline_comment|/* need to change this to sleep. */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;raw_sendto: write buffer full?&bslash;n&quot;
)paren
suffix:semicolon
id|print_sk
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|noblock
)paren
r_return
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
id|tmp
op_assign
id|sk-&gt;wmem_alloc
suffix:semicolon
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
id|tmp
op_le
id|sk-&gt;wmem_alloc
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
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERESTARTSYS
)paren
suffix:semicolon
)brace
)brace
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
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
multiline_comment|/* these two should be unecessary. */
id|skb-&gt;arp
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|sk-&gt;prot-&gt;build_header
(paren
id|skb
comma
id|sk-&gt;saddr
comma
id|sin.sin_addr.s_addr
comma
op_amp
id|dev
comma
id|sk-&gt;protocol
comma
id|sk-&gt;opt
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
(brace
id|PRINTK
(paren
l_string|&quot;raw_sendto: error building ip header.&bslash;n&quot;
)paren
suffix:semicolon
id|sk-&gt;prot-&gt;wfree
(paren
id|sk
comma
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
r_return
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/*   verify_area (from, len);*/
id|memcpy_fromfs
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|skb
op_plus
l_int|1
)paren
op_plus
id|tmp
comma
id|from
comma
id|len
)paren
suffix:semicolon
id|skb-&gt;len
op_assign
id|tmp
op_plus
id|len
suffix:semicolon
id|sk-&gt;prot-&gt;queue_xmit
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
id|release_sock
(paren
id|sk
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
DECL|function|raw_write
id|raw_write
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
id|raw_sendto
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
DECL|function|raw_close
id|raw_close
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
id|PRINTK
(paren
l_string|&quot;raw_close: deleting ip_protocol %d&bslash;n&quot;
comma
(paren
(paren
r_struct
id|ip_protocol
op_star
)paren
id|sk-&gt;pair
)paren
op_member_access_from_pointer
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delete_ip_protocol
(paren
(paren
r_struct
id|ip_protocol
op_star
)paren
id|sk-&gt;pair
)paren
OL
l_int|0
)paren
id|PRINTK
(paren
l_string|&quot;raw_close: delete_ip_protocol failed. &bslash;n&quot;
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
id|ip_protocol
)paren
)paren
suffix:semicolon
id|sk-&gt;pair
op_assign
l_int|NULL
suffix:semicolon
id|release_sock
(paren
id|sk
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|raw_init
id|raw_init
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|ip_protocol
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
id|p-&gt;handler
op_assign
id|raw_rcv
suffix:semicolon
id|p-&gt;protocol
op_assign
id|sk-&gt;protocol
suffix:semicolon
id|p-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|sk
suffix:semicolon
id|add_ip_protocol
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
id|PRINTK
(paren
l_string|&quot;raw init added protocol %d&bslash;n&quot;
comma
id|sk-&gt;protocol
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|raw_recvfrom
id|raw_recvfrom
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
id|PRINTK
(paren
l_string|&quot;raw_recvfrom (sk=%X, to=%X, len=%d, noblock=%d, flags=%X,&bslash;n&quot;
l_string|&quot;              sin=%X, addr_len=%X)&bslash;n&quot;
comma
id|sk
comma
id|to
comma
id|len
comma
id|noblock
comma
id|flags
comma
id|sin
comma
id|addr_len
)paren
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
id|sin
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
r_if
c_cond
(paren
id|copied
)paren
r_return
(paren
id|copied
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
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERESTARTSYS
)paren
suffix:semicolon
)brace
)brace
id|sk-&gt;inuse
op_assign
l_int|1
suffix:semicolon
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
id|skb-&gt;h.raw
comma
id|copied
)paren
suffix:semicolon
multiline_comment|/* copy the address. */
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
id|addr.sin_addr.s_addr
op_assign
id|skb-&gt;daddr
suffix:semicolon
id|verify_area
(paren
id|sin
comma
r_sizeof
(paren
op_star
id|sin
)paren
)paren
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
id|kfree_skb
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
DECL|function|raw_read
id|raw_read
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
id|raw_recvfrom
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
DECL|variable|raw_prot
r_struct
id|proto
id|raw_prot
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
id|raw_close
comma
id|raw_read
comma
id|raw_write
comma
id|raw_sendto
comma
id|raw_recvfrom
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
id|raw_rcv
comma
id|udp_select
comma
l_int|NULL
comma
id|raw_init
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