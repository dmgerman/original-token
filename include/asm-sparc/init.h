macro_line|#ifndef _SPARC_INIT_H
DECL|macro|_SPARC_INIT_H
mdefine_line|#define _SPARC_INIT_H
macro_line|#if (defined (__svr4__) || defined (__ELF__))
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ &bslash;&n;&t;&t;&t;((__section__ (&quot;.data.cacheline_aligned&quot;)))
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
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned
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
