macro_line|#ifndef __ASM_ARM_UNISTD_H
DECL|macro|__ASM_ARM_UNISTD_H
mdefine_line|#define __ASM_ARM_UNISTD_H
DECL|macro|__NR_SYSCALL_BASE
mdefine_line|#define __NR_SYSCALL_BASE&t;0x900000
multiline_comment|/*&n; * This file contains the system call numbers.&n; */
DECL|macro|__NR_setup
mdefine_line|#define __NR_setup&t;&t;&t;(__NR_SYSCALL_BASE+  0)&t;/* used only by init, to get system going */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;&t;&t;(__NR_SYSCALL_BASE+  1)
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;&t;&t;(__NR_SYSCALL_BASE+  2)
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;&t;&t;(__NR_SYSCALL_BASE+  3)
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;&t;&t;(__NR_SYSCALL_BASE+  4)
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;&t;&t;(__NR_SYSCALL_BASE+  5)
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;&t;&t;(__NR_SYSCALL_BASE+  6)
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;&t;&t;(__NR_SYSCALL_BASE+  7)
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;&t;&t;(__NR_SYSCALL_BASE+  8)
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;&t;&t;(__NR_SYSCALL_BASE+  9)
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;&t;&t;(__NR_SYSCALL_BASE+ 10)
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;&t;&t;(__NR_SYSCALL_BASE+ 11)
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;&t;&t;(__NR_SYSCALL_BASE+ 12)
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;&t;&t;(__NR_SYSCALL_BASE+ 13)
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;&t;&t;(__NR_SYSCALL_BASE+ 14)
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;&t;&t;(__NR_SYSCALL_BASE+ 15)
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;&t;&t;(__NR_SYSCALL_BASE+ 16)
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;&t;&t;(__NR_SYSCALL_BASE+ 17)
DECL|macro|__NR_oldstat
mdefine_line|#define __NR_oldstat&t;&t;&t;(__NR_SYSCALL_BASE+ 18)
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;&t;&t;(__NR_SYSCALL_BASE+ 19)
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;&t;&t;(__NR_SYSCALL_BASE+ 20)
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;&t;&t;(__NR_SYSCALL_BASE+ 21)
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;&t;&t;(__NR_SYSCALL_BASE+ 22)
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;&t;&t;(__NR_SYSCALL_BASE+ 23)
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;&t;&t;(__NR_SYSCALL_BASE+ 24)
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;&t;&t;(__NR_SYSCALL_BASE+ 25)
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;&t;&t;(__NR_SYSCALL_BASE+ 26)
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;&t;&t;(__NR_SYSCALL_BASE+ 27)
DECL|macro|__NR_oldfstat
mdefine_line|#define __NR_oldfstat&t;&t;&t;(__NR_SYSCALL_BASE+ 28)
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;&t;&t;(__NR_SYSCALL_BASE+ 29)
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;&t;&t;(__NR_SYSCALL_BASE+ 30)
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;&t;&t;(__NR_SYSCALL_BASE+ 31)
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;&t;&t;(__NR_SYSCALL_BASE+ 32)
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;&t;&t;(__NR_SYSCALL_BASE+ 33)
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;&t;&t;(__NR_SYSCALL_BASE+ 34)
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;&t;&t;(__NR_SYSCALL_BASE+ 35)
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;&t;&t;(__NR_SYSCALL_BASE+ 36)
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;&t;&t;(__NR_SYSCALL_BASE+ 37)
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;&t;&t;(__NR_SYSCALL_BASE+ 38)
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;&t;&t;(__NR_SYSCALL_BASE+ 39)
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;&t;&t;(__NR_SYSCALL_BASE+ 40)
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;&t;&t;(__NR_SYSCALL_BASE+ 41)
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;&t;&t;(__NR_SYSCALL_BASE+ 42)
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;&t;&t;(__NR_SYSCALL_BASE+ 43)
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;&t;&t;(__NR_SYSCALL_BASE+ 44)
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;&t;&t;(__NR_SYSCALL_BASE+ 45)
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;&t;&t;(__NR_SYSCALL_BASE+ 46)
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;&t;&t;(__NR_SYSCALL_BASE+ 47)
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;&t;&t;(__NR_SYSCALL_BASE+ 48)
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;&t;&t;(__NR_SYSCALL_BASE+ 49)
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;&t;&t;(__NR_SYSCALL_BASE+ 50)
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;&t;&t;(__NR_SYSCALL_BASE+ 51)
DECL|macro|__NR_phys
mdefine_line|#define __NR_phys&t;&t;&t;(__NR_SYSCALL_BASE+ 52)
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;&t;&t;(__NR_SYSCALL_BASE+ 53)
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;&t;&t;(__NR_SYSCALL_BASE+ 54)
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;&t;&t;(__NR_SYSCALL_BASE+ 55)
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;&t;&t;(__NR_SYSCALL_BASE+ 56)
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;&t;&t;(__NR_SYSCALL_BASE+ 57)
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;&t;&t;(__NR_SYSCALL_BASE+ 58)
DECL|macro|__NR_oldolduname
mdefine_line|#define __NR_oldolduname&t;&t;(__NR_SYSCALL_BASE+ 59)
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;&t;&t;(__NR_SYSCALL_BASE+ 60)
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;&t;&t;(__NR_SYSCALL_BASE+ 61)
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;&t;&t;(__NR_SYSCALL_BASE+ 62)
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;&t;&t;(__NR_SYSCALL_BASE+ 63)
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;&t;&t;(__NR_SYSCALL_BASE+ 64)
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;&t;&t;(__NR_SYSCALL_BASE+ 65)
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;&t;&t;(__NR_SYSCALL_BASE+ 66)
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;&t;&t;(__NR_SYSCALL_BASE+ 67)
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;&t;&t;(__NR_SYSCALL_BASE+ 68)
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;&t;&t;(__NR_SYSCALL_BASE+ 69)
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;&t;&t;(__NR_SYSCALL_BASE+ 70)
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;&t;&t;(__NR_SYSCALL_BASE+ 71)
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;&t;&t;(__NR_SYSCALL_BASE+ 72)
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending&t;&t;&t;(__NR_SYSCALL_BASE+ 73)
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname&t;&t;(__NR_SYSCALL_BASE+ 74)
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;&t;&t;(__NR_SYSCALL_BASE+ 75)
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;&t;&t;(__NR_SYSCALL_BASE+ 76)
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;&t;&t;(__NR_SYSCALL_BASE+ 77)
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday&t;&t;(__NR_SYSCALL_BASE+ 78)
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday&t;&t;(__NR_SYSCALL_BASE+ 79)
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;&t;&t;(__NR_SYSCALL_BASE+ 80)
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;&t;&t;(__NR_SYSCALL_BASE+ 81)
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;&t;&t;(__NR_SYSCALL_BASE+ 82)
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;&t;&t;(__NR_SYSCALL_BASE+ 83)
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat&t;&t;&t;(__NR_SYSCALL_BASE+ 84)
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;&t;&t;(__NR_SYSCALL_BASE+ 85)
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;&t;&t;(__NR_SYSCALL_BASE+ 86)
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon&t;&t;&t;(__NR_SYSCALL_BASE+ 87)
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot&t;&t;&t;(__NR_SYSCALL_BASE+ 88)
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir&t;&t;&t;(__NR_SYSCALL_BASE+ 89)
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap&t;&t;&t;(__NR_SYSCALL_BASE+ 90)
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap&t;&t;&t;(__NR_SYSCALL_BASE+ 91)
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate&t;&t;&t;(__NR_SYSCALL_BASE+ 92)
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate&t;&t;&t;(__NR_SYSCALL_BASE+ 93)
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod&t;&t;&t;(__NR_SYSCALL_BASE+ 94)
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown&t;&t;&t;(__NR_SYSCALL_BASE+ 95)
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority&t;&t;(__NR_SYSCALL_BASE+ 96)
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority&t;&t;(__NR_SYSCALL_BASE+ 97)
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil&t;&t;&t;(__NR_SYSCALL_BASE+ 98)
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs&t;&t;&t;(__NR_SYSCALL_BASE+ 99)
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs&t;&t;&t;(__NR_SYSCALL_BASE+100)
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm&t;&t;&t;(__NR_SYSCALL_BASE+101)
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall&t;&t;&t;(__NR_SYSCALL_BASE+102)
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog&t;&t;&t;(__NR_SYSCALL_BASE+103)
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer&t;&t;&t;(__NR_SYSCALL_BASE+104)
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer&t;&t;&t;(__NR_SYSCALL_BASE+105)
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;&t;&t;(__NR_SYSCALL_BASE+106)
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;&t;&t;(__NR_SYSCALL_BASE+107)
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;&t;&t;(__NR_SYSCALL_BASE+108)
DECL|macro|__NR_olduname
mdefine_line|#define __NR_olduname&t;&t;&t;(__NR_SYSCALL_BASE+109)
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl&t;&t;&t;(__NR_SYSCALL_BASE+110)
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup&t;&t;&t;(__NR_SYSCALL_BASE+111)
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle&t;&t;&t;(__NR_SYSCALL_BASE+112)
DECL|macro|__NR_syscall
mdefine_line|#define __NR_syscall&t;&t;&t;(__NR_SYSCALL_BASE+113) /* syscall to call a syscall! */
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4&t;&t;&t;(__NR_SYSCALL_BASE+114)
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff&t;&t;&t;(__NR_SYSCALL_BASE+115)
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo&t;&t;&t;(__NR_SYSCALL_BASE+116)
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc&t;&t;&t;(__NR_SYSCALL_BASE+117)
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync&t;&t;&t;(__NR_SYSCALL_BASE+118)
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn&t;&t;&t;(__NR_SYSCALL_BASE+119)
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone&t;&t;&t;(__NR_SYSCALL_BASE+120)
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname&t;&t;(__NR_SYSCALL_BASE+121)
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;&t;&t;(__NR_SYSCALL_BASE+122)
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt&t;&t;&t;(__NR_SYSCALL_BASE+123)
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex&t;&t;&t;(__NR_SYSCALL_BASE+124)
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect&t;&t;&t;(__NR_SYSCALL_BASE+125)
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask&t;&t;(__NR_SYSCALL_BASE+126)
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module&t;&t;(__NR_SYSCALL_BASE+127)
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module&t;&t;(__NR_SYSCALL_BASE+128)
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module&t;&t;(__NR_SYSCALL_BASE+129)
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms&t;&t;(__NR_SYSCALL_BASE+130)
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl&t;&t;&t;(__NR_SYSCALL_BASE+131)
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid&t;&t;&t;(__NR_SYSCALL_BASE+132)
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir&t;&t;&t;(__NR_SYSCALL_BASE+133)
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush&t;&t;&t;(__NR_SYSCALL_BASE+134)
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs&t;&t;&t;(__NR_SYSCALL_BASE+135)
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality&t;&t;(__NR_SYSCALL_BASE+136)
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall&t;&t;(__NR_SYSCALL_BASE+137) /* Syscall for Andrew File System */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid&t;&t;&t;(__NR_SYSCALL_BASE+138)
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid&t;&t;&t;(__NR_SYSCALL_BASE+139)
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek&t;&t;&t;(__NR_SYSCALL_BASE+140)
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents&t;&t;&t;(__NR_SYSCALL_BASE+141)
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect&t;&t;&t;(__NR_SYSCALL_BASE+142)
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock&t;&t;&t;(__NR_SYSCALL_BASE+143)
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync&t;&t;&t;(__NR_SYSCALL_BASE+144)
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv&t;&t;&t;(__NR_SYSCALL_BASE+145)
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev&t;&t;&t;(__NR_SYSCALL_BASE+146)
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid&t;&t;&t;(__NR_SYSCALL_BASE+147)
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync&t;&t;&t;(__NR_SYSCALL_BASE+148)
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl&t;&t;&t;(__NR_SYSCALL_BASE+149)
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock&t;&t;&t;(__NR_SYSCALL_BASE+150)
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock&t;&t;&t;(__NR_SYSCALL_BASE+151)
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall&t;&t;&t;(__NR_SYSCALL_BASE+152)
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall&t;&t;&t;(__NR_SYSCALL_BASE+153)
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam&t;&t;(__NR_SYSCALL_BASE+154)
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam&t;&t;(__NR_SYSCALL_BASE+155)
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler&t;&t;(__NR_SYSCALL_BASE+156)
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler&t;&t;(__NR_SYSCALL_BASE+157)
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield&t;&t;(__NR_SYSCALL_BASE+158)
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max&t;(__NR_SYSCALL_BASE+159)
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min&t;(__NR_SYSCALL_BASE+160)
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval&t;(__NR_SYSCALL_BASE+161)
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep&t;&t;&t;(__NR_SYSCALL_BASE+162)
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap&t;&t;&t;(__NR_SYSCALL_BASE+163)
DECL|macro|__NR_setresuid
mdefine_line|#define __NR_setresuid&t;&t;&t;(__NR_SYSCALL_BASE+164)
DECL|macro|__NR_getresuid
mdefine_line|#define __NR_getresuid&t;&t;&t;(__NR_SYSCALL_BASE+165)
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86&t;&t;&t;(__NR_SYSCALL_BASE+166)
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;&t;(__NR_SYSCALL_BASE+167)
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll&t;&t;&t;(__NR_SYSCALL_BASE+168)
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl&t;&t;&t;(__NR_SYSCALL_BASE+169)
DECL|macro|__NR_setresgid
mdefine_line|#define __NR_setresgid&t;&t;&t;(__NR_SYSCALL_BASE+170)
DECL|macro|__NR_getresgid
mdefine_line|#define __NR_getresgid&t;&t;&t;(__NR_SYSCALL_BASE+171)
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;&t;(__NR_SYSCALL_BASE+172)
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn&t;&t;(__NR_SYSCALL_BASE+173)
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction&t;&t;(__NR_SYSCALL_BASE+174)
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask&t;&t;(__NR_SYSCALL_BASE+175)
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending&t;&t;(__NR_SYSCALL_BASE+176)
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait&t;&t;(__NR_SYSCALL_BASE+177)
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo&t;&t;(__NR_SYSCALL_BASE+178)
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend&t;&t;(__NR_SYSCALL_BASE+179)
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread&t;&t;&t;(__NR_SYSCALL_BASE+180)
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite&t;&t;&t;(__NR_SYSCALL_BASE+181)
DECL|macro|__NR_xstat
mdefine_line|#define __NR_xstat&t;&t;&t;(__NR_SYSCALL_BASE+182)
DECL|macro|__NR_xmknod
mdefine_line|#define __NR_xmknod&t;&t;&t;(__NR_SYSCALL_BASE+183)
DECL|macro|__sys2
mdefine_line|#define __sys2(x) #x
DECL|macro|__sys1
mdefine_line|#define __sys1(x) __sys2(x)
macro_line|#ifndef __syscall
DECL|macro|__syscall
mdefine_line|#define __syscall(name) &quot;swi&bslash;t&quot; __sys1(__NR_##name) &quot;&bslash;n&bslash;t&quot;
macro_line|#endif
DECL|macro|__syscall_return
mdefine_line|#define __syscall_return(type, res)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((unsigned long)(res) &gt;= (unsigned long)(-125)) {&t;&t;&bslash;&n;&t;&t;errno = -(res);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;res = -1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return (type) (res);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name)&t;&t;&t;&t;&t;&t;&bslash;&n;type name(void) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov %0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  :&quot;=r&quot; (__res) : : &quot;r0&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1)&t;&t;&t;&t;&t;&bslash;&n;type name(type1 arg1) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov %0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2)&t;&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2) {&t;&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2))&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;r1&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3)&t;&t;&bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) {&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3))&t;&bslash;&n;        : &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4)&t;&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {&t;&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr3,%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3)),&quot;r&quot; ((long)(arg4))&t;&bslash;&n;  &t;: &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;r3&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4,type5,arg5)&t;&bslash;&n;type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) {&t;&t;&t;&bslash;&n;  long __res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr2,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr3,%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;tr4,%5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &quot;mov&bslash;t%0,r0&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;: &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)),&quot;r&quot; ((long)(arg3)),&quot;r&quot; ((long)(arg4)),&t;&bslash;&n;&t;  &quot;r&quot; ((long)(arg5))&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r0&quot;,&quot;r1&quot;,&quot;r2&quot;,&quot;r3&quot;,&quot;r4&quot;,&quot;lr&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;  __syscall_return(type,__res);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|idle
)paren
suffix:semicolon
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|pause
)paren
suffix:semicolon
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|setup
comma
r_int
comma
id|magic
)paren
suffix:semicolon
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|sync
)paren
suffix:semicolon
r_static
r_inline
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
suffix:semicolon
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|write
comma
r_int
comma
id|fd
comma
r_const
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
suffix:semicolon
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|read
comma
r_int
comma
id|fd
comma
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|dup
comma
r_int
comma
id|fd
)paren
suffix:semicolon
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
r_const
r_char
op_star
comma
id|file
comma
r_char
op_star
op_star
comma
id|argv
comma
r_char
op_star
op_star
comma
id|envp
)paren
suffix:semicolon
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|open
comma
r_const
r_char
op_star
comma
id|file
comma
r_int
comma
id|flag
comma
r_int
comma
id|mode
)paren
suffix:semicolon
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|close
comma
r_int
comma
id|fd
)paren
suffix:semicolon
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|_exit
comma
r_int
comma
id|exitcode
)paren
suffix:semicolon
r_static
r_inline
id|_syscall3
c_func
(paren
id|pid_t
comma
id|waitpid
comma
id|pid_t
comma
id|pid
comma
r_int
op_star
comma
id|wait_stat
comma
r_int
comma
id|options
)paren
suffix:semicolon
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|delete_module
comma
r_const
r_char
op_star
comma
id|name
)paren
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
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE! Only a kernel-only process(ie the swapper or direct descendants&n; * who haven&squot;t done an &quot;execve()&quot;) should use this: it will work within&n; * a system call from a &quot;real&quot; process, but the process memory space will&n; * not be free&squot;d until both the parent and the child have exited.&n; */
DECL|function|kernel_thread
r_static
r_inline
id|pid_t
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
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mov
id|r0
comma
op_mod
l_int|1
id|mov
id|r1
comma
op_mod
l_int|2
l_string|&quot;__syscall(clone)&quot;
id|teq
id|r0
comma
macro_line|#0
id|bne
l_float|1f
id|mov
id|r0
comma
op_mod
l_int|4
id|mov
id|lr
comma
id|pc
id|mov
id|pc
comma
op_mod
l_int|3
l_string|&quot;__syscall(exit)&quot;
l_int|1
suffix:colon
id|mov
op_mod
l_int|0
comma
id|r0
"&quot;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|flags
op_or
id|CLONE_VM
)paren
comma
l_string|&quot;Ir&quot;
(paren
l_int|NULL
)paren
comma
l_string|&quot;r&quot;
(paren
id|fn
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|arg
)paren
suffix:colon
l_string|&quot;r0&quot;
comma
l_string|&quot;r1&quot;
comma
l_string|&quot;r2&quot;
comma
l_string|&quot;r3&quot;
comma
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __ASM_ARM_UNISTD_H */
eof
