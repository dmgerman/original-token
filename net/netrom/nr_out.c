multiline_comment|/*&n; *&t;NET/ROM release 006&n; *&n; *&t;This is ALPHA test software. This code may break your machine, randomly fail to work with new &n; *&t;releases, misbehave and/or generally screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;NET/ROM 001&t;Jonathan(G4KLX)&t;Cloned from ax25_out.c&n; *&t;NET/ROM 003&t;Jonathan(G4KLX)&t;Added NET/ROM fragmentation.&n; *&t;&t;&t;Darryl(G7LED)&t;Fixed NAK, to give out correct reponse.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_NETROM) || defined(CONFIG_NETROM_MODULE)
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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
multiline_comment|/*&n; *&t;This is where all NET/ROM frames pass, except for IP-over-NET/ROM which&n; *&t;cannot be fragmented in this manner.&n; */
DECL|function|nr_output
r_void
id|nr_output
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
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
id|transport
(braket
id|NR_TRANSPORT_LEN
)braket
suffix:semicolon
r_int
id|err
comma
id|frontlen
comma
id|len
comma
id|mtu
suffix:semicolon
id|mtu
op_assign
id|sk-&gt;protinfo.nr-&gt;paclen
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_minus
id|NR_TRANSPORT_LEN
OG
id|mtu
)paren
(brace
multiline_comment|/* Save a copy of the Transport Header */
id|memcpy
c_func
(paren
id|transport
comma
id|skb-&gt;data
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|frontlen
op_assign
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|frontlen
op_plus
id|mtu
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skbn-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skbn-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
)paren
suffix:semicolon
id|len
op_assign
(paren
id|mtu
OG
id|skb-&gt;len
)paren
ques
c_cond
id|skb-&gt;len
suffix:colon
id|mtu
suffix:semicolon
multiline_comment|/* Copy the user data */
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|len
)paren
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Duplicate the Transport Header */
id|skb_push
c_func
(paren
id|skbn
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skbn-&gt;data
comma
id|transport
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
l_int|0
)paren
id|skbn-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_MORE_FLAG
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skbn
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;state
op_eq
id|NR_STATE_3
)paren
id|nr_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;This procedure is passed a buffer descriptor for an iframe. It builds&n; *&t;the rest of the control part of the frame and then writes it out.&n; */
DECL|function|nr_send_iframe
r_static
r_void
id|nr_send_iframe
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
(brace
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_assign
id|sk-&gt;protinfo.nr-&gt;vs
suffix:semicolon
id|skb-&gt;data
(braket
l_int|3
)braket
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
id|skb-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_CHOKE_FLAG
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
DECL|function|nr_send_nak_frame
r_void
id|nr_send_nak_frame
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
id|skbn
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;protinfo.nr-&gt;ack_queue
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skbn-&gt;data
(braket
l_int|2
)braket
op_assign
id|sk-&gt;protinfo.nr-&gt;va
suffix:semicolon
id|skbn-&gt;data
(braket
l_int|3
)braket
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
id|skbn-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_CHOKE_FLAG
suffix:semicolon
id|nr_transmit_buffer
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;vl
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|nr_kick
r_void
id|nr_kick
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
id|skbn
suffix:semicolon
r_int
id|last
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|start
comma
id|end
comma
id|next
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|start
op_assign
(paren
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;protinfo.nr-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|sk-&gt;protinfo.nr-&gt;va
suffix:colon
id|sk-&gt;protinfo.nr-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|sk-&gt;protinfo.nr-&gt;va
op_plus
id|sk-&gt;protinfo.nr-&gt;window
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|PEER_RX_BUSY_CONDITION
)paren
op_logical_and
id|start
op_ne
id|end
op_logical_and
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Transmit data until either we&squot;re out of data to send or&n;&t;&t; * the window is full.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Dequeue the frame and copy it.&n;&t;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|sk-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|next
op_assign
(paren
id|sk-&gt;protinfo.nr-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
id|last
op_assign
(paren
id|next
op_eq
id|end
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Transmit the frame copy.&n;&t;&t;&t; */
id|nr_send_iframe
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;vs
op_assign
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Requeue the original data frame.&n;&t;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;protinfo.nr-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|last
op_logical_and
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
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;vl
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;t1timer
op_eq
l_int|0
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
id|sk-&gt;protinfo.nr-&gt;t1
op_assign
id|nr_calculate_t1
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
id|nr_set_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|nr_transmit_buffer
r_void
id|nr_transmit_buffer
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
(brace
r_int
r_char
op_star
id|dptr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add the protocol byte and network header.&n;&t; */
id|dptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|NR_NETWORK_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|sk-&gt;protinfo.nr-&gt;source_addr
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
id|sk-&gt;protinfo.nr-&gt;dest_addr
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
id|sysctl_netrom_network_ttl_initialiser
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_route_frame
c_func
(paren
id|skb
comma
l_int|NULL
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
id|ENETUNREACH
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The following routines are taken from page 170 of the 7th ARRL Computer&n; * Networking Conference paper, as is the whole state machine.&n; */
DECL|function|nr_establish_data_link
r_void
id|nr_establish_data_link
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|sk-&gt;protinfo.nr-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_CONNREQ
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;t2timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
id|sk-&gt;protinfo.nr-&gt;t1
op_assign
id|nr_calculate_t1
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Never send a NAK when we are CHOKEd.&n; */
DECL|function|nr_enquiry_response
r_void
id|nr_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|frametype
op_assign
id|NR_INFOACK
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;condition
op_amp
id|OWN_RX_BUSY_CONDITION
)paren
(brace
id|frametype
op_or_assign
id|NR_CHOKE_FLAG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;protinfo.nr-&gt;reseq_queue
)paren
op_ne
l_int|NULL
)paren
(brace
id|frametype
op_or_assign
id|NR_NAK_FLAG
suffix:semicolon
)brace
)brace
id|nr_write_internal
c_func
(paren
id|sk
comma
id|frametype
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;vl
op_assign
id|sk-&gt;protinfo.nr-&gt;vr
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;condition
op_and_assign
op_complement
id|ACK_PENDING_CONDITION
suffix:semicolon
)brace
DECL|function|nr_check_iframes_acked
r_void
id|nr_check_iframes_acked
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
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;vs
op_eq
id|nr
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
id|nr_calculate_rtt
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;protinfo.nr-&gt;va
op_ne
id|nr
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
id|sk-&gt;protinfo.nr-&gt;t1timer
op_assign
id|sk-&gt;protinfo.nr-&gt;t1
op_assign
id|nr_calculate_t1
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
eof
