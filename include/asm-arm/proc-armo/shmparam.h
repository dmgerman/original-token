multiline_comment|/*&n; * linux/include/asm-arm/proc-armo/shmparam.h&n; *&n; * Copyright (C) 1996 Russell King&n; *&n; * definitions for the shared process memory on the ARM3&n; */
macro_line|#ifndef __ASM_PROC_SHMPARAM_H
DECL|macro|__ASM_PROC_SHMPARAM_H
mdefine_line|#define __ASM_PROC_SHMPARAM_H
macro_line|#ifndef SHM_RANGE_START
DECL|macro|SHM_RANGE_START
mdefine_line|#define SHM_RANGE_START&t;0x00a00000
DECL|macro|SHM_RANGE_END
mdefine_line|#define SHM_RANGE_END&t;0x00c00000
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX&t;&t;0x003fa000
macro_line|#endif
macro_line|#endif
eof
