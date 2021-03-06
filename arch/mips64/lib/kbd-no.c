multiline_comment|/* $Id: kbd-no.c,v 1.1 1999/08/21 21:43:00 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Stub keyboard and psaux routines to keep Linux from crashing on machines&n; * without a keyboard.&n; *&n; * Copyright (C) 1998 by Ralf Baechle&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
DECL|function|no_kbd_request_region
r_static
r_void
id|no_kbd_request_region
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* No I/O ports are being used on the Indy.  */
)brace
DECL|function|no_kbd_request_irq
r_static
r_int
id|no_kbd_request_irq
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
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|no_aux_request_irq
r_static
r_int
id|no_aux_request_irq
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
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|no_aux_free_irq
r_static
r_void
id|no_aux_free_irq
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|no_kbd_read_input
r_static
r_int
r_char
id|no_kbd_read_input
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|no_kbd_write_output
r_static
r_void
id|no_kbd_write_output
c_func
(paren
r_int
r_char
id|val
)paren
(brace
)brace
DECL|function|no_kbd_write_command
r_static
r_void
id|no_kbd_write_command
c_func
(paren
r_int
r_char
id|val
)paren
(brace
)brace
DECL|function|no_kbd_read_status
r_static
r_int
r_char
id|no_kbd_read_status
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|no_kbd_ops
r_struct
id|kbd_ops
id|no_kbd_ops
op_assign
(brace
id|no_kbd_request_region
comma
id|no_kbd_request_irq
comma
id|no_aux_request_irq
comma
id|no_aux_free_irq
comma
id|no_kbd_read_input
comma
id|no_kbd_write_output
comma
id|no_kbd_write_command
comma
id|no_kbd_read_status
)brace
suffix:semicolon
eof
