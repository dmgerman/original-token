macro_line|#ifndef __ASMm68k_ELF_H
DECL|macro|__ASMm68k_ELF_H
mdefine_line|#define __ASMm68k_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 20 /* d1-d7/a0-a6/d0/usp/orig_d0/sr/pc/fmtvec */
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
id|user_m68kfp_struct
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x) == EM_M68K)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; * FIXME(eric) I don&squot;t know what the correct endianness to use is.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_M68K
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
macro_line|#endif
eof
