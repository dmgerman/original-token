multiline_comment|/* ELF support for BFD.&n;   Copyright (C) 1991, 1992 Free Software Foundation, Inc.&n;&n;   Written by Fred Fish @ Cygnus Support, from information published&n;   in &quot;UNIX System V Release 4, Programmers Guide: ANSI C and&n;   Programming Support Tools&quot;.&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file is part of ELF support for BFD, and contains the portions&n;   that describe how ELF is represented externally by the BFD library.&n;   I.E. it describes the in-file representation of ELF.  It requires&n;   the elf-common.h file which contains the portions that are common to&n;   both the internal and external representations. */
multiline_comment|/* The 64-bit stuff is kind of random.  Perhaps someone will publish a&n;   spec someday.  */
multiline_comment|/* ELF Header (32-bit implementations) */
r_typedef
r_struct
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
r_char
id|e_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifies object file type */
DECL|member|e_machine
r_int
r_char
id|e_machine
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Specifies required architecture */
DECL|member|e_version
r_int
r_char
id|e_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Identifies object file version */
DECL|member|e_entry
r_int
r_char
id|e_entry
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Entry point virtual address */
DECL|member|e_phoff
r_int
r_char
id|e_phoff
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Program header table file offset */
DECL|member|e_shoff
r_int
r_char
id|e_shoff
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section header table file offset */
DECL|member|e_flags
r_int
r_char
id|e_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Processor-specific flags */
DECL|member|e_ehsize
r_int
r_char
id|e_ehsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ELF header size in bytes */
DECL|member|e_phentsize
r_int
r_char
id|e_phentsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Program header table entry size */
DECL|member|e_phnum
r_int
r_char
id|e_phnum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Program header table entry count */
DECL|member|e_shentsize
r_int
r_char
id|e_shentsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header table entry size */
DECL|member|e_shnum
r_int
r_char
id|e_shnum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header table entry count */
DECL|member|e_shstrndx
r_int
r_char
id|e_shstrndx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header string table index */
DECL|typedef|Elf32_External_Ehdr
)brace
id|Elf32_External_Ehdr
suffix:semicolon
r_typedef
r_struct
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
r_char
id|e_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifies object file type */
DECL|member|e_machine
r_int
r_char
id|e_machine
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Specifies required architecture */
DECL|member|e_version
r_int
r_char
id|e_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Identifies object file version */
DECL|member|e_entry
r_int
r_char
id|e_entry
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Entry point virtual address */
DECL|member|e_phoff
r_int
r_char
id|e_phoff
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Program header table file offset */
DECL|member|e_shoff
r_int
r_char
id|e_shoff
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Section header table file offset */
DECL|member|e_flags
r_int
r_char
id|e_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Processor-specific flags */
DECL|member|e_ehsize
r_int
r_char
id|e_ehsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ELF header size in bytes */
DECL|member|e_phentsize
r_int
r_char
id|e_phentsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Program header table entry size */
DECL|member|e_phnum
r_int
r_char
id|e_phnum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Program header table entry count */
DECL|member|e_shentsize
r_int
r_char
id|e_shentsize
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header table entry size */
DECL|member|e_shnum
r_int
r_char
id|e_shnum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header table entry count */
DECL|member|e_shstrndx
r_int
r_char
id|e_shstrndx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Section header string table index */
DECL|typedef|Elf64_External_Ehdr
)brace
id|Elf64_External_Ehdr
suffix:semicolon
multiline_comment|/* Program header */
r_typedef
r_struct
(brace
DECL|member|p_type
r_int
r_char
id|p_type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Identifies program segment type */
DECL|member|p_offset
r_int
r_char
id|p_offset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment file offset */
DECL|member|p_vaddr
r_int
r_char
id|p_vaddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment virtual address */
DECL|member|p_paddr
r_int
r_char
id|p_paddr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment physical address */
DECL|member|p_filesz
r_int
r_char
id|p_filesz
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment size in file */
DECL|member|p_memsz
r_int
r_char
id|p_memsz
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment size in memory */
DECL|member|p_flags
r_int
r_char
id|p_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment flags */
DECL|member|p_align
r_int
r_char
id|p_align
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment alignment, file &amp; memory */
DECL|typedef|Elf32_External_Phdr
)brace
id|Elf32_External_Phdr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|p_type
r_int
r_char
id|p_type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Identifies program segment type */
DECL|member|p_flags
r_int
r_char
id|p_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Segment flags */
DECL|member|p_offset
r_int
r_char
id|p_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment file offset */
DECL|member|p_vaddr
r_int
r_char
id|p_vaddr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment virtual address */
DECL|member|p_paddr
r_int
r_char
id|p_paddr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment physical address */
DECL|member|p_filesz
r_int
r_char
id|p_filesz
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment size in file */
DECL|member|p_memsz
r_int
r_char
id|p_memsz
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment size in memory */
DECL|member|p_align
r_int
r_char
id|p_align
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Segment alignment, file &amp; memory */
DECL|typedef|Elf64_External_Phdr
)brace
id|Elf64_External_Phdr
suffix:semicolon
multiline_comment|/* Section header */
r_typedef
r_struct
(brace
DECL|member|sh_name
r_int
r_char
id|sh_name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section name, index in string tbl */
DECL|member|sh_type
r_int
r_char
id|sh_type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Type of section */
DECL|member|sh_flags
r_int
r_char
id|sh_flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Miscellaneous section attributes */
DECL|member|sh_addr
r_int
r_char
id|sh_addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section virtual addr at execution */
DECL|member|sh_offset
r_int
r_char
id|sh_offset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section file offset */
DECL|member|sh_size
r_int
r_char
id|sh_size
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Size of section in bytes */
DECL|member|sh_link
r_int
r_char
id|sh_link
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Index of another section */
DECL|member|sh_info
r_int
r_char
id|sh_info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Additional section information */
DECL|member|sh_addralign
r_int
r_char
id|sh_addralign
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section alignment */
DECL|member|sh_entsize
r_int
r_char
id|sh_entsize
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Entry size if section holds table */
DECL|typedef|Elf32_External_Shdr
)brace
id|Elf32_External_Shdr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|sh_name
r_int
r_char
id|sh_name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Section name, index in string tbl */
DECL|member|sh_type
r_int
r_char
id|sh_type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Type of section */
DECL|member|sh_flags
r_int
r_char
id|sh_flags
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Miscellaneous section attributes */
DECL|member|sh_addr
r_int
r_char
id|sh_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Section virtual addr at execution */
DECL|member|sh_offset
r_int
r_char
id|sh_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Section file offset */
DECL|member|sh_size
r_int
r_char
id|sh_size
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Size of section in bytes */
DECL|member|sh_link
r_int
r_char
id|sh_link
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Index of another section */
DECL|member|sh_info
r_int
r_char
id|sh_info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Additional section information */
DECL|member|sh_addralign
r_int
r_char
id|sh_addralign
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Section alignment */
DECL|member|sh_entsize
r_int
r_char
id|sh_entsize
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Entry size if section holds table */
DECL|typedef|Elf64_External_Shdr
)brace
id|Elf64_External_Shdr
suffix:semicolon
multiline_comment|/* Symbol table entry */
r_typedef
r_struct
(brace
DECL|member|st_name
r_int
r_char
id|st_name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Symbol name, index in string tbl */
DECL|member|st_value
r_int
r_char
id|st_value
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Value of the symbol */
DECL|member|st_size
r_int
r_char
id|st_size
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Associated symbol size */
DECL|member|st_info
r_int
r_char
id|st_info
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Type and binding attributes */
DECL|member|st_other
r_int
r_char
id|st_other
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* No defined meaning, 0 */
DECL|member|st_shndx
r_int
r_char
id|st_shndx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Associated section index */
DECL|typedef|Elf32_External_Sym
)brace
id|Elf32_External_Sym
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|st_name
r_int
r_char
id|st_name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Symbol name, index in string tbl */
DECL|member|st_info
r_int
r_char
id|st_info
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Type and binding attributes */
DECL|member|st_other
r_int
r_char
id|st_other
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* No defined meaning, 0 */
DECL|member|st_shndx
r_int
r_char
id|st_shndx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Associated section index */
DECL|member|st_value
r_int
r_char
id|st_value
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Value of the symbol */
DECL|member|st_size
r_int
r_char
id|st_size
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Associated symbol size */
DECL|typedef|Elf64_External_Sym
)brace
id|Elf64_External_Sym
suffix:semicolon
multiline_comment|/* Note segments */
r_typedef
r_struct
(brace
DECL|member|namesz
r_int
r_char
id|namesz
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Size of entry&squot;s owner string */
DECL|member|descsz
r_int
r_char
id|descsz
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Size of the note descriptor */
DECL|member|type
r_int
r_char
id|type
(braket
l_int|4
)braket
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
DECL|typedef|Elf_External_Note
)brace
id|Elf_External_Note
suffix:semicolon
multiline_comment|/* Relocation Entries */
r_typedef
r_struct
(brace
DECL|member|r_offset
r_int
r_char
id|r_offset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_char
id|r_info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|typedef|Elf32_External_Rel
)brace
id|Elf32_External_Rel
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|r_offset
r_int
r_char
id|r_offset
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_char
id|r_info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|member|r_addend
r_int
r_char
id|r_addend
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Constant addend used to compute value */
DECL|typedef|Elf32_External_Rela
)brace
id|Elf32_External_Rela
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|r_offset
r_int
r_char
id|r_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_char
id|r_info
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|typedef|Elf64_External_Rel
)brace
id|Elf64_External_Rel
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|r_offset
r_int
r_char
id|r_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Location at which to apply the action */
DECL|member|r_info
r_int
r_char
id|r_info
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* index and type of relocation */
DECL|member|r_addend
r_int
r_char
id|r_addend
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Constant addend used to compute value */
DECL|typedef|Elf64_External_Rela
)brace
id|Elf64_External_Rela
suffix:semicolon
multiline_comment|/* dynamic section structure */
r_typedef
r_struct
(brace
DECL|member|d_tag
r_int
r_char
id|d_tag
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* entry tag value */
r_union
(brace
DECL|member|d_val
r_int
r_char
id|d_val
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|d_ptr
r_int
r_char
id|d_ptr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|d_un
)brace
id|d_un
suffix:semicolon
DECL|typedef|Elf32_External_Dyn
)brace
id|Elf32_External_Dyn
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|d_tag
r_int
r_char
id|d_tag
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* entry tag value */
r_union
(brace
DECL|member|d_val
r_int
r_char
id|d_val
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|d_ptr
r_int
r_char
id|d_ptr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|d_un
)brace
id|d_un
suffix:semicolon
DECL|typedef|Elf64_External_Dyn
)brace
id|Elf64_External_Dyn
suffix:semicolon
eof
