macro_line|#ifndef _SPARC_BITOPS_H
DECL|macro|_SPARC_BITOPS_H
mdefine_line|#define _SPARC_BITOPS_H
multiline_comment|/*&n; * Copyright 1994, David S. Miller (davem@caip.rutgers.edu).&n; */
multiline_comment|/* Set bit &squot;nr&squot; in 32-bit quantity at address &squot;addr&squot; where bit &squot;0&squot;&n; * is in the highest of the four bytes and bit &squot;31&squot; is the high bit&n; * within the first byte. Sparc is BIG-Endian. Unless noted otherwise&n; * all bit-ops return 0 if bit was previously clear and != 0 otherwise.&n; */
multiline_comment|/* For now, the sun4c implementation will disable and enable traps&n; * in order to insure atomicity. Things will have to be different&n; * for sun4m (ie. SMP) no doubt.&n; */
DECL|function|set_bit
r_extern
id|__inline__
r_int
r_int
id|set_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_register
r_int
r_int
id|retval
comma
id|tmp
comma
id|mask
comma
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %%g0, 0x1, %3&bslash;n&bslash;t&quot;
multiline_comment|/* produce the mask */
l_string|&quot;sll %3, %4, %3&bslash;n&bslash;t&quot;
l_string|&quot;rd %%psr, %5&bslash;n&bslash;t&quot;
multiline_comment|/* read the psr */
l_string|&quot;wr %5, 0x20, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* traps disabled */
l_string|&quot;ld [%1], %2&bslash;n&bslash;t&quot;
multiline_comment|/* critical section */
l_string|&quot;and %3, %2, %0&bslash;n&bslash;t&quot;
l_string|&quot;or  %3, %2, %2&bslash;n&bslash;t&quot;
l_string|&quot;st  %2, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;wr %5, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* re-enable traps */
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;r&quot;
(paren
id|psr
op_assign
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
multiline_comment|/* confuse gcc :-) */
)brace
DECL|function|clear_bit
r_extern
id|__inline__
r_int
r_int
id|clear_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_register
r_int
r_int
id|retval
comma
id|tmp
comma
id|mask
comma
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %%g0, 0x1, %3&bslash;n&bslash;t&quot;
l_string|&quot;sll %3, %4, %3&bslash;n&bslash;t&quot;
l_string|&quot;rd %%psr, %5&bslash;n&bslash;t&quot;
l_string|&quot;wr %5, 0x20, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* disable traps */
l_string|&quot;ld [%1], %2&bslash;n&bslash;t&quot;
l_string|&quot;and %2, %3, %0&bslash;n&bslash;t&quot;
multiline_comment|/* get old bit */
l_string|&quot;andn %2, %3, %2&bslash;n&bslash;t&quot;
multiline_comment|/* set new val */
l_string|&quot;st  %2, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;wr %5, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* enable traps */
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;r&quot;
(paren
id|psr
op_assign
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
multiline_comment|/* confuse gcc ;-) */
)brace
DECL|function|change_bit
r_extern
id|__inline__
r_int
r_int
id|change_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_register
r_int
r_int
id|retval
comma
id|tmp
comma
id|mask
comma
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %%g0, 0x1, %3&bslash;n&bslash;t&quot;
l_string|&quot;sll %3, %4, %3&bslash;n&bslash;t&quot;
l_string|&quot;rd %%psr, %5&bslash;n&bslash;t&quot;
l_string|&quot;wr %5, 0x20, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* disable traps */
l_string|&quot;ld [%1], %2&bslash;n&bslash;t&quot;
l_string|&quot;and %3, %2, %0&bslash;n&bslash;t&quot;
multiline_comment|/* get old bit val */
l_string|&quot;xor %3, %2, %2&bslash;n&bslash;t&quot;
multiline_comment|/* set new val */
l_string|&quot;st  %2, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;wr %5, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* enable traps */
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;r&quot;
(paren
id|psr
op_assign
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
multiline_comment|/* confuse gcc ;-) */
)brace
multiline_comment|/* The following routine need not be atomic. */
DECL|function|test_bit
r_extern
id|__inline__
r_int
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_register
r_int
r_int
id|retval
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%1], %2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, 0x1, %0&bslash;n&bslash;t&quot;
l_string|&quot;sll %0, %3, %0&bslash;n&bslash;t&quot;
l_string|&quot;and %0, %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
multiline_comment|/* confuse gcc :&gt; */
)brace
multiline_comment|/* There has to be a faster way to do this, sigh... */
DECL|function|ffz
r_extern
id|__inline__
r_int
r_int
id|ffz
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_register
r_int
r_int
id|cnt
comma
id|tmp
comma
id|tmp2
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;or %%g0, %3, %2&bslash;n&bslash;t&quot;
l_string|&quot;1: and %2, 0x1, %1&bslash;n&bslash;t&quot;
l_string|&quot;srl %2, 0x1, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp %1, 0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a 1b&bslash;n&bslash;t&quot;
l_string|&quot;add %0, 0x1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cnt
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|tmp
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp2
op_assign
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|word
)paren
)paren
suffix:semicolon
r_return
id|cnt
suffix:semicolon
)brace
multiline_comment|/* find_next_zero_bit() finds the first zero bit in a bit string of length&n; * &squot;size&squot; bits, starting the search at bit &squot;offset&squot;. This is largely based&n; * on Linus&squot;s ALPHA routines, which are pretty portable BTW.&n; */
DECL|function|find_next_zero_bit
r_extern
id|__inline__
r_int
r_int
id|find_next_zero_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|31UL
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
id|size
op_sub_assign
id|result
suffix:semicolon
id|offset
op_and_assign
l_int|31UL
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
suffix:semicolon
id|tmp
op_or_assign
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|32
)paren
r_goto
id|found_first
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|tmp
)paren
r_goto
id|found_middle
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|32UL
)paren
(brace
r_if
c_cond
(paren
op_complement
(paren
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
)paren
)paren
r_goto
id|found_middle
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|result
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_or_assign
op_complement
l_int|0UL
op_lshift
id|size
suffix:semicolon
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/* Linus sez that gcc can optimize the following correctly, we&squot;ll see if this&n; * holds on the Sparc as it does for the ALPHA.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;        find_next_zero_bit((addr), (size), 0)
macro_line|#endif /* defined(_SPARC_BITOPS_H) */
eof
