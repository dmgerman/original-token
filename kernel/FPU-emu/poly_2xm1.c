multiline_comment|/*---------------------------------------------------------------------------+&n; |  poly_2xm1.c                                                              |&n; |                                                                           |&n; | Function to compute 2^x-1 by a polynomial approximation.                  |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;reg_constant.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
DECL|macro|HIPOWER
mdefine_line|#define&t;HIPOWER&t;13
DECL|variable|lterms
r_static
r_int
r_int
id|lterms
(braket
id|HIPOWER
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x79b5
comma
l_int|0xd1cf
comma
l_int|0x17f7
comma
l_int|0xb172
)brace
comma
(brace
l_int|0x1b56
comma
l_int|0x058b
comma
l_int|0x7bff
comma
l_int|0x3d7f
)brace
comma
(brace
l_int|0x8bb0
comma
l_int|0x8250
comma
l_int|0x846b
comma
l_int|0x0e35
)brace
comma
(brace
l_int|0xbc65
comma
l_int|0xf747
comma
l_int|0x556d
comma
l_int|0x0276
)brace
comma
(brace
l_int|0x17cb
comma
l_int|0x9e39
comma
l_int|0x61ff
comma
l_int|0x0057
)brace
comma
(brace
l_int|0xe018
comma
l_int|0x9776
comma
l_int|0x1848
comma
l_int|0x000a
)brace
comma
(brace
l_int|0x66f2
comma
l_int|0xff30
comma
l_int|0xffe5
comma
l_int|0x0000
)brace
comma
(brace
l_int|0x682f
comma
l_int|0xffb6
comma
l_int|0x162b
comma
l_int|0x0000
)brace
comma
(brace
l_int|0xb7ca
comma
l_int|0x2956
comma
l_int|0x01b5
comma
l_int|0x0000
)brace
comma
(brace
l_int|0xcd3e
comma
l_int|0x4817
comma
l_int|0x001e
comma
l_int|0x0000
)brace
comma
(brace
l_int|0xb7e2
comma
l_int|0xecbe
comma
l_int|0x0001
comma
l_int|0x0000
)brace
comma
(brace
l_int|0x0ed5
comma
l_int|0x1a27
comma
l_int|0x0000
comma
l_int|0x0000
)brace
comma
(brace
l_int|0x101d
comma
l_int|0x0222
comma
l_int|0x0000
comma
l_int|0x0000
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*--- poly_2xm1() -----------------------------------------------------------+&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
DECL|function|poly_2xm1
r_int
id|poly_2xm1
c_func
(paren
id|FPU_REG
op_star
id|arg
comma
id|FPU_REG
op_star
id|result
)paren
(brace
r_int
id|exponent
suffix:semicolon
r_int
r_int
id|Xll
suffix:semicolon
id|FPU_REG
id|accum
suffix:semicolon
id|exponent
op_assign
id|arg-&gt;exp
op_minus
id|EXP_BIAS
suffix:semicolon
r_if
c_cond
(paren
id|arg-&gt;tag
op_eq
id|TW_Zero
)paren
(brace
multiline_comment|/* Return 0.0 */
id|reg_move
c_func
(paren
op_amp
id|CONST_Z
comma
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exponent
op_ge
l_int|0
)paren
multiline_comment|/* Can&squot;t hack a number &gt;= 1.0 */
(brace
id|arith_invalid
c_func
(paren
id|result
)paren
suffix:semicolon
r_return
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
multiline_comment|/* Can&squot;t hack a number &lt; 0.0 */
(brace
id|arith_invalid
c_func
(paren
id|result
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exponent
OL
op_minus
l_int|64
)paren
(brace
id|reg_move
c_func
(paren
op_amp
id|CONST_LN2
comma
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
(paren
r_int
op_star
)paren
op_amp
id|Xll
op_assign
id|arg-&gt;sigl
suffix:semicolon
op_star
(paren
(paren
(paren
r_int
op_star
)paren
op_amp
id|Xll
)paren
op_plus
l_int|1
)paren
op_assign
id|arg-&gt;sigh
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
id|Xll
comma
op_minus
l_int|1
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
op_star
(paren
r_int
op_star
)paren
op_amp
(paren
id|accum.sign
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* will be a valid positive nr with expon = 0 */
id|accum.exp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
(paren
r_int
op_star
)paren
op_amp
id|accum.sigl
comma
(paren
r_int
op_star
)paren
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
multiline_comment|/* Convert to 64 bit signed-compatible */
id|accum.exp
op_add_assign
id|EXP_BIAS
op_minus
l_int|1
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|accum
comma
id|result
)paren
suffix:semicolon
id|normalize
c_func
(paren
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
