macro_line|#ifndef _SPARC_SEMAPHORE_H
DECL|macro|_SPARC_SEMAPHORE_H
mdefine_line|#define _SPARC_SEMAPHORE_H
multiline_comment|/* Dinky, good for nothing, just barely irq safe, Sparc semaphores. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|waking
id|atomic_t
id|waking
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MUTEX
mdefine_line|#define MUTEX ((struct semaphore) { { (1 &lt;&lt; 8) }, { 0 }, NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { { 0 }, { 0 }, NULL })
r_extern
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
DECL|macro|sema_init
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), val)
DECL|function|waking_non_zero
r_static
r_inline
r_int
id|waking_non_zero
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
OG
l_int|0
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* This isn&squot;t quite as clever as the x86 side, I&squot;ll be fixing this&n; * soon enough.&n; */
DECL|function|down
r_extern
r_inline
r_void
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
OL
l_int|0
)paren
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
DECL|function|down_interruptible
r_extern
r_inline
r_int
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|up
r_extern
r_inline
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_if
c_cond
(paren
id|atomic_inc_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_le
l_int|0
)paren
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC_SEMAPHORE_H) */
eof
