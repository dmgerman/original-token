multiline_comment|/*&n; *  linux/include/asm-ppc/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; *  Modified for Power Macintosh by Paul Mackerras&n; */
multiline_comment|/*&n; * This file contains the ppc architecture specific keyboard definitions -&n; * like the intel pc for prep systems, different for power macs.&n; */
macro_line|#ifndef __ASMPPC_KEYBOARD_H
DECL|macro|__ASMPPC_KEYBOARD_H
mdefine_line|#define __ASMPPC_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/adb.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifdef CONFIG_APUS
macro_line|#include &lt;asm-m68k/keyboard.h&gt;
macro_line|#else
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;1
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS&t;0
DECL|macro|INIT_KBD
mdefine_line|#define INIT_KBD
DECL|function|kbd_setkeycode
r_static
r_inline
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
id|ppc_md
dot
id|kbd_setkeycode
c_func
(paren
id|scancode
comma
id|keycode
)paren
suffix:semicolon
)brace
DECL|function|kbd_getkeycode
r_static
r_inline
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
id|ppc_md
dot
id|kbd_getkeycode
c_func
(paren
id|scancode
)paren
suffix:semicolon
)brace
DECL|function|kbd_translate
r_static
r_inline
r_int
id|kbd_translate
c_func
(paren
r_int
r_char
id|keycode
comma
r_int
r_char
op_star
id|keycodep
comma
r_char
id|raw_mode
)paren
(brace
r_return
id|ppc_md
dot
id|kbd_translate
c_func
(paren
id|keycode
comma
id|keycodep
comma
id|raw_mode
)paren
suffix:semicolon
)brace
DECL|function|kbd_unexpected_up
r_static
r_inline
r_int
id|kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
r_return
id|ppc_md
dot
id|kbd_unexpected_up
c_func
(paren
id|keycode
)paren
suffix:semicolon
)brace
DECL|function|kbd_leds
r_static
r_inline
r_void
id|kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
id|ppc_md
dot
id|kbd_leds
c_func
(paren
id|leds
)paren
suffix:semicolon
)brace
DECL|function|kbd_init_hw
r_static
r_inline
r_void
id|kbd_init_hw
c_func
(paren
r_void
)paren
(brace
id|ppc_md
dot
id|kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;(ppc_md.kbd_sysrq_xlate)
macro_line|#ifdef CONFIG_MAC_KEYBOARD
DECL|macro|SYSRQ_KEY
macro_line|# define SYSRQ_KEY 0x69
macro_line|#else
DECL|macro|SYSRQ_KEY
macro_line|# define SYSRQ_KEY 0x54
macro_line|#endif
macro_line|#endif /* CONFIG_APUS */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMPPC_KEYBOARD_H */
eof
