macro_line|#ifndef _M68K_BITOPS_H
DECL|macro|_M68K_BITOPS_H
mdefine_line|#define _M68K_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Require 68020 or better.&n; *&n; * They use the standard big-endian m680x0 bit ordering.&n; */
DECL|function|test_and_set_bit
r_extern
id|__inline__
r_int
id|test_and_set_bit
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
op_xor
l_int|31
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
DECL|function|set_bit
r_extern
id|__inline__
r_void
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
)brace
DECL|function|test_and_clear_bit
r_extern
id|__inline__
r_int
id|test_and_clear_bit
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
op_xor
l_int|31
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
r_void
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
)brace
DECL|function|test_and_change_bit
r_extern
id|__inline__
r_int
id|test_and_change_bit
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
op_xor
l_int|31
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
r_void
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfchg %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
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
r_return
(paren
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|5
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|find_first_zero_bit
r_extern
id|__inline__
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
op_star
id|p
op_assign
id|vaddr
comma
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
r_int
id|allones
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
r_int
id|num
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
id|size
op_assign
(paren
id|size
op_rshift
l_int|5
)paren
op_plus
(paren
(paren
id|size
op_amp
l_int|31
)paren
OG
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_increment
op_eq
id|allones
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|5
suffix:semicolon
)brace
id|num
op_assign
op_complement
op_star
op_decrement
id|p
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
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
(paren
id|res
op_xor
l_int|31
)paren
suffix:semicolon
)brace
DECL|function|find_next_zero_bit
r_extern
id|__inline__
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
l_int|31UL
comma
id|res
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
r_if
c_cond
(paren
id|bit
)paren
(brace
r_int
r_int
id|num
op_assign
op_complement
op_star
id|p
op_amp
(paren
op_complement
l_int|0UL
op_lshift
id|bit
)paren
suffix:semicolon
multiline_comment|/* Look for zero in first longword */
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|32
)paren
r_return
(paren
id|offset
op_amp
op_complement
l_int|31UL
)paren
op_plus
(paren
id|res
op_xor
l_int|31
)paren
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
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_complement
id|word
op_amp
op_minus
op_complement
id|word
)paren
)paren
suffix:semicolon
r_return
id|res
op_xor
l_int|31
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the minix filesystem */
r_extern
id|__inline__
r_int
DECL|function|minix_find_first_zero_bit
id|minix_find_first_zero_bit
(paren
r_const
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
comma
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
r_int
id|num
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
id|size
op_assign
(paren
id|size
op_rshift
l_int|4
)paren
op_plus
(paren
(paren
id|size
op_amp
l_int|15
)paren
OG
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_increment
op_eq
l_int|0xffff
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|4
suffix:semicolon
)brace
id|num
op_assign
op_complement
op_star
op_decrement
id|p
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#16,#16},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
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
l_int|4
)paren
op_plus
(paren
id|res
op_xor
l_int|31
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|minix_set_bit
id|minix_set_bit
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
l_string|&quot;bfset %2{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|15
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|minix_clear_bit
id|minix_clear_bit
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
l_string|&quot;bfclr %2{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|15
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|minix_test_bit
id|minix_test_bit
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
r_return
(paren
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|15
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|4
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the ext2 filesystem. */
r_extern
id|__inline__
r_int
DECL|function|ext2_set_bit
id|ext2_set_bit
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
l_string|&quot;bfset %2{%1,#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|7
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|ext2_clear_bit
id|ext2_clear_bit
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
l_string|&quot;bfclr %2{%1,#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|7
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|ext2_test_bit
id|ext2_test_bit
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
r_return
(paren
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|ext2_find_first_zero_bit
id|ext2_find_first_zero_bit
(paren
r_const
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
comma
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
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
id|size
op_assign
(paren
id|size
op_rshift
l_int|5
)paren
op_plus
(paren
(paren
id|size
op_amp
l_int|31
)paren
OG
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_increment
op_eq
op_complement
l_int|0UL
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|5
suffix:semicolon
)brace
op_decrement
id|p
suffix:semicolon
r_for
c_loop
(paren
id|res
op_assign
l_int|0
suffix:semicolon
id|res
OL
l_int|32
suffix:semicolon
id|res
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
(paren
id|res
comma
id|p
)paren
)paren
r_break
suffix:semicolon
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|ext2_find_next_zero_bit
id|ext2_find_next_zero_bit
(paren
r_const
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
r_const
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_const
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
id|bit
op_assign
id|offset
op_amp
l_int|31UL
comma
id|res
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
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/* Look for zero in first longword */
r_for
c_loop
(paren
id|res
op_assign
id|bit
suffix:semicolon
id|res
OL
l_int|32
suffix:semicolon
id|res
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
(paren
id|res
comma
id|p
)paren
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* No zero yet, search remaining full bytes for a zero */
id|res
op_assign
id|ext2_find_first_zero_bit
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
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
)brace
multiline_comment|/* Byte swapping. */
r_extern
id|__inline__
r_int
r_int
DECL|function|swab16
id|swab16
(paren
r_int
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_lshift
l_int|8
)paren
op_or
(paren
id|val
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|swab32
id|swab32
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
(paren
l_string|&quot;rolw #8,%0; swap %0; rolw #8,%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
macro_line|#endif /* _M68K_BITOPS_H */
eof
