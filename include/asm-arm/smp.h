macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#ifdef __SMP__
macro_line|#error SMP not supported
macro_line|#else
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu) (cpu)
macro_line|#endif
macro_line|#endif
eof
