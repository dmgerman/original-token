multiline_comment|/*  $Id: process.c,v 1.110 1998/04/08 16:15:51 jj Exp $&n; *  linux/arch/sparc/kernel/process.c&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1996 Eddie C. Dost   (ecd@skynet.be)&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
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
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
r_extern
r_void
id|fpsave
c_func
(paren
r_int
r_int
op_star
comma
r_int
r_int
op_star
comma
r_void
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|srmmu_check_pgt_cache
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|current_set
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
op_assign
(brace
op_amp
id|init_task
comma
)brace
suffix:semicolon
macro_line|#ifndef __SMP__
DECL|macro|SUN4C_FAULT_HIGH
mdefine_line|#define SUN4C_FAULT_HIGH 100
multiline_comment|/*&n; * the idle loop on a Sparc... ;)&n; */
DECL|function|sys_idle
id|asmlinkage
r_int
id|sys_idle
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* endless idle loop with no priority at all */
id|current-&gt;priority
op_assign
op_minus
l_int|100
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
)paren
(brace
r_static
r_int
id|count
op_assign
id|HZ
suffix:semicolon
r_static
r_int
r_int
id|last_jiffies
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|last_faults
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|fps
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|now
suffix:semicolon
r_int
r_int
id|faults
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_extern
r_int
r_int
id|sun4c_kernel_faults
suffix:semicolon
r_extern
r_void
id|sun4c_grow_kernel_ring
c_func
(paren
r_void
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|now
op_assign
id|jiffies
suffix:semicolon
id|count
op_sub_assign
(paren
id|now
op_minus
id|last_jiffies
)paren
suffix:semicolon
id|last_jiffies
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
id|count
op_add_assign
id|HZ
suffix:semicolon
id|faults
op_assign
id|sun4c_kernel_faults
suffix:semicolon
id|fps
op_assign
(paren
id|fps
op_plus
(paren
id|faults
op_minus
id|last_faults
)paren
)paren
op_rshift
l_int|1
suffix:semicolon
id|last_faults
op_assign
id|faults
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;kernel faults / second = %d&bslash;n&quot;
comma
id|fps
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|fps
op_ge
id|SUN4C_FAULT_HIGH
)paren
(brace
id|sun4c_grow_kernel_ring
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|srmmu_check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
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
macro_line|#else
multiline_comment|/* This is being executed in task 0 &squot;user space&squot;. */
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_extern
r_volatile
r_int
id|smp_commenced
suffix:semicolon
id|current-&gt;priority
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
id|srmmu_check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * tq_scheduler currently assumes we&squot;re running in a process&n;&t;&t; * context (ie that we hold the kernel lock..)&n;&t;&t; */
r_if
c_cond
(paren
id|tq_scheduler
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_scheduler
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* endless idle loop with no priority at all */
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smp_commenced
op_logical_or
id|need_resched
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
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
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|cpu_idle
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_char
id|reboot_command
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_CONSOLE
r_extern
r_void
id|console_restore_palette
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
macro_line|#endif
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|8000
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_CONSOLE
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
id|console_restore_palette
(paren
)paren
suffix:semicolon
macro_line|#endif
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Halt failed!&quot;
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|8000
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|strchr
(paren
id|reboot_command
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_CONSOLE
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
id|console_restore_palette
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|cmd
)paren
id|prom_reboot
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|reboot_command
)paren
id|prom_reboot
c_func
(paren
id|reboot_command
)paren
suffix:semicolon
id|prom_feval
(paren
l_string|&quot;reset&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Reboot failed!&quot;
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|auxio_power_register
)paren
op_star
id|auxio_power_register
op_or_assign
id|AUXIO_POWER_OFF
suffix:semicolon
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|show_regwindow
r_void
id|show_regwindow
c_func
(paren
r_struct
id|reg_window
op_star
id|rw
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;l0: %08lx l1: %08lx l2: %08lx l3: %08lx &quot;
l_string|&quot;l4: %08lx l5: %08lx l6: %08lx l7: %08lx&bslash;n&quot;
comma
id|rw-&gt;locals
(braket
l_int|0
)braket
comma
id|rw-&gt;locals
(braket
l_int|1
)braket
comma
id|rw-&gt;locals
(braket
l_int|2
)braket
comma
id|rw-&gt;locals
(braket
l_int|3
)braket
comma
id|rw-&gt;locals
(braket
l_int|4
)braket
comma
id|rw-&gt;locals
(braket
l_int|5
)braket
comma
id|rw-&gt;locals
(braket
l_int|6
)braket
comma
id|rw-&gt;locals
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;i0: %08lx i1: %08lx i2: %08lx i3: %08lx &quot;
l_string|&quot;i4: %08lx i5: %08lx fp: %08lx i7: %08lx&bslash;n&quot;
comma
id|rw-&gt;ins
(braket
l_int|0
)braket
comma
id|rw-&gt;ins
(braket
l_int|1
)braket
comma
id|rw-&gt;ins
(braket
l_int|2
)braket
comma
id|rw-&gt;ins
(braket
l_int|3
)braket
comma
id|rw-&gt;ins
(braket
l_int|4
)braket
comma
id|rw-&gt;ins
(braket
l_int|5
)braket
comma
id|rw-&gt;ins
(braket
l_int|6
)braket
comma
id|rw-&gt;ins
(braket
l_int|7
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef __SMP__
DECL|variable|sparc_backtrace_lock
r_static
id|spinlock_t
id|sparc_backtrace_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#endif
DECL|function|__show_backtrace
r_void
id|__show_backtrace
c_func
(paren
r_int
r_int
id|fp
)paren
(brace
r_struct
id|reg_window
op_star
id|rw
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sparc_backtrace_lock
comma
id|flags
)paren
suffix:semicolon
id|rw
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|fp
suffix:semicolon
r_while
c_loop
(paren
id|rw
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU[%d]: ARGS[%08lx,%08lx,%08lx,%08lx,%08lx,%08lx] &quot;
l_string|&quot;FP[%08lx] CALLER[%08lx]&bslash;n&quot;
comma
id|cpu
comma
id|rw-&gt;ins
(braket
l_int|0
)braket
comma
id|rw-&gt;ins
(braket
l_int|1
)braket
comma
id|rw-&gt;ins
(braket
l_int|2
)braket
comma
id|rw-&gt;ins
(braket
l_int|3
)braket
comma
id|rw-&gt;ins
(braket
l_int|4
)braket
comma
id|rw-&gt;ins
(braket
l_int|5
)braket
comma
id|rw-&gt;ins
(braket
l_int|6
)braket
comma
id|rw-&gt;ins
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|rw
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|rw-&gt;ins
(braket
l_int|6
)braket
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sparc_backtrace_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|show_backtrace
r_void
id|show_backtrace
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|fp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;save %%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;restore&bslash;n&bslash;t&quot;
l_string|&quot;mov %%i6, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fp
)paren
)paren
suffix:semicolon
id|__show_backtrace
c_func
(paren
id|fp
)paren
suffix:semicolon
)brace
macro_line|#ifdef __SMP__
DECL|function|smp_show_backtrace_all_cpus
r_void
id|smp_show_backtrace_all_cpus
c_func
(paren
r_void
)paren
(brace
id|xc0
c_func
(paren
(paren
id|smpfunc_t
)paren
id|show_backtrace
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|show_stackframe
r_void
id|show_stackframe
c_func
(paren
r_struct
id|sparc_stackf
op_star
id|sf
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
op_star
id|stk
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;l0: %08lx l1: %08lx l2: %08lx l3: %08lx &quot;
l_string|&quot;l4: %08lx l5: %08lx l6: %08lx l7: %08lx&bslash;n&quot;
comma
id|sf-&gt;locals
(braket
l_int|0
)braket
comma
id|sf-&gt;locals
(braket
l_int|1
)braket
comma
id|sf-&gt;locals
(braket
l_int|2
)braket
comma
id|sf-&gt;locals
(braket
l_int|3
)braket
comma
id|sf-&gt;locals
(braket
l_int|4
)braket
comma
id|sf-&gt;locals
(braket
l_int|5
)braket
comma
id|sf-&gt;locals
(braket
l_int|6
)braket
comma
id|sf-&gt;locals
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;i0: %08lx i1: %08lx i2: %08lx i3: %08lx &quot;
l_string|&quot;i4: %08lx i5: %08lx fp: %08lx i7: %08lx&bslash;n&quot;
comma
id|sf-&gt;ins
(braket
l_int|0
)braket
comma
id|sf-&gt;ins
(braket
l_int|1
)braket
comma
id|sf-&gt;ins
(braket
l_int|2
)braket
comma
id|sf-&gt;ins
(braket
l_int|3
)braket
comma
id|sf-&gt;ins
(braket
l_int|4
)braket
comma
id|sf-&gt;ins
(braket
l_int|5
)braket
comma
(paren
r_int
r_int
)paren
id|sf-&gt;fp
comma
id|sf-&gt;callers_pc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sp: %08lx x0: %08lx x1: %08lx x2: %08lx &quot;
l_string|&quot;x3: %08lx x4: %08lx x5: %08lx xx: %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|sf-&gt;structptr
comma
id|sf-&gt;xargs
(braket
l_int|0
)braket
comma
id|sf-&gt;xargs
(braket
l_int|1
)braket
comma
id|sf-&gt;xargs
(braket
l_int|2
)braket
comma
id|sf-&gt;xargs
(braket
l_int|3
)braket
comma
id|sf-&gt;xargs
(braket
l_int|4
)braket
comma
id|sf-&gt;xargs
(braket
l_int|5
)braket
comma
id|sf-&gt;xxargs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|size
op_assign
(paren
(paren
r_int
r_int
)paren
id|sf-&gt;fp
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
id|sf
)paren
suffix:semicolon
id|size
op_sub_assign
id|STACKFRAME_SZ
suffix:semicolon
id|stk
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|sf
op_plus
id|STACKFRAME_SZ
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|printk
c_func
(paren
l_string|&quot;s%d: %08lx&bslash;n&quot;
comma
id|i
op_increment
comma
op_star
id|stk
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|size
op_sub_assign
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
suffix:semicolon
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
macro_line|#if __MPP__
id|printk
c_func
(paren
l_string|&quot;CID: %d&bslash;n&quot;
comma
id|mpp_cid
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;PSR: %08lx PC: %08lx NPC: %08lx Y: %08lx&bslash;n&quot;
comma
id|regs-&gt;psr
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
comma
id|regs-&gt;y
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;g0: %08lx g1: %08lx g2: %08lx g3: %08lx &quot;
comma
id|regs-&gt;u_regs
(braket
l_int|0
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|1
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|2
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;g4: %08lx g5: %08lx g6: %08lx g7: %08lx&bslash;n&quot;
comma
id|regs-&gt;u_regs
(braket
l_int|4
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|5
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|6
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;o0: %08lx o1: %08lx o2: %08lx o3: %08lx &quot;
comma
id|regs-&gt;u_regs
(braket
l_int|8
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|9
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|10
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;o4: %08lx o5: %08lx sp: %08lx o7: %08lx&bslash;n&quot;
comma
id|regs-&gt;u_regs
(braket
l_int|12
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|13
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|14
)braket
comma
id|regs-&gt;u_regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|show_regwindow
c_func
(paren
(paren
r_struct
id|reg_window
op_star
)paren
id|regs-&gt;u_regs
(braket
l_int|14
)braket
)paren
suffix:semicolon
)brace
macro_line|#if NOTUSED
DECL|function|show_thread
r_void
id|show_thread
c_func
(paren
r_struct
id|thread_struct
op_star
id|tss
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;uwinmask:          0x%08lx  kregs:             0x%08lx&bslash;n&quot;
comma
id|tss-&gt;uwinmask
comma
(paren
r_int
r_int
)paren
id|tss-&gt;kregs
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|tss-&gt;kregs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sig_address:       0x%08lx  sig_desc:          0x%08lx&bslash;n&quot;
comma
id|tss-&gt;sig_address
comma
id|tss-&gt;sig_desc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ksp:               0x%08lx  kpc:               0x%08lx&bslash;n&quot;
comma
id|tss-&gt;ksp
comma
id|tss-&gt;kpc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kpsr:              0x%08lx  kwim:              0x%08lx&bslash;n&quot;
comma
id|tss-&gt;kpsr
comma
id|tss-&gt;kwim
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fork_kpsr:         0x%08lx  fork_kwim:         0x%08lx&bslash;n&quot;
comma
id|tss-&gt;fork_kpsr
comma
id|tss-&gt;fork_kwim
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NSWINS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tss-&gt;rwbuf_stkptrs
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;reg_window[%d]:&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;stack ptr:         0x%08lx&bslash;n&quot;
comma
id|tss-&gt;rwbuf_stkptrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|show_regwindow
c_func
(paren
op_amp
id|tss-&gt;reg_window
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;w_saved:           0x%08lx&bslash;n&quot;
comma
id|tss-&gt;w_saved
)paren
suffix:semicolon
multiline_comment|/* XXX missing: float_regs */
id|printk
c_func
(paren
l_string|&quot;fsr:               0x%08lx  fpqdepth:          0x%08lx&bslash;n&quot;
comma
id|tss-&gt;fsr
comma
id|tss-&gt;fpqdepth
)paren
suffix:semicolon
multiline_comment|/* XXX missing: fpqueue */
id|printk
c_func
(paren
l_string|&quot;sstk_info.stack:   0x%08lx  sstk_info.status:  0x%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|tss-&gt;sstk_info.the_stack
comma
(paren
r_int
r_int
)paren
id|tss-&gt;sstk_info.cur_status
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;flags:             0x%08lx  current_ds:        0x%08lx&bslash;n&quot;
comma
id|tss-&gt;flags
comma
id|tss-&gt;current_ds.seg
)paren
suffix:semicolon
id|show_regwindow
c_func
(paren
(paren
r_struct
id|reg_window
op_star
)paren
id|tss-&gt;ksp
)paren
suffix:semicolon
multiline_comment|/* XXX missing: core_exec */
)brace
macro_line|#endif
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef __SMP__
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
macro_line|#endif
multiline_comment|/* Keep process from leaving FPU in a bogon state. */
id|put_psr
c_func
(paren
id|get_psr
c_func
(paren
)paren
op_or
id|PSR_EF
)paren
suffix:semicolon
id|fpsave
c_func
(paren
op_amp
id|current-&gt;tss.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.fsr
comma
op_amp
id|current-&gt;tss.fpqueue
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.fpqdepth
)paren
suffix:semicolon
macro_line|#ifndef __SMP__
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
macro_line|#else
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
id|current-&gt;tss.w_saved
op_assign
l_int|0
suffix:semicolon
id|current-&gt;tss.sstk_info.cur_status
op_assign
l_int|0
suffix:semicolon
id|current-&gt;tss.sstk_info.the_stack
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No new signal delivery by default */
id|current-&gt;tss.new_signal
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef __SMP__
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
macro_line|#endif
multiline_comment|/* Clean the fpu. */
id|put_psr
c_func
(paren
id|get_psr
c_func
(paren
)paren
op_or
id|PSR_EF
)paren
suffix:semicolon
id|fpsave
c_func
(paren
op_amp
id|current-&gt;tss.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.fsr
comma
op_amp
id|current-&gt;tss.fpqueue
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.fpqdepth
)paren
suffix:semicolon
macro_line|#ifndef __SMP__
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
macro_line|#else
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Now, this task is no longer a kernel thread. */
id|current-&gt;tss.current_ds
op_assign
id|USER_DS
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_KTHREAD
)paren
(brace
id|current-&gt;tss.flags
op_and_assign
op_complement
id|SPARC_FLAG_KTHREAD
suffix:semicolon
id|switch_to_context
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
)brace
DECL|function|copy_regs
r_static
id|__inline__
r_void
id|copy_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|dst
comma
r_struct
id|pt_regs
op_star
id|src
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd&bslash;t[%1 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x10], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%o4, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x18], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x20], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x28], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x18]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x20]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%o4, [%0 + 0x28]&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x30], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x38], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x40], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x30]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x38]&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x48], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%o4, [%0 + 0x40]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x48]&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;r&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
)paren
suffix:semicolon
)brace
DECL|function|copy_regwin
r_static
id|__inline__
r_void
id|copy_regwin
c_func
(paren
r_struct
id|reg_window
op_star
id|dst
comma
r_struct
id|reg_window
op_star
id|src
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldd&bslash;t[%1 + 0x00], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x08], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x10], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%o4, [%0 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x18], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x20], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x28], %%o4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x18]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x20]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%o4, [%0 + 0x28]&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x30], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ldd&bslash;t[%1 + 0x38], %%g4&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g2, [%0 + 0x30]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g4, [%0 + 0x38]&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|dst
)paren
comma
l_string|&quot;r&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_struct
id|sparc_stackf
op_star
DECL|function|clone_stackframe
id|clone_stackframe
c_func
(paren
r_struct
id|sparc_stackf
op_star
id|dst
comma
r_struct
id|sparc_stackf
op_star
id|src
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_struct
id|sparc_stackf
op_star
id|sp
suffix:semicolon
id|size
op_assign
(paren
(paren
r_int
r_int
)paren
id|src-&gt;fp
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
id|src
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_struct
id|sparc_stackf
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|dst
)paren
op_minus
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|sp
comma
id|src
comma
id|size
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|dst
comma
op_amp
id|sp-&gt;fp
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/* Copy a Sparc thread.  The fork() return value conventions&n; * under SunOS are nothing short of bletcherous:&n; * Parent --&gt;  %o0 == childs  pid, %o1 == 0&n; * Child  --&gt;  %o0 == parents pid, %o1 == 1&n; *&n; * NOTE: We have a separate fork kpsr/kwim because&n; *       the parent could change these values between&n; *       sys_fork invocation and when we reach here&n; *       if the parent should sleep while trying to&n; *       allocate the task_struct and kernel stack in&n; *       do_fork().&n; */
macro_line|#ifdef __SMP__
r_extern
r_void
id|ret_from_smpfork
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
r_extern
r_void
id|ret_from_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
id|sp
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
id|reg_window
op_star
id|new_stack
suffix:semicolon
r_int
r_int
id|stack_offset
suffix:semicolon
macro_line|#ifndef __SMP__
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
macro_line|#endif
id|put_psr
c_func
(paren
id|get_psr
c_func
(paren
)paren
op_or
id|PSR_EF
)paren
suffix:semicolon
id|fpsave
c_func
(paren
op_amp
id|p-&gt;tss.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|p-&gt;tss.fsr
comma
op_amp
id|p-&gt;tss.fpqueue
(braket
l_int|0
)braket
comma
op_amp
id|p-&gt;tss.fpqdepth
)paren
suffix:semicolon
macro_line|#ifdef __SMP__
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Calculate offset to stack_frame &amp; pt_regs */
id|stack_offset
op_assign
id|TASK_UNION_SIZE
op_minus
id|TRACEREG_SZ
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
(brace
id|stack_offset
op_sub_assign
id|REGWIN_SZ
suffix:semicolon
)brace
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
(paren
r_int
r_int
)paren
id|p
)paren
op_plus
id|stack_offset
)paren
)paren
suffix:semicolon
id|copy_regs
c_func
(paren
id|childregs
comma
id|regs
)paren
suffix:semicolon
id|new_stack
op_assign
(paren
(paren
(paren
r_struct
id|reg_window
op_star
)paren
id|childregs
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|copy_regwin
c_func
(paren
id|new_stack
comma
(paren
(paren
(paren
r_struct
id|reg_window
op_star
)paren
id|regs
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|p-&gt;tss.ksp
op_assign
(paren
r_int
r_int
)paren
id|new_stack
suffix:semicolon
macro_line|#ifdef __SMP__
id|p-&gt;tss.kpc
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|ret_from_smpfork
)paren
op_minus
l_int|0x8
)paren
suffix:semicolon
id|p-&gt;tss.kpsr
op_assign
id|current-&gt;tss.fork_kpsr
op_or
id|PSR_PIL
suffix:semicolon
macro_line|#else
id|p-&gt;tss.kpc
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|ret_from_syscall
)paren
op_minus
l_int|0x8
)paren
suffix:semicolon
id|p-&gt;tss.kpsr
op_assign
id|current-&gt;tss.fork_kpsr
suffix:semicolon
macro_line|#endif
id|p-&gt;tss.kwim
op_assign
id|current-&gt;tss.fork_kwim
suffix:semicolon
id|p-&gt;tss.kregs
op_assign
id|childregs
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
(brace
id|childregs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_assign
id|p-&gt;tss.ksp
suffix:semicolon
id|p-&gt;tss.flags
op_or_assign
id|SPARC_FLAG_KTHREAD
suffix:semicolon
id|p-&gt;tss.current_ds
op_assign
id|KERNEL_DS
suffix:semicolon
id|childregs-&gt;u_regs
(braket
id|UREG_G6
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
)brace
r_else
(brace
id|childregs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_assign
id|sp
suffix:semicolon
id|p-&gt;tss.flags
op_and_assign
op_complement
id|SPARC_FLAG_KTHREAD
suffix:semicolon
id|p-&gt;tss.current_ds
op_assign
id|USER_DS
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_ne
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
)paren
(brace
r_struct
id|sparc_stackf
op_star
id|childstack
suffix:semicolon
r_struct
id|sparc_stackf
op_star
id|parentstack
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * This is a clone() call with supplied user stack.&n;&t;&t;&t; * Set some valid stack frames to give to the child.&n;&t;&t;&t; */
id|childstack
op_assign
(paren
r_struct
id|sparc_stackf
op_star
)paren
id|sp
suffix:semicolon
id|parentstack
op_assign
(paren
r_struct
id|sparc_stackf
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;clone: parent stack:&bslash;n&quot;
)paren
suffix:semicolon
id|show_stackframe
c_func
(paren
id|parentstack
)paren
suffix:semicolon
macro_line|#endif
id|childstack
op_assign
id|clone_stackframe
c_func
(paren
id|childstack
comma
id|parentstack
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|childstack
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;clone: child stack:&bslash;n&quot;
)paren
suffix:semicolon
id|show_stackframe
c_func
(paren
id|childstack
)paren
suffix:semicolon
macro_line|#endif
id|childregs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_assign
(paren
r_int
r_int
)paren
id|childstack
suffix:semicolon
)brace
)brace
multiline_comment|/* Set the return value for the child. */
id|childregs-&gt;u_regs
(braket
id|UREG_I0
)braket
op_assign
id|current-&gt;pid
suffix:semicolon
id|childregs-&gt;u_regs
(braket
id|UREG_I1
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Set the return value for the parent. */
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
op_assign
l_int|0
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
r_int
r_int
id|first_stack_page
suffix:semicolon
id|dump-&gt;magic
op_assign
id|SUNOS_CORE_MAGIC
suffix:semicolon
id|dump-&gt;len
op_assign
r_sizeof
(paren
r_struct
id|user
)paren
suffix:semicolon
id|dump-&gt;regs.psr
op_assign
id|regs-&gt;psr
suffix:semicolon
id|dump-&gt;regs.pc
op_assign
id|regs-&gt;pc
suffix:semicolon
id|dump-&gt;regs.npc
op_assign
id|regs-&gt;npc
suffix:semicolon
id|dump-&gt;regs.y
op_assign
id|regs-&gt;y
suffix:semicolon
multiline_comment|/* fuck me plenty */
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs.regs
(braket
l_int|0
)braket
comma
op_amp
id|regs-&gt;u_regs
(braket
l_int|1
)braket
comma
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|15
)paren
)paren
suffix:semicolon
id|dump-&gt;uexec
op_assign
id|current-&gt;tss.core_exec
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;start_code
)paren
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|dump-&gt;u_dsize
op_sub_assign
id|dump-&gt;u_tsize
suffix:semicolon
id|dump-&gt;u_dsize
op_and_assign
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|first_stack_page
op_assign
(paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
(paren
id|TASK_SIZE
op_minus
id|first_stack_page
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;fpu.fpstatus.fregs.regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.float_regs
(braket
l_int|0
)braket
comma
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|32
)paren
)paren
suffix:semicolon
id|dump-&gt;fpu.fpstatus.fsr
op_assign
id|current-&gt;tss.fsr
suffix:semicolon
id|dump-&gt;fpu.fpstatus.flags
op_assign
id|dump-&gt;fpu.fpstatus.extra
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;fpu.fpstatus.fpq_count
op_assign
id|current-&gt;tss.fpqdepth
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;fpu.fpstatus.fpq
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;tss.fpqueue
(braket
l_int|0
)braket
comma
(paren
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|2
)paren
op_star
l_int|16
)paren
)paren
suffix:semicolon
id|dump-&gt;sigcode
op_assign
id|current-&gt;tss.sig_desc
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the fpu structure for a core dump.&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
(brace
multiline_comment|/* Currently we report that we couldn&squot;t dump the fpu structure */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sparc_execve() executes a new program after the asm stub has set&n; * things up for us.  This should basically do what I want it to.&n; */
DECL|function|sparc_execve
id|asmlinkage
r_int
id|sparc_execve
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|error
comma
id|base
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
multiline_comment|/* Check for indirect call. */
r_if
c_cond
(paren
id|regs-&gt;u_regs
(braket
id|UREG_G1
)braket
op_eq
l_int|0
)paren
(brace
id|base
op_assign
l_int|1
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|regs-&gt;u_regs
(braket
id|base
op_plus
id|UREG_I0
)braket
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
(brace
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;u_regs
(braket
id|base
op_plus
id|UREG_I1
)braket
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;u_regs
(braket
id|base
op_plus
id|UREG_I2
)braket
comma
id|regs
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
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
id|error
suffix:semicolon
)brace
eof
