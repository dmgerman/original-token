multiline_comment|/*&n; * Architecture-specific signal handling support.&n; *&n; * Copyright (C) 1999-2000 Hewlett-Packard Co&n; * Copyright (C) 1999-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Derived from i386 and Alpha versions.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rse.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG&t;0
DECL|macro|STACK_ALIGN
mdefine_line|#define STACK_ALIGN&t;16&t;&t;/* minimal alignment for stack pointer */
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE&t;(~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
macro_line|#if _NSIG_WORDS &gt; 1
DECL|macro|PUT_SIGSET
macro_line|# define PUT_SIGSET(k,u)&t;__copy_to_user((u)-&gt;sig, (k)-&gt;sig, sizeof(sigset_t))
DECL|macro|GET_SIGSET
macro_line|# define GET_SIGSET(k,u)&t;__copy_from_user((k)-&gt;sig, (u)-&gt;sig, sizeof(sigset_t))
macro_line|#else
DECL|macro|PUT_SIGSET
macro_line|# define PUT_SIGSET(k,u)&t;__put_user((k)-&gt;sig[0], &amp;(u)-&gt;sig[0])
DECL|macro|GET_SIGSET
macro_line|# define GET_SIGSET(k,u)&t;__get_user((k)-&gt;sig[0], &amp;(u)-&gt;sig[0])
macro_line|#endif
DECL|struct|sigscratch
r_struct
id|sigscratch
(brace
macro_line|#ifdef CONFIG_IA64_NEW_UNWIND
DECL|member|scratch_unat
r_int
r_int
id|scratch_unat
suffix:semicolon
multiline_comment|/* ar.unat for the general registers saved in pt */
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
macro_line|#else
r_struct
id|switch_stack
id|sw
suffix:semicolon
macro_line|#endif
DECL|member|pt
r_struct
id|pt_regs
id|pt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext
id|sc
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sys_wait4
(paren
r_int
comma
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ia64_do_signal
(paren
id|sigset_t
op_star
comma
r_struct
id|sigscratch
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* forward decl */
r_int
DECL|function|ia64_rt_sigsuspend
id|ia64_rt_sigsuspend
(paren
id|sigset_t
op_star
id|uset
comma
r_int
id|sigsetsize
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
id|sigset_t
id|oldset
comma
id|set
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
id|GET_SIGSET
c_func
(paren
op_amp
id|set
comma
id|uset
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
(brace
id|oldset
op_assign
id|current-&gt;blocked
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
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The return below usually returns to the signal handler.  We need to&n;&t; * pre-set the correct error code here to ensure that the right values&n;&t; * get saved in sigcontext by ia64_do_signal.&n;&t; */
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
id|scr-&gt;pt.r8
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
id|scr-&gt;pt.r8
op_assign
id|EINTR
suffix:semicolon
id|scr-&gt;pt.r10
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
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
id|ia64_do_signal
c_func
(paren
op_amp
id|oldset
comma
id|scr
comma
l_int|1
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaltstack
id|sys_sigaltstack
(paren
r_const
id|stack_t
op_star
id|uss
comma
id|stack_t
op_star
id|uoss
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|arg4
comma
r_int
id|arg5
comma
r_int
id|arg6
comma
r_int
id|arg7
comma
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|pt
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|pt-&gt;r12
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|restore_sigcontext
id|restore_sigcontext
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_int
r_int
id|ip
comma
id|flags
comma
id|nat
comma
id|um
comma
id|cfm
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* restore scratch that always needs gets updated during signal delivery: */
id|err
op_assign
id|__get_user
c_func
(paren
id|flags
comma
op_amp
id|sc-&gt;sc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|nat
comma
op_amp
id|sc-&gt;sc_nat
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ip
comma
op_amp
id|sc-&gt;sc_ip
)paren
suffix:semicolon
multiline_comment|/* instruction pointer */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|cfm
comma
op_amp
id|sc-&gt;sc_cfm
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|um
comma
op_amp
id|sc-&gt;sc_um
)paren
suffix:semicolon
multiline_comment|/* user mask */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_rsc
comma
op_amp
id|sc-&gt;sc_ar_rsc
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_ccv
comma
op_amp
id|sc-&gt;sc_ar_ccv
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_unat
comma
op_amp
id|sc-&gt;sc_ar_unat
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_fpsr
comma
op_amp
id|sc-&gt;sc_ar_fpsr
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_pfs
comma
op_amp
id|sc-&gt;sc_ar_pfs
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.pr
comma
op_amp
id|sc-&gt;sc_pr
)paren
suffix:semicolon
multiline_comment|/* predicates */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b0
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* b0 (rp) */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b6
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* b6 */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b7
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* b7 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r1
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|1
)braket
comma
l_int|3
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r1-r3 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r8
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|8
)braket
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r8-r11 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r12
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|12
)braket
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r12-r15 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r16
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|16
)braket
comma
l_int|16
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r16-r31 */
id|scr-&gt;pt.cr_ifs
op_assign
id|cfm
op_or
(paren
l_int|1UL
op_lshift
l_int|63
)paren
suffix:semicolon
multiline_comment|/* establish new instruction pointer: */
id|scr-&gt;pt.cr_iip
op_assign
id|ip
op_amp
op_complement
l_int|0x3UL
suffix:semicolon
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
op_assign
id|ip
op_amp
l_int|0x3
suffix:semicolon
id|scr-&gt;pt.cr_ipsr
op_assign
(paren
id|scr-&gt;pt.cr_ipsr
op_amp
op_complement
id|IA64_PSR_UM
)paren
op_or
(paren
id|um
op_amp
id|IA64_PSR_UM
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_NEW_UNWIND
id|scr-&gt;scratch_unat
op_assign
id|ia64_put_scratch_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
id|nat
)paren
suffix:semicolon
macro_line|#else
id|ia64_put_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
op_amp
id|scr-&gt;sw
comma
id|nat
)paren
suffix:semicolon
multiline_comment|/* restore the original scratch NaT bits */
macro_line|#endif
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|IA64_SC_FLAG_FPH_VALID
)paren
op_ne
l_int|0
)paren
(brace
r_struct
id|ia64_psr
op_star
id|psr
op_assign
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.fph
comma
op_amp
id|sc-&gt;sc_fr
(braket
l_int|32
)braket
comma
l_int|96
op_star
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psr-&gt;dfh
)paren
(brace
id|psr-&gt;mfh
op_assign
l_int|0
suffix:semicolon
id|__ia64_load_fpu
c_func
(paren
id|current-&gt;thread.fph
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
r_int
DECL|function|copy_siginfo_to_user
id|copy_siginfo_to_user
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_WRITE
comma
id|to
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
r_return
id|__copy_to_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
suffix:semicolon
r_else
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If you change siginfo_t structure, please be sure&n;&t;&t; * this code is fixed accordingly.  It should never&n;&t;&t; * copy any pad contained in the structure to avoid&n;&t;&t; * security leaks, but must copy the generic 3 ints&n;&t;&t; * plus the relevant union member.&n;&t;&t; */
id|err
op_assign
id|__put_user
c_func
(paren
id|from-&gt;si_signo
comma
op_amp
id|to-&gt;si_signo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_errno
comma
op_amp
id|to-&gt;si_errno
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
r_int
)paren
id|from-&gt;si_code
comma
op_amp
id|to-&gt;si_code
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|from-&gt;si_code
op_rshift
l_int|16
)paren
(brace
r_case
id|__SI_FAULT
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_isr
comma
op_amp
id|to-&gt;si_isr
)paren
suffix:semicolon
r_case
id|__SI_POLL
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_addr
comma
op_amp
id|to-&gt;si_addr
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_imm
comma
op_amp
id|to-&gt;si_imm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__SI_CHLD
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_utime
comma
op_amp
id|to-&gt;si_utime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_stime
comma
op_amp
id|to-&gt;si_stime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_status
comma
op_amp
id|to-&gt;si_status
)paren
suffix:semicolon
r_default
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_uid
comma
op_amp
id|to-&gt;si_uid
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_pid
comma
op_amp
id|to-&gt;si_pid
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* case __SI_RT: This is not generated by the kernel as of now.  */
)brace
r_return
id|err
suffix:semicolon
)brace
)brace
r_int
DECL|function|ia64_rt_sigreturn
id|ia64_rt_sigreturn
(paren
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_extern
r_char
id|ia64_strace_leave_kernel
comma
id|ia64_leave_kernel
suffix:semicolon
r_struct
id|sigcontext
op_star
id|sc
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|sc
op_assign
op_amp
(paren
(paren
r_struct
id|sigframe
op_star
)paren
(paren
id|scr-&gt;pt.r12
op_plus
l_int|16
)paren
)paren
op_member_access_from_pointer
id|sc
suffix:semicolon
multiline_comment|/*&n;&t; * When we return to the previously executing context, r8 and&n;&t; * r10 have already been setup the way we want them.  Indeed,&n;&t; * if the signal wasn&squot;t delivered while in a system call, we&n;&t; * must not touch r8 or r10 as otherwise user-level stat could&n;&t; * be corrupted.&n;&t; */
id|retval
op_assign
(paren
r_int
)paren
op_amp
id|ia64_leave_kernel
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYS
)paren
multiline_comment|/*&n;&t;&t; * strace expects to be notified after sigreturn&n;&t;&t; * returns even though the context to which we return&n;&t;&t; * may not be in the middle of a syscall.  Thus, the&n;&t;&t; * return-value that strace displays for sigreturn is&n;&t;&t; * meaningless.&n;&t;&t; */
id|retval
op_assign
(paren
r_int
)paren
op_amp
id|ia64_strace_leave_kernel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
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
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|GET_SIGSET
c_func
(paren
op_amp
id|set
comma
op_amp
id|sc-&gt;sc_mask
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
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
(brace
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
)brace
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
id|restore_sigcontext
c_func
(paren
id|sc
comma
id|scr
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG return (%s:%d): sp=%lx ip=%lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|scr-&gt;pt.r12
comma
id|scr-&gt;pt.cr_iip
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * It is more difficult to avoid calling this function than to&n;&t; * call it and ignore errors.&n;&t; */
id|do_sigaltstack
c_func
(paren
op_amp
id|sc-&gt;sc_stack
comma
l_int|0
comma
id|scr-&gt;pt.r12
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|give_sigsegv
suffix:colon
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|SI_KERNEL
suffix:semicolon
id|si.si_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|si.si_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|si.si_addr
op_assign
id|sc
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * This does just the minimum required setup of sigcontext.&n; * Specifically, it only installs data that is either not knowable at&n; * the user-level or that gets modified before execution in the&n; * trampoline starts.  Everything else is done at the user-level.&n; */
r_static
r_int
DECL|function|setup_sigcontext
id|setup_sigcontext
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
id|sigset_t
op_star
id|mask
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
comma
id|ifs
comma
id|nat
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ifs
op_assign
id|scr-&gt;pt.cr_ifs
suffix:semicolon
r_if
c_cond
(paren
id|on_sig_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|sc
)paren
)paren
id|flags
op_or_assign
id|IA64_SC_FLAG_ONSTACK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ifs
op_amp
(paren
l_int|1UL
op_lshift
l_int|63
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* if cr_ifs isn&squot;t valid, we got here through a syscall */
id|flags
op_or_assign
id|IA64_SC_FLAG_IN_SYSCALL
suffix:semicolon
)brace
id|ia64_flush_fph
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_FPH_VALID
)paren
)paren
(brace
id|flags
op_or_assign
id|IA64_SC_FLAG_FPH_VALID
suffix:semicolon
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_fr
(braket
l_int|32
)braket
comma
id|current-&gt;thread.fph
comma
l_int|96
op_star
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Note: sw-&gt;ar_unat is UNDEFINED unless the process is being&n;&t; * PTRACED.  However, this is OK because the NaT bits of the&n;&t; * preserved registers (r4-r7) are never being looked at by&n;&t; * the signal handler (registers r4-r7 are used instead).&n;&t; */
macro_line|#ifdef CONFIG_IA64_NEW_UNWIND
id|nat
op_assign
id|ia64_get_scratch_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
id|scr-&gt;scratch_unat
)paren
suffix:semicolon
macro_line|#else
id|nat
op_assign
id|ia64_get_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
op_amp
id|scr-&gt;sw
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|__put_user
c_func
(paren
id|flags
comma
op_amp
id|sc-&gt;sc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|nat
comma
op_amp
id|sc-&gt;sc_nat
)paren
suffix:semicolon
id|err
op_or_assign
id|PUT_SIGSET
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;sc_mask
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.cr_ipsr
op_amp
id|IA64_PSR_UM
comma
op_amp
id|sc-&gt;sc_um
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_rsc
comma
op_amp
id|sc-&gt;sc_ar_rsc
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_ccv
comma
op_amp
id|sc-&gt;sc_ar_ccv
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_unat
comma
op_amp
id|sc-&gt;sc_ar_unat
)paren
suffix:semicolon
multiline_comment|/* ar.unat */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_fpsr
comma
op_amp
id|sc-&gt;sc_ar_fpsr
)paren
suffix:semicolon
multiline_comment|/* ar.fpsr */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_pfs
comma
op_amp
id|sc-&gt;sc_ar_pfs
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.pr
comma
op_amp
id|sc-&gt;sc_pr
)paren
suffix:semicolon
multiline_comment|/* predicates */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b0
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* b0 (rp) */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b6
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* b6 */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b7
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* b7 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|1
)braket
comma
op_amp
id|scr-&gt;pt.r1
comma
l_int|3
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r1-r3 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|8
)braket
comma
op_amp
id|scr-&gt;pt.r8
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r8-r11 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|12
)braket
comma
op_amp
id|scr-&gt;pt.r12
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r12-r15 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|16
)braket
comma
op_amp
id|scr-&gt;pt.r16
comma
l_int|16
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r16-r31 */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.cr_iip
op_plus
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
comma
op_amp
id|sc-&gt;sc_ip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|setup_frame
id|setup_frame
(paren
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
id|set
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_extern
r_char
id|ia64_sigtramp
(braket
)braket
comma
id|__start_gate_section
(braket
)braket
suffix:semicolon
r_int
r_int
id|tramp_addr
comma
id|new_rbs
op_assign
l_int|0
suffix:semicolon
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
r_int
id|err
suffix:semicolon
id|frame
op_assign
(paren
r_void
op_star
)paren
id|scr-&gt;pt.r12
suffix:semicolon
id|tramp_addr
op_assign
id|GATE_ADDR
op_plus
(paren
id|ia64_sigtramp
op_minus
id|__start_gate_section
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_ne
l_int|0
op_logical_and
op_logical_neg
id|on_sig_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
)paren
(brace
id|new_rbs
op_assign
(paren
id|current-&gt;sas_ss_sp
op_plus
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|frame
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
)paren
op_amp
op_complement
(paren
id|STACK_ALIGN
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
id|frame
op_assign
(paren
r_void
op_star
)paren
id|frame
op_minus
(paren
(paren
r_sizeof
(paren
op_star
id|frame
)paren
op_plus
id|STACK_ALIGN
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|STACK_ALIGN
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
id|give_sigsegv
suffix:semicolon
id|err
op_assign
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
id|info
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|frame-&gt;sc.sc_stack.ss_sp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|frame-&gt;sc.sc_stack.ss_size
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|scr-&gt;pt.r12
)paren
comma
op_amp
id|frame-&gt;sc.sc_stack.ss_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
id|set
comma
id|scr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
id|scr-&gt;pt.r12
op_assign
(paren
r_int
r_int
)paren
id|frame
op_minus
l_int|16
suffix:semicolon
multiline_comment|/* new stack pointer */
id|scr-&gt;pt.r2
op_assign
id|sig
suffix:semicolon
multiline_comment|/* signal number */
id|scr-&gt;pt.r3
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
multiline_comment|/* addr. of handler&squot;s proc desc */
id|scr-&gt;pt.r15
op_assign
id|new_rbs
suffix:semicolon
id|scr-&gt;pt.ar_fpsr
op_assign
id|FPSR_DEFAULT
suffix:semicolon
multiline_comment|/* reset fpsr for signal handler */
id|scr-&gt;pt.cr_iip
op_assign
id|tramp_addr
suffix:semicolon
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start executing in first slot */
macro_line|#ifdef CONFIG_IA64_NEW_UNWIND
multiline_comment|/*&n;&t; * Note: this affects only the NaT bits of the scratch regs&n;&t; * (the ones saved in pt_regs), which is exactly what we want.&n;&t; */
id|scr-&gt;scratch_unat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ensure NaT bits of at least r2, r3, r12, and r15 are clear */
macro_line|#else
multiline_comment|/*&n;&t; * Note: this affects only the NaT bits of the scratch regs&n;&t; * (the ones saved in pt_regs), which is exactly what we want.&n;&t; * The NaT bits for the preserved regs (r4-r7) are in&n;&t; * sw-&gt;ar_unat iff this process is being PTRACED.&n;&t; */
id|scr-&gt;sw.caller_unat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ensure NaT bits of at least r2, r3, r12, and r15 are clear */
macro_line|#endif
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver (%s:%d): sig=%d sp=%lx ip=%lx handler=%lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sig
comma
id|scr-&gt;pt.r12
comma
id|scr-&gt;pt.cr_iip
comma
id|scr-&gt;pt.r3
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
id|give_sigsegv
suffix:colon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|SI_KERNEL
suffix:semicolon
id|si.si_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|si.si_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|si.si_addr
op_assign
id|frame
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|handle_signal
id|handle_signal
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
id|sigscratch
op_star
id|scr
)paren
(brace
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
multiline_comment|/* send signal to IA-32 process */
r_if
c_cond
(paren
op_logical_neg
id|ia32_setup_frame1
c_func
(paren
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
comma
op_amp
id|scr-&gt;pt
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
macro_line|#endif
multiline_comment|/* send signal to IA-64 process */
r_if
c_cond
(paren
op_logical_neg
id|setup_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
comma
id|scr
)paren
)paren
r_return
l_int|0
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
(brace
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
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that `init&squot; is a special process: it doesn&squot;t get signals it&n; * doesn&squot;t want to handle.  Thus you cannot kill init even with a&n; * SIGKILL even by mistake.&n; *&n; * Note that we go through the signals twice: once to check the&n; * signals that the kernel can handle, and then we build all the&n; * user-level signal handling stack-frames in one go after that.&n; */
r_int
DECL|function|ia64_do_signal
id|ia64_do_signal
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|sigscratch
op_star
id|scr
comma
r_int
id|in_syscall
)paren
(brace
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
id|restart
op_assign
id|in_syscall
suffix:semicolon
r_int
id|errno
op_assign
id|scr-&gt;pt.r8
suffix:semicolon
multiline_comment|/*&n;&t; * In the ia64_leave_kernel code path, we want the common case&n;&t; * to go fast, which is why we may in certain cases get here&n;&t; * from kernel mode. Just return without doing anything if so.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
r_return
l_int|0
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
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
r_if
c_cond
(paren
id|in_syscall
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ge
l_int|0
)paren
id|restart
op_assign
l_int|0
suffix:semicolon
r_else
id|errno
op_assign
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|scr-&gt;pt.r10
op_ne
op_minus
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * A system calls has to be restarted only if one of&n;&t;&t; * the error codes ERESTARTNOHAND, ERESTARTSYS, or&n;&t;&t; * ERESTARTNOINTR is returned.  If r10 isn&squot;t -1 then&n;&t;&t; * r8 doesn&squot;t hold an error code and we don&squot;t need to&n;&t;&t; * restart the syscall, so we set in_syscall to zero.&n;&t;&t; */
id|restart
op_assign
l_int|0
suffix:semicolon
)brace
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
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
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
id|current-&gt;thread.siginfo
op_assign
op_amp
id|info
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
id|signr
op_assign
id|current-&gt;exit_code
suffix:semicolon
id|current-&gt;thread.siginfo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We&squot;re back.  Did the debugger cancel the sig?  */
r_if
c_cond
(paren
op_logical_neg
id|signr
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
r_case
id|SIGBUS
suffix:colon
r_case
id|SIGSYS
suffix:colon
r_case
id|SIGXCPU
suffix:colon
r_case
id|SIGXFSZ
suffix:colon
r_if
c_cond
(paren
id|do_coredump
c_func
(paren
id|signr
comma
op_amp
id|scr-&gt;pt
)paren
)paren
id|exit_code
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_default
suffix:colon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|signr
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
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
r_if
c_cond
(paren
id|restart
)paren
(brace
r_switch
c_cond
(paren
id|errno
)paren
(brace
r_case
id|ERESTARTSYS
suffix:colon
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
op_eq
l_int|0
)paren
(brace
r_case
id|ERESTARTNOHAND
suffix:colon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
id|scr-&gt;pt.r8
op_assign
op_minus
id|EINTR
suffix:semicolon
r_else
macro_line|#endif
id|scr-&gt;pt.r8
op_assign
id|EINTR
suffix:semicolon
multiline_comment|/* note: scr-&gt;pt.r10 is already -1 */
r_break
suffix:semicolon
)brace
r_case
id|ERESTARTNOINTR
suffix:colon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
id|scr-&gt;pt.r8
op_assign
id|scr-&gt;pt.r1
suffix:semicolon
id|scr-&gt;pt.cr_iip
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
macro_line|#endif
id|ia64_decrement_ip
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Whee!  Actually deliver the signal.  If the&n;&t;&t;   delivery failed, we need to continue to iterate in&n;&t;&t;   this loop so we can deliver the SIGSEGV... */
r_if
c_cond
(paren
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
id|scr
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|restart
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|errno
op_eq
id|ERESTARTNOHAND
op_logical_or
id|errno
op_eq
id|ERESTARTSYS
op_logical_or
id|errno
op_eq
id|ERESTARTNOINTR
)paren
(brace
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
id|scr-&gt;pt.r8
op_assign
id|scr-&gt;pt.r1
suffix:semicolon
id|scr-&gt;pt.cr_iip
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t; * Note: the syscall number is in r15 which is&n;&t;&t;&t; * saved in pt_regs so all we need to do here&n;&t;&t;&t; * is adjust ip so that the &quot;break&quot;&n;&t;&t;&t; * instruction gets re-executed.&n;&t;&t;&t; */
id|ia64_decrement_ip
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
