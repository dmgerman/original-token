multiline_comment|/*&n; * include/asm-mips/cachectl.h&n; *&n; * Written by Ralf Baechle,&n; * Copyright (C) 1994 by Waldorf GMBH&n; *&n; * Defines for Risc/OS compatible cacheflush systemcall&n; */
macro_line|#ifndef&t;__ASM_MIPS_CACHECTL
DECL|macro|__ASM_MIPS_CACHECTL
mdefine_line|#define&t;__ASM_MIPS_CACHECTL
multiline_comment|/*&n; * cachectl.h -- defines for MIPS cache control system calls&n; */
multiline_comment|/*&n; * Options for cacheflush system call&n; */
DECL|macro|ICACHE
mdefine_line|#define&t;ICACHE&t;(1&lt;&lt;0)&t;&t;/* flush instruction cache        */
DECL|macro|DCACHE
mdefine_line|#define&t;DCACHE&t;(1&lt;&lt;1)&t;&t;/* writeback and flush data cache */
DECL|macro|BCACHE
mdefine_line|#define&t;BCACHE&t;(ICACHE|DCACHE)&t;/* flush both caches              */
DECL|macro|CACHELINES
mdefine_line|#define CACHELINES      512             /* number of cachelines    */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|sys_cacheflush
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|nbytes
comma
r_int
id|cache
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif&t;/* __ASM_MIPS_CACHECTL */
eof
