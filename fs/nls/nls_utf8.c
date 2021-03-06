multiline_comment|/*&n; * Module for handling utf8 just like any other charset.&n; * By Urban Widmark 2000&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|variable|identity
r_static
r_int
r_char
id|identity
(braket
l_int|256
)braket
suffix:semicolon
DECL|function|uni2char
r_static
r_int
id|uni2char
c_func
(paren
m_wchar_t
id|uni
comma
r_int
r_char
op_star
id|out
comma
r_int
id|boundlen
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|utf8_wctomb
c_func
(paren
id|out
comma
id|uni
comma
id|boundlen
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
op_star
id|out
op_assign
l_char|&squot;?&squot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|char2uni
r_static
r_int
id|char2uni
c_func
(paren
r_const
r_int
r_char
op_star
id|rawstring
comma
r_int
id|boundlen
comma
m_wchar_t
op_star
id|uni
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|utf8_mbtowc
c_func
(paren
id|uni
comma
id|rawstring
comma
id|boundlen
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
op_star
id|uni
op_assign
l_int|0x003f
suffix:semicolon
multiline_comment|/* ? */
id|n
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|variable|table
r_static
r_struct
id|nls_table
id|table
op_assign
(brace
l_string|&quot;utf8&quot;
comma
id|uni2char
comma
id|char2uni
comma
id|identity
comma
multiline_comment|/* no conversion */
id|identity
comma
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_nls_utf8
r_static
r_int
id|__init
id|init_nls_utf8
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|identity
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
r_return
id|register_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
)brace
DECL|function|exit_nls_utf8
r_static
r_void
id|__exit
id|exit_nls_utf8
c_func
(paren
r_void
)paren
(brace
id|unregister_nls
c_func
(paren
op_amp
id|table
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_nls_utf8
)paren
id|module_exit
c_func
(paren
id|exit_nls_utf8
)paren
eof
