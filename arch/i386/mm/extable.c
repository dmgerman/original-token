multiline_comment|/*&n; * linux/arch/i386/mm/extable.c&n; */
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
r_inline
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
multiline_comment|/* Some versions of the linker are buggy and do not align the&n;&t;   __start pointer along with the section, thus we may be low.  */
r_if
c_cond
(paren
(paren
r_int
)paren
id|first
op_amp
l_int|3
)paren
(paren
r_int
)paren
id|first
op_assign
(paren
(paren
r_int
)paren
id|first
op_or
l_int|3
)paren
op_plus
l_int|1
suffix:semicolon
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
id|mid-&gt;fixup
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
r_int
id|ret
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
r_struct
id|module
op_star
id|mp
suffix:semicolon
macro_line|#endif
multiline_comment|/* Search the kernel&squot;s table first.  */
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
macro_line|#ifdef CONFIG_MODULES
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
id|mp-&gt;exceptinfo.start
op_ne
l_int|NULL
)paren
(brace
id|ret
op_assign
id|search_one_table
c_func
(paren
id|mp-&gt;exceptinfo.start
comma
id|mp-&gt;exceptinfo.stop
op_minus
l_int|1
comma
id|addr
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
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof