macro_line|#ifndef _M68K_INIT_H
DECL|macro|_M68K_INIT_H
mdefine_line|#define _M68K_INIT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_KGDB
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,#alloc,#execinstr
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,#alloc,#write
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ &bslash;&n;&t;&t;((__aligned__(16), __section__ (&quot;.data.cacheline_aligned&quot;)))
macro_line|#else
multiline_comment|/* gdb doesn&squot;t like it all if the code for one source file isn&squot;t together in&n; * the executable, so we must avoid the .init sections :-( */
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT
DECL|macro|__FINIT
mdefine_line|#define __FINIT
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ ((__aligned__(16)))
macro_line|#endif /* CONFIG_KGDB */
macro_line|#endif
eof
