multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/mmu.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  20-10-1996&t;RMK&t;Created&n; *  31-12-1997&t;RMK&t;Fixed definitions to reduce warnings&n; *  11-01-1998&t;RMK&t;Uninlined to reduce hits on cache&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
r_extern
r_int
r_int
id|__virt_to_phys
c_func
(paren
r_int
r_int
id|vpage
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__phys_to_virt
c_func
(paren
r_int
r_int
id|ppage
)paren
suffix:semicolon
macro_line|#endif
eof
