macro_line|#ifndef _PPC_INIT_H
DECL|macro|_PPC_INIT_H
mdefine_line|#define _PPC_INIT_H
macro_line|#if __GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 90 /* egcs */
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__pmac
mdefine_line|#define __pmac __attribute__ ((__section__ (&quot;.text.pmac&quot;)))
DECL|macro|__pmacdata
mdefine_line|#define __pmacdata __attribute__ ((__section__ (&quot;.data.pmac&quot;)))
DECL|macro|__pmacfunc
mdefine_line|#define __pmacfunc(__argpmac) &bslash;&n;&t;__argpmac __pmac; &bslash;&n;&t;__argpmac
DECL|macro|__prep
mdefine_line|#define __prep __attribute__ ((__section__ (&quot;.text.prep&quot;)))
DECL|macro|__prepdata
mdefine_line|#define __prepdata __attribute__ ((__section__ (&quot;.data.prep&quot;)))
DECL|macro|__prepfunc
mdefine_line|#define __prepfunc(__argprep) &bslash;&n;&t;__argprep __prep; &bslash;&n;&t;__argprep
multiline_comment|/* this is actually just common chrp/pmac code, not OF code -- Cort */
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware __attribute__ ((__section__ (&quot;.text.openfirmware&quot;)))
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata __attribute__ ((__section__ (&quot;.data.openfirmware&quot;)))
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(__argopenfirmware) &bslash;&n;&t;__argopenfirmware __openfirmware; &bslash;&n;&t;__argopenfirmware
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;&quot;.text.init&quot;,#alloc,#execinstr
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;&quot;.data.init&quot;,#alloc,#write
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ &bslash;&n;&t;&t;&t; ((__section__ (&quot;.data.cacheline_aligned&quot;)))
macro_line|#else /* not egcs */
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__INIT
mdefine_line|#define __INIT
DECL|macro|__FINIT
mdefine_line|#define __FINIT
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA
DECL|macro|__pmac
mdefine_line|#define __pmac
DECL|macro|__pmacdata
mdefine_line|#define __pmacdata
DECL|macro|__pmacfunc
mdefine_line|#define __pmacfunc(x) x
DECL|macro|__prep
mdefine_line|#define __prep
DECL|macro|__prepdata
mdefine_line|#define __prepdata
DECL|macro|__prepfunc
mdefine_line|#define __prepfunc(x) x
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(x) x
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned
macro_line|#endif /* egcs */
macro_line|#endif
eof
