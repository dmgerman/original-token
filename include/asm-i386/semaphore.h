macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; * Modified 1999-02-14 by Andrea Arcangeli, split the sched.c helper&n; *&t;&t;       functions in asm/sempahore-helper.h while fixing a&n; *&t;&t;       potential and subtle race discovered by Ulrich Schmid&n; *&t;&t;       in down_interruptible(). Since I started to play here I&n; *&t;&t;       also implemented the `trylock&squot; semaphore operation.&n; *          1999-07-02 Artur Skawina &lt;skawina@geocities.com&gt;&n; *                     Optimized &quot;0(ecx)&quot; -&gt; &quot;(ecx)&quot; (the assembler does not&n; *                     do this). Changed calling sequences from push/jmp to&n; *                     traditional call/ret.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/rwlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|sleepers
r_int
id|sleepers
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name) &bslash;&n;&t;&t;, (int)&amp;(name).__magic
macro_line|#else
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name)
macro_line|#endif
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(count), 0, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count) &bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) __DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name) __DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|function|sema_init
r_extern
r_inline
r_void
id|sema_init
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_int
id|val
)paren
(brace
multiline_comment|/*&n; *&t;*sem = (struct semaphore)__SEMAPHORE_INITIALIZER((*sem),val);&n; *&n; * i&squot;d rather use the more flexible initialization above, but sadly&n; * GCC 2.7.2.3 emits a bogus warning. EGCS doesnt. Oh well.&n; */
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|val
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|sem-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
suffix:semicolon
macro_line|#endif
)brace
DECL|function|init_MUTEX
r_static
r_inline
r_void
id|init_MUTEX
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|init_MUTEX_LOCKED
r_static
r_inline
r_void
id|init_MUTEX_LOCKED
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
)brace
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
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl (%0)&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __down_failed&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
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
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl (%1)&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __down_failed_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
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
r_int
id|result
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl (%1)&bslash;n&bslash;t&quot;
multiline_comment|/* --sem-&gt;count */
l_string|&quot;js 2f&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __down_failed_trylock&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
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
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic up operation&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;incl (%0)&bslash;n&bslash;t&quot;
multiline_comment|/* ++sem-&gt;count */
l_string|&quot;jle 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __up_wakeup&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
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
multiline_comment|/* rw mutexes (should that be mutices? =) -- throw rw&n; * spinlocks and semaphores together, and this is what we&n; * end up with...&n; *&n; * The lock is initialized to BIAS.  This way, a writer&n; * subtracts BIAS ands gets 0 for the case of an uncontended&n; * lock.  Readers decrement by 1 and see a positive value&n; * when uncontended, negative if there are writers waiting&n; * (in which case it goes to sleep).&n; *&n; * The value 0x01000000 supports up to 128 processors and&n; * lots of processes.  BIAS must be chosen such that subl&squot;ing&n; * BIAS once per CPU will result in the long remaining&n; * negative.&n; *&n; * In terms of fairness, this should result in the lock&n; * flopping back and forth between readers and writers&n; * under heavy use.&n; *&n; *&t;&t;-ben&n; */
DECL|struct|rw_semaphore
r_struct
id|rw_semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|write_bias_granted
r_volatile
r_int
r_char
id|write_bias_granted
suffix:semicolon
DECL|member|read_bias_granted
r_volatile
r_int
r_char
id|read_bias_granted
suffix:semicolon
DECL|member|pad1
r_volatile
r_int
r_char
id|pad1
suffix:semicolon
DECL|member|pad2
r_volatile
r_int
r_char
id|pad2
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|write_bias_wait
id|wait_queue_head_t
id|write_bias_wait
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
DECL|member|readers
id|atomic_t
id|readers
suffix:semicolon
DECL|member|writers
id|atomic_t
id|writers
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT&t;, ATOMIC_INIT(0), ATOMIC_INIT(0)
macro_line|#else
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT&t;/* */
macro_line|#endif
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;{ ATOMIC_INIT(RW_LOCK_BIAS), 0, 0, 0, 0, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait), &bslash;&n;&t;__WAIT_QUEUE_HEAD_INITIALIZER((name).write_bias_wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) __RWSEM_DEBUG_INIT }
DECL|function|init_rwsem
r_extern
r_inline
r_void
id|init_rwsem
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|RW_LOCK_BIAS
)paren
suffix:semicolon
id|sem-&gt;read_bias_granted
op_assign
l_int|0
suffix:semicolon
id|sem-&gt;write_bias_granted
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;write_bias_wait
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|sem-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;readers
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;writers
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* we use FASTCALL convention for the helpers */
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
DECL|function|down_read
r_extern
r_inline
r_void
id|down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;__magic
op_ne
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__build_read_lock
c_func
(paren
id|sem
comma
l_string|&quot;__down_read_failed&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;write_bias_granted
)paren
id|BUG
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
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|down_write
r_extern
r_inline
r_void
id|down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;__magic
op_ne
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__build_write_lock
c_func
(paren
id|sem
comma
l_string|&quot;__down_write_failed&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
)paren
id|BUG
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
id|sem-&gt;readers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;read_bias_granted
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;write_bias_granted
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* When a reader does a release, the only significant&n; * case is when there was a writer waiting, and we&squot;ve&n; * bumped the count to 0: we must wake the writer up.&n; */
DECL|function|__up_read
r_extern
r_inline
r_void
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# up_read&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;incl (%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;jz 2f&bslash;n&quot;
multiline_comment|/* only do the wake if result == 0 (ie, a writer) */
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __rwsem_wake&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* releasing the writer is easy -- just release it and&n; * wake up any sleepers.&n; */
DECL|function|__up_write
r_extern
r_inline
r_void
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# up_write&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;addl $&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;,(%%eax)&bslash;n&quot;
l_string|&quot;jc 2f&bslash;n&quot;
multiline_comment|/* only do the wake if the result was -&squot;ve to 0/+&squot;ve */
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tcall __rwsem_wake&bslash;n&bslash;t&quot;
l_string|&quot;jmp 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|up_read
r_extern
r_inline
r_void
id|up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;write_bias_granted
)paren
id|BUG
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
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
id|__up_read
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
DECL|function|up_write
r_extern
r_inline
r_void
id|up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;read_bias_granted
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;write_bias_granted
)paren
id|BUG
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
id|sem-&gt;readers
)paren
)paren
id|BUG
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
id|sem-&gt;writers
)paren
op_ne
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
id|__up_write
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
