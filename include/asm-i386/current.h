macro_line|#ifndef _I386_CURRENT_H
DECL|macro|_I386_CURRENT_H
mdefine_line|#define _I386_CURRENT_H
multiline_comment|/* Some architectures may want to do something &quot;clever&quot; here since&n; * this is the most frequently accessed piece of data in the entire&n; * kernel.  For an example, see the Sparc implementation where an&n; * entire register is hard locked to contain the value of current.&n; */
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|get_esp
r_static
r_inline
r_int
r_int
id|get_esp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|esp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%esp,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|esp
)paren
)paren
suffix:semicolon
r_return
id|esp
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current ((struct task_struct *)(get_esp() &amp; ~8191UL))
macro_line|#endif /* !(_I386_CURRENT_H) */
eof
