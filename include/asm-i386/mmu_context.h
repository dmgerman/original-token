macro_line|#ifndef __I386_MMU_CONTEXT_H
DECL|macro|__I386_MMU_CONTEXT_H
mdefine_line|#define __I386_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context.. x86&squot;s don&squot;t know about contexts.&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(x) do { } while (0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm)&t;do { } while(0)
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while(0)
macro_line|#endif
eof
