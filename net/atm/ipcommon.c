multiline_comment|/* net/atm/ipcommon.c - Common items for all ways of doing IP over ATM */
multiline_comment|/* Written 1996,1997 by Werner Almesberger, EPFL LRC */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmclip.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#include &quot;ipcommon.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
DECL|variable|llc_oui
r_const
r_int
r_char
id|llc_oui
(braket
)braket
op_assign
(brace
l_int|0xaa
comma
multiline_comment|/* DSAP: non-ISO */
l_int|0xaa
comma
multiline_comment|/* SSAP: non-ISO */
l_int|0x03
comma
multiline_comment|/* Ctrl: Unnumbered Information Command PDU */
l_int|0x00
comma
multiline_comment|/* OUI: EtherType */
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
multiline_comment|/*&n; * skb_migrate moves the list at FROM to TO, emptying FROM in the process.&n; * This function should live in skbuff.c or skbuff.h. Note that skb_migrate&n; * is not atomic, so turn off interrupts when using it.&n; */
DECL|function|skb_migrate
r_void
id|skb_migrate
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|from
comma
r_struct
id|sk_buff_head
op_star
id|to
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|prev
suffix:semicolon
r_for
c_loop
(paren
id|skb
op_assign
(paren
(paren
r_struct
id|sk_buff
op_star
)paren
id|from
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|skb
op_ne
(paren
r_struct
id|sk_buff
op_star
)paren
id|from
suffix:semicolon
id|skb
op_assign
id|skb-&gt;next
)paren
id|skb-&gt;list
op_assign
id|to
suffix:semicolon
id|prev
op_assign
id|from-&gt;prev
suffix:semicolon
id|from-&gt;next-&gt;prev
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|to
suffix:semicolon
id|prev-&gt;next
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|to
suffix:semicolon
op_star
id|to
op_assign
op_star
id|from
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
id|from
)paren
suffix:semicolon
)brace
eof
