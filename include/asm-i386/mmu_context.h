macro_line|#ifndef __I386_MMU_CONTEXT_H
DECL|macro|__I386_MMU_CONTEXT_H
mdefine_line|#define __I386_MMU_CONTEXT_H
macro_line|#include &lt;asm/desc.h&gt;
multiline_comment|/*&n; * get a new mmu context.. x86&squot;s don&squot;t know much about contexts,&n; * but we have to reload the new LDT in exec(). &n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(tsk)&t;do { } while(0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm)&t;do { } while(0)
multiline_comment|/*&n; * possibly do the LDT unload here?&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while(0)
DECL|macro|activate_context
mdefine_line|#define activate_context(x)&t;load_LDT((x)-&gt;mm)
macro_line|#endif
eof
