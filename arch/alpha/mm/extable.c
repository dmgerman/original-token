multiline_comment|/*&n; * linux/arch/alpha/mm/extable.c&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_const
r_struct
id|exception_table_entry
id|__start___ex_table
(braket
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|exception_table_entry
id|__stop___ex_table
(braket
)braket
suffix:semicolon
r_static
r_inline
r_int
DECL|function|search_one_table
id|search_one_table
c_func
(paren
r_const
r_struct
id|exception_table_entry
op_star
id|first
comma
r_const
r_struct
id|exception_table_entry
op_star
id|last
comma
r_int
r_int
id|value
)paren
(brace
r_while
c_loop
(paren
id|first
op_le
id|last
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|mid
suffix:semicolon
r_int
id|diff
suffix:semicolon
id|mid
op_assign
(paren
id|last
op_minus
id|first
)paren
op_div
l_int|2
op_plus
id|first
suffix:semicolon
id|diff
op_assign
id|mid-&gt;insn
op_minus
id|value
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
r_return
id|mid-&gt;fixup.unit
suffix:semicolon
r_else
r_if
c_cond
(paren
id|diff
OL
l_int|0
)paren
id|first
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
r_else
id|last
op_assign
id|mid
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|search_exception_table
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|reladdr
suffix:semicolon
multiline_comment|/* Search the kernel&squot;s table first.  */
(brace
r_register
r_int
r_int
id|gp
id|__asm__
c_func
(paren
l_string|&quot;$29&quot;
)paren
suffix:semicolon
id|reladdr
op_assign
id|addr
op_minus
id|gp
suffix:semicolon
)brace
id|ret
op_assign
id|search_one_table
c_func
(paren
id|__start___ex_table
comma
id|__stop___ex_table
op_minus
l_int|1
comma
id|reladdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* FIXME -- search the module&squot;s tables here */
r_return
l_int|0
suffix:semicolon
)brace
eof