multiline_comment|/*&n; *  joy-analog.c  Version 1.2&n; *&n; *  Copyright (c) 1996-1998 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This is a module for the Linux joystick driver, supporting&n; * up to two analog (or CHF/FCS) joysticks on a single joystick port.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/joystick.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|JS_AN_MAX_TIME
mdefine_line|#define JS_AN_MAX_TIME 3000
DECL|variable|__initdata
r_static
r_int
id|js_an_port_list
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x201
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|js_port
op_star
id|js_an_port
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|js_an
comma
l_string|&quot;2-24i&quot;
)paren
suffix:semicolon
DECL|variable|js_an
r_static
r_int
id|js_an
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#include &quot;joy-analog.h&quot;
multiline_comment|/*&n; * js_an_read() reads analog joystick data.&n; */
DECL|function|js_an_read
r_static
r_int
id|js_an_read
c_func
(paren
r_void
op_star
id|xinfo
comma
r_int
op_star
op_star
id|axes
comma
r_int
op_star
op_star
id|buttons
)paren
(brace
r_struct
id|js_an_info
op_star
id|info
op_assign
id|xinfo
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|time
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
id|u
comma
id|v
comma
id|a
suffix:semicolon
r_int
r_int
id|t
comma
id|t1
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|timeout
suffix:semicolon
r_int
id|io
op_assign
id|info-&gt;io
suffix:semicolon
id|timeout
op_assign
(paren
id|JS_AN_MAX_TIME
op_star
id|js_time_speed_a
)paren
op_rshift
l_int|10
suffix:semicolon
id|info-&gt;buttons
op_assign
(paren
op_complement
id|inb
c_func
(paren
id|io
)paren
op_amp
id|JS_AN_BUTTONS_STD
)paren
op_rshift
l_int|4
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|u
op_assign
id|a
op_assign
(paren
(paren
id|info-&gt;mask
(braket
l_int|0
)braket
op_or
id|info-&gt;mask
(braket
l_int|1
)braket
)paren
op_amp
id|JS_AN_AXES_STD
)paren
op_or
(paren
id|info-&gt;extensions
op_amp
id|JS_AN_HAT_FCS
)paren
op_or
(paren
(paren
id|info-&gt;extensions
op_amp
id|JS_AN_BUTTONS_PXY_XY
)paren
op_rshift
l_int|2
)paren
op_or
(paren
(paren
id|info-&gt;extensions
op_amp
id|JS_AN_BUTTONS_PXY_UV
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|io
)paren
suffix:semicolon
id|t
op_assign
id|js_get_time_a
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|v
op_assign
id|inb
c_func
(paren
id|io
)paren
op_amp
id|a
suffix:semicolon
id|t1
op_assign
id|js_get_time_a
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|u
op_xor
id|v
)paren
(brace
id|time
(braket
id|i
)braket
op_assign
id|js_delta_a
c_func
(paren
id|t1
comma
id|t
)paren
suffix:semicolon
id|buf
(braket
id|i
)braket
op_assign
id|u
op_xor
id|v
suffix:semicolon
id|u
op_assign
id|v
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|v
op_logical_and
id|js_delta_a
c_func
(paren
id|t1
comma
id|t
)paren
OL
id|timeout
)paren
suffix:semicolon
r_for
c_loop
(paren
op_decrement
id|i
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|4
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_amp
(paren
l_int|1
op_lshift
id|j
)paren
)paren
id|info-&gt;axes
(braket
id|j
)braket
op_assign
(paren
id|time
(braket
id|i
)braket
op_lshift
l_int|10
)paren
op_div
id|js_time_speed_a
suffix:semicolon
id|js_an_decode
c_func
(paren
id|info
comma
id|axes
comma
id|buttons
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * js_an_open() is a callback from the file open routine.&n; */
DECL|function|js_an_open
r_static
r_int
id|js_an_open
c_func
(paren
r_struct
id|js_dev
op_star
id|jd
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * js_an_close() is a callback from the file release routine.&n; */
DECL|function|js_an_close
r_static
r_int
id|js_an_close
c_func
(paren
r_struct
id|js_dev
op_star
id|jd
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * js_an_probe() probes for analog joysticks.&n; */
DECL|function|js_an_probe
r_static
r_struct
id|js_port
id|__init
op_star
id|js_an_probe
c_func
(paren
r_int
id|io
comma
r_int
id|mask0
comma
r_int
id|mask1
comma
r_struct
id|js_port
op_star
id|port
)paren
(brace
r_struct
id|js_an_info
id|info
suffix:semicolon
r_int
id|i
comma
id|numdev
suffix:semicolon
r_int
r_char
id|u
suffix:semicolon
r_if
c_cond
(paren
id|io
OL
l_int|0
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|io
comma
l_int|1
)paren
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u
op_assign
id|inb
c_func
(paren
id|io
)paren
)paren
op_amp
l_int|3
)paren
op_eq
l_int|3
)paren
r_return
id|port
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|io
)paren
suffix:semicolon
id|u
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|JS_AN_MAX_TIME
)paren
suffix:semicolon
id|u
op_assign
(paren
id|inb
c_func
(paren
id|io
)paren
op_xor
id|u
)paren
op_amp
id|u
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|u
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
id|u
op_amp
l_int|0xf0
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
(paren
id|numdev
op_assign
id|js_an_probe_devs
c_func
(paren
op_amp
id|info
comma
id|u
comma
id|mask0
comma
id|mask1
comma
id|port
)paren
)paren
op_le
l_int|0
)paren
r_return
id|port
suffix:semicolon
id|info.io
op_assign
id|io
suffix:semicolon
id|request_region
c_func
(paren
id|info.io
comma
l_int|1
comma
l_string|&quot;joystick (analog)&quot;
)paren
suffix:semicolon
id|port
op_assign
id|js_register_port
c_func
(paren
id|port
comma
op_amp
id|info
comma
id|numdev
comma
r_sizeof
(paren
r_struct
id|js_an_info
)paren
comma
id|js_an_read
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
id|numdev
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;js%d: %s at %#x&bslash;n&quot;
comma
id|js_register_device
c_func
(paren
id|port
comma
id|i
comma
id|js_an_axes
c_func
(paren
id|i
comma
op_amp
id|info
)paren
comma
id|js_an_buttons
c_func
(paren
id|i
comma
op_amp
id|info
)paren
comma
id|js_an_name
c_func
(paren
id|i
comma
op_amp
id|info
)paren
comma
id|js_an_open
comma
id|js_an_close
)paren
comma
id|js_an_name
c_func
(paren
id|i
comma
op_amp
id|info
)paren
comma
id|info.io
)paren
suffix:semicolon
id|js_an_read
c_func
(paren
id|port-&gt;info
comma
id|port-&gt;axes
comma
id|port-&gt;buttons
)paren
suffix:semicolon
id|js_an_init_corr
c_func
(paren
id|port-&gt;info
comma
id|port-&gt;axes
comma
id|port-&gt;corr
comma
l_int|8
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|js_an_setup
r_void
id|__init
id|js_an_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|ints
(braket
l_int|0
)braket
op_logical_and
id|i
OL
l_int|24
suffix:semicolon
id|i
op_increment
)paren
id|js_an
(braket
id|i
)braket
op_assign
id|ints
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
r_int
id|__init
id|js_an_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|js_an
(braket
l_int|0
)braket
op_ge
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|js_an
(braket
id|i
op_star
l_int|3
)braket
op_ge
l_int|0
)paren
op_logical_and
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|js_an_port
op_assign
id|js_an_probe
c_func
(paren
id|js_an
(braket
id|i
op_star
l_int|3
)braket
comma
id|js_an
(braket
id|i
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|js_an
(braket
id|i
op_star
l_int|3
op_plus
l_int|2
)braket
comma
id|js_an_port
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|js_an_port_list
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|js_an_port
op_assign
id|js_an_probe
c_func
(paren
id|js_an_port_list
(braket
id|i
)braket
comma
l_int|0
comma
l_int|0
comma
id|js_an_port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|js_an_port
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-analog: no joysticks found&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|js_an_info
op_star
id|info
suffix:semicolon
r_while
c_loop
(paren
id|js_an_port
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
id|js_an_port-&gt;ndevs
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|js_an_port-&gt;devs
(braket
id|i
)braket
)paren
id|js_unregister_device
c_func
(paren
id|js_an_port-&gt;devs
(braket
id|i
)braket
)paren
suffix:semicolon
id|info
op_assign
id|js_an_port-&gt;info
suffix:semicolon
id|release_region
c_func
(paren
id|info-&gt;io
comma
l_int|1
)paren
suffix:semicolon
id|js_an_port
op_assign
id|js_unregister_port
c_func
(paren
id|js_an_port
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof