macro_line|#ifndef __ASM_MIPS_DELAY_H
DECL|macro|__ASM_MIPS_DELAY_H
mdefine_line|#define __ASM_MIPS_DELAY_H
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
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tbne&bslash;t$0,%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
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
multiline_comment|/*&n; * division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
DECL|function|udelay
r_extern
id|__inline__
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
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
l_string|&quot;multu&bslash;t%0,%1&bslash;n&bslash;t&quot;
l_string|&quot;mfhi&bslash;t%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|usecs
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;r&quot;
(paren
id|loops_per_sec
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
multiline_comment|/*&n; * The different variants for 32/64 bit are pure paranoia. The typical&n; * range of numbers that apprears for MIPS machines avoids overflows.&n; */
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
r_return
(paren
id|a
op_star
id|b
)paren
op_div
id|c
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MIPS_DELAY_H */
eof
