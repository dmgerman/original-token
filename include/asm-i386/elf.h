macro_line|#ifndef __ASMi386_ELF_H
DECL|macro|__ASMi386_ELF_H
mdefine_line|#define __ASMi386_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|user_i387_struct
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( ((x) == EM_386) || ((x) == EM_486) )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_386
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program&n;&t;   starts %edx contains a pointer to a function which might be&n;&t;   registered using `atexit&squot;.  This provides a mean for the&n;&t;   dynamic linker to call DT_FINI functions for shared libraries&n;&t;   that have been loaded before the code runs.&n;&n;&t;   A value of 0 tells we have no such handler.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;_r-&gt;edx = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
macro_line|#endif
eof
