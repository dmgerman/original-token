multiline_comment|/* $Id: sys_sparc.c,v 1.32 1996/12/19 05:25:46 davem Exp $&n; * linux/arch/sparc/kernel/sys_sparc.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/sparc&n; * platform.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
multiline_comment|/* XXX Make this per-binary type, this way we can detect the type of&n; * XXX a binary.  Every Sparc executable calls this very early on.&n; */
DECL|function|sys_getpagesize
id|asmlinkage
r_int
r_int
id|sys_getpagesize
c_func
(paren
r_void
)paren
(brace
r_return
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Possibly older binaries want 8192 on sun4&squot;s? */
)brace
r_extern
id|asmlinkage
r_int
r_int
id|sys_brk
c_func
(paren
r_int
r_int
id|brk
)paren
suffix:semicolon
DECL|function|sparc_brk
id|asmlinkage
r_int
r_int
id|sparc_brk
c_func
(paren
r_int
r_int
id|brk
)paren
(brace
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4c
)paren
(brace
r_if
c_cond
(paren
id|brk
op_ge
l_int|0x20000000
op_logical_and
id|brk
OL
l_int|0xe0000000
)paren
(brace
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
)brace
)brace
r_return
id|sys_brk
c_func
(paren
id|brk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
DECL|function|sparc_pipe
id|asmlinkage
r_int
id|sparc_pipe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_pipe
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_return
id|error
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|fd
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
r_int
id|sys_ipc
(paren
id|uint
id|call
comma
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
r_void
op_star
id|ptr
comma
r_int
id|fifth
)paren
(brace
r_int
id|version
suffix:semicolon
id|version
op_assign
id|call
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* hack for backward compatibility */
id|call
op_and_assign
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|call
op_le
id|SEMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
r_return
id|sys_semop
(paren
id|first
comma
(paren
r_struct
id|sembuf
op_star
)paren
id|ptr
comma
id|second
)paren
suffix:semicolon
r_case
id|SEMGET
suffix:colon
r_return
id|sys_semget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
(brace
r_union
id|semun
id|fourth
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|fourth.__pad
comma
(paren
r_void
op_star
op_star
)paren
id|ptr
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|sys_semctl
(paren
id|first
comma
id|second
comma
id|third
comma
id|fourth
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|MSGCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|MSGSND
suffix:colon
r_return
id|sys_msgsnd
(paren
id|first
comma
(paren
r_struct
id|msgbuf
op_star
)paren
id|ptr
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|MSGRCV
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
l_int|0
suffix:colon
(brace
r_struct
id|ipc_kludge
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
(paren
r_struct
id|ipc_kludge
op_star
)paren
id|ptr
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|sys_msgrcv
(paren
id|first
comma
id|tmp.msgp
comma
id|second
comma
id|tmp.msgtyp
comma
id|third
)paren
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_return
id|sys_msgrcv
(paren
id|first
comma
(paren
r_struct
id|msgbuf
op_star
)paren
id|ptr
comma
id|second
comma
id|fifth
comma
id|third
)paren
suffix:semicolon
)brace
r_case
id|MSGGET
suffix:colon
r_return
id|sys_msgget
(paren
(paren
id|key_t
)paren
id|first
comma
id|second
)paren
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
r_return
id|sys_msgctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|msqid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|SHMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SHMAT
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
l_int|0
suffix:colon
r_default
suffix:colon
(brace
)brace
(brace
id|ulong
id|raddr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|sys_shmat
(paren
id|first
comma
(paren
r_char
op_star
)paren
id|ptr
comma
id|second
comma
op_amp
id|raddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|put_user
(paren
id|raddr
comma
(paren
id|ulong
op_star
)paren
id|third
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
multiline_comment|/* iBCS2 emulator entry point */
r_return
id|sys_shmat
(paren
id|first
comma
(paren
r_char
op_star
)paren
id|ptr
comma
id|second
comma
(paren
id|ulong
op_star
)paren
id|third
)paren
suffix:semicolon
)brace
r_case
id|SHMDT
suffix:colon
r_return
id|sys_shmdt
(paren
(paren
r_char
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_case
id|SHMGET
suffix:colon
r_return
id|sys_shmget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
r_return
id|sys_shmctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|shmid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_extern
r_int
r_int
id|get_unmapped_area
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* Linux version of mmap */
DECL|function|sys_mmap
id|asmlinkage
r_int
r_int
id|sys_mmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|off
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
(brace
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
op_logical_and
op_logical_neg
id|addr
)paren
(brace
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
id|addr
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
multiline_comment|/* See asm-sparc/uaccess.h */
r_if
c_cond
(paren
(paren
id|len
OG
(paren
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
)paren
op_logical_or
(paren
id|addr
OG
(paren
id|TASK_SIZE
op_minus
id|len
op_minus
id|PAGE_SIZE
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4c
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|addr
op_ge
l_int|0x20000000
)paren
op_logical_and
(paren
id|addr
OL
l_int|0xe0000000
)paren
)paren
)paren
(brace
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
)brace
)brace
id|retval
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|off
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* we come to here via sys_nis_syscall so it can setup the regs argument */
id|asmlinkage
r_int
r_int
DECL|function|c_sys_nis_syscall
id|c_sys_nis_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;Unimplemented SPARC system call %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/* #define DEBUG_SPARC_BREAKPOINT */
id|asmlinkage
r_void
DECL|function|sparc_breakpoint
id|sparc_breakpoint
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Entering kernel PC=%x, nPC=%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
)paren
suffix:semicolon
macro_line|#endif
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Returning to space: PC=%x nPC=%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
)paren
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_int
id|sys_sigaction
(paren
r_int
id|signum
comma
r_const
r_struct
id|sigaction
op_star
id|action
comma
r_struct
id|sigaction
op_star
id|oldaction
)paren
suffix:semicolon
id|asmlinkage
r_int
DECL|function|sparc_sigaction
id|sparc_sigaction
(paren
r_int
id|signum
comma
r_const
r_struct
id|sigaction
op_star
id|action
comma
r_struct
id|sigaction
op_star
id|oldaction
)paren
(brace
r_if
c_cond
(paren
id|signum
op_ge
l_int|0
)paren
(brace
r_return
id|sys_sigaction
(paren
id|signum
comma
id|action
comma
id|oldaction
)paren
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;tss.new_signal
op_assign
l_int|1
suffix:semicolon
r_return
id|sys_sigaction
(paren
op_minus
id|signum
comma
id|action
comma
id|oldaction
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifndef CONFIG_AP1000
multiline_comment|/* only AP+ systems have sys_aplib */
DECL|function|sys_aplib
id|asmlinkage
r_int
id|sys_aplib
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
eof
