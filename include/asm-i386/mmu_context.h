macro_line|#ifndef __I386_MMU_CONTEXT_H
DECL|macro|__I386_MMU_CONTEXT_H
mdefine_line|#define __I386_MMU_CONTEXT_H
macro_line|#include &lt;asm/desc.h&gt;
multiline_comment|/*&n; * possibly do the LDT unload here?&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;do { } while (0)
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
)paren
(brace
multiline_comment|/*&n;&t; * Re-load LDT if necessary&n;&t; */
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
)brace
macro_line|#endif
eof
