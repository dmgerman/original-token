multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * (C) Copyright 1996  Linus Torvalds, Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_SEMAPHORE_H
DECL|macro|__ASM_MIPS_SEMAPHORE_H
mdefine_line|#define __ASM_MIPS_SEMAPHORE_H
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
mdefine_line|#define MUTEX ((struct semaphore) { ATOMIC_INIT(1), ATOMIC_INIT(0), NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { ATOMIC_INIT(0), ATOMIC_INIT(0), NULL })
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
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; *&n; * This is trivially done with load_locked/store_cond,&n; * which we have.  Let the rest of the losers suck eggs.&n; */
DECL|function|wake_one_more
r_static
r_inline
r_void
id|wake_one_more
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
)brace
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
id|ret
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tll&bslash;t%1,%2&bslash;n&quot;
l_string|&quot;blez&bslash;t%1,2f&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%0,%1,1&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
l_string|&quot;.text&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
id|ret
op_assign
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; */
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
macro_line|#endif /* __ASM_MIPS_SEMAPHORE_H */
eof