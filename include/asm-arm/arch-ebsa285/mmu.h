multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/mmu.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  20-10-1996&t;RMK&t;Created&n; *  31-12-1997&t;RMK&t;Fixed definitions to reduce warnings&n; *  17-05-1998&t;DAG&t;Added __virt_to_bus and __bus_to_virt functions.&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
multiline_comment|/*&n; * On ebsa285, the dram is contiguous&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((vpage) - PAGE_OFFSET)
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((ppage) + PAGE_OFFSET)
r_extern
r_int
r_int
id|__virt_to_bus
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__bus_to_virt
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
