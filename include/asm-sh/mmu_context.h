multiline_comment|/*&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * ASID handling idea taken from MIPS implementation.&n; */
macro_line|#ifndef __ASM_SH_MMU_CONTEXT_H
DECL|macro|__ASM_SH_MMU_CONTEXT_H
mdefine_line|#define __ASM_SH_MMU_CONTEXT_H
multiline_comment|/* The MMU &quot;context&quot; consists of two things:&n;     (a) TLB cache version (or round, cycle whatever expression you like)&n;     (b) ASID (Address Space IDentifier)&n; */
multiline_comment|/*&n; * Cache of MMU context last used.&n; */
r_extern
r_int
r_int
id|mmu_context_cache
suffix:semicolon
DECL|macro|MMU_CONTEXT_ASID_MASK
mdefine_line|#define MMU_CONTEXT_ASID_MASK 0xff
DECL|macro|MMU_CONTEXT_VERSION_MASK
mdefine_line|#define MMU_CONTEXT_VERSION_MASK 0xffffff00
DECL|macro|MMU_CONTEXT_FIRST_VERSION
mdefine_line|#define MMU_CONTEXT_FIRST_VERSION 0x100
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT 0
r_extern
id|__inline__
r_void
DECL|function|get_new_mmu_context
id|get_new_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|mc
op_assign
op_increment
id|mmu_context_cache
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mc
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
)paren
(brace
multiline_comment|/* We exhaust ASID of this version.&n;&t;&t;   Flush all TLB and start new cycle. */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fix version if needed.&n;&t;&t;   Note that we avoid version #0 to distingush NO_CONTEXT. */
r_if
c_cond
(paren
op_logical_neg
id|mc
)paren
id|mmu_context_cache
op_assign
id|mc
op_assign
id|MMU_CONTEXT_FIRST_VERSION
suffix:semicolon
)brace
id|mm-&gt;context
op_assign
id|mc
suffix:semicolon
)brace
multiline_comment|/*&n; * Get MMU context if needed.&n; */
r_extern
id|__inline__
r_void
DECL|function|get_mmu_context
id|get_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
)paren
(brace
r_int
r_int
id|mc
op_assign
id|mmu_context_cache
suffix:semicolon
multiline_comment|/* Check if we have old version of context.&n;&t;&t;   If it&squot;s old, we need to get new context with new version. */
r_if
c_cond
(paren
(paren
id|mm-&gt;context
op_xor
id|mc
)paren
op_amp
id|MMU_CONTEXT_VERSION_MASK
)paren
id|get_new_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|function|init_new_context
r_extern
id|__inline__
r_void
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
DECL|function|destroy_context
r_extern
id|__inline__
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
)brace
multiline_comment|/* Other MMU related constants. */
macro_line|#if defined(__sh3__)
DECL|macro|MMU_PTEH
mdefine_line|#define MMU_PTEH&t;0xFFFFFFF0&t;/* Page table entry register HIGH */
DECL|macro|MMU_PTEL
mdefine_line|#define MMU_PTEL&t;0xFFFFFFF4&t;/* Page table entry register LOW */
DECL|macro|MMU_TTB
mdefine_line|#define MMU_TTB&t;&t;0xFFFFFFF8&t;/* Translation table base register */
DECL|macro|MMU_TEA
mdefine_line|#define MMU_TEA&t;&t;0xFFFFFFFC&t;/* TLB Exception Address */
DECL|macro|MMUCR
mdefine_line|#define MMUCR&t;&t;0xFFFFFFE0&t;/* MMU Control Register */
DECL|macro|MMU_TLB_ADDRESS_ARRAY
mdefine_line|#define MMU_TLB_ADDRESS_ARRAY 0xF2000000
DECL|macro|MMU_PAGE_ASSOC_BIT
mdefine_line|#define MMU_PAGE_ASSOC_BIT 0x80
DECL|macro|MMU_NTLB_ENTRIES
mdefine_line|#define MMU_NTLB_ENTRIES       128&t;/* for 7708 */
DECL|macro|MMU_CONTROL_INIT
mdefine_line|#define MMU_CONTROL_INIT 0x007&t;/* SV=0, TF=1, IX=1, AT=1 */
macro_line|#elif defined(__SH4__)
DECL|macro|MMU_PTEH
mdefine_line|#define MMU_PTEH&t;0xFF000000&t;/* Page table entry register HIGH */
DECL|macro|MMU_PTEL
mdefine_line|#define MMU_PTEL&t;0xFF000004&t;/* Page table entry register LOW */
DECL|macro|MMU_TTB
mdefine_line|#define MMU_TTB&t;&t;0xFF000008&t;/* Translation table base register */
DECL|macro|MMU_TEA
mdefine_line|#define MMU_TEA&t;&t;0xFF00000C&t;/* TLB Exception Address */
DECL|macro|MMUCR
mdefine_line|#define MMUCR&t;&t;0xFF000010&t;/* MMU Control Register */
DECL|macro|MMU_ITLB_ADDRESS_ARRAY
mdefine_line|#define MMU_ITLB_ADDRESS_ARRAY 0xF2000000
DECL|macro|MMU_UTLB_ADDRESS_ARRAY
mdefine_line|#define MMU_UTLB_ADDRESS_ARRAY 0xF6000000
DECL|macro|MMU_PAGE_ASSOC_BIT
mdefine_line|#define MMU_PAGE_ASSOC_BIT 0x80
DECL|macro|MMU_NTLB_ENTRIES
mdefine_line|#define MMU_NTLB_ENTRIES       64&t;/* for 7750 */
DECL|macro|MMU_CONTROL_INIT
mdefine_line|#define MMU_CONTROL_INIT 0x205&t;/* SQMD=1, SV=0, TI=1, AT=1 */
macro_line|#endif
DECL|function|set_asid
r_extern
id|__inline__
r_void
id|set_asid
(paren
r_int
r_int
id|asid
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov.l&t;%0,%1&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|asid
)paren
comma
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_PTEH
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_asid
r_extern
id|__inline__
r_int
r_int
id|get_asid
(paren
r_void
)paren
(brace
r_int
r_int
id|asid
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov.l %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|asid
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_PTEH
)paren
)paren
)paren
suffix:semicolon
id|asid
op_and_assign
id|MMU_CONTEXT_ASID_MASK
suffix:semicolon
r_return
id|asid
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_context
r_extern
id|__inline__
r_void
id|activate_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|get_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|set_asid
c_func
(paren
id|mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/* MMU_TTB can be used for optimizing the fault handling.&n;   (Currently not used) */
DECL|function|switch_mm
r_extern
id|__inline__
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
r_struct
id|task_struct
op_star
id|tsk
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
r_int
r_int
id|__pgdir
op_assign
(paren
r_int
r_int
)paren
id|next-&gt;pgd
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov.l&t;%0,%1&quot;
suffix:colon
"&bslash;"
suffix:colon
l_string|&quot;r&quot;
(paren
id|__pgdir
)paren
comma
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|MMU_TTB
)paren
)paren
)paren
suffix:semicolon
id|activate_context
c_func
(paren
id|next
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
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next) &bslash;&n;&t;switch_mm((prev),(next),NULL,smp_processor_id())
macro_line|#endif /* __ASM_SH_MMU_CONTEXT_H */
eof
