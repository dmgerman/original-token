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
macro_line|#include &lt;asm/smplock.h&gt;
macro_line|#endif /* __SMP__ */
macro_line|#endif
eof
