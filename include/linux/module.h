multiline_comment|/*&n; * Dynamic loading of modules into the kernel.&n; */
macro_line|#ifndef _LINUX_MODULE_H
DECL|macro|_LINUX_MODULE_H
mdefine_line|#define _LINUX_MODULE_H
multiline_comment|/* values of module.state */
DECL|macro|MOD_UNINITIALIZED
mdefine_line|#define MOD_UNINITIALIZED 0
DECL|macro|MOD_RUNNING
mdefine_line|#define MOD_RUNNING 1
DECL|macro|MOD_DELETED
mdefine_line|#define MOD_DELETED 2
multiline_comment|/* maximum length of module name */
DECL|macro|MOD_MAX_NAME
mdefine_line|#define MOD_MAX_NAME 64
multiline_comment|/* maximum length of symbol name */
DECL|macro|SYM_MAX_NAME
mdefine_line|#define SYM_MAX_NAME 60
DECL|struct|module
r_struct
id|module
(brace
DECL|member|next
r_struct
id|module
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of module in pages */
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
multiline_comment|/* address of module */
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* cleanup routine */
)brace
suffix:semicolon
DECL|struct|mod_routines
r_struct
id|mod_routines
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* initialization routine */
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* cleanup routine */
)brace
suffix:semicolon
DECL|struct|kernel_sym
r_struct
id|kernel_sym
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* value of symbol */
DECL|member|name
r_char
id|name
(braket
id|SYM_MAX_NAME
)braket
suffix:semicolon
multiline_comment|/* name of symbol */
)brace
suffix:semicolon
r_extern
r_struct
id|module
op_star
id|module_list
suffix:semicolon
multiline_comment|/*&n; * The first word of the module contains the use count.&n; */
DECL|macro|GET_USE_COUNT
mdefine_line|#define GET_USE_COUNT(module)&t;(* (int *) (module)-&gt;addr)
multiline_comment|/*&n; * define the count variable, and usage macros.&n; */
r_extern
r_int
id|mod_use_count_
suffix:semicolon
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT      mod_use_count_++
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT      mod_use_count_--
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;       (mod_use_count_ != 0)
macro_line|#endif
eof
