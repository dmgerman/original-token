multiline_comment|/*&n; * linux/kernel/math/convert.c&n; *&n; * (C) 1991 Linus Torvalds&n; */
macro_line|#include &lt;linux/math_emu.h&gt;
multiline_comment|/*&n; * NOTE!!! There is some &quot;non-obvious&quot; optimisations in the temp_to_long&n; * and temp_to_short conversion routines: don&squot;t touch them if you don&squot;t&n; * know what&squot;s going on. They are the adding of one in the rounding: the&n; * overflow bit is also used for adding one into the exponent. Thus it&n; * looks like the overflow would be incorrectly handled, but due to the&n; * way the IEEE numbers work, things are correct.&n; *&n; * There is no checking for total overflow in the conversions, though (ie&n; * if the temp-real number simply won&squot;t fit in a short- or long-real.)&n; */
DECL|function|short_to_temp
r_void
id|short_to_temp
c_func
(paren
r_const
id|short_real
op_star
id|a
comma
id|temp_real
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|a
op_amp
l_int|0x7fffffff
)paren
)paren
(brace
id|b-&gt;a
op_assign
id|b-&gt;b
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|a
)paren
id|b-&gt;exponent
op_assign
l_int|0x8000
suffix:semicolon
r_else
id|b-&gt;exponent
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;exponent
op_assign
(paren
(paren
op_star
id|a
op_rshift
l_int|23
)paren
op_amp
l_int|0xff
)paren
op_minus
l_int|127
op_plus
l_int|16383
suffix:semicolon
r_if
c_cond
(paren
op_star
id|a
OL
l_int|0
)paren
id|b-&gt;exponent
op_or_assign
l_int|0x8000
suffix:semicolon
id|b-&gt;b
op_assign
(paren
op_star
id|a
op_lshift
l_int|8
)paren
op_or
l_int|0x80000000
suffix:semicolon
id|b-&gt;a
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|long_to_temp
r_void
id|long_to_temp
c_func
(paren
r_const
id|long_real
op_star
id|a
comma
id|temp_real
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|a-&gt;a
op_logical_and
op_logical_neg
(paren
id|a-&gt;b
op_amp
l_int|0x7fffffff
)paren
)paren
(brace
id|b-&gt;a
op_assign
id|b-&gt;b
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;b
)paren
id|b-&gt;exponent
op_assign
l_int|0x8000
suffix:semicolon
r_else
id|b-&gt;exponent
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;exponent
op_assign
(paren
(paren
id|a-&gt;b
op_rshift
l_int|20
)paren
op_amp
l_int|0x7ff
)paren
op_minus
l_int|1023
op_plus
l_int|16383
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;b
OL
l_int|0
)paren
id|b-&gt;exponent
op_or_assign
l_int|0x8000
suffix:semicolon
id|b-&gt;b
op_assign
l_int|0x80000000
op_or
(paren
id|a-&gt;b
op_lshift
l_int|11
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|a-&gt;a
)paren
op_rshift
l_int|21
)paren
suffix:semicolon
id|b-&gt;a
op_assign
id|a-&gt;a
op_lshift
l_int|11
suffix:semicolon
)brace
DECL|function|temp_to_short
r_void
id|temp_to_short
c_func
(paren
r_const
id|temp_real
op_star
id|a
comma
id|short_real
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|a-&gt;exponent
op_amp
l_int|0x7fff
)paren
)paren
(brace
op_star
id|b
op_assign
(paren
id|a-&gt;exponent
)paren
ques
c_cond
l_int|0x80000000
suffix:colon
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|b
op_assign
(paren
(paren
(paren
(paren
r_int
)paren
id|a-&gt;exponent
)paren
op_minus
l_int|16383
op_plus
l_int|127
)paren
op_lshift
l_int|23
)paren
op_amp
l_int|0x7f800000
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;exponent
OL
l_int|0
)paren
op_star
id|b
op_or_assign
l_int|0x80000000
suffix:semicolon
op_star
id|b
op_or_assign
(paren
id|a-&gt;b
op_rshift
l_int|8
)paren
op_amp
l_int|0x007fffff
suffix:semicolon
r_switch
c_cond
(paren
id|ROUNDING
)paren
(brace
r_case
id|ROUND_NEAREST
suffix:colon
r_if
c_cond
(paren
(paren
id|a-&gt;b
op_amp
l_int|0xff
)paren
OG
l_int|0x80
)paren
op_increment
op_star
id|b
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_DOWN
suffix:colon
r_if
c_cond
(paren
(paren
id|a-&gt;exponent
op_amp
l_int|0x8000
)paren
op_logical_and
(paren
id|a-&gt;b
op_amp
l_int|0xff
)paren
)paren
op_increment
op_star
id|b
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_UP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a-&gt;exponent
op_amp
l_int|0x8000
)paren
op_logical_and
(paren
id|a-&gt;b
op_amp
l_int|0xff
)paren
)paren
op_increment
op_star
id|b
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|temp_to_long
r_void
id|temp_to_long
c_func
(paren
r_const
id|temp_real
op_star
id|a
comma
id|long_real
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|a-&gt;exponent
op_amp
l_int|0x7fff
)paren
)paren
(brace
id|b-&gt;a
op_assign
l_int|0
suffix:semicolon
id|b-&gt;b
op_assign
(paren
id|a-&gt;exponent
)paren
ques
c_cond
l_int|0x80000000
suffix:colon
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;b
op_assign
(paren
(paren
(paren
l_int|0x7fff
op_amp
(paren
r_int
)paren
id|a-&gt;exponent
)paren
op_minus
l_int|16383
op_plus
l_int|1023
)paren
op_lshift
l_int|20
)paren
op_amp
l_int|0x7ff00000
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;exponent
OL
l_int|0
)paren
id|b-&gt;b
op_or_assign
l_int|0x80000000
suffix:semicolon
id|b-&gt;b
op_or_assign
(paren
id|a-&gt;b
op_rshift
l_int|11
)paren
op_amp
l_int|0x000fffff
suffix:semicolon
id|b-&gt;a
op_assign
id|a-&gt;b
op_lshift
l_int|21
suffix:semicolon
id|b-&gt;a
op_or_assign
(paren
id|a-&gt;a
op_rshift
l_int|11
)paren
op_amp
l_int|0x001fffff
suffix:semicolon
r_switch
c_cond
(paren
id|ROUNDING
)paren
(brace
r_case
id|ROUND_NEAREST
suffix:colon
r_if
c_cond
(paren
(paren
id|a-&gt;a
op_amp
l_int|0x7ff
)paren
OG
l_int|0x400
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_DOWN
suffix:colon
r_if
c_cond
(paren
(paren
id|a-&gt;exponent
op_amp
l_int|0x8000
)paren
op_logical_and
(paren
id|a-&gt;b
op_amp
l_int|0xff
)paren
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_UP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a-&gt;exponent
op_amp
l_int|0x8000
)paren
op_logical_and
(paren
id|a-&gt;b
op_amp
l_int|0xff
)paren
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|frndint
r_void
id|frndint
c_func
(paren
r_const
id|temp_real
op_star
id|a
comma
id|temp_real
op_star
id|b
)paren
(brace
r_int
id|shift
op_assign
l_int|16383
op_plus
l_int|63
op_minus
(paren
id|a-&gt;exponent
op_amp
l_int|0x7fff
)paren
suffix:semicolon
r_int
r_int
id|underflow
suffix:semicolon
r_if
c_cond
(paren
(paren
id|shift
OL
l_int|0
)paren
op_logical_or
(paren
id|shift
op_eq
l_int|16383
op_plus
l_int|63
)paren
)paren
(brace
op_star
id|b
op_assign
op_star
id|a
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;a
op_assign
id|b-&gt;b
op_assign
id|underflow
op_assign
l_int|0
suffix:semicolon
id|b-&gt;exponent
op_assign
id|a-&gt;exponent
suffix:semicolon
r_if
c_cond
(paren
id|shift
OL
l_int|32
)paren
(brace
id|b-&gt;b
op_assign
id|a-&gt;b
suffix:semicolon
id|b-&gt;a
op_assign
id|a-&gt;a
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shift
OL
l_int|64
)paren
(brace
id|b-&gt;a
op_assign
id|a-&gt;b
suffix:semicolon
id|underflow
op_assign
id|a-&gt;a
suffix:semicolon
id|shift
op_sub_assign
l_int|32
suffix:semicolon
id|b-&gt;exponent
op_add_assign
l_int|32
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shift
OL
l_int|96
)paren
(brace
id|underflow
op_assign
id|a-&gt;b
suffix:semicolon
id|shift
op_sub_assign
l_int|64
suffix:semicolon
id|b-&gt;exponent
op_add_assign
l_int|64
suffix:semicolon
)brace
r_else
(brace
id|underflow
op_assign
l_int|1
suffix:semicolon
id|shift
op_assign
l_int|0
suffix:semicolon
)brace
id|b-&gt;exponent
op_add_assign
id|shift
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shrdl %2,%1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|underflow
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|underflow
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;a
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shrdl %2,%1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shrl %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ROUNDING
)paren
(brace
r_case
id|ROUND_NEAREST
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;addl %4,%5 ; adcl $0,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x7fffffff
op_plus
(paren
id|b-&gt;a
op_amp
l_int|1
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|underflow
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_UP
suffix:colon
r_if
c_cond
(paren
(paren
id|b-&gt;exponent
op_ge
l_int|0
)paren
op_logical_and
id|underflow
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_DOWN
suffix:colon
r_if
c_cond
(paren
(paren
id|b-&gt;exponent
OL
l_int|0
)paren
op_logical_and
id|underflow
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b-&gt;a
op_logical_or
id|b-&gt;b
)paren
r_while
c_loop
(paren
id|b-&gt;b
op_ge
l_int|0
)paren
(brace
id|b-&gt;exponent
op_decrement
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;addl %0,%0 ; adcl %1,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
)brace
r_else
id|b-&gt;exponent
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|real_to_int
r_void
id|real_to_int
c_func
(paren
r_const
id|temp_real
op_star
id|a
comma
id|temp_int
op_star
id|b
)paren
(brace
r_int
id|shift
op_assign
l_int|16383
op_plus
l_int|63
op_minus
(paren
id|a-&gt;exponent
op_amp
l_int|0x7fff
)paren
suffix:semicolon
r_int
r_int
id|underflow
suffix:semicolon
id|b-&gt;a
op_assign
id|b-&gt;b
op_assign
id|underflow
op_assign
l_int|0
suffix:semicolon
id|b-&gt;sign
op_assign
(paren
id|a-&gt;exponent
OL
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
(brace
id|set_OE
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
id|shift
OL
l_int|32
)paren
(brace
id|b-&gt;b
op_assign
id|a-&gt;b
suffix:semicolon
id|b-&gt;a
op_assign
id|a-&gt;a
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shift
OL
l_int|64
)paren
(brace
id|b-&gt;a
op_assign
id|a-&gt;b
suffix:semicolon
id|underflow
op_assign
id|a-&gt;a
suffix:semicolon
id|shift
op_sub_assign
l_int|32
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shift
OL
l_int|96
)paren
(brace
id|underflow
op_assign
id|a-&gt;b
suffix:semicolon
id|shift
op_sub_assign
l_int|64
suffix:semicolon
)brace
r_else
(brace
id|underflow
op_assign
l_int|1
suffix:semicolon
id|shift
op_assign
l_int|0
suffix:semicolon
)brace
id|__asm__
c_func
(paren
l_string|&quot;shrdl %2,%1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|underflow
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|underflow
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;a
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shrdl %2,%1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;shrl %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
(paren
r_char
)paren
id|shift
)paren
comma
l_string|&quot;0&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ROUNDING
)paren
(brace
r_case
id|ROUND_NEAREST
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;addl %4,%5 ; adcl $0,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x7fffffff
op_plus
(paren
id|b-&gt;a
op_amp
l_int|1
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|underflow
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_UP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|b-&gt;sign
op_logical_and
id|underflow
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUND_DOWN
suffix:colon
r_if
c_cond
(paren
id|b-&gt;sign
op_logical_and
id|underflow
)paren
id|__asm__
c_func
(paren
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|int_to_real
r_void
id|int_to_real
c_func
(paren
r_const
id|temp_int
op_star
id|a
comma
id|temp_real
op_star
id|b
)paren
(brace
id|b-&gt;a
op_assign
id|a-&gt;a
suffix:semicolon
id|b-&gt;b
op_assign
id|a-&gt;b
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;a
op_logical_or
id|b-&gt;b
)paren
id|b-&gt;exponent
op_assign
l_int|16383
op_plus
l_int|63
op_plus
(paren
id|a-&gt;sign
ques
c_cond
l_int|0x8000
suffix:colon
l_int|0
)paren
suffix:semicolon
r_else
(brace
id|b-&gt;exponent
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|b-&gt;b
op_ge
l_int|0
)paren
(brace
id|b-&gt;exponent
op_decrement
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;addl %0,%0 ; adcl %1,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|b-&gt;b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|b-&gt;a
)paren
comma
l_string|&quot;1&quot;
(paren
id|b-&gt;b
)paren
)paren
suffix:semicolon
)brace
)brace
eof
