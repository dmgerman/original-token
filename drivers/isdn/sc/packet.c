multiline_comment|/*&n; *  $Id: packet.c,v 1.2 1996/11/20 17:49:55 fritz Exp $&n; *  Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;includes.h&quot;
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;message.h&quot;
macro_line|#include &quot;card.h&quot;
r_extern
id|board
op_star
id|adapter
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|cinst
suffix:semicolon
r_extern
r_int
id|get_card_from_id
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|indicate_status
c_func
(paren
r_int
comma
r_int
comma
id|ulong
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy_toshmem
c_func
(paren
r_int
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy_fromshmem
c_func
(paren
r_int
comma
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sendmessage
c_func
(paren
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
op_star
)paren
suffix:semicolon
DECL|function|sndpkt
r_int
id|sndpkt
c_func
(paren
r_int
id|devId
comma
r_int
id|channel
comma
r_struct
id|sk_buff
op_star
id|data
)paren
(brace
id|LLData
id|ReqLnkWrite
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|card
suffix:semicolon
id|card
op_assign
id|get_card_from_id
c_func
(paren
id|devId
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_CARD
c_func
(paren
id|card
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Invalid param: %d is not a valid card id&bslash;n&quot;
comma
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Send Packet: frst = 0x%x nxt = %d  f = %d n = %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|first_sendbuf
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|free_sendbufs
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|num_sendbufs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|free_sendbufs
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Out out TX buffers&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;len
OG
id|BUFFER_SIZE
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Data overflows buffer size (data &gt; buffer)&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ReqLnkWrite.buff_offset
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
op_star
id|BUFFER_SIZE
op_plus
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|first_sendbuf
suffix:semicolon
id|ReqLnkWrite.msg_len
op_assign
id|data-&gt;len
suffix:semicolon
multiline_comment|/* sk_buff size */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Writing %d bytes to buffer offset 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|ReqLnkWrite.msg_len
comma
id|ReqLnkWrite.buff_offset
)paren
suffix:semicolon
id|memcpy_toshmem
c_func
(paren
id|card
comma
(paren
r_char
op_star
)paren
id|ReqLnkWrite.buff_offset
comma
id|data-&gt;data
comma
id|ReqLnkWrite.msg_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * sendmessage&n;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Send Packet size=%d, buf_offset=0x%x buf_indx=%d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|ReqLnkWrite.msg_len
comma
id|ReqLnkWrite.buff_offset
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
)paren
suffix:semicolon
id|status
op_assign
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass1
comma
id|ceReqLnkWrite
comma
id|channel
op_plus
l_int|1
comma
r_sizeof
(paren
id|LLData
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|ReqLnkWrite
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Failed to send packet, status = %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|free_sendbufs
op_decrement
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
op_assign
op_increment
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
op_eq
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|num_sendbufs
ques
c_cond
l_int|0
suffix:colon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|channel
)braket
dot
id|next_sendbuf
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Packet sent successfully&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|data
comma
id|FREE_WRITE
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|card
comma
id|ISDN_STAT_BSENT
comma
id|channel
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|data-&gt;len
suffix:semicolon
)brace
DECL|function|rcvpkt
r_void
id|rcvpkt
c_func
(paren
r_int
id|card
comma
id|RspMessage
op_star
id|rcvmsg
)paren
(brace
id|LLData
id|newll
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_CARD
c_func
(paren
id|card
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Invalid param: %d is not a valid card id&bslash;n&quot;
comma
id|card
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|rcvmsg-&gt;rsp_status
)paren
(brace
r_case
l_int|0x01
suffix:colon
r_case
l_int|0x02
suffix:colon
r_case
l_int|0x70
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Error status code: 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg-&gt;rsp_status
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|0x00
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|rcvmsg-&gt;msg_data.response.msg_len
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: rcvpkt out of memory, dropping packet&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|skb
comma
id|rcvmsg-&gt;msg_data.response.msg_len
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: getting data from offset: 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rcvmsg-&gt;msg_data.response.buff_offset
)paren
suffix:semicolon
id|memcpy_fromshmem
c_func
(paren
id|card
comma
id|skb_put
c_func
(paren
id|skb
comma
id|rcvmsg-&gt;msg_data.response.msg_len
)paren
comma
(paren
r_char
op_star
)paren
id|rcvmsg-&gt;msg_data.response.buff_offset
comma
id|rcvmsg-&gt;msg_data.response.msg_len
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|card
op_member_access_from_pointer
id|rcvcallb_skb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|driverId
comma
id|rcvmsg-&gt;phy_link_no
op_minus
l_int|1
comma
id|skb
)paren
suffix:semicolon
r_case
l_int|0x03
suffix:colon
multiline_comment|/*&n;&t; &t; * Recycle the buffer&n;&t; &t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Buffer size : %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|BUFFER_SIZE
)paren
suffix:semicolon
multiline_comment|/*&t;&t;memset_shmem(card, rcvmsg-&gt;msg_data.response.buff_offset, 0, BUFFER_SIZE); */
id|newll.buff_offset
op_assign
id|rcvmsg-&gt;msg_data.response.buff_offset
suffix:semicolon
id|newll.msg_len
op_assign
id|BUFFER_SIZE
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: recycled buffer at offset 0x%x size %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|newll.buff_offset
comma
id|newll.msg_len
)paren
suffix:semicolon
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass1
comma
id|ceReqLnkRead
comma
id|rcvmsg-&gt;phy_link_no
comma
r_sizeof
(paren
id|LLData
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|newll
)paren
suffix:semicolon
)brace
)brace
DECL|function|setup_buffers
r_int
id|setup_buffers
c_func
(paren
r_int
id|card
comma
r_int
id|c
)paren
(brace
r_int
r_int
id|nBuffers
comma
id|i
comma
id|cBase
suffix:semicolon
r_int
r_int
id|buffer_size
suffix:semicolon
id|LLData
id|RcvBuffOffset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_CARD
c_func
(paren
id|card
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Invalid param: %d is not a valid card id&bslash;n&quot;
comma
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate the buffer offsets (send/recv/send/recv)&n;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Seting up channel buffer space in shared RAM&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|buffer_size
op_assign
id|BUFFER_SIZE
suffix:semicolon
id|nBuffers
op_assign
(paren
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ramsize
op_minus
id|BUFFER_BASE
)paren
op_div
id|buffer_size
)paren
op_div
l_int|2
suffix:semicolon
id|nBuffers
op_assign
id|nBuffers
OG
id|BUFFERS_MAX
ques
c_cond
id|BUFFERS_MAX
suffix:colon
id|nBuffers
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Calculating buffer space: %d buffers, %d big&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|nBuffers
comma
id|buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nBuffers
OL
l_int|2
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Not enough buffer space&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|cBase
op_assign
(paren
id|nBuffers
op_star
id|buffer_size
)paren
op_star
(paren
id|c
op_minus
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Channel buffer offset from Shared RAM: 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|cBase
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|first_sendbuf
op_assign
id|BUFFER_BASE
op_plus
id|cBase
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|num_sendbufs
op_assign
id|nBuffers
op_div
l_int|2
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|free_sendbufs
op_assign
id|nBuffers
op_div
l_int|2
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|next_sendbuf
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Send buffer setup complete: first=0x%x n=%d f=%d, nxt=%d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|first_sendbuf
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|num_sendbufs
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|free_sendbufs
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|next_sendbuf
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Prep the receive buffers&n;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Adding %d RecvBuffers:&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|nBuffers
op_div
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nBuffers
op_div
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|RcvBuffOffset.buff_offset
op_assign
(paren
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|channel
(braket
id|c
op_minus
l_int|1
)braket
dot
id|first_sendbuf
op_plus
(paren
id|nBuffers
op_div
l_int|2
)paren
op_star
id|buffer_size
)paren
op_plus
(paren
id|buffer_size
op_star
id|i
)paren
)paren
suffix:semicolon
id|RcvBuffOffset.msg_len
op_assign
id|buffer_size
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Adding RcvBuffer #%d offset=0x%x sz=%d buffsz:%d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|i
op_plus
l_int|1
comma
id|RcvBuffOffset.buff_offset
comma
id|RcvBuffOffset.msg_len
comma
id|buffer_size
)paren
suffix:semicolon
id|sendmessage
c_func
(paren
id|card
comma
id|CEPID
comma
id|ceReqTypeLnk
comma
id|ceReqClass1
comma
id|ceReqLnkRead
comma
id|c
comma
r_sizeof
(paren
id|LLData
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|RcvBuffOffset
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_skb
r_int
(def_block
id|print_skb
c_func
(paren
r_int
id|card
comma
r_char
op_star
id|skb_p
comma
r_int
id|len
)paren
(brace
r_int
id|i
comma
id|data
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: data at 0x%x len: 0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|skb_p
comma
id|len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|len
suffix:semicolon
id|i
op_increment
comma
id|skb_p
op_increment
)paren
(brace
id|data
op_assign
(paren
r_int
)paren
(paren
l_int|0xff
op_amp
(paren
op_star
id|skb_p
)paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: data =  0x%x&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|4
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|32
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|pr_debug
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
eof