multiline_comment|/*&n; * include/asm-sparc64/cache.h&n; */
macro_line|#ifndef __ARCH_SPARC64_CACHE_H
DECL|macro|__ARCH_SPARC64_CACHE_H
mdefine_line|#define __ARCH_SPARC64_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES&t;&t;32 /* Two 16-byte sub-blocks per line. */
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
macro_line|#endif
eof