multiline_comment|/*&n; * $Id: keybdev.c,v 1.3 2000/05/28 17:31:36 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Input driver to keyboard driver binding.&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#if defined(CONFIG_X86) || defined(CONFIG_IA64) || defined(__alpha__) || defined(__mips__)
DECL|variable|x86_sysrq_alt
r_static
r_int
id|x86_sysrq_alt
op_assign
l_int|0
suffix:semicolon
DECL|variable|x86_keycodes
r_static
r_int
r_int
id|x86_keycodes
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
comma
l_int|32
comma
l_int|33
comma
l_int|34
comma
l_int|35
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|39
comma
l_int|40
comma
l_int|41
comma
l_int|42
comma
l_int|43
comma
l_int|44
comma
l_int|45
comma
l_int|46
comma
l_int|47
comma
l_int|48
comma
l_int|49
comma
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|54
comma
l_int|55
comma
l_int|56
comma
l_int|57
comma
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|69
comma
l_int|70
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|74
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|78
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|82
comma
l_int|83
comma
l_int|43
comma
l_int|85
comma
l_int|86
comma
l_int|87
comma
l_int|88
comma
l_int|115
comma
l_int|119
comma
l_int|120
comma
l_int|121
comma
l_int|375
comma
l_int|123
comma
l_int|90
comma
l_int|284
comma
l_int|285
comma
l_int|309
comma
l_int|298
comma
l_int|312
comma
l_int|91
comma
l_int|327
comma
l_int|328
comma
l_int|329
comma
l_int|331
comma
l_int|333
comma
l_int|335
comma
l_int|336
comma
l_int|337
comma
l_int|338
comma
l_int|339
comma
l_int|367
comma
l_int|294
comma
l_int|293
comma
l_int|286
comma
l_int|350
comma
l_int|92
comma
l_int|334
comma
l_int|512
comma
l_int|116
comma
l_int|377
comma
l_int|109
comma
l_int|111
comma
l_int|373
comma
l_int|347
comma
l_int|348
comma
l_int|349
comma
l_int|360
comma
l_int|93
comma
l_int|94
comma
l_int|95
comma
l_int|98
comma
l_int|376
comma
l_int|100
comma
l_int|101
comma
l_int|357
comma
l_int|316
comma
l_int|354
comma
l_int|304
comma
l_int|289
comma
l_int|102
comma
l_int|351
comma
l_int|355
comma
l_int|103
comma
l_int|104
comma
l_int|105
comma
l_int|275
comma
l_int|281
comma
l_int|272
comma
l_int|306
comma
l_int|106
comma
l_int|274
comma
l_int|107
comma
l_int|288
comma
l_int|364
comma
l_int|358
comma
l_int|363
comma
l_int|362
comma
l_int|361
comma
l_int|291
comma
l_int|108
comma
l_int|381
comma
l_int|290
comma
l_int|287
comma
l_int|292
comma
l_int|279
comma
l_int|305
comma
l_int|280
comma
l_int|99
comma
l_int|112
comma
l_int|257
comma
l_int|258
comma
l_int|113
comma
l_int|270
comma
l_int|114
comma
l_int|118
comma
l_int|117
comma
l_int|125
comma
l_int|374
comma
l_int|379
comma
l_int|259
comma
l_int|260
comma
l_int|261
comma
l_int|262
comma
l_int|263
comma
l_int|264
comma
l_int|265
comma
l_int|266
comma
l_int|267
comma
l_int|268
comma
l_int|269
comma
l_int|271
comma
l_int|273
comma
l_int|276
comma
l_int|277
comma
l_int|278
comma
l_int|282
comma
l_int|283
comma
l_int|295
comma
l_int|296
comma
l_int|297
comma
l_int|299
comma
l_int|300
comma
l_int|301
comma
l_int|302
comma
l_int|303
comma
l_int|307
comma
l_int|308
comma
l_int|310
comma
l_int|313
comma
l_int|314
comma
l_int|315
comma
l_int|317
comma
l_int|318
comma
l_int|319
comma
l_int|320
comma
l_int|321
comma
l_int|322
comma
l_int|323
comma
l_int|324
comma
l_int|325
comma
l_int|326
comma
l_int|330
comma
l_int|332
comma
l_int|340
comma
l_int|341
comma
l_int|342
comma
l_int|343
comma
l_int|344
comma
l_int|345
comma
l_int|346
comma
l_int|356
comma
l_int|359
comma
l_int|365
comma
l_int|368
comma
l_int|369
comma
l_int|370
comma
l_int|371
comma
l_int|372
)brace
suffix:semicolon
DECL|function|emulate_raw
r_static
r_int
id|emulate_raw
c_func
(paren
r_int
r_int
id|keycode
comma
r_int
id|down
)paren
(brace
r_if
c_cond
(paren
id|keycode
OG
l_int|255
op_logical_or
op_logical_neg
id|x86_keycodes
(braket
id|keycode
)braket
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|keycode
op_eq
id|KEY_PAUSE
)paren
(brace
id|handle_scancode
c_func
(paren
l_int|0xe1
comma
l_int|1
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
l_int|0x1d
comma
id|down
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
l_int|0x45
comma
id|down
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|keycode
op_eq
id|KEY_SYSRQ
op_logical_and
id|x86_sysrq_alt
)paren
(brace
id|handle_scancode
c_func
(paren
l_int|0x54
comma
id|down
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x86_keycodes
(braket
id|keycode
)braket
op_amp
l_int|0x100
)paren
id|handle_scancode
c_func
(paren
l_int|0xe0
comma
l_int|1
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
id|x86_keycodes
(braket
id|keycode
)braket
op_amp
l_int|0x7f
comma
id|down
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keycode
op_eq
id|KEY_SYSRQ
)paren
(brace
id|handle_scancode
c_func
(paren
l_int|0xe0
comma
l_int|1
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
l_int|0x37
comma
id|down
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|keycode
op_eq
id|KEY_LEFTALT
op_logical_or
id|keycode
op_eq
id|KEY_RIGHTALT
)paren
id|x86_sysrq_alt
op_assign
id|down
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_ADB_KEYBOARD)
DECL|variable|mac_keycodes
r_static
r_int
r_char
id|mac_keycodes
(braket
l_int|128
)braket
op_assign
(brace
l_int|0
comma
l_int|53
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|23
comma
l_int|22
comma
l_int|26
comma
l_int|28
comma
l_int|25
comma
l_int|29
comma
l_int|27
comma
l_int|24
comma
l_int|51
comma
l_int|48
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|17
comma
l_int|16
comma
l_int|32
comma
l_int|34
comma
l_int|31
comma
l_int|35
comma
l_int|33
comma
l_int|30
comma
l_int|36
comma
l_int|54
comma
l_int|128
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|5
comma
l_int|4
comma
l_int|38
comma
l_int|40
comma
l_int|37
comma
l_int|41
comma
l_int|39
comma
l_int|50
comma
l_int|56
comma
l_int|42
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|11
comma
l_int|45
comma
l_int|46
comma
l_int|43
comma
l_int|47
comma
l_int|44
comma
l_int|123
comma
l_int|67
comma
l_int|58
comma
l_int|49
comma
l_int|57
comma
l_int|122
comma
l_int|120
comma
l_int|99
comma
l_int|118
comma
l_int|96
comma
l_int|97
comma
l_int|98
comma
l_int|100
comma
l_int|101
comma
l_int|109
comma
l_int|71
comma
l_int|107
comma
l_int|89
comma
l_int|91
comma
l_int|92
comma
l_int|78
comma
l_int|86
comma
l_int|87
comma
l_int|88
comma
l_int|69
comma
l_int|83
comma
l_int|84
comma
l_int|85
comma
l_int|82
comma
l_int|65
comma
l_int|42
comma
l_int|0
comma
l_int|10
comma
l_int|103
comma
l_int|111
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|76
comma
l_int|125
comma
l_int|75
comma
l_int|105
comma
l_int|124
comma
l_int|0
comma
l_int|115
comma
l_int|62
comma
l_int|116
comma
l_int|59
comma
l_int|60
comma
l_int|119
comma
l_int|61
comma
l_int|121
comma
l_int|114
comma
l_int|117
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|127
comma
l_int|81
comma
l_int|0
comma
l_int|113
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|55
comma
l_int|55
)brace
suffix:semicolon
DECL|function|emulate_raw
r_static
r_int
id|emulate_raw
c_func
(paren
r_int
r_int
id|keycode
comma
r_int
id|down
)paren
(brace
r_if
c_cond
(paren
id|keycode
OG
l_int|127
op_logical_or
op_logical_neg
id|mac_keycodes
(braket
id|keycode
)braket
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|handle_scancode
c_func
(paren
id|mac_keycodes
(braket
id|keycode
)braket
op_amp
l_int|0x7f
comma
id|down
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|keybdev_handler
r_static
r_struct
id|input_handler
id|keybdev_handler
suffix:semicolon
DECL|function|keybdev_ledfunc
r_void
id|keybdev_ledfunc
c_func
(paren
r_int
r_int
id|led
)paren
(brace
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
r_for
c_loop
(paren
id|handle
op_assign
id|keybdev_handler.handle
suffix:semicolon
id|handle
suffix:semicolon
id|handle
op_assign
id|handle-&gt;hnext
)paren
(brace
id|input_event
c_func
(paren
id|handle-&gt;dev
comma
id|EV_LED
comma
id|LED_SCROLLL
comma
op_logical_neg
op_logical_neg
(paren
id|led
op_amp
l_int|0x01
)paren
)paren
suffix:semicolon
id|input_event
c_func
(paren
id|handle-&gt;dev
comma
id|EV_LED
comma
id|LED_NUML
comma
op_logical_neg
op_logical_neg
(paren
id|led
op_amp
l_int|0x02
)paren
)paren
suffix:semicolon
id|input_event
c_func
(paren
id|handle-&gt;dev
comma
id|EV_LED
comma
id|LED_CAPSL
comma
op_logical_neg
op_logical_neg
(paren
id|led
op_amp
l_int|0x04
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|keybdev_event
r_void
id|keybdev_event
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
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
id|down
)paren
(brace
r_if
c_cond
(paren
id|type
op_ne
id|EV_KEY
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|emulate_raw
c_func
(paren
id|code
comma
id|down
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;keyboard.c: can&squot;t emulate rawmode for keycode %d&bslash;n&quot;
comma
id|code
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|keyboard_tasklet
)paren
suffix:semicolon
)brace
DECL|function|keybdev_connect
r_static
r_struct
id|input_handle
op_star
id|keybdev_connect
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
comma
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
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|EV_KEY
comma
id|dev-&gt;evbit
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|KEY_RESERVED
suffix:semicolon
id|i
OL
id|BTN_MISC
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|dev-&gt;keybit
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|BTN_MISC
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|handle
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|input_handle
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
id|handle
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|input_handle
)paren
)paren
suffix:semicolon
id|handle-&gt;dev
op_assign
id|dev
suffix:semicolon
id|handle-&gt;handler
op_assign
id|handler
suffix:semicolon
id|input_open_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keybdev.c: Adding keyboard: input%d&bslash;n&quot;
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_return
id|handle
suffix:semicolon
)brace
DECL|function|keybdev_disconnect
r_static
r_void
id|keybdev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keybdev.c: Removing keyboard: input%d&bslash;n&quot;
comma
id|handle-&gt;dev-&gt;number
)paren
suffix:semicolon
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
DECL|variable|keybdev_handler
r_static
r_struct
id|input_handler
id|keybdev_handler
op_assign
(brace
id|event
suffix:colon
id|keybdev_event
comma
id|connect
suffix:colon
id|keybdev_connect
comma
id|disconnect
suffix:colon
id|keybdev_disconnect
comma
)brace
suffix:semicolon
DECL|function|keybdev_init
r_static
r_int
id|__init
id|keybdev_init
c_func
(paren
r_void
)paren
(brace
id|input_register_handler
c_func
(paren
op_amp
id|keybdev_handler
)paren
suffix:semicolon
id|kbd_ledfunc
op_assign
id|keybdev_ledfunc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|keybdev_exit
r_static
r_void
id|__exit
id|keybdev_exit
c_func
(paren
r_void
)paren
(brace
id|kbd_ledfunc
op_assign
l_int|NULL
suffix:semicolon
id|input_unregister_handler
c_func
(paren
op_amp
id|keybdev_handler
)paren
suffix:semicolon
)brace
DECL|variable|keybdev_init
id|module_init
c_func
(paren
id|keybdev_init
)paren
suffix:semicolon
DECL|variable|keybdev_exit
id|module_exit
c_func
(paren
id|keybdev_exit
)paren
suffix:semicolon
eof
