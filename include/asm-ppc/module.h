macro_line|#ifndef _ASM_PPC_MODULE_H
DECL|macro|_ASM_PPC_MODULE_H
mdefine_line|#define _ASM_PPC_MODULE_H
multiline_comment|/*&n; * This file contains the PPC architecture specific module code.&n; */
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
macro_line|#endif /* _ASM_PPC_MODULE_H */
eof
