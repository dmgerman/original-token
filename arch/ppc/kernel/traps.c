multiline_comment|/*&n; *  linux/arch/ppc/kernel/traps.c&n; *&n; *  Copyright (C) 1995-1996  Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  and Paul Mackerras (paulus@cs.anu.edu.au)&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of hardware exceptions&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
r_extern
r_int
id|fix_alignment
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bad_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
r_extern
r_void
id|xmon
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|xmon_bpt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|xmon_sstep
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|xmon_iabr_match
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|xmon_dabr_match
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|xmon_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_XMON
DECL|variable|debugger
r_void
(paren
op_star
id|debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|xmon
suffix:semicolon
DECL|variable|debugger_bpt
r_int
(paren
op_star
id|debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|xmon_bpt
suffix:semicolon
DECL|variable|debugger_sstep
r_int
(paren
op_star
id|debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|xmon_sstep
suffix:semicolon
DECL|variable|debugger_iabr_match
r_int
(paren
op_star
id|debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|xmon_iabr_match
suffix:semicolon
DECL|variable|debugger_dabr_match
r_int
(paren
op_star
id|debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|xmon_dabr_match
suffix:semicolon
DECL|variable|debugger_fault_handler
r_void
(paren
op_star
id|debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_KGDB
DECL|variable|debugger
r_void
(paren
op_star
id|debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_bpt
r_int
(paren
op_star
id|debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_sstep
r_int
(paren
op_star
id|debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_iabr_match
r_int
(paren
op_star
id|debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_dabr_match
r_int
(paren
op_star
id|debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger_fault_handler
r_void
(paren
op_star
id|debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Trap &amp; Exception support&n; */
r_void
DECL|function|trap_init
id|trap_init
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|_exception
id|_exception
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|print_backtrace
c_func
(paren
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
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Exception in kernel pc %lx signal %d&quot;
comma
id|regs-&gt;nip
comma
id|signr
)paren
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|signr
comma
id|current
)paren
suffix:semicolon
)brace
r_void
DECL|function|MachineCheckException
id|MachineCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_fault_handler
)paren
(brace
id|debugger_fault_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Machine check in kernel mode.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Caused by (from msr): &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;regs %p &quot;
comma
id|regs
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x0000F000
)paren
(brace
r_case
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Machine check signal - probably due to mm fault&bslash;n&quot;
l_string|&quot;with mmu off&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|1
op_lshift
l_int|13
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Transfer error ack signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|1
op_lshift
l_int|14
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Data parity signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|1
op_lshift
l_int|15
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Address parity signal&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown values in msr&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|print_backtrace
c_func
(paren
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
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;machine check&quot;
)paren
suffix:semicolon
)brace
id|_exception
c_func
(paren
id|SIGSEGV
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|UnknownException
id|UnknownException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad trap at PC: %lx, SR: %lx, vector=%lx&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
comma
id|regs-&gt;trap
)paren
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|InstructionBreakpoint
id|InstructionBreakpoint
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_iabr_match
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|RunModeException
id|RunModeException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|ProgramCheckException
id|ProgramCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x100000
)paren
(brace
multiline_comment|/* IEEE FP exception */
id|_exception
c_func
(paren
id|SIGFPE
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
l_int|0x20000
)paren
(brace
multiline_comment|/* trap exception */
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_bpt
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|SingleStepException
id|SingleStepException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SE
suffix:semicolon
multiline_comment|/* Turn off &squot;trace&squot; bit */
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
r_if
c_cond
(paren
id|debugger_sstep
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|AlignmentException
id|AlignmentException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|fixed
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
macro_line|#endif&t;
id|fixed
op_assign
id|fix_alignment
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixed
op_eq
l_int|1
)paren
(brace
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* skip over emulated instruction */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fixed
op_eq
op_minus
id|EFAULT
)paren
(brace
multiline_comment|/* fixed == -EFAULT means the operand address was bad */
id|bad_page_fault
c_func
(paren
id|regs
comma
id|regs-&gt;dar
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
)paren
suffix:semicolon
)brace
r_void
DECL|function|StackOverflow
id|StackOverflow
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Kernel stack overflow in process %p, r1=%lx&bslash;n&quot;
comma
id|current
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_XMON) || defined(CONFIG_KGDB)
id|debugger
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|print_backtrace
c_func
(paren
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
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;kernel stack overflow&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|trace_syscall
id|trace_syscall
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Task: %p(%d), PC: %08lX/%08lX, Syscall: %3ld, Result: %s%ld&bslash;n&quot;
comma
id|current
comma
id|current-&gt;pid
comma
id|regs-&gt;nip
comma
id|regs-&gt;link
comma
id|regs-&gt;gpr
(braket
l_int|0
)braket
comma
id|regs-&gt;ccr
op_amp
l_int|0x10000000
ques
c_cond
l_string|&quot;Error=&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|regs-&gt;gpr
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_8xx
r_void
DECL|function|SoftwareEmulation
id|SoftwareEmulation
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|errcode
suffix:semicolon
r_extern
r_int
id|Soft_emulate_8xx
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;(user mode)&bslash;n&quot;
)paren
suffix:semicolon
id|_exception
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|errcode
op_assign
id|Soft_emulate_8xx
c_func
(paren
id|regs
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Software Emulation 0x%x: 0x%x &quot;
comma
id|regs-&gt;nip
comma
op_star
(paren
(paren
id|uint
op_star
)paren
id|regs-&gt;nip
)paren
)paren
suffix:semicolon
id|print_8xx_pte
c_func
(paren
id|current-&gt;mm
comma
id|regs-&gt;nip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errcode
op_eq
id|EFAULT
)paren
id|_exception
c_func
(paren
id|SIGBUS
comma
id|regs
)paren
suffix:semicolon
r_else
id|_exception
c_func
(paren
id|SIGILL
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;(kernel mode)&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Kernel Mode Software Emulation&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_void
DECL|function|TAUException
id|TAUException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TAU trap at PC: %lx, SR: %lx, vector=%lx&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;msr
comma
id|regs-&gt;trap
)paren
suffix:semicolon
)brace
eof
