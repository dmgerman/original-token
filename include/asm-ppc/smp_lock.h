macro_line|#ifndef __PPC_SMPLOCK_H
DECL|macro|__PPC_SMPLOCK_H
mdefine_line|#define __PPC_SMPLOCK_H
macro_line|#include &lt;linux/kernel.h&gt; /* for panic */
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;do { } while (0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;do { } while (0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#else
multiline_comment|/* Release global kernel lock and global interrupt lock */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if((depth = (task)-&gt;lock_depth) != 0) {&t;&t;&bslash;&n;&t;&t;__cli();&t;&t;&t;&t;&bslash;&n;&t;&t;(task)-&gt;lock_depth = 0;&t;&t;&t;&bslash;&n;&t;&t;klock_info.akp = NO_PROC_ID;&t;&t;&bslash;&n;&t;&t;klock_info.kernel_flag = 0;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;release_irqlock(cpu);&t;&t;&t;&t;&bslash;&n;&t;__sti();&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* Re-acquire the kernel lock */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth) &bslash;&n;do { if (depth) &bslash;&n;&t;{ __cli(); &bslash;&n;&t;  __asm__ __volatile__( &bslash;&n;&t;  &quot;blr __lock_kernel&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;stw %2,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;  : &quot;=m&quot; (task-&gt;lock_depth) &bslash;&n;&t;  : &quot;d&quot; (cpu), &quot;c&quot; (depth)); &bslash;&n;&t;  __sti(); &bslash;&n;       } &bslash;&n;} while (0)
multiline_comment|/* The following acquire and release the master kernel global lock,&n; * the idea is that the usage of this mechanmism becomes less and less&n; * as time goes on, to the point where they are no longer needed at all&n; * and can thus disappear.&n; */
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
id|panic
c_func
(paren
l_string|&quot;lock_kernel()&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Release kernel global lock. */
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
id|panic
c_func
(paren
l_string|&quot;unlock_kernel()&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __PPC_SMPLOCK_H */
eof
