multiline_comment|/*&n; *  linux/arch/mips/jazz/process.c&n; *&n; *  Reset a Jazz machine.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
DECL|function|jazz_machine_restart
r_void
id|jazz_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Implement jazz_machine_restart().&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Press reset to continue.&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|jazz_machine_halt
r_void
id|jazz_machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|jazz_machine_power_off
r_void
id|jazz_machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Jazz machines don&squot;t have a software power switch */
)brace
eof
