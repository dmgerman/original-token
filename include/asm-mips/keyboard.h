multiline_comment|/*&n; * CPU specific parts of the keyboard driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * $Id: keyboard.h,v 1.8 1998/05/07 00:40:03 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_KEYBOARD_H
DECL|macro|__ASM_MIPS_KEYBOARD_H
mdefine_line|#define __ASM_MIPS_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
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
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
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
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate         pckbd_sysrq_xlate
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do { } while(0)
multiline_comment|/* Pointers to keyboard hardware access and init functions.  */
DECL|variable|kbd_read_input
r_int
r_char
(paren
op_star
id|kbd_read_input
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|kbd_write_output
r_void
(paren
op_star
id|kbd_write_output
)paren
(paren
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|variable|kbd_write_command
r_void
(paren
op_star
id|kbd_write_command
)paren
(paren
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|variable|kbd_read_status
r_int
r_char
(paren
op_star
id|kbd_read_status
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|keyboard_setup
r_void
(paren
op_star
id|keyboard_setup
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS_JAZZ
multiline_comment|/* Not true for Jazz machines, we cheat a bit for &squot;em. */
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ 1
multiline_comment|/*&n; * No PS/2 style mouse support for Jazz machines&n; */
macro_line|#endif /* CONFIG_MIPS_JAZZ */
macro_line|#ifdef CONFIG_SGI
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS 1
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ 20
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver.&n; * Aux device and keyboard share the interrupt on the Indy.&n; */
DECL|macro|ps2_request_irq
mdefine_line|#define ps2_request_irq() 0
DECL|macro|ps2_free_irq
mdefine_line|#define ps2_free_irq(void) do { } while(0);
macro_line|#endif /* CONFIG_SGI */
macro_line|#if defined(CONFIG_ACER_PICA_61) || defined(CONFIG_SNI_RM200_PCI)
DECL|macro|CONF_KEYBOARD_USES_IO_PORTS
mdefine_line|#define CONF_KEYBOARD_USES_IO_PORTS
macro_line|#endif
macro_line|#ifdef CONF_KEYBOARD_USES_IO_PORTS
multiline_comment|/*&n; * Most other MIPS machines access the keyboard controller via&n; * memory mapped I/O ports.&n; */
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ 1
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver&n; */
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ 12
DECL|macro|ps2_request_irq
mdefine_line|#define ps2_request_irq()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;request_irq(AUX_IRQ, aux_interrupt, 0, &quot;PS/2 Mouse&quot;, NULL)
DECL|macro|ps2_free_irq
mdefine_line|#define ps2_free_irq(inode) free_irq(AUX_IRQ, NULL)
macro_line|#endif /* CONF_KEYBOARD_USES_IO_PORTS */
macro_line|#endif /* __KERNEL */
macro_line|#endif /* __ASM_MIPS_KEYBOARD_H */
eof
