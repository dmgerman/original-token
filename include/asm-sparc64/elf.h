multiline_comment|/* $Id: elf.h,v 1.8 1997/08/21 18:09:07 richard Exp $ */
macro_line|#ifndef __ASM_SPARC64_ELF_H
DECL|macro|__ASM_SPARC64_ELF_H
mdefine_line|#define __ASM_SPARC64_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
macro_line|#ifndef ELF_ARCH
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_SPARC64
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB
macro_line|#endif
macro_line|#ifndef ELF_FLAGS_INIT
DECL|macro|ELF_FLAGS_INIT
mdefine_line|#define ELF_FLAGS_INIT current-&gt;tss.flags &amp;= ~SPARC_FLAG_32BIT
macro_line|#endif
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
macro_line|#ifndef elf_check_arch
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x) == ELF_ARCH)&t;/* Might be EM_SPARC64 or EM_SPARC */
macro_line|#endif
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
macro_line|#ifndef ELF_ET_DYN_BASE
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)
macro_line|#endif
macro_line|#endif /* !(__ASM_SPARC64_ELF_H) */
eof
