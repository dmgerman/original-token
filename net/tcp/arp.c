multiline_comment|/* arp.c */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: arp.c,v 0.8.4.5 1992/12/12 19:25:04 bir7 Exp $ */
multiline_comment|/* $Log: arp.c,v $&n; * Revision 0.8.4.5  1992/12/12  19:25:04  bir7&n; * Cleaned up Log messages.&n; *&n; * Revision 0.8.4.4  1992/12/03  19:52:20  bir7&n; * Added paranoid queue checking.&n; *&n; * Revision 0.8.4.3  1992/11/15  14:55:30  bir7&n; * Put more cli/sti pairs in send_q and another sanity check&n; * in arp_queue.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.3  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &quot;arp.h&quot;
DECL|macro|ARP_DEBUG
macro_line|#undef ARP_DEBUG
macro_line|#ifdef  ARP_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK printk
macro_line|#else
DECL|macro|PRINTK
mdefine_line|#define PRINTK dummy_routine
macro_line|#endif
DECL|variable|arp_table
r_static
r_struct
id|arp_table
op_star
id|arp_table
(braket
id|ARP_TABLE_SIZE
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|arp_q
r_struct
id|sk_buff
op_star
id|arp_q
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* this will try to retransmit everything on the queue. */
r_static
r_void
DECL|function|send_arp_q
id|send_arp_q
c_func
(paren
r_void
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp_q
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb
op_assign
id|arp_q
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|skb-&gt;magic
op_ne
id|ARP_QUEUE_MAGIC
)paren
(brace
id|printk
(paren
l_string|&quot;arp.c skb with bad magic - %X: squashing queue&bslash;n&quot;
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|arp_q
op_assign
l_int|NULL
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* extra consistancy check. */
r_if
c_cond
(paren
id|skb-&gt;next
op_eq
l_int|NULL
macro_line|#ifdef CONFIG_MAX_16M
op_logical_or
(paren
r_int
r_int
)paren
(paren
id|skb-&gt;next
)paren
OG
l_int|16
op_star
l_int|1024
op_star
l_int|1024
macro_line|#endif
)paren
(brace
id|printk
(paren
l_string|&quot;dev.c: *** bug bad skb-&gt;next, squashing queue &bslash;n&quot;
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|arp_q
op_assign
l_int|NULL
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb-&gt;magic
op_assign
l_int|0
suffix:semicolon
id|skb2
op_assign
id|skb-&gt;next
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;dev-&gt;rebuild_header
(paren
id|skb
op_plus
l_int|1
comma
id|skb-&gt;dev
)paren
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;next
op_eq
id|skb
)paren
(brace
id|arp_q
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;next-&gt;prev
op_assign
id|skb-&gt;prev
suffix:semicolon
id|skb-&gt;prev-&gt;next
op_assign
id|skb-&gt;next
suffix:semicolon
id|arp_q
op_assign
id|skb-&gt;next
suffix:semicolon
)brace
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|skb-&gt;dev-&gt;queue_xmit
(paren
id|skb
comma
id|skb-&gt;dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp_q
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|skb
op_assign
id|skb2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|skb
op_ne
id|arp_q
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|print_arp
id|print_arp
c_func
(paren
r_struct
id|arp
op_star
id|arp
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|lptr
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;arp: &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp
op_eq
l_int|NULL
)paren
(brace
id|PRINTK
(paren
l_string|&quot;(null)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|PRINTK
(paren
l_string|&quot;   hrd = %d&bslash;n&quot;
comma
id|net16
c_func
(paren
id|arp-&gt;hrd
)paren
)paren
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;   pro = %d&bslash;n&quot;
comma
id|net16
c_func
(paren
id|arp-&gt;pro
)paren
)paren
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;   hlen = %d plen = %d&bslash;n&quot;
comma
id|arp-&gt;hlen
comma
id|arp-&gt;plen
)paren
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;   op = %d&bslash;n&quot;
comma
id|net16
c_func
(paren
id|arp-&gt;op
)paren
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;   sender haddr = &quot;
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
id|arp-&gt;hlen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|PRINTK
(paren
l_string|&quot;0x%02X &quot;
comma
op_star
id|ptr
op_increment
)paren
suffix:semicolon
)brace
id|lptr
op_assign
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
id|PRINTK
(paren
l_string|&quot; send paddr = %X&bslash;n&quot;
comma
op_star
id|lptr
)paren
suffix:semicolon
id|lptr
op_increment
suffix:semicolon
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|lptr
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;   destination haddr = &quot;
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
id|arp-&gt;hlen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|PRINTK
(paren
l_string|&quot;0x%02X &quot;
comma
op_star
id|ptr
op_increment
)paren
suffix:semicolon
)brace
id|lptr
op_assign
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
id|PRINTK
(paren
l_string|&quot; destination paddr = %X&bslash;n&quot;
comma
op_star
id|lptr
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
op_star
DECL|function|arp_sourceh
id|arp_sourceh
c_func
(paren
r_struct
id|arp
op_star
id|arp
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|ptr
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
op_star
DECL|function|arp_targeth
id|arp_targeth
c_func
(paren
r_struct
id|arp
op_star
id|arp
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
id|arp-&gt;hlen
op_plus
l_int|4
suffix:semicolon
r_return
(paren
id|ptr
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
op_star
DECL|function|arp_sourcep
id|arp_sourcep
c_func
(paren
r_struct
id|arp
op_star
id|arp
)paren
(brace
r_int
r_int
op_star
id|lptr
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
id|arp-&gt;hlen
suffix:semicolon
id|lptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|ptr
suffix:semicolon
r_return
(paren
id|lptr
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
op_star
DECL|function|arp_targetp
id|arp_targetp
c_func
(paren
r_struct
id|arp
op_star
id|arp
)paren
(brace
r_int
r_int
op_star
id|lptr
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|arp
op_plus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
l_int|2
op_star
id|arp-&gt;hlen
op_plus
l_int|4
suffix:semicolon
id|lptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|ptr
suffix:semicolon
r_return
(paren
id|lptr
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|arp_free
id|arp_free
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|len
)paren
(brace
id|kfree_s
c_func
(paren
id|ptr
comma
id|len
)paren
suffix:semicolon
)brace
r_static
r_void
op_star
DECL|function|arp_malloc
id|arp_malloc
(paren
r_int
r_int
id|amount
comma
r_int
id|priority
)paren
(brace
r_return
(paren
id|kmalloc
(paren
id|amount
comma
id|priority
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|arp_response
id|arp_response
(paren
r_struct
id|arp
op_star
id|arp1
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|arp
op_star
id|arp2
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|tmp
suffix:semicolon
multiline_comment|/* get some mem and initialize it for the return trip. */
id|skb
op_assign
id|arp_malloc
(paren
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
r_sizeof
(paren
op_star
id|arp2
)paren
op_plus
l_int|2
op_star
id|arp1-&gt;hlen
op_plus
l_int|2
op_star
id|arp1-&gt;plen
op_plus
id|dev-&gt;hard_header_len
comma
id|GFP_ATOMIC
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
l_int|1
)paren
suffix:semicolon
id|skb-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
r_sizeof
(paren
op_star
id|arp2
)paren
op_plus
l_int|2
op_star
id|arp1-&gt;hlen
op_plus
l_int|2
op_star
id|arp1-&gt;plen
op_plus
id|dev-&gt;hard_header_len
suffix:semicolon
id|skb-&gt;len
op_assign
r_sizeof
(paren
op_star
id|arp2
)paren
op_plus
l_int|2
op_star
id|arp1-&gt;hlen
op_plus
l_int|2
op_star
id|arp1-&gt;plen
op_plus
id|dev-&gt;hard_header_len
suffix:semicolon
id|tmp
op_assign
id|dev
op_member_access_from_pointer
id|hard_header
c_func
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
comma
id|dev
comma
id|ETHERTYPE_ARP
comma
op_star
id|arp_sourcep
c_func
(paren
id|arp1
)paren
comma
op_star
id|arp_targetp
c_func
(paren
id|arp1
)paren
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
r_return
(paren
l_int|1
)paren
suffix:semicolon
id|arp2
op_assign
(paren
r_struct
id|arp
op_star
)paren
(paren
(paren
r_int
r_char
op_star
)paren
id|skb
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
id|tmp
)paren
suffix:semicolon
id|memcpy
(paren
id|arp2
comma
id|arp1
comma
r_sizeof
(paren
op_star
id|arp2
)paren
)paren
suffix:semicolon
multiline_comment|/* now swap the addresses. */
op_star
id|arp_sourcep
c_func
(paren
id|arp2
)paren
op_assign
op_star
id|arp_targetp
c_func
(paren
id|arp1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_sourceh
c_func
(paren
id|arp2
)paren
comma
id|dev-&gt;dev_addr
comma
id|arp1-&gt;hlen
)paren
suffix:semicolon
op_star
id|arp_targetp
c_func
(paren
id|arp2
)paren
op_assign
op_star
id|arp_sourcep
c_func
(paren
id|arp1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|arp_targeth
c_func
(paren
id|arp2
)paren
comma
id|arp_sourceh
c_func
(paren
id|arp1
)paren
comma
id|arp1-&gt;hlen
)paren
suffix:semicolon
id|arp2-&gt;op
op_assign
id|NET16
c_func
(paren
id|ARP_REPLY
)paren
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* so the code will know it&squot;s not waiting on an arp. */
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;&gt;&gt;&quot;
)paren
suffix:semicolon
id|print_arp
c_func
(paren
id|arp2
)paren
suffix:semicolon
multiline_comment|/* send it. */
id|dev-&gt;queue_xmit
(paren
id|skb
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* This will find an entry in the arp table by looking at the ip&n;   address. */
r_static
r_struct
id|arp_table
op_star
DECL|function|arp_lookup
id|arp_lookup
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;arp_lookup(paddr=%X)&bslash;n&quot;
comma
id|paddr
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t want to arp ourselves. */
r_if
c_cond
(paren
id|my_ip_addr
c_func
(paren
id|paddr
)paren
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
id|hash
op_assign
id|net32
c_func
(paren
id|paddr
)paren
op_amp
(paren
id|ARP_TABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|apt
op_assign
id|arp_table
(braket
id|hash
)braket
suffix:semicolon
id|apt
op_ne
l_int|NULL
suffix:semicolon
id|apt
op_assign
id|apt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|apt-&gt;ip
op_eq
id|paddr
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|apt
)paren
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|arp_destroy
id|arp_destroy
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
r_struct
id|arp_table
op_star
id|lapt
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;arp_destroy (paddr=%X)&bslash;n&quot;
comma
id|paddr
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t want to destroy are own arp */
r_if
c_cond
(paren
id|my_ip_addr
c_func
(paren
id|paddr
)paren
)paren
r_return
suffix:semicolon
id|hash
op_assign
id|net32
c_func
(paren
id|paddr
)paren
op_amp
(paren
id|ARP_TABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* can&squot;t be interrupted. */
multiline_comment|/* make sure there is something there. */
r_if
c_cond
(paren
id|arp_table
(braket
id|hash
)braket
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* check the first one. */
r_if
c_cond
(paren
id|arp_table
(braket
id|hash
)braket
op_member_access_from_pointer
id|ip
op_eq
id|paddr
)paren
(brace
id|apt
op_assign
id|arp_table
(braket
id|hash
)braket
suffix:semicolon
id|arp_table
(braket
id|hash
)braket
op_assign
id|arp_table
(braket
id|hash
)braket
op_member_access_from_pointer
id|next
suffix:semicolon
id|arp_free
(paren
id|apt
comma
r_sizeof
(paren
op_star
id|apt
)paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* now deal with it any where else in the chain. */
id|lapt
op_assign
id|arp_table
(braket
id|hash
)braket
suffix:semicolon
r_for
c_loop
(paren
id|apt
op_assign
id|arp_table
(braket
id|hash
)braket
op_member_access_from_pointer
id|next
suffix:semicolon
id|apt
op_ne
l_int|NULL
suffix:semicolon
id|apt
op_assign
id|apt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|apt-&gt;ip
op_eq
id|paddr
)paren
(brace
id|lapt-&gt;next
op_assign
id|apt-&gt;next
suffix:semicolon
id|arp_free
(paren
id|apt
comma
r_sizeof
(paren
op_star
id|apt
)paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* this routine does not check for duplicates.  It assumes the caller&n;   does. */
r_static
r_struct
id|arp_table
op_star
DECL|function|create_arp
id|create_arp
(paren
r_int
r_int
id|paddr
comma
r_int
r_char
op_star
id|addr
comma
r_int
id|hlen
)paren
(brace
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
id|apt
op_assign
id|arp_malloc
(paren
r_sizeof
(paren
op_star
id|apt
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apt
op_eq
l_int|NULL
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
id|hash
op_assign
id|net32
c_func
(paren
id|paddr
)paren
op_amp
(paren
id|ARP_TABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|apt-&gt;ip
op_assign
id|paddr
suffix:semicolon
id|apt-&gt;hlen
op_assign
id|hlen
suffix:semicolon
id|memcpy
(paren
id|apt-&gt;hard
comma
id|addr
comma
id|hlen
)paren
suffix:semicolon
id|apt-&gt;last_used
op_assign
id|timer_seq
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|apt-&gt;next
op_assign
id|arp_table
(braket
id|hash
)braket
suffix:semicolon
id|arp_table
(braket
id|hash
)braket
op_assign
id|apt
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|apt
)paren
suffix:semicolon
)brace
r_int
DECL|function|arp_rcv
id|arp_rcv
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
id|arp
op_star
id|arp
suffix:semicolon
r_struct
id|arp_table
op_star
id|tbl
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;&lt;&lt;&bslash;n&quot;
)paren
suffix:semicolon
id|arp
op_assign
id|skb-&gt;h.arp
suffix:semicolon
id|print_arp
c_func
(paren
id|arp
)paren
suffix:semicolon
multiline_comment|/* if this test doesn&squot;t pass, something fishy is going on. */
r_if
c_cond
(paren
id|arp-&gt;hlen
op_ne
id|dev-&gt;addr_len
op_logical_or
id|dev-&gt;type
op_ne
id|NET16
c_func
(paren
id|arp-&gt;hrd
)paren
)paren
(brace
id|kfree_skb
c_func
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
multiline_comment|/* for now we will only deal with ip addresses. */
r_if
c_cond
(paren
id|arp-&gt;pro
op_ne
id|NET16
c_func
(paren
id|ARP_IP_PROT
)paren
op_logical_or
id|arp-&gt;plen
op_ne
l_int|4
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
multiline_comment|/* now look up the ip address in the table. */
id|tbl
op_assign
id|arp_lookup
(paren
op_star
id|arp_sourcep
c_func
(paren
id|arp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbl
op_ne
l_int|NULL
)paren
(brace
id|memcpy
(paren
id|tbl-&gt;hard
comma
id|arp
op_plus
l_int|1
comma
id|arp-&gt;hlen
)paren
suffix:semicolon
id|tbl-&gt;hlen
op_assign
id|arp-&gt;hlen
suffix:semicolon
id|tbl-&gt;last_used
op_assign
id|timer_seq
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|my_ip_addr
c_func
(paren
op_star
id|arp_targetp
c_func
(paren
id|arp
)paren
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tbl
op_eq
l_int|NULL
)paren
id|create_arp
(paren
op_star
id|arp_sourcep
c_func
(paren
id|arp
)paren
comma
id|arp_sourceh
c_func
(paren
id|arp
)paren
comma
id|arp-&gt;hlen
)paren
suffix:semicolon
multiline_comment|/* now see if we can send anything. */
id|send_arp_q
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp-&gt;op
op_ne
id|NET16
c_func
(paren
id|ARP_REQUEST
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* now we need to create a new packet. */
id|ret
op_assign
id|arp_response
c_func
(paren
id|arp
comma
id|dev
)paren
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
id|ret
)paren
suffix:semicolon
)brace
r_void
DECL|function|arp_snd
id|arp_snd
(paren
r_int
r_int
id|paddr
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|saddr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|arp
op_star
id|arp
suffix:semicolon
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
r_int
id|tmp
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;arp_snd (paddr=%X, dev=%X, saddr=%X)&bslash;n&quot;
comma
id|paddr
comma
id|dev
comma
id|saddr
)paren
suffix:semicolon
multiline_comment|/* first we build a dummy arp table entry. */
id|apt
op_assign
id|create_arp
(paren
id|paddr
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apt
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb
op_assign
id|arp_malloc
(paren
r_sizeof
(paren
op_star
id|arp
)paren
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
id|dev-&gt;hard_header_len
op_plus
l_int|2
op_star
id|dev-&gt;addr_len
op_plus
l_int|8
comma
id|GFP_ATOMIC
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
suffix:semicolon
id|skb-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
id|skb-&gt;mem_len
op_assign
r_sizeof
(paren
op_star
id|arp
)paren
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
id|dev-&gt;hard_header_len
op_plus
l_int|2
op_star
id|dev-&gt;addr_len
op_plus
l_int|8
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;len
op_assign
r_sizeof
(paren
op_star
id|arp
)paren
op_plus
id|dev-&gt;hard_header_len
op_plus
l_int|2
op_star
id|dev-&gt;addr_len
op_plus
l_int|8
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|dev-&gt;hard_header
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
comma
id|dev
comma
id|ETHERTYPE_ARP
comma
l_int|0
comma
id|saddr
comma
id|skb-&gt;len
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
id|arp_free
(paren
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|arp
op_assign
(paren
r_struct
id|arp
op_star
)paren
(paren
(paren
r_int
r_char
op_star
)paren
id|skb
op_plus
r_sizeof
(paren
op_star
id|skb
)paren
op_plus
id|tmp
)paren
suffix:semicolon
id|arp-&gt;hrd
op_assign
id|net16
c_func
(paren
id|dev-&gt;type
)paren
suffix:semicolon
id|arp-&gt;pro
op_assign
id|NET16
c_func
(paren
id|ARP_IP_PROT
)paren
suffix:semicolon
id|arp-&gt;hlen
op_assign
id|dev-&gt;addr_len
suffix:semicolon
id|arp-&gt;plen
op_assign
l_int|4
suffix:semicolon
id|arp-&gt;op
op_assign
id|NET16
c_func
(paren
id|ARP_REQUEST
)paren
suffix:semicolon
op_star
id|arp_sourcep
c_func
(paren
id|arp
)paren
op_assign
id|saddr
suffix:semicolon
op_star
id|arp_targetp
c_func
(paren
id|arp
)paren
op_assign
id|paddr
suffix:semicolon
id|memcpy
(paren
id|arp_sourceh
c_func
(paren
id|arp
)paren
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|memcpy
(paren
id|arp_targeth
c_func
(paren
id|arp
)paren
comma
id|dev-&gt;broadcast
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;&gt;&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|print_arp
c_func
(paren
id|arp
)paren
suffix:semicolon
id|dev-&gt;queue_xmit
(paren
id|skb
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|arp_find
id|arp_find
c_func
(paren
r_int
r_char
op_star
id|haddr
comma
r_int
r_int
id|paddr
comma
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|saddr
)paren
(brace
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;arp_find(haddr=%X, paddr=%X, dev=%X, saddr=%X)&bslash;n&quot;
comma
id|haddr
comma
id|paddr
comma
id|dev
comma
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|my_ip_addr
(paren
id|paddr
)paren
)paren
(brace
id|memcpy
(paren
id|haddr
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|apt
op_assign
id|arp_lookup
(paren
id|paddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apt
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* make sure it&squot;s not too old. If it is too old, we will&n;&t;  just pretend we did not find it, and then arp_snd&n;&t;  will verify the address for us. */
r_if
c_cond
(paren
op_logical_neg
id|before
(paren
id|apt-&gt;last_used
comma
id|timer_seq
op_plus
id|ARP_TIMEOUT
)paren
op_logical_and
id|apt-&gt;hlen
op_ne
l_int|0
)paren
(brace
id|apt-&gt;last_used
op_assign
id|timer_seq
suffix:semicolon
id|memcpy
(paren
id|haddr
comma
id|apt-&gt;hard
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* this assume haddr are at least 4 bytes.&n;     If this isn&squot;t true we can use a lookup&n;     table, one for every dev. */
op_star
(paren
r_int
r_int
op_star
)paren
id|haddr
op_assign
id|paddr
suffix:semicolon
multiline_comment|/* if we didn&squot;t find an entry, we will try to &n;     send an arp packet. */
id|arp_snd
c_func
(paren
id|paddr
comma
id|dev
comma
id|saddr
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|arp_add
id|arp_add
(paren
r_int
r_int
id|addr
comma
r_int
r_char
op_star
id|haddr
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|arp_table
op_star
id|apt
suffix:semicolon
multiline_comment|/* first see if the address is already in the table. */
id|apt
op_assign
id|arp_lookup
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apt
op_ne
l_int|NULL
)paren
(brace
id|apt-&gt;last_used
op_assign
id|timer_seq
suffix:semicolon
id|memcpy
(paren
id|apt-&gt;hard
comma
id|haddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|create_arp
(paren
id|addr
comma
id|haddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
)brace
r_void
DECL|function|arp_add_broad
id|arp_add_broad
(paren
r_int
r_int
id|addr
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
id|arp_add
(paren
id|addr
comma
id|dev-&gt;broadcast
comma
id|dev
)paren
suffix:semicolon
)brace
r_void
DECL|function|arp_queue
id|arp_queue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;next
op_ne
l_int|NULL
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;arp.c: arp_queue skb already on queue magic=%X. &bslash;n&quot;
comma
id|skb-&gt;magic
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arp_q
op_eq
l_int|NULL
)paren
(brace
id|arp_q
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
id|arp_q
suffix:semicolon
id|skb-&gt;prev
op_assign
id|arp_q-&gt;prev
suffix:semicolon
id|skb-&gt;next-&gt;prev
op_assign
id|skb
suffix:semicolon
id|skb-&gt;prev-&gt;next
op_assign
id|skb
suffix:semicolon
)brace
id|skb-&gt;magic
op_assign
id|ARP_QUEUE_MAGIC
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
eof
