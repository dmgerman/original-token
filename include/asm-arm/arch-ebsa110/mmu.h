multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/mmu.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  20-10-1996&t;RMK&t;Created&n; *  31-12-1997&t;RMK&t;Fixed definitions to reduce warnings&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
multiline_comment|/*&n; * On ebsa, the dram is contiguous&n; */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((vpage) - PAGE_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((ppage) + PAGE_OFFSET)
macro_line|#endif
eof
