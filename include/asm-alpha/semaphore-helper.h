macro_line|#ifndef _ALPHA_SEMAPHORE_HELPER_H
DECL|macro|_ALPHA_SEMAPHORE_HELPER_H
mdefine_line|#define _ALPHA_SEMAPHORE_HELPER_H
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores helper functions.&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * (C) Copyright 1999 Richard Henderson&n; */
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; *&n; * This is trivially done with load_locked/store_cond,&n; * which we have.  Let the rest of the losers suck eggs.&n; */
r_static
r_inline
r_void
DECL|function|wake_one_more
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
r_static
r_inline
r_int
DECL|function|waking_non_zero
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
multiline_comment|/* An atomic conditional decrement.  */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%2&bslash;n&quot;
l_string|&quot;&t;blt&t;%1,2f&bslash;n&quot;
l_string|&quot;&t;subl&t;%1,1,%0&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%0,%2&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,3f&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
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
id|sem-&gt;waking.counter
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
OG
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_interruptible:&n; *&t;1&t;got the lock&n; *&t;0&t;go to sleep&n; *&t;-EINTR&t;interrupted&n; *&n; * We must undo the sem-&gt;count down_interruptible decrement&n; * simultaneously and atomicly with the sem-&gt;waking adjustment,&n; * otherwise we can race with wake_one_more.&n; *&n; * This is accomplished by doing a 64-bit ll/sc on the 2 32-bit words.&n; */
r_static
r_inline
r_int
DECL|function|waking_non_zero_interruptible
id|waking_non_zero_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
id|ret
comma
id|tmp
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
multiline_comment|/* &quot;Equivalent&quot; C.  Note that we have to do this all without&n;&t;   (taken) branches in order to be a valid ll/sc sequence.&n;&n;&t;   do {&n;&t;       tmp = ldq_l;&n;&t;       ret = 0;&n;&t;       if (tmp &gt;= 0) {&n;&t;           tmp += 0xffffffff00000000;&n;&t;           ret = 1;&n;&t;       }&n;&t;       else if (pending) {&n;&t;&t;   // Since -1 + 1 carries into the high word, we have&n;&t;&t;   // to be more careful adding 1 here.&n;&t;&t;   tmp = (tmp &amp; 0xffffffff00000000)&n;&t;&t;&t; | ((tmp + 1) &amp; 0x00000000ffffffff;&n;&t;           ret = -EINTR;&n;&t;       }&n;&t;       else {&n;&t;&t;   break;&t;// ideally.  we don&squot;t actually break &n;&t;&t;   &t;&t;// since this is a predicate we don&squot;t&n;&t;&t;&t;&t;// have, and is more trouble to build&n;&t;&t;&t;&t;// than to elide the noop stq_c.&n;&t;       }&n;&t;       tmp = stq_c = tmp;&n;&t;   } while (tmp == 0);&n;&t;*/
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l&t;%1,%4&bslash;n&quot;
l_string|&quot;&t;lda&t;%0,0&bslash;n&quot;
l_string|&quot;&t;cmovne&t;%5,%6,%0&bslash;n&quot;
l_string|&quot;&t;addq&t;%1,1,%2&bslash;n&quot;
l_string|&quot;&t;and&t;%1,%7,%3&bslash;n&quot;
l_string|&quot;&t;andnot&t;%2,%7,%2&bslash;n&quot;
l_string|&quot;&t;cmovge&t;%1,1,%0&bslash;n&quot;
l_string|&quot;&t;or&t;%3,%2,%2&bslash;n&quot;
l_string|&quot;&t;addq&t;%1,%7,%3&bslash;n&quot;
l_string|&quot;&t;cmovne&t;%5,%2,%1&bslash;n&quot;
l_string|&quot;&t;cmovge&t;%2,%3,%1&bslash;n&quot;
l_string|&quot;&t;stq_c&t;%1,%4&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,3f&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|sem
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
op_minus
id|EINTR
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0xffffffff00000000
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * waking_non_zero_trylock is unused.  we do everything in &n; * down_trylock and let non-ll/sc hosts bounce around.&n; */
r_static
r_inline
r_int
DECL|function|waking_non_zero_trylock
id|waking_non_zero_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
