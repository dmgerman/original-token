multiline_comment|/* sock.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: sock.h,v 0.8.4.7 1993/01/26 22:04:00 bir7 Exp $ */
multiline_comment|/* $Log: sock.h,v $&n; * Revision 0.8.4.7  1993/01/26  22:04:00  bir7&n; * Added support for proc fs.&n; *&n; * Revision 0.8.4.6  1993/01/23  18:00:11  bir7&n; * Added volatile keyword&n; *&n; * Revision 0.8.4.5  1992/12/12  01:50:49  bir7&n; * Fixed support for half duplex connections.&n; *&n; * Revision 0.8.4.4  1992/12/06  23:29:59  bir7&n; * Added mss and support for half completed packets.&n; *&n; * Revision 0.8.4.3  1992/12/03  19:54:12  bir7&n; * Added paranoid queue checking.&n; *&n; * Revision 0.8.4.2  1992/11/10  10:38:48  bir7&n; * Change free_s to kfree_s and accidently changed free_skb to kfree_skb.&n; *&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.4  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added Id and Log&n; *&n; */
macro_line|#ifndef _TCP_SOCK_H
DECL|macro|_TCP_SOCK_H
mdefine_line|#define _TCP_SOCK_H
DECL|macro|SOCK_ARRAY_SIZE
mdefine_line|#define SOCK_ARRAY_SIZE 64
multiline_comment|/* This structure really needs to be cleaned up.  Most of it is&n;   for tcp, and not used by any of the other protocols. */
DECL|struct|sock
r_struct
id|sock
(brace
DECL|member|opt
r_struct
id|options
op_star
id|opt
suffix:semicolon
DECL|member|wmem_alloc
r_volatile
r_int
r_int
id|wmem_alloc
suffix:semicolon
DECL|member|rmem_alloc
r_volatile
r_int
r_int
id|rmem_alloc
suffix:semicolon
DECL|member|send_seq
r_int
r_int
id|send_seq
suffix:semicolon
DECL|member|acked_seq
r_int
r_int
id|acked_seq
suffix:semicolon
DECL|member|copied_seq
r_int
r_int
id|copied_seq
suffix:semicolon
DECL|member|rcv_ack_seq
r_int
r_int
id|rcv_ack_seq
suffix:semicolon
DECL|member|window_seq
r_int
r_int
id|window_seq
suffix:semicolon
DECL|member|fin_seq
r_int
r_int
id|fin_seq
suffix:semicolon
multiline_comment|/* not all are volatile, but some are, so we might as&n;     well say they all are. */
DECL|member|inuse
DECL|member|dead
DECL|member|urginline
r_volatile
r_int
r_int
id|inuse
suffix:colon
l_int|1
comma
id|dead
suffix:colon
l_int|1
comma
id|urginline
suffix:colon
l_int|1
comma
DECL|member|intr
DECL|member|blog
DECL|member|done
DECL|member|reuse
DECL|member|keepopen
DECL|member|linger
id|intr
suffix:colon
l_int|1
comma
id|blog
suffix:colon
l_int|1
comma
id|done
suffix:colon
l_int|1
comma
id|reuse
suffix:colon
l_int|1
comma
id|keepopen
suffix:colon
l_int|1
comma
id|linger
suffix:colon
l_int|1
comma
DECL|member|delay_acks
DECL|member|timeout
DECL|member|destroy
DECL|member|ack_timed
DECL|member|no_check
id|delay_acks
suffix:colon
l_int|1
comma
id|timeout
suffix:colon
l_int|3
comma
id|destroy
suffix:colon
l_int|1
comma
id|ack_timed
suffix:colon
l_int|1
comma
id|no_check
suffix:colon
l_int|1
comma
DECL|member|exp_growth
id|exp_growth
suffix:colon
l_int|1
suffix:semicolon
DECL|member|proc
r_int
id|proc
suffix:semicolon
DECL|member|next
r_volatile
r_struct
id|sock
op_star
id|next
suffix:semicolon
DECL|member|pair
r_volatile
r_struct
id|sock
op_star
id|pair
suffix:semicolon
DECL|member|send_tail
r_struct
id|sk_buff
op_star
id|send_tail
suffix:semicolon
DECL|member|send_head
r_struct
id|sk_buff
op_star
id|send_head
suffix:semicolon
DECL|member|back_log
r_volatile
r_struct
id|sk_buff
op_star
r_volatile
id|back_log
suffix:semicolon
DECL|member|send_tmp
r_struct
id|sk_buff
op_star
id|send_tmp
suffix:semicolon
DECL|member|retransmits
r_int
id|retransmits
suffix:semicolon
DECL|member|wback
DECL|member|wfront
DECL|member|rqueue
r_struct
id|sk_buff
op_star
id|wback
comma
op_star
id|wfront
comma
op_star
id|rqueue
suffix:semicolon
DECL|member|prot
r_struct
id|proto
op_star
id|prot
suffix:semicolon
DECL|member|sleep
r_struct
id|wait_queue
op_star
op_star
id|sleep
suffix:semicolon
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
DECL|member|saddr
r_int
r_int
id|saddr
suffix:semicolon
DECL|member|max_unacked
r_int
r_int
id|max_unacked
suffix:semicolon
DECL|member|window
r_int
r_int
id|window
suffix:semicolon
DECL|member|bytes_rcv
r_int
r_int
id|bytes_rcv
suffix:semicolon
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
DECL|member|cong_window
r_volatile
r_int
r_int
id|cong_window
suffix:semicolon
DECL|member|packets_out
r_volatile
r_int
r_int
id|packets_out
suffix:semicolon
DECL|member|urg
r_volatile
r_int
r_int
id|urg
suffix:semicolon
DECL|member|shutdown
r_volatile
r_int
r_int
id|shutdown
suffix:semicolon
DECL|member|mss
r_int
r_int
id|mss
suffix:semicolon
DECL|member|rtt
r_volatile
r_int
id|rtt
suffix:semicolon
DECL|member|err
r_volatile
r_int
id|err
suffix:semicolon
DECL|member|protocol
r_int
r_char
id|protocol
suffix:semicolon
DECL|member|state
r_volatile
r_int
r_char
id|state
suffix:semicolon
DECL|member|ack_backlog
r_volatile
r_int
r_char
id|ack_backlog
suffix:semicolon
DECL|member|max_ack_backlog
r_int
r_char
id|max_ack_backlog
suffix:semicolon
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
DECL|member|dummy_th
r_struct
id|tcp_header
id|dummy_th
suffix:semicolon
multiline_comment|/* I may be able to get rid of this. */
DECL|member|time_wait
r_volatile
r_struct
id|timer
id|time_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|proto
r_struct
id|proto
(brace
DECL|member|wmalloc
r_void
op_star
(paren
op_star
id|wmalloc
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
DECL|member|rmalloc
r_void
op_star
(paren
op_star
id|rmalloc
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
DECL|member|wfree
r_void
(paren
op_star
id|wfree
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|rfree
r_void
(paren
op_star
id|rfree
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|rspace
r_int
r_int
(paren
op_star
id|rspace
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|wspace
r_int
r_int
(paren
op_star
id|wspace
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|timeout
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|to
comma
r_int
id|len
comma
r_int
id|nonblock
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|to
comma
r_int
id|len
comma
r_int
id|nonblock
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|sendto
r_int
(paren
op_star
id|sendto
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|from
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
id|addr_len
)paren
suffix:semicolon
DECL|member|recvfrom
r_int
(paren
op_star
id|recvfrom
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
op_star
id|from
comma
r_int
id|len
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
op_star
id|addr_len
)paren
suffix:semicolon
DECL|member|build_header
r_int
(paren
op_star
id|build_header
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_struct
id|device
op_star
op_star
id|dev
comma
r_int
id|type
comma
r_struct
id|options
op_star
id|opt
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|connect
r_int
(paren
op_star
id|connect
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr_in
op_star
id|usin
comma
r_int
id|addr_len
)paren
suffix:semicolon
DECL|member|accept
r_volatile
r_struct
id|sock
op_star
(paren
op_star
id|accept
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|queue_xmit
r_void
(paren
op_star
id|queue_xmit
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|free
)paren
suffix:semicolon
DECL|member|retransmit
r_void
(paren
op_star
id|retransmit
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|all
)paren
suffix:semicolon
DECL|member|write_wakeup
r_void
(paren
op_star
id|write_wakeup
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|read_wakeup
r_void
(paren
op_star
id|read_wakeup
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|rcv
r_int
(paren
op_star
id|rcv
)paren
(paren
r_struct
id|sk_buff
op_star
id|buff
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|options
op_star
id|opt
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|saddr
comma
r_int
id|redo
comma
r_struct
id|ip_protocol
op_star
id|protocol
)paren
suffix:semicolon
DECL|member|select
r_int
(paren
op_star
id|select
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|which
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
id|how
)paren
suffix:semicolon
DECL|member|max_header
r_int
r_int
id|max_header
suffix:semicolon
DECL|member|retransmits
r_int
r_int
id|retransmits
suffix:semicolon
DECL|member|sock_array
r_volatile
r_struct
id|sock
op_star
id|sock_array
(braket
id|SOCK_ARRAY_SIZE
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TIME_WRITE
mdefine_line|#define TIME_WRITE 1
DECL|macro|TIME_CLOSE
mdefine_line|#define TIME_CLOSE 2
DECL|macro|TIME_KEEPOPEN
mdefine_line|#define TIME_KEEPOPEN 3
DECL|macro|TIME_DESTROY
mdefine_line|#define TIME_DESTROY 4
DECL|macro|TIME_DONE
mdefine_line|#define TIME_DONE 5 /* used to absorb those last few packets. */
DECL|macro|SOCK_DESTROY_TIME
mdefine_line|#define SOCK_DESTROY_TIME 1000 /* about 10 seconds. */
multiline_comment|/* used with free skb */
DECL|macro|FREE_READ
mdefine_line|#define FREE_READ 1
DECL|macro|FREE_WRITE
mdefine_line|#define FREE_WRITE 0
DECL|struct|sk_buff
r_struct
id|sk_buff
(brace
DECL|member|next
r_volatile
r_struct
id|sk_buff
op_star
id|next
suffix:semicolon
DECL|member|prev
r_volatile
r_struct
id|sk_buff
op_star
id|prev
suffix:semicolon
DECL|member|link3
r_volatile
r_struct
id|sk_buff
op_star
id|link3
suffix:semicolon
DECL|member|sk
r_volatile
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
multiline_comment|/* used to compute rtt&squot;s. */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|mem_addr
r_void
op_star
id|mem_addr
suffix:semicolon
r_union
(brace
DECL|member|th
r_struct
id|tcp_header
op_star
id|th
suffix:semicolon
DECL|member|eth
r_struct
id|enet_header
op_star
id|eth
suffix:semicolon
DECL|member|iph
r_struct
id|ip_header
op_star
id|iph
suffix:semicolon
DECL|member|uh
r_struct
id|udp_header
op_star
id|uh
suffix:semicolon
DECL|member|arp
r_struct
id|arp
op_star
id|arp
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
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|acked
DECL|member|used
DECL|member|free
DECL|member|arp
DECL|member|urg_used
DECL|member|lock
r_volatile
r_int
r_int
id|acked
suffix:colon
l_int|1
comma
id|used
suffix:colon
l_int|1
comma
id|free
suffix:colon
l_int|1
comma
id|arp
suffix:colon
l_int|1
comma
id|urg_used
suffix:colon
l_int|1
comma
id|lock
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROT_SOCK
mdefine_line|#define PROT_SOCK 1024
DECL|macro|SK_WMEM_MAX
mdefine_line|#define SK_WMEM_MAX 8192
DECL|macro|SK_RMEM_MAX
mdefine_line|#define SK_RMEM_MAX 32767
DECL|macro|SHUTDOWN_MASK
mdefine_line|#define SHUTDOWN_MASK 3
DECL|macro|RCV_SHUTDOWN
mdefine_line|#define RCV_SHUTDOWN 1
DECL|macro|SEND_SHUTDOWN
mdefine_line|#define SEND_SHUTDOWN 2
r_void
id|destroy_sock
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_int
r_int
id|get_new_socknum
(paren
r_struct
id|proto
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|put_sock
(paren
r_int
r_int
comma
r_volatile
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_void
id|release_sock
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_volatile
r_struct
id|sock
op_star
id|get_sock
c_func
(paren
r_struct
id|proto
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|print_sk
(paren
r_volatile
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_void
id|print_skb
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
op_star
id|sock_wmalloc
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
op_star
id|sock_rmalloc
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|size
comma
r_int
id|force
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|sock_wfree
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
id|sock_rfree
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
comma
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
r_int
id|sock_rspace
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_int
r_int
id|sock_wspace
c_func
(paren
r_volatile
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_void
id|kfree_skb
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
r_void
id|lock_skb
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|unlock_skb
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
r_void
id|dummy_routine
c_func
(paren
r_void
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
eof
