macro_line|#ifndef _LIMITS_H
DECL|macro|_LIMITS_H
mdefine_line|#define _LIMITS_H
DECL|macro|RAND_MAX
mdefine_line|#define RAND_MAX 0x7ffffffd&t;/* don&squot;t ask - see rand.c */
DECL|macro|CHAR_BIT
mdefine_line|#define CHAR_BIT 8
DECL|macro|MB_LEN_MAX
mdefine_line|#define MB_LEN_MAX 1
DECL|macro|SCHAR_MIN
mdefine_line|#define SCHAR_MIN (-128)
DECL|macro|SCHAR_MAX
mdefine_line|#define SCHAR_MAX 127
DECL|macro|UCHAR_MAX
mdefine_line|#define UCHAR_MAX 255U
macro_line|#ifdef __CHAR_UNSIGNED__
DECL|macro|CHAR_MIN
mdefine_line|#define CHAR_MIN 0
DECL|macro|CHAR_MAX
mdefine_line|#define CHAR_MAX UCHAR_MAX
macro_line|#else
DECL|macro|CHAR_MIN
mdefine_line|#define CHAR_MIN SCHAR_MIN
DECL|macro|CHAR_MAX
mdefine_line|#define CHAR_MAX SCHAR_MAX
macro_line|#endif
DECL|macro|SHRT_MIN
mdefine_line|#define SHRT_MIN (-32768)
DECL|macro|SHRT_MAX
mdefine_line|#define SHRT_MAX 32767
DECL|macro|USHRT_MAX
mdefine_line|#define USHRT_MAX 65535U
DECL|macro|INT_MIN
mdefine_line|#define INT_MIN (-2147483648)
DECL|macro|INT_MAX
mdefine_line|#define INT_MAX 2147483647
DECL|macro|UINT_MAX
mdefine_line|#define UINT_MAX 4294967295U
DECL|macro|LONG_MIN
mdefine_line|#define LONG_MIN (-2147483648)
DECL|macro|LONG_MAX
mdefine_line|#define LONG_MAX 2147483647
DECL|macro|ULONG_MAX
mdefine_line|#define ULONG_MAX 4294967295U
multiline_comment|/*&n; * Why are these different from the section below?  -- TYT&n; */
DECL|macro|_POSIX_ARG_MAX
mdefine_line|#define _POSIX_ARG_MAX 40960&t;/* exec() may have 40K worth of args */
DECL|macro|_POSIX_CHILD_MAX
mdefine_line|#define _POSIX_CHILD_MAX   6&t;/* a process may have 6 children */
DECL|macro|_POSIX_LINK_MAX
mdefine_line|#define _POSIX_LINK_MAX    8&t;/* a file may have 8 links */
DECL|macro|_POSIX_MAX_CANON
mdefine_line|#define _POSIX_MAX_CANON 255&t;/* size of the canonical input queue */
DECL|macro|_POSIX_MAX_INPUT
mdefine_line|#define _POSIX_MAX_INPUT 255&t;/* you can type 255 chars ahead */
DECL|macro|_POSIX_NAME_MAX
mdefine_line|#define _POSIX_NAME_MAX   14&t;/* a file name may have 14 chars */
DECL|macro|_POSIX_NGROUPS_MAX
mdefine_line|#define _POSIX_NGROUPS_MAX 32&t;/* supplementary group IDs are optional */
DECL|macro|_POSIX_OPEN_MAX
mdefine_line|#define _POSIX_OPEN_MAX   16&t;/* a process may have 16 files open */
DECL|macro|_POSIX_PATH_MAX
mdefine_line|#define _POSIX_PATH_MAX  255&t;/* a pathname may contain 255 chars */
DECL|macro|_POSIX_PIPE_BUF
mdefine_line|#define _POSIX_PIPE_BUF  512&t;/* pipes writes of 512 bytes must be atomic */
DECL|macro|NGROUPS_MAX
mdefine_line|#define NGROUPS_MAX       32&t;/* supplemental group IDs are available */
DECL|macro|ARG_MAX
mdefine_line|#define ARG_MAX        40960&t;/* # bytes of args + environ for exec() */
DECL|macro|CHILD_MAX
mdefine_line|#define CHILD_MAX        999    /* no limit :-) */
DECL|macro|OPEN_MAX
mdefine_line|#define OPEN_MAX          20&t;/* # open files a process may have */
DECL|macro|LINK_MAX
mdefine_line|#define LINK_MAX         127&t;/* # links a file may have */
DECL|macro|MAX_CANON
mdefine_line|#define MAX_CANON        255&t;/* size of the canonical input queue */
DECL|macro|MAX_INPUT
mdefine_line|#define MAX_INPUT        255&t;/* size of the type-ahead buffer */
DECL|macro|NAME_MAX
mdefine_line|#define NAME_MAX         255&t;/* # chars in a file name */
DECL|macro|PATH_MAX
mdefine_line|#define PATH_MAX        1024&t;/* # chars in a path name */
DECL|macro|PIPE_BUF
mdefine_line|#define PIPE_BUF        4095&t;/* # bytes in atomic write to a pipe */
macro_line|#endif
eof
