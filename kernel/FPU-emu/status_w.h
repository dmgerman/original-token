multiline_comment|/*---------------------------------------------------------------------------+&n; |  status_w.h                                                               |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _STATUS_H_
DECL|macro|_STATUS_H_
mdefine_line|#define _STATUS_H_
macro_line|#ifdef __ASSEMBLER__
DECL|macro|Const__
mdefine_line|#define&t;Const__(x)&t;$##x
macro_line|#else
DECL|macro|Const__
mdefine_line|#define&t;Const__(x)&t;x
macro_line|#endif
DECL|macro|SW_B
mdefine_line|#define SW_B&t;&t;Const__(0x8000)&t;/* backward compatibility (=ES) */
DECL|macro|SW_C3
mdefine_line|#define SW_C3&t;&t;Const__(0x4000)&t;/* condition bit 3 */
DECL|macro|SW_TOP
mdefine_line|#define SW_TOP&t;&t;Const__(0x3800)&t;/* top of stack */
DECL|macro|SW_TOPS
mdefine_line|#define SW_TOPS &t;Const__(11)&t;/* shift for top of stack bits */
DECL|macro|SW_C2
mdefine_line|#define SW_C2&t;&t;Const__(0x0400)&t;/* condition bit 2 */
DECL|macro|SW_C1
mdefine_line|#define SW_C1&t;&t;Const__(0x0200)&t;/* condition bit 1 */
DECL|macro|SW_C0
mdefine_line|#define SW_C0&t;&t;Const__(0x0100)&t;/* condition bit 0 */
DECL|macro|SW_ES
mdefine_line|#define SW_ES&t;&t;Const__(0x0080)&t;/* exception summary */
DECL|macro|SW_SF
mdefine_line|#define SW_SF&t;&t;Const__(0x0040)&t;/* stack fault */
DECL|macro|SW_PE
mdefine_line|#define SW_PE&t;&t;Const__(0x0020)&t;/* loss of precision */
DECL|macro|SW_UE
mdefine_line|#define SW_UE&t;&t;Const__(0x0010)&t;/* underflow */
DECL|macro|SW_OE
mdefine_line|#define SW_OE&t;&t;Const__(0x0008)&t;/* overflow */
DECL|macro|SW_ZE
mdefine_line|#define SW_ZE&t;&t;Const__(0x0004)&t;/* divide by zero */
DECL|macro|SW_DE
mdefine_line|#define SW_DE&t;&t;Const__(0x0002)&t;/* denormalized operand */
DECL|macro|SW_IE
mdefine_line|#define SW_IE&t;&t;Const__(0x0001)&t;/* invalid operation */
macro_line|#ifndef __ASSEMBLER__
DECL|macro|COMP_A_GT_B
mdefine_line|#define COMP_A_GT_B&t;1
DECL|macro|COMP_A_EQ_B
mdefine_line|#define COMP_A_EQ_B&t;2
DECL|macro|COMP_A_LT_B
mdefine_line|#define COMP_A_LT_B&t;3
DECL|macro|COMP_NOCOMP
mdefine_line|#define COMP_NOCOMP&t;4
DECL|macro|COMP_NAN
mdefine_line|#define COMP_NAN&t;0x40
DECL|macro|COMP_SNAN
mdefine_line|#define COMP_SNAN&t;0x80
DECL|macro|setcc
mdefine_line|#define setcc(cc) ({ &bslash;&n;  status_word &amp;= ~(SW_C0|SW_C1|SW_C2|SW_C3); &bslash;&n;  status_word |= (cc) &amp; (SW_C0|SW_C1|SW_C2|SW_C3); })
macro_line|#endif __ASSEMBLER__
macro_line|#endif _STATUS_H_
eof
