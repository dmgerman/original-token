multiline_comment|/*&n; * Dynamic loading of modules into the kernel.&n; *&n; * Rewritten by Richard Henderson &lt;rth@tamu.edu&gt; Dec 1996&n; */
macro_line|#ifndef _LINUX_MODULE_H
DECL|macro|_LINUX_MODULE_H
mdefine_line|#define _LINUX_MODULE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef __GENKSYMS__
DECL|macro|_set_ver
macro_line|#  define _set_ver(sym) sym
DECL|macro|MODVERSIONS
macro_line|#  undef  MODVERSIONS
DECL|macro|MODVERSIONS
macro_line|#  define MODVERSIONS
macro_line|#else /* ! __GENKSYMS__ */
macro_line|# if !defined(MODVERSIONS) &amp;&amp; defined(EXPORT_SYMTAB)
DECL|macro|_set_ver
macro_line|#   define _set_ver(sym) sym
macro_line|#   include &lt;linux/modversions.h&gt;
macro_line|# endif
macro_line|#endif /* __GENKSYMS__ */
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* Don&squot;t need to bring in all of uaccess.h just for this decl.  */
r_struct
id|exception_table_entry
suffix:semicolon
multiline_comment|/* Used by get_kernel_syms, which is obsolete.  */
DECL|struct|kernel_sym
r_struct
id|kernel_sym
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* should have been 64-sizeof(long); oh well */
)brace
suffix:semicolon
DECL|struct|module_symbol
r_struct
id|module_symbol
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|module_ref
r_struct
id|module_ref
(brace
DECL|member|dep
r_struct
id|module
op_star
id|dep
suffix:semicolon
multiline_comment|/* &quot;parent&quot; pointer */
DECL|member|ref
r_struct
id|module
op_star
id|ref
suffix:semicolon
multiline_comment|/* &quot;child&quot; pointer */
DECL|member|next_ref
r_struct
id|module_ref
op_star
id|next_ref
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TBD */
r_struct
id|module_persist
suffix:semicolon
DECL|struct|module
r_struct
id|module
(brace
DECL|member|size_of_struct
r_int
r_int
id|size_of_struct
suffix:semicolon
multiline_comment|/* == sizeof(module) */
DECL|member|next
r_struct
id|module
op_star
id|next
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
r_union
(brace
DECL|member|usecount
id|atomic_t
id|usecount
suffix:semicolon
DECL|member|pad
r_int
id|pad
suffix:semicolon
DECL|member|uc
)brace
id|uc
suffix:semicolon
multiline_comment|/* Needs to keep its size - so says rth */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* AUTOCLEAN et al */
DECL|member|nsyms
r_int
id|nsyms
suffix:semicolon
DECL|member|ndeps
r_int
id|ndeps
suffix:semicolon
DECL|member|syms
r_struct
id|module_symbol
op_star
id|syms
suffix:semicolon
DECL|member|deps
r_struct
id|module_ref
op_star
id|deps
suffix:semicolon
DECL|member|refs
r_struct
id|module_ref
op_star
id|refs
suffix:semicolon
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
DECL|member|ex_table_start
r_const
r_struct
id|exception_table_entry
op_star
id|ex_table_start
suffix:semicolon
DECL|member|ex_table_end
r_const
r_struct
id|exception_table_entry
op_star
id|ex_table_end
suffix:semicolon
macro_line|#ifdef __alpha__
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
macro_line|#endif
multiline_comment|/* Members past this point are extensions to the basic&n;&t;   module support and are optional.  Use mod_opt_member()&n;&t;   to examine them.  */
DECL|member|persist_start
r_const
r_struct
id|module_persist
op_star
id|persist_start
suffix:semicolon
DECL|member|persist_end
r_const
r_struct
id|module_persist
op_star
id|persist_end
suffix:semicolon
DECL|member|can_unload
r_int
(paren
op_star
id|can_unload
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|module_info
r_struct
id|module_info
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits of module.flags.  */
DECL|macro|MOD_UNINITIALIZED
mdefine_line|#define MOD_UNINITIALIZED&t;0
DECL|macro|MOD_RUNNING
mdefine_line|#define MOD_RUNNING&t;&t;1
DECL|macro|MOD_DELETED
mdefine_line|#define MOD_DELETED&t;&t;2
DECL|macro|MOD_AUTOCLEAN
mdefine_line|#define MOD_AUTOCLEAN&t;&t;4
DECL|macro|MOD_VISITED
mdefine_line|#define MOD_VISITED  &t;&t;8
DECL|macro|MOD_USED_ONCE
mdefine_line|#define MOD_USED_ONCE&t;&t;16
DECL|macro|MOD_JUST_FREED
mdefine_line|#define MOD_JUST_FREED&t;&t;32
multiline_comment|/* Values for query_module&squot;s which.  */
DECL|macro|QM_MODULES
mdefine_line|#define QM_MODULES&t;1
DECL|macro|QM_DEPS
mdefine_line|#define QM_DEPS&t;&t;2
DECL|macro|QM_REFS
mdefine_line|#define QM_REFS&t;&t;3
DECL|macro|QM_SYMBOLS
mdefine_line|#define QM_SYMBOLS&t;4
DECL|macro|QM_INFO
mdefine_line|#define QM_INFO&t;&t;5
multiline_comment|/* When struct module is extended, we must test whether the new member&n;   is present in the header received from insmod before we can use it.  &n;   This function returns true if the member is present.  */
DECL|macro|mod_member_present
mdefine_line|#define mod_member_present(mod,member) &t;&t;&t;&t;&t;&bslash;&n;&t;((unsigned long)(&amp;((struct module *)0L)-&gt;member + 1)&t;&t;&bslash;&n;&t; &lt;= (mod)-&gt;size_of_struct)
multiline_comment|/* Backwards compatibility definition.  */
DECL|macro|GET_USE_COUNT
mdefine_line|#define GET_USE_COUNT(module)&t;(atomic_read(&amp;(module)-&gt;uc.usecount))
multiline_comment|/* Poke the use count of a module.  */
DECL|macro|__MOD_INC_USE_COUNT
mdefine_line|#define __MOD_INC_USE_COUNT(mod)&t;&t;&t;&t;&t;&bslash;&n;&t;(atomic_inc(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED|MOD_USED_ONCE)
DECL|macro|__MOD_DEC_USE_COUNT
mdefine_line|#define __MOD_DEC_USE_COUNT(mod)&t;&t;&t;&t;&t;&bslash;&n;&t;(atomic_dec(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED)
DECL|macro|__MOD_IN_USE
mdefine_line|#define __MOD_IN_USE(mod)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(mod_member_present((mod), can_unload) &amp;&amp; (mod)-&gt;can_unload&t;&bslash;&n;&t; ? (mod)-&gt;can_unload() : atomic_read(&amp;(mod)-&gt;uc.usecount))
multiline_comment|/* Indirect stringification.  */
DECL|macro|__MODULE_STRING_1
mdefine_line|#define __MODULE_STRING_1(x)&t;#x
DECL|macro|__MODULE_STRING
mdefine_line|#define __MODULE_STRING(x)&t;__MODULE_STRING_1(x)
multiline_comment|/* Find a symbol exported by the kernel or another module */
r_extern
r_int
r_int
id|get_module_symbol
c_func
(paren
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#if defined(MODULE) &amp;&amp; !defined(__GENKSYMS__)
multiline_comment|/* Embedded module documentation macros.  */
multiline_comment|/* For documentation purposes only.  */
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(name)&t;&t;&t;&t;&t;&t;   &bslash;&n;const char __module_author[] __attribute__((section(&quot;.modinfo&quot;))) = &t;   &bslash;&n;&quot;author=&quot; name
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(desc)&t;&t;&t;&t;&t;   &bslash;&n;const char __module_description[] __attribute__((section(&quot;.modinfo&quot;))) =   &bslash;&n;&quot;description=&quot; desc
multiline_comment|/* Could potentially be used by kmod...  */
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(dev)&t;&t;&t;&t;&t;   &bslash;&n;const char __module_device[] __attribute__((section(&quot;.modinfo&quot;))) = &t;   &bslash;&n;&quot;device=&quot; dev
multiline_comment|/* Used to verify parameters given to the module.  The TYPE arg should&n;   be a string in the following format:&n;   &t;[min[-max]]{b,h,i,l,s}&n;   The MIN and MAX specifiers delimit the length of the array.  If MAX&n;   is omitted, it defaults to MIN; if both are omitted, the default is 1.&n;   The final character is a type specifier:&n;&t;b&t;byte&n;&t;h&t;short&n;&t;i&t;int&n;&t;l&t;long&n;&t;s&t;string&n;*/
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)&t;&t;&t;&bslash;&n;const char __module_parm_##var[]&t;&t;&bslash;&n;__attribute__((section(&quot;.modinfo&quot;))) =&t;&t;&bslash;&n;&quot;parm_&quot; __MODULE_STRING(var) &quot;=&quot; type
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(var,desc)&t;&t;&bslash;&n;const char __module_parm_desc_##var[]&t;&t;&bslash;&n;__attribute__((section(&quot;.modinfo&quot;))) =&t;&t;&bslash;&n;&quot;parm_desc_&quot; __MODULE_STRING(var) &quot;=&quot; desc
multiline_comment|/* The attributes of a section are set the first time the section is&n;   seen; we want .modinfo to not be allocated.  */
id|__asm__
c_func
(paren
l_string|&quot;.section .modinfo&bslash;n&bslash;t.previous&quot;
)paren
suffix:semicolon
multiline_comment|/* Define the module variable, and usage macros.  */
r_extern
r_struct
id|module
id|__this_module
suffix:semicolon
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE&t;&t;(&amp;__this_module)
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;__MOD_INC_USE_COUNT(THIS_MODULE)
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT&t;__MOD_DEC_USE_COUNT(THIS_MODULE)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;&t;__MOD_IN_USE(THIS_MODULE)
macro_line|#ifndef __NO_VERSION__
macro_line|#include &lt;linux/version.h&gt;
DECL|variable|__module_kernel_version
r_const
r_char
id|__module_kernel_version
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.modinfo&quot;
)paren
)paren
)paren
op_assign
l_string|&quot;kernel_version=&quot;
id|UTS_RELEASE
suffix:semicolon
macro_line|#ifdef MODVERSIONS
DECL|variable|__module_using_checksums
r_const
r_char
id|__module_using_checksums
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.modinfo&quot;
)paren
)paren
)paren
op_assign
l_string|&quot;using_checksums=1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#else /* MODULE */
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(name)
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(desc)
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(name)
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(var,type)
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(var,desc)
macro_line|#ifndef __GENKSYMS__
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE&t;&t;NULL
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT&t;do { } while (0)
DECL|macro|MOD_IN_USE
mdefine_line|#define MOD_IN_USE&t;&t;1
r_extern
r_struct
id|module
op_star
id|module_list
suffix:semicolon
macro_line|#endif /* !__GENKSYMS__ */
macro_line|#endif /* MODULE */
multiline_comment|/* Export a symbol either from the kernel or a module.&n;&n;   In the kernel, the symbol is added to the kernel&squot;s global symbol table.&n;&n;   In a module, it controls which variables are exported.  If no&n;   variables are explicitly exported, the action is controled by the&n;   insmod -[xX] flags.  Otherwise, only the variables listed are exported.&n;   This obviates the need for the old register_symtab() function.  */
macro_line|#if defined(__GENKSYMS__)
multiline_comment|/* We want the EXPORT_SYMBOL tag left intact for recognition.  */
macro_line|#elif !defined(AUTOCONF_INCLUDED)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)   error config_must_be_included_before_module
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)&t;   error config_must_be_included_before_module
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  error config_must_be_included_before_module
macro_line|#elif !defined(CONFIG_MODULES)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)
macro_line|#elif !defined(EXPORT_SYMTAB)
multiline_comment|/* If things weren&squot;t set up in the Makefiles to get EXPORT_SYMTAB defined,&n;   then they weren&squot;t set up to run genksyms properly so MODVERSIONS breaks.  */
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)   error EXPORT_SYMTAB_not_defined
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)&t;   error EXPORT_SYMTAB_not_defined
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  error EXPORT_SYMTAB_not_defined
macro_line|#else
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym, str)&t;&t;&t;&bslash;&n;const char __kstrtab_##sym[]&t;&t;&t;&t;&bslash;&n;__attribute__((section(&quot;.kstrtab&quot;))) = str;&t;&t;&bslash;&n;const struct module_symbol __ksymtab_##sym &t;&t;&bslash;&n;__attribute__((section(&quot;__ksymtab&quot;))) =&t;&t;&t;&bslash;&n;{ (unsigned long)&amp;sym, __kstrtab_##sym }
macro_line|#if defined(MODVERSIONS) || !defined(CONFIG_MODVERSIONS)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
macro_line|#else
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(__VERSIONED_SYMBOL(var)))
macro_line|#endif
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
macro_line|#endif /* __GENKSYMS__ */
macro_line|#ifdef MODULE
multiline_comment|/* Force a module to export no symbols.  */
DECL|macro|EXPORT_NO_SYMBOLS
mdefine_line|#define EXPORT_NO_SYMBOLS  __asm__(&quot;.section __ksymtab&bslash;n.previous&quot;)
macro_line|#else
DECL|macro|EXPORT_NO_SYMBOLS
mdefine_line|#define EXPORT_NO_SYMBOLS
macro_line|#endif /* MODULE */
macro_line|#endif /* _LINUX_MODULE_H */
eof
