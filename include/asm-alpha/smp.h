macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#ifdef __SMP__
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
DECL|struct|cpuinfo_alpha
r_struct
id|cpuinfo_alpha
(brace
DECL|member|loops_per_sec
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|member|last_asn
r_int
r_int
id|last_asn
suffix:semicolon
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
DECL|member|ipi_count
r_int
r_int
id|ipi_count
suffix:semicolon
DECL|member|prof_multiplier
r_int
r_int
id|prof_multiplier
suffix:semicolon
DECL|member|prof_counter
r_int
r_int
id|prof_counter
suffix:semicolon
DECL|member|irq_count
DECL|member|bh_count
r_int
id|irq_count
comma
id|bh_count
suffix:semicolon
DECL|member|mcheck_expected
r_int
r_char
id|mcheck_expected
suffix:semicolon
DECL|member|mcheck_taken
r_int
r_char
id|mcheck_taken
suffix:semicolon
DECL|member|mcheck_hose
r_int
r_char
id|mcheck_hose
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|cpuinfo_alpha
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY     20
multiline_comment|/* Map from cpu id to sequential logical cpu number.  This will only&n;   not be idempotent when cpus failed to come on-line.  */
r_extern
r_int
id|cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* The reverse map from sequential logical cpu number to cpu id.  */
r_extern
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)  __cpu_logical_map[cpu]
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id()&t;__hard_smp_processor_id()
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current-&gt;processor)
macro_line|#endif /* __SMP__ */
multiline_comment|/* HACK: Cabrio WHAMI return value is bogus if more than 8 bits used.. :-( */
r_static
id|__inline__
r_int
r_char
DECL|function|__hard_smp_processor_id
id|__hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_char
id|__r0
id|__asm__
c_func
(paren
l_string|&quot;$0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call_pal %1 #whami&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__r0
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|PAL_whami
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
r_return
id|__r0
suffix:semicolon
)brace
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
macro_line|#endif
eof
