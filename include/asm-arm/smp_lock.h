macro_line|#ifndef __I386_SMPLOCK_H
DECL|macro|__I386_SMPLOCK_H
mdefine_line|#define __I386_SMPLOCK_H
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#else
macro_line|#error SMP not supported
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __I386_SMPLOCK_H */
eof