multiline_comment|/*&n; *  linux/abi/emulate.c&n; *&n; *  Copyright (C) 1993  Linus Torvalds&n; */
multiline_comment|/*&n; * Emulate.c contains the entry point for the &squot;lcall 7,xxx&squot; handler.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/segment.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|function|iABI_emulate
id|asmlinkage
r_void
id|iABI_emulate
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lcall 7,xxx: eax = %08x&bslash;n&quot;
comma
id|regs-&gt;eax
)paren
suffix:semicolon
)brace
eof
