multiline_comment|/*&n; * linux/include/asm-arm/arch-vnc/keyboard.h&n; *&n; * Keyboard driver definitions for VNC architecture&n; *&n; * (C) 1998 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;IRQ_KEYBOARD
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
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;&t;pckbd_setkeycode
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;&t;pckbd_getkeycode
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, ufp, rm) ({ *ufp = sc &amp; 0200; &bslash;&n;&t;&t;pckbd_translate(sc &amp; 0x7f, kcp, rm);})
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;&t;pckbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;&t;pckbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;pckbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;pckbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
eof
