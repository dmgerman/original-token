multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/keyboard.h&n; *&n; * Keyboard driver definitions for EBSA285 architecture&n; *&n; * (C) 1998 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|kbd_sysrq_xlate
r_static
r_int
r_char
id|kbd_sysrq_xlate
(braket
id|NR_SCANCODES
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;(-EINVAL)
multiline_comment|/* Prototype: int kbd_pretranslate(scancode, raw_mode)&n; * Returns  : 0 to ignore scancode&n; */
DECL|macro|kbd_pretranslate
mdefine_line|#define kbd_pretranslate(sc,rm)&t;&t;(1)
multiline_comment|/* Prototype: int kbd_translate(scancode, *keycode, *up_flag, raw_mode)&n; * Returns  : 0 to ignore scancode, *keycode set to keycode, *up_flag&n; *            set to 0200 if scancode indicates release&n; */
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, ufp, rm)&t;(1)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()
singleline_comment|//#define kbd_sysrq_xlate&t;&t;&t;ps2kbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
eof
