multiline_comment|/*&n; *  linux/arch/mips/sgi/kernel/process.c&n; *&n; *  Reset a SGI.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|prom_imode
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|sgi_machine_halt
r_void
id|sgi_machine_halt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|sgi_machine_power_off
r_void
id|sgi_machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
eof
