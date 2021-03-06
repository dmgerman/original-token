multiline_comment|/*&n; * linux/arch/ppc/kernel/sys_ppc.c&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; * Derived from &quot;arch/i386/kernel/sys_i386.c&quot;&n; * Adapted from the i386 version by Gary Thomas&n; * Modified by Cort Dougan (cort@cs.nmt.edu)&n; * and Paul Mackerras (paulus@cs.anu.edu.au).&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/PPC&n; * platform.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
r_void
DECL|function|check_bugs
id|check_bugs
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|sys_ioperm
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sys_ioperm()&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|sys_iopl
r_int
id|sys_iopl
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_int
id|a3
comma
r_int
id|a4
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sys_iopl(%x, %x, %x, %x)!&bslash;n&quot;
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENOSYS
)paren
suffix:semicolon
)brace
DECL|function|sys_vm86
r_int
id|sys_vm86
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_int
id|a3
comma
r_int
id|a4
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sys_vm86(%x, %x, %x, %x)!&bslash;n&quot;
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENOSYS
)paren
suffix:semicolon
)brace
DECL|function|sys_modify_ldt
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_int
id|a3
comma
r_int
id|a4
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sys_modify_ldt(%x, %x, %x, %x)!&bslash;n&quot;
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENOSYS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
r_int
DECL|function|sys_ipc
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
comma
id|ret
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
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
id|ret
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
r_break
suffix:semicolon
r_case
id|SEMGET
suffix:colon
id|ret
op_assign
id|sys_semget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_break
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
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
id|ptr
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
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
)paren
r_break
suffix:semicolon
id|ret
op_assign
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
r_break
suffix:semicolon
)brace
r_case
id|MSGSND
suffix:colon
id|ret
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
id|third
)paren
suffix:semicolon
r_break
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
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
id|ptr
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
op_logical_or
(paren
id|ret
op_assign
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
)paren
r_break
suffix:semicolon
id|ret
op_assign
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
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
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
id|third
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MSGGET
suffix:colon
id|ret
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
r_break
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
id|ret
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
r_break
suffix:semicolon
r_case
id|SHMAT
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_default
suffix:colon
(brace
)brace
(brace
id|ulong
id|raddr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
id|ulong
op_star
)paren
id|third
comma
r_sizeof
(paren
id|ulong
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
id|ret
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
id|ret
)paren
r_break
suffix:semicolon
id|ret
op_assign
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
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
multiline_comment|/* iBCS2 emulator entry point */
r_if
c_cond
(paren
op_logical_neg
id|segment_eq
c_func
(paren
id|get_fs
c_func
(paren
)paren
comma
id|get_ds
c_func
(paren
)paren
)paren
)paren
r_break
suffix:semicolon
id|ret
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
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SHMDT
suffix:colon
id|ret
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
r_break
suffix:semicolon
r_case
id|SHMGET
suffix:colon
id|ret
op_assign
id|sys_shmget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
id|ret
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
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
DECL|function|sys_pipe
r_int
id|sys_pipe
c_func
(paren
r_int
op_star
id|fildes
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
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|fildes
comma
id|fd
comma
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_mmap
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
id|off_t
id|offset
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
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
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
id|offset
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
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
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_int
id|sys_select
c_func
(paren
r_int
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
r_struct
id|timeval
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Due to some executables calling the wrong select we sometimes&n; * get wrong args.  This determines how the args are being passed&n; * (a single ptr to them all args passed) then calls&n; * sys_select() with the appropriate args. -- Cort&n; */
r_int
DECL|function|ppc_select
id|ppc_select
c_func
(paren
r_int
id|n
comma
id|fd_set
op_star
id|inp
comma
id|fd_set
op_star
id|outp
comma
id|fd_set
op_star
id|exp
comma
r_struct
id|timeval
op_star
id|tvp
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|n
op_ge
l_int|4096
)paren
(brace
r_int
r_int
op_star
id|buffer
op_assign
(paren
r_int
r_int
op_star
)paren
id|n
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buffer
comma
l_int|5
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|n
comma
id|buffer
)paren
op_logical_or
id|__get_user
c_func
(paren
id|inp
comma
(paren
(paren
id|fd_set
op_star
op_star
)paren
(paren
id|buffer
op_plus
l_int|1
)paren
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|outp
comma
(paren
(paren
id|fd_set
op_star
op_star
)paren
(paren
id|buffer
op_plus
l_int|2
)paren
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|exp
comma
(paren
(paren
id|fd_set
op_star
op_star
)paren
(paren
id|buffer
op_plus
l_int|3
)paren
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tvp
comma
(paren
(paren
r_struct
id|timeval
op_star
op_star
)paren
(paren
id|buffer
op_plus
l_int|4
)paren
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|sys_select
c_func
(paren
id|n
comma
id|inp
comma
id|outp
comma
id|exp
comma
id|tvp
)paren
suffix:semicolon
)brace
DECL|function|sys_pause
r_int
id|sys_pause
c_func
(paren
r_void
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
r_return
op_minus
id|ERESTARTNOHAND
suffix:semicolon
)brace
DECL|function|sys_uname
r_int
id|sys_uname
c_func
(paren
r_struct
id|old_utsname
op_star
id|name
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_logical_and
op_logical_neg
id|copy_to_user
c_func
(paren
id|name
comma
op_amp
id|system_utsname
comma
r_sizeof
(paren
op_star
id|name
)paren
)paren
)paren
id|err
op_assign
l_int|0
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_olduname
r_int
id|sys_olduname
c_func
(paren
r_struct
id|oldold_utsname
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
(paren
r_struct
id|oldold_utsname
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|system_utsname.sysname
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;sysname
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|system_utsname.nodename
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;nodename
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|system_utsname.release
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;release
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|system_utsname.version
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;version
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_sub_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|system_utsname.machine
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;machine
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PCI
multiline_comment|/*&n; * Those are normally defined in arch/ppc/kernel/pci.c. But when CONFIG_PCI is&n; * not defined, this file is not linked at all, so here are the &quot;empty&quot; versions&n; */
DECL|function|sys_pciconfig_read
id|asmlinkage
r_int
id|sys_pciconfig_read
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_pciconfig_write
id|asmlinkage
r_int
id|sys_pciconfig_write
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_pciconfig_iobase
id|asmlinkage
r_int
id|sys_pciconfig_iobase
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
eof
