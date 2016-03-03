multiline_comment|/*&n; * Process resource limits&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_RESOURCE_H
DECL|macro|__ASM_MIPS_RESOURCE_H
mdefine_line|#define __ASM_MIPS_RESOURCE_H
multiline_comment|/*&n; * Resource limits&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU 0&t;&t;&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE 1&t;&t;&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA 2&t;&t;&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK 3&t;&t;&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE 4&t;&t;&t;/* max core file size */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE 5&t;&t;&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS 6&t;&t;&t;/* mapped memory */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS 7&t;&t;&t;/* max resident set size */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC 8&t;&t;&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK 9&t;&t;/* max locked-in-memory address space */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS 10&t;&t;&t;/* Number of limit flavors.  */
macro_line|#ifdef __KERNEL__
DECL|macro|INIT_RLIMITS
mdefine_line|#define INIT_RLIMITS&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{LONG_MAX, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{LONG_MAX, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{LONG_MAX, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{_STK_LIM, _STK_LIM},&t;&t;&t;&t;&bslash;&n;&t;{       0, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{NR_OPEN, NR_OPEN},&t;&t;&t;&t;&bslash;&n;&t;{LONG_MAX, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{LONG_MAX, LONG_MAX},&t;&t;&t;&t;&bslash;&n;&t;{MAX_TASKS_PER_USER, MAX_TASKS_PER_USER},&t;&bslash;&n;&t;{ LONG_MAX, LONG_MAX },&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_MIPS_RESOURCE_H */
eof
