multiline_comment|/* Space.c */
multiline_comment|/* Holds initial configuration information for devices. */
macro_line|#include &quot;dev.h&quot;
macro_line|#include &lt;linux/stddef.h&gt;
r_extern
r_void
id|wd8003_init
c_func
(paren
r_struct
id|device
op_star
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
r_extern
r_void
id|loopback_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
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
