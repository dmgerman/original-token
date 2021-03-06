multiline_comment|/* $Id: ptrace.c,v 1.6 2000/06/08 23:44:50 gniibe Exp $&n; *&n; * linux/arch/sh/kernel/ptrace.c&n; *&n; * Original x86 implementation:&n; *&t;By Ross Biro 1/23/92&n; *&t;edited by Linus Torvalds&n; *&n; * SuperH version:   Copyright (C) 1999, 2000  Kaz Kojima &amp; Niibe Yutaka&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/*&n; * This routine will get a word off of the process kernel stack.&n; */
DECL|function|get_stack_long
r_static
r_inline
r_int
id|get_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
r_return
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|stack
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine will put a word on the process kernel stack.&n; */
DECL|function|put_stack_long
r_static
r_inline
r_int
id|put_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|stack
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|compute_next_pc
id|compute_next_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|inst
comma
r_int
r_int
op_star
id|pc1
comma
r_int
r_int
op_star
id|pc2
)paren
(brace
r_int
id|nib
(braket
l_int|4
)braket
op_assign
(brace
(paren
id|inst
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
comma
(paren
id|inst
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
comma
(paren
id|inst
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|inst
op_amp
l_int|0xf
)brace
suffix:semicolon
multiline_comment|/* bra &amp; bsr */
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0xa
op_logical_or
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0xb
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_int
)paren
(paren
(paren
id|inst
op_amp
l_int|0xfff
)paren
op_lshift
l_int|4
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
op_star
id|pc2
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* bt &amp; bf */
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x8
op_logical_and
(paren
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0x9
op_logical_or
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0xb
)paren
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_char
)paren
(paren
id|inst
op_amp
l_int|0xff
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
op_star
id|pc2
op_assign
id|regs-&gt;pc
op_plus
l_int|2
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* bt/s &amp; bf/s */
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x8
op_logical_and
(paren
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0xd
op_logical_or
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0xf
)paren
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_char
)paren
(paren
id|inst
op_amp
l_int|0xff
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
op_star
id|pc2
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* jmp &amp; jsr */
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x4
op_logical_and
id|nib
(braket
l_int|3
)braket
op_eq
l_int|0xb
op_logical_and
(paren
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x0
op_logical_or
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x2
)paren
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;regs
(braket
id|nib
(braket
l_int|1
)braket
)braket
suffix:semicolon
op_star
id|pc2
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* braf &amp; bsrf */
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x0
op_logical_and
id|nib
(braket
l_int|3
)braket
op_eq
l_int|0x3
op_logical_and
(paren
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x0
op_logical_or
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x2
)paren
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
id|regs-&gt;regs
(braket
id|nib
(braket
l_int|1
)braket
)braket
suffix:semicolon
op_star
id|pc2
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inst
op_eq
l_int|0x000b
)paren
(brace
op_star
id|pc1
op_assign
id|regs-&gt;pr
suffix:semicolon
op_star
id|pc2
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|pc1
op_assign
id|regs-&gt;pc
op_plus
l_int|2
suffix:semicolon
op_star
id|pc2
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Tracing by user break controller.  */
r_static
r_void
DECL|function|ubc_set_tracing
id|ubc_set_tracing
c_func
(paren
r_int
id|asid
comma
r_int
r_int
id|nextpc1
comma
r_int
id|nextpc2
)paren
(brace
id|ctrl_outl
c_func
(paren
id|nextpc1
comma
id|UBC_BARA
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|asid
comma
id|UBC_BASRA
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7709)
id|ctrl_outl
c_func
(paren
l_int|0x0fff
comma
id|UBC_BAMRA
)paren
suffix:semicolon
macro_line|#else
id|ctrl_outb
c_func
(paren
id|BAMR_12
comma
id|UBC_BAMRA
)paren
suffix:semicolon
macro_line|#endif
id|ctrl_outw
c_func
(paren
id|BBR_INST
op_or
id|BBR_READ
comma
id|UBC_BBRA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextpc2
op_ne
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
(brace
id|ctrl_outl
c_func
(paren
id|nextpc2
comma
id|UBC_BARB
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|asid
comma
id|UBC_BASRB
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7709)
id|ctrl_outl
c_func
(paren
l_int|0x0fff
comma
id|UBC_BAMRA
)paren
suffix:semicolon
macro_line|#else
id|ctrl_outb
c_func
(paren
id|BAMR_12
comma
id|UBC_BAMRB
)paren
suffix:semicolon
macro_line|#endif
id|ctrl_outw
c_func
(paren
id|BBR_INST
op_or
id|BBR_READ
comma
id|UBC_BBRB
)paren
suffix:semicolon
)brace
id|ctrl_outw
c_func
(paren
id|BRCR_PCBA
op_or
id|BRCR_PCBB
comma
id|UBC_BRCR
)paren
suffix:semicolon
)brace
DECL|function|sys_ptrace
id|asmlinkage
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
comma
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|user
op_star
id|dummy
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
r_if
c_cond
(paren
id|child
op_eq
id|tsk
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|child-&gt;dumpable
op_logical_or
(paren
id|tsk-&gt;uid
op_ne
id|child-&gt;euid
)paren
op_logical_or
(paren
id|tsk-&gt;uid
op_ne
id|child-&gt;suid
)paren
op_logical_or
(paren
id|tsk-&gt;uid
op_ne
id|child-&gt;uid
)paren
op_logical_or
(paren
id|tsk-&gt;gid
op_ne
id|child-&gt;egid
)paren
op_logical_or
(paren
id|tsk-&gt;gid
op_ne
id|child-&gt;sgid
)paren
op_logical_or
(paren
op_logical_neg
id|cap_issubset
c_func
(paren
id|child-&gt;cap_permitted
comma
id|tsk-&gt;cap_permitted
)paren
)paren
op_logical_or
(paren
id|tsk-&gt;gid
op_ne
id|child-&gt;gid
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
multiline_comment|/* the same process cannot be attached many times */
r_if
c_cond
(paren
id|child-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out_tsk
suffix:semicolon
id|child-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|tsk
)paren
(brace
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;p_pptr
op_assign
id|tsk
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSTOP
comma
id|child
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|child-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_STOPPED
)paren
(brace
r_if
c_cond
(paren
id|request
op_ne
id|PTRACE_KILL
)paren
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|tsk
)paren
r_goto
id|out_tsk
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* when I and D space are separate, these will need to be fixed. */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* read the word at location addr in the USER area. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;fpu
op_logical_and
id|addr
OL
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_fpvalid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;used_math
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;fpu.fpscr
)paren
id|tmp
op_assign
id|FPSCR_INIT
suffix:semicolon
r_else
id|tmp
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|tmp
op_assign
(paren
(paren
r_int
op_star
)paren
op_amp
id|child-&gt;thread.fpu
)paren
(braket
(paren
id|addr
op_minus
(paren
r_int
)paren
op_amp
id|dummy-&gt;fpu
)paren
op_rshift
l_int|2
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_fpvalid
)paren
id|tmp
op_assign
id|child-&gt;used_math
suffix:semicolon
r_else
id|tmp
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* when I and D space are separate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|data
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the word at location addr in the USER area */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
id|ret
op_assign
id|put_stack_long
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;fpu
op_logical_and
id|addr
OL
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_fpvalid
)paren
(brace
id|child-&gt;used_math
op_assign
l_int|1
suffix:semicolon
(paren
(paren
r_int
op_star
)paren
op_amp
id|child-&gt;thread.fpu
)paren
(braket
(paren
id|addr
op_minus
(paren
r_int
)paren
op_amp
id|dummy-&gt;fpu
)paren
op_rshift
l_int|2
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_fpvalid
)paren
(brace
id|child-&gt;used_math
op_assign
id|data
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYS
suffix:semicolon
r_else
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYS
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it wants to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_break
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SINGLESTEP
suffix:colon
(brace
multiline_comment|/* set the trap flag. */
r_int
id|tmp
comma
id|pc
suffix:semicolon
r_struct
id|pt_regs
op_star
id|dummy
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
r_int
id|nextpc1
comma
id|nextpc2
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Spurious delayed TF traps may occur */
id|child-&gt;ptrace
op_or_assign
id|PT_DTRACE
suffix:semicolon
)brace
multiline_comment|/* Compute next pc.  */
id|pc
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
(paren
r_int
)paren
op_amp
id|dummy-&gt;pc
)paren
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|child
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|pc
op_amp
op_complement
l_int|3
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
macro_line|#ifdef  __LITTLE_ENDIAN__
r_if
c_cond
(paren
id|pc
op_amp
l_int|3
)paren
id|insn
op_assign
id|tmp
op_rshift
l_int|16
suffix:semicolon
r_else
id|insn
op_assign
id|tmp
op_amp
l_int|0xffff
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|pc
op_amp
l_int|3
)paren
id|insn
op_assign
id|tmp
op_amp
l_int|0xffff
suffix:semicolon
r_else
id|insn
op_assign
id|tmp
op_rshift
l_int|16
suffix:semicolon
macro_line|#endif
id|compute_next_pc
(paren
id|regs
comma
id|insn
comma
op_amp
id|nextpc1
comma
op_amp
id|nextpc2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextpc1
op_amp
l_int|0x80000000
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|nextpc2
op_ne
(paren
r_int
r_int
)paren
op_minus
l_int|1
op_logical_and
(paren
id|nextpc2
op_amp
l_int|0x80000000
)paren
)paren
r_break
suffix:semicolon
id|ubc_set_tracing
c_func
(paren
id|child-&gt;mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
comma
id|nextpc1
comma
id|nextpc2
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* give it a chance to run. */
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_DETACH
suffix:colon
(brace
multiline_comment|/* detach a process that was attached. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|child-&gt;ptrace
op_assign
l_int|0
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;p_pptr
op_assign
id|child-&gt;p_opptr
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETOPTIONS
suffix:colon
(brace
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACESYSGOOD
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYSGOOD
suffix:semicolon
r_else
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYSGOOD
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out_tsk
suffix:colon
id|free_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|syscall_trace
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tsk-&gt;ptrace
op_amp
(paren
id|PT_PTRACED
op_or
id|PT_TRACESYS
)paren
)paren
op_ne
(paren
id|PT_PTRACED
op_or
id|PT_TRACESYS
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* the 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
id|tsk-&gt;exit_code
op_assign
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|tsk
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|tsk-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|tsk-&gt;exit_code
comma
id|tsk
comma
l_int|1
)paren
suffix:semicolon
id|tsk-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
