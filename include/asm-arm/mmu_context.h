multiline_comment|/*&n; * linux/include/asm-arm/mmu_context.h&n; *&n; * Copyright (c) 1996 Russell King.&n; *&n; * Changelog:&n; *  27-06-1996&t;RMK&t;Created&n; */
macro_line|#ifndef __ASM_ARM_MMU_CONTEXT_H
DECL|macro|__ASM_ARM_MMU_CONTEXT_H
mdefine_line|#define __ASM_ARM_MMU_CONTEXT_H
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(x) do { } while (0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm)&t;do { } while(0)
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while(0)
DECL|macro|activate_context
mdefine_line|#define activate_context(tsk)&t;do { } while(0)
macro_line|#endif
eof
