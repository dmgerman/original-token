multiline_comment|/* smp_lock.h: Locking and unlocking the kernel on the 64-bit Sparc.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SMPLOCK_H
DECL|macro|__SPARC64_SMPLOCK_H
mdefine_line|#define __SPARC64_SMPLOCK_H
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reaquire_kernel_lock
mdefine_line|#define reaquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#else
macro_line|#error SMP on sparc64 not supported yet
macro_line|#endif /* (__SMP__) */
macro_line|#endif /* !(__SPARC64_SMPLOCK_H) */
eof
