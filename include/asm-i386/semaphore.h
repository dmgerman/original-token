macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; */
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
id|down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|up_wakeup
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
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;down_failed&quot; is a special asm handler that calls the C&n; * routine that actually waits. See arch/i386/lib/semaphore.S&n; */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic down operation&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;movl $1b,%%eax&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;decl %0&bslash;n&bslash;t&quot;
l_string|&quot;js &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|down_failed
)paren
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;dx&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic up operation&bslash;n&bslash;t&quot;
l_string|&quot;movl $1f,%%eax&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;incl %0&bslash;n&bslash;t&quot;
l_string|&quot;jle &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|up_wakeup
)paren
l_string|&quot;&bslash;n1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
comma
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
