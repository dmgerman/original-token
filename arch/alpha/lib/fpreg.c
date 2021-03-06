multiline_comment|/*&n; * arch/alpha/lib/fpreg.c&n; *&n; * (C) Copyright 1998 Linus Torvalds&n; */
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
DECL|macro|STT
mdefine_line|#define STT(reg,val)  asm volatile (&quot;ftoit $f&quot;#reg&quot;,%0&quot; : &quot;=r&quot;(val));
macro_line|#else
DECL|macro|STT
mdefine_line|#define STT(reg,val)  asm volatile (&quot;stt $f&quot;#reg&quot;,%0&quot; : &quot;=m&quot;(val));
macro_line|#endif
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
id|val
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
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
id|STT
c_func
(paren
l_int|31
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
DECL|macro|LDT
mdefine_line|#define LDT(reg,val)  asm volatile (&quot;itoft %0,$f&quot;#reg : : &quot;r&quot;(val));
macro_line|#else
DECL|macro|LDT
mdefine_line|#define LDT(reg,val)  asm volatile (&quot;ldt $f&quot;#reg&quot;,%0&quot; : : &quot;m&quot;(val));
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
)brace
)brace
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
DECL|macro|STS
mdefine_line|#define STS(reg,val)  asm volatile (&quot;ftois $f&quot;#reg&quot;,%0&quot; : &quot;=r&quot;(val));
macro_line|#else
DECL|macro|STS
mdefine_line|#define STS(reg,val)  asm volatile (&quot;sts $f&quot;#reg&quot;,%0&quot; : &quot;=m&quot;(val));
macro_line|#endif
r_int
r_int
DECL|function|alpha_read_fp_reg_s
id|alpha_read_fp_reg_s
(paren
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|val
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
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
id|STS
c_func
(paren
l_int|31
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
DECL|macro|LDS
mdefine_line|#define LDS(reg,val)  asm volatile (&quot;itofs %0,$f&quot;#reg : : &quot;r&quot;(val));
macro_line|#else
DECL|macro|LDS
mdefine_line|#define LDS(reg,val)  asm volatile (&quot;lds $f&quot;#reg&quot;,%0&quot; : : &quot;m&quot;(val));
macro_line|#endif
r_void
DECL|function|alpha_write_fp_reg_s
id|alpha_write_fp_reg_s
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
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
id|LDS
c_func
(paren
l_int|31
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof
