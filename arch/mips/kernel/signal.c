multiline_comment|/*&n; *  linux/arch/mips/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
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
id|regs-&gt;reg2
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
multiline_comment|/*&n; * This sets regs-&gt;reg29 even though we don&squot;t actually use sigstacks yet..&n; */
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
id|context
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t support fixing ADEL/ADES exceptions for signal stack frames.&n;&t; * No big loss - who doesn&squot;t care about the alignment of this stack&n;&t; * really deserves to loose.&n;&t; */
id|context
op_assign
(paren
r_struct
id|sigcontext_struct
op_star
)paren
id|regs-&gt;reg29
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|context
comma
r_sizeof
(paren
r_struct
id|sigcontext_struct
)paren
)paren
op_logical_or
(paren
id|regs-&gt;reg29
op_amp
l_int|3
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|current-&gt;blocked
op_assign
id|context-&gt;sc_oldmask
op_amp
id|_BLOCKABLE
suffix:semicolon
id|regs-&gt;reg1
op_assign
id|context-&gt;sc_at
suffix:semicolon
id|regs-&gt;reg2
op_assign
id|context-&gt;sc_v0
suffix:semicolon
id|regs-&gt;reg3
op_assign
id|context-&gt;sc_v1
suffix:semicolon
id|regs-&gt;reg4
op_assign
id|context-&gt;sc_a0
suffix:semicolon
id|regs-&gt;reg5
op_assign
id|context-&gt;sc_a1
suffix:semicolon
id|regs-&gt;reg6
op_assign
id|context-&gt;sc_a2
suffix:semicolon
id|regs-&gt;reg7
op_assign
id|context-&gt;sc_a3
suffix:semicolon
id|regs-&gt;reg8
op_assign
id|context-&gt;sc_t0
suffix:semicolon
id|regs-&gt;reg9
op_assign
id|context-&gt;sc_t1
suffix:semicolon
id|regs-&gt;reg10
op_assign
id|context-&gt;sc_t2
suffix:semicolon
id|regs-&gt;reg11
op_assign
id|context-&gt;sc_t3
suffix:semicolon
id|regs-&gt;reg12
op_assign
id|context-&gt;sc_t4
suffix:semicolon
id|regs-&gt;reg13
op_assign
id|context-&gt;sc_t5
suffix:semicolon
id|regs-&gt;reg14
op_assign
id|context-&gt;sc_t6
suffix:semicolon
id|regs-&gt;reg15
op_assign
id|context-&gt;sc_t7
suffix:semicolon
id|regs-&gt;reg16
op_assign
id|context-&gt;sc_s0
suffix:semicolon
id|regs-&gt;reg17
op_assign
id|context-&gt;sc_s1
suffix:semicolon
id|regs-&gt;reg18
op_assign
id|context-&gt;sc_s2
suffix:semicolon
id|regs-&gt;reg19
op_assign
id|context-&gt;sc_s3
suffix:semicolon
id|regs-&gt;reg20
op_assign
id|context-&gt;sc_s4
suffix:semicolon
id|regs-&gt;reg21
op_assign
id|context-&gt;sc_s5
suffix:semicolon
id|regs-&gt;reg22
op_assign
id|context-&gt;sc_s6
suffix:semicolon
id|regs-&gt;reg23
op_assign
id|context-&gt;sc_s7
suffix:semicolon
id|regs-&gt;reg24
op_assign
id|context-&gt;sc_t8
suffix:semicolon
id|regs-&gt;reg25
op_assign
id|context-&gt;sc_t9
suffix:semicolon
multiline_comment|/*&n;&t; * Skip k0/k1&n;&t; */
id|regs-&gt;reg28
op_assign
id|context-&gt;sc_gp
suffix:semicolon
id|regs-&gt;reg29
op_assign
id|context-&gt;sc_sp
suffix:semicolon
id|regs-&gt;reg30
op_assign
id|context-&gt;sc_fp
suffix:semicolon
id|regs-&gt;reg31
op_assign
id|context-&gt;sc_ra
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|context-&gt;sc_epc
suffix:semicolon
id|regs-&gt;cp0_cause
op_assign
id|context-&gt;sc_cause
suffix:semicolon
multiline_comment|/*&n;&t; * disable syscall checks&n;&t; */
id|regs-&gt;orig_reg2
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|context-&gt;sc_v0
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
multiline_comment|/*&n; * Set up a signal frame...&n; *&n; * This routine is somewhat complicated by the fact that if the kernel may be&n; * entered by an exception other than a system call; e.g. a bus error or other&n; * &quot;bad&quot; exception.  If this is the case, then *all* the context on the kernel&n; * stack frame must be saved.&n; *&n; * For a large number of exceptions, the stack frame format is the same&n; * as that which will be created when the process traps back to the kernel&n; * when finished executing the signal handler.&t;In this case, nothing&n; * must be done. This information is saved on the user stack and restored&n; * when the signal handler is returned.&n; *&n; * The signal handler will be called with ra pointing to code1 (see below) and&n; * one parameters in a0 (signum).&n; *&n; *     usp -&gt;  [unused]                         ; first free word on stack&n; *             arg save space                   ; 16 bytes argument save space&n; *&t;       code1   (addiu sp,#1-offset)&t;; syscall number&n; *&t;       code2   (li v0,__NR_sigreturn)&t;; syscall number&n; *&t;       code3   (syscall)&t;&t;; do sigreturn(2)&n; *     #1|     at, v0, v1, a0, a1, a2, a3       ; All integer registers&n; *       |     t0, t1, t2, t3, t4, t5, t6, t7   ; except zero, k0 and k1&n; *       |     s0, s1, s2, s3, s4, s5, s6, s7&n; *       |     t8, t9, gp, sp, fp, ra;&n; *       |     epc                              ; old program counter&n; *       |     cause                            ; CP0 cause register&n; *       |     oldmask&n; */
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
id|sigcontext_struct
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
id|sc
op_star
op_star
id|fp
comma
r_int
r_int
id|pc
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
id|frame
op_assign
op_star
id|fp
suffix:semicolon
id|frame
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t support fixing ADEL/ADES exceptions for signal stack frames.&n;&t; * No big loss - who doesn&squot;t care about the alignment of this stack&n;&t; * really deserves to loose.&n;&t; */
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
r_struct
id|sc
)paren
)paren
op_logical_or
(paren
(paren
r_int
r_int
)paren
id|frame
op_amp
l_int|3
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the return code ...&n;&t; *&n;&t; *         .set    noreorder&n;&t; *         addiu   sp,24&n;&t; *         li      v0,__NR_sigreturn&n;&t; *         syscall&n;&t; *         .set    reorder&n;&t; */
id|frame-&gt;code
(braket
l_int|0
)braket
op_assign
l_int|0x27bd0000
op_plus
id|scc_offset
suffix:semicolon
id|frame-&gt;code
(braket
l_int|1
)braket
op_assign
l_int|0x24020000
op_plus
id|__NR_sigreturn
suffix:semicolon
id|frame-&gt;code
(braket
l_int|2
)braket
op_assign
l_int|0x0000000c
suffix:semicolon
multiline_comment|/*&n;&t; * Flush caches so that the instructions will be correctly executed.&n;&t; */
id|sys_cacheflush
(paren
id|frame-&gt;code
comma
r_sizeof
(paren
id|frame-&gt;code
)paren
comma
id|ICACHE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the &quot;normal&quot; sigcontext_struct&n;&t; */
id|frame-&gt;scc.sc_at
op_assign
id|regs-&gt;reg1
suffix:semicolon
multiline_comment|/* Assembler temporary */
id|frame-&gt;scc.sc_v0
op_assign
id|regs-&gt;reg2
suffix:semicolon
multiline_comment|/* Result registers */
id|frame-&gt;scc.sc_v1
op_assign
id|regs-&gt;reg3
suffix:semicolon
id|frame-&gt;scc.sc_a0
op_assign
id|regs-&gt;reg4
suffix:semicolon
multiline_comment|/* Argument registers */
id|frame-&gt;scc.sc_a1
op_assign
id|regs-&gt;reg5
suffix:semicolon
id|frame-&gt;scc.sc_a2
op_assign
id|regs-&gt;reg6
suffix:semicolon
id|frame-&gt;scc.sc_a3
op_assign
id|regs-&gt;reg7
suffix:semicolon
id|frame-&gt;scc.sc_t0
op_assign
id|regs-&gt;reg8
suffix:semicolon
multiline_comment|/* Caller saved */
id|frame-&gt;scc.sc_t1
op_assign
id|regs-&gt;reg9
suffix:semicolon
id|frame-&gt;scc.sc_t2
op_assign
id|regs-&gt;reg10
suffix:semicolon
id|frame-&gt;scc.sc_t3
op_assign
id|regs-&gt;reg11
suffix:semicolon
id|frame-&gt;scc.sc_t4
op_assign
id|regs-&gt;reg12
suffix:semicolon
id|frame-&gt;scc.sc_t5
op_assign
id|regs-&gt;reg13
suffix:semicolon
id|frame-&gt;scc.sc_t6
op_assign
id|regs-&gt;reg14
suffix:semicolon
id|frame-&gt;scc.sc_t7
op_assign
id|regs-&gt;reg15
suffix:semicolon
id|frame-&gt;scc.sc_s0
op_assign
id|regs-&gt;reg16
suffix:semicolon
multiline_comment|/* Callee saved */
id|frame-&gt;scc.sc_s1
op_assign
id|regs-&gt;reg17
suffix:semicolon
id|frame-&gt;scc.sc_s2
op_assign
id|regs-&gt;reg18
suffix:semicolon
id|frame-&gt;scc.sc_s3
op_assign
id|regs-&gt;reg19
suffix:semicolon
id|frame-&gt;scc.sc_s4
op_assign
id|regs-&gt;reg20
suffix:semicolon
id|frame-&gt;scc.sc_s5
op_assign
id|regs-&gt;reg21
suffix:semicolon
id|frame-&gt;scc.sc_s6
op_assign
id|regs-&gt;reg22
suffix:semicolon
id|frame-&gt;scc.sc_s7
op_assign
id|regs-&gt;reg23
suffix:semicolon
id|frame-&gt;scc.sc_t8
op_assign
id|regs-&gt;reg24
suffix:semicolon
multiline_comment|/* Caller saved */
id|frame-&gt;scc.sc_t9
op_assign
id|regs-&gt;reg25
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t copy k0/k1&n;&t; */
id|frame-&gt;scc.sc_gp
op_assign
id|regs-&gt;reg28
suffix:semicolon
multiline_comment|/* global pointer / s8 */
id|frame-&gt;scc.sc_sp
op_assign
id|regs-&gt;reg29
suffix:semicolon
multiline_comment|/* old stack pointer */
id|frame-&gt;scc.sc_fp
op_assign
id|regs-&gt;reg30
suffix:semicolon
multiline_comment|/* old frame pointer */
id|frame-&gt;scc.sc_ra
op_assign
id|regs-&gt;reg31
suffix:semicolon
multiline_comment|/* old return address */
id|frame-&gt;scc.sc_epc
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
multiline_comment|/* Program counter */
id|frame-&gt;scc.sc_cause
op_assign
id|regs-&gt;cp0_cause
suffix:semicolon
multiline_comment|/* c0_epc register */
id|frame-&gt;scc.sc_oldmask
op_assign
id|oldmask
suffix:semicolon
op_star
id|fp
op_assign
id|frame
suffix:semicolon
id|regs-&gt;reg4
op_assign
id|signr
suffix:semicolon
multiline_comment|/* argument for handler */
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
r_struct
id|sc
op_star
id|frame
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|pc
op_assign
l_int|0
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
r_case
id|SIGBUS
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
multiline_comment|/*&n;&t;&t; * OK, we&squot;re invoking a handler&n;&t;&t; */
r_if
c_cond
(paren
id|regs-&gt;orig_reg2
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;reg2
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
(paren
id|regs-&gt;reg2
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
id|regs-&gt;reg2
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
multiline_comment|/*&n;&t; * Who&squot;s code doesn&squot;t conform to the restartable syscall convention&n;&t; * dies here!!!  The li instruction, a single machine instruction,&n;&t; * must directly be followed by the syscall instruction.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;orig_reg2
op_ge
l_int|0
op_logical_and
(paren
id|regs-&gt;reg2
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;reg2
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;reg2
op_eq
op_minus
id|ERESTARTNOINTR
)paren
)paren
(brace
id|regs-&gt;reg2
op_assign
id|regs-&gt;orig_reg2
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler_signal
)paren
multiline_comment|/* no handler will be called - return 0 */
r_return
l_int|0
suffix:semicolon
id|pc
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sc
op_star
)paren
id|regs-&gt;reg29
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
id|setup_frame
c_func
(paren
id|sa
comma
op_amp
id|frame
comma
id|pc
comma
id|regs
comma
id|signr
comma
id|oldmask
)paren
suffix:semicolon
id|pc
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
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
id|oldmask
op_or_assign
id|sa-&gt;sa_mask
suffix:semicolon
)brace
id|regs-&gt;reg29
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
multiline_comment|/* Stack pointer */
id|regs-&gt;reg31
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
id|pc
suffix:semicolon
multiline_comment|/* &quot;return&quot; to the first handler */
r_return
l_int|1
suffix:semicolon
)brace
eof
