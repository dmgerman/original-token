multiline_comment|/*&n; *  linux/include/asm-m68k/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; */
multiline_comment|/*&n; *  This file contains the m68k architecture specific keyboard definitions&n; */
macro_line|#include &lt;linux/config.h&gt; /* CONFIG_MAGIC_SYSRQ */
macro_line|#ifndef __M68K_KEYBOARD_H
DECL|macro|__M68K_KEYBOARD_H
mdefine_line|#define __M68K_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/machdep.h&gt;
DECL|function|kbd_setkeycode
r_static
id|__inline__
r_int
id|kbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|kbd_getkeycode
r_static
id|__inline__
r_int
id|kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
r_return
id|scancode
OG
l_int|127
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|scancode
suffix:semicolon
)brace
DECL|function|kbd_translate
r_static
id|__inline__
r_int
id|kbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
(brace
op_star
id|keycode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kbd_unexpected_up
r_static
id|__inline__
r_char
id|kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
r_return
l_int|0200
suffix:semicolon
)brace
DECL|function|kbd_leds
r_static
id|__inline__
r_void
id|kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
r_if
c_cond
(paren
id|mach_kbd_leds
)paren
id|mach_kbd_leds
c_func
(paren
id|leds
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|macro|kbd_is_sysrq
mdefine_line|#define kbd_is_sysrq(keycode)&t;((keycode) == mach_sysrq_key &amp;&amp; &bslash;&n;&t;&t;&t;&t; (up_flag || &bslash;&n;&t;&t;&t;&t;  (shift_state &amp; mach_sysrq_shift_mask) == &bslash;&n;&t;&t;&t;&t;  mach_sysrq_shift_state))
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;mach_sysrq_xlate
macro_line|#endif
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;mach_keyb_init
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __M68K_KEYBOARD_H */
eof
