macro_line|#ifndef _UNISTD_H
DECL|macro|_UNISTD_H
mdefine_line|#define _UNISTD_H
multiline_comment|/* ok, this may be a joke, but I&squot;m working on it */
DECL|macro|_POSIX_VERSION
mdefine_line|#define _POSIX_VERSION 198808L
DECL|macro|_POSIX_CHOWN_RESTRICTED
mdefine_line|#define _POSIX_CHOWN_RESTRICTED&t;/* only root can do a chown (I think..) */
DECL|macro|_POSIX_NO_TRUNC
mdefine_line|#define _POSIX_NO_TRUNC&t;&t;/* no pathname truncation (but see in kernel) */
DECL|macro|_POSIX_VDISABLE
mdefine_line|#define _POSIX_VDISABLE &squot;&bslash;0&squot;&t;/* character to disable things like ^C */
DECL|macro|_POSIX_JOB_CONTROL
mdefine_line|#define _POSIX_JOB_CONTROL
DECL|macro|_POSIX_SAVED_IDS
mdefine_line|#define _POSIX_SAVED_IDS&t;/* Implemented, for whatever good it is */
DECL|macro|STDIN_FILENO
mdefine_line|#define STDIN_FILENO&t;0
DECL|macro|STDOUT_FILENO
mdefine_line|#define STDOUT_FILENO&t;1
DECL|macro|STDERR_FILENO
mdefine_line|#define STDERR_FILENO&t;2
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL    ((void *)0)
macro_line|#endif
multiline_comment|/* access */
DECL|macro|F_OK
mdefine_line|#define F_OK&t;0
DECL|macro|X_OK
mdefine_line|#define X_OK&t;1
DECL|macro|W_OK
mdefine_line|#define W_OK&t;2
DECL|macro|R_OK
mdefine_line|#define R_OK&t;4
multiline_comment|/* lseek */
DECL|macro|SEEK_SET
mdefine_line|#define SEEK_SET&t;0
DECL|macro|SEEK_CUR
mdefine_line|#define SEEK_CUR&t;1
DECL|macro|SEEK_END
mdefine_line|#define SEEK_END&t;2
multiline_comment|/* _SC stands for System Configuration. We don&squot;t use them much */
DECL|macro|_SC_ARG_MAX
mdefine_line|#define _SC_ARG_MAX&t;&t;1
DECL|macro|_SC_CHILD_MAX
mdefine_line|#define _SC_CHILD_MAX&t;&t;2
DECL|macro|_SC_CLOCKS_PER_SEC
mdefine_line|#define _SC_CLOCKS_PER_SEC&t;3
DECL|macro|_SC_NGROUPS_MAX
mdefine_line|#define _SC_NGROUPS_MAX&t;&t;4
DECL|macro|_SC_OPEN_MAX
mdefine_line|#define _SC_OPEN_MAX&t;&t;5
DECL|macro|_SC_JOB_CONTROL
mdefine_line|#define _SC_JOB_CONTROL&t;&t;6
DECL|macro|_SC_SAVED_IDS
mdefine_line|#define _SC_SAVED_IDS&t;&t;7
DECL|macro|_SC_VERSION
mdefine_line|#define _SC_VERSION&t;&t;8
multiline_comment|/* more (possibly) configurable things - now pathnames */
DECL|macro|_PC_LINK_MAX
mdefine_line|#define _PC_LINK_MAX&t;&t;1
DECL|macro|_PC_MAX_CANON
mdefine_line|#define _PC_MAX_CANON&t;&t;2
DECL|macro|_PC_MAX_INPUT
mdefine_line|#define _PC_MAX_INPUT&t;&t;3
DECL|macro|_PC_NAME_MAX
mdefine_line|#define _PC_NAME_MAX&t;&t;4
DECL|macro|_PC_PATH_MAX
mdefine_line|#define _PC_PATH_MAX&t;&t;5
DECL|macro|_PC_PIPE_BUF
mdefine_line|#define _PC_PIPE_BUF&t;&t;6
DECL|macro|_PC_NO_TRUNC
mdefine_line|#define _PC_NO_TRUNC&t;&t;7
DECL|macro|_PC_VDISABLE
mdefine_line|#define _PC_VDISABLE&t;&t;8
DECL|macro|_PC_CHOWN_RESTRICTED
mdefine_line|#define _PC_CHOWN_RESTRICTED&t;9
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/times.h&gt;
macro_line|#include &lt;sys/utsname.h&gt;
macro_line|#include &lt;sys/resource.h&gt;
macro_line|#include &lt;utime.h&gt;
macro_line|#ifdef __LIBRARY__
DECL|macro|__NR_setup
mdefine_line|#define __NR_setup&t;0&t;/* used only by init, to get system going */
DECL|macro|__NR_exit
mdefine_line|#define __NR_exit&t;1
DECL|macro|__NR_fork
mdefine_line|#define __NR_fork&t;2
DECL|macro|__NR_read
mdefine_line|#define __NR_read&t;3
DECL|macro|__NR_write
mdefine_line|#define __NR_write&t;4
DECL|macro|__NR_open
mdefine_line|#define __NR_open&t;5
DECL|macro|__NR_close
mdefine_line|#define __NR_close&t;6
DECL|macro|__NR_waitpid
mdefine_line|#define __NR_waitpid&t;7
DECL|macro|__NR_creat
mdefine_line|#define __NR_creat&t;8
DECL|macro|__NR_link
mdefine_line|#define __NR_link&t;9
DECL|macro|__NR_unlink
mdefine_line|#define __NR_unlink&t;10
DECL|macro|__NR_execve
mdefine_line|#define __NR_execve&t;11
DECL|macro|__NR_chdir
mdefine_line|#define __NR_chdir&t;12
DECL|macro|__NR_time
mdefine_line|#define __NR_time&t;13
DECL|macro|__NR_mknod
mdefine_line|#define __NR_mknod&t;14
DECL|macro|__NR_chmod
mdefine_line|#define __NR_chmod&t;15
DECL|macro|__NR_chown
mdefine_line|#define __NR_chown&t;16
DECL|macro|__NR_break
mdefine_line|#define __NR_break&t;17
DECL|macro|__NR_stat
mdefine_line|#define __NR_stat&t;18
DECL|macro|__NR_lseek
mdefine_line|#define __NR_lseek&t;19
DECL|macro|__NR_getpid
mdefine_line|#define __NR_getpid&t;20
DECL|macro|__NR_mount
mdefine_line|#define __NR_mount&t;21
DECL|macro|__NR_umount
mdefine_line|#define __NR_umount&t;22
DECL|macro|__NR_setuid
mdefine_line|#define __NR_setuid&t;23
DECL|macro|__NR_getuid
mdefine_line|#define __NR_getuid&t;24
DECL|macro|__NR_stime
mdefine_line|#define __NR_stime&t;25
DECL|macro|__NR_ptrace
mdefine_line|#define __NR_ptrace&t;26
DECL|macro|__NR_alarm
mdefine_line|#define __NR_alarm&t;27
DECL|macro|__NR_fstat
mdefine_line|#define __NR_fstat&t;28
DECL|macro|__NR_pause
mdefine_line|#define __NR_pause&t;29
DECL|macro|__NR_utime
mdefine_line|#define __NR_utime&t;30
DECL|macro|__NR_stty
mdefine_line|#define __NR_stty&t;31
DECL|macro|__NR_gtty
mdefine_line|#define __NR_gtty&t;32
DECL|macro|__NR_access
mdefine_line|#define __NR_access&t;33
DECL|macro|__NR_nice
mdefine_line|#define __NR_nice&t;34
DECL|macro|__NR_ftime
mdefine_line|#define __NR_ftime&t;35
DECL|macro|__NR_sync
mdefine_line|#define __NR_sync&t;36
DECL|macro|__NR_kill
mdefine_line|#define __NR_kill&t;37
DECL|macro|__NR_rename
mdefine_line|#define __NR_rename&t;38
DECL|macro|__NR_mkdir
mdefine_line|#define __NR_mkdir&t;39
DECL|macro|__NR_rmdir
mdefine_line|#define __NR_rmdir&t;40
DECL|macro|__NR_dup
mdefine_line|#define __NR_dup&t;41
DECL|macro|__NR_pipe
mdefine_line|#define __NR_pipe&t;42
DECL|macro|__NR_times
mdefine_line|#define __NR_times&t;43
DECL|macro|__NR_prof
mdefine_line|#define __NR_prof&t;44
DECL|macro|__NR_brk
mdefine_line|#define __NR_brk&t;45
DECL|macro|__NR_setgid
mdefine_line|#define __NR_setgid&t;46
DECL|macro|__NR_getgid
mdefine_line|#define __NR_getgid&t;47
DECL|macro|__NR_signal
mdefine_line|#define __NR_signal&t;48
DECL|macro|__NR_geteuid
mdefine_line|#define __NR_geteuid&t;49
DECL|macro|__NR_getegid
mdefine_line|#define __NR_getegid&t;50
DECL|macro|__NR_acct
mdefine_line|#define __NR_acct&t;51
DECL|macro|__NR_phys
mdefine_line|#define __NR_phys&t;52
DECL|macro|__NR_lock
mdefine_line|#define __NR_lock&t;53
DECL|macro|__NR_ioctl
mdefine_line|#define __NR_ioctl&t;54
DECL|macro|__NR_fcntl
mdefine_line|#define __NR_fcntl&t;55
DECL|macro|__NR_mpx
mdefine_line|#define __NR_mpx&t;56
DECL|macro|__NR_setpgid
mdefine_line|#define __NR_setpgid&t;57
DECL|macro|__NR_ulimit
mdefine_line|#define __NR_ulimit&t;58
DECL|macro|__NR_uname
mdefine_line|#define __NR_uname&t;59
DECL|macro|__NR_umask
mdefine_line|#define __NR_umask&t;60
DECL|macro|__NR_chroot
mdefine_line|#define __NR_chroot&t;61
DECL|macro|__NR_ustat
mdefine_line|#define __NR_ustat&t;62
DECL|macro|__NR_dup2
mdefine_line|#define __NR_dup2&t;63
DECL|macro|__NR_getppid
mdefine_line|#define __NR_getppid&t;64
DECL|macro|__NR_getpgrp
mdefine_line|#define __NR_getpgrp&t;65
DECL|macro|__NR_setsid
mdefine_line|#define __NR_setsid&t;66
DECL|macro|__NR_sigaction
mdefine_line|#define __NR_sigaction&t;67
DECL|macro|__NR_sgetmask
mdefine_line|#define __NR_sgetmask&t;68
DECL|macro|__NR_ssetmask
mdefine_line|#define __NR_ssetmask&t;69
DECL|macro|__NR_setreuid
mdefine_line|#define __NR_setreuid&t;70
DECL|macro|__NR_setregid
mdefine_line|#define __NR_setregid&t;71
DECL|macro|__NR_sigsuspend
mdefine_line|#define __NR_sigsuspend&t;72
DECL|macro|__NR_sigpending
mdefine_line|#define __NR_sigpending 73
DECL|macro|__NR_sethostname
mdefine_line|#define __NR_sethostname 74
DECL|macro|__NR_setrlimit
mdefine_line|#define __NR_setrlimit&t;75
DECL|macro|__NR_getrlimit
mdefine_line|#define __NR_getrlimit&t;76
DECL|macro|__NR_getrusage
mdefine_line|#define __NR_getrusage&t;77
DECL|macro|__NR_gettimeofday
mdefine_line|#define __NR_gettimeofday 78
DECL|macro|__NR_settimeofday
mdefine_line|#define __NR_settimeofday 79
DECL|macro|__NR_getgroups
mdefine_line|#define __NR_getgroups&t;80
DECL|macro|__NR_setgroups
mdefine_line|#define __NR_setgroups&t;81
DECL|macro|__NR_select
mdefine_line|#define __NR_select&t;82
DECL|macro|__NR_symlink
mdefine_line|#define __NR_symlink&t;83
DECL|macro|__NR_lstat
mdefine_line|#define __NR_lstat&t;84
DECL|macro|__NR_readlink
mdefine_line|#define __NR_readlink&t;85
DECL|macro|__NR_uselib
mdefine_line|#define __NR_uselib&t;86
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name)); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a,btype b) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name(atype a,btype b,ctype c) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b)),&quot;d&quot; ((long)(c))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#endif /* __LIBRARY__ */
r_extern
r_int
id|errno
suffix:semicolon
r_int
id|access
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_int
id|acct
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
suffix:semicolon
r_int
id|alarm
c_func
(paren
r_int
id|sec
)paren
suffix:semicolon
r_int
id|brk
c_func
(paren
r_void
op_star
id|end_data_segment
)paren
suffix:semicolon
r_void
op_star
id|sbrk
c_func
(paren
r_int
id|increment
)paren
suffix:semicolon
r_int
id|chdir
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
suffix:semicolon
r_int
id|chmod
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_int
id|chown
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|uid_t
id|owner
comma
id|gid_t
id|group
)paren
suffix:semicolon
r_int
id|chroot
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
suffix:semicolon
r_int
id|close
c_func
(paren
r_int
id|fildes
)paren
suffix:semicolon
r_int
id|creat
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_int
id|dup
c_func
(paren
r_int
id|fildes
)paren
suffix:semicolon
r_int
id|execve
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
suffix:semicolon
r_int
id|execv
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_char
op_star
op_star
id|argv
)paren
suffix:semicolon
r_int
id|execvp
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
)paren
suffix:semicolon
r_int
id|execl
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_char
op_star
id|arg0
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|execlp
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_char
op_star
id|arg0
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|execle
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_char
op_star
id|arg0
comma
dot
dot
dot
)paren
suffix:semicolon
r_volatile
r_void
m_exit
(paren
r_int
id|status
)paren
suffix:semicolon
r_volatile
r_void
id|_exit
c_func
(paren
r_int
id|status
)paren
suffix:semicolon
r_int
id|fcntl
c_func
(paren
r_int
id|fildes
comma
r_int
id|cmd
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|getpid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|getuid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|geteuid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|getgid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|getegid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ioctl
c_func
(paren
r_int
id|fildes
comma
r_int
id|cmd
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|kill
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|signal
)paren
suffix:semicolon
r_int
id|link
c_func
(paren
r_const
r_char
op_star
id|filename1
comma
r_const
r_char
op_star
id|filename2
)paren
suffix:semicolon
r_int
id|lseek
c_func
(paren
r_int
id|fildes
comma
id|off_t
id|offset
comma
r_int
id|origin
)paren
suffix:semicolon
r_int
id|mknod
c_func
(paren
r_const
r_char
op_star
id|filename
comma
id|mode_t
id|mode
comma
id|dev_t
id|dev
)paren
suffix:semicolon
r_int
id|mount
c_func
(paren
r_const
r_char
op_star
id|specialfile
comma
r_const
r_char
op_star
id|dir
comma
r_int
id|rwflag
)paren
suffix:semicolon
r_int
id|nice
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_int
id|open
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|flag
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pipe
c_func
(paren
r_int
op_star
id|fildes
)paren
suffix:semicolon
r_int
id|read
c_func
(paren
r_int
id|fildes
comma
r_char
op_star
id|buf
comma
id|off_t
id|count
)paren
suffix:semicolon
r_int
id|setpgrp
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|setpgid
c_func
(paren
id|pid_t
id|pid
comma
id|pid_t
id|pgid
)paren
suffix:semicolon
r_int
id|setuid
c_func
(paren
id|uid_t
id|uid
)paren
suffix:semicolon
r_int
id|setgid
c_func
(paren
id|gid_t
id|gid
)paren
suffix:semicolon
r_void
(paren
op_star
id|signal
c_func
(paren
r_int
id|sig
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
)paren
)paren
)paren
(paren
r_int
)paren
suffix:semicolon
r_int
id|stat
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|stat_buf
)paren
suffix:semicolon
r_int
id|fstat
c_func
(paren
r_int
id|fildes
comma
r_struct
id|stat
op_star
id|stat_buf
)paren
suffix:semicolon
r_int
id|stime
c_func
(paren
id|time_t
op_star
id|tptr
)paren
suffix:semicolon
r_int
id|sync
c_func
(paren
r_void
)paren
suffix:semicolon
id|time_t
id|time
c_func
(paren
id|time_t
op_star
id|tloc
)paren
suffix:semicolon
id|time_t
id|times
c_func
(paren
r_struct
id|tms
op_star
id|tbuf
)paren
suffix:semicolon
r_int
id|ulimit
c_func
(paren
r_int
id|cmd
comma
r_int
id|limit
)paren
suffix:semicolon
id|mode_t
id|umask
c_func
(paren
id|mode_t
id|mask
)paren
suffix:semicolon
r_int
id|umount
c_func
(paren
r_const
r_char
op_star
id|specialfile
)paren
suffix:semicolon
r_int
id|uname
c_func
(paren
r_struct
id|utsname
op_star
id|name
)paren
suffix:semicolon
r_int
id|unlink
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
suffix:semicolon
r_int
id|ustat
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|ustat
op_star
id|ubuf
)paren
suffix:semicolon
r_int
id|utime
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|utimbuf
op_star
id|times
)paren
suffix:semicolon
id|pid_t
id|waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
op_star
id|wait_stat
comma
r_int
id|options
)paren
suffix:semicolon
id|pid_t
id|wait
c_func
(paren
r_int
op_star
id|wait_stat
)paren
suffix:semicolon
r_int
id|write
c_func
(paren
r_int
id|fildes
comma
r_const
r_char
op_star
id|buf
comma
id|off_t
id|count
)paren
suffix:semicolon
r_int
id|dup2
c_func
(paren
r_int
id|oldfd
comma
r_int
id|newfd
)paren
suffix:semicolon
r_int
id|getppid
c_func
(paren
r_void
)paren
suffix:semicolon
id|pid_t
id|getpgrp
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
id|sethostname
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|setrlimit
c_func
(paren
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlp
)paren
suffix:semicolon
r_int
id|getrlimit
c_func
(paren
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlp
)paren
suffix:semicolon
r_int
id|getrusage
c_func
(paren
r_int
id|who
comma
r_struct
id|rusage
op_star
id|rusage
)paren
suffix:semicolon
r_int
id|gettimeofday
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
suffix:semicolon
r_int
id|settimeofday
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
suffix:semicolon
r_int
id|getgroups
c_func
(paren
r_int
id|gidsetlen
comma
id|gid_t
op_star
id|gidset
)paren
suffix:semicolon
r_int
id|setgroups
c_func
(paren
r_int
id|gidsetlen
comma
id|gid_t
op_star
id|gidset
)paren
suffix:semicolon
r_int
id|select
c_func
(paren
r_int
id|width
comma
id|fd_set
op_star
id|readfds
comma
id|fd_set
op_star
id|writefds
comma
id|fd_set
op_star
id|exceptfds
comma
r_struct
id|timeval
op_star
id|timeout
)paren
suffix:semicolon
macro_line|#endif
eof
