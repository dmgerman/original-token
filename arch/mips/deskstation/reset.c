multiline_comment|/*&n; * linux/arch/mips/deskstation/process.c&n; *&n; * Reset a Deskstation.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|function|deskstation_machine_restart
r_void
id|deskstation_machine_restart
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Implement deskstation_machine_restart().&bslash;n&quot;
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
DECL|function|deskstation_machine_halt
r_void
id|deskstation_machine_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Implement deskstation_machine_halt().&bslash;n&quot;
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
DECL|function|deskstation_machine_power_off
r_void
id|deskstation_machine_power_off
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Implement dec_machine_power_off().&bslash;n&quot;
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
eof
