macro_line|#ifndef __ASMm68k_ELF_H
DECL|macro|__ASMm68k_ELF_H
mdefine_line|#define __ASMm68k_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(elf_greg_t))
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
mdefine_line|#define elf_check_arch(x) ((x) == EM_68K)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_68K
multiline_comment|/* For SVR4/m68k the function pointer to be registered with&n;&t;   `atexit&squot; is passed in %a1.  Although my copy of the ABI has&n;&t;   no such statement, it is actually used on ASV.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;_r-&gt;a1 = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&t;&t;&t;&bslash;&n;&t;/* Bleech. */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;d1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;d3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;d4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;d5;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = regs-&gt;a0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[8] = regs-&gt;a1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[9] = regs-&gt;a2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[14] = regs-&gt;d0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[15] = rdusp();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = regs-&gt;orig_d0;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[17] = regs-&gt;sr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[18] = regs-&gt;pc;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[19] = (regs-&gt;format &lt;&lt; 12) | regs-&gt;vector;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  struct switch_stack *sw = ((struct switch_stack *)regs) - 1;&t;&bslash;&n;&t;  pr_reg[5] = sw-&gt;d6;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[6] = sw-&gt;d7;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[10] = sw-&gt;a3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[11] = sw-&gt;a4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[12] = sw-&gt;a5;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[13] = sw-&gt;a6;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#endif
eof
