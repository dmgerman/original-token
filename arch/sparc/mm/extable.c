multiline_comment|/*&n; * linux/arch/sparc/mm/extable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
r_int
r_int
DECL|function|search_one_table
id|search_one_table
c_func
(paren
r_const
r_struct
id|exception_table_entry
op_star
id|start
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
comma
r_int
r_int
op_star
id|g2
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|first
op_assign
id|start
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|mid
suffix:semicolon
r_int
id|diff
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|first
op_le
id|last
)paren
(brace
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|mid-&gt;fixup
)paren
(brace
op_star
id|g2
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|mid
op_plus
l_int|1
)paren
op_member_access_from_pointer
id|fixup
suffix:semicolon
)brace
r_else
r_return
id|mid-&gt;fixup
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|last-&gt;insn
template_param
id|value
)paren
(brace
op_star
id|g2
op_assign
(paren
id|value
op_minus
id|last-&gt;insn
)paren
op_div
l_int|4
suffix:semicolon
r_return
id|last
(braket
l_int|1
)braket
dot
id|fixup
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first
OG
id|start
op_logical_and
id|first
(braket
op_minus
l_int|1
)braket
dot
id|insn
OL
id|value
op_logical_and
op_logical_neg
id|first
(braket
op_minus
l_int|1
)braket
dot
id|fixup
op_logical_and
id|first-&gt;insn
OL
id|value
)paren
(brace
op_star
id|g2
op_assign
(paren
id|value
op_minus
id|first
(braket
op_minus
l_int|1
)braket
dot
id|insn
)paren
op_div
l_int|4
suffix:semicolon
r_return
id|first-&gt;fixup
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
DECL|function|search_exception_table
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|g2
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
macro_line|#ifndef CONFIG_MODULES
multiline_comment|/* There is only the kernel to search.  */
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
id|addr
comma
id|g2
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
macro_line|#else
multiline_comment|/* The kernel is the last &quot;module&quot; -- no need to treat it special.  */
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_for
c_loop
(paren
id|mp
op_assign
id|module_list
suffix:semicolon
id|mp
op_ne
l_int|NULL
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;ex_table_start
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|search_one_table
c_func
(paren
id|mp-&gt;ex_table_start
comma
id|mp-&gt;ex_table_end
op_minus
l_int|1
comma
id|addr
comma
id|g2
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
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
