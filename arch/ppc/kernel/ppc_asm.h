multiline_comment|/*&n; * arch/ppc/kernel/ppc_asm.h&n; *&n; * Definitions used by various bits of low-level assembly code on PowerPC.&n; *&n; * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ppc_asm.tmpl&quot;
macro_line|#include &quot;ppc_defs.h&quot;
multiline_comment|/*&n; * Macros for storing registers into and loading registers from&n; * exception frames.&n; */
DECL|macro|SAVE_GPR
mdefine_line|#define SAVE_GPR(n, base)&t;stw&t;n,GPR0+4*(n)(base)
DECL|macro|SAVE_2GPRS
mdefine_line|#define SAVE_2GPRS(n, base)&t;SAVE_GPR(n, base); SAVE_GPR(n+1, base)
DECL|macro|SAVE_4GPRS
mdefine_line|#define SAVE_4GPRS(n, base)&t;SAVE_2GPRS(n, base); SAVE_2GPRS(n+2, base)
DECL|macro|SAVE_8GPRS
mdefine_line|#define SAVE_8GPRS(n, base)&t;SAVE_4GPRS(n, base); SAVE_4GPRS(n+4, base)
DECL|macro|SAVE_10GPRS
mdefine_line|#define SAVE_10GPRS(n, base)&t;SAVE_8GPRS(n, base); SAVE_2GPRS(n+8, base)
DECL|macro|REST_GPR
mdefine_line|#define REST_GPR(n, base)&t;lwz&t;n,GPR0+4*(n)(base)
DECL|macro|REST_2GPRS
mdefine_line|#define REST_2GPRS(n, base)&t;REST_GPR(n, base); REST_GPR(n+1, base)
DECL|macro|REST_4GPRS
mdefine_line|#define REST_4GPRS(n, base)&t;REST_2GPRS(n, base); REST_2GPRS(n+2, base)
DECL|macro|REST_8GPRS
mdefine_line|#define REST_8GPRS(n, base)&t;REST_4GPRS(n, base); REST_4GPRS(n+4, base)
DECL|macro|REST_10GPRS
mdefine_line|#define REST_10GPRS(n, base)&t;REST_8GPRS(n, base); REST_2GPRS(n+8, base)
DECL|macro|SAVE_FPR
mdefine_line|#define SAVE_FPR(n, base)&t;stfd&t;n,THREAD_FPR0+8*(n)(base)
DECL|macro|SAVE_2FPRS
mdefine_line|#define SAVE_2FPRS(n, base)&t;SAVE_FPR(n, base); SAVE_FPR(n+1, base)
DECL|macro|SAVE_4FPRS
mdefine_line|#define SAVE_4FPRS(n, base)&t;SAVE_2FPRS(n, base); SAVE_2FPRS(n+2, base)
DECL|macro|SAVE_8FPRS
mdefine_line|#define SAVE_8FPRS(n, base)&t;SAVE_4FPRS(n, base); SAVE_4FPRS(n+4, base)
DECL|macro|SAVE_16FPRS
mdefine_line|#define SAVE_16FPRS(n, base)&t;SAVE_8FPRS(n, base); SAVE_8FPRS(n+8, base)
DECL|macro|SAVE_32FPRS
mdefine_line|#define SAVE_32FPRS(n, base)&t;SAVE_16FPRS(n, base); SAVE_16FPRS(n+16, base)
DECL|macro|REST_FPR
mdefine_line|#define REST_FPR(n, base)&t;lfd&t;n,THREAD_FPR0+8*(n)(base)
DECL|macro|REST_2FPRS
mdefine_line|#define REST_2FPRS(n, base)&t;REST_FPR(n, base); REST_FPR(n+1, base)
DECL|macro|REST_4FPRS
mdefine_line|#define REST_4FPRS(n, base)&t;REST_2FPRS(n, base); REST_2FPRS(n+2, base)
DECL|macro|REST_8FPRS
mdefine_line|#define REST_8FPRS(n, base)&t;REST_4FPRS(n, base); REST_4FPRS(n+4, base)
DECL|macro|REST_16FPRS
mdefine_line|#define REST_16FPRS(n, base)&t;REST_8FPRS(n, base); REST_8FPRS(n+8, base)
DECL|macro|REST_32FPRS
mdefine_line|#define REST_32FPRS(n, base)&t;REST_16FPRS(n, base); REST_16FPRS(n+16, base)
DECL|macro|SYNC
mdefine_line|#define SYNC &bslash;&n;&t;sync; &bslash;&n;&t;isync
multiline_comment|/*&n; * This instruction is not implemented on the PPC 603 or 601; however, on&n; * the 403GCX and 405GP tlbia IS defined and tlbie is not.&n; */
macro_line|#if !defined(CONFIG_4xx)
DECL|macro|tlbia
mdefine_line|#define tlbia&t;&t;&t;&t;&t;&bslash;&n;&t;li&t;r4,128;&t;&t;&t;&t;&bslash;&n;&t;mtctr&t;r4;&t;&t;&t;&t;&bslash;&n;&t;lis&t;r4,KERNELBASE@h;&t;&t;&bslash;&n;0:&t;tlbie&t;r4;&t;&t;&t;&t;&bslash;&n;&t;addi&t;r4,r4,0x1000;&t;&t;&t;&bslash;&n;&t;bdnz&t;0b
macro_line|#endif
multiline_comment|/*&n; * On APUS (Amiga PowerPC cpu upgrade board), we don&squot;t know the&n; * physical base address of RAM at compile time.&n; */
DECL|macro|tophys
mdefine_line|#define tophys(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,-KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.vtop_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
DECL|macro|tovirt
mdefine_line|#define tovirt(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.ptov_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
eof
