macro_line|#ifndef __ASM_MIPS_CURRENT_H
DECL|macro|__ASM_MIPS_CURRENT_H
mdefine_line|#define __ASM_MIPS_CURRENT_H
macro_line|#ifdef __LANGUAGE_C__
DECL|function|__get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|__get_current
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|__current
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;ori&bslash;t%0,$29,%1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t%0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__current
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
l_int|8191UL
)paren
)paren
suffix:semicolon
r_return
id|__current
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current __get_current()
macro_line|#endif /* __LANGUAGE_C__ */
macro_line|#ifdef __LANGUAGE_ASSEMBLY__
multiline_comment|/*&n; * Get current task pointer&n; */
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT(reg)&t;&t;&t;&bslash;&n;&t;lui&t;reg, %hi(kernelsp);&t;&t;&bslash;&n;&t;lw&t;reg, %lo(kernelsp)(reg);&t;&bslash;&n;&t;ori&t;reg, 8191;&t;&t;&t;&bslash;&n;&t;xori&t;reg, 8191
multiline_comment|/*&n; * Special variant for use by exception handlers when the stack pointer&n; * is not loaded.&n; */
DECL|macro|_GET_CURRENT
mdefine_line|#define _GET_CURRENT(reg)&t;&t;&t;&bslash;&n;&t;lui&t;reg, %hi(kernelsp);&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;.set&t;noreorder;&t;&t;&t;&bslash;&n;&t;lw&t;reg, %lo(kernelsp)(reg);&t;&bslash;&n;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;&t;ori&t;reg, 8191;&t;&t;&t;&bslash;&n;&t;xori&t;reg, 8191
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_CURRENT_H */
eof
