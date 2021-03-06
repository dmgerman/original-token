multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start_idle
suffix:semicolon
id|start_idle
op_assign
id|jiffies
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|current-&gt;need_resched
op_logical_or
id|hlt_counter
)paren
r_goto
id|slow_out
suffix:semicolon
id|cpu_do_idle
c_func
(paren
id|IDLE_WAIT_FAST
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|start_idle
op_plus
id|HZ
op_div
l_int|50
)paren
)paren
suffix:semicolon
id|cpu_do_idle
c_func
(paren
id|IDLE_CLOCK_SLOW
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
op_logical_and
op_logical_neg
id|hlt_counter
)paren
(brace
id|cpu_do_idle
c_func
(paren
id|IDLE_WAIT_SLOW
)paren
suffix:semicolon
)brace
id|cpu_do_idle
c_func
(paren
id|IDLE_CLOCK_FAST
)paren
suffix:semicolon
id|slow_out
suffix:colon
)brace
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;do { } while (0)
macro_line|#endif
eof
