multiline_comment|/*&n; * include/asm-i386/cache.h&n; */
macro_line|#ifndef __ARCH_I386_CACHE_H
DECL|macro|__ARCH_I386_CACHE_H
mdefine_line|#define __ARCH_I386_CACHE_H
multiline_comment|/* bytes per L1 cache line */
macro_line|#if    CPU==586 || CPU==686
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32
macro_line|#else
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  16
macro_line|#endif
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define        SMP_CACHE_BYTES L1_CACHE_BYTES
macro_line|#endif
eof
