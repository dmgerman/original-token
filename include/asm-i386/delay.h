macro_line|#ifndef _I386_DELAY_H
DECL|macro|_I386_DELAY_H
mdefine_line|#define _I386_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
macro_line|#ifdef __SMP__
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif 
DECL|function|__delay
r_extern
id|__inline__
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.align 2,0x90&bslash;n1:&bslash;tdecl %0&bslash;n&bslash;tjns 1b&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
DECL|function|__udelay
r_extern
id|__inline__
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
comma
r_int
r_int
id|lps
)paren
(brace
id|usecs
op_mul_assign
l_int|0x000010c6
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
id|__asm__
c_func
(paren
l_string|&quot;mull %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|usecs
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;0&quot;
(paren
id|lps
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
macro_line|#ifdef __SMP__
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val cpu_data[smp_processor_id()].udelay_val
macro_line|#else
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val loops_per_sec
macro_line|#endif
DECL|macro|udelay
mdefine_line|#define udelay(usecs) __udelay((usecs),__udelay_val)
DECL|function|muldiv
r_extern
id|__inline__
r_int
r_int
id|muldiv
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
comma
r_int
r_int
id|c
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;mull %1 ; divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|c
)paren
comma
l_string|&quot;0&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;dx&quot;
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
macro_line|#endif /* defined(_I386_DELAY_H) */
eof
