multiline_comment|/*&n; *  linux/arch/mips/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Copyright (C) 1994, 1995, 1996  Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
id|asmlinkage
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
r_extern
id|asmlinkage
r_void
(paren
op_star
id|save_fp_context
)paren
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
(paren
op_star
id|restore_fp_context
)paren
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; * Unlike on Intel we pass a sigset_t *, not sigset_t.&n; */
DECL|function|sys_sigsuspend
id|asmlinkage
r_int
id|sys_sigsuspend
c_func
(paren
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
id|sigset_t
op_star
id|uset
comma
id|set
suffix:semicolon
id|uset
op_assign
(paren
id|sigset_t
op_star
)paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|set
comma
id|uset
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
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
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|2
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
r_return
op_minus
id|EINTR
suffix:semicolon
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
id|sigcontext
op_star
id|context
suffix:semicolon
r_int
id|i
suffix:semicolon
id|context
op_assign
(paren
r_struct
id|sigcontext
op_star
)paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
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
id|context
comma
r_sizeof
(paren
r_struct
id|sigcontext
)paren
)paren
op_logical_or
(paren
id|regs-&gt;regs
(braket
l_int|29
)braket
op_amp
(paren
id|SZREG
op_minus
l_int|1
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|current-&gt;blocked
op_assign
id|context-&gt;sc_sigset
op_amp
id|_BLOCKABLE
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|context-&gt;sc_pc
suffix:semicolon
multiline_comment|/*&n;&t; * We only allow user processes in 64bit mode (n32, 64 bit ABI) to&n;&t; * restore the upper half of registers.&n;&t; */
r_if
c_cond
(paren
id|read_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
)paren
op_amp
id|ST0_UX
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|__get_user
c_func
(paren
id|regs-&gt;regs
(braket
id|i
)braket
comma
op_amp
id|context-&gt;sc_regs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|__get_user
c_func
(paren
id|regs-&gt;regs
(braket
id|i
)braket
comma
op_amp
id|context-&gt;sc_regs
(braket
id|i
)braket
)paren
suffix:semicolon
id|regs-&gt;regs
(braket
id|i
)braket
op_assign
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|i
)braket
suffix:semicolon
)brace
id|__get_user
c_func
(paren
id|regs-&gt;hi
comma
op_amp
id|context-&gt;sc_mdhi
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;lo
comma
op_amp
id|context-&gt;sc_mdlo
)paren
suffix:semicolon
id|restore_fp_context
c_func
(paren
id|context
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable syscall checks&n;&t; */
id|regs-&gt;orig_reg2
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t let your children do this ...&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$29,%0&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;tret_from_sys_call&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs
)paren
)paren
suffix:semicolon
multiline_comment|/* Unreached */
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame...&n; *&n; * This routine is somewhat complicated by the fact that if the kernel may be&n; * entered by an exception other than a system call; e.g. a bus error or other&n; * &quot;bad&quot; exception.  If this is the case, then *all* the context on the kernel&n; * stack frame must be saved.&n; *&n; * For a large number of exceptions, the stack frame format is the same&n; * as that which will be created when the process traps back to the kernel&n; * when finished executing the signal handler.&t;In this case, nothing&n; * must be done. This information is saved on the user stack and restored&n; * when the signal handler is returned.&n; *&n; * The signal handler will be called with ra pointing to code1 (see below) and&n; * one parameters in a0 (signum).&n; *&n; *     usp -&gt;  [unused]                         ; first free word on stack&n; *             arg save space                   ; 16/32 bytes arg. save space&n; *&t;       code1   (addiu sp,#1-offset)&t;; pop stackframe&n; *&t;       code2   (li v0,__NR_sigreturn)&t;; syscall number&n; *&t;       code3   (syscall)&t;&t;; do sigreturn(2)&n; *     #1|     $0, at, v0, v1, a0, a1, a2, a3   ; All integer registers&n; *       |     t0, t1, t2, t3, t4, t5, t6, t7   ; $0, k0 and k1 are placeholders&n; *       |     s0, s1, s2, s3, s4, s5, s6, s7&n; *       |     k0, k1, t8, t9, gp, sp, fp, ra;&n; *       |     epc                              ; old program counter&n; *       |     cause                            ; CP0 cause register&n; *       |     oldmask&n; */
DECL|struct|sc
r_struct
id|sc
(brace
DECL|member|ass
r_int
r_int
id|ass
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|code
r_int
r_int
id|code
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|scc
r_struct
id|sigcontext
id|scc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|scc_offset
mdefine_line|#define scc_offset ((size_t)&amp;((struct sc *)0)-&gt;scc)
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
r_struct
id|sc
op_star
id|frame
suffix:semicolon
r_struct
id|sigcontext
op_star
id|sc
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Align the stackframe to an adequate boundary for the architecture. */
id|frame
op_assign
(paren
r_struct
id|sc
op_star
)paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
suffix:semicolon
id|frame
op_decrement
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sc
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|frame
op_amp
id|ALMASK
)paren
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
id|segv_and_exit
suffix:semicolon
id|sc
op_assign
op_amp
id|frame-&gt;scc
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the return code ...&n;&t; *&n;&t; *         .set    noreorder&n;&t; *         addiu   sp,24&n;&t; *         li      v0,__NR_sigreturn&n;&t; *         syscall&n;&t; *         .set    reorder&n;&t; */
id|__put_user
c_func
(paren
l_int|0x27bd0000
op_plus
id|scc_offset
comma
op_amp
id|frame-&gt;code
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
l_int|0x24020000
op_plus
id|__NR_sigreturn
comma
op_amp
id|frame-&gt;code
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
l_int|0x0000000c
comma
op_amp
id|frame-&gt;code
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flush caches so that the instructions will be correctly executed.&n;&t; */
id|flush_cache_sigtramp
c_func
(paren
(paren
r_int
r_int
)paren
id|frame-&gt;code
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the &quot;normal&quot; sigcontext&n;&t; */
id|__put_user
c_func
(paren
id|regs-&gt;cp0_epc
comma
op_amp
id|sc-&gt;sc_pc
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|regs-&gt;cp0_status
comma
op_amp
id|sc-&gt;sc_status
)paren
suffix:semicolon
multiline_comment|/* Status register */
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|__put_user
c_func
(paren
id|regs-&gt;regs
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;sc_regs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|save_fp_context
c_func
(paren
id|sc
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|regs-&gt;hi
comma
op_amp
id|sc-&gt;sc_mdhi
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|regs-&gt;lo
comma
op_amp
id|sc-&gt;sc_mdlo
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|regs-&gt;cp0_cause
comma
op_amp
id|sc-&gt;sc_cause
)paren
suffix:semicolon
id|__put_user
c_func
(paren
(paren
id|regs-&gt;cp0_status
op_amp
id|ST0_CU1
)paren
op_ne
l_int|0
comma
op_amp
id|sc-&gt;sc_ownedfp
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|oldmask
comma
op_amp
id|sc-&gt;sc_sigset
)paren
suffix:semicolon
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;__pad0
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;__pad0
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;__pad0
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|4
)braket
op_assign
id|signr
suffix:semicolon
multiline_comment|/* Arguments for handler */
id|regs-&gt;regs
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* For now. */
id|regs-&gt;regs
(braket
l_int|6
)braket
op_assign
(paren
r_int
)paren
id|frame
suffix:semicolon
multiline_comment|/* Pointer to sigcontext */
id|regs-&gt;regs
(braket
l_int|29
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
multiline_comment|/* Stack pointer */
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;code
suffix:semicolon
multiline_comment|/* Return address */
id|regs-&gt;cp0_epc
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
suffix:semicolon
multiline_comment|/* &quot;return&quot; to the first handler */
id|regs-&gt;regs
(braket
l_int|25
)braket
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
multiline_comment|/* PIC shit... */
r_return
suffix:semicolon
id|segv_and_exit
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|handle_signal
r_static
r_inline
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_NOMASK
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
id|current-&gt;blocked
op_or_assign
(paren
id|sa-&gt;sa_mask
op_or
id|_S
c_func
(paren
id|signr
)paren
)paren
op_amp
id|_BLOCKABLE
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|syscall_restart
r_static
r_inline
r_void
id|syscall_restart
c_func
(paren
r_int
r_int
id|r0
comma
r_int
r_int
id|or2
comma
r_int
r_int
id|or7
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigaction
op_star
id|sa
)paren
(brace
r_switch
c_cond
(paren
id|r0
)paren
(brace
r_case
id|ERESTARTNOHAND
suffix:colon
id|no_system_call_restart
suffix:colon
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
r_case
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
r_goto
id|no_system_call_restart
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_case
id|ERESTARTNOINTR
suffix:colon
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|or2
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|7
)braket
op_assign
id|or7
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|8
suffix:semicolon
)brace
)brace
r_extern
r_int
id|do_irix_signal
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
comma
id|r0
op_assign
id|regs-&gt;regs
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|r7
op_assign
id|regs-&gt;orig_reg7
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
suffix:semicolon
macro_line|#ifdef CONFIG_BINFMT_IRIX
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_LINUX
)paren
(brace
r_return
id|do_irix_signal
c_func
(paren
id|oldmask
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|signr
op_assign
id|ffz
c_func
(paren
op_complement
id|signr
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|signr
comma
op_amp
id|current-&gt;signal
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
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;signal
op_or_assign
id|_S
c_func
(paren
id|signr
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
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
r_case
id|SIGSTOP
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
r_case
id|SIGBUS
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
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
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_SIGNALED
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 8-( */
id|do_exit
c_func
(paren
id|signr
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * OK, we&squot;re invoking a handler&n;&t;&t; */
r_if
c_cond
(paren
id|r0
)paren
(brace
id|syscall_restart
c_func
(paren
id|r0
comma
id|regs-&gt;orig_reg2
comma
id|r7
comma
id|regs
comma
id|sa
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t; * Who&squot;s code doesn&squot;t conform to the restartable syscall convention&n;&t; * dies here!!!  The li instruction, a single machine instruction,&n;&t; * must directly be followed by the syscall instruction.&n;&t; */
r_if
c_cond
(paren
id|r0
op_logical_and
(paren
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTSYS
op_logical_or
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTNOINTR
)paren
)paren
(brace
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|regs-&gt;orig_reg2
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|7
)braket
op_assign
id|r7
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The signal(2) syscall is no longer available in the kernel&n; * because GNU libc doesn&squot;t use it.  Maybe I&squot;ll add it back to the&n; * kernel for the binary compatibility stuff.&n; */
DECL|function|sys_signal
id|asmlinkage
r_int
r_int
id|sys_signal
c_func
(paren
r_int
id|signum
comma
id|__sighandler_t
id|handler
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
