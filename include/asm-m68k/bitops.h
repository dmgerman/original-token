macro_line|#ifndef _M68K_BITOPS_H
DECL|macro|_M68K_BITOPS_H
mdefine_line|#define _M68K_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Require 68020 or better.&n; *&n; * They don&squot;t use the standard m680x0 bit ordering.&n; * Instead, the use the standard m680x0 bitfield ordering.&n; *&n; * Thus, bit 0 is the MSB of addr; bit 32 is the MSB of (addr+1).&n; */
DECL|function|set_bit
r_extern
id|__inline__
r_int
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|clear_bit
r_extern
id|__inline__
r_int
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|change_bit
r_extern
id|__inline__
r_int
id|change_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfchg %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_bit
r_extern
id|__inline__
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bftst %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|find_first_zero_bit
r_extern
r_inline
r_int
id|find_first_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
r_int
r_int
op_star
id|p
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;    moveq #-1,d0&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
l_string|&quot;    cmpl  %1@+,d0&bslash;n&bslash;t&quot;
l_string|&quot;    bne   2f&bslash;n&bslash;t&quot;
l_string|&quot;    subql #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;    bne   1b&bslash;n&bslash;t&quot;
l_string|&quot;    bra   5f&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
l_string|&quot;    movel %1@-,d0&bslash;n&bslash;t&quot;
l_string|&quot;    notl  d0&bslash;n&bslash;t&quot;
l_string|&quot;    bfffo d0{#0,#0},%0&bslash;n&bslash;t&quot;
l_string|&quot;5:&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
comma
l_string|&quot;=a&quot;
(paren
id|p
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
id|size
op_plus
l_int|31
)paren
op_rshift
l_int|5
)paren
comma
l_string|&quot;1&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|5
)paren
op_plus
id|res
suffix:semicolon
)brace
DECL|function|find_next_zero_bit
r_static
r_inline
r_int
id|find_next_zero_bit
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|set
op_assign
l_int|0
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/* Look for zero in first longword */
id|__asm__
c_func
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_complement
op_star
id|p
op_lshift
id|bit
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|set
op_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* No zero yet, search remaining full bytes for a zero */
id|res
op_assign
id|find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|set
op_plus
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_complement
(paren
id|word
)paren
)paren
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
macro_line|#endif /* _M68K_BITOPS_H */
eof