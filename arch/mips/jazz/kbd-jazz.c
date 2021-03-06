multiline_comment|/* $Id: kbd-jazz.c,v 1.1 1998/10/28 12:38:10 ralf Exp $&n; *&n; * Low-level hardware access stuff for Jazz family machines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998 by Ralf Baechle&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
DECL|macro|jazz_kh
mdefine_line|#define jazz_kh ((keyboard_hardware *) JAZZ_KEYBOARD_ADDRESS)
DECL|function|jazz_request_region
r_static
r_void
id|jazz_request_region
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* No I/O ports are being used on Jazz.  */
)brace
DECL|function|jazz_request_irq
r_static
r_int
id|jazz_request_irq
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
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
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
id|request_irq
c_func
(paren
id|JAZZ_KEYBOARD_IRQ
comma
id|handler
comma
l_int|0
comma
l_string|&quot;keyboard&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|0
)paren
r_return
id|res
suffix:semicolon
multiline_comment|/* jazz_request_irq() should do this ...  */
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jazz_aux_request_irq
r_static
r_int
id|jazz_aux_request_irq
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
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
)paren
(brace
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
id|handler
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
id|ret
op_ne
l_int|0
)paren
r_return
id|ret
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
id|JAZZ_IE_MOUSE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jazz_aux_free_irq
r_static
r_void
id|jazz_aux_free_irq
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
DECL|variable|jazz_kbd_ops
r_struct
id|kbd_ops
id|jazz_kbd_ops
op_assign
(brace
id|jazz_request_region
comma
id|jazz_request_irq
comma
id|jazz_aux_request_irq
comma
id|jazz_aux_free_irq
comma
id|jazz_read_input
comma
id|jazz_write_output
comma
id|jazz_write_command
comma
id|jazz_read_status
)brace
suffix:semicolon
eof
