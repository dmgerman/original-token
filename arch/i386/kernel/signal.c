multiline_comment|/*&n; *  linux/arch/i386/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
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
suffix:semicolon
multiline_comment|/*&n; * atomically swap in the new signal mask, and wait for a signal.&n; */
DECL|function|sys_sigsuspend
id|asmlinkage
r_int
id|sys_sigsuspend
c_func
(paren
r_int
id|restart
comma
r_int
r_int
id|oldmask
comma
r_int
r_int
id|set
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
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
id|restart
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
id|regs-&gt;eax
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
multiline_comment|/*&n; * FIXME. We don&squot;t currently restore emulator state&n; */
DECL|macro|restore_i387_soft
mdefine_line|#define restore_i387_soft(x) do { } while (0)
DECL|function|restore_i387_hard
r_static
r_inline
r_void
id|restore_i387_hard
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
(brace
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|current
op_eq
id|last_task_used_math
)paren
(brace
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|current-&gt;tss.i387.hard
comma
id|buf
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
suffix:semicolon
)brace
DECL|function|restore_i387
r_static
r_void
id|restore_i387
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
(brace
macro_line|#ifndef CONFIG_MATH_EMULATION
id|restore_i387_hard
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|hard_math
)paren
(brace
id|restore_i387_hard
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|restore_i387_soft
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
multiline_comment|/*&n; * This sets regs-&gt;esp even though we don&squot;t actually use sigstacks yet..&n; */
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_int
r_int
id|__unused
)paren
(brace
DECL|macro|COPY
mdefine_line|#define COPY(x) regs-&gt;x = context.x
DECL|macro|COPY_SEG
mdefine_line|#define COPY_SEG(x) &bslash;&n;if ((context.x &amp; 0xfffc) &amp;&amp; (context.x &amp; 3) != 3) goto badframe; COPY(x);
DECL|macro|COPY_SEG_STRICT
mdefine_line|#define COPY_SEG_STRICT(x) &bslash;&n;if (!(context.x &amp; 0xfffc) || (context.x &amp; 3) != 3) goto badframe; COPY(x);
r_struct
id|sigcontext_struct
id|context
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|__unused
suffix:semicolon
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
id|regs-&gt;esp
comma
r_sizeof
(paren
id|context
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|context
comma
(paren
r_void
op_star
)paren
id|regs-&gt;esp
comma
r_sizeof
(paren
id|context
)paren
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|context.oldmask
op_amp
id|_BLOCKABLE
suffix:semicolon
id|COPY_SEG
c_func
(paren
id|ds
)paren
suffix:semicolon
id|COPY_SEG
c_func
(paren
id|es
)paren
suffix:semicolon
id|COPY_SEG
c_func
(paren
id|fs
)paren
suffix:semicolon
id|COPY_SEG
c_func
(paren
id|gs
)paren
suffix:semicolon
id|COPY_SEG_STRICT
c_func
(paren
id|ss
)paren
suffix:semicolon
id|COPY_SEG_STRICT
c_func
(paren
id|cs
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|eip
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ecx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|edx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ebx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|esp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ebp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|edi
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|esi
)paren
suffix:semicolon
id|regs-&gt;eflags
op_and_assign
op_complement
l_int|0x40DD5
suffix:semicolon
id|regs-&gt;eflags
op_or_assign
id|context.eflags
op_amp
l_int|0x40DD5
suffix:semicolon
id|regs-&gt;orig_eax
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* disable syscall checks */
r_if
c_cond
(paren
id|context.fpstate
)paren
(brace
r_struct
id|_fpstate
op_star
id|buf
op_assign
id|context.fpstate
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|restore_i387
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
id|context.eax
suffix:semicolon
id|badframe
suffix:colon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME. We currently don&squot;t save 387 state if we use emulation&n; */
DECL|macro|save_i387_soft
mdefine_line|#define save_i387_soft(x) NULL
DECL|function|save_i387_hard
r_static
r_inline
r_struct
id|_fpstate
op_star
id|save_i387_hard
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
(brace
macro_line|#ifdef __SMP__
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;fnsave %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|current-&gt;tss.i387.hard
)paren
)paren
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|current
op_eq
id|last_task_used_math
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;fnsave %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|current-&gt;tss.i387.hard
)paren
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;fwait&quot;
)paren
suffix:semicolon
multiline_comment|/* not needed on 486+ */
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|current-&gt;tss.i387.hard.status
op_assign
id|current-&gt;tss.i387.hard.swd
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
op_amp
id|current-&gt;tss.i387.hard
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|save_i387
r_static
r_struct
id|_fpstate
op_star
id|save_i387
c_func
(paren
r_struct
id|_fpstate
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#ifndef CONFIG_MATH_EMULATION
r_return
id|save_i387_hard
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|hard_math
)paren
r_return
id|save_i387_hard
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|save_i387_soft
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Set up a signal frame... Make the stack look the way iBCS2 expects&n; * it to look.&n; */
DECL|function|setup_frame
r_static
r_void
id|setup_frame
c_func
(paren
r_struct
id|sigaction
op_star
id|sa
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|signr
comma
r_int
r_int
id|oldmask
)paren
(brace
r_int
r_int
op_star
id|frame
suffix:semicolon
id|frame
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;esp
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;ss
op_ne
id|USER_DS
op_logical_and
id|sa-&gt;sa_restorer
)paren
id|frame
op_assign
(paren
r_int
r_int
op_star
)paren
id|sa-&gt;sa_restorer
suffix:semicolon
id|frame
op_sub_assign
l_int|64
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
l_int|64
op_star
l_int|4
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
multiline_comment|/* set up the &quot;normal&quot; stack seen by the signal handler (iBCS2) */
DECL|macro|__CODE
mdefine_line|#define __CODE ((unsigned long)(frame+24))
DECL|macro|CODE
mdefine_line|#define CODE(x) ((unsigned long *) ((x)+__CODE))
id|put_user
c_func
(paren
id|__CODE
comma
id|frame
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;signal_invmap
)paren
id|put_user
c_func
(paren
id|current-&gt;exec_domain-&gt;signal_invmap
(braket
id|signr
)braket
comma
id|frame
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|put_user
c_func
(paren
id|signr
comma
id|frame
op_plus
l_int|1
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;gs
comma
id|frame
op_plus
l_int|2
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;fs
comma
id|frame
op_plus
l_int|3
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;es
comma
id|frame
op_plus
l_int|4
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;ds
comma
id|frame
op_plus
l_int|5
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;edi
comma
id|frame
op_plus
l_int|6
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;esi
comma
id|frame
op_plus
l_int|7
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;ebp
comma
id|frame
op_plus
l_int|8
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;esp
comma
id|frame
op_plus
l_int|9
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;ebx
comma
id|frame
op_plus
l_int|10
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;edx
comma
id|frame
op_plus
l_int|11
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;ecx
comma
id|frame
op_plus
l_int|12
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;eax
comma
id|frame
op_plus
l_int|13
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|current-&gt;tss.trap_no
comma
id|frame
op_plus
l_int|14
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|current-&gt;tss.error_code
comma
id|frame
op_plus
l_int|15
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;eip
comma
id|frame
op_plus
l_int|16
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;cs
comma
id|frame
op_plus
l_int|17
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;eflags
comma
id|frame
op_plus
l_int|18
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;esp
comma
id|frame
op_plus
l_int|19
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|regs-&gt;ss
comma
id|frame
op_plus
l_int|20
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|save_i387
c_func
(paren
(paren
r_struct
id|_fpstate
op_star
)paren
(paren
id|frame
op_plus
l_int|32
)paren
)paren
comma
id|frame
op_plus
l_int|21
)paren
suffix:semicolon
multiline_comment|/* non-iBCS2 extensions.. */
id|put_user
c_func
(paren
id|oldmask
comma
id|frame
op_plus
l_int|22
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|current-&gt;tss.cr2
comma
id|frame
op_plus
l_int|23
)paren
suffix:semicolon
multiline_comment|/* set up the return code... */
id|put_user
c_func
(paren
l_int|0x0000b858
comma
id|CODE
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* popl %eax ; movl $,%eax */
id|put_user
c_func
(paren
l_int|0x80cd0000
comma
id|CODE
c_func
(paren
l_int|4
)paren
)paren
suffix:semicolon
multiline_comment|/* int $0x80 */
id|put_user
c_func
(paren
id|__NR_sigreturn
comma
id|CODE
c_func
(paren
l_int|2
)paren
)paren
suffix:semicolon
DECL|macro|__CODE
macro_line|#undef __CODE
DECL|macro|CODE
macro_line|#undef CODE
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;esp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;eip
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
suffix:semicolon
id|regs-&gt;cs
op_assign
id|USER_CS
suffix:semicolon
id|regs-&gt;ss
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;ds
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;es
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;gs
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;fs
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
)brace
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
DECL|function|handle_signal
r_static
r_void
id|handle_signal
c_func
(paren
r_int
r_int
id|signr
comma
r_struct
id|sigaction
op_star
id|sa
comma
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
multiline_comment|/* are we from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_eax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;eax
)paren
(brace
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;eax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ERESTARTSYS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_RESTART
)paren
)paren
(brace
id|regs-&gt;eax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_case
op_minus
id|ERESTARTNOINTR
suffix:colon
id|regs-&gt;eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|regs-&gt;eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* set up the stack frame */
id|setup_frame
c_func
(paren
id|sa
comma
id|regs
comma
id|signr
comma
id|oldmask
)paren
suffix:semicolon
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
id|current-&gt;blocked
op_or_assign
id|sa-&gt;sa_mask
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
id|signr
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
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
multiline_comment|/*&n;&t;&t; *&t;This stops gcc flipping out. Otherwise the assembler&n;&t;&t; *&t;including volatiles for the inline function to get&n;&t;&t; *&t;current combined with this gets it confused.&n;&t;&t; */
r_struct
id|task_struct
op_star
id|t
op_assign
id|current
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;bsf %3,%1&bslash;n&bslash;t&quot;
l_string|&quot;btrl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|t-&gt;signal
)paren
comma
l_string|&quot;=r&quot;
(paren
id|signr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|t-&gt;signal
)paren
comma
l_string|&quot;1&quot;
(paren
id|signr
)paren
)paren
suffix:semicolon
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
id|SIGABRT
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
id|current-&gt;flags
op_or_assign
id|PF_SIGNALED
suffix:semicolon
id|do_exit
c_func
(paren
id|signr
)paren
suffix:semicolon
)brace
)brace
id|handle_signal
c_func
(paren
id|signr
comma
id|sa
comma
id|oldmask
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_eax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|regs-&gt;eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
