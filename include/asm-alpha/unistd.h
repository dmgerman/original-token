macro_line|#ifndef _ALPHA_UNISTD_H
DECL|macro|_ALPHA_UNISTD_H
mdefine_line|#define _ALPHA_UNISTD_H
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;  1
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;  2
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;  3
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;  4
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;  6
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;  7
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;  9
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t; 10
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t; 12
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t; 13
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t; 14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t; 15
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t; 16
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t; 17
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t; 19
DECL|macro|__NR_getxpid
mdefine_line|#define __NR_getxpid&t;&t; 20
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t; 23
DECL|macro|__NR_getxuid
mdefine_line|#define __NR_getxuid&t;&t; 24
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t; 26
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t; 33
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t; 36
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t; 37
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t; 39
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t; 41
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t; 42
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t; 45
DECL|macro|__NR_getxgid
mdefine_line|#define __NR_getxgid&t;&t; 47
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t; 51
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t; 52
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t; 54
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t; 57
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t; 58
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t; 59
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t; 60
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t; 61
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t; 63
DECL|macro|__NR_getpagesize
mdefine_line|#define __NR_getpagesize&t; 64
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t; 67
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t; 68
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t; 71&t;/* OSF/1 mmap is superset of Linux */
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t; 73
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t; 74
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise&t;&t; 75
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t; 76
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t; 79
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t; 80
DECL|macro|__NR_setpgrp
mdefine_line|#define __NR_setpgrp&t;&t; 82&t;/* BSD alias for setpgid */
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t; 83
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t; 86
DECL|macro|__NR_gethostname
mdefine_line|#define __NR_gethostname&t; 87
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t; 88
DECL|macro|__NR_getdtablesize
mdefine_line|#define __NR_getdtablesize&t; 89
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t; 90
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t; 91
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t; 92
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t; 93
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t; 95
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t; 96
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket&t;&t; 97
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect&t;&t; 98
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept&t;&t; 99
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;100
DECL|macro|__NR_send
mdefine_line|#define __NR_send&t;&t;101
DECL|macro|__NR_recv
mdefine_line|#define __NR_recv&t;&t;102
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;103
DECL|macro|__NR_bind
mdefine_line|#define __NR_bind&t;&t;104
DECL|macro|__NR_setsockopt
mdefine_line|#define __NR_setsockopt&t;&t;105
DECL|macro|__NR_listen
mdefine_line|#define __NR_listen&t;&t;106
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t;111
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg&t;&t;113
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg&t;&t;114
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;116
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;117
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt&t;&t;118
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;120
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;121
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;122
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;123
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;124
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom&t;&t;125
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;126
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;127
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;128
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;129
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;130
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;131
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;132
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto&t;&t;133
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown&t;&t;134
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair&t;&t;135
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;136
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;137
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes&t;&t;138
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername&t;141
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;144
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;145
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;147
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;148
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname&t;150
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t;156
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;166
DECL|macro|__NR_msgctl
mdefine_line|#define __NR_msgctl&t;&t;200
DECL|macro|__NR_msgget
mdefine_line|#define __NR_msgget&t;&t;201
DECL|macro|__NR_msgrcv
mdefine_line|#define __NR_msgrcv&t;&t;202
DECL|macro|__NR_msgsnd
mdefine_line|#define __NR_msgsnd&t;&t;203
DECL|macro|__NR_semctl
mdefine_line|#define __NR_semctl&t;&t;204
DECL|macro|__NR_semget
mdefine_line|#define __NR_semget&t;&t;205
DECL|macro|__NR_semop
mdefine_line|#define __NR_semop&t;&t;206
DECL|macro|__NR_shmctl
mdefine_line|#define __NR_shmctl&t;&t;210
DECL|macro|__NR_shmdt
mdefine_line|#define __NR_shmdt&t;&t;211
DECL|macro|__NR_shmget
mdefine_line|#define __NR_shmget&t;&t;212
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;217
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;233
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;234
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;254
multiline_comment|/*&n; * Linux-specific system calls begin at 300&n; */
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;300
DECL|macro|__NR_sethae
mdefine_line|#define __NR_sethae&t;&t;301
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;302
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;303
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;304
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;305
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;306
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;307
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;308
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;309
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;310
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;311
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;312
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t;313
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;314
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;315
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;316
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;317
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;318
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;319
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;320
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t;321
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;322
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;323
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;324
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;325
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;326
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;327
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;328
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;329
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;330
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;331
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;332
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;333
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;334
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;335
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;336
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;337
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;338
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;339
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;340
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;341
DECL|macro|__NR_nfsctl
mdefine_line|#define __NR_nfsctl&t;&t;&t;342
macro_line|#if defined(__LIBRARY__) &amp;&amp; defined(__GNUC__)
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type, name)&t;&t;&t;&t;&t;&t;&bslash;&n;type name(void)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t;&bslash;&n;&t;return syscall(__NR_##name));&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;&bslash;&n;type name(type1 arg1)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t;&bslash;&n;&t;return syscall(__NR_##name, arg1);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t;&bslash;&n;&t;return syscall(__NR_##name, arg1, arg2);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t;&bslash;&n;&t;return syscall(__NR_##name, arg1, arg2, arg3);&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4)&t;&t; &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t; &bslash;&n;&t;return syscall(__NR_##name, arg1, arg2, arg3, arg4);&t;&t; &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5)&t;&t;&t;&t;&t;&t;&t; &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5)&t; &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;extern long syscall (int, ...);&t;&t;&t;&t;&t; &bslash;&n;&t;return syscall(__NR_##name, arg1, arg2, arg3, arg4);&t;&t; &bslash;&n;}
macro_line|#endif /* __LIBRARY__ &amp;&amp; __GNUC__ */
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
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
r_extern
r_void
id|sys_idle
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|idle
r_static
r_inline
r_void
id|idle
c_func
(paren
r_void
)paren
(brace
id|sys_idle
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_setup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|setup
r_static
r_inline
r_int
id|setup
c_func
(paren
r_void
)paren
(brace
r_return
id|sys_setup
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_open
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
DECL|function|open
r_static
r_inline
r_int
id|open
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|mode
comma
r_int
id|flags
)paren
(brace
r_return
id|sys_open
c_func
(paren
id|name
comma
id|mode
comma
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_dup
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|dup
r_static
r_inline
r_int
id|dup
c_func
(paren
r_int
id|fd
)paren
(brace
r_return
id|sys_dup
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|close
r_static
r_inline
r_int
id|close
c_func
(paren
r_int
id|fd
)paren
(brace
r_return
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|_exit
r_static
r_inline
r_int
id|_exit
c_func
(paren
r_int
id|value
)paren
(brace
r_return
id|sys_exit
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
DECL|macro|exit
mdefine_line|#define exit(x) _exit(x)
r_extern
r_int
id|sys_write
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|write
r_static
r_inline
r_int
id|write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
(brace
r_return
id|sys_write
c_func
(paren
id|fd
comma
id|buf
comma
id|nr
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_read
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|read
r_static
r_inline
r_int
id|read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
(brace
r_return
id|sys_read
c_func
(paren
id|fd
comma
id|buf
comma
id|nr
)paren
suffix:semicolon
)brace
r_extern
r_int
id|do_execve
c_func
(paren
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
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|execve
r_static
r_inline
r_int
id|execve
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argvp
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pt_regs
id|regs
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
id|i
op_assign
id|do_execve
c_func
(paren
id|file
comma
id|argvp
comma
id|envp
comma
op_amp
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;bis %0,%0,$30&bslash;n&bslash;t&quot;
l_string|&quot;bis %1,%1,$26&bslash;n&bslash;t&quot;
l_string|&quot;ret $31,($26),1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|regs
)paren
comma
l_string|&quot;r&quot;
(paren
id|ret_from_sys_call
)paren
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_extern
r_int
id|sys_setsid
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|setsid
r_static
r_inline
r_int
id|setsid
c_func
(paren
r_void
)paren
(brace
r_return
id|sys_setsid
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|sync
r_static
r_inline
r_int
id|sync
c_func
(paren
r_void
)paren
(brace
r_return
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|sys_wait4
c_func
(paren
r_int
comma
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
DECL|function|waitpid
r_static
r_inline
id|pid_t
id|waitpid
c_func
(paren
r_int
id|pid
comma
r_int
op_star
id|wait_stat
comma
r_int
id|flags
)paren
(brace
r_return
id|sys_wait4
c_func
(paren
id|pid
comma
id|wait_stat
comma
id|flags
comma
l_int|NULL
)paren
suffix:semicolon
)brace
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
macro_line|#endif
macro_line|#endif /* _ALPHA_UNISTD_H */
eof
