multiline_comment|/*&n; * $Id: adi.c,v 1.12 2000/06/03 20:18:52 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * Logitech ADI joystick family driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Times, array sizes, flags, ids.&n; */
DECL|macro|ADI_MAX_START
mdefine_line|#define ADI_MAX_START&t;&t;200&t;/* Trigger to packet timeout [200us] */
DECL|macro|ADI_MAX_STROBE
mdefine_line|#define ADI_MAX_STROBE&t;&t;40&t;/* Single bit timeout [40us] */
DECL|macro|ADI_REFRESH_TIME
mdefine_line|#define ADI_REFRESH_TIME&t;HZ/50&t;/* How often to poll the joystick [20 ms] */
DECL|macro|ADI_INIT_DELAY
mdefine_line|#define ADI_INIT_DELAY&t;&t;10&t;/* Delay after init packet [10ms] */
DECL|macro|ADI_DATA_DELAY
mdefine_line|#define ADI_DATA_DELAY&t;&t;4&t;/* Delay after data packet [4ms] */
DECL|macro|ADI_MAX_LENGTH
mdefine_line|#define ADI_MAX_LENGTH&t;&t;256
DECL|macro|ADI_MIN_LENGTH
mdefine_line|#define ADI_MIN_LENGTH&t;&t;8
DECL|macro|ADI_MIN_LEN_LENGTH
mdefine_line|#define ADI_MIN_LEN_LENGTH&t;10
DECL|macro|ADI_MIN_ID_LENGTH
mdefine_line|#define ADI_MIN_ID_LENGTH&t;66
DECL|macro|ADI_MAX_NAME_LENGTH
mdefine_line|#define ADI_MAX_NAME_LENGTH&t;48
DECL|macro|ADI_MAX_CNAME_LENGTH
mdefine_line|#define ADI_MAX_CNAME_LENGTH&t;16
DECL|macro|ADI_FLAG_HAT
mdefine_line|#define ADI_FLAG_HAT&t;&t;0x04
DECL|macro|ADI_FLAG_10BIT
mdefine_line|#define ADI_FLAG_10BIT&t;&t;0x08
DECL|macro|ADI_ID_TPD
mdefine_line|#define ADI_ID_TPD&t;&t;0x01
DECL|macro|ADI_ID_WGP
mdefine_line|#define ADI_ID_WGP&t;&t;0x06
DECL|macro|ADI_ID_WGPE
mdefine_line|#define ADI_ID_WGPE&t;&t;0x08
DECL|macro|ADI_ID_MAX
mdefine_line|#define ADI_ID_MAX&t;&t;0x0a
multiline_comment|/*&n; * Names, buttons, axes ...&n; */
DECL|variable|adi_names
r_static
r_char
op_star
id|adi_names
(braket
)braket
op_assign
(brace
l_string|&quot;WingMan Extreme Digital&quot;
comma
l_string|&quot;ThunderPad Digital&quot;
comma
l_string|&quot;SideCar&quot;
comma
l_string|&quot;CyberMan 2&quot;
comma
l_string|&quot;WingMan Interceptor&quot;
comma
l_string|&quot;WingMan Formula&quot;
comma
l_string|&quot;WingMan GamePad&quot;
comma
l_string|&quot;WingMan Extreme Digital 3D&quot;
comma
l_string|&quot;WingMan GamePad Extreme&quot;
comma
l_string|&quot;WingMan GamePad USB&quot;
comma
l_string|&quot;Unknown Device %#x&quot;
)brace
suffix:semicolon
DECL|variable|adi_wmgpe_abs
r_static
r_char
id|adi_wmgpe_abs
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
)brace
suffix:semicolon
DECL|variable|adi_wmi_abs
r_static
r_char
id|adi_wmi_abs
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_THROTTLE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
id|ABS_HAT1X
comma
id|ABS_HAT1Y
comma
id|ABS_HAT2X
comma
id|ABS_HAT2Y
)brace
suffix:semicolon
DECL|variable|adi_wmed3d_abs
r_static
r_char
id|adi_wmed3d_abs
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_THROTTLE
comma
id|ABS_RZ
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
)brace
suffix:semicolon
DECL|variable|adi_cm2_abs
r_static
r_char
id|adi_cm2_abs
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
DECL|variable|adi_wmf_abs
r_static
r_char
id|adi_wmf_abs
(braket
)braket
op_assign
(brace
id|ABS_WHEEL
comma
id|ABS_GAS
comma
id|ABS_BRAKE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
id|ABS_HAT1X
comma
id|ABS_HAT1Y
comma
id|ABS_HAT2X
comma
id|ABS_HAT2Y
)brace
suffix:semicolon
DECL|variable|adi_wmgpe_key
r_static
r_int
id|adi_wmgpe_key
(braket
)braket
op_assign
(brace
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
comma
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_START
comma
id|BTN_MODE
comma
id|BTN_SELECT
)brace
suffix:semicolon
DECL|variable|adi_wmi_key
r_static
r_int
id|adi_wmi_key
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_TOP
comma
id|BTN_THUMB
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
id|BTN_EXTRA
)brace
suffix:semicolon
DECL|variable|adi_wmed3d_key
r_static
r_int
id|adi_wmed3d_key
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB
comma
id|BTN_THUMB2
comma
id|BTN_TOP
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
)brace
suffix:semicolon
DECL|variable|adi_cm2_key
r_static
r_int
id|adi_cm2_key
(braket
)braket
op_assign
(brace
id|BTN_1
comma
id|BTN_2
comma
id|BTN_3
comma
id|BTN_4
comma
id|BTN_5
comma
id|BTN_6
comma
id|BTN_7
comma
id|BTN_8
)brace
suffix:semicolon
DECL|variable|adi_abs
r_static
r_char
op_star
id|adi_abs
(braket
)braket
op_assign
(brace
id|adi_wmi_abs
comma
id|adi_wmgpe_abs
comma
id|adi_wmf_abs
comma
id|adi_cm2_abs
comma
id|adi_wmi_abs
comma
id|adi_wmf_abs
comma
id|adi_wmgpe_abs
comma
id|adi_wmed3d_abs
comma
id|adi_wmgpe_abs
comma
id|adi_wmgpe_abs
comma
id|adi_wmi_abs
)brace
suffix:semicolon
DECL|variable|adi_key
r_static
r_int
op_star
id|adi_key
(braket
)braket
op_assign
(brace
id|adi_wmi_key
comma
id|adi_wmgpe_key
comma
id|adi_cm2_key
comma
id|adi_cm2_key
comma
id|adi_wmi_key
comma
id|adi_cm2_key
comma
id|adi_wmgpe_key
comma
id|adi_wmed3d_key
comma
id|adi_wmgpe_key
comma
id|adi_wmgpe_key
comma
id|adi_wmi_key
)brace
suffix:semicolon
multiline_comment|/*&n; * Hat to axis conversion arrays.&n; */
r_static
r_struct
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|variable|adi_hat_to_axis
)brace
id|adi_hat_to_axis
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|0
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Per-port information.&n; */
DECL|struct|adi
r_struct
id|adi
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|ret
r_int
id|ret
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|buttons
r_char
id|buttons
suffix:semicolon
DECL|member|axes10
r_char
id|axes10
suffix:semicolon
DECL|member|axes8
r_char
id|axes8
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|hats
r_char
id|hats
suffix:semicolon
DECL|member|abs
r_char
op_star
id|abs
suffix:semicolon
DECL|member|key
r_int
op_star
id|key
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|ADI_MAX_NAME_LENGTH
)braket
suffix:semicolon
DECL|member|cname
r_char
id|cname
(braket
id|ADI_MAX_CNAME_LENGTH
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|ADI_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adi_port
r_struct
id|adi_port
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|adi
r_struct
id|adi
id|adi
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bad
r_int
id|bad
suffix:semicolon
DECL|member|reads
r_int
id|reads
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * adi_read_packet() reads a Logitech ADI packet.&n; */
DECL|function|adi_read_packet
r_static
r_void
id|adi_read_packet
c_func
(paren
r_struct
id|adi_port
op_star
id|port
)paren
(brace
r_struct
id|adi
op_star
id|adi
op_assign
id|port-&gt;adi
suffix:semicolon
r_struct
id|gameport
op_star
id|gameport
op_assign
id|port-&gt;gameport
suffix:semicolon
r_int
r_char
id|u
comma
id|v
comma
id|w
comma
id|x
comma
id|z
suffix:semicolon
r_int
id|t
(braket
l_int|2
)braket
comma
id|s
(braket
l_int|2
)braket
comma
id|i
suffix:semicolon
r_int
r_int
id|flags
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|adi
(braket
id|i
)braket
dot
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
id|t
(braket
id|i
)braket
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|ADI_MAX_START
)paren
suffix:semicolon
id|s
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
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
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|v
op_assign
id|z
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_do
(brace
id|u
op_assign
id|v
suffix:semicolon
id|w
op_assign
id|u
op_xor
(paren
id|v
op_assign
id|x
op_assign
id|gameport_read
c_func
(paren
id|gameport
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
l_int|2
suffix:semicolon
id|i
op_increment
comma
id|w
op_rshift_assign
l_int|2
comma
id|x
op_rshift_assign
l_int|2
)paren
(brace
id|t
(braket
id|i
)braket
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|w
op_amp
l_int|0x30
)paren
op_logical_and
id|s
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
(paren
id|w
op_amp
l_int|0x30
)paren
OL
l_int|0x30
op_logical_and
id|adi
(braket
id|i
)braket
dot
id|ret
template_param
l_int|0
)paren
(brace
id|adi
(braket
id|i
)braket
dot
id|data
(braket
op_increment
id|adi
(braket
id|i
)braket
dot
id|ret
)braket
op_assign
id|w
suffix:semicolon
id|t
(braket
id|i
)braket
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|ADI_MAX_STROBE
)paren
suffix:semicolon
)brace
r_else
id|t
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0x30
)paren
)paren
id|s
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|t
(braket
l_int|0
)braket
OG
l_int|0
op_logical_or
id|t
(braket
l_int|1
)braket
OG
l_int|0
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_move_bits() detects a possible 2-stream mode, and moves&n; * the bits accordingly. &n; */
DECL|function|adi_move_bits
r_static
r_void
id|adi_move_bits
c_func
(paren
r_struct
id|adi_port
op_star
id|port
comma
r_int
id|length
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|adi
op_star
id|adi
op_assign
id|port-&gt;adi
suffix:semicolon
id|adi
(braket
l_int|0
)braket
dot
id|idx
op_assign
id|adi
(braket
l_int|1
)braket
dot
id|idx
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|adi
(braket
l_int|0
)braket
dot
id|ret
op_le
l_int|0
op_logical_or
id|adi
(braket
l_int|1
)braket
dot
id|ret
op_le
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|adi
(braket
l_int|0
)braket
dot
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x20
op_logical_or
op_complement
id|adi
(braket
l_int|1
)braket
dot
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x20
)paren
r_return
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
id|adi
(braket
l_int|1
)braket
dot
id|ret
suffix:semicolon
id|i
op_increment
)paren
id|adi
(braket
l_int|0
)braket
dot
id|data
(braket
(paren
(paren
id|length
op_minus
l_int|1
)paren
op_rshift
l_int|1
)paren
op_plus
id|i
op_plus
l_int|1
)braket
op_assign
id|adi
(braket
l_int|1
)braket
dot
id|data
(braket
id|i
)braket
suffix:semicolon
id|adi
(braket
l_int|0
)braket
dot
id|ret
op_add_assign
id|adi
(braket
l_int|1
)braket
dot
id|ret
suffix:semicolon
id|adi
(braket
l_int|1
)braket
dot
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_get_bits() gathers bits from the data packet.&n; */
DECL|function|adi_get_bits
r_static
r_inline
r_int
id|adi_get_bits
c_func
(paren
r_struct
id|adi
op_star
id|adi
comma
r_int
id|count
)paren
(brace
r_int
id|bits
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|adi-&gt;idx
op_add_assign
id|count
)paren
OG
id|adi-&gt;ret
)paren
r_return
l_int|0
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
id|count
suffix:semicolon
id|i
op_increment
)paren
id|bits
op_or_assign
(paren
(paren
id|adi-&gt;data
(braket
id|adi-&gt;idx
op_minus
id|i
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
op_lshift
id|i
suffix:semicolon
r_return
id|bits
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_decode() decodes Logitech joystick data into input events.&n; */
DECL|function|adi_decode
r_static
r_int
id|adi_decode
c_func
(paren
r_struct
id|adi
op_star
id|adi
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|adi-&gt;dev
suffix:semicolon
r_char
op_star
id|abs
op_assign
id|adi-&gt;abs
suffix:semicolon
r_int
op_star
id|key
op_assign
id|adi-&gt;key
suffix:semicolon
r_int
id|i
comma
id|t
suffix:semicolon
r_if
c_cond
(paren
id|adi-&gt;ret
OL
id|adi-&gt;length
op_logical_or
id|adi-&gt;id
op_ne
(paren
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
op_or
(paren
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
op_lshift
l_int|4
)paren
)paren
)paren
r_return
op_minus
l_int|1
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
id|adi-&gt;axes10
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|10
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
id|adi-&gt;axes8
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|8
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
id|adi-&gt;buttons
op_logical_and
id|i
OL
l_int|63
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|adi-&gt;pad
)paren
(brace
id|t
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
(paren
(paren
id|t
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|t
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
(paren
(paren
id|t
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|t
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
)brace
id|input_report_key
c_func
(paren
id|dev
comma
op_star
id|key
op_increment
comma
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|adi-&gt;hats
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|t
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
)paren
OG
l_int|8
)paren
id|t
op_assign
l_int|0
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
id|adi_hat_to_axis
(braket
id|t
)braket
dot
id|x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
op_star
id|abs
op_increment
comma
id|adi_hat_to_axis
(braket
id|t
)braket
dot
id|y
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|63
suffix:semicolon
id|i
OL
id|adi-&gt;buttons
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
op_star
id|key
op_increment
comma
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_read() reads the data packet and decodes it.&n; */
DECL|function|adi_read
r_static
r_int
id|adi_read
c_func
(paren
r_struct
id|adi_port
op_star
id|port
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|adi_read_packet
c_func
(paren
id|port
)paren
suffix:semicolon
id|adi_move_bits
c_func
(paren
id|port
comma
id|port-&gt;adi
(braket
l_int|0
)braket
dot
id|length
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|port-&gt;adi
(braket
id|i
)braket
dot
id|length
)paren
id|result
op_or_assign
id|adi_decode
c_func
(paren
id|port-&gt;adi
op_plus
id|i
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_timer() repeatedly polls the Logitech joysticks.&n; */
DECL|function|adi_timer
r_static
r_void
id|adi_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|adi_port
op_star
id|port
op_assign
(paren
r_void
op_star
)paren
id|data
suffix:semicolon
id|port-&gt;bad
op_sub_assign
id|adi_read
c_func
(paren
id|port
)paren
suffix:semicolon
id|port-&gt;reads
op_increment
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|port-&gt;timer
comma
id|jiffies
op_plus
id|ADI_REFRESH_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_open() is a callback from the input open routine.&n; */
DECL|function|adi_open
r_static
r_int
id|adi_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|adi_port
op_star
id|port
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|port-&gt;timer
comma
id|jiffies
op_plus
id|ADI_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_close() is a callback from the input close routine.&n; */
DECL|function|adi_close
r_static
r_void
id|adi_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|adi_port
op_star
id|port
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|port-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|port-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * adi_init_digital() sends a trigger &amp; delay sequence&n; * to reset and initialize a Logitech joystick into digital mode.&n; */
DECL|function|adi_init_digital
r_static
r_void
id|adi_init_digital
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_int
id|seq
(braket
)braket
op_assign
(brace
l_int|3
comma
op_minus
l_int|2
comma
op_minus
l_int|3
comma
l_int|10
comma
op_minus
l_int|6
comma
op_minus
l_int|11
comma
op_minus
l_int|7
comma
op_minus
l_int|9
comma
l_int|11
comma
l_int|0
)brace
suffix:semicolon
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
id|seq
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seq
(braket
id|i
)braket
OG
l_int|0
)paren
id|wait_ms
c_func
(paren
id|seq
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seq
(braket
id|i
)braket
OL
l_int|0
)paren
id|mdelay
c_func
(paren
op_minus
id|seq
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|adi_id_decode
r_static
r_void
id|adi_id_decode
c_func
(paren
r_struct
id|adi
op_star
id|adi
comma
r_struct
id|adi_port
op_star
id|port
)paren
(brace
r_int
id|i
comma
id|t
suffix:semicolon
r_if
c_cond
(paren
id|adi-&gt;ret
OL
id|ADI_MIN_ID_LENGTH
)paren
multiline_comment|/* Minimum ID packet length */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|adi-&gt;ret
OL
(paren
id|t
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|10
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;adi: Short ID packet: reported: %d != read: %d&bslash;n&quot;
comma
id|t
comma
id|adi-&gt;ret
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|adi-&gt;id
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
op_or
(paren
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
op_lshift
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
)paren
op_amp
id|ADI_FLAG_HAT
)paren
id|adi-&gt;hats
op_increment
suffix:semicolon
id|adi-&gt;length
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adi-&gt;length
op_ge
id|ADI_MAX_LENGTH
op_logical_or
id|adi-&gt;length
OL
id|ADI_MIN_LENGTH
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;adi: Bad data packet length (%d).&bslash;n&quot;
comma
id|adi-&gt;length
)paren
suffix:semicolon
id|adi-&gt;length
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|adi-&gt;axes8
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
suffix:semicolon
id|adi-&gt;buttons
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|6
)paren
op_ne
l_int|8
op_logical_and
id|adi-&gt;hats
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;adi: Other than 8-dir POVs not supported yet.&bslash;n&quot;
)paren
suffix:semicolon
id|adi-&gt;length
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|adi-&gt;buttons
op_add_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|6
)paren
suffix:semicolon
id|adi-&gt;hats
op_add_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
suffix:semicolon
id|i
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_amp
id|ADI_FLAG_10BIT
)paren
(brace
id|adi-&gt;axes10
op_assign
id|adi-&gt;axes8
op_minus
id|i
suffix:semicolon
id|adi-&gt;axes8
op_assign
id|i
suffix:semicolon
)brace
id|t
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|4
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
id|t
suffix:semicolon
id|i
op_increment
)paren
id|adi-&gt;cname
(braket
id|i
)braket
op_assign
id|adi_get_bits
c_func
(paren
id|adi
comma
l_int|8
)paren
suffix:semicolon
id|adi-&gt;cname
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|adi-&gt;length
op_ne
(paren
id|t
op_assign
l_int|8
op_plus
id|adi-&gt;buttons
op_plus
id|adi-&gt;axes10
op_star
l_int|10
op_plus
id|adi-&gt;axes8
op_star
l_int|8
op_plus
id|adi-&gt;hats
op_star
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;adi: Expected length %d != data length %d&bslash;n&quot;
comma
id|t
comma
id|adi-&gt;length
)paren
suffix:semicolon
id|adi-&gt;length
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|adi-&gt;id
)paren
(brace
r_case
id|ADI_ID_TPD
suffix:colon
id|adi-&gt;pad
op_assign
l_int|4
suffix:semicolon
id|adi-&gt;buttons
op_sub_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ADI_ID_WGP
suffix:colon
id|adi-&gt;pad
op_assign
l_int|0
suffix:semicolon
id|adi-&gt;buttons
op_sub_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|adi-&gt;pad
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|adi_init_input
r_static
r_void
id|adi_init_input
c_func
(paren
r_struct
id|adi
op_star
id|adi
comma
r_struct
id|adi_port
op_star
id|port
)paren
(brace
r_int
id|i
comma
id|t
suffix:semicolon
r_char
id|buf
(braket
id|ADI_MAX_NAME_LENGTH
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adi-&gt;length
)paren
r_return
suffix:semicolon
id|t
op_assign
id|adi-&gt;id
OL
id|ADI_ID_MAX
ques
c_cond
id|adi-&gt;id
suffix:colon
id|ADI_ID_MAX
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
id|adi_names
(braket
id|t
)braket
comma
id|adi-&gt;id
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|adi-&gt;name
comma
l_string|&quot;Logitech %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|adi-&gt;abs
op_assign
id|adi_abs
(braket
id|t
)braket
suffix:semicolon
id|adi-&gt;key
op_assign
id|adi_key
(braket
id|t
)braket
suffix:semicolon
id|adi-&gt;dev.open
op_assign
id|adi_open
suffix:semicolon
id|adi-&gt;dev.close
op_assign
id|adi_close
suffix:semicolon
id|adi-&gt;dev.name
op_assign
id|adi-&gt;name
suffix:semicolon
id|adi-&gt;dev.idbus
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|adi-&gt;dev.idvendor
op_assign
id|GAMEPORT_ID_VENDOR_LOGITECH
suffix:semicolon
id|adi-&gt;dev.idproduct
op_assign
id|adi-&gt;id
suffix:semicolon
id|adi-&gt;dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|adi-&gt;dev
dot
r_private
op_assign
id|port
suffix:semicolon
id|adi-&gt;dev.evbit
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
id|adi-&gt;axes10
op_plus
id|adi-&gt;axes8
op_plus
(paren
id|adi-&gt;hats
op_plus
(paren
id|adi-&gt;pad
OG
l_int|0
)paren
)paren
op_star
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|adi-&gt;abs
(braket
id|i
)braket
comma
op_amp
id|adi-&gt;dev.absbit
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
id|adi-&gt;buttons
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|adi-&gt;key
(braket
id|i
)braket
comma
op_amp
id|adi-&gt;dev.keybit
)paren
suffix:semicolon
)brace
DECL|function|adi_init_center
r_static
r_void
id|adi_init_center
c_func
(paren
r_struct
id|adi
op_star
id|adi
)paren
(brace
r_int
id|i
comma
id|t
comma
id|x
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adi-&gt;length
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
id|adi-&gt;axes10
op_plus
id|adi-&gt;axes8
op_plus
(paren
id|adi-&gt;hats
op_plus
(paren
id|adi-&gt;pad
OG
l_int|0
)paren
)paren
op_star
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|t
op_assign
id|adi-&gt;abs
(braket
id|i
)braket
suffix:semicolon
id|x
op_assign
id|adi-&gt;dev.abs
(braket
id|t
)braket
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
id|ABS_THROTTLE
op_logical_or
id|t
op_eq
id|ABS_RUDDER
op_logical_or
id|adi-&gt;id
op_eq
id|ADI_ID_WGPE
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|adi-&gt;axes10
)paren
id|x
op_assign
l_int|512
suffix:semicolon
r_else
id|x
op_assign
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|adi-&gt;axes10
)paren
(brace
id|adi-&gt;dev.absmax
(braket
id|t
)braket
op_assign
id|x
op_star
l_int|2
op_minus
l_int|64
suffix:semicolon
id|adi-&gt;dev.absmin
(braket
id|t
)braket
op_assign
l_int|64
suffix:semicolon
id|adi-&gt;dev.absfuzz
(braket
id|t
)braket
op_assign
l_int|2
suffix:semicolon
id|adi-&gt;dev.absflat
(braket
id|t
)braket
op_assign
l_int|16
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|adi-&gt;axes10
op_plus
id|adi-&gt;axes8
)paren
(brace
id|adi-&gt;dev.absmax
(braket
id|t
)braket
op_assign
id|x
op_star
l_int|2
op_minus
l_int|48
suffix:semicolon
id|adi-&gt;dev.absmin
(braket
id|t
)braket
op_assign
l_int|48
suffix:semicolon
id|adi-&gt;dev.absfuzz
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
id|adi-&gt;dev.absflat
(braket
id|t
)braket
op_assign
l_int|16
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|adi-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
id|adi-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * adi_connect() probes for Logitech ADI joysticks.&n; */
DECL|function|adi_connect
r_static
r_void
id|adi_connect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_struct
id|gameport_dev
op_star
id|dev
)paren
(brace
r_struct
id|adi_port
op_star
id|port
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|adi_port
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
id|port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|adi_port
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|port
suffix:semicolon
id|port-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|port-&gt;timer
)paren
suffix:semicolon
id|port-&gt;timer.data
op_assign
(paren
r_int
)paren
id|port
suffix:semicolon
id|port-&gt;timer.function
op_assign
id|adi_timer
suffix:semicolon
r_if
c_cond
(paren
id|gameport_open
c_func
(paren
id|gameport
comma
id|dev
comma
id|GAMEPORT_MODE_RAW
)paren
)paren
(brace
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|adi_init_digital
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|adi_read_packet
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;adi
(braket
l_int|0
)braket
dot
id|ret
op_ge
id|ADI_MIN_LEN_LENGTH
)paren
id|adi_move_bits
c_func
(paren
id|port
comma
id|adi_get_bits
c_func
(paren
id|port-&gt;adi
comma
l_int|10
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|adi_id_decode
c_func
(paren
id|port-&gt;adi
op_plus
id|i
comma
id|port
)paren
suffix:semicolon
id|adi_init_input
c_func
(paren
id|port-&gt;adi
op_plus
id|i
comma
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;adi
(braket
l_int|0
)braket
dot
id|length
op_logical_and
op_logical_neg
id|port-&gt;adi
(braket
l_int|1
)braket
dot
id|length
)paren
(brace
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|wait_ms
c_func
(paren
id|ADI_INIT_DELAY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adi_read
c_func
(paren
id|port
)paren
)paren
(brace
id|wait_ms
c_func
(paren
id|ADI_DATA_DELAY
)paren
suffix:semicolon
id|adi_read
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|port-&gt;adi
(braket
id|i
)braket
dot
id|length
OG
l_int|0
)paren
(brace
id|adi_init_center
c_func
(paren
id|port-&gt;adi
op_plus
id|i
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|port-&gt;adi
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s [%s] on gameport%d.%d&bslash;n&quot;
comma
id|port-&gt;adi
(braket
id|i
)braket
dot
id|dev.number
comma
id|port-&gt;adi
(braket
id|i
)braket
dot
id|name
comma
id|port-&gt;adi
(braket
id|i
)braket
dot
id|cname
comma
id|gameport-&gt;number
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|adi_disconnect
r_static
r_void
id|adi_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|adi_port
op_star
id|port
op_assign
id|gameport
op_member_access_from_pointer
r_private
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|port-&gt;adi
(braket
id|i
)braket
dot
id|length
OG
l_int|0
)paren
id|input_unregister_device
c_func
(paren
op_amp
id|port-&gt;adi
(braket
id|i
)braket
dot
id|dev
)paren
suffix:semicolon
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The gameport device structure.&n; */
DECL|variable|adi_dev
r_static
r_struct
id|gameport_dev
id|adi_dev
op_assign
(brace
id|connect
suffix:colon
id|adi_connect
comma
id|disconnect
suffix:colon
id|adi_disconnect
comma
)brace
suffix:semicolon
DECL|function|adi_init
r_int
id|__init
id|adi_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|adi_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adi_exit
r_void
id|__exit
id|adi_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|adi_dev
)paren
suffix:semicolon
)brace
DECL|variable|adi_init
id|module_init
c_func
(paren
id|adi_init
)paren
suffix:semicolon
DECL|variable|adi_exit
id|module_exit
c_func
(paren
id|adi_exit
)paren
suffix:semicolon
eof
