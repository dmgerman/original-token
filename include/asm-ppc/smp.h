multiline_comment|/* smp.h: PPC specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _PPC_SMP_H
DECL|macro|_PPC_SMP_H
mdefine_line|#define _PPC_SMP_H
macro_line|#include &lt;linux/kernel.h&gt; /* for panic */
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
DECL|member|udelay_val
r_int
r_int
id|udelay_val
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
id|cpu_logical_map
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
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_of
c_func
(paren
)paren
)paren
multiline_comment|/* assume prep */
id|panic
c_func
(paren
l_string|&quot;hard_smp_processor_id()&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;hard_smp_processor_id()&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() hard_smp_processor_id()
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(__SMP__) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID               0xFF            /* No processor magic marker */
macro_line|#endif /* !(_PPC_SMP_H) */
eof
