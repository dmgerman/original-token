multiline_comment|/*&n; * &lt;asm/smplock.h&gt;&n; *&n; * i386 SMP lock implementation&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0) &bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag); &bslash;&n;&t;release_irqlock(cpu); &bslash;&n;&t;__sti(); &bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0) &bslash;&n;&t;&t;spin_lock(&amp;kernel_flag); &bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;jne 9f&quot;
id|spin_lock_string
l_string|&quot;&bslash;n9:&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
comma
l_string|&quot;=m&quot;
(paren
id|current-&gt;lock_depth
)paren
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
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;jns 9f&bslash;n&quot;
id|spin_unlock_string
l_string|&quot;&bslash;n9:&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
comma
l_string|&quot;=m&quot;
(paren
id|current-&gt;lock_depth
)paren
)paren
suffix:semicolon
)brace
eof