multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/memory.h&n; *&n; * Copyright (c) 1999 Nicolas Pitre &lt;nico@visuaide.com&gt;&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xc0000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x00000000UL)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
multiline_comment|/*&n; * The following gives a maximum memory size of 128MB (32MB in each bank).&n; *&n; * Does this still need to be optimised for one bank machines?&n; */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(x)&t;(((x) &amp; 0xe0ffffff) | ((x) &amp; 0x06000000) &lt;&lt; 2)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(x)&t;(((x) &amp; 0xe7ffffff) | ((x) &amp; 0x30000000) &gt;&gt; 2)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t; address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t; to an address that the kernel can use.&n; *&n; * On the SA1100, bus addresses are equivalent to physical addresses.&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#endif
eof
