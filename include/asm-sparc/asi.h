macro_line|#ifndef _SPARC_ASI_H
DECL|macro|_SPARC_ASI_H
mdefine_line|#define _SPARC_ASI_H
multiline_comment|/* asi.h:  Address Space Identifier values for the sparc.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
multiline_comment|/* These are sun4c, beware on other architectures. Although things should&n; * be similar under regular sun4&squot;s.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SUN4M
macro_line|#include &quot;asi4m.h&quot;
macro_line|#else
DECL|macro|ASI_NULL1
mdefine_line|#define ASI_NULL1        0x0
DECL|macro|ASI_NULL2
mdefine_line|#define ASI_NULL2        0x1
multiline_comment|/* sun4c and sun4 control registers and mmu/vac ops */
DECL|macro|ASI_CONTROL
mdefine_line|#define ASI_CONTROL          0x2
DECL|macro|ASI_SEGMAP
mdefine_line|#define ASI_SEGMAP           0x3
DECL|macro|ASI_PTE
mdefine_line|#define ASI_PTE              0x4
DECL|macro|ASI_HWFLUSHSEG
mdefine_line|#define ASI_HWFLUSHSEG       0x5      /* These are to initiate hw flushes of the cache */
DECL|macro|ASI_HWFLUSHPAGE
mdefine_line|#define ASI_HWFLUSHPAGE      0x6
DECL|macro|ASI_HWFLUSHCONTEXT
mdefine_line|#define ASI_HWFLUSHCONTEXT   0x7
DECL|macro|ASI_USERTXT
mdefine_line|#define ASI_USERTXT      0x8
DECL|macro|ASI_KERNELTXT
mdefine_line|#define ASI_KERNELTXT    0x9
DECL|macro|ASI_USERDATA
mdefine_line|#define ASI_USERDATA     0xa
DECL|macro|ASI_KERNELDATA
mdefine_line|#define ASI_KERNELDATA   0xb
multiline_comment|/* VAC Cache flushing on sun4c and sun4 */
DECL|macro|ASI_FLUSHSEG
mdefine_line|#define ASI_FLUSHSEG     0xc      /* These are for &quot;software&quot; flushes of the cache */
DECL|macro|ASI_FLUSHPG
mdefine_line|#define ASI_FLUSHPG      0xd
DECL|macro|ASI_FLUSHCTX
mdefine_line|#define ASI_FLUSHCTX     0xe
macro_line|#endif /* CONFIG_SUN4M */
macro_line|#endif /* _SPARC_ASI_H */
eof
