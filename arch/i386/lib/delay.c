multiline_comment|/*&n; *&t;Precise Delay Loops for i386&n; *&n; *&t;Copyright (C) 1993 Linus Torvalds&n; *&t;Copyright (C) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; *&n; *&t;The __delay function must _NOT_ be inlined as its execution time&n; *&t;depends wildly on alignment on many x86 processors.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#ifdef __SMP__
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
macro_line|#ifdef __SMP__
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val cpu_data[smp_processor_id()].udelay_val
macro_line|#else
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val loops_per_sec
macro_line|#endif
DECL|function|__delay
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
l_string|&quot;1:&bslash;tdecl %0&bslash;n&bslash;tjns 1b&quot;
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
id|__asm__
c_func
(paren
l_string|&quot;mull %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|xloops
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|xloops
)paren
comma
l_string|&quot;0&quot;
(paren
id|__udelay_val
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|xloops
)paren
suffix:semicolon
)brace
DECL|function|__udelay
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
eof
