macro_line|#ifndef _LINUX_SCHED_H
DECL|macro|_LINUX_SCHED_H
mdefine_line|#define _LINUX_SCHED_H
macro_line|#include &lt;asm/param.h&gt;&t;/* for HZ */
r_extern
r_int
r_int
id|event
suffix:semicolon
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
multiline_comment|/*&n; * cloning flags:&n; */
DECL|macro|CSIGNAL
mdefine_line|#define CSIGNAL&t;&t;0x000000ff&t;/* signal mask to be sent at exit */
DECL|macro|CLONE_VM
mdefine_line|#define CLONE_VM&t;0x00000100&t;/* set if VM shared between processes */
DECL|macro|CLONE_FS
mdefine_line|#define CLONE_FS&t;0x00000200&t;/* set if fs info shared between processes */
DECL|macro|CLONE_FILES
mdefine_line|#define CLONE_FILES&t;0x00000400&t;/* set if open files shared between processes */
DECL|macro|CLONE_SIGHAND
mdefine_line|#define CLONE_SIGHAND&t;0x00000800&t;/* set if signal handlers shared */
DECL|macro|CLONE_PID
mdefine_line|#define CLONE_PID&t;0x00001000&t;/* set if pid shared */
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
r_extern
r_int
id|nr_running
comma
id|nr_tasks
suffix:semicolon
r_extern
r_int
id|last_pid
suffix:semicolon
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/resource.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
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
multiline_comment|/*&n; * Scheduling policies&n; */
DECL|macro|SCHED_OTHER
mdefine_line|#define SCHED_OTHER&t;&t;0
DECL|macro|SCHED_FIFO
mdefine_line|#define SCHED_FIFO&t;&t;1
DECL|macro|SCHED_RR
mdefine_line|#define SCHED_RR&t;&t;2
DECL|struct|sched_param
r_struct
id|sched_param
(brace
DECL|member|sched_priority
r_int
id|sched_priority
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/spinlock.h&gt;
multiline_comment|/*&n; * This serializes &quot;schedule()&quot; and also protects&n; * the run-queue from deletions/modifications (but&n; * _adding_ to the beginning of the run-queue has&n; * a separate lock).&n; */
r_extern
id|rwlock_t
id|tasklist_lock
suffix:semicolon
r_extern
id|spinlock_t
id|scheduler_lock
suffix:semicolon
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
multiline_comment|/* Open file table structure */
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
DECL|member|open_fds
id|fd_set
id|open_fds
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
mdefine_line|#define INIT_FILES { &bslash;&n;&t;1, &bslash;&n;&t;{ { 0, } }, &bslash;&n;&t;{ { 0, } }, &bslash;&n;&t;{ NULL, } &bslash;&n;}
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
mdefine_line|#define INIT_FS { &bslash;&n;&t;1, &bslash;&n;&t;0022, &bslash;&n;&t;NULL, NULL &bslash;&n;}
DECL|struct|mm_struct
r_struct
id|mm_struct
(brace
DECL|member|mmap
DECL|member|mmap_cache
r_struct
id|vm_area_struct
op_star
id|mmap
comma
op_star
id|mmap_cache
suffix:semicolon
DECL|member|pgd
id|pgd_t
op_star
id|pgd
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|mmap_sem
r_struct
id|semaphore
id|mmap_sem
suffix:semicolon
DECL|member|context
r_int
r_int
id|context
suffix:semicolon
DECL|member|start_code
DECL|member|end_code
DECL|member|start_data
DECL|member|end_data
r_int
r_int
id|start_code
comma
id|end_code
comma
id|start_data
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
DECL|member|total_vm
DECL|member|locked_vm
r_int
r_int
id|rss
comma
id|total_vm
comma
id|locked_vm
suffix:semicolon
DECL|member|def_flags
r_int
r_int
id|def_flags
suffix:semicolon
DECL|member|cpu_vm_mask
r_int
r_int
id|cpu_vm_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MM
mdefine_line|#define INIT_MM {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&amp;init_mmap, NULL, swapper_pg_dir, 1,&t;&bslash;&n;&t;&t;MUTEX,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;0, 0, 0, 0,&t;&t;&t;&t;&bslash;&n;&t;&t;0, 0, 0, 0,&t;&t;&t;&t;&bslash;&n;&t;&t;0, 0, 0, 0,&t;&t;&t;&t;&bslash;&n;&t;&t;0, 0, 0,&t;&t;&t;&t;&bslash;&n;&t;&t;0, 0 }
DECL|struct|signal_struct
r_struct
id|signal_struct
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|action
r_struct
id|sigaction
id|action
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|siglock
id|spinlock_t
id|siglock
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_SIGNALS
mdefine_line|#define INIT_SIGNALS { &bslash;&n;&t;&t;ATOMIC_INIT(1), &bslash;&n;&t;&t;{ {0,}, }, &bslash;&n;&t;&t;SPIN_LOCK_UNLOCKED }
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
DECL|member|next_run
DECL|member|prev_run
r_struct
id|task_struct
op_star
id|next_run
comma
op_star
id|prev_run
suffix:semicolon
DECL|member|exit_code
DECL|member|exit_signal
r_int
id|exit_code
comma
id|exit_signal
suffix:semicolon
multiline_comment|/* ??? */
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
multiline_comment|/* shouldn&squot;t this be pid_t? */
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|tty_old_pgrp
r_int
id|tty_old_pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* boolean value for session group leader */
DECL|member|leader
r_int
id|leader
suffix:semicolon
DECL|member|ngroups
r_int
id|ngroups
suffix:semicolon
DECL|member|groups
id|gid_t
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
multiline_comment|/* PID hash table linkage. */
DECL|member|pidhash_next
r_struct
id|task_struct
op_star
id|pidhash_next
suffix:semicolon
DECL|member|pidhash_pprev
r_struct
id|task_struct
op_star
op_star
id|pidhash_pprev
suffix:semicolon
multiline_comment|/* Pointer to task[] array linkage. */
DECL|member|tarray_ptr
r_struct
id|task_struct
op_star
op_star
id|tarray_ptr
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
DECL|member|policy
DECL|member|rt_priority
r_int
r_int
id|timeout
comma
id|policy
comma
id|rt_priority
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
DECL|member|real_timer
r_struct
id|timer_list
id|real_timer
suffix:semicolon
DECL|member|times
r_struct
id|tms
id|times
suffix:semicolon
DECL|member|start_time
r_int
r_int
id|start_time
suffix:semicolon
multiline_comment|/* mm fault and swap info: this can arguably be seen as either mm-specific or thread-specific */
DECL|member|min_flt
DECL|member|maj_flt
DECL|member|nswap
DECL|member|cmin_flt
DECL|member|cmaj_flt
DECL|member|cnswap
r_int
r_int
id|min_flt
comma
id|maj_flt
comma
id|nswap
comma
id|cmin_flt
comma
id|cmaj_flt
comma
id|cnswap
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
multiline_comment|/* limits */
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
op_star
id|fs
suffix:semicolon
multiline_comment|/* open file information */
DECL|member|files
r_struct
id|files_struct
op_star
id|files
suffix:semicolon
multiline_comment|/* memory management info */
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
multiline_comment|/* signal handlers */
DECL|member|sig
r_struct
id|signal_struct
op_star
id|sig
suffix:semicolon
multiline_comment|/* SMP state */
DECL|member|has_cpu
r_int
id|has_cpu
suffix:semicolon
DECL|member|processor
r_int
id|processor
suffix:semicolon
DECL|member|last_processor
r_int
id|last_processor
suffix:semicolon
DECL|member|lock_depth
r_int
id|lock_depth
suffix:semicolon
multiline_comment|/* Lock depth. We can context switch in and out of holding a syscall kernel lock... */
multiline_comment|/* Spinlocks for various pieces or per-task state. */
DECL|member|sigmask_lock
id|spinlock_t
id|sigmask_lock
suffix:semicolon
multiline_comment|/* Protects signal and blocked */
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
DECL|macro|PF_FORKNOEXEC
mdefine_line|#define PF_FORKNOEXEC&t;0x00000040&t;/* forked but didn&squot;t exec */
DECL|macro|PF_SUPERPRIV
mdefine_line|#define PF_SUPERPRIV&t;0x00000100&t;/* used super-user privileges */
DECL|macro|PF_DUMPCORE
mdefine_line|#define PF_DUMPCORE&t;0x00000200&t;/* dumped core */
DECL|macro|PF_SIGNALED
mdefine_line|#define PF_SIGNALED&t;0x00000400&t;/* killed by a signal */
DECL|macro|PF_STARTING
mdefine_line|#define PF_STARTING&t;0x00000002&t;/* being created */
DECL|macro|PF_EXITING
mdefine_line|#define PF_EXITING&t;0x00000004&t;/* getting shut down */
DECL|macro|PF_USEDFPU
mdefine_line|#define PF_USEDFPU&t;0x00100000&t;/* Process used the FPU this quantum (SMP only) */
DECL|macro|PF_DTRACE
mdefine_line|#define PF_DTRACE&t;0x00200000&t;/* delayed trace (used on m68k) */
DECL|macro|PF_ONSIGSTK
mdefine_line|#define PF_ONSIGSTK&t;0x00400000&t;/* works on signal stack (m68k only) */
multiline_comment|/*&n; * Limit the stack by to some sane default: root can always&n; * increase this limit if needed..  8MB seems reasonable.&n; */
DECL|macro|_STK_LIM
mdefine_line|#define _STK_LIM&t;(8*1024*1024)
DECL|macro|DEF_PRIORITY
mdefine_line|#define DEF_PRIORITY&t;(20*HZ/100)&t;/* 200 ms time slices */
multiline_comment|/* Note: This is very ugly I admit.  But some versions of gcc will&n; *       dump core when an empty structure constant is parsed at&n; *       the end of a large top level structure initialization. -DaveM&n; */
macro_line|#ifdef __SMP__
DECL|macro|INIT_LOCKS
mdefine_line|#define INIT_LOCKS&t;SPIN_LOCK_UNLOCKED
macro_line|#else
DECL|macro|INIT_LOCKS
mdefine_line|#define INIT_LOCKS
macro_line|#endif
multiline_comment|/*&n; *  INIT_TASK is used to set up the first task table, touch at&n; * your own risk!. Base=0, limit=0x1fffff (=2MB)&n; */
DECL|macro|INIT_TASK
mdefine_line|#define INIT_TASK &bslash;&n;/* state etc */&t;{ 0,DEF_PRIORITY,DEF_PRIORITY,0,0,0,0, &bslash;&n;/* debugregs */ { 0, },            &bslash;&n;/* exec domain */&amp;default_exec_domain, &bslash;&n;/* binfmt */&t;NULL, &bslash;&n;/* schedlink */&t;&amp;init_task,&amp;init_task, &amp;init_task, &amp;init_task, &bslash;&n;/* ec,brk... */&t;0,0,0,0,0, &bslash;&n;/* pid etc.. */&t;0,0,0,0,0, &bslash;&n;/* suppl grps*/ 0, {0,}, &bslash;&n;/* proc links*/ &amp;init_task,&amp;init_task,NULL,NULL,NULL, &bslash;&n;/* pidhash */&t;NULL, NULL, &bslash;&n;/* tarray */&t;&amp;task[0], &bslash;&n;/* chld wait */&t;NULL, &bslash;&n;/* uid etc */&t;0,0,0,0,0,0,0,0, &bslash;&n;/* timeout */&t;0,SCHED_OTHER,0,0,0,0,0,0,0, &bslash;&n;/* timer */&t;{ NULL, NULL, 0, 0, it_real_fn }, &bslash;&n;/* utime */&t;{0,0,0,0},0, &bslash;&n;/* flt */&t;0,0,0,0,0,0, &bslash;&n;/* swp */&t;0,0,0,0,0, &bslash;&n;/* rlimits */   INIT_RLIMITS, &bslash;&n;/* math */&t;0, &bslash;&n;/* comm */&t;&quot;swapper&quot;, &bslash;&n;/* fs info */&t;0,NULL, &bslash;&n;/* ipc */&t;NULL, NULL, &bslash;&n;/* ldt */&t;NULL, &bslash;&n;/* tss */&t;INIT_TSS, &bslash;&n;/* fs */&t;&amp;init_fs, &bslash;&n;/* files */&t;&amp;init_files, &bslash;&n;/* mm */&t;&amp;init_mm, &bslash;&n;/* signals */&t;&amp;init_signals, &bslash;&n;/* SMP */&t;0,0,0,0, &bslash;&n;/* locks */&t;INIT_LOCKS &bslash;&n;}
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
r_int
r_int
id|stack
(braket
l_int|2048
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_union
id|task_union
id|init_task_union
suffix:semicolon
r_extern
r_struct
id|mm_struct
id|init_mm
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
op_star
id|tarray_freelist
suffix:semicolon
r_extern
id|spinlock_t
id|taskslot_lock
suffix:semicolon
DECL|function|add_free_taskslot
r_extern
id|__inline__
r_void
id|add_free_taskslot
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|t
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|taskslot_lock
)paren
suffix:semicolon
op_star
id|t
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
id|tarray_freelist
suffix:semicolon
id|tarray_freelist
op_assign
id|t
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|taskslot_lock
)paren
suffix:semicolon
)brace
DECL|function|get_free_taskslot
r_extern
id|__inline__
r_struct
id|task_struct
op_star
op_star
id|get_free_taskslot
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|tslot
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|taskslot_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tslot
op_assign
id|tarray_freelist
)paren
op_ne
l_int|NULL
)paren
(brace
id|tarray_freelist
op_assign
(paren
r_struct
id|task_struct
op_star
op_star
)paren
op_star
id|tslot
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|taskslot_lock
)paren
suffix:semicolon
r_return
id|tslot
suffix:semicolon
)brace
multiline_comment|/* PID hashing. */
DECL|macro|PIDHASH_SZ
mdefine_line|#define PIDHASH_SZ (NR_TASKS &gt;&gt; 2)
r_extern
r_struct
id|task_struct
op_star
id|pidhash
(braket
id|PIDHASH_SZ
)braket
suffix:semicolon
r_extern
id|spinlock_t
id|pidhash_lock
suffix:semicolon
DECL|macro|pid_hashfn
mdefine_line|#define pid_hashfn(x)&t;((((x) &gt;&gt; 8) ^ (x)) &amp; (PIDHASH_SZ - 1))
DECL|function|hash_pid
r_extern
id|__inline__
r_void
id|hash_pid
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|htable
op_assign
op_amp
id|pidhash
(braket
id|pid_hashfn
c_func
(paren
id|p-&gt;pid
)paren
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;pidhash_next
op_assign
op_star
id|htable
)paren
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|htable
)paren
op_member_access_from_pointer
id|pidhash_pprev
op_assign
op_amp
id|p-&gt;pidhash_next
suffix:semicolon
)brace
op_star
id|htable
op_assign
id|p
suffix:semicolon
id|p-&gt;pidhash_pprev
op_assign
id|htable
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
)brace
DECL|function|unhash_pid
r_extern
id|__inline__
r_void
id|unhash_pid
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pidhash_next
)paren
(brace
id|p-&gt;pidhash_next-&gt;pidhash_pprev
op_assign
id|p-&gt;pidhash_pprev
suffix:semicolon
)brace
op_star
id|p-&gt;pidhash_pprev
op_assign
id|p-&gt;pidhash_next
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
)brace
DECL|function|find_task_by_pid
r_extern
id|__inline__
r_struct
id|task_struct
op_star
id|find_task_by_pid
c_func
(paren
r_int
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|htable
op_assign
op_amp
id|pidhash
(braket
id|pid_hashfn
c_func
(paren
id|pid
)paren
)braket
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_star
id|htable
suffix:semicolon
id|p
op_logical_and
id|p-&gt;pid
op_ne
id|pid
suffix:semicolon
id|p
op_assign
id|p-&gt;pidhash_next
)paren
(brace
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|pidhash_lock
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/* per-UID process charging. */
r_extern
r_int
id|charge_uid
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#include &lt;asm/current.h&gt;
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
r_extern
r_void
id|do_timer
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
r_extern
r_int
id|securelevel
suffix:semicolon
multiline_comment|/* system security level */
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
id|wake_up_process
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
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
r_void
id|force_sig
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
r_void
op_star
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
comma
r_void
op_star
id|dev_id
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
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
multiline_comment|/*&n; * This has now become a routine instead of a macro, it sets a flag if&n; * it returns true (to do BSD-style accounting where the process is flagged&n; * if it uses root privs). The implication of this is that you should do&n; * normal permissions checks first, and check suser() last.&n; */
DECL|function|suser
r_extern
r_inline
r_int
id|suser
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
l_int|0
)paren
(brace
id|current-&gt;flags
op_or_assign
id|PF_SUPERPRIV
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|copy_thread
c_func
(paren
r_int
comma
r_int
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
r_void
id|exit_mm
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|exit_fs
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|exit_files
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|exit_sighand
c_func
(paren
r_struct
id|task_struct
op_star
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
r_extern
r_int
id|do_fork
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* See if we have a valid user level fd.&n; * If it makes sense, return the file structure it references.&n; * Otherwise return NULL.&n; */
DECL|function|file_from_fd
r_extern
r_inline
r_struct
id|file
op_star
id|file_from_fd
c_func
(paren
r_const
r_int
r_int
id|fd
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* either valid or null */
r_return
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * The wait-queues are circular lists, and you have to be *very* sure&n; * to keep them correct. Use only these two functions to add/remove&n; * entries in the queues.&n; */
DECL|function|__add_wait_queue
r_extern
r_inline
r_void
id|__add_wait_queue
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
id|wait-&gt;next
op_assign
op_star
id|p
ques
c_cond
suffix:colon
id|WAIT_QUEUE_HEAD
c_func
(paren
id|p
)paren
suffix:semicolon
op_star
id|p
op_assign
id|wait
suffix:semicolon
)brace
r_extern
id|rwlock_t
id|waitqueue_lock
suffix:semicolon
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
id|write_lock_irqsave
c_func
(paren
op_amp
id|waitqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|__add_wait_queue
c_func
(paren
id|p
comma
id|wait
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|waitqueue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__remove_wait_queue
r_extern
r_inline
r_void
id|__remove_wait_queue
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
r_struct
id|wait_queue
op_star
id|next
op_assign
id|wait-&gt;next
suffix:semicolon
r_struct
id|wait_queue
op_star
id|head
op_assign
id|next
suffix:semicolon
r_struct
id|wait_queue
op_star
id|tmp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|head-&gt;next
)paren
op_ne
id|wait
)paren
(brace
id|head
op_assign
id|tmp
suffix:semicolon
)brace
id|head-&gt;next
op_assign
id|next
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
id|write_lock_irqsave
c_func
(paren
op_amp
id|waitqueue_lock
comma
id|flags
)paren
suffix:semicolon
id|__remove_wait_queue
c_func
(paren
id|p
comma
id|wait
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|waitqueue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|poll_wait
r_extern
r_inline
r_void
id|poll_wait
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|wait_address
comma
id|poll_table
op_star
id|p
)paren
(brace
r_struct
id|poll_table_entry
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
id|__MAX_POLL_TABLE_ENTRIES
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
DECL|macro|REMOVE_LINKS
mdefine_line|#define REMOVE_LINKS(p) do { unsigned long flags; &bslash;&n;&t;write_lock_irqsave(&amp;tasklist_lock, flags); &bslash;&n;&t;(p)-&gt;next_task-&gt;prev_task = (p)-&gt;prev_task; &bslash;&n;&t;(p)-&gt;prev_task-&gt;next_task = (p)-&gt;next_task; &bslash;&n;&t;write_unlock_irqrestore(&amp;tasklist_lock, flags); &bslash;&n;&t;if ((p)-&gt;p_osptr) &bslash;&n;&t;&t;(p)-&gt;p_osptr-&gt;p_ysptr = (p)-&gt;p_ysptr; &bslash;&n;&t;if ((p)-&gt;p_ysptr) &bslash;&n;&t;&t;(p)-&gt;p_ysptr-&gt;p_osptr = (p)-&gt;p_osptr; &bslash;&n;&t;else &bslash;&n;&t;&t;(p)-&gt;p_pptr-&gt;p_cptr = (p)-&gt;p_osptr; &bslash;&n;&t;} while (0)
DECL|macro|SET_LINKS
mdefine_line|#define SET_LINKS(p) do { unsigned long flags; &bslash;&n;&t;write_lock_irqsave(&amp;tasklist_lock, flags); &bslash;&n;&t;(p)-&gt;next_task = &amp;init_task; &bslash;&n;&t;(p)-&gt;prev_task = init_task.prev_task; &bslash;&n;&t;init_task.prev_task-&gt;next_task = (p); &bslash;&n;&t;init_task.prev_task = (p); &bslash;&n;&t;write_unlock_irqrestore(&amp;tasklist_lock, flags); &bslash;&n;&t;(p)-&gt;p_ysptr = NULL; &bslash;&n;&t;if (((p)-&gt;p_osptr = (p)-&gt;p_pptr-&gt;p_cptr) != NULL) &bslash;&n;&t;&t;(p)-&gt;p_osptr-&gt;p_ysptr = p; &bslash;&n;&t;(p)-&gt;p_pptr-&gt;p_cptr = p; &bslash;&n;&t;} while (0)
DECL|macro|for_each_task
mdefine_line|#define for_each_task(p) &bslash;&n;&t;for (p = &amp;init_task ; (p = p-&gt;next_task) != &amp;init_task ; )
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
