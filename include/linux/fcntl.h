macro_line|#ifndef _LINUX_FCNTL_H
DECL|macro|_LINUX_FCNTL_H
mdefine_line|#define _LINUX_FCNTL_H
multiline_comment|/* open/fcntl - O_SYNC isn&squot;t implemented yet */
DECL|macro|O_ACCMODE
mdefine_line|#define O_ACCMODE&t;  0003
DECL|macro|O_RDONLY
mdefine_line|#define O_RDONLY&t;    00
DECL|macro|O_WRONLY
mdefine_line|#define O_WRONLY&t;    01
DECL|macro|O_RDWR
mdefine_line|#define O_RDWR&t;&t;    02
DECL|macro|O_CREAT
mdefine_line|#define O_CREAT&t;&t;  0100&t;/* not fcntl */
DECL|macro|O_EXCL
mdefine_line|#define O_EXCL&t;&t;  0200&t;/* not fcntl */
DECL|macro|O_NOCTTY
mdefine_line|#define O_NOCTTY&t;  0400&t;/* not fcntl */
DECL|macro|O_TRUNC
mdefine_line|#define O_TRUNC&t;&t; 01000&t;/* not fcntl */
DECL|macro|O_APPEND
mdefine_line|#define O_APPEND&t; 02000
DECL|macro|O_NONBLOCK
mdefine_line|#define O_NONBLOCK&t; 04000
DECL|macro|O_NDELAY
mdefine_line|#define O_NDELAY&t;O_NONBLOCK
DECL|macro|O_SYNC
mdefine_line|#define O_SYNC&t;&t;010000
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
mdefine_line|#define F_GETLK&t;&t;5&t;/* not implemented */
DECL|macro|F_SETLK
mdefine_line|#define F_SETLK&t;&t;6
DECL|macro|F_SETLKW
mdefine_line|#define F_SETLKW&t;7
DECL|macro|F_SETOWN
mdefine_line|#define F_SETOWN&t;8&t;/*  for sockets. */
DECL|macro|F_GETOWN
mdefine_line|#define F_GETOWN&t;9&t;/*  for sockets. */
multiline_comment|/* for F_[GET|SET]FL */
DECL|macro|FD_CLOEXEC
mdefine_line|#define FD_CLOEXEC&t;1&t;/* actually anything with low bit set goes */
DECL|macro|F_RDLCK
mdefine_line|#define F_RDLCK&t;&t;0
DECL|macro|F_WRLCK
mdefine_line|#define F_WRLCK&t;&t;1
DECL|macro|F_UNLCK
mdefine_line|#define F_UNLCK&t;&t;2
multiline_comment|/* For bsd flock () */
DECL|macro|F_EXLCK
mdefine_line|#define F_EXLCK&t;&t;4&t;/* or 3 */
DECL|macro|F_SHLCK
mdefine_line|#define F_SHLCK&t;&t;8&t;/* or 4 */
multiline_comment|/* Once again - not implemented, but ... */
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
