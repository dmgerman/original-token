macro_line|#ifndef __ALPHA_DELAY_H
DECL|macro|__ALPHA_DELAY_H
mdefine_line|#define __ALPHA_DELAY_H
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
multiline_comment|/* We can make the delay loop inline, but we have to be very careful wrt&n;   scheduling for ev6 machines, so that we keep a consistent number of&n;   iterations for all invocations.  */
r_extern
id|__inline__
r_void
DECL|function|__delay
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;1:&t;subq %0,1,%0&bslash;n&quot;
l_string|&quot;&t;bge %0,1b&bslash;n&quot;
l_string|&quot;&t;nop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant).&n; *&n; * Optimize small constants further by exposing the second multiplication&n; * to the compiler.  In addition, mulq is 2 cycles faster than umulh.&n; */
r_extern
id|__inline__
r_void
DECL|function|__udelay
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
multiline_comment|/* compute (usecs * 2**64 / 10**6) * loops_per_sec / 2**64 */
id|usecs
op_mul_assign
l_int|0x000010c6f7a0b5edUL
suffix:semicolon
multiline_comment|/* 2**64 / 1000000 */
id|__asm__
c_func
(paren
l_string|&quot;umulh %1,%2,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|usecs
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;r&quot;
(paren
id|lps
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|__small_const_udelay
id|__small_const_udelay
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
multiline_comment|/* compute (usecs * 2**32 / 10**6) * loops_per_sec / 2**32 */
id|usecs
op_mul_assign
l_int|0x10c6
suffix:semicolon
multiline_comment|/* 2^32 / 10^6 */
id|usecs
op_mul_assign
id|lps
suffix:semicolon
id|usecs
op_rshift_assign
l_int|32
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
macro_line|#ifdef __SMP__
DECL|macro|udelay
mdefine_line|#define udelay(usecs)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(usecs) &amp;&amp; usecs &lt; 0x100000000UL&t;&bslash;&n;&t; ? __small_const_udelay(usecs,&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_data[smp_processor_id()].loops_per_sec)&t;&bslash;&n;&t; : __udelay(usecs,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_data[smp_processor_id()].loops_per_sec))
macro_line|#else
DECL|macro|udelay
mdefine_line|#define udelay(usecs)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(usecs) &amp;&amp; usecs &lt; 0x100000000UL&t;&bslash;&n;&t; ? __small_const_udelay(usecs, loops_per_sec)&t;&t;&bslash;&n;&t; : __udelay(usecs, loops_per_sec))
macro_line|#endif
macro_line|#endif /* defined(__ALPHA_DELAY_H) */
eof
