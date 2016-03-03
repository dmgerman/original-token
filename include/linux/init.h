macro_line|#ifndef _LINUX_INIT_H
DECL|macro|_LINUX_INIT_H
mdefine_line|#define _LINUX_INIT_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* These macros are used to mark some functions or &n; * initialized data (doesn&squot;t apply to uninitialized data)&n; * as `initialization&squot; functions. The kernel can take this&n; * as hint that the function is used only during the initialization&n; * phase and free up used memory resources after&n; *&n; * Usage:&n; * For functions:&n; * &n; * You should add __init immediately before the function name, like:&n; *&n; * static void __init initme(int x, int y)&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * If the function has a prototype somewhere, you can also add&n; * __init between closing brace of the prototype and semicolon:&n; *&n; * extern int initialize_foobar_device(int, int, int) __init;&n; *&n; * For initialized data:&n; * You should insert __initdata between the variable name and equal&n; * sign followed by value, e.g.:&n; *&n; * static int init_variable __initdata = 0;&n; * static char linux_logo[] __initdata = { 0x32, 0x36, ... };&n; *&n; * Don&squot;t forget to initialize data not at file scope, i.e. within a function,&n; * as gcc otherwise puts the data into the bss section and not into the init&n; * section.&n; */
macro_line|#ifndef MODULE
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Used for initialization calls..&n; */
DECL|typedef|initcall_t
r_typedef
r_int
(paren
op_star
id|initcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|exitcall_t
r_typedef
r_void
(paren
op_star
id|exitcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|initcall_t
id|__initcall_start
comma
id|__initcall_end
suffix:semicolon
DECL|macro|__initcall
mdefine_line|#define __initcall(fn)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static initcall_t __initcall_##fn __init_call = fn
DECL|macro|__exitcall
mdefine_line|#define __exitcall(fn)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static exitcall_t __exitcall_##fn __exit_call = fn
multiline_comment|/*&n; * Used for kernel command line parameter setup&n; */
DECL|struct|kernel_param
r_struct
id|kernel_param
(brace
DECL|member|str
r_const
r_char
op_star
id|str
suffix:semicolon
DECL|member|setup_func
r_int
(paren
op_star
id|setup_func
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|kernel_param
id|__setup_start
comma
id|__setup_end
suffix:semicolon
DECL|macro|__setup
mdefine_line|#define __setup(str, fn)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static char __setup_str_##fn[] __initdata = str;&t;&t;&t;&t;&bslash;&n;&t;static struct kernel_param __setup_##fn __attribute__((unused)) __initsetup = { __setup_str_##fn, fn }
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Mark functions and data as being only used at initialization&n; * or exit time.&n; */
DECL|macro|__init
mdefine_line|#define __init&t;&t;__attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__exit
mdefine_line|#define __exit&t;&t;__attribute__ ((unused, __section__(&quot;.text.exit&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata&t;__attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__exitdata
mdefine_line|#define __exitdata&t;__attribute__ ((unused, __section__ (&quot;.data.exit&quot;)))
DECL|macro|__initsetup
mdefine_line|#define __initsetup&t;__attribute__ ((unused,__section__ (&quot;.setup.init&quot;)))
DECL|macro|__init_call
mdefine_line|#define __init_call&t;__attribute__ ((unused,__section__ (&quot;.initcall.init&quot;)))
DECL|macro|__exit_call
mdefine_line|#define __exit_call&t;__attribute__ ((unused,__section__ (&quot;.exitcall.exit&quot;)))
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,&quot;ax&quot;
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,&quot;aw&quot;
DECL|macro|module_init
mdefine_line|#define module_init(x)&t;__initcall(x);
DECL|macro|module_exit
mdefine_line|#define module_exit(x)&t;__exitcall(x);
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__exit
mdefine_line|#define __exit
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__exitdata
mdefine_line|#define __exitdata
DECL|macro|__initcall
mdefine_line|#define __initcall(fn)
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT
DECL|macro|__FINIT
mdefine_line|#define __FINIT
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA
multiline_comment|/* These macros create a dummy inline: gcc 2.9x does not count alias&n; as usage, hence the `unused function&squot; warning when __init functions&n; are declared static. We use the dummy __*_module_inline functions&n; both to kill the warning and check the type of the init/cleanup&n; function. */
DECL|typedef|__init_module_func_t
r_typedef
r_int
(paren
op_star
id|__init_module_func_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|__cleanup_module_func_t
r_typedef
r_void
(paren
op_star
id|__cleanup_module_func_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|macro|module_init
mdefine_line|#define module_init(x) &bslash;&n;&t;int init_module(void) __attribute__((alias(#x))); &bslash;&n;&t;extern inline __init_module_func_t __init_module_inline(void) &bslash;&n;&t;{ return x; }
DECL|macro|module_exit
mdefine_line|#define module_exit(x) &bslash;&n;&t;void cleanup_module(void) __attribute__((alias(#x))); &bslash;&n;&t;extern inline __cleanup_module_func_t __cleanup_module_inline(void) &bslash;&n;&t;{ return x; }
DECL|macro|__setup
mdefine_line|#define __setup(str,func) /* nothing */
macro_line|#endif
macro_line|#ifdef CONFIG_HOTPLUG
DECL|macro|__devinit
mdefine_line|#define __devinit
DECL|macro|__devinitdata
mdefine_line|#define __devinitdata
DECL|macro|__devexit
mdefine_line|#define __devexit
DECL|macro|__devexitdata
mdefine_line|#define __devexitdata
macro_line|#else
DECL|macro|__devinit
mdefine_line|#define __devinit __init
DECL|macro|__devinitdata
mdefine_line|#define __devinitdata __initdata
DECL|macro|__devexit
mdefine_line|#define __devexit __exit
DECL|macro|__devexitdata
mdefine_line|#define __devexitdata __exitdata
macro_line|#endif
macro_line|#endif /* _LINUX_INIT_H */
eof
