multiline_comment|/* ELF support for BFD.&n;   Copyright (C) 1991, 1992, 1993, 1994 Free Software Foundation, Inc.&n;&n;   Written by Fred Fish @ Cygnus Support, from information published&n;   in &quot;UNIX System V Release 4, Programmers Guide: ANSI C and&n;   Programming Support Tools&quot;.&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file is part of ELF support for BFD, and contains the portions&n;   that describe how ELF is represented internally in the BFD library.&n;   I.E. it describes the in-memory representation of ELF.  It requires&n;   the elf-common.h file which contains the portions that are common to&n;   both the internal and external representations. */
multiline_comment|/* NOTE that these structures are not kept in the same order as they appear&n;   in the object file.  In some cases they&squot;ve been reordered for more optimal&n;   packing under various circumstances.  */
multiline_comment|/* ELF Header */
DECL|macro|EI_NIDENT
mdefine_line|#define EI_NIDENT&t;16&t;&t;/* Size of e_ident[] */
DECL|struct|elf_internal_ehdr
r_typedef
r_struct
id|elf_internal_ehdr
(brace
DECL|member|e_ident
r_int
r_char
id|e_ident
(braket
id|EI_NIDENT
)braket
suffix:semicolon
multiline_comment|/* ELF &quot;magic number&quot; */
DECL|member|e_entry
id|bfd_vma
id|e_entry
suffix:semicolon
multiline_comment|/* Entry point virtual address */
DECL|member|e_phoff
id|bfd_signed_vma
id|e_phoff
suffix:semicolon
multiline_comment|/* Program header table file offset */
DECL|member|e_shoff
id|bfd_signed_vma
id|e_shoff
suffix:semicolon
multiline_comment|/* Section header table file offset */
DECL|member|e_version
r_int
r_int
id|e_version
suffix:semicolon
multiline_comment|/* Identifies object file version */
DECL|member|e_flags
r_int
r_int
id|e_flags
suffix:semicolon
multiline_comment|/* Processor-specific flags */
DECL|member|e_type
r_int
r_int
id|e_type
suffix:semicolon
multiline_comment|/* Identifies object file type */
DECL|member|e_machine
r_int
r_int
id|e_machine
suffix:semicolon
multiline_comment|/* Specifies required architecture */
DECL|member|e_ehsize
r_int
r_int
id|e_ehsize
suffix:semicolon
multiline_comment|/* ELF header size in bytes */
DECL|member|e_phentsize
r_int
r_int
id|e_phentsize
suffix:semicolon
multiline_comment|/* Program header table entry size */
DECL|member|e_phnum
r_int
r_int
id|e_phnum
suffix:semicolon
multiline_comment|/* Program header table entry count */
DECL|member|e_shentsize
r_int
r_int
id|e_shentsize
suffix:semicolon
multiline_comment|/* Section header table entry size */
DECL|member|e_shnum
r_int
r_int
id|e_shnum
suffix:semicolon
multiline_comment|/* Section header table entry count */
DECL|member|e_shstrndx
r_int
r_int
id|e_shstrndx
suffix:semicolon
multiline_comment|/* Section header string table index */
DECL|typedef|Elf_Internal_Ehdr
)brace
id|Elf_Internal_Ehdr
suffix:semicolon
DECL|macro|elf32_internal_ehdr
mdefine_line|#define elf32_internal_ehdr elf_internal_ehdr
DECL|macro|Elf32_Internal_Ehdr
mdefine_line|#define Elf32_Internal_Ehdr Elf_Internal_Ehdr
DECL|macro|elf64_internal_ehdr
mdefine_line|#define elf64_internal_ehdr elf_internal_ehdr
DECL|macro|Elf64_Internal_Ehdr
mdefine_line|#define Elf64_Internal_Ehdr Elf_Internal_Ehdr
multiline_comment|/* Program header */
DECL|struct|elf_internal_phdr
r_struct
id|elf_internal_phdr
(brace
DECL|member|p_type
r_int
r_int
id|p_type
suffix:semicolon
multiline_comment|/* Identifies program segment type */
DECL|member|p_flags
r_int
r_int
id|p_flags
suffix:semicolon
multiline_comment|/* Segment flags */
DECL|member|p_offset
id|bfd_vma
id|p_offset
suffix:semicolon
multiline_comment|/* Segment file offset */
DECL|member|p_vaddr
id|bfd_vma
id|p_vaddr
suffix:semicolon
multiline_comment|/* Segment virtual address */
DECL|member|p_paddr
id|bfd_vma
id|p_paddr
suffix:semicolon
multiline_comment|/* Segment physical address */
DECL|member|p_filesz
id|bfd_vma
id|p_filesz
suffix:semicolon
multiline_comment|/* Segment size in file */
DECL|member|p_memsz
id|bfd_vma
id|p_memsz
suffix:semicolon
multiline_comment|/* Segment size in memory */
DECL|member|p_align
id|bfd_vma
id|p_align
suffix:semicolon
multiline_comment|/* Segment alignment, file &amp; memory */
)brace
suffix:semicolon
DECL|typedef|Elf_Internal_Phdr
r_typedef
r_struct
id|elf_internal_phdr
id|Elf_Internal_Phdr
suffix:semicolon
DECL|macro|elf32_internal_phdr
mdefine_line|#define elf32_internal_phdr elf_internal_phdr
DECL|macro|Elf32_Internal_Phdr
mdefine_line|#define Elf32_Internal_Phdr Elf_Internal_Phdr
DECL|macro|elf64_internal_phdr
mdefine_line|#define elf64_internal_phdr elf_internal_phdr
DECL|macro|Elf64_Internal_Phdr
mdefine_line|#define Elf64_Internal_Phdr Elf_Internal_Phdr
multiline_comment|/* Section header */
DECL|struct|elf_internal_shdr
r_typedef
r_struct
id|elf_internal_shdr
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
id|bfd_vma
id|sh_flags
suffix:semicolon
multiline_comment|/* Miscellaneous section attributes */
DECL|member|sh_addr
id|bfd_vma
id|sh_addr
suffix:semicolon
multiline_comment|/* Section virtual addr at execution */
DECL|member|sh_size
id|bfd_size_type
id|sh_size
suffix:semicolon
multiline_comment|/* Size of section in bytes */
DECL|member|sh_entsize
id|bfd_size_type
id|sh_entsize
suffix:semicolon
multiline_comment|/* Entry size if section holds table */
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
DECL|member|sh_offset
id|file_ptr
id|sh_offset
suffix:semicolon
multiline_comment|/* Section file offset */
DECL|member|sh_addralign
r_int
r_int
id|sh_addralign
suffix:semicolon
multiline_comment|/* Section alignment */
multiline_comment|/* The internal rep also has some cached info associated with it. */
DECL|member|bfd_section
id|asection
op_star
id|bfd_section
suffix:semicolon
multiline_comment|/* Associated BFD section.  */
DECL|member|contents
id|PTR
id|contents
suffix:semicolon
multiline_comment|/* Section contents.  */
DECL|typedef|Elf_Internal_Shdr
)brace
id|Elf_Internal_Shdr
suffix:semicolon
DECL|macro|elf32_internal_shdr
mdefine_line|#define elf32_internal_shdr elf_internal_shdr
DECL|macro|Elf32_Internal_Shdr
mdefine_line|#define Elf32_Internal_Shdr Elf_Internal_Shdr
DECL|macro|elf64_internal_shdr
mdefine_line|#define elf64_internal_shdr elf_internal_shdr
DECL|macro|Elf64_Internal_Shdr
mdefine_line|#define Elf64_Internal_Shdr Elf_Internal_Shdr
multiline_comment|/* Symbol table entry */
DECL|struct|elf_internal_sym
r_struct
id|elf_internal_sym
(brace
DECL|member|st_value
id|bfd_vma
id|st_value
suffix:semicolon
multiline_comment|/* Value of the symbol */
DECL|member|st_size
id|bfd_vma
id|st_size
suffix:semicolon
multiline_comment|/* Associated symbol size */
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
)brace
suffix:semicolon
DECL|typedef|Elf_Internal_Sym
r_typedef
r_struct
id|elf_internal_sym
id|Elf_Internal_Sym
suffix:semicolon
DECL|macro|elf32_internal_sym
mdefine_line|#define elf32_internal_sym elf_internal_sym
DECL|macro|elf64_internal_sym
mdefine_line|#define elf64_internal_sym elf_internal_sym
DECL|macro|Elf32_Internal_Sym
mdefine_line|#define Elf32_Internal_Sym Elf_Internal_Sym
DECL|macro|Elf64_Internal_Sym
mdefine_line|#define Elf64_Internal_Sym Elf_Internal_Sym
multiline_comment|/* Note segments */
DECL|struct|elf_internal_note
r_typedef
r_struct
id|elf_internal_note
(brace
DECL|member|namesz
r_int
r_int
id|namesz
suffix:semicolon
multiline_comment|/* Size of entry&squot;s owner string */
DECL|member|descsz
r_int
r_int
id|descsz
suffix:semicolon
multiline_comment|/* Size of the note descriptor */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* Interpretation of the descriptor */
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Start of the name+desc data */
DECL|typedef|Elf_Internal_Note
)brace
id|Elf_Internal_Note
suffix:semicolon
DECL|macro|Elf32_Internal_Note
mdefine_line|#define Elf32_Internal_Note&t;Elf_Internal_Note
DECL|macro|elf32_internal_note
mdefine_line|#define elf32_internal_note&t;elf_internal_note
multiline_comment|/* Relocation Entries */
DECL|struct|elf_internal_rel
r_typedef
r_struct
id|elf_internal_rel
(brace
DECL|member|r_offset
id|bfd_vma
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
multiline_comment|/* This needs to support 64-bit values in elf64.  */
DECL|member|r_info
id|bfd_vma
id|r_info
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|typedef|Elf_Internal_Rel
)brace
id|Elf_Internal_Rel
suffix:semicolon
DECL|macro|elf32_internal_rel
mdefine_line|#define elf32_internal_rel elf_internal_rel
DECL|macro|Elf32_Internal_Rel
mdefine_line|#define Elf32_Internal_Rel Elf_Internal_Rel
DECL|macro|elf64_internal_rel
mdefine_line|#define elf64_internal_rel elf_internal_rel
DECL|macro|Elf64_Internal_Rel
mdefine_line|#define Elf64_Internal_Rel Elf_Internal_Rel
DECL|struct|elf_internal_rela
r_typedef
r_struct
id|elf_internal_rela
(brace
DECL|member|r_offset
id|bfd_vma
id|r_offset
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
id|bfd_vma
id|r_info
suffix:semicolon
multiline_comment|/* Index and Type of relocation */
DECL|member|r_addend
id|bfd_signed_vma
id|r_addend
suffix:semicolon
multiline_comment|/* Constant addend used to compute value */
DECL|typedef|Elf_Internal_Rela
)brace
id|Elf_Internal_Rela
suffix:semicolon
DECL|macro|elf32_internal_rela
mdefine_line|#define elf32_internal_rela elf_internal_rela
DECL|macro|elf64_internal_rela
mdefine_line|#define elf64_internal_rela elf_internal_rela
DECL|macro|Elf32_Internal_Rela
mdefine_line|#define Elf32_Internal_Rela Elf_Internal_Rela
DECL|macro|Elf64_Internal_Rela
mdefine_line|#define Elf64_Internal_Rela Elf_Internal_Rela
multiline_comment|/* dynamic section structure */
DECL|struct|elf_internal_dyn
r_typedef
r_struct
id|elf_internal_dyn
(brace
multiline_comment|/* This needs to support 64-bit values in elf64.  */
DECL|member|d_tag
id|bfd_vma
id|d_tag
suffix:semicolon
multiline_comment|/* entry tag value */
r_union
(brace
multiline_comment|/* This needs to support 64-bit values in elf64.  */
DECL|member|d_val
id|bfd_vma
id|d_val
suffix:semicolon
DECL|member|d_ptr
id|bfd_vma
id|d_ptr
suffix:semicolon
DECL|member|d_un
)brace
id|d_un
suffix:semicolon
DECL|typedef|Elf_Internal_Dyn
)brace
id|Elf_Internal_Dyn
suffix:semicolon
DECL|macro|elf32_internal_dyn
mdefine_line|#define elf32_internal_dyn elf_internal_dyn
DECL|macro|elf64_internal_dyn
mdefine_line|#define elf64_internal_dyn elf_internal_dyn
DECL|macro|Elf32_Internal_Dyn
mdefine_line|#define Elf32_Internal_Dyn Elf_Internal_Dyn
DECL|macro|Elf64_Internal_Dyn
mdefine_line|#define Elf64_Internal_Dyn Elf_Internal_Dyn
eof
