multiline_comment|/*&n; * i386 semaphore implementation.&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * Portions Copyright 1999 Red Hat, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * rw semaphores implemented November 1999 by Benjamin LaHaise &lt;bcrl@redhat.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * Semaphores are implemented using a two-way counter:&n; * The &quot;count&quot; variable is decremented for each process&n; * that tries to aquire the semaphore, while the &quot;sleeping&quot;&n; * variable is a count of such aquires.&n; *&n; * Notably, the inline &quot;up()&quot; and &quot;down()&quot; functions can&n; * efficiently test if they need to do any extra work (up&n; * needs to do something only if count was negative before&n; * the increment operation.&n; *&n; * &quot;sleeping&quot; and the contention routine ordering is&n; * protected by the semaphore spinlock.&n; *&n; * Note that these functions are only called when there is&n; * contention on the lock, and as such all this is the&n; * &quot;non-critical&quot; part of the whole semaphore business. The&n; * critical part is the inline stuff in &lt;asm/semaphore.h&gt;&n; * where we want to avoid any extra jumps and calls.&n; */
multiline_comment|/*&n; * Logic:&n; *  - only on a boundary condition do we need to care. When we go&n; *    from a negative count to a non-negative, we wake people up.&n; *  - when we go from a non-negative count to a negative do we&n; *    (a) synchronize with the &quot;sleeper&quot; count and (b) make sure&n; *    that we&squot;re on the wakeup list before we synchronize so that&n; *    we cannot lose wakeup events.&n; */
DECL|function|__up
r_void
id|__up
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
DECL|variable|semaphore_lock
r_static
id|spinlock_t
id|semaphore_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|__down
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
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
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
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
id|tsk-&gt;state
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
)brace
DECL|function|__down_interruptible
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
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
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * With signals pending, this turns into&n;&t;&t; * the trylock failure case - we won&squot;t be&n;&t;&t; * sleeping, and we* can&squot;t get the lock as&n;&t;&t; * it has contention. Just correct the count&n;&t;&t; * and exit.&n;&t;&t; */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINTR
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|atomic_add
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock. The&n;&t;&t; * &quot;-1&quot; is because we&squot;re still hoping to get&n;&t;&t; * the lock.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
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
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Trylock failed - make sure we correct for&n; * having decremented the count.&n; *&n; * We could have done the trylock with a&n; * single &quot;cmpxchg&quot; without failure cases,&n; * but then it wouldn&squot;t work on a 386.&n; */
DECL|function|__down_trylock
r_int
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|sleepers
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_lock
comma
id|flags
)paren
suffix:semicolon
id|sleepers
op_assign
id|sem-&gt;sleepers
op_plus
l_int|1
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Add &quot;everybody else&quot; and us into it. They aren&squot;t&n;&t; * playing, because we own the spinlock.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The semaphore operations have a special calling sequence that&n; * allow us to do a simpler in-line version of them. These routines&n; * need to convert that sequence back into the C sequence when&n; * there is contention on the semaphore.&n; *&n; * %ecx contains the semaphore pointer on entry. Save the C-clobbered&n; * registers (%eax, %edx and %ecx) except %eax when used as a return&n; * value..&n; */
id|asm
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed&bslash;n&quot;
l_string|&quot;__down_failed:&bslash;n&bslash;t&quot;
l_string|&quot;pushl %eax&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
l_string|&quot;popl %eax&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed_interruptible&bslash;n&quot;
l_string|&quot;__down_failed_interruptible:&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed_trylock&bslash;n&quot;
l_string|&quot;__down_failed_trylock:&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down_trylock&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __up_wakeup&bslash;n&quot;
l_string|&quot;__up_wakeup:&bslash;n&bslash;t&quot;
l_string|&quot;pushl %eax&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __up&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
l_string|&quot;popl %eax&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
"&quot;"
dot
id|align
l_int|4
dot
id|globl
id|__down_read_failed
id|__down_read_failed
suffix:colon
id|pushl
op_mod
id|edx
id|pushl
op_mod
id|ecx
id|jnc
l_float|2f
l_int|3
suffix:colon
id|call
id|down_read_failed_biased
l_int|1
suffix:colon
id|popl
op_mod
id|ecx
id|popl
op_mod
id|edx
id|ret
l_int|2
suffix:colon
id|call
id|down_read_failed
l_string|&quot; LOCK &quot;
id|subl
"$"
l_int|1
comma
(paren
op_mod
id|eax
)paren
id|jns
l_int|1
id|b
id|jnc
l_int|2
id|b
id|jmp
l_int|3
id|b
"&quot;"
)paren
suffix:semicolon
id|asm
c_func
(paren
"&quot;"
dot
id|align
l_int|4
dot
id|globl
id|__down_write_failed
id|__down_write_failed
suffix:colon
id|pushl
op_mod
id|edx
id|pushl
op_mod
id|ecx
id|jnc
l_float|2f
l_int|3
suffix:colon
id|call
id|down_write_failed_biased
l_int|1
suffix:colon
id|popl
op_mod
id|ecx
id|popl
op_mod
id|edx
id|ret
l_int|2
suffix:colon
id|call
id|down_write_failed
l_string|&quot; LOCK &quot;
id|subl
"$"
l_string|&quot; RW_LOCK_BIAS_STR &quot;
comma
(paren
op_mod
id|eax
)paren
id|jz
l_int|1
id|b
id|jnc
l_int|2
id|b
id|jmp
l_int|3
id|b
"&quot;"
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_wake_readers
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_wake_writer
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_read_failed_biased
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_write_failed_biased
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
DECL|function|down_read_failed_biased
r_struct
id|rw_semaphore
op_star
id|down_read_failed_biased
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
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
multiline_comment|/* put ourselves at the head of the list */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|sem-&gt;read_bias_granted
op_logical_and
id|xchg
c_func
(paren
op_amp
id|sem-&gt;read_bias_granted
comma
l_int|0
)paren
)paren
r_break
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem-&gt;read_bias_granted
)paren
id|schedule
c_func
(paren
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
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
DECL|function|down_write_failed_biased
r_struct
id|rw_semaphore
op_star
id|down_write_failed_biased
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;write_bias_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* put ourselves at the end of the list */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|sem-&gt;write_bias_granted
op_logical_and
id|xchg
c_func
(paren
op_amp
id|sem-&gt;write_bias_granted
comma
l_int|0
)paren
)paren
r_break
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sem-&gt;write_bias_granted
)paren
id|schedule
c_func
(paren
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
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/* if the lock is currently unbiased, awaken the sleepers&n;&t; * FIXME: this wakes up the readers early in a bit of a&n;&t; * stampede -&gt; bad!&n;&t; */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_ge
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/* Wait for the lock to become unbiased.  Readers&n; * are non-exclusive. =)&n; */
DECL|function|down_read_failed
r_struct
id|rw_semaphore
op_star
id|down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|__up_read
c_func
(paren
id|sem
)paren
suffix:semicolon
multiline_comment|/* this takes care of granting the lock */
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
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_ge
l_int|0
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
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
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
multiline_comment|/* Wait for the lock to become unbiased. Since we&squot;re&n; * a writer, we&squot;ll make ourselves exclusive.&n; */
DECL|function|down_write_failed
r_struct
id|rw_semaphore
op_star
id|down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|__up_write
c_func
(paren
id|sem
)paren
suffix:semicolon
multiline_comment|/* this takes care of granting the lock */
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
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_EXCLUSIVE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_ge
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* we must attempt to aquire or bias the lock */
id|schedule
c_func
(paren
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
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|sem
suffix:semicolon
)brace
id|asm
c_func
(paren
"&quot;"
dot
id|align
l_int|4
dot
id|globl
id|__rwsem_wake
id|__rwsem_wake
suffix:colon
id|pushl
op_mod
id|edx
id|pushl
op_mod
id|ecx
id|jz
l_float|1f
id|call
id|rwsem_wake_readers
id|jmp
l_float|2f
l_int|1
suffix:colon
id|call
id|rwsem_wake_writer
l_int|2
suffix:colon
id|popl
op_mod
id|ecx
id|popl
op_mod
id|edx
id|ret
"&quot;"
)paren
suffix:semicolon
multiline_comment|/* Called when someone has done an up that transitioned from&n; * negative to non-negative, meaning that the lock has been&n; * granted to whomever owned the bias.&n; */
DECL|function|rwsem_wake_readers
r_struct
id|rw_semaphore
op_star
id|rwsem_wake_readers
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|sem-&gt;read_bias_granted
comma
l_int|1
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
r_return
id|sem
suffix:semicolon
)brace
DECL|function|rwsem_wake_writer
r_struct
id|rw_semaphore
op_star
id|rwsem_wake_writer
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|sem-&gt;write_bias_granted
comma
l_int|1
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
r_return
id|sem
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SMP)
id|asm
c_func
(paren
"&quot;"
dot
id|align
l_int|4
dot
id|globl
id|__write_lock_failed
id|__write_lock_failed
suffix:colon
l_string|&quot; LOCK &quot;
id|addl
"$"
l_string|&quot; RW_LOCK_BIAS_STR &quot;
comma
(paren
op_mod
id|eax
)paren
l_int|1
suffix:colon
id|cmpl
"$"
l_string|&quot; RW_LOCK_BIAS_STR &quot;
comma
(paren
op_mod
id|eax
)paren
id|jne
l_int|1
id|b
l_string|&quot; LOCK &quot;
id|subl
"$"
l_string|&quot; RW_LOCK_BIAS_STR &quot;
comma
(paren
op_mod
id|eax
)paren
id|jnz
id|__write_lock_failed
id|ret
dot
id|align
l_int|4
dot
id|globl
id|__read_lock_failed
id|__read_lock_failed
suffix:colon
id|lock
suffix:semicolon
id|incl
(paren
op_mod
id|eax
)paren
l_int|1
suffix:colon
id|cmpl
"$"
l_int|1
comma
(paren
op_mod
id|eax
)paren
id|js
l_int|1
id|b
id|lock
suffix:semicolon
id|decl
(paren
op_mod
id|eax
)paren
id|js
id|__read_lock_failed
id|ret
"&quot;"
)paren
suffix:semicolon
macro_line|#endif
eof
