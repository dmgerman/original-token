macro_line|#ifndef __I386_MMU_CONTEXT_H
DECL|macro|__I386_MMU_CONTEXT_H
mdefine_line|#define __I386_MMU_CONTEXT_H
macro_line|#include &lt;asm/desc.h&gt;
multiline_comment|/*&n; * get a new mmu context.. x86&squot;s don&squot;t know much about contexts,&n; * but we have to reload the new LDT in exec().&n; *&n; * We implement lazy MMU context-switching on x86 to optimize context&n; * switches done to/from kernel threads. Kernel threads &squot;inherit&squot; the&n; * previous MM, so Linux doesnt have to flush the TLB. In most cases&n; * we switch back to the same process so we preserve the TLB cache.&n; * This all means that kernel threads have about as much overhead as&n; * a function call ...&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(next) do { } while (0)
DECL|macro|set_mmu_context
mdefine_line|#define set_mmu_context(prev,next) do { next-&gt;thread.cr3 = prev-&gt;thread.cr3; } while(0)
multiline_comment|/*&n; * possibly do the LDT unload here?&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;do { (tsk)-&gt;thread.cr3 = __pa((mm)-&gt;pgd); } while (0)
DECL|function|activate_context
r_static
r_inline
r_void
id|activate_context
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_int
r_int
id|cr3
suffix:semicolon
id|load_LDT
c_func
(paren
id|mm
)paren
suffix:semicolon
id|cr3
op_assign
id|__pa
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
id|tsk-&gt;thread.cr3
op_assign
id|cr3
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %0,%%cr3&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
