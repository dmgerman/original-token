multiline_comment|/* dummy.c: a dummy net driver&n;&n;&t;The purpose of this driver is to provide a device to point a&n;&t;route through, but not to actually transmit packets.&n;&n;&t;Why?  If you have a machine whose only connection is an occasional&n;&t;PPP/SLIP/PLIP link, you can only connect to your own hostname&n;&t;when the link is up.  Otherwise you have to use localhost.&n;&t;This isn&squot;t very consistent.&n;&n;&t;One solution is to set up a dummy link using PPP/SLIP/PLIP,&n;&t;but this seems (to me) too much overhead for too little gain.&n;&t;This driver provides a small alternative. Thus you can do&n;&t;&n;&t;[when not running slip]&n;&t;&t;ifconfig dummy slip.addr.ess.here up&n;&t;[to go to slip]&n;&t;&t;ifconfig dummy down&n;&t;&t;dip whatever&n;&n;&t;This was written by looking at Donald Becker&squot;s skeleton driver&n;&t;and the loopback driver.  I then threw away anything that didn&squot;t&n;&t;apply!&t;Thanks to Alan Cox for the key clue on what to do with&n;&t;misguided packets.&n;&n;&t;&t;&t;Nick Holloway, 27th May 1994&n;&t;[I tweaked this explanation a little but thats all]&n;&t;&t;&t;Alan Cox, 30th May 1994&n;*/
multiline_comment|/* To have statistics (just packets sent) define this */
DECL|macro|DUMMY_STATS
macro_line|#undef DUMMY_STATS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_static
r_int
id|dummy_xmit
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
suffix:semicolon
macro_line|#ifdef DUMMY_STATS
r_static
r_struct
id|enet_statistics
op_star
id|dummy_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_int
DECL|function|dummy_init
id|dummy_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* I commented this out as bootup is noisy enough anyway and this driver&n;   seems pretty reliable 8) 8) 8) */
multiline_comment|/*&t;printk ( KERN_INFO &quot;Dummy net driver (94/05/27 v1.0)&bslash;n&quot; ); */
multiline_comment|/* Initialize the device structure. */
id|dev-&gt;hard_start_xmit
op_assign
id|dummy_xmit
suffix:semicolon
macro_line|#if DUMMY_STATS
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|enet_statistics
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|enet_statistics
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|dummy_get_stats
suffix:semicolon
macro_line|#endif
multiline_comment|/* Fill in the fields of the device structure with ethernet-generic values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dummy_xmit
id|dummy_xmit
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
macro_line|#if DUMMY_STATS
r_struct
id|enet_statistics
op_star
id|stats
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
op_logical_or
id|dev
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
macro_line|#if DUMMY_STATS
id|stats
op_assign
(paren
r_struct
id|enet_statistics
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if DUMMY_STATS
r_static
r_struct
id|enet_statistics
op_star
DECL|function|dummy_get_stats
id|dummy_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|enet_statistics
op_star
id|stats
op_assign
(paren
r_struct
id|enet_statistics
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
id|stats
suffix:semicolon
)brace
macro_line|#endif
eof
