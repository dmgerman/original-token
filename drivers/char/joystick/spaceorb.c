multiline_comment|/*&n; * $Id: spaceorb.c,v 1.7 2000/05/29 11:19:51 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; * &n; *  Based on the work of:&n; *  &t;David Thompson&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * SpaceTec SpaceOrb 360 and Avenger 6dof controller driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; *  Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|SPACEORB_MAX_LENGTH
mdefine_line|#define SPACEORB_MAX_LENGTH&t;64
DECL|variable|spaceorb_buttons
r_static
r_int
id|spaceorb_buttons
(braket
)braket
op_assign
(brace
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_Y
comma
id|BTN_X
comma
id|BTN_B
comma
id|BTN_A
comma
id|BTN_MODE
)brace
suffix:semicolon
DECL|variable|spaceorb_axes
r_static
r_int
id|spaceorb_axes
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_Z
comma
id|ABS_RX
comma
id|ABS_RY
comma
id|ABS_RZ
)brace
suffix:semicolon
DECL|variable|spaceorb_name
r_static
r_char
op_star
id|spaceorb_name
op_assign
l_string|&quot;SpaceTec SpaceOrb 360&quot;
suffix:semicolon
multiline_comment|/*&n; * Per-Orb data.&n; */
DECL|struct|spaceorb
r_struct
id|spaceorb
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
DECL|member|data
r_int
r_char
id|data
(braket
id|SPACEORB_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|spaceorb_xor
r_static
r_int
r_char
id|spaceorb_xor
(braket
)braket
op_assign
l_string|&quot;SpaceWare&quot;
suffix:semicolon
DECL|variable|spaceorb_errors
r_static
r_int
r_char
op_star
id|spaceorb_errors
(braket
)braket
op_assign
(brace
l_string|&quot;EEPROM storing 0 failed&quot;
comma
l_string|&quot;Receive queue overflow&quot;
comma
l_string|&quot;Transmit queue timeout&quot;
comma
l_string|&quot;Bad packet&quot;
comma
l_string|&quot;Power brown-out&quot;
comma
l_string|&quot;EEPROM checksum error&quot;
comma
l_string|&quot;Hardware fault&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * spaceorb_process_packet() decodes packets the driver receives from the&n; * SpaceOrb.&n; */
DECL|function|spaceorb_process_packet
r_static
r_void
id|spaceorb_process_packet
c_func
(paren
r_struct
id|spaceorb
op_star
id|spaceorb
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|spaceorb-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|spaceorb-&gt;data
suffix:semicolon
r_int
r_char
id|c
op_assign
l_int|0
suffix:semicolon
r_int
id|axes
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|spaceorb-&gt;idx
OL
l_int|2
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
id|spaceorb-&gt;idx
suffix:semicolon
id|i
op_increment
)paren
id|c
op_xor_assign
id|data
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|data
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;R&squot;
suffix:colon
multiline_comment|/* Reset packet */
id|spaceorb-&gt;data
(braket
id|spaceorb-&gt;idx
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
id|spaceorb-&gt;idx
op_logical_and
id|spaceorb-&gt;data
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
id|spaceorb-&gt;dev.number
comma
id|spaceorb_name
comma
id|spaceorb-&gt;data
op_plus
id|i
comma
id|spaceorb-&gt;serio-&gt;number
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
multiline_comment|/* Ball + button data */
r_if
c_cond
(paren
id|spaceorb-&gt;idx
op_ne
l_int|12
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
l_int|9
suffix:semicolon
id|i
op_increment
)paren
id|spaceorb-&gt;data
(braket
id|i
op_plus
l_int|2
)braket
op_xor_assign
id|spaceorb_xor
(braket
id|i
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
op_assign
(paren
id|data
(braket
l_int|2
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|3
)braket
op_rshift
l_int|4
)paren
suffix:semicolon
id|axes
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|4
)braket
op_rshift
l_int|1
)paren
suffix:semicolon
id|axes
(braket
l_int|2
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|4
)braket
op_amp
l_int|0x01
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|data
(braket
l_int|5
)braket
op_lshift
l_int|2
)paren
op_or
(paren
id|data
(braket
l_int|4
)braket
op_rshift
l_int|5
)paren
suffix:semicolon
id|axes
(braket
l_int|3
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|6
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|2
)paren
suffix:semicolon
id|axes
(braket
l_int|4
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|7
)braket
op_amp
l_int|0x03
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|data
(braket
l_int|8
)braket
op_lshift
l_int|1
)paren
op_or
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
suffix:semicolon
id|axes
(braket
l_int|5
)braket
op_assign
(paren
(paren
id|data
(braket
l_int|9
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|data
(braket
l_int|10
)braket
op_rshift
l_int|3
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
id|input_report_abs
c_func
(paren
id|dev
comma
id|spaceorb_axes
(braket
id|i
)braket
comma
id|axes
(braket
id|i
)braket
op_minus
(paren
(paren
id|axes
(braket
id|i
)braket
op_amp
l_int|0x200
)paren
ques
c_cond
l_int|1024
suffix:colon
l_int|0
)paren
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|spaceorb_buttons
(braket
id|i
)braket
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;K&squot;
suffix:colon
multiline_comment|/* Button data */
r_if
c_cond
(paren
id|spaceorb-&gt;idx
op_ne
l_int|5
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|spaceorb_buttons
(braket
id|i
)braket
comma
(paren
id|data
(braket
l_int|2
)braket
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;E&squot;
suffix:colon
multiline_comment|/* Error packet */
r_if
c_cond
(paren
id|spaceorb-&gt;idx
op_ne
l_int|4
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;joy-spaceorb: Device error. [ &quot;
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|data
(braket
l_int|1
)braket
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|spaceorb_errors
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|spaceorb_interrupt
r_static
r_void
id|spaceorb_interrupt
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
id|spaceorb
op_star
id|spaceorb
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|data
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
id|spaceorb-&gt;idx
)paren
id|spaceorb_process_packet
c_func
(paren
id|spaceorb
)paren
suffix:semicolon
id|spaceorb-&gt;idx
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spaceorb-&gt;idx
OL
id|SPACEORB_MAX_LENGTH
)paren
id|spaceorb-&gt;data
(braket
id|spaceorb-&gt;idx
op_increment
)braket
op_assign
id|data
op_amp
l_int|0x7f
suffix:semicolon
)brace
multiline_comment|/*&n; * spaceorb_disconnect() is the opposite of spaceorb_connect()&n; */
DECL|function|spaceorb_disconnect
r_static
r_void
id|spaceorb_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|spaceorb
op_star
id|spaceorb
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|spaceorb-&gt;dev
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
id|spaceorb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * spaceorb_connect() is the routine that is called when someone adds a&n; * new serio device. It looks for the SpaceOrb/Avenger, and if found, registers&n; * it as an input device.&n; */
DECL|function|spaceorb_connect
r_static
r_void
id|spaceorb_connect
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
id|spaceorb
op_star
id|spaceorb
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
id|SERIO_SPACEORB
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|spaceorb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|spaceorb
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
id|spaceorb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|spaceorb
)paren
)paren
suffix:semicolon
id|spaceorb-&gt;dev.evbit
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|spaceorb_buttons
(braket
id|i
)braket
comma
op_amp
id|spaceorb-&gt;dev.keybit
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
id|spaceorb_axes
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|spaceorb-&gt;dev.absbit
)paren
suffix:semicolon
id|spaceorb-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|508
suffix:semicolon
id|spaceorb-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|508
suffix:semicolon
)brace
id|spaceorb-&gt;serio
op_assign
id|serio
suffix:semicolon
id|spaceorb-&gt;dev
dot
r_private
op_assign
id|spaceorb
suffix:semicolon
id|spaceorb-&gt;dev.name
op_assign
id|spaceorb_name
suffix:semicolon
id|spaceorb-&gt;dev.idbus
op_assign
id|BUS_RS232
suffix:semicolon
id|spaceorb-&gt;dev.idvendor
op_assign
id|SERIO_SPACEORB
suffix:semicolon
id|spaceorb-&gt;dev.idproduct
op_assign
l_int|0x0001
suffix:semicolon
id|spaceorb-&gt;dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|spaceorb
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
id|spaceorb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|spaceorb-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio device structure.&n; */
DECL|variable|spaceorb_dev
r_static
r_struct
id|serio_dev
id|spaceorb_dev
op_assign
(brace
id|interrupt
suffix:colon
id|spaceorb_interrupt
comma
id|connect
suffix:colon
id|spaceorb_connect
comma
id|disconnect
suffix:colon
id|spaceorb_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|spaceorb_init
r_int
id|__init
id|spaceorb_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|spaceorb_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|spaceorb_exit
r_void
id|__exit
id|spaceorb_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|spaceorb_dev
)paren
suffix:semicolon
)brace
DECL|variable|spaceorb_init
id|module_init
c_func
(paren
id|spaceorb_init
)paren
suffix:semicolon
DECL|variable|spaceorb_exit
id|module_exit
c_func
(paren
id|spaceorb_exit
)paren
suffix:semicolon
eof
