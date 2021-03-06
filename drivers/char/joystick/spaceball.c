multiline_comment|/*&n; * $Id: spaceball.c,v 1.7 2000/06/24 11:55:40 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *  &t;David Thompson&n; *  &t;Joseph Krahn&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * SpaceTec SpaceBall 4000 FLX driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; *  Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|JS_SBALL_MAX_LENGTH
mdefine_line|#define JS_SBALL_MAX_LENGTH&t;128
DECL|variable|spaceball_axes
r_static
r_int
id|spaceball_axes
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Z
comma
id|ABS_Y
comma
id|ABS_RX
comma
id|ABS_RZ
comma
id|ABS_RY
)brace
suffix:semicolon
DECL|variable|spaceball_name
r_static
r_char
op_star
id|spaceball_name
op_assign
l_string|&quot;SpaceTec SpaceBall 4000 FLX&quot;
suffix:semicolon
multiline_comment|/*&n; * Per-Ball data.&n; */
DECL|struct|spaceball
r_struct
id|spaceball
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|escape
r_int
id|escape
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|JS_SBALL_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * spaceball_process_packet() decodes packets the driver receives from the&n; * SpaceBall.&n; */
DECL|function|spaceball_process_packet
r_static
r_void
id|spaceball_process_packet
c_func
(paren
r_struct
id|spaceball
op_star
id|spaceball
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|spaceball-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|spaceball-&gt;data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|spaceball-&gt;idx
OL
l_int|2
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%c %d&bslash;n&quot;
comma
id|spaceball-&gt;data
(braket
l_int|0
)braket
comma
id|spaceball-&gt;idx
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|spaceball-&gt;data
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;@&squot;
suffix:colon
multiline_comment|/* Reset packet */
id|spaceball-&gt;data
(braket
id|spaceball-&gt;idx
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|spaceball-&gt;idx
op_logical_and
id|spaceball-&gt;data
(braket
id|i
)braket
op_eq
l_char|&squot; &squot;
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s [%s] on serio%d&bslash;n&quot;
comma
id|spaceball-&gt;dev.number
comma
id|spaceball_name
comma
id|spaceball-&gt;data
op_plus
id|i
comma
id|spaceball-&gt;serio-&gt;number
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
multiline_comment|/* Ball data */
r_if
c_cond
(paren
id|spaceball-&gt;idx
op_ne
l_int|15
)paren
r_return
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|spaceball_axes
(braket
id|i
)braket
comma
(paren
id|__s16
)paren
(paren
(paren
id|data
(braket
l_int|2
op_star
id|i
op_plus
l_int|3
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|2
op_star
id|i
op_plus
l_int|2
)braket
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;.&squot;
suffix:colon
multiline_comment|/* Button data, part2 */
r_if
c_cond
(paren
id|spaceball-&gt;idx
op_ne
l_int|3
)paren
r_return
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_0
comma
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_1
comma
id|data
(braket
l_int|2
)braket
op_amp
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;?&squot;
suffix:colon
multiline_comment|/* Error packet */
id|spaceball-&gt;data
(braket
id|spaceball-&gt;idx
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;spaceball: Device error. [%s]&bslash;n&quot;
comma
id|spaceball-&gt;data
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Spaceball 4000 FLX packets all start with a one letter packet-type decriptor,&n; * and end in 0x0d. It uses &squot;^&squot; as an escape for 0x0d characters which can&n; * occur in the axis values. ^M, ^Q and ^S all mean 0x0d, depending (I think)&n; * on whether the axis value is increasing, decreasing, or same as before.&n; * (I don&squot;t see why this is useful).&n; */
DECL|function|spaceball_interrupt
r_static
r_void
id|spaceball_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|spaceball
op_star
id|spaceball
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
l_int|0xd
suffix:colon
id|spaceball_process_packet
c_func
(paren
id|spaceball
)paren
suffix:semicolon
id|spaceball-&gt;idx
op_assign
l_int|0
suffix:semicolon
id|spaceball-&gt;escape
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
l_char|&squot;^&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|spaceball-&gt;escape
)paren
(brace
id|spaceball-&gt;escape
op_xor_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spaceball-&gt;escape
op_assign
l_int|0
suffix:semicolon
r_case
l_char|&squot;M&squot;
suffix:colon
r_case
l_char|&squot;Q&squot;
suffix:colon
r_case
l_char|&squot;S&squot;
suffix:colon
r_if
c_cond
(paren
id|spaceball-&gt;escape
)paren
(brace
id|spaceball-&gt;escape
op_assign
l_int|0
suffix:semicolon
id|data
op_assign
l_int|0xd
suffix:semicolon
)brace
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|spaceball-&gt;escape
)paren
(brace
id|spaceball-&gt;escape
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;spaceball.c: Unknown escaped character: %#x (%c)&bslash;n&quot;
comma
id|data
comma
id|data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spaceball-&gt;idx
OL
id|JS_SBALL_MAX_LENGTH
)paren
id|spaceball-&gt;data
(braket
id|spaceball-&gt;idx
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * spaceball_disconnect() is the opposite of spaceball_connect()&n; */
DECL|function|spaceball_disconnect
r_static
r_void
id|spaceball_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|spaceball
op_star
id|spaceball
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|spaceball-&gt;dev
)paren
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|spaceball
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * spaceball_connect() is the routine that is called when someone adds a&n; * new serio device. It looks for the Magellan, and if found, registers&n; * it as an input device.&n; */
DECL|function|spaceball_connect
r_static
r_void
id|spaceball_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|spaceball
op_star
id|spaceball
suffix:semicolon
r_int
id|i
comma
id|t
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;type
op_ne
(paren
id|SERIO_RS232
op_or
id|SERIO_SPACEBALL
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|spaceball
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|spaceball
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|spaceball
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|spaceball
)paren
)paren
suffix:semicolon
id|spaceball-&gt;dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
id|spaceball-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_0
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_0
)paren
op_or
id|BIT
c_func
(paren
id|BTN_1
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|t
op_assign
id|spaceball_axes
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|spaceball-&gt;dev.absbit
)paren
suffix:semicolon
id|spaceball-&gt;dev.absmin
(braket
id|t
)braket
op_assign
id|i
OL
l_int|3
ques
c_cond
op_minus
l_int|8000
suffix:colon
op_minus
l_int|1600
suffix:semicolon
id|spaceball-&gt;dev.absmax
(braket
id|t
)braket
op_assign
id|i
OL
l_int|3
ques
c_cond
l_int|8000
suffix:colon
l_int|1600
suffix:semicolon
id|spaceball-&gt;dev.absflat
(braket
id|t
)braket
op_assign
id|i
OL
l_int|3
ques
c_cond
l_int|40
suffix:colon
l_int|8
suffix:semicolon
id|spaceball-&gt;dev.absfuzz
(braket
id|t
)braket
op_assign
id|i
OL
l_int|3
ques
c_cond
l_int|8
suffix:colon
l_int|2
suffix:semicolon
)brace
id|spaceball-&gt;serio
op_assign
id|serio
suffix:semicolon
id|spaceball-&gt;dev
dot
r_private
op_assign
id|spaceball
suffix:semicolon
id|spaceball-&gt;dev.name
op_assign
id|spaceball_name
suffix:semicolon
id|spaceball-&gt;dev.idbus
op_assign
id|BUS_RS232
suffix:semicolon
id|spaceball-&gt;dev.idvendor
op_assign
id|SERIO_SPACEBALL
suffix:semicolon
id|spaceball-&gt;dev.idproduct
op_assign
l_int|0x0001
suffix:semicolon
id|spaceball-&gt;dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|spaceball
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|dev
)paren
)paren
(brace
id|kfree
c_func
(paren
id|spaceball
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|spaceball-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio device structure.&n; */
DECL|variable|spaceball_dev
r_static
r_struct
id|serio_dev
id|spaceball_dev
op_assign
(brace
id|interrupt
suffix:colon
id|spaceball_interrupt
comma
id|connect
suffix:colon
id|spaceball_connect
comma
id|disconnect
suffix:colon
id|spaceball_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|spaceball_init
r_int
id|__init
id|spaceball_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|spaceball_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|spaceball_exit
r_void
id|__exit
id|spaceball_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|spaceball_dev
)paren
suffix:semicolon
)brace
DECL|variable|spaceball_init
id|module_init
c_func
(paren
id|spaceball_init
)paren
suffix:semicolon
DECL|variable|spaceball_exit
id|module_exit
c_func
(paren
id|spaceball_exit
)paren
suffix:semicolon
eof
