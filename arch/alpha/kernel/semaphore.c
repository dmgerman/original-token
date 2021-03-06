multiline_comment|/*&n; * Alpha semaphore implementation.&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * (C) Copyright 1999, 2000 Richard Henderson&n; */
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * Semaphores are implemented using a two-way counter:&n; * &n; * The &quot;count&quot; variable is decremented for each process that tries to sleep,&n; * while the &quot;waking&quot; variable is incremented when the &quot;up()&quot; code goes to&n; * wake up waiting processes.&n; *&n; * Notably, the inline &quot;up()&quot; and &quot;down()&quot; functions can efficiently test&n; * if they need to do any extra work (up needs to do something only if count&n; * was negative before the increment operation.&n; *&n; * waking_non_zero() (from asm/semaphore.h) must execute atomically.&n; *&n; * When __up() is called, the count was negative before incrementing it,&n; * and we need to wake up somebody.&n; *&n; * This routine adds one to the count of processes that need to wake up and&n; * exit.  ALL waiting processes actually wake up but only the one that gets&n; * to the &quot;waking&quot; field first will gate through and acquire the semaphore.&n; * The others will go back to sleep.&n; *&n; * Note that these functions are only called when there is contention on the&n; * lock, and as such all this is the &quot;non-critical&quot; part of the whole&n; * semaphore business. The critical part is the inline stuff in&n; * &lt;asm/semaphore.h&gt; where we want to avoid any extra jumps and calls.&n; */
multiline_comment|/*&n; * Perform the &quot;down&quot; function.  Return zero for semaphore acquired,&n; * return negative for signalled out of the function.&n; *&n; * If called from down, the return is ignored and the wait loop is&n; * not interruptible.  This means that a task waiting on a semaphore&n; * using &quot;down()&quot; cannot be killed until someone does an &quot;up()&quot; on&n; * the semaphore.&n; *&n; * If called from down_interruptible, the return value gets checked&n; * upon return.  If the return value is negative then the task continues&n; * with the negative value in the return register (it can be tested by&n; * the caller).&n; *&n; * Either form may be used in conjunction with &quot;up()&quot;.&n; */
r_void
DECL|function|__down_failed
id|__down_failed
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down failed(%p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* At this point we know that sem-&gt;count is negative.  In order&n;&t;   to avoid racing with __up, we must check for wakeup before&n;&t;   going to sleep the first time.  */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|ret
comma
id|tmp
suffix:semicolon
multiline_comment|/* An atomic conditional decrement of sem-&gt;waking.  */
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
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;waking
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down acquired(%p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|__down_failed_interruptible
id|__down_failed_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down failed(%p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|tmp
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
multiline_comment|/* We must undo the sem-&gt;count down_interruptible decrement&n;&t;&t;   simultaneously and atomicly with the sem-&gt;waking&n;&t;&t;   adjustment, otherwise we can race with __up.  This is&n;&t;&t;   accomplished by doing a 64-bit ll/sc on two 32-bit words.&n;&t;&t;&n;&t;&t;   &quot;Equivalent&quot; C.  Note that we have to do this all without&n;&t;&t;   (taken) branches in order to be a valid ll/sc sequence.&n;&n;&t;&t;   do {&n;&t;&t;       tmp = ldq_l;&n;&t;&t;       ret = 0;&n;&t;&t;       if (tmp &gt;= 0) {&t;&t;&t;// waking &gt;= 0&n;&t;&t;           tmp += 0xffffffff00000000;&t;// waking -= 1&n;&t;&t;           ret = 1;&n;&t;&t;       }&n;&t;&t;       else if (pending) {&n;&t;&t;&t;   // count += 1, but since -1 + 1 carries into the&n;&t;&t;&t;   // high word, we have to be more careful here.&n;&t;&t;&t;   tmp = (tmp &amp; 0xffffffff00000000)&n;&t;&t;&t;&t; | ((tmp + 1) &amp; 0x00000000ffffffff);&n;&t;&t;           ret = -EINTR;&n;&t;&t;       }&n;&t;&t;       tmp = stq_c = tmp;&n;&t;&t;   } while (tmp == 0);&n;&t;&t;*/
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
id|current
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
multiline_comment|/* At this point we have ret&n;&t;&t;  &t;1&t;got the lock&n;&t;&t;  &t;0&t;go to sleep&n;&t;&t;  &t;-EINTR&t;interrupted  */
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down %s(%p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
id|ret
OL
l_int|0
ques
c_cond
l_string|&quot;interrupted&quot;
suffix:colon
l_string|&quot;acquired&quot;
)paren
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Convert &quot;got the lock&quot; to 0==success.  */
r_return
(paren
id|ret
OL
l_int|0
ques
c_cond
id|ret
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|__up_wakeup
id|__up_wakeup
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
r_void
DECL|function|down
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_int
DECL|function|down_interruptible
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_int
DECL|function|down_trylock
id|down_trylock
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
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|ret
op_assign
id|__down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down_trylock %s from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|ret
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;acquired&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|up
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): up(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * RW Semaphores&n; */
r_void
DECL|function|__down_read_failed
id|__down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_int
id|count
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|retry_down
suffix:colon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
multiline_comment|/* Waiting on multiple readers and/or writers.  */
multiline_comment|/* Undo the acquisition we started in down_read.  */
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
OL
l_int|0
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_goto
id|retry_down
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Waiting on exactly one writer.  */
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|sem-&gt;granted
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
)brace
r_void
DECL|function|__down_write_failed
id|__down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_int
id|count
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|retry_down
suffix:colon
r_if
c_cond
(paren
id|count
op_plus
id|RW_LOCK_BIAS
OL
l_int|0
)paren
(brace
multiline_comment|/* Waiting on multiple readers and/or writers.  */
multiline_comment|/* Undo the acquisition we started in down_write.  */
id|atomic_add
c_func
(paren
id|RW_LOCK_BIAS
comma
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_plus
id|RW_LOCK_BIAS
OL
l_int|0
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|count
op_assign
id|atomic_sub_return
c_func
(paren
id|RW_LOCK_BIAS
comma
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
l_int|0
)paren
r_goto
id|retry_down
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Waiting on exactly one writer.  */
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
l_int|1
comma
op_amp
id|sem-&gt;granted
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;write_bias_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/* If the lock is currently unbiased, awaken the sleepers.&n;&t;&t;   FIXME: This wakes up the readers early in a bit of a&n;&t;&t;   stampede -&gt; bad!  */
id|count
op_assign
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__builtin_expect
c_func
(paren
id|count
op_ge
l_int|0
comma
l_int|0
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|__rwsem_wake
id|__rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_int
id|readers
)paren
(brace
r_if
c_cond
(paren
id|readers
)paren
(brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|sem-&gt;granted
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|1
comma
op_amp
id|sem-&gt;granted
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;write_bias_wait
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|down_read
id|down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__down_read
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;granted
op_amp
l_int|2
)paren
id|BUG
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
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|down_write
id|down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__down_write
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
r_if
c_cond
(paren
id|sem-&gt;granted
op_amp
l_int|3
)paren
id|BUG
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
id|sem-&gt;writers
)paren
)paren
id|BUG
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
id|sem-&gt;readers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|up_read
id|up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;granted
op_amp
l_int|2
)paren
id|BUG
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
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
id|__up_read
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_void
DECL|function|up_write
id|up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;granted
op_amp
l_int|3
)paren
id|BUG
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
id|sem-&gt;readers
)paren
)paren
id|BUG
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
id|sem-&gt;writers
)paren
op_ne
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
id|__up_write
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
eof
