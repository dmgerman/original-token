macro_line|#ifndef _ASM_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; */
macro_line|#ifdef i386
multiline_comment|/*&n; * These have to be done with inline assembly: that way the bit-setting&n; * is guaranteed to be atomic. Both set_bit and clear_bit return 0&n; * if the bit-setting went ok, != 0 if the bit already was set/cleared.&n; *&n; * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).&n; */
DECL|function|set_bit
r_extern
r_inline
r_int
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_char
id|ok
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btsl %1,%2&bslash;n&bslash;tsetb %0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|ok
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
DECL|function|clear_bit
r_extern
r_inline
r_int
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_char
id|ok
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btrl %1,%2&bslash;n&bslash;tsetnb %0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|ok
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine doesn&squot;t need to be atomic, but it&squot;s faster to code it&n; * this way.&n; */
DECL|function|test_bit
r_extern
r_inline
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_char
id|ok
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btl %1,%2&bslash;n&bslash;tsetb %0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|ok
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * For the benefit of those who are trying to port Linux to another&n; * architecture, here are some C-language equivalents.  You should&n; * recode these in the native assmebly language, if at all possible.&n; * To guarantee atomicity, these routines call cli() and sti() to&n; * disable interrupts while they operate.  (You have to provide inline&n; * routines to cli() and sti().)&n; *&n; * Also note, these routines assume that you have 32 bit integers.&n; * You will have to change this if you are trying to port Linux to the&n; * Alpha architecture or to a Cray.  :-)&n; * &n; * C language equivalents written by Theodore Ts&squot;o, 9/26/92&n; */
DECL|function|set_bit
r_extern
r_inline
r_int
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|clear_bit
r_extern
r_inline
r_int
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_eq
l_int|0
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_bit
r_extern
r_inline
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
suffix:semicolon
id|addr
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
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
r_return
(paren
(paren
id|mask
op_amp
op_star
id|addr
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* i386 */
macro_line|#endif /* _ASM_BITOPS_H */
eof