multiline_comment|/*&n; *  linux/kernel/sys.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/resource.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * this indicates whether you can reboot with ctrl-alt-del: the default is yes&n; */
DECL|variable|C_A_D
r_static
r_int
id|C_A_D
op_assign
l_int|1
suffix:semicolon
r_extern
r_void
id|adjust_clock
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PZERO
mdefine_line|#define&t;PZERO&t;15
DECL|function|sys_ni_syscall
id|asmlinkage
r_int
id|sys_ni_syscall
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
id|i
suffix:semicolon
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
multiline_comment|/* Map out the low memory: it&squot;s no longer needed */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|768
suffix:semicolon
id|i
op_increment
)paren
id|swapper_pg_dir
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* endless idle loop with no priority at all */
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
id|hlt_works_ok
op_logical_and
op_logical_neg
id|need_resched
)paren
id|__asm__
c_func
(paren
l_string|&quot;hlt&quot;
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
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
id|asmlinkage
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
id|asmlinkage
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
id|asmlinkage
r_int
id|sys_profil
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
DECL|function|sys_ftime
id|asmlinkage
r_int
id|sys_ftime
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
DECL|function|sys_break
id|asmlinkage
r_int
id|sys_break
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
DECL|function|sys_stty
id|asmlinkage
r_int
id|sys_stty
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
DECL|function|sys_gtty
id|asmlinkage
r_int
id|sys_gtty
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
DECL|function|sys_prof
id|asmlinkage
r_int
id|sys_prof
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
r_extern
r_void
id|hard_reset_now
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
id|sys_kill
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Reboot system call: for obvious reasons only root may call it,&n; * and even root needs to set up some magic numbers in the registers&n; * so that some mistake won&squot;t make this reboot the whole machine.&n; * You can also set the meaning of the ctrl-alt-del-key here.&n; *&n; * reboot doesn&squot;t sync: do that yourself before calling this.&n; */
DECL|function|sys_reboot
id|asmlinkage
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
r_if
c_cond
(paren
id|flag
op_eq
l_int|0xCDEF0123
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;System halted&bslash;n&quot;
)paren
suffix:semicolon
id|sys_kill
c_func
(paren
op_minus
l_int|1
comma
id|SIGKILL
)paren
suffix:semicolon
id|do_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * This function gets called by ctrl-alt-del - ie the keyboard interrupt.&n; * As it&squot;s called within an interrupt, it may NOT sync: the only choice&n; * is whether to reboot at once, or just ignore the ctrl-alt-del.&n; */
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
multiline_comment|/*&n; * Unprivileged users may change the real gid to the effective gid&n; * or vice versa.  (BSD-style)&n; *&n; * If you set the real gid at all, or set the effective gid to a value not&n; * equal to the real gid, then the saved gid is set to the new effective gid.&n; *&n; * This makes it possible for a setgid program to completely drop its&n; * privileges, which is often a useful assertion to make when you are doing&n; * a security audit over a program.&n; *&n; * The general idea is that a program which uses just setregid() will be&n; * 100% compatible with BSD.  A program which uses just setgid() will be&n; * 100% compatible with POSIX w/ Saved ID&squot;s. &n; */
DECL|function|sys_setregid
id|asmlinkage
r_int
id|sys_setregid
c_func
(paren
id|gid_t
id|rgid
comma
id|gid_t
id|egid
)paren
(brace
r_int
id|old_rgid
op_assign
id|current-&gt;gid
suffix:semicolon
r_if
c_cond
(paren
id|rgid
op_ne
(paren
id|gid_t
)paren
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|old_rgid
op_eq
id|rgid
)paren
op_logical_or
(paren
id|current-&gt;egid
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
op_ne
(paren
id|gid_t
)paren
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|old_rgid
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
(paren
id|current-&gt;sgid
op_eq
id|egid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;egid
op_assign
id|egid
suffix:semicolon
r_else
(brace
id|current-&gt;gid
op_assign
id|old_rgid
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rgid
op_ne
(paren
id|gid_t
)paren
op_minus
l_int|1
op_logical_or
(paren
id|egid
op_ne
(paren
id|gid_t
)paren
op_minus
l_int|1
op_logical_and
id|egid
op_ne
id|old_rgid
)paren
)paren
id|current-&gt;sgid
op_assign
id|current-&gt;egid
suffix:semicolon
id|current-&gt;fsgid
op_assign
id|current-&gt;egid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * setgid() is implemented like SysV w/ SAVED_IDS &n; */
DECL|function|sys_setgid
id|asmlinkage
r_int
id|sys_setgid
c_func
(paren
id|gid_t
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
id|current-&gt;fsgid
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
id|current-&gt;fsgid
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
id|asmlinkage
r_int
id|sys_acct
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
DECL|function|sys_phys
id|asmlinkage
r_int
id|sys_phys
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
DECL|function|sys_lock
id|asmlinkage
r_int
id|sys_lock
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
DECL|function|sys_mpx
id|asmlinkage
r_int
id|sys_mpx
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
DECL|function|sys_ulimit
id|asmlinkage
r_int
id|sys_ulimit
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
DECL|function|sys_old_syscall
id|asmlinkage
r_int
id|sys_old_syscall
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
multiline_comment|/*&n; * Unprivileged users may change the real uid to the effective uid&n; * or vice versa.  (BSD-style)&n; *&n; * If you set the real uid at all, or set the effective uid to a value not&n; * equal to the real uid, then the saved uid is set to the new effective uid.&n; *&n; * This makes it possible for a setuid program to completely drop its&n; * privileges, which is often a useful assertion to make when you are doing&n; * a security audit over a program.&n; *&n; * The general idea is that a program which uses just setreuid() will be&n; * 100% compatible with BSD.  A program which uses just setuid() will be&n; * 100% compatible with POSIX w/ Saved ID&squot;s. &n; */
DECL|function|sys_setreuid
id|asmlinkage
r_int
id|sys_setreuid
c_func
(paren
id|uid_t
id|ruid
comma
id|uid_t
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
op_ne
(paren
id|uid_t
)paren
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|old_ruid
op_eq
id|ruid
)paren
op_logical_or
(paren
id|current-&gt;euid
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
op_ne
(paren
id|uid_t
)paren
op_minus
l_int|1
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
(paren
id|current-&gt;suid
op_eq
id|euid
)paren
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;euid
op_assign
id|euid
suffix:semicolon
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
r_if
c_cond
(paren
id|ruid
op_ne
(paren
id|uid_t
)paren
op_minus
l_int|1
op_logical_or
(paren
id|euid
op_ne
(paren
id|uid_t
)paren
op_minus
l_int|1
op_logical_and
id|euid
op_ne
id|old_ruid
)paren
)paren
id|current-&gt;suid
op_assign
id|current-&gt;euid
suffix:semicolon
id|current-&gt;fsuid
op_assign
id|current-&gt;euid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * setuid() is implemented like SysV w/ SAVED_IDS &n; * &n; * Note that SAVED_ID&squot;s is deficient in that a setuid root program&n; * like sendmail, for example, cannot set its uid to be a normal &n; * user and then switch back, because if you&squot;re root, setuid() sets&n; * the saved uid too.  If you don&squot;t like this, blame the bright people&n; * in the POSIX committee and/or USG.  Note that the BSD-style setreuid()&n; * will allow a root program to temporarily drop privileges and be able to&n; * regain them by swapping the real and effective uid.  &n; */
DECL|function|sys_setuid
id|asmlinkage
r_int
id|sys_setuid
c_func
(paren
id|uid_t
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
id|current-&gt;fsuid
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
id|current-&gt;fsuid
op_assign
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
multiline_comment|/*&n; * &quot;setfsuid()&quot; sets the fsuid - the uid used for filesystem checks. This&n; * is used for &quot;access()&quot; and for the NFS daemon (letting nfsd stay at&n; * whatever uid it wants to). It normally shadows &quot;euid&quot;, except when&n; * explicitly set by setfsuid() or for access..&n; */
DECL|function|sys_setfsuid
id|asmlinkage
r_int
id|sys_setfsuid
c_func
(paren
id|uid_t
id|uid
)paren
(brace
r_int
id|old_fsuid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|uid
op_eq
id|current-&gt;uid
op_logical_or
id|uid
op_eq
id|current-&gt;euid
op_logical_or
id|uid
op_eq
id|current-&gt;suid
op_logical_or
id|uid
op_eq
id|current-&gt;fsuid
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;fsuid
op_assign
id|uid
suffix:semicolon
r_return
id|old_fsuid
suffix:semicolon
)brace
multiline_comment|/*&n; * Samma p&#xfffd; svenska..&n; */
DECL|function|sys_setfsgid
id|asmlinkage
r_int
id|sys_setfsgid
c_func
(paren
id|gid_t
id|gid
)paren
(brace
r_int
id|old_fsgid
op_assign
id|current-&gt;fsgid
suffix:semicolon
r_if
c_cond
(paren
id|gid
op_eq
id|current-&gt;gid
op_logical_or
id|gid
op_eq
id|current-&gt;egid
op_logical_or
id|gid
op_eq
id|current-&gt;sgid
op_logical_or
id|gid
op_eq
id|current-&gt;fsgid
op_logical_or
id|suser
c_func
(paren
)paren
)paren
id|current-&gt;fsgid
op_assign
id|gid
suffix:semicolon
r_return
id|old_fsgid
suffix:semicolon
)brace
DECL|function|sys_times
id|asmlinkage
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
r_int
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|tbuf
comma
r_sizeof
op_star
id|tbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
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
id|asmlinkage
r_int
id|sys_brk
c_func
(paren
r_int
r_int
id|brk
)paren
(brace
r_int
id|freepages
suffix:semicolon
r_int
r_int
id|rlim
suffix:semicolon
r_int
r_int
id|newbrk
comma
id|oldbrk
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_if
c_cond
(paren
id|brk
OL
id|current-&gt;mm-&gt;end_code
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
id|newbrk
op_assign
id|PAGE_ALIGN
c_func
(paren
id|brk
)paren
suffix:semicolon
id|oldbrk
op_assign
id|PAGE_ALIGN
c_func
(paren
id|current-&gt;mm-&gt;brk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldbrk
op_eq
id|newbrk
)paren
r_return
id|current-&gt;mm-&gt;brk
op_assign
id|brk
suffix:semicolon
multiline_comment|/*&n;&t; * Always allow shrinking brk&n;&t; */
r_if
c_cond
(paren
id|brk
op_le
id|current-&gt;mm-&gt;brk
)paren
(brace
id|current-&gt;mm-&gt;brk
op_assign
id|brk
suffix:semicolon
id|do_munmap
c_func
(paren
id|newbrk
comma
id|oldbrk
op_minus
id|newbrk
)paren
suffix:semicolon
r_return
id|brk
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check against rlimit and stack..&n;&t; */
id|rlim
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_DATA
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|rlim
op_ge
id|RLIM_INFINITY
)paren
id|rlim
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|brk
op_minus
id|current-&gt;mm-&gt;end_code
OG
id|rlim
op_logical_or
id|brk
op_ge
id|current-&gt;mm-&gt;start_stack
op_minus
l_int|16384
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
multiline_comment|/*&n;&t; * Check against existing mmap mappings.&n;&t; */
r_for
c_loop
(paren
id|vma
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_if
c_cond
(paren
id|newbrk
op_le
id|vma-&gt;vm_start
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|oldbrk
OL
id|vma-&gt;vm_end
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * stupid algorithm to decide if we have enough memory: while&n;&t; * simple, it hopefully works in most obvious cases.. Easy to&n;&t; * fool it, but this should catch most mistakes.&n;&t; */
id|freepages
op_assign
id|buffermem
op_rshift
l_int|12
suffix:semicolon
id|freepages
op_add_assign
id|nr_free_pages
suffix:semicolon
id|freepages
op_add_assign
id|nr_swap_pages
suffix:semicolon
id|freepages
op_sub_assign
(paren
id|high_memory
op_minus
l_int|0x100000
)paren
op_rshift
l_int|16
suffix:semicolon
id|freepages
op_sub_assign
(paren
id|newbrk
op_minus
id|oldbrk
)paren
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|freepages
OL
l_int|0
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
macro_line|#if 0
id|freepages
op_add_assign
id|current-&gt;mm-&gt;rss
suffix:semicolon
id|freepages
op_sub_assign
id|oldbrk
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|freepages
OL
l_int|0
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Ok, we have probably got enough memory - let it rip.&n;&t; */
id|current-&gt;mm-&gt;brk
op_assign
id|brk
suffix:semicolon
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|oldbrk
comma
id|newbrk
op_minus
id|oldbrk
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
r_return
id|brk
suffix:semicolon
)brace
multiline_comment|/*&n; * This needs some heave checking ...&n; * I just haven&squot;t get the stomach for it. I also don&squot;t fully&n; * understand sessions/pgrp etc. Let somebody who does explain it.&n; *&n; * OK, I think I have the protection semantics right.... this is really&n; * only important on a multi-user system anyway, to make sure one user&n; * can&squot;t send a signal to a process owned by another.  -TYT, 12/12/91&n; *&n; * Auch. Had to add the &squot;did_exec&squot; flag to conform completely to POSIX.&n; * LBT 04.03.94&n; */
DECL|function|sys_setpgid
id|asmlinkage
r_int
id|sys_setpgid
c_func
(paren
id|pid_t
id|pid
comma
id|pid_t
id|pgid
)paren
(brace
r_struct
id|task_struct
op_star
id|p
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
id|pid
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
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
r_goto
id|found_task
suffix:semicolon
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
id|found_task
suffix:colon
r_if
c_cond
(paren
id|p-&gt;p_pptr
op_eq
id|current
op_logical_or
id|p-&gt;p_opptr
op_eq
id|current
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;session
op_ne
id|current-&gt;session
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;did_exec
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p
op_ne
id|current
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;leader
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pgid
op_ne
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
id|tmp
suffix:semicolon
id|for_each_task
(paren
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;pgrp
op_eq
id|pgid
op_logical_and
id|tmp-&gt;session
op_eq
id|current-&gt;session
)paren
r_goto
id|ok_pgid
suffix:semicolon
)brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|ok_pgid
suffix:colon
id|p-&gt;pgrp
op_assign
id|pgid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_getpgid
id|asmlinkage
r_int
id|sys_getpgid
c_func
(paren
id|pid_t
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
r_return
id|current-&gt;pgrp
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
r_return
id|p-&gt;pgrp
suffix:semicolon
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|function|sys_getpgrp
id|asmlinkage
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
id|asmlinkage
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
l_int|NULL
suffix:semicolon
r_return
id|current-&gt;pgrp
suffix:semicolon
)brace
multiline_comment|/*&n; * Supplementary group ID&squot;s&n; */
DECL|function|sys_getgroups
id|asmlinkage
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
(brace
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
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
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
)brace
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gidsetsize
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|gidsetsize
)paren
r_break
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
id|grouplist
op_increment
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|sys_setgroups
id|asmlinkage
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
id|current-&gt;fsgid
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
DECL|function|sys_newuname
id|asmlinkage
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|memcpy_tofs
c_func
(paren
id|name
comma
op_amp
id|system_utsname
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_uname
id|asmlinkage
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|system_utsname.sysname
comma
r_sizeof
(paren
id|system_utsname.sysname
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|system_utsname.nodename
comma
r_sizeof
(paren
id|system_utsname.nodename
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|system_utsname.release
comma
r_sizeof
(paren
id|system_utsname.release
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|system_utsname.version
comma
r_sizeof
(paren
id|system_utsname.version
)paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|system_utsname.machine
comma
r_sizeof
(paren
id|system_utsname.machine
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_olduname
id|asmlinkage
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
op_star
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_tofs
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
id|system_utsname.nodename
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
id|system_utsname.release
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
id|system_utsname.version
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
id|system_utsname.machine
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
id|asmlinkage
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
id|system_utsname.nodename
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
id|system_utsname.nodename
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
multiline_comment|/*&n; * Only setdomainname; getdomainname can be implemented by calling&n; * uname()&n; */
DECL|function|sys_setdomainname
id|asmlinkage
r_int
id|sys_setdomainname
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
id|system_utsname.domainname
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
id|system_utsname.domainname
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
id|asmlinkage
r_int
id|sys_getrlimit
c_func
(paren
r_int
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
(brace
r_int
id|error
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|rlim
comma
r_sizeof
op_star
id|rlim
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
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
id|asmlinkage
r_int
id|sys_setrlimit
c_func
(paren
r_int
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
id|new_rlim
comma
op_star
id|old_rlim
suffix:semicolon
r_int
id|err
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
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|rlim
comma
r_sizeof
(paren
op_star
id|rlim
)paren
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
id|memcpy_fromfs
c_func
(paren
op_amp
id|new_rlim
comma
id|rlim
comma
r_sizeof
(paren
op_star
id|rlim
)paren
)paren
suffix:semicolon
id|old_rlim
op_assign
id|current-&gt;rlim
op_plus
id|resource
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|new_rlim.rlim_cur
OG
id|old_rlim-&gt;rlim_max
)paren
op_logical_or
(paren
id|new_rlim.rlim_max
OG
id|old_rlim-&gt;rlim_max
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
id|old_rlim
op_assign
id|new_rlim
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * It would make sense to put struct rusage in the task_struct,&n; * except that would make the task_struct be *really big*.  After&n; * task_struct gets moved into malloc&squot;ed memory, it would&n; * make sense to do this.  It will make moving the rest of the information&n; * a lot simpler!  (Which we&squot;re not doing right now because we&squot;re not&n; * measuring them yet).&n; */
DECL|function|getrusage
r_int
id|getrusage
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
id|who
comma
r_struct
id|rusage
op_star
id|ru
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|rusage
id|r
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|ru
comma
r_sizeof
op_star
id|ru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
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
r_switch
c_cond
(paren
id|who
)paren
(brace
r_case
id|RUSAGE_SELF
suffix:colon
id|r.ru_utime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;utime
)paren
suffix:semicolon
id|r.ru_utime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;utime
)paren
suffix:semicolon
id|r.ru_stime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;stime
)paren
suffix:semicolon
id|r.ru_stime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;stime
)paren
suffix:semicolon
id|r.ru_minflt
op_assign
id|p-&gt;mm-&gt;min_flt
suffix:semicolon
id|r.ru_majflt
op_assign
id|p-&gt;mm-&gt;maj_flt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RUSAGE_CHILDREN
suffix:colon
id|r.ru_utime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;cutime
)paren
suffix:semicolon
id|r.ru_utime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;cutime
)paren
suffix:semicolon
id|r.ru_stime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;cstime
)paren
suffix:semicolon
id|r.ru_stime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;cstime
)paren
suffix:semicolon
id|r.ru_minflt
op_assign
id|p-&gt;mm-&gt;cmin_flt
suffix:semicolon
id|r.ru_majflt
op_assign
id|p-&gt;mm-&gt;cmaj_flt
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|r.ru_utime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;utime
op_plus
id|p-&gt;cutime
)paren
suffix:semicolon
id|r.ru_utime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;utime
op_plus
id|p-&gt;cutime
)paren
suffix:semicolon
id|r.ru_stime.tv_sec
op_assign
id|CT_TO_SECS
c_func
(paren
id|p-&gt;stime
op_plus
id|p-&gt;cstime
)paren
suffix:semicolon
id|r.ru_stime.tv_usec
op_assign
id|CT_TO_USECS
c_func
(paren
id|p-&gt;stime
op_plus
id|p-&gt;cstime
)paren
suffix:semicolon
id|r.ru_minflt
op_assign
id|p-&gt;mm-&gt;min_flt
op_plus
id|p-&gt;mm-&gt;cmin_flt
suffix:semicolon
id|r.ru_majflt
op_assign
id|p-&gt;mm-&gt;maj_flt
op_plus
id|p-&gt;mm-&gt;cmaj_flt
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|ru
comma
op_amp
id|r
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_getrusage
id|asmlinkage
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
r_return
id|getrusage
c_func
(paren
id|current
comma
id|who
comma
id|ru
)paren
suffix:semicolon
)brace
DECL|function|sys_umask
id|asmlinkage
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
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|current-&gt;fs-&gt;umask
op_assign
id|mask
op_amp
id|S_IRWXUGO
suffix:semicolon
r_return
(paren
id|old
)paren
suffix:semicolon
)brace
eof
