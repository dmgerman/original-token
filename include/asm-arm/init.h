macro_line|#ifndef _ASMARM_INIT_H
DECL|macro|_ASMARM_INIT_H
mdefine_line|#define _ASMARM_INIT_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* C routines */
macro_line|#ifdef CONFIG_TEXT_SECTIONS
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) __arginit
macro_line|#endif
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
multiline_comment|/* Assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,@alloc,@execinstr
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,@alloc,@write
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;.previous
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ &bslash;&n;&t;&t;&t; ((__aligned__ (L1_CACHE_BYTES)))
macro_line|#endif
eof
