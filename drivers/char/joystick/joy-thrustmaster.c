multiline_comment|/*&n; *  joy-thrustmaster.c  Version 1.2&n; *&n; *  Copyright (c) 1998 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This is a module for the Linux joystick driver, supporting&n; * ThrustMaster DirectConnect (BSP) joystick family.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/joystick.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|JS_TM_MAX_START
mdefine_line|#define JS_TM_MAX_START&t;&t;200
DECL|macro|JS_TM_MAX_STROBE
mdefine_line|#define JS_TM_MAX_STROBE&t;15
DECL|macro|JS_TM_MAX_LENGTH
mdefine_line|#define JS_TM_MAX_LENGTH&t;13
DECL|macro|JS_TM_MODE_M3DI
mdefine_line|#define JS_TM_MODE_M3DI&t;&t;1
DECL|macro|JS_TM_MODE_3DRP
mdefine_line|#define JS_TM_MODE_3DRP&t;&t;2
DECL|macro|JS_TM_MODE_WCS3
mdefine_line|#define JS_TM_MODE_WCS3&t;&t;4
DECL|macro|JS_TM_MODE_MAX
mdefine_line|#define JS_TM_MODE_MAX&t;&t;5&t;/* Last mode + 1 */
DECL|macro|JS_TM_BYTE_A0
mdefine_line|#define JS_TM_BYTE_A0&t;&t;0
DECL|macro|JS_TM_BYTE_A1
mdefine_line|#define JS_TM_BYTE_A1&t;&t;1
DECL|macro|JS_TM_BYTE_A2
mdefine_line|#define JS_TM_BYTE_A2&t;&t;3
DECL|macro|JS_TM_BYTE_A3
mdefine_line|#define JS_TM_BYTE_A3&t;&t;4
DECL|macro|JS_TM_BYTE_A4
mdefine_line|#define JS_TM_BYTE_A4&t;&t;6
DECL|macro|JS_TM_BYTE_A5
mdefine_line|#define JS_TM_BYTE_A5&t;&t;7
DECL|macro|JS_TM_BYTE_D0
mdefine_line|#define JS_TM_BYTE_D0&t;&t;2
DECL|macro|JS_TM_BYTE_D1
mdefine_line|#define JS_TM_BYTE_D1&t;&t;5
DECL|macro|JS_TM_BYTE_D2
mdefine_line|#define JS_TM_BYTE_D2&t;&t;8
DECL|macro|JS_TM_BYTE_D3
mdefine_line|#define JS_TM_BYTE_D3&t;&t;9
DECL|macro|JS_TM_BYTE_ID
mdefine_line|#define JS_TM_BYTE_ID&t;&t;10
DECL|macro|JS_TM_BYTE_REV
mdefine_line|#define JS_TM_BYTE_REV&t;&t;11
DECL|macro|JS_TM_BYTE_DEF
mdefine_line|#define JS_TM_BYTE_DEF&t;&t;12
DECL|variable|__initdata
r_static
r_int
id|js_tm_port_list
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
id|js_tm_port
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|js_tm_info
r_struct
id|js_tm_info
(brace
DECL|member|io
r_int
id|io
suffix:semicolon
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|js_tm_id_to_def
r_static
r_int
id|js_tm_id_to_def
(braket
id|JS_TM_MODE_MAX
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x42
comma
l_int|0x22
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
multiline_comment|/*&n; * js_tm_read_packet() reads a ThrustMaster packet.&n; */
DECL|function|js_tm_read_packet
r_static
r_int
id|js_tm_read_packet
c_func
(paren
r_int
id|io
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_int
r_int
id|t
comma
id|t1
suffix:semicolon
r_int
r_char
id|u
comma
id|v
comma
id|error
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|start
op_assign
(paren
id|js_time_speed
op_star
id|JS_TM_MAX_START
)paren
op_rshift
l_int|10
suffix:semicolon
r_int
id|strobe
op_assign
(paren
id|js_time_speed
op_star
id|JS_TM_MAX_STROBE
)paren
op_rshift
l_int|10
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
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
id|js_get_time
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|u
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|t1
op_assign
id|js_get_time
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|u
op_amp
l_int|1
)paren
op_logical_and
id|js_delta
c_func
(paren
id|t1
comma
id|t
)paren
OL
id|start
)paren
suffix:semicolon
id|t
op_assign
id|t1
suffix:semicolon
id|u
op_rshift_assign
l_int|4
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
op_rshift
l_int|4
suffix:semicolon
id|t1
op_assign
id|js_get_time
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u
op_xor
id|v
)paren
op_amp
id|u
op_amp
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|j
)paren
(brace
r_if
c_cond
(paren
id|j
OL
l_int|9
)paren
(brace
multiline_comment|/* Data bit */
id|data
(braket
id|i
)braket
op_or_assign
(paren
op_complement
id|v
op_amp
l_int|1
)paren
op_lshift
(paren
id|j
op_minus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Stop bit */
id|error
op_or_assign
id|v
op_amp
l_int|1
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Start bit */
id|error
op_or_assign
op_complement
id|v
op_amp
l_int|1
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
id|t
op_assign
id|t1
suffix:semicolon
)brace
id|u
op_assign
id|v
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|error
op_logical_and
id|i
OL
id|JS_TM_MAX_LENGTH
op_logical_and
id|js_delta
c_func
(paren
id|t1
comma
id|t
)paren
OL
id|strobe
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
(paren
id|i
op_ne
id|JS_TM_MAX_LENGTH
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * js_tm_read() reads and analyzes ThrustMaster joystick data.&n; */
DECL|function|js_tm_read
r_static
r_int
id|js_tm_read
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
id|js_tm_info
op_star
id|info
op_assign
id|xinfo
suffix:semicolon
r_int
r_char
id|data
(braket
id|JS_TM_MAX_LENGTH
)braket
suffix:semicolon
r_if
c_cond
(paren
id|js_tm_read_packet
c_func
(paren
id|info-&gt;io
comma
id|data
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: failed to read data packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
id|JS_TM_BYTE_ID
)braket
op_ne
id|info-&gt;mode
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: ID (%d) != mode (%d)&bslash;n&quot;
comma
id|data
(braket
id|JS_TM_BYTE_ID
)braket
comma
id|info-&gt;mode
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
id|JS_TM_BYTE_DEF
)braket
op_ne
id|js_tm_id_to_def
(braket
id|info-&gt;mode
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: DEF (%d) != def(mode) (%d)&bslash;n&quot;
comma
id|data
(braket
id|JS_TM_BYTE_DEF
)braket
comma
id|js_tm_id_to_def
(braket
id|info-&gt;mode
)braket
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|info-&gt;mode
)paren
(brace
r_case
id|JS_TM_MODE_M3DI
suffix:colon
id|axes
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A0
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A1
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|2
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A2
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|3
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A3
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|4
)braket
op_assign
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|5
)braket
op_assign
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|buttons
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|0x01
)paren
op_or
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|0x06
)paren
op_or
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x08
)paren
op_or
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D1
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x30
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|JS_TM_MODE_3DRP
suffix:colon
id|axes
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A0
)braket
suffix:semicolon
id|axes
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_assign
id|data
(braket
id|JS_TM_BYTE_A1
)braket
suffix:semicolon
id|buttons
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_assign
(paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
op_amp
l_int|0x3f
)paren
op_or
(paren
(paren
id|data
(braket
id|JS_TM_BYTE_D1
)braket
op_lshift
l_int|6
)paren
op_amp
l_int|0xc0
)paren
op_or
(paren
(paren
(paren
(paren
r_int
)paren
id|data
(braket
id|JS_TM_BYTE_D0
)braket
)paren
op_lshift
l_int|2
)paren
op_amp
l_int|0x300
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * js_tm_open() is a callback from the file open routine.&n; */
DECL|function|js_tm_open
r_static
r_int
id|js_tm_open
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
multiline_comment|/*&n; * js_tm_close() is a callback from the file release routine.&n; */
DECL|function|js_tm_close
r_static
r_int
id|js_tm_close
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
multiline_comment|/*&n; * js_tm_init_corr() initializes the correction values for&n; * ThrustMaster joysticks.&n; */
DECL|function|js_tm_init_corr
r_static
r_void
id|__init
id|js_tm_init_corr
c_func
(paren
r_int
id|num_axes
comma
r_int
id|mode
comma
r_int
op_star
op_star
id|axes
comma
r_struct
id|js_corr
op_star
op_star
id|corr
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_axes
suffix:semicolon
id|j
op_increment
)paren
(brace
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|type
op_assign
id|JS_CORR_BROKEN
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|prec
op_assign
l_int|0
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|0
)braket
op_assign
l_int|127
op_minus
l_int|2
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|1
)braket
op_assign
l_int|128
op_plus
l_int|2
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|2
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
op_div
(paren
l_int|127
op_minus
l_int|4
)paren
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|3
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
op_div
(paren
l_int|127
op_minus
l_int|4
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|JS_TM_MODE_M3DI
suffix:colon
id|j
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JS_TM_MODE_3DRP
suffix:colon
id|j
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|j
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|num_axes
suffix:semicolon
id|j
op_increment
)paren
(brace
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|type
op_assign
id|JS_CORR_BROKEN
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|prec
op_assign
l_int|0
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|2
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
suffix:semicolon
id|corr
(braket
l_int|0
)braket
(braket
id|j
)braket
dot
id|coef
(braket
l_int|3
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * js_tm_probe() probes for ThrustMaster type joysticks.&n; */
DECL|function|js_tm_probe
r_static
r_struct
id|js_port
id|__init
op_star
id|js_tm_probe
c_func
(paren
r_int
id|io
comma
r_struct
id|js_port
op_star
id|port
)paren
(brace
r_struct
id|js_tm_info
id|info
suffix:semicolon
r_char
op_star
id|names
(braket
id|JS_TM_MODE_MAX
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;ThrustMaster Millenium 3D Inceptor&quot;
comma
l_string|&quot;ThrustMaster Rage 3D Gamepad&quot;
comma
l_int|NULL
comma
l_string|&quot;ThrustMaster WCS III&quot;
)brace
suffix:semicolon
r_char
id|axes
(braket
id|JS_TM_MODE_MAX
)braket
op_assign
(brace
l_int|0
comma
l_int|6
comma
l_int|2
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_char
id|buttons
(braket
id|JS_TM_MODE_MAX
)braket
op_assign
(brace
l_int|0
comma
l_int|5
comma
l_int|10
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_char
id|data
(braket
id|JS_TM_MAX_LENGTH
)braket
suffix:semicolon
r_int
r_char
id|u
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
r_if
c_cond
(paren
op_logical_neg
(paren
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
op_complement
id|u
op_amp
l_int|0xf
)paren
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
id|js_tm_read_packet
c_func
(paren
id|io
comma
id|data
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: probe - can&squot;t read packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
id|info.io
op_assign
id|io
suffix:semicolon
id|info.mode
op_assign
id|data
(braket
id|JS_TM_BYTE_ID
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info.mode
)paren
r_return
id|port
suffix:semicolon
r_if
c_cond
(paren
id|info.mode
op_ge
id|JS_TM_MODE_MAX
op_logical_or
op_logical_neg
id|names
(braket
id|info.mode
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: unknown device detected &quot;
l_string|&quot;(io=%#x, id=%d), contact &lt;vojtech@ucw.cz&gt;&bslash;n&quot;
comma
id|io
comma
id|info.mode
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
id|JS_TM_BYTE_DEF
)braket
op_ne
id|js_tm_id_to_def
(braket
id|info.mode
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: wrong DEF (%d) for ID %d - should be %d&bslash;n&quot;
comma
id|data
(braket
id|JS_TM_BYTE_DEF
)braket
comma
id|info.mode
comma
id|js_tm_id_to_def
(braket
id|info.mode
)braket
)paren
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|io
comma
l_int|1
comma
l_string|&quot;joystick (thrustmaster)&quot;
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
l_int|1
comma
r_sizeof
(paren
r_struct
id|js_tm_info
)paren
comma
id|js_tm_read
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;js%d: %s revision %d at %#x&bslash;n&quot;
comma
id|js_register_device
c_func
(paren
id|port
comma
l_int|0
comma
id|axes
(braket
id|info.mode
)braket
comma
id|buttons
(braket
id|info.mode
)braket
comma
id|names
(braket
id|info.mode
)braket
comma
id|js_tm_open
comma
id|js_tm_close
)paren
comma
id|names
(braket
id|info.mode
)braket
comma
id|data
(braket
id|JS_TM_BYTE_REV
)braket
comma
id|io
)paren
suffix:semicolon
id|js_tm_init_corr
c_func
(paren
id|axes
(braket
id|info.mode
)braket
comma
id|info.mode
comma
id|port-&gt;axes
comma
id|port-&gt;corr
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
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
id|js_tm_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_int
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|js_tm_port_list
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
id|js_tm_port
op_assign
id|js_tm_probe
c_func
(paren
op_star
id|p
comma
id|js_tm_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|js_tm_port
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;joy-thrustmaster: no joysticks found&bslash;n&quot;
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
r_struct
id|js_tm_info
op_star
id|info
suffix:semicolon
r_while
c_loop
(paren
id|js_tm_port
)paren
(brace
id|js_unregister_device
c_func
(paren
id|js_tm_port-&gt;devs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|info
op_assign
id|js_tm_port-&gt;info
suffix:semicolon
id|release_region
c_func
(paren
id|info-&gt;io
comma
l_int|1
)paren
suffix:semicolon
id|js_tm_port
op_assign
id|js_unregister_port
c_func
(paren
id|js_tm_port
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
