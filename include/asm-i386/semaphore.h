macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|waking
r_int
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
mdefine_line|#define MUTEX ((struct semaphore) { ATOMIC_INIT(1), 0, NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { ATOMIC_INIT(0), 0, NULL })
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
r_extern
id|spinlock_t
id|semaphore_wake_lock
suffix:semicolon
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), (val))
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; *&n; * This is trivially done with load_locked/store_cond,&n; * but on the x86 we need an external synchronizer.&n; */
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
id|sem-&gt;waking
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
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
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;waking
OG
l_int|0
)paren
(brace
id|sem-&gt;waking
op_decrement
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_wake_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
l_string|&quot;# atomic down operation&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;decl 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tpushl $1b&bslash;n&bslash;t&quot;
l_string|&quot;jmp __down_failed&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
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
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;decl 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tpushl $1b&bslash;n&bslash;t&quot;
l_string|&quot;jmp __down_failed_interruptible&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic up operation&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;incl 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;jle 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tpushl $1b&bslash;n&bslash;t&quot;
l_string|&quot;jmp __up_wakeup&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
