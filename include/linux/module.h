multiline_comment|/*&n; * Dynamic loading of modules into the kernel.&n; *&n; * Modified by Bjorn Ekwall &lt;bj0rn@blox.se&gt;&n; */
macro_line|#ifndef _LINUX_MODULE_H
DECL|macro|_LINUX_MODULE_H
mdefine_line|#define _LINUX_MODULE_H
macro_line|#ifdef __GENKSYMS__
DECL|macro|_set_ver
macro_line|#  define _set_ver(sym,vers) sym
DECL|macro|MODVERSIONS
macro_line|#  undef  MODVERSIONS
DECL|macro|MODVERSIONS
macro_line|#  define MODVERSIONS
macro_line|#else /* ! __GENKSYMS__ */
macro_line|# ifdef MODVERSIONS
macro_line|#  ifndef MODULE
macro_line|#   ifdef EXPORT_SYMTAB
DECL|macro|_set_ver
macro_line|#    define _set_ver(sym,vers) sym
macro_line|#    include &lt;linux/modversions.h&gt;
macro_line|#   endif /* EXPORT_SYMTAB */
macro_line|#  endif /* MODULE */
macro_line|# endif /* MODVERSIONS */
macro_line|#endif /* __GENKSYMS__ */
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
DECL|struct|kernel_sym
r_struct
id|kernel_sym
(brace
multiline_comment|/* sent to &quot;insmod&quot; */
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
DECL|struct|module_ref
r_struct
id|module_ref
(brace
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|next
r_struct
id|module_ref
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|internal_symbol
r_struct
id|internal_symbol
(brace
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|symbol_table
r_struct
id|symbol_table
(brace
multiline_comment|/* received from &quot;insmod&quot; */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* total, including string table!!! */
DECL|member|n_symbols
r_int
id|n_symbols
suffix:semicolon
DECL|member|n_refs
r_int
id|n_refs
suffix:semicolon
DECL|member|symbol
r_struct
id|internal_symbol
id|symbol
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* actual size defined by n_symbols */
DECL|member|ref
r_struct
id|module_ref
id|ref
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* actual size defined by n_refs */
)brace
suffix:semicolon
multiline_comment|/*&n; * Note: The string table follows immediately after the symbol table in memory!&n; */
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
DECL|member|ref
r_struct
id|module_ref
op_star
id|ref
suffix:semicolon
multiline_comment|/* the list of modules that refer to me */
DECL|member|symtab
r_struct
id|symbol_table
op_star
id|symtab
suffix:semicolon
DECL|member|name
r_const
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
multiline_comment|/* rename_module_symbol(old_name, new_name)  WOW! */
r_extern
r_int
id|rename_module_symbol
c_func
(paren
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* insert new symbol table */
r_extern
r_int
id|register_symtab
c_func
(paren
r_struct
id|symbol_table
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * The first word of the module contains the use count.&n; */
DECL|macro|GET_USE_COUNT
mdefine_line|#define GET_USE_COUNT(module)&t;(* (long *) (module)-&gt;addr)
multiline_comment|/*&n; * define the count variable, and usage macros.&n; */
macro_line|#ifdef MODULE
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
macro_line|#ifndef __NO_VERSION__
macro_line|#include &lt;linux/version.h&gt;
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
macro_line|#endif
macro_line|#if defined(MODVERSIONS) &amp;&amp; !defined(__GENKSYMS__)
DECL|variable|Using_Versions
r_int
id|Using_Versions
suffix:semicolon
multiline_comment|/* gcc will handle this global (used as a flag) correctly */
macro_line|#endif
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;&t;1
macro_line|#endif
macro_line|#endif
eof
