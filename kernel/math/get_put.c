multiline_comment|/*&n; * linux/kernel/math/get_put.c&n; *&n; * (C) 1991 Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles all accesses to user memory: getting and putting&n; * ints/reals/BCD etc. This is the only part that concerns itself with&n; * other than temporary real format. All other cals are strictly temp_real.&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;linux/math_emu.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|function|get_short_real
r_void
id|get_short_real
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|short_real
id|sr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|sr
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|short_to_temp
c_func
(paren
op_amp
id|sr
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|get_long_real
r_void
id|get_long_real
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|long_real
id|lr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|lr.a
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|lr.b
op_assign
id|get_fs_long
c_func
(paren
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|long_to_temp
c_func
(paren
op_amp
id|lr
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|get_temp_real
r_void
id|get_temp_real
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|tmp-&gt;a
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|tmp-&gt;b
op_assign
id|get_fs_long
c_func
(paren
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|tmp-&gt;exponent
op_assign
id|get_fs_word
c_func
(paren
l_int|4
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|get_short_int
r_void
id|get_short_int
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|ti.a
op_assign
(paren
r_int
r_int
)paren
id|get_fs_word
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|ti.b
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
op_assign
(paren
id|ti.a
OL
l_int|0
)paren
)paren
id|ti.a
op_assign
op_minus
id|ti.a
suffix:semicolon
id|int_to_real
c_func
(paren
op_amp
id|ti
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|get_long_int
r_void
id|get_long_int
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|ti.a
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|ti.b
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
op_assign
(paren
id|ti.a
OL
l_int|0
)paren
)paren
id|ti.a
op_assign
op_minus
id|ti.a
suffix:semicolon
id|int_to_real
c_func
(paren
op_amp
id|ti
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|get_longlong_int
r_void
id|get_longlong_int
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|ti.a
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|ti.b
op_assign
id|get_fs_long
c_func
(paren
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
op_assign
(paren
id|ti.b
OL
l_int|0
)paren
)paren
id|__asm__
c_func
(paren
l_string|&quot;notl %0 ; notl %1&bslash;n&bslash;t&quot;
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti.a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ti.b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ti.a
)paren
comma
l_string|&quot;1&quot;
(paren
id|ti.b
)paren
)paren
suffix:semicolon
id|int_to_real
c_func
(paren
op_amp
id|ti
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|macro|MUL10
mdefine_line|#define MUL10(low,high) &bslash;&n;__asm__(&quot;addl %0,%0 ; adcl %1,%1&bslash;n&bslash;t&quot; &bslash;&n;&quot;movl %0,%%ecx ; movl %1,%%ebx&bslash;n&bslash;t&quot; &bslash;&n;&quot;addl %0,%0 ; adcl %1,%1&bslash;n&bslash;t&quot; &bslash;&n;&quot;addl %0,%0 ; adcl %1,%1&bslash;n&bslash;t&quot; &bslash;&n;&quot;addl %%ecx,%0 ; adcl %%ebx,%1&quot; &bslash;&n;:&quot;=a&quot; (low),&quot;=d&quot; (high) &bslash;&n;:&quot;0&quot; (low),&quot;1&quot; (high):&quot;cx&quot;,&quot;bx&quot;)
DECL|macro|ADD64
mdefine_line|#define ADD64(val,low,high) &bslash;&n;__asm__(&quot;addl %4,%0 ; adcl $0,%1&quot;:&quot;=r&quot; (low),&quot;=r&quot; (high) &bslash;&n;:&quot;0&quot; (low),&quot;1&quot; (high),&quot;r&quot; ((unsigned long) (val)))
DECL|function|get_BCD
r_void
id|get_BCD
c_func
(paren
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_int
id|k
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|i
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|9
suffix:semicolon
id|i.sign
op_assign
l_int|0x80
op_amp
id|get_fs_byte
c_func
(paren
id|addr
op_decrement
)paren
suffix:semicolon
id|i.a
op_assign
id|i.b
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|9
suffix:semicolon
id|k
op_increment
)paren
(brace
id|c
op_assign
id|get_fs_byte
c_func
(paren
id|addr
op_decrement
)paren
suffix:semicolon
id|MUL10
c_func
(paren
id|i.a
comma
id|i.b
)paren
suffix:semicolon
id|ADD64
c_func
(paren
(paren
id|c
op_rshift
l_int|4
)paren
comma
id|i.a
comma
id|i.b
)paren
suffix:semicolon
id|MUL10
c_func
(paren
id|i.a
comma
id|i.b
)paren
suffix:semicolon
id|ADD64
c_func
(paren
(paren
id|c
op_amp
l_int|0xf
)paren
comma
id|i.a
comma
id|i.b
)paren
suffix:semicolon
)brace
id|int_to_real
c_func
(paren
op_amp
id|i
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|put_short_real
r_void
id|put_short_real
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|short_real
id|sr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|4
)paren
suffix:semicolon
id|temp_to_short
c_func
(paren
id|tmp
comma
op_amp
id|sr
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sr
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|put_long_real
r_void
id|put_long_real
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|long_real
id|lr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|8
)paren
suffix:semicolon
id|temp_to_long
c_func
(paren
id|tmp
comma
op_amp
id|lr
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|lr.a
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|lr.b
comma
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|put_temp_real
r_void
id|put_temp_real
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|10
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp-&gt;a
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|tmp-&gt;b
comma
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|tmp-&gt;exponent
comma
l_int|4
op_plus
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|put_short_int
r_void
id|put_short_int
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|real_to_int
c_func
(paren
id|tmp
comma
op_amp
id|ti
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
)paren
id|ti.a
op_assign
op_minus
id|ti.a
suffix:semicolon
id|put_fs_word
c_func
(paren
id|ti.a
comma
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|put_long_int
r_void
id|put_long_int
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|real_to_int
c_func
(paren
id|tmp
comma
op_amp
id|ti
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
)paren
id|ti.a
op_assign
op_minus
id|ti.a
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ti.a
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|put_longlong_int
r_void
id|put_longlong_int
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|ti
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|real_to_int
c_func
(paren
id|tmp
comma
op_amp
id|ti
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ti.sign
)paren
id|__asm__
c_func
(paren
l_string|&quot;notl %0 ; notl %1&bslash;n&bslash;t&quot;
l_string|&quot;addl $1,%0 ; adcl $0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti.a
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ti.b
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ti.a
)paren
comma
l_string|&quot;1&quot;
(paren
id|ti.b
)paren
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ti.a
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ti.b
comma
l_int|1
op_plus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|DIV10
mdefine_line|#define DIV10(low,high,rem) &bslash;&n;__asm__(&quot;divl %6 ; xchgl %1,%2 ; divl %6&quot; &bslash;&n;&t;:&quot;=d&quot; (rem),&quot;=a&quot; (low),&quot;=b&quot; (high) &bslash;&n;&t;:&quot;0&quot; (0),&quot;1&quot; (high),&quot;2&quot; (low),&quot;c&quot; (10))
DECL|function|put_BCD
r_void
id|put_BCD
c_func
(paren
r_const
id|temp_real
op_star
id|tmp
comma
r_struct
id|info
op_star
id|info
comma
r_int
r_int
id|code
)paren
(brace
r_int
id|k
comma
id|rem
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|temp_int
id|i
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|addr
op_assign
id|ea
c_func
(paren
id|info
comma
id|code
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|addr
comma
l_int|10
)paren
suffix:semicolon
id|real_to_int
c_func
(paren
id|tmp
comma
op_amp
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i.sign
)paren
id|put_fs_byte
c_func
(paren
l_int|0x80
comma
id|addr
op_plus
l_int|9
)paren
suffix:semicolon
r_else
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|addr
op_plus
l_int|9
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|9
suffix:semicolon
id|k
op_increment
)paren
(brace
id|DIV10
c_func
(paren
id|i.a
comma
id|i.b
comma
id|rem
)paren
suffix:semicolon
id|c
op_assign
id|rem
suffix:semicolon
id|DIV10
c_func
(paren
id|i.a
comma
id|i.b
comma
id|rem
)paren
suffix:semicolon
id|c
op_add_assign
id|rem
op_lshift
l_int|4
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|c
comma
id|addr
op_increment
)paren
suffix:semicolon
)brace
)brace
eof
