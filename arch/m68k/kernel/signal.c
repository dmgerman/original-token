multiline_comment|/*&n; *  linux/arch/m68k/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Linux/m68k support by Hamish Macdonald&n; *&n; * 68060 fixes by Jesper Skov&n; */
multiline_comment|/*&n; * ++roman (07/09/96): implemented signal stacks (specially for tosemu on&n; * Atari :-) Current limitation: Only one sigstack can be active at one time.&n; * If a second signal with SA_STACK set arrives while working on a sigstack,&n; * SA_STACK is ignored. This behaviour avoids lots of trouble with nested&n; * signal handlers!&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
DECL|macro|offsetof
mdefine_line|#define offsetof(type, member)  ((size_t)(&amp;((type *)0)-&gt;member))
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
DECL|variable|frame_extra_sizes
r_const
r_int
id|frame_extra_sizes
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmt1), */
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmt2
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmt3
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmt4
)paren
comma
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmt5), */
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmt6), */
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmt7
)paren
comma
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmt8), */
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmt9
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmta
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|frame
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|un.fmtb
)paren
comma
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmtc), */
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmtd), */
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmte), */
op_minus
l_int|1
comma
multiline_comment|/* sizeof(((struct frame *)0)-&gt;un.fmtf), */
)brace
suffix:semicolon
multiline_comment|/*&n; * atomically swap in the new signal mask, and wait for a signal.&n; */
DECL|function|do_sigsuspend
id|asmlinkage
r_int
id|do_sigsuspend
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
id|oldmask
op_assign
id|current-&gt;blocked
suffix:semicolon
r_int
r_int
id|newmask
op_assign
id|regs-&gt;d3
suffix:semicolon
id|current-&gt;blocked
op_assign
id|newmask
op_amp
id|_BLOCKABLE
suffix:semicolon
id|regs-&gt;d0
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
id|oldmask
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
DECL|variable|fpu_version
r_static
r_int
r_char
id|fpu_version
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* version number of fpu, set by setup_frame */
DECL|function|do_sigreturn
id|asmlinkage
r_int
id|do_sigreturn
c_func
(paren
r_int
r_int
id|__unused
)paren
(brace
r_struct
id|sigcontext
id|context
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_struct
id|switch_stack
op_star
id|sw
suffix:semicolon
r_int
id|fsize
op_assign
l_int|0
suffix:semicolon
r_int
id|formatvec
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|fp
suffix:semicolon
r_int
r_int
id|usp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;sys_sigreturn, usp=%08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|usp
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* get stack frame pointer */
id|sw
op_assign
(paren
r_struct
id|switch_stack
op_star
)paren
op_amp
id|__unused
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|sw
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* get previous context (including pointer to possible extra junk) */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|context
comma
(paren
r_void
op_star
)paren
id|usp
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
id|fp
op_assign
id|usp
op_plus
r_sizeof
(paren
id|context
)paren
suffix:semicolon
multiline_comment|/* restore signal mask */
id|current-&gt;blocked
op_assign
id|context.sc_mask
op_amp
id|_BLOCKABLE
suffix:semicolon
multiline_comment|/* restore passed registers */
id|regs-&gt;d0
op_assign
id|context.sc_d0
suffix:semicolon
id|regs-&gt;d1
op_assign
id|context.sc_d1
suffix:semicolon
id|regs-&gt;a0
op_assign
id|context.sc_a0
suffix:semicolon
id|regs-&gt;a1
op_assign
id|context.sc_a1
suffix:semicolon
id|regs-&gt;sr
op_assign
(paren
id|regs-&gt;sr
op_amp
l_int|0xff00
)paren
op_or
(paren
id|context.sc_sr
op_amp
l_int|0xff
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|context.sc_pc
suffix:semicolon
id|regs-&gt;orig_d0
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* disable syscall checks */
id|wrusp
c_func
(paren
id|context.sc_usp
)paren
suffix:semicolon
id|formatvec
op_assign
id|context.sc_formatvec
suffix:semicolon
id|regs-&gt;format
op_assign
id|formatvec
op_rshift
l_int|12
suffix:semicolon
id|regs-&gt;vector
op_assign
id|formatvec
op_amp
l_int|0xfff
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|CPU_IS_060
op_logical_and
id|context.sc_fpstate
(braket
l_int|0
)braket
)paren
op_logical_or
(paren
id|CPU_IS_060
op_logical_and
id|context.sc_fpstate
(braket
l_int|2
)braket
)paren
)paren
(brace
multiline_comment|/* Verify the frame format.  */
r_if
c_cond
(paren
op_logical_neg
id|CPU_IS_060
op_logical_and
(paren
id|context.sc_fpstate
(braket
l_int|0
)braket
op_ne
id|fpu_version
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68881
)paren
(brace
r_if
c_cond
(paren
id|context.sc_fpstate
(braket
l_int|1
)braket
op_ne
l_int|0x18
op_logical_and
id|context.sc_fpstate
(braket
l_int|1
)braket
op_ne
l_int|0xb4
)paren
r_goto
id|badframe
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68882
)paren
(brace
r_if
c_cond
(paren
id|context.sc_fpstate
(braket
l_int|1
)braket
op_ne
l_int|0x38
op_logical_and
id|context.sc_fpstate
(braket
l_int|1
)braket
op_ne
l_int|0xd4
)paren
r_goto
id|badframe
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68040
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|context.sc_fpstate
(braket
l_int|1
)braket
op_eq
l_int|0x00
op_logical_or
id|context.sc_fpstate
(braket
l_int|1
)braket
op_eq
l_int|0x28
op_logical_or
id|context.sc_fpstate
(braket
l_int|1
)braket
op_eq
l_int|0x60
)paren
)paren
r_goto
id|badframe
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68060
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|context.sc_fpstate
(braket
l_int|3
)braket
op_eq
l_int|0x00
op_logical_or
id|context.sc_fpstate
(braket
l_int|3
)braket
op_eq
l_int|0x60
op_logical_or
id|context.sc_fpstate
(braket
l_int|3
)braket
op_eq
l_int|0xe0
)paren
)paren
r_goto
id|badframe
suffix:semicolon
)brace
id|__asm__
r_volatile
(paren
l_string|&quot;fmovemx %0,%/fp0-%/fp1&bslash;n&bslash;t&quot;
l_string|&quot;fmoveml %1,%/fpcr/%/fpsr/%/fpiar&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpcntl
)paren
)paren
suffix:semicolon
)brace
id|__asm__
r_volatile
(paren
l_string|&quot;frestore %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpstate
)paren
)paren
suffix:semicolon
id|fsize
op_assign
id|frame_extra_sizes
(braket
id|regs-&gt;format
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fsize
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * user process trying to return with weird frame format&n;&t;&t; */
macro_line|#if DEBUG
id|printk
c_func
(paren
l_string|&quot;user process returning with weird frame format&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|badframe
suffix:semicolon
)brace
r_if
c_cond
(paren
id|context.sc_usp
op_ne
id|fp
op_plus
id|fsize
)paren
id|current-&gt;flags
op_and_assign
op_complement
id|PF_ONSIGSTK
suffix:semicolon
multiline_comment|/* OK.&t;Make room on the supervisor stack for the extra junk,&n;&t; * if necessary.&n;&t; */
r_if
c_cond
(paren
id|fsize
)paren
(brace
DECL|macro|frame_offset
mdefine_line|#define frame_offset (sizeof(struct pt_regs)+sizeof(struct switch_stack))
id|__asm__
id|__volatile__
(paren
l_string|&quot;   movel %0,%/a0&bslash;n&bslash;t&quot;
l_string|&quot;   subl %1,%/a0&bslash;n&bslash;t&quot;
multiline_comment|/* make room on stack */
l_string|&quot;   movel %/a0,%/sp&bslash;n&bslash;t&quot;
multiline_comment|/* set stack pointer */
multiline_comment|/* move switch_stack and pt_regs */
l_string|&quot;1: movel %0@+,%/a0@+&bslash;n&bslash;t&quot;
l_string|&quot;   dbra %2,1b&bslash;n&bslash;t&quot;
l_string|&quot;   lea %/sp@(%c3),%/a0&bslash;n&bslash;t&quot;
multiline_comment|/* add offset of fmt */
l_string|&quot;   lsrl  #2,%1&bslash;n&bslash;t&quot;
l_string|&quot;   subql #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;2: movesl %4@+,%2&bslash;n&bslash;t&quot;
l_string|&quot;3: movel %2,%/a0@+&bslash;n&bslash;t&quot;
l_string|&quot;   dbra %1,2b&bslash;n&bslash;t&quot;
l_string|&quot;   bral &quot;
id|SYMBOL_NAME_STR
c_func
(paren
id|ret_from_signal
)paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;4:&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 2b,4b&bslash;n&quot;
l_string|&quot;   .long 3b,4b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
multiline_comment|/* no outputs, it doesn&squot;t ever return */
suffix:colon
l_string|&quot;a&quot;
(paren
id|sw
)paren
comma
l_string|&quot;d&quot;
(paren
id|fsize
)paren
comma
l_string|&quot;d&quot;
(paren
id|frame_offset
op_div
l_int|4
op_minus
l_int|1
)paren
comma
l_string|&quot;n&quot;
(paren
id|frame_offset
)paren
comma
l_string|&quot;a&quot;
(paren
id|fp
)paren
suffix:colon
l_string|&quot;a0&quot;
)paren
suffix:semicolon
DECL|macro|frame_offset
macro_line|#undef frame_offset
multiline_comment|/*&n;&t;&t; * If we ever get here an exception occured while&n;&t;&t; * building the above stack-frame.&n;&t;&t; */
r_goto
id|badframe
suffix:semicolon
)brace
r_return
id|regs-&gt;d0
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
multiline_comment|/*&n; * Set up a signal frame...&n; *&n; * This routine is somewhat complicated by the fact that if the&n; * kernel may be entered by an exception other than a system call;&n; * e.g. a bus error or other &quot;bad&quot; exception.  If this is the case,&n; * then *all* the context on the kernel stack frame must be saved.&n; *&n; * For a large number of exceptions, the stack frame format is the same&n; * as that which will be created when the process traps back to the kernel&n; * when finished executing the signal handler.&t;In this case, nothing&n; * must be done.  This is exception frame format &quot;0&quot;.  For exception frame&n; * formats &quot;2&quot;, &quot;9&quot;, &quot;A&quot; and &quot;B&quot;, the extra information on the frame must&n; * be saved.  This information is saved on the user stack and restored&n; * when the signal handler is returned.&n; *&n; * The format of the user stack when executing the signal handler is:&n; *&n; *     usp -&gt;  RETADDR (points to code below)&n; *&t;       signum  (parm #1)&n; *&t;       sigcode (parm #2 ; vector number)&n; *&t;       scp     (parm #3 ; sigcontext pointer, pointer to #1 below)&n; *&t;       code1   (addaw #20,sp) ; pop parms and code off stack&n; *&t;       code2   (moveq #119,d0; trap #0) ; sigreturn syscall&n; *     #1|     oldmask&n; *&t; |     old usp&n; *&t; |     d0      (first saved reg)&n; *&t; |     d1&n; *&t; |     a0&n; *&t; |     a1&n; *&t; |     sr      (saved status register)&n; *&t; |     pc      (old pc; one to return to)&n; *&t; |     forvec  (format and vector word of old supervisor stack frame)&n; *&t; |     floating point context&n; *&n; * These are optionally followed by some extra stuff, depending on the&n; * stack frame interrupted. This is 1 longword for format &quot;2&quot;, 3&n; * longwords for format &quot;9&quot;, 6 longwords for format &quot;A&quot;, and 21&n; * longwords for format &quot;B&quot;.&n; */
DECL|macro|UFRAME_SIZE
mdefine_line|#define UFRAME_SIZE(fs) (sizeof(struct sigcontext)/4 + 6 + fs/4)
DECL|function|setup_frame
r_static
r_inline
r_void
id|setup_frame
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
id|sigcontext
id|context
suffix:semicolon
r_int
r_int
op_star
id|frame
comma
op_star
id|tframe
suffix:semicolon
r_int
id|fsize
op_assign
id|frame_extra_sizes
(braket
id|regs-&gt;format
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fsize
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;setup_frame: Unknown frame format %#x&bslash;n&quot;
comma
id|regs-&gt;format
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|frame
op_assign
(paren
r_int
r_int
op_star
)paren
id|rdusp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;flags
op_amp
id|PF_ONSIGSTK
)paren
op_logical_and
(paren
id|sa-&gt;sa_flags
op_amp
id|SA_STACK
)paren
)paren
(brace
id|frame
op_assign
(paren
r_int
r_int
op_star
)paren
id|sa-&gt;sa_restorer
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_ONSIGSTK
suffix:semicolon
)brace
id|frame
op_sub_assign
id|UFRAME_SIZE
c_func
(paren
id|fsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fsize
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|frame
op_plus
id|UFRAME_SIZE
c_func
(paren
l_int|0
)paren
comma
id|regs
op_plus
l_int|1
comma
id|fsize
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
id|regs-&gt;stkadj
op_assign
id|fsize
suffix:semicolon
)brace
multiline_comment|/* set up the &quot;normal&quot; stack seen by the signal handler */
id|tframe
op_assign
id|frame
suffix:semicolon
multiline_comment|/* return address points to code on stack */
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
id|ulong
)paren
(paren
id|frame
op_plus
l_int|4
)paren
comma
id|tframe
)paren
)paren
(brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|tframe
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;exec_domain
op_logical_and
id|current-&gt;exec_domain-&gt;signal_invmap
)paren
id|__put_user
c_func
(paren
id|current-&gt;exec_domain-&gt;signal_invmap
(braket
id|signr
)braket
comma
id|tframe
)paren
suffix:semicolon
r_else
id|__put_user
c_func
(paren
id|signr
comma
id|tframe
)paren
suffix:semicolon
id|tframe
op_increment
suffix:semicolon
id|__put_user
c_func
(paren
id|regs-&gt;vector
comma
id|tframe
)paren
suffix:semicolon
id|tframe
op_increment
suffix:semicolon
multiline_comment|/* &quot;scp&quot; parameter.  points to sigcontext */
id|__put_user
c_func
(paren
(paren
id|ulong
)paren
(paren
id|frame
op_plus
l_int|6
)paren
comma
id|tframe
)paren
suffix:semicolon
id|tframe
op_increment
suffix:semicolon
multiline_comment|/* set up the return code... */
id|__put_user
c_func
(paren
l_int|0xdefc0014
comma
id|tframe
)paren
suffix:semicolon
id|tframe
op_increment
suffix:semicolon
multiline_comment|/* addaw #20,sp */
id|__put_user
c_func
(paren
l_int|0x70774e40
comma
id|tframe
)paren
suffix:semicolon
id|tframe
op_increment
suffix:semicolon
multiline_comment|/* moveq #119,d0; trap #0 */
multiline_comment|/* Flush caches so the instructions will be correctly executed. (MA) */
id|cache_push_v
(paren
(paren
r_int
r_int
)paren
id|frame
comma
(paren
r_int
)paren
id|tframe
op_minus
(paren
r_int
)paren
id|frame
)paren
suffix:semicolon
multiline_comment|/* setup and copy the sigcontext structure */
id|context.sc_mask
op_assign
id|oldmask
suffix:semicolon
id|context.sc_usp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|context.sc_d0
op_assign
id|regs-&gt;d0
suffix:semicolon
id|context.sc_d1
op_assign
id|regs-&gt;d1
suffix:semicolon
id|context.sc_a0
op_assign
id|regs-&gt;a0
suffix:semicolon
id|context.sc_a1
op_assign
id|regs-&gt;a1
suffix:semicolon
id|context.sc_sr
op_assign
id|regs-&gt;sr
suffix:semicolon
id|context.sc_pc
op_assign
id|regs-&gt;pc
suffix:semicolon
id|context.sc_formatvec
op_assign
(paren
id|regs-&gt;format
op_lshift
l_int|12
op_or
id|regs-&gt;vector
)paren
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;fsave %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpstate
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|CPU_IS_060
op_logical_and
id|context.sc_fpstate
(braket
l_int|0
)braket
)paren
op_logical_or
(paren
id|CPU_IS_060
op_logical_and
id|context.sc_fpstate
(braket
l_int|2
)braket
)paren
)paren
(brace
id|fpu_version
op_assign
id|context.sc_fpstate
(braket
l_int|0
)braket
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;fmovemx %/fp0-%/fp1,%0&bslash;n&bslash;t&quot;
l_string|&quot;fmoveml %/fpcr/%/fpsr/%/fpiar,%1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|context.sc_fpcntl
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|tframe
comma
op_amp
id|context
comma
r_sizeof
(paren
id|context
)paren
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * no matter what frame format we were using before, we&n;&t; * will do the &quot;RTE&quot; using a normal 4 word frame.&n;&t; */
id|regs-&gt;format
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
id|wrusp
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
(paren
r_int
r_int
)paren
id|sa-&gt;sa_handler
suffix:semicolon
multiline_comment|/* Prepare to skip over the extra stuff in the exception frame.  */
r_if
c_cond
(paren
id|regs-&gt;stkadj
)paren
(brace
r_struct
id|pt_regs
op_star
id|tregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
id|ulong
)paren
id|regs
op_plus
id|regs-&gt;stkadj
)paren
suffix:semicolon
macro_line|#if DEBUG
id|printk
c_func
(paren
l_string|&quot;Performing stackadjust=%04x&bslash;n&quot;
comma
id|regs-&gt;stkadj
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* This must be copied with decreasing addresses to&n;                   handle overlaps.  */
id|tregs-&gt;vector
op_assign
id|regs-&gt;vector
suffix:semicolon
id|tregs-&gt;format
op_assign
id|regs-&gt;format
suffix:semicolon
id|tregs-&gt;pc
op_assign
id|regs-&gt;pc
suffix:semicolon
id|tregs-&gt;sr
op_assign
id|regs-&gt;sr
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
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
multiline_comment|/* are we from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_d0
op_ge
l_int|0
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;d0
)paren
(brace
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;d0
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
id|regs-&gt;d0
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
id|regs-&gt;d0
op_assign
id|regs-&gt;orig_d0
suffix:semicolon
id|regs-&gt;pc
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
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; *&n; * Note that we go through the signals twice: once to check the signals&n; * that the kernel can handle, and then we build all the user-level signal&n; * handling stack-frames in one go after that.&n; */
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
id|current-&gt;tss.esp0
op_assign
(paren
r_int
r_int
)paren
id|regs
suffix:semicolon
multiline_comment|/* If the process is traced, all signals are passed to the debugger. */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|mask
op_assign
op_complement
l_int|0UL
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
id|__asm__
c_func
(paren
l_string|&quot;bfffo  %2,#0,#0,%1&bslash;n&bslash;t&quot;
l_string|&quot;bfclr  %0,%1,#1&bslash;n&bslash;t&quot;
l_string|&quot;eorw   #31,%1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|current-&gt;signal
)paren
comma
l_string|&quot;=d&quot;
(paren
id|signr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|current-&gt;signal
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
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_d0
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call */
r_if
c_cond
(paren
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;d0
op_assign
id|regs-&gt;orig_d0
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
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
(brace
id|discard_frame
suffix:colon
multiline_comment|/* Make sure that a faulted bus cycle&n;&t;&t;&t;       isn&squot;t restarted (only needed on the&n;&t;&t;&t;       68030).  */
r_if
c_cond
(paren
id|regs-&gt;format
op_eq
l_int|10
op_logical_or
id|regs-&gt;format
op_eq
l_int|11
)paren
(brace
id|regs-&gt;stkadj
op_assign
id|frame_extra_sizes
(braket
id|regs-&gt;format
)braket
suffix:semicolon
id|regs-&gt;format
op_assign
l_int|0
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
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
r_goto
id|discard_frame
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
id|mask
op_and_assign
op_complement
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
id|regs-&gt;orig_d0
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;d0
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;d0
op_assign
id|regs-&gt;orig_d0
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* If we are about to discard some frame stuff we must copy&n;&t;   over the remaining frame. */
r_if
c_cond
(paren
id|regs-&gt;stkadj
)paren
(brace
r_struct
id|pt_regs
op_star
id|tregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
id|ulong
)paren
id|regs
op_plus
id|regs-&gt;stkadj
)paren
suffix:semicolon
multiline_comment|/* This must be copied with decreasing addresses to&n;&t;&t;   handle overlaps.  */
id|tregs-&gt;vector
op_assign
id|regs-&gt;vector
suffix:semicolon
id|tregs-&gt;format
op_assign
id|regs-&gt;format
suffix:semicolon
id|tregs-&gt;pc
op_assign
id|regs-&gt;pc
suffix:semicolon
id|tregs-&gt;sr
op_assign
id|regs-&gt;sr
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
