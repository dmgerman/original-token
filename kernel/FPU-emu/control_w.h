multiline_comment|/*---------------------------------------------------------------------------+&n; |  control_w.h                                                              |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _CONTROLW_H_
DECL|macro|_CONTROLW_H_
mdefine_line|#define _CONTROLW_H_
macro_line|#ifdef __ASSEMBLER__
DECL|macro|_Const_
mdefine_line|#define&t;_Const_(x)&t;$##x
macro_line|#else
DECL|macro|_Const_
mdefine_line|#define&t;_Const_(x)&t;x
macro_line|#endif
DECL|macro|CW_RC
mdefine_line|#define CW_RC&t;&t;_Const_(0x0C00)&t;/* rounding control */
DECL|macro|CW_PC
mdefine_line|#define CW_PC&t;&t;_Const_(0x0300)&t;/* precision control */
DECL|macro|CW_PM
mdefine_line|#define CW_PM&t;&t;_Const_(0x0020)&t;/* precision mask */
DECL|macro|CW_UM
mdefine_line|#define CW_UM&t;&t;_Const_(0x0010)&t;/* underflow mask */
DECL|macro|CW_OM
mdefine_line|#define CW_OM&t;&t;_Const_(0x0008)&t;/* overflow mask */
DECL|macro|CW_ZM
mdefine_line|#define CW_ZM&t;&t;_Const_(0x0004)&t;/* divide by zero mask */
DECL|macro|CW_DM
mdefine_line|#define CW_DM&t;&t;_Const_(0x0002)&t;/* denormalized operand mask */
DECL|macro|CW_IM
mdefine_line|#define CW_IM&t;&t;_Const_(0x0001)&t;/* invalid operation mask */
DECL|macro|CW_EXM
mdefine_line|#define CW_EXM&t;&t;_Const_(0x007f)&t;/* all masks */
DECL|macro|RC_RND
mdefine_line|#define RC_RND&t;&t;_Const_(0x0000)
DECL|macro|RC_DOWN
mdefine_line|#define RC_DOWN&t;&t;_Const_(0x0400)
DECL|macro|RC_UP
mdefine_line|#define RC_UP&t;&t;_Const_(0x0800)
DECL|macro|RC_CHOP
mdefine_line|#define RC_CHOP&t;&t;_Const_(0x0C00)
multiline_comment|/* p 15-5: Precision control bits affect only the following:&n;   ADD, SUB(R), MUL, DIV(R), and SQRT */
DECL|macro|FULL_PRECISION
mdefine_line|#define FULL_PRECISION  (CW_PC | RC_RND)
DECL|macro|PR_24_BITS
mdefine_line|#define PR_24_BITS      _Const_(0x000)
DECL|macro|PR_53_BITS
mdefine_line|#define PR_53_BITS      _Const_(0x200)
DECL|macro|PR_64_BITS
mdefine_line|#define PR_64_BITS      _Const_(0x300)
macro_line|#endif _CONTROLW_H_
eof
