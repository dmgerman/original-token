macro_line|#ifndef _ALPHA_BITOPS_H
DECL|macro|_ALPHA_BITOPS_H
mdefine_line|#define _ALPHA_BITOPS_H
multiline_comment|/*&n; * Copyright 1994, Linus Torvalds.&n; */
multiline_comment|/*&n; * These have to be done with inline assembly: that way the bit-setting&n; * is guaranteed to be atomic. All bit operations return 0 if the bit&n; * was cleared before the operation and != 0 if it was not.&n; *&n; * bit 0 is the LSB of addr; bit 64 is the LSB of (addr+1).&n; */
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
r_int
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;and %0,%3,%2&bslash;n&bslash;t&quot;
l_string|&quot;bne %2,2f&bslash;n&bslash;t&quot;
l_string|&quot;xor %0,%3,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|63
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
)paren
suffix:semicolon
r_return
id|oldbit
op_ne
l_int|0
suffix:semicolon
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
r_int
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;and %0,%3,%2&bslash;n&bslash;t&quot;
l_string|&quot;beq %2,2f&bslash;n&bslash;t&quot;
l_string|&quot;xor %0,%3,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|63
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
)paren
suffix:semicolon
r_return
id|oldbit
op_ne
l_int|0
suffix:semicolon
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
r_int
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;and %0,%3,%2&bslash;n&bslash;t&quot;
l_string|&quot;xor %0,%3,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|63
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
)paren
)paren
suffix:semicolon
r_return
id|oldbit
op_ne
l_int|0
suffix:semicolon
)brace
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
r_return
l_int|1UL
op_amp
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|6
)braket
op_rshift
(paren
id|nr
op_amp
l_int|63
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; *&n; * This uses the cmpbge insn to check which byte contains the zero.&n; * I don&squot;t know if that&squot;s actually a good idea, but it&squot;s fun and the&n; * resulting LBS tests should be natural on the alpha.. Besides, I&squot;m&n; * just teaching myself the asm of the alpha anyway.&n; */
DECL|function|ffz
r_extern
r_inline
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
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;cmpbge %1,%0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|word
)paren
comma
l_string|&quot;0&quot;
(paren
op_complement
l_int|0UL
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_amp
l_int|1
)paren
(brace
id|word
op_rshift_assign
l_int|8
suffix:semicolon
id|tmp
op_rshift_assign
l_int|1
suffix:semicolon
id|result
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
id|word
op_amp
l_int|1
)paren
(brace
id|result
op_increment
suffix:semicolon
id|word
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Find next zero bit in a bitmap reasonably efficiently..&n; */
DECL|function|find_next_zero_bit
r_extern
r_inline
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
l_int|63UL
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
l_int|63UL
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
l_int|64
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|64
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
l_int|64
suffix:semicolon
id|result
op_add_assign
l_int|64
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|63UL
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
l_int|64
suffix:semicolon
id|size
op_sub_assign
l_int|64
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
multiline_comment|/*&n; * The optimizer actually does good code for this case..&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
macro_line|#endif /* _ALPHA_BITOPS_H */
eof
