multiline_comment|/*&n; * linux/include/asm-arm/semaphore.h&n; */
macro_line|#ifndef __ASM_ARM_SEMAPHORE_H
DECL|macro|__ASM_ARM_SEMAPHORE_H
mdefine_line|#define __ASM_ARM_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
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
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), (val))
macro_line|#include &lt;asm/proc/semaphore.h&gt;
macro_line|#endif
eof
