macro_line|#ifndef _ELF_H
DECL|macro|_ELF_H
mdefine_line|#define _ELF_H
multiline_comment|/* THese constants are for the segment types stored in the image headers */
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
DECL|struct|dynamic
r_struct
id|dynamic
(brace
DECL|member|d_tag
r_int
id|d_tag
suffix:semicolon
(def_block
r_union
(brace
DECL|member|d_val
r_int
id|d_val
suffix:semicolon
DECL|member|d_ptr
r_char
op_star
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
)def_block
id|d_un
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* THe following are used with relocations */
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
DECL|struct|Elf32_Rel
r_struct
id|Elf32_Rel
(brace
DECL|member|offset
r_int
r_int
op_star
id|offset
suffix:semicolon
DECL|member|info
r_int
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Elf32_Rela
r_struct
id|Elf32_Rela
(brace
DECL|member|offset
r_int
r_int
op_star
id|offset
suffix:semicolon
DECL|member|info
r_int
id|info
suffix:semicolon
DECL|member|addend
r_int
id|addend
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Elf32_Sym
r_struct
id|Elf32_Sym
(brace
DECL|member|st_name
r_int
id|st_name
suffix:semicolon
DECL|member|st_value
r_int
r_int
id|st_value
suffix:semicolon
DECL|member|st_size
r_int
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
r_int
r_int
id|st_shndx
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|elfhdr
r_struct
id|elfhdr
(brace
DECL|member|e_ident
r_char
id|e_ident
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|e_type
r_int
r_int
id|e_type
suffix:semicolon
DECL|member|e_machine
r_int
r_int
id|e_machine
suffix:semicolon
DECL|member|e_version
r_int
id|e_version
suffix:semicolon
DECL|member|e_entry
r_char
op_star
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point */
DECL|member|e_phoff
r_int
id|e_phoff
suffix:semicolon
DECL|member|e_shoff
r_int
id|e_shoff
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|elf_phdr
r_struct
id|elf_phdr
(brace
DECL|member|p_type
r_int
id|p_type
suffix:semicolon
DECL|member|p_offset
r_int
id|p_offset
suffix:semicolon
DECL|member|p_vaddr
r_int
id|p_vaddr
suffix:semicolon
DECL|member|p_paddr
r_int
id|p_paddr
suffix:semicolon
DECL|member|p_filesz
r_int
id|p_filesz
suffix:semicolon
DECL|member|p_memsz
r_int
id|p_memsz
suffix:semicolon
DECL|member|p_flags
r_int
id|p_flags
suffix:semicolon
DECL|member|p_align
r_int
id|p_align
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ELF_START_MMAP
mdefine_line|#define ELF_START_MMAP 0x80000000
macro_line|#endif
eof
