multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/mmu.h&n; *&n; * Copyright (c) 1997 Philip Blundell.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
multiline_comment|/*&n; * On NexusPCI, the dram is contiguous&n; */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((vpage) - PAGE_OFFSET + 0x40000000)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((ppage) + PAGE_OFFSET - 0x40000000)
macro_line|#endif
eof
