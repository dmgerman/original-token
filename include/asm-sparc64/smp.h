multiline_comment|/* smp.h: Sparc64 specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_SMP_H
DECL|macro|_SPARC64_SMP_H
mdefine_line|#define _SPARC64_SMP_H
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
DECL|struct|cpuinfo_sparc
r_struct
id|cpuinfo_sparc
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
multiline_comment|/* that&squot;s it */
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
DECL|struct|klock_info
r_struct
id|klock_info
(brace
DECL|member|kernel_flag
r_int
r_char
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
id|klock_info
id|klock_info
suffix:semicolon
DECL|macro|KLOCK_HELD
mdefine_line|#define KLOCK_HELD       0xff
DECL|macro|KLOCK_CLEAR
mdefine_line|#define KLOCK_CLEAR      0x00
multiline_comment|/*&n; *&t;Private routines/data&n; */
r_extern
r_int
id|smp_found_cpus
suffix:semicolon
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
r_extern
id|__volatile__
r_int
r_int
id|smp_invalidate_needed
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|__volatile__
r_int
r_int
id|kernel_counter
suffix:semicolon
r_extern
id|__volatile__
r_int
r_char
id|active_kernel_processor
suffix:semicolon
r_extern
r_void
id|smp_message_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ipi_count
suffix:semicolon
r_extern
id|__volatile__
r_int
r_int
id|kernel_counter
suffix:semicolon
r_extern
id|__volatile__
r_int
r_int
id|syscall_count
suffix:semicolon
r_extern
r_void
id|print_lock_state
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|smpfunc_t
r_typedef
r_void
(paren
op_star
id|smpfunc_t
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
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
id|cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
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
id|__volatile__
r_int
r_int
id|smp_proc_in_lock
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* for computing process time */
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* Sparc specific messages. */
DECL|macro|MSG_CROSS_CALL
mdefine_line|#define MSG_CROSS_CALL         0x0005       /* run func on cpus */
multiline_comment|/* Empirical PROM processor mailbox constants.  If the per-cpu mailbox&n; * contains something other than one of these then the ipi is from&n; * Linux&squot;s active_kernel_processor.  This facility exists so that&n; * the boot monitor can capture all the other cpus when one catches&n; * a watchdog reset or the user enters the monitor using L1-A keys.&n; */
DECL|macro|MBOX_STOPCPU
mdefine_line|#define MBOX_STOPCPU          0xFB
DECL|macro|MBOX_IDLECPU
mdefine_line|#define MBOX_IDLECPU          0xFC
DECL|macro|MBOX_IDLECPU2
mdefine_line|#define MBOX_IDLECPU2         0xFD
DECL|macro|MBOX_STOPCPU2
mdefine_line|#define MBOX_STOPCPU2         0xFE
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY     20
DECL|macro|SMP_FROM_INT
mdefine_line|#define SMP_FROM_INT&t;&t;1
DECL|macro|SMP_FROM_SYSCALL
mdefine_line|#define SMP_FROM_SYSCALL&t;2
macro_line|#endif /* !(__SMP__) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID            0xFF
macro_line|#endif /* !(_SPARC64_SMP_H) */
eof
