macro_line|#ifndef __ASMARM_ELF_H
DECL|macro|__ASMARM_ELF_H
mdefine_line|#define __ASMARM_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|EM_ARM
mdefine_line|#define EM_ARM&t;40
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
DECL|member|null
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
(brace
r_void
op_star
id|null
suffix:semicolon
)brace
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( ((x) == EM_ARM) )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_ARM
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;32768
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;(2 * TASK_SIZE / 3)
DECL|macro|R_ARM_NONE
mdefine_line|#define R_ARM_NONE&t;(0)
DECL|macro|R_ARM_32
mdefine_line|#define R_ARM_32&t;(1)&t;/* =&gt; ld 32 */
DECL|macro|R_ARM_PC26
mdefine_line|#define R_ARM_PC26&t;(2)&t;/* =&gt; ld b/bl branches */
DECL|macro|R_ARM_PC32
mdefine_line|#define R_ARM_PC32&t;(3)
DECL|macro|R_ARM_GOT32
mdefine_line|#define R_ARM_GOT32&t;(4)&t;/* -&gt; object relocation into GOT */
DECL|macro|R_ARM_PLT32
mdefine_line|#define R_ARM_PLT32&t;(5)
DECL|macro|R_ARM_COPY
mdefine_line|#define R_ARM_COPY&t;(6)&t;/* =&gt; dlink copy object */
DECL|macro|R_ARM_GLOB_DAT
mdefine_line|#define R_ARM_GLOB_DAT&t;(7)&t;/* =&gt; dlink 32bit absolute address for .got */
DECL|macro|R_ARM_JUMP_SLOT
mdefine_line|#define R_ARM_JUMP_SLOT&t;(8)&t;/* =&gt; dlink 32bit absolute address for .got.plt */
DECL|macro|R_ARM_RELATIVE
mdefine_line|#define R_ARM_RELATIVE&t;(9)&t;/* =&gt; ld resolved 32bit absolute address requiring load address adjustment */
DECL|macro|R_ARM_GOTOFF
mdefine_line|#define R_ARM_GOTOFF&t;(10)&t;/* =&gt; ld calculates offset of data from base of GOT */
DECL|macro|R_ARM_GOTPC
mdefine_line|#define R_ARM_GOTPC&t;(11)&t;/* =&gt; ld 32-bit relative offset */
macro_line|#endif
eof
