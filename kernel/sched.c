multiline_comment|/*&n; * &squot;sched.c&squot; is the main kernel file. It contains scheduling primitives&n; * (sleep_on, wakeup, schedule etc) as well as a number of simple system&n; * call functions (type getpid(), which just extracts a field from&n; * current-task&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
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
r_volatile
id|jiffies
op_assign
l_int|0
suffix:semicolon
DECL|variable|startup_time
r_int
id|startup_time
op_assign
l_int|0
suffix:semicolon
DECL|variable|current
DECL|variable|last_task_used_math
r_struct
id|task_struct
op_star
id|current
op_assign
op_amp
(paren
id|init_task.task
)paren
comma
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
)paren
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
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
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
id|last_task_used_math
op_assign
id|current
suffix:semicolon
)brace
multiline_comment|/*&n; *  &squot;schedule()&squot; is the scheduler function. This is GOOD CODE! There&n; * probably won&squot;t be any reason to change this, as it should work well&n; * in all circumstances (ie gives IO-bound processes good response etc).&n; * The one thing you might take a look at is the signal-handler code here.&n; *&n; *   NOTE!!  Task 0 is the &squot;idle&squot; task, which gets called when no other&n; * tasks can run. It can not be killed, and it cannot sleep. The &squot;state&squot;&n; * information in task[0] is never used.&n; */
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
id|alarm
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|alarm
OL
id|jiffies
)paren
(brace
(paren
op_star
id|p
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
id|p
)paren
op_member_access_from_pointer
id|alarm
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|signal
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
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
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
r_struct
id|task_struct
op_star
id|tmp
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
op_amp
(paren
id|init_task.task
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;task[0] trying to sleep&quot;
)paren
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|current
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|tmp-&gt;state
op_assign
l_int|0
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
r_struct
id|task_struct
op_star
id|tmp
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
op_amp
(paren
id|init_task.task
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;task[0] trying to sleep&quot;
)paren
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|current
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_logical_and
op_star
id|p
op_ne
id|current
)paren
(brace
op_star
id|p.state
op_assign
l_int|0
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|tmp-&gt;state
op_assign
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|p
op_logical_and
op_star
id|p
)paren
(brace
op_star
id|p.state
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|do_timer
r_void
id|do_timer
c_func
(paren
r_int
id|cpl
)paren
(brace
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
(paren
op_decrement
id|current-&gt;counter
)paren
OG
l_int|0
)paren
r_return
suffix:semicolon
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpl
)paren
r_return
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
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
id|current-&gt;alarm
op_assign
(paren
id|seconds
OG
l_int|0
)paren
ques
c_cond
(paren
id|jiffies
op_plus
id|HZ
op_star
id|seconds
)paren
suffix:colon
l_int|0
suffix:semicolon
r_return
id|seconds
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
id|current-&gt;father
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
id|current-&gt;priority
op_minus
id|increment
OG
l_int|0
)paren
id|current-&gt;priority
op_sub_assign
id|increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_signal
r_int
id|sys_signal
c_func
(paren
r_int
id|signal
comma
r_int
id|addr
comma
r_int
id|restorer
)paren
(brace
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|signal
)paren
(brace
r_case
id|SIGHUP
suffix:colon
r_case
id|SIGINT
suffix:colon
r_case
id|SIGQUIT
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGTRAP
suffix:colon
r_case
id|SIGABRT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGUSR1
suffix:colon
r_case
id|SIGSEGV
suffix:colon
r_case
id|SIGUSR2
suffix:colon
r_case
id|SIGPIPE
suffix:colon
r_case
id|SIGALRM
suffix:colon
r_case
id|SIGCHLD
suffix:colon
id|i
op_assign
(paren
r_int
)paren
id|current-&gt;sig_fn
(braket
id|signal
op_minus
l_int|1
)braket
suffix:semicolon
id|current-&gt;sig_fn
(braket
id|signal
op_minus
l_int|1
)braket
op_assign
(paren
id|fn_ptr
)paren
id|addr
suffix:semicolon
id|current-&gt;sig_restorer
op_assign
(paren
id|fn_ptr
)paren
id|restorer
suffix:semicolon
r_return
id|i
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
