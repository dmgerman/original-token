multiline_comment|/*&n; *  include/asm-mips/bugs.h&n; *&n; *  Copyright (C) 1995  Waldorf Electronics&n; *  written by Ralf Baechle&n; */
macro_line|#include &lt;asm/bootinfo.h&gt;
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
DECL|function|check_wait
r_static
r_void
id|check_wait
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Checking for &squot;wait&squot; instruction... &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mips_cputype
)paren
(brace
r_case
id|CPU_R4200
suffix:colon
r_case
id|CPU_R4300
suffix:colon
r_case
id|CPU_R4600
suffix:colon
r_case
id|CPU_R5000
suffix:colon
id|wait_available
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; available.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot; unavailable.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|check_bugs
r_static
r_void
id|check_bugs
c_func
(paren
r_void
)paren
(brace
id|check_wait
c_func
(paren
)paren
suffix:semicolon
)brace
eof
