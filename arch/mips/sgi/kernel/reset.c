multiline_comment|/*&n; *  Reset a SGI.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998 by Ralf Baechle&n; *&n; * $Id: reset.c,v 1.3 1998/05/01 01:35:18 ralf Exp $&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
multiline_comment|/* XXX How to pass the reboot command to the firmware??? */
DECL|function|sgi_machine_restart
r_void
id|sgi_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|prom_reboot
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sgi_machine_halt
r_void
id|sgi_machine_halt
c_func
(paren
r_void
)paren
(brace
id|prom_imode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sgi_machine_power_off
r_void
id|sgi_machine_power_off
c_func
(paren
r_void
)paren
(brace
id|prom_powerdown
c_func
(paren
)paren
suffix:semicolon
)brace
eof
