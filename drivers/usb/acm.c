multiline_comment|/*&n; * acm.c  Version 0.16&n; *&n; * Copyright (c) 1999 Armin Fuerst&t;&lt;fuerst@in.tum.de&gt;&n; * Copyright (c) 1999 Pavel Machek&t;&lt;pavel@suse.cz&gt;&n; * Copyright (c) 1999 Johannes Erdfelt&t;&lt;jerdfelt@valinux.com&gt;&n; * Copyright (c) 2000 Vojtech Pavlik&t;&lt;vojtech@suse.cz&gt;&n; *&n; * USB Abstract Control Model driver for USB modems and ISDN adapters&n; *&n; * Sponsored by SuSE&n; *&n; * ChangeLog:&n; *&t;v0.9  - thorough cleaning, URBification, almost a rewrite&n; *&t;v0.10 - some more cleanups&n; *&t;v0.11 - fixed flow control, read error doesn&squot;t stop reads&n; *&t;v0.12 - added TIOCM ioctls, added break handling, made struct acm kmalloced&n; *&t;v0.13 - added termios, added hangup&n; *&t;v0.14 - sized down struct acm&n; *&t;v0.15 - fixed flow control again - characters could be lost&n; *&t;v0.16 - added code for modems with swapped data and control interfaces&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/usb.h&gt;
r_void
id|tty_register_devfs
(paren
r_struct
id|tty_driver
op_star
id|driver
comma
r_int
r_int
id|flags
comma
r_int
id|minor
)paren
suffix:semicolon
r_void
id|tty_unregister_devfs
(paren
r_struct
id|tty_driver
op_star
id|driver
comma
r_int
id|minor
)paren
suffix:semicolon
multiline_comment|/*&n; * CMSPAR, some architectures can&squot;t have space and mark parity.&n; */
macro_line|#ifndef CMSPAR
DECL|macro|CMSPAR
mdefine_line|#define CMSPAR&t;&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * Major and minor numbers.&n; */
DECL|macro|ACM_TTY_MAJOR
mdefine_line|#define ACM_TTY_MAJOR&t;&t;166
DECL|macro|ACM_TTY_MINORS
mdefine_line|#define ACM_TTY_MINORS&t;&t;32
multiline_comment|/*&n; * Requests.&n; */
DECL|macro|USB_RT_ACM
mdefine_line|#define USB_RT_ACM&t;&t;(USB_TYPE_CLASS | USB_RECIP_INTERFACE)
DECL|macro|ACM_REQ_COMMAND
mdefine_line|#define ACM_REQ_COMMAND&t;&t;0x00
DECL|macro|ACM_REQ_RESPONSE
mdefine_line|#define ACM_REQ_RESPONSE&t;0x01
DECL|macro|ACM_REQ_SET_FEATURE
mdefine_line|#define ACM_REQ_SET_FEATURE&t;0x02
DECL|macro|ACM_REQ_GET_FEATURE
mdefine_line|#define ACM_REQ_GET_FEATURE&t;0x03
DECL|macro|ACM_REQ_CLEAR_FEATURE
mdefine_line|#define ACM_REQ_CLEAR_FEATURE&t;0x04
DECL|macro|ACM_REQ_SET_LINE
mdefine_line|#define ACM_REQ_SET_LINE&t;0x20
DECL|macro|ACM_REQ_GET_LINE
mdefine_line|#define ACM_REQ_GET_LINE&t;0x21
DECL|macro|ACM_REQ_SET_CONTROL
mdefine_line|#define ACM_REQ_SET_CONTROL&t;0x22
DECL|macro|ACM_REQ_SEND_BREAK
mdefine_line|#define ACM_REQ_SEND_BREAK&t;0x23
multiline_comment|/*&n; * IRQs.&n; */
DECL|macro|ACM_IRQ_NETWORK
mdefine_line|#define ACM_IRQ_NETWORK&t;&t;0x00
DECL|macro|ACM_IRQ_LINE_STATE
mdefine_line|#define ACM_IRQ_LINE_STATE&t;0x20
multiline_comment|/*&n; * Output control lines.&n; */
DECL|macro|ACM_CTRL_DTR
mdefine_line|#define ACM_CTRL_DTR&t;&t;0x01
DECL|macro|ACM_CTRL_RTS
mdefine_line|#define ACM_CTRL_RTS&t;&t;0x02
multiline_comment|/*&n; * Input control lines and line errors.&n; */
DECL|macro|ACM_CTRL_DCD
mdefine_line|#define ACM_CTRL_DCD&t;&t;0x01
DECL|macro|ACM_CTRL_DSR
mdefine_line|#define ACM_CTRL_DSR&t;&t;0x02
DECL|macro|ACM_CTRL_BRK
mdefine_line|#define ACM_CTRL_BRK&t;&t;0x04
DECL|macro|ACM_CTRL_RI
mdefine_line|#define ACM_CTRL_RI&t;&t;0x08
DECL|macro|ACM_CTRL_FRAMING
mdefine_line|#define ACM_CTRL_FRAMING&t;0x10
DECL|macro|ACM_CTRL_PARITY
mdefine_line|#define ACM_CTRL_PARITY&t;&t;0x20
DECL|macro|ACM_CTRL_OVERRUN
mdefine_line|#define ACM_CTRL_OVERRUN&t;0x40
multiline_comment|/*&n; * Line speed and caracter encoding.&n; */
DECL|struct|acm_line
r_struct
id|acm_line
(brace
DECL|member|speed
id|__u32
id|speed
suffix:semicolon
DECL|member|stopbits
id|__u8
id|stopbits
suffix:semicolon
DECL|member|parity
id|__u8
id|parity
suffix:semicolon
DECL|member|databits
id|__u8
id|databits
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal driver structures.&n; */
DECL|struct|acm
r_struct
id|acm
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* the coresponding usb device */
DECL|member|iface
r_struct
id|usb_interface
op_star
id|iface
suffix:semicolon
multiline_comment|/* the interfaces - +0 control +1 data */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* the coresponding tty */
DECL|member|ctrlurb
DECL|member|readurb
DECL|member|writeurb
r_struct
id|urb
id|ctrlurb
comma
id|readurb
comma
id|writeurb
suffix:semicolon
multiline_comment|/* urbs */
DECL|member|line
r_struct
id|acm_line
id|line
suffix:semicolon
multiline_comment|/* line coding (bits, stop, parity) */
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
multiline_comment|/* task queue for line discipline waking up */
DECL|member|ctrlin
r_int
r_int
id|ctrlin
suffix:semicolon
multiline_comment|/* input control lines (DCD, DSR, RI, break, overruns) */
DECL|member|ctrlout
r_int
r_int
id|ctrlout
suffix:semicolon
multiline_comment|/* output control lines (DTR, RTS) */
DECL|member|writesize
r_int
r_int
id|writesize
suffix:semicolon
multiline_comment|/* max packet size for the output bulk endpoint */
DECL|member|used
r_int
r_int
id|used
suffix:semicolon
multiline_comment|/* someone has this acm&squot;s device open */
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
multiline_comment|/* acm minor number */
DECL|member|throttle
r_int
r_char
id|throttle
suffix:semicolon
multiline_comment|/* throttled by tty layer */
DECL|member|clocal
r_int
r_char
id|clocal
suffix:semicolon
multiline_comment|/* termios CLOCAL */
)brace
suffix:semicolon
DECL|variable|acm_driver
r_static
r_struct
id|usb_driver
id|acm_driver
suffix:semicolon
DECL|variable|acm_tty_driver
r_static
r_struct
id|tty_driver
id|acm_tty_driver
suffix:semicolon
DECL|variable|acm_table
r_static
r_struct
id|acm
op_star
id|acm_table
(braket
id|ACM_TTY_MINORS
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* .... */
)brace
suffix:semicolon
DECL|macro|ACM_READY
mdefine_line|#define ACM_READY(acm)&t;(acm &amp;&amp; acm-&gt;dev &amp;&amp; acm-&gt;used)
multiline_comment|/*&n; * Functions for ACM control messages.&n; */
DECL|function|acm_ctrl_msg
r_static
r_int
id|acm_ctrl_msg
c_func
(paren
r_struct
id|acm
op_star
id|acm
comma
r_int
id|request
comma
r_int
id|value
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
id|acm-&gt;dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|acm-&gt;dev
comma
l_int|0
)paren
comma
id|request
comma
id|USB_RT_ACM
comma
id|value
comma
id|acm-&gt;iface
(braket
l_int|0
)braket
dot
id|altsetting
(braket
l_int|0
)braket
dot
id|bInterfaceNumber
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
l_string|&quot;acm_control_msg: rq: 0x%02x val: %#x len: %#x result: %d&quot;
comma
id|request
comma
id|value
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
DECL|macro|acm_set_control
mdefine_line|#define acm_set_control(acm, control)&t;acm_ctrl_msg(acm, ACM_REQ_SET_CONTROL, control, NULL, 0)
DECL|macro|acm_set_line
mdefine_line|#define acm_set_line(acm, line)&t;&t;acm_ctrl_msg(acm, ACM_REQ_SET_LINE, 0, line, sizeof(struct acm_line))
DECL|macro|acm_send_break
mdefine_line|#define acm_send_break(acm, ms)&t;&t;acm_ctrl_msg(acm, ACM_REQ_SEND_BREAK, ms, NULL, 0)
multiline_comment|/*&n; * Interrupt handler for various ACM control events&n; */
DECL|function|acm_ctrl_irq
r_static
r_void
id|acm_ctrl_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|urb-&gt;context
suffix:semicolon
id|devrequest
op_star
id|dr
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|dr
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|newctrl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;nonzero ctrl irq status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dr-&gt;request
)paren
(brace
r_case
id|ACM_IRQ_NETWORK
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s network&quot;
comma
id|data
(braket
l_int|0
)braket
ques
c_cond
l_string|&quot;connected to&quot;
suffix:colon
l_string|&quot;disconnected from&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ACM_IRQ_LINE_STATE
suffix:colon
id|newctrl
op_assign
id|le16_to_cpup
c_func
(paren
(paren
id|__u16
op_star
)paren
id|data
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Please someone tell me how to do this properly to kill pppd and not kill minicom */
r_if
c_cond
(paren
id|acm-&gt;tty
op_logical_and
op_logical_neg
id|acm-&gt;clocal
op_logical_and
(paren
id|acm-&gt;ctrlin
op_amp
op_complement
id|newctrl
op_amp
id|ACM_CTRL_DCD
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;calling hangup&quot;
)paren
suffix:semicolon
id|tty_hangup
c_func
(paren
id|acm-&gt;tty
)paren
suffix:semicolon
)brace
macro_line|#endif
id|acm-&gt;ctrlin
op_assign
id|newctrl
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;input control lines: dcd%c dsr%c break%c ring%c framing%c parity%c overrun%c&quot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_DCD
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_DSR
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_BRK
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_RI
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_FRAMING
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_PARITY
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_OVERRUN
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;unknown control event received: request %d index %d len %d data0 %d data1 %d&quot;
comma
id|dr-&gt;request
comma
id|dr-&gt;index
comma
id|dr-&gt;length
comma
id|data
(braket
l_int|0
)braket
comma
id|data
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|acm_read_bulk
r_static
r_void
id|acm_read_bulk
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|urb-&gt;context
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|acm-&gt;tty
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
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
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
id|dbg
c_func
(paren
l_string|&quot;nonzero read bulk status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb-&gt;status
op_amp
op_logical_neg
id|acm-&gt;throttle
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|urb-&gt;actual_length
op_logical_and
op_logical_neg
id|acm-&gt;throttle
suffix:semicolon
id|i
op_increment
)paren
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
id|data
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acm-&gt;throttle
)paren
(brace
id|memmove
c_func
(paren
id|data
comma
id|data
op_plus
id|i
comma
id|urb-&gt;actual_length
op_minus
id|i
)paren
suffix:semicolon
id|urb-&gt;actual_length
op_sub_assign
id|i
suffix:semicolon
r_return
suffix:semicolon
)brace
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|urb
)paren
)paren
id|dbg
c_func
(paren
l_string|&quot;failed resubmitting read urb&quot;
)paren
suffix:semicolon
)brace
DECL|function|acm_write_bulk
r_static
r_void
id|acm_write_bulk
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
(paren
r_struct
id|acm
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
id|dbg
c_func
(paren
l_string|&quot;nonzero write bulk status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|queue_task
c_func
(paren
op_amp
id|acm-&gt;tqueue
comma
op_amp
id|tq_scheduler
)paren
suffix:semicolon
)brace
DECL|function|acm_softint
r_static
r_void
id|acm_softint
c_func
(paren
r_void
op_star
r_private
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
r_private
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|acm-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tty-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
)paren
op_logical_and
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TTY handlers&n; */
DECL|function|acm_tty_open
r_static
r_int
id|acm_tty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|acm_table
(braket
id|MINOR
c_func
(paren
id|tty-&gt;device
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acm
op_logical_or
op_logical_neg
id|acm-&gt;dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tty-&gt;driver_data
op_assign
id|acm
suffix:semicolon
id|acm-&gt;tty
op_assign
id|tty
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|acm-&gt;used
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|acm-&gt;ctrlurb
)paren
)paren
id|dbg
c_func
(paren
l_string|&quot;usb_submit_urb(ctrl irq) failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|acm-&gt;readurb
)paren
)paren
id|dbg
c_func
(paren
l_string|&quot;usb_submit_urb(read bulk) failed&quot;
)paren
suffix:semicolon
id|acm_set_control
c_func
(paren
id|acm
comma
id|acm-&gt;ctrlout
op_assign
id|ACM_CTRL_DTR
op_or
id|ACM_CTRL_RTS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acm_tty_close
r_static
r_void
id|acm_tty_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acm
op_logical_or
op_logical_neg
id|acm-&gt;used
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|acm-&gt;used
)paren
(brace
r_if
c_cond
(paren
id|acm-&gt;dev
)paren
(brace
id|acm_set_control
c_func
(paren
id|acm
comma
id|acm-&gt;ctrlout
op_assign
l_int|0
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;ctrlurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;writeurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;readurb
)paren
suffix:semicolon
)brace
r_else
(brace
id|tty_unregister_devfs
c_func
(paren
op_amp
id|acm_tty_driver
comma
id|acm-&gt;minor
)paren
suffix:semicolon
id|acm_table
(braket
id|acm-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|acm
)paren
suffix:semicolon
)brace
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|acm_tty_write
r_static
r_int
id|acm_tty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|acm-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
)paren
r_return
l_int|0
suffix:semicolon
id|count
op_assign
(paren
id|count
OG
id|acm-&gt;writesize
)paren
ques
c_cond
id|acm-&gt;writesize
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
id|copy_from_user
c_func
(paren
id|acm-&gt;writeurb.transfer_buffer
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|acm-&gt;writeurb.transfer_buffer
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|acm-&gt;writeurb.transfer_buffer_length
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|acm-&gt;writeurb
)paren
)paren
id|dbg
c_func
(paren
l_string|&quot;usb_submit_urb(write bulk) failed&quot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|acm_tty_write_room
r_static
r_int
id|acm_tty_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|acm-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
ques
c_cond
l_int|0
suffix:colon
id|acm-&gt;writesize
suffix:semicolon
)brace
DECL|function|acm_tty_chars_in_buffer
r_static
r_int
id|acm_tty_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|acm-&gt;writeurb.status
op_eq
op_minus
id|EINPROGRESS
ques
c_cond
id|acm-&gt;writeurb.transfer_buffer_length
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|acm_tty_throttle
r_static
r_void
id|acm_tty_throttle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
id|acm-&gt;throttle
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|acm_tty_unthrottle
r_static
r_void
id|acm_tty_unthrottle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
id|acm-&gt;throttle
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|acm-&gt;readurb.status
op_ne
op_minus
id|EINPROGRESS
)paren
id|acm_read_bulk
c_func
(paren
op_amp
id|acm-&gt;readurb
)paren
suffix:semicolon
)brace
DECL|function|acm_tty_break_ctl
r_static
r_void
id|acm_tty_break_ctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|state
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|acm_send_break
c_func
(paren
id|acm
comma
id|state
ques
c_cond
l_int|0xffff
suffix:colon
l_int|0
)paren
)paren
id|dbg
c_func
(paren
l_string|&quot;send break failed&quot;
)paren
suffix:semicolon
)brace
DECL|function|acm_tty_ioctl
r_static
r_int
id|acm_tty_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_int
r_int
id|retval
comma
id|mask
comma
id|newctrl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMGET
suffix:colon
r_return
id|put_user
c_func
(paren
(paren
id|acm-&gt;ctrlout
op_amp
id|ACM_CTRL_DTR
ques
c_cond
id|TIOCM_DTR
suffix:colon
l_int|0
)paren
op_or
(paren
id|acm-&gt;ctrlout
op_amp
id|ACM_CTRL_RTS
ques
c_cond
id|TIOCM_RTS
suffix:colon
l_int|0
)paren
op_or
(paren
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_DSR
ques
c_cond
id|TIOCM_DSR
suffix:colon
l_int|0
)paren
op_or
(paren
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_RI
ques
c_cond
id|TIOCM_RI
suffix:colon
l_int|0
)paren
op_or
(paren
id|acm-&gt;ctrlin
op_amp
id|ACM_CTRL_DCD
ques
c_cond
id|TIOCM_CD
suffix:colon
l_int|0
)paren
op_or
id|TIOCM_CTS
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|TIOCMSET
suffix:colon
r_case
id|TIOCMBIS
suffix:colon
r_case
id|TIOCMBIC
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|mask
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
id|newctrl
op_assign
id|acm-&gt;ctrlout
suffix:semicolon
id|mask
op_assign
(paren
id|mask
op_amp
id|TIOCM_DTR
ques
c_cond
id|ACM_CTRL_DTR
suffix:colon
l_int|0
)paren
op_or
(paren
id|mask
op_amp
id|TIOCM_RTS
ques
c_cond
id|ACM_CTRL_RTS
suffix:colon
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMSET
suffix:colon
id|newctrl
op_assign
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMBIS
suffix:colon
id|newctrl
op_or_assign
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMBIC
suffix:colon
id|newctrl
op_and_assign
op_complement
id|mask
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acm-&gt;ctrlout
op_eq
id|newctrl
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|acm_set_control
c_func
(paren
id|acm
comma
id|acm-&gt;ctrlout
op_assign
id|newctrl
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|variable|acm_tty_speed
r_static
id|__u32
id|acm_tty_speed
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|50
comma
l_int|75
comma
l_int|110
comma
l_int|134
comma
l_int|150
comma
l_int|200
comma
l_int|300
comma
l_int|600
comma
l_int|1200
comma
l_int|1800
comma
l_int|2400
comma
l_int|4800
comma
l_int|9600
comma
l_int|19200
comma
l_int|38400
comma
l_int|57600
comma
l_int|115200
comma
l_int|230400
comma
l_int|460800
comma
l_int|500000
comma
l_int|576000
comma
l_int|921600
comma
l_int|1000000
comma
l_int|1152000
comma
l_int|1500000
comma
l_int|2000000
comma
l_int|2500000
comma
l_int|3000000
comma
l_int|3500000
comma
l_int|4000000
)brace
suffix:semicolon
DECL|variable|acm_tty_size
r_static
id|__u8
id|acm_tty_size
(braket
)braket
op_assign
(brace
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
)brace
suffix:semicolon
DECL|function|acm_tty_set_termios
r_static
r_void
id|acm_tty_set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|termios_old
)paren
(brace
r_struct
id|acm
op_star
id|acm
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_struct
id|termios
op_star
id|termios
op_assign
id|tty-&gt;termios
suffix:semicolon
r_struct
id|acm_line
id|newline
suffix:semicolon
r_int
id|newctrl
op_assign
id|acm-&gt;ctrlout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACM_READY
c_func
(paren
id|acm
)paren
)paren
r_return
suffix:semicolon
id|newline.speed
op_assign
id|cpu_to_le32p
c_func
(paren
id|acm_tty_speed
op_plus
(paren
id|termios-&gt;c_cflag
op_amp
id|CBAUD
op_amp
op_complement
id|CBAUDEX
)paren
op_plus
(paren
id|termios-&gt;c_cflag
op_amp
id|CBAUDEX
ques
c_cond
l_int|15
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|newline.stopbits
op_assign
id|termios-&gt;c_cflag
op_amp
id|CSTOPB
ques
c_cond
l_int|2
suffix:colon
l_int|0
suffix:semicolon
id|newline.parity
op_assign
id|termios-&gt;c_cflag
op_amp
id|PARENB
ques
c_cond
(paren
id|termios-&gt;c_cflag
op_amp
id|PARODD
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
op_plus
(paren
id|termios-&gt;c_cflag
op_amp
id|CMSPAR
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:colon
l_int|0
suffix:semicolon
id|newline.databits
op_assign
id|acm_tty_size
(braket
(paren
id|termios-&gt;c_cflag
op_amp
id|CSIZE
)paren
op_rshift
l_int|4
)braket
suffix:semicolon
id|acm-&gt;clocal
op_assign
id|termios-&gt;c_cflag
op_amp
id|CLOCAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newline.speed
)paren
(brace
id|newline.speed
op_assign
id|acm-&gt;line.speed
suffix:semicolon
id|newctrl
op_and_assign
op_complement
id|ACM_CTRL_DTR
suffix:semicolon
)brace
r_else
id|newctrl
op_or_assign
id|ACM_CTRL_DTR
suffix:semicolon
r_if
c_cond
(paren
id|newctrl
op_ne
id|acm-&gt;ctrlout
)paren
id|acm_set_control
c_func
(paren
id|acm
comma
id|acm-&gt;ctrlout
op_assign
id|newctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|acm-&gt;line
comma
op_amp
id|newline
comma
r_sizeof
(paren
r_struct
id|acm_line
)paren
)paren
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|acm-&gt;line
comma
op_amp
id|newline
comma
r_sizeof
(paren
r_struct
id|acm_line
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;set line: %d %d %d %d&quot;
comma
id|newline.speed
comma
id|newline.stopbits
comma
id|newline.parity
comma
id|newline.databits
)paren
suffix:semicolon
id|acm_set_line
c_func
(paren
id|acm
comma
op_amp
id|acm-&gt;line
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * USB probe and disconnect routines.&n; */
DECL|function|acm_probe
r_static
r_void
op_star
id|acm_probe
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
id|acm
op_star
id|acm
suffix:semicolon
r_struct
id|usb_config_descriptor
op_star
id|cfacm
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|ifcom
comma
op_star
id|ifdata
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|epctrl
comma
op_star
id|epread
comma
op_star
id|epwrite
suffix:semicolon
r_int
id|readsize
comma
id|ctrlsize
comma
id|minor
comma
id|i
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;descriptor.bDeviceClass
op_ne
l_int|2
op_logical_or
id|dev-&gt;descriptor.bDeviceSubClass
op_ne
l_int|0
op_logical_or
id|dev-&gt;descriptor.bDeviceProtocol
op_ne
l_int|0
)paren
r_return
l_int|NULL
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
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cfacm
op_assign
id|dev-&gt;config
op_plus
id|i
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;probing config %d&quot;
comma
id|cfacm-&gt;bConfigurationValue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfacm-&gt;bNumInterfaces
op_ne
l_int|2
op_logical_or
id|usb_interface_claimed
c_func
(paren
id|cfacm-&gt;interface
op_plus
l_int|0
)paren
op_logical_or
id|usb_interface_claimed
c_func
(paren
id|cfacm-&gt;interface
op_plus
l_int|1
)paren
)paren
r_continue
suffix:semicolon
id|ifcom
op_assign
id|cfacm-&gt;interface
(braket
l_int|0
)braket
dot
id|altsetting
op_plus
l_int|0
suffix:semicolon
id|ifdata
op_assign
id|cfacm-&gt;interface
(braket
l_int|1
)braket
dot
id|altsetting
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ifdata-&gt;bInterfaceClass
op_ne
l_int|10
op_logical_or
id|ifdata-&gt;bNumEndpoints
op_ne
l_int|2
)paren
(brace
id|ifcom
op_assign
id|cfacm-&gt;interface
(braket
l_int|1
)braket
dot
id|altsetting
op_plus
l_int|0
suffix:semicolon
id|ifdata
op_assign
id|cfacm-&gt;interface
(braket
l_int|0
)braket
dot
id|altsetting
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ifdata-&gt;bInterfaceClass
op_ne
l_int|10
op_logical_or
id|ifdata-&gt;bNumEndpoints
op_ne
l_int|2
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifcom-&gt;bInterfaceClass
op_ne
l_int|2
op_logical_or
id|ifcom-&gt;bInterfaceSubClass
op_ne
l_int|2
op_logical_or
id|ifcom-&gt;bInterfaceProtocol
op_ne
l_int|1
op_logical_or
id|ifcom-&gt;bNumEndpoints
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
id|epctrl
op_assign
id|ifcom-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
id|epread
op_assign
id|ifdata-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
id|epwrite
op_assign
id|ifdata-&gt;endpoint
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|epctrl-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_ne
l_int|0x80
op_logical_or
(paren
id|epctrl-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|3
op_logical_or
(paren
id|epread-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|2
op_logical_or
(paren
id|epwrite-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|2
op_logical_or
(paren
(paren
id|epread-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_xor
(paren
id|epwrite-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
)paren
op_ne
l_int|0x80
)paren
r_continue
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
id|epread
op_assign
id|ifdata-&gt;endpoint
op_plus
l_int|1
suffix:semicolon
id|epwrite
op_assign
id|ifdata-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
)brace
id|usb_set_configuration
c_func
(paren
id|dev
comma
id|cfacm-&gt;bConfigurationValue
)paren
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
id|ACM_TTY_MINORS
op_logical_and
id|acm_table
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
id|acm_table
(braket
id|minor
)braket
)paren
(brace
id|err
c_func
(paren
l_string|&quot;no more free acm devices&quot;
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
id|acm
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acm
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
id|acm
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acm
)paren
)paren
suffix:semicolon
id|ctrlsize
op_assign
id|epctrl-&gt;wMaxPacketSize
suffix:semicolon
id|readsize
op_assign
id|epread-&gt;wMaxPacketSize
suffix:semicolon
id|acm-&gt;writesize
op_assign
id|epwrite-&gt;wMaxPacketSize
suffix:semicolon
id|acm-&gt;iface
op_assign
id|cfacm-&gt;interface
suffix:semicolon
id|acm-&gt;minor
op_assign
id|minor
suffix:semicolon
id|acm-&gt;dev
op_assign
id|dev
suffix:semicolon
id|acm-&gt;tqueue.routine
op_assign
id|acm_softint
suffix:semicolon
id|acm-&gt;tqueue.data
op_assign
id|acm
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
id|ctrlsize
op_plus
id|readsize
op_plus
id|acm-&gt;writesize
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
id|acm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|FILL_INT_URB
c_func
(paren
op_amp
id|acm-&gt;ctrlurb
comma
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|epctrl-&gt;bEndpointAddress
)paren
comma
id|buf
comma
id|ctrlsize
comma
id|acm_ctrl_irq
comma
id|acm
comma
id|epctrl-&gt;bInterval
)paren
suffix:semicolon
id|FILL_BULK_URB
c_func
(paren
op_amp
id|acm-&gt;readurb
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
op_add_assign
id|ctrlsize
comma
id|readsize
comma
id|acm_read_bulk
comma
id|acm
)paren
suffix:semicolon
id|FILL_BULK_URB
c_func
(paren
op_amp
id|acm-&gt;writeurb
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
op_add_assign
id|readsize
comma
id|acm-&gt;writesize
comma
id|acm_write_bulk
comma
id|acm
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ttyACM%d: USB ACM device&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
id|acm_set_control
c_func
(paren
id|acm
comma
id|acm-&gt;ctrlout
)paren
suffix:semicolon
id|acm-&gt;line.speed
op_assign
id|cpu_to_le32
c_func
(paren
l_int|9600
)paren
suffix:semicolon
id|acm-&gt;line.databits
op_assign
l_int|8
suffix:semicolon
id|acm_set_line
c_func
(paren
id|acm
comma
op_amp
id|acm-&gt;line
)paren
suffix:semicolon
id|usb_driver_claim_interface
c_func
(paren
op_amp
id|acm_driver
comma
id|acm-&gt;iface
op_plus
l_int|0
comma
id|acm
)paren
suffix:semicolon
id|usb_driver_claim_interface
c_func
(paren
op_amp
id|acm_driver
comma
id|acm-&gt;iface
op_plus
l_int|1
comma
id|acm
)paren
suffix:semicolon
id|tty_register_devfs
c_func
(paren
op_amp
id|acm_tty_driver
comma
l_int|0
comma
id|minor
)paren
suffix:semicolon
r_return
id|acm_table
(braket
id|minor
)braket
op_assign
id|acm
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|acm_disconnect
r_static
r_void
id|acm_disconnect
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
id|acm
op_star
id|acm
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acm
op_logical_or
op_logical_neg
id|acm-&gt;dev
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;disconnect on nonexisting interface&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|acm-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;ctrlurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;readurb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|acm-&gt;writeurb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|acm-&gt;ctrlurb.transfer_buffer
)paren
suffix:semicolon
id|usb_driver_release_interface
c_func
(paren
op_amp
id|acm_driver
comma
id|acm-&gt;iface
op_plus
l_int|0
)paren
suffix:semicolon
id|usb_driver_release_interface
c_func
(paren
op_amp
id|acm_driver
comma
id|acm-&gt;iface
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acm-&gt;used
)paren
(brace
id|tty_unregister_devfs
c_func
(paren
op_amp
id|acm_tty_driver
comma
id|acm-&gt;minor
)paren
suffix:semicolon
id|acm_table
(braket
id|acm-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|acm
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acm-&gt;tty
)paren
id|tty_hangup
c_func
(paren
id|acm-&gt;tty
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * USB driver structure.&n; */
DECL|variable|acm_driver
r_static
r_struct
id|usb_driver
id|acm_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;acm&quot;
comma
id|probe
suffix:colon
id|acm_probe
comma
id|disconnect
suffix:colon
id|acm_disconnect
)brace
suffix:semicolon
multiline_comment|/*&n; * TTY driver structures.&n; */
DECL|variable|acm_tty_refcount
r_static
r_int
id|acm_tty_refcount
suffix:semicolon
DECL|variable|acm_tty_table
r_static
r_struct
id|tty_struct
op_star
id|acm_tty_table
(braket
id|ACM_TTY_MINORS
)braket
suffix:semicolon
DECL|variable|acm_tty_termios
r_static
r_struct
id|termios
op_star
id|acm_tty_termios
(braket
id|ACM_TTY_MINORS
)braket
suffix:semicolon
DECL|variable|acm_tty_termios_locked
r_static
r_struct
id|termios
op_star
id|acm_tty_termios_locked
(braket
id|ACM_TTY_MINORS
)braket
suffix:semicolon
DECL|variable|acm_tty_driver
r_static
r_struct
id|tty_driver
id|acm_tty_driver
op_assign
(brace
id|magic
suffix:colon
id|TTY_DRIVER_MAGIC
comma
id|driver_name
suffix:colon
l_string|&quot;acm&quot;
comma
id|name
suffix:colon
l_string|&quot;usb/acm/%d&quot;
comma
id|major
suffix:colon
id|ACM_TTY_MAJOR
comma
id|minor_start
suffix:colon
l_int|0
comma
id|num
suffix:colon
id|ACM_TTY_MINORS
comma
id|type
suffix:colon
id|TTY_DRIVER_TYPE_SERIAL
comma
id|subtype
suffix:colon
id|SERIAL_TYPE_NORMAL
comma
id|flags
suffix:colon
id|TTY_DRIVER_REAL_RAW
op_or
id|TTY_DRIVER_NO_DEVFS
comma
id|refcount
suffix:colon
op_amp
id|acm_tty_refcount
comma
id|table
suffix:colon
id|acm_tty_table
comma
id|termios
suffix:colon
id|acm_tty_termios
comma
id|termios_locked
suffix:colon
id|acm_tty_termios_locked
comma
id|open
suffix:colon
id|acm_tty_open
comma
id|close
suffix:colon
id|acm_tty_close
comma
id|write
suffix:colon
id|acm_tty_write
comma
id|write_room
suffix:colon
id|acm_tty_write_room
comma
id|ioctl
suffix:colon
id|acm_tty_ioctl
comma
id|throttle
suffix:colon
id|acm_tty_throttle
comma
id|unthrottle
suffix:colon
id|acm_tty_unthrottle
comma
id|chars_in_buffer
suffix:colon
id|acm_tty_chars_in_buffer
comma
id|break_ctl
suffix:colon
id|acm_tty_break_ctl
comma
id|set_termios
suffix:colon
id|acm_tty_set_termios
)brace
suffix:semicolon
multiline_comment|/*&n; * Init / exit.&n; */
DECL|function|acm_init
r_static
r_int
id|__init
id|acm_init
c_func
(paren
r_void
)paren
(brace
id|acm_tty_driver.init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|acm_tty_driver.init_termios.c_cflag
op_assign
id|B9600
op_or
id|CS8
op_or
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
op_amp
id|acm_tty_driver
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|acm_driver
)paren
OL
l_int|0
)paren
(brace
id|tty_unregister_driver
c_func
(paren
op_amp
id|acm_tty_driver
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acm_exit
r_static
r_void
id|__exit
id|acm_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|acm_driver
)paren
suffix:semicolon
id|tty_unregister_driver
c_func
(paren
op_amp
id|acm_tty_driver
)paren
suffix:semicolon
)brace
DECL|variable|acm_init
id|module_init
c_func
(paren
id|acm_init
)paren
suffix:semicolon
DECL|variable|acm_exit
id|module_exit
c_func
(paren
id|acm_exit
)paren
suffix:semicolon
eof
