macro_line|#ifndef _PPC_CURRENT_H
DECL|macro|_PPC_CURRENT_H
mdefine_line|#define _PPC_CURRENT_H
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
l_int|1
)braket
suffix:semicolon
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
c_func
(paren
l_string|&quot;r2&quot;
)paren
suffix:semicolon
macro_line|#endif /* !(_PPC_CURRENT_H) */
eof
