multiline_comment|/* $Id: ip27-klconfig.c,v 1.1 2000/01/17 23:32:47 ralf Exp $&n; *&n; * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/mm.h&gt;&t;&t;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
DECL|function|find_lboard
id|lboard_t
op_star
id|find_lboard
c_func
(paren
r_int
r_int
id|type
)paren
(brace
id|lboard_t
op_star
id|b
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
id|KL_CONFIG_INFO
c_func
(paren
id|get_nasid
c_func
(paren
)paren
)paren
suffix:semicolon
id|b
suffix:semicolon
id|b
op_assign
id|KLCF_NEXT
c_func
(paren
id|b
)paren
)paren
(brace
r_if
c_cond
(paren
id|KLCF_REMOTE
c_func
(paren
id|b
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Skip remote boards. */
r_if
c_cond
(paren
id|b-&gt;brd_type
op_eq
id|type
)paren
r_return
(paren
id|lboard_t
op_star
)paren
id|b
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
