multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/keyboard.h&n; *&n; * Keyboard driver definitions for RiscPC architecture&n; *&n; * (C) 1998 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_int
id|ps2kbd_pretranslate
c_func
(paren
r_int
r_char
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|ps2kbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode_p
comma
r_char
op_star
id|up_flag_p
)paren
suffix:semicolon
r_extern
r_void
id|ps2kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|ps2kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|ps2kbd_sysrq_xlate
(braket
id|NR_SCANCODES
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;(-EINVAL)
multiline_comment|/* Prototype: int kbd_pretranslate(scancode, raw_mode)&n; * Returns  : 0 to ignore scancode&n; */
DECL|macro|kbd_pretranslate
mdefine_line|#define kbd_pretranslate(sc,rm)&t;&t;ps2kbd_pretranslate(sc)
multiline_comment|/* Prototype: int kbd_translate(scancode, *keycode, *up_flag, raw_mode)&n; * Returns  : 0 to ignore scancode, *keycode set to keycode, *up_flag&n; *            set to 0200 if scancode indicates release&n; */
macro_line|#ifdef NEW_KEYBOARD
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, ufp, rm)&t;ps2kbd_translate(sc, kcp, ufp)
macro_line|#else
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm) ({ unsigned int up_flag; ps2kbd_translate(sc, kcp, &amp;up_flag); })
macro_line|#endif
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;ps2kbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;ps2kbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;ps2kbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;&t;disable_irq(IRQ_KEYBOARDRX)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;&t;enable_irq(IRQ_KEYBOARDRX)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;13
eof
