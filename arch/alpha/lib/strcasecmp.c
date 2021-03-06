multiline_comment|/*&n; *  linux/arch/alpha/lib/strcasecmp.c&n; */
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/* We handle nothing here except the C locale.  Since this is used in&n;   only one place, on strings known to contain only 7 bit ASCII, this&n;   is ok.  */
DECL|function|strcasecmp
r_int
id|strcasecmp
c_func
(paren
r_const
r_char
op_star
id|a
comma
r_const
r_char
op_star
id|b
)paren
(brace
r_int
id|ca
comma
id|cb
suffix:semicolon
r_do
(brace
id|ca
op_assign
op_star
id|a
op_increment
op_amp
l_int|0xff
suffix:semicolon
id|cb
op_assign
op_star
id|b
op_increment
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ca
op_ge
l_char|&squot;A&squot;
op_logical_and
id|ca
op_le
l_char|&squot;Z&squot;
)paren
id|ca
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|cb
op_ge
l_char|&squot;A&squot;
op_logical_and
id|cb
op_le
l_char|&squot;Z&squot;
)paren
id|cb
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ca
op_eq
id|cb
op_logical_and
id|ca
op_ne
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_return
id|ca
op_minus
id|cb
suffix:semicolon
)brace
eof
