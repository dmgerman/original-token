multiline_comment|/*---------------------------------------------------------------------------+&n; |  poly_2xm1.c                                                              |&n; |                                                                           |&n; | Function to compute 2^x-1 by a polynomial approximation.                  |&n; |                                                                           |&n; | Copyright (C) 1992,1993,1994                                              |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;reg_constant.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;control_w.h&quot;
macro_line|#include &quot;poly.h&quot;
DECL|macro|HIPOWER
mdefine_line|#define&t;HIPOWER&t;11
DECL|variable|lterms
r_static
r_const
r_int
r_int
r_int
id|lterms
(braket
id|HIPOWER
)braket
op_assign
(brace
l_int|0x0000000000000000LL
comma
multiline_comment|/* This term done separately as 12 bytes */
l_int|0xf5fdeffc162c7543LL
comma
l_int|0x1c6b08d704a0bfa6LL
comma
l_int|0x0276556df749cc21LL
comma
l_int|0x002bb0ffcf14f6b8LL
comma
l_int|0x0002861225ef751cLL
comma
l_int|0x00001ffcbfcd5422LL
comma
l_int|0x00000162c005d5f1LL
comma
l_int|0x0000000da96ccb1bLL
comma
l_int|0x0000000078d1b897LL
comma
l_int|0x000000000422b029LL
)brace
suffix:semicolon
DECL|variable|hiterm
r_static
r_const
id|Xsig
id|hiterm
op_assign
id|MK_XSIG
c_func
(paren
l_int|0xb17217f7
comma
l_int|0xd1cf79ab
comma
l_int|0xc8a39194
)paren
suffix:semicolon
multiline_comment|/* Four slices: 0.0 : 0.25 : 0.50 : 0.75 : 1.0,&n;   These numbers are 2^(1/4), 2^(1/2), and 2^(3/4)&n; */
DECL|variable|shiftterm0
r_static
r_const
id|Xsig
id|shiftterm0
op_assign
id|MK_XSIG
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|shiftterm1
r_static
r_const
id|Xsig
id|shiftterm1
op_assign
id|MK_XSIG
c_func
(paren
l_int|0x9837f051
comma
l_int|0x8db8a96f
comma
l_int|0x46ad2318
)paren
suffix:semicolon
DECL|variable|shiftterm2
r_static
r_const
id|Xsig
id|shiftterm2
op_assign
id|MK_XSIG
c_func
(paren
l_int|0xb504f333
comma
l_int|0xf9de6484
comma
l_int|0x597d89b3
)paren
suffix:semicolon
DECL|variable|shiftterm3
r_static
r_const
id|Xsig
id|shiftterm3
op_assign
id|MK_XSIG
c_func
(paren
l_int|0xd744fcca
comma
l_int|0xd69d6af4
comma
l_int|0x39a68bb9
)paren
suffix:semicolon
DECL|variable|shiftterm
r_static
r_const
id|Xsig
op_star
id|shiftterm
(braket
)braket
op_assign
(brace
op_amp
id|shiftterm0
comma
op_amp
id|shiftterm1
comma
op_amp
id|shiftterm2
comma
op_amp
id|shiftterm3
)brace
suffix:semicolon
multiline_comment|/*--- poly_2xm1() -----------------------------------------------------------+&n; | Requires an argument which is TW_Valid and &lt; 1.                           |&n; +---------------------------------------------------------------------------*/
DECL|function|poly_2xm1
r_int
id|poly_2xm1
c_func
(paren
id|FPU_REG
r_const
op_star
id|arg
comma
id|FPU_REG
op_star
id|result
)paren
(brace
r_int
r_int
id|exponent
comma
id|shift
suffix:semicolon
r_int
r_int
r_int
id|Xll
suffix:semicolon
id|Xsig
id|accumulator
comma
id|Denom
comma
id|argSignif
suffix:semicolon
id|exponent
op_assign
id|arg-&gt;exp
op_minus
id|EXP_BIAS
suffix:semicolon
macro_line|#ifdef PARANOID
r_if
c_cond
(paren
(paren
id|exponent
op_ge
l_int|0
)paren
multiline_comment|/* Don&squot;t want a |number| &gt;= 1.0 */
op_logical_or
(paren
id|arg-&gt;tag
op_ne
id|TW_Valid
)paren
)paren
(brace
multiline_comment|/* Number negative, too large, or not Valid. */
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x127
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif PARANOID
id|argSignif.lsw
op_assign
l_int|0
suffix:semicolon
id|XSIG_LL
c_func
(paren
id|argSignif
)paren
op_assign
id|Xll
op_assign
id|significand
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exponent
op_eq
op_minus
l_int|1
)paren
(brace
id|shift
op_assign
(paren
id|argSignif.msw
op_amp
l_int|0x40000000
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* subtract 0.5 or 0.75 */
id|exponent
op_sub_assign
l_int|2
suffix:semicolon
id|XSIG_LL
c_func
(paren
id|argSignif
)paren
op_lshift_assign
l_int|2
suffix:semicolon
id|Xll
op_lshift_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|exponent
op_eq
op_minus
l_int|2
)paren
(brace
id|shift
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* subtract 0.25 */
id|exponent
op_decrement
suffix:semicolon
id|XSIG_LL
c_func
(paren
id|argSignif
)paren
op_lshift_assign
l_int|1
suffix:semicolon
id|Xll
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_else
id|shift
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|exponent
OL
op_minus
l_int|2
)paren
(brace
multiline_comment|/* Shift the argument right by the required places. */
r_if
c_cond
(paren
id|shrx
c_func
(paren
op_amp
id|Xll
comma
op_minus
l_int|2
op_minus
id|exponent
)paren
op_ge
l_int|0x80000000U
)paren
id|Xll
op_increment
suffix:semicolon
multiline_comment|/* round up */
)brace
id|accumulator.lsw
op_assign
id|accumulator.midw
op_assign
id|accumulator.msw
op_assign
l_int|0
suffix:semicolon
id|polynomial_Xsig
c_func
(paren
op_amp
id|accumulator
comma
op_amp
id|Xll
comma
id|lterms
comma
id|HIPOWER
op_minus
l_int|1
)paren
suffix:semicolon
id|mul_Xsig_Xsig
c_func
(paren
op_amp
id|accumulator
comma
op_amp
id|argSignif
)paren
suffix:semicolon
id|shr_Xsig
c_func
(paren
op_amp
id|accumulator
comma
l_int|3
)paren
suffix:semicolon
id|mul_Xsig_Xsig
c_func
(paren
op_amp
id|argSignif
comma
op_amp
id|hiterm
)paren
suffix:semicolon
multiline_comment|/* The leading term */
id|add_two_Xsig
c_func
(paren
op_amp
id|accumulator
comma
op_amp
id|argSignif
comma
op_amp
id|exponent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
)paren
(brace
multiline_comment|/* The argument is large, use the identity:&n;&t; f(x+a) = f(a) * (f(x) + 1) - 1;&n;&t; */
id|shr_Xsig
c_func
(paren
op_amp
id|accumulator
comma
op_minus
id|exponent
)paren
suffix:semicolon
id|accumulator.msw
op_or_assign
l_int|0x80000000
suffix:semicolon
multiline_comment|/* add 1.0 */
id|mul_Xsig_Xsig
c_func
(paren
op_amp
id|accumulator
comma
id|shiftterm
(braket
id|shift
)braket
)paren
suffix:semicolon
id|accumulator.msw
op_and_assign
l_int|0x3fffffff
suffix:semicolon
multiline_comment|/* subtract 1.0 */
id|exponent
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg-&gt;sign
op_ne
id|SIGN_POS
)paren
(brace
multiline_comment|/* The argument is negative, use the identity:&n;&t;     f(-x) = -f(x) / (1 + f(x))&n;&t; */
id|Denom.lsw
op_assign
id|accumulator.lsw
suffix:semicolon
id|XSIG_LL
c_func
(paren
id|Denom
)paren
op_assign
id|XSIG_LL
c_func
(paren
id|accumulator
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exponent
OL
l_int|0
)paren
id|shr_Xsig
c_func
(paren
op_amp
id|Denom
comma
op_minus
id|exponent
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|exponent
OG
l_int|0
)paren
(brace
multiline_comment|/* exponent must be 1 here */
id|XSIG_LL
c_func
(paren
id|Denom
)paren
op_lshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|Denom.lsw
op_amp
l_int|0x80000000
)paren
id|XSIG_LL
c_func
(paren
id|Denom
)paren
op_or_assign
l_int|1
suffix:semicolon
(paren
id|Denom.lsw
)paren
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|Denom.msw
op_or_assign
l_int|0x80000000
suffix:semicolon
multiline_comment|/* add 1.0 */
id|div_Xsig
c_func
(paren
op_amp
id|accumulator
comma
op_amp
id|Denom
comma
op_amp
id|accumulator
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert to 64 bit signed-compatible */
id|exponent
op_add_assign
id|round_Xsig
c_func
(paren
op_amp
id|accumulator
)paren
suffix:semicolon
id|significand
c_func
(paren
id|result
)paren
op_assign
id|XSIG_LL
c_func
(paren
id|accumulator
)paren
suffix:semicolon
id|result-&gt;tag
op_assign
id|TW_Valid
suffix:semicolon
id|result-&gt;exp
op_assign
id|exponent
op_plus
id|EXP_BIAS
suffix:semicolon
id|result-&gt;sign
op_assign
id|arg-&gt;sign
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof