macro_line|#ifndef _LINUX_INIT_H
DECL|macro|_LINUX_INIT_H
mdefine_line|#define _LINUX_INIT_H
multiline_comment|/* These macros are used to mark some functions or &n; * initialized data (doesn&squot;t apply to uninitialized data)&n; * as `initialization&squot; functions. The kernel can take this&n; * as hint that the function is used only during the initialization&n; * phase and free up used memory resources after&n; *&n; * Usage:&n; * For functions:&n; * you can surround the whole function declaration &n; * just before function body into __initfunc() macro, like:&n; *&n; * __initfunc (static void initme(int x, int y))&n; * {&n; *    extern int z; z = x * y;&n; * }&n; *&n; * if the function has a prototype somewhere, you can also add&n; * __init between closing brace of the prototype and semicolon:&n; *&n; * extern int initialize_foobar_device(int, int, int) __init;&n; *&n; * For initialized data:&n; * you should insert __initdata between the variable name and equal&n; * sign followed by value, e.g.:&n; *&n; * static int init_variable __initdata = 0;&n; * static char linux_logo[] __initdata = { 0x32, 0x36, ... };&n; */
macro_line|#ifndef __init
macro_line|#if (defined (__svr4__) || defined (__ELF__)) &amp;&amp; !defined (MODULE)
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,#alloc,#execinstr
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,#alloc,#write
macro_line|#else
DECL|macro|__init
mdefine_line|#define&t;__init
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
macro_line|#endif
macro_line|#endif
eof
