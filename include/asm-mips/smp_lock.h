multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996  Ralf Baechle&n; *&n; * Linux/MIPS SMP support.  Just a dummy to make building possible.&n; */
macro_line|#ifndef __ASM_MIPS_SMPLOCK_H
DECL|macro|__ASM_MIPS_SMPLOCK_H
mdefine_line|#define __ASM_MIPS_SMPLOCK_H
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)  ((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth) do { } while(0)
macro_line|#else
macro_line|#error &quot;We do not support SMP on MIPS yet&quot;
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ASM_MIPS_SMPLOCK_H */
eof
