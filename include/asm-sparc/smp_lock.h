multiline_comment|/* smp_lock.h: 32-bit Sparc SMP master lock primitives.&n; *&n; * Copyright (C) 1996,1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC_SMPLOCK_H
DECL|macro|__SPARC_SMPLOCK_H
mdefine_line|#define __SPARC_SMPLOCK_H
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while(0)
macro_line|#else
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/* Release global kernel lock and global interrupt lock */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if((depth = (task)-&gt;lock_depth) != 0) {&t;&t;&bslash;&n;&t;&t;__cli();&t;&t;&t;&t;&bslash;&n;&t;&t;(task)-&gt;lock_depth = 0;&t;&t;&t;&bslash;&n;&t;&t;klock_info.akp = NO_PROC_ID;&t;&t;&bslash;&n;&t;&t;klock_info.kernel_flag = 0;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;release_irqlock(cpu);&t;&t;&t;&t;&bslash;&n;&t;__sti();&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* Do not fuck with this without consulting arch/sparc/lib/locks.S first! */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(depth) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;register struct klock_info *klip asm(&quot;g1&quot;);&t;&t;&t;&bslash;&n;&t;&t;register int proc asm(&quot;g5&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;klip = &amp;klock_info;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;proc = cpu;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     &quot;call&t;___lock_reacquire_kernel&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&t;     &quot; mov&t;%2, %%g2&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     : /* No outputs. */&t;&t;&t;&bslash;&n;&t;&t;&t;&t;     : &quot;r&quot; (klip), &quot;r&quot; (proc), &quot;r&quot; (depth)&t;&bslash;&n;&t;&t;&t;&t;     : &quot;g2&quot;, &quot;g3&quot;, &quot;g4&quot;, &quot;g7&quot;, &quot;memory&quot;, &quot;cc&quot;);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* The following acquire and release the master kernel global lock,&n; * the idea is that the usage of this mechanmism becomes less and less&n; * as time goes on, to the point where they are no longer needed at all&n; * and can thus disappear.&n; */
multiline_comment|/* Do not fuck with this without consulting arch/sparc/lib/locks.S first! */
DECL|function|lock_kernel
r_extern
id|__inline__
r_void
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
r_register
r_struct
id|klock_info
op_star
id|klip
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|proc
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
id|klip
op_assign
op_amp
id|klock_info
suffix:semicolon
id|proc
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___lock_kernel
id|ld
(braket
op_mod
op_mod
id|g6
op_plus
op_mod
l_int|0
)braket
comma
op_mod
op_mod
id|g2
l_string|&quot;&t;: : &quot;
id|i
l_string|&quot; (AOFF_task_lock_depth), &quot;
id|r
l_string|&quot; (klip), &quot;
id|r
"&quot;"
(paren
id|proc
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Release kernel global lock. */
DECL|function|unlock_kernel
r_extern
id|__inline__
r_void
id|unlock_kernel
c_func
(paren
r_void
)paren
(brace
r_register
r_struct
id|klock_info
op_star
id|klip
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|klip
op_assign
op_amp
id|klock_info
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___unlock_kernel
id|ld
(braket
op_mod
op_mod
id|g6
op_plus
op_mod
l_int|0
)braket
comma
op_mod
op_mod
id|g2
l_string|&quot;&t;: : &quot;
id|i
l_string|&quot; (AOFF_task_lock_depth), &quot;
id|r
"&quot;"
(paren
id|klip
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__SPARC_SMPLOCK_H) */
macro_line|#endif /* (__SMP__) */
eof
