macro_line|#ifndef _SPARC_CURRENT_H
DECL|macro|_SPARC_CURRENT_H
mdefine_line|#define _SPARC_CURRENT_H
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
multiline_comment|/* Sparc rules... */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
c_func
(paren
l_string|&quot;g6&quot;
)paren
suffix:semicolon
macro_line|#endif /* !(_SPARC_CURRENT_H) */
eof
