multiline_comment|/*&n; *  linux/arch/mips/dec/process.c&n; *&n; *  Reset a DECstation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
DECL|function|dec_machine_restart
r_void
id|dec_machine_restart
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
l_string|&quot;Implement dec_machine_restart().&bslash;n&quot;
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
DECL|function|dec_machine_halt
r_void
id|dec_machine_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Implement dec_machine_halt().&bslash;n&quot;
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
DECL|function|dec_machine_power_off
r_void
id|dec_machine_power_off
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
