macro_line|#ifndef _ERRNO_H
DECL|macro|_ERRNO_H
mdefine_line|#define _ERRNO_H
multiline_comment|/*&n; * ok, as I hadn&squot;t got any other source of information about&n; * possible error numbers, I was forced to use the same numbers&n; * as minix.&n; * Hopefully these are posix or something. I wouldn&squot;t know (and posix&n; * isn&squot;t telling me - they want $$$ for their f***ing standard).&n; *&n; * We don&squot;t use the _SIGN cludge of minix, so kernel returns must&n; * see to the sign by themselves.&n; *&n; * NOTE! Remember to change strerror() if you change this file!&n; */
r_extern
r_int
id|errno
suffix:semicolon
DECL|macro|ERROR
mdefine_line|#define ERROR&t;&t;99
DECL|macro|EPERM
mdefine_line|#define EPERM&t;&t; 1
DECL|macro|ENOENT
mdefine_line|#define ENOENT&t;&t; 2
DECL|macro|ESRCH
mdefine_line|#define ESRCH&t;&t; 3
DECL|macro|EINTR
mdefine_line|#define EINTR&t;&t; 4
DECL|macro|EIO
mdefine_line|#define EIO&t;&t; 5
DECL|macro|ENXIO
mdefine_line|#define ENXIO&t;&t; 6
DECL|macro|E2BIG
mdefine_line|#define E2BIG&t;&t; 7
DECL|macro|ENOEXEC
mdefine_line|#define ENOEXEC&t;&t; 8
DECL|macro|EBADF
mdefine_line|#define EBADF&t;&t; 9
DECL|macro|ECHILD
mdefine_line|#define ECHILD&t;&t;10
DECL|macro|EAGAIN
mdefine_line|#define EAGAIN&t;&t;11
DECL|macro|ENOMEM
mdefine_line|#define ENOMEM&t;&t;12
DECL|macro|EACCES
mdefine_line|#define EACCES&t;&t;13
DECL|macro|EFAULT
mdefine_line|#define EFAULT&t;&t;14
DECL|macro|ENOTBLK
mdefine_line|#define ENOTBLK&t;&t;15
DECL|macro|EBUSY
mdefine_line|#define EBUSY&t;&t;16
DECL|macro|EEXIST
mdefine_line|#define EEXIST&t;&t;17
DECL|macro|EXDEV
mdefine_line|#define EXDEV&t;&t;18
DECL|macro|ENODEV
mdefine_line|#define ENODEV&t;&t;19
DECL|macro|ENOTDIR
mdefine_line|#define ENOTDIR&t;&t;20
DECL|macro|EISDIR
mdefine_line|#define EISDIR&t;&t;21
DECL|macro|EINVAL
mdefine_line|#define EINVAL&t;&t;22
DECL|macro|ENFILE
mdefine_line|#define ENFILE&t;&t;23
DECL|macro|EMFILE
mdefine_line|#define EMFILE&t;&t;24
DECL|macro|ENOTTY
mdefine_line|#define ENOTTY&t;&t;25
DECL|macro|ETXTBSY
mdefine_line|#define ETXTBSY&t;&t;26
DECL|macro|EFBIG
mdefine_line|#define EFBIG&t;&t;27
DECL|macro|ENOSPC
mdefine_line|#define ENOSPC&t;&t;28
DECL|macro|ESPIPE
mdefine_line|#define ESPIPE&t;&t;29
DECL|macro|EROFS
mdefine_line|#define EROFS&t;&t;30
DECL|macro|EMLINK
mdefine_line|#define EMLINK&t;&t;31
DECL|macro|EPIPE
mdefine_line|#define EPIPE&t;&t;32
DECL|macro|EDOM
mdefine_line|#define EDOM&t;&t;33
DECL|macro|ERANGE
mdefine_line|#define ERANGE&t;&t;34
DECL|macro|EDEADLK
mdefine_line|#define EDEADLK&t;&t;35
DECL|macro|ENAMETOOLONG
mdefine_line|#define ENAMETOOLONG&t;36
DECL|macro|ENOLCK
mdefine_line|#define ENOLCK&t;&t;37
DECL|macro|ENOSYS
mdefine_line|#define ENOSYS&t;&t;38
DECL|macro|ENOTEMPTY
mdefine_line|#define ENOTEMPTY&t;39
multiline_comment|/* Should never be seen by user programs */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
macro_line|#endif
eof
