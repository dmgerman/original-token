multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/processor.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; *&n; * Changelog:&n; *  10-Sep-1996&t;RMK&t;Created&n; *  21-Mar-1999&t;RMK&t;Added asm/arch/memory.h&n; */
macro_line|#ifndef __ASM_ARCH_PROCESSOR_H
DECL|macro|__ASM_ARCH_PROCESSOR_H
mdefine_line|#define __ASM_ARCH_PROCESSOR_H
macro_line|#include &lt;asm/arch/memory.h&gt;
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
macro_line|#endif
eof
