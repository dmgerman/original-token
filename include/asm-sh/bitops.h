macro_line|#ifndef __ASM_SH_BITOPS_H
DECL|macro|__ASM_SH_BITOPS_H
mdefine_line|#define __ASM_SH_BITOPS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* For __swab32 */
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|function|set_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|a
op_or_assign
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_bit() doesn&squot;t provide any barrier for the compiler.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier()
DECL|function|clear_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|a
op_and_assign
op_complement
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|change_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|a
op_xor_assign
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|test_and_set_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|a
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|a
op_or_assign
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_and_clear_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|a
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|a
op_and_assign
op_complement
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_and_change_bit
r_static
id|__inline__
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
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|a
op_assign
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|a
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|a
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|a
op_xor_assign
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|test_bit
r_static
id|__inline__
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_volatile
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
r_const
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|5
)braket
op_rshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
DECL|function|ffz
r_static
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
r_int
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;shlr&t;%1&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_complement
l_int|0L
)paren
comma
l_string|&quot;1&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|find_next_zero_bit
r_static
id|__inline__
r_int
id|find_next_zero_bit
c_func
(paren
r_void
op_star
id|addr
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
l_int|31UL
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
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;        find_next_zero_bit((addr), (size), 0)
macro_line|#ifdef __LITTLE_ENDIAN__
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr) test_and_set_bit((nr), (addr))
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr) test_and_clear_bit((nr), (addr))
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr, addr) test_bit((nr), (addr))
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) find_first_zero_bit((addr), (size))
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(addr, size, offset) &bslash;&n;                find_next_zero_bit((addr), (size), (offset))
macro_line|#else
DECL|function|ext2_set_bit
r_static
id|__inline__
r_int
id|ext2_set_bit
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
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_volatile
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|ADDR
op_or_assign
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ext2_clear_bit
r_static
id|__inline__
r_int
id|ext2_clear_bit
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
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_volatile
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
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|ADDR
op_and_assign
op_complement
id|mask
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ext2_test_bit
r_static
id|__inline__
r_int
id|ext2_test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
id|mask
suffix:semicolon
r_const
r_volatile
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_const
r_int
r_char
op_star
)paren
id|addr
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
r_return
(paren
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;        ext2_find_next_zero_bit((addr), (size), 0)
DECL|function|ext2_find_next_zero_bit
r_static
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
multiline_comment|/* We hold the little endian value in tmp, but then the&n;&t;&t; * shift is illegal. So we could keep a big endian value&n;&t;&t; * in tmp, like this:&n;&t;&t; *&n;&t;&t; * tmp = __swab32(*(p++));&n;&t;&t; * tmp |= ~0UL &gt;&gt; (32-offset);&n;&t;&t; *&n;&t;&t; * but this would decrease preformance, so we change the&n;&t;&t; * shift:&n;&t;&t; */
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
id|__swab32
c_func
(paren
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|32
)paren
(brace
r_goto
id|found_first
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|tmp
)paren
(brace
r_goto
id|found_middle
suffix:semicolon
)brace
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
l_int|31UL
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
(brace
r_goto
id|found_middle
suffix:semicolon
)brace
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
(brace
r_return
id|result
suffix:semicolon
)brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
multiline_comment|/* tmp is little endian, so we would have to swab the shift,&n;&t; * see above. But then we have to swab tmp below for ffz, so&n;&t; * we might as well do this here.&n;&t; */
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|__swab32
c_func
(paren
id|tmp
)paren
op_or
(paren
op_complement
l_int|0UL
op_lshift
id|size
)paren
)paren
suffix:semicolon
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|__swab32
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) test_and_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) set_bit(nr,addr)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) test_and_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) find_first_zero_bit(addr,size)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_BITOPS_H */
eof
