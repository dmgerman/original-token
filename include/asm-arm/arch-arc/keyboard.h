multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/keyboard.h&n; *&n; * Keyboard driver definitions for Acorn Archimedes/A5000&n; * architecture&n; *&n; * Copyright (C) 1998 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_int
id|a5kkbd_translate
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
id|a5kkbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|a5kkbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|a5kkbd_sysrq_xlate
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
mdefine_line|#define kbd_pretranslate(sc,rm)&t;(1)
multiline_comment|/* Prototype: int kbd_translate(scancode, *keycode, *up_flag, raw_mode)&n; * Returns  : 0 to ignore scancode, *keycode set to keycode, *up_flag&n; *            set to 0200 if scancode indicates release&n; */
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, ufp, rm)&t;a5kkbd_translate(sc, kcp, ufp)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;a5kkbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;a5kkbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;a5kkbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;&t;disable_irq(IRQ_KEYBOARDRX)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;&t;enable_irq(IRQ_KEYBOARDRX)
eof