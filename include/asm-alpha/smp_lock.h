macro_line|#ifndef __ALPHA_SMPLOCK_H
DECL|macro|__ALPHA_SMPLOCK_H
mdefine_line|#define __ALPHA_SMPLOCK_H
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reaquire_kernel_lock
mdefine_line|#define reaquire_kernel_lock(task, cpu, depth)&t;do { } while (0)
macro_line|#else
macro_line|#error &quot;We do not support SMP on alpha yet&quot;
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ALPHA_SMPLOCK_H */
eof
