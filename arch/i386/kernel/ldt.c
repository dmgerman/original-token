multiline_comment|/*&n; * linux/kernel/ldt.c&n; *&n; * Copyright (C) 1992 Krishna Balasubramanian and Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
DECL|function|read_ldt
r_static
r_int
id|read_ldt
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_int
id|error
suffix:semicolon
r_void
op_star
id|address
op_assign
id|current-&gt;ldt
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|size
op_assign
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
(brace
id|address
op_assign
op_amp
id|default_ldt
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|default_ldt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OG
id|bytecount
)paren
id|size
op_assign
id|bytecount
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|ptr
comma
id|address
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|write_ldt
r_static
r_int
id|write_ldt
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_struct
id|modify_ldt_ldt_s
id|ldt_info
suffix:semicolon
r_int
r_int
op_star
id|lp
suffix:semicolon
r_int
r_int
id|base
comma
id|limit
suffix:semicolon
r_int
id|error
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|bytecount
op_ne
r_sizeof
(paren
id|ldt_info
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|ptr
comma
r_sizeof
(paren
id|ldt_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|ldt_info
comma
id|ptr
comma
r_sizeof
(paren
id|ldt_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.contents
op_eq
l_int|3
op_logical_or
id|ldt_info.entry_number
op_ge
id|LDT_ENTRIES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|limit
op_assign
id|ldt_info.limit
suffix:semicolon
id|base
op_assign
id|ldt_info.base_addr
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.limit_in_pages
)paren
id|limit
op_mul_assign
id|PAGE_SIZE
suffix:semicolon
id|limit
op_add_assign
id|base
suffix:semicolon
r_if
c_cond
(paren
id|limit
OL
id|base
op_logical_or
id|limit
op_ge
l_int|0xC0000000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;ldt
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_eq
id|current
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ldt
op_assign
(paren
r_struct
id|desc_struct
op_star
)paren
id|vmalloc
c_func
(paren
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|current-&gt;ldt
comma
l_int|0
comma
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|set_ldt_desc
c_func
(paren
id|gdt
op_plus
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
id|FIRST_LDT_ENTRY
comma
id|current-&gt;ldt
comma
id|LDT_ENTRIES
)paren
suffix:semicolon
id|load_ldt
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
id|lp
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|current-&gt;ldt
(braket
id|ldt_info.entry_number
)braket
suffix:semicolon
multiline_comment|/* Allow LDTs to be cleared by the user. */
r_if
c_cond
(paren
id|ldt_info.base_addr
op_eq
l_int|0
op_logical_and
id|ldt_info.limit
op_eq
l_int|0
)paren
(brace
op_star
id|lp
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|lp
op_plus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|lp
op_assign
(paren
(paren
id|ldt_info.base_addr
op_amp
l_int|0x0000ffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ldt_info.limit
op_amp
l_int|0x0ffff
)paren
suffix:semicolon
op_star
(paren
id|lp
op_plus
l_int|1
)paren
op_assign
(paren
id|ldt_info.base_addr
op_amp
l_int|0xff000000
)paren
op_or
(paren
(paren
id|ldt_info.base_addr
op_amp
l_int|0x00ff0000
)paren
op_rshift
l_int|16
)paren
op_or
(paren
id|ldt_info.limit
op_amp
l_int|0xf0000
)paren
op_or
(paren
id|ldt_info.contents
op_lshift
l_int|10
)paren
op_or
(paren
(paren
id|ldt_info.read_exec_only
op_xor
l_int|1
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|ldt_info.seg_32bit
op_lshift
l_int|22
)paren
op_or
(paren
id|ldt_info.limit_in_pages
op_lshift
l_int|23
)paren
op_or
(paren
(paren
id|ldt_info.seg_not_present
op_xor
l_int|1
)paren
op_lshift
l_int|15
)paren
op_or
l_int|0x7000
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_modify_ldt
id|asmlinkage
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_if
c_cond
(paren
id|func
op_eq
l_int|0
)paren
r_return
id|read_ldt
c_func
(paren
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|func
op_eq
l_int|1
)paren
r_return
id|write_ldt
c_func
(paren
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof