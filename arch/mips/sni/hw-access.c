multiline_comment|/* $Id: hw-access.c,v 1.8 1998/09/16 22:50:46 ralf Exp $&n; *&n; * Low-level hardware access stuff for SNI RM200 PCI&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998 by Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/kbdcntrlr.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
DECL|macro|KBD_STAT_IBF
mdefine_line|#define KBD_STAT_IBF&t;&t;0x02&t;/* Keyboard input buffer full */
DECL|function|sni_read_input
r_static
r_int
r_char
id|sni_read_input
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|sni_write_output
r_static
r_void
id|sni_write_output
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
id|inb
c_func
(paren
id|KBD_CNTL_REG
)paren
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
id|outb
c_func
(paren
id|val
comma
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|sni_write_command
r_static
r_void
id|sni_write_command
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
id|inb
c_func
(paren
id|KBD_CNTL_REG
)paren
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
id|outb
c_func
(paren
id|val
comma
id|KBD_CNTL_REG
)paren
suffix:semicolon
)brace
DECL|function|sni_read_status
r_static
r_int
r_char
id|sni_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_STATUS_REG
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|sni_rm200_keyboard_setup
c_func
(paren
r_void
)paren
)paren
(brace
id|kbd_read_input
op_assign
id|sni_read_input
suffix:semicolon
id|kbd_write_output
op_assign
id|sni_write_output
suffix:semicolon
id|kbd_write_command
op_assign
id|sni_write_command
suffix:semicolon
id|kbd_read_status
op_assign
id|sni_read_status
suffix:semicolon
id|request_irq
c_func
(paren
id|PCIMT_KEYBOARD_IRQ
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
)brace
eof
