macro_line|#ifndef __ASM_MIPS_ELF_H
DECL|macro|__ASM_MIPS_ELF_H
mdefine_line|#define __ASM_MIPS_ELF_H
multiline_comment|/*&n; * ELF register definitions&n; * This is &quot;make it compile&quot; stuff!&n; */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;32
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;32
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpreg_t
r_typedef
r_float
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_ELF_H */
eof
