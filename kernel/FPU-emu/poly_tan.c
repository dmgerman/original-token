multiline_comment|/*---------------------------------------------------------------------------+&n; |  poly_tan.c                                                               |&n; |                                                                           |&n; | Compute the tan of a FPU_REG, using a polynomial approximation.           |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;reg_constant.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;control_w.h&quot;
DECL|macro|HIPOWERop
mdefine_line|#define&t;HIPOWERop&t;3&t;/* odd poly, positive terms */
DECL|variable|oddplterms
r_static
r_int
r_int
id|oddplterms
(braket
id|HIPOWERop
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x846a
comma
l_int|0x42d1
comma
l_int|0xb544
comma
l_int|0x921f
)brace
comma
(brace
l_int|0x6fb2
comma
l_int|0x0215
comma
l_int|0x95c0
comma
l_int|0x099c
)brace
comma
(brace
l_int|0xfce6
comma
l_int|0x0cc8
comma
l_int|0x1c9a
comma
l_int|0x0000
)brace
)brace
suffix:semicolon
DECL|macro|HIPOWERon
mdefine_line|#define&t;HIPOWERon&t;2&t;/* odd poly, negative terms */
DECL|variable|oddnegterms
r_static
r_int
r_int
id|oddnegterms
(braket
id|HIPOWERon
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x6906
comma
l_int|0xe205
comma
l_int|0x25c8
comma
l_int|0x8838
)brace
comma
(brace
l_int|0x1dd7
comma
l_int|0x3fe3
comma
l_int|0x944e
comma
l_int|0x002c
)brace
)brace
suffix:semicolon
DECL|macro|HIPOWERep
mdefine_line|#define&t;HIPOWERep&t;2&t;/* even poly, positive terms */
DECL|variable|evenplterms
r_static
r_int
r_int
id|evenplterms
(braket
id|HIPOWERep
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0xdb8f
comma
l_int|0x3761
comma
l_int|0x1432
comma
l_int|0x2acf
)brace
comma
(brace
l_int|0x16eb
comma
l_int|0x13c1
comma
l_int|0x3099
comma
l_int|0x0003
)brace
)brace
suffix:semicolon
DECL|macro|HIPOWERen
mdefine_line|#define&t;HIPOWERen&t;2&t;/* even poly, negative terms */
DECL|variable|evennegterms
r_static
r_int
r_int
id|evennegterms
(braket
id|HIPOWERen
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x3a7c
comma
l_int|0xe4c5
comma
l_int|0x7f87
comma
l_int|0x2945
)brace
comma
(brace
l_int|0x572b
comma
l_int|0x664c
comma
l_int|0xc543
comma
l_int|0x018c
)brace
)brace
suffix:semicolon
multiline_comment|/*--- poly_tan() ------------------------------------------------------------+&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
DECL|function|poly_tan
r_void
id|poly_tan
c_func
(paren
id|FPU_REG
op_star
id|arg
comma
id|FPU_REG
op_star
id|y_reg
comma
r_int
id|invert
)paren
(brace
r_int
id|exponent
suffix:semicolon
id|FPU_REG
id|odd_poly
comma
id|even_poly
comma
id|pos_poly
comma
id|neg_poly
suffix:semicolon
id|FPU_REG
id|argSq
suffix:semicolon
r_int
r_int
id|arg_signif
comma
id|argSqSq
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
id|arg-&gt;sign
op_ne
l_int|0
)paren
multiline_comment|/* Can&squot;t hack a number &lt; 0.0 */
(brace
id|arith_invalid
c_func
(paren
id|y_reg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Need a positive number */
macro_line|#endif PARANOID
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|arg_signif
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|arg-&gt;sigl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exponent
OL
op_minus
l_int|1
)paren
(brace
multiline_comment|/* shift the argument right by the required places */
r_if
c_cond
(paren
id|shrx
c_func
(paren
op_amp
id|arg_signif
comma
op_minus
l_int|1
op_minus
id|exponent
)paren
op_ge
l_int|0x80000000U
)paren
id|arg_signif
op_increment
suffix:semicolon
multiline_comment|/* round up */
)brace
id|mul64
c_func
(paren
op_amp
id|arg_signif
comma
op_amp
id|arg_signif
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|argSq.sigl
)paren
)paren
suffix:semicolon
id|mul64
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|argSq.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|argSq.sigl
)paren
comma
op_amp
id|argSqSq
)paren
suffix:semicolon
multiline_comment|/* will be a valid positive nr with expon = 0 */
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|pos_poly.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|pos_poly.exp
op_assign
id|EXP_BIAS
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
id|pos_poly.sigl
comma
(paren
r_int
op_star
)paren
op_amp
id|argSqSq
comma
id|oddplterms
comma
id|HIPOWERop
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* will be a valid positive nr with expon = 0 */
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|neg_poly.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|neg_poly.exp
op_assign
id|EXP_BIAS
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
id|neg_poly.sigl
comma
(paren
r_int
op_star
)paren
op_amp
id|argSqSq
comma
id|oddnegterms
comma
id|HIPOWERon
op_minus
l_int|1
)paren
suffix:semicolon
id|mul64
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|argSq.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|neg_poly.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|neg_poly.sigl
)paren
)paren
suffix:semicolon
multiline_comment|/* Subtract the mantissas */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|pos_poly.sigl
)paren
)paren
op_sub_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|neg_poly.sigl
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert to 64 bit signed-compatible */
id|pos_poly.exp
op_sub_assign
l_int|1
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|pos_poly
comma
op_amp
id|odd_poly
)paren
suffix:semicolon
id|normalize
c_func
(paren
op_amp
id|odd_poly
)paren
suffix:semicolon
id|reg_mul
c_func
(paren
op_amp
id|odd_poly
comma
id|arg
comma
op_amp
id|odd_poly
comma
id|FULL_PRECISION
)paren
suffix:semicolon
multiline_comment|/* Complete the odd polynomial. */
id|reg_u_add
c_func
(paren
op_amp
id|odd_poly
comma
id|arg
comma
op_amp
id|odd_poly
comma
id|FULL_PRECISION
)paren
suffix:semicolon
multiline_comment|/* will be a valid positive nr with expon = 0 */
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|pos_poly.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|pos_poly.exp
op_assign
id|EXP_BIAS
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
id|pos_poly.sigl
comma
(paren
r_int
op_star
)paren
op_amp
id|argSqSq
comma
id|evenplterms
comma
id|HIPOWERep
op_minus
l_int|1
)paren
suffix:semicolon
id|mul64
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|argSq.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|pos_poly.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|pos_poly.sigl
)paren
)paren
suffix:semicolon
multiline_comment|/* will be a valid positive nr with expon = 0 */
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|neg_poly.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|neg_poly.exp
op_assign
id|EXP_BIAS
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
id|neg_poly.sigl
comma
(paren
r_int
op_star
)paren
op_amp
id|argSqSq
comma
id|evennegterms
comma
id|HIPOWERen
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Subtract the mantissas */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|neg_poly.sigl
)paren
)paren
op_sub_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|pos_poly.sigl
)paren
)paren
suffix:semicolon
multiline_comment|/* and multiply by argSq */
multiline_comment|/* Convert argSq to a valid reg number */
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|argSq.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|argSq.exp
op_assign
id|EXP_BIAS
op_minus
l_int|1
suffix:semicolon
id|normalize
c_func
(paren
op_amp
id|argSq
)paren
suffix:semicolon
multiline_comment|/* Convert to 64 bit signed-compatible */
id|neg_poly.exp
op_sub_assign
l_int|1
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|neg_poly
comma
op_amp
id|even_poly
)paren
suffix:semicolon
id|normalize
c_func
(paren
op_amp
id|even_poly
)paren
suffix:semicolon
id|reg_mul
c_func
(paren
op_amp
id|even_poly
comma
op_amp
id|argSq
comma
op_amp
id|even_poly
comma
id|FULL_PRECISION
)paren
suffix:semicolon
id|reg_add
c_func
(paren
op_amp
id|even_poly
comma
op_amp
id|argSq
comma
op_amp
id|even_poly
comma
id|FULL_PRECISION
)paren
suffix:semicolon
multiline_comment|/* Complete the even polynomial */
id|reg_sub
c_func
(paren
op_amp
id|CONST_1
comma
op_amp
id|even_poly
comma
op_amp
id|even_poly
comma
id|FULL_PRECISION
)paren
suffix:semicolon
multiline_comment|/* Now ready to copy the results */
r_if
c_cond
(paren
id|invert
)paren
(brace
id|reg_div
c_func
(paren
op_amp
id|even_poly
comma
op_amp
id|odd_poly
comma
id|y_reg
comma
id|FULL_PRECISION
)paren
suffix:semicolon
)brace
r_else
(brace
id|reg_div
c_func
(paren
op_amp
id|odd_poly
comma
op_amp
id|even_poly
comma
id|y_reg
comma
id|FULL_PRECISION
)paren
suffix:semicolon
)brace
)brace
eof
