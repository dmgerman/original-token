multiline_comment|/* $Id: ip27-reset.c,v 1.1 2000/01/17 23:32:47 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Reset an IP27.&n; *&n; * Copyright (C) 1997, 1998, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;asm/sgi/sgint23.h&gt;
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_void
id|machine_halt
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX How to pass the reboot command to the firmware??? */
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|ArcReboot
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* To do ...  */
)brace
DECL|function|ip27_reboot_setup
r_void
id|ip27_reboot_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do on IP27.  */
)brace
eof
