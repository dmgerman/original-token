multiline_comment|/*&n; * linux/include/asm-arm/mmu_context.h&n; *&n; * Copyright (c) 1996 Russell King.&n; *&n; * Changelog:&n; *  27-06-1996&t;RMK&t;Created&n; */
macro_line|#ifndef __ASM_ARM_MMU_CONTEXT_H
DECL|macro|__ASM_ARM_MMU_CONTEXT_H
mdefine_line|#define __ASM_ARM_MMU_CONTEXT_H
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;do { } while(0)
multiline_comment|/*&n; * This is the actual mm switch as far as the scheduler&n; * is concerned.  No registers are touched.&n; */
DECL|function|switch_mm
r_static
r_inline
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_int
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
(brace
id|processor.u.armv3v4
dot
id|_set_pgd
c_func
(paren
id|__virt_to_phys
c_func
(paren
(paren
r_int
r_int
)paren
id|next-&gt;pgd
)paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|prev-&gt;cpu_vm_mask
)paren
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|cpu
comma
op_amp
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
