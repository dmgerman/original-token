macro_line|#ifndef __ALPHA_DELAY_H
DECL|macro|__ALPHA_DELAY_H
mdefine_line|#define __ALPHA_DELAY_H
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * Copyright (C) 1993, 2000 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
multiline_comment|/*&n; * Use only for very small delays (&lt; 1 msec). &n; *&n; * The active part of our cycle counter is only 32-bits wide, and&n; * we&squot;re treating the difference between two marks as signed.  On&n; * a 1GHz box, that&squot;s about 2 seconds.&n; */
r_extern
id|__inline__
r_void
DECL|function|__delay
id|__delay
c_func
(paren
r_int
id|loops
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rpcc %0&bslash;n&quot;
l_string|&quot;&t;addl %1,%0,%1&bslash;n&quot;
l_string|&quot;1:&t;rpcc %0&bslash;n&quot;
l_string|&quot;&t;subl %1,%0,%0&bslash;n&quot;
l_string|&quot;&t;bgt %0,1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|udelay
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
r_int
r_int
id|lps
suffix:semicolon
macro_line|#ifdef __SMP__
id|lps
op_assign
id|cpu_data
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|loops_per_sec
suffix:semicolon
macro_line|#else
id|lps
op_assign
id|loops_per_sec
suffix:semicolon
macro_line|#endif
multiline_comment|/* Compute (usecs * 2**32 / 10**6) * loops_per_sec / 2**32.  */
id|usecs
op_mul_assign
l_int|0x10c6
suffix:semicolon
multiline_comment|/* 2^32 / 10^6 */
id|usecs
op_mul_assign
id|lps
suffix:semicolon
id|__delay
c_func
(paren
(paren
r_int
)paren
id|usecs
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(__ALPHA_DELAY_H) */
eof
