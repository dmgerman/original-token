multiline_comment|/*&n; *&t;arch/alpha/lib/srm_puts.c&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/console.h&gt;
r_void
DECL|function|srm_puts
id|srm_puts
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* Expand &bslash;n to &bslash;r&bslash;n as we go.  */
r_while
c_loop
(paren
op_star
id|str
)paren
(brace
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|e
op_assign
id|str
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|srm_dispatch
c_func
(paren
id|CCB_PUTS
comma
l_int|0
comma
l_string|&quot;&bslash;r&quot;
comma
l_int|1
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
op_increment
id|e
suffix:semicolon
)brace
id|e
op_assign
id|strchr
c_func
(paren
id|e
comma
l_char|&squot;&bslash;n&squot;
)paren
ques
c_cond
suffix:colon
id|strchr
c_func
(paren
id|e
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|len
op_assign
id|e
op_minus
id|str
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|written
op_assign
id|srm_dispatch
c_func
(paren
id|CCB_PUTS
comma
l_int|0
comma
id|str
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
OL
l_int|0
)paren
r_return
suffix:semicolon
id|len
op_sub_assign
id|written
op_amp
l_int|0xffffffff
suffix:semicolon
id|str
op_add_assign
id|written
op_amp
l_int|0xffffffff
suffix:semicolon
)brace
)brace
)brace
eof