macro_line|#ifndef __LINUX_SMPLOCK_H
DECL|macro|__LINUX_SMPLOCK_H
mdefine_line|#define __LINUX_SMPLOCK_H
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu)&t;&t;do { } while(0)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;do { } while(0)
macro_line|#else
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth) &bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag); &bslash;&n;&t;release_irqlock(cpu); &bslash;&n;&t;__sti(); &bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth) &bslash;&n;&t;&t;spin_lock(&amp;kernel_flag); &bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
DECL|function|lock_kernel
r_extern
id|__inline__
r_void
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
id|lock_depth
suffix:semicolon
id|lock_depth
op_assign
id|tsk-&gt;lock_depth
suffix:semicolon
id|tsk-&gt;lock_depth
op_assign
id|lock_depth
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock_depth
)paren
id|spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
DECL|function|unlock_kernel
r_extern
id|__inline__
r_void
id|unlock_kernel
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
id|lock_depth
suffix:semicolon
id|lock_depth
op_assign
id|tsk-&gt;lock_depth
op_minus
l_int|1
suffix:semicolon
id|tsk-&gt;lock_depth
op_assign
id|lock_depth
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock_depth
)paren
id|spin_unlock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
macro_line|#endif
eof
