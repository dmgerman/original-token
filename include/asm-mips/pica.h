multiline_comment|/*&n; * Hardware info about Acer PICA 61 and similar&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Andreas Busse and Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_PICA_H 
DECL|macro|__ASM_MIPS_PICA_H
mdefine_line|#define __ASM_MIPS_PICA_H 
multiline_comment|/*&n; * The addresses below are virtual address. The mappings are&n; * created on startup via wired entries in the tlb. The Mips&n; * Magnum R3000 and R4000 machines are similar in many aspects,&n; * but many hardware register are accessible at 0xb9000000 in&n; * instead of 0xe0000000.&n; */
multiline_comment|/*&n; * Revision numbers in PICA_ASIC_REVISION&n; *&n; * 0xf0000000 - Rev1&n; * 0xf0000001 - Rev2&n; * 0xf0000002 - Rev3&n; */
DECL|macro|PICA_ASIC_REVISION
mdefine_line|#define PICA_ASIC_REVISION      0xe0000008
multiline_comment|/*&n; * The segments of the seven segment LED are mapped&n; * to the control bits as follows:&n; *&n; *         (7)&n; *      ---------&n; *      |       |&n; *  (2) |       | (6)&n; *      |  (1)  |&n; *      ---------&n; *      |       |&n; *  (3) |       | (5)&n; *      |  (4)  |&n; *      --------- . (0)&n; */
DECL|macro|PICA_LED
mdefine_line|#define PICA_LED                0xe000f000
multiline_comment|/*&n; * Some characters for the LED control registers&n; * The original Mips machines seem to have a LED display&n; * with integrated decoder while the Acer machines can&n; * control each of the seven segments and the dot independend.&n; * It only a toy, anyway...&n; */
DECL|macro|LED_DOT
mdefine_line|#define LED_DOT                 0x01
DECL|macro|LED_SPACE
mdefine_line|#define LED_SPACE               0x00
DECL|macro|LED_0
mdefine_line|#define LED_0                   0xfc
DECL|macro|LED_1
mdefine_line|#define LED_1                   0x60
DECL|macro|LED_2
mdefine_line|#define LED_2                   0xda
DECL|macro|LED_3
mdefine_line|#define LED_3                   0xf2
DECL|macro|LED_4
mdefine_line|#define LED_4                   0x66
DECL|macro|LED_5
mdefine_line|#define LED_5                   0xb6
DECL|macro|LED_6
mdefine_line|#define LED_6                   0xbe
DECL|macro|LED_7
mdefine_line|#define LED_7                   0xe0
DECL|macro|LED_8
mdefine_line|#define LED_8                   0xfe
DECL|macro|LED_9
mdefine_line|#define LED_9                   0xf6
DECL|macro|LED_A
mdefine_line|#define LED_A                   0xee
DECL|macro|LED_b
mdefine_line|#define LED_b                   0x3e
DECL|macro|LED_C
mdefine_line|#define LED_C                   0x9c
DECL|macro|LED_d
mdefine_line|#define LED_d                   0x7a
DECL|macro|LED_E
mdefine_line|#define LED_E                   0x9e
DECL|macro|LED_F
mdefine_line|#define LED_F                   0x8e
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
DECL|function|pica_set_led
r_extern
id|__inline__
r_void
id|pica_set_led
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
r_volatile
r_int
r_int
op_star
id|led_register
op_assign
(paren
r_int
r_int
op_star
)paren
id|PICA_LED
suffix:semicolon
op_star
id|led_register
op_assign
id|bits
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * i8042 keyboard controller for PICA chipset.&n; * This address is just a guess and seems to differ&n; * from the other mips machines...&n; */
DECL|macro|PICA_KEYBOARD_ADDRESS
mdefine_line|#define PICA_KEYBOARD_ADDRESS   0xe0005000
DECL|macro|PICA_KEYBOARD_DATA
mdefine_line|#define PICA_KEYBOARD_DATA      0xe0005000
DECL|macro|PICA_KEYBOARD_COMMAND
mdefine_line|#define PICA_KEYBOARD_COMMAND   0xe0005001
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|pica_keyboard_hardware
)brace
id|pica_keyboard_hardware
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|mips_keyboard_hardware
)brace
id|mips_keyboard_hardware
suffix:semicolon
multiline_comment|/*&n; * For now&n; */
DECL|macro|keyboard_hardware
mdefine_line|#define keyboard_hardware       pica_keyboard_hardware
macro_line|#endif
multiline_comment|/*&n; * i8042 keyboard controller for most other Mips machines.&n; */
DECL|macro|MIPS_KEYBOARD_ADDRESS
mdefine_line|#define MIPS_KEYBOARD_ADDRESS   0xb9005000
DECL|macro|MIPS_KEYBOARD_DATA
mdefine_line|#define MIPS_KEYBOARD_DATA      0xb9005003
DECL|macro|MIPS_KEYBOARD_COMMAND
mdefine_line|#define MIPS_KEYBOARD_COMMAND   0xb9005007
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
macro_line|#endif
multiline_comment|/*&n; * PICA timer registers and interrupt no.&n; * Note that the hardware timer interrupt is actually on&n; * cpu level 6, but to keep compatibility with PC stuff&n; * it is remapped to vector 0. See arch/mips/kernel/entry.S.&n; */
DECL|macro|PICA_TIMER_INTERVAL
mdefine_line|#define PICA_TIMER_INTERVAL     0xe0000228
DECL|macro|PICA_TIMER_REGISTER
mdefine_line|#define PICA_TIMER_REGISTER     0xe0000230
multiline_comment|/*&n; * DRAM configuration register&n; */
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
macro_line|#ifdef __MIPSEL__
r_typedef
r_struct
(brace
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#else /* defined (__MIPSEB__) */
r_typedef
r_struct
(brace
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
DECL|macro|PICA_DRAM_CONFIG
mdefine_line|#define PICA_DRAM_CONFIG        0xe00fffe0
multiline_comment|/*&n; * PICA interrupt control registers&n; */
DECL|macro|PICA_IO_IRQ_SOURCE
mdefine_line|#define PICA_IO_IRQ_SOURCE      0xe0100000
DECL|macro|PICA_IO_IRQ_ENABLE
mdefine_line|#define PICA_IO_IRQ_ENABLE      0xe0100002
multiline_comment|/*&n; * Pica interrupt enable bits&n; */
DECL|macro|PIE_PARALLEL
mdefine_line|#define PIE_PARALLEL            (1&lt;&lt;0)
DECL|macro|PIE_FLOPPY
mdefine_line|#define PIE_FLOPPY              (1&lt;&lt;1)
DECL|macro|PIE_SOUND
mdefine_line|#define PIE_SOUND               (1&lt;&lt;2)
DECL|macro|PIE_VIDEO
mdefine_line|#define PIE_VIDEO               (1&lt;&lt;3)
DECL|macro|PIE_ETHERNET
mdefine_line|#define PIE_ETHERNET            (1&lt;&lt;4)
DECL|macro|PIE_SCSI
mdefine_line|#define PIE_SCSI                (1&lt;&lt;5)
DECL|macro|PIE_KEYBOARD
mdefine_line|#define PIE_KEYBOARD            (1&lt;&lt;6)
DECL|macro|PIE_MOUSE
mdefine_line|#define PIE_MOUSE               (1&lt;&lt;7)
DECL|macro|PIE_SERIAL1
mdefine_line|#define PIE_SERIAL1             (1&lt;&lt;8)
DECL|macro|PIE_SERIAL2
mdefine_line|#define PIE_SERIAL2             (1&lt;&lt;9)
macro_line|#endif /* __ASM_MIPS_PICA_H */
eof
