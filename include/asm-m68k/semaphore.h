macro_line|#ifndef _M68K_SEMAPHORE_H
DECL|macro|_M68K_SEMAPHORE_H
mdefine_line|#define _M68K_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * m68k version by Andreas Schwab&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|waiting
r_int
id|waiting
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MUTEX
mdefine_line|#define MUTEX ((struct semaphore) { 1, 0, NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { 0, 0, NULL })
id|asmlinkage
r_void
id|__down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
r_extern
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;down_failed&quot; is a special asm handler that calls the C&n; * routine that actually waits. See arch/m68k/lib/semaphore.S&n; */
DECL|function|down
r_extern
r_inline
r_void
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_register
r_struct
id|semaphore
op_star
id|sem1
id|__asm__
(paren
l_string|&quot;%a1&quot;
)paren
op_assign
id|sem
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic down operation&bslash;n&bslash;t&quot;
l_string|&quot;lea %%pc@(1f),%%a0&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jmi &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|__down_failed
)paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;%a0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
DECL|function|up
r_extern
r_inline
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_register
r_struct
id|semaphore
op_star
id|sem1
id|__asm__
(paren
l_string|&quot;%a1&quot;
)paren
op_assign
id|sem
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic up operation&bslash;n&bslash;t&quot;
l_string|&quot;lea %%pc@(1f),%%a0&bslash;n&bslash;t&quot;
l_string|&quot;addql #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jle &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|__up_wakeup
)paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;%a0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof