multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/memory.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; *&n; * Changelog:&n; *  20-Oct-1996&t;RMK&t;Created&n; *  31-Dec-1997&t;RMK&t;Fixed definitions to reduce warnings.&n; *  17-May-1998&t;DAG&t;Added __virt_to_bus and __bus_to_virt functions.&n; *  21-Nov-1998&t;RMK&t;Changed __virt_to_bus and __bus_to_virt to macros.&n; *  21-Mar-1999&t;RMK&t;Added PAGE_OFFSET for co285 architecture.&n; *&t;&t;&t;Renamed to memory.h&n; *&t;&t;&t;Moved PAGE_OFFSET and TASK_SIZE here&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
macro_line|#if defined(CONFIG_HOST_FOOTBRIDGE)
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(0xc0000000UL)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0xc0000000UL)
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;((x) - 0xe0000000)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;((x) + 0xe0000000)
macro_line|#elif defined(CONFIG_ADDIN_FOOTBRIDGE)
macro_line|#if defined(CONFIG_ARCH_CO285)
multiline_comment|/*&n; * Task size: 1.5GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(0x60000000UL)
multiline_comment|/*&n; * Page offset: 1.5GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0x60000000UL)
macro_line|#else
macro_line|#error Add in your architecture here
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
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
macro_line|#endif
multiline_comment|/*&n; * On Footbridge machines, the dram is contiguous.&n; * On Host Footbridge, these conversions are constant.&n; * On an add-in footbridge, these depend on register settings.&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((unsigned long)(vpage) - PAGE_OFFSET)
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((unsigned long)(ppage) + PAGE_OFFSET)
macro_line|#endif
eof
