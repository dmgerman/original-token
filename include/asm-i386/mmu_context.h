macro_line|#ifndef __I386_MMU_CONTEXT_H
DECL|macro|__I386_MMU_CONTEXT_H
mdefine_line|#define __I386_MMU_CONTEXT_H
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/*&n; * possibly do the LDT unload here?&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;do { } while (0)
macro_line|#ifdef __SMP__
r_extern
r_int
r_int
id|cpu_tlbbad
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
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
r_struct
id|task_struct
op_star
id|tsk
comma
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
multiline_comment|/*&n;&t;&t; * Re-load LDT if necessary&n;&t;&t; */
r_if
c_cond
(paren
id|prev-&gt;segments
op_ne
id|next-&gt;segments
)paren
id|load_LDT
c_func
(paren
id|next
)paren
suffix:semicolon
multiline_comment|/* Re-load page tables */
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%cr3&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|__pa
c_func
(paren
id|next-&gt;pgd
)paren
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
macro_line|#ifdef __SMP__
r_else
(brace
r_if
c_cond
(paren
id|cpu_tlbbad
(braket
id|cpu
)braket
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|cpu_tlbbad
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
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
macro_line|#endif
eof
