multiline_comment|/* loopback.c contains the loopback device functions. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: loopback.c,v 0.8.4.8 1993/01/23 18:00:11 bir7 Exp $ */
multiline_comment|/* $Log: loopback.c,v $&n; * Revision 0.8.4.8  1993/01/23  18:00:11  bir7&n; * Fixed problems introduced by merge.&n; *&n; * Revision 0.8.4.7  1993/01/22  23:21:38  bir7&n; * Merged with 99 pl4&n; *&n; * Revision 0.8.4.6  1993/01/22  22:58:08  bir7&n; * Changed so transmitting takes place in bottom half of interrupt routine.&n; *&n; * Revision 0.8.4.5  1992/12/12  19:25:04  bir7&n; * Cleaned up Log messages.&n; *&n; * Revision 0.8.4.4  1992/12/05  21:35:53  bir7&n; * changed dev-&gt;init to return an int.&n; *&n; * Revision 0.8.4.3  1992/11/18  15:38:03  bir7&n; * Fixed bug in start_xmit.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; * */
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
macro_line|#ifdef PRINTK
DECL|macro|PRINTK
macro_line|#undef PRINTK
macro_line|#endif
macro_line|#ifdef LOOPBACK_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) printk x
macro_line|#else
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) /**/
macro_line|#endif
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
r_int
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
op_logical_or
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;loopback_xmit (dev = %X)&bslash;n&quot;
comma
id|dev
)paren
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
id|dev-&gt;tbusy
op_ne
l_int|0
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
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
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
id|done
op_assign
id|dev_rint
(paren
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|dev
)paren
suffix:semicolon
)brace
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
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
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
