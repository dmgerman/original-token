multiline_comment|/* $Id: sys_sparc.c,v 1.13 1998/03/29 10:10:52 davem Exp $&n; * linux/arch/sparc64/kernel/sys_sparc.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/sparc&n; * platform.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
macro_line|#include &lt;asm/utrap.h&gt;
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
r_int
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brk
op_ge
l_int|0x80000000000UL
)paren
(brace
multiline_comment|/* VM hole */
id|ret
op_assign
id|current-&gt;mm-&gt;brk
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|sys_brk
c_func
(paren
id|brk
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
id|lock_kernel
c_func
(paren
)paren
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
r_goto
id|out
suffix:semicolon
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
id|error
op_assign
id|fd
(braket
l_int|0
)braket
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
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
r_int
id|sys_ipc
(paren
r_int
id|call
comma
r_int
id|first
comma
r_int
id|second
comma
r_int
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
id|err
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* No need for backward compatibility. We can start fresh... */
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
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_case
id|SEMGET
suffix:colon
id|err
op_assign
id|sys_semget
(paren
id|first
comma
id|second
comma
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
(brace
r_union
id|semun
id|fourth
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
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
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|sys_semctl
(paren
id|first
comma
id|second
comma
(paren
r_int
)paren
id|third
comma
id|fourth
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
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
id|err
op_assign
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
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|MSGRCV
suffix:colon
id|err
op_assign
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
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|MSGGET
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
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
r_if
c_cond
(paren
id|first
op_ge
l_int|0
)paren
(brace
r_extern
r_struct
id|shmid_ds
op_star
id|shm_segs
(braket
)braket
suffix:semicolon
r_struct
id|shmid_ds
op_star
id|shp
op_assign
id|shm_segs
(braket
(paren
r_int
r_int
)paren
id|first
op_mod
id|SHMMNI
)braket
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
id|IPC_UNUSED
op_logical_or
id|shp
op_eq
id|IPC_NOID
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|ptr
op_ge
l_int|0x80000000000UL
op_minus
id|shp-&gt;shm_segsz
op_logical_and
(paren
r_int
r_int
)paren
id|ptr
OL
l_int|0xfffff80000000000UL
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Somebody is trying to fool us */
)brace
)brace
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
(paren
id|ulong
op_star
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SHMDT
suffix:colon
id|err
op_assign
id|sys_shmdt
(paren
(paren
r_char
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SHMGET
suffix:colon
id|err
op_assign
id|sys_shmget
(paren
id|first
comma
id|second
comma
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
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
r_int
id|retval
op_assign
op_minus
id|EBADF
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
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
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
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
r_goto
id|out_putf
suffix:semicolon
)brace
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
(brace
r_if
c_cond
(paren
id|len
OG
l_int|0xf0000000UL
op_logical_or
id|addr
OG
l_int|0xf0000000UL
op_minus
id|len
)paren
r_goto
id|out_putf
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|len
op_ge
l_int|0x80000000000UL
op_logical_or
(paren
id|addr
template_param
l_int|0x80000000000UL
op_minus
id|len
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x80000000000ULL
op_logical_and
id|addr
OL
l_int|0xfffff80000000000UL
)paren
(brace
multiline_comment|/* VM hole */
id|retval
op_assign
id|current-&gt;mm-&gt;brk
suffix:semicolon
r_goto
id|out_putf
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
id|out_putf
suffix:colon
r_if
c_cond
(paren
id|file
)paren
id|fput
c_func
(paren
id|file
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
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
op_le
l_int|20
)paren
(brace
multiline_comment|/* Don&squot;t make the system unusable, if someone goes stuck */
id|printk
(paren
l_string|&quot;Unimplemented SPARC system call %ld&bslash;n&quot;
comma
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
)brace
id|unlock_kernel
c_func
(paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Entering kernel PC=%lx, nPC=%lx&bslash;n&quot;
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
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
l_string|&quot;TRAP: Returning to space: PC=%lx nPC=%lx&bslash;n&quot;
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
macro_line|#endif
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|check_pending
c_func
(paren
r_int
id|signum
)paren
suffix:semicolon
DECL|function|sys_getdomainname
id|asmlinkage
r_int
id|sys_getdomainname
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|nlen
op_assign
id|strlen
c_func
(paren
id|system_utsname.domainname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlen
OL
id|len
)paren
id|len
op_assign
id|nlen
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|__NEW_UTS_LEN
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|name
comma
id|system_utsname.domainname
comma
id|len
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
DECL|function|solaris_syscall
id|asmlinkage
r_int
id|solaris_syscall
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
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
id|printk
(paren
l_string|&quot;For Solaris binary emulation you need solaris module loaded&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_utrap_install
id|asmlinkage
r_int
id|sys_utrap_install
c_func
(paren
id|utrap_entry_t
id|type
comma
id|utrap_handler_t
id|new_p
comma
id|utrap_handler_t
id|new_d
comma
id|utrap_handler_t
op_star
id|old_p
comma
id|utrap_handler_t
op_star
id|old_d
)paren
(brace
r_if
c_cond
(paren
id|type
template_param
id|UT_TRAP_INSTRUCTION_31
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|new_p
op_eq
(paren
id|utrap_handler_t
)paren
(paren
r_int
)paren
id|UTH_NOCHANGE
)paren
(brace
r_if
c_cond
(paren
id|old_p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;tss.utraps
)paren
id|put_user_ret
c_func
(paren
l_int|NULL
comma
id|old_p
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_else
id|put_user_ret
c_func
(paren
(paren
id|utrap_handler_t
)paren
(paren
id|current-&gt;tss.utraps
(braket
id|type
)braket
)paren
comma
id|old_p
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_d
)paren
id|put_user_ret
c_func
(paren
l_int|NULL
comma
id|old_d
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;tss.utraps
)paren
(brace
id|current-&gt;tss.utraps
op_assign
id|kmalloc
c_func
(paren
(paren
id|UT_TRAP_INSTRUCTION_31
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;tss.utraps
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|current-&gt;tss.utraps
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|current-&gt;tss.utraps
op_plus
l_int|1
comma
l_int|0
comma
id|UT_TRAP_INSTRUCTION_31
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|utrap_handler_t
)paren
id|current-&gt;tss.utraps
(braket
id|type
)braket
op_ne
id|new_p
op_logical_and
id|current-&gt;tss.utraps
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
r_int
op_star
id|p
op_assign
id|current-&gt;tss.utraps
suffix:semicolon
id|current-&gt;tss.utraps
op_assign
id|kmalloc
c_func
(paren
(paren
id|UT_TRAP_INSTRUCTION_31
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;tss.utraps
)paren
(brace
id|current-&gt;tss.utraps
op_assign
id|p
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|p
(braket
l_int|0
)braket
op_decrement
suffix:semicolon
id|current-&gt;tss.utraps
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|current-&gt;tss.utraps
op_plus
l_int|1
comma
id|p
op_plus
l_int|1
comma
id|UT_TRAP_INSTRUCTION_31
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|old_p
)paren
id|put_user_ret
c_func
(paren
(paren
id|utrap_handler_t
)paren
(paren
id|current-&gt;tss.utraps
(braket
id|type
)braket
)paren
comma
id|old_p
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_d
)paren
id|put_user_ret
c_func
(paren
l_int|NULL
comma
id|old_d
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|current-&gt;tss.utraps
(braket
id|type
)braket
op_assign
(paren
r_int
)paren
id|new_p
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sparc_memory_ordering
r_int
id|sparc_memory_ordering
c_func
(paren
r_int
r_int
id|model
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
id|model
op_ge
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|regs-&gt;tstate
op_assign
(paren
id|regs-&gt;tstate
op_amp
op_complement
id|TSTATE_MM
)paren
op_or
(paren
id|model
op_lshift
l_int|14
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaction
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
op_star
id|act
comma
r_struct
id|old_sigaction
op_star
id|oact
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|old_sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_restorer
comma
op_amp
id|act-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask
)paren
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|new_ka.sa.sa_mask
comma
id|mask
)paren
suffix:semicolon
id|new_ka.ka_restorer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oact
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_restorer
comma
op_amp
id|oact-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
op_amp
id|oact-&gt;sa_mask
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_rt_sigaction
id|sys_rt_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|sigaction
op_star
id|act
comma
r_struct
id|sigaction
op_star
id|oact
comma
r_void
op_star
id|restorer
comma
r_int
id|sigsetsize
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s.  */
r_if
c_cond
(paren
id|sigsetsize
op_ne
r_sizeof
(paren
id|sigset_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|new_ka.ka_restorer
op_assign
id|restorer
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_ka.sa
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|oact
comma
op_amp
id|old_ka.sa
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
