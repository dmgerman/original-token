macro_line|#ifndef __PPC_SMPLOCK_H
DECL|macro|__PPC_SMPLOCK_H
mdefine_line|#define __PPC_SMPLOCK_H
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;do { } while (0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;do { } while (0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#else /* __SMP__ */
multiline_comment|/* Release global kernel lock and global interrupt lock */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if((depth = (task)-&gt;lock_depth) != 0) {&t;&t;&bslash;&n;&t;&t;__cli();&t;&t;&t;&t;&bslash;&n;&t;&t;(task)-&gt;lock_depth = 0;&t;&t;&t;&bslash;&n;&t;&t;klock_info.akp = NO_PROC_ID;&t;&t;&bslash;&n;&t;&t;klock_info.kernel_flag = 0;&t;&t;&bslash;&n;&t;} &t;&t;&t;&t;&t;&t;&bslash;&n;&t;release_irqlock(cpu);&t;&t;&t;&t;&bslash;&n;&t;__sti();&t;&t;&t;&t;&t;&bslash;&n;} while(0)
r_extern
r_void
id|reacquire_kernel_lock
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* The following acquire and release the master kernel global lock,&n; * the idea is that the usage of this mechanmism becomes less and less&n; * as time goes on, to the point where they are no longer needed at all&n; * and can thus disappear.&n; */
r_extern
r_void
id|__lock_kernel
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__unlock_kernel
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
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
id|__lock_kernel
c_func
(paren
id|current
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
id|__unlock_kernel
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __PPC_SMPLOCK_H */
eof
