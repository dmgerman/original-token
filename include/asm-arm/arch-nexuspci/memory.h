multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/memory.h&n; *&n; * Copyright (c) 1997, 1998 Philip Blundell.&n; * Copyright (c) 1999 Russell King&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x04000000UL)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xc0000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x40000000UL)
multiline_comment|/*&n; * On NexusPCI, the DRAM is contiguous&n; */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((vpage) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((ppage) + PAGE_OFFSET - PHYS_OFFSET)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
multiline_comment|/*&n; * On the PCI bus the DRAM appears at address 0&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) ((x) - PAGE_OFFSET)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) ((x) + PAGE_OFFSET)
macro_line|#endif
eof
