multiline_comment|/*&n; * linux/arch/m68k/amiga/amikeyb.c&n; *&n; * Amiga Keyboard driver for Linux/m68k&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Amiga support by Hamish Macdonald&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/keyboard.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|AMIKEY_CAPS
mdefine_line|#define AMIKEY_CAPS&t;(0x62)
DECL|macro|BREAK_MASK
mdefine_line|#define BREAK_MASK&t;(0x80)
DECL|macro|RESET_WARNING
mdefine_line|#define RESET_WARNING&t;(0xf0)&t;/* before rotation */
DECL|variable|__initdata
r_static
id|u_short
id|amiplain_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf060
comma
l_int|0xf031
comma
l_int|0xf032
comma
l_int|0xf033
comma
l_int|0xf034
comma
l_int|0xf035
comma
l_int|0xf036
comma
l_int|0xf037
comma
l_int|0xf038
comma
l_int|0xf039
comma
l_int|0xf030
comma
l_int|0xf02d
comma
l_int|0xf03d
comma
l_int|0xf05c
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xfb71
comma
l_int|0xfb77
comma
l_int|0xfb65
comma
l_int|0xfb72
comma
l_int|0xfb74
comma
l_int|0xfb79
comma
l_int|0xfb75
comma
l_int|0xfb69
comma
l_int|0xfb6f
comma
l_int|0xfb70
comma
l_int|0xf05b
comma
l_int|0xf05d
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xfb61
comma
l_int|0xfb73
comma
l_int|0xfb64
comma
l_int|0xfb66
comma
l_int|0xfb67
comma
l_int|0xfb68
comma
l_int|0xfb6a
comma
l_int|0xfb6b
comma
l_int|0xfb6c
comma
l_int|0xf03b
comma
l_int|0xf027
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xfb7a
comma
l_int|0xfb78
comma
l_int|0xfb63
comma
l_int|0xfb76
comma
l_int|0xfb62
comma
l_int|0xfb6e
comma
l_int|0xfb6d
comma
l_int|0xf02c
comma
l_int|0xf02e
comma
l_int|0xf02f
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf020
comma
l_int|0xf07f
comma
l_int|0xf009
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf01b
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf100
comma
l_int|0xf101
comma
l_int|0xf102
comma
l_int|0xf103
comma
l_int|0xf104
comma
l_int|0xf105
comma
l_int|0xf106
comma
l_int|0xf107
comma
l_int|0xf108
comma
l_int|0xf109
comma
l_int|0xf312
comma
l_int|0xf313
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf11b
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amishift_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf07e
comma
l_int|0xf021
comma
l_int|0xf040
comma
l_int|0xf023
comma
l_int|0xf024
comma
l_int|0xf025
comma
l_int|0xf05e
comma
l_int|0xf026
comma
l_int|0xf02a
comma
l_int|0xf028
comma
l_int|0xf029
comma
l_int|0xf05f
comma
l_int|0xf02b
comma
l_int|0xf07c
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xfb51
comma
l_int|0xfb57
comma
l_int|0xfb45
comma
l_int|0xfb52
comma
l_int|0xfb54
comma
l_int|0xfb59
comma
l_int|0xfb55
comma
l_int|0xfb49
comma
l_int|0xfb4f
comma
l_int|0xfb50
comma
l_int|0xf07b
comma
l_int|0xf07d
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xfb41
comma
l_int|0xfb53
comma
l_int|0xfb44
comma
l_int|0xfb46
comma
l_int|0xfb47
comma
l_int|0xfb48
comma
l_int|0xfb4a
comma
l_int|0xfb4b
comma
l_int|0xfb4c
comma
l_int|0xf03a
comma
l_int|0xf022
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xfb5a
comma
l_int|0xfb58
comma
l_int|0xfb43
comma
l_int|0xfb56
comma
l_int|0xfb42
comma
l_int|0xfb4e
comma
l_int|0xfb4d
comma
l_int|0xf03c
comma
l_int|0xf03e
comma
l_int|0xf03f
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf020
comma
l_int|0xf07f
comma
l_int|0xf009
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf01b
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf10a
comma
l_int|0xf10b
comma
l_int|0xf10c
comma
l_int|0xf10d
comma
l_int|0xf10e
comma
l_int|0xf10f
comma
l_int|0xf110
comma
l_int|0xf111
comma
l_int|0xf112
comma
l_int|0xf113
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf203
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amialtgr_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf040
comma
l_int|0xf200
comma
l_int|0xf024
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf07b
comma
l_int|0xf05b
comma
l_int|0xf05d
comma
l_int|0xf07d
comma
l_int|0xf05c
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf07e
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf200
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf50c
comma
l_int|0xf50d
comma
l_int|0xf50e
comma
l_int|0xf50f
comma
l_int|0xf510
comma
l_int|0xf511
comma
l_int|0xf512
comma
l_int|0xf513
comma
l_int|0xf514
comma
l_int|0xf515
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf204
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amictrl_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf000
comma
l_int|0xf200
comma
l_int|0xf000
comma
l_int|0xf01b
comma
l_int|0xf01c
comma
l_int|0xf01d
comma
l_int|0xf01e
comma
l_int|0xf01f
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf01f
comma
l_int|0xf200
comma
l_int|0xf01c
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xf011
comma
l_int|0xf017
comma
l_int|0xf005
comma
l_int|0xf012
comma
l_int|0xf014
comma
l_int|0xf019
comma
l_int|0xf015
comma
l_int|0xf009
comma
l_int|0xf00f
comma
l_int|0xf010
comma
l_int|0xf01b
comma
l_int|0xf01d
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xf001
comma
l_int|0xf013
comma
l_int|0xf004
comma
l_int|0xf006
comma
l_int|0xf007
comma
l_int|0xf008
comma
l_int|0xf00a
comma
l_int|0xf00b
comma
l_int|0xf00c
comma
l_int|0xf200
comma
l_int|0xf007
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xf01a
comma
l_int|0xf018
comma
l_int|0xf003
comma
l_int|0xf016
comma
l_int|0xf002
comma
l_int|0xf00e
comma
l_int|0xf00d
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf000
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf100
comma
l_int|0xf101
comma
l_int|0xf102
comma
l_int|0xf103
comma
l_int|0xf104
comma
l_int|0xf105
comma
l_int|0xf106
comma
l_int|0xf107
comma
l_int|0xf108
comma
l_int|0xf109
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf202
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amishift_ctrl_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf200
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf200
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amialt_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf860
comma
l_int|0xf831
comma
l_int|0xf832
comma
l_int|0xf833
comma
l_int|0xf834
comma
l_int|0xf835
comma
l_int|0xf836
comma
l_int|0xf837
comma
l_int|0xf838
comma
l_int|0xf839
comma
l_int|0xf830
comma
l_int|0xf82d
comma
l_int|0xf83d
comma
l_int|0xf85c
comma
l_int|0xf200
comma
l_int|0xf900
comma
l_int|0xf871
comma
l_int|0xf877
comma
l_int|0xf865
comma
l_int|0xf872
comma
l_int|0xf874
comma
l_int|0xf879
comma
l_int|0xf875
comma
l_int|0xf869
comma
l_int|0xf86f
comma
l_int|0xf870
comma
l_int|0xf85b
comma
l_int|0xf85d
comma
l_int|0xf200
comma
l_int|0xf901
comma
l_int|0xf902
comma
l_int|0xf903
comma
l_int|0xf861
comma
l_int|0xf873
comma
l_int|0xf864
comma
l_int|0xf866
comma
l_int|0xf867
comma
l_int|0xf868
comma
l_int|0xf86a
comma
l_int|0xf86b
comma
l_int|0xf86c
comma
l_int|0xf83b
comma
l_int|0xf827
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf904
comma
l_int|0xf905
comma
l_int|0xf906
comma
l_int|0xf200
comma
l_int|0xf87a
comma
l_int|0xf878
comma
l_int|0xf863
comma
l_int|0xf876
comma
l_int|0xf862
comma
l_int|0xf86e
comma
l_int|0xf86d
comma
l_int|0xf82c
comma
l_int|0xf82e
comma
l_int|0xf82f
comma
l_int|0xf200
comma
l_int|0xf310
comma
l_int|0xf907
comma
l_int|0xf908
comma
l_int|0xf909
comma
l_int|0xf820
comma
l_int|0xf87f
comma
l_int|0xf809
comma
l_int|0xf30e
comma
l_int|0xf80d
comma
l_int|0xf81b
comma
l_int|0xf87f
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf500
comma
l_int|0xf501
comma
l_int|0xf502
comma
l_int|0xf503
comma
l_int|0xf504
comma
l_int|0xf505
comma
l_int|0xf506
comma
l_int|0xf507
comma
l_int|0xf508
comma
l_int|0xf509
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf204
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_short
id|amictrl_alt_map
(braket
id|NR_KEYS
)braket
id|__initdata
op_assign
(brace
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf300
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf301
comma
l_int|0xf302
comma
l_int|0xf303
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf304
comma
l_int|0xf305
comma
l_int|0xf306
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf20c
comma
l_int|0xf307
comma
l_int|0xf308
comma
l_int|0xf309
comma
l_int|0xf200
comma
l_int|0xf07f
comma
l_int|0xf200
comma
l_int|0xf30e
comma
l_int|0xf201
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf30b
comma
l_int|0xf200
comma
l_int|0xf603
comma
l_int|0xf600
comma
l_int|0xf602
comma
l_int|0xf601
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf208
comma
l_int|0xf209
comma
l_int|0xf30d
comma
l_int|0xf30c
comma
l_int|0xf30a
comma
l_int|0xf200
comma
l_int|0xf700
comma
l_int|0xf700
comma
l_int|0xf207
comma
l_int|0xf702
comma
l_int|0xf703
comma
l_int|0xf701
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
l_int|0xf200
comma
)brace
suffix:semicolon
DECL|macro|DEFAULT_KEYB_REP_DELAY
mdefine_line|#define&t;DEFAULT_KEYB_REP_DELAY&t;(HZ/4)
DECL|macro|DEFAULT_KEYB_REP_RATE
mdefine_line|#define&t;DEFAULT_KEYB_REP_RATE&t;(HZ/25)
multiline_comment|/* These could be settable by some ioctl() in future... */
DECL|variable|key_repeat_delay
r_static
r_int
r_int
id|key_repeat_delay
op_assign
id|DEFAULT_KEYB_REP_DELAY
suffix:semicolon
DECL|variable|key_repeat_rate
r_static
r_int
r_int
id|key_repeat_rate
op_assign
id|DEFAULT_KEYB_REP_RATE
suffix:semicolon
DECL|variable|rep_scancode
r_static
r_int
r_char
id|rep_scancode
suffix:semicolon
r_static
r_void
id|amikeyb_rep
c_func
(paren
r_int
r_int
id|ignore
)paren
suffix:semicolon
DECL|variable|amikeyb_rep_timer
r_static
r_struct
id|timer_list
id|amikeyb_rep_timer
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|amikeyb_rep
)brace
suffix:semicolon
DECL|function|amikeyb_rep
r_static
r_void
id|amikeyb_rep
c_func
(paren
r_int
r_int
id|ignore
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|kbd_pt_regs
op_assign
l_int|NULL
suffix:semicolon
id|amikeyb_rep_timer.expires
op_assign
id|jiffies
op_plus
id|key_repeat_rate
suffix:semicolon
id|amikeyb_rep_timer.prev
op_assign
id|amikeyb_rep_timer.next
op_assign
l_int|NULL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|amikeyb_rep_timer
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
id|rep_scancode
comma
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|keyboard_interrupt
r_static
r_void
id|keyboard_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_char
id|scancode
comma
id|break_flag
comma
id|keycode
suffix:semicolon
r_static
r_int
id|reset_warning
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* save frame for register dump */
id|kbd_pt_regs
op_assign
id|fp
suffix:semicolon
multiline_comment|/* get and invert scancode (keyboard is active low) */
id|scancode
op_assign
op_complement
id|ciaa.sdr
suffix:semicolon
multiline_comment|/* switch SP pin to output for handshake */
id|ciaa.cra
op_or_assign
l_int|0x40
suffix:semicolon
macro_line|#if 0 /* No longer used */
multiline_comment|/*&n;     *  On receipt of the second RESET_WARNING, we must not pull KDAT high&n;     *  again to delay the hard reset as long as possible.&n;     *&n;     *  Note that not all keyboards send reset warnings...&n;     */
r_if
c_cond
(paren
id|reset_warning
)paren
r_if
c_cond
(paren
id|scancode
op_eq
id|RESET_WARNING
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;amikeyb: Ctrl-Amiga-Amiga reset warning!!&bslash;n&quot;
l_string|&quot;The system will be reset within 10 seconds!!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Panic doesn&squot;t sync from within an interrupt, so we do nothing */
r_return
suffix:semicolon
)brace
r_else
multiline_comment|/* Probably a mistake, cancel the alert */
id|reset_warning
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* wait until 85 us have expired */
id|udelay
c_func
(paren
l_int|85
)paren
suffix:semicolon
multiline_comment|/* switch CIA serial port to input mode */
id|ciaa.cra
op_and_assign
op_complement
l_int|0x40
suffix:semicolon
id|mark_bh
c_func
(paren
id|KEYBOARD_BH
)paren
suffix:semicolon
multiline_comment|/* rotate scan code to get up/down bit in proper position */
id|scancode
op_assign
(paren
(paren
id|scancode
op_rshift
l_int|1
)paren
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|scancode
op_lshift
l_int|7
)paren
op_amp
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/*&n;     * Check make/break first&n;     */
id|break_flag
op_assign
id|scancode
op_amp
id|BREAK_MASK
suffix:semicolon
id|keycode
op_assign
id|scancode
op_amp
(paren
r_int
r_char
)paren
op_complement
id|BREAK_MASK
suffix:semicolon
r_if
c_cond
(paren
id|keycode
op_eq
id|AMIKEY_CAPS
)paren
(brace
multiline_comment|/* if the key is CAPS, fake a press/release. */
id|handle_scancode
c_func
(paren
id|AMIKEY_CAPS
comma
l_int|1
)paren
suffix:semicolon
id|handle_scancode
c_func
(paren
id|AMIKEY_CAPS
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|keycode
OL
l_int|0x78
)paren
(brace
multiline_comment|/* handle repeat */
r_if
c_cond
(paren
id|break_flag
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|amikeyb_rep_timer
)paren
suffix:semicolon
id|rep_scancode
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|del_timer
c_func
(paren
op_amp
id|amikeyb_rep_timer
)paren
suffix:semicolon
id|rep_scancode
op_assign
id|keycode
suffix:semicolon
id|amikeyb_rep_timer.expires
op_assign
id|jiffies
op_plus
id|key_repeat_delay
suffix:semicolon
id|amikeyb_rep_timer.prev
op_assign
id|amikeyb_rep_timer.next
op_assign
l_int|NULL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|amikeyb_rep_timer
)paren
suffix:semicolon
)brace
id|handle_scancode
c_func
(paren
id|keycode
comma
op_logical_neg
id|break_flag
)paren
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|keycode
)paren
(brace
r_case
l_int|0x78
suffix:colon
id|reset_warning
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x79
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;amikeyb: keyboard lost sync&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7a
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;amikeyb: keyboard buffer overflow&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0 /* obsolete according to the HRM */
r_case
l_int|0x7b
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;amikeyb: keyboard controller failure&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|0x7c
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;amikeyb: keyboard selftest failure&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7d
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;amikeyb: initiate power-up key stream&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7e
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;amikeyb: terminate power-up key stream&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0 /* obsolete according to the HRM */
r_case
l_int|0x7f
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;amikeyb: keyboard interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;amikeyb: unknown keyboard communication code 0x%02x&bslash;n&quot;
comma
id|scancode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|amiga_keyb_init
r_int
id|__init
id|amiga_keyb_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|AMI_KEYBOARD
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* setup key map */
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|0
)braket
comma
id|amiplain_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|1
)braket
comma
id|amishift_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|2
)braket
comma
id|amialtgr_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|4
)braket
comma
id|amictrl_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|5
)braket
comma
id|amishift_ctrl_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|8
)braket
comma
id|amialt_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key_maps
(braket
l_int|12
)braket
comma
id|amictrl_alt_map
comma
r_sizeof
(paren
id|plain_map
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     * Initialize serial data direction.&n;     */
id|ciaa.cra
op_and_assign
op_complement
l_int|0x41
suffix:semicolon
multiline_comment|/* serial data in, turn off TA */
multiline_comment|/*&n;     * arrange for processing of keyboard interrupt&n;     */
id|request_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_SP
comma
id|keyboard_interrupt
comma
l_int|0
comma
l_string|&quot;keyboard&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amiga_kbdrate
r_int
id|amiga_kbdrate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|k
)paren
(brace
r_if
c_cond
(paren
id|k-&gt;delay
OG
l_int|0
)paren
(brace
multiline_comment|/* convert from msec to jiffies */
id|key_repeat_delay
op_assign
(paren
id|k-&gt;delay
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|key_repeat_delay
OL
l_int|1
)paren
id|key_repeat_delay
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k-&gt;rate
OG
l_int|0
)paren
(brace
id|key_repeat_rate
op_assign
(paren
id|k-&gt;rate
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|key_repeat_rate
OL
l_int|1
)paren
id|key_repeat_rate
op_assign
l_int|1
suffix:semicolon
)brace
id|k-&gt;delay
op_assign
id|key_repeat_delay
op_star
l_int|1000
op_div
id|HZ
suffix:semicolon
id|k-&gt;rate
op_assign
id|key_repeat_rate
op_star
l_int|1000
op_div
id|HZ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
