multiline_comment|/*&n; * $Id: bitops.h,v 1.7 1997/08/03 00:12:07 paulus Exp $&n; * bitops.h: Bit string operations on the ppc&n; */
macro_line|#ifndef _ASM_PPC_BITOPS_H_
DECL|macro|_ASM_PPC_BITOPS_H_
mdefine_line|#define _ASM_PPC_BITOPS_H_
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
r_extern
r_void
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * These are if&squot;d out here because using : &quot;cc&quot; as a constraint&n; * results in errors from gcc. -- Cort&n; * Besides, they need to be changed so we have both set_bit&n; * and test_and_set_bit, etc.&n; */
macro_line|#if 0
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
id|addr
)paren
(brace
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:lwarx %0,0,%3 &bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1,%0,%2 &bslash;n&bslash;t&quot;
l_string|&quot;stwcx.&t;%1,0,%3 &bslash;n&bslash;t&quot;
l_string|&quot;bne&t;1b &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
multiline_comment|/*, &quot;=m&quot; (*p)*/
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
multiline_comment|/*: &quot;cc&quot; */
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
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
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;&bslash;"
id|n
"&bslash;"
l_int|1
suffix:colon
id|lwarx
op_mod
l_int|0
comma
l_int|0
comma
op_mod
l_int|3
id|andc
op_mod
l_int|1
comma
op_mod
l_int|0
comma
op_mod
l_int|2
id|stwcx
dot
op_mod
l_int|1
comma
l_int|0
comma
op_mod
l_int|3
id|bne
l_int|1
id|b
"&quot;"
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
multiline_comment|/*, &quot;=m&quot; (*p)*/
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
multiline_comment|/*: &quot;cc&quot;*/
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
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
id|old
comma
id|t
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;&bslash;"
id|n
"&bslash;"
l_int|1
suffix:colon
id|lwarx
op_mod
l_int|0
comma
l_int|0
comma
op_mod
l_int|3
op_xor
op_mod
l_int|1
comma
op_mod
l_int|0
comma
op_mod
l_int|2
id|stwcx
dot
op_mod
l_int|1
comma
l_int|0
comma
op_mod
l_int|3
id|bne
l_int|1
id|b
"&quot;"
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
multiline_comment|/*, &quot;=m&quot; (*p)*/
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
multiline_comment|/*: &quot;cc&quot;*/
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
id|__const__
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__const__
r_int
r_int
op_star
id|p
op_assign
(paren
id|__const__
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_return
(paren
id|p
(braket
id|nr
op_rshift
l_int|5
)braket
op_rshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1UL
suffix:semicolon
)brace
DECL|function|ffz
r_extern
id|__inline__
r_int
id|ffz
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
op_complement
l_int|0
)paren
r_return
l_int|32
suffix:semicolon
id|x
op_assign
op_complement
id|x
op_amp
(paren
id|x
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* set LS zero to 1, other bits to 0 */
id|__asm__
(paren
l_string|&quot;cntlzw %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|31
op_minus
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * This implementation of find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
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
l_int|5
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
id|p
op_increment
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
id|tmp
op_ne
op_complement
l_int|0U
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
op_ge
l_int|32
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_star
id|p
op_increment
)paren
op_ne
op_complement
l_int|0U
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
DECL|macro|_EXT2_HAVE_ASM_BITOPS_
mdefine_line|#define _EXT2_HAVE_ASM_BITOPS_
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * test_and_{set,clear}_bit guarantee atomicity without&n; * disabling interrupts.&n; */
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)&t;&t;test_and_set_bit((nr) ^ 0x18, addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr)&t;test_and_clear_bit((nr) ^ 0x18, addr)
macro_line|#else
DECL|function|ext2_set_bit
r_extern
id|__inline__
r_int
id|ext2_set_bit
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
r_int
id|mask
suffix:semicolon
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|ADDR
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|ADDR
op_or_assign
id|mask
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
DECL|function|ext2_clear_bit
r_extern
id|__inline__
r_int
id|ext2_clear_bit
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
r_int
id|mask
suffix:semicolon
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|ADDR
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|ADDR
op_assign
op_star
id|ADDR
op_amp
op_complement
id|mask
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
DECL|function|ext2_test_bit
r_extern
id|__inline__
r_int
id|ext2_test_bit
c_func
(paren
r_int
id|nr
comma
id|__const__
r_void
op_star
id|addr
)paren
(brace
id|__const__
r_int
r_char
op_star
id|ADDR
op_assign
(paren
id|__const__
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_return
(paren
id|ADDR
(braket
id|nr
op_rshift
l_int|3
)braket
op_rshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This implementation of ext2_find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h and modified for a big-endian machine.&n; */
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;        ext2_find_next_zero_bit((addr), (size), 0)
DECL|function|ext2_find_next_zero_bit
r_extern
id|__inline__
r_int
r_int
id|ext2_find_next_zero_bit
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
l_int|5
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
id|cpu_to_le32p
c_func
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
id|tmp
op_ne
op_complement
l_int|0U
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
op_ge
l_int|32
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|cpu_to_le32p
c_func
(paren
id|p
op_increment
)paren
)paren
op_ne
op_complement
l_int|0U
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
id|cpu_to_le32p
c_func
(paren
id|p
)paren
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_or_assign
op_complement
l_int|0U
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
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) ext2_set_bit(nr,addr)
DECL|macro|minix_clear_bit
mdefine_line|#define minix_clear_bit(nr,addr) ext2_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) ext2_test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) ext2_find_first_zero_bit(addr,size)
macro_line|#endif /* _ASM_PPC_BITOPS_H */
eof
