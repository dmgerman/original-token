macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)&t;(cpu)
macro_line|#ifdef __SMP__
macro_line|#include &lt;linux/tasks.h&gt;
DECL|struct|cpuinfo_alpha
r_struct
id|cpuinfo_alpha
(brace
DECL|member|loops_per_sec
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_alpha
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_typedef
r_volatile
r_struct
(brace
DECL|member|kernel_flag
r_int
r_int
id|kernel_flag
suffix:semicolon
multiline_comment|/* 4 bytes, please */
DECL|member|akp
r_int
r_int
id|akp
suffix:semicolon
multiline_comment|/* 4 bytes, please */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
DECL|typedef|klock_info_t
)brace
id|klock_info_t
suffix:semicolon
r_extern
id|klock_info_t
id|klock_info
suffix:semicolon
DECL|macro|KLOCK_HELD
mdefine_line|#define KLOCK_HELD&t;0xff
DECL|macro|KLOCK_CLEAR
mdefine_line|#define KLOCK_CLEAR&t;0x00
r_extern
r_int
id|task_lock_depth
suffix:semicolon
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
multiline_comment|/* HACK: Cabrio WHAMI return value is bogus if more than 8 bits used.. :-( */
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id() &bslash;&n;({ &bslash;&n;&t;register unsigned char __r0 __asm__(&quot;$0&quot;); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %0&quot; &bslash;&n;&t;&t;: /* no output (bound to the template) */ &bslash;&n;&t;&t;:&quot;i&quot; (PAL_whami) &bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;&t;__r0; &bslash;&n;})
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() hard_smp_processor_id()
macro_line|#endif /* __SMP__ */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
macro_line|#endif
eof
