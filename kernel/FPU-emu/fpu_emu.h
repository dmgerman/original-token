multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_emu.h                                                                |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_EMU_H_
DECL|macro|_FPU_EMU_H_
mdefine_line|#define _FPU_EMU_H_
multiline_comment|/*&n; * Define DENORM_OPERAND to make the emulator detect denormals&n; * and use the denormal flag of the status word. Note: this only&n; * affects the flag and corresponding interrupt, the emulator&n; * will always generate denormals and operate upon them as required.&n; */
DECL|macro|DENORM_OPERAND
mdefine_line|#define DENORM_OPERAND
multiline_comment|/*&n; * Define PECULIAR_486 to get a closer approximation to 80486 behaviour,&n; * rather than behaviour which appears to be cleaner.&n; * This is a matter of opinion: for all I know, the 80486 may simply&n; * be complying with the IEEE spec. Maybe one day I&squot;ll get to see the&n; * spec...&n; */
DECL|macro|PECULIAR_486
mdefine_line|#define PECULIAR_486
macro_line|#ifdef __ASSEMBLER__
macro_line|#include &quot;fpu_asm.h&quot;
DECL|macro|Const
mdefine_line|#define&t;Const(x)&t;$##x
macro_line|#else
DECL|macro|Const
mdefine_line|#define&t;Const(x)&t;x
macro_line|#endif
DECL|macro|EXP_BIAS
mdefine_line|#define EXP_BIAS&t;Const(0)
DECL|macro|EXP_OVER
mdefine_line|#define EXP_OVER&t;Const(0x4000)    /* smallest invalid large exponent */
DECL|macro|EXP_UNDER
mdefine_line|#define&t;EXP_UNDER&t;Const(-0x3fff)   /* largest invalid small exponent */
DECL|macro|SIGN_POS
mdefine_line|#define SIGN_POS&t;Const(0)
DECL|macro|SIGN_NEG
mdefine_line|#define SIGN_NEG&t;Const(1)
multiline_comment|/* Keep the order TW_Valid, TW_Zero, TW_Denormal */
DECL|macro|TW_Valid
mdefine_line|#define TW_Valid&t;Const(0)&t;/* valid */
DECL|macro|TW_Zero
mdefine_line|#define TW_Zero&t;&t;Const(1)&t;/* zero */
multiline_comment|/* The following fold to 2 (Special) in the Tag Word */
DECL|macro|TW_Denormal
mdefine_line|#define TW_Denormal     Const(4)        /* De-normal */
DECL|macro|TW_Infinity
mdefine_line|#define TW_Infinity&t;Const(5)&t;/* + or - infinity */
DECL|macro|TW_NaN
mdefine_line|#define&t;TW_NaN&t;&t;Const(6)&t;/* Not a Number */
DECL|macro|TW_Empty
mdefine_line|#define TW_Empty&t;Const(7)&t;/* empty */
multiline_comment|/* #define TW_FPU_Interrupt Const(0x80) */
multiline_comment|/* Signals an interrupt */
macro_line|#ifndef __ASSEMBLER__
macro_line|#include &lt;linux/math_emu.h&gt;
macro_line|#ifdef PARANOID
r_extern
r_char
id|emulating
suffix:semicolon
DECL|macro|RE_ENTRANT_CHECK_OFF
macro_line|#  define RE_ENTRANT_CHECK_OFF emulating = 0;
DECL|macro|RE_ENTRANT_CHECK_ON
macro_line|#  define RE_ENTRANT_CHECK_ON emulating = 1;
macro_line|#else
DECL|macro|RE_ENTRANT_CHECK_OFF
macro_line|#  define RE_ENTRANT_CHECK_OFF
DECL|macro|RE_ENTRANT_CHECK_ON
macro_line|#  define RE_ENTRANT_CHECK_ON
macro_line|#endif PARANOID
DECL|typedef|FUNC
r_typedef
r_void
(paren
op_star
id|FUNC
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|FPU_REG
r_typedef
r_struct
id|fpu_reg
id|FPU_REG
suffix:semicolon
DECL|macro|st
mdefine_line|#define&t;st(x)&t;( regs[((top+x) &amp;7 )] )
DECL|macro|STACK_OVERFLOW
mdefine_line|#define&t;STACK_OVERFLOW&t;(st_new_ptr = &amp;st(-1), st_new_ptr-&gt;tag != TW_Empty)
DECL|macro|NOT_EMPTY
mdefine_line|#define&t;NOT_EMPTY(i)&t;(st(i).tag != TW_Empty)
DECL|macro|NOT_EMPTY_0
mdefine_line|#define&t;NOT_EMPTY_0&t;(FPU_st0_tag ^ TW_Empty)
r_extern
r_int
r_char
id|FPU_rm
suffix:semicolon
r_extern
r_char
id|FPU_st0_tag
suffix:semicolon
r_extern
id|FPU_REG
op_star
id|FPU_st0_ptr
suffix:semicolon
r_extern
r_void
op_star
id|FPU_data_address
suffix:semicolon
r_extern
id|FPU_REG
id|FPU_loaded_data
suffix:semicolon
DECL|macro|pop
mdefine_line|#define pop()&t;{ FPU_st0_ptr-&gt;tag = TW_Empty; top++; }
multiline_comment|/* push() does not affect the tags */
DECL|macro|push
mdefine_line|#define push()&t;{ top--; FPU_st0_ptr = st_new_ptr; }
DECL|macro|reg_move
mdefine_line|#define reg_move(x, y) { &bslash;&n;&t;&t; *(short *)&amp;((y)-&gt;sign) = *(short *)&amp;((x)-&gt;sign); &bslash;&n;&t;&t; *(long *)&amp;((y)-&gt;exp) = *(long *)&amp;((x)-&gt;exp); &bslash;&n;&t;&t; *(long long *)&amp;((y)-&gt;sigl) = *(long long *)&amp;((x)-&gt;sigl); }
multiline_comment|/*----- Prototypes for functions written in assembler -----*/
multiline_comment|/* extern void reg_move(FPU_REG *a, FPU_REG *b); */
r_extern
r_void
id|mul64
c_func
(paren
r_int
r_int
op_star
id|a
comma
r_int
r_int
op_star
id|b
comma
r_int
r_int
op_star
id|result
)paren
suffix:semicolon
r_extern
r_void
id|poly_div2
c_func
(paren
r_int
r_int
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|poly_div4
c_func
(paren
r_int
r_int
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|poly_div16
c_func
(paren
r_int
r_int
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|polynomial
c_func
(paren
r_int
id|accum
(braket
)braket
comma
r_int
id|x
(braket
)braket
comma
r_int
r_int
id|terms
(braket
)braket
(braket
l_int|4
)braket
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|normalize
c_func
(paren
id|FPU_REG
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|normalize_nuo
c_func
(paren
id|FPU_REG
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|reg_div
c_func
(paren
id|FPU_REG
op_star
id|arg1
comma
id|FPU_REG
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_void
id|reg_u_sub
c_func
(paren
id|FPU_REG
op_star
id|arg1
comma
id|FPU_REG
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_void
id|reg_u_mul
c_func
(paren
id|FPU_REG
op_star
id|arg1
comma
id|FPU_REG
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_void
id|reg_u_div
c_func
(paren
id|FPU_REG
op_star
id|arg1
comma
id|FPU_REG
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_void
id|reg_u_add
c_func
(paren
id|FPU_REG
op_star
id|arg1
comma
id|FPU_REG
op_star
id|arg2
comma
id|FPU_REG
op_star
id|answ
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_void
id|wm_sqrt
c_func
(paren
id|FPU_REG
op_star
id|n
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
r_extern
r_int
id|shrx
c_func
(paren
r_void
op_star
id|l
comma
r_int
id|x
)paren
suffix:semicolon
r_extern
r_int
id|shrxs
c_func
(paren
r_void
op_star
id|v
comma
r_int
id|x
)paren
suffix:semicolon
r_extern
r_int
r_int
id|div_small
c_func
(paren
r_int
r_int
r_int
op_star
id|x
comma
r_int
r_int
id|y
)paren
suffix:semicolon
r_extern
r_void
id|round_reg
c_func
(paren
id|FPU_REG
op_star
id|arg
comma
r_int
r_int
id|extent
comma
r_int
r_int
id|control_w
)paren
suffix:semicolon
macro_line|#ifndef MAKING_PROTO
macro_line|#include &quot;fpu_proto.h&quot;
macro_line|#endif
macro_line|#endif __ASSEMBLER__
macro_line|#endif _FPU_EMU_H_
eof
