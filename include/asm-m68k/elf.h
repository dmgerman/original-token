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
macro_line|#endif
eof
