multiline_comment|/*&n; * linux/arch/arm/lib/system.c&n; *&n; * Copyright (C) 1999 Russell King&n; *&n; * Converted from ASM version 04/09/1999&n; */
macro_line|#include &lt;linux/kernel.h&gt;
DECL|function|abort
r_extern
r_void
m_abort
(paren
r_void
)paren
(brace
r_void
op_star
id|lr
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;kernel abort from %p!  (Please report to rmk@arm.linux.org.uk)&bslash;n&quot;
comma
id|lr
)paren
suffix:semicolon
multiline_comment|/* force an oops */
op_star
(paren
r_int
op_star
)paren
l_int|0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if that doesn&squot;t kill us, halt */
id|panic
c_func
(paren
l_string|&quot;Oops failed to kill thread&quot;
)paren
suffix:semicolon
)brace
eof
