macro_line|#ifndef _M68K_SEMAPHORE_H
DECL|macro|_M68K_SEMAPHORE_H
mdefine_line|#define _M68K_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * m68k version by Andreas Schwab&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|waking
id|atomic_t
id|waking
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
mdefine_line|#define MUTEX ((struct semaphore) { ATOMIC_INIT(1), ATOMIC_INIT(0), NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { ATOMIC_INIT(0), ATOMIC_INIT(0), NULL })
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
r_int
id|__down_failed_interruptible
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_trylock
c_func
(paren
r_void
multiline_comment|/* params in registers */
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
id|asmlinkage
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
id|asmlinkage
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
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
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), val)
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
l_string|&quot;subql #1,%0@&bslash;n&bslash;t&quot;
l_string|&quot;jmi 2f&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;tpea 1b&bslash;n&bslash;t&quot;
l_string|&quot;jbra __down_failed&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|down_interruptible
r_extern
r_inline
r_int
id|down_interruptible
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
r_register
r_int
id|result
id|__asm__
(paren
l_string|&quot;%d0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic interruptible down operation&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1@&bslash;n&bslash;t&quot;
l_string|&quot;jmi 2f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;tpea 1b&bslash;n&bslash;t&quot;
l_string|&quot;jbra __down_failed_interruptible&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;%d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|down_trylock
r_extern
r_inline
r_int
id|down_trylock
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
r_register
r_int
id|result
id|__asm__
(paren
l_string|&quot;%d0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic down trylock operation&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1@&bslash;n&bslash;t&quot;
l_string|&quot;jmi 2f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;tpea 1b&bslash;n&bslash;t&quot;
l_string|&quot;jbra __down_failed_trylock&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;%d0&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
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
l_string|&quot;addql #1,%0@&bslash;n&bslash;t&quot;
l_string|&quot;jle 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;t&quot;
l_string|&quot;pea 1b&bslash;n&bslash;t&quot;
l_string|&quot;jbra __up_wakeup&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
