multiline_comment|/* $Id: unistd.h,v 1.14 1997/12/11 15:16:08 jj Exp $ */
macro_line|#ifndef _SPARC64_UNISTD_H
DECL|macro|_SPARC64_UNISTD_H
mdefine_line|#define _SPARC64_UNISTD_H
multiline_comment|/*&n; * System calls under the Sparc.&n; *&n; * Don&squot;t be scared by the ugly clobbers, it is the only way I can&n; * think of right now to force the arguments into fixed registers&n; * before the trap into the system call with gcc &squot;asm&squot; statements.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * SunOS compatibility based upon preliminary work which is:&n; *&n; * Copyright (C) 1995 Adrian M. Rodriguez (adrian@remus.rutgers.edu)&n; */
DECL|macro|__NR_setup
mdefine_line|#define __NR_setup                0 /* Used only by init, to get system going.     */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit                 1 /* Common                                      */
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork                 2 /* Common                                      */
DECL|macro|__NR_read
mdefine_line|#define __NR_read                 3 /* Common                                      */
DECL|macro|__NR_write
mdefine_line|#define __NR_write                4 /* Common                                      */
DECL|macro|__NR_open
mdefine_line|#define __NR_open                 5 /* Common                                      */
DECL|macro|__NR_close
mdefine_line|#define __NR_close                6 /* Common                                      */
DECL|macro|__NR_wait4
mdefine_line|#define __NR_wait4                7 /* Common                                      */
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat                8 /* Common                                      */
DECL|macro|__NR_link
mdefine_line|#define __NR_link                 9 /* Common                                      */
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink              10 /* Common                                      */
DECL|macro|__NR_execv
mdefine_line|#define __NR_execv               11 /* SunOS Specific                              */
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir               12 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       13    ENOSYS under SunOS                          */
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod               14 /* Common                                      */
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod               15 /* Common                                      */
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown               16 /* Common                                      */
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk                 17 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       18    ENOSYS under SunOS                          */
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek               19 /* Common                                      */
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid              20 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       21    ENOSYS under SunOS                          */
multiline_comment|/* #define __NR_ni_syscall       22    ENOSYS under SunOS                          */
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid              23 /* Implemented via setreuid in SunOS           */
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid              24 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       25    ENOSYS under SunOS                          */
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace              26 /* Common                                      */
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm               27 /* Implemented via setitimer in SunOS          */
multiline_comment|/* #define __NR_ni_syscall       28    ENOSYS under SunOS                          */
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause               29 /* Is sigblock(0)-&gt;sigpause() in SunOS         */
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime               30 /* Implemented via utimes() under SunOS        */
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty                31 /* Implemented via ioctl() under SunOS         */
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty                32 /* Implemented via ioctl() under SunOS         */
DECL|macro|__NR_access
mdefine_line|#define __NR_access              33 /* Common                                      */
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice                34 /* Implemented via get/setpriority() in SunOS  */
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime               35 /* Implemented via gettimeofday() in SunOS     */
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync                36 /* Common                                      */
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill                37 /* Common                                      */
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat                38 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       39    ENOSYS under SunOS                          */
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat               40 /* Common                                      */
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup                 41 /* Common                                      */
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe                42 /* Common                                      */
DECL|macro|__NR_times
mdefine_line|#define __NR_times               43 /* Implemented via getrusage() in SunOS        */
DECL|macro|__NR_profil
mdefine_line|#define __NR_profil              44 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       45    ENOSYS under SunOS                          */
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid              46 /* Implemented via setregid() in SunOS         */
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid              47 /* Common                                      */
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal              48 /* Implemented via sigvec() in SunOS           */
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid             49 /* SunOS calls getuid()                        */
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid             50 /* SunOS calls getgid()                        */
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct                51 /* Common                                      */
DECL|macro|__NR_memory_ordering
mdefine_line|#define __NR_memory_ordering&t; 52 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_mctl
mdefine_line|#define __NR_mctl                53 /* SunOS specific                              */
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl               54 /* Common                                      */
DECL|macro|__NR_reboot
mdefine_line|#define __NR_reboot              55 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       56    ENOSYS under SunOS                          */
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink             57 /* Common                                      */
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink            58 /* Common                                      */
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve              59 /* Common                                      */
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask               60 /* Common                                      */
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot              61 /* Common                                      */
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat               62 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       63    ENOSYS under SunOS                          */
DECL|macro|__NR_getpagesize
mdefine_line|#define __NR_getpagesize         64 /* Common                                      */
DECL|macro|__NR_msync
mdefine_line|#define __NR_msync               65 /* Common in newer 1.3.x revs...               */
multiline_comment|/* #define __NR_ni_syscall       66    ENOSYS under SunOS                          */
DECL|macro|__NR_pread
mdefine_line|#define __NR_pread               67 /* Linux Specific                              */
DECL|macro|__NR_pwrite
mdefine_line|#define __NR_pwrite              68 /* Linux Specific                              */
DECL|macro|__NR_sbrk
mdefine_line|#define __NR_sbrk                69 /* SunOS Specific                              */
DECL|macro|__NR_sstk
mdefine_line|#define __NR_sstk                70 /* SunOS Specific                              */
DECL|macro|__NR_mmap
mdefine_line|#define __NR_mmap                71 /* Common                                      */
DECL|macro|__NR_vadvise
mdefine_line|#define __NR_vadvise             72 /* SunOS Specific                              */
DECL|macro|__NR_munmap
mdefine_line|#define __NR_munmap              73 /* Common                                      */
DECL|macro|__NR_mprotect
mdefine_line|#define __NR_mprotect            74 /* Common                                      */
DECL|macro|__NR_madvise
mdefine_line|#define __NR_madvise             75 /* SunOS Specific                              */
DECL|macro|__NR_vhangup
mdefine_line|#define __NR_vhangup             76 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       77    ENOSYS under SunOS                          */
DECL|macro|__NR_mincore
mdefine_line|#define __NR_mincore             78 /* SunOS Specific                              */
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups           79 /* Common                                      */
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups           80 /* Common                                      */
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp             81 /* Common                                      */
DECL|macro|__NR_setpgrp
mdefine_line|#define __NR_setpgrp             82 /* setpgid, same difference...                 */
DECL|macro|__NR_setitimer
mdefine_line|#define __NR_setitimer           83 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall       84    ENOSYS under SunOS                          */
DECL|macro|__NR_swapon
mdefine_line|#define __NR_swapon              85 /* Common                                      */
DECL|macro|__NR_getitimer
mdefine_line|#define __NR_getitimer           86 /* Common                                      */
DECL|macro|__NR_gethostname
mdefine_line|#define __NR_gethostname         87 /* SunOS Specific                              */
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname         88 /* Common                                      */
DECL|macro|__NR_getdtablesize
mdefine_line|#define __NR_getdtablesize       89 /* SunOS Specific                              */
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2                90 /* Common                                      */
DECL|macro|__NR_getdopt
mdefine_line|#define __NR_getdopt             91 /* SunOS Specific                              */
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl               92 /* Common                                      */
DECL|macro|__NR_select
mdefine_line|#define __NR_select              93 /* Common                                      */
DECL|macro|__NR_setdopt
mdefine_line|#define __NR_setdopt             94 /* SunOS Specific                              */
DECL|macro|__NR_fsync
mdefine_line|#define __NR_fsync               95 /* Common                                      */
DECL|macro|__NR_setpriority
mdefine_line|#define __NR_setpriority         96 /* Common                                      */
DECL|macro|__NR_socket
mdefine_line|#define __NR_socket              97 /* Common                                      */
DECL|macro|__NR_connect
mdefine_line|#define __NR_connect             98 /* Common                                      */
DECL|macro|__NR_accept
mdefine_line|#define __NR_accept              99 /* Common                                      */
DECL|macro|__NR_getpriority
mdefine_line|#define __NR_getpriority        100 /* Common                                      */
DECL|macro|__NR_rt_sigreturn
mdefine_line|#define __NR_rt_sigreturn       101 /* Linux Specific                              */
DECL|macro|__NR_rt_sigaction
mdefine_line|#define __NR_rt_sigaction       102 /* Linux Specific                              */
DECL|macro|__NR_rt_sigprocmask
mdefine_line|#define __NR_rt_sigprocmask     103 /* Linux Specific                              */
DECL|macro|__NR_rt_sigpending
mdefine_line|#define __NR_rt_sigpending      104 /* Linux Specific                              */
DECL|macro|__NR_rt_sigtimedwait
mdefine_line|#define __NR_rt_sigtimedwait    105 /* Linux Specific                              */
DECL|macro|__NR_rt_sigqueueinfo
mdefine_line|#define __NR_rt_sigqueueinfo    106 /* Linux Specific                              */
DECL|macro|__NR_rt_sigsuspend
mdefine_line|#define __NR_rt_sigsuspend      107 /* Linux Specific                              */
DECL|macro|__NR_sigvec
mdefine_line|#define __NR_sigvec             108 /* SunOS Specific                              */
DECL|macro|__NR_sigblock
mdefine_line|#define __NR_sigblock           109 /* SunOS Specific                              */
DECL|macro|__NR_sigsetmask
mdefine_line|#define __NR_sigsetmask         110 /* SunOS Specific                              */
DECL|macro|__NR_sigpause
mdefine_line|#define __NR_sigpause           111 /* SunOS Specific                              */
DECL|macro|__NR_sigstack
mdefine_line|#define __NR_sigstack           112 /* SunOS Specific                              */
DECL|macro|__NR_recvmsg
mdefine_line|#define __NR_recvmsg            113 /* Common                                      */
DECL|macro|__NR_sendmsg
mdefine_line|#define __NR_sendmsg            114 /* Common                                      */
DECL|macro|__NR_vtrace
mdefine_line|#define __NR_vtrace             115 /* SunOS Specific                              */
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday       116 /* Common                                      */
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage          117 /* Common                                      */
DECL|macro|__NR_getsockopt
mdefine_line|#define __NR_getsockopt         118 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall      119    ENOSYS under SunOS                          */
DECL|macro|__NR_readv
mdefine_line|#define __NR_readv              120 /* Common                                      */
DECL|macro|__NR_writev
mdefine_line|#define __NR_writev             121 /* Common                                      */
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday       122 /* Common                                      */
DECL|macro|__NR_fchown
mdefine_line|#define __NR_fchown             123 /* Common                                      */
DECL|macro|__NR_fchmod
mdefine_line|#define __NR_fchmod             124 /* Common                                      */
DECL|macro|__NR_recvfrom
mdefine_line|#define __NR_recvfrom           125 /* Common                                      */
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid           126 /* Common                                      */
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid           127 /* Common                                      */
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename             128 /* Common                                      */
DECL|macro|__NR_truncate
mdefine_line|#define __NR_truncate           129 /* Common                                      */
DECL|macro|__NR_ftruncate
mdefine_line|#define __NR_ftruncate          130 /* Common                                      */
DECL|macro|__NR_flock
mdefine_line|#define __NR_flock              131 /* Common                                      */
multiline_comment|/* #define __NR_ni_syscall      132    ENOSYS under SunOS                          */
DECL|macro|__NR_sendto
mdefine_line|#define __NR_sendto             133 /* Common                                      */
DECL|macro|__NR_shutdown
mdefine_line|#define __NR_shutdown           134 /* Common                                      */
DECL|macro|__NR_socketpair
mdefine_line|#define __NR_socketpair         135 /* Common                                      */
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir              136 /* Common                                      */
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir              137 /* Common                                      */
DECL|macro|__NR_utimes
mdefine_line|#define __NR_utimes             138 /* SunOS Specific                              */
multiline_comment|/* #define __NR_ni_syscall      139    ENOSYS under SunOS                          */
DECL|macro|__NR_adjtime
mdefine_line|#define __NR_adjtime            140 /* SunOS Specific                              */
DECL|macro|__NR_getpeername
mdefine_line|#define __NR_getpeername        141 /* Common                                      */
DECL|macro|__NR_gethostid
mdefine_line|#define __NR_gethostid          142 /* SunOS Specific                              */
multiline_comment|/* #define __NR_ni_syscall      143    ENOSYS under SunOS                          */
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit          144 /* Common                                      */
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit          145 /* Common                                      */
DECL|macro|__NR_killpg
mdefine_line|#define __NR_killpg             146 /* SunOS Specific                              */
DECL|macro|__NR_prctl
mdefine_line|#define __NR_prctl&t;&t;147 /* ENOSYS under SunOS                          */
DECL|macro|__NR_pciconfig_read
mdefine_line|#define __NR_pciconfig_read&t;148 /* ENOSYS under SunOS                          */
DECL|macro|__NR_pciconfig_write
mdefine_line|#define __NR_pciconfig_write&t;149 /* ENOSYS under SunOS                          */
DECL|macro|__NR_getsockname
mdefine_line|#define __NR_getsockname        150 /* Common                                      */
DECL|macro|__NR_getmsg
mdefine_line|#define __NR_getmsg             151 /* SunOS Specific                              */
DECL|macro|__NR_putmsg
mdefine_line|#define __NR_putmsg             152 /* SunOS Specific                              */
DECL|macro|__NR_poll
mdefine_line|#define __NR_poll               153 /* SunOS Specific                              */
multiline_comment|/* #define __NR_ni_syscall      154    ENOSYS under SunOS                          */
DECL|macro|__NR_nfssvc
mdefine_line|#define __NR_nfssvc             155 /* SunOS Specific                              */
DECL|macro|__NR_getdirentries
mdefine_line|#define __NR_getdirentries      156 /* SunOS Specific                              */
DECL|macro|__NR_statfs
mdefine_line|#define __NR_statfs             157 /* Common                                      */
DECL|macro|__NR_fstatfs
mdefine_line|#define __NR_fstatfs            158 /* Common                                      */
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount             159 /* Common                                      */
DECL|macro|__NR_async_daemon
mdefine_line|#define __NR_async_daemon       160 /* SunOS Specific                              */
DECL|macro|__NR_getfh
mdefine_line|#define __NR_getfh              161 /* SunOS Specific                              */
DECL|macro|__NR_getdomainname
mdefine_line|#define __NR_getdomainname      162 /* SunOS Specific                              */
DECL|macro|__NR_setdomainname
mdefine_line|#define __NR_setdomainname      163 /* Common                                      */
DECL|macro|__NR_utrap_install
mdefine_line|#define __NR_utrap_install&t;164 /* SYSV ABI/v9 required&t;&t;&t;   */
DECL|macro|__NR_quotactl
mdefine_line|#define __NR_quotactl           165 /* Common                                      */
DECL|macro|__NR_exportfs
mdefine_line|#define __NR_exportfs           166 /* SunOS Specific                              */
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount              167 /* Common                                      */
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat              168 /* Common                                      */
DECL|macro|__NR_semsys
mdefine_line|#define __NR_semsys             169 /* SunOS Specific                              */
DECL|macro|__NR_msgsys
mdefine_line|#define __NR_msgsys             170 /* SunOS Specific                              */
DECL|macro|__NR_shmsys
mdefine_line|#define __NR_shmsys             171 /* SunOS Specific                              */
DECL|macro|__NR_auditsys
mdefine_line|#define __NR_auditsys           172 /* SunOS Specific                              */
DECL|macro|__NR_rfssys
mdefine_line|#define __NR_rfssys             173 /* SunOS Specific                              */
DECL|macro|__NR_getdents
mdefine_line|#define __NR_getdents           174 /* Common                                      */
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid             175 /* Common                                      */
DECL|macro|__NR_fchdir
mdefine_line|#define __NR_fchdir             176 /* Common                                      */
DECL|macro|__NR_fchroot
mdefine_line|#define __NR_fchroot            177 /* SunOS Specific                              */
DECL|macro|__NR_vpixsys
mdefine_line|#define __NR_vpixsys            178 /* SunOS Specific                              */
DECL|macro|__NR_aioread
mdefine_line|#define __NR_aioread            179 /* SunOS Specific                              */
DECL|macro|__NR_aiowrite
mdefine_line|#define __NR_aiowrite           180 /* SunOS Specific                              */
DECL|macro|__NR_aiowait
mdefine_line|#define __NR_aiowait            181 /* SunOS Specific                              */
DECL|macro|__NR_aiocancel
mdefine_line|#define __NR_aiocancel          182 /* SunOS Specific                              */
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending         183 /* Common                                      */
DECL|macro|__NR_query_module
mdefine_line|#define __NR_query_module&t;184 /* Linux Specific&t;&t;&t;&t;   */
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid            185 /* Common                                      */
DECL|macro|__NR_pathconf
mdefine_line|#define __NR_pathconf           186 /* SunOS Specific                              */
DECL|macro|__NR_fpathconf
mdefine_line|#define __NR_fpathconf          187 /* SunOS Specific                              */
DECL|macro|__NR_sysconf
mdefine_line|#define __NR_sysconf            188 /* SunOS Specific                              */
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname              189 /* Linux Specific                              */
DECL|macro|__NR_init_module
mdefine_line|#define __NR_init_module        190 /* Linux Specific                              */
DECL|macro|__NR_personality
mdefine_line|#define __NR_personality        191 /* Linux Specific                              */
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof               192 /* Linux Specific                              */
DECL|macro|__NR_break
mdefine_line|#define __NR_break              193 /* Linux Specific                              */
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock               194 /* Linux Specific                              */
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx                195 /* Linux Specific                              */
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit             196 /* Linux Specific                              */
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid            197 /* Linux Specific                              */
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction          198 /* Linux Specific                              */
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask           199 /* Linux Specific                              */
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask           200 /* Linux Specific                              */
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend         201 /* Linux Specific                              */
DECL|macro|__NR_oldlstat
mdefine_line|#define __NR_oldlstat           202 /* Linux Specific                              */
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib             203 /* Linux Specific                              */
DECL|macro|__NR_readdir
mdefine_line|#define __NR_readdir            204 /* Linux Specific                              */
DECL|macro|__NR_ioperm
mdefine_line|#define __NR_ioperm             205 /* Linux Specific - i386 specific, unused      */
DECL|macro|__NR_socketcall
mdefine_line|#define __NR_socketcall         206 /* Linux Specific                              */
DECL|macro|__NR_syslog
mdefine_line|#define __NR_syslog             207 /* Linux Specific                              */
DECL|macro|__NR_olduname
mdefine_line|#define __NR_olduname           208 /* Linux Specific                              */
DECL|macro|__NR_iopl
mdefine_line|#define __NR_iopl               209 /* Linux Specific - i386 specific, unused      */
DECL|macro|__NR_idle
mdefine_line|#define __NR_idle               210 /* Linux Specific                              */
DECL|macro|__NR_vm86
mdefine_line|#define __NR_vm86               211 /* Linux Specific - i386 specific, unused      */
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid            212 /* Linux Specific                              */
DECL|macro|__NR_swapoff
mdefine_line|#define __NR_swapoff            213 /* Linux Specific                              */
DECL|macro|__NR_sysinfo
mdefine_line|#define __NR_sysinfo            214 /* Linux Specific                              */
DECL|macro|__NR_ipc
mdefine_line|#define __NR_ipc                215 /* Linux Specific                              */
DECL|macro|__NR_sigreturn
mdefine_line|#define __NR_sigreturn          216 /* Linux Specific                              */
DECL|macro|__NR_clone
mdefine_line|#define __NR_clone              217 /* Linux Specific                              */
DECL|macro|__NR_modify_ldt
mdefine_line|#define __NR_modify_ldt         218 /* Linux Specific - i386 specific, unused      */
DECL|macro|__NR_adjtimex
mdefine_line|#define __NR_adjtimex           219 /* Linux Specific                              */
DECL|macro|__NR_sigprocmask
mdefine_line|#define __NR_sigprocmask        220 /* Linux Specific                              */
DECL|macro|__NR_create_module
mdefine_line|#define __NR_create_module      221 /* Linux Specific                              */
DECL|macro|__NR_delete_module
mdefine_line|#define __NR_delete_module      222 /* Linux Specific                              */
DECL|macro|__NR_get_kernel_syms
mdefine_line|#define __NR_get_kernel_syms    223 /* Linux Specific                              */
DECL|macro|__NR_getpgid
mdefine_line|#define __NR_getpgid            224 /* Linux Specific                              */
DECL|macro|__NR_bdflush
mdefine_line|#define __NR_bdflush            225 /* Linux Specific                              */
DECL|macro|__NR_sysfs
mdefine_line|#define __NR_sysfs              226 /* Linux Specific                              */
DECL|macro|__NR_afs_syscall
mdefine_line|#define __NR_afs_syscall        227 /* Linux Specific                              */
DECL|macro|__NR_setfsuid
mdefine_line|#define __NR_setfsuid           228 /* Linux Specific                              */
DECL|macro|__NR_setfsgid
mdefine_line|#define __NR_setfsgid           229 /* Linux Specific                              */
DECL|macro|__NR__newselect
mdefine_line|#define __NR__newselect         230 /* Linux Specific                              */
DECL|macro|__NR_time
mdefine_line|#define __NR_time               231 /* Linux Specific                              */
DECL|macro|__NR_oldstat
mdefine_line|#define __NR_oldstat            232 /* Linux Specific                              */
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime              233 /* Linux Specific                              */
DECL|macro|__NR_oldfstat
mdefine_line|#define __NR_oldfstat           234 /* Linux Specific                              */
DECL|macro|__NR_phys
mdefine_line|#define __NR_phys               235 /* Linux Specific                              */
DECL|macro|__NR__llseek
mdefine_line|#define __NR__llseek            236 /* Linux Specific                              */
DECL|macro|__NR_mlock
mdefine_line|#define __NR_mlock              237
DECL|macro|__NR_munlock
mdefine_line|#define __NR_munlock            238
DECL|macro|__NR_mlockall
mdefine_line|#define __NR_mlockall           239
DECL|macro|__NR_munlockall
mdefine_line|#define __NR_munlockall         240
DECL|macro|__NR_sched_setparam
mdefine_line|#define __NR_sched_setparam     241
DECL|macro|__NR_sched_getparam
mdefine_line|#define __NR_sched_getparam     242
DECL|macro|__NR_sched_setscheduler
mdefine_line|#define __NR_sched_setscheduler 243
DECL|macro|__NR_sched_getscheduler
mdefine_line|#define __NR_sched_getscheduler 244
DECL|macro|__NR_sched_yield
mdefine_line|#define __NR_sched_yield        245
DECL|macro|__NR_sched_get_priority_max
mdefine_line|#define __NR_sched_get_priority_max 246
DECL|macro|__NR_sched_get_priority_min
mdefine_line|#define __NR_sched_get_priority_min 247
DECL|macro|__NR_sched_rr_get_interval
mdefine_line|#define __NR_sched_rr_get_interval  248
DECL|macro|__NR_nanosleep
mdefine_line|#define __NR_nanosleep          249
DECL|macro|__NR_mremap
mdefine_line|#define __NR_mremap             250
DECL|macro|__NR__sysctl
mdefine_line|#define __NR__sysctl            251
DECL|macro|__NR_getsid
mdefine_line|#define __NR_getsid             252
DECL|macro|__NR_fdatasync
mdefine_line|#define __NR_fdatasync          253
DECL|macro|__NR_nfsservctl
mdefine_line|#define __NR_nfsservctl         254
DECL|macro|__NR_aplib
mdefine_line|#define __NR_aplib              255
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ __volatile__ (&quot;mov %0, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res)&bslash;&n;&t;&t;      : &quot;0&quot; (__NR_##name) &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;    return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ __volatile__ (&quot;mov %0, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %1, %%o0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=r&quot; ((long)(arg1)) &bslash;&n;&t;&t;      : &quot;0&quot; (__NR_##name),&quot;1&quot; ((long)(arg1)) &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ __volatile__ (&quot;mov %0, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %1, %%o0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %2, %%o1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=r&quot; ((long)(arg1)), &quot;=r&quot; ((long)(arg2)) &bslash;&n;&t;&t;      : &quot;0&quot; (__NR_##name),&quot;1&quot; ((long)(arg1)),&quot;2&quot; ((long)(arg2)) &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;o1&quot;, &quot;cc&quot;); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ __volatile__ (&quot;mov %0, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %1, %%o0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %2, %%o1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %3, %%o2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=r&quot; ((long)(arg1)), &quot;=r&quot; ((long)(arg2)), &bslash;&n;&t;&t;        &quot;=r&quot; ((long)(arg3)) &bslash;&n;&t;&t;      : &quot;0&quot; (__NR_##name), &quot;1&quot; ((long)(arg1)), &quot;2&quot; ((long)(arg2)), &bslash;&n;&t;&t;        &quot;3&quot; ((long)(arg3)) &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ __volatile__ (&quot;mov %0, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %1, %%o0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %2, %%o1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %3, %%o2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %4, %%o3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0,%%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res), &quot;=r&quot; ((long)(arg1)), &quot;=r&quot; ((long)(arg2)), &bslash;&n;&t;&t;        &quot;=r&quot; ((long)(arg3)), &quot;=r&quot; ((long)(arg4)) &bslash;&n;&t;&t;      : &quot;0&quot; (__NR_##name),&quot;1&quot; ((long)(arg1)),&quot;2&quot; ((long)(arg2)), &bslash;&n;&t;&t;        &quot;3&quot; ((long)(arg3)),&quot;4&quot; ((long)(arg4)) &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;, &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ &bslash;&n;      long __res; &bslash;&n;&bslash;&n;__asm__ __volatile__ (&quot;mov %1, %%o0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %2, %%o1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %3, %%o2&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %4, %%o3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %5, %%o4&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;mov %6, %%g1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;t 0x6d&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;sub %%g0, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      &quot;movcc %%xcc, %%o0, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;      : &quot;=r&quot; (__res) &bslash;&n;&t;&t;      : &quot;r&quot; ((long)(arg1)),&quot;r&quot; ((long)(arg2)), &bslash;&n;&t;&t;        &quot;r&quot; ((long)(arg3)),&quot;r&quot; ((long)(arg4)),&quot;r&quot; ((long)(arg5)), &bslash;&n;&t;&t;        &quot;i&quot; (__NR_##name)  &bslash;&n;&t;&t;      : &quot;g1&quot;, &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;, &quot;o4&quot;, &quot;cc&quot;); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#ifdef __KERNEL_SYSCALLS__
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
r_static
id|__inline__
id|_syscall0
c_func
(paren
r_int
comma
id|idle
)paren
r_static
id|__inline__
id|_syscall0
c_func
(paren
r_int
comma
id|fork
)paren
r_static
id|__inline__
id|_syscall2
c_func
(paren
r_int
comma
id|clone
comma
r_int
r_int
comma
id|flags
comma
r_char
op_star
comma
id|ksp
)paren
r_static
id|__inline__
id|_syscall0
c_func
(paren
r_int
comma
id|pause
)paren
r_static
id|__inline__
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
r_static
id|__inline__
id|_syscall0
c_func
(paren
r_int
comma
id|sync
)paren
r_static
id|__inline__
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
r_static
id|__inline__
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
id|__const__
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
id|__inline__
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
r_static
id|__inline__
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
id|__const__
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
r_static
id|__inline__
id|_syscall3
c_func
(paren
r_int
comma
id|open
comma
id|__const__
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
r_static
id|__inline__
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
r_static
id|__inline__
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
r_static
id|__inline__
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
DECL|function|wait
r_static
id|__inline__
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
id|__inline__
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
id|__volatile
c_func
(paren
l_string|&quot;mov %4, %%g2&bslash;n&bslash;t&quot;
multiline_comment|/* Set aside fn ptr... */
l_string|&quot;mov %5, %%g3&bslash;n&bslash;t&quot;
multiline_comment|/* and arg. */
l_string|&quot;mov %1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;mov %2, %%o0&bslash;n&bslash;t&quot;
multiline_comment|/* Clone flags. */
l_string|&quot;mov 0, %%o1&bslash;n&bslash;t&quot;
multiline_comment|/* usp arg == 0 */
l_string|&quot;t 0x6d&bslash;n&bslash;t&quot;
multiline_comment|/* Linux/Sparc clone(). */
l_string|&quot;brz,a,pn %%o1, 1f&bslash;n&bslash;t&quot;
multiline_comment|/* The parent, just return. */
l_string|&quot; mov %%o0, %0&bslash;n&bslash;t&quot;
l_string|&quot;jmpl %%g2, %%o7&bslash;n&bslash;t&quot;
multiline_comment|/* Call the function. */
l_string|&quot; mov %%g3, %%o0&bslash;n&bslash;t&quot;
multiline_comment|/* Get back the arg in delay. */
l_string|&quot;mov %3, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;t 0x6d&bslash;n&bslash;t&quot;
multiline_comment|/* Linux/Sparc exit(). */
multiline_comment|/* Notreached by child. */
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|__NR_clone
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
op_or
id|CLONE_VM
)paren
comma
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;r&quot;
(paren
id|fn
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;o0&quot;
comma
l_string|&quot;o1&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL_SYSCALLS__ */
macro_line|#ifdef __KERNEL__
multiline_comment|/* sysconf options, for SunOS compatibility */
DECL|macro|_SC_ARG_MAX
mdefine_line|#define   _SC_ARG_MAX             1
DECL|macro|_SC_CHILD_MAX
mdefine_line|#define   _SC_CHILD_MAX           2
DECL|macro|_SC_CLK_TCK
mdefine_line|#define   _SC_CLK_TCK             3
DECL|macro|_SC_NGROUPS_MAX
mdefine_line|#define   _SC_NGROUPS_MAX         4
DECL|macro|_SC_OPEN_MAX
mdefine_line|#define   _SC_OPEN_MAX            5
DECL|macro|_SC_JOB_CONTROL
mdefine_line|#define   _SC_JOB_CONTROL         6
DECL|macro|_SC_SAVED_IDS
mdefine_line|#define   _SC_SAVED_IDS           7
DECL|macro|_SC_VERSION
mdefine_line|#define   _SC_VERSION             8
macro_line|#endif
macro_line|#endif /* _SPARC64_UNISTD_H */
eof
