multiline_comment|/*&n; *&t;NET/ROM release 003&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 1.2.1 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;NET/ROM 001&t;Jonathan(G4KLX)&t;Cloned from ax25_subr.c&n; *&t;NET/ROM&t;003&t;Jonathan(G4KLX)&t;Added G8BPQ NET/ROM extensions.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NETROM
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
multiline_comment|/*&n; *&t;This routine purges all of the queues of frames.&n; */
DECL|function|nr_clear_queues
r_void
id|nr_clear_queues
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;ack_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;reseq_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;frag_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|nr_frames_acked
r_void
id|nr_frames_acked
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|nr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;va
op_ne
id|nr
)paren
(brace
r_while
c_loop
(paren
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;ack_queue
)paren
op_ne
l_int|NULL
op_logical_and
id|sk-&gt;nr-&gt;va
op_ne
id|nr
)paren
(brace
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;ack_queue
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|sk-&gt;nr-&gt;va
op_assign
(paren
id|sk-&gt;nr-&gt;va
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Requeue all the un-ack-ed frames on the output queue to be picked&n; * up by nr_kick called from the timer. This arrangement handles the&n; * possibility of an empty output queue.&n; */
DECL|function|nr_requeue_frames
r_void
id|nr_requeue_frames
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skb_prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;nr-&gt;ack_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|skb_prev
op_eq
l_int|NULL
)paren
id|skb_queue_head
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_else
id|skb_append
c_func
(paren
id|skb_prev
comma
id|skb
)paren
suffix:semicolon
id|skb_prev
op_assign
id|skb
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Validate that the value of nr is between va and vs. Return true or&n; *&t;false for testing.&n; */
DECL|function|nr_validate_nr
r_int
id|nr_validate_nr
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|vc
op_assign
id|sk-&gt;nr-&gt;va
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|sk-&gt;nr-&gt;vs
)paren
(brace
r_if
c_cond
(paren
id|nr
op_eq
id|vc
)paren
r_return
l_int|1
suffix:semicolon
id|vc
op_assign
(paren
id|vc
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_eq
id|sk-&gt;nr-&gt;vs
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check that ns is within the receive window.&n; */
DECL|function|nr_in_rx_window
r_int
id|nr_in_rx_window
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|ns
)paren
(brace
r_int
r_int
id|vc
op_assign
id|sk-&gt;nr-&gt;vr
suffix:semicolon
r_int
r_int
id|vt
op_assign
(paren
id|sk-&gt;nr-&gt;vl
op_plus
id|sk-&gt;window
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|vt
)paren
(brace
r_if
c_cond
(paren
id|ns
op_eq
id|vc
)paren
r_return
l_int|1
suffix:semicolon
id|vc
op_assign
(paren
id|vc
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; *  This routine is called when the HDLC layer internally generates a&n; *  control frame.&n; */
DECL|function|nr_write_internal
r_void
id|nr_write_internal
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|frametype
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_int
id|len
comma
id|timeout
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
op_amp
l_int|0x0F
)paren
(brace
r_case
id|NR_CONNREQ
suffix:colon
id|len
op_add_assign
l_int|17
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_CONNACK
suffix:colon
id|len
op_add_assign
(paren
id|sk-&gt;nr-&gt;bpqext
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
r_case
id|NR_DISCACK
suffix:colon
r_case
id|NR_INFOACK
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nr_write_internal: invalid frame type %d&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Space for AX.25 and NET/ROM network header&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|NR_NETWORK_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
op_amp
l_int|0x0F
)paren
(brace
r_case
id|NR_CONNREQ
suffix:colon
id|timeout
op_assign
(paren
id|sk-&gt;nr-&gt;rtt
op_div
id|PR_SLOWHZ
)paren
op_star
l_int|2
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;my_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;my_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;window
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|sk-&gt;nr-&gt;user_addr
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_C
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_E
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|sk-&gt;nr-&gt;source_addr
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_C
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_E
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|timeout
op_mod
l_int|256
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|timeout
op_div
l_int|256
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_CONNACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;my_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;my_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;window
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;bpqext
)paren
op_star
id|dptr
op_increment
op_assign
id|nr_default.ttl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
r_case
id|NR_DISCACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_INFOACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sk-&gt;nr-&gt;vr
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|nr_transmit_buffer
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when a Connect Acknowledge with the Choke Flag&n; * set is needed to refuse a connection.&n; */
DECL|function|nr_transmit_dm
r_void
id|nr_transmit_dm
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skbn
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skbn
comma
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|skb-&gt;data
op_plus
l_int|7
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_C
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_E
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|skb-&gt;data
op_plus
l_int|0
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|LAPB_C
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|LAPB_E
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr_default.ttl
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|15
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|16
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|NR_CONNACK
op_or
id|NR_CHOKE_FLAG
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
id|skbn-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skbn-&gt;sk
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_route_frame
c_func
(paren
id|skbn
comma
l_int|NULL
)paren
)paren
id|kfree_skb
c_func
(paren
id|skbn
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Exponential backoff for NET/ROM&n; */
DECL|function|nr_calculate_t1
r_int
r_int
id|nr_calculate_t1
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|n
comma
id|t
suffix:semicolon
r_for
c_loop
(paren
id|t
op_assign
l_int|2
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|sk-&gt;nr-&gt;n2count
suffix:semicolon
id|n
op_increment
)paren
id|t
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
l_int|8
)paren
id|t
op_assign
l_int|8
suffix:semicolon
r_return
id|t
op_star
id|sk-&gt;nr-&gt;rtt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Calculate the Round Trip Time&n; */
DECL|function|nr_calculate_rtt
r_void
id|nr_calculate_rtt
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;t1timer
OG
l_int|0
op_logical_and
id|sk-&gt;nr-&gt;n2count
op_eq
l_int|0
)paren
id|sk-&gt;nr-&gt;rtt
op_assign
(paren
l_int|9
op_star
id|sk-&gt;nr-&gt;rtt
op_plus
id|sk-&gt;nr-&gt;t1
op_minus
id|sk-&gt;nr-&gt;t1timer
)paren
op_div
l_int|10
suffix:semicolon
macro_line|#ifdef&t;NR_T1CLAMPLO
multiline_comment|/* Don&squot;t go below one tenth of a second */
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;rtt
OL
(paren
id|NR_T1CLAMPLO
)paren
)paren
id|sk-&gt;nr-&gt;rtt
op_assign
(paren
id|NR_T1CLAMPLO
)paren
suffix:semicolon
macro_line|#else   /* Failsafe - some people might have sub 1/10th RTTs :-) **/
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;rtt
op_eq
l_int|0
)paren
id|sk-&gt;nr-&gt;rtt
op_assign
id|PR_SLOWHZ
suffix:semicolon
macro_line|#endif
macro_line|#ifdef  NR_T1CLAMPHI
multiline_comment|/* OR above clamped seconds **/
r_if
c_cond
(paren
id|sk-&gt;nr-&gt;rtt
OG
(paren
id|NR_T1CLAMPHI
)paren
)paren
id|sk-&gt;nr-&gt;rtt
op_assign
(paren
id|NR_T1CLAMPHI
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof
