macro_line|#ifndef __ALPHA_SMPLOCK_H
DECL|macro|__ALPHA_SMPLOCK_H
mdefine_line|#define __ALPHA_SMPLOCK_H
macro_line|#ifndef __SMP__
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;do { } while (0)
macro_line|#else
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|kernel_lock_held
mdefine_line|#define kernel_lock_held() &bslash;&n;  (klock_info.kernel_flag &amp;&amp; (klock_info.akp == smp_processor_id()))
multiline_comment|/* Release global kernel lock and global interrupt lock */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((depth = (task)-&gt;lock_depth) != 0) {&t;&bslash;&n;&t;&t;__cli();&t;&t;&t;&t;&bslash;&n;&t;&t;(task)-&gt;lock_depth = 0;&t;&t;&t;&bslash;&n;&t;&t;klock_info.akp = NO_PROC_ID;&t;&t;&bslash;&n;&t;&t;klock_info.kernel_flag = 0;&t;&t;&bslash;&n;&t;&t;mb();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;release_irqlock(cpu);&t;&t;&t;&t;&bslash;&n;&t;__sti();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#if 1
DECL|macro|DEBUG_KERNEL_LOCK
mdefine_line|#define DEBUG_KERNEL_LOCK
macro_line|#else
DECL|macro|DEBUG_KERNEL_LOCK
macro_line|#undef DEBUG_KERNEL_LOCK
macro_line|#endif
macro_line|#ifdef DEBUG_KERNEL_LOCK
r_extern
r_void
id|___lock_kernel
c_func
(paren
id|klock_info_t
op_star
id|klip
comma
r_int
id|cpu
comma
r_int
id|ipl
)paren
suffix:semicolon
macro_line|#else /* DEBUG_KERNEL_LOCK */
DECL|function|___lock_kernel
r_static
r_inline
r_void
id|___lock_kernel
c_func
(paren
id|klock_info_t
op_star
id|klip
comma
r_int
id|cpu
comma
r_int
id|ipl
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0;&quot;
l_string|&quot;&t;blbs&t;%1,6f;&quot;
l_string|&quot;&t;or&t;%1,1,%1;&quot;
l_string|&quot;&t;stl_c&t;%1,%0;&quot;
l_string|&quot;&t;beq&t;%1,6f;&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;mov %4,$16;&quot;
l_string|&quot;&t;call_pal %3;&quot;
l_string|&quot;7:&t;ldl %1,%0;&quot;
l_string|&quot;&t;blbs %1,7b;&quot;
l_string|&quot;&t;bis $31,7,$16;&quot;
l_string|&quot;&t;call_pal %3;&quot;
l_string|&quot;&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m,=m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|klip
)paren
)paren
comma
l_string|&quot;=&amp;r,=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;0,0&quot;
(paren
id|__dummy_lock
c_func
(paren
id|klip
)paren
)paren
comma
l_string|&quot;i,i&quot;
(paren
id|PAL_swpipl
)paren
comma
l_string|&quot;i,r&quot;
(paren
id|ipl
)paren
suffix:colon
l_string|&quot;$0&quot;
comma
l_string|&quot;$1&quot;
comma
l_string|&quot;$16&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_KERNEL_LOCK */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;  if (depth) {&t;&t;&t;&t;&t;&bslash;&n;    long ipl;&t;&t;&t;&t;&t;&bslash;&n;    klock_info_t *klip = &amp;klock_info;&t;&t;&bslash;&n;    __save_and_cli(ipl);&t;&t;&t;&bslash;&n;    ___lock_kernel(klip, cpu, ipl);&t;&t;&bslash;&n;    klip-&gt;akp = cpu;&t;&t;&t;&t;&bslash;&n;    (task)-&gt;lock_depth = depth;&t;&t;&t;&bslash;&n;    __restore_flags(ipl);&t;&t;&t;&bslash;&n;  }&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* The following acquire and release the master kernel global lock,&n; * the idea is that the usage of this mechanmism becomes less and less&n; * as time goes on, to the point where they are no longer needed at all&n; * and can thus disappear.&n; */
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;&bslash;&n;if (current-&gt;lock_depth &gt; 0) {&t;&t;&t;&bslash;&n;     ++current-&gt;lock_depth;&t;&t;&t;&bslash;&n;} else {&t;&t;&t;&t;&t;&bslash;&n;  long ipl;&t;&t;&t;&t;&t;&bslash;&n;  int cpu = smp_processor_id();&t;&t;&t;&bslash;&n;  klock_info_t *klip = &amp;klock_info;&t;&t;&bslash;&n;  __save_and_cli(ipl);&t;&t;&t;&t;&bslash;&n;  ___lock_kernel(klip, cpu, ipl);&t;&t;&bslash;&n;  klip-&gt;akp = cpu;&t;&t;&t;&t;&bslash;&n;  current-&gt;lock_depth = 1;&t;&t;&t;&bslash;&n;  __restore_flags(ipl);&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* Release kernel global lock. */
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;&bslash;&n;if (current-&gt;lock_depth &gt; 1) {&t;&t;&t;&bslash;&n;  --current-&gt;lock_depth;&t;&t;&t;&bslash;&n;} else {&t;&t;&t;&t;&t;&bslash;&n;  long ipl;&t;&t;&t;&t;&t;&bslash;&n;  __save_and_cli(ipl);&t;&t;&t;&t;&bslash;&n;  klock_info.akp = NO_PROC_ID;&t;&t;&t;&bslash;&n;  klock_info.kernel_flag = KLOCK_CLEAR;&t;&t;&bslash;&n;  mb();&t;&t;&t;&t;&t;&t;&bslash;&n;  current-&gt;lock_depth = 0;&t;&t;&t;&bslash;&n;  __restore_flags(ipl);&t;&t;&t;&t;&bslash;&n;}  
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __ALPHA_SMPLOCK_H */
eof
