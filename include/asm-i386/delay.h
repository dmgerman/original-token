macro_line|#ifndef _I386_DELAY_H
DECL|macro|_I386_DELAY_H
mdefine_line|#define _I386_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines calling functions in arch/i386/lib/delay.c&n; */
r_extern
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
suffix:semicolon
DECL|macro|udelay
mdefine_line|#define udelay(n) (__builtin_constant_p(n) ? &bslash;&n;&t;__const_udelay((n) * 0x10c6) : &bslash;&n;&t;__udelay(n))
macro_line|#endif /* defined(_I386_DELAY_H) */
eof
