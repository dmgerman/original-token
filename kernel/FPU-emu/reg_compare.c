multiline_comment|/*---------------------------------------------------------------------------+&n; |  reg_compare.c                                                            |&n; |                                                                           |&n; | Compare two floating point registers                                      |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | compare() is the core FPU_REG comparison function                         |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;control_w.h&quot;
macro_line|#include &quot;status_w.h&quot;
DECL|function|compare
r_int
id|compare
c_func
(paren
id|FPU_REG
op_star
id|b
)paren
(brace
r_int
id|diff
suffix:semicolon
r_if
c_cond
(paren
id|FPU_st0_ptr-&gt;tag
op_or
id|b-&gt;tag
)paren
(brace
r_if
c_cond
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Zero
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_Zero
)paren
r_return
id|COMP_A_eq_B
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_Valid
)paren
(brace
r_return
(paren
(paren
id|b-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_lt_B
suffix:colon
id|COMP_A_gt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_Zero
)paren
(brace
r_if
c_cond
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Valid
)paren
(brace
r_return
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_gt_B
suffix:colon
id|COMP_A_lt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Infinity
)paren
(brace
r_if
c_cond
(paren
(paren
id|b-&gt;tag
op_eq
id|TW_Valid
)paren
op_logical_or
(paren
id|b-&gt;tag
op_eq
id|TW_Zero
)paren
)paren
(brace
r_return
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_gt_B
suffix:colon
id|COMP_A_lt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|b-&gt;tag
op_eq
id|TW_Valid
)paren
op_logical_and
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_Infinity
)paren
(brace
multiline_comment|/* The 80486 book says that infinities can be equal! */
r_return
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|b-&gt;sign
)paren
ques
c_cond
id|COMP_A_eq_B
suffix:colon
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_gt_B
suffix:colon
id|COMP_A_lt_B
)paren
suffix:semicolon
)brace
multiline_comment|/* Fall through to the NaN code */
)brace
r_else
r_if
c_cond
(paren
id|b-&gt;tag
op_eq
id|TW_Infinity
)paren
(brace
r_if
c_cond
(paren
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Valid
)paren
op_logical_or
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Zero
)paren
)paren
(brace
r_return
(paren
(paren
id|b-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_lt_B
suffix:colon
id|COMP_A_gt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_Valid
)paren
op_logical_and
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
multiline_comment|/* Fall through to the NaN code */
)brace
multiline_comment|/* The only possibility now should be that one of the arguments&n;&t; is a NaN */
r_if
c_cond
(paren
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_NaN
)paren
op_logical_or
(paren
id|b-&gt;tag
op_eq
id|TW_NaN
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;tag
op_eq
id|TW_NaN
)paren
op_logical_and
op_logical_neg
(paren
id|FPU_st0_ptr-&gt;sigh
op_amp
l_int|0x40000000
)paren
)paren
op_logical_or
(paren
(paren
id|b-&gt;tag
op_eq
id|TW_NaN
)paren
op_logical_and
op_logical_neg
(paren
id|b-&gt;sigh
op_amp
l_int|0x40000000
)paren
)paren
)paren
multiline_comment|/* At least one arg is a signaling NaN */
r_return
id|COMP_No_Comp
op_or
id|COMP_SNaN
op_or
id|COMP_NaN
suffix:semicolon
r_else
multiline_comment|/* Neither is a signaling NaN */
r_return
id|COMP_No_Comp
op_or
id|COMP_NaN
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
)brace
macro_line|#ifdef PARANOID
r_if
c_cond
(paren
op_logical_neg
(paren
id|FPU_st0_ptr-&gt;sigh
op_amp
l_int|0x80000000
)paren
)paren
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|b-&gt;sigh
op_amp
l_int|0x80000000
)paren
)paren
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
macro_line|#endif PARANOID
r_if
c_cond
(paren
id|FPU_st0_ptr-&gt;sign
op_ne
id|b-&gt;sign
)paren
(brace
r_return
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_gt_B
suffix:colon
id|COMP_A_lt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
op_logical_or
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
id|diff
op_assign
id|FPU_st0_ptr-&gt;exp
op_minus
id|b-&gt;exp
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
(brace
id|diff
op_assign
id|FPU_st0_ptr-&gt;sigh
op_minus
id|b-&gt;sigh
suffix:semicolon
multiline_comment|/* Works only if ms bits are&n;&t;&t;&t;&t;&t;      identical */
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
(brace
id|diff
op_assign
id|FPU_st0_ptr-&gt;sigl
OG
id|b-&gt;sigl
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
id|diff
op_assign
op_minus
(paren
id|FPU_st0_ptr-&gt;sigl
OL
id|b-&gt;sigl
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|diff
OG
l_int|0
)paren
(brace
r_return
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_gt_B
suffix:colon
id|COMP_A_lt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
op_logical_or
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|diff
OL
l_int|0
)paren
(brace
r_return
(paren
(paren
id|FPU_st0_ptr-&gt;sign
op_eq
id|SIGN_POS
)paren
ques
c_cond
id|COMP_A_lt_B
suffix:colon
id|COMP_A_gt_B
)paren
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
op_logical_or
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
r_return
id|COMP_A_eq_B
macro_line|#ifdef DENORM_OPERAND
op_or
(paren
(paren
(paren
id|FPU_st0_ptr-&gt;exp
op_le
id|EXP_UNDER
)paren
op_logical_or
(paren
id|b-&gt;exp
op_le
id|EXP_UNDER
)paren
)paren
ques
c_cond
id|COMP_Denormal
suffix:colon
l_int|0
)paren
macro_line|#endif DENORM_OPERAND
suffix:semicolon
)brace
multiline_comment|/* This function requires that st(0) is not empty */
DECL|function|compare_st_data
r_int
id|compare_st_data
c_func
(paren
r_void
)paren
(brace
r_int
id|f
comma
id|c
suffix:semicolon
id|c
op_assign
id|compare
c_func
(paren
op_amp
id|FPU_loaded_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_NaN
)paren
(brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|c
op_amp
l_int|7
)paren
(brace
r_case
id|COMP_A_lt_B
suffix:colon
id|f
op_assign
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_eq_B
suffix:colon
id|f
op_assign
id|SW_C3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_gt_B
suffix:colon
id|f
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_No_Comp
suffix:colon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef PARANOID
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x121
)paren
suffix:semicolon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif PARANOID
)brace
id|setcc
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_Denormal
)paren
(brace
r_return
id|denormal_operand
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compare_st_st
r_static
r_int
id|compare_st_st
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
id|f
comma
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
op_logical_or
op_logical_neg
id|NOT_EMPTY
c_func
(paren
id|nr
)paren
)paren
(brace
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
multiline_comment|/* Stack fault */
id|EXCEPTION
c_func
(paren
id|EX_StackUnder
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
suffix:semicolon
)brace
id|c
op_assign
id|compare
c_func
(paren
op_amp
id|st
c_func
(paren
id|nr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_NaN
)paren
(brace
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|c
op_amp
l_int|7
)paren
(brace
r_case
id|COMP_A_lt_B
suffix:colon
id|f
op_assign
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_eq_B
suffix:colon
id|f
op_assign
id|SW_C3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_gt_B
suffix:colon
id|f
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_No_Comp
suffix:colon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef PARANOID
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x122
)paren
suffix:semicolon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif PARANOID
)brace
id|setcc
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_Denormal
)paren
(brace
r_return
id|denormal_operand
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compare_u_st_st
r_static
r_int
id|compare_u_st_st
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
id|f
comma
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NOT_EMPTY_0
op_logical_or
op_logical_neg
id|NOT_EMPTY
c_func
(paren
id|nr
)paren
)paren
(brace
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
multiline_comment|/* Stack fault */
id|EXCEPTION
c_func
(paren
id|EX_StackUnder
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
suffix:semicolon
)brace
id|c
op_assign
id|compare
c_func
(paren
op_amp
id|st
c_func
(paren
id|nr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_NaN
)paren
(brace
id|setcc
c_func
(paren
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_SNaN
)paren
multiline_comment|/* This is the only difference between&n;&t;&t;&t;&t;  un-ordered and ordinary comparisons */
(brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|control_word
op_amp
id|CW_Invalid
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|c
op_amp
l_int|7
)paren
(brace
r_case
id|COMP_A_lt_B
suffix:colon
id|f
op_assign
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_eq_B
suffix:colon
id|f
op_assign
id|SW_C3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_A_gt_B
suffix:colon
id|f
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMP_No_Comp
suffix:colon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef PARANOID
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x123
)paren
suffix:semicolon
id|f
op_assign
id|SW_C3
op_or
id|SW_C2
op_or
id|SW_C0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif PARANOID
)brace
id|setcc
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
id|COMP_Denormal
)paren
(brace
r_return
id|denormal_operand
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*---------------------------------------------------------------------------*/
DECL|function|fcom_st
r_void
id|fcom_st
c_func
(paren
)paren
(brace
multiline_comment|/* fcom st(i) */
id|compare_st_st
c_func
(paren
id|FPU_rm
)paren
suffix:semicolon
)brace
DECL|function|fcompst
r_void
id|fcompst
c_func
(paren
)paren
(brace
multiline_comment|/* fcomp st(i) */
r_if
c_cond
(paren
op_logical_neg
id|compare_st_st
c_func
(paren
id|FPU_rm
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fcompp
r_void
id|fcompp
c_func
(paren
)paren
(brace
multiline_comment|/* fcompp */
r_if
c_cond
(paren
id|FPU_rm
op_ne
l_int|1
)paren
(brace
id|Un_impl
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|compare_st_st
c_func
(paren
l_int|1
)paren
)paren
(brace
id|pop
c_func
(paren
)paren
suffix:semicolon
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|fucom_
r_void
id|fucom_
c_func
(paren
)paren
(brace
multiline_comment|/* fucom st(i) */
id|compare_u_st_st
c_func
(paren
id|FPU_rm
)paren
suffix:semicolon
)brace
DECL|function|fucomp
r_void
id|fucomp
c_func
(paren
)paren
(brace
multiline_comment|/* fucomp st(i) */
r_if
c_cond
(paren
op_logical_neg
id|compare_u_st_st
c_func
(paren
id|FPU_rm
)paren
)paren
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fucompp
r_void
id|fucompp
c_func
(paren
)paren
(brace
multiline_comment|/* fucompp */
r_if
c_cond
(paren
id|FPU_rm
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|compare_u_st_st
c_func
(paren
l_int|1
)paren
)paren
(brace
id|pop
c_func
(paren
)paren
suffix:semicolon
id|FPU_st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pop
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|Un_impl
c_func
(paren
)paren
suffix:semicolon
)brace
eof
