macro_line|#ifndef __M68K_SMPLOCK_H
DECL|macro|__M68K_SMPLOCK_H
mdefine_line|#define __M68K_SMPLOCK_H
multiline_comment|/*&n; * We don&squot;t do SMP so this is again one of these silly dummy files&n; * to keep the kernel source looking nice ;-(.&n; */
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#endif
macro_line|#ifndef __M68K_SMPLOCK_H
DECL|macro|__M68K_SMPLOCK_H
mdefine_line|#define __M68K_SMPLOCK_H
multiline_comment|/*&n; * We don&squot;t do SMP so this is again one of these silly dummy files&n; * to keep the kernel source looking nice ;-(.&n; */
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reaquire_kernel_lock
mdefine_line|#define reaquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#endif
eof
