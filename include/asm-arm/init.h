macro_line|#ifndef _ASMARM_INIT_H
DECL|macro|_ASMARM_INIT_H
mdefine_line|#define _ASMARM_INIT_H
macro_line|#if 0
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
multiline_comment|/* For assembly routines */
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,@alloc,@execinstr
mdefine_line|#define __FINIT&t;.previous
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,@alloc,@write
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
macro_line|#endif
eof
