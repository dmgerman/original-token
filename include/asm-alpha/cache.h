multiline_comment|/*&n; * include/asm-alpha/cache.h&n; */
macro_line|#ifndef __ARCH_ALPHA_CACHE_H
DECL|macro|__ARCH_ALPHA_CACHE_H
mdefine_line|#define __ARCH_ALPHA_CACHE_H
multiline_comment|/* Bytes per L1 (data) cache line.  Both EV4 and EV5 are write-through,&n;   read-allocate, direct-mapped, physical. */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES     32
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)  (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES    L1_CACHE_BYTES
macro_line|#endif
eof
