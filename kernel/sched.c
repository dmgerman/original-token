multiline_comment|/*&n; *  linux/kernel/sched.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;sched.c&squot; is the main kernel file. It contains scheduling primitives&n; * (sleep_on, wakeup, schedule etc) as well as a number of simple system&n; * call functions (type getpid(), which just extracts a field from&n; * current-task&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/fdreg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
DECL|variable|need_resched
r_int
id|need_resched
op_assign
l_int|0
suffix:semicolon
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
DECL|function|show_task
r_void
id|show_task
c_func
(paren
r_int
id|nr
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
id|i
comma
id|j
op_assign
l_int|4096
op_minus
r_sizeof
(paren
r_struct
id|task_struct
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d: pid=%d, state=%d, father=%d, child=%d, &quot;
comma
id|nr
comma
id|p-&gt;pid
comma
id|p-&gt;state
comma
id|p-&gt;p_pptr-&gt;pid
comma
id|p-&gt;p_cptr
ques
c_cond
id|p-&gt;p_cptr-&gt;pid
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|j
op_logical_and
op_logical_neg
(paren
(paren
r_char
op_star
)paren
(paren
id|p
op_plus
l_int|1
)paren
)paren
(braket
id|i
)braket
)paren
id|i
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d/%d chars free in kstack&bslash;n&bslash;r&quot;
comma
id|i
comma
id|j
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;   PC=%08X.&quot;
comma
op_star
(paren
l_int|1019
op_plus
(paren
r_int
r_int
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_ysptr
op_logical_or
id|p-&gt;p_osptr
)paren
id|printk
c_func
(paren
l_string|&quot;   Younger sib=%d, older sib=%d&bslash;n&bslash;r&quot;
comma
id|p-&gt;p_ysptr
ques
c_cond
id|p-&gt;p_ysptr-&gt;pid
suffix:colon
op_minus
l_int|1
comma
id|p-&gt;p_osptr
ques
c_cond
id|p-&gt;p_osptr-&gt;pid
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_state
r_void
id|show_state
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;rTask-info:&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
)paren
id|show_task
c_func
(paren
id|i
comma
id|task
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|macro|LATCH
mdefine_line|#define LATCH (1193180/HZ)
r_extern
r_void
id|mem_use
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|timer_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|union|task_union
r_union
id|task_union
(brace
DECL|member|task
r_struct
id|task_struct
id|task
suffix:semicolon
DECL|member|stack
r_char
id|stack
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|init_task
r_static
r_union
id|task_union
id|init_task
op_assign
(brace
id|INIT_TASK
comma
)brace
suffix:semicolon
DECL|variable|jiffies
r_int
r_int
r_volatile
id|jiffies
op_assign
l_int|0
suffix:semicolon
DECL|variable|startup_time
r_int
r_int
id|startup_time
op_assign
l_int|0
suffix:semicolon
DECL|variable|jiffies_offset
r_int
id|jiffies_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # clock ticks to add to get &quot;true&n;&t;&t;&t;&t;   time&quot;.  Should always be less than&n;&t;&t;&t;&t;   1 second&squot;s worth.  For time fanatics&n;&t;&t;&t;&t;   who like to syncronize their machines&n;&t;&t;&t;&t;   to WWV :-) */
DECL|variable|current
r_struct
id|task_struct
op_star
id|current
op_assign
op_amp
(paren
id|init_task.task
)paren
suffix:semicolon
DECL|variable|last_task_used_math
r_struct
id|task_struct
op_star
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|task
r_struct
id|task_struct
op_star
id|task
(braket
id|NR_TASKS
)braket
op_assign
(brace
op_amp
(paren
id|init_task.task
)paren
comma
)brace
suffix:semicolon
DECL|variable|user_stack
r_int
id|user_stack
(braket
id|PAGE_SIZE
op_rshift
l_int|2
)braket
suffix:semicolon
r_struct
(brace
DECL|member|a
r_int
op_star
id|a
suffix:semicolon
DECL|member|b
r_int
id|b
suffix:semicolon
DECL|variable|stack_start
)brace
id|stack_start
op_assign
(brace
op_amp
id|user_stack
(braket
id|PAGE_SIZE
op_rshift
l_int|2
)braket
comma
l_int|0x10
)brace
suffix:semicolon
multiline_comment|/*&n; *  &squot;math_state_restore()&squot; saves the current math information in the&n; * old math state array, and gets the new ones from the current task&n; */
DECL|function|math_state_restore
r_void
id|math_state_restore
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
r_return
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fwait&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;fnsave %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|last_task_used_math-&gt;tss.i387
)paren
)paren
suffix:semicolon
)brace
id|last_task_used_math
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;frstor %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|current-&gt;tss.i387
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
c_func
(paren
l_string|&quot;fninit&quot;
op_scope_resolution
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  &squot;schedule()&squot; is the scheduler function. It&squot;s a very simple and nice&n; * scheduler: it&squot;s not perfect, but certainly works for most things.&n; * The one thing you might take a look at is the signal-handler code here.&n; *&n; *   NOTE!!  Task 0 is the &squot;idle&squot; task, which gets called when no other&n; * tasks can run. It can not be killed, and it cannot sleep. The &squot;state&squot;&n; * information in task[0] is never used.&n; */
DECL|function|schedule
r_void
id|schedule
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|next
comma
id|c
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
multiline_comment|/* check alarm, wake up any interruptible tasks that have got a signal */
id|need_resched
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|timeout
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|timeout
OL
id|jiffies
)paren
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_INTERRUPTIBLE
)paren
(brace
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|timeout
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|signal
op_amp
op_complement
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|blocked
)paren
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_INTERRUPTIBLE
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
multiline_comment|/* this is the scheduler proper: */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|c
op_assign
op_minus
l_int|1
suffix:semicolon
id|next
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|NR_TASKS
suffix:semicolon
id|p
op_assign
op_amp
id|task
(braket
id|NR_TASKS
)braket
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
op_decrement
id|p
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_RUNNING
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|counter
OG
id|c
)paren
id|c
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|counter
comma
id|next
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|counter
op_assign
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|counter
op_rshift
l_int|1
)paren
op_plus
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
suffix:semicolon
)brace
id|switch_to
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
DECL|function|sys_pause
r_int
id|sys_pause
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|old_blocked
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
op_assign
id|current-&gt;sigaction
suffix:semicolon
id|old_blocked
op_assign
id|current-&gt;blocked
suffix:semicolon
r_for
c_loop
(paren
id|mask
op_assign
l_int|1
suffix:semicolon
id|mask
suffix:semicolon
id|sa
op_increment
comma
id|mask
op_add_assign
id|mask
)paren
r_if
c_cond
(paren
id|sa-&gt;sa_handler
op_eq
id|SIG_IGN
)paren
id|current-&gt;blocked
op_or_assign
id|mask
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|old_blocked
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
multiline_comment|/*&n; * wake_up doesn&squot;t wake up stopped processes - they have to be awakened&n; * with signals or similar.&n; */
DECL|function|wake_up
r_void
id|wake_up
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
(brace
r_struct
id|task_struct
op_star
id|wakeup_ptr
comma
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
op_star
id|p
)paren
(brace
id|wakeup_ptr
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|wakeup_ptr
op_logical_and
id|wakeup_ptr
op_ne
id|task
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|wakeup_ptr-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
id|printk
c_func
(paren
l_string|&quot;wake_up: TASK_ZOMBIE&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wakeup_ptr-&gt;state
op_ne
id|TASK_STOPPED
)paren
(brace
id|wakeup_ptr-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_if
c_cond
(paren
id|wakeup_ptr-&gt;counter
OG
id|current-&gt;counter
)paren
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
id|tmp
op_assign
id|wakeup_ptr-&gt;next_wait
suffix:semicolon
id|wakeup_ptr-&gt;next_wait
op_assign
id|task
(braket
l_int|0
)braket
suffix:semicolon
id|wakeup_ptr
op_assign
id|tmp
suffix:semicolon
)brace
)brace
)brace
DECL|function|__sleep_on
r_static
r_inline
r_void
id|__sleep_on
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|current
op_eq
id|task
(braket
l_int|0
)braket
)paren
id|panic
c_func
(paren
l_string|&quot;task[0] trying to sleep&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;pushfl ; popl %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
id|current-&gt;next_wait
op_assign
op_star
id|p
suffix:semicolon
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|next_wait
op_assign
l_int|NULL
suffix:semicolon
op_star
id|p
op_assign
id|current
suffix:semicolon
id|current-&gt;state
op_assign
id|state
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;next_wait
op_ne
id|task
(braket
l_int|0
)braket
)paren
id|wake_up
c_func
(paren
id|p
)paren
suffix:semicolon
id|current-&gt;next_wait
op_assign
l_int|NULL
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;pushl %0 ; popfl&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|flags
)paren
)paren
suffix:semicolon
)brace
DECL|function|interruptible_sleep_on
r_void
id|interruptible_sleep_on
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
(brace
id|__sleep_on
c_func
(paren
id|p
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
DECL|function|sleep_on
r_void
id|sleep_on
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
(brace
id|__sleep_on
c_func
(paren
id|p
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * OK, here are some floppy things that shouldn&squot;t be in the kernel&n; * proper. They are here because the floppy needs a timer, and this&n; * was the easiest way of doing it.&n; */
DECL|variable|wait_motor
r_static
r_struct
id|task_struct
op_star
id|wait_motor
(braket
l_int|4
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|mon_timer
r_static
r_int
id|mon_timer
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|moff_timer
r_static
r_int
id|moff_timer
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|current_DOR
r_int
r_char
id|current_DOR
op_assign
l_int|0x0C
suffix:semicolon
DECL|function|ticks_to_floppy_on
r_int
id|ticks_to_floppy_on
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_extern
r_int
r_char
id|selected
suffix:semicolon
r_int
r_char
id|mask
op_assign
l_int|0x10
op_lshift
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
l_int|3
)paren
id|panic
c_func
(paren
l_string|&quot;floppy_on: nr&gt;3&quot;
)paren
suffix:semicolon
id|moff_timer
(braket
id|nr
)braket
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* 100 s = very big :-) */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* use floppy_off to turn it off */
id|mask
op_or_assign
id|current_DOR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|selected
)paren
(brace
id|mask
op_and_assign
l_int|0xFC
suffix:semicolon
id|mask
op_or_assign
id|nr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
op_ne
id|current_DOR
)paren
(brace
id|outb
c_func
(paren
id|mask
comma
id|FD_DOR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mask
op_xor
id|current_DOR
)paren
op_amp
l_int|0xf0
)paren
id|mon_timer
(braket
id|nr
)braket
op_assign
id|HZ
op_div
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mon_timer
(braket
id|nr
)braket
OL
l_int|2
)paren
id|mon_timer
(braket
id|nr
)braket
op_assign
l_int|2
suffix:semicolon
id|current_DOR
op_assign
id|mask
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
id|mon_timer
(braket
id|nr
)braket
suffix:semicolon
)brace
DECL|function|floppy_off
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
id|moff_timer
(braket
id|nr
)braket
op_assign
l_int|3
op_star
id|HZ
suffix:semicolon
)brace
DECL|function|do_floppy_timer
r_void
id|do_floppy_timer
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|mask
op_assign
l_int|0x10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|mask
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
id|current_DOR
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|mon_timer
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|mon_timer
(braket
id|i
)braket
)paren
id|wake_up
c_func
(paren
id|i
op_plus
id|wait_motor
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|moff_timer
(braket
id|i
)braket
)paren
(brace
id|current_DOR
op_and_assign
op_complement
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|current_DOR
comma
id|FD_DOR
)paren
suffix:semicolon
)brace
r_else
id|moff_timer
(braket
id|i
)braket
op_decrement
suffix:semicolon
)brace
)brace
DECL|macro|TIME_REQUESTS
mdefine_line|#define TIME_REQUESTS 64
DECL|struct|timer_list
r_static
r_struct
id|timer_list
(brace
DECL|member|jiffies
r_int
id|jiffies
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
)paren
suffix:semicolon
DECL|member|next
r_struct
id|timer_list
op_star
id|next
suffix:semicolon
DECL|variable|timer_list
)brace
id|timer_list
(braket
id|TIME_REQUESTS
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|variable|next_timer
r_static
r_struct
id|timer_list
op_star
id|next_timer
op_assign
l_int|NULL
suffix:semicolon
DECL|function|add_timer
r_void
id|add_timer
c_func
(paren
r_int
id|jiffies
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
)paren
(brace
r_struct
id|timer_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
r_return
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_le
l_int|0
)paren
(paren
id|fn
)paren
(paren
)paren
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|p
op_assign
id|timer_list
suffix:semicolon
id|p
OL
id|timer_list
op_plus
id|TIME_REQUESTS
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fn
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|timer_list
op_plus
id|TIME_REQUESTS
)paren
id|panic
c_func
(paren
l_string|&quot;No more time requests free&quot;
)paren
suffix:semicolon
id|p-&gt;fn
op_assign
id|fn
suffix:semicolon
id|p-&gt;jiffies
op_assign
id|jiffies
suffix:semicolon
id|p-&gt;next
op_assign
id|next_timer
suffix:semicolon
id|next_timer
op_assign
id|p
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;next
op_logical_and
id|p-&gt;next-&gt;jiffies
OL
id|p-&gt;jiffies
)paren
(brace
id|p-&gt;jiffies
op_sub_assign
id|p-&gt;next-&gt;jiffies
suffix:semicolon
id|fn
op_assign
id|p-&gt;fn
suffix:semicolon
id|p-&gt;fn
op_assign
id|p-&gt;next-&gt;fn
suffix:semicolon
id|p-&gt;next-&gt;fn
op_assign
id|fn
suffix:semicolon
id|jiffies
op_assign
id|p-&gt;jiffies
suffix:semicolon
id|p-&gt;jiffies
op_assign
id|p-&gt;next-&gt;jiffies
suffix:semicolon
id|p-&gt;next-&gt;jiffies
op_assign
id|jiffies
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|FSHIFT
mdefine_line|#define&t;FSHIFT&t;11
DECL|macro|FSCALE
mdefine_line|#define&t;FSCALE&t;(1&lt;&lt;FSHIFT)
multiline_comment|/*&n; * Constants for averages over 1, 5, and 15 minutes&n; * when sampling at 5 second intervals.&n; */
DECL|variable|cexp
r_static
r_int
r_int
id|cexp
(braket
l_int|3
)braket
op_assign
(brace
l_int|1884
comma
multiline_comment|/* 0.9200444146293232 * FSCALE,&t; exp(-1/12) */
l_int|2014
comma
multiline_comment|/* 0.9834714538216174 * FSCALE,&t; exp(-1/60) */
l_int|2037
comma
multiline_comment|/* 0.9944598480048967 * FSCALE,&t; exp(-1/180) */
)brace
suffix:semicolon
DECL|variable|averunnable
r_int
r_int
id|averunnable
(braket
l_int|3
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* fixed point numbers */
DECL|function|update_avg
r_void
id|update_avg
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|n
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_RUNNING
op_logical_or
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_eq
id|TASK_UNINTERRUPTIBLE
)paren
)paren
op_increment
id|n
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
op_increment
id|i
)paren
id|averunnable
(braket
id|i
)braket
op_assign
(paren
id|cexp
(braket
id|i
)braket
op_star
id|averunnable
(braket
id|i
)braket
op_plus
id|n
op_star
id|FSCALE
op_star
(paren
id|FSCALE
op_minus
id|cexp
(braket
id|i
)braket
)paren
)paren
op_rshift
id|FSHIFT
suffix:semicolon
)brace
DECL|variable|timer_active
r_int
r_int
id|timer_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|timer_table
r_struct
id|timer_struct
id|timer_table
(braket
l_int|32
)braket
suffix:semicolon
DECL|function|do_timer
r_void
id|do_timer
c_func
(paren
r_int
id|cpl
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_struct
id|timer_struct
op_star
id|tp
op_assign
id|timer_table
op_plus
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|task_p
suffix:semicolon
r_static
r_int
id|avg_cnt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|mask
op_assign
l_int|1
suffix:semicolon
id|mask
suffix:semicolon
id|tp
op_increment
comma
id|mask
op_add_assign
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
OG
id|timer_active
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
id|timer_active
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;expires
OG
id|jiffies
)paren
r_continue
suffix:semicolon
id|timer_active
op_and_assign
op_complement
id|mask
suffix:semicolon
id|tp
op_member_access_from_pointer
id|fn
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Update ITIMER_REAL for every task */
r_for
c_loop
(paren
id|task_p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|task_p
op_ge
op_amp
id|FIRST_TASK
suffix:semicolon
id|task_p
op_decrement
)paren
r_if
c_cond
(paren
op_star
id|task_p
op_logical_and
(paren
op_star
id|task_p
)paren
op_member_access_from_pointer
id|it_real_value
op_logical_and
op_logical_neg
(paren
op_decrement
(paren
op_star
id|task_p
)paren
op_member_access_from_pointer
id|it_real_value
)paren
)paren
(brace
(paren
op_star
id|task_p
)paren
op_member_access_from_pointer
id|signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SIGALRM
op_minus
l_int|1
)paren
)paren
suffix:semicolon
(paren
op_star
id|task_p
)paren
op_member_access_from_pointer
id|it_real_value
op_assign
(paren
op_star
id|task_p
)paren
op_member_access_from_pointer
id|it_real_incr
suffix:semicolon
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Update ITIMER_PROF for the current task */
r_if
c_cond
(paren
id|current-&gt;it_prof_value
op_logical_and
op_logical_neg
(paren
op_decrement
id|current-&gt;it_prof_value
)paren
)paren
(brace
id|current-&gt;it_prof_value
op_assign
id|current-&gt;it_prof_incr
suffix:semicolon
id|current-&gt;signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SIGPROF
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Update ITIMER_VIRT for current task if not in a system call */
r_if
c_cond
(paren
id|cpl
op_logical_and
id|current-&gt;it_virt_value
op_logical_and
op_logical_neg
(paren
op_decrement
id|current-&gt;it_virt_value
)paren
)paren
(brace
id|current-&gt;it_virt_value
op_assign
id|current-&gt;it_virt_incr
suffix:semicolon
id|current-&gt;signal
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SIGVTALRM
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpl
)paren
id|current-&gt;utime
op_increment
suffix:semicolon
r_else
id|current-&gt;stime
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|next_timer
)paren
(brace
id|next_timer-&gt;jiffies
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|next_timer
op_logical_and
id|next_timer-&gt;jiffies
op_le
l_int|0
)paren
(brace
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
suffix:semicolon
id|fn
op_assign
id|next_timer-&gt;fn
suffix:semicolon
id|next_timer-&gt;fn
op_assign
l_int|NULL
suffix:semicolon
id|next_timer
op_assign
id|next_timer-&gt;next
suffix:semicolon
(paren
id|fn
)paren
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|current_DOR
op_amp
l_int|0xf0
)paren
id|do_floppy_timer
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|avg_cnt
OL
l_int|0
)paren
(brace
id|avg_cnt
op_assign
l_int|500
suffix:semicolon
id|update_avg
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_decrement
id|current-&gt;counter
)paren
op_le
l_int|0
)paren
(brace
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|sys_alarm
r_int
id|sys_alarm
c_func
(paren
r_int
id|seconds
)paren
(brace
r_extern
r_int
id|_setitimer
c_func
(paren
r_int
comma
r_struct
id|itimerval
op_star
comma
r_struct
id|itimerval
op_star
)paren
suffix:semicolon
r_struct
id|itimerval
r_new
comma
id|old
suffix:semicolon
r_new
dot
id|it_interval.tv_sec
op_assign
r_new
dot
id|it_interval.tv_usec
op_assign
l_int|0
suffix:semicolon
r_new
dot
id|it_value.tv_sec
op_assign
id|seconds
suffix:semicolon
r_new
dot
id|it_value.tv_usec
op_assign
l_int|0
suffix:semicolon
id|_setitimer
c_func
(paren
id|ITIMER_REAL
comma
op_amp
r_new
comma
op_amp
id|old
)paren
suffix:semicolon
r_return
id|old.it_value.tv_sec
op_plus
(paren
id|old.it_value.tv_usec
op_div
l_int|1000000
)paren
suffix:semicolon
)brace
DECL|function|sys_getpid
r_int
id|sys_getpid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_getppid
r_int
id|sys_getppid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;p_pptr-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_getuid
r_int
id|sys_getuid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;uid
suffix:semicolon
)brace
DECL|function|sys_geteuid
r_int
id|sys_geteuid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;euid
suffix:semicolon
)brace
DECL|function|sys_getgid
r_int
id|sys_getgid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;gid
suffix:semicolon
)brace
DECL|function|sys_getegid
r_int
id|sys_getegid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;egid
suffix:semicolon
)brace
DECL|function|sys_nice
r_int
id|sys_nice
c_func
(paren
r_int
id|increment
)paren
(brace
r_if
c_cond
(paren
id|increment
OL
l_int|0
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|increment
op_ge
id|current-&gt;priority
)paren
id|increment
op_assign
id|current-&gt;priority
op_minus
l_int|1
suffix:semicolon
id|current-&gt;priority
op_sub_assign
id|increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sched_init
r_void
id|sched_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|desc_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|sigaction
)paren
op_ne
l_int|16
)paren
id|panic
c_func
(paren
l_string|&quot;Struct sigaction MUST be 16 bytes&quot;
)paren
suffix:semicolon
id|set_tss_desc
c_func
(paren
id|gdt
op_plus
id|FIRST_TSS_ENTRY
comma
op_amp
(paren
id|init_task.task.tss
)paren
)paren
suffix:semicolon
id|set_ldt_desc
c_func
(paren
id|gdt
op_plus
id|FIRST_LDT_ENTRY
comma
op_amp
(paren
id|init_task.task.ldt
)paren
)paren
suffix:semicolon
id|p
op_assign
id|gdt
op_plus
l_int|2
op_plus
id|FIRST_TSS_ENTRY
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|task
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;a
op_assign
id|p-&gt;b
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|p-&gt;a
op_assign
id|p-&gt;b
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* Clear NT, so that we won&squot;t have troubles with that later on */
id|__asm__
c_func
(paren
l_string|&quot;pushfl ; andl $0xffffbfff,(%esp) ; popfl&quot;
)paren
suffix:semicolon
id|ltr
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|lldt
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x36
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 3, LSB/MSB, ch 0 */
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|set_intr_gate
c_func
(paren
l_int|0x20
comma
op_amp
id|timer_interrupt
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_amp
op_complement
l_int|0x01
comma
l_int|0x21
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|0x80
comma
op_amp
id|system_call
)paren
suffix:semicolon
)brace
eof
