multiline_comment|/*&n; * SMP Support&n; *&n; * Copyright (C) 1999 VA Linux Systems &n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_SMP_H
DECL|macro|_ASM_IA64_SMP_H
mdefine_line|#define _ASM_IA64_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|IPI_DEFAULT_BASE_ADDR
mdefine_line|#define IPI_DEFAULT_BASE_ADDR&t;0xfee00000
DECL|macro|XTP_OFFSET
mdefine_line|#define XTP_OFFSET&t;&t;0x1e0008
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current-&gt;processor)
r_extern
r_int
r_int
id|cpu_present_map
suffix:semicolon
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
r_extern
r_int
r_int
id|ipi_base_addr
suffix:semicolon
r_extern
r_int
id|bootstrap_processor
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(i)&t;__cpu_logical_map[i]
macro_line|#if defined(CONFIG_KDB)
r_extern
r_volatile
r_int
r_int
id|smp_kdb_wait
suffix:semicolon
macro_line|#endif  /* CONFIG_KDB */
r_extern
r_int
r_int
id|ap_wakeup_vector
suffix:semicolon
multiline_comment|/*&n; * XTP control functions:&n; *    min_xtp   :  route all interrupts to this CPU&n; *    normal_xtp:  nominal XTP value&n; *    raise_xtp :  Route all interrupts away from this CPU&n; *    max_xtp   :  never deliver interrupts to this CPU.&n; */
multiline_comment|/* &n; * This turns off XTP based interrupt routing.  There is a bug in the handling of &n; * IRQ_INPROGRESS when the same vector appears on more than one CPU. &n; */
r_extern
r_int
id|use_xtp
suffix:semicolon
r_extern
id|__inline
r_void
DECL|function|min_xtp
id|min_xtp
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|use_xtp
)paren
id|writeb
c_func
(paren
l_int|0x80
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* XTP to min */
)brace
r_extern
id|__inline
r_void
DECL|function|normal_xtp
id|normal_xtp
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|use_xtp
)paren
id|writeb
c_func
(paren
l_int|0x8e
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* XTP normal */
)brace
r_extern
id|__inline
r_void
DECL|function|max_xtp
id|max_xtp
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|use_xtp
)paren
id|writeb
c_func
(paren
l_int|0x8f
comma
id|ipi_base_addr
op_or
id|XTP_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Set XTP to max... */
)brace
r_extern
id|__inline
r_int
r_int
DECL|function|hard_smp_processor_id
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_struct
(brace
r_int
r_int
id|reserved
suffix:colon
l_int|16
suffix:semicolon
r_int
r_int
id|eid
suffix:colon
l_int|8
suffix:semicolon
r_int
r_int
id|id
suffix:colon
l_int|8
suffix:semicolon
r_int
r_int
id|ignored
suffix:colon
l_int|32
suffix:semicolon
)brace
id|lid
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov %0=cr.lid&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lid
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Damn.  IA64 CPU ID&squot;s are 16 bits long, Linux expect the hard id to be &n;&t; * in the range 0..31.  So, return the low-order bits of the bus-local ID &n;&t; * only and hope it&squot;s less than 32. This needs to be fixed...&n;&t; */
r_return
(paren
id|lid.id
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID 0xffffffff
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY 20
r_extern
r_void
id|__init
id|init_smp_config
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_do_timer
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SMP_H */
eof
