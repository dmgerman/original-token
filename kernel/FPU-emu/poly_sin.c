multiline_comment|/*---------------------------------------------------------------------------+&n; |  poly_sin.c                                                               |&n; |                                                                           |&n; |  Computation of an approximation of the sin function by a polynomial      |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;reg_constant.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;control_w.h&quot;
DECL|macro|HIPOWER
mdefine_line|#define&t;HIPOWER&t;5
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
l_int|0xe110
comma
l_int|0x75aa
comma
l_int|0xbc67
comma
l_int|0x1466
)brace
comma
(brace
l_int|0x503d
comma
l_int|0xa43f
comma
l_int|0x83c1
comma
l_int|0x000a
)brace
comma
(brace
l_int|0x8f9d
comma
l_int|0x7a19
comma
l_int|0x00f4
comma
l_int|0x0000
)brace
comma
(brace
l_int|0xda03
comma
l_int|0x06aa
comma
l_int|0x0000
comma
l_int|0x0000
)brace
comma
)brace
suffix:semicolon
DECL|variable|negterms
r_static
r_int
r_int
id|negterms
(braket
id|HIPOWER
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x95ed
comma
l_int|0x2df2
comma
l_int|0xe731
comma
l_int|0xa55d
)brace
comma
(brace
l_int|0xd159
comma
l_int|0xe62b
comma
l_int|0xd2cc
comma
l_int|0x0132
)brace
comma
(brace
l_int|0x6342
comma
l_int|0xe9fb
comma
l_int|0x3c60
comma
l_int|0x0000
)brace
comma
(brace
l_int|0x6256
comma
l_int|0xdf5a
comma
l_int|0x0002
comma
l_int|0x0000
)brace
comma
(brace
l_int|0xf279
comma
l_int|0x000b
comma
l_int|0x0000
comma
l_int|0x0000
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*--- poly_sine() -----------------------------------------------------------+&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
DECL|function|poly_sine
r_void
id|poly_sine
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
id|FPU_REG
id|fixed_arg
comma
id|arg_sqrd
comma
id|arg_to_4
comma
id|accum
comma
id|negaccum
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
suffix:semicolon
)brace
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
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|CONST_QNaN
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exponent
op_ge
l_int|0
)paren
multiline_comment|/* Can&squot;t hack a number &gt; 1.0 */
(brace
r_if
c_cond
(paren
(paren
id|exponent
op_eq
l_int|0
)paren
op_logical_and
(paren
id|arg-&gt;sigl
op_eq
l_int|0
)paren
op_logical_and
(paren
id|arg-&gt;sigh
op_eq
l_int|0x80000000
)paren
)paren
(brace
id|reg_move
c_func
(paren
op_amp
id|CONST_1
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|EXCEPTION
c_func
(paren
id|EX_Invalid
)paren
suffix:semicolon
id|reg_move
c_func
(paren
op_amp
id|CONST_QNaN
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif PARANOID
id|fixed_arg.sigl
op_assign
id|arg-&gt;sigl
suffix:semicolon
id|fixed_arg.sigh
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
(paren
id|fixed_arg.sigl
)paren
comma
op_minus
l_int|1
op_minus
id|exponent
)paren
op_ge
l_int|0x80000000U
)paren
(paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
(paren
id|fixed_arg.sigl
)paren
)paren
)paren
)paren
op_increment
suffix:semicolon
multiline_comment|/* round up */
)brace
id|mul64
c_func
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|fixed_arg.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|fixed_arg.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|arg_sqrd.sigl
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
op_amp
(paren
id|arg_sqrd.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|arg_sqrd.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|arg_to_4.sigl
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
id|accum.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|accum.exp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
(paren
id|accum.sigl
)paren
comma
op_amp
(paren
id|arg_to_4.sigl
)paren
comma
id|lterms
comma
id|HIPOWER
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
id|negaccum.sign
)paren
op_assign
l_int|0
suffix:semicolon
id|negaccum.exp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do the basic fixed point polynomial evaluation */
id|polynomial
c_func
(paren
op_amp
(paren
id|negaccum.sigl
)paren
comma
op_amp
(paren
id|arg_to_4.sigl
)paren
comma
id|negterms
comma
id|HIPOWER
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
op_amp
(paren
id|arg_sqrd.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|negaccum.sigl
)paren
comma
(paren
r_int
r_int
op_star
)paren
op_amp
(paren
id|negaccum.sigl
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
(paren
id|accum.sigl
)paren
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
(paren
id|negaccum.sigl
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert to 64 bit signed-compatible */
id|accum.exp
op_assign
id|EXP_BIAS
op_minus
l_int|1
op_plus
id|accum.exp
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
id|reg_mul
c_func
(paren
id|result
comma
id|arg
comma
id|result
comma
id|FULL_PRECISION
)paren
suffix:semicolon
id|reg_u_add
c_func
(paren
id|result
comma
id|arg
comma
id|result
comma
id|FULL_PRECISION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result-&gt;exp
op_ge
id|EXP_BIAS
)paren
(brace
multiline_comment|/* A small overflow may be possible... but an illegal result. */
r_if
c_cond
(paren
(paren
id|result-&gt;exp
OG
id|EXP_BIAS
)paren
multiline_comment|/* Larger or equal 2.0 */
op_logical_or
(paren
id|result-&gt;sigl
OG
l_int|1
)paren
multiline_comment|/* Larger than 1.0+msb */
op_logical_or
(paren
id|result-&gt;sigh
op_ne
l_int|0x80000000
)paren
multiline_comment|/* Much &gt; 1.0 */
)paren
(brace
macro_line|#ifdef DEBUGGING
id|RE_ENTRANT_CHECK_OFF
id|printk
c_func
(paren
l_string|&quot;&bslash;nEXP=%d, MS=%08x, LS=%08x&bslash;n&quot;
comma
id|result-&gt;exp
comma
id|result-&gt;sigh
comma
id|result-&gt;sigl
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
macro_line|#endif DEBUGGING
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x103
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUGGING
id|RE_ENTRANT_CHECK_OFF
id|printk
c_func
(paren
l_string|&quot;&bslash;n***CORRECTING ILLEGAL RESULT*** in poly_sin() computation&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EXP=%d, MS=%08x, LS=%08x&bslash;n&quot;
comma
id|result-&gt;exp
comma
id|result-&gt;sigh
comma
id|result-&gt;sigl
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
macro_line|#endif DEBUGGING
id|result-&gt;sigl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Truncate the result to 1.00 */
)brace
)brace
eof
