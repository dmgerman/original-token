macro_line|#ifndef _PPC_RESOURCE_H
DECL|macro|_PPC_RESOURCE_H
mdefine_line|#define _PPC_RESOURCE_H
multiline_comment|/*&n; * These were swiped from asm-i386 so they don&squot;t fit well with the&n; * powerstack very well at all.  Anyone want to go through them and&n; * correct them?&n; *                              -- Cort&n; */
multiline_comment|/*&n; * Resource limits&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU&t;0&t;&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE&t;1&t;&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA&t;2&t;&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK&t;3&t;&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE&t;4&t;&t;/* max core file size */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS&t;5&t;&t;/* max resident set size */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;6&t;&t;/* max number of processes */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;7&t;&t;/* max number of open files */
macro_line|#ifdef notdef
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;8&t;&t;/* max locked-in-memory address space*/
macro_line|#endif
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;8
macro_line|#endif
eof
