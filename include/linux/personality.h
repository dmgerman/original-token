macro_line|#ifndef _PERSONALITY_H
DECL|macro|_PERSONALITY_H
mdefine_line|#define _PERSONALITY_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
multiline_comment|/* Flags for bug emulation. These occupy the top three bytes. */
DECL|macro|STICKY_TIMEOUTS
mdefine_line|#define STICKY_TIMEOUTS&t;&t;0x4000000
DECL|macro|WHOLE_SECONDS
mdefine_line|#define WHOLE_SECONDS&t;&t;0x2000000
DECL|macro|ADDR_LIMIT_32BIT
mdefine_line|#define ADDR_LIMIT_32BIT&t;0x0800000
multiline_comment|/* Personality types. These go in the low byte. Avoid using the top bit,&n; * it will conflict with error returns.&n; */
DECL|macro|PER_MASK
mdefine_line|#define PER_MASK&t;&t;(0x00ff)
DECL|macro|PER_LINUX
mdefine_line|#define PER_LINUX&t;&t;(0x0000)
DECL|macro|PER_LINUX_32BIT
mdefine_line|#define PER_LINUX_32BIT&t;&t;(0x0000 | ADDR_LIMIT_32BIT)
DECL|macro|PER_SVR4
mdefine_line|#define PER_SVR4&t;&t;(0x0001 | STICKY_TIMEOUTS)
DECL|macro|PER_SVR3
mdefine_line|#define PER_SVR3&t;&t;(0x0002 | STICKY_TIMEOUTS)
DECL|macro|PER_SCOSVR3
mdefine_line|#define PER_SCOSVR3&t;&t;(0x0003 | STICKY_TIMEOUTS | WHOLE_SECONDS)
DECL|macro|PER_WYSEV386
mdefine_line|#define PER_WYSEV386&t;&t;(0x0004 | STICKY_TIMEOUTS)
DECL|macro|PER_ISCR4
mdefine_line|#define PER_ISCR4&t;&t;(0x0005 | STICKY_TIMEOUTS)
DECL|macro|PER_BSD
mdefine_line|#define PER_BSD&t;&t;&t;(0x0006)
DECL|macro|PER_XENIX
mdefine_line|#define PER_XENIX&t;&t;(0x0007 | STICKY_TIMEOUTS)
multiline_comment|/* Prototype for an lcall7 syscall handler. */
DECL|typedef|lcall7_func
r_typedef
r_void
(paren
op_star
id|lcall7_func
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* Description of an execution domain - personality range supported,&n; * lcall7 syscall handler, start up / shut down functions etc.&n; * N.B. The name and lcall7 handler must be where they are since the&n; * offset of the handler is hard coded in kernel/sys_call.S.&n; */
DECL|struct|exec_domain
r_struct
id|exec_domain
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|handler
id|lcall7_func
id|handler
suffix:semicolon
DECL|member|pers_low
DECL|member|pers_high
r_int
r_char
id|pers_low
comma
id|pers_high
suffix:semicolon
DECL|member|signal_map
r_int
r_int
op_star
id|signal_map
suffix:semicolon
DECL|member|signal_invmap
r_int
r_int
op_star
id|signal_invmap
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|next
r_struct
id|exec_domain
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|exec_domain
id|default_exec_domain
suffix:semicolon
r_extern
r_struct
id|exec_domain
op_star
id|lookup_exec_domain
c_func
(paren
r_int
r_int
id|personality
)paren
suffix:semicolon
r_extern
r_int
id|register_exec_domain
c_func
(paren
r_struct
id|exec_domain
op_star
id|it
)paren
suffix:semicolon
r_extern
r_int
id|unregister_exec_domain
c_func
(paren
r_struct
id|exec_domain
op_star
id|it
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_personality
c_func
(paren
r_int
r_int
id|personality
)paren
suffix:semicolon
macro_line|#endif /* _PERSONALITY_H */
eof
