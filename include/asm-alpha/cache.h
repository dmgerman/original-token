multiline_comment|/*&n; * include/asm-alpha/cache.h&n; */
macro_line|#ifndef __ARCH_ALPHA_CACHE_H
DECL|macro|__ARCH_ALPHA_CACHE_H
mdefine_line|#define __ARCH_ALPHA_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32      /* a guess */
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
macro_line|#endif
eof
