macro_line|#ifndef __SPARC_DELAY_H
DECL|macro|__SPARC_DELAY_H
mdefine_line|#define __SPARC_DELAY_H
r_extern
r_int
r_int
id|loops_per_sec
suffix:semicolon
multiline_comment|/*&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu).&n; *&n; * Delay quick inlined code using &squot;loops_per_second&squot; which is&n; * calculated in calibrate_delay() in main.c (ie. BogoMIPS :-)&n; */
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
l_string|&quot;&bslash;n1:&bslash;tcmp %0, 0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;sub %0, 1, %0&bslash;n&quot;
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
multiline_comment|/* udelay(usecs) is used for very short delays up to 1 millisecond. */
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
multiline_comment|/* Sparc is 32-bit just like ix86 */
id|__asm__
c_func
(paren
l_string|&quot;sethi %hi(_loops_per_sec), %o1&bslash;n&bslash;t&quot;
l_string|&quot;ld [%o1 + %lo(_loops_per_sec)], %o1&bslash;n&bslash;t&quot;
l_string|&quot;call ___delay&bslash;n&bslash;t&quot;
l_string|&quot;umul %o1, %o0, %o0&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(__SPARC_DELAY_H) */
eof
