multiline_comment|/*&n; *&t;Generate devlist.h from the PCI ID file.&n; *&n; *&t;(c) 1999 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
r_static
r_void
DECL|function|pq
id|pq
c_func
(paren
r_char
op_star
id|c
)paren
(brace
r_while
c_loop
(paren
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
op_star
id|c
op_eq
l_char|&squot;&quot;&squot;
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;&bslash;&bslash;&quot;&quot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
op_star
id|c
)paren
suffix:semicolon
id|c
op_increment
suffix:semicolon
)brace
)brace
r_int
DECL|function|main
id|main
c_func
(paren
r_void
)paren
(brace
r_char
id|line
(braket
l_int|1024
)braket
comma
op_star
id|c
comma
id|vend
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|vendors
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
op_minus
l_int|1
comma
id|stdin
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|c
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
)paren
op_star
id|c
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
(braket
l_int|0
)braket
op_logical_or
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|vend
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;t&squot;
)paren
(brace
r_if
c_cond
(paren
id|vend
(braket
l_int|0
)braket
op_logical_and
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|5
op_logical_and
id|line
(braket
l_int|5
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|c
op_assign
id|line
op_plus
l_int|5
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_eq
l_char|&squot; &squot;
)paren
op_star
id|c
op_increment
op_assign
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;tDEVICE(%s,%s,&bslash;&quot;&quot;
comma
id|vend
comma
id|line
op_plus
l_int|1
)paren
suffix:semicolon
id|pq
c_func
(paren
id|c
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;&quot;)&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|line
)paren
OG
l_int|4
op_logical_and
id|line
(braket
l_int|4
)braket
op_eq
l_char|&squot; &squot;
)paren
(brace
id|c
op_assign
id|line
op_plus
l_int|4
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
op_eq
l_char|&squot; &squot;
)paren
op_star
id|c
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vendors
)paren
id|puts
c_func
(paren
l_string|&quot;ENDVENDOR()&bslash;n&quot;
)paren
suffix:semicolon
id|vendors
op_increment
suffix:semicolon
id|strcpy
c_func
(paren
id|vend
comma
id|line
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;VENDOR(%s,&bslash;&quot;&quot;
comma
id|vend
)paren
suffix:semicolon
id|pq
c_func
(paren
id|c
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;&quot;)&quot;
)paren
suffix:semicolon
)brace
)brace
id|puts
c_func
(paren
l_string|&quot;ENDVENDOR()&bslash;n&bslash;&n;&bslash;n&bslash;&n;#undef VENDOR&bslash;n&bslash;&n;#undef DEVICE&bslash;n&bslash;&n;#undef ENDVENDOR&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
