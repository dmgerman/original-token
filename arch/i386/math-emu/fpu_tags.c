multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_tags.c                                                               |&n; |                                                                           |&n; |  Set FPU register tags.                                                   |&n; |                                                                           |&n; | Copyright (C) 1997                                                        |&n; |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |&n; |                  E-mail   billm@jacobi.maths.monash.edu.au                |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;exception.h&quot;
DECL|function|FPU_pop
r_void
id|FPU_pop
c_func
(paren
r_void
)paren
(brace
id|fpu_tag_word
op_or_assign
l_int|3
op_lshift
(paren
(paren
id|top
op_amp
l_int|7
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|top
op_increment
suffix:semicolon
)brace
DECL|function|FPU_gettag0
r_int
id|FPU_gettag0
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|fpu_tag_word
op_rshift
(paren
(paren
id|top
op_amp
l_int|7
)paren
op_star
l_int|2
)paren
)paren
op_amp
l_int|3
suffix:semicolon
)brace
DECL|function|FPU_gettagi
r_int
id|FPU_gettagi
c_func
(paren
r_int
id|stnr
)paren
(brace
r_return
(paren
id|fpu_tag_word
op_rshift
(paren
(paren
(paren
id|top
op_plus
id|stnr
)paren
op_amp
l_int|7
)paren
op_star
l_int|2
)paren
)paren
op_amp
l_int|3
suffix:semicolon
)brace
DECL|function|FPU_gettag
r_int
id|FPU_gettag
c_func
(paren
r_int
id|regnr
)paren
(brace
r_return
(paren
id|fpu_tag_word
op_rshift
(paren
(paren
id|regnr
op_amp
l_int|7
)paren
op_star
l_int|2
)paren
)paren
op_amp
l_int|3
suffix:semicolon
)brace
DECL|function|FPU_settag0
r_void
id|FPU_settag0
c_func
(paren
r_int
id|tag
)paren
(brace
r_int
id|regnr
op_assign
id|top
suffix:semicolon
id|regnr
op_and_assign
l_int|7
suffix:semicolon
id|fpu_tag_word
op_and_assign
op_complement
(paren
l_int|3
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|fpu_tag_word
op_or_assign
(paren
id|tag
op_amp
l_int|3
)paren
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|FPU_settagi
r_void
id|FPU_settagi
c_func
(paren
r_int
id|stnr
comma
r_int
id|tag
)paren
(brace
r_int
id|regnr
op_assign
id|stnr
op_plus
id|top
suffix:semicolon
id|regnr
op_and_assign
l_int|7
suffix:semicolon
id|fpu_tag_word
op_and_assign
op_complement
(paren
l_int|3
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|fpu_tag_word
op_or_assign
(paren
id|tag
op_amp
l_int|3
)paren
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|FPU_settag
r_void
id|FPU_settag
c_func
(paren
r_int
id|regnr
comma
r_int
id|tag
)paren
(brace
id|regnr
op_and_assign
l_int|7
suffix:semicolon
id|fpu_tag_word
op_and_assign
op_complement
(paren
l_int|3
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|fpu_tag_word
op_or_assign
(paren
id|tag
op_amp
l_int|3
)paren
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|FPU_Special
r_int
id|FPU_Special
c_func
(paren
id|FPU_REG
r_const
op_star
id|ptr
)paren
(brace
r_int
id|exp
op_assign
id|exponent
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp
op_eq
id|EXP_BIAS
op_plus
id|EXP_UNDER
)paren
r_return
id|TW_Denormal
suffix:semicolon
r_else
r_if
c_cond
(paren
id|exp
op_ne
id|EXP_BIAS
op_plus
id|EXP_OVER
)paren
r_return
id|TW_NaN
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|ptr-&gt;sigh
op_eq
l_int|0x80000000
)paren
op_logical_and
(paren
id|ptr-&gt;sigl
op_eq
l_int|0
)paren
)paren
r_return
id|TW_Infinity
suffix:semicolon
r_return
id|TW_NaN
suffix:semicolon
)brace
DECL|function|isNaN
r_int
id|isNaN
c_func
(paren
id|FPU_REG
r_const
op_star
id|ptr
)paren
(brace
r_return
(paren
(paren
id|exponent
c_func
(paren
id|ptr
)paren
op_eq
id|EXP_BIAS
op_plus
id|EXP_OVER
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|ptr-&gt;sigh
op_eq
l_int|0x80000000
)paren
op_logical_and
(paren
id|ptr-&gt;sigl
op_eq
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|FPU_empty_i
r_int
id|FPU_empty_i
c_func
(paren
r_int
id|stnr
)paren
(brace
r_int
id|regnr
op_assign
(paren
id|top
op_plus
id|stnr
)paren
op_amp
l_int|7
suffix:semicolon
r_return
(paren
(paren
id|fpu_tag_word
op_rshift
(paren
id|regnr
op_star
l_int|2
)paren
)paren
op_amp
l_int|3
)paren
op_eq
id|TAG_Empty
suffix:semicolon
)brace
DECL|function|FPU_stackoverflow
r_int
id|FPU_stackoverflow
c_func
(paren
id|FPU_REG
op_star
op_star
id|st_new_ptr
)paren
(brace
op_star
id|st_new_ptr
op_assign
op_amp
id|st
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
(paren
id|fpu_tag_word
op_rshift
(paren
(paren
(paren
id|top
op_minus
l_int|1
)paren
op_amp
l_int|7
)paren
op_star
l_int|2
)paren
)paren
op_amp
l_int|3
)paren
op_ne
id|TAG_Empty
suffix:semicolon
)brace
DECL|function|FPU_copy_to_regi
r_void
id|FPU_copy_to_regi
c_func
(paren
id|FPU_REG
r_const
op_star
id|r
comma
id|u_char
id|tag
comma
r_int
id|stnr
)paren
(brace
id|reg_copy
c_func
(paren
id|r
comma
op_amp
id|st
c_func
(paren
id|stnr
)paren
)paren
suffix:semicolon
id|FPU_settagi
c_func
(paren
id|stnr
comma
id|tag
)paren
suffix:semicolon
)brace
DECL|function|FPU_copy_to_reg1
r_void
id|FPU_copy_to_reg1
c_func
(paren
id|FPU_REG
r_const
op_star
id|r
comma
id|u_char
id|tag
)paren
(brace
id|reg_copy
c_func
(paren
id|r
comma
op_amp
id|st
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|FPU_settagi
c_func
(paren
l_int|1
comma
id|tag
)paren
suffix:semicolon
)brace
DECL|function|FPU_copy_to_reg0
r_void
id|FPU_copy_to_reg0
c_func
(paren
id|FPU_REG
r_const
op_star
id|r
comma
id|u_char
id|tag
)paren
(brace
r_int
id|regnr
op_assign
id|top
suffix:semicolon
id|regnr
op_and_assign
l_int|7
suffix:semicolon
id|reg_copy
c_func
(paren
id|r
comma
op_amp
id|st
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|fpu_tag_word
op_and_assign
op_complement
(paren
l_int|3
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|fpu_tag_word
op_or_assign
(paren
id|tag
op_amp
l_int|3
)paren
op_lshift
(paren
id|regnr
op_star
l_int|2
)paren
suffix:semicolon
)brace
eof