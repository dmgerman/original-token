multiline_comment|/*&n; *  linux/lib/vsprintf.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/* vsprintf.c -- Lars Wirzenius &amp; Linus Torvalds. */
multiline_comment|/*&n; * Wirzenius wrote this portably, Torvalds fucked it up :-)&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
DECL|function|simple_strtoul
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|base
op_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|base
op_assign
l_int|8
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_char|&squot;x&squot;
)paren
op_logical_and
id|isxdigit
c_func
(paren
id|cp
(braket
l_int|1
)braket
)paren
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|base
op_assign
l_int|16
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|isxdigit
c_func
(paren
op_star
id|cp
)paren
op_logical_and
(paren
id|value
op_assign
id|isdigit
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
op_star
id|cp
op_minus
l_char|&squot;0&squot;
suffix:colon
(paren
id|islower
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
id|toupper
c_func
(paren
op_star
id|cp
)paren
suffix:colon
op_star
id|cp
)paren
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
OL
id|base
)paren
(brace
id|result
op_assign
id|result
op_star
id|base
op_plus
id|value
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
(paren
r_char
op_star
)paren
id|cp
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* we use this so that we can do without the ctype library */
DECL|macro|is_digit
mdefine_line|#define is_digit(c)&t;((c) &gt;= &squot;0&squot; &amp;&amp; (c) &lt;= &squot;9&squot;)
DECL|function|skip_atoi
r_static
r_int
id|skip_atoi
c_func
(paren
r_const
r_char
op_star
op_star
id|s
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|is_digit
c_func
(paren
op_star
op_star
id|s
)paren
)paren
id|i
op_assign
id|i
op_star
l_int|10
op_plus
op_star
(paren
(paren
op_star
id|s
)paren
op_increment
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|ZEROPAD
mdefine_line|#define ZEROPAD&t;1&t;&t;/* pad with zero */
DECL|macro|SIGN
mdefine_line|#define SIGN&t;2&t;&t;/* unsigned/signed long */
DECL|macro|PLUS
mdefine_line|#define PLUS&t;4&t;&t;/* show plus */
DECL|macro|SPACE
mdefine_line|#define SPACE&t;8&t;&t;/* space if plus */
DECL|macro|LEFT
mdefine_line|#define LEFT&t;16&t;&t;/* left justified */
DECL|macro|SPECIAL
mdefine_line|#define SPECIAL&t;32&t;&t;/* 0x */
DECL|macro|LARGE
mdefine_line|#define LARGE&t;64&t;&t;/* use &squot;ABCDEF&squot; instead of &squot;abcdef&squot; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;int __res; &bslash;&n;__res = ((unsigned long) n) % (unsigned) base; &bslash;&n;n = ((unsigned long) n) / (unsigned) base; &bslash;&n;__res; })
DECL|function|number
r_static
r_char
op_star
id|number
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|num
comma
r_int
id|base
comma
r_int
id|size
comma
r_int
id|precision
comma
r_int
id|type
)paren
(brace
r_char
id|c
comma
id|sign
comma
id|tmp
(braket
l_int|66
)braket
suffix:semicolon
r_const
r_char
op_star
id|digits
op_assign
l_string|&quot;0123456789abcdefghijklmnopqrstuvwxyz&quot;
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LARGE
)paren
id|digits
op_assign
l_string|&quot;0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LEFT
)paren
id|type
op_and_assign
op_complement
id|ZEROPAD
suffix:semicolon
r_if
c_cond
(paren
id|base
template_param
l_int|36
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
(paren
id|type
op_amp
id|ZEROPAD
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot; &squot;
suffix:semicolon
id|sign
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SIGN
)paren
(brace
r_if
c_cond
(paren
id|num
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|num
op_assign
op_minus
id|num
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|PLUS
)paren
(brace
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|SPACE
)paren
(brace
id|sign
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
id|size
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
id|size
op_decrement
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_while
c_loop
(paren
id|num
op_ne
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|digits
(braket
id|do_div
c_func
(paren
id|num
comma
id|base
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|precision
)paren
id|precision
op_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|precision
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
(paren
id|ZEROPAD
op_plus
id|LEFT
)paren
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sign
)paren
op_star
id|str
op_increment
op_assign
id|sign
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_star
id|str
op_increment
op_assign
id|digits
(braket
l_int|33
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|c
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|precision
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|tmp
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
DECL|function|vsprintf
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
r_int
id|i
comma
id|base
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_const
r_char
op_star
id|s
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags to number() */
r_int
id|field_width
suffix:semicolon
multiline_comment|/* width of output field */
r_int
id|precision
suffix:semicolon
multiline_comment|/* min. # of digits for integers; max&n;&t;&t;&t;&t;   number of chars for from string */
r_int
id|qualifier
suffix:semicolon
multiline_comment|/* &squot;h&squot;, &squot;l&squot;, or &squot;L&squot; for integer fields */
r_for
c_loop
(paren
id|str
op_assign
id|buf
suffix:semicolon
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
)paren
(brace
op_star
id|str
op_increment
op_assign
op_star
id|fmt
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* process flags */
id|flags
op_assign
l_int|0
suffix:semicolon
id|repeat
suffix:colon
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* this also skips first &squot;%&squot; */
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;-&squot;
suffix:colon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|flags
op_or_assign
id|PLUS
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
id|flags
op_or_assign
id|SPACE
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;#&squot;
suffix:colon
id|flags
op_or_assign
id|SPECIAL
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;0&squot;
suffix:colon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* get field width */
id|field_width
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|is_digit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|field_width
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|field_width
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field_width
OL
l_int|0
)paren
(brace
id|field_width
op_assign
op_minus
id|field_width
suffix:semicolon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
)brace
)brace
multiline_comment|/* get the precision */
id|precision
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
r_if
c_cond
(paren
id|is_digit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|precision
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|precision
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|precision
OL
l_int|0
)paren
id|precision
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* get the conversion qualifier */
id|qualifier
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;h&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;L&squot;
)paren
(brace
id|qualifier
op_assign
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
suffix:semicolon
)brace
multiline_comment|/* default base */
id|base
op_assign
l_int|10
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_star
id|str
op_increment
op_assign
(paren
r_int
r_char
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|s
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
id|s
op_assign
l_string|&quot;&lt;NULL&gt;&quot;
suffix:semicolon
id|len
op_assign
id|strnlen
c_func
(paren
id|s
comma
id|precision
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
op_star
id|str
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
r_if
c_cond
(paren
id|field_width
op_eq
op_minus
l_int|1
)paren
(brace
id|field_width
op_assign
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
)brace
id|str
op_assign
id|number
c_func
(paren
id|str
comma
(paren
r_int
r_int
)paren
id|va_arg
c_func
(paren
id|args
comma
r_void
op_star
)paren
comma
l_int|16
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
multiline_comment|/* integer number formats - set up the flags and &quot;break&quot; */
r_case
l_char|&squot;o&squot;
suffix:colon
id|base
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
id|flags
op_or_assign
id|LARGE
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
id|base
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;i&squot;
suffix:colon
id|flags
op_or_assign
id|SIGN
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
)paren
op_star
id|str
op_increment
op_assign
op_star
id|fmt
suffix:semicolon
r_else
op_decrement
id|fmt
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;h&squot;
)paren
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_else
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_else
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
id|str
op_assign
id|number
c_func
(paren
id|str
comma
id|num
comma
id|base
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
)brace
op_star
id|str
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|sprintf
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof