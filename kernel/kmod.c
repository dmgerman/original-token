multiline_comment|/*&n;&t;kmod, the new module loader (replaces kerneld)&n;&t;Kirk Petersen&n;&n;&t;Reorganized not to be a daemon by Adam Richter, with guidance&n;&t;from Greg Zornetzer.&n;&n;&t;Modified to avoid chroot and file sharing problems.&n;&t;Mikael Pettersson&n;&n;&t;Limit the concurrent number of kmod modprobes to catch loops from&n;&t;&quot;modprobe needs a service that is in a module&quot;.&n;&t;Keith Owens &lt;kaos@ocs.com.au&gt; December 1999&n;*/
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n;&t;modprobe_path is set via /proc/sys.&n;*/
DECL|variable|modprobe_path
r_char
id|modprobe_path
(braket
l_int|256
)braket
op_assign
l_string|&quot;/sbin/modprobe&quot;
suffix:semicolon
r_extern
r_int
id|max_threads
suffix:semicolon
r_static
r_inline
r_void
DECL|function|use_init_fs_context
id|use_init_fs_context
c_func
(paren
r_void
)paren
(brace
r_struct
id|fs_struct
op_star
id|our_fs
comma
op_star
id|init_fs
suffix:semicolon
multiline_comment|/*&n;&t; * Make modprobe&squot;s fs context be a copy of init&squot;s.&n;&t; *&n;&t; * We cannot use the user&squot;s fs context, because it&n;&t; * may have a different root than init.&n;&t; * Since init was created with CLONE_FS, we can grab&n;&t; * its fs context from &quot;init_task&quot;.&n;&t; *&n;&t; * The fs context has to be a copy. If it is shared&n;&t; * with init, then any chdir() call in modprobe will&n;&t; * also affect init and the other threads sharing&n;&t; * init_task&squot;s fs context.&n;&t; *&n;&t; * We created the exec_modprobe thread without CLONE_FS,&n;&t; * so we can update the fields in our fs context freely.&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|our_fs
op_assign
id|current-&gt;fs
suffix:semicolon
id|init_fs
op_assign
id|init_task.fs
suffix:semicolon
id|our_fs-&gt;umask
op_assign
id|init_fs-&gt;umask
suffix:semicolon
id|set_fs_root
c_func
(paren
id|our_fs
comma
id|init_fs-&gt;rootmnt
comma
id|init_fs-&gt;root
)paren
suffix:semicolon
id|set_fs_pwd
c_func
(paren
id|our_fs
comma
id|init_fs-&gt;pwdmnt
comma
id|init_fs-&gt;pwd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|our_fs-&gt;altroot
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
op_assign
id|our_fs-&gt;altrootmnt
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|our_fs-&gt;altroot
suffix:semicolon
id|our_fs-&gt;altrootmnt
op_assign
l_int|NULL
suffix:semicolon
id|our_fs-&gt;altroot
op_assign
l_int|NULL
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|exec_usermodehelper
r_int
id|exec_usermodehelper
c_func
(paren
r_char
op_star
id|program_path
comma
r_char
op_star
id|argv
(braket
)braket
comma
r_char
op_star
id|envp
(braket
)braket
)paren
(brace
r_int
id|i
suffix:semicolon
id|current-&gt;session
op_assign
l_int|1
suffix:semicolon
id|current-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|use_init_fs_context
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Prevent parent user process from sending signals to child.&n;&t;   Otherwise, if the modprobe program does not exist, it might&n;&t;   be possible to get a user defined signal handler to execute&n;&t;   as the super user right after the execve fails if you time&n;&t;   the signal just right.&n;&t;*/
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|flush_signal_handlers
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
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
id|current-&gt;files-&gt;max_fds
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;files-&gt;fd
(braket
id|i
)braket
)paren
id|close
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Drop the &quot;current user&quot; thing */
id|free_uid
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* Give kmod all effective privileges.. */
id|current-&gt;uid
op_assign
id|current-&gt;euid
op_assign
id|current-&gt;fsuid
op_assign
l_int|0
suffix:semicolon
id|cap_set_full
c_func
(paren
id|current-&gt;cap_effective
)paren
suffix:semicolon
multiline_comment|/* Allow execve args to be in kernel space. */
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* Go, go, go... */
r_if
c_cond
(paren
id|execve
c_func
(paren
id|program_path
comma
id|argv
comma
id|envp
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exec_modprobe
r_static
r_int
id|exec_modprobe
c_func
(paren
r_void
op_star
id|module_name
)paren
(brace
r_static
r_char
op_star
id|envp
(braket
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=linux&quot;
comma
l_string|&quot;PATH=/sbin:/usr/sbin:/bin:/usr/bin&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
id|modprobe_path
comma
l_string|&quot;-s&quot;
comma
l_string|&quot;-k&quot;
comma
(paren
r_char
op_star
)paren
id|module_name
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|exec_usermodehelper
c_func
(paren
id|modprobe_path
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kmod: failed to exec %s -s -k %s, errno = %d&bslash;n&quot;
comma
id|modprobe_path
comma
(paren
r_char
op_star
)paren
id|module_name
comma
id|errno
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;request_module - try to load a kernel module&n; *&t;@module_name: Name of module&n; *&n; * &t;Load a module using the user mode module loader. The function returns&n; *&t;zero on success or a negative errno code on failure. Note that a&n; * &t;successful module load does not mean the module did not then unload&n; *&t;and exit on an error of its own. Callers must check that the service&n; *&t;they requested is now available not blindly invoke it.&n; *&n; *&t;If module auto-loading support is disabled then this function&n; *&t;becomes a no-operation.&n; */
DECL|function|request_module
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_int
id|pid
suffix:semicolon
r_int
id|waitpid_result
suffix:semicolon
id|sigset_t
id|tmpsig
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
id|atomic_t
id|kmod_concurrent
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|macro|MAX_KMOD_CONCURRENT
mdefine_line|#define MAX_KMOD_CONCURRENT 50&t;/* Completely arbitrary value - KAO */
r_static
r_int
id|kmod_loop_msg
suffix:semicolon
multiline_comment|/* Don&squot;t allow request_module() before the root fs is mounted!  */
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: Root fs not mounted&bslash;n&quot;
comma
id|module_name
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* If modprobe needs a service that is in a module, we get a recursive&n;&t; * loop.  Limit the number of running kmod threads to max_threads/2 or&n;&t; * MAX_KMOD_CONCURRENT, whichever is the smaller.  A cleaner method&n;&t; * would be to run the parents of this process, counting how many times&n;&t; * kmod was invoked.  That would mean accessing the internals of the&n;&t; * process tables to get the command line, proc_pid_cmdline is static&n;&t; * and it is not worth changing the proc code just to handle this case. &n;&t; * KAO.&n;&t; */
id|i
op_assign
id|max_threads
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|MAX_KMOD_CONCURRENT
)paren
id|i
op_assign
id|MAX_KMOD_CONCURRENT
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|kmod_concurrent
)paren
OG
id|i
)paren
(brace
r_if
c_cond
(paren
id|kmod_loop_msg
op_increment
OL
l_int|5
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kmod: runaway modprobe loop assumed and stopped&bslash;n&quot;
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|exec_modprobe
comma
(paren
r_void
op_star
)paren
id|module_name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: fork failed, errno %d&bslash;n&quot;
comma
id|module_name
comma
op_minus
id|pid
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
multiline_comment|/* Block everything but SIGKILL/SIGSTOP */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|tmpsig
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sigmask
c_func
(paren
id|SIGKILL
)paren
op_or
id|sigmask
c_func
(paren
id|SIGSTOP
)paren
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|waitpid_result
op_assign
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
id|__WCLONE
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
multiline_comment|/* Allow signals again.. */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|tmpsig
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitpid_result
op_ne
id|pid
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: waitpid(%d,...) failed, errno %d&bslash;n&quot;
comma
id|module_name
comma
id|pid
comma
op_minus
id|waitpid_result
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
