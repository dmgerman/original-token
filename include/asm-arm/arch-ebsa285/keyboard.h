multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/keyboard.h&n; *&n; * Keyboard driver definitions for EBSA285 architecture&n; *&n; * (C) 1998 Russell King&n; * (C) 1998 Phil Blundell&n; */
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_int
id|have_isa_bridge
suffix:semicolon
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
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;IRQ_ISA_KEYBOARD
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __ret;&t;&t;&t;&t;&bslash;&n;&t;&t;if (have_isa_bridge)&t;&t;&t;&bslash;&n;&t;&t;&t;__ret = pckbd_setkeycode(sc,kc);&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__ret = -EINVAL;&t;&t;&bslash;&n;&t;&t;__ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int __ret;&t;&t;&t;&t;&bslash;&n;&t;&t;if (have_isa_bridge)&t;&t;&t;&bslash;&n;&t;&t;&t;__ret = pckbd_getkeycode(sc);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__ret = -EINVAL;&t;&t;&bslash;&n;&t;&t;__ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm)&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;pckbd_translate(sc, kcp, rm);&t;&t;&bslash;&n;&t;})
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;&t;pckbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (have_isa_bridge)&t;&t;&t;&bslash;&n;&t;&t;&t;pckbd_leds(leds);&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (have_isa_bridge)&t;&t;&t;&bslash;&n;&t;&t;&t;pckbd_init_hw();&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;pckbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;0x54
eof
