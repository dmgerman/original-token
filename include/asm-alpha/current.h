macro_line|#ifndef _ALPHA_CURRENT_H
DECL|macro|_ALPHA_CURRENT_H
mdefine_line|#define _ALPHA_CURRENT_H
multiline_comment|/* Some architectures may want to do something &quot;clever&quot; here since&n; * this is the most frequently accessed piece of data in the entire&n; * kernel.&n; */
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_register
r_struct
id|task_struct
op_star
id|current
id|__asm__
c_func
(paren
l_string|&quot;$8&quot;
)paren
suffix:semicolon
macro_line|#endif /* !(_ALPHA_CURRENT_H) */
eof
