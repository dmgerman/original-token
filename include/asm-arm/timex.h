multiline_comment|/*&n; * linux/include/asm-arm/timex.h&n; *&n; * Architecture Specific TIME specifications&n; *&n; * Copyright (C) 1997,1998 Russell King&n; */
macro_line|#ifndef _ASMARM_TIMEX_H
DECL|macro|_ASMARM_TIMEX_H
mdefine_line|#define _ASMARM_TIMEX_H
macro_line|#include &lt;asm/arch/timex.h&gt;
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
