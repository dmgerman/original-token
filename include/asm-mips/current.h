macro_line|#ifndef __ASM_MIPS_CURRENT_H
DECL|macro|__ASM_MIPS_CURRENT_H
mdefine_line|#define __ASM_MIPS_CURRENT_H
macro_line|#ifdef __LANGUAGE_C__
multiline_comment|/* MIPS rules... */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
c_func
(paren
l_string|&quot;$28&quot;
)paren
suffix:semicolon
macro_line|#endif /* __LANGUAGE_C__ */
macro_line|#ifdef __LANGUAGE_ASSEMBLY__
multiline_comment|/*&n; * Special variant for use by exception handlers when the stack pointer&n; * is not loaded.&n; */
DECL|macro|_GET_CURRENT
mdefine_line|#define _GET_CURRENT(reg)&t;&t;&t;&bslash;&n;&t;lui&t;reg, %hi(kernelsp);&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;.set&t;noreorder;&t;&t;&t;&bslash;&n;&t;lw&t;reg, %lo(kernelsp)(reg);&t;&bslash;&n;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;&t;ori&t;reg, 8191;&t;&t;&t;&bslash;&n;&t;xori&t;reg, 8191
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_CURRENT_H */
eof
