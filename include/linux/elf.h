macro_line|#ifndef _LINUX_ELF_H
DECL|macro|_LINUX_ELF_H
mdefine_line|#define _LINUX_ELF_H
macro_line|#include &lt;asm/elf.h&gt;
DECL|typedef|Elf32_Addr
r_typedef
r_int
r_int
id|Elf32_Addr
suffix:semicolon
DECL|typedef|Elf32_Half
r_typedef
r_int
r_int
id|Elf32_Half
suffix:semicolon
DECL|typedef|Elf32_Off
r_typedef
r_int
r_int
id|Elf32_Off
suffix:semicolon
DECL|typedef|Elf32_Sword
r_typedef
r_int
id|Elf32_Sword
suffix:semicolon
DECL|typedef|Elf32_Word
r_typedef
r_int
r_int
id|Elf32_Word
suffix:semicolon
multiline_comment|/* These constants are for the segment types stored in the image headers */
DECL|macro|PT_NULL
mdefine_line|#define PT_NULL    0
DECL|macro|PT_LOAD
mdefine_line|#define PT_LOAD    1
DECL|macro|PT_DYNAMIC
mdefine_line|#define PT_DYNAMIC 2
DECL|macro|PT_INTERP
mdefine_line|#define PT_INTERP  3
DECL|macro|PT_NOTE
mdefine_line|#define PT_NOTE    4
DECL|macro|PT_SHLIB
mdefine_line|#define PT_SHLIB   5
DECL|macro|PT_PHDR
mdefine_line|#define PT_PHDR    6
DECL|macro|PT_LOPROC
mdefine_line|#define PT_LOPROC  0x70000000
DECL|macro|PT_HIPROC
mdefine_line|#define PT_HIPROC  0x7fffffff
multiline_comment|/* These constants define the different elf file types */
DECL|macro|ET_NONE
mdefine_line|#define ET_NONE   0
DECL|macro|ET_REL
mdefine_line|#define ET_REL    1
DECL|macro|ET_EXEC
mdefine_line|#define ET_EXEC   2
DECL|macro|ET_DYN
mdefine_line|#define ET_DYN    3
DECL|macro|ET_CORE
mdefine_line|#define ET_CORE   4
DECL|macro|ET_LOPROC
mdefine_line|#define ET_LOPROC 5
DECL|macro|ET_HIPROC
mdefine_line|#define ET_HIPROC 6
multiline_comment|/* These constants define the various ELF target machines */
DECL|macro|EM_NONE
mdefine_line|#define EM_NONE  0
DECL|macro|EM_M32
mdefine_line|#define EM_M32   1
DECL|macro|EM_SPARC
mdefine_line|#define EM_SPARC 2
DECL|macro|EM_386
mdefine_line|#define EM_386   3
DECL|macro|EM_68K
mdefine_line|#define EM_68K   4
DECL|macro|EM_88K
mdefine_line|#define EM_88K   5
DECL|macro|EM_486
mdefine_line|#define EM_486   6   /* Perhaps disused */
DECL|macro|EM_860
mdefine_line|#define EM_860   7
DECL|macro|EM_MIPS
mdefine_line|#define EM_MIPS&t;&t;8&t;/* MIPS R3000 (officially, big-endian only) */
DECL|macro|EM_MIPS_RS4_BE
mdefine_line|#define EM_MIPS_RS4_BE 10&t;/* MIPS R4000 big-endian */
DECL|macro|EM_SPARC64
mdefine_line|#define EM_SPARC64     11&t;/* SPARC v9 (not official) 64-bit */
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC      15&t;/* HPPA */
DECL|macro|EM_SPARC32PLUS
mdefine_line|#define EM_SPARC32PLUS 18&t;/* Sun&squot;s &quot;v8plus&quot; */
DECL|macro|EM_PPC
mdefine_line|#define EM_PPC&t;       20&t;/* PowerPC */
multiline_comment|/*&n; * This is an interim value that we will use until the committee comes&n; * up with a final number.&n; */
DECL|macro|EM_ALPHA
mdefine_line|#define EM_ALPHA&t;0x9026
multiline_comment|/* This is the info that is needed to parse the dynamic section of the file */
DECL|macro|DT_NULL
mdefine_line|#define DT_NULL&t;&t;0
DECL|macro|DT_NEEDED
mdefine_line|#define DT_NEEDED&t;1
DECL|macro|DT_PLTRELSZ
mdefine_line|#define DT_PLTRELSZ&t;2
DECL|macro|DT_PLTGOT
mdefine_line|#define DT_PLTGOT&t;3
DECL|macro|DT_HASH
mdefine_line|#define DT_HASH&t;&t;4
DECL|macro|DT_STRTAB
mdefine_line|#define DT_STRTAB&t;5
DECL|macro|DT_SYMTAB
mdefine_line|#define DT_SYMTAB&t;6
DECL|macro|DT_RELA
mdefine_line|#define DT_RELA&t;&t;7
DECL|macro|DT_RELASZ
mdefine_line|#define DT_RELASZ&t;8
DECL|macro|DT_RELAENT
mdefine_line|#define DT_RELAENT&t;9
DECL|macro|DT_STRSZ
mdefine_line|#define DT_STRSZ&t;10
DECL|macro|DT_SYMENT
mdefine_line|#define DT_SYMENT&t;11
DECL|macro|DT_INIT
mdefine_line|#define DT_INIT&t;&t;12
DECL|macro|DT_FINI
mdefine_line|#define DT_FINI&t;&t;13
DECL|macro|DT_SONAME
mdefine_line|#define DT_SONAME&t;14
DECL|macro|DT_RPATH
mdefine_line|#define DT_RPATH &t;15
DECL|macro|DT_SYMBOLIC
mdefine_line|#define DT_SYMBOLIC&t;16
DECL|macro|DT_REL
mdefine_line|#define DT_REL&t;        17
DECL|macro|DT_RELSZ
mdefine_line|#define DT_RELSZ&t;18
DECL|macro|DT_RELENT
mdefine_line|#define DT_RELENT&t;19
DECL|macro|DT_PLTREL
mdefine_line|#define DT_PLTREL&t;20
DECL|macro|DT_DEBUG
mdefine_line|#define DT_DEBUG&t;21
DECL|macro|DT_TEXTREL
mdefine_line|#define DT_TEXTREL&t;22
DECL|macro|DT_JMPREL
mdefine_line|#define DT_JMPREL&t;23
DECL|macro|DT_LOPROC
mdefine_line|#define DT_LOPROC&t;0x70000000
DECL|macro|DT_HIPROC
mdefine_line|#define DT_HIPROC&t;0x7fffffff
multiline_comment|/* This info is needed when parsing the symbol table */
DECL|macro|STB_LOCAL
mdefine_line|#define STB_LOCAL  0
DECL|macro|STB_GLOBAL
mdefine_line|#define STB_GLOBAL 1
DECL|macro|STB_WEAK
mdefine_line|#define STB_WEAK   2
DECL|macro|STT_NOTYPE
mdefine_line|#define STT_NOTYPE  0
DECL|macro|STT_OBJECT
mdefine_line|#define STT_OBJECT  1
DECL|macro|STT_FUNC
mdefine_line|#define STT_FUNC    2
DECL|macro|STT_SECTION
mdefine_line|#define STT_SECTION 3
DECL|macro|STT_FILE
mdefine_line|#define STT_FILE    4
DECL|macro|ELF32_ST_BIND
mdefine_line|#define ELF32_ST_BIND(x) ((x) &gt;&gt; 4)
DECL|macro|ELF32_ST_TYPE
mdefine_line|#define ELF32_ST_TYPE(x) (((unsigned int) x) &amp; 0xf)
multiline_comment|/* Symbolic values for the entries in the auxiliary table&n;   put on the initial stack */
DECL|macro|AT_NULL
mdefine_line|#define AT_NULL   0&t;/* end of vector */
DECL|macro|AT_IGNORE
mdefine_line|#define AT_IGNORE 1&t;/* entry should be ignored */
DECL|macro|AT_EXECFD
mdefine_line|#define AT_EXECFD 2&t;/* file descriptor of program */
DECL|macro|AT_PHDR
mdefine_line|#define AT_PHDR   3&t;/* program headers for program */
DECL|macro|AT_PHENT
mdefine_line|#define AT_PHENT  4&t;/* size of program header entry */
DECL|macro|AT_PHNUM
mdefine_line|#define AT_PHNUM  5&t;/* number of program headers */
DECL|macro|AT_PAGESZ
mdefine_line|#define AT_PAGESZ 6&t;/* system page size */
DECL|macro|AT_BASE
mdefine_line|#define AT_BASE   7&t;/* base address of interpreter */
DECL|macro|AT_FLAGS
mdefine_line|#define AT_FLAGS  8&t;/* flags */
DECL|macro|AT_ENTRY
mdefine_line|#define AT_ENTRY  9&t;/* entry point of program */
DECL|macro|AT_NOTELF
mdefine_line|#define AT_NOTELF 10&t;/* program is not ELF */
DECL|macro|AT_UID
mdefine_line|#define AT_UID    11&t;/* real uid */
DECL|macro|AT_EUID
mdefine_line|#define AT_EUID   12&t;/* effective uid */
DECL|macro|AT_GID
mdefine_line|#define AT_GID    13&t;/* real gid */
DECL|macro|AT_EGID
mdefine_line|#define AT_EGID   14&t;/* effective gid */
DECL|struct|dynamic
r_typedef
r_struct
id|dynamic
(brace
DECL|member|d_tag
id|Elf32_Sword
id|d_tag
suffix:semicolon
(def_block
r_union
(brace
DECL|member|d_val
id|Elf32_Sword
id|d_val
suffix:semicolon
DECL|member|d_ptr
id|Elf32_Addr
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
)def_block
id|d_un
suffix:semicolon
DECL|typedef|Elf32_Dyn
)brace
id|Elf32_Dyn
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|d_tag
r_int
r_int
r_int
id|d_tag
suffix:semicolon
multiline_comment|/* entry tag value */
r_union
(brace
DECL|member|d_val
r_int
r_int
r_int
id|d_val
suffix:semicolon
DECL|member|d_ptr
r_int
r_int
r_int
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
id|d_un
suffix:semicolon
DECL|typedef|Elf64_Dyn
)brace
id|Elf64_Dyn
suffix:semicolon
multiline_comment|/* The following are used with relocations */
DECL|macro|ELF32_R_SYM
mdefine_line|#define ELF32_R_SYM(x) ((x) &gt;&gt; 8)
DECL|macro|ELF32_R_TYPE
mdefine_line|#define ELF32_R_TYPE(x) ((x) &amp; 0xff)
DECL|macro|R_386_NONE
mdefine_line|#define R_386_NONE&t;0
DECL|macro|R_386_32
mdefine_line|#define R_386_32&t;1
DECL|macro|R_386_PC32
mdefine_line|#define R_386_PC32&t;2
DECL|macro|R_386_GOT32
mdefine_line|#define R_386_GOT32&t;3
DECL|macro|R_386_PLT32
mdefine_line|#define R_386_PLT32&t;4
DECL|macro|R_386_COPY
mdefine_line|#define R_386_COPY&t;5
DECL|macro|R_386_GLOB_DAT
mdefine_line|#define R_386_GLOB_DAT&t;6
DECL|macro|R_386_JMP_SLOT
mdefine_line|#define R_386_JMP_SLOT&t;7
DECL|macro|R_386_RELATIVE
mdefine_line|#define R_386_RELATIVE&t;8
DECL|macro|R_386_GOTOFF
mdefine_line|#define R_386_GOTOFF&t;9
DECL|macro|R_386_GOTPC
mdefine_line|#define R_386_GOTPC&t;10
DECL|macro|R_386_NUM
mdefine_line|#define R_386_NUM&t;11
multiline_comment|/*&n; * Sparc ELF relocation types&n; */
DECL|macro|R_SPARC_NONE
mdefine_line|#define&t;R_SPARC_NONE&t;&t;0
DECL|macro|R_SPARC_8
mdefine_line|#define&t;R_SPARC_8&t;&t;1
DECL|macro|R_SPARC_16
mdefine_line|#define&t;R_SPARC_16&t;&t;2
DECL|macro|R_SPARC_32
mdefine_line|#define&t;R_SPARC_32&t;&t;3
DECL|macro|R_SPARC_DISP8
mdefine_line|#define&t;R_SPARC_DISP8&t;&t;4
DECL|macro|R_SPARC_DISP16
mdefine_line|#define&t;R_SPARC_DISP16&t;&t;5
DECL|macro|R_SPARC_DISP32
mdefine_line|#define&t;R_SPARC_DISP32&t;&t;6
DECL|macro|R_SPARC_WDISP30
mdefine_line|#define&t;R_SPARC_WDISP30&t;&t;7
DECL|macro|R_SPARC_WDISP22
mdefine_line|#define&t;R_SPARC_WDISP22&t;&t;8
DECL|macro|R_SPARC_HI22
mdefine_line|#define&t;R_SPARC_HI22&t;&t;9
DECL|macro|R_SPARC_22
mdefine_line|#define&t;R_SPARC_22&t;&t;10
DECL|macro|R_SPARC_13
mdefine_line|#define&t;R_SPARC_13&t;&t;11
DECL|macro|R_SPARC_LO10
mdefine_line|#define&t;R_SPARC_LO10&t;&t;12
DECL|macro|R_SPARC_GOT10
mdefine_line|#define&t;R_SPARC_GOT10&t;&t;13
DECL|macro|R_SPARC_GOT13
mdefine_line|#define&t;R_SPARC_GOT13&t;&t;14
DECL|macro|R_SPARC_GOT22
mdefine_line|#define&t;R_SPARC_GOT22&t;&t;15
DECL|macro|R_SPARC_PC10
mdefine_line|#define&t;R_SPARC_PC10&t;&t;16
DECL|macro|R_SPARC_PC22
mdefine_line|#define&t;R_SPARC_PC22&t;&t;17
DECL|macro|R_SPARC_WPLT30
mdefine_line|#define&t;R_SPARC_WPLT30&t;&t;18
DECL|macro|R_SPARC_COPY
mdefine_line|#define&t;R_SPARC_COPY&t;&t;19
DECL|macro|R_SPARC_GLOB_DAT
mdefine_line|#define&t;R_SPARC_GLOB_DAT&t;20
DECL|macro|R_SPARC_JMP_SLOT
mdefine_line|#define&t;R_SPARC_JMP_SLOT&t;21
DECL|macro|R_SPARC_RELATIVE
mdefine_line|#define&t;R_SPARC_RELATIVE&t;22
DECL|macro|R_SPARC_UA32
mdefine_line|#define&t;R_SPARC_UA32&t;&t;23
DECL|macro|R_SPARC_NUM
mdefine_line|#define&t;R_SPARC_NUM&t;&t;24
multiline_comment|/*&n; * 68k ELF relocation types&n; */
DECL|macro|R_68K_NONE
mdefine_line|#define R_68K_NONE&t;0
DECL|macro|R_68K_32
mdefine_line|#define R_68K_32&t;1
DECL|macro|R_68K_16
mdefine_line|#define R_68K_16&t;2
DECL|macro|R_68K_8
mdefine_line|#define R_68K_8&t;&t;3
DECL|macro|R_68K_PC32
mdefine_line|#define R_68K_PC32&t;4
DECL|macro|R_68K_PC16
mdefine_line|#define R_68K_PC16&t;5
DECL|macro|R_68K_PC8
mdefine_line|#define R_68K_PC8&t;6
DECL|macro|R_68K_GOT32
mdefine_line|#define R_68K_GOT32&t;7
DECL|macro|R_68K_GOT16
mdefine_line|#define R_68K_GOT16&t;8
DECL|macro|R_68K_GOT8
mdefine_line|#define R_68K_GOT8&t;9
DECL|macro|R_68K_GOT32O
mdefine_line|#define R_68K_GOT32O&t;10
DECL|macro|R_68K_GOT16O
mdefine_line|#define R_68K_GOT16O&t;11
DECL|macro|R_68K_GOT8O
mdefine_line|#define R_68K_GOT8O&t;12
DECL|macro|R_68K_PLT32
mdefine_line|#define R_68K_PLT32&t;13
DECL|macro|R_68K_PLT16
mdefine_line|#define R_68K_PLT16&t;14
DECL|macro|R_68K_PLT8
mdefine_line|#define R_68K_PLT8&t;15
DECL|macro|R_68K_PLT32O
mdefine_line|#define R_68K_PLT32O&t;16
DECL|macro|R_68K_PLT16O
mdefine_line|#define R_68K_PLT16O&t;17
DECL|macro|R_68K_PLT8O
mdefine_line|#define R_68K_PLT8O&t;18
DECL|macro|R_68K_COPY
mdefine_line|#define R_68K_COPY&t;19
DECL|macro|R_68K_GLOB_DAT
mdefine_line|#define R_68K_GLOB_DAT&t;20
DECL|macro|R_68K_JMP_SLOT
mdefine_line|#define R_68K_JMP_SLOT&t;21
DECL|macro|R_68K_RELATIVE
mdefine_line|#define R_68K_RELATIVE&t;22
DECL|struct|elf32_rel
r_typedef
r_struct
id|elf32_rel
(brace
DECL|member|r_offset
id|Elf32_Addr
id|r_offset
suffix:semicolon
DECL|member|r_info
id|Elf32_Word
id|r_info
suffix:semicolon
DECL|typedef|Elf32_Rel
)brace
id|Elf32_Rel
suffix:semicolon
DECL|struct|elf64_rel
r_typedef
r_struct
id|elf64_rel
(brace
DECL|member|r_offset
r_int
r_int
r_int
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_int
r_int
id|r_info
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|typedef|Elf64_Rel
)brace
id|Elf64_Rel
suffix:semicolon
DECL|struct|elf32_rela
r_typedef
r_struct
id|elf32_rela
(brace
DECL|member|r_offset
id|Elf32_Addr
id|r_offset
suffix:semicolon
DECL|member|r_info
id|Elf32_Word
id|r_info
suffix:semicolon
DECL|member|r_addend
id|Elf32_Sword
id|r_addend
suffix:semicolon
DECL|typedef|Elf32_Rela
)brace
id|Elf32_Rela
suffix:semicolon
DECL|struct|elf64_rela
r_typedef
r_struct
id|elf64_rela
(brace
DECL|member|r_offset
r_int
r_int
r_int
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_int
r_int
id|r_info
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|member|r_addend
r_int
r_int
r_int
id|r_addend
suffix:semicolon
multiline_comment|/* Constant addend used to compute value */
DECL|typedef|Elf64_Rela
)brace
id|Elf64_Rela
suffix:semicolon
DECL|struct|elf32_sym
r_typedef
r_struct
id|elf32_sym
(brace
DECL|member|st_name
id|Elf32_Word
id|st_name
suffix:semicolon
DECL|member|st_value
id|Elf32_Addr
id|st_value
suffix:semicolon
DECL|member|st_size
id|Elf32_Word
id|st_size
suffix:semicolon
DECL|member|st_info
r_int
r_char
id|st_info
suffix:semicolon
DECL|member|st_other
r_int
r_char
id|st_other
suffix:semicolon
DECL|member|st_shndx
id|Elf32_Half
id|st_shndx
suffix:semicolon
DECL|typedef|Elf32_Sym
)brace
id|Elf32_Sym
suffix:semicolon
DECL|struct|elf64_sym
r_typedef
r_struct
id|elf64_sym
(brace
DECL|member|st_name
r_int
r_int
id|st_name
suffix:semicolon
multiline_comment|/* Symbol name, index in string tbl */
DECL|member|st_info
r_int
r_char
id|st_info
suffix:semicolon
multiline_comment|/* Type and binding attributes */
DECL|member|st_other
r_int
r_char
id|st_other
suffix:semicolon
multiline_comment|/* No defined meaning, 0 */
DECL|member|st_shndx
r_int
r_int
id|st_shndx
suffix:semicolon
multiline_comment|/* Associated section index */
DECL|member|st_value
r_int
r_int
r_int
id|st_value
suffix:semicolon
multiline_comment|/* Value of the symbol */
DECL|member|st_size
r_int
r_int
r_int
id|st_size
suffix:semicolon
multiline_comment|/* Associated symbol size */
DECL|typedef|Elf64_Sym
)brace
id|Elf64_Sym
suffix:semicolon
DECL|macro|EI_NIDENT
mdefine_line|#define EI_NIDENT&t;16
DECL|struct|elf32_hdr
r_typedef
r_struct
id|elf32_hdr
(brace
DECL|member|e_ident
r_int
r_char
id|e_ident
(braket
id|EI_NIDENT
)braket
suffix:semicolon
DECL|member|e_type
id|Elf32_Half
id|e_type
suffix:semicolon
DECL|member|e_machine
id|Elf32_Half
id|e_machine
suffix:semicolon
DECL|member|e_version
id|Elf32_Word
id|e_version
suffix:semicolon
DECL|member|e_entry
id|Elf32_Addr
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point */
DECL|member|e_phoff
id|Elf32_Off
id|e_phoff
suffix:semicolon
DECL|member|e_shoff
id|Elf32_Off
id|e_shoff
suffix:semicolon
DECL|member|e_flags
id|Elf32_Word
id|e_flags
suffix:semicolon
DECL|member|e_ehsize
id|Elf32_Half
id|e_ehsize
suffix:semicolon
DECL|member|e_phentsize
id|Elf32_Half
id|e_phentsize
suffix:semicolon
DECL|member|e_phnum
id|Elf32_Half
id|e_phnum
suffix:semicolon
DECL|member|e_shentsize
id|Elf32_Half
id|e_shentsize
suffix:semicolon
DECL|member|e_shnum
id|Elf32_Half
id|e_shnum
suffix:semicolon
DECL|member|e_shstrndx
id|Elf32_Half
id|e_shstrndx
suffix:semicolon
DECL|typedef|Elf32_Ehdr
)brace
id|Elf32_Ehdr
suffix:semicolon
DECL|struct|elf64_hdr
r_typedef
r_struct
id|elf64_hdr
(brace
DECL|member|e_ident
r_int
r_char
id|e_ident
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* ELF &quot;magic number&quot; */
DECL|member|e_type
r_int
r_int
id|e_type
suffix:semicolon
DECL|member|e_machine
r_int
r_int
r_int
id|e_machine
suffix:semicolon
DECL|member|e_version
r_int
id|e_version
suffix:semicolon
DECL|member|e_entry
r_int
r_int
r_int
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point virtual address */
DECL|member|e_phoff
r_int
r_int
r_int
id|e_phoff
suffix:semicolon
multiline_comment|/* Program header table file offset */
DECL|member|e_shoff
r_int
r_int
r_int
id|e_shoff
suffix:semicolon
multiline_comment|/* Section header table file offset */
DECL|member|e_flags
r_int
id|e_flags
suffix:semicolon
DECL|member|e_ehsize
r_int
r_int
id|e_ehsize
suffix:semicolon
DECL|member|e_phentsize
r_int
r_int
id|e_phentsize
suffix:semicolon
DECL|member|e_phnum
r_int
r_int
id|e_phnum
suffix:semicolon
DECL|member|e_shentsize
r_int
r_int
id|e_shentsize
suffix:semicolon
DECL|member|e_shnum
r_int
r_int
id|e_shnum
suffix:semicolon
DECL|member|e_shstrndx
r_int
r_int
id|e_shstrndx
suffix:semicolon
DECL|typedef|Elf64_Ehdr
)brace
id|Elf64_Ehdr
suffix:semicolon
multiline_comment|/* These constants define the permissions on sections in the program&n;   header, p_flags. */
DECL|macro|PF_R
mdefine_line|#define PF_R&t;&t;0x4
DECL|macro|PF_W
mdefine_line|#define PF_W&t;&t;0x2
DECL|macro|PF_X
mdefine_line|#define PF_X&t;&t;0x1
DECL|struct|elf32_phdr
r_typedef
r_struct
id|elf32_phdr
(brace
DECL|member|p_type
id|Elf32_Word
id|p_type
suffix:semicolon
DECL|member|p_offset
id|Elf32_Off
id|p_offset
suffix:semicolon
DECL|member|p_vaddr
id|Elf32_Addr
id|p_vaddr
suffix:semicolon
DECL|member|p_paddr
id|Elf32_Addr
id|p_paddr
suffix:semicolon
DECL|member|p_filesz
id|Elf32_Word
id|p_filesz
suffix:semicolon
DECL|member|p_memsz
id|Elf32_Word
id|p_memsz
suffix:semicolon
DECL|member|p_flags
id|Elf32_Word
id|p_flags
suffix:semicolon
DECL|member|p_align
id|Elf32_Word
id|p_align
suffix:semicolon
DECL|typedef|Elf32_Phdr
)brace
id|Elf32_Phdr
suffix:semicolon
DECL|struct|elf64_phdr
r_typedef
r_struct
id|elf64_phdr
(brace
DECL|member|p_type
r_int
id|p_type
suffix:semicolon
DECL|member|p_flags
r_int
id|p_flags
suffix:semicolon
DECL|member|p_offset
r_int
r_int
r_int
id|p_offset
suffix:semicolon
multiline_comment|/* Segment file offset */
DECL|member|p_vaddr
r_int
r_int
r_int
id|p_vaddr
suffix:semicolon
multiline_comment|/* Segment virtual address */
DECL|member|p_paddr
r_int
r_int
r_int
id|p_paddr
suffix:semicolon
multiline_comment|/* Segment physical address */
DECL|member|p_filesz
r_int
r_int
r_int
id|p_filesz
suffix:semicolon
multiline_comment|/* Segment size in file */
DECL|member|p_memsz
r_int
r_int
r_int
id|p_memsz
suffix:semicolon
multiline_comment|/* Segment size in memory */
DECL|member|p_align
r_int
r_int
r_int
id|p_align
suffix:semicolon
multiline_comment|/* Segment alignment, file &amp; memory */
DECL|typedef|Elf64_Phdr
)brace
id|Elf64_Phdr
suffix:semicolon
multiline_comment|/* sh_type */
DECL|macro|SHT_NULL
mdefine_line|#define SHT_NULL&t;0
DECL|macro|SHT_PROGBITS
mdefine_line|#define SHT_PROGBITS&t;1
DECL|macro|SHT_SYMTAB
mdefine_line|#define SHT_SYMTAB&t;2
DECL|macro|SHT_STRTAB
mdefine_line|#define SHT_STRTAB&t;3
DECL|macro|SHT_RELA
mdefine_line|#define SHT_RELA&t;4
DECL|macro|SHT_HASH
mdefine_line|#define SHT_HASH&t;5
DECL|macro|SHT_DYNAMIC
mdefine_line|#define SHT_DYNAMIC&t;6
DECL|macro|SHT_NOTE
mdefine_line|#define SHT_NOTE&t;7
DECL|macro|SHT_NOBITS
mdefine_line|#define SHT_NOBITS&t;8
DECL|macro|SHT_REL
mdefine_line|#define SHT_REL&t;&t;9
DECL|macro|SHT_SHLIB
mdefine_line|#define SHT_SHLIB&t;10
DECL|macro|SHT_DYNSYM
mdefine_line|#define SHT_DYNSYM&t;11
DECL|macro|SHT_NUM
mdefine_line|#define SHT_NUM&t;&t;12
DECL|macro|SHT_LOPROC
mdefine_line|#define SHT_LOPROC&t;0x70000000
DECL|macro|SHT_HIPROC
mdefine_line|#define SHT_HIPROC&t;0x7fffffff
DECL|macro|SHT_LOUSER
mdefine_line|#define SHT_LOUSER&t;0x80000000
DECL|macro|SHT_HIUSER
mdefine_line|#define SHT_HIUSER&t;0xffffffff
multiline_comment|/* sh_flags */
DECL|macro|SHF_WRITE
mdefine_line|#define SHF_WRITE&t;0x1
DECL|macro|SHF_ALLOC
mdefine_line|#define SHF_ALLOC&t;0x2
DECL|macro|SHF_EXECINSTR
mdefine_line|#define SHF_EXECINSTR&t;0x4
DECL|macro|SHF_MASKPROC
mdefine_line|#define SHF_MASKPROC&t;0xf0000000
multiline_comment|/* special section indexes */
DECL|macro|SHN_UNDEF
mdefine_line|#define SHN_UNDEF&t;0
DECL|macro|SHN_LORESERVE
mdefine_line|#define SHN_LORESERVE&t;0xff00
DECL|macro|SHN_LOPROC
mdefine_line|#define SHN_LOPROC&t;0xff00
DECL|macro|SHN_HIPROC
mdefine_line|#define SHN_HIPROC&t;0xff1f
DECL|macro|SHN_ABS
mdefine_line|#define SHN_ABS&t;&t;0xfff1
DECL|macro|SHN_COMMON
mdefine_line|#define SHN_COMMON&t;0xfff2
DECL|macro|SHN_HIRESERVE
mdefine_line|#define SHN_HIRESERVE&t;0xffff
r_typedef
r_struct
(brace
DECL|member|sh_name
id|Elf32_Word
id|sh_name
suffix:semicolon
DECL|member|sh_type
id|Elf32_Word
id|sh_type
suffix:semicolon
DECL|member|sh_flags
id|Elf32_Word
id|sh_flags
suffix:semicolon
DECL|member|sh_addr
id|Elf32_Addr
id|sh_addr
suffix:semicolon
DECL|member|sh_offset
id|Elf32_Off
id|sh_offset
suffix:semicolon
DECL|member|sh_size
id|Elf32_Word
id|sh_size
suffix:semicolon
DECL|member|sh_link
id|Elf32_Word
id|sh_link
suffix:semicolon
DECL|member|sh_info
id|Elf32_Word
id|sh_info
suffix:semicolon
DECL|member|sh_addralign
id|Elf32_Word
id|sh_addralign
suffix:semicolon
DECL|member|sh_entsize
id|Elf32_Word
id|sh_entsize
suffix:semicolon
DECL|typedef|Elf32_Shdr
)brace
id|Elf32_Shdr
suffix:semicolon
DECL|struct|elf64_shdr
r_typedef
r_struct
id|elf64_shdr
(brace
DECL|member|sh_name
r_int
r_int
id|sh_name
suffix:semicolon
multiline_comment|/* Section name, index in string tbl */
DECL|member|sh_type
r_int
r_int
id|sh_type
suffix:semicolon
multiline_comment|/* Type of section */
DECL|member|sh_flags
r_int
r_int
r_int
id|sh_flags
suffix:semicolon
multiline_comment|/* Miscellaneous section attributes */
DECL|member|sh_addr
r_int
r_int
r_int
id|sh_addr
suffix:semicolon
multiline_comment|/* Section virtual addr at execution */
DECL|member|sh_offset
r_int
r_int
r_int
id|sh_offset
suffix:semicolon
multiline_comment|/* Section file offset */
DECL|member|sh_size
r_int
r_int
r_int
id|sh_size
suffix:semicolon
multiline_comment|/* Size of section in bytes */
DECL|member|sh_link
r_int
r_int
id|sh_link
suffix:semicolon
multiline_comment|/* Index of another section */
DECL|member|sh_info
r_int
r_int
id|sh_info
suffix:semicolon
multiline_comment|/* Additional section information */
DECL|member|sh_addralign
r_int
r_int
r_int
id|sh_addralign
suffix:semicolon
multiline_comment|/* Section alignment */
DECL|member|sh_entsize
r_int
r_int
r_int
id|sh_entsize
suffix:semicolon
multiline_comment|/* Entry size if section holds table */
DECL|typedef|Elf64_Shdr
)brace
id|Elf64_Shdr
suffix:semicolon
DECL|macro|EI_MAG0
mdefine_line|#define&t;EI_MAG0&t;&t;0&t;&t;/* e_ident[] indexes */
DECL|macro|EI_MAG1
mdefine_line|#define&t;EI_MAG1&t;&t;1
DECL|macro|EI_MAG2
mdefine_line|#define&t;EI_MAG2&t;&t;2
DECL|macro|EI_MAG3
mdefine_line|#define&t;EI_MAG3&t;&t;3
DECL|macro|EI_CLASS
mdefine_line|#define&t;EI_CLASS&t;4
DECL|macro|EI_DATA
mdefine_line|#define&t;EI_DATA&t;&t;5
DECL|macro|EI_VERSION
mdefine_line|#define&t;EI_VERSION&t;6
DECL|macro|EI_PAD
mdefine_line|#define&t;EI_PAD&t;&t;7
DECL|macro|ELFMAG0
mdefine_line|#define&t;ELFMAG0&t;&t;0x7f&t;&t;/* EI_MAG */
DECL|macro|ELFMAG1
mdefine_line|#define&t;ELFMAG1&t;&t;&squot;E&squot;
DECL|macro|ELFMAG2
mdefine_line|#define&t;ELFMAG2&t;&t;&squot;L&squot;
DECL|macro|ELFMAG3
mdefine_line|#define&t;ELFMAG3&t;&t;&squot;F&squot;
DECL|macro|ELFMAG
mdefine_line|#define&t;ELFMAG&t;&t;&quot;&bslash;177ELF&quot;
DECL|macro|SELFMAG
mdefine_line|#define&t;SELFMAG&t;&t;4
DECL|macro|ELFCLASSNONE
mdefine_line|#define&t;ELFCLASSNONE&t;0&t;&t;/* EI_CLASS */
DECL|macro|ELFCLASS32
mdefine_line|#define&t;ELFCLASS32&t;1
DECL|macro|ELFCLASS64
mdefine_line|#define&t;ELFCLASS64&t;2
DECL|macro|ELFCLASSNUM
mdefine_line|#define&t;ELFCLASSNUM&t;3
DECL|macro|ELFDATANONE
mdefine_line|#define ELFDATANONE&t;0&t;&t;/* e_ident[EI_DATA] */
DECL|macro|ELFDATA2LSB
mdefine_line|#define ELFDATA2LSB&t;1
DECL|macro|ELFDATA2MSB
mdefine_line|#define ELFDATA2MSB&t;2
DECL|macro|EV_NONE
mdefine_line|#define EV_NONE&t;&t;0&t;&t;/* e_version, EI_VERSION */
DECL|macro|EV_CURRENT
mdefine_line|#define EV_CURRENT&t;1
DECL|macro|EV_NUM
mdefine_line|#define EV_NUM&t;&t;2
multiline_comment|/* Notes used in ET_CORE */
DECL|macro|NT_PRSTATUS
mdefine_line|#define NT_PRSTATUS&t;1
DECL|macro|NT_PRFPREG
mdefine_line|#define NT_PRFPREG&t;2
DECL|macro|NT_PRPSINFO
mdefine_line|#define NT_PRPSINFO&t;3
DECL|macro|NT_TASKSTRUCT
mdefine_line|#define NT_TASKSTRUCT&t;4
multiline_comment|/* Note header in a PT_NOTE section */
DECL|struct|elf32_note
r_typedef
r_struct
id|elf32_note
(brace
DECL|member|n_namesz
id|Elf32_Word
id|n_namesz
suffix:semicolon
multiline_comment|/* Name size */
DECL|member|n_descsz
id|Elf32_Word
id|n_descsz
suffix:semicolon
multiline_comment|/* Content size */
DECL|member|n_type
id|Elf32_Word
id|n_type
suffix:semicolon
multiline_comment|/* Content type */
DECL|typedef|Elf32_Nhdr
)brace
id|Elf32_Nhdr
suffix:semicolon
multiline_comment|/* Note header in a PT_NOTE section */
multiline_comment|/*&n; * For now we use the 32 bit version of the structure until we figure&n; * out whether we need anything better.  Note - on the Alpha, &quot;unsigned int&quot;&n; * is only 32 bits.&n; */
DECL|struct|elf64_note
r_typedef
r_struct
id|elf64_note
(brace
DECL|member|n_namesz
r_int
r_int
id|n_namesz
suffix:semicolon
multiline_comment|/* Name size */
DECL|member|n_descsz
r_int
r_int
id|n_descsz
suffix:semicolon
multiline_comment|/* Content size */
DECL|member|n_type
r_int
r_int
id|n_type
suffix:semicolon
multiline_comment|/* Content type */
DECL|typedef|Elf64_Nhdr
)brace
id|Elf64_Nhdr
suffix:semicolon
DECL|macro|ELF_START_MMAP
mdefine_line|#define ELF_START_MMAP 0x80000000
macro_line|#if ELF_CLASS == ELFCLASS32
r_extern
id|Elf32_Dyn
id|_DYNAMIC
(braket
)braket
suffix:semicolon
DECL|macro|elfhdr
mdefine_line|#define elfhdr&t;&t;elf32_hdr
DECL|macro|elf_phdr
mdefine_line|#define elf_phdr&t;elf32_phdr
DECL|macro|elf_note
mdefine_line|#define elf_note&t;elf32_note
macro_line|#else
r_extern
id|Elf64_Dyn
id|_DYNAMIC
(braket
)braket
suffix:semicolon
DECL|macro|elfhdr
mdefine_line|#define elfhdr&t;&t;elf64_hdr
DECL|macro|elf_phdr
mdefine_line|#define elf_phdr&t;elf64_phdr
DECL|macro|elf_note
mdefine_line|#define elf_note&t;elf64_note
macro_line|#endif
macro_line|#endif /* _LINUX_ELF_H */
eof
