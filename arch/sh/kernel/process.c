multiline_comment|/* $Id: process.c,v 1.33 2000/03/25 00:06:15 gniibe Exp $&n; *&n; *  linux/arch/sh/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  SuperH version:  Copyright (C) 1999, 2000  Niibe Yutaka &amp; Kaz Kojima&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
DECL|variable|hlt_counter
r_static
r_int
id|hlt_counter
op_assign
l_int|0
suffix:semicolon
DECL|macro|HARD_IDLE_TIMEOUT
mdefine_line|#define HARD_IDLE_TIMEOUT (HZ / 3)
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_increment
suffix:semicolon
)brace
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n; * The idle loop on a uniprocessor i386..&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|init_idle
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;nice
op_assign
l_int|20
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
(brace
r_if
c_cond
(paren
id|hlt_counter
)paren
r_continue
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sleep&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
multiline_comment|/* Need to set MMU_TTB?? */
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|show_regs
r_void
id|show_regs
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC  : %08lx SP  : %08lx SR  : %08lx TEA : %08lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;regs
(braket
l_int|15
)braket
comma
id|regs-&gt;sr
comma
id|ctrl_inl
c_func
(paren
id|MMU_TEA
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R0  : %08lx R1  : %08lx R2  : %08lx R3  : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|0
)braket
comma
id|regs-&gt;regs
(braket
l_int|1
)braket
comma
id|regs-&gt;regs
(braket
l_int|2
)braket
comma
id|regs-&gt;regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R4  : %08lx R5  : %08lx R6  : %08lx R7  : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|4
)braket
comma
id|regs-&gt;regs
(braket
l_int|5
)braket
comma
id|regs-&gt;regs
(braket
l_int|6
)braket
comma
id|regs-&gt;regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R8  : %08lx R9  : %08lx R10 : %08lx R11 : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|8
)braket
comma
id|regs-&gt;regs
(braket
l_int|9
)braket
comma
id|regs-&gt;regs
(braket
l_int|10
)braket
comma
id|regs-&gt;regs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R12 : %08lx R13 : %08lx R14 : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|12
)braket
comma
id|regs-&gt;regs
(braket
l_int|13
)braket
comma
id|regs-&gt;regs
(braket
l_int|14
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MACH: %08lx MACL: %08lx GBR : %08lx PR  : %08lx&bslash;n&quot;
comma
id|regs-&gt;mach
comma
id|regs-&gt;macl
comma
id|regs-&gt;gbr
comma
id|regs-&gt;pr
)paren
suffix:semicolon
)brace
DECL|function|alloc_task_struct
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Get two pages */
r_return
(paren
r_struct
id|task_struct
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|free_task_struct
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE! Only a kernel-only process(ie the swapper or direct descendants&n; * who haven&squot;t done an &quot;execve()&quot;) should use this: it will work within&n; * a system call from a &quot;real&quot; process, but the process memory space will&n; * not be free&squot;d until both the parent and the child have exited.&n; */
DECL|function|kernel_thread
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
multiline_comment|/* Don&squot;t use this in BL=1(cli).  Or else, CPU resets! */
r_register
r_int
r_int
id|__sc0
id|__asm__
(paren
l_string|&quot;r0&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|__sc3
id|__asm__
(paren
l_string|&quot;r3&quot;
)paren
op_assign
id|__NR_clone
suffix:semicolon
r_register
r_int
r_int
id|__sc4
id|__asm__
(paren
l_string|&quot;r4&quot;
)paren
op_assign
(paren
r_int
)paren
id|flags
op_or
id|CLONE_VM
suffix:semicolon
r_register
r_int
r_int
id|__sc5
id|__asm__
(paren
l_string|&quot;r5&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_register
r_int
r_int
id|__sc8
id|__asm__
(paren
l_string|&quot;r8&quot;
)paren
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_register
r_int
r_int
id|__sc9
id|__asm__
(paren
l_string|&quot;r9&quot;
)paren
op_assign
(paren
r_int
)paren
id|fn
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;trapa&t;#0x12&bslash;n&bslash;t&quot;
multiline_comment|/* Linux/SH system call */
l_string|&quot;tst&t;#0xff, $r0&bslash;n&bslash;t&quot;
multiline_comment|/* child or parent? */
l_string|&quot;bf&t;1f&bslash;n&bslash;t&quot;
multiline_comment|/* parent - jump */
l_string|&quot;jsr&t;@$r9&bslash;n&bslash;t&quot;
multiline_comment|/* call fn */
l_string|&quot; mov&t;$r8, $r4&bslash;n&bslash;t&quot;
multiline_comment|/* push argument */
l_string|&quot;mov&t;$r0, $r4&bslash;n&bslash;t&quot;
multiline_comment|/* return value to arg of exit */
l_string|&quot;mov&t;%1, $r3&bslash;n&bslash;t&quot;
multiline_comment|/* exit */
l_string|&quot;trapa&t;#0x11&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=z&quot;
(paren
id|__sc0
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;r&quot;
(paren
id|__sc3
)paren
comma
l_string|&quot;r&quot;
(paren
id|__sc4
)paren
comma
l_string|&quot;r&quot;
(paren
id|__sc5
)paren
comma
l_string|&quot;r&quot;
(paren
id|__sc8
)paren
comma
l_string|&quot;r&quot;
(paren
id|__sc9
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|__sc0
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do. */
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(__sh3__)
multiline_comment|/* do nothing */
multiline_comment|/* Possibly, set clear debug registers */
macro_line|#elif defined(__SH4__)
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
multiline_comment|/* Forget lazy FPU state */
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
multiline_comment|/* do nothing */
)brace
multiline_comment|/* Fill in the fpu structure for a core dump.. */
DECL|function|dump_fpu
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
macro_line|#if defined(__SH4__)
r_int
id|fpvalid
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|fpvalid
op_assign
id|tsk-&gt;used_math
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.fpu.hard
comma
r_sizeof
(paren
op_star
id|fpu
)paren
)paren
suffix:semicolon
)brace
r_return
id|fpvalid
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Task didn&squot;t use the fpu at all. */
macro_line|#endif
)brace
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|copy_thread
r_int
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_int
r_int
id|unused
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
macro_line|#if defined(__SH4__)
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
id|tsk
op_ne
op_amp
id|init_task
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|p-&gt;thread.fpu
op_assign
id|current-&gt;thread.fpu
suffix:semicolon
id|p-&gt;used_math
op_assign
id|tsk-&gt;used_math
suffix:semicolon
)brace
macro_line|#endif
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|THREAD_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p
)paren
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
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
id|childregs-&gt;regs
(braket
l_int|15
)braket
op_assign
id|usp
suffix:semicolon
)brace
r_else
(brace
id|childregs-&gt;regs
(braket
l_int|15
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
op_plus
l_int|2
op_star
id|PAGE_SIZE
suffix:semicolon
)brace
id|childregs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set return value for child */
id|childregs-&gt;sr
op_or_assign
id|SR_FD
suffix:semicolon
multiline_comment|/* Invalidate FPU flag */
id|p-&gt;thread.sp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.pc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
id|current-&gt;mm-&gt;start_code
suffix:semicolon
id|dump-&gt;start_data
op_assign
id|current-&gt;mm-&gt;start_data
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;regs
(braket
l_int|15
)braket
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
id|current-&gt;mm-&gt;end_code
op_minus
id|dump-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
id|dump-&gt;start_data
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
(paren
id|current-&gt;mm-&gt;start_stack
op_minus
id|dump-&gt;start_stack
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Debug registers will come here. */
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
c_func
(paren
id|regs
comma
op_amp
id|dump-&gt;fpu
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;switch_to(x,y) should switch tasks from x to y.&n; *&n; */
DECL|function|__switch_to
r_void
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
id|next
)paren
(brace
macro_line|#if defined(__SH4__)
r_if
c_cond
(paren
id|prev
op_ne
op_amp
id|init_task
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|prev
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Restore the kernel mode register&n;&t; *   &t;k7 (r7_bank1)&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;ldc&t;%0, $r7_bank&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|next
)paren
)paren
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|newsp
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.regs
(braket
l_int|15
)braket
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|ufilename
comma
r_char
op_star
op_star
id|uargv
comma
r_char
op_star
op_star
id|uenvp
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
id|ufilename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
id|uargv
comma
id|uenvp
comma
op_amp
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long) scheduling_functions_end_here)
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|schedule_frame
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The same comment as on the Alpha applies here, too ...&n;&t; */
id|pc
op_assign
id|thread_saved_pc
c_func
(paren
op_amp
id|p-&gt;thread
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|interruptible_sleep_on
op_logical_and
id|pc
OL
(paren
r_int
r_int
)paren
id|add_timer
)paren
(brace
id|schedule_frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
(paren
r_int
)paren
id|p-&gt;thread.sp
)paren
(braket
l_int|1
)braket
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|schedule_frame
)paren
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_return
id|pc
suffix:semicolon
)brace
DECL|function|print_syscall
id|asmlinkage
r_void
id|print_syscall
c_func
(paren
r_int
id|x
)paren
(brace
r_int
r_int
id|flags
comma
id|sr
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;stc&t;$sr, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sr
)paren
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%c: %c %c, %c: SYSCALL&bslash;n&quot;
comma
(paren
id|x
op_amp
l_int|63
)paren
op_plus
l_int|32
comma
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
ques
c_cond
l_char|&squot;C&squot;
suffix:colon
l_char|&squot; &squot;
comma
(paren
id|init_task.flags
op_amp
id|PF_USEDFPU
)paren
ques
c_cond
l_char|&squot;K&squot;
suffix:colon
l_char|&squot; &squot;
comma
(paren
id|sr
op_amp
id|SR_FD
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;F&squot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|break_point_trap
id|asmlinkage
r_void
id|break_point_trap
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
multiline_comment|/* Clear tracing.  */
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRA
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRB
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|break_point_trap_software
id|asmlinkage
r_void
id|break_point_trap_software
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
id|regs.pc
op_sub_assign
l_int|2
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
eof
