multiline_comment|/*&n; *  $Id: message.c,v 1.5 1999/09/04 06:20:07 keil Exp $&n; *  Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; *  message.c - functions for sending and receiving control messages&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
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
multiline_comment|/*&n; * Obligitory function prototypes&n; */
r_extern
r_int
id|indicate_status
c_func
(paren
r_int
comma
id|ulong
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scm_command
c_func
(paren
id|isdn_ctrl
op_star
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
multiline_comment|/*&n; * Dump message queue in shared memory to screen&n; */
DECL|function|dump_messages
r_void
id|dump_messages
c_func
(paren
r_int
id|card
)paren
(brace
id|DualPortMemory
id|dpm
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
l_int|0
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
)brace
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
id|outb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_pgport
)braket
comma
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_magic
op_rshift
l_int|14
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
id|memcpy_fromshmem
c_func
(paren
id|card
comma
op_amp
id|dpm
comma
l_int|0
comma
r_sizeof
(paren
id|dpm
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Dumping Request Queue&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
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
id|dpm.req_head
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Message #%d: (%d,%d,%d), link: %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|i
comma
id|dpm.req_queue
(braket
id|i
)braket
dot
id|type
comma
id|dpm.req_queue
(braket
id|i
)braket
dot
r_class
comma
id|dpm.req_queue
(braket
id|i
)braket
dot
id|code
comma
id|dpm.req_queue
(braket
id|i
)braket
dot
id|phy_link_no
)paren
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Dumping Response Queue&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
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
id|dpm.rsp_head
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Message #%d: (%d,%d,%d), link: %d, status: %d&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|i
comma
id|dpm.rsp_queue
(braket
id|i
)braket
dot
id|type
comma
id|dpm.rsp_queue
(braket
id|i
)braket
dot
r_class
comma
id|dpm.rsp_queue
(braket
id|i
)braket
dot
id|code
comma
id|dpm.rsp_queue
(braket
id|i
)braket
dot
id|phy_link_no
comma
id|dpm.rsp_queue
(braket
id|i
)braket
dot
id|rsp_status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * receive a message from the board&n; */
DECL|function|receivemessage
r_int
id|receivemessage
c_func
(paren
r_int
id|card
comma
id|RspMessage
op_star
id|rspmsg
)paren
(brace
id|DualPortMemory
op_star
id|dpm
suffix:semicolon
r_int
r_int
id|flags
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
id|EINVAL
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Entered receivemessage&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * See if there are messages waiting&n;&t; */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_STATUS
)braket
)paren
op_amp
id|RF_HAS_DATA
)paren
(brace
multiline_comment|/*&n;&t;&t; * Map in the DPM to the base page and copy the message&n;&t;&t; */
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
id|outb
c_func
(paren
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_magic
op_rshift
l_int|14
)paren
op_or
l_int|0x80
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_pgport
)braket
)paren
suffix:semicolon
id|dpm
op_assign
(paren
id|DualPortMemory
op_star
)paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|rambase
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|rspmsg
comma
op_amp
(paren
id|dpm-&gt;rsp_queue
(braket
id|dpm-&gt;rsp_tail
)braket
)paren
comma
id|MSG_LEN
)paren
suffix:semicolon
id|dpm-&gt;rsp_tail
op_assign
(paren
id|dpm-&gt;rsp_tail
op_plus
l_int|1
)paren
op_mod
id|MAX_MESSAGES
suffix:semicolon
id|inb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_READ
)braket
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Tell the board that the message is received&n;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Received Message seq:%d pid:%d time:%d cmd:%d &quot;
l_string|&quot;cnt:%d (type,class,code):(%d,%d,%d) &quot;
l_string|&quot;link:%d stat:0x%x&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|rspmsg-&gt;sequence_no
comma
id|rspmsg-&gt;process_id
comma
id|rspmsg-&gt;time_stamp
comma
id|rspmsg-&gt;cmd_sequence_no
comma
id|rspmsg-&gt;msg_byte_cnt
comma
id|rspmsg-&gt;type
comma
id|rspmsg
op_member_access_from_pointer
r_class
comma
id|rspmsg-&gt;code
comma
id|rspmsg-&gt;phy_link_no
comma
id|rspmsg-&gt;rsp_status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOMSG
suffix:semicolon
)brace
multiline_comment|/*&n; * send a message to the board&n; */
DECL|function|sendmessage
r_int
id|sendmessage
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|procid
comma
r_int
r_int
id|type
comma
r_int
r_int
r_class
comma
r_int
r_int
id|code
comma
r_int
r_int
id|link
comma
r_int
r_int
id|data_len
comma
r_int
r_int
op_star
id|data
)paren
(brace
id|DualPortMemory
op_star
id|dpm
suffix:semicolon
id|ReqMessage
id|sndmsg
suffix:semicolon
r_int
r_int
id|flags
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
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure we only send CEPID messages when the engine is up&n;&t; * and CMPID messages when it is down&n;&t; */
r_if
c_cond
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
op_logical_and
id|procid
op_eq
id|CMPID
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Attempt to send CM message with engine up&bslash;n&quot;
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
id|ESRCH
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|EngineUp
op_logical_and
id|procid
op_eq
id|CEPID
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: Attempt to send CE message with engine down&bslash;n&quot;
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
id|ESRCH
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|sndmsg
comma
l_int|0
comma
id|MSG_LEN
)paren
suffix:semicolon
id|sndmsg.msg_byte_cnt
op_assign
l_int|4
suffix:semicolon
id|sndmsg.type
op_assign
id|type
suffix:semicolon
id|sndmsg
dot
r_class
op_assign
r_class
suffix:semicolon
id|sndmsg.code
op_assign
id|code
suffix:semicolon
id|sndmsg.phy_link_no
op_assign
id|link
suffix:semicolon
r_if
c_cond
(paren
id|data_len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|data_len
OG
id|MSG_DATA_LEN
)paren
id|data_len
op_assign
id|MSG_DATA_LEN
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|sndmsg.msg_data
)paren
comma
id|data
comma
id|data_len
)paren
suffix:semicolon
id|sndmsg.msg_byte_cnt
op_assign
id|data_len
op_plus
l_int|8
suffix:semicolon
)brace
id|sndmsg.process_id
op_assign
id|procid
suffix:semicolon
id|sndmsg.sequence_no
op_assign
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|seq_no
op_increment
op_mod
l_int|256
suffix:semicolon
multiline_comment|/*&n;&t; * wait for an empty slot in the queue&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_STATUS
)braket
)paren
op_amp
id|WF_NOT_FULL
)paren
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable interrupts and map in shared memory&n;&t; */
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
id|outb
c_func
(paren
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_magic
op_rshift
l_int|14
)paren
op_or
l_int|0x80
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|shmem_pgport
)braket
)paren
suffix:semicolon
id|dpm
op_assign
(paren
id|DualPortMemory
op_star
)paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|rambase
suffix:semicolon
multiline_comment|/* Fix me */
id|memcpy_toio
c_func
(paren
op_amp
(paren
id|dpm-&gt;req_queue
(braket
id|dpm-&gt;req_head
)braket
)paren
comma
op_amp
id|sndmsg
comma
id|MSG_LEN
)paren
suffix:semicolon
id|dpm-&gt;req_head
op_assign
(paren
id|dpm-&gt;req_head
op_plus
l_int|1
)paren
op_mod
id|MAX_MESSAGES
suffix:semicolon
id|outb
c_func
(paren
id|sndmsg.sequence_no
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|ioport
(braket
id|FIFO_WRITE
)braket
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: Sent Message seq:%d pid:%d time:%d &quot;
l_string|&quot;cnt:%d (type,class,code):(%d,%d,%d) &quot;
l_string|&quot;link:%d&bslash;n &quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
comma
id|sndmsg.sequence_no
comma
id|sndmsg.process_id
comma
id|sndmsg.time_stamp
comma
id|sndmsg.msg_byte_cnt
comma
id|sndmsg.type
comma
id|sndmsg
dot
r_class
comma
id|sndmsg.code
comma
id|sndmsg.phy_link_no
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|send_and_receive
r_int
id|send_and_receive
c_func
(paren
r_int
id|card
comma
r_int
r_int
id|procid
comma
r_int
r_char
id|type
comma
r_int
r_char
r_class
comma
r_int
r_char
id|code
comma
r_int
r_char
id|link
comma
r_int
r_char
id|data_len
comma
r_int
r_char
op_star
id|data
comma
id|RspMessage
op_star
id|mesgdata
comma
r_int
id|timeout
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|tries
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
id|EINVAL
suffix:semicolon
)brace
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|want_async_messages
op_assign
l_int|1
suffix:semicolon
id|retval
op_assign
id|sendmessage
c_func
(paren
id|card
comma
id|procid
comma
id|type
comma
r_class
comma
id|code
comma
id|link
comma
id|data_len
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SendMessage failed in SAR&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|want_async_messages
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tries
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait for the response */
r_while
c_loop
(paren
id|tries
OL
id|timeout
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;SAR waiting..&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * See if we got our message back&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg.type
op_eq
id|type
)paren
op_logical_and
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg
dot
r_class
op_eq
r_class
)paren
op_logical_and
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg.code
op_eq
id|code
)paren
op_logical_and
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg.phy_link_no
op_eq
id|link
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Got it!&n;&t;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;%s: Got ASYNC message&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|mesgdata
comma
op_amp
(paren
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|async_msg
)paren
comma
r_sizeof
(paren
id|RspMessage
)paren
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|want_async_messages
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tries
op_increment
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: SAR message timeout&bslash;n&quot;
comma
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|devicename
)paren
suffix:semicolon
id|adapter
(braket
id|card
)braket
op_member_access_from_pointer
id|want_async_messages
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
eof
