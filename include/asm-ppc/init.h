macro_line|#ifndef _PPC_INIT_H
DECL|macro|_PPC_INIT_H
mdefine_line|#define _PPC_INIT_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#if 0/*__GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 90*/ /* egcs */
mdefine_line|#define __pmacdata __attribute__ ((__section__ (&quot;.data.pmac&quot;)))
mdefine_line|#define __pmacfunc(__argpmac) &bslash;&n;&t;__argpmac __pmac; &bslash;&n;&t;__argpmac
mdefine_line|#define __prep __attribute__ ((__section__ (&quot;.text.prep&quot;)))
mdefine_line|#define __prepdata /* __attribute__ ((__section__ (&quot;.data.prep&quot;)))*/
mdefine_line|#define __prepfunc(__argprep) &bslash;&n;&t;__argprep __prep; &bslash;&n;&t;__argprep
mdefine_line|#define __apus __attribute__ ((__section__ (&quot;.text.apus&quot;)))
mdefine_line|#define __apusdata __attribute__ ((__section__ (&quot;.data.apus&quot;)))
mdefine_line|#define __apusfunc(__argapus) &bslash;&n;&t;__argapus __apus; &bslash;&n;&t;__argapus
multiline_comment|/* this is actually just common chrp/pmac code, not OF code -- Cort */
mdefine_line|#define __openfirmware __attribute__ ((__section__ (&quot;.text.openfirmware&quot;)))
mdefine_line|#define __openfirmwaredata __attribute__ ((__section__ (&quot;.data.openfirmware&quot;)))
mdefine_line|#define __openfirmwarefunc(__argopenfirmware) &bslash;&n;&t;__argopenfirmware __openfirmware; &bslash;&n;&t;__argopenfirmware
macro_line|#else /* not egcs */
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
DECL|macro|__apus
mdefine_line|#define __apus
DECL|macro|__apusdata
mdefine_line|#define __apusdata
DECL|macro|__apusfunc
mdefine_line|#define __apusfunc(x) x
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(x) x
macro_line|#endif /* egcs */
macro_line|#endif /* _PPC_INIT_H */
eof
