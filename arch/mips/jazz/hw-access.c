multiline_comment|/* $Id: hw-access.c,v 1.11 1998/09/16 22:50:39 ralf Exp $&n; *&n; * Low-level hardware access stuff for Jazz family machines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998 by Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|jazz_kh
r_static
r_volatile
id|keyboard_hardware
op_star
id|jazz_kh
op_assign
(paren
id|keyboard_hardware
op_star
)paren
id|JAZZ_KEYBOARD_ADDRESS
suffix:semicolon
DECL|macro|KBD_STAT_IBF
mdefine_line|#define KBD_STAT_IBF&t;&t;0x02&t;/* Keyboard input buffer full */
DECL|function|jazz_read_input
r_static
r_int
r_char
id|jazz_read_input
c_func
(paren
r_void
)paren
(brace
r_return
id|jazz_kh-&gt;data
suffix:semicolon
)brace
DECL|function|jazz_write_output
r_static
r_void
id|jazz_write_output
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
r_do
(brace
id|status
op_assign
id|jazz_kh-&gt;command
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|KBD_STAT_IBF
)paren
suffix:semicolon
id|jazz_kh-&gt;data
op_assign
id|val
suffix:semicolon
)brace
DECL|function|jazz_write_command
r_static
r_void
id|jazz_write_command
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
r_do
(brace
id|status
op_assign
id|jazz_kh-&gt;command
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|KBD_STAT_IBF
)paren
suffix:semicolon
id|jazz_kh-&gt;command
op_assign
id|val
suffix:semicolon
)brace
DECL|function|jazz_read_status
r_static
r_int
r_char
id|jazz_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|jazz_kh-&gt;command
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|jazz_keyboard_setup
c_func
(paren
r_void
)paren
)paren
(brace
id|kbd_read_input
op_assign
id|jazz_read_input
suffix:semicolon
id|kbd_write_output
op_assign
id|jazz_write_output
suffix:semicolon
id|kbd_write_command
op_assign
id|jazz_write_command
suffix:semicolon
id|kbd_read_status
op_assign
id|jazz_read_status
suffix:semicolon
id|request_irq
c_func
(paren
id|JAZZ_KEYBOARD_IRQ
comma
id|keyboard_interrupt
comma
l_int|0
comma
l_string|&quot;keyboard&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x60
comma
l_int|16
comma
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
id|r4030_write_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
comma
id|r4030_read_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
)paren
op_or
id|JAZZ_IE_KEYBOARD
)paren
suffix:semicolon
)brace
DECL|function|jazz_ps2_request_irq
r_int
id|jazz_ps2_request_irq
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|aux_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|JAZZ_MOUSE_IRQ
comma
id|aux_interrupt
comma
l_int|0
comma
l_string|&quot;PS/2 Mouse&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|r4030_write_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
comma
id|r4030_read_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
)paren
op_or
id|JAZZ_IE_MOUSE
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jazz_ps2_free_irq
r_void
id|jazz_ps2_free_irq
c_func
(paren
r_void
)paren
(brace
id|r4030_write_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
comma
id|r4030_read_reg16
c_func
(paren
id|JAZZ_IO_IRQ_ENABLE
)paren
op_or
id|JAZZ_IE_MOUSE
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|JAZZ_MOUSE_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
