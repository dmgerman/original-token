multiline_comment|/* binfmt_elf32.c: Support 32-bit Sparc ELF binaries on Ultra.&n; *&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_SPARC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB;
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x)&t;(((x) == EM_SPARC) || ((x) == EM_SPARC32PLUS))
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0x60000000
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;u32
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t&t;u32
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread start_thread32
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt init_elf32_binfmt
DECL|macro|CONFIG_BINFMT_ELF
macro_line|#undef CONFIG_BINFMT_ELF
macro_line|#ifdef CONFIG_BINFMT_ELF32
DECL|macro|CONFIG_BINFMT_ELF
mdefine_line|#define CONFIG_BINFMT_ELF CONFIG_BINFMT_ELF32
macro_line|#endif
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|#undef CONFIG_BINFMT_ELF_MODULE
macro_line|#ifdef CONFIG_BINFMT_ELF32_MODULE
DECL|macro|CONFIG_BINFMT_ELF_MODULE
mdefine_line|#define CONFIG_BINFMT_ELF_MODULE CONFIG_BINFMT_ELF32_MODULE
macro_line|#endif
DECL|macro|ELF_FLAGS_INIT
mdefine_line|#define ELF_FLAGS_INIT&t;current-&gt;tss.flags |= SPARC_FLAG_32BIT
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Binary format loader for compatibility with 32bit SparcLinux binaries on the Ultra&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Youngdale, David S. Miller, Jakub Jelinek&quot;
)paren
suffix:semicolon
DECL|macro|MODULE_DESCRIPTION
macro_line|#undef MODULE_DESCRIPTION
DECL|macro|MODULE_AUTHOR
macro_line|#undef MODULE_AUTHOR
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
eof
