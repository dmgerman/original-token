multiline_comment|/*&n; *&t;Routines having to do with the &squot;struct sk_buff&squot; memory handlers.&n; *&n; *&t;Authors:&t;Alan Cox &lt;iiitac@pyr.swan.ac.uk&gt;&n; *&t;&t;&t;Florian La Roche &lt;rzsfl@rz.uni-sb.de&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;ip.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;route.h&quot;
macro_line|#include &quot;tcp.h&quot;
macro_line|#include &quot;udp.h&quot;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;sock.h&quot;
multiline_comment|/*&n; *&t;Resource tracking variables&n; */
DECL|variable|net_memory
r_volatile
r_int
r_int
id|net_memory
op_assign
l_int|0
suffix:semicolon
DECL|variable|net_skbcount
r_volatile
r_int
r_int
id|net_skbcount
op_assign
l_int|0
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
multiline_comment|/*&n; *&t;Debugging paranoia. Can go later when this crud stack works&n; */
DECL|function|skb_check
r_int
id|skb_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|head
comma
r_int
id|line
comma
r_char
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|head
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;magic_debug_cookie
op_ne
id|SK_HEAD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, found a bad skb-head&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;next
op_logical_or
op_logical_neg
id|skb-&gt;prev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;skb_check: head without next or prev&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;next-&gt;magic_debug_cookie
op_ne
id|SK_HEAD_SKB
op_logical_and
id|skb-&gt;next-&gt;magic_debug_cookie
op_ne
id|SK_GOOD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, bad next head-skb member&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;prev-&gt;magic_debug_cookie
op_ne
id|SK_HEAD_SKB
op_logical_and
id|skb-&gt;prev-&gt;magic_debug_cookie
op_ne
id|SK_GOOD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, bad prev head-skb member&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#if 0
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb-&gt;next
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|skb2
op_ne
id|skb
op_logical_and
id|i
OL
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|skb_check
c_func
(paren
id|skb2
comma
l_int|0
comma
id|line
comma
id|file
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad queue element in whole queue&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
id|skb2
op_assign
id|skb2-&gt;next
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;next
op_ne
l_int|NULL
op_logical_and
id|skb-&gt;next-&gt;magic_debug_cookie
op_ne
id|SK_HEAD_SKB
op_logical_and
id|skb-&gt;next-&gt;magic_debug_cookie
op_ne
id|SK_GOOD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, bad next skb member&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;prev
op_ne
l_int|NULL
op_logical_and
id|skb-&gt;prev-&gt;magic_debug_cookie
op_ne
id|SK_HEAD_SKB
op_logical_and
id|skb-&gt;prev-&gt;magic_debug_cookie
op_ne
id|SK_GOOD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, bad prev skb member&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;magic_debug_cookie
op_eq
id|SK_FREED_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, found a freed skb lurking in the undergrowth!&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;skb=%p, real size=%ld, claimed size=%ld, free=%d&bslash;n&quot;
comma
id|skb
comma
id|skb-&gt;truesize
comma
id|skb-&gt;mem_len
comma
id|skb-&gt;free
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;magic_debug_cookie
op_ne
id|SK_GOOD_SKB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, passed a non skb!&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;skb=%p, real size=%ld, claimed size=%ld, free=%d&bslash;n&quot;
comma
id|skb
comma
id|skb-&gt;truesize
comma
id|skb-&gt;mem_len
comma
id|skb-&gt;free
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;mem_len
op_ne
id|skb-&gt;truesize
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;File: %s Line %d, Dubious size setting!&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;skb=%p, real size=%ld, claimed size=%ld&bslash;n&quot;
comma
id|skb
comma
id|skb-&gt;truesize
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Guess it might be acceptable then */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|skb_queue_head_init
r_void
id|skb_queue_head_init
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
(brace
id|list-&gt;prev
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
suffix:semicolon
id|list-&gt;next
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
id|list-&gt;magic_debug_cookie
op_assign
id|SK_HEAD_SKB
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Insert an sk_buff at the start of a list.&n; */
DECL|function|skb_queue_head
r_void
id|skb_queue_head
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list_
comma
r_struct
id|sk_buff
op_star
id|newsk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|list
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
id|IS_SKB
c_func
(paren
id|newsk
)paren
suffix:semicolon
id|IS_SKB_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newsk-&gt;next
op_logical_or
id|newsk-&gt;prev
)paren
id|printk
c_func
(paren
l_string|&quot;Suspicious queue head: sk_buff on list!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|newsk-&gt;next
op_assign
id|list-&gt;next
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|list
suffix:semicolon
id|newsk-&gt;next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;prev-&gt;next
op_assign
id|newsk
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Insert an sk_buff at the end of a list.&n; */
DECL|function|skb_queue_tail
r_void
id|skb_queue_tail
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list_
comma
r_struct
id|sk_buff
op_star
id|newsk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|list
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
r_if
c_cond
(paren
id|newsk-&gt;next
op_logical_or
id|newsk-&gt;prev
)paren
id|printk
c_func
(paren
l_string|&quot;Suspicious queue tail: sk_buff on list!&bslash;n&quot;
)paren
suffix:semicolon
id|IS_SKB
c_func
(paren
id|newsk
)paren
suffix:semicolon
id|IS_SKB_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
macro_line|#endif
id|newsk-&gt;next
op_assign
id|list
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|list-&gt;prev
suffix:semicolon
id|newsk-&gt;next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;prev-&gt;next
op_assign
id|newsk
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove an sk_buff from a list. This routine is also interrupt safe&n; *&t;so you can grab read and free buffers as another process adds them.&n; */
DECL|function|skb_dequeue
r_struct
id|sk_buff
op_star
id|skb_dequeue
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list_
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|result
suffix:semicolon
r_struct
id|sk_buff
op_star
id|list
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|IS_SKB_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
id|result
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|list
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|result-&gt;next-&gt;prev
op_assign
id|list
suffix:semicolon
id|list-&gt;next
op_assign
id|result-&gt;next
suffix:semicolon
id|result-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Insert a packet before another one in a list.&n; */
DECL|function|skb_insert
r_void
id|skb_insert
c_func
(paren
r_struct
id|sk_buff
op_star
id|old
comma
r_struct
id|sk_buff
op_star
id|newsk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
id|IS_SKB
c_func
(paren
id|old
)paren
suffix:semicolon
id|IS_SKB
c_func
(paren
id|newsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old-&gt;next
op_logical_or
op_logical_neg
id|old-&gt;prev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;insert before unlisted item!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newsk-&gt;next
op_logical_or
id|newsk-&gt;prev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;inserted item is already on a list.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|newsk-&gt;next
op_assign
id|old
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|old-&gt;prev
suffix:semicolon
id|old-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;prev-&gt;next
op_assign
id|newsk
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Place a packet after a given packet in a list.&n; */
DECL|function|skb_append
r_void
id|skb_append
c_func
(paren
r_struct
id|sk_buff
op_star
id|old
comma
r_struct
id|sk_buff
op_star
id|newsk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
id|IS_SKB
c_func
(paren
id|old
)paren
suffix:semicolon
id|IS_SKB
c_func
(paren
id|newsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old-&gt;next
op_logical_or
op_logical_neg
id|old-&gt;prev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;append before unlisted item!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newsk-&gt;next
op_logical_or
id|newsk-&gt;prev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;append item is already on a list.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|old
suffix:semicolon
id|newsk-&gt;next
op_assign
id|old-&gt;next
suffix:semicolon
id|newsk-&gt;next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|old-&gt;next
op_assign
id|newsk
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove an sk_buff from its list. Works even without knowing the list it&n; *&t;is sitting on, which can be handy at times. It also means that THE LIST&n; *&t;MUST EXIST when you unlink. Thus a list must have its contents unlinked&n; *&t;_FIRST_.&n; */
DECL|function|skb_unlink
r_void
id|skb_unlink
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|IS_SKB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;prev
op_logical_and
id|skb-&gt;next
)paren
(brace
id|skb-&gt;next-&gt;prev
op_assign
id|skb-&gt;prev
suffix:semicolon
id|skb-&gt;prev-&gt;next
op_assign
id|skb-&gt;next
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef PARANOID_BUGHUNT_MODE&t;/* This is legal but we sometimes want to watch it */
r_else
id|printk
c_func
(paren
l_string|&quot;skb_unlink: not a linked element&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Get a clone of an sk_buff. This is the safe way to peek at&n; *&t;a socket queue without accidents. Its a bit long but most&n; *&t;of it acutally ends up as tiny bits of inline assembler&n; *&t;anyway. Only the memcpy of upto 4K with ints off is not&n; *&t;as nice as I&squot;d like.&n; */
DECL|function|skb_peek_copy
r_struct
id|sk_buff
op_star
id|skb_peek_copy
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list_
)paren
(brace
r_struct
id|sk_buff
op_star
id|list
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
suffix:semicolon
r_struct
id|sk_buff
op_star
id|orig
comma
op_star
id|newsk
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Now for some games to avoid races */
id|IS_SKB_HEAD
c_func
(paren
id|list
)paren
suffix:semicolon
r_do
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|orig
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|orig
op_eq
id|list
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|IS_SKB
c_func
(paren
id|orig
)paren
suffix:semicolon
id|len
op_assign
id|orig-&gt;truesize
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|newsk
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* May sleep */
r_if
c_cond
(paren
id|newsk
op_eq
l_int|NULL
)paren
multiline_comment|/* Oh dear... not to worry */
r_return
l_int|NULL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
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
id|list-&gt;next
op_ne
id|orig
)paren
multiline_comment|/* List changed go around another time */
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|newsk-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|newsk-&gt;free
op_assign
l_int|1
suffix:semicolon
id|newsk-&gt;mem_addr
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;mem_len
op_assign
id|len
suffix:semicolon
id|kfree_skb
c_func
(paren
id|newsk
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|IS_SKB
c_func
(paren
id|orig
)paren
suffix:semicolon
id|IS_SKB
c_func
(paren
id|newsk
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newsk
comma
id|orig
comma
id|len
)paren
suffix:semicolon
id|newsk-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|newsk-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|newsk-&gt;mem_addr
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;h.raw
op_add_assign
(paren
(paren
r_char
op_star
)paren
id|newsk
op_minus
(paren
r_char
op_star
)paren
id|orig
)paren
suffix:semicolon
id|newsk-&gt;link3
op_assign
l_int|NULL
suffix:semicolon
id|newsk-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|newsk-&gt;free
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|newsk
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Free an sk_buff. This still knows about things it should&n; *&t;not need to like protocols and sockets.&n; */
DECL|function|kfree_skb
r_void
id|kfree_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|rw
)paren
(brace
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kfree_skb: skb = NULL (from %08lx)&bslash;n&quot;
comma
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|skb
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|IS_SKB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;lock
)paren
(brace
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Free when unlocked */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;free
op_eq
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: kfree_skb passed an skb that nobody set the free flag on! (from %08lx)&bslash;n&quot;
comma
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|skb
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;next
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: kfree_skb passed an skb still on a list (from %08lx).&bslash;n&quot;
comma
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|skb
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;sk
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;sk-&gt;prot
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|rw
)paren
id|skb-&gt;sk-&gt;prot
op_member_access_from_pointer
id|rfree
c_func
(paren
id|skb-&gt;sk
comma
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
r_else
id|skb-&gt;sk-&gt;prot
op_member_access_from_pointer
id|wfree
c_func
(paren
id|skb-&gt;sk
comma
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Non INET - default wmalloc/rmalloc handler */
r_if
c_cond
(paren
id|rw
)paren
id|skb-&gt;sk-&gt;rmem_alloc
op_sub_assign
id|skb-&gt;mem_len
suffix:semicolon
r_else
id|skb-&gt;sk-&gt;wmem_alloc
op_sub_assign
id|skb-&gt;mem_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;sk-&gt;dead
)paren
(brace
id|skb-&gt;sk
op_member_access_from_pointer
id|write_space
c_func
(paren
id|skb-&gt;sk
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SLAVE_BALANCING&t;&t;&t;&t;
r_if
c_cond
(paren
id|skb-&gt;in_dev_queue
op_logical_and
id|skb-&gt;dev
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;dev-&gt;pkt_queue
op_decrement
suffix:semicolon
)brace
macro_line|#endif
id|kfree_skbmem
c_func
(paren
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
macro_line|#ifdef CONFIG_SLAVE_BALANCING&t;&t;&t;&t;
r_if
c_cond
(paren
id|skb-&gt;in_dev_queue
op_logical_and
id|skb-&gt;dev
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;dev-&gt;pkt_queue
op_decrement
suffix:semicolon
)brace
macro_line|#endif
id|kfree_skbmem
c_func
(paren
id|skb-&gt;mem_addr
comma
id|skb-&gt;mem_len
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Allocate a new skbuff. We do this ourselves so we can fill in a few &squot;private&squot;&n; *&t;fields and also do memory statistics to find all the [BEEP] leaks.&n; */
DECL|function|alloc_skb
r_struct
id|sk_buff
op_star
id|alloc_skb
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|intr_count
op_logical_and
id|priority
op_ne
id|GFP_ATOMIC
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;alloc_skb called nonatomically from interrupt %08lx&bslash;n&quot;
comma
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|size
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|priority
op_assign
id|GFP_ATOMIC
suffix:semicolon
)brace
)brace
id|size
op_add_assign
r_sizeof
(paren
r_struct
id|sk_buff
)paren
suffix:semicolon
id|skb
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|priority
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
l_int|NULL
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Invalid so we pick up forgetful users */
id|skb-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
multiline_comment|/* Default type */
id|skb-&gt;truesize
op_assign
id|size
suffix:semicolon
id|skb-&gt;mem_len
op_assign
id|size
suffix:semicolon
id|skb-&gt;mem_addr
op_assign
id|skb
suffix:semicolon
macro_line|#ifdef CONFIG_SLAVE_BALANCING &t;
id|skb-&gt;in_dev_queue
op_assign
l_int|0
suffix:semicolon
macro_line|#endif &t;
id|skb-&gt;fraglist
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;prev
op_assign
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;link3
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;stamp.tv_sec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No idea about time */
id|net_memory
op_add_assign
id|size
suffix:semicolon
id|net_skbcount
op_increment
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
id|skb-&gt;magic_debug_cookie
op_assign
id|SK_GOOD_SKB
suffix:semicolon
macro_line|#endif
id|skb-&gt;users
op_assign
l_int|0
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Free an skbuff by memory&n; */
DECL|function|kfree_skbmem
r_void
id|kfree_skbmem
c_func
(paren
r_void
op_star
id|mem
comma
r_int
id|size
)paren
(brace
macro_line|#ifdef CONFIG_SLAVE_BALANCING
r_struct
id|sk_buff
op_star
id|x
op_assign
id|mem
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
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
id|x-&gt;in_dev_queue
op_logical_and
id|x-&gt;dev
op_ne
l_int|NULL
)paren
(brace
id|x-&gt;dev-&gt;pkt_queue
op_decrement
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#if CONFIG_SKB_CHECK
macro_line|#ifndef CONFIG_SLAVE_BALANCING
r_struct
id|sk_buff
op_star
id|x
op_assign
id|mem
suffix:semicolon
macro_line|#endif&t;
id|IS_SKB
c_func
(paren
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;magic_debug_cookie
op_eq
id|SK_GOOD_SKB
)paren
(brace
id|x-&gt;magic_debug_cookie
op_assign
id|SK_FREED_SKB
suffix:semicolon
id|kfree_s
c_func
(paren
id|mem
comma
id|size
)paren
suffix:semicolon
id|net_skbcount
op_decrement
suffix:semicolon
id|net_memory
op_sub_assign
id|size
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;kfree_skbmem: bad magic cookie&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|kfree_s
c_func
(paren
id|mem
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Duplicate an sk_buff. The new one is not owned by a socket or locked&n; *&t;and will be freed on deletion.&n; */
DECL|function|skb_clone
r_struct
id|sk_buff
op_star
id|skb_clone
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|priority
)paren
(brace
r_struct
id|sk_buff
op_star
id|n
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
id|n
op_assign
id|alloc_skb
c_func
(paren
id|skb-&gt;mem_len
op_minus
r_sizeof
(paren
r_struct
id|sk_buff
)paren
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|offset
op_assign
(paren
(paren
r_char
op_star
)paren
id|n
)paren
op_minus
(paren
(paren
r_char
op_star
)paren
id|skb
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|n-&gt;data
comma
id|skb-&gt;data
comma
id|skb-&gt;mem_len
op_minus
r_sizeof
(paren
r_struct
id|sk_buff
)paren
)paren
suffix:semicolon
id|n-&gt;len
op_assign
id|skb-&gt;len
suffix:semicolon
id|n-&gt;link3
op_assign
l_int|NULL
suffix:semicolon
id|n-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
id|n-&gt;when
op_assign
id|skb-&gt;when
suffix:semicolon
id|n-&gt;dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|n-&gt;h.raw
op_assign
id|skb-&gt;h.raw
op_plus
id|offset
suffix:semicolon
id|n-&gt;ip_hdr
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|skb-&gt;ip_hdr
)paren
op_plus
id|offset
)paren
suffix:semicolon
id|n-&gt;fraglen
op_assign
id|skb-&gt;fraglen
suffix:semicolon
id|n-&gt;fraglist
op_assign
id|skb-&gt;fraglist
suffix:semicolon
id|n-&gt;saddr
op_assign
id|skb-&gt;saddr
suffix:semicolon
id|n-&gt;daddr
op_assign
id|skb-&gt;daddr
suffix:semicolon
id|n-&gt;raddr
op_assign
id|skb-&gt;raddr
suffix:semicolon
id|n-&gt;acked
op_assign
id|skb-&gt;acked
suffix:semicolon
id|n-&gt;used
op_assign
id|skb-&gt;used
suffix:semicolon
id|n-&gt;free
op_assign
l_int|1
suffix:semicolon
id|n-&gt;arp
op_assign
id|skb-&gt;arp
suffix:semicolon
id|n-&gt;tries
op_assign
l_int|0
suffix:semicolon
id|n-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|n-&gt;users
op_assign
l_int|0
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; *     Skbuff device locking&n; */
DECL|function|skb_kept_by_device
r_void
id|skb_kept_by_device
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|skb-&gt;lock
op_increment
suffix:semicolon
)brace
DECL|function|skb_device_release
r_void
id|skb_device_release
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
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
op_logical_neg
op_decrement
id|skb-&gt;lock
op_logical_and
id|skb-&gt;free
op_eq
l_int|1
)paren
id|kfree_skb
c_func
(paren
id|skb
comma
id|mode
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|skb_device_locked
r_int
id|skb_device_locked
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|skb-&gt;lock
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
