macro_line|#ifndef _I386_SEMAPHORE_H
DECL|macro|_I386_SEMAPHORE_H
mdefine_line|#define _I386_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * Modified 1996-12-23 by Dave Grothe &lt;dave@gcom.com&gt; to fix bugs in&n; *                     the original code and to make semaphore waits&n; *                     interruptible so that processes waiting on&n; *                     semaphores can be killed.&n; *&n; * If you would like to see an analysis of this implementation, please&n; * ftp to gcom.com and download the file&n; * /pub/linux/src/semaphore/semaphore-2.0.24.tar.gz.&n; *&n; */
macro_line|#include &lt;asm/system.h&gt;
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
r_int
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
mdefine_line|#define MUTEX ((struct semaphore) { { 1 }, 0, NULL })
DECL|macro|MUTEX_LOCKED
mdefine_line|#define MUTEX_LOCKED ((struct semaphore) { { 0 }, 0, NULL })
id|asmlinkage
r_void
id|__down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_interruptible
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
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
mdefine_line|#define sema_init(sem, val)&t;atomic_set(&amp;((sem)-&gt;count), (val))
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; *&n; * This is trivially done with load_locked/store_cond,&n; * but on the x86 we need an external synchronizer.&n; * Currently this is just the global interrupt lock,&n; * bah. Go for a smaller spinlock some day.&n; *&n; * (On the other hand this shouldn&squot;t be in any critical&n; * path, so..)&n; */
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
r_int
r_int
id|flags
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
id|sem-&gt;waking
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
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
id|sem-&gt;waking
OG
l_int|0
)paren
(brace
id|sem-&gt;waking
op_decrement
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
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;down_failed&quot; is a special asm handler that calls the C&n; * routine that actually waits. See arch/i386/lib/semaphore.S&n; */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic down operation&bslash;n&bslash;t&quot;
l_string|&quot;movl $1f,%%eax&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;decl 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;js &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|__down_failed
)paren
l_string|&quot;&bslash;n1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This version waits in interruptible state so that the waiting&n; * process can be killed.  The down_failed_interruptible routine&n; * returns negative for signalled and zero for semaphore acquired.&n; */
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
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic interruptible down operation&bslash;n&bslash;t&quot;
l_string|&quot;movl $1f,%0&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;decl 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;js &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|__down_failed_interruptible
)paren
l_string|&quot;&bslash;n&bslash;t&quot;
l_string|&quot;xorl %0,%0&quot;
l_string|&quot;&bslash;n1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;# atomic up operation&bslash;n&bslash;t&quot;
l_string|&quot;movl $1f,%%eax&bslash;n&bslash;t&quot;
macro_line|#ifdef __SMP__
l_string|&quot;lock ; &quot;
macro_line|#endif
l_string|&quot;incl 0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;jle &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|__up_wakeup
)paren
l_string|&quot;&bslash;n1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;c&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
