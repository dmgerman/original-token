multiline_comment|/* mp.c:  SMP cpu idling and dispatch on the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller&n; */
macro_line|#include &lt;asm/mp.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
DECL|variable|percpu_table
r_struct
id|sparc_percpu
op_star
id|percpu_table
suffix:semicolon
r_void
DECL|function|sparc_cpu_init
id|sparc_cpu_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We now have our per-cpu mappings ok, and we should&n;&t; * be good to go.&n;&t; */
multiline_comment|/* Do cache crap here. */
multiline_comment|/* CPU initted, idle the puppy. */
r_return
suffix:semicolon
)brace
r_extern
id|thiscpus_mid
suffix:semicolon
r_void
DECL|function|sparc_cpu_idle
id|sparc_cpu_idle
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
multiline_comment|/*&t;cpuid = get_cpuid(); */
id|cpuid
op_assign
(paren
id|thiscpus_mid
op_amp
(paren
op_complement
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/*&t;printk(&quot;SMP: cpu%d has entered idle loop&quot;, cpuid); */
multiline_comment|/* Say that we exist and set up. */
id|percpu_table
(braket
id|cpuid
)braket
dot
id|cpuid
op_assign
id|cpuid
suffix:semicolon
id|percpu_table
(braket
id|cpuid
)braket
dot
id|cpu_is_alive
op_assign
l_int|0x1
suffix:semicolon
id|percpu_table
(braket
id|cpuid
)braket
dot
id|cpu_is_idling
op_assign
l_int|0x1
suffix:semicolon
multiline_comment|/* Let other cpus catch up. */
r_while
c_loop
(paren
id|linux_smp_still_initting
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;cpu%d done spinning&bslash;n&quot;
comma
id|get_cpuid
c_func
(paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Do something useful here... */
r_return
suffix:semicolon
)brace
eof
