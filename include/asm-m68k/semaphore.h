macro_line|#ifndef _M68K_SEMAPHORE_H
DECL|macro|_M68K_SEMAPHORE_H
mdefine_line|#define _M68K_SEMAPHORE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * m68k version by Andreas Schwab&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|owner
DECL|member|owner_depth
r_int
r_int
id|owner
comma
id|owner_depth
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
multiline_comment|/*&n; * Because we want the non-contention case to be&n; * fast, we save the stack pointer into the &quot;owner&quot;&n; * field, and to get the true task pointer we have&n; * to do the bit masking. That moves the masking&n; * operation into the slow path.&n; */
DECL|macro|semaphore_owner
mdefine_line|#define semaphore_owner(sem) &bslash;&n;&t;((struct task_struct *)((2*PAGE_MASK) &amp; (sem)-&gt;owner))
DECL|macro|MUTEX
mdefine_line|#define MUTEX ((struct semaphore) { ATOMIC_INIT(1), 0, 0, ATOMIC_INIT(0), NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { ATOMIC_INIT(0), 0, 1, ATOMIC_INIT(0), NULL })
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
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), val)
DECL|function|wake_one_more
r_static
r_inline
r_void
id|wake_one_more
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
)brace
DECL|function|waking_non_zero
r_static
r_inline
r_int
id|waking_non_zero
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
macro_line|#ifndef CONFIG_RMW_INSNS
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
OG
l_int|0
op_logical_or
(paren
id|owner_depth
op_logical_and
id|semaphore_owner
c_func
(paren
id|sem
)paren
op_eq
id|tsk
)paren
)paren
(brace
id|sem-&gt;owner
op_assign
(paren
r_int
r_int
)paren
id|tsk
suffix:semicolon
id|sem-&gt;owner_depth
op_increment
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#else
r_int
id|ret
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&t;movel&t;%2,%0&bslash;n&quot;
l_string|&quot;    jeq&t;3f&bslash;n&quot;
l_string|&quot;2:&t;movel&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;subql&t;#1,%1&bslash;n&quot;
l_string|&quot;&t;casl&t;%0,%1,%2&bslash;n&quot;
l_string|&quot;&t;jeq&t;3f&bslash;n&quot;
l_string|&quot;&t;tstl&t;%0&bslash;n&quot;
l_string|&quot;&t;jne&t;2b&bslash;n&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;waking
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
(paren
(paren
id|sem-&gt;owner_depth
op_ne
l_int|0
)paren
op_logical_and
(paren
id|semaphore_owner
c_func
(paren
id|sem
)paren
op_eq
id|tsk
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|sem-&gt;owner
op_assign
(paren
r_int
r_int
)paren
id|tsk
suffix:semicolon
id|sem-&gt;owner_depth
op_increment
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
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
l_string|&quot;movel %%sp,4(%0)&bslash;n&quot;
l_string|&quot;movel #1,8(%0)&bslash;n&bslash;t&quot;
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
l_string|&quot;movel %%sp,4(%1)&bslash;n&quot;
l_string|&quot;moveql #1,%0&bslash;n&quot;
l_string|&quot;movel %0,8(%1)&bslash;n&quot;
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
l_string|&quot;subql #1,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;addql #1,%0@&bslash;n&bslash;t&quot;
l_string|&quot;jle 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;tpea 1b&bslash;n&bslash;t&quot;
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
