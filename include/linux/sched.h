macro_line|#ifndef _LINUX_SCHED_H
DECL|macro|_LINUX_SCHED_H
mdefine_line|#define _LINUX_SCHED_H
multiline_comment|/*&n; * define DEBUG if you want the wait-queues to have some extra&n; * debugging code. It&squot;s not normally used, but might catch some&n; * wait-queue coding errors.&n; *&n; *  #define DEBUG&n; */
macro_line|#include &lt;asm/param.h&gt;&t;/* for HZ */
r_extern
r_int
r_int
id|intr_count
suffix:semicolon
r_extern
r_int
r_int
id|event
suffix:semicolon
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * These are the constant used to fake the fixed-point load-average&n; * counting. Some notes:&n; *  - 11 bit fractions expand to 22 bits by the multiplies: this gives&n; *    a load-average precision of 10 bits integer + 11 bits fractional&n; *  - if you want to count load-averages more often, you need more&n; *    precision, or rounding will get you. With 2-second counting freq,&n; *    the EXP_n values would be 1981, 2034 and 2043 if still using only&n; *    11 bit fractions.&n; */
r_extern
r_int
r_int
id|avenrun
(braket
)braket
suffix:semicolon
multiline_comment|/* Load averages */
DECL|macro|FSHIFT
mdefine_line|#define FSHIFT&t;&t;11&t;&t;/* nr of bits of precision */
DECL|macro|FIXED_1
mdefine_line|#define FIXED_1&t;&t;(1&lt;&lt;FSHIFT)&t;/* 1.0 as fixed-point */
DECL|macro|LOAD_FREQ
mdefine_line|#define LOAD_FREQ&t;(5*HZ)&t;&t;/* 5 sec intervals */
DECL|macro|EXP_1
mdefine_line|#define EXP_1&t;&t;1884&t;&t;/* 1/exp(5sec/1min) as fixed-point */
DECL|macro|EXP_5
mdefine_line|#define EXP_5&t;&t;2014&t;&t;/* 1/exp(5sec/5min) */
DECL|macro|EXP_15
mdefine_line|#define EXP_15&t;&t;2037&t;&t;/* 1/exp(5sec/15min) */
DECL|macro|CALC_LOAD
mdefine_line|#define CALC_LOAD(load,exp,n) &bslash;&n;&t;load *= exp; &bslash;&n;&t;load += n*(FIXED_1-exp); &bslash;&n;&t;load &gt;&gt;= FSHIFT;
DECL|macro|CT_TO_SECS
mdefine_line|#define CT_TO_SECS(x)&t;((x) / HZ)
DECL|macro|CT_TO_USECS
mdefine_line|#define CT_TO_USECS(x)&t;(((x) % HZ) * 1000000/HZ)
DECL|macro|FIRST_TASK
mdefine_line|#define FIRST_TASK task[0]
DECL|macro|LAST_TASK
mdefine_line|#define LAST_TASK task[NR_TASKS-1]
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/resource.h&gt;
macro_line|#include &lt;linux/vm86.h&gt;
macro_line|#include &lt;linux/math_emu.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|TASK_RUNNING
mdefine_line|#define TASK_RUNNING&t;&t;0
DECL|macro|TASK_INTERRUPTIBLE
mdefine_line|#define TASK_INTERRUPTIBLE&t;1
DECL|macro|TASK_UNINTERRUPTIBLE
mdefine_line|#define TASK_UNINTERRUPTIBLE&t;2
DECL|macro|TASK_ZOMBIE
mdefine_line|#define TASK_ZOMBIE&t;&t;3
DECL|macro|TASK_STOPPED
mdefine_line|#define TASK_STOPPED&t;&t;4
DECL|macro|TASK_SWAPPING
mdefine_line|#define TASK_SWAPPING&t;&t;5
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|sched_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|show_state
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|schedule
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|struct|files_struct
r_struct
id|files_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|close_on_exec
id|fd_set
id|close_on_exec
suffix:semicolon
DECL|member|fd
r_struct
id|file
op_star
id|fd
(braket
id|NR_OPEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FILES
mdefine_line|#define INIT_FILES { &bslash;&n;&t;0, &bslash;&n;&t;{ { 0, } }, &bslash;&n;&t;{ NULL, } &bslash;&n;}
DECL|struct|fs_struct
r_struct
id|fs_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|umask
r_int
r_int
id|umask
suffix:semicolon
DECL|member|root
DECL|member|pwd
r_struct
id|inode
op_star
id|root
comma
op_star
id|pwd
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FS
mdefine_line|#define INIT_FS { &bslash;&n;&t;0, &bslash;&n;&t;0022, &bslash;&n;&t;NULL, NULL &bslash;&n;}
DECL|struct|mm_struct
r_struct
id|mm_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|start_code
DECL|member|end_code
DECL|member|end_data
r_int
r_int
id|start_code
comma
id|end_code
comma
id|end_data
suffix:semicolon
DECL|member|start_brk
DECL|member|brk
DECL|member|start_stack
DECL|member|start_mmap
r_int
r_int
id|start_brk
comma
id|brk
comma
id|start_stack
comma
id|start_mmap
suffix:semicolon
DECL|member|arg_start
DECL|member|arg_end
DECL|member|env_start
DECL|member|env_end
r_int
r_int
id|arg_start
comma
id|arg_end
comma
id|env_start
comma
id|env_end
suffix:semicolon
DECL|member|rss
r_int
r_int
id|rss
suffix:semicolon
DECL|member|min_flt
DECL|member|maj_flt
DECL|member|cmin_flt
DECL|member|cmaj_flt
r_int
r_int
id|min_flt
comma
id|maj_flt
comma
id|cmin_flt
comma
id|cmaj_flt
suffix:semicolon
DECL|member|swappable
r_int
id|swappable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|swap_address
r_int
r_int
id|swap_address
suffix:semicolon
DECL|member|old_maj_flt
r_int
r_int
id|old_maj_flt
suffix:semicolon
multiline_comment|/* old value of maj_flt */
DECL|member|dec_flt
r_int
r_int
id|dec_flt
suffix:semicolon
multiline_comment|/* page fault count of the last time */
DECL|member|swap_cnt
r_int
r_int
id|swap_cnt
suffix:semicolon
multiline_comment|/* number of pages to swap on next pass */
DECL|member|mmap
r_struct
id|vm_area_struct
op_star
id|mmap
suffix:semicolon
DECL|member|mmap_avl
r_struct
id|vm_area_struct
op_star
id|mmap_avl
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_task, 0, 0x40000000, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_MM
mdefine_line|#define INIT_MM { &bslash;&n;&t;&t;0, &bslash;&n;&t;&t;0, 0, 0, &bslash;&n;&t;&t;0, 0, 0, 0, &bslash;&n;&t;&t;0, 0, 0, 0, &bslash;&n;&t;&t;0, &bslash;&n;/* ?_flt */&t;0, 0, 0, 0, &bslash;&n;&t;&t;0, &bslash;&n;/* swap */&t;0, 0, 0, 0, &bslash;&n;&t;&t;&amp;init_mmap, &amp;init_mmap }
DECL|struct|task_struct
r_struct
id|task_struct
(brace
multiline_comment|/* these are hardcoded - don&squot;t touch */
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
multiline_comment|/* -1 unrunnable, 0 runnable, &gt;0 stopped */
DECL|member|counter
r_int
id|counter
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
DECL|member|blocked
r_int
r_int
id|blocked
suffix:semicolon
multiline_comment|/* bitmap of masked signals */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* per process flags, defined below */
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|member|debugreg
r_int
id|debugreg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Hardware debugging registers */
DECL|member|exec_domain
r_struct
id|exec_domain
op_star
id|exec_domain
suffix:semicolon
multiline_comment|/* various fields */
DECL|member|binfmt
r_struct
id|linux_binfmt
op_star
id|binfmt
suffix:semicolon
DECL|member|next_task
DECL|member|prev_task
r_struct
id|task_struct
op_star
id|next_task
comma
op_star
id|prev_task
suffix:semicolon
DECL|member|sigaction
r_struct
id|sigaction
id|sigaction
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|saved_kernel_stack
r_int
r_int
id|saved_kernel_stack
suffix:semicolon
DECL|member|kernel_stack_page
r_int
r_int
id|kernel_stack_page
suffix:semicolon
DECL|member|exit_code
DECL|member|exit_signal
r_int
id|exit_code
comma
id|exit_signal
suffix:semicolon
DECL|member|personality
r_int
r_int
id|personality
suffix:semicolon
DECL|member|dumpable
r_int
id|dumpable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|did_exec
r_int
id|did_exec
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pid
DECL|member|pgrp
DECL|member|tty_old_pgrp
DECL|member|session
DECL|member|leader
r_int
id|pid
comma
id|pgrp
comma
id|tty_old_pgrp
comma
id|session
comma
id|leader
suffix:semicolon
DECL|member|groups
r_int
id|groups
(braket
id|NGROUPS
)braket
suffix:semicolon
multiline_comment|/* &n;&t; * pointers to (original) parent process, youngest child, younger sibling,&n;&t; * older sibling, respectively.  (p-&gt;father can be replaced with &n;&t; * p-&gt;p_pptr-&gt;pid)&n;&t; */
DECL|member|p_opptr
DECL|member|p_pptr
DECL|member|p_cptr
DECL|member|p_ysptr
DECL|member|p_osptr
r_struct
id|task_struct
op_star
id|p_opptr
comma
op_star
id|p_pptr
comma
op_star
id|p_cptr
comma
op_star
id|p_ysptr
comma
op_star
id|p_osptr
suffix:semicolon
DECL|member|wait_chldexit
r_struct
id|wait_queue
op_star
id|wait_chldexit
suffix:semicolon
multiline_comment|/* for wait4() */
DECL|member|uid
DECL|member|euid
DECL|member|suid
DECL|member|fsuid
r_int
r_int
id|uid
comma
id|euid
comma
id|suid
comma
id|fsuid
suffix:semicolon
DECL|member|gid
DECL|member|egid
DECL|member|sgid
DECL|member|fsgid
r_int
r_int
id|gid
comma
id|egid
comma
id|sgid
comma
id|fsgid
suffix:semicolon
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
DECL|member|it_real_value
DECL|member|it_prof_value
DECL|member|it_virt_value
r_int
r_int
id|it_real_value
comma
id|it_prof_value
comma
id|it_virt_value
suffix:semicolon
DECL|member|it_real_incr
DECL|member|it_prof_incr
DECL|member|it_virt_incr
r_int
r_int
id|it_real_incr
comma
id|it_prof_incr
comma
id|it_virt_incr
suffix:semicolon
DECL|member|utime
DECL|member|stime
DECL|member|cutime
DECL|member|cstime
DECL|member|start_time
r_int
id|utime
comma
id|stime
comma
id|cutime
comma
id|cstime
comma
id|start_time
suffix:semicolon
DECL|member|rlim
r_struct
id|rlimit
id|rlim
(braket
id|RLIM_NLIMITS
)braket
suffix:semicolon
DECL|member|used_math
r_int
r_int
id|used_math
suffix:semicolon
DECL|member|comm
r_char
id|comm
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* file system info */
DECL|member|link_count
r_int
id|link_count
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* NULL if no tty */
multiline_comment|/* ipc stuff */
DECL|member|semundo
r_struct
id|sem_undo
op_star
id|semundo
suffix:semicolon
DECL|member|semsleeping
r_struct
id|sem_queue
op_star
id|semsleeping
suffix:semicolon
multiline_comment|/* ldt for this task - used by Wine.  If NULL, default_ldt is used */
DECL|member|ldt
r_struct
id|desc_struct
op_star
id|ldt
suffix:semicolon
multiline_comment|/* tss for this task */
DECL|member|tss
r_struct
id|thread_struct
id|tss
suffix:semicolon
multiline_comment|/* filesystem information */
DECL|member|fs
r_struct
id|fs_struct
id|fs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* open file information */
DECL|member|files
r_struct
id|files_struct
id|files
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* memory management info */
DECL|member|mm
r_struct
id|mm_struct
id|mm
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Per process flags&n; */
DECL|macro|PF_ALIGNWARN
mdefine_line|#define PF_ALIGNWARN&t;0x00000001&t;/* Print alignment warning msgs */
multiline_comment|/* Not implemented yet, only for 486*/
DECL|macro|PF_PTRACED
mdefine_line|#define PF_PTRACED&t;0x00000010&t;/* set if ptrace (0) has been called. */
DECL|macro|PF_TRACESYS
mdefine_line|#define PF_TRACESYS&t;0x00000020&t;/* tracing system calls */
multiline_comment|/*&n; * cloning flags:&n; */
DECL|macro|CSIGNAL
mdefine_line|#define CSIGNAL&t;&t;0x000000ff&t;/* signal mask to be sent at exit */
DECL|macro|COPYVM
mdefine_line|#define COPYVM&t;&t;0x00000100&t;/* set if VM copy desired (like normal fork()) */
DECL|macro|COPYFD
mdefine_line|#define COPYFD&t;&t;0x00000200&t;/* set if fd&squot;s should be copied, not shared (NI) */
multiline_comment|/*&n; *  INIT_TASK is used to set up the first task table, touch at&n; * your own risk!. Base=0, limit=0x1fffff (=2MB)&n; */
DECL|macro|INIT_TASK
mdefine_line|#define INIT_TASK &bslash;&n;/* state etc */&t;{ 0,15,15,0,0,0,0, &bslash;&n;/* debugregs */ { 0, },            &bslash;&n;/* exec domain */&amp;default_exec_domain, &bslash;&n;/* binfmt */&t;NULL, &bslash;&n;/* schedlink */&t;&amp;init_task,&amp;init_task, &bslash;&n;/* signals */&t;{{ 0, },}, &bslash;&n;/* stack */&t;0,(unsigned long) &amp;init_kernel_stack, &bslash;&n;/* ec,brk... */&t;0,0,0,0,0, &bslash;&n;/* pid etc.. */&t;0,0,0,0,0, &bslash;&n;/* suppl grps*/ {NOGROUP,}, &bslash;&n;/* proc links*/ &amp;init_task,&amp;init_task,NULL,NULL,NULL,NULL, &bslash;&n;/* uid etc */&t;0,0,0,0,0,0,0,0, &bslash;&n;/* timeout */&t;0,0,0,0,0,0,0,0,0,0,0,0, &bslash;&n;/* rlimits */   { {LONG_MAX, LONG_MAX}, {LONG_MAX, LONG_MAX},  &bslash;&n;&t;&t;  {LONG_MAX, LONG_MAX}, {LONG_MAX, LONG_MAX},  &bslash;&n;&t;&t;  {       0, LONG_MAX}, {LONG_MAX, LONG_MAX}, &bslash;&n;&t;&t;  {MAX_TASKS_PER_USER, MAX_TASKS_PER_USER}, {NR_OPEN, NR_OPEN}}, &bslash;&n;/* math */&t;0, &bslash;&n;/* comm */&t;&quot;swapper&quot;, &bslash;&n;/* fs info */&t;0,NULL, &bslash;&n;/* ipc */&t;NULL, NULL, &bslash;&n;/* ldt */&t;NULL, &bslash;&n;/* tss */&t;INIT_TSS, &bslash;&n;/* fs */&t;{ INIT_FS }, &bslash;&n;/* files */&t;{ INIT_FILES }, &bslash;&n;/* mm */&t;{ INIT_MM } &bslash;&n;}
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|task_struct
id|init_task
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|task
(braket
id|NR_TASKS
)braket
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
r_extern
r_int
r_int
r_volatile
id|jiffies
suffix:semicolon
r_extern
r_int
r_int
id|itimer_ticks
suffix:semicolon
r_extern
r_int
r_int
id|itimer_next
suffix:semicolon
r_extern
r_struct
id|timeval
id|xtime
suffix:semicolon
r_extern
r_int
id|need_resched
suffix:semicolon
DECL|macro|CURRENT_TIME
mdefine_line|#define CURRENT_TIME (xtime.tv_sec)
r_extern
r_void
id|sleep_on
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|interruptible_sleep_on
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|wake_up
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|wake_up_interruptible
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|notify_parent
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|send_sig
c_func
(paren
r_int
r_int
id|sig
comma
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|in_group_p
c_func
(paren
id|gid_t
id|grp
)paren
suffix:semicolon
r_extern
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|device
)paren
suffix:semicolon
r_extern
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
r_int
id|copy_thread
c_func
(paren
r_int
comma
r_int
r_int
comma
r_struct
id|task_struct
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_thread
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|exit_thread
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|do_execve
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
r_char
op_star
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
id|asmlinkage
r_int
id|do_signal
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * The wait-queues are circular lists, and you have to be *very* sure&n; * to keep them correct. Use only these two functions to add/remove&n; * entries in the queues.&n; */
DECL|function|add_wait_queue
r_extern
r_inline
r_void
id|add_wait_queue
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
comma
r_struct
id|wait_queue
op_star
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|wait-&gt;next
)paren
(brace
r_int
r_int
id|pc
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call 1f&bslash;n&quot;
l_string|&quot;1:&bslash;tpopl %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pc
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;add_wait_queue (%08x): wait-&gt;next = %08x&bslash;n&quot;
comma
id|pc
comma
(paren
r_int
r_int
)paren
id|wait-&gt;next
)paren
suffix:semicolon
)brace
macro_line|#endif
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
op_logical_neg
op_star
id|p
)paren
(brace
id|wait-&gt;next
op_assign
id|wait
suffix:semicolon
op_star
id|p
op_assign
id|wait
suffix:semicolon
)brace
r_else
(brace
id|wait-&gt;next
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
op_assign
id|wait
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|remove_wait_queue
r_extern
r_inline
r_void
id|remove_wait_queue
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|p
comma
r_struct
id|wait_queue
op_star
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|wait_queue
op_star
id|tmp
suffix:semicolon
macro_line|#ifdef DEBUG
r_int
r_int
id|ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
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
(paren
op_star
id|p
op_eq
id|wait
)paren
op_logical_and
macro_line|#ifdef DEBUG
(paren
id|ok
op_assign
l_int|1
)paren
op_logical_and
macro_line|#endif
(paren
(paren
op_star
id|p
op_assign
id|wait-&gt;next
)paren
op_eq
id|wait
)paren
)paren
(brace
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
id|wait
suffix:semicolon
r_while
c_loop
(paren
id|tmp-&gt;next
op_ne
id|wait
)paren
(brace
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|tmp
op_eq
op_star
id|p
)paren
id|ok
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
)brace
id|tmp-&gt;next
op_assign
id|wait-&gt;next
suffix:semicolon
)brace
id|wait-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;removed wait_queue not on list.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;list = %08x, queue = %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|p
comma
(paren
r_int
r_int
)paren
id|wait
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;call 1f&bslash;n1:&bslash;tpopl %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ok
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;eip = %08x&bslash;n&quot;
comma
id|ok
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|select_wait
r_extern
r_inline
r_void
id|select_wait
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|wait_address
comma
id|select_table
op_star
id|p
)paren
(brace
r_struct
id|select_table_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|wait_address
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;nr
op_ge
id|__MAX_SELECT_TABLE_ENTRIES
)paren
r_return
suffix:semicolon
id|entry
op_assign
id|p-&gt;entry
op_plus
id|p-&gt;nr
suffix:semicolon
id|entry-&gt;wait_address
op_assign
id|wait_address
suffix:semicolon
id|entry-&gt;wait.task
op_assign
id|current
suffix:semicolon
id|entry-&gt;wait.next
op_assign
l_int|NULL
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|wait_address
comma
op_amp
id|entry-&gt;wait
)paren
suffix:semicolon
id|p-&gt;nr
op_increment
suffix:semicolon
)brace
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
multiline_comment|/*&n; * These are not yet interrupt-safe&n; */
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
id|sem-&gt;count
op_le
l_int|0
)paren
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
id|sem-&gt;count
op_decrement
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
id|sem-&gt;count
op_increment
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|macro|REMOVE_LINKS
mdefine_line|#define REMOVE_LINKS(p) do { unsigned long flags; &bslash;&n;&t;save_flags(flags) ; cli(); &bslash;&n;&t;(p)-&gt;next_task-&gt;prev_task = (p)-&gt;prev_task; &bslash;&n;&t;(p)-&gt;prev_task-&gt;next_task = (p)-&gt;next_task; &bslash;&n;&t;restore_flags(flags); &bslash;&n;&t;if ((p)-&gt;p_osptr) &bslash;&n;&t;&t;(p)-&gt;p_osptr-&gt;p_ysptr = (p)-&gt;p_ysptr; &bslash;&n;&t;if ((p)-&gt;p_ysptr) &bslash;&n;&t;&t;(p)-&gt;p_ysptr-&gt;p_osptr = (p)-&gt;p_osptr; &bslash;&n;&t;else &bslash;&n;&t;&t;(p)-&gt;p_pptr-&gt;p_cptr = (p)-&gt;p_osptr; &bslash;&n;&t;} while (0)
DECL|macro|SET_LINKS
mdefine_line|#define SET_LINKS(p) do { unsigned long flags; &bslash;&n;&t;save_flags(flags); cli(); &bslash;&n;&t;(p)-&gt;next_task = &amp;init_task; &bslash;&n;&t;(p)-&gt;prev_task = init_task.prev_task; &bslash;&n;&t;init_task.prev_task-&gt;next_task = (p); &bslash;&n;&t;init_task.prev_task = (p); &bslash;&n;&t;restore_flags(flags); &bslash;&n;&t;(p)-&gt;p_ysptr = NULL; &bslash;&n;&t;if (((p)-&gt;p_osptr = (p)-&gt;p_pptr-&gt;p_cptr) != NULL) &bslash;&n;&t;&t;(p)-&gt;p_osptr-&gt;p_ysptr = p; &bslash;&n;&t;(p)-&gt;p_pptr-&gt;p_cptr = p; &bslash;&n;&t;} while (0)
DECL|macro|for_each_task
mdefine_line|#define for_each_task(p) &bslash;&n;&t;for (p = &amp;init_task ; (p = p-&gt;next_task) != &amp;init_task ; )
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
