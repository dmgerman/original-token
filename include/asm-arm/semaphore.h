multiline_comment|/*&n; * linux/include/asm-arm/semaphore.h&n; */
macro_line|#ifndef __ASM_ARM_SEMAPHORE_H
DECL|macro|__ASM_ARM_SEMAPHORE_H
mdefine_line|#define __ASM_ARM_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
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
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INIT
mdefine_line|#define __SEMAPHORE_INIT(name,count)&t;&t;&t;&bslash;&n;&t;{ ATOMIC_INIT(count), 0,&t;&t;&t;&bslash;&n;&t;  __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) }
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INIT(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count)&t;&bslash;&n;&t;struct semaphore name = __SEMAPHORE_INIT(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name)&t;&t;__DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name)&t;__DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;atomic_set(&amp;((sem)-&gt;count), (val));&t;&bslash;&n;&t;(sem)-&gt;sleepers = 0;&t;&t;&t;&bslash;&n;&t;init_waitqueue_head(&amp;(sem)-&gt;wait);&t;&bslash;&n;} while (0)
DECL|function|init_MUTEX
r_static
r_inline
r_void
id|init_MUTEX
c_func
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
c_func
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
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_interruptible_failed
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_trylock_failed
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
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
r_extern
id|spinlock_t
id|semaphore_wake_lock
suffix:semicolon
macro_line|#include &lt;asm/proc/semaphore.h&gt;
macro_line|#endif
eof
