multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/keyboard.h&n; *&n; * Keyboard driver definitions for SA1100 architecture&n; *&n; * This really has to be cleaned up somehow...&n; * &n; */
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ 
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)  (-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)     (-EINVAL)
DECL|macro|kbd_pretranslate
mdefine_line|#define kbd_pretranslate(sc,kc)       1
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, raw)   kbd_drv_translate(sc, kcp, raw)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;kbd_drv_init()
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;&t;
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;0x54
eof
