multiline_comment|/* Space.c */
multiline_comment|/* Holds initial configuration information for devices. */
multiline_comment|/* $Id: Space.c,v 0.8.4.5 1992/12/12 19:25:04 bir7 Exp $ */
multiline_comment|/* $Log: Space.c,v $&n; * Revision 0.8.4.5  1992/12/12  19:25:04  bir7&n; * Cleaned up Log messages.&n; *&n; * Revision 0.8.4.4  1992/12/05  21:35:53  bir7&n; * Updated dev-&gt;init type.&n; *&n; * Revision 0.8.4.3  1992/11/15  14:55:30  bir7&n; * Removed ctrl-h so diff no longer thinks it&squot;s a binary file.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; *&n; */
macro_line|#include &quot;dev.h&quot;
macro_line|#include &lt;linux/stddef.h&gt;
r_extern
r_int
id|wd8003_init
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|loopback_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|wd8003_dev
r_static
r_struct
id|device
id|wd8003_dev
op_assign
(brace
l_string|&quot;eth0&quot;
comma
l_int|0xd2000
comma
multiline_comment|/* recv memory end. */
l_int|0xd0600
comma
multiline_comment|/* recv memory start. */
l_int|0xd2000
comma
multiline_comment|/* memory end. */
l_int|0xd0000
comma
multiline_comment|/* memory start. */
l_int|0x280
comma
multiline_comment|/* base i/o address. */
l_int|5
comma
multiline_comment|/* irq */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags */
l_int|NULL
comma
multiline_comment|/* next device */
id|wd8003_init
comma
multiline_comment|/* wd8003_init should set up the rest. */
l_int|0
comma
multiline_comment|/* trans start. */
(brace
l_int|NULL
)brace
comma
multiline_comment|/* buffs */
l_int|NULL
comma
multiline_comment|/* backlog */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* stop */
l_int|NULL
comma
multiline_comment|/* hard_start_xmit */
l_int|NULL
comma
multiline_comment|/* hard_header */
l_int|NULL
comma
multiline_comment|/* add arp */
l_int|NULL
comma
multiline_comment|/* queue xmit */
l_int|NULL
comma
multiline_comment|/* rebuild header */
l_int|NULL
comma
multiline_comment|/* type_trans */
l_int|NULL
comma
multiline_comment|/* send_packet */
l_int|NULL
comma
multiline_comment|/* private */
l_int|0
comma
multiline_comment|/* type. */
l_int|0
comma
multiline_comment|/* hard_header_len */
l_int|0
comma
multiline_comment|/* mtu */
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* broadcast address */
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* device address */
l_int|0
multiline_comment|/* addr len */
)brace
suffix:semicolon
DECL|variable|loopback_dev
r_static
r_struct
id|device
id|loopback_dev
op_assign
(brace
l_string|&quot;loopback&quot;
comma
op_minus
l_int|1
comma
multiline_comment|/* recv memory end. */
l_int|0x0
comma
multiline_comment|/* recv memory start. */
op_minus
l_int|1
comma
multiline_comment|/* memory end. */
l_int|0
comma
multiline_comment|/* memory start. */
l_int|0
comma
multiline_comment|/* base i/o address. */
l_int|0
comma
multiline_comment|/* irq */
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags */
op_amp
id|wd8003_dev
comma
multiline_comment|/* next device */
id|loopback_init
comma
multiline_comment|/* loopback_init should set up the rest. */
l_int|0
comma
multiline_comment|/* trans start. */
(brace
l_int|NULL
)brace
comma
multiline_comment|/* buffs */
l_int|NULL
comma
multiline_comment|/* backlog */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* stop */
l_int|NULL
comma
multiline_comment|/* hard_start_xmit */
l_int|NULL
comma
multiline_comment|/* hard_header */
l_int|NULL
comma
multiline_comment|/* add arp */
l_int|NULL
comma
multiline_comment|/* queue xmit */
l_int|NULL
comma
multiline_comment|/* rebuild header */
l_int|NULL
comma
multiline_comment|/* type_trans */
l_int|NULL
comma
multiline_comment|/* send_packet */
l_int|NULL
comma
multiline_comment|/* private */
l_int|0
comma
multiline_comment|/* type. */
l_int|0
comma
multiline_comment|/* hard_header_len */
l_int|0
comma
multiline_comment|/* mtu */
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* broadcast address */
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* device address */
l_int|0
multiline_comment|/* addr len */
)brace
suffix:semicolon
DECL|variable|dev_base
r_struct
id|device
op_star
id|dev_base
op_assign
op_amp
id|loopback_dev
suffix:semicolon
eof
