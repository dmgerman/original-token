macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
multiline_comment|/*&n; * Semaphores are recursive: we allow the holder process&n; * to recursively do down() operations on a semaphore that&n; * the process already owns. In order to do that, we need&n; * to keep a semaphore-local copy of the owner and the&n; * &quot;depth of ownership&quot;.&n; *&n; * NOTE! Nasty memory ordering rules:&n; *  - &quot;owner&quot; and &quot;owner_count&quot; may only be modified once you hold the&n; *    lock. &n; *  - &quot;owner_count&quot; must be written _after_ modifying owner, and&n; *    must be read _before_ reading owner. There must be appropriate&n; *    write and read barriers to enforce this.&n; *&n; * On an x86, writes are always ordered, so the only enformcement&n; * necessary is to make sure that the owner_depth is written after&n; * the owner value in program order.&n; *&n; * For read ordering guarantees, the semaphore wake_lock spinlock&n; * is already giving us ordering guarantees.&n; *&n; * Other (saner) architectures would use &quot;wmb()&quot; and &quot;rmb()&quot; to&n; * do this in a more obvious manner.&n; */
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
multiline_comment|/*&n; * Because we want the non-contention case to be&n; * fast, we save the stack pointer into the &quot;owner&quot;&n; * field, and to get the true task pointer we have&n; * to do the bit masking. That moves the masking&n; * operation into the slow path.&n; */
DECL|macro|semaphore_owner
mdefine_line|#define semaphore_owner(sem) &bslash;&n;&t;((struct task_struct *)((2*PAGE_MASK) &amp; (sem)-&gt;owner))
DECL|macro|MUTEX
mdefine_line|#define MUTEX ((struct semaphore) { ATOMIC_INIT(1), 0, 0, 0, NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { ATOMIC_INIT(0), 0, 1, 0, NULL })
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
multiline_comment|/*&n; * NOTE NOTE NOTE!&n; *&n; * We read owner-count _before_ getting the semaphore. This&n; * is important, because the semaphore also acts as a memory&n; * ordering point between reading owner_depth and reading&n; * the owner.&n; *&n; * Why is this necessary? The &quot;owner_depth&quot; essentially protects&n; * us from using stale owner information - in the case that this&n; * process was the previous owner but somebody else is racing to&n; * aquire the semaphore, the only way we can see ourselves as an&n; * owner is with &quot;owner_depth&quot; of zero (so that we know to avoid&n; * the stale value).&n; *&n; * In the non-race case (where we really _are_ the owner), there&n; * is not going to be any question about what owner_depth is.&n; *&n; * In the race case, the race winner will not even get here, because&n; * it will have successfully gotten the semaphore with the locked&n; * decrement operation.&n; *&n; * Basically, we have two values, and we cannot guarantee that either&n; * is really up-to-date until we have aquired the semaphore. But we&n; * _can_ depend on a ordering between the two values, so we can use&n; * one of them to determine whether we can trust the other:&n; *&n; * Cases:&n; *  - owner_depth == zero: ignore the semaphore owner, because it&n; *    cannot possibly be us. Somebody else may be in the process&n; *    of modifying it and the zero may be &quot;stale&quot;, but it sure isn&squot;t&n; *    going to say that &quot;we&quot; are the owner anyway, so who cares?&n; *  - owner_depth is non-zero. That means that even if somebody&n; *    else wrote the non-zero count value, the write ordering requriement&n; *    means that they will have written themselves as the owner, so&n; *    if we now see ourselves as an owner we can trust it to be true.&n; */
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
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|owner_depth
op_assign
id|sem-&gt;owner_depth
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
multiline_comment|/* Don&squot;t use the possibly stale value */
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
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;movl %%esp,4(%0)&bslash;n&quot;
l_string|&quot;movl $1,8(%0)&bslash;n&bslash;t&quot;
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
l_string|&quot;movl %%esp,4(%1)&bslash;n&bslash;t&quot;
l_string|&quot;movl $1,8(%1)&bslash;n&bslash;t&quot;
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
l_string|&quot;decl 8(%0)&bslash;n&bslash;t&quot;
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
