macro_line|#ifndef _ALPHA_FCNTL_H
DECL|macro|_ALPHA_FCNTL_H
mdefine_line|#define _ALPHA_FCNTL_H
multiline_comment|/* open/fcntl - O_SYNC is only implemented on blocks devices and on files&n;   located on an ext2 file system */
DECL|macro|O_ACCMODE
mdefine_line|#define O_ACCMODE&t;  0003
DECL|macro|O_RDONLY
mdefine_line|#define O_RDONLY&t;    00
DECL|macro|O_WRONLY
mdefine_line|#define O_WRONLY&t;    01
DECL|macro|O_RDWR
mdefine_line|#define O_RDWR&t;&t;    02
DECL|macro|O_CREAT
mdefine_line|#define O_CREAT&t;&t; 01000&t;/* not fcntl */
DECL|macro|O_TRUNC
mdefine_line|#define O_TRUNC&t;&t; 02000&t;/* not fcntl */
DECL|macro|O_EXCL
mdefine_line|#define O_EXCL&t;&t; 04000&t;/* not fcntl */
DECL|macro|O_NOCTTY
mdefine_line|#define O_NOCTTY&t;010000&t;/* not fcntl */
DECL|macro|O_NONBLOCK
mdefine_line|#define O_NONBLOCK&t; 00004
DECL|macro|O_APPEND
mdefine_line|#define O_APPEND&t; 00010
DECL|macro|O_NDELAY
mdefine_line|#define O_NDELAY&t;O_NONBLOCK
DECL|macro|O_SYNC
mdefine_line|#define O_SYNC&t;&t;040000
DECL|macro|FASYNC
mdefine_line|#define FASYNC&t;&t;020000&t;/* fcntl, for BSD compatibility */
DECL|macro|F_DUPFD
mdefine_line|#define F_DUPFD&t;&t;0&t;/* dup */
DECL|macro|F_GETFD
mdefine_line|#define F_GETFD&t;&t;1&t;/* get f_flags */
DECL|macro|F_SETFD
mdefine_line|#define F_SETFD&t;&t;2&t;/* set f_flags */
DECL|macro|F_GETFL
mdefine_line|#define F_GETFL&t;&t;3&t;/* more flags (cloexec) */
DECL|macro|F_SETFL
mdefine_line|#define F_SETFL&t;&t;4
DECL|macro|F_GETLK
mdefine_line|#define F_GETLK&t;&t;7
DECL|macro|F_SETLK
mdefine_line|#define F_SETLK&t;&t;8
DECL|macro|F_SETLKW
mdefine_line|#define F_SETLKW&t;9
DECL|macro|F_SETOWN
mdefine_line|#define F_SETOWN&t;5&t;/*  for sockets. */
DECL|macro|F_GETOWN
mdefine_line|#define F_GETOWN&t;6&t;/*  for sockets. */
multiline_comment|/* for F_[GET|SET]FL */
DECL|macro|FD_CLOEXEC
mdefine_line|#define FD_CLOEXEC&t;1&t;/* actually anything with low bit set goes */
multiline_comment|/* for posix fcntl() and lockf() */
DECL|macro|F_RDLCK
mdefine_line|#define F_RDLCK&t;&t;1
DECL|macro|F_WRLCK
mdefine_line|#define F_WRLCK&t;&t;2
DECL|macro|F_UNLCK
mdefine_line|#define F_UNLCK&t;&t;8
multiline_comment|/* for old implementation of bsd flock () */
DECL|macro|F_EXLCK
mdefine_line|#define F_EXLCK&t;&t;16&t;/* or 3 */
DECL|macro|F_SHLCK
mdefine_line|#define F_SHLCK&t;&t;32&t;/* or 4 */
multiline_comment|/* operations for bsd flock(), also used by the kernel implementation */
DECL|macro|LOCK_SH
mdefine_line|#define LOCK_SH&t;&t;1&t;/* shared lock */
DECL|macro|LOCK_EX
mdefine_line|#define LOCK_EX&t;&t;2&t;/* exclusive lock */
DECL|macro|LOCK_NB
mdefine_line|#define LOCK_NB&t;&t;4&t;/* or&squot;d with one of the above to prevent&n;&t;&t;&t;&t;   blocking */
DECL|macro|LOCK_UN
mdefine_line|#define LOCK_UN&t;&t;8&t;/* remove lock */
macro_line|#ifdef __KERNEL__
DECL|macro|F_POSIX
mdefine_line|#define F_POSIX&t;&t;1
DECL|macro|F_FLOCK
mdefine_line|#define F_FLOCK&t;&t;2
macro_line|#endif /* __KERNEL__ */
DECL|struct|flock
r_struct
id|flock
(brace
DECL|member|l_type
r_int
id|l_type
suffix:semicolon
DECL|member|l_whence
r_int
id|l_whence
suffix:semicolon
DECL|member|l_start
id|off_t
id|l_start
suffix:semicolon
DECL|member|l_len
id|off_t
id|l_len
suffix:semicolon
DECL|member|l_pid
id|pid_t
id|l_pid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof