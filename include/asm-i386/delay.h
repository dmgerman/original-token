macro_line|#ifndef _I386_DELAY_H
DECL|macro|_I386_DELAY_H
mdefine_line|#define _I386_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
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
c_func
(paren
l_string|&quot;.align 2,0x90&bslash;n1:&bslash;tdecl %0&bslash;n&bslash;tjns 1b&quot;
suffix:colon
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
id|loops_per_sec
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
macro_line|#endif /* defined(_I386_DELAY_H) */
eof
