multiline_comment|/*&n; *  linux/include/asm-mips/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; */
multiline_comment|/*&n; *  This file contains the mips architecture specific keyboard definitions&n; */
macro_line|#ifndef __ASMMIPS_KEYBOARD_H
DECL|macro|__ASMMIPS_KEYBOARD_H
mdefine_line|#define __ASMMIPS_KEYBOARD_H
macro_line|#ifdef __KERNEL__
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;1
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS&t;0
DECL|macro|KBD_REPORT_ERR
mdefine_line|#define KBD_REPORT_ERR
DECL|macro|KBD_REPORT_UNKN
mdefine_line|#define KBD_REPORT_UNKN
multiline_comment|/* #define KBD_IS_FOCUS_9000 */
r_extern
r_int
id|pckbd_setkeycode
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
suffix:semicolon
r_extern
r_int
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_pretranslate
c_func
(paren
r_int
r_char
id|scancode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_translate
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
suffix:semicolon
r_extern
r_char
id|pckbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;pckbd_setkeycode
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;pckbd_getkeycode
DECL|macro|kbd_pretranslate
mdefine_line|#define kbd_pretranslate&t;pckbd_pretranslate
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;pckbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;pckbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;pckbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;pckbd_init_hw
DECL|macro|INIT_KBD
mdefine_line|#define INIT_KBD
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMMIPS_KEYBOARD_H */
eof
