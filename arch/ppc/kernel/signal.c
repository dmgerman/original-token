multiline_comment|/*&n; *  linux/arch/ppc/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Adapted for PowerPC by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu) &n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
id|asmlinkage
r_int
id|sys_waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
op_star
id|stat_addr
comma
r_int
id|options
)paren
suffix:semicolon
multiline_comment|/*&n; * atomically swap in the new signal mask, and wait for a signal.&n; */
DECL|function|sys_sigsuspend
id|asmlinkage
r_int
id|sys_sigsuspend
c_func
(paren
r_int
r_int
id|set
comma
r_int
id|p2
comma
r_int
id|p3
comma
r_int
id|p4
comma
r_int
id|p6
comma
r_int
id|p7
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
op_amp
id|_BLOCKABLE
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
op_minus
id|EINTR
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Task: %x[%d] - SIGSUSPEND at %x, Mask: %x&bslash;n&quot;
comma
id|current
comma
id|current-&gt;pid
comma
id|regs-&gt;nip
comma
id|set
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
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
r_if
c_cond
(paren
id|do_signal
c_func
(paren
id|mask
comma
id|regs
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|sigcontext_struct
op_star
id|sc
suffix:semicolon
r_struct
id|pt_regs
op_star
id|int_regs
suffix:semicolon
r_int
id|signo
suffix:semicolon
macro_line|#if 1 &t;
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
r_sizeof
(paren
id|sc
)paren
)paren
op_logical_or
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_ge
id|KERNELBASE
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#endif&t;
id|sc
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
id|current-&gt;blocked
op_assign
id|sc-&gt;oldmask
op_amp
id|_BLOCKABLE
suffix:semicolon
id|int_regs
op_assign
id|sc-&gt;regs
suffix:semicolon
id|signo
op_assign
id|sc-&gt;signal
suffix:semicolon
id|sc
op_increment
suffix:semicolon
multiline_comment|/* Pop signal &squot;context&squot; */
r_if
c_cond
(paren
id|sc
op_eq
(paren
r_struct
id|sigcontext_struct
op_star
)paren
(paren
id|int_regs
)paren
)paren
(brace
multiline_comment|/* Last stacked signal */
macro_line|#if 0&t;
multiline_comment|/* This doesn&squot;t work - it blows away the return address! */
id|memcpy
c_func
(paren
id|regs
comma
id|int_regs
comma
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Don&squot;t mess up &squot;my&squot; stack frame */
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;gpr
comma
op_amp
id|int_regs-&gt;gpr
comma
r_sizeof
(paren
op_star
id|regs
)paren
op_minus
r_sizeof
(paren
id|regs-&gt;_overhead
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;orig_gpr3
op_ge
l_int|0
op_logical_and
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTNOINTR
)paren
)paren
(brace
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|regs-&gt;orig_gpr3
suffix:semicolon
id|regs-&gt;nip
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Back up &amp; retry system call */
id|regs-&gt;result
op_assign
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|regs-&gt;result
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* More signals to go */
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|sc
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|sc-&gt;signal
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|4
)braket
op_assign
id|sc-&gt;regs
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
id|sc-&gt;regs
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|regs-&gt;nip
op_assign
id|sc-&gt;handler
suffix:semicolon
r_return
(paren
id|sc-&gt;signal
)paren
suffix:semicolon
)brace
id|badframe
suffix:colon
multiline_comment|/*printk(&quot;sys_sigreturn(): badstack regs %x cur %s/%d&bslash;n&quot;,&n;&t; regs,current-&gt;comm,current-&gt;pid);*/
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; *&n; * Note that we go through the signals twice: once to check the signals that&n; * the kernel can handle, and then we build all the user-level signal handling&n; * stack-frames in one go after that.&n; */
DECL|function|do_signal
id|asmlinkage
r_int
id|do_signal
c_func
(paren
r_int
r_int
id|oldmask
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mask
op_assign
op_complement
id|current-&gt;blocked
suffix:semicolon
r_int
r_int
id|handler_signal
op_assign
l_int|0
suffix:semicolon
r_int
r_int
op_star
id|frame
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|trampoline
suffix:semicolon
r_int
r_int
op_star
id|regs_ptr
suffix:semicolon
r_int
r_int
id|nip
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|signr
suffix:semicolon
r_int
id|bitno
suffix:semicolon
r_struct
id|sigcontext_struct
op_star
id|sc
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
suffix:semicolon
r_int
id|s
suffix:semicolon
r_while
c_loop
(paren
(paren
id|signr
op_assign
id|current-&gt;signal
op_amp
id|mask
)paren
)paren
(brace
r_for
c_loop
(paren
id|bitno
op_assign
l_int|0
suffix:semicolon
id|bitno
OL
l_int|32
suffix:semicolon
id|bitno
op_increment
)paren
(brace
r_if
c_cond
(paren
id|signr
op_amp
(paren
l_int|1
op_lshift
id|bitno
)paren
)paren
r_break
suffix:semicolon
)brace
id|signr
op_assign
id|bitno
suffix:semicolon
id|current-&gt;signal
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|signr
)paren
suffix:semicolon
multiline_comment|/* Clear bit */
id|sa
op_assign
id|current-&gt;sig-&gt;action
op_plus
id|signr
suffix:semicolon
id|signr
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
op_logical_and
id|signr
op_ne
id|SIGKILL
)paren
(brace
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
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
op_logical_neg
(paren
id|signr
op_assign
id|current-&gt;exit_code
)paren
)paren
r_continue
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|signr
op_eq
id|SIGSTOP
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|_S
c_func
(paren
id|signr
)paren
op_amp
id|current-&gt;blocked
)paren
(brace
id|current-&gt;signal
op_or_assign
id|_S
c_func
(paren
id|signr
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sa
op_assign
id|current-&gt;sig-&gt;action
op_plus
id|signr
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sa-&gt;sa_handler
op_eq
id|SIG_IGN
)paren
(brace
r_if
c_cond
(paren
id|signr
op_ne
id|SIGCHLD
)paren
r_continue
suffix:semicolon
multiline_comment|/* check for SIGCHLD: it&squot;s special */
r_while
c_loop
(paren
id|sys_waitpid
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
)paren
OG
l_int|0
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sa-&gt;sa_handler
op_eq
id|SIG_DFL
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|signr
)paren
(brace
r_case
id|SIGCONT
suffix:colon
r_case
id|SIGCHLD
suffix:colon
r_case
id|SIGWINCH
suffix:colon
r_continue
suffix:semicolon
r_case
id|SIGSTOP
suffix:colon
r_case
id|SIGTSTP
suffix:colon
r_case
id|SIGTTIN
suffix:colon
r_case
id|SIGTTOU
suffix:colon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
r_continue
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;p_pptr-&gt;sig-&gt;action
(braket
id|SIGCHLD
op_minus
l_int|1
)braket
dot
id|sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
)paren
id|notify_parent
c_func
(paren
id|current
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
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
id|SIGIOT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGSEGV
suffix:colon
r_if
c_cond
(paren
id|current-&gt;binfmt
op_logical_and
id|current-&gt;binfmt-&gt;core_dump
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;binfmt
op_member_access_from_pointer
id|core_dump
c_func
(paren
id|signr
comma
id|regs
)paren
)paren
id|signr
op_or_assign
l_int|0x80
suffix:semicolon
)brace
multiline_comment|/* fall through */
r_default
suffix:colon
id|current-&gt;signal
op_or_assign
id|_S
c_func
(paren
id|signr
op_amp
l_int|0x7f
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|signr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* handle signal */
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;orig_gpr3
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTSYS
op_logical_and
op_logical_neg
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_RESTART
)paren
)paren
)paren
(paren
r_int
)paren
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
id|handler_signal
op_or_assign
l_int|1
op_lshift
(paren
id|signr
op_minus
l_int|1
)paren
suffix:semicolon
id|mask
op_and_assign
op_complement
id|sa-&gt;sa_mask
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler_signal
)paren
multiline_comment|/* no handler will be called - return 0 */
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|nip
op_assign
id|regs-&gt;nip
suffix:semicolon
id|frame
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Build trampoline code on stack */
id|frame
op_sub_assign
l_int|2
suffix:semicolon
id|trampoline
op_assign
id|frame
suffix:semicolon
macro_line|#if 1
multiline_comment|/* verify stack is valid for writing regs struct */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|frame
comma
r_sizeof
(paren
r_int
)paren
op_star
l_int|2
op_plus
r_sizeof
(paren
op_star
id|regs
)paren
)paren
op_logical_or
(paren
id|frame
op_ge
id|KERNELBASE
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#endif
id|trampoline
(braket
l_int|0
)braket
op_assign
l_int|0x38007777
suffix:semicolon
multiline_comment|/* li r0,0x7777 */
id|trampoline
(braket
l_int|1
)braket
op_assign
l_int|0x44000002
suffix:semicolon
multiline_comment|/* sc           */
id|frame
op_sub_assign
r_sizeof
(paren
op_star
id|regs
)paren
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|regs_ptr
op_assign
id|frame
suffix:semicolon
id|memcpy
c_func
(paren
id|regs_ptr
comma
id|regs
comma
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
id|signr
op_assign
l_int|1
suffix:semicolon
id|sa
op_assign
id|current-&gt;sig-&gt;action
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
id|signr
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
id|handler_signal
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
id|handler_signal
)paren
)paren
r_continue
suffix:semicolon
id|frame
op_sub_assign
r_sizeof
(paren
r_struct
id|sigcontext_struct
)paren
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|frame
comma
r_sizeof
(paren
r_struct
id|sigcontext_struct
)paren
op_div
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#endif    
id|sc
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
id|frame
suffix:semicolon
id|nip
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
suffix:semicolon
macro_line|#if 0 /* Old compiler */&t;&t;
id|nip
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|nip
suffix:semicolon
macro_line|#endif&t;&t;
r_if
c_cond
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_ONESHOT
)paren
id|sa-&gt;sa_handler
op_assign
l_int|NULL
suffix:semicolon
id|sc-&gt;handler
op_assign
id|nip
suffix:semicolon
id|sc-&gt;oldmask
op_assign
id|current-&gt;blocked
suffix:semicolon
id|sc-&gt;regs
op_assign
(paren
r_int
r_int
)paren
id|regs_ptr
suffix:semicolon
id|sc-&gt;signal
op_assign
id|signr
suffix:semicolon
id|current-&gt;blocked
op_or_assign
id|sa-&gt;sa_mask
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|signr
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|regs_ptr
suffix:semicolon
)brace
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|trampoline
suffix:semicolon
id|regs-&gt;nip
op_assign
id|nip
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|sc
suffix:semicolon
multiline_comment|/* The DATA cache must be flushed here to insure coherency */
multiline_comment|/* between the DATA &amp; INSTRUCTION caches.  Since we just */
multiline_comment|/* created an instruction stream using the DATA [cache] space */
multiline_comment|/* and since the instruction cache will not look in the DATA */
multiline_comment|/* cache for new data, we have to force the data to go on to */
multiline_comment|/* memory and flush the instruction cache to force it to look */
multiline_comment|/* there.  The following function performs this magic */
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|badframe
suffix:colon
multiline_comment|/*  printk(&quot;do_signal(): badstack signr %d frame %x regs %x cur %s/%d&bslash;n&quot;,&n;&t; signr,frame,regs,current-&gt;comm,current-&gt;pid);*/
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
eof
