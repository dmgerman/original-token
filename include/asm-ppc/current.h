macro_line|#ifndef _PPC_CURRENT_H
DECL|macro|_PPC_CURRENT_H
mdefine_line|#define _PPC_CURRENT_H
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
DECL|macro|current
mdefine_line|#define current (current_set[smp_processor_id()])&t;/* Current on this processor */
macro_line|#endif /* !(_PPC_CURRENT_H) */
eof
