macro_line|#ifndef __M68K_MMU_CONTEXT_H
DECL|macro|__M68K_MMU_CONTEXT_H
mdefine_line|#define __M68K_MMU_CONTEXT_H
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_extern
r_inline
r_void
DECL|function|init_new_context
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
id|virt_to_phys
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
)brace
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|function|switch_mm_0230
r_extern
r_inline
r_void
id|switch_mm_0230
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|crp
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x80000000
op_or
id|_PAGE_TABLE
comma
id|mm-&gt;context
)brace
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68030&quot;
)paren
suffix:semicolon
multiline_comment|/* flush MC68030/MC68020 caches (they are virtually addressed) */
id|asm
r_volatile
(paren
l_string|&quot;movec %%cacr,%0;&quot;
l_string|&quot;orw %1,%0; &quot;
l_string|&quot;movec %0,%%cacr&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|FLUSH_I_AND_D
)paren
)paren
suffix:semicolon
multiline_comment|/* Switch the root pointer. For a 030-only kernel,&n;&t; * avoid flushing the whole ATC, we only need to&n;&t; * flush the user entries. The 68851 does this by&n;&t; * itself. Avoid a runtime check here.&n;&t; */
id|asm
r_volatile
(paren
macro_line|#ifdef CPU_M68030_ONLY
l_string|&quot;pmovefd %0,%%crp; &quot;
l_string|&quot;pflush #0,#4&quot;
macro_line|#else
l_string|&quot;pmove %0,%%crp&quot;
macro_line|#endif
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|crp
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68k&quot;
)paren
suffix:semicolon
)brace
DECL|function|switch_mm_0460
r_extern
r_inline
r_void
id|switch_mm_0460
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;.chip 68040&quot;
)paren
suffix:semicolon
multiline_comment|/* flush address translation cache (user entries) */
id|asm
r_volatile
(paren
l_string|&quot;pflushan&quot;
)paren
suffix:semicolon
multiline_comment|/* switch the root pointer */
id|asm
r_volatile
(paren
l_string|&quot;movec %0,%%urp&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mm-&gt;context
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_060
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* clear user entries in the branch cache */
id|asm
r_volatile
(paren
l_string|&quot;movec %%cacr,%0; &quot;
l_string|&quot;orl %1,%0; &quot;
l_string|&quot;movec %0,%%cacr&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
l_int|0x00200000
)paren
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;.chip 68k&quot;
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
id|switch_mm_0230
c_func
(paren
id|next
)paren
suffix:semicolon
r_else
id|switch_mm_0460
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
)brace
DECL|function|activate_mm
r_extern
r_inline
r_void
id|activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
)paren
(brace
id|next_mm-&gt;context
op_assign
id|virt_to_phys
c_func
(paren
id|next_mm-&gt;pgd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
id|switch_mm_0230
c_func
(paren
id|next_mm
)paren
suffix:semicolon
r_else
id|switch_mm_0460
c_func
(paren
id|next_mm
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
