multiline_comment|/*&n; *  linux/arch/ppc/kernel/signal.c&n; *&n; *  $Id: signal.c,v 1.20 1998/09/28 16:47:09 cort Exp $&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/kernel/signal.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; *    1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
DECL|macro|GP_REGS_SIZE
mdefine_line|#define GP_REGS_SIZE&t;MIN(sizeof(elf_gregset_t), sizeof(struct pt_regs))
multiline_comment|/* &n; * These are the flags in the MSR that the user is allowed to change&n; * by modifying the saved value of the MSR on the stack.  SE and BE&n; * should not be in this list since gdb may want to change these.  I.e,&n; * you should be able to step out of a signal handler to see what&n; * instruction executes next after the signal handler completes.&n; * Alternately, if you stepped into a signal handler, you should be&n; * able to continue &squot;til the next breakpoint from within the signal&n; * handler, even if the handler returns.&n; */
DECL|macro|MSR_USERCHANGE
mdefine_line|#define MSR_USERCHANGE&t;(MSR_FE0 | MSR_FE1)
r_int
id|do_signal
c_func
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|sys_wait4
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
comma
r_int
r_int
op_star
id|ru
)paren
suffix:semicolon
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
id|old_sigset_t
id|mask
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
id|sigset_t
id|saveset
suffix:semicolon
id|mask
op_and_assign
id|_BLOCKABLE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|mask
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
op_minus
id|EINTR
suffix:semicolon
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
op_amp
id|saveset
comma
id|regs
)paren
)paren
multiline_comment|/*&n;&t;&t;&t; * If a signal handler needs to be called,&n;&t;&t;&t; * do_signal() has set R3 to the signal number (the&n;&t;&t;&t; * first argument of the signal handler), so don&squot;t&n;&t;&t;&t; * overwrite that with EINTR !&n;&t;&t;&t; * In the other cases, do_signal() doesn&squot;t touch &n;&t;&t;&t; * R3, so it&squot;s still set to -EINTR (see above).&n;&t;&t;&t; */
r_return
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
)brace
)brace
r_int
DECL|function|sys_rt_sigsuspend
id|sys_rt_sigsuspend
c_func
(paren
id|sigset_t
op_star
id|unewset
comma
r_int
id|sigsetsize
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
id|sigset_t
id|saveset
comma
id|newset
suffix:semicolon
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s.  */
r_if
c_cond
(paren
id|sigsetsize
op_ne
r_sizeof
(paren
id|sigset_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|newset
comma
id|unewset
comma
r_sizeof
(paren
id|newset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|newset
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|newset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
op_minus
id|EINTR
suffix:semicolon
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
op_amp
id|saveset
comma
id|regs
)paren
)paren
r_return
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
)brace
)brace
DECL|function|sys_rt_sigreturn
id|asmlinkage
r_int
id|sys_rt_sigreturn
c_func
(paren
r_int
r_int
id|__unused
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sys_rt_sigreturn(): %s/%d not yet implemented.&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaltstack
id|sys_sigaltstack
c_func
(paren
r_const
id|stack_t
op_star
id|uss
comma
id|stack_t
op_star
id|uoss
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|uss
suffix:semicolon
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_int
DECL|function|sys_sigaction
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
op_star
id|act
comma
r_struct
id|old_sigaction
op_star
id|oact
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|old_sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_restorer
comma
op_amp
id|act-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask
)paren
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|new_ka.sa.sa_mask
comma
id|mask
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oact
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_restorer
comma
op_amp
id|oact-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
op_amp
id|oact-&gt;sa_mask
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * When we have signals to deliver, we set up on the&n; * user stack, going down from the original stack pointer:&n; *&t;a sigregs struct&n; *&t;one or more sigcontext structs&n; *&t;a gap of __SIGNAL_FRAMESIZE bytes&n; *&n; * Each of these things must be a multiple of 16 bytes in size.&n; *&n; * XXX ultimately we will have to stack up a siginfo and ucontext&n; * for each rt signal.&n; */
DECL|struct|sigregs
r_struct
id|sigregs
(brace
DECL|member|gp_regs
id|elf_gregset_t
id|gp_regs
suffix:semicolon
DECL|member|fp_regs
r_float
id|fp_regs
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
DECL|member|tramp
r_int
r_int
id|tramp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Programs using the rs6000/xcoff abi can save up to 19 gp regs&n;&t;   and 18 fp regs below sp before decrementing it. */
DECL|member|abigap
r_int
id|abigap
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|function|sys_sigreturn
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
comma
id|sigctx
suffix:semicolon
r_struct
id|sigregs
op_star
id|sr
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|elf_gregset_t
id|saved_regs
suffix:semicolon
multiline_comment|/* an array of ELF_NGREG unsigned longs */
id|sigset_t
id|set
suffix:semicolon
r_int
r_int
id|prevsp
suffix:semicolon
id|sc
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_plus
id|__SIGNAL_FRAMESIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sigctx
comma
id|sc
comma
r_sizeof
(paren
id|sigctx
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|set.sig
(braket
l_int|0
)braket
op_assign
id|sigctx.oldmask
suffix:semicolon
macro_line|#if _NSIG_WORDS &gt; 1
id|set.sig
(braket
l_int|1
)braket
op_assign
id|sigctx._unused
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
id|sigdelsetmask
c_func
(paren
op_amp
id|set
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sc
op_increment
suffix:semicolon
multiline_comment|/* Look at next sigcontext */
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
id|sigctx.regs
)paren
)paren
(brace
multiline_comment|/* Last stacked signal - restore registers */
id|sr
op_assign
(paren
r_struct
id|sigregs
op_star
)paren
id|sigctx.regs
suffix:semicolon
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|smp_giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#else&t;
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|giveup_fpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|saved_regs
comma
op_amp
id|sr-&gt;gp_regs
comma
r_sizeof
(paren
id|sr-&gt;gp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|saved_regs
(braket
id|PT_MSR
)braket
op_assign
(paren
id|regs-&gt;msr
op_amp
op_complement
id|MSR_USERCHANGE
)paren
op_or
(paren
id|saved_regs
(braket
id|PT_MSR
)braket
op_amp
id|MSR_USERCHANGE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|regs
comma
id|saved_regs
comma
id|GP_REGS_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|current-&gt;tss.fpr
comma
op_amp
id|sr-&gt;fp_regs
comma
r_sizeof
(paren
id|sr-&gt;fp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|ret
op_assign
id|regs-&gt;result
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
op_minus
id|__SIGNAL_FRAMESIZE
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sigctx
comma
id|sc
comma
r_sizeof
(paren
id|sigctx
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|sr
op_assign
(paren
r_struct
id|sigregs
op_star
)paren
id|sigctx.regs
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|ret
op_assign
id|sigctx.signal
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
id|sr
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
op_amp
id|sr-&gt;tramp
suffix:semicolon
id|regs-&gt;nip
op_assign
id|sigctx.handler
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|prevsp
comma
op_amp
id|sr-&gt;gp_regs
(braket
id|PT_R1
)braket
)paren
op_logical_or
id|put_user
c_func
(paren
id|prevsp
comma
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
)paren
r_goto
id|badframe
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|badframe
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
r_static
r_void
DECL|function|setup_frame
id|setup_frame
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigregs
op_star
id|frame
comma
r_int
r_int
id|newsp
)paren
(brace
r_struct
id|sigcontext_struct
op_star
id|sc
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
id|newsp
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|frame
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|smp_giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#else&t;
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|giveup_fpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;gp_regs
comma
id|regs
comma
id|GP_REGS_SIZE
)paren
op_logical_or
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;fp_regs
comma
id|current-&gt;tss.fpr
comma
id|ELF_NFPREG
op_star
r_sizeof
(paren
r_float
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0x38007777UL
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
)paren
multiline_comment|/* li r0,0x7777 */
op_logical_or
id|__put_user
c_func
(paren
l_int|0x44000002UL
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|1
)braket
)paren
)paren
multiline_comment|/* sc */
r_goto
id|badframe
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;tramp
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|newsp
op_sub_assign
id|__SIGNAL_FRAMESIZE
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
op_star
)paren
id|newsp
)paren
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;nip
comma
op_amp
id|sc-&gt;handler
)paren
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|3
)braket
comma
op_amp
id|sc-&gt;signal
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|newsp
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
id|frame
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
suffix:semicolon
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in setup_frame, regs=%p frame=%p newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
id|newsp
)paren
suffix:semicolon
macro_line|#endif
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
r_static
r_void
DECL|function|handle_signal
id|handle_signal
c_func
(paren
r_int
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
op_star
id|newspp
comma
r_int
r_int
id|frame
)paren
(brace
r_struct
id|sigcontext_struct
op_star
id|sc
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x0C00
multiline_comment|/* System Call! */
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
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
)paren
)paren
)paren
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* Put another sigcontext on the stack */
op_star
id|newspp
op_sub_assign
r_sizeof
(paren
op_star
id|sc
)paren
suffix:semicolon
id|sc
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
op_star
id|newspp
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|sc
comma
r_sizeof
(paren
op_star
id|sc
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
comma
op_amp
id|sc-&gt;handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|oldset-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|sc-&gt;oldmask
)paren
macro_line|#if _NSIG_WORDS &gt; 1
op_logical_or
id|__put_user
c_func
(paren
id|oldset-&gt;sig
(braket
l_int|1
)braket
comma
op_amp
id|sc-&gt;_unused
(braket
l_int|3
)braket
)paren
macro_line|#endif
op_logical_or
id|__put_user
c_func
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|frame
comma
op_amp
id|sc-&gt;regs
)paren
op_logical_or
id|__put_user
c_func
(paren
id|sig
comma
op_amp
id|sc-&gt;signal
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONESHOT
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_NODEFER
)paren
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigorsets
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|current-&gt;blocked
comma
op_amp
id|ka-&gt;sa.sa_mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sig
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in handle_signal, regs=%p frame=%lx newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
op_star
id|newspp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sc=%p sig=%d ka=%p info=%p oldset=%p&bslash;n&quot;
comma
id|sc
comma
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
)paren
suffix:semicolon
macro_line|#endif
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
r_int
r_int
id|frame
comma
id|newsp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldset
)paren
id|oldset
op_assign
op_amp
id|current-&gt;blocked
suffix:semicolon
id|newsp
op_assign
id|frame
op_assign
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_minus
r_sizeof
(paren
r_struct
id|sigregs
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|signr
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|signr
op_assign
id|dequeue_signal
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|info
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|signr
)paren
r_break
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
multiline_comment|/* Let the debugger run.  */
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
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;re back.  Did the debugger cancel the sig?  */
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
multiline_comment|/* The debugger continued.  Ignore SIGSTOP.  */
r_if
c_cond
(paren
id|signr
op_eq
id|SIGSTOP
)paren
r_continue
suffix:semicolon
multiline_comment|/* Update the siginfo structure.  Is this good?  */
r_if
c_cond
(paren
id|signr
op_ne
id|info.si_signo
)paren
(brace
id|info.si_signo
op_assign
id|signr
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|SI_USER
suffix:semicolon
id|info.si_pid
op_assign
id|current-&gt;p_pptr-&gt;pid
suffix:semicolon
id|info.si_uid
op_assign
id|current-&gt;p_pptr-&gt;uid
suffix:semicolon
)brace
multiline_comment|/* If the (new) signal is now blocked, requeue it.  */
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|signr
)paren
)paren
(brace
id|send_sig_info
c_func
(paren
id|signr
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|signr
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_handler
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
multiline_comment|/* Check for SIGCHLD: it&squot;s special.  */
r_while
c_loop
(paren
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
comma
l_int|NULL
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
id|ka-&gt;sa.sa_handler
op_eq
id|SIG_DFL
)paren
(brace
r_int
id|exit_code
op_assign
id|signr
suffix:semicolon
multiline_comment|/* Init gets no signals it doesn&squot;t want.  */
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
id|is_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_case
id|SIGSTOP
suffix:colon
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
id|sa.sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
)paren
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
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
id|SIGABRT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGSEGV
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;binfmt
op_logical_and
id|current-&gt;binfmt-&gt;core_dump
op_logical_and
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
id|exit_code
op_or_assign
l_int|0x80
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_default
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;signal
comma
id|signr
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_SIGNALED
suffix:semicolon
id|do_exit
c_func
(paren
id|exit_code
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
)brace
multiline_comment|/* Whee!  Actually deliver the signal.  */
id|handle_signal
c_func
(paren
id|signr
comma
id|ka
comma
op_amp
id|info
comma
id|oldset
comma
id|regs
comma
op_amp
id|newsp
comma
id|frame
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x0C00
multiline_comment|/* System Call! */
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
r_if
c_cond
(paren
id|newsp
op_eq
id|frame
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no signals delivered */
id|setup_frame
c_func
(paren
id|regs
comma
(paren
r_struct
id|sigregs
op_star
)paren
id|frame
comma
id|newsp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
