multiline_comment|/* smp.h: Sparc64 specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_SMP_H
DECL|macro|_SPARC64_SMP_H
mdefine_line|#define _SPARC64_SMP_H
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* PROM provided per-processor information we need&n; * to start them all up.&n; */
DECL|struct|prom_cpuinfo
r_struct
id|prom_cpuinfo
(brace
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|mid
r_int
id|mid
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|linux_num_cpus
suffix:semicolon
multiline_comment|/* number of CPUs probed  */
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#ifdef __SMP__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Per processor Sparc parameters we need. */
multiline_comment|/* Keep this a multiple of 64-bytes for cache reasons. */
DECL|struct|cpuinfo_sparc
r_struct
id|cpuinfo_sparc
(brace
multiline_comment|/* Dcache line 1 */
DECL|member|irq_count
r_int
r_int
id|irq_count
suffix:semicolon
DECL|member|bh_count
r_int
r_int
id|bh_count
suffix:semicolon
DECL|member|multiplier
r_int
r_int
id|multiplier
suffix:semicolon
DECL|member|counter
r_int
r_int
id|counter
suffix:semicolon
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
multiline_comment|/* Dcache line 2 */
DECL|member|pgcache_size
r_int
r_int
id|pgcache_size
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgdcache_size
r_int
r_int
id|pgdcache_size
suffix:semicolon
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_sparc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Private routines/data&n; */
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
r_int
r_int
id|cpu_present_map
suffix:semicolon
multiline_comment|/*&n; *&t;General functions that each host system must provide.&n; */
r_extern
r_void
id|smp_callin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
r_extern
id|__volatile__
r_int
id|cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|__volatile__
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|cpu_logical_map
r_extern
id|__inline__
r_int
id|cpu_logical_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|__cpu_logical_map
(braket
id|cpu
)braket
suffix:semicolon
)brace
DECL|function|hard_smp_processor_id
r_extern
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|upaconfig
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&t;[%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|upaconfig
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_UPA_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|upaconfig
op_rshift
l_int|17
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
)brace
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current-&gt;processor)
r_extern
r_void
id|smp_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
suffix:semicolon
multiline_comment|/* As idle task checks need_resched in a tight loop, it is not necessary to&n;   wake it up. -jj */
DECL|macro|smp_send_reschedule
mdefine_line|#define smp_send_reschedule(cpu) do {} while (0)
macro_line|#endif /* !(__ASSEMBLY__) */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20
macro_line|#endif /* !(__SMP__) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF
macro_line|#endif /* !(_SPARC64_SMP_H) */
eof
