multiline_comment|/*&n; *  linux/kernel/sys.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/resource.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * this indicates wether you can reboot with ctrl-alt-del: the default is yes&n; */
DECL|variable|C_A_D
r_static
r_int
id|C_A_D
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &n; * The timezone where the local system is located.  Used as a default by some&n; * programs who obtain this value by using gettimeofday.&n; */
DECL|variable|sys_tz
r_struct
id|timezone
id|sys_tz
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_extern
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
DECL|macro|PZERO
mdefine_line|#define&t;PZERO&t;15
DECL|function|proc_sel
r_static
r_int
id|proc_sel
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|which
comma
r_int
id|who
)paren
(brace
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|PRIO_PROCESS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|who
op_logical_and
id|p
op_eq
id|current
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|p-&gt;pid
op_eq
id|who
suffix:semicolon
r_case
id|PRIO_PGRP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|who
)paren
id|who
op_assign
id|current-&gt;pgrp
suffix:semicolon
r_return
id|p-&gt;pgrp
op_eq
id|who
suffix:semicolon
r_case
id|PRIO_USER
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|who
)paren
id|who
op_assign
id|current-&gt;uid
suffix:semicolon
r_return
id|p-&gt;uid
op_eq
id|who
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_setpriority
r_int
id|sys_setpriority
c_func
(paren
r_int
id|which
comma
r_int
id|who
comma
r_int
id|niceval
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_int
id|error
op_assign
id|ESRCH
suffix:semicolon
r_int
id|priority
suffix:semicolon
r_if
c_cond
(paren
id|which
OG
l_int|2
op_logical_or
id|which
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priority
op_assign
id|PZERO
op_minus
id|niceval
)paren
op_le
l_int|0
)paren
id|priority
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
op_logical_or
op_logical_neg
id|proc_sel
c_func
(paren
op_star
id|p
comma
id|which
comma
id|who
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|uid
op_ne
id|current-&gt;euid
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|uid
op_ne
id|current-&gt;uid
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
id|EPERM
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_eq
id|ESRCH
)paren
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|priority
OG
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
id|error
op_assign
id|EACCES
suffix:semicolon
r_else
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
op_assign
id|priority
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
DECL|function|sys_getpriority
r_int
id|sys_getpriority
c_func
(paren
r_int
id|which
comma
r_int
id|who
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
r_int
id|max_prio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|which
OG
l_int|2
op_logical_or
id|which
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|LAST_TASK
suffix:semicolon
id|p
OG
op_amp
id|FIRST_TASK
suffix:semicolon
op_decrement
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
op_logical_or
op_logical_neg
id|proc_sel
c_func
(paren
op_star
id|p
comma
id|which
comma
id|who
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
OG
id|max_prio
)paren
id|max_prio
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
suffix:semicolon
)brace
r_return
id|max_prio
ques
c_cond
id|max_prio
suffix:colon
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|function|sys_profil
r_int
id|sys_profil
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_ftime
r_int
id|sys_ftime
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_break
r_int
id|sys_break
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_stty
r_int
id|sys_stty
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_gtty
r_int
id|sys_gtty
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_prof
r_int
id|sys_prof
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|save_v86_state
r_int
r_int
id|save_v86_state
c_func
(paren
r_int
id|signr
comma
r_struct
id|vm86_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|stack
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;vm86_info
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;no vm86_info: BAD&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
op_amp
(paren
id|current-&gt;vm86_info-&gt;regs
)paren
comma
id|regs
comma
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
id|stack
op_assign
id|current-&gt;tss.esp0
suffix:semicolon
id|current-&gt;tss.esp0
op_assign
id|current-&gt;saved_kernel_stack
suffix:semicolon
id|current-&gt;saved_kernel_stack
op_assign
l_int|0
suffix:semicolon
r_return
id|stack
suffix:semicolon
)brace
DECL|function|sys_vm86
r_int
id|sys_vm86
c_func
(paren
r_struct
id|vm86_struct
op_star
id|v86
)paren
(brace
r_struct
id|vm86_struct
id|info
suffix:semicolon
r_struct
id|pt_regs
op_star
id|pt_regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|v86
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;saved_kernel_stack
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|info
comma
id|v86
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * make sure the vm86() system call doesn&squot;t try to do anything silly&n; */
id|info.regs.__null_ds
op_assign
l_int|0
suffix:semicolon
id|info.regs.__null_es
op_assign
l_int|0
suffix:semicolon
id|info.regs.__null_fs
op_assign
l_int|0
suffix:semicolon
id|info.regs.__null_gs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * The eflags register is also special: we cannot trust that the user&n; * has set it up safely, so this makes sure interrupt etc flags are&n; * inherited from protected mode.&n; */
id|info.regs.eflags
op_and_assign
l_int|0x00000dd5
suffix:semicolon
id|info.regs.eflags
op_or_assign
l_int|0xfffff22a
op_amp
id|pt_regs-&gt;eflags
suffix:semicolon
id|info.regs.eflags
op_or_assign
id|VM_MASK
suffix:semicolon
id|current-&gt;saved_kernel_stack
op_assign
id|current-&gt;tss.esp0
suffix:semicolon
id|current-&gt;tss.esp0
op_assign
(paren
r_int
r_int
)paren
id|pt_regs
suffix:semicolon
id|current-&gt;vm86_info
op_assign
id|v86
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %0,%%esp&bslash;n&bslash;t&quot;
l_string|&quot;pushl $ret_from_sys_call&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
op_scope_resolution
l_string|&quot;g&quot;
(paren
(paren
r_int
)paren
op_amp
(paren
id|info.regs
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|info.regs.eax
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|hard_reset_now
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Reboot system call: for obvious reasons only root may call it,&n; * and even root needs to set up some magic numbers in the registers&n; * so that some mistake won&squot;t make this reboot the whole machine.&n; * You can also set the meaning of the ctrl-alt-del-key here.&n; *&n; * reboot doesn&squot;t sync: do that yourself before calling this.&n; */
DECL|function|sys_reboot
r_int
id|sys_reboot
c_func
(paren
r_int
id|magic
comma
r_int
id|magic_too
comma
r_int
id|flag
)paren
(brace
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
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|magic
op_ne
l_int|0xfee1dead
op_logical_or
id|magic_too
op_ne
l_int|672274793
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_eq
l_int|0x01234567
)paren
id|hard_reset_now
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|flag
op_eq
l_int|0x89ABCDEF
)paren
id|C_A_D
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|flag
)paren
id|C_A_D
op_assign
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function gets called by ctrl-alt-del - ie the keyboard interrupt.&n; * As it&squot;s called within an interrupt, it may NOT sync: the only choice&n; * is wether to reboot at once, or just ignore the ctrl-alt-del.&n; */
DECL|function|ctrl_alt_del
r_void
id|ctrl_alt_del
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|C_A_D
)paren
id|hard_reset_now
c_func
(paren
)paren
suffix:semicolon
r_else
id|send_sig
c_func
(paren
id|SIGINT
comma
id|task
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is done BSD-style, with no consideration of the saved gid, except&n; * that if you set the effective gid, it sets the saved gid too.  This &n; * makes it possible for a setgid program to completely drop its privileges,&n; * which is often a useful assertion to make when you are doing a security&n; * audit over a program.&n; *&n; * The general idea is that a program which uses just setregid() will be&n; * 100% compatible with BSD.  A program which uses just setgid() will be&n; * 100% compatible with POSIX w/ Saved ID&squot;s. &n; */
DECL|function|sys_setregid
r_int
id|sys_setregid
c_func
(paren
r_int
id|rgid
comma
r_int
id|egid
)paren
(brace
r_if
c_cond
(paren
id|rgid
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;gid
op_eq
id|rgid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;gid
op_assign
id|rgid
suffix:semicolon
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|egid
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;gid
op_eq
id|egid
)paren
op_logical_or
(paren
id|current-&gt;egid
op_eq
id|egid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
(brace
id|current-&gt;egid
op_assign
id|egid
suffix:semicolon
id|current-&gt;sgid
op_assign
id|egid
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * setgid() is implemeneted like SysV w/ SAVED_IDS &n; */
DECL|function|sys_setgid
r_int
id|sys_setgid
c_func
(paren
r_int
id|gid
)paren
(brace
r_if
c_cond
(paren
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;gid
op_assign
id|current-&gt;egid
op_assign
id|current-&gt;sgid
op_assign
id|gid
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|gid
op_eq
id|current-&gt;gid
)paren
op_logical_or
(paren
id|gid
op_eq
id|current-&gt;sgid
)paren
)paren
id|current-&gt;egid
op_assign
id|gid
suffix:semicolon
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_acct
r_int
id|sys_acct
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_phys
r_int
id|sys_phys
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_lock
r_int
id|sys_lock
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_mpx
r_int
id|sys_mpx
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_ulimit
r_int
id|sys_ulimit
c_func
(paren
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_time
r_int
id|sys_time
c_func
(paren
r_int
op_star
id|tloc
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|tloc
)paren
(brace
id|verify_area
c_func
(paren
id|tloc
comma
l_int|4
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|i
comma
(paren
r_int
r_int
op_star
)paren
id|tloc
)paren
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * Unprivileged users may change the real user id to the effective uid&n; * or vice versa.  (BSD-style)&n; *&n; * When you set the effective uid, it sets the saved uid too.  This &n; * makes it possible for a setuid program to completely drop its privileges,&n; * which is often a useful assertion to make when you are doing a security&n; * audit over a program.&n; *&n; * The general idea is that a program which uses just setreuid() will be&n; * 100% compatible with BSD.  A program which uses just setuid() will be&n; * 100% compatible with POSIX w/ Saved ID&squot;s. &n; */
DECL|function|sys_setreuid
r_int
id|sys_setreuid
c_func
(paren
r_int
id|ruid
comma
r_int
id|euid
)paren
(brace
r_int
id|old_ruid
op_assign
id|current-&gt;uid
suffix:semicolon
r_if
c_cond
(paren
id|ruid
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|current-&gt;euid
op_eq
id|ruid
)paren
op_logical_or
(paren
id|old_ruid
op_eq
id|ruid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;uid
op_assign
id|ruid
suffix:semicolon
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|euid
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|old_ruid
op_eq
id|euid
)paren
op_logical_or
(paren
id|current-&gt;euid
op_eq
id|euid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
(brace
id|current-&gt;euid
op_assign
id|euid
suffix:semicolon
id|current-&gt;suid
op_assign
id|euid
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;uid
op_assign
id|old_ruid
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * setuid() is implemeneted like SysV w/ SAVED_IDS &n; * &n; * Note that SAVED_ID&squot;s is deficient in that a setuid root program&n; * like sendmail, for example, cannot set its uid to be a normal &n; * user and then switch back, because if you&squot;re root, setuid() sets&n; * the saved uid too.  If you don&squot;t like this, blame the bright people&n; * in the POSIX commmittee and/or USG.  Note that the BSD-style setreuid()&n; * will allow a root program to temporarily drop privileges and be able to&n; * regain them by swapping the real and effective uid.  &n; */
DECL|function|sys_setuid
r_int
id|sys_setuid
c_func
(paren
r_int
id|uid
)paren
(brace
r_if
c_cond
(paren
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;uid
op_assign
id|current-&gt;euid
op_assign
id|current-&gt;suid
op_assign
id|uid
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|uid
op_eq
id|current-&gt;uid
)paren
op_logical_or
(paren
id|uid
op_eq
id|current-&gt;suid
)paren
)paren
id|current-&gt;euid
op_assign
id|uid
suffix:semicolon
r_else
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_stime
r_int
id|sys_stime
c_func
(paren
r_int
op_star
id|tptr
)paren
(brace
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
op_minus
id|EPERM
suffix:semicolon
id|startup_time
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|tptr
)paren
op_minus
id|jiffies
op_div
id|HZ
suffix:semicolon
id|jiffies_offset
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_times
r_int
id|sys_times
c_func
(paren
r_struct
id|tms
op_star
id|tbuf
)paren
(brace
r_if
c_cond
(paren
id|tbuf
)paren
(brace
id|verify_area
c_func
(paren
id|tbuf
comma
r_sizeof
op_star
id|tbuf
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;utime
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tbuf-&gt;tms_utime
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;stime
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tbuf-&gt;tms_stime
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;cutime
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tbuf-&gt;tms_cutime
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;cstime
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tbuf-&gt;tms_cstime
)paren
suffix:semicolon
)brace
r_return
id|jiffies
suffix:semicolon
)brace
DECL|function|sys_brk
r_int
id|sys_brk
c_func
(paren
r_int
r_int
id|end_data_seg
)paren
(brace
r_if
c_cond
(paren
id|end_data_seg
op_ge
id|current-&gt;end_code
op_logical_and
id|end_data_seg
OL
id|current-&gt;start_stack
op_minus
l_int|16384
)paren
id|current-&gt;brk
op_assign
id|end_data_seg
suffix:semicolon
r_return
id|current-&gt;brk
suffix:semicolon
)brace
multiline_comment|/*&n; * This needs some heave checking ...&n; * I just haven&squot;t get the stomach for it. I also don&squot;t fully&n; * understand sessions/pgrp etc. Let somebody who does explain it.&n; *&n; * OK, I think I have the protection semantics right.... this is really&n; * only important on a multi-user system anyway, to make sure one user&n; * can&squot;t send a signal to a process owned by another.  -TYT, 12/12/91&n; */
DECL|function|sys_setpgid
r_int
id|sys_setpgid
c_func
(paren
r_int
id|pid
comma
r_int
id|pgid
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
id|pid
op_assign
id|current-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgid
)paren
id|pgid
op_assign
id|current-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
id|pgid
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_logical_and
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
op_logical_and
(paren
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|p_pptr
op_eq
id|current
)paren
op_logical_or
(paren
id|task
(braket
id|i
)braket
op_eq
id|current
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|leader
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|session
op_ne
id|current-&gt;session
)paren
op_logical_or
(paren
(paren
id|pgid
op_ne
id|pid
)paren
op_logical_and
(paren
id|session_of_pgrp
c_func
(paren
id|pgid
)paren
op_ne
id|current-&gt;session
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pgrp
op_assign
id|pgid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|function|sys_getpgrp
r_int
id|sys_getpgrp
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;pgrp
suffix:semicolon
)brace
DECL|function|sys_setsid
r_int
id|sys_setsid
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;leader
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|current-&gt;leader
op_assign
l_int|1
suffix:semicolon
id|current-&gt;session
op_assign
id|current-&gt;pgrp
op_assign
id|current-&gt;pid
suffix:semicolon
id|current-&gt;tty
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|current-&gt;pgrp
suffix:semicolon
)brace
multiline_comment|/*&n; * Supplementary group ID&squot;s&n; */
DECL|function|sys_getgroups
r_int
id|sys_getgroups
c_func
(paren
r_int
id|gidsetsize
comma
id|gid_t
op_star
id|grouplist
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|gidsetsize
)paren
id|verify_area
c_func
(paren
id|grouplist
comma
r_sizeof
(paren
id|gid_t
)paren
op_star
id|gidsetsize
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|NGROUPS
)paren
op_logical_and
(paren
id|current-&gt;groups
(braket
id|i
)braket
op_ne
id|NOGROUP
)paren
suffix:semicolon
id|i
op_increment
comma
id|grouplist
op_increment
)paren
(brace
r_if
c_cond
(paren
id|gidsetsize
)paren
(brace
r_if
c_cond
(paren
id|i
op_ge
id|gidsetsize
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|put_fs_word
c_func
(paren
id|current-&gt;groups
(braket
id|i
)braket
comma
(paren
r_int
op_star
)paren
id|grouplist
)paren
suffix:semicolon
)brace
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|sys_setgroups
r_int
id|sys_setgroups
c_func
(paren
r_int
id|gidsetsize
comma
id|gid_t
op_star
id|grouplist
)paren
(brace
r_int
id|i
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
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|gidsetsize
OG
id|NGROUPS
)paren
r_return
op_minus
id|EINVAL
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
id|gidsetsize
suffix:semicolon
id|i
op_increment
comma
id|grouplist
op_increment
)paren
(brace
id|current-&gt;groups
(braket
id|i
)braket
op_assign
id|get_fs_word
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|grouplist
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|NGROUPS
)paren
id|current-&gt;groups
(braket
id|i
)braket
op_assign
id|NOGROUP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|in_group_p
r_int
id|in_group_p
c_func
(paren
id|gid_t
id|grp
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|grp
op_eq
id|current-&gt;egid
)paren
r_return
l_int|1
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
id|NGROUPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;groups
(braket
id|i
)braket
op_eq
id|NOGROUP
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;groups
(braket
id|i
)braket
op_eq
id|grp
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|thisname
r_static
r_struct
id|new_utsname
id|thisname
op_assign
(brace
id|UTS_SYSNAME
comma
id|UTS_NODENAME
comma
id|UTS_RELEASE
comma
id|UTS_VERSION
comma
id|UTS_MACHINE
)brace
suffix:semicolon
DECL|function|sys_newuname
r_int
id|sys_newuname
c_func
(paren
r_struct
id|new_utsname
op_star
id|name
)paren
(brace
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
id|verify_area
c_func
(paren
id|name
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|name
comma
op_amp
id|thisname
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
r_return
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|verify_area
c_func
(paren
id|name
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|thisname.sysname
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|name-&gt;sysname
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|thisname.nodename
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|name-&gt;nodename
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|thisname.release
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|name-&gt;release
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|thisname.version
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|name-&gt;version
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|thisname.machine
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|name-&gt;machine
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Only sethostname; gethostname can be implemented by calling uname()&n; */
DECL|function|sys_sethostname
r_int
id|sys_sethostname
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
id|i
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
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|__NEW_UTS_LEN
)paren
r_return
op_minus
id|EINVAL
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|thisname.nodename
(braket
id|i
)braket
op_assign
id|get_fs_byte
c_func
(paren
id|name
op_plus
id|i
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|thisname.nodename
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_getrlimit
r_int
id|sys_getrlimit
c_func
(paren
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
(brace
r_if
c_cond
(paren
id|resource
op_ge
id|RLIM_NLIMITS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|verify_area
c_func
(paren
id|rlim
comma
r_sizeof
op_star
id|rlim
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;rlim
(braket
id|resource
)braket
dot
id|rlim_cur
comma
(paren
r_int
r_int
op_star
)paren
id|rlim
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|current-&gt;rlim
(braket
id|resource
)braket
dot
id|rlim_max
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|rlim
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_setrlimit
r_int
id|sys_setrlimit
c_func
(paren
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
(brace
r_struct
id|rlimit
r_new
comma
op_star
id|old
suffix:semicolon
r_if
c_cond
(paren
id|resource
op_ge
id|RLIM_NLIMITS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|old
op_assign
id|current-&gt;rlim
op_plus
id|resource
suffix:semicolon
r_new
dot
id|rlim_cur
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|rlim
)paren
suffix:semicolon
r_new
dot
id|rlim_max
op_assign
id|get_fs_long
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|rlim
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_new
dot
id|rlim_cur
OG
id|old-&gt;rlim_max
)paren
op_logical_or
(paren
r_new
dot
id|rlim_max
OG
id|old-&gt;rlim_max
)paren
)paren
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
op_star
id|old
op_assign
r_new
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * It would make sense to put struct rusuage in the task_struct,&n; * except that would make the task_struct be *really big*.  After&n; * task_struct gets moved into malloc&squot;ed memory, it would&n; * make sense to do this.  It will make moving the rest of the information&n; * a lot simpler!  (Which we&squot;re not doing right now because we&squot;re not&n; * measuring them yet).&n; */
DECL|function|sys_getrusage
r_int
id|sys_getrusage
c_func
(paren
r_int
id|who
comma
r_struct
id|rusage
op_star
id|ru
)paren
(brace
r_struct
id|rusage
id|r
suffix:semicolon
r_int
r_int
op_star
id|lp
comma
op_star
id|lpend
comma
op_star
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|who
op_ne
id|RUSAGE_SELF
op_logical_and
id|who
op_ne
id|RUSAGE_CHILDREN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|verify_area
c_func
(paren
id|ru
comma
r_sizeof
op_star
id|ru
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|who
op_eq
id|RUSAGE_SELF
)paren
(brace
id|r.ru_utime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|current-&gt;utime
)paren
suffix:semicolon
id|r.ru_utime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|current-&gt;utime
)paren
suffix:semicolon
id|r.ru_stime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|current-&gt;stime
)paren
suffix:semicolon
id|r.ru_stime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|current-&gt;stime
)paren
suffix:semicolon
id|r.ru_minflt
op_assign
id|current-&gt;min_flt
suffix:semicolon
id|r.ru_majflt
op_assign
id|current-&gt;maj_flt
suffix:semicolon
)brace
r_else
(brace
id|r.ru_utime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|current-&gt;cutime
)paren
suffix:semicolon
id|r.ru_utime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|current-&gt;cutime
)paren
suffix:semicolon
id|r.ru_stime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|current-&gt;cstime
)paren
suffix:semicolon
id|r.ru_stime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|current-&gt;cstime
)paren
suffix:semicolon
id|r.ru_minflt
op_assign
id|current-&gt;cmin_flt
suffix:semicolon
id|r.ru_majflt
op_assign
id|current-&gt;cmaj_flt
suffix:semicolon
)brace
id|lp
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|r
suffix:semicolon
id|lpend
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|r
op_plus
l_int|1
)paren
suffix:semicolon
id|dest
op_assign
(paren
r_int
r_int
op_star
)paren
id|ru
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|lp
OL
id|lpend
suffix:semicolon
id|lp
op_increment
comma
id|dest
op_increment
)paren
id|put_fs_long
c_func
(paren
op_star
id|lp
comma
id|dest
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_gettimeofday
r_int
id|sys_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_if
c_cond
(paren
id|tv
)paren
(brace
id|verify_area
c_func
(paren
id|tv
comma
r_sizeof
op_star
id|tv
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|startup_time
op_plus
id|CT_TO_SECS
c_func
(paren
id|jiffies
op_plus
id|jiffies_offset
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|tv
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|CT_TO_USECS
c_func
(paren
id|jiffies
op_plus
id|jiffies_offset
)paren
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|tv
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
id|verify_area
c_func
(paren
id|tz
comma
r_sizeof
op_star
id|tz
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sys_tz.tz_minuteswest
comma
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sys_tz.tz_dsttime
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The first time we set the timezone, we will warp the clock so that&n; * it is ticking GMT time instead of local time.  Presumably, &n; * if someone is setting the timezone then we are running in an&n; * environment where the programs understand about timezones.&n; * This should be done at boot time in the /etc/rc script, as&n; * soon as possible, so that the clock can be set right.  Otherwise,&n; * various programs will get confused when the clock gets warped.&n; */
DECL|function|sys_settimeofday
r_int
id|sys_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_static
r_int
id|firsttime
op_assign
l_int|1
suffix:semicolon
r_void
id|adjust_clock
c_func
(paren
)paren
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
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|tz
)paren
(brace
id|sys_tz.tz_minuteswest
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
suffix:semicolon
id|sys_tz.tz_dsttime
op_assign
id|get_fs_long
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firsttime
)paren
(brace
id|firsttime
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tv
)paren
id|adjust_clock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tv
)paren
(brace
r_int
id|sec
comma
id|usec
suffix:semicolon
id|sec
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|tv
)paren
suffix:semicolon
id|usec
op_assign
id|get_fs_long
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|tv
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|startup_time
op_assign
id|sec
op_minus
id|jiffies
op_div
id|HZ
suffix:semicolon
id|jiffies_offset
op_assign
id|usec
op_star
id|HZ
op_div
l_int|1000000
op_minus
id|jiffies
op_mod
id|HZ
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust the time obtained from the CMOS to be GMT time instead of&n; * local time.&n; * &n; * This is ugly, but preferable to the alternatives.  Otherwise we&n; * would either need to write a program to do it in /etc/rc (and risk&n; * confusion if the program gets run more than once; it would also be &n; * hard to make the program warp the clock precisely n hours)  or&n; * compile in the timezone information into the kernel.  Bad, bad....&n; *&n; * XXX Currently does not adjust for daylight savings time.  May not&n; * need to do anything, depending on how smart (dumb?) the BIOS&n; * is.  Blast it all.... the best thing to do not depend on the CMOS&n; * clock at all, but get the time via NTP or timed if you&squot;re on a &n; * network....&t;&t;&t;&t;- TYT, 1/1/92&n; */
DECL|function|adjust_clock
r_void
id|adjust_clock
c_func
(paren
)paren
(brace
id|startup_time
op_add_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
)brace
DECL|function|sys_umask
r_int
id|sys_umask
c_func
(paren
r_int
id|mask
)paren
(brace
r_int
id|old
op_assign
id|current-&gt;umask
suffix:semicolon
id|current-&gt;umask
op_assign
id|mask
op_amp
l_int|0777
suffix:semicolon
r_return
(paren
id|old
)paren
suffix:semicolon
)brace
eof
