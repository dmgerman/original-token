multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/processor.h&n; *&n; * Copyright (C) 1996,1997,1998 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_PROCESSOR_H
DECL|macro|__ASM_ARCH_PROCESSOR_H
mdefine_line|#define __ASM_ARCH_PROCESSOR_H
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User space: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE(off)&t;(TASK_SIZE / 3)
DECL|macro|TASK_UNMAPPED_ALIGN
mdefine_line|#define TASK_UNMAPPED_ALIGN(addr, off)&t;PAGE_ALIGN(addr)
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, NULL, &amp;init_mm.mmap }
macro_line|#endif
eof
