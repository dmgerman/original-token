multiline_comment|/* $Id: init.h,v 1.3 1999/02/15 02:22:10 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright 1998, 1999 Ralf Baechle&n; */
macro_line|#ifndef __MIPS_INIT_H
DECL|macro|__MIPS_INIT_H
mdefine_line|#define __MIPS_INIT_H
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
macro_line|#if __GNUC__ &gt;= 2 &amp;&amp; __GNUC_MINOR__ &gt;= 8
DECL|macro|__initlocaldata
mdefine_line|#define __initlocaldata  __initdata
macro_line|#else
DECL|macro|__initlocaldata
mdefine_line|#define __initlocaldata
macro_line|#endif
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;.text.init,&quot;ax&quot;
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;.data.init,&quot;a&quot;
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
macro_line|#endif /* __MIPS_INIT_H */
eof
