multiline_comment|/*&n; * linux/include/asm-arm/arch-rpc/mmu.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  20-10-1996&t;RMK&t;Created&n; *  31-12-1997&t;RMK&t;Fixed definitions to reduce warnings&n; *  11-01-1998&t;RMK&t;Uninlined to reduce hits on cache&n; *  08-02-1998&t;RMK&t;Added __virt_to_bus and __bus_to_virt&n; */
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
multiline_comment|/*&n; * These are exactly the same on the RiscPC as the&n; * physical memory view.&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) __virt_to_phys(x)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) __phys_to_virt(x)
macro_line|#endif
eof
