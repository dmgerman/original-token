multiline_comment|/*&n; * $Id: input.c,v 1.7 2000/05/28 17:31:36 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  The input layer module itself&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/random.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
DECL|variable|input_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|input_register_device
)paren
suffix:semicolon
DECL|variable|input_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|input_unregister_device
)paren
suffix:semicolon
DECL|variable|input_register_handler
id|EXPORT_SYMBOL
c_func
(paren
id|input_register_handler
)paren
suffix:semicolon
DECL|variable|input_unregister_handler
id|EXPORT_SYMBOL
c_func
(paren
id|input_unregister_handler
)paren
suffix:semicolon
DECL|variable|input_register_minor
id|EXPORT_SYMBOL
c_func
(paren
id|input_register_minor
)paren
suffix:semicolon
DECL|variable|input_unregister_minor
id|EXPORT_SYMBOL
c_func
(paren
id|input_unregister_minor
)paren
suffix:semicolon
DECL|variable|input_open_device
id|EXPORT_SYMBOL
c_func
(paren
id|input_open_device
)paren
suffix:semicolon
DECL|variable|input_close_device
id|EXPORT_SYMBOL
c_func
(paren
id|input_close_device
)paren
suffix:semicolon
DECL|variable|input_event
id|EXPORT_SYMBOL
c_func
(paren
id|input_event
)paren
suffix:semicolon
DECL|macro|INPUT_MAJOR
mdefine_line|#define INPUT_MAJOR&t;13
DECL|macro|INPUT_DEVICES
mdefine_line|#define INPUT_DEVICES&t;256
DECL|variable|input_dev
r_static
r_struct
id|input_dev
op_star
id|input_dev
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|input_handler
r_static
r_struct
id|input_handler
op_star
id|input_handler
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|input_table
r_static
r_struct
id|input_handler
op_star
id|input_table
(braket
l_int|8
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
DECL|variable|input_devfs_handle
r_static
id|devfs_handle_t
id|input_devfs_handle
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|input_number
r_static
r_int
id|input_number
op_assign
l_int|0
suffix:semicolon
DECL|variable|input_devices
r_static
r_int
id|input_devices
(braket
id|NBITS
c_func
(paren
id|INPUT_DEVICES
)paren
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
DECL|function|input_event
r_void
id|input_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|input_handle
op_star
id|handle
op_assign
id|dev-&gt;handle
suffix:semicolon
multiline_comment|/*&n; * Filter non-events, and bad input values out.&n; */
r_if
c_cond
(paren
id|type
OG
id|EV_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|type
comma
id|dev-&gt;evbit
)paren
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_KEY
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|KEY_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;keybit
)paren
op_logical_or
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;key
)paren
op_eq
id|value
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|2
)paren
r_break
suffix:semicolon
id|change_bit
c_func
(paren
id|code
comma
id|dev-&gt;key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EV_REP
comma
id|dev-&gt;evbit
)paren
op_logical_and
id|dev-&gt;timer.function
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|dev-&gt;timer
comma
id|jiffies
op_plus
id|dev-&gt;rep
(braket
id|REP_DELAY
)braket
)paren
suffix:semicolon
id|dev-&gt;repeat_key
op_assign
id|code
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;repeat_key
op_eq
id|code
)paren
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_ABS
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|ABS_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;absbit
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;absfuzz
(braket
id|code
)braket
)paren
(brace
r_if
c_cond
(paren
(paren
id|value
OG
id|dev-&gt;abs
(braket
id|code
)braket
op_minus
(paren
id|dev-&gt;absfuzz
(braket
id|code
)braket
op_rshift
l_int|1
)paren
)paren
op_logical_and
(paren
id|value
OL
id|dev-&gt;abs
(braket
id|code
)braket
op_plus
(paren
id|dev-&gt;absfuzz
(braket
id|code
)braket
op_rshift
l_int|1
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
OG
id|dev-&gt;abs
(braket
id|code
)braket
op_minus
id|dev-&gt;absfuzz
(braket
id|code
)braket
)paren
op_logical_and
(paren
id|value
OL
id|dev-&gt;abs
(braket
id|code
)braket
op_plus
id|dev-&gt;absfuzz
(braket
id|code
)braket
)paren
)paren
id|value
op_assign
(paren
id|dev-&gt;abs
(braket
id|code
)braket
op_star
l_int|3
op_plus
id|value
)paren
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
OG
id|dev-&gt;abs
(braket
id|code
)braket
op_minus
(paren
id|dev-&gt;absfuzz
(braket
id|code
)braket
op_lshift
l_int|1
)paren
)paren
op_logical_and
(paren
id|value
OL
id|dev-&gt;abs
(braket
id|code
)braket
op_plus
(paren
id|dev-&gt;absfuzz
(braket
id|code
)braket
op_lshift
l_int|1
)paren
)paren
)paren
id|value
op_assign
(paren
id|dev-&gt;abs
(braket
id|code
)braket
op_plus
id|value
)paren
op_rshift
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;abs
(braket
id|code
)braket
op_eq
id|value
)paren
r_return
suffix:semicolon
id|dev-&gt;abs
(braket
id|code
)braket
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_REL
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|REL_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;relbit
)paren
op_logical_or
(paren
id|value
op_eq
l_int|0
)paren
)paren
r_return
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_LED
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|LED_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;ledbit
)paren
op_logical_or
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;led
)paren
op_eq
id|value
)paren
r_return
suffix:semicolon
id|change_bit
c_func
(paren
id|code
comma
id|dev-&gt;led
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;event
)paren
id|dev
op_member_access_from_pointer
id|event
c_func
(paren
id|dev
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_SND
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|SND_MAX
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;sndbit
)paren
op_logical_or
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|code
comma
id|dev-&gt;snd
)paren
op_eq
id|value
)paren
r_return
suffix:semicolon
id|change_bit
c_func
(paren
id|code
comma
id|dev-&gt;snd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;event
)paren
id|dev
op_member_access_from_pointer
id|event
c_func
(paren
id|dev
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_REP
suffix:colon
r_if
c_cond
(paren
id|code
OG
id|REP_MAX
op_logical_or
id|dev-&gt;rep
(braket
id|code
)braket
op_eq
id|value
)paren
r_return
suffix:semicolon
id|dev-&gt;rep
(braket
id|code
)braket
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;event
)paren
id|dev
op_member_access_from_pointer
id|event
c_func
(paren
id|dev
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Add randomness.&n; */
macro_line|#if 0 /* BUG */
id|add_input_randomness
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|dev
)paren
op_xor
(paren
id|type
op_lshift
l_int|24
)paren
op_xor
(paren
id|code
op_lshift
l_int|16
)paren
op_xor
id|value
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Distribute the event to handler modules.&n; */
r_while
c_loop
(paren
id|handle
)paren
(brace
r_if
c_cond
(paren
id|handle-&gt;open
)paren
id|handle-&gt;handler
op_member_access_from_pointer
id|event
c_func
(paren
id|handle
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
id|handle
op_assign
id|handle-&gt;dnext
suffix:semicolon
)brace
)brace
DECL|function|input_repeat_key
r_static
r_void
id|input_repeat_key
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
(paren
r_void
op_star
)paren
id|data
suffix:semicolon
id|input_event
c_func
(paren
id|dev
comma
id|EV_KEY
comma
id|dev-&gt;repeat_key
comma
l_int|2
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|dev-&gt;timer
comma
id|jiffies
op_plus
id|dev-&gt;rep
(braket
id|REP_PERIOD
)braket
)paren
suffix:semicolon
)brace
DECL|function|input_open_device
r_int
id|input_open_device
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
id|handle-&gt;open
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|handle-&gt;dev-&gt;open
)paren
r_return
id|handle-&gt;dev
op_member_access_from_pointer
id|open
c_func
(paren
id|handle-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|input_close_device
r_void
id|input_close_device
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
id|handle-&gt;dev-&gt;close
)paren
id|handle-&gt;dev
op_member_access_from_pointer
id|close
c_func
(paren
id|handle-&gt;dev
)paren
suffix:semicolon
id|handle-&gt;open
op_decrement
suffix:semicolon
)brace
DECL|function|input_link_handle
r_static
r_void
id|input_link_handle
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
id|handle-&gt;dnext
op_assign
id|handle-&gt;dev-&gt;handle
suffix:semicolon
id|handle-&gt;hnext
op_assign
id|handle-&gt;handler-&gt;handle
suffix:semicolon
id|handle-&gt;dev-&gt;handle
op_assign
id|handle
suffix:semicolon
id|handle-&gt;handler-&gt;handle
op_assign
id|handle
suffix:semicolon
)brace
DECL|function|input_unlink_handle
r_static
r_void
id|input_unlink_handle
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|input_handle
op_star
op_star
id|handleptr
suffix:semicolon
id|handleptr
op_assign
op_amp
id|handle-&gt;dev-&gt;handle
suffix:semicolon
r_while
c_loop
(paren
op_star
id|handleptr
op_logical_and
(paren
op_star
id|handleptr
op_ne
id|handle
)paren
)paren
id|handleptr
op_assign
op_amp
(paren
(paren
op_star
id|handleptr
)paren
op_member_access_from_pointer
id|dnext
)paren
suffix:semicolon
op_star
id|handleptr
op_assign
(paren
op_star
id|handleptr
)paren
op_member_access_from_pointer
id|dnext
suffix:semicolon
id|handleptr
op_assign
op_amp
id|handle-&gt;handler-&gt;handle
suffix:semicolon
r_while
c_loop
(paren
op_star
id|handleptr
op_logical_and
(paren
op_star
id|handleptr
op_ne
id|handle
)paren
)paren
id|handleptr
op_assign
op_amp
(paren
(paren
op_star
id|handleptr
)paren
op_member_access_from_pointer
id|hnext
)paren
suffix:semicolon
op_star
id|handleptr
op_assign
(paren
op_star
id|handleptr
)paren
op_member_access_from_pointer
id|hnext
suffix:semicolon
)brace
DECL|function|input_register_device
r_void
id|input_register_device
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|input_handler
op_star
id|handler
op_assign
id|input_handler
suffix:semicolon
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
multiline_comment|/*&n; * Initialize repeat timer to default values.&n; */
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
id|dev-&gt;timer.data
op_assign
(paren
r_int
)paren
id|dev
suffix:semicolon
id|dev-&gt;timer.function
op_assign
id|input_repeat_key
suffix:semicolon
id|dev-&gt;rep
(braket
id|REP_DELAY
)braket
op_assign
id|HZ
op_div
l_int|4
suffix:semicolon
id|dev-&gt;rep
(braket
id|REP_PERIOD
)braket
op_assign
id|HZ
op_div
l_int|33
suffix:semicolon
multiline_comment|/*&n; * Add the device.&n; */
r_if
c_cond
(paren
id|input_number
op_ge
id|INPUT_DEVICES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;input: ran out of input device numbers!&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;number
op_assign
id|input_number
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;number
op_assign
id|find_first_zero_bit
c_func
(paren
id|input_devices
comma
id|INPUT_DEVICES
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|dev-&gt;number
comma
id|input_devices
)paren
suffix:semicolon
)brace
id|dev-&gt;next
op_assign
id|input_dev
suffix:semicolon
id|input_dev
op_assign
id|dev
suffix:semicolon
id|input_number
op_increment
suffix:semicolon
multiline_comment|/*&n; * Notify handlers.&n; */
r_while
c_loop
(paren
id|handler
)paren
(brace
r_if
c_cond
(paren
(paren
id|handle
op_assign
id|handler
op_member_access_from_pointer
id|connect
c_func
(paren
id|handler
comma
id|dev
)paren
)paren
)paren
id|input_link_handle
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handler
op_assign
id|handler-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|input_unregister_device
r_void
id|input_unregister_device
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|input_handle
op_star
id|handle
op_assign
id|dev-&gt;handle
suffix:semicolon
r_struct
id|input_dev
op_star
op_star
id|devptr
op_assign
op_amp
id|input_dev
suffix:semicolon
r_struct
id|input_handle
op_star
id|dnext
suffix:semicolon
multiline_comment|/*&n; * Kill any pending repeat timers.&n; */
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
multiline_comment|/*&n; * Notify handlers.&n; */
r_while
c_loop
(paren
id|handle
)paren
(brace
id|dnext
op_assign
id|handle-&gt;dnext
suffix:semicolon
id|input_unlink_handle
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handle-&gt;handler
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handle
op_assign
id|dnext
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove the device.&n; */
r_while
c_loop
(paren
op_star
id|devptr
op_logical_and
(paren
op_star
id|devptr
op_ne
id|dev
)paren
)paren
id|devptr
op_assign
op_amp
(paren
(paren
op_star
id|devptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|devptr
op_assign
(paren
op_star
id|devptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|input_number
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;number
OL
id|INPUT_DEVICES
)paren
id|clear_bit
c_func
(paren
id|dev-&gt;number
comma
id|input_devices
)paren
suffix:semicolon
)brace
DECL|function|input_register_handler
r_void
id|input_register_handler
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
id|input_dev
suffix:semicolon
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
multiline_comment|/*&n; * Add minors if needed.&n; */
r_if
c_cond
(paren
id|handler-&gt;fops
op_ne
l_int|NULL
)paren
id|input_table
(braket
id|handler-&gt;minor
op_rshift
l_int|5
)braket
op_assign
id|handler
suffix:semicolon
multiline_comment|/*&n; * Add the handler.&n; */
id|handler-&gt;next
op_assign
id|input_handler
suffix:semicolon
id|input_handler
op_assign
id|handler
suffix:semicolon
multiline_comment|/*&n; * Notify it about all existing devices.&n; */
r_while
c_loop
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|handle
op_assign
id|handler
op_member_access_from_pointer
id|connect
c_func
(paren
id|handler
comma
id|dev
)paren
)paren
)paren
id|input_link_handle
c_func
(paren
id|handle
)paren
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|input_unregister_handler
r_void
id|input_unregister_handler
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
)paren
(brace
r_struct
id|input_handler
op_star
op_star
id|handlerptr
op_assign
op_amp
id|input_handler
suffix:semicolon
r_struct
id|input_handle
op_star
id|handle
op_assign
id|handler-&gt;handle
suffix:semicolon
r_struct
id|input_handle
op_star
id|hnext
suffix:semicolon
multiline_comment|/*&n; * Tell the handler to disconnect from all devices it keeps open.&n; */
r_while
c_loop
(paren
id|handle
)paren
(brace
id|hnext
op_assign
id|handle-&gt;hnext
suffix:semicolon
id|input_unlink_handle
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handler
op_member_access_from_pointer
id|disconnect
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handle
op_assign
id|hnext
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove it.&n; */
r_while
c_loop
(paren
op_star
id|handlerptr
op_logical_and
(paren
op_star
id|handlerptr
op_ne
id|handler
)paren
)paren
id|handlerptr
op_assign
op_amp
(paren
(paren
op_star
id|handlerptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|handlerptr
op_assign
(paren
op_star
id|handlerptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
multiline_comment|/*&n; * Remove minors.&n; */
r_if
c_cond
(paren
id|handler-&gt;fops
op_ne
l_int|NULL
)paren
id|input_table
(braket
id|handler-&gt;minor
op_rshift
l_int|5
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|input_open_file
r_static
r_int
id|input_open_file
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
id|input_handler
op_star
id|handler
op_assign
id|input_table
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
l_int|5
)braket
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
op_logical_or
op_logical_neg
id|handler-&gt;fops
op_logical_or
op_logical_neg
id|handler-&gt;fops-&gt;open
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|handler-&gt;fops
)paren
suffix:semicolon
id|err
op_assign
id|handler-&gt;fops
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|input_fops
r_static
r_struct
id|file_operations
id|input_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|input_open_file
comma
)brace
suffix:semicolon
DECL|function|input_register_minor
id|devfs_handle_t
id|input_register_minor
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|minor
comma
r_int
id|minor_base
)paren
(brace
r_char
id|devfs_name
(braket
l_int|16
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|devfs_name
comma
id|name
comma
id|minor
)paren
suffix:semicolon
r_return
id|devfs_register
c_func
(paren
id|input_devfs_handle
comma
id|devfs_name
comma
l_int|0
comma
id|DEVFS_FL_DEFAULT
comma
id|INPUT_MAJOR
comma
id|minor
op_plus
id|minor_base
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
l_int|0
comma
l_int|0
comma
op_amp
id|input_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|input_unregister_minor
r_void
id|input_unregister_minor
c_func
(paren
id|devfs_handle_t
id|handle
)paren
(brace
id|devfs_unregister
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
DECL|function|input_init
r_static
r_int
id|__init
id|input_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|devfs_register_chrdev
c_func
(paren
id|INPUT_MAJOR
comma
l_string|&quot;input&quot;
comma
op_amp
id|input_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;input: unable to register char major %d&quot;
comma
id|INPUT_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|input_devfs_handle
op_assign
id|devfs_mk_dir
c_func
(paren
l_int|NULL
comma
l_string|&quot;input&quot;
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|input_exit
r_static
r_void
id|__exit
id|input_exit
c_func
(paren
r_void
)paren
(brace
id|devfs_unregister
c_func
(paren
id|input_devfs_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devfs_unregister_chrdev
c_func
(paren
id|INPUT_MAJOR
comma
l_string|&quot;input&quot;
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;input: can&squot;t unregister char major %d&quot;
comma
id|INPUT_MAJOR
)paren
suffix:semicolon
)brace
DECL|variable|input_init
id|module_init
c_func
(paren
id|input_init
)paren
suffix:semicolon
DECL|variable|input_exit
id|module_exit
c_func
(paren
id|input_exit
)paren
suffix:semicolon
eof
