multiline_comment|/* $Id: mmu_context.h,v 1.4 1996/12/28 18:39:51 davem Exp $ */
macro_line|#ifndef __SPARC64_MMU_CONTEXT_H
DECL|macro|__SPARC64_MMU_CONTEXT_H
mdefine_line|#define __SPARC64_MMU_CONTEXT_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT     -1
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Initialize the context related info for a new mm_struct&n; * instance.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm) ((mm)-&gt;context = NO_CONTEXT)
r_extern
r_void
id|spitfire_get_new_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
DECL|function|get_mmu_context
r_extern
id|__inline__
r_void
id|get_mmu_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;mm-&gt;context
op_eq
id|NO_CONTEXT
)paren
(brace
id|spitfire_get_new_context
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/* Get current set of user windows out of the cpu. */
id|flushw_user
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Jump into new ASN. */
id|spitfire_set_primary_context
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
id|spitfire_set_secondary_context
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_MMU_CONTEXT_H) */
eof
