macro_line|#ifndef _FCNTL_H
DECL|macro|_FCNTL_H
mdefine_line|#define _FCNTL_H
macro_line|#include &lt;sys/types.h&gt;
multiline_comment|/* open/fcntl - NOCTTY, NDELAY isn&squot;t implemented yet */
DECL|macro|O_ACCMODE
mdefine_line|#define O_ACCMODE&t;00003
DECL|macro|O_RDONLY
mdefine_line|#define O_RDONLY&t;   00
DECL|macro|O_WRONLY
mdefine_line|#define O_WRONLY&t;   01
DECL|macro|O_RDWR
mdefine_line|#define O_RDWR&t;&t;   02
DECL|macro|O_CREAT
mdefine_line|#define O_CREAT&t;&t;00100&t;/* not fcntl */
DECL|macro|O_EXCL
mdefine_line|#define O_EXCL&t;&t;00200&t;/* not fcntl */
DECL|macro|O_NOCTTY
mdefine_line|#define O_NOCTTY&t;00400&t;/* not fcntl */
DECL|macro|O_TRUNC
mdefine_line|#define O_TRUNC&t;&t;01000&t;/* not fcntl */
DECL|macro|O_APPEND
mdefine_line|#define O_APPEND&t;02000
DECL|macro|O_NONBLOCK
mdefine_line|#define O_NONBLOCK&t;04000&t;/* not fcntl */
DECL|macro|O_NDELAY
mdefine_line|#define O_NDELAY&t;O_NONBLOCK
multiline_comment|/* Defines for fcntl-commands. Note that currently&n; * locking isn&squot;t supported, and other things aren&squot;t really&n; * tested.&n; */
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
multiline_comment|/* for F_[GET|SET]FL */
DECL|macro|FD_CLOEXEC
mdefine_line|#define FD_CLOEXEC&t;1&t;/* actually anything with low bit set goes */
multiline_comment|/* Ok, these are locking features, and aren&squot;t implemented at any&n; * level. POSIX wants them.&n; */
DECL|macro|F_RDLCK
mdefine_line|#define F_RDLCK&t;&t;0
DECL|macro|F_WRLCK
mdefine_line|#define F_WRLCK&t;&t;1
DECL|macro|F_UNLCK
mdefine_line|#define F_UNLCK&t;&t;2
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
r_extern
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
r_extern
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
r_extern
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
id|flags
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
eof
