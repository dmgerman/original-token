macro_line|#ifndef _LINUX_INIT_H
DECL|macro|_LINUX_INIT_H
mdefine_line|#define _LINUX_INIT_H
multiline_comment|/* These macros are used to mark some functions or &n; * initialized data (doesn&squot;t apply to uninitialized data)&n; * as `initialization&squot; functions. The kernel can take this&n; * as hint that the function is used only during the initialization&n; * phase and free up used memory resources after&n; *&n; * Usage:&n; * For functions:&n; * &n; * You should add __init immediately before the function name, like:&n; *&n; * static void __init initme(int x, int y)&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * Depricated: you can surround the whole function declaration &n; * just before function body into __initfunc() macro, like:&n; *&n; * __initfunc (static void initme(int x, int y))&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * If the function has a prototype somewhere, you can also add&n; * __init between closing brace of the prototype and semicolon:&n; *&n; * extern int initialize_foobar_device(int, int, int) __init;&n; *&n; * For initialized data:&n; * You should insert __initdata between the variable name and equal&n; * sign followed by value, e.g.:&n; *&n; * static int init_variable __initdata = 0;&n; * static char linux_logo[] __initdata = { 0x32, 0x36, ... };&n; *&n; * For initialized data not at file scope, i.e. within a function,&n; * you should use __initlocaldata instead, due to a bug in GCC 2.7.&n; */
multiline_comment|/*&n; * Disable the __initfunc macros if a file that is a part of a&n; * module attempts to use them. We do not want to interfere&n; * with module linking.&n; */
macro_line|#ifndef MODULE
macro_line|#include &lt;asm/init.h&gt;
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) __arginit
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT
DECL|macro|__FINIT
mdefine_line|#define __FINIT
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA
macro_line|#endif
macro_line|#if __GNUC__ &gt;= 2 &amp;&amp; __GNUC_MINOR__ &gt;= 8
DECL|macro|__initlocaldata
mdefine_line|#define __initlocaldata  __initdata
macro_line|#else
DECL|macro|__initlocaldata
mdefine_line|#define __initlocaldata
macro_line|#endif
macro_line|#endif
eof
