macro_line|#ifndef __SPARC_MMU_CONTEXT_H
DECL|macro|__SPARC_MMU_CONTEXT_H
mdefine_line|#define __SPARC_MMU_CONTEXT_H
multiline_comment|/* For now I still leave the context handling in the&n; * switch_to() macro, I&squot;ll do it right soon enough.&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(x) do { } while (0)
multiline_comment|/* Initialize the context related info for a new mm_struct&n; * instance.&n; */
r_extern
r_void
(paren
op_star
id|init_new_context
)paren
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/* Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
r_extern
r_void
(paren
op_star
id|destroy_context
)paren
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
macro_line|#endif /* !(__SPARC_MMU_CONTEXT_H) */
eof
