multiline_comment|/*&n; *  linux/arch/alpha/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#ifdef CONFIG_RTC
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;bios32.h&quot;
multiline_comment|/*&n; * Initial task structure. Make this a per-architecture thing,&n; * because different architectures tend to have different&n; * alignment requirements and potentially different initial&n; * setup.&n; */
DECL|variable|init_user_stack
r_int
r_int
id|init_user_stack
(braket
l_int|1024
)braket
op_assign
(brace
id|STACK_MAGIC
comma
)brace
suffix:semicolon
DECL|variable|init_mmap
r_static
r_struct
id|vm_area_struct
id|init_mmap
op_assign
id|INIT_MMAP
suffix:semicolon
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
suffix:semicolon
DECL|variable|init_fd_array
r_static
r_struct
id|file
op_star
id|init_fd_array
(braket
id|NR_OPEN
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|init_files
r_static
r_struct
id|files_struct
id|init_files
op_assign
id|INIT_FILES
suffix:semicolon
DECL|variable|init_signals
r_static
r_struct
id|signal_struct
id|init_signals
op_assign
id|INIT_SIGNALS
suffix:semicolon
DECL|variable|init_mm
r_struct
id|mm_struct
id|init_mm
op_assign
id|INIT_MM
suffix:semicolon
DECL|variable|init_task_union
r_union
id|task_union
id|init_task_union
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;init_task&quot;
)paren
)paren
)paren
op_assign
(brace
id|task
suffix:colon
id|INIT_TASK
)brace
suffix:semicolon
multiline_comment|/*&n; * No need to acquire the kernel lock, we&squot;re entirely local..&n; */
id|asmlinkage
r_int
DECL|function|sys_sethae
id|sys_sethae
c_func
(paren
r_int
r_int
id|hae
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
(paren
op_amp
id|regs
)paren
op_member_access_from_pointer
id|hae
op_assign
id|hae
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
DECL|function|do_cpu_idle
id|do_cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* An endless idle loop with no priority at all.  */
id|current-&gt;priority
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|check_pgt_cache
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
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef __SMP__
r_void
DECL|function|cpu_idle
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|do_cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|asmlinkage
r_int
DECL|function|sys_idle
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
op_eq
l_int|0
)paren
id|do_cpu_idle
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_void
DECL|function|generic_kill_arch
id|generic_kill_arch
(paren
r_int
id|mode
comma
r_char
op_star
id|restart_cmd
)paren
(brace
multiline_comment|/* The following currently only has any effect on SRM.  We should&n;&t;   fix MILO to understand it.  Should be pretty easy.  Also we can&n;&t;   support RESTART2 via the ipc_buffer machinations pictured below,&n;&t;   which SRM ignores.  */
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
r_struct
id|percpu_struct
op_star
id|cpup
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|cpup
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
id|flags
op_assign
id|cpup-&gt;flags
suffix:semicolon
multiline_comment|/* Clear reason to &quot;default&quot;; clear &quot;bootstrap in progress&quot;. */
id|flags
op_and_assign
op_complement
l_int|0x00ff0001UL
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|LINUX_REBOOT_CMD_RESTART
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|restart_cmd
)paren
(brace
id|flags
op_or_assign
l_int|0x00020000UL
suffix:semicolon
multiline_comment|/* &quot;cold bootstrap&quot; */
id|cpup-&gt;ipc_buffer
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|flags
op_or_assign
l_int|0x00030000UL
suffix:semicolon
multiline_comment|/* &quot;warm bootstrap&quot; */
id|strncpy
c_func
(paren
(paren
r_char
op_star
)paren
id|cpup-&gt;ipc_buffer
comma
id|restart_cmd
comma
r_sizeof
(paren
id|cpup-&gt;ipc_buffer
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|flags
op_or_assign
l_int|0x00040000UL
suffix:semicolon
multiline_comment|/* &quot;remain halted&quot; */
)brace
id|cpup-&gt;flags
op_assign
id|flags
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|reset_for_srm
c_func
(paren
)paren
suffix:semicolon
id|set_hae
c_func
(paren
id|srm_hae
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
multiline_comment|/* This has the effect of reseting the VGA video origin.  */
id|take_over_console
c_func
(paren
op_amp
id|dummy_con
comma
l_int|0
comma
id|MAX_NR_CONSOLES
op_minus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_RTC
multiline_comment|/* Reset rtc to defaults.  */
(brace
r_int
r_char
id|control
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Reset periodic interrupt frequency.  */
id|CMOS_WRITE
c_func
(paren
l_int|0x26
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* Turn on periodic interrupts.  */
id|control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
id|control
op_or_assign
id|RTC_PIE
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|alpha_using_srm
op_logical_and
id|mode
op_ne
id|LINUX_REBOOT_CMD_RESTART
)paren
(brace
multiline_comment|/* Unfortunately, since MILO doesn&squot;t currently understand&n;&t;&t;   the hwrpb bits above, we can&squot;t reliably halt the &n;&t;&t;   processor and keep it halted.  So just loop.  */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|srm_paging_stop
c_func
(paren
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_restart
id|machine_restart
c_func
(paren
r_char
op_star
id|restart_cmd
)paren
(brace
id|alpha_mv
dot
id|kill_arch
c_func
(paren
id|LINUX_REBOOT_CMD_RESTART
comma
id|restart_cmd
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_halt
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|alpha_mv
dot
id|kill_arch
c_func
(paren
id|LINUX_REBOOT_CMD_HALT
comma
l_int|NULL
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
id|alpha_mv
dot
id|kill_arch
c_func
(paren
id|LINUX_REBOOT_CMD_POWER_OFF
comma
l_int|NULL
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
id|printk
c_func
(paren
l_string|&quot;&bslash;nps: %04lx pc: [&lt;%016lx&gt;]&bslash;n&quot;
comma
id|regs-&gt;ps
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;rp: [&lt;%016lx&gt;] sp: %p&bslash;n&quot;
comma
id|regs-&gt;r26
comma
id|regs
op_plus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r0: %016lx  r1: %016lx  r2: %016lx  r3: %016lx&bslash;n&quot;
comma
id|regs-&gt;r0
comma
id|regs-&gt;r1
comma
id|regs-&gt;r2
comma
id|regs-&gt;r3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r4: %016lx  r5: %016lx  r6: %016lx  r7: %016lx&bslash;n&quot;
comma
id|regs-&gt;r4
comma
id|regs-&gt;r5
comma
id|regs-&gt;r6
comma
id|regs-&gt;r7
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r8: %016lx r16: %016lx r17: %016lx r18: %016lx&bslash;n&quot;
comma
id|regs-&gt;r8
comma
id|regs-&gt;r16
comma
id|regs-&gt;r17
comma
id|regs-&gt;r18
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r19: %016lx r20: %016lx r21: %016lx r22: %016lx&bslash;n&quot;
comma
id|regs-&gt;r19
comma
id|regs-&gt;r20
comma
id|regs-&gt;r21
comma
id|regs-&gt;r22
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r23: %016lx r24: %016lx r25: %016lx r26: %016lx&bslash;n&quot;
comma
id|regs-&gt;r23
comma
id|regs-&gt;r24
comma
id|regs-&gt;r25
comma
id|regs-&gt;r26
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r27: %016lx r28: %016lx r29: %016lx hae: %016lx&bslash;n&quot;
comma
id|regs-&gt;r27
comma
id|regs-&gt;r28
comma
id|regs-&gt;gp
comma
id|regs-&gt;hae
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-start a thread when doing execve()&n; */
DECL|function|start_thread
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;ps
op_assign
l_int|8
suffix:semicolon
id|wrusp
c_func
(paren
id|sp
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
multiline_comment|/* Arrange for each exec&squot;ed process to start off with a clean slate&n;&t;   with respect to the FPU.  This is all exceptions disabled.  Note&n;           that EV6 defines UNFD valid only with UNDZ, which we don&squot;t want&n;&t;   for IEEE conformance -- so that disabled bit remains in software.  */
id|current-&gt;tss.flags
op_and_assign
op_complement
id|IEEE_SW_MASK
suffix:semicolon
id|wrfpcr
c_func
(paren
id|FPCR_DYN_NORMAL
op_or
id|FPCR_INVD
op_or
id|FPCR_DZED
op_or
id|FPCR_OVFD
op_or
id|FPCR_INED
)paren
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
multiline_comment|/*&n; * &quot;alpha_clone()&quot;.. By the time we get here, the&n; * non-volatile registers have also been saved on the&n; * stack. We do some ugly pointer stuff here.. (see&n; * also copy_thread)&n; *&n; * Notice that &quot;fork()&quot; is implemented in terms of clone,&n; * with parameters (SIGCHLD, 0).&n; */
DECL|function|alpha_clone
r_int
id|alpha_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_struct
id|switch_stack
op_star
id|swstack
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|usp
)paren
id|usp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|usp
comma
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|swstack
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|alpha_vfork
r_int
id|alpha_vfork
c_func
(paren
r_struct
id|switch_stack
op_star
id|swstack
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
id|rdusp
c_func
(paren
)paren
comma
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|swstack
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy an alpha thread..&n; *&n; * Note the &quot;stack_offset&quot; stuff: when returning to kernel mode, we need&n; * to have some extra stack-space for the kernel stack that still exists&n; * after the &quot;ret_from_sys_call&quot;. When returning to user mode, we only&n; * want the space needed by the syscall stack frame (ie &quot;struct pt_regs&quot;).&n; * Use the passed &quot;regs&quot; pointer to determine how much space we need&n; * for a kernel fork().&n; */
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
r_extern
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ret_from_smp_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|switch_stack
op_star
id|childstack
comma
op_star
id|stack
suffix:semicolon
r_int
r_int
id|stack_offset
suffix:semicolon
id|stack_offset
op_assign
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;ps
op_amp
l_int|8
)paren
)paren
id|stack_offset
op_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
(paren
r_int
r_int
)paren
id|regs
suffix:semicolon
id|childregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|stack_offset
op_plus
id|PAGE_SIZE
op_plus
(paren
r_int
)paren
id|p
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;r0
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;r19
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;r20
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* OSF/1 has some strange fork() semantics.  */
id|regs-&gt;r20
op_assign
l_int|0
suffix:semicolon
id|stack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|childstack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|childregs
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childstack
op_assign
op_star
id|stack
suffix:semicolon
macro_line|#ifdef __SMP__
id|childstack-&gt;r26
op_assign
(paren
r_int
r_int
)paren
id|ret_from_smp_fork
suffix:semicolon
macro_line|#else
id|childstack-&gt;r26
op_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
macro_line|#endif
id|p-&gt;tss.usp
op_assign
id|usp
suffix:semicolon
id|p-&gt;tss.ksp
op_assign
(paren
r_int
r_int
)paren
id|childstack
suffix:semicolon
id|p-&gt;tss.pal_flags
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set FEN, clear everything else */
id|p-&gt;tss.flags
op_assign
id|current-&gt;tss.flags
suffix:semicolon
id|p-&gt;mm-&gt;context
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
id|pt
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
multiline_comment|/* switch stack follows right below pt_regs: */
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|pt
)paren
op_minus
l_int|1
suffix:semicolon
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
id|rdusp
c_func
(paren
)paren
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
(paren
id|current-&gt;mm-&gt;end_code
op_minus
id|dump-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
id|PAGE_SIZE
op_minus
l_int|1
op_minus
id|dump-&gt;start_data
)paren
op_rshift
id|PAGE_SHIFT
)paren
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
multiline_comment|/*&n;&t; * We store the registers in an order/format that is&n;&t; * compatible with DEC Unix/OSF/1 as this makes life easier&n;&t; * for gdb.&n;&t; */
id|dump-&gt;regs
(braket
id|EF_V0
)braket
op_assign
id|pt-&gt;r0
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T0
)braket
op_assign
id|pt-&gt;r1
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T1
)braket
op_assign
id|pt-&gt;r2
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T2
)braket
op_assign
id|pt-&gt;r3
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T3
)braket
op_assign
id|pt-&gt;r4
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T4
)braket
op_assign
id|pt-&gt;r5
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T5
)braket
op_assign
id|pt-&gt;r6
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T6
)braket
op_assign
id|pt-&gt;r7
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T7
)braket
op_assign
id|pt-&gt;r8
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S0
)braket
op_assign
id|sw-&gt;r9
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S1
)braket
op_assign
id|sw-&gt;r10
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S2
)braket
op_assign
id|sw-&gt;r11
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S3
)braket
op_assign
id|sw-&gt;r12
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S4
)braket
op_assign
id|sw-&gt;r13
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S5
)braket
op_assign
id|sw-&gt;r14
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S6
)braket
op_assign
id|sw-&gt;r15
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A3
)braket
op_assign
id|pt-&gt;r19
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A4
)braket
op_assign
id|pt-&gt;r20
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A5
)braket
op_assign
id|pt-&gt;r21
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T8
)braket
op_assign
id|pt-&gt;r22
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T9
)braket
op_assign
id|pt-&gt;r23
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T10
)braket
op_assign
id|pt-&gt;r24
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T11
)braket
op_assign
id|pt-&gt;r25
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_RA
)braket
op_assign
id|pt-&gt;r26
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T12
)braket
op_assign
id|pt-&gt;r27
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_AT
)braket
op_assign
id|pt-&gt;r28
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_SP
)braket
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_PS
)braket
op_assign
id|pt-&gt;ps
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_PC
)braket
op_assign
id|pt-&gt;pc
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_GP
)braket
op_assign
id|pt-&gt;gp
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A0
)braket
op_assign
id|pt-&gt;r16
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A1
)braket
op_assign
id|pt-&gt;r17
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A2
)braket
op_assign
id|pt-&gt;r18
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|dump-&gt;regs
op_plus
id|EF_SIZE
comma
id|sw-&gt;fp
comma
l_int|32
op_star
l_int|8
)paren
suffix:semicolon
)brace
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
id|r
)paren
(brace
multiline_comment|/* switch stack follows right below pt_regs: */
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|r
comma
id|sw-&gt;fp
comma
l_int|32
op_star
l_int|8
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; *&n; * This works due to the alpha calling sequence: the first 6 args&n; * are gotten from registers, while the rest is on the stack, so&n; * we get a0-a5 for free, and then magically find &quot;struct pt_regs&quot;&n; * on the stack for us..&n; *&n; * Don&squot;t do this at home.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_int
r_int
id|a0
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
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
id|a0
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
(paren
r_char
op_star
op_star
)paren
id|a1
comma
(paren
r_char
op_star
op_star
)paren
id|a2
comma
op_amp
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
