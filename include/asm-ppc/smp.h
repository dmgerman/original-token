multiline_comment|/* smp.h: PPC specific SMP stuff.&n; *&n; * Taken from asm-sparc/smp.h&n; */
macro_line|#ifndef _PPC_SMP_H
DECL|macro|_PPC_SMP_H
mdefine_line|#define _PPC_SMP_H
macro_line|#include &lt;linux/kernel.h&gt; /* for panic */
macro_line|#include &lt;linux/tasks.h&gt; /* for NR_CPUS */
macro_line|#ifdef __SMP__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|cpu_present_map
suffix:semicolon
multiline_comment|/* per processor PPC parameters we need. */
DECL|struct|cpuinfo_PPC
r_struct
id|cpuinfo_PPC
(brace
DECL|member|loops_per_sec
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|member|pvr
r_int
r_int
id|pvr
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_PPC
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|struct|klock_info_struct
r_struct
id|klock_info_struct
(brace
DECL|member|kernel_flag
r_int
r_int
id|kernel_flag
suffix:semicolon
DECL|member|akp
r_int
r_char
id|akp
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|klock_info_struct
id|klock_info
suffix:semicolon
DECL|macro|KLOCK_HELD
mdefine_line|#define KLOCK_HELD       0xffffffff
DECL|macro|KLOCK_CLEAR
mdefine_line|#define KLOCK_CLEAR      0x0
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY     20
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
r_extern
r_int
r_int
id|smp_proc_in_lock
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
id|cpuid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* assume cpu # 0 for now */
r_return
id|cpuid
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
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#else /* !(__SMP__) */
macro_line|#ifndef __ASSEMBLY__
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
id|cpu
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* !(__SMP__) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID               0xFF            /* No processor magic marker */
r_extern
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
macro_line|#endif /* !(_PPC_SMP_H) */
eof
