multiline_comment|/* ELF support for BFD.&n;   Copyright (C) 1991, 1992, 1993, 1994 Free Software Foundation, Inc.&n;&n;   Written by Fred Fish @ Cygnus Support, from information published&n;   in &quot;UNIX System V Release 4, Programmers Guide: ANSI C and&n;   Programming Support Tools&quot;.&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file is part of ELF support for BFD, and contains the portions&n;   that are common to both the internal and external representations.&n;   For example, ELFMAG0 is the byte 0x7F in both the internal (in-memory)&n;   and external (in-file) representations. */
multiline_comment|/* Fields in e_ident[] */
DECL|macro|EI_MAG0
mdefine_line|#define EI_MAG0&t;&t;0&t;&t;/* File identification byte 0 index */
DECL|macro|ELFMAG0
mdefine_line|#define ELFMAG0&t;&t;0x7F&t;&t;/* Magic number byte 0 */
DECL|macro|EI_MAG1
mdefine_line|#define EI_MAG1&t;&t;1&t;&t;/* File identification byte 1 index */
DECL|macro|ELFMAG1
mdefine_line|#define ELFMAG1&t;&t;&squot;E&squot;&t;&t;/* Magic number byte 1 */
DECL|macro|EI_MAG2
mdefine_line|#define EI_MAG2&t;&t;2&t;&t;/* File identification byte 2 index */
DECL|macro|ELFMAG2
mdefine_line|#define ELFMAG2&t;&t;&squot;L&squot;&t;&t;/* Magic number byte 2 */
DECL|macro|EI_MAG3
mdefine_line|#define EI_MAG3&t;&t;3&t;&t;/* File identification byte 3 index */
DECL|macro|ELFMAG3
mdefine_line|#define ELFMAG3&t;&t;&squot;F&squot;&t;&t;/* Magic number byte 3 */
DECL|macro|EI_CLASS
mdefine_line|#define EI_CLASS&t;4&t;&t;/* File class */
DECL|macro|ELFCLASSNONE
mdefine_line|#define ELFCLASSNONE&t;0&t;&t;/* Invalid class */
DECL|macro|ELFCLASS32
mdefine_line|#define ELFCLASS32&t;1&t;&t;/* 32-bit objects */
DECL|macro|ELFCLASS64
mdefine_line|#define ELFCLASS64&t;2&t;&t;/* 64-bit objects */
DECL|macro|EI_DATA
mdefine_line|#define EI_DATA&t;&t;5&t;&t;/* Data encoding */
DECL|macro|ELFDATANONE
mdefine_line|#define ELFDATANONE&t;0&t;&t;/* Invalid data encoding */
DECL|macro|ELFDATA2LSB
mdefine_line|#define ELFDATA2LSB&t;1&t;&t;/* 2&squot;s complement, little endian */
DECL|macro|ELFDATA2MSB
mdefine_line|#define ELFDATA2MSB&t;2&t;&t;/* 2&squot;s complement, big endian */
DECL|macro|EI_VERSION
mdefine_line|#define EI_VERSION&t;6&t;&t;/* File version */
DECL|macro|EI_PAD
mdefine_line|#define EI_PAD&t;&t;7&t;&t;/* Start of padding bytes */
multiline_comment|/* Values for e_type, which identifies the object file type */
DECL|macro|ET_NONE
mdefine_line|#define ET_NONE&t;&t;0&t;&t;/* No file type */
DECL|macro|ET_REL
mdefine_line|#define ET_REL&t;&t;1&t;&t;/* Relocatable file */
DECL|macro|ET_EXEC
mdefine_line|#define ET_EXEC&t;&t;2&t;&t;/* Executable file */
DECL|macro|ET_DYN
mdefine_line|#define ET_DYN&t;&t;3&t;&t;/* Shared object file */
DECL|macro|ET_CORE
mdefine_line|#define ET_CORE&t;&t;4&t;&t;/* Core file */
DECL|macro|ET_LOPROC
mdefine_line|#define ET_LOPROC&t;0xFF00&t;&t;/* Processor-specific */
DECL|macro|ET_HIPROC
mdefine_line|#define ET_HIPROC&t;0xFFFF&t;&t;/* Processor-specific */
multiline_comment|/* Values for e_machine, which identifies the architecture */
DECL|macro|EM_NONE
mdefine_line|#define EM_NONE&t;&t;0&t;/* No machine */
DECL|macro|EM_M32
mdefine_line|#define EM_M32&t;&t;1&t;/* AT&amp;T WE 32100 */
DECL|macro|EM_SPARC
mdefine_line|#define EM_SPARC&t;2&t;/* SUN SPARC */
DECL|macro|EM_386
mdefine_line|#define EM_386&t;&t;3&t;/* Intel 80386 */
DECL|macro|EM_68K
mdefine_line|#define EM_68K&t;&t;4&t;/* Motorola m68k family */
DECL|macro|EM_88K
mdefine_line|#define EM_88K&t;&t;5&t;/* Motorola m88k family */
DECL|macro|EM_860
mdefine_line|#define EM_860&t;&t;7&t;/* Intel 80860 */
DECL|macro|EM_MIPS
mdefine_line|#define EM_MIPS&t;&t;8&t;/* MIPS R3000 (officially, big-endian only) */
DECL|macro|EM_MIPS_RS4_BE
mdefine_line|#define EM_MIPS_RS4_BE 10&t;/* MIPS R4000 big-endian */
DECL|macro|EM_SPARC64
mdefine_line|#define EM_SPARC64     11&t;/* SPARC v9 (not official) 64-bit */
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC      15&t;/* HPPA */
DECL|macro|EM_PPC
mdefine_line|#define EM_PPC&t;       20&t;/* PowerPC */
multiline_comment|/* If it is necessary to assign new unofficial EM_* values, please pick large&n;   random numbers (0x8523, 0xa7f2, etc.) to minimize the chances of collision&n;   with official or non-GNU unofficial values.  */
multiline_comment|/* Cygnus PowerPC ELF backend.  Written in the absence of an ABI.  */
DECL|macro|EM_CYGNUS_POWERPC
mdefine_line|#define EM_CYGNUS_POWERPC 0x9025
multiline_comment|/* Old version of PowerPC, this should be removed shortly. */
DECL|macro|EM_PPC_OLD
mdefine_line|#define EM_PPC_OLD&t;17
multiline_comment|/* Values for e_version */
DECL|macro|EV_NONE
mdefine_line|#define EV_NONE&t;&t;0&t;&t;/* Invalid ELF version */
DECL|macro|EV_CURRENT
mdefine_line|#define EV_CURRENT&t;1&t;&t;/* Current version */
multiline_comment|/* Values for program header, p_type field */
DECL|macro|PT_NULL
mdefine_line|#define&t;PT_NULL&t;&t;0&t;&t;/* Program header table entry unused */
DECL|macro|PT_LOAD
mdefine_line|#define PT_LOAD&t;&t;1&t;&t;/* Loadable program segment */
DECL|macro|PT_DYNAMIC
mdefine_line|#define PT_DYNAMIC&t;2&t;&t;/* Dynamic linking information */
DECL|macro|PT_INTERP
mdefine_line|#define PT_INTERP&t;3&t;&t;/* Program interpreter */
DECL|macro|PT_NOTE
mdefine_line|#define PT_NOTE&t;&t;4&t;&t;/* Auxiliary information */
DECL|macro|PT_SHLIB
mdefine_line|#define PT_SHLIB&t;5&t;&t;/* Reserved, unspecified semantics */
DECL|macro|PT_PHDR
mdefine_line|#define PT_PHDR&t;&t;6&t;&t;/* Entry for header table itself */
DECL|macro|PT_LOPROC
mdefine_line|#define PT_LOPROC&t;0x70000000&t;/* Processor-specific */
DECL|macro|PT_HIPROC
mdefine_line|#define PT_HIPROC&t;0x7FFFFFFF&t;/* Processor-specific */
multiline_comment|/* Program segment permissions, in program header p_flags field */
DECL|macro|PF_X
mdefine_line|#define PF_X&t;&t;(1 &lt;&lt; 0)&t;/* Segment is executable */
DECL|macro|PF_W
mdefine_line|#define PF_W&t;&t;(1 &lt;&lt; 1)&t;/* Segment is writable */
DECL|macro|PF_R
mdefine_line|#define PF_R&t;&t;(1 &lt;&lt; 2)&t;/* Segment is readable */
DECL|macro|PF_MASKPROC
mdefine_line|#define PF_MASKPROC&t;0xF0000000&t;/* Processor-specific reserved bits */
multiline_comment|/* Values for section header, sh_type field */
DECL|macro|SHT_NULL
mdefine_line|#define SHT_NULL&t;0&t;&t;/* Section header table entry unused */
DECL|macro|SHT_PROGBITS
mdefine_line|#define SHT_PROGBITS&t;1&t;&t;/* Program specific (private) data */
DECL|macro|SHT_SYMTAB
mdefine_line|#define SHT_SYMTAB&t;2&t;&t;/* Link editing symbol table */
DECL|macro|SHT_STRTAB
mdefine_line|#define SHT_STRTAB&t;3&t;&t;/* A string table */
DECL|macro|SHT_RELA
mdefine_line|#define SHT_RELA&t;4&t;&t;/* Relocation entries with addends */
DECL|macro|SHT_HASH
mdefine_line|#define SHT_HASH&t;5&t;&t;/* A symbol hash table */
DECL|macro|SHT_DYNAMIC
mdefine_line|#define SHT_DYNAMIC&t;6&t;&t;/* Information for dynamic linking */
DECL|macro|SHT_NOTE
mdefine_line|#define SHT_NOTE&t;7&t;&t;/* Information that marks file */
DECL|macro|SHT_NOBITS
mdefine_line|#define SHT_NOBITS&t;8&t;&t;/* Section occupies no space in file */
DECL|macro|SHT_REL
mdefine_line|#define SHT_REL&t;&t;9&t;&t;/* Relocation entries, no addends */
DECL|macro|SHT_SHLIB
mdefine_line|#define SHT_SHLIB&t;10&t;&t;/* Reserved, unspecified semantics */
DECL|macro|SHT_DYNSYM
mdefine_line|#define SHT_DYNSYM&t;11&t;&t;/* Dynamic linking symbol table */
DECL|macro|SHT_LOPROC
mdefine_line|#define SHT_LOPROC&t;0x70000000&t;/* Processor-specific semantics, lo */
DECL|macro|SHT_HIPROC
mdefine_line|#define SHT_HIPROC&t;0x7FFFFFFF&t;/* Processor-specific semantics, hi */
DECL|macro|SHT_LOUSER
mdefine_line|#define SHT_LOUSER&t;0x80000000&t;/* Application-specific semantics */
DECL|macro|SHT_HIUSER
mdefine_line|#define SHT_HIUSER&t;0x8FFFFFFF&t;/* Application-specific semantics */
multiline_comment|/* Values for section header, sh_flags field */
DECL|macro|SHF_WRITE
mdefine_line|#define SHF_WRITE&t;(1 &lt;&lt; 0)&t;/* Writable data during execution */
DECL|macro|SHF_ALLOC
mdefine_line|#define SHF_ALLOC&t;(1 &lt;&lt; 1)&t;/* Occupies memory during execution */
DECL|macro|SHF_EXECINSTR
mdefine_line|#define SHF_EXECINSTR&t;(1 &lt;&lt; 2)&t;/* Executable machine instructions */
DECL|macro|SHF_MASKPROC
mdefine_line|#define SHF_MASKPROC&t;0xF0000000&t;/* Processor-specific semantics */
multiline_comment|/* Values of note segment descriptor types for core files. */
DECL|macro|NT_PRSTATUS
mdefine_line|#define NT_PRSTATUS&t;1&t;&t;/* Contains copy of prstatus struct */
DECL|macro|NT_FPREGSET
mdefine_line|#define NT_FPREGSET&t;2&t;&t;/* Contains copy of fpregset struct */
DECL|macro|NT_PRPSINFO
mdefine_line|#define NT_PRPSINFO&t;3&t;&t;/* Contains copy of prpsinfo struct */
multiline_comment|/* Values of note segment descriptor types for object files.  */
multiline_comment|/* (Only for hppa right now.  Should this be moved elsewhere?)  */
DECL|macro|NT_VERSION
mdefine_line|#define NT_VERSION&t;1&t;&t;/* Contains a version string.  */
multiline_comment|/* These three macros disassemble and assemble a symbol table st_info field,&n;   which contains the symbol binding and symbol type.  The STB_ and STT_&n;   defines identify the binding and type. */
DECL|macro|ELF_ST_BIND
mdefine_line|#define ELF_ST_BIND(val)&t;&t;(((unsigned int)(val)) &gt;&gt; 4)
DECL|macro|ELF_ST_TYPE
mdefine_line|#define ELF_ST_TYPE(val)&t;&t;((val) &amp; 0xF)
DECL|macro|ELF_ST_INFO
mdefine_line|#define ELF_ST_INFO(bind,type)&t;&t;(((bind) &lt;&lt; 4) + ((type) &amp; 0xF))
DECL|macro|STN_UNDEF
mdefine_line|#define STN_UNDEF&t;0&t;&t;/* undefined symbol index */
DECL|macro|STB_LOCAL
mdefine_line|#define STB_LOCAL&t;0&t;&t;/* Symbol not visible outside obj */
DECL|macro|STB_GLOBAL
mdefine_line|#define STB_GLOBAL&t;1&t;&t;/* Symbol visible outside obj */
DECL|macro|STB_WEAK
mdefine_line|#define STB_WEAK&t;2&t;&t;/* Like globals, lower precedence */
DECL|macro|STB_LOPROC
mdefine_line|#define STB_LOPROC&t;13&t;&t;/* Application-specific semantics */
DECL|macro|STB_HIPROC
mdefine_line|#define STB_HIPROC&t;15&t;&t;/* Application-specific semantics */
DECL|macro|STT_NOTYPE
mdefine_line|#define STT_NOTYPE&t;0&t;&t;/* Symbol type is unspecified */
DECL|macro|STT_OBJECT
mdefine_line|#define STT_OBJECT&t;1&t;&t;/* Symbol is a data object */
DECL|macro|STT_FUNC
mdefine_line|#define STT_FUNC&t;2&t;&t;/* Symbol is a code object */
DECL|macro|STT_SECTION
mdefine_line|#define STT_SECTION&t;3&t;&t;/* Symbol associated with a section */
DECL|macro|STT_FILE
mdefine_line|#define STT_FILE&t;4&t;&t;/* Symbol gives a file name */
DECL|macro|STT_LOPROC
mdefine_line|#define STT_LOPROC&t;13&t;&t;/* Application-specific semantics */
DECL|macro|STT_HIPROC
mdefine_line|#define STT_HIPROC&t;15&t;&t;/* Application-specific semantics */
multiline_comment|/* Special section indices, which may show up in st_shndx fields, among&n;   other places. */
DECL|macro|SHN_UNDEF
mdefine_line|#define SHN_UNDEF&t;0&t;&t;/* Undefined section reference */
DECL|macro|SHN_LORESERVE
mdefine_line|#define SHN_LORESERVE&t;0xFF00&t;&t;/* Begin range of reserved indices */
DECL|macro|SHN_LOPROC
mdefine_line|#define SHN_LOPROC&t;0xFF00&t;&t;/* Begin range of appl-specific */
DECL|macro|SHN_HIPROC
mdefine_line|#define SHN_HIPROC&t;0xFF1F&t;&t;/* End range of appl-specific */
DECL|macro|SHN_ABS
mdefine_line|#define SHN_ABS&t;&t;0xFFF1&t;&t;/* Associated symbol is absolute */
DECL|macro|SHN_COMMON
mdefine_line|#define SHN_COMMON&t;0xFFF2&t;&t;/* Associated symbol is in common */
DECL|macro|SHN_HIRESERVE
mdefine_line|#define SHN_HIRESERVE&t;0xFFFF&t;&t;/* End range of reserved indices */
multiline_comment|/* relocation info handling macros */
DECL|macro|ELF32_R_SYM
mdefine_line|#define ELF32_R_SYM(i)&t;&t;((i) &gt;&gt; 8)
DECL|macro|ELF32_R_TYPE
mdefine_line|#define ELF32_R_TYPE(i)&t;&t;((i) &amp; 0xff)
DECL|macro|ELF32_R_INFO
mdefine_line|#define ELF32_R_INFO(s,t)&t;(((s) &lt;&lt; 8) + ((t) &amp; 0xff))
DECL|macro|ELF64_R_SYM
mdefine_line|#define ELF64_R_SYM(i)&t;&t;((i) &gt;&gt; 32)
DECL|macro|ELF64_R_TYPE
mdefine_line|#define ELF64_R_TYPE(i)&t;&t;((i) &amp; 0xffffffff)
DECL|macro|ELF64_R_INFO
mdefine_line|#define ELF64_R_INFO(s,t)&t;(((bfd_vma) (s) &lt;&lt; 32) + (bfd_vma) (t))
multiline_comment|/* Dynamic section tags */
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
mdefine_line|#define DT_RPATH&t;15
DECL|macro|DT_SYMBOLIC
mdefine_line|#define DT_SYMBOLIC&t;16
DECL|macro|DT_REL
mdefine_line|#define DT_REL&t;&t;17
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
eof
