macro_line|#ifndef __SPARC_MMU_CONTEXT_H
DECL|macro|__SPARC_MMU_CONTEXT_H
mdefine_line|#define __SPARC_MMU_CONTEXT_H
macro_line|#include &lt;asm/btfixup.h&gt;
multiline_comment|/* For now I still leave the context handling in the&n; * switch_to() macro, I&squot;ll do it right soon enough.&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(x) do { } while (0)
multiline_comment|/* Initialize the context related info for a new mm_struct&n; * instance.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|init_new_context
comma
r_struct
id|mm_struct
op_star
)paren
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm) BTFIXUP_CALL(init_new_context)(mm)
multiline_comment|/* Destroy context related info for an mm_struct that is about&n; * to be put to rest.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|destroy_context
comma
r_struct
id|mm_struct
op_star
)paren
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm) BTFIXUP_CALL(destroy_context)(mm)
multiline_comment|/* This need not do anything on Sparc32.  The switch happens&n; * properly later as a side effect of calling flush_thread.&n; */
DECL|macro|activate_context
mdefine_line|#define activate_context(tsk)&t;do { } while(0)
macro_line|#endif /* !(__SPARC_MMU_CONTEXT_H) */
eof
