multiline_comment|/* loopback.c contains the loopback device functions. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: loopback.c,v 0.8.4.2 1992/11/10 10:38:48 bir7 Exp $ */
multiline_comment|/* $Log: loopback.c,v $&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and &n; * */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;eth.h&quot;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;sock.h&quot;
macro_line|#include &quot;arp.h&quot;
macro_line|#include &quot;../kern_sock.h&quot; /* for PRINTK */
r_static
r_int
DECL|function|loopback_xmit
id|loopback_xmit
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
)paren
(brace
r_static
r_int
id|inuse
op_assign
l_int|0
suffix:semicolon
r_struct
id|enet_header
op_star
id|eth
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|done
suffix:semicolon
r_static
r_int
r_char
id|buff
(braket
l_int|2048
)braket
suffix:semicolon
r_int
r_char
op_star
id|tmp
suffix:semicolon
id|PRINTK
(paren
l_string|&quot;loopback_xmit (dev = %X)&bslash;n&quot;
comma
id|dev
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
id|inuse
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|inuse
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|tmp
op_assign
l_int|NULL
suffix:semicolon
id|done
op_assign
id|dev_rint
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
id|skb-&gt;len
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;free
)paren
id|kfree_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|done
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|done
op_ne
op_minus
l_int|1
op_logical_and
(paren
id|i
op_assign
id|dev_tint
(paren
id|buff
comma
id|dev
)paren
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* print out the buffer. */
id|PRINTK
(paren
l_string|&quot;ethernet xmit: &bslash;n&quot;
)paren
suffix:semicolon
id|eth
op_assign
(paren
r_struct
id|enet_header
op_star
)paren
id|buff
suffix:semicolon
id|print_eth
(paren
id|eth
)paren
suffix:semicolon
id|tmp
op_assign
id|buff
suffix:semicolon
id|done
op_assign
id|dev_rint
(paren
id|buff
comma
id|i
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|done
op_ne
op_minus
l_int|1
)paren
id|tmp
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|done
op_assign
id|dev_rint
(paren
id|tmp
comma
l_int|0
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
)brace
)brace
id|inuse
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|loopback_init
id|loopback_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|printk
(paren
l_string|&quot;Loopback device init&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* initialize the rest of the device structure. */
id|dev-&gt;mtu
op_assign
l_int|2000
suffix:semicolon
multiline_comment|/* mtu */
id|dev-&gt;hard_start_xmit
op_assign
id|loopback_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|eth_hard_header
suffix:semicolon
id|dev-&gt;add_arp
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
r_sizeof
(paren
r_struct
id|enet_header
)paren
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|ETHER_ADDR_LEN
suffix:semicolon
id|dev-&gt;type
op_assign
id|ETHER_TYPE
suffix:semicolon
id|dev-&gt;queue_xmit
op_assign
id|dev_queue_xmit
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|eth_rebuild_header
suffix:semicolon
id|dev-&gt;type_trans
op_assign
id|eth_type_trans
suffix:semicolon
id|dev-&gt;loopback
op_assign
l_int|1
suffix:semicolon
)brace
eof
