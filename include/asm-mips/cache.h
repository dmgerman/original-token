multiline_comment|/*&n; * include/asm-mips/cache.h&n; */
macro_line|#ifndef __ASM_MIPS_CACHE_H
DECL|macro|__ASM_MIPS_CACHE_H
mdefine_line|#define __ASM_MIPS_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32      /* a guess */
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define        SMP_CACHE_BYTES L1_CACHE_BYTES
macro_line|#endif /* __ASM_MIPS_CACHE_H */
eof
