multiline_comment|/* $Id: elf.h,v 1.16 1998/05/01 16:28:47 davem Exp $ */
macro_line|#ifndef __ASMSPARC_ELF_H
DECL|macro|__ASMSPARC_ELF_H
mdefine_line|#define __ASMSPARC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
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
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x) == EM_SPARC)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_SPARC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
macro_line|#ifndef CONFIG_SUN4
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
macro_line|#else
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
macro_line|#endif
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE(0) + 0x1000000)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This can NOT be done in userspace&n;   on Sparc.  */
multiline_comment|/* Sun4c has none of the capabilities, most sun4m&squot;s have them all.&n; * XXX This is gross, set some global variable at boot time. -DaveM&n; */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;((ARCH_SUN4C_SUN4) ? 0 : &bslash;&n;&t;&t;&t; (HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_SWAP | &bslash;&n;&t;&t;&t;  ((srmmu_modtype != Cypress &amp;&amp; &bslash;&n;&t;&t;&t;    srmmu_modtype != Cypress_vE &amp;&amp; &bslash;&n;&t;&t;&t;    srmmu_modtype != Cypress_vD) ? &bslash;&n;&t;&t;&t;   HWCAP_SPARC_MULDIV : 0)))
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo. */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) &bslash;&n;&t;current-&gt;personality = (ibcs2 ? PER_SVR4 : PER_LINUX)
macro_line|#endif
macro_line|#endif /* !(__ASMSPARC_ELF_H) */
eof
