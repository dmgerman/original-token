multiline_comment|/* smp.h: PPC specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _PPC_SMP_H
DECL|macro|_PPC_SMP_H
mdefine_line|#define _PPC_SMP_H
macro_line|#ifdef __SMP__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NCPUS
)braket
suffix:semicolon
multiline_comment|/* Per processor PPC parameters we need. */
DECL|struct|cpuinfo_PPC
r_struct
id|cpuinfo_PPC
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
id|cpuinfo_PPC
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(__SMP__) */
macro_line|#endif /* !(_PPC_SMP_H) */
eof
