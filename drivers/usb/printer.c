multiline_comment|/*&n; * printer.c  Version 0.3&n; *&n; * Copyright (c) 1999 Michael Gee &t;&lt;michael@linuxspecific.com&gt;&n; * Copyright (c) 1999 Pavel Machek      &lt;pavel@suse.cz&gt;&n; * Copyright (c) 2000 Vojtech Pavlik    &lt;vojtech@suse.cz&gt;&n; *&n; * USB Printer Device Class driver for USB printers and printer cables&n; *&n; * Sponsored by SuSE&n; *&n; * ChangeLog:&n; *&t;v0.1 - thorough cleaning, URBification, almost a rewrite&n; *&t;v0.2 - some more cleanups&n; *&t;v0.3 - cleaner again, waitqueue fixes&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/lp.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &quot;usb.h&quot;
DECL|macro|USBLP_BUF_SIZE
mdefine_line|#define USBLP_BUF_SIZE&t;&t;8192
multiline_comment|/*&n; * USB Printer Requests&n; */
DECL|macro|USBLP_REQ_GET_ID
mdefine_line|#define USBLP_REQ_GET_ID&t;0x00
DECL|macro|USBLP_REQ_GET_STATUS
mdefine_line|#define USBLP_REQ_GET_STATUS&t;0x01
DECL|macro|USBLP_REQ_RESET
mdefine_line|#define USBLP_REQ_RESET&t;&t;0x02
DECL|macro|USBLP_MINORS
mdefine_line|#define USBLP_MINORS&t;&t;16
DECL|macro|USBLP_MINOR_BASE
mdefine_line|#define USBLP_MINOR_BASE&t;0
DECL|macro|USBLP_WRITE_TIMEOUT
mdefine_line|#define USBLP_WRITE_TIMEOUT&t;(60*HZ)&t;&t;&t;/* 60 seconds */
DECL|struct|usblp
r_struct
id|usblp
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* USB device */
DECL|member|readurb
DECL|member|writeurb
r_struct
id|urb
id|readurb
comma
id|writeurb
suffix:semicolon
multiline_comment|/* The urbs */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* Zzzzz ... */
DECL|member|readcount
r_int
id|readcount
suffix:semicolon
multiline_comment|/* Counter for reads */
DECL|member|ifnum
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* Interface number */
DECL|member|minor
r_int
id|minor
suffix:semicolon
multiline_comment|/* minor number of device */
DECL|member|used
r_int
r_char
id|used
suffix:semicolon
multiline_comment|/* True if open */
DECL|member|bidir
r_int
r_char
id|bidir
suffix:semicolon
multiline_comment|/* interface is bidirectional */
)brace
suffix:semicolon
DECL|variable|usblp_table
r_static
r_struct
id|usblp
op_star
id|usblp_table
(braket
id|USBLP_MINORS
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
multiline_comment|/*&n; * Functions for usblp control messages.&n; */
DECL|function|usblp_ctrl_msg
r_static
r_int
id|usblp_ctrl_msg
c_func
(paren
r_struct
id|usblp
op_star
id|usblp
comma
r_int
id|request
comma
r_int
id|dir
comma
r_int
id|recip
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|retval
op_assign
id|usb_control_msg
c_func
(paren
id|usblp-&gt;dev
comma
id|dir
ques
c_cond
id|usb_rcvctrlpipe
c_func
(paren
id|usblp-&gt;dev
comma
l_int|0
)paren
suffix:colon
id|usb_sndctrlpipe
c_func
(paren
id|usblp-&gt;dev
comma
l_int|0
)paren
comma
id|request
comma
id|USB_TYPE_CLASS
op_or
id|dir
op_or
id|recip
comma
l_int|0
comma
id|usblp-&gt;ifnum
comma
id|buf
comma
id|len
comma
id|HZ
op_star
l_int|5
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;usblp_control_msg: rq: 0x%02x dir: %d recip: %d len: %#x result: %d&quot;
comma
id|request
comma
op_logical_neg
op_logical_neg
id|dir
comma
id|recip
comma
id|len
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
OL
l_int|0
ques
c_cond
id|retval
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|macro|usblp_read_status
mdefine_line|#define usblp_read_status(usblp, status)&bslash;&n;&t;usblp_ctrl_msg(usblp, USBLP_REQ_GET_STATUS, USB_DIR_IN, USB_RECIP_INTERFACE, status, 1)
DECL|macro|usblp_get_id
mdefine_line|#define usblp_get_id(usblp, id, maxlen)&bslash;&n;&t;usblp_ctrl_msg(usblp, USBLP_REQ_GET_ID, USB_DIR_IN, USB_RECIP_INTERFACE, id, maxlen)
DECL|macro|usblp_reset
mdefine_line|#define usblp_reset(usblp)&bslash;&n;&t;usblp_ctrl_msg(usblp, USBLP_REQ_RESET, USB_DIR_OUT, USB_RECIP_OTHER, NULL, 0)
multiline_comment|/*&n; * URB callback.&n; */
DECL|function|usblp_bulk
r_static
r_void
id|usblp_bulk
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usblp
op_star
id|usblp
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usblp
op_logical_or
op_logical_neg
id|usblp-&gt;dev
op_logical_or
op_logical_neg
id|usblp-&gt;used
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
id|warn
c_func
(paren
l_string|&quot;nonzero read bulk status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|usblp-&gt;wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get and print printer errors.&n; */
DECL|function|usblp_check_status
r_static
r_int
id|usblp_check_status
c_func
(paren
r_struct
id|usblp
op_star
id|usblp
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
id|usblp_read_status
c_func
(paren
id|usblp
comma
op_amp
id|status
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;failed reading usblp status&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|LP_PERRORP
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|LP_POUTPA
)paren
(brace
id|info
c_func
(paren
l_string|&quot;usblp%d: out of paper&quot;
comma
id|usblp-&gt;minor
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|status
op_amp
id|LP_PSELECD
)paren
(brace
id|info
c_func
(paren
l_string|&quot;usblp%d: off-line&quot;
comma
id|usblp-&gt;minor
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|status
op_amp
id|LP_PERRORP
)paren
(brace
id|info
c_func
(paren
l_string|&quot;usblp%d: on fire&quot;
comma
id|usblp-&gt;minor
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * File op functions.&n; */
DECL|function|usblp_open
r_static
r_int
id|usblp_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|USBLP_MINOR_BASE
suffix:semicolon
r_struct
id|usblp
op_star
id|usblp
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
op_logical_or
id|minor
op_ge
id|USBLP_MINORS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|usblp
op_assign
id|usblp_table
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usblp
op_logical_or
op_logical_neg
id|usblp-&gt;dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|usblp-&gt;used
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|usblp_check_status
c_func
(paren
id|usblp
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|usblp-&gt;used
op_assign
l_int|1
suffix:semicolon
id|file-&gt;private_data
op_assign
id|usblp
suffix:semicolon
id|usblp-&gt;writeurb.transfer_buffer_length
op_assign
l_int|0
suffix:semicolon
id|usblp-&gt;writeurb.status
op_assign
l_int|0
suffix:semicolon
id|usblp-&gt;readcount
op_assign
l_int|0
suffix:semicolon
id|usb_submit_urb
c_func
(paren
op_amp
id|usblp-&gt;readurb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usblp_release
r_static
r_int
id|usblp_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|usblp
op_star
id|usblp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|usblp-&gt;used
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|usblp-&gt;dev
)paren
(brace
id|usb_unlink_urb
c_func
(paren
op_amp
id|usblp-&gt;readurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|usblp-&gt;writeurb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|usblp_table
(braket
id|usblp-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|usblp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usblp_poll
r_static
r_int
r_int
id|usblp_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_struct
id|usblp
op_star
id|usblp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|usblp-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_return
(paren
id|usblp-&gt;readurb.status
op_eq
op_minus
id|EINPROGRESS
ques
c_cond
l_int|0
suffix:colon
id|POLLIN
op_or
id|POLLRDNORM
)paren
op_or
(paren
id|usblp-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
ques
c_cond
l_int|0
suffix:colon
id|POLLOUT
op_or
id|POLLWRNORM
)paren
suffix:semicolon
)brace
DECL|function|usblp_write
r_static
id|ssize_t
id|usblp_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|usblp
op_star
id|usblp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
comma
id|timeout
comma
id|writecount
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|writecount
OL
id|count
)paren
(brace
r_if
c_cond
(paren
id|usblp-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|timeout
op_assign
id|USBLP_WRITE_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_logical_and
id|usblp-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
id|writecount
ques
c_cond
id|writecount
suffix:colon
op_minus
id|EINTR
suffix:semicolon
id|timeout
op_assign
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|usblp-&gt;wait
comma
id|timeout
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|usblp-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
id|usb_unlink_urb
c_func
(paren
op_amp
id|usblp-&gt;writeurb
)paren
suffix:semicolon
id|err
c_func
(paren
l_string|&quot;usblp%d: timed out&quot;
comma
id|usblp-&gt;minor
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|usblp-&gt;dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usblp-&gt;writeurb.status
)paren
(brace
id|writecount
op_add_assign
id|usblp-&gt;writeurb.transfer_buffer_length
suffix:semicolon
id|usblp-&gt;writeurb.transfer_buffer_length
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|retval
op_assign
id|usblp_check_status
c_func
(paren
id|usblp
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usblp%d: error %d writing to printer&quot;
comma
id|usblp-&gt;minor
comma
id|usblp-&gt;writeurb.status
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|writecount
op_eq
id|count
)paren
r_continue
suffix:semicolon
id|usblp-&gt;writeurb.transfer_buffer_length
op_assign
(paren
id|count
op_minus
id|writecount
)paren
OL
id|USBLP_BUF_SIZE
ques
c_cond
(paren
id|count
op_minus
id|writecount
)paren
suffix:colon
id|USBLP_BUF_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|usblp-&gt;writeurb.transfer_buffer
comma
id|buffer
op_plus
id|writecount
comma
id|usblp-&gt;writeurb.transfer_buffer_length
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|usb_submit_urb
c_func
(paren
op_amp
id|usblp-&gt;writeurb
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|usblp_read
r_static
id|ssize_t
id|usblp_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|usblp
op_star
id|usblp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usblp-&gt;bidir
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|usblp-&gt;readurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_while
c_loop
(paren
id|usblp-&gt;readurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|usblp-&gt;wait
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|usblp-&gt;dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|usblp-&gt;readurb.status
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usblp%d: error %d reading from printer&quot;
comma
id|usblp-&gt;minor
comma
id|usblp-&gt;readurb.status
)paren
suffix:semicolon
id|usb_submit_urb
c_func
(paren
op_amp
id|usblp-&gt;readurb
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|count
op_assign
id|count
OL
id|usblp-&gt;readurb.actual_length
op_minus
id|usblp-&gt;readcount
ques
c_cond
id|count
suffix:colon
id|usblp-&gt;readurb.actual_length
op_minus
id|usblp-&gt;readcount
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|usblp-&gt;readurb.transfer_buffer
op_plus
id|usblp-&gt;readcount
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|usblp-&gt;readcount
op_add_assign
id|count
)paren
op_eq
id|usblp-&gt;readurb.actual_length
)paren
id|usb_submit_urb
c_func
(paren
op_amp
id|usblp-&gt;readurb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|usblp_probe
r_static
r_void
op_star
id|usblp_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|epread
comma
op_star
id|epwrite
suffix:semicolon
r_struct
id|usblp
op_star
id|usblp
suffix:semicolon
r_int
id|minor
comma
id|i
comma
id|alts
op_assign
op_minus
l_int|1
comma
id|bidir
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|buf
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
id|dev-&gt;actconfig-&gt;interface
(braket
id|ifnum
)braket
dot
id|num_altsetting
suffix:semicolon
id|i
op_increment
)paren
(brace
id|interface
op_assign
op_amp
id|dev-&gt;actconfig-&gt;interface
(braket
id|ifnum
)braket
dot
id|altsetting
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|interface-&gt;bInterfaceClass
op_ne
l_int|7
op_logical_or
id|interface-&gt;bInterfaceSubClass
op_ne
l_int|1
op_logical_or
(paren
id|interface-&gt;bInterfaceProtocol
op_ne
l_int|1
op_logical_and
id|interface-&gt;bInterfaceProtocol
op_ne
l_int|2
)paren
op_logical_or
(paren
id|interface-&gt;bInterfaceProtocol
OG
id|interface-&gt;bNumEndpoints
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|alts
op_eq
op_minus
l_int|1
)paren
id|alts
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bidir
op_logical_and
id|interface-&gt;bInterfaceProtocol
op_eq
l_int|2
)paren
(brace
id|bidir
op_assign
l_int|1
suffix:semicolon
id|alts
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|alts
op_eq
op_minus
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
id|interface
op_assign
op_amp
id|dev-&gt;actconfig-&gt;interface
(braket
id|ifnum
)braket
dot
id|altsetting
(braket
id|alts
)braket
suffix:semicolon
r_if
c_cond
(paren
id|usb_set_interface
c_func
(paren
id|dev
comma
id|ifnum
comma
id|alts
)paren
)paren
id|err
c_func
(paren
l_string|&quot;can&squot;t set desired altsetting %d on interface %d&quot;
comma
id|alts
comma
id|ifnum
)paren
suffix:semicolon
id|epwrite
op_assign
id|interface-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
id|epread
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bidir
)paren
(brace
id|epread
op_assign
id|interface-&gt;endpoint
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|epread-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_ne
l_int|0x80
)paren
(brace
id|epwrite
op_assign
id|interface-&gt;endpoint
op_plus
l_int|1
suffix:semicolon
id|epread
op_assign
id|interface-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|epread-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_ne
l_int|0x80
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|epwrite-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_eq
l_int|0x80
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|USBLP_MINORS
op_logical_and
id|usblp_table
(braket
id|minor
)braket
suffix:semicolon
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usblp_table
(braket
id|minor
)braket
)paren
(brace
id|err
c_func
(paren
l_string|&quot;no more free usblp devices&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|usblp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usblp
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|usblp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usblp
)paren
)paren
suffix:semicolon
id|usblp-&gt;dev
op_assign
id|dev
suffix:semicolon
id|usblp-&gt;ifnum
op_assign
id|ifnum
suffix:semicolon
id|usblp-&gt;minor
op_assign
id|minor
suffix:semicolon
id|usblp-&gt;bidir
op_assign
id|bidir
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|usblp-&gt;wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
op_assign
id|kmalloc
c_func
(paren
id|USBLP_BUF_SIZE
op_star
(paren
id|bidir
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|usblp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|FILL_BULK_URB
c_func
(paren
op_amp
id|usblp-&gt;writeurb
comma
id|dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dev
comma
id|epwrite-&gt;bEndpointAddress
)paren
comma
id|buf
comma
l_int|0
comma
id|usblp_bulk
comma
id|usblp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bidir
)paren
(brace
id|FILL_BULK_URB
c_func
(paren
op_amp
id|usblp-&gt;readurb
comma
id|dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dev
comma
id|epread-&gt;bEndpointAddress
)paren
comma
id|buf
op_plus
id|USBLP_BUF_SIZE
comma
id|USBLP_BUF_SIZE
comma
id|usblp_bulk
comma
id|usblp
)paren
suffix:semicolon
)brace
id|info
c_func
(paren
l_string|&quot;usblp%d: USB %sdirectional printer dev %d if %d alt %d&quot;
comma
id|minor
comma
id|bidir
ques
c_cond
l_string|&quot;Bi&quot;
suffix:colon
l_string|&quot;Uni&quot;
comma
id|dev-&gt;devnum
comma
id|ifnum
comma
id|alts
)paren
suffix:semicolon
r_return
id|usblp_table
(braket
id|minor
)braket
op_assign
id|usblp
suffix:semicolon
)brace
DECL|function|usblp_disconnect
r_static
r_void
id|usblp_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|usblp
op_star
id|usblp
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usblp
op_logical_or
op_logical_neg
id|usblp-&gt;dev
)paren
(brace
id|err
c_func
(paren
l_string|&quot;disconnect on nonexisting interface&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usblp-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|usblp-&gt;readurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|usblp-&gt;writeurb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|usblp-&gt;writeurb.transfer_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usblp-&gt;used
)paren
r_return
suffix:semicolon
id|usblp_table
(braket
id|usblp-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|usblp
)paren
suffix:semicolon
)brace
DECL|variable|usblp_fops
r_static
r_struct
id|file_operations
id|usblp_fops
op_assign
(brace
id|read
suffix:colon
id|usblp_read
comma
id|write
suffix:colon
id|usblp_write
comma
id|open
suffix:colon
id|usblp_open
comma
id|release
suffix:colon
id|usblp_release
comma
id|poll
suffix:colon
id|usblp_poll
)brace
suffix:semicolon
DECL|variable|usblp_driver
r_static
r_struct
id|usb_driver
id|usblp_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;usblp&quot;
comma
id|probe
suffix:colon
id|usblp_probe
comma
id|disconnect
suffix:colon
id|usblp_disconnect
comma
id|fops
suffix:colon
op_amp
id|usblp_fops
comma
id|minor
suffix:colon
id|USBLP_MINOR_BASE
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|usblp_driver
)paren
suffix:semicolon
)brace
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
r_int
id|usb_printer_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|usblp_driver
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
