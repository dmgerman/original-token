macro_line|#ifndef _ASM_PPC_UNISTD_H_
DECL|macro|_ASM_PPC_UNISTD_H_
mdefine_line|#define _ASM_PPC_UNISTD_H_
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
DECL|macro|__NR_setup
mdefine_line|#define __NR_setup&t;&t;  0&t;/* used only by init, to get system going */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;  1
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;  2
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;  3
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;  4
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;  5
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;  6
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;&t;  7
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;  8
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;  9
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t; 10
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t; 11
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t; 12
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t; 13
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t; 14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t; 15
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t; 16
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t; 17
DECL|macro|__NR_oldstat
mdefine_line|#define __NR_oldstat&t;&t; 18
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t; 19
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t; 20
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t; 21
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t; 22
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t; 23
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t; 24
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;&t; 25
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t; 26
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t; 27
DECL|macro|__NR_oldfstat
mdefine_line|#define __NR_oldfstat&t;&t; 28
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t; 29
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t; 30
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;&t; 31
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;&t; 32
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t; 33
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t; 34
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;&t; 35
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t; 36
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t; 37
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t; 38
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t; 39
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t; 40
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t; 41
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t; 42
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t; 43
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;&t; 44
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t; 45
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t; 46
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t; 47
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;&t; 48
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t; 49
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t; 50
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t; 51
DECL|macro|__NR_phys
mdefine_line|#define __NR_phys&t;&t; 52
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;&t; 53
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t; 54
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t; 55
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;&t; 56
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t; 57
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;&t; 58
DECL|macro|__NR_oldolduname
mdefine_line|#define __NR_oldolduname&t; 59
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t; 60
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t; 61
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t; 62
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t; 63
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t; 64
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t; 65
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t; 66
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t; 67
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;&t; 68
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;&t; 69
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t; 70
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t; 71
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t; 72
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t; 73
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t; 74
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t; 75
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t; 76
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t; 77
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t; 78
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t; 79
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t; 80
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t; 81
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t; 82
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t; 83
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat&t;&t; 84
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t; 85
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t; 86
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t; 87
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t; 88
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir&t;&t; 89
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t; 90
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t; 91
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t; 92
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t; 93
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t; 94
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t; 95
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t; 96
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t; 97
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil&t;&t; 98
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t; 99
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;100
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm&t;&t;101
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall&t;&t;102
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;103
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;104
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;105
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;106
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;107
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;108
DECL|macro|__NR_olduname
mdefine_line|#define __NR_olduname&t;&t;109
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl&t;&t;110
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;111
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;112
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;113
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;114
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;115
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;116
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc&t;&t;117
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;118
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;119
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;120
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;121
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;122
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt&t;&t;123
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;124
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;125
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;126
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;127
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;128
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;129
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;130
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;131
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;132
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;133
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;134
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;135
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;136
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;137 /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;138
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;139
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek&t;&t;140
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;141
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;142
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;143
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;144
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;145
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;146
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;147
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;148
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;149
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;150
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;151
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;152
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;153
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;154
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;155
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;156
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;157
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;158
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;159
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;160
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;161
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;162
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;163
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;164
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;165
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;166
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;167
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;168
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;169
DECL|macro|__NR
mdefine_line|#define __NR(n)&t;#n
DECL|macro|__do_syscall
mdefine_line|#define __do_syscall(n) &bslash;&n;&t;asm volatile (&quot;li 0,%0&bslash;n&bslash;&n;&t;sc&bslash;n&bslash;&n;&t;bns 1f&bslash;n&bslash;&n;&t;mr 0,3&bslash;n&bslash;&n;&t;lis 3,errno@ha&bslash;n&bslash;&n;&t;stw 0,errno@l(3)&bslash;n&bslash;&n;&t;li 3,-1&bslash;n&bslash;&n;1:&quot; : : &quot;i&quot; (n) : &quot;r0&quot;, &quot;r3&quot;)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ __do_syscall(__NR_##name); }
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ __do_syscall(__NR_##name); }
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ __do_syscall(__NR_##name); }
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ __do_syscall(__NR_##name); }
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ __do_syscall(__NR_##name); }
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ __do_syscall(__NR_##name); }
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * Forking from kernel space will result in NO COPY ON WRITE (!!!),&n; * until an execve is executed. This is no problem, but for the stack.&n; * This is handled by not letting main() use the stack at all after&n; * fork().  On the PowerPC, this means we can only call leaf functions.&n; */
multiline_comment|/*&n; * Create a new kernel thread.&n; */
r_extern
r_int
id|__kernel_thread
c_func
(paren
r_int
r_int
comma
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
DECL|function|kernel_thread
r_static
r_inline
r_int
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
r_return
id|__kernel_thread
c_func
(paren
id|flags
op_or
id|CLONE_VM
comma
id|fn
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * System call prototypes.&n; */
r_int
id|idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|setup
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|sync
c_func
(paren
r_void
)paren
suffix:semicolon
id|pid_t
id|setsid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|write
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
id|off_t
)paren
suffix:semicolon
r_int
id|dup
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|execve
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_char
op_star
op_star
)paren
suffix:semicolon
r_int
id|open
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|close
c_func
(paren
r_int
)paren
suffix:semicolon
id|pid_t
id|waitpid
c_func
(paren
id|pid_t
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|wait
r_static
r_inline
id|pid_t
id|wait
c_func
(paren
r_int
op_star
id|wait_stat
)paren
(brace
r_return
id|waitpid
c_func
(paren
op_minus
l_int|1
comma
id|wait_stat
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#endif /* _ASM_PPC_UNISTD_H_ */
eof
