multiline_comment|/*&n; *&t;Definitions for the &squot;struct sk_buff&squot; memory handlers.&n; *&n; *&t;Authors:&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&t;&t;Florian La Roche, &lt;rzsfl@rz.uni-sb.de&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_SKBUFF_H
DECL|macro|_LINUX_SKBUFF_H
mdefine_line|#define _LINUX_SKBUFF_H
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CONFIG_SKB_CHECK
macro_line|#undef CONFIG_SKB_CHECK
DECL|macro|HAVE_ALLOC_SKB
mdefine_line|#define HAVE_ALLOC_SKB&t;&t;/* For the drivers to know */
DECL|macro|FREE_READ
mdefine_line|#define FREE_READ&t;1
DECL|macro|FREE_WRITE
mdefine_line|#define FREE_WRITE&t;0
DECL|struct|sk_buff_head
r_struct
id|sk_buff_head
(brace
DECL|member|next
r_struct
id|sk_buff
op_star
r_volatile
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|sk_buff
op_star
r_volatile
id|prev
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
DECL|member|magic_debug_cookie
r_int
id|magic_debug_cookie
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|sk_buff
r_struct
id|sk_buff
(brace
DECL|member|next
r_struct
id|sk_buff
op_star
r_volatile
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|sk_buff
op_star
r_volatile
id|prev
suffix:semicolon
macro_line|#if CONFIG_SKB_CHECK
DECL|member|magic_debug_cookie
r_int
id|magic_debug_cookie
suffix:semicolon
macro_line|#endif
DECL|member|link3
r_struct
id|sk_buff
op_star
r_volatile
id|link3
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|when
r_volatile
r_int
r_int
id|when
suffix:semicolon
multiline_comment|/* used to compute rtt&squot;s&t;*/
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|mem_addr
r_struct
id|sk_buff
op_star
id|mem_addr
suffix:semicolon
r_union
(brace
DECL|member|th
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
DECL|member|eth
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
DECL|member|iph
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
DECL|member|uh
r_struct
id|udphdr
op_star
id|uh
suffix:semicolon
DECL|member|raw
r_int
r_char
op_star
id|raw
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
DECL|member|h
)brace
id|h
suffix:semicolon
DECL|member|ip_hdr
r_struct
id|iphdr
op_star
id|ip_hdr
suffix:semicolon
multiline_comment|/* For IPPROTO_RAW */
DECL|member|mem_len
r_int
r_int
id|mem_len
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|fraglen
r_int
r_int
id|fraglen
suffix:semicolon
DECL|member|fraglist
r_struct
id|sk_buff
op_star
id|fraglist
suffix:semicolon
multiline_comment|/* Fragment list */
DECL|member|truesize
r_int
r_int
id|truesize
suffix:semicolon
DECL|member|saddr
r_int
r_int
id|saddr
suffix:semicolon
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
DECL|member|raddr
r_int
r_int
id|raddr
suffix:semicolon
multiline_comment|/* next hop addr */
DECL|member|acked
r_volatile
r_char
id|acked
comma
DECL|member|used
id|used
comma
DECL|member|free
id|free
comma
DECL|member|arp
id|arp
suffix:semicolon
DECL|member|tries
DECL|member|lock
DECL|member|localroute
DECL|member|pkt_type
r_int
r_char
id|tries
comma
id|lock
comma
id|localroute
comma
id|pkt_type
suffix:semicolon
DECL|macro|PACKET_HOST
mdefine_line|#define PACKET_HOST&t;&t;0&t;&t;/* To us */
DECL|macro|PACKET_BROADCAST
mdefine_line|#define PACKET_BROADCAST&t;1
DECL|macro|PACKET_MULTICAST
mdefine_line|#define PACKET_MULTICAST&t;2
DECL|macro|PACKET_OTHERHOST
mdefine_line|#define PACKET_OTHERHOST&t;3&t;&t;/* Unmatched promiscuous */
DECL|member|users
r_int
r_int
id|users
suffix:semicolon
multiline_comment|/* User count - see datagram.c (and soon seqpacket.c/stream.c) */
macro_line|#ifdef CONFIG_SLAVE_BALANCING
DECL|member|in_dev_queue
r_int
r_int
id|in_dev_queue
suffix:semicolon
macro_line|#endif  
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SK_WMEM_MAX
mdefine_line|#define SK_WMEM_MAX&t;32767
DECL|macro|SK_RMEM_MAX
mdefine_line|#define SK_RMEM_MAX&t;32767
macro_line|#ifdef CONFIG_SKB_CHECK
DECL|macro|SK_FREED_SKB
mdefine_line|#define SK_FREED_SKB&t;0x0DE2C0DE
DECL|macro|SK_GOOD_SKB
mdefine_line|#define SK_GOOD_SKB&t;0xDEC0DED1
DECL|macro|SK_HEAD_SKB
mdefine_line|#define SK_HEAD_SKB&t;0x12231298
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;Handling routines are only of interest to the kernel&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#if 0
r_extern
r_void
id|print_skb
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
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
suffix:semicolon
r_extern
r_void
id|skb_queue_head_init
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
suffix:semicolon
r_extern
r_void
id|skb_queue_head
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
comma
r_struct
id|sk_buff
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|skb_queue_tail
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
comma
r_struct
id|sk_buff
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|skb_dequeue
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|skb_unlink
c_func
(paren
r_struct
id|sk_buff
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|skb_peek_copy
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|kfree_skbmem
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|skb_device_lock
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|skb_device_unlock
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|dev_kfree_skb
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
suffix:semicolon
r_extern
r_int
id|skb_device_locked
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Peek an sk_buff. Unlike most other operations you _MUST_&n; *&t;be careful with this one. A peek leaves the buffer on the&n; *&t;list and someone else may run off with it. For an interrupt&n; *&t;type system cli() peek the buffer copy the data and sti();&n; */
DECL|function|skb_peek
r_static
id|__inline__
r_struct
id|sk_buff
op_star
id|skb_peek
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
r_return
(paren
id|list-&gt;next
op_ne
id|list
)paren
ques
c_cond
id|list-&gt;next
suffix:colon
l_int|NULL
suffix:semicolon
)brace
macro_line|#if CONFIG_SKB_CHECK
r_extern
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
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
DECL|macro|IS_SKB
mdefine_line|#define IS_SKB(skb)&t;&t;skb_check((skb), 0, __LINE__,__FILE__)
DECL|macro|IS_SKB_HEAD
mdefine_line|#define IS_SKB_HEAD(skb)&t;skb_check((skb), 1, __LINE__,__FILE__)
macro_line|#else
DECL|macro|IS_SKB
mdefine_line|#define IS_SKB(skb)&t;&t;
DECL|macro|IS_SKB_HEAD
mdefine_line|#define IS_SKB_HEAD(skb)&t;
DECL|function|skb_queue_head_init
r_extern
id|__inline__
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
)brace
multiline_comment|/*&n; *&t;Insert an sk_buff at the start of a list.&n; */
DECL|function|skb_queue_head
r_extern
id|__inline__
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
r_extern
id|__inline__
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
r_extern
id|__inline__
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
r_extern
id|__inline__
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
r_extern
id|__inline__
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
r_extern
id|__inline__
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
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_struct
id|sk_buff
op_star
id|skb_recv_datagram
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
comma
r_int
id|noblock
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_extern
r_int
id|datagram_select
c_func
(paren
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
r_extern
r_void
id|skb_copy_datagram
c_func
(paren
r_struct
id|sk_buff
op_star
id|from
comma
r_int
id|offset
comma
r_char
op_star
id|to
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|skb_free_datagram
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_SKBUFF_H */
eof
