multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/memory.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; *&n; * Changelog:&n; *  22-Nov-1996&t;RMK&t;Created&n; *  21-Mar-1999&t;RMK&t;Renamed to memory.h&n; *&t;&t;RMK&t;Moved PAGE_OFFSET and TASK_SIZE here&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * User space: 26MB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x01a00000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x01a00000UL)
multiline_comment|/*&n; * Page offset: 32MB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0x02000000UL)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) vpage
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ppage
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *              address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *              to an address that the kernel can use.&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(x)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;(x)
macro_line|#endif
eof
