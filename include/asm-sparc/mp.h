multiline_comment|/* mp.h:  Multiprocessing definitions for the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MP_H
DECL|macro|_SPARC_MP_H
mdefine_line|#define _SPARC_MP_H
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
r_extern
r_int
id|linux_smp_still_initting
suffix:semicolon
DECL|struct|sparc_percpu
r_struct
id|sparc_percpu
(brace
DECL|member|trap_table
r_struct
id|tt_entry
id|trap_table
(braket
id|NUM_SPARC_TRAPS
)braket
suffix:semicolon
multiline_comment|/* One page */
DECL|member|kernel_stack
r_int
r_int
id|kernel_stack
(braket
id|PAGE_SIZE
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* One page */
DECL|member|cpuid
r_int
id|cpuid
suffix:semicolon
multiline_comment|/* Who am I? */
DECL|member|cpu_is_alive
r_int
id|cpu_is_alive
suffix:semicolon
multiline_comment|/* Linux has fired it up. */
DECL|member|cpu_is_idling
r_int
id|cpu_is_idling
suffix:semicolon
multiline_comment|/* Is sitting in the idle loop. */
multiline_comment|/* More to come... */
DECL|member|filler
r_char
id|filler
(braket
id|PERCPU_ENTSIZE
op_minus
(paren
id|PAGE_SIZE
op_star
l_int|2
)paren
op_minus
l_int|0xc
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sparc_percpu
op_star
id|percpu_table
suffix:semicolon
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
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NCPUS
)braket
suffix:semicolon
macro_line|#endif /* !(_SPARC_MP_H) */
eof
