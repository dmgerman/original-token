multiline_comment|/*&n; * kernel/fpreg.c&n; *&n; * (C) Copyright 1998 Linus Torvalds&n; */
r_int
r_int
DECL|function|alpha_read_fp_reg
id|alpha_read_fp_reg
(paren
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|r
suffix:semicolon
r_switch
c_cond
(paren
id|reg
)paren
(brace
r_case
l_int|0
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f0,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f1,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f2,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f3,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f4,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f5,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f6,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f7,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f8,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|asm
(paren
l_string|&quot;stt  $f9,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|asm
(paren
l_string|&quot;stt $f10,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|asm
(paren
l_string|&quot;stt $f11,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|asm
(paren
l_string|&quot;stt $f12,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|asm
(paren
l_string|&quot;stt $f13,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|asm
(paren
l_string|&quot;stt $f14,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|asm
(paren
l_string|&quot;stt $f15,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|asm
(paren
l_string|&quot;stt $f16,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
suffix:colon
id|asm
(paren
l_string|&quot;stt $f17,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|18
suffix:colon
id|asm
(paren
l_string|&quot;stt $f18,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19
suffix:colon
id|asm
(paren
l_string|&quot;stt $f19,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|20
suffix:colon
id|asm
(paren
l_string|&quot;stt $f20,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|21
suffix:colon
id|asm
(paren
l_string|&quot;stt $f21,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|22
suffix:colon
id|asm
(paren
l_string|&quot;stt $f22,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|23
suffix:colon
id|asm
(paren
l_string|&quot;stt $f23,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|asm
(paren
l_string|&quot;stt $f24,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
id|asm
(paren
l_string|&quot;stt $f25,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|26
suffix:colon
id|asm
(paren
l_string|&quot;stt $f26,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|27
suffix:colon
id|asm
(paren
l_string|&quot;stt $f27,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|28
suffix:colon
id|asm
(paren
l_string|&quot;stt $f28,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|29
suffix:colon
id|asm
(paren
l_string|&quot;stt $f29,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|30
suffix:colon
id|asm
(paren
l_string|&quot;stt $f30,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|31
suffix:colon
id|asm
(paren
l_string|&quot;stt $f31,%0&quot;
suffix:colon
l_string|&quot;m=&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
macro_line|#if 1
multiline_comment|/*&n; * This is IMHO the better way of implementing LDT().  But it&n; * has the disadvantage that gcc 2.7.0 refuses to compile it&n; * (invalid operand constraints), so instead, we use the uglier&n; * macro below.&n; */
DECL|macro|LDT
macro_line|# define LDT(reg,val)&t;&bslash;&n;  asm volatile (&quot;ldt $f&quot;#reg&quot;,%0&quot; : : &quot;m&quot;(val));
macro_line|#else
DECL|macro|LDT
macro_line|# define LDT(reg,val)&t;&bslash;&n;  asm volatile (&quot;ldt $f&quot;#reg&quot;,0(%0)&quot; : : &quot;r&quot;(&amp;val));
macro_line|#endif
r_void
DECL|function|alpha_write_fp_reg
id|alpha_write_fp_reg
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
(brace
r_switch
c_cond
(paren
id|reg
)paren
(brace
r_case
l_int|0
suffix:colon
id|LDT
c_func
(paren
l_int|0
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|LDT
c_func
(paren
l_int|1
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|LDT
c_func
(paren
l_int|2
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|LDT
c_func
(paren
l_int|3
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|LDT
c_func
(paren
l_int|4
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|LDT
c_func
(paren
l_int|5
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|LDT
c_func
(paren
l_int|6
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|LDT
c_func
(paren
l_int|7
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|LDT
c_func
(paren
l_int|8
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|LDT
c_func
(paren
l_int|9
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|LDT
c_func
(paren
l_int|10
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|LDT
c_func
(paren
l_int|11
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|LDT
c_func
(paren
l_int|12
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|LDT
c_func
(paren
l_int|13
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|LDT
c_func
(paren
l_int|14
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|LDT
c_func
(paren
l_int|15
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|LDT
c_func
(paren
l_int|16
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
suffix:colon
id|LDT
c_func
(paren
l_int|17
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|18
suffix:colon
id|LDT
c_func
(paren
l_int|18
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19
suffix:colon
id|LDT
c_func
(paren
l_int|19
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|20
suffix:colon
id|LDT
c_func
(paren
l_int|20
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|21
suffix:colon
id|LDT
c_func
(paren
l_int|21
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|22
suffix:colon
id|LDT
c_func
(paren
l_int|22
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|23
suffix:colon
id|LDT
c_func
(paren
l_int|23
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|LDT
c_func
(paren
l_int|24
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
id|LDT
c_func
(paren
l_int|25
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|26
suffix:colon
id|LDT
c_func
(paren
l_int|26
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|27
suffix:colon
id|LDT
c_func
(paren
l_int|27
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|28
suffix:colon
id|LDT
c_func
(paren
l_int|28
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|29
suffix:colon
id|LDT
c_func
(paren
l_int|29
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|30
suffix:colon
id|LDT
c_func
(paren
l_int|30
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|31
suffix:colon
id|LDT
c_func
(paren
l_int|31
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
eof