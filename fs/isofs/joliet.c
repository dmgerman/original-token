multiline_comment|/*&n; *  linux/fs/isofs/joliet.c&n; *&n; *  (C) 1996 Gordon Chaffee&n; *&n; *  Joliet: Microsoft&squot;s Unicode extensions to iso9660&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
multiline_comment|/*&n; * Convert Unicode 16 to UTF8 or ASCII.&n; */
r_static
r_int
DECL|function|uni16_to_x8
id|uni16_to_x8
c_func
(paren
r_int
r_char
op_star
id|ascii
comma
r_int
r_char
op_star
id|uni
comma
r_int
id|len
comma
r_struct
id|nls_table
op_star
id|nls
)paren
(brace
r_int
r_char
op_star
id|ip
comma
op_star
id|op
suffix:semicolon
r_int
r_char
id|ch
comma
id|cl
suffix:semicolon
r_int
r_char
op_star
id|uni_page
suffix:semicolon
id|ip
op_assign
id|uni
suffix:semicolon
id|op
op_assign
id|ascii
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|ip
op_logical_or
id|ip
(braket
l_int|1
)braket
)paren
op_logical_and
id|len
)paren
(brace
id|ch
op_assign
op_star
id|ip
op_increment
suffix:semicolon
id|cl
op_assign
op_star
id|ip
op_increment
suffix:semicolon
id|uni_page
op_assign
id|nls-&gt;page_uni2charset
(braket
id|ch
)braket
suffix:semicolon
r_if
c_cond
(paren
id|uni_page
op_logical_and
id|uni_page
(braket
id|cl
)braket
)paren
(brace
op_star
id|op
op_increment
op_assign
id|uni_page
(braket
id|cl
)braket
suffix:semicolon
)brace
r_else
(brace
op_star
id|op
op_increment
op_assign
l_char|&squot;?&squot;
suffix:semicolon
)brace
id|len
op_decrement
suffix:semicolon
)brace
op_star
id|op
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|op
op_minus
id|ascii
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert big endian wide character string to utf8 */
r_static
r_int
DECL|function|wcsntombs_be
id|wcsntombs_be
c_func
(paren
id|__u8
op_star
id|s
comma
r_const
id|__u8
op_star
id|pwcs
comma
r_int
id|inlen
comma
r_int
id|maxlen
)paren
(brace
r_const
id|__u8
op_star
id|ip
suffix:semicolon
id|__u8
op_star
id|op
suffix:semicolon
r_int
id|size
suffix:semicolon
id|__u16
id|c
suffix:semicolon
id|op
op_assign
id|s
suffix:semicolon
id|ip
op_assign
id|pwcs
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|ip
op_logical_or
id|ip
(braket
l_int|1
)braket
)paren
op_logical_and
(paren
id|maxlen
OG
l_int|0
)paren
op_logical_and
(paren
id|inlen
OG
l_int|0
)paren
)paren
(brace
id|c
op_assign
(paren
op_star
id|ip
op_lshift
l_int|8
)paren
op_or
id|ip
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
l_int|0x7f
)paren
(brace
id|size
op_assign
id|utf8_wctomb
c_func
(paren
id|op
comma
id|c
comma
id|maxlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Ignore character and move on */
id|maxlen
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|op
op_add_assign
id|size
suffix:semicolon
id|maxlen
op_sub_assign
id|size
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|op
op_increment
op_assign
(paren
id|__u8
)paren
id|c
suffix:semicolon
)brace
id|ip
op_add_assign
l_int|2
suffix:semicolon
id|inlen
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|op
op_minus
id|s
)paren
suffix:semicolon
)brace
r_int
DECL|function|get_joliet_filename
id|get_joliet_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
r_char
op_star
id|outname
)paren
(brace
r_int
r_char
id|utf8
suffix:semicolon
r_struct
id|nls_table
op_star
id|nls
suffix:semicolon
r_int
r_char
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
id|utf8
op_assign
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_utf8
suffix:semicolon
id|nls
op_assign
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_nls_iocharset
suffix:semicolon
r_if
c_cond
(paren
id|utf8
)paren
(brace
id|len
op_assign
id|wcsntombs_be
c_func
(paren
id|outname
comma
id|de-&gt;name
comma
id|de-&gt;name_len
(braket
l_int|0
)braket
op_rshift
l_int|1
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|uni16_to_x8
c_func
(paren
id|outname
comma
id|de-&gt;name
comma
id|de-&gt;name_len
(braket
l_int|0
)braket
op_rshift
l_int|1
comma
id|nls
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|len
OG
l_int|2
)paren
op_logical_and
(paren
id|outname
(braket
id|len
op_minus
l_int|2
)braket
op_eq
l_char|&squot;;&squot;
)paren
op_logical_and
(paren
id|outname
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;1&squot;
)paren
)paren
(brace
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_name_check
op_eq
l_char|&squot;r&squot;
)paren
(brace
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
id|i
op_increment
)paren
(brace
id|c
op_assign
id|outname
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* lower case */
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_or_assign
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
)paren
id|c
op_assign
l_char|&squot;.&squot;
suffix:semicolon
id|outname
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
eof
