multiline_comment|/*&n; *&t;Precise Delay Loops for SuperH&n; *&n; *&t;Copyright (C) 1999 Niibe Yutaka&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|function|__const_udelay
r_inline
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|xloops
)paren
(brace
id|xloops
op_mul_assign
id|current_cpu_data.loops_per_sec
suffix:semicolon
id|__delay
c_func
(paren
id|xloops
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
id|__const_udelay
c_func
(paren
id|usecs
op_star
l_int|0x000010c6
)paren
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
)brace
macro_line|#endif
eof
