macro_line|#ifndef _PPC_INIT_H
DECL|macro|_PPC_INIT_H
mdefine_line|#define _PPC_INIT_H
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(x) x
multiline_comment|/*&n;#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))&n;#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))&n;#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit&n;*/
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT
DECL|macro|__FINIT
mdefine_line|#define __FINIT
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA
multiline_comment|/*&t;&n;#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,#alloc,#execinstr&n;#define __FINIT&t;.previous&n;#define __INITDATA&t;.section&t;&quot;.data.init&quot;,#alloc,#write&n;*/
macro_line|#endif
eof
