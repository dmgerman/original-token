macro_line|#ifndef __I386_SMPLOCK_H
DECL|macro|__I386_SMPLOCK_H
mdefine_line|#define __I386_SMPLOCK_H
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
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
mdefine_line|#define release_kernel_lock(task, cpu, depth) &bslash;&n;do { &bslash;&n;&t;if ((depth = (task)-&gt;lock_depth) != 0) { &bslash;&n;&t;&t;__cli(); &bslash;&n;&t;&t;(task)-&gt;lock_depth = 0; &bslash;&n;&t;&t;active_kernel_processor = NO_PROC_ID; &bslash;&n;&t;&t;clear_bit(0,&amp;kernel_flag); &bslash;&n;&t;} &bslash;&n;&t;release_irqlock(cpu); &bslash;&n;&t;__sti(); &bslash;&n;} while (0)
multiline_comment|/* Re-acquire the kernel lock */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth) &bslash;&n;do { if (depth) __asm__ __volatile__( &bslash;&n;&t;&quot;cli&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call __lock_kernel&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %2,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sti&quot; &bslash;&n;&t;: &quot;=m&quot; (task-&gt;lock_depth) &bslash;&n;&t;: &quot;d&quot; (cpu), &quot;c&quot; (depth)); &bslash;&n;} while (0)
r_extern
r_const
r_char
id|lk_lockmsg
(braket
)braket
suffix:semicolon
multiline_comment|/* Locking the kernel */
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_irq_count
(braket
id|cpu
)braket
)paren
(brace
id|__label__
id|l1
suffix:semicolon
id|l1
suffix:colon
id|printk
c_func
(paren
id|lk_lockmsg
comma
op_logical_and
id|l1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu
op_eq
id|global_irq_holder
)paren
(brace
id|__label__
id|l2
suffix:semicolon
id|l2
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Ugh at %p&bslash;n&quot;
comma
op_logical_and
id|l2
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|pushfl
id|cli
id|cmpl
"$"
l_int|0
comma
op_mod
l_int|0
id|jne
l_float|0f
id|call
id|__lock_kernel
l_int|0
suffix:colon
id|incl
op_mod
l_int|0
id|popfl
"&quot;"
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|current-&gt;lock_depth
)paren
comma
l_string|&quot;d&quot;
(paren
id|cpu
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|pushfl
id|cli
id|decl
op_mod
l_int|0
id|jnz
l_float|1f
id|movb
op_mod
l_int|1
comma
l_string|&quot; __STR(active_kernel_processor) &quot;
id|lock
id|btrl
"$"
l_int|0
comma
l_string|&quot; __STR(kernel_flag) &quot;
l_int|1
suffix:colon
id|popfl
"&quot;"
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
id|current-&gt;lock_depth
)paren
comma
l_string|&quot;i&quot;
(paren
id|NO_PROC_ID
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
macro_line|#endif /* __I386_SMPLOCK_H */
eof
