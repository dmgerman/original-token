macro_line|#ifndef __ALPHA_DELAY_H
DECL|macro|__ALPHA_DELAY_H
mdefine_line|#define __ALPHA_DELAY_H
r_extern
r_int
r_int
id|loops_per_sec
suffix:semicolon
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
DECL|function|__delay
r_extern
id|__inline__
r_void
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
l_string|&quot;.align 3&bslash;n&quot;
l_string|&quot;1:&bslash;tsubq %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bge %0,1b&quot;
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
macro_line|#endif /* defined(__ALPHA_DELAY_H) */
eof
