multiline_comment|/*&n; *&t;Definitions for the &squot;struct sk_buff&squot; memory handlers.&n; *&n; *&t;Authors:&n; *&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&t;&t;Florian La Roche, &lt;rzsfl@rz.uni-sb.de&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_SKBUFF_H
DECL|macro|_LINUX_SKBUFF_H
mdefine_line|#define _LINUX_SKBUFF_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|CONFIG_SKB_CHECK
mdefine_line|#define CONFIG_SKB_CHECK 0
DECL|macro|HAVE_ALLOC_SKB
mdefine_line|#define HAVE_ALLOC_SKB&t;&t;/* For the drivers to know */
DECL|macro|HAVE_ALIGNABLE_SKB
mdefine_line|#define HAVE_ALIGNABLE_SKB&t;/* Ditto 8)&t;&t;   */
DECL|macro|FREE_READ
mdefine_line|#define FREE_READ&t;1
DECL|macro|FREE_WRITE
mdefine_line|#define FREE_WRITE&t;0
DECL|macro|CHECKSUM_NONE
mdefine_line|#define CHECKSUM_NONE 0
DECL|macro|CHECKSUM_HW
mdefine_line|#define CHECKSUM_HW 1
DECL|macro|CHECKSUM_UNNECESSARY
mdefine_line|#define CHECKSUM_UNNECESSARY 2
DECL|struct|sk_buff_head
r_struct
id|sk_buff_head
(brace
DECL|member|next
r_struct
id|sk_buff
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|sk_buff
op_star
id|prev
suffix:semicolon
DECL|member|qlen
id|__u32
id|qlen
suffix:semicolon
multiline_comment|/* Must be same length as a pointer&n;&t;&t;&t;&t;&t;   for using debugging */
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
id|next
suffix:semicolon
multiline_comment|/* Next buffer in list &t;&t;&t;&t;*/
DECL|member|prev
r_struct
id|sk_buff
op_star
id|prev
suffix:semicolon
multiline_comment|/* Previous buffer in list &t;&t;&t;*/
DECL|member|list
r_struct
id|sk_buff_head
op_star
id|list
suffix:semicolon
multiline_comment|/* List we are on&t;&t;&t;&t;*/
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
id|link3
suffix:semicolon
multiline_comment|/* Link for IP protocol level buffer chains &t;*/
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Socket we are owned by &t;&t;&t;*/
DECL|member|when
r_int
r_int
id|when
suffix:semicolon
multiline_comment|/* used to compute rtt&squot;s&t;&t;&t;*/
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
multiline_comment|/* Time we arrived&t;&t;&t;&t;*/
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device we arrived on/are leaving by&t;&t;*/
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
multiline_comment|/* for passing file handles in a unix domain socket */
DECL|member|filp
r_void
op_star
id|filp
suffix:semicolon
DECL|member|h
)brace
id|h
suffix:semicolon
r_union
(brace
multiline_comment|/* As yet incomplete physical layer views */
DECL|member|raw
r_int
r_char
op_star
id|raw
suffix:semicolon
DECL|member|ethernet
r_struct
id|ethhdr
op_star
id|ethernet
suffix:semicolon
DECL|member|mac
)brace
id|mac
suffix:semicolon
DECL|member|ip_hdr
r_struct
id|iphdr
op_star
id|ip_hdr
suffix:semicolon
multiline_comment|/* For IPPROTO_RAW &t;&t;&t;&t;*/
macro_line|#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
DECL|member|ipv6_hdr
r_struct
id|ipv6hdr
op_star
id|ipv6_hdr
suffix:semicolon
multiline_comment|/* &n;&t; *&t;It would be inefficient to store the nexthop address in every&n;&t; *&t;skb. Instead we store a pointer to the respective neighbour&n;&t; *&t;cache entry. This might make ndisc cache management harder.&n;&t; */
DECL|member|nexthop
r_struct
id|neighbour
op_star
id|nexthop
suffix:semicolon
macro_line|#endif&t;&t;
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of actual data&t;&t;&t;*/
DECL|member|csum
r_int
r_int
id|csum
suffix:semicolon
multiline_comment|/* Checksum &t;&t;&t;&t;&t;*/
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* IP source address&t;&t;&t;&t;*/
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* IP target address&t;&t;&t;&t;*/
DECL|member|raddr
id|__u32
id|raddr
suffix:semicolon
multiline_comment|/* IP next hop address&t;&t;&t;&t;*/
DECL|member|seq
id|__u32
id|seq
suffix:semicolon
multiline_comment|/* TCP sequence number&t;&t;&t;&t;*/
DECL|member|end_seq
id|__u32
id|end_seq
suffix:semicolon
multiline_comment|/* seq [+ fin] [+ syn] + datalen&t;&t;*/
DECL|member|ack_seq
id|__u32
id|ack_seq
suffix:semicolon
multiline_comment|/* TCP ack sequence number&t;&t;&t;*/
DECL|member|proto_priv
r_int
r_char
id|proto_priv
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Protocol private data&t;&t;&t;*/
DECL|member|acked
r_volatile
r_char
id|acked
comma
multiline_comment|/* Are we acked ?&t;&t;&t;&t;*/
DECL|member|used
id|used
comma
multiline_comment|/* Are we in use ?&t;&t;&t;&t;*/
DECL|member|free
id|free
comma
multiline_comment|/* How to free this buffer&t;&t;&t;*/
DECL|member|arp
id|arp
suffix:semicolon
multiline_comment|/* Has IP/ARP resolution finished&t;&t;*/
DECL|member|tries
r_int
r_char
id|tries
comma
multiline_comment|/* Times tried&t;&t;&t;&t;&t;*/
DECL|member|lock
id|lock
comma
multiline_comment|/* Are we locked ?&t;&t;&t;&t;*/
DECL|member|localroute
id|localroute
comma
multiline_comment|/* Local routing asserted for this frame&t;*/
DECL|member|pkt_type
id|pkt_type
comma
multiline_comment|/* Packet class&t;&t;&t;&t;&t;*/
DECL|member|pkt_bridged
id|pkt_bridged
comma
multiline_comment|/* Tracker for bridging &t;&t;&t;*/
DECL|member|ip_summed
id|ip_summed
suffix:semicolon
multiline_comment|/* Driver fed us an IP checksum&t;&t;&t;*/
DECL|macro|PACKET_HOST
mdefine_line|#define PACKET_HOST&t;&t;0&t;&t;/* To us&t;&t;&t;&t;&t;*/
DECL|macro|PACKET_BROADCAST
mdefine_line|#define PACKET_BROADCAST&t;1&t;&t;/* To all&t;&t;&t;&t;&t;*/
DECL|macro|PACKET_MULTICAST
mdefine_line|#define PACKET_MULTICAST&t;2&t;&t;/* To group&t;&t;&t;&t;&t;*/
DECL|macro|PACKET_OTHERHOST
mdefine_line|#define PACKET_OTHERHOST&t;3&t;&t;/* To someone else &t;&t;&t;&t;*/
DECL|macro|PACKET_NDISC
mdefine_line|#define PACKET_NDISC&t;&t;17&t;&t;/* Outgoing NDISC packet&t;&t;&t;*/
DECL|member|users
r_int
r_int
id|users
suffix:semicolon
multiline_comment|/* User count - see datagram.c,tcp.c &t;&t;*/
DECL|member|protocol
r_int
r_int
id|protocol
suffix:semicolon
multiline_comment|/* Packet protocol from driver. &t;&t;*/
DECL|member|truesize
r_int
r_int
id|truesize
suffix:semicolon
multiline_comment|/* Buffer size &t;&t;&t;&t;&t;*/
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* reference count&t;&t;&t;&t;*/
DECL|member|data_skb
r_struct
id|sk_buff
op_star
id|data_skb
suffix:semicolon
multiline_comment|/* Link to the actual data skb&t;&t;&t;*/
DECL|member|head
r_int
r_char
op_star
id|head
suffix:semicolon
multiline_comment|/* Head of buffer &t;&t;&t;&t;*/
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Data head pointer&t;&t;&t;&t;*/
DECL|member|tail
r_int
r_char
op_star
id|tail
suffix:semicolon
multiline_comment|/* Tail pointer&t;&t;&t;&t;&t;*/
DECL|member|end
r_int
r_char
op_star
id|end
suffix:semicolon
multiline_comment|/* End pointer&t;&t;&t;&t;&t;*/
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Destruct function&t;&t;*/
DECL|member|redirport
id|__u16
id|redirport
suffix:semicolon
multiline_comment|/* Redirect port&t;&t;&t;&t;*/
DECL|member|inclone
id|__u16
id|inclone
suffix:semicolon
multiline_comment|/* Inline clone&t;*/
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SKB_LARGE
DECL|macro|SK_WMEM_MAX
mdefine_line|#define SK_WMEM_MAX&t;65535
DECL|macro|SK_RMEM_MAX
mdefine_line|#define SK_RMEM_MAX&t;65535
macro_line|#else
DECL|macro|SK_WMEM_MAX
mdefine_line|#define SK_WMEM_MAX&t;32767
DECL|macro|SK_RMEM_MAX
mdefine_line|#define SK_RMEM_MAX&t;32767
macro_line|#endif
macro_line|#if CONFIG_SKB_CHECK
DECL|macro|SK_FREED_SKB
mdefine_line|#define SK_FREED_SKB&t;0x0DE2C0DE
DECL|macro|SK_GOOD_SKB
mdefine_line|#define SK_GOOD_SKB&t;0xDEC0DED1
DECL|macro|SK_HEAD_SKB
mdefine_line|#define SK_HEAD_SKB&t;0x12231298
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;Handling routines are only of interest to the kernel&n; */
macro_line|#include &lt;linux/malloc.h&gt;
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
id|__u32
id|skb_queue_len
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
r_struct
id|sk_buff
op_star
id|dev_alloc_skb
c_func
(paren
r_int
r_int
id|size
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
r_struct
id|sk_buff
op_star
id|skb_copy
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
r_extern
r_int
r_char
op_star
id|skb_put
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|skb_push
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|skb_pull
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|skb_headroom
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|skb_tailroom
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
id|skb_reserve
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|skb_trim
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
suffix:semicolon
DECL|function|skb_queue_empty
r_extern
id|__inline__
r_int
id|skb_queue_empty
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
(brace
r_return
(paren
id|list-&gt;next
op_eq
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Peek an sk_buff. Unlike most other operations you _MUST_&n; *&t;be careful with this one. A peek leaves the buffer on the&n; *&t;list and someone else may run off with it. For an interrupt&n; *&t;type system cli() peek the buffer copy the data and sti();&n; */
DECL|function|skb_peek
r_extern
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
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
(paren
r_struct
id|sk_buff
op_star
)paren
id|list_
)paren
id|list
op_assign
l_int|NULL
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Return the length of an sk_buff queue&n; */
DECL|function|skb_queue_len
r_extern
id|__inline__
id|__u32
id|skb_queue_len
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list_
)paren
(brace
r_return
id|list_-&gt;qlen
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
id|list-&gt;qlen
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Insert an sk_buff at the start of a list.&n; *&n; *&t;The &quot;__skb_xxxx()&quot; functions are the non-atomic ones that&n; *&t;can only be called with interrupts disabled.&n; */
DECL|function|__skb_queue_head
r_extern
id|__inline__
r_void
id|__skb_queue_head
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
id|newsk
)paren
(brace
r_struct
id|sk_buff
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
id|newsk-&gt;list
op_assign
id|list
suffix:semicolon
id|list-&gt;qlen
op_increment
suffix:semicolon
id|prev
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
suffix:semicolon
id|next
op_assign
id|prev-&gt;next
suffix:semicolon
id|newsk-&gt;next
op_assign
id|next
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|prev
suffix:semicolon
id|next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|prev-&gt;next
op_assign
id|newsk
suffix:semicolon
)brace
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
id|list
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
id|__skb_queue_head
c_func
(paren
id|list
comma
id|newsk
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Insert an sk_buff at the end of a list.&n; */
DECL|function|__skb_queue_tail
r_extern
id|__inline__
r_void
id|__skb_queue_tail
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
id|newsk
)paren
(brace
r_struct
id|sk_buff
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
id|newsk-&gt;list
op_assign
id|list
suffix:semicolon
id|list-&gt;qlen
op_increment
suffix:semicolon
id|next
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
suffix:semicolon
id|prev
op_assign
id|next-&gt;prev
suffix:semicolon
id|newsk-&gt;next
op_assign
id|next
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|prev
suffix:semicolon
id|next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|prev-&gt;next
op_assign
id|newsk
suffix:semicolon
)brace
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
id|list
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
id|__skb_queue_tail
c_func
(paren
id|list
comma
id|newsk
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove an sk_buff from a list.&n; */
DECL|function|__skb_dequeue
r_extern
id|__inline__
r_struct
id|sk_buff
op_star
id|__skb_dequeue
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|list
)paren
(brace
r_struct
id|sk_buff
op_star
id|next
comma
op_star
id|prev
comma
op_star
id|result
suffix:semicolon
id|prev
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|list
suffix:semicolon
id|next
op_assign
id|prev-&gt;next
suffix:semicolon
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
id|prev
)paren
(brace
id|result
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
id|list-&gt;qlen
op_decrement
suffix:semicolon
id|next-&gt;prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
id|result-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;list
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
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
id|list
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
id|__skb_dequeue
c_func
(paren
id|list
)paren
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
multiline_comment|/*&n; *&t;Insert a packet on a list.&n; */
DECL|function|__skb_insert
r_extern
id|__inline__
r_void
id|__skb_insert
c_func
(paren
r_struct
id|sk_buff
op_star
id|newsk
comma
r_struct
id|sk_buff
op_star
id|prev
comma
r_struct
id|sk_buff
op_star
id|next
comma
r_struct
id|sk_buff_head
op_star
id|list
)paren
(brace
id|newsk-&gt;next
op_assign
id|next
suffix:semicolon
id|newsk-&gt;prev
op_assign
id|prev
suffix:semicolon
id|next-&gt;prev
op_assign
id|newsk
suffix:semicolon
id|prev-&gt;next
op_assign
id|newsk
suffix:semicolon
id|newsk-&gt;list
op_assign
id|list
suffix:semicolon
id|list-&gt;qlen
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Place a packet before a given packet in a list&n; */
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
id|__skb_insert
c_func
(paren
id|newsk
comma
id|old-&gt;prev
comma
id|old
comma
id|old-&gt;list
)paren
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
id|__skb_insert
c_func
(paren
id|newsk
comma
id|old
comma
id|old-&gt;next
comma
id|old-&gt;list
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove sk_buff from list. _Must_ be called atomically, and with&n; * the list known..&n; */
DECL|function|__skb_unlink
r_extern
id|__inline__
r_void
id|__skb_unlink
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff_head
op_star
id|list
)paren
(brace
r_struct
id|sk_buff
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
id|list-&gt;qlen
op_decrement
suffix:semicolon
id|next
op_assign
id|skb-&gt;next
suffix:semicolon
id|prev
op_assign
id|skb-&gt;prev
suffix:semicolon
id|skb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;list
op_assign
l_int|NULL
suffix:semicolon
id|next-&gt;prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|next
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
id|skb-&gt;list
)paren
(brace
id|__skb_unlink
c_func
(paren
id|skb
comma
id|skb-&gt;list
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Add data to an sk_buff&n; */
DECL|function|skb_put
r_extern
id|__inline__
r_int
r_char
op_star
id|skb_put
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|tmp
op_assign
id|skb-&gt;tail
suffix:semicolon
id|skb-&gt;tail
op_add_assign
id|len
suffix:semicolon
id|skb-&gt;len
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;tail
OG
id|skb-&gt;end
)paren
(brace
id|__label__
id|here
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;skput:over: %p:%d&quot;
comma
op_logical_and
id|here
comma
id|len
)paren
suffix:semicolon
id|here
suffix:colon
)brace
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|skb_push
r_extern
id|__inline__
r_int
r_char
op_star
id|skb_push
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
(brace
id|skb-&gt;data
op_sub_assign
id|len
suffix:semicolon
id|skb-&gt;len
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
OL
id|skb-&gt;head
)paren
(brace
id|__label__
id|here
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;skpush:under: %p:%d&quot;
comma
op_logical_and
id|here
comma
id|len
)paren
suffix:semicolon
id|here
suffix:colon
)brace
r_return
id|skb-&gt;data
suffix:semicolon
)brace
DECL|function|skb_pull
r_extern
id|__inline__
r_int
r_char
op_star
id|skb_pull
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
OG
id|skb-&gt;len
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|skb-&gt;data
op_add_assign
id|len
suffix:semicolon
id|skb-&gt;len
op_sub_assign
id|len
suffix:semicolon
r_return
id|skb-&gt;data
suffix:semicolon
)brace
DECL|function|skb_headroom
r_extern
id|__inline__
r_int
id|skb_headroom
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|skb-&gt;data
op_minus
id|skb-&gt;head
suffix:semicolon
)brace
DECL|function|skb_tailroom
r_extern
id|__inline__
r_int
id|skb_tailroom
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|skb-&gt;end
op_minus
id|skb-&gt;tail
suffix:semicolon
)brace
DECL|function|skb_reserve
r_extern
id|__inline__
r_void
id|skb_reserve
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
(brace
id|skb-&gt;data
op_add_assign
id|len
suffix:semicolon
id|skb-&gt;tail
op_add_assign
id|len
suffix:semicolon
)brace
DECL|function|skb_trim
r_extern
id|__inline__
r_void
id|skb_trim
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|len
)paren
(brace
id|skb-&gt;len
op_assign
id|len
suffix:semicolon
id|skb-&gt;tail
op_assign
id|skb-&gt;data
op_plus
id|len
suffix:semicolon
)brace
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
id|skb_copy_datagram_iovec
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
r_struct
id|iovec
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
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_SKBUFF_H */
eof
