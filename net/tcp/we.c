multiline_comment|/* we.c an wd8003 and wd8013 ethernet driver for linux. */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* The bsd386 version was used as an example in order to write this&n;   code */
multiline_comment|/*&n;&t;The driver was significantly modified by Bob Harris to allow the&n;&t;software to operate with either the wd8003 or wd8013 boards.  The&n;&t;wd8013 boards will operate using full memory on board (as specified&n;&t;by the user in Space.c) and the 16 bit wide interface.  The driver&n;&t;will autodetect which board it is using on boot (i.e. &quot;using 16 bit I/F&quot;).&n;&t;In addition, the interrupts structure was significantly modified to &n;&t;respond to all the chips interrupts and to keep track of statistics.&n;&t;The statistics are not currently used.  Debug messages can be toggled&n;&t;by setting the wd_debug variable to a non-zero number.   The driver &n;&t;can detect an open or shorted cable - the wd8013 board functions after&n;&t;the problem is corrected, but the wd8003 board does not always recover.&n;&t;The driver is gradually being migrated toward the National Semiconductor&n;&t;recommendations.  Constructive comments or suggestions can be sent to:&n;&n;&t;&t;Bob Harris, rth@sparta.com&n;&t;&t;7926 Jones Branch Drive, Suite 900&n;&t;&t;McLean, Va. 22102&n;*/
multiline_comment|/* Note:  My driver was full of bugs.  Basically if it works, credit&n;   Bob Harris.  If it&squot;s broken blame me.  -RAB */
multiline_comment|/* $Id: we.c,v 0.8.4.8 1992/12/12 19:25:04 bir7 Exp $ */
multiline_comment|/* $Log: we.c,v $&n; * Revision 0.8.4.8  1992/12/12  19:25:04  bir7&n; * cleaned up Log messages.&n; *&n; * Revision 0.8.4.7  1992/12/12  01:50:49  bir7&n; * made ring buffer volatile.&n; *&n; * Revision 0.8.4.6  1992/12/06  11:31:47  bir7&n; * Added missing braces in if statement.&n; *&n; * Revision 0.8.4.5  1992/12/05  21:35:53  bir7&n; * Added check for bad hardware returning runt packets.&n; *&n; * Revision 0.8.4.4  1992/12/03  19:52:20  bir7&n; * Added better queue checking.&n; *&n; * Revision 0.8.4.3  1992/11/15  14:55:30  bir7&n; * Put more checking in start_xmit to make sure packet doesn&squot;t disapear&n; * out from under us.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.4  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; * */
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
macro_line|#include &quot;wereg.h&quot;
DECL|variable|interrupt_mask
r_static
r_int
r_char
id|interrupt_mask
suffix:semicolon
multiline_comment|/* format of status byte. &n;   bit &n;    0&t;start&n;    1&t;open&n;    2   transmitter in use */
DECL|macro|START
mdefine_line|#define START 1
DECL|macro|OPEN
mdefine_line|#define OPEN  2
DECL|macro|TRS_BUSY
mdefine_line|#define TRS_BUSY 0x400
DECL|macro|IN_INT
mdefine_line|#define IN_INT 8
multiline_comment|/* We need to get rid of all these statics and move them into the&n;   device structure that way we can have more than one wd8003 board&n;   in the system at once. */
DECL|variable|status
r_static
r_volatile
r_int
r_int
id|status
suffix:semicolon
DECL|variable|stats
r_static
r_struct
id|enet_statistics
id|stats
suffix:semicolon
multiline_comment|/* Statistics collection */
DECL|variable|max_pages
r_static
r_int
r_char
id|max_pages
suffix:semicolon
multiline_comment|/* Board memory/256 */
DECL|variable|wd_debug
r_static
r_int
r_char
id|wd_debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turns on/off debug messages */
DECL|variable|dconfig
r_static
r_int
r_char
id|dconfig
op_assign
id|WD_DCONFIG
suffix:semicolon
multiline_comment|/* default data configuration */
DECL|variable|tx_aborted
r_static
r_int
id|tx_aborted
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Empties tx bit bucket */
r_static
r_void
id|wd_trs
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_static
r_int
DECL|function|max
id|max
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|a
OG
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
r_static
r_void
DECL|function|wd_start
id|wd_start
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
suffix:semicolon
id|interrupt_mask
op_assign
id|RECV_MASK
op_or
id|TRANS_MASK
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
id|cmd
op_and_assign
op_complement
(paren
id|CSTOP
op_or
id|CPAGE
)paren
suffix:semicolon
id|cmd
op_or_assign
id|CSTART
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|interrupt_mask
comma
id|WD_IMR
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|status
op_or_assign
id|START
suffix:semicolon
)brace
r_int
DECL|function|wd8003_open
id|wd8003_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* we probably don&squot;t want to be interrupted here. */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This section of code is mostly copied from the bsd driver which is&n;     mostly copied from somewhere else. */
multiline_comment|/* The somewhere else is probably the cmwymr(sp?) dos packet driver */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
id|cmd
op_or_assign
id|CSTOP
suffix:semicolon
id|cmd
op_and_assign
op_complement
(paren
id|CSTART
op_or
id|CPAGE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|WD_IMR
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|dconfig
comma
id|WD_DCR
)paren
suffix:semicolon
multiline_comment|/*Zero the remote byte count. */
id|outb_p
c_func
(paren
l_int|0
comma
id|WD_RBY0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|WD_RBY1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|WD_MCONFIG
comma
id|WD_RCC
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|WD_TCONFIG
comma
id|WD_TRC
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|WD_TRPG
)paren
suffix:semicolon
multiline_comment|/* Set the transmit page start = 0 */
id|outb_p
c_func
(paren
id|max_pages
comma
id|WD_PSTOP
)paren
suffix:semicolon
multiline_comment|/* (read) page stop = top of board memory */
id|outb_p
c_func
(paren
id|WD_TXBS
comma
id|WD_PSTRT
)paren
suffix:semicolon
multiline_comment|/* (read) page start = cur = bnd = top of tx memory */
id|outb_p
c_func
(paren
id|WD_TXBS
comma
id|WD_BNDR
)paren
suffix:semicolon
multiline_comment|/* clear interrupt status. */
id|outb_p
c_func
(paren
l_int|0xff
comma
id|WD_ISR
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t want no stinking interrupts. */
id|outb_p
c_func
(paren
l_int|0
comma
id|WD_IMR
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|1
op_lshift
id|CPAGE_SHIFT
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* set the ether address. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outb_p
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
id|WD_PAR0
op_plus
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* National recommends setting the boundry &lt; current page register */
id|outb_p
c_func
(paren
id|WD_TXBS
op_plus
l_int|1
comma
id|WD_CUR
)paren
suffix:semicolon
multiline_comment|/* Set the current page = page start + 1 */
multiline_comment|/* set the multicast address. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outb_p
c_func
(paren
id|dev-&gt;broadcast
(braket
id|i
)braket
comma
id|WD_MAR0
op_plus
id|i
)paren
suffix:semicolon
)brace
id|cmd
op_and_assign
op_complement
(paren
id|CPAGE
op_or
id|CRDMA
)paren
suffix:semicolon
id|cmd
op_or_assign
l_int|4
op_lshift
id|CRDMA_SHIFT
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|WD_RCONFIG
comma
id|WD_RCC
)paren
suffix:semicolon
id|status
op_assign
id|OPEN
suffix:semicolon
id|wd_start
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* This routine just calls the ether rcv_int. */
r_static
r_int
DECL|function|wdget
id|wdget
c_func
(paren
r_volatile
r_struct
id|wd_ring
op_star
id|ring
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
op_star
id|fptr
suffix:semicolon
r_int
id|len
suffix:semicolon
id|fptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|ring
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* some people have bugs in their hardware which let&n;     ring-&gt;count be 0.  It shouldn&squot;t happen, but we&n;     should check for it. */
id|len
op_assign
id|ring-&gt;count
op_minus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|56
)paren
id|printk
(paren
l_string|&quot;we.c: Hardware problem, runt packet. ring-&gt;count = %d&bslash;n&quot;
comma
id|ring-&gt;count
)paren
suffix:semicolon
r_return
(paren
id|dev_rint
c_func
(paren
id|fptr
comma
id|len
comma
l_int|0
comma
id|dev
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|wd8003_start_xmit
id|wd8003_start_xmit
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
r_char
id|cmd
suffix:semicolon
r_int
id|len
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|TRS_BUSY
)paren
(brace
multiline_comment|/* put in a time out. */
r_if
c_cond
(paren
id|jiffies
op_minus
id|dev-&gt;trans_start
OL
l_int|30
)paren
(brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;wd8003 transmit timed out. &bslash;n&quot;
)paren
suffix:semicolon
)brace
id|status
op_or_assign
id|TRS_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|wd_trs
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* this should check to see if it&squot;s been killed. */
r_if
c_cond
(paren
id|skb-&gt;dev
op_ne
id|dev
)paren
(brace
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
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;arp
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;rebuild_header
(paren
id|skb
op_plus
l_int|1
comma
id|dev
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
id|skb-&gt;dev
op_eq
id|dev
)paren
(brace
id|arp_queue
(paren
id|skb
)paren
suffix:semicolon
)brace
id|cli
(paren
)paren
suffix:semicolon
multiline_comment|/* arp_queue turns them back on. */
id|status
op_and_assign
op_complement
id|TRS_BUSY
suffix:semicolon
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
)brace
id|memcpy
(paren
(paren
r_int
r_char
op_star
)paren
id|dev-&gt;mem_start
comma
id|skb
op_plus
l_int|1
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* now we need to set up the card info. */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|len
op_assign
id|max
c_func
(paren
id|len
comma
id|ETHER_MIN_LEN
)paren
suffix:semicolon
multiline_comment|/* actually we should zero out&n;&t;&t;&t;&t;  the extra memory. */
multiline_comment|/*  printk (&quot;start_xmit len - %d&bslash;n&quot;, len);*/
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
id|cmd
op_and_assign
op_complement
id|CPAGE
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|interrupt_mask
op_or_assign
id|TRANS_MASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IN_INT
)paren
)paren
id|outb
(paren
id|interrupt_mask
comma
id|WD_IMR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
op_amp
l_int|0xff
comma
id|WD_TB0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
op_rshift
l_int|8
comma
id|WD_TB1
)paren
suffix:semicolon
id|cmd
op_or_assign
id|CTRANS
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;free
)paren
(brace
id|kfree_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* tell the card about the new boundary. */
r_static
r_void
DECL|function|wd_put_bnd
id|wd_put_bnd
c_func
(paren
r_int
r_char
id|bnd
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
suffix:semicolon
multiline_comment|/* Ensure page 0 selected */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|CR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x40
)paren
(brace
id|outb_p
c_func
(paren
id|cmd
op_amp
(paren
op_complement
id|CPAGE1
)paren
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* select page 0 */
id|outb_p
c_func
(paren
id|bnd
comma
id|WD_BNDR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
op_or
id|CPAGE1
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* reselect page 1 */
)brace
r_else
(brace
id|outb_p
c_func
(paren
id|bnd
comma
id|WD_BNDR
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
r_char
DECL|function|wd_get_bnd
id|wd_get_bnd
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
comma
id|bnd
suffix:semicolon
multiline_comment|/* Ensure page 0 selected */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x40
)paren
(brace
id|outb_p
c_func
(paren
id|cmd
op_amp
(paren
op_complement
id|CPAGE1
)paren
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* select page 0 */
id|bnd
op_assign
id|inb_p
c_func
(paren
id|WD_BNDR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
op_or
id|CPAGE1
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* reselect page 1 */
r_return
(paren
id|bnd
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|inb_p
c_func
(paren
id|WD_BNDR
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
r_char
DECL|function|wd_get_cur
id|wd_get_cur
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
comma
id|cur
suffix:semicolon
multiline_comment|/* Ensure page 1 selected */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x40
)paren
(brace
r_return
(paren
id|inb_p
c_func
(paren
id|WD_CUR
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb_p
c_func
(paren
id|cmd
op_or
id|CPAGE1
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* select page 1 */
id|cur
op_assign
id|inb_p
c_func
(paren
id|WD_CUR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
op_amp
(paren
op_complement
id|CPAGE1
)paren
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* reselect page 0 */
r_return
(paren
id|cur
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* This routine handles the packet recieved interrupt. */
multiline_comment|/* Debug routines slow things down, but reveal bugs... */
multiline_comment|/* Modified Boundry Page Register to follow Current Page */
r_static
r_void
DECL|function|wd_rcv
id|wd_rcv
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|pkt
suffix:semicolon
multiline_comment|/* Next packet page start */
r_int
r_char
id|bnd
suffix:semicolon
multiline_comment|/* Last packet page end */
r_int
r_char
id|cur
suffix:semicolon
multiline_comment|/* Future packet page start */
r_int
r_char
id|cmd
suffix:semicolon
multiline_comment|/* Command register save */
r_volatile
r_struct
id|wd_ring
op_star
id|ring
suffix:semicolon
r_int
id|done
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Calculate next packet location */
id|cur
op_assign
id|wd_get_cur
c_func
(paren
id|dev
)paren
suffix:semicolon
id|bnd
op_assign
id|wd_get_bnd
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pkt
op_assign
id|bnd
op_plus
l_int|1
)paren
op_eq
id|max_pages
)paren
(brace
id|pkt
op_assign
id|WD_TXBS
suffix:semicolon
)brace
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
id|pkt
op_ne
id|cur
)paren
(brace
multiline_comment|/* Position pointer to packet in card ring buffer */
id|ring
op_assign
(paren
r_volatile
r_struct
id|wd_ring
op_star
)paren
(paren
id|dev-&gt;mem_start
op_plus
(paren
id|pkt
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/* Ensure a valid packet */
r_if
c_cond
(paren
id|ring-&gt;status
op_amp
l_int|1
)paren
(brace
multiline_comment|/* Too small and too big packets are&n;&t;&t;     filtered by the board */
r_if
c_cond
(paren
id|wd_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - wdget: bnd = %d, pkt = %d, &quot;
l_string|&quot;cur = %d, status = %d, len = %d, next = %d&quot;
comma
id|bnd
comma
id|pkt
comma
id|cur
comma
id|ring-&gt;status
comma
id|ring-&gt;count
comma
id|ring-&gt;next
)paren
suffix:semicolon
)brace
id|stats.rx_packets
op_increment
suffix:semicolon
multiline_comment|/* count all receives */
id|done
op_assign
id|wdget
c_func
(paren
id|ring
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* get the packet */
multiline_comment|/* see if we need to process this packet again. */
r_if
c_cond
(paren
id|done
op_eq
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
multiline_comment|/* Calculate next packet location */
id|pkt
op_assign
id|ring-&gt;next
suffix:semicolon
multiline_comment|/* Compute new boundry - tell the chip */
r_if
c_cond
(paren
(paren
id|bnd
op_assign
id|pkt
op_minus
l_int|1
)paren
OL
id|WD_TXBS
)paren
(brace
id|bnd
op_assign
id|max_pages
op_minus
l_int|1
suffix:semicolon
)brace
id|wd_put_bnd
c_func
(paren
id|bnd
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* update our copy of cur. */
id|cur
op_assign
id|wd_get_cur
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Bad packet in ring buffer -&n;&t;&t;&t;   should not happen due to hardware filtering */
id|printk
c_func
(paren
l_string|&quot;wd8013 - bad packet: len = %d, status = x%x, &quot;
l_string|&quot;bnd = %d, pkt = %d, cur = %d&bslash;n&quot;
l_string|&quot;trashing receive buffer!&quot;
comma
id|ring-&gt;count
comma
id|ring-&gt;status
comma
id|bnd
comma
id|pkt
comma
id|cur
)paren
suffix:semicolon
multiline_comment|/* Reset bnd = cur-1 */
r_if
c_cond
(paren
(paren
id|bnd
op_assign
id|wd_get_cur
c_func
(paren
id|dev
)paren
op_minus
l_int|1
)paren
OL
id|WD_TXBS
)paren
(brace
id|bnd
op_assign
id|max_pages
op_minus
l_int|1
suffix:semicolon
)brace
id|wd_put_bnd
c_func
(paren
id|bnd
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* return */
)brace
)brace
r_else
(brace
id|done
op_assign
id|dev_rint
c_func
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
)brace
multiline_comment|/* reset to page 0 */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x40
)paren
(brace
id|outb_p
c_func
(paren
id|cmd
op_amp
op_complement
(paren
id|CPAGE1
)paren
comma
id|WD_COMM
)paren
suffix:semicolon
multiline_comment|/* select page 0 */
)brace
)brace
multiline_comment|/* This routine handles the interrupt case of receiver overruns */
r_static
r_void
DECL|function|wd_rx_over
id|wd_rx_over
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
comma
id|dummy
suffix:semicolon
multiline_comment|/* Nothing actually has been overwritten */
multiline_comment|/* the chip has stopped at the boundry */
multiline_comment|/* but we must get it going again - according to National Semiconductor */
id|printk
(paren
l_string|&quot;wd_rx_over&bslash;n&quot;
)paren
suffix:semicolon
id|cmd
op_assign
id|inb_p
c_func
(paren
id|CR
)paren
suffix:semicolon
multiline_comment|/* get current command register */
id|cmd
op_assign
(paren
id|cmd
op_amp
op_complement
(paren
id|STA
op_or
id|PS0
op_or
id|PS1
)paren
)paren
op_or
id|STOP
suffix:semicolon
multiline_comment|/* toggle start and stop bits, select page 0 */
id|outb_p
c_func
(paren
id|cmd
comma
id|CR
)paren
suffix:semicolon
id|dummy
op_assign
id|inb_p
c_func
(paren
id|RBCR0
)paren
suffix:semicolon
multiline_comment|/* required to detect reset status */
id|dummy
op_assign
id|inb_p
c_func
(paren
id|RBCR1
)paren
suffix:semicolon
id|wd_rcv
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* clear out received packets */
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|PRX
)paren
(brace
id|outb_p
c_func
(paren
id|PRX
comma
id|ISR
)paren
suffix:semicolon
)brace
multiline_comment|/* acknowledge RX interrupt */
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|RST
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* wait for reset to be completed */
id|outb_p
c_func
(paren
id|RST
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge RST interrupt */
id|outb_p
c_func
(paren
(paren
id|cmd
op_amp
op_complement
id|STOP
)paren
op_or
id|STA
comma
id|CR
)paren
suffix:semicolon
multiline_comment|/* Start NIC */
id|outb_p
c_func
(paren
id|WD_TCONFIG
comma
id|TCR
)paren
suffix:semicolon
multiline_comment|/* resume normal mode */
)brace
multiline_comment|/*&n; * This get&squot;s the transmit interrupts. It assumes command page 0 is set, and&n; * returns with command page 0 set.&n; */
r_static
r_void
DECL|function|wd_trs
id|wd_trs
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|cmd
comma
id|errors
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|wd_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd_trs() - TX complete, status = x%x&quot;
comma
id|inb_p
c_func
(paren
id|TSR
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|errors
op_assign
id|inb_p
c_func
(paren
id|TSR
)paren
op_amp
id|PTXOK
)paren
op_logical_or
id|tx_aborted
)paren
(brace
r_if
c_cond
(paren
(paren
id|errors
op_amp
op_complement
l_int|0x02
)paren
op_eq
l_int|0
)paren
(brace
id|stats.tx_packets
op_increment
suffix:semicolon
id|tx_aborted
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* attempt to start a new transmission. */
id|len
op_assign
id|dev_tint
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|dev-&gt;mem_start
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|0
)paren
(brace
id|len
op_assign
id|max
c_func
(paren
id|len
comma
id|ETHER_MIN_LEN
)paren
suffix:semicolon
id|cmd
op_assign
id|inb_p
c_func
(paren
id|WD_COMM
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
op_amp
l_int|0xff
comma
id|WD_TB0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
op_rshift
l_int|8
comma
id|WD_TB1
)paren
suffix:semicolon
id|cmd
op_or_assign
id|CTRANS
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|WD_COMM
)paren
suffix:semicolon
id|interrupt_mask
op_or_assign
id|TRANS_MASK
suffix:semicolon
)brace
r_else
(brace
id|status
op_and_assign
op_complement
id|TRS_BUSY
suffix:semicolon
id|interrupt_mask
op_and_assign
op_complement
id|TRANS_MASK
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* TX error occurred! - H/W will reschedule */
r_if
c_cond
(paren
id|errors
op_amp
id|CRS
)paren
(brace
id|stats.tx_carrier_errors
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - network cable short!&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errors
op_amp
id|COL
)paren
id|stats.collisions
op_add_assign
id|inb_p
c_func
(paren
id|NCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errors
op_amp
id|CDH
)paren
id|stats.tx_heartbeat_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|errors
op_amp
id|OWC
)paren
id|stats.tx_window_errors
op_increment
suffix:semicolon
)brace
)brace
r_void
DECL|function|wd8003_interrupt
id|wd8003_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
(brace
r_int
r_char
id|cmd
suffix:semicolon
r_int
r_char
id|errors
suffix:semicolon
r_int
r_char
id|isr
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_struct
id|pt_regs
op_star
id|ptr
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|ptr
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|reg_ptr
suffix:semicolon
id|irq
op_assign
op_minus
(paren
id|ptr-&gt;orig_eax
op_plus
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
op_ne
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
id|irq
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;we.c: irq %d for unknown device&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* this could take a long time, we should have interrupts on. */
id|cmd
op_assign
id|inb_p
c_func
(paren
id|CR
)paren
suffix:semicolon
multiline_comment|/* Select page 0 */
r_if
c_cond
(paren
id|cmd
op_amp
(paren
id|PS0
op_or
id|PS1
)paren
)paren
(brace
id|cmd
op_and_assign
op_complement
(paren
id|PS0
op_or
id|PS1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|CR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wd_debug
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - interrupt isr = x%x&quot;
comma
id|inb_p
c_func
(paren
id|ISR
)paren
)paren
suffix:semicolon
id|status
op_or_assign
id|IN_INT
suffix:semicolon
r_do
(brace
multiline_comment|/* find out who called */
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Check for overrunning receive buffer first */
r_if
c_cond
(paren
(paren
id|isr
op_assign
id|inb_p
c_func
(paren
id|ISR
)paren
)paren
op_amp
id|OVW
)paren
(brace
multiline_comment|/* Receiver overwrite warning */
id|stats.rx_over_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|wd_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 overrun bnd = %d, cur = %d&quot;
comma
id|wd_get_bnd
c_func
(paren
id|dev
)paren
comma
id|wd_get_cur
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
id|wd_rx_over
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* performs wd_rcv() as well */
id|outb_p
c_func
(paren
id|OVW
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
r_else
r_if
c_cond
(paren
id|isr
op_amp
id|PRX
)paren
(brace
multiline_comment|/* got a packet. */
id|wd_rcv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|PRX
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
multiline_comment|/* This completes rx processing... whats next */
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|PTX
)paren
(brace
multiline_comment|/* finished sending a packet. */
id|wd_trs
c_func
(paren
id|dev
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|PTX
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|RXE
)paren
(brace
multiline_comment|/* recieve error */
id|stats.rx_errors
op_increment
suffix:semicolon
multiline_comment|/* general errors */
id|errors
op_assign
id|inb_p
c_func
(paren
id|RSR
)paren
suffix:semicolon
multiline_comment|/* detailed errors */
r_if
c_cond
(paren
id|errors
op_amp
id|CRC
)paren
id|stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|errors
op_amp
id|FAE
)paren
id|stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|errors
op_amp
id|FO
)paren
id|stats.rx_fifo_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|errors
op_amp
id|MPA
)paren
id|stats.rx_missed_errors
op_increment
suffix:semicolon
id|outb_p
c_func
(paren
id|RXE
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|TXE
)paren
(brace
multiline_comment|/* transmit aborted! */
id|stats.tx_errors
op_increment
suffix:semicolon
multiline_comment|/* general errors */
id|errors
op_assign
id|inb_p
c_func
(paren
id|TSR
)paren
suffix:semicolon
multiline_comment|/* get detailed errors */
r_if
c_cond
(paren
id|errors
op_amp
id|ABT
)paren
(brace
id|stats.tx_aborted_errors
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - network cable open!&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errors
op_amp
id|FU
)paren
(brace
id|stats.tx_fifo_errors
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - TX FIFO underrun!&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Cannot do anymore - empty the bit bucket */
id|tx_aborted
op_assign
l_int|1
suffix:semicolon
id|wd_trs
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tx_aborted
op_assign
l_int|0
suffix:semicolon
id|outb_p
c_func
(paren
id|TXE
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|CNTE
)paren
(brace
multiline_comment|/* Tally counters overflowing */
id|errors
op_assign
id|inb_p
c_func
(paren
id|CNTR0
)paren
suffix:semicolon
id|errors
op_assign
id|inb_p
c_func
(paren
id|CNTR1
)paren
suffix:semicolon
id|errors
op_assign
id|inb_p
c_func
(paren
id|CNTR2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|CNTE
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_amp
id|RST
)paren
(brace
multiline_comment|/* Reset has been performed */
id|outb_p
c_func
(paren
id|RST
comma
id|ISR
)paren
suffix:semicolon
)brace
multiline_comment|/* acknowledge interrupt */
r_if
c_cond
(paren
id|wd_debug
)paren
(brace
r_if
c_cond
(paren
(paren
id|isr
op_assign
id|inb_p
c_func
(paren
id|ISR
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013 - ISR not cleared = x%x&quot;
comma
id|isr
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_increment
id|count
OG
id|max_pages
op_plus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd8013_interrupt - infinite loop detected, isr = x%x, count = %d&quot;
comma
id|isr
comma
id|count
)paren
suffix:semicolon
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|inb_p
c_func
(paren
id|ISR
)paren
op_ne
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|IN_INT
suffix:semicolon
)brace
DECL|variable|wd8003_sigaction
r_static
r_struct
id|sigaction
id|wd8003_sigaction
op_assign
(brace
id|wd8003_interrupt
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_int
DECL|function|wd8003_init
id|wd8003_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_char
id|csum
suffix:semicolon
r_int
id|i
suffix:semicolon
id|csum
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|csum
op_add_assign
id|inb_p
c_func
(paren
id|WD_ROM
op_plus
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csum
op_ne
id|WD_CHECK
)paren
(brace
id|printk
(paren
l_string|&quot;Warning WD8013 board not found at i/o = %X.&bslash;n&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* make sure no one can attempt to open the device. */
id|status
op_assign
id|OPEN
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;wd8013&quot;
)paren
suffix:semicolon
multiline_comment|/* initialize the rest of the device structure. */
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
multiline_comment|/* eth_mtu */
id|dev-&gt;hard_start_xmit
op_assign
id|wd8003_start_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
id|wd8003_open
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|eth_hard_header
suffix:semicolon
id|dev-&gt;add_arp
op_assign
id|eth_add_arp
suffix:semicolon
id|dev-&gt;type_trans
op_assign
id|eth_type_trans
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DEV_NUMBUFFS
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;buffs
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifndef FORCE_8BIT
multiline_comment|/* check for 16 bit board - it doesn&squot;t have register 0/8 aliasing */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|EN_SAPROM
op_plus
id|i
)paren
op_ne
id|inb_p
c_func
(paren
id|EN_CMD
op_plus
id|i
)paren
)paren
(brace
id|csum
op_assign
id|inb_p
c_func
(paren
id|EN_REG1
)paren
suffix:semicolon
multiline_comment|/* fiddle with 16bit bit */
id|outb
c_func
(paren
id|csum
op_xor
id|BUS16
comma
id|EN_REG1
)paren
suffix:semicolon
multiline_comment|/* attempt to clear 16bit bit */
r_if
c_cond
(paren
(paren
id|csum
op_amp
id|BUS16
)paren
op_eq
(paren
id|inb_p
c_func
(paren
id|EN_REG1
)paren
op_amp
id|BUS16
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;, using 16 bit I/F &quot;
)paren
suffix:semicolon
id|dconfig
op_or_assign
l_int|1
suffix:semicolon
multiline_comment|/* use word mode of operation */
id|outb_p
c_func
(paren
id|LAN16ENABLE
op_or
id|MEMMASK
comma
id|EN_REG5
)paren
suffix:semicolon
id|outb
c_func
(paren
id|csum
comma
id|EN_REG1
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* We have a 16bit board here! */
)brace
id|outb
c_func
(paren
id|csum
comma
id|EN_REG1
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* FORCE_8BIT */
multiline_comment|/* mapin the interface memory. */
id|outb_p
c_func
(paren
id|WD_IMEM
comma
id|WD_CTL
)paren
suffix:semicolon
multiline_comment|/* clear the interface memory */
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|i
OL
id|dev-&gt;mem_end
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|i
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|i
)paren
op_ne
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;WD Memory error.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_minus
id|dev-&gt;mem_start
)paren
OG
l_int|4096
)paren
(brace
r_break
suffix:semicolon
)brace
r_else
id|status
op_assign
id|OPEN
suffix:semicolon
)brace
)brace
multiline_comment|/* Calculate how many pages of memory on board */
id|max_pages
op_assign
(paren
id|i
op_minus
id|dev-&gt;mem_start
)paren
op_div
l_int|256
suffix:semicolon
multiline_comment|/* need to set up the dev-&gt;mem_end and dev-&gt;rmem_end */
id|dev-&gt;rmem_end
op_assign
id|i
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|i
suffix:semicolon
multiline_comment|/* print the initialization message, and the&n;     ethernet address. */
id|printk
(paren
l_string|&quot;, %d pages memory, ethernet Address: &quot;
comma
id|max_pages
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
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|inb_p
c_func
(paren
id|WD_ROM
op_plus
id|i
)paren
suffix:semicolon
id|dev-&gt;broadcast
(braket
id|i
)braket
op_assign
l_int|0xff
suffix:semicolon
id|printk
(paren
l_string|&quot;%2.2X &quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the statistics */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
r_struct
id|enet_statistics
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_char
op_star
)paren
op_amp
id|stats
)paren
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irqaction
(paren
id|dev-&gt;irq
comma
op_amp
id|wd8003_sigaction
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to get IRQ%d for wd8013 board&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
