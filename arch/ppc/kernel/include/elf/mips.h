multiline_comment|/* MIPS ELF support for BFD.&n;   Copyright (C) 1993, 1994 Free Software Foundation, Inc.&n;&n;   By Ian Lance Taylor, Cygnus Support, &lt;ian@cygnus.com&gt;, from&n;   information in the System V Application Binary Interface, MIPS&n;   Processor Supplement.&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file holds definitions specific to the MIPS ELF ABI.  Note&n;   that most of this is not actually implemented by BFD.  */
multiline_comment|/* Processor specific flags for the ELF header e_flags field.  */
multiline_comment|/* At least one .noreorder directive appears in the source.  */
DECL|macro|EF_MIPS_NOREORDER
mdefine_line|#define EF_MIPS_NOREORDER&t;0x00000001
multiline_comment|/* File contains position independent code.  */
DECL|macro|EF_MIPS_PIC
mdefine_line|#define EF_MIPS_PIC&t;&t;0x00000002
multiline_comment|/* Code in file uses the standard calling sequence for calling&n;   position independent code.  */
DECL|macro|EF_MIPS_CPIC
mdefine_line|#define EF_MIPS_CPIC&t;&t;0x00000004
multiline_comment|/* Four bit MIPS architecture field.  */
DECL|macro|EF_MIPS_ARCH
mdefine_line|#define EF_MIPS_ARCH&t;&t;0xf0000000
multiline_comment|/* -mips1 code.  */
DECL|macro|E_MIPS_ARCH_1
mdefine_line|#define E_MIPS_ARCH_1&t;&t;0x00000000
multiline_comment|/* -mips2 code.  */
DECL|macro|E_MIPS_ARCH_2
mdefine_line|#define E_MIPS_ARCH_2&t;&t;0x10000000
multiline_comment|/* -mips3 code.  */
DECL|macro|E_MIPS_ARCH_3
mdefine_line|#define E_MIPS_ARCH_3&t;&t;0x20000000
"&f;"
multiline_comment|/* Processor specific section indices.  These sections do not actually&n;   exist.  Symbols with a st_shndx field corresponding to one of these&n;   values have a special meaning.  */
multiline_comment|/* Defined and allocated common symbol.  Value is virtual address.  If&n;   relocated, alignment must be preserved.  */
DECL|macro|SHN_MIPS_ACOMMON
mdefine_line|#define SHN_MIPS_ACOMMON&t;0xff00
multiline_comment|/* Defined and allocated text symbol.  Value is virtual address.&n;   Occur in the dynamic symbol table of Alpha OSF/1 and Irix 5 executables.  */
DECL|macro|SHN_MIPS_TEXT
mdefine_line|#define SHN_MIPS_TEXT&t;&t;0xff01
multiline_comment|/* Defined and allocated data symbol.  Value is virtual address.&n;   Occur in the dynamic symbol table of Alpha OSF/1 and Irix 5 executables.  */
DECL|macro|SHN_MIPS_DATA
mdefine_line|#define SHN_MIPS_DATA&t;&t;0xff02
multiline_comment|/* Small common symbol.  */
DECL|macro|SHN_MIPS_SCOMMON
mdefine_line|#define SHN_MIPS_SCOMMON&t;0xff03
multiline_comment|/* Small undefined symbol.  */
DECL|macro|SHN_MIPS_SUNDEFINED
mdefine_line|#define SHN_MIPS_SUNDEFINED&t;0xff04
"&f;"
multiline_comment|/* Processor specific section types.  */
multiline_comment|/* Section contains the set of dynamic shared objects used when&n;   statically linking.  */
DECL|macro|SHT_MIPS_LIBLIST
mdefine_line|#define SHT_MIPS_LIBLIST&t;0x70000000
multiline_comment|/* I&squot;m not sure what this is, but it&squot;s used on Irix 5.  */
DECL|macro|SHT_MIPS_MSYM
mdefine_line|#define SHT_MIPS_MSYM&t;&t;0x70000001
multiline_comment|/* Section contains list of symbols whose definitions conflict with&n;   symbols defined in shared objects.  */
DECL|macro|SHT_MIPS_CONFLICT
mdefine_line|#define SHT_MIPS_CONFLICT&t;0x70000002
multiline_comment|/* Section contains the global pointer table.  */
DECL|macro|SHT_MIPS_GPTAB
mdefine_line|#define SHT_MIPS_GPTAB&t;&t;0x70000003
multiline_comment|/* Section contains microcode information.  The exact format is&n;   unspecified.  */
DECL|macro|SHT_MIPS_UCODE
mdefine_line|#define SHT_MIPS_UCODE&t;&t;0x70000004
multiline_comment|/* Section contains some sort of debugging information.  The exact&n;   format is unspecified.  It&squot;s probably ECOFF symbols.  */
DECL|macro|SHT_MIPS_DEBUG
mdefine_line|#define SHT_MIPS_DEBUG&t;&t;0x70000005
multiline_comment|/* Section contains register usage information.  */
DECL|macro|SHT_MIPS_REGINFO
mdefine_line|#define SHT_MIPS_REGINFO&t;0x70000006
multiline_comment|/* Section contains miscellaneous options (used on Irix).  */
DECL|macro|SHT_MIPS_OPTIONS
mdefine_line|#define SHT_MIPS_OPTIONS&t;0x7000000d
multiline_comment|/* DWARF debugging section (used on Irix 6).  */
DECL|macro|SHT_MIPS_DWARF
mdefine_line|#define SHT_MIPS_DWARF&t;&t;0x7000001e
multiline_comment|/* Events section.  This appears on Irix 6.  I don&squot;t know what it&n;   means.  */
DECL|macro|SHT_MIPS_EVENTS
mdefine_line|#define SHT_MIPS_EVENTS&t;&t;0x70000021
multiline_comment|/* A section of type SHT_MIPS_LIBLIST contains an array of the&n;   following structure.  The sh_link field is the section index of the&n;   string table.  The sh_info field is the number of entries in the&n;   section.  */
r_typedef
r_struct
(brace
multiline_comment|/* String table index for name of shared object.  */
DECL|member|l_name
r_int
r_int
id|l_name
suffix:semicolon
multiline_comment|/* Time stamp.  */
DECL|member|l_time_stamp
r_int
r_int
id|l_time_stamp
suffix:semicolon
multiline_comment|/* Checksum of symbol names and common sizes.  */
DECL|member|l_checksum
r_int
r_int
id|l_checksum
suffix:semicolon
multiline_comment|/* String table index for version.  */
DECL|member|l_version
r_int
r_int
id|l_version
suffix:semicolon
multiline_comment|/* Flags.  */
DECL|member|l_flags
r_int
r_int
id|l_flags
suffix:semicolon
DECL|typedef|Elf32_Lib
)brace
id|Elf32_Lib
suffix:semicolon
multiline_comment|/* The l_flags field of an Elf32_Lib structure may contain the&n;   following flags.  */
multiline_comment|/* Require an exact match at runtime.  */
DECL|macro|LL_EXACT_MATCH
mdefine_line|#define LL_EXACT_MATCH&t;&t;0x00000001
multiline_comment|/* Ignore version incompatibilities at runtime.  */
DECL|macro|LL_IGNORE_INT_VER
mdefine_line|#define LL_IGNORE_INT_VER&t;0x00000002
multiline_comment|/* A section of type SHT_MIPS_CONFLICT is an array of indices into the&n;   .dynsym section.  Each element has the following type.  */
DECL|typedef|Elf32_Conflict
r_typedef
r_int
r_int
id|Elf32_Conflict
suffix:semicolon
multiline_comment|/* A section of type SHT_MIPS_GPTAB contains information about how&n;   much GP space would be required for different -G arguments.  This&n;   information is only used so that the linker can provide informative&n;   suggestions as to the best -G value to use.  The sh_info field is&n;   the index of the section for which this information applies.  The&n;   contents of the section are an array of the following union.  The&n;   first element uses the gt_header field.  The remaining elements use&n;   the gt_entry field.  */
r_typedef
r_union
(brace
r_struct
(brace
multiline_comment|/* -G value actually used for this object file.  */
DECL|member|gt_current_g_value
r_int
r_int
id|gt_current_g_value
suffix:semicolon
multiline_comment|/* Unused.  */
DECL|member|gt_unused
r_int
r_int
id|gt_unused
suffix:semicolon
DECL|member|gt_header
)brace
id|gt_header
suffix:semicolon
r_struct
(brace
multiline_comment|/* If this -G argument has been used...  */
DECL|member|gt_g_value
r_int
r_int
id|gt_g_value
suffix:semicolon
multiline_comment|/* ...this many GP section bytes would be required.  */
DECL|member|gt_bytes
r_int
r_int
id|gt_bytes
suffix:semicolon
DECL|member|gt_entry
)brace
id|gt_entry
suffix:semicolon
DECL|typedef|Elf32_gptab
)brace
id|Elf32_gptab
suffix:semicolon
multiline_comment|/* The external version of Elf32_gptab.  */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|gt_current_g_value
r_int
r_char
id|gt_current_g_value
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|gt_unused
r_int
r_char
id|gt_unused
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|gt_header
)brace
id|gt_header
suffix:semicolon
r_struct
(brace
DECL|member|gt_g_value
r_int
r_char
id|gt_g_value
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|gt_bytes
r_int
r_char
id|gt_bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|gt_entry
)brace
id|gt_entry
suffix:semicolon
DECL|typedef|Elf32_External_gptab
)brace
id|Elf32_External_gptab
suffix:semicolon
multiline_comment|/* A section of type SHT_MIPS_REGINFO contains the following&n;   structure.  */
r_typedef
r_struct
(brace
multiline_comment|/* Mask of general purpose registers used.  */
DECL|member|ri_gprmask
r_int
r_int
id|ri_gprmask
suffix:semicolon
multiline_comment|/* Mask of co-processor registers used.  */
DECL|member|ri_cprmask
r_int
r_int
id|ri_cprmask
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* GP register value for this object file.  */
DECL|member|ri_gp_value
r_int
id|ri_gp_value
suffix:semicolon
DECL|typedef|Elf32_RegInfo
)brace
id|Elf32_RegInfo
suffix:semicolon
multiline_comment|/* The external version of the Elf_RegInfo structure.  */
r_typedef
r_struct
(brace
DECL|member|ri_gprmask
r_int
r_char
id|ri_gprmask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ri_cprmask
r_int
r_char
id|ri_cprmask
(braket
l_int|4
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ri_gp_value
r_int
r_char
id|ri_gp_value
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|Elf32_External_RegInfo
)brace
id|Elf32_External_RegInfo
suffix:semicolon
multiline_comment|/* MIPS ELF .reginfo swapping routines.  */
r_extern
r_void
id|bfd_mips_elf32_swap_reginfo_in
id|PARAMS
(paren
(paren
id|bfd
op_star
comma
r_const
id|Elf32_External_RegInfo
op_star
comma
id|Elf32_RegInfo
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|bfd_mips_elf32_swap_reginfo_out
id|PARAMS
(paren
(paren
id|bfd
op_star
comma
r_const
id|Elf32_RegInfo
op_star
comma
id|Elf32_External_RegInfo
op_star
)paren
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Processor specific section flags.  */
multiline_comment|/* This section must be in the global data area.  */
DECL|macro|SHF_MIPS_GPREL
mdefine_line|#define SHF_MIPS_GPREL&t;&t;0x10000000
"&f;"
multiline_comment|/* Processor specific program header types.  */
multiline_comment|/* Register usage information.  Identifies one .reginfo section.  */
DECL|macro|PT_MIPS_REGINFO
mdefine_line|#define PT_MIPS_REGINFO&t;&t;0x70000000
"&f;"
multiline_comment|/* Processor specific dynamic array tags.  */
multiline_comment|/* 32 bit version number for runtime linker interface.  */
DECL|macro|DT_MIPS_RLD_VERSION
mdefine_line|#define DT_MIPS_RLD_VERSION&t;0x70000001
multiline_comment|/* Time stamp.  */
DECL|macro|DT_MIPS_TIME_STAMP
mdefine_line|#define DT_MIPS_TIME_STAMP&t;0x70000002
multiline_comment|/* Checksum of external strings and common sizes.  */
DECL|macro|DT_MIPS_ICHECKSUM
mdefine_line|#define DT_MIPS_ICHECKSUM&t;0x70000003
multiline_comment|/* Index of version string in string table.  */
DECL|macro|DT_MIPS_IVERSION
mdefine_line|#define DT_MIPS_IVERSION&t;0x70000004
multiline_comment|/* 32 bits of flags.  */
DECL|macro|DT_MIPS_FLAGS
mdefine_line|#define DT_MIPS_FLAGS&t;&t;0x70000005
multiline_comment|/* Base address of the segment.  */
DECL|macro|DT_MIPS_BASE_ADDRESS
mdefine_line|#define DT_MIPS_BASE_ADDRESS&t;0x70000006
multiline_comment|/* Address of .conflict section.  */
DECL|macro|DT_MIPS_CONFLICT
mdefine_line|#define DT_MIPS_CONFLICT&t;0x70000008
multiline_comment|/* Address of .liblist section.  */
DECL|macro|DT_MIPS_LIBLIST
mdefine_line|#define DT_MIPS_LIBLIST&t;&t;0x70000009
multiline_comment|/* Number of local global offset table entries.  */
DECL|macro|DT_MIPS_LOCAL_GOTNO
mdefine_line|#define DT_MIPS_LOCAL_GOTNO&t;0x7000000a
multiline_comment|/* Number of entries in the .conflict section.  */
DECL|macro|DT_MIPS_CONFLICTNO
mdefine_line|#define DT_MIPS_CONFLICTNO&t;0x7000000b
multiline_comment|/* Number of entries in the .liblist section.  */
DECL|macro|DT_MIPS_LIBLISTNO
mdefine_line|#define DT_MIPS_LIBLISTNO&t;0x70000010
multiline_comment|/* Number of entries in the .dynsym section.  */
DECL|macro|DT_MIPS_SYMTABNO
mdefine_line|#define DT_MIPS_SYMTABNO&t;0x70000011
multiline_comment|/* Index of first external dynamic symbol not referenced locally.  */
DECL|macro|DT_MIPS_UNREFEXTNO
mdefine_line|#define DT_MIPS_UNREFEXTNO&t;0x70000012
multiline_comment|/* Index of first dynamic symbol in global offset table.  */
DECL|macro|DT_MIPS_GOTSYM
mdefine_line|#define DT_MIPS_GOTSYM&t;&t;0x70000013
multiline_comment|/* Number of page table entries in global offset table.  */
DECL|macro|DT_MIPS_HIPAGENO
mdefine_line|#define DT_MIPS_HIPAGENO&t;0x70000014
multiline_comment|/* Address of run time loader map, used for debugging.  */
DECL|macro|DT_MIPS_RLD_MAP
mdefine_line|#define DT_MIPS_RLD_MAP&t;&t;0x70000016
eof
