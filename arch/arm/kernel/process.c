multiline_comment|/*&n; *  linux/arch/arm/kernel/process.c&n; *&n; *  Copyright (C) 1996 Russell King - Converted to ARM.&n; *  Origional Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_char
op_star
id|processor_modes
(braket
)braket
suffix:semicolon
id|asmlinkage
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_sys_call&quot;
)paren
suffix:semicolon
DECL|variable|hlt_counter
r_static
r_int
id|hlt_counter
op_assign
l_int|0
suffix:semicolon
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
multiline_comment|/*&n; * The idle loop on an ARM...&n; */
DECL|function|sys_idle
id|asmlinkage
r_int
id|sys_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* endless idle loop with no priority at all */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
op_logical_and
op_logical_neg
id|hlt_counter
)paren
id|proc_idle
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;policy
op_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_NO_PGT_CACHE
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|variable|reboot_mode
r_static
r_char
id|reboot_mode
op_assign
l_char|&squot;h&squot;
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|reboot_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
)paren
(brace
id|reboot_mode
op_assign
id|str
(braket
l_int|0
)braket
suffix:semicolon
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
id|arch_reset
c_func
(paren
id|reboot_mode
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Reboot failed&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
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
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|condition_codes
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pc : [&lt;%08lx&gt;]    lr : [&lt;%08lx&gt;]&bslash;n&quot;
l_string|&quot;sp : %08lx  ip : %08lx  fp : %08lx&bslash;n&quot;
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
comma
id|regs-&gt;ARM_lr
comma
id|regs-&gt;ARM_sp
comma
id|regs-&gt;ARM_ip
comma
id|regs-&gt;ARM_fp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r10: %08lx  r9 : %08lx  r8 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r10
comma
id|regs-&gt;ARM_r9
comma
id|regs-&gt;ARM_r8
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r7
comma
id|regs-&gt;ARM_r6
comma
id|regs-&gt;ARM_r5
comma
id|regs-&gt;ARM_r4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r3
comma
id|regs-&gt;ARM_r2
comma
id|regs-&gt;ARM_r1
comma
id|regs-&gt;ARM_r0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Flags: %c%c%c%c&quot;
comma
id|flags
op_amp
id|CC_N_BIT
ques
c_cond
l_char|&squot;N&squot;
suffix:colon
l_char|&squot;n&squot;
comma
id|flags
op_amp
id|CC_Z_BIT
ques
c_cond
l_char|&squot;Z&squot;
suffix:colon
l_char|&squot;z&squot;
comma
id|flags
op_amp
id|CC_C_BIT
ques
c_cond
l_char|&squot;C&squot;
suffix:colon
l_char|&squot;c&squot;
comma
id|flags
op_amp
id|CC_V_BIT
ques
c_cond
l_char|&squot;V&squot;
suffix:colon
l_char|&squot;v&squot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  IRQs %s  FIQs %s  Mode %s  Segment %s&bslash;n&quot;
comma
id|interrupts_enabled
c_func
(paren
id|regs
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|fast_interrupts_enabled
c_func
(paren
id|regs
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|processor_modes
(braket
id|processor_mode
c_func
(paren
id|regs
)paren
)braket
comma
id|get_fs
c_func
(paren
)paren
op_eq
id|get_ds
c_func
(paren
)paren
ques
c_cond
l_string|&quot;kernel&quot;
suffix:colon
l_string|&quot;user&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_32)
(brace
r_int
id|ctrl
comma
id|transbase
comma
id|dac
suffix:semicolon
id|__asm__
(paren
l_string|&quot;&t;mrc p15, 0, %0, c1, c0&bslash;n&quot;
l_string|&quot;&t;mrc p15, 0, %1, c2, c0&bslash;n&quot;
l_string|&quot;&t;mrc p15, 0, %2, c3, c0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctrl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|transbase
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dac
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Control: %04X  Table: %08X  DAC: %08X&bslash;n&quot;
comma
id|ctrl
comma
id|transbase
comma
id|dac
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * Task structure and kernel stack allocation.&n; *&n; * Taken from the i386 version.&n; */
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|EXTRA_TASK_STRUCT
mdefine_line|#define EXTRA_TASK_STRUCT&t;8
DECL|variable|task_struct_stack
r_static
r_struct
id|task_struct
op_star
id|task_struct_stack
(braket
id|EXTRA_TASK_STRUCT
)braket
suffix:semicolon
DECL|variable|task_struct_stack_ptr
r_static
r_int
id|task_struct_stack_ptr
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
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
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
macro_line|#ifndef EXTRA_TASK_STRUCT
id|tsk
op_assign
id|ll_alloc_task_struct
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_int
id|index
suffix:semicolon
id|index
op_assign
id|task_struct_stack_ptr
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
id|EXTRA_TASK_STRUCT
op_div
l_int|2
)paren
r_goto
id|use_cache
suffix:semicolon
id|tsk
op_assign
id|ll_alloc_task_struct
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
(brace
id|index
op_assign
id|task_struct_stack_ptr
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
l_int|0
)paren
(brace
id|use_cache
suffix:colon
id|tsk
op_assign
id|task_struct_stack
(braket
id|index
)braket
suffix:semicolon
id|task_struct_stack_ptr
op_assign
id|index
op_minus
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SYSRQ
multiline_comment|/* You need this if you want SYSRQ-T to give sensible stack&n;&t; * usage information&n;&t; */
r_if
c_cond
(paren
id|tsk
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|tsk
suffix:semicolon
id|memzero
c_func
(paren
id|p
op_plus
id|KERNEL_STACK_SIZE
comma
id|KERNEL_STACK_SIZE
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|tsk
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
macro_line|#ifdef EXTRA_TASK_STRUCT
r_int
id|index
op_assign
id|task_struct_stack_ptr
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|EXTRA_TASK_STRUCT
)paren
(brace
id|task_struct_stack
(braket
id|index
)braket
op_assign
id|p
suffix:semicolon
id|task_struct_stack_ptr
op_assign
id|index
suffix:semicolon
)brace
r_else
macro_line|#endif
id|ll_free_task_struct
c_func
(paren
id|p
)paren
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
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|current-&gt;tss.debug
comma
l_int|0
comma
r_sizeof
(paren
id|current-&gt;tss.debug
)paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
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
)brace
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
id|esp
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
r_struct
id|context_save_struct
op_star
id|save
suffix:semicolon
id|childregs
op_assign
(paren
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
id|p
op_plus
l_int|8192
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
id|childregs-&gt;ARM_r0
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;ARM_sp
op_assign
id|esp
suffix:semicolon
id|save
op_assign
(paren
(paren
r_struct
id|context_save_struct
op_star
)paren
(paren
id|childregs
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|init_thread_css
c_func
(paren
id|save
)paren
suffix:semicolon
id|p-&gt;tss.save
op_assign
id|save
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the fpe structure for a core dump...&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user_fp
op_star
id|fp
)paren
(brace
r_int
id|fpvalid
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
id|memcpy
(paren
id|fp
comma
op_amp
id|current-&gt;tss.fpstate.soft
comma
r_sizeof
(paren
id|fp
)paren
)paren
suffix:semicolon
r_return
id|fpvalid
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
id|dump-&gt;start_stack
op_assign
id|regs-&gt;ARM_sp
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
id|current-&gt;mm-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|current-&gt;mm-&gt;brk
op_minus
id|current-&gt;mm-&gt;start_data
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|0
)braket
op_assign
id|current-&gt;tss.debug.bp
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|1
)braket
op_assign
id|current-&gt;tss.debug.bp
(braket
l_int|1
)braket
dot
id|address
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|2
)braket
op_assign
id|current-&gt;tss.debug.bp
(braket
l_int|0
)braket
dot
id|insn
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|3
)braket
op_assign
id|current-&gt;tss.debug.bp
(braket
l_int|1
)braket
dot
id|insn
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|4
)braket
op_assign
id|current-&gt;tss.debug.nsaved
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
l_int|0x04000000
)paren
id|dump-&gt;u_ssize
op_assign
(paren
l_int|0x04000000
op_minus
id|dump-&gt;start_stack
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;u_fp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE! Only a kernel-only process(ie the swapper or direct descendants&n; * who haven&squot;t done an &quot;execve()&quot;) should use this: it will work within&n; * a system call from a &quot;real&quot; process, but the process memory space will&n; * not be free&squot;d until both the parent and the child have exited.&n; */
DECL|function|kernel_thread
id|pid_t
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
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
id|pid_t
id|__ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;r0, %1&t;&t;@ kernel_thread sys_clone&bslash;n&quot;
l_string|&quot;&t;mov&t;r1, #0&bslash;n&quot;
id|__syscall
c_func
(paren
id|clone
)paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;mov&t;%0, r0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__ret
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|flags
op_or
id|CLONE_VM
)paren
suffix:colon
l_string|&quot;r0&quot;
comma
l_string|&quot;r1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__ret
op_eq
l_int|0
)paren
id|sys_exit
c_func
(paren
(paren
id|fn
)paren
(paren
id|arg
)paren
)paren
suffix:semicolon
r_return
id|__ret
suffix:semicolon
)brace
eof
