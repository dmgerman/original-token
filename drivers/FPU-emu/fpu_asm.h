multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_asm.h                                                                |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_ASM_H_
DECL|macro|_FPU_ASM_H_
mdefine_line|#define _FPU_ASM_H_
macro_line|#include &quot;fpu_emu.h&quot;
DECL|macro|EXCEPTION
mdefine_line|#define&t;EXCEPTION&t;_exception
DECL|macro|PARAM1
mdefine_line|#define PARAM1&t;8(%ebp)
DECL|macro|PARAM2
mdefine_line|#define&t;PARAM2&t;12(%ebp)
DECL|macro|PARAM3
mdefine_line|#define&t;PARAM3&t;16(%ebp)
DECL|macro|PARAM4
mdefine_line|#define&t;PARAM4&t;20(%ebp)
DECL|macro|SIGL_OFFSET
mdefine_line|#define SIGL_OFFSET 8
DECL|macro|SIGN
mdefine_line|#define SIGN(x)&t;(x)
DECL|macro|TAG
mdefine_line|#define&t;TAG(x)&t;1(x)
DECL|macro|EXP
mdefine_line|#define&t;EXP(x)&t;4(x)
DECL|macro|SIG
mdefine_line|#define SIG(x)&t;SIGL_OFFSET##(x)
DECL|macro|SIGL
mdefine_line|#define&t;SIGL(x)&t;SIGL_OFFSET##(x)
DECL|macro|SIGH
mdefine_line|#define&t;SIGH(x)&t;12(x)
macro_line|#endif _FPU_ASM_H_
eof
