multiline_comment|/* $Id: elf.h,v 1.3 1996/04/22 15:48:48 miguel Exp $ */
macro_line|#ifndef __ASMSPARC_ELF_H
DECL|macro|__ASMSPARC_ELF_H
mdefine_line|#define __ASMSPARC_ELF_H
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
r_int
r_int
id|elf_fpregset_t
suffix:semicolon
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x) == EM_SPARC)
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH EM_SPARC
macro_line|#endif
eof
