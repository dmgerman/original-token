multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/shmparam.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * definitions for the shared process memory on ARM v3 or v4&n; * processors&n; */
macro_line|#ifndef __ASM_PROC_SHMPARAM_H
DECL|macro|__ASM_PROC_SHMPARAM_H
mdefine_line|#define __ASM_PROC_SHMPARAM_H
macro_line|#ifndef SHM_RANGE_START
DECL|macro|SHM_RANGE_START
mdefine_line|#define SHM_RANGE_START&t;0x50000000
DECL|macro|SHM_RANGE_END
mdefine_line|#define SHM_RANGE_END&t;0x60000000
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX&t;&t;0x01000000
macro_line|#endif
macro_line|#endif
eof
