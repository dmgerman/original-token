multiline_comment|/*&n; * List of Linux/MIPS syscalls.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; */
multiline_comment|/*&n; * This file is being included twice - once to build a list of all&n; * syscalls and once to build a table of how many arguments each syscall&n; * accepts.  Syscalls that receive a pointer to the saved registers are&n; * marked as having zero arguments.&n; *&n; * The binary compatibility calls are still missing in this list.&n; */
id|SYS
c_func
(paren
id|sys_syscall
comma
l_int|7
)paren
multiline_comment|/* 4000 */
id|SYS
c_func
(paren
id|sys_exit
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_fork
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_read
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_write
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_open
comma
l_int|3
)paren
multiline_comment|/* 4005 */
id|SYS
c_func
(paren
id|sys_close
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_waitpid
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_creat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_link
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_unlink
comma
l_int|1
)paren
multiline_comment|/* 4010 */
id|SYS
c_func
(paren
id|sys_execve
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_chdir
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_time
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_mknod
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_chmod
comma
l_int|2
)paren
multiline_comment|/* 4015 */
id|SYS
c_func
(paren
id|sys_chown
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_break
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_stat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_lseek
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_getpid
comma
l_int|0
)paren
multiline_comment|/* 4020 */
id|SYS
c_func
(paren
id|sys_mount
comma
l_int|5
)paren
id|SYS
c_func
(paren
id|sys_umount
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_setuid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_getuid
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_stime
comma
l_int|1
)paren
multiline_comment|/* 4025 */
id|SYS
c_func
(paren
id|sys_ptrace
comma
l_int|4
)paren
id|SYS
c_func
(paren
id|sys_alarm
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_fstat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_pause
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_utime
comma
l_int|2
)paren
multiline_comment|/* 4030 */
id|SYS
c_func
(paren
id|sys_stty
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_gtty
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_access
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_nice
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ftime
comma
l_int|0
)paren
multiline_comment|/* 4035 */
id|SYS
c_func
(paren
id|sys_sync
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_kill
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_rename
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_mkdir
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_rmdir
comma
l_int|1
)paren
multiline_comment|/* 4040 */
id|SYS
c_func
(paren
id|sys_dup
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_pipe
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_times
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_prof
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_brk
comma
l_int|1
)paren
multiline_comment|/* 4045 */
id|SYS
c_func
(paren
id|sys_setgid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_getgid
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_signal
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_geteuid
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_getegid
comma
l_int|0
)paren
multiline_comment|/* 4050 */
id|SYS
c_func
(paren
id|sys_acct
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_phys
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_lock
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_ioctl
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_fcntl
comma
l_int|3
)paren
multiline_comment|/* 4055 */
id|SYS
c_func
(paren
id|sys_mpx
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_setpgid
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_ulimit
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_olduname
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_umask
comma
l_int|1
)paren
multiline_comment|/* 4060 */
id|SYS
c_func
(paren
id|sys_chroot
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ustat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_dup2
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_getppid
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_getpgrp
comma
l_int|0
)paren
multiline_comment|/* 4065 */
id|SYS
c_func
(paren
id|sys_setsid
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_sigaction
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_sgetmask
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_ssetmask
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_setreuid
comma
l_int|2
)paren
multiline_comment|/* 4070 */
id|SYS
c_func
(paren
id|sys_setregid
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_sigsuspend
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_sigpending
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_sethostname
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_setrlimit
comma
l_int|2
)paren
multiline_comment|/* 4075 */
id|SYS
c_func
(paren
id|sys_getrlimit
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_getrusage
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_gettimeofday
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_settimeofday
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_getgroups
comma
l_int|2
)paren
multiline_comment|/* 4080 */
id|SYS
c_func
(paren
id|sys_setgroups
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_ni_syscall
comma
l_int|0
)paren
multiline_comment|/* old_select */
id|SYS
c_func
(paren
id|sys_symlink
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_lstat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_readlink
comma
l_int|3
)paren
multiline_comment|/* 4085 */
id|SYS
c_func
(paren
id|sys_uselib
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_swapon
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_reboot
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|old_readdir
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_mmap
comma
l_int|6
)paren
multiline_comment|/* 4090 */
id|SYS
c_func
(paren
id|sys_munmap
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_truncate
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_ftruncate
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_fchmod
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_fchown
comma
l_int|3
)paren
multiline_comment|/* 4095 */
id|SYS
c_func
(paren
id|sys_getpriority
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_setpriority
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_profil
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_statfs
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_fstatfs
comma
l_int|2
)paren
multiline_comment|/* 4100 */
id|SYS
c_func
(paren
id|sys_ioperm
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_socketcall
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_syslog
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_setitimer
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_getitimer
comma
l_int|2
)paren
multiline_comment|/* 4105 */
id|SYS
c_func
(paren
id|sys_newstat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_newlstat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_newfstat
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_uname
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_iopl
comma
l_int|0
)paren
multiline_comment|/* Well, actually 17 args ... */
multiline_comment|/* 4110 */
id|SYS
c_func
(paren
id|sys_vhangup
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_idle
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_vm86
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_wait4
comma
l_int|4
)paren
id|SYS
c_func
(paren
id|sys_swapoff
comma
l_int|1
)paren
multiline_comment|/* 4115 */
id|SYS
c_func
(paren
id|sys_sysinfo
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ipc
comma
l_int|6
)paren
id|SYS
c_func
(paren
id|sys_fsync
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_sigreturn
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_clone
comma
l_int|0
)paren
multiline_comment|/* 4120 */
id|SYS
c_func
(paren
id|sys_setdomainname
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_newuname
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ni_syscall
comma
l_int|0
)paren
multiline_comment|/* sys_modify_ldt */
id|SYS
c_func
(paren
id|sys_adjtimex
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_mprotect
comma
l_int|3
)paren
multiline_comment|/* 4125 */
id|SYS
c_func
(paren
id|sys_sigprocmask
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_create_module
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_init_module
comma
l_int|5
)paren
id|SYS
c_func
(paren
id|sys_delete_module
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_get_kernel_syms
comma
l_int|1
)paren
multiline_comment|/* 4130 */
id|SYS
c_func
(paren
id|sys_quotactl
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_getpgid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_fchdir
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_bdflush
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_sysfs
comma
l_int|3
)paren
multiline_comment|/* 4135 */
id|SYS
c_func
(paren
id|sys_personality
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ni_syscall
comma
l_int|0
)paren
multiline_comment|/* for afs_syscall */
id|SYS
c_func
(paren
id|sys_setfsuid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_setfsgid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_llseek
comma
l_int|5
)paren
multiline_comment|/* 4140 */
id|SYS
c_func
(paren
id|sys_getdents
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_select
comma
l_int|5
)paren
id|SYS
c_func
(paren
id|sys_flock
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_msync
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_readv
comma
l_int|3
)paren
multiline_comment|/* 4145 */
id|SYS
c_func
(paren
id|sys_writev
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_cacheflush
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_cachectl
comma
l_int|3
)paren
id|SYS
c_func
(paren
id|sys_sysmips
comma
l_int|4
)paren
id|SYS
c_func
(paren
id|sys_setup
comma
l_int|0
)paren
multiline_comment|/* 4150 */
id|SYS
c_func
(paren
id|sys_getsid
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_ni_syscall
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_ni_syscall
comma
l_int|0
)paren
id|SYS
c_func
(paren
id|sys_mlock
comma
l_int|2
)paren
id|SYS
c_func
(paren
id|sys_munlock
comma
l_int|2
)paren
multiline_comment|/* 4155 */
id|SYS
c_func
(paren
id|sys_mlockall
comma
l_int|1
)paren
id|SYS
c_func
(paren
id|sys_munlockall
comma
l_int|0
)paren
eof