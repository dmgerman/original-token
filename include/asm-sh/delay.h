macro_line|#ifndef __ASM_SH_DELAY_H
DECL|macro|__ASM_SH_DELAY_H
mdefine_line|#define __ASM_SH_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1999  Kaz Kojima&n; */
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
l_string|&quot;tst&t;%0,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;bf/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; dt&t;%0&quot;
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
l_string|&quot;dmulu.l&t;%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;sts&t;mach,%0&quot;
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
id|lps
)paren
suffix:colon
l_string|&quot;macl&quot;
comma
l_string|&quot;mach&quot;
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
macro_line|#endif /* __ASM_SH_DELAY_H */
eof
