multiline_comment|/*&n; * $Id: wacom.c,v 1.14 2000/11/23 09:34:32 vojtech Exp $&n; *&n; *  Copyright (c) 2000 Vojtech Pavlik&t;&t;&lt;vojtech@suse.cz&gt;&n; *  Copyright (c) 2000 Andreas Bach Aaen&t;&lt;abach@stofanet.dk&gt;&n; *  Copyright (c) 2000 Clifford Wolf&t;&t;&lt;clifford@clifford.at&gt;&n; *  Copyright (c) 2000 Sam Mosel&t;&t;&lt;sam.mosel@computer.org&gt;&n; *  Copyright (c) 2000 James E. Blair&t;&t;&lt;corvus@gnu.org&gt;&n; *  Copyright (c) 2000 Daniel Egger&t;&t;&lt;egger@suse.de&gt;&n; *&n; *  USB Wacom Graphire and Wacom Intuos tablet support&n; *&n; *  Sponsored by SuSE&n; *&n; *  ChangeLog:&n; *      v0.1 (vp)  - Initial release&n; *      v0.2 (aba) - Support for all buttons / combinations&n; *      v0.3 (vp)  - Support for Intuos added&n; *&t;v0.4 (sm)  - Support for more Intuos models, menustrip&n; *&t;&t;&t;relative mode, proximity.&n; *&t;v0.5 (vp)  - Big cleanup, nifty features removed,&n; * &t;&t;&t;they belong in userspace&n; *&t;v1.8 (vp)  - Submit URB only when operating, moved to CVS,&n; *&t;&t;&t;use input_report_key instead of report_btn and&n; *&t;&t;&t;other cleanups&n; *&t;v1.11 (vp) - Add URB -&gt;dev setting for new kernels&n; *&t;v1.11 (jb) - Add support for the 4D Mouse &amp; Lens&n; *&t;v1.12 (de) - Add support for two more inking pen IDs&n; *&t;v1.14 (vp) - Use new USB device id probing scheme.&n; *&t;&t;     Fix Wacom Graphire mouse wheel&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;USB Wacom Graphire and Wacom Intuos tablet driver&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Wacom Graphire packet:&n; *&n; * byte 0: report ID (2)&n; * byte 1: bit7&t;&t;pointer in range&n; *&t;   bit5-6&t;pointer type 0 - pen, 1 - rubber, 2 - mouse&n; *&t;   bit4&t;&t;1 ?&n; *&t;   bit3&t;&t;0 ?&n; *&t;   bit2&t;&t;mouse middle button / pen button2&n; *&t;   bit1&t;&t;mouse right button / pen button1&n; *&t;   bit0&t;&t;mouse left button / touch&n; * byte 2: X low bits&n; * byte 3: X high bits&n; * byte 4: Y low bits&n; * byte 5: Y high bits&n; * byte 6: pen pressure low bits / mouse wheel&n; * byte 7: pen presure high bits / mouse distance&n; *&n; * There are also two single-byte feature reports (2 and 3).&n; *&n; * Wacom Intuos status packet:&n; *&n; * byte 0: report ID (2)&n; * byte 1: bit7&t;&t;1 - sync bit&n; *&t;   bit6&t;&t;pointer in range&n; *&t;   bit5&t;&t;pointer type report&n; *&t;   bit4&t;&t;0 ?&n; *&t;   bit3&t;&t;mouse packet type&n; *&t;   bit2&t;&t;pen button2&n; *&t;   bit1&t;&t;pen button1&n; *&t;   bit0&t;&t;0 ?&n; * byte 2: X high bits&n; * byte 3: X low bits&n; * byte 4: Y high bits&n; * byte 5: Y low bits&n; *&n; * Pen packet:&n; *&n; * byte 6: bits 0-7: pressure&t;(bits 2-9)&n; * byte 7: bits 6-7: pressure&t;(bits 0-1)&n; * byte 7: bits 0-5: X tilt&t;(bits 1-6)&n; * byte 8: bit    7: X tilt&t;(bit  0)&n; * byte 8: bits 0-6: Y tilt&t;(bits 0-6)&n; * byte 9: bits 4-7: distance&n; *&n; * Mouse packet type 0:&n; *&n; * byte 6: bits 0-7: wheel&t;(bits 2-9)&n; * byte 7: bits 6-7: wheel&t;(bits 0-1)&n; * byte 7: bits 0-5: 0&n; * byte 8: bits 6-7: 0&n; * byte 8: bit    5: left extra button&n; * byte 8: bit    4: right extra button&n; * byte 8: bit    3: wheel      (sign)&n; * byte 8: bit    2: right button&n; * byte 8: bit    1: middle button&n; * byte 8: bit    0: left button&n; * byte 9: bits 4-7: distance&n; *&n; * Mouse packet type 1:&n; *&n; * byte 6: bits 0-7: rotation&t;(bits 2-9)&n; * byte 7: bits 6-7: rotation&t;(bits 0-1)&n; * byte 7: bit    5: rotation&t;(sign)&n; * byte 7: bits 0-4: 0&n; * byte 8: bits 0-7: 0&n; * byte 9: bits 4-7: distance&n; */
DECL|macro|USB_VENDOR_ID_WACOM
mdefine_line|#define USB_VENDOR_ID_WACOM&t;0x056a
DECL|struct|wacom_features
r_struct
id|wacom_features
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|pktlen
r_int
id|pktlen
suffix:semicolon
DECL|member|x_max
r_int
id|x_max
suffix:semicolon
DECL|member|y_max
r_int
id|y_max
suffix:semicolon
DECL|member|pressure_max
r_int
id|pressure_max
suffix:semicolon
DECL|member|distance_max
r_int
id|distance_max
suffix:semicolon
DECL|member|irq
r_void
(paren
op_star
id|irq
)paren
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|evbit
r_int
r_int
id|evbit
suffix:semicolon
DECL|member|absbit
r_int
r_int
id|absbit
suffix:semicolon
DECL|member|relbit
r_int
r_int
id|relbit
suffix:semicolon
DECL|member|btnbit
r_int
r_int
id|btnbit
suffix:semicolon
DECL|member|digibit
r_int
r_int
id|digibit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wacom
r_struct
id|wacom
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|irq
r_struct
id|urb
id|irq
suffix:semicolon
DECL|member|features
r_struct
id|wacom_features
op_star
id|features
suffix:semicolon
DECL|member|tool
r_int
id|tool
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
)brace
suffix:semicolon
DECL|function|wacom_graphire_irq
r_static
r_void
id|wacom_graphire_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|wacom
op_star
id|wacom
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|wacom-&gt;data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|wacom-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_ne
l_int|2
)paren
id|dbg
c_func
(paren
l_string|&quot;received unknown report #%d&quot;
comma
id|data
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|data
(braket
l_int|2
)braket
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|data
(braket
l_int|4
)braket
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Pen */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_PEN
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Rubber */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_RUBBER
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Mouse */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_MOUSE
comma
id|data
(braket
l_int|7
)braket
OG
l_int|24
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x04
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_DISTANCE
comma
id|data
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
(paren
r_int
r_char
)paren
id|data
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|data
(braket
l_int|6
)braket
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_STYLUS
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_STYLUS2
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x04
)paren
suffix:semicolon
)brace
DECL|function|wacom_intuos_irq
r_static
r_void
id|wacom_intuos_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|wacom
op_star
id|wacom
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|wacom-&gt;data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|wacom-&gt;dev
suffix:semicolon
r_int
r_int
id|t
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_ne
l_int|2
)paren
id|dbg
c_func
(paren
l_string|&quot;received unknown report #%d&quot;
comma
id|data
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x3
)paren
op_eq
l_int|0x2
)paren
(brace
multiline_comment|/* Enter report */
r_switch
c_cond
(paren
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|2
)braket
op_lshift
l_int|4
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
)paren
(brace
r_case
l_int|0x832
suffix:colon
r_case
l_int|0x812
suffix:colon
r_case
l_int|0x012
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_PENCIL
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Inking pen */
r_case
l_int|0x822
suffix:colon
r_case
l_int|0x022
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_PEN
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Pen */
r_case
l_int|0x032
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_BRUSH
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Stroke pen */
r_case
l_int|0x094
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_MOUSE
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Mouse 4D */
r_case
l_int|0x096
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_LENS
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Lens cursor */
r_case
l_int|0x82a
suffix:colon
r_case
l_int|0x0fa
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_RUBBER
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Eraser */
r_case
l_int|0x112
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_AIRBRUSH
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Airbrush */
r_default
suffix:colon
id|wacom-&gt;tool
op_assign
id|BTN_TOOL_PEN
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Unknown tool */
)brace
id|input_report_key
c_func
(paren
id|dev
comma
id|wacom-&gt;tool
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|data
(braket
l_int|1
)braket
op_or
id|data
(braket
l_int|2
)braket
op_or
id|data
(braket
l_int|3
)braket
op_or
id|data
(braket
l_int|4
)braket
op_or
id|data
(braket
l_int|5
)braket
op_or
id|data
(braket
l_int|6
)braket
op_or
id|data
(braket
l_int|7
)braket
op_or
id|data
(braket
l_int|8
)braket
op_or
id|data
(braket
l_int|9
)braket
)paren
op_eq
l_int|0x80
)paren
(brace
multiline_comment|/* Exit report */
id|input_report_key
c_func
(paren
id|dev
comma
id|wacom-&gt;tool
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|4
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_DISTANCE
comma
id|data
(braket
l_int|9
)braket
op_rshift
l_int|4
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|wacom-&gt;tool
)paren
(brace
r_case
id|BTN_TOOL_PENCIL
suffix:colon
r_case
id|BTN_TOOL_PEN
suffix:colon
r_case
id|BTN_TOOL_BRUSH
suffix:colon
r_case
id|BTN_TOOL_RUBBER
suffix:colon
r_case
id|BTN_TOOL_AIRBRUSH
suffix:colon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|t
op_assign
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_TILT_X
comma
(paren
(paren
id|data
(braket
l_int|7
)braket
op_lshift
l_int|1
)paren
op_amp
l_int|0x7e
)paren
op_or
(paren
id|data
(braket
l_int|8
)braket
op_rshift
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_TILT_Y
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x7f
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_STYLUS
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_STYLUS2
comma
id|data
(braket
l_int|1
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
id|t
OG
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTN_TOOL_MOUSE
suffix:colon
r_case
id|BTN_TOOL_LENS
suffix:colon
r_if
c_cond
(paren
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* Rotation packet */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RZ
comma
(paren
id|data
(braket
l_int|7
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
suffix:colon
(paren
op_minus
(paren
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x04
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x20
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x10
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_THROTTLE
comma
(paren
id|data
(braket
l_int|8
)braket
op_amp
l_int|0x08
)paren
ques
c_cond
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
suffix:colon
op_minus
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|data
(braket
l_int|7
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|WACOM_INTUOS_TOOLS
mdefine_line|#define WACOM_INTUOS_TOOLS&t;(BIT(BTN_TOOL_BRUSH) | BIT(BTN_TOOL_PENCIL) | BIT(BTN_TOOL_AIRBRUSH) | BIT(BTN_TOOL_LENS))
DECL|macro|WACOM_INTUOS_BUTTONS
mdefine_line|#define WACOM_INTUOS_BUTTONS&t;(BIT(BTN_SIDE) | BIT(BTN_EXTRA))
DECL|macro|WACOM_INTUOS_ABS
mdefine_line|#define WACOM_INTUOS_ABS&t;(BIT(ABS_TILT_X) | BIT(ABS_TILT_Y) | BIT(ABS_RZ) | BIT(ABS_THROTTLE))
DECL|variable|wacom_features
r_struct
id|wacom_features
id|wacom_features
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Wacom Graphire&quot;
comma
l_int|8
comma
l_int|10206
comma
l_int|7422
comma
l_int|511
comma
l_int|32
comma
id|wacom_graphire_irq
comma
id|BIT
c_func
(paren
id|EV_REL
)paren
comma
l_int|0
comma
id|REL_WHEEL
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Wacom Intuos 4x5&quot;
comma
l_int|10
comma
l_int|12700
comma
l_int|10360
comma
l_int|1023
comma
l_int|15
comma
id|wacom_intuos_irq
comma
l_int|0
comma
id|WACOM_INTUOS_ABS
comma
l_int|0
comma
id|WACOM_INTUOS_BUTTONS
comma
id|WACOM_INTUOS_TOOLS
)brace
comma
(brace
l_string|&quot;Wacom Intuos 6x8&quot;
comma
l_int|10
comma
l_int|20320
comma
l_int|15040
comma
l_int|1023
comma
l_int|15
comma
id|wacom_intuos_irq
comma
l_int|0
comma
id|WACOM_INTUOS_ABS
comma
l_int|0
comma
id|WACOM_INTUOS_BUTTONS
comma
id|WACOM_INTUOS_TOOLS
)brace
comma
(brace
l_string|&quot;Wacom Intuos 9x12&quot;
comma
l_int|10
comma
l_int|30480
comma
l_int|23060
comma
l_int|1023
comma
l_int|15
comma
id|wacom_intuos_irq
comma
l_int|0
comma
id|WACOM_INTUOS_ABS
comma
l_int|0
comma
id|WACOM_INTUOS_BUTTONS
comma
id|WACOM_INTUOS_TOOLS
)brace
comma
(brace
l_string|&quot;Wacom Intuos 12x12&quot;
comma
l_int|10
comma
l_int|30480
comma
l_int|30480
comma
l_int|1023
comma
l_int|15
comma
id|wacom_intuos_irq
comma
l_int|0
comma
id|WACOM_INTUOS_ABS
comma
l_int|0
comma
id|WACOM_INTUOS_BUTTONS
comma
id|WACOM_INTUOS_TOOLS
)brace
comma
(brace
l_string|&quot;Wacom Intuos 12x18&quot;
comma
l_int|10
comma
l_int|47720
comma
l_int|30480
comma
l_int|1023
comma
l_int|15
comma
id|wacom_intuos_irq
comma
l_int|0
comma
id|WACOM_INTUOS_ABS
comma
l_int|0
comma
id|WACOM_INTUOS_BUTTONS
comma
id|WACOM_INTUOS_TOOLS
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|wacom_ids
r_struct
id|usb_device_id
id|wacom_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x10
)paren
comma
id|driver_info
suffix:colon
l_int|0
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x20
)paren
comma
id|driver_info
suffix:colon
l_int|1
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x21
)paren
comma
id|driver_info
suffix:colon
l_int|2
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x22
)paren
comma
id|driver_info
suffix:colon
l_int|3
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x23
)paren
comma
id|driver_info
suffix:colon
l_int|4
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_WACOM
comma
l_int|0x24
)paren
comma
id|driver_info
suffix:colon
l_int|5
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|wacom_ids
)paren
suffix:semicolon
DECL|function|wacom_open
r_static
r_int
id|wacom_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|wacom
op_star
id|wacom
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|wacom-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|wacom-&gt;irq.dev
op_assign
id|wacom-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|wacom-&gt;irq
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wacom_close
r_static
r_void
id|wacom_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|wacom
op_star
id|wacom
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
id|wacom-&gt;open
)paren
id|usb_unlink_urb
c_func
(paren
op_amp
id|wacom-&gt;irq
)paren
suffix:semicolon
)brace
DECL|function|wacom_probe
r_static
r_void
op_star
id|wacom_probe
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
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|wacom
op_star
id|wacom
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|wacom
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|wacom
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|wacom
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|wacom
)paren
)paren
suffix:semicolon
id|wacom-&gt;features
op_assign
id|wacom_features
op_plus
id|id-&gt;driver_info
suffix:semicolon
id|wacom-&gt;dev.evbit
(braket
l_int|0
)braket
op_or_assign
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
op_or
id|wacom-&gt;features-&gt;evbit
suffix:semicolon
id|wacom-&gt;dev.absbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
op_or
id|BIT
c_func
(paren
id|ABS_PRESSURE
)paren
op_or
id|BIT
c_func
(paren
id|ABS_DISTANCE
)paren
op_or
id|wacom-&gt;features-&gt;absbit
suffix:semicolon
id|wacom-&gt;dev.relbit
(braket
l_int|0
)braket
op_or_assign
id|wacom-&gt;features-&gt;relbit
suffix:semicolon
id|wacom-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
op_or
id|wacom-&gt;features-&gt;btnbit
suffix:semicolon
id|wacom-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_DIGI
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOOL_PEN
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOOL_RUBBER
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOOL_MOUSE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
op_or
id|BIT
c_func
(paren
id|BTN_STYLUS
)paren
op_or
id|BIT
c_func
(paren
id|BTN_STYLUS2
)paren
op_or
id|wacom-&gt;features-&gt;digibit
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_X
)braket
op_assign
id|wacom-&gt;features-&gt;x_max
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_Y
)braket
op_assign
id|wacom-&gt;features-&gt;y_max
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_PRESSURE
)braket
op_assign
id|wacom-&gt;features-&gt;pressure_max
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_DISTANCE
)braket
op_assign
id|wacom-&gt;features-&gt;distance_max
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_TILT_X
)braket
op_assign
l_int|127
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_TILT_Y
)braket
op_assign
l_int|127
suffix:semicolon
id|wacom-&gt;dev.absmin
(braket
id|ABS_RZ
)braket
op_assign
op_minus
l_int|900
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_RZ
)braket
op_assign
l_int|899
suffix:semicolon
id|wacom-&gt;dev.absmin
(braket
id|ABS_THROTTLE
)braket
op_assign
op_minus
l_int|1023
suffix:semicolon
id|wacom-&gt;dev.absmax
(braket
id|ABS_THROTTLE
)braket
op_assign
l_int|1023
suffix:semicolon
id|wacom-&gt;dev.absfuzz
(braket
id|ABS_X
)braket
op_assign
l_int|4
suffix:semicolon
id|wacom-&gt;dev.absfuzz
(braket
id|ABS_Y
)braket
op_assign
l_int|4
suffix:semicolon
id|wacom-&gt;dev
dot
r_private
op_assign
id|wacom
suffix:semicolon
id|wacom-&gt;dev.open
op_assign
id|wacom_open
suffix:semicolon
id|wacom-&gt;dev.close
op_assign
id|wacom_close
suffix:semicolon
id|wacom-&gt;dev.name
op_assign
id|wacom-&gt;features-&gt;name
suffix:semicolon
id|wacom-&gt;dev.idbus
op_assign
id|BUS_USB
suffix:semicolon
id|wacom-&gt;dev.idvendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|wacom-&gt;dev.idproduct
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|wacom-&gt;dev.idversion
op_assign
id|dev-&gt;descriptor.bcdDevice
suffix:semicolon
id|wacom-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|endpoint
op_assign
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|interface
(braket
id|ifnum
)braket
dot
id|altsetting
(braket
l_int|0
)braket
dot
id|endpoint
op_plus
l_int|0
suffix:semicolon
id|FILL_INT_URB
c_func
(paren
op_amp
id|wacom-&gt;irq
comma
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|wacom-&gt;data
comma
id|wacom-&gt;features-&gt;pktlen
comma
id|wacom-&gt;features-&gt;irq
comma
id|wacom
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|wacom-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s on usb%d:%d.%d&bslash;n&quot;
comma
id|wacom-&gt;dev.number
comma
id|wacom-&gt;features-&gt;name
comma
id|dev-&gt;bus-&gt;busnum
comma
id|dev-&gt;devnum
comma
id|ifnum
)paren
suffix:semicolon
r_return
id|wacom
suffix:semicolon
)brace
DECL|function|wacom_disconnect
r_static
r_void
id|wacom_disconnect
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
id|wacom
op_star
id|wacom
op_assign
id|ptr
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|wacom-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|wacom-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|wacom
)paren
suffix:semicolon
)brace
DECL|variable|wacom_driver
r_static
r_struct
id|usb_driver
id|wacom_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;wacom&quot;
comma
id|probe
suffix:colon
id|wacom_probe
comma
id|disconnect
suffix:colon
id|wacom_disconnect
comma
id|id_table
suffix:colon
id|wacom_ids
comma
)brace
suffix:semicolon
DECL|function|wacom_init
r_static
r_int
id|__init
id|wacom_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|wacom_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wacom_exit
r_static
r_void
id|__exit
id|wacom_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|wacom_driver
)paren
suffix:semicolon
)brace
DECL|variable|wacom_init
id|module_init
c_func
(paren
id|wacom_init
)paren
suffix:semicolon
DECL|variable|wacom_exit
id|module_exit
c_func
(paren
id|wacom_exit
)paren
suffix:semicolon
eof
