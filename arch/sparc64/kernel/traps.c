multiline_comment|/* $Id: traps.c,v 1.49 1998/04/06 16:09:38 jj Exp $&n; * arch/sparc64/kernel/traps.c&n; *&n; * Copyright (C) 1995,1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
multiline_comment|/*&n; * I like traps on v9, :))))&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;  /* for jiffies */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/fpumacro.h&gt;
macro_line|#include &lt;asm/lsu.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
multiline_comment|/* #define SYSCALL_TRACING */
multiline_comment|/* #define VERBOSE_SYSCALL_TRACING */
multiline_comment|/* #define DEBUG_FPU */
macro_line|#ifdef SYSCALL_TRACING
macro_line|#ifdef VERBOSE_SYSCALL_TRACING
DECL|struct|sdesc
r_struct
id|sdesc
(brace
DECL|member|scall_num
r_int
id|scall_num
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|num_args
r_int
id|num_args
suffix:semicolon
DECL|member|arg_is_string
r_char
id|arg_is_string
(braket
l_int|6
)braket
suffix:semicolon
DECL|variable|sdesc_entries
)brace
id|sdesc_entries
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_string|&quot;setup&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|1
comma
l_string|&quot;exit&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|2
comma
l_string|&quot;fork&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|3
comma
l_string|&quot;read&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|4
comma
l_string|&quot;write&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|5
comma
l_string|&quot;open&quot;
comma
l_int|3
comma
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|6
comma
l_string|&quot;close&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|7
comma
l_string|&quot;wait4&quot;
comma
l_int|4
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|8
comma
l_string|&quot;creat&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|9
comma
l_string|&quot;link&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|1
comma
)brace
)brace
comma
(brace
l_int|10
comma
l_string|&quot;unlink&quot;
comma
l_int|1
comma
(brace
l_int|1
comma
)brace
)brace
comma
(brace
l_int|11
comma
l_string|&quot;execv&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|12
comma
l_string|&quot;chdir&quot;
comma
l_int|1
comma
(brace
l_int|1
comma
)brace
)brace
comma
(brace
l_int|15
comma
l_string|&quot;chmod&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|16
comma
l_string|&quot;chown&quot;
comma
l_int|3
comma
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|17
comma
l_string|&quot;brk&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|19
comma
l_string|&quot;lseek&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|27
comma
l_string|&quot;alarm&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|29
comma
l_string|&quot;pause&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|33
comma
l_string|&quot;access&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|36
comma
l_string|&quot;sync&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|37
comma
l_string|&quot;kill&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|38
comma
l_string|&quot;stat&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|40
comma
l_string|&quot;lstat&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|41
comma
l_string|&quot;dup&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|42
comma
l_string|&quot;pipd&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|54
comma
l_string|&quot;ioctl&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|57
comma
l_string|&quot;symlink&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|1
comma
)brace
)brace
comma
(brace
l_int|58
comma
l_string|&quot;readlink&quot;
comma
l_int|3
comma
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|59
comma
l_string|&quot;execve&quot;
comma
l_int|3
comma
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|60
comma
l_string|&quot;umask&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|62
comma
l_string|&quot;fstat&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|64
comma
l_string|&quot;getpagesize&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|71
comma
l_string|&quot;mmap&quot;
comma
l_int|6
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|73
comma
l_string|&quot;munmap&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|74
comma
l_string|&quot;mprotect&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|83
comma
l_string|&quot;setitimer&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|90
comma
l_string|&quot;dup2&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|92
comma
l_string|&quot;fcntl&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|93
comma
l_string|&quot;select&quot;
comma
l_int|5
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|97
comma
l_string|&quot;socket&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|98
comma
l_string|&quot;connect&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|99
comma
l_string|&quot;accept&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|101
comma
l_string|&quot;send&quot;
comma
l_int|4
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|102
comma
l_string|&quot;recv&quot;
comma
l_int|4
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|104
comma
l_string|&quot;bind&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|105
comma
l_string|&quot;setsockopt&quot;
comma
l_int|5
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|106
comma
l_string|&quot;listen&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|120
comma
l_string|&quot;readv&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|121
comma
l_string|&quot;writev&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|123
comma
l_string|&quot;fchown&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|124
comma
l_string|&quot;fchmod&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|128
comma
l_string|&quot;rename&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|1
comma
)brace
)brace
comma
(brace
l_int|129
comma
l_string|&quot;truncate&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|130
comma
l_string|&quot;ftruncate&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|131
comma
l_string|&quot;flock&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|136
comma
l_string|&quot;mkdir&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|137
comma
l_string|&quot;rmdir&quot;
comma
l_int|1
comma
(brace
l_int|1
comma
)brace
)brace
comma
(brace
l_int|146
comma
l_string|&quot;killpg&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|157
comma
l_string|&quot;statfs&quot;
comma
l_int|2
comma
(brace
l_int|1
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|158
comma
l_string|&quot;fstatfs&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|159
comma
l_string|&quot;umount&quot;
comma
l_int|1
comma
(brace
l_int|1
comma
)brace
)brace
comma
(brace
l_int|167
comma
l_string|&quot;mount&quot;
comma
l_int|5
comma
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|174
comma
l_string|&quot;getdents&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|176
comma
l_string|&quot;fchdir&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|198
comma
l_string|&quot;sigaction&quot;
comma
l_int|3
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|201
comma
l_string|&quot;sigsuspend&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
(brace
l_int|206
comma
l_string|&quot;socketcall&quot;
comma
l_int|2
comma
(brace
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|216
comma
l_string|&quot;sigreturn&quot;
comma
l_int|0
comma
)brace
comma
(brace
l_int|230
comma
l_string|&quot;newselect&quot;
comma
l_int|5
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|236
comma
l_string|&quot;llseek&quot;
comma
l_int|5
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
comma
(brace
l_int|251
comma
l_string|&quot;sysctl&quot;
comma
l_int|1
comma
(brace
l_int|0
comma
)brace
)brace
comma
)brace
suffix:semicolon
DECL|macro|NUM_SDESC_ENTRIES
mdefine_line|#define NUM_SDESC_ENTRIES (sizeof(sdesc_entries) / sizeof(sdesc_entries[0]))
macro_line|#endif
macro_line|#ifdef VERBOSE_SYSCALL_TRACING
DECL|variable|scall_strbuf
r_static
r_char
id|scall_strbuf
(braket
l_int|512
)braket
suffix:semicolon
macro_line|#endif
DECL|function|syscall_trace_entry
r_void
id|syscall_trace_entry
c_func
(paren
r_int
r_int
id|g1
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef VERBOSE_SYSCALL_TRACING
r_struct
id|sdesc
op_star
id|sdp
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;pid
)paren
r_return
suffix:semicolon
macro_line|#endif&t;
id|printk
c_func
(paren
l_string|&quot;SYS[%s:%d]: PC(%016lx) &lt;%3d&gt; &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;tpc
comma
(paren
r_int
)paren
id|g1
)paren
suffix:semicolon
macro_line|#ifdef VERBOSE_SYSCALL_TRACING
id|sdp
op_assign
l_int|NULL
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
id|NUM_SDESC_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|sdesc_entries
(braket
id|i
)braket
dot
id|scall_num
op_eq
id|g1
)paren
(brace
id|sdp
op_assign
op_amp
id|sdesc_entries
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sdp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s(&quot;
comma
id|sdp-&gt;name
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
id|sdp-&gt;num_args
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sdp-&gt;arg_is_string
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
id|printk
c_func
(paren
l_string|&quot;%08x&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
op_plus
id|i
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%016lx&quot;
comma
id|regs-&gt;u_regs
(braket
id|UREG_I0
op_plus
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
id|strncpy_from_user
c_func
(paren
id|scall_strbuf
comma
(paren
r_char
op_star
)paren
(paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
op_plus
id|i
)braket
op_amp
l_int|0xffffffff
)paren
comma
l_int|512
)paren
suffix:semicolon
r_else
id|strncpy_from_user
c_func
(paren
id|scall_strbuf
comma
(paren
r_char
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
op_plus
id|i
)braket
comma
l_int|512
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|scall_strbuf
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;) &quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|syscall_trace_exit
r_int
r_int
id|syscall_trace_exit
c_func
(paren
r_int
r_int
id|retval
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|current-&gt;pid
)paren
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;ret[%016lx]&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif /* SYSCALL_TRACING */
DECL|function|bad_trap
r_void
id|bad_trap
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|lvl
)paren
(brace
id|lock_kernel
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lvl
OL
l_int|0x100
)paren
(brace
r_char
id|buffer
(braket
l_int|24
)braket
suffix:semicolon
id|sprintf
(paren
id|buffer
comma
l_string|&quot;Bad hw trap %lx at tl0&bslash;n&quot;
comma
id|lvl
)paren
suffix:semicolon
id|die_if_kernel
(paren
id|buffer
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
id|die_if_kernel
(paren
l_string|&quot;Kernel bad trap&quot;
comma
id|regs
)paren
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_BADTRAP
c_func
(paren
id|lvl
op_minus
l_int|0x100
)paren
suffix:semicolon
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
(paren
)paren
suffix:semicolon
)brace
DECL|function|bad_trap_tl1
r_void
id|bad_trap_tl1
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|lvl
)paren
(brace
r_char
id|buffer
(braket
l_int|24
)braket
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sprintf
(paren
id|buffer
comma
l_string|&quot;Bad trap %lx at tl&gt;0&quot;
comma
id|lvl
)paren
suffix:semicolon
id|die_if_kernel
(paren
id|buffer
comma
id|regs
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|data_access_exception
r_void
id|data_access_exception
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
multiline_comment|/* Test if this comes from uaccess places. */
r_int
r_int
id|fixup
comma
id|g2
suffix:semicolon
id|g2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fixup
op_assign
id|search_exception_table
(paren
id|regs-&gt;tpc
comma
op_amp
id|g2
)paren
)paren
)paren
(brace
multiline_comment|/* Ouch, somebody is trying ugly VM hole tricks on us... */
macro_line|#ifdef DEBUG_EXCEPTIONS
id|printk
c_func
(paren
l_string|&quot;Exception: PC&lt;%016lx&gt; faddr&lt;UNKNOWN&gt;&bslash;n&quot;
comma
id|regs-&gt;tpc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EX_TABLE: insn&lt;%016lx&gt; fixup&lt;%016lx&gt; &quot;
l_string|&quot;g2&lt;%016lx&gt;&bslash;n&quot;
comma
id|regs-&gt;tpc
comma
id|fixup
comma
id|g2
)paren
suffix:semicolon
macro_line|#endif
id|regs-&gt;tpc
op_assign
id|fixup
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|regs-&gt;tpc
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
op_assign
id|g2
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* This is really pathetic... */
multiline_comment|/* #define DEBUG_PCI_POKES */
r_extern
r_volatile
r_int
id|pci_poke_in_progress
suffix:semicolon
r_extern
r_volatile
r_int
id|pci_poke_faulted
suffix:semicolon
macro_line|#endif
multiline_comment|/* When access exceptions happen, we must do this. */
DECL|function|clean_and_reenable_l1_caches
r_static
id|__inline__
r_void
id|clean_and_reenable_l1_caches
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* Clean &squot;em. */
r_for
c_loop
(paren
id|va
op_assign
l_int|0
suffix:semicolon
id|va
OL
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
suffix:semicolon
id|va
op_add_assign
l_int|32
)paren
(brace
id|spitfire_put_icache_tag
c_func
(paren
id|va
comma
l_int|0x0
)paren
suffix:semicolon
id|spitfire_put_dcache_tag
c_func
(paren
id|va
comma
l_int|0x0
)paren
suffix:semicolon
)brace
multiline_comment|/* Re-enable. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;flush %%g6&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&bslash;n&bslash;t&quot;
l_string|&quot;stxa %0, [%%g0] %1&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|LSU_CONTROL_IC
op_or
id|LSU_CONTROL_DC
op_or
id|LSU_CONTROL_IM
op_or
id|LSU_CONTROL_DM
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_LSU_CONTROL
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|do_dae
r_void
id|do_dae
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|pci_poke_in_progress
)paren
(brace
macro_line|#ifdef DEBUG_PCI_POKES
id|prom_printf
c_func
(paren
l_string|&quot; (POKE tpc[%016lx] tnpc[%016lx] &quot;
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
macro_line|#endif
id|pci_poke_faulted
op_assign
l_int|1
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|regs-&gt;tpc
op_plus
l_int|4
suffix:semicolon
macro_line|#ifdef DEBUG_PCI_POKES
id|prom_printf
c_func
(paren
l_string|&quot;PCI) &quot;
)paren
suffix:semicolon
multiline_comment|/* prom_halt(); */
macro_line|#endif
id|clean_and_reenable_l1_caches
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|clean_and_reenable_l1_caches
c_func
(paren
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|instruction_access_exception
r_void
id|instruction_access_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|clean_and_reenable_l1_caches
c_func
(paren
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_iae
r_void
id|do_iae
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_fpe_common
r_void
id|do_fpe_common
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_FPERROR
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_fpieee
r_void
id|do_fpieee
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef DEBUG_FPU&t;
r_struct
id|fpustate
op_star
id|f
op_assign
id|FPUSTATE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fpieee %016lx&bslash;n&quot;
comma
id|f-&gt;fsr
)paren
suffix:semicolon
macro_line|#endif
id|do_fpe_common
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_extern
r_int
id|do_mathemu
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|fpustate
op_star
)paren
suffix:semicolon
DECL|function|do_fpother
r_void
id|do_fpother
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|fpustate
op_star
id|f
op_assign
id|FPUSTATE
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|f-&gt;fsr
op_amp
l_int|0x1c000
)paren
)paren
(brace
r_case
(paren
l_int|2
op_lshift
l_int|14
)paren
suffix:colon
multiline_comment|/* unfinished_FPop */
r_case
(paren
l_int|3
op_lshift
l_int|14
)paren
suffix:colon
multiline_comment|/* unimplemented_FPop */
id|ret
op_assign
id|do_mathemu
c_func
(paren
id|regs
comma
id|f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
suffix:semicolon
macro_line|#ifdef DEBUG_FPU&t;
id|printk
c_func
(paren
l_string|&quot;fpother %016lx&bslash;n&quot;
comma
id|f-&gt;fsr
)paren
suffix:semicolon
macro_line|#endif
id|do_fpe_common
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_tof
r_void
id|do_tof
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
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Penguin overflow trap from kernel mode&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_TAG
suffix:semicolon
multiline_comment|/* as good as any */
id|send_sig
c_func
(paren
id|SIGEMT
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|do_div0
r_void
id|do_div0
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|instruction_dump
r_void
id|instruction_dump
(paren
r_int
r_int
op_star
id|pc
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pc
)paren
op_amp
l_int|3
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|3
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c%08x%c&quot;
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&lt;&squot;
comma
id|pc
(braket
id|i
)braket
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Amuse the user. */
id|printk
c_func
(paren
l_string|&quot;              &bslash;&bslash;|/ ____ &bslash;&bslash;|/&bslash;n&quot;
l_string|&quot;              &bslash;&quot;@&squot;/ .. &bslash;&bslash;`@&bslash;&quot;&bslash;n&quot;
l_string|&quot;              /_| &bslash;&bslash;__/ |_&bslash;&bslash;&bslash;n&quot;
l_string|&quot;                 &bslash;&bslash;__U_/&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(%d): %s&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|str
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;flushw&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
(brace
r_struct
id|reg_window
op_star
id|rw
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
(paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
multiline_comment|/* Stop the back trace when we hit userland or we&n;&t;&t; * find some badly aligned kernel stack.&n;&t;&t; */
r_while
c_loop
(paren
id|rw
op_logical_and
(paren
(paren
(paren
r_int
r_int
)paren
id|rw
)paren
op_ge
id|PAGE_OFFSET
)paren
op_logical_and
op_logical_neg
(paren
(paren
(paren
r_int
r_int
)paren
id|rw
)paren
op_amp
l_int|0x7
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Caller[%016lx]&bslash;n&quot;
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
(paren
id|rw-&gt;ins
(braket
l_int|6
)braket
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Instruction DUMP:&quot;
)paren
suffix:semicolon
id|instruction_dump
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;tpc
)paren
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Or else! */
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
r_extern
r_int
id|handle_popc
c_func
(paren
id|u32
id|insn
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|handle_ldq_stq
c_func
(paren
id|u32
id|insn
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|do_illegal_instruction
r_void
id|do_illegal_instruction
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
id|pc
op_assign
id|regs-&gt;tpc
suffix:semicolon
r_int
r_int
id|tstate
op_assign
id|regs-&gt;tstate
suffix:semicolon
id|u32
id|insn
suffix:semicolon
r_if
c_cond
(paren
id|tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel illegal instruction&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
(brace
id|pc
op_assign
(paren
id|u32
)paren
id|pc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|insn
comma
(paren
id|u32
op_star
)paren
id|pc
)paren
op_ne
op_minus
id|EFAULT
)paren
(brace
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1ffc000
)paren
op_eq
l_int|0x81700000
)paren
multiline_comment|/* POPC */
(brace
r_if
c_cond
(paren
id|handle_popc
c_func
(paren
id|insn
comma
id|regs
)paren
)paren
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1580000
)paren
op_eq
l_int|0xc1100000
)paren
multiline_comment|/* LDQ/STQ */
(brace
r_if
c_cond
(paren
id|handle_ldq_stq
c_func
(paren
id|insn
comma
id|regs
)paren
)paren
r_return
suffix:semicolon
)brace
)brace
id|current-&gt;tss.sig_address
op_assign
id|pc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_ILLINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mem_address_unaligned
r_void
id|mem_address_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|sfar
comma
r_int
r_int
id|sfsr
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
r_extern
r_void
id|kernel_unaligned_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|insn
comma
r_int
r_int
id|sfar
comma
r_int
r_int
id|sfsr
)paren
suffix:semicolon
r_return
id|kernel_unaligned_trap
c_func
(paren
id|regs
comma
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;tpc
)paren
comma
id|sfar
comma
id|sfsr
)paren
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGBUS
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_privop
r_void
id|do_privop
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|do_privact
r_void
id|do_privact
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|current-&gt;tss.sig_address
op_assign
id|regs-&gt;tpc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|do_priv_instruction
r_void
id|do_priv_instruction
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
id|npc
comma
r_int
r_int
id|tstate
)paren
(brace
r_if
c_cond
(paren
id|tstate
op_amp
id|TSTATE_PRIV
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Penguin instruction from Penguin mode??!?!&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|current-&gt;tss.sig_address
op_assign
id|pc
suffix:semicolon
id|current-&gt;tss.sig_desc
op_assign
id|SUBSIG_PRIVINST
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|handle_hw_divzero
r_void
id|handle_hw_divzero
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
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Trap level 1 stuff or other traps we should never see... */
DECL|function|do_cee
r_void
id|do_cee
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL0: Cache Error Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_cee_tl1
r_void
id|do_cee_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Cache Error Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_dae_tl1
r_void
id|do_dae_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Data Access Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_iae_tl1
r_void
id|do_iae_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Instruction Access Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_div0_tl1
r_void
id|do_div0_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: DIV0 Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_fpdis_tl1
r_void
id|do_fpdis_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: FPU Disabled&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_fpieee_tl1
r_void
id|do_fpieee_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: FPU IEEE Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_fpother_tl1
r_void
id|do_fpother_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: FPU Other Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_ill_tl1
r_void
id|do_ill_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Illegal Instruction Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_irq_tl1
r_void
id|do_irq_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: IRQ Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_lddfmna_tl1
r_void
id|do_lddfmna_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: LDDF Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_stdfmna_tl1
r_void
id|do_stdfmna_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: STDF Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_paw
r_void
id|do_paw
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL0: Phys Watchpoint Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_paw_tl1
r_void
id|do_paw_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Phys Watchpoint Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_vaw
r_void
id|do_vaw
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL0: Virt Watchpoint Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_vaw_tl1
r_void
id|do_vaw_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Virt Watchpoint Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_tof_tl1
r_void
id|do_tof_tl1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;TL1: Tag Overflow Exception&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_EC_FLUSH_TRAP
DECL|function|cache_flush_trap
r_void
id|cache_flush_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifndef __SMP__
r_int
id|node
op_assign
id|linux_cpus
(braket
id|get_cpuid
c_func
(paren
)paren
)braket
dot
id|prom_node
suffix:semicolon
macro_line|#else
macro_line|#error SMP not supported on sparc64 yet
macro_line|#endif
macro_line|#if 0
multiline_comment|/* Broken */
r_int
id|size
op_assign
id|prom_getintdefault
c_func
(paren
id|node
comma
l_string|&quot;ecache-size&quot;
comma
l_int|512
op_star
l_int|1024
)paren
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|end
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|regs-&gt;tnpc
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|addr
op_assign
id|PAGE_OFFSET
op_minus
id|PAGE_SIZE
suffix:semicolon
id|page
op_assign
id|mem_map
op_minus
l_int|1
suffix:semicolon
id|end
op_assign
id|mem_map
op_plus
id|max_mapnr
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_do
(brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|page
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|page
op_ge
id|end
)paren
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
multiline_comment|/* E-Cache line size is 64B. Let us pollute it :)) */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|PAGE_SIZE
suffix:semicolon
id|j
op_add_assign
l_int|64
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldx [%0 + %1], %%g1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|j
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;g1&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#endif
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
)brace
eof
