multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_arith.c                                                              |&n; |                                                                           |&n; | Code to implement the FPU register/register arithmetic instructions       |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;control_w.h&quot;
macro_line|#include &quot;status_w.h&quot;
DECL|function|fadd__
r_void
id|fadd__
c_func
(paren
)paren
(brace
multiline_comment|/* fadd st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_add
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fmul__
r_void
id|fmul__
c_func
(paren
)paren
(brace
multiline_comment|/* fmul st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_mul
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fsub__
r_void
id|fsub__
c_func
(paren
)paren
(brace
multiline_comment|/* fsub st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_sub
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fsubr_
r_void
id|fsubr_
c_func
(paren
)paren
(brace
multiline_comment|/* fsubr st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_sub
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fdiv__
r_void
id|fdiv__
c_func
(paren
)paren
(brace
multiline_comment|/* fdiv st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_div
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fdivr_
r_void
id|fdivr_
c_func
(paren
)paren
(brace
multiline_comment|/* fdivr st,st(i) */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_div
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
id|FPU_st0_ptr
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fadd_i
r_void
id|fadd_i
c_func
(paren
)paren
(brace
multiline_comment|/* fadd st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_add
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fmul_i
r_void
id|fmul_i
c_func
(paren
)paren
(brace
multiline_comment|/* fmul st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_mul
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fsubri
r_void
id|fsubri
c_func
(paren
)paren
(brace
multiline_comment|/* fsubr st(i),st */
multiline_comment|/* This is the sense of the 80486 manual&n;     reg_sub(&amp;st(FPU_rm), FPU_st0_ptr, &amp;st(FPU_rm), control_word); */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_sub
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fsub_i
r_void
id|fsub_i
c_func
(paren
)paren
(brace
multiline_comment|/* fsub st(i),st */
multiline_comment|/* This is the sense of the 80486 manual&n;     reg_sub(FPU_st0_ptr, &amp;st(FPU_rm), &amp;st(FPU_rm), control_word); */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_sub
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fdivri
r_void
id|fdivri
c_func
(paren
)paren
(brace
multiline_comment|/* fdivr st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_div
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|fdiv_i
r_void
id|fdiv_i
c_func
(paren
)paren
(brace
multiline_comment|/* fdiv st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
id|reg_div
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
suffix:semicolon
)brace
DECL|function|faddp_
r_void
id|faddp_
c_func
(paren
)paren
(brace
multiline_comment|/* faddp st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_add
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fmulp_
r_void
id|fmulp_
c_func
(paren
)paren
(brace
multiline_comment|/* fmulp st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_mul
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fsubrp
r_void
id|fsubrp
c_func
(paren
)paren
(brace
multiline_comment|/* fsubrp st(i),st */
multiline_comment|/* This is the sense of the 80486 manual&n;     reg_sub(&amp;st(FPU_rm), FPU_st0_ptr, &amp;st(FPU_rm), control_word); */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_sub
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fsubp_
r_void
id|fsubp_
c_func
(paren
)paren
(brace
multiline_comment|/* fsubp st(i),st */
multiline_comment|/* This is the sense of the 80486 manual&n;     reg_sub(FPU_st0_ptr, &amp;st(FPU_rm), &amp;st(FPU_rm), control_word); */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_sub
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fdivrp
r_void
id|fdivrp
c_func
(paren
)paren
(brace
multiline_comment|/* fdivrp st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_div
c_func
(paren
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fdivp_
r_void
id|fdivp_
c_func
(paren
)paren
(brace
multiline_comment|/* fdivp st(i),st */
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif PECULIAR_486
r_if
c_cond
(paren
op_logical_neg
id|reg_div
c_func
(paren
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|FPU_st0_ptr
comma
op_amp
id|st
c_func
(paren
id|FPU_rm
)paren
comma
id|control_word
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
eof
