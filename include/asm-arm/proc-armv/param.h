multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/param.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROC_PARAM_H
DECL|macro|__ASM_PROC_PARAM_H
mdefine_line|#define __ASM_PROC_PARAM_H
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE   4096
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS         32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP         (-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN  64      /* max length of hostname */
macro_line|#endif
eof
