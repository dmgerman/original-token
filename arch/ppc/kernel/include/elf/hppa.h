multiline_comment|/* HPPA ELF support for BFD.&n;   Copyright (C) 1993, 1994 Free Software Foundation, Inc.&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file holds definitions specific to the HPPA ELF ABI.  Note&n;   that most of this is not actually implemented by BFD.  */
multiline_comment|/* Processor specific flags for the ELF header e_flags field.  */
multiline_comment|/* Target processor IDs to be placed in the low 16 bits of the flags&n;   field.  Note these names are shared with SOM, and therefore do not&n;   follow ELF naming conventions.  */
multiline_comment|/* PA 1.0 big endian.  */
macro_line|#ifndef CPU_PA_RISC1_0
DECL|macro|CPU_PA_RISC1_0
mdefine_line|#define CPU_PA_RISC1_0&t;&t;0x0000020b
macro_line|#endif
multiline_comment|/* PA 1.1 big endian.  */
macro_line|#ifndef CPU_PA_RISC1_1
DECL|macro|CPU_PA_RISC1_1
mdefine_line|#define CPU_PA_RISC1_1&t;&t;0x00000210
macro_line|#endif
multiline_comment|/* PA 1.0 little endian (unsupported) is 0x0000028b.  */
multiline_comment|/* PA 1.1 little endian (unsupported) is 0x00000290.  */
multiline_comment|/* Trap null address dereferences.  */
DECL|macro|ELF_PARISC_TRAPNIL
mdefine_line|#define ELF_PARISC_TRAPNIL&t;0x00010000
multiline_comment|/* .PARISC.archext section is present.  */
DECL|macro|EF_PARISC_EXT
mdefine_line|#define EF_PARISC_EXT&t;&t;0x00020000
multiline_comment|/* Processor specific section types.  */
multiline_comment|/* Holds the global offset table, a table of pointers to external&n;   data.  */
DECL|macro|SHT_PARISC_GOT
mdefine_line|#define SHT_PARISC_GOT&t;&t;SHT_LOPROC+0
multiline_comment|/* Nonloadable section containing information in architecture&n;   extensions used by the code.  */
DECL|macro|SHT_PARISC_ARCH
mdefine_line|#define SHT_PARISC_ARCH&t;&t;SHT_LOPROC+1
multiline_comment|/* Section in which $global$ is defined.  */
DECL|macro|SHT_PARISC_GLOBAL
mdefine_line|#define SHT_PARISC_GLOBAL&t;SHT_LOPROC+2
multiline_comment|/* Section holding millicode routines (mul, div, rem, dyncall, etc.  */
DECL|macro|SHT_PARISC_MILLI
mdefine_line|#define SHT_PARISC_MILLI&t;SHT_LOPROC+3
multiline_comment|/* Section holding unwind information for use by debuggers.  */
DECL|macro|SHT_PARISC_UNWIND
mdefine_line|#define SHT_PARISC_UNWIND&t;SHT_LOPROC+4
multiline_comment|/* Section holding the procedure linkage table.  */
DECL|macro|SHT_PARISC_PLT
mdefine_line|#define SHT_PARISC_PLT&t;&t;SHT_LOPROC+5
multiline_comment|/* Short initialized and uninitialized data.  */
DECL|macro|SHT_PARISC_SDATA
mdefine_line|#define SHT_PARISC_SDATA&t;SHT_LOPROC+6
DECL|macro|SHT_PARISC_SBSS
mdefine_line|#define SHT_PARISC_SBSS&t;&t;SHT_LOPROC+7
multiline_comment|/* Optional section holding argument location/relocation info.  */
DECL|macro|SHT_PARISC_SYMEXTN
mdefine_line|#define SHT_PARISC_SYMEXTN&t;SHT_LOPROC+8
multiline_comment|/* Option section for linker stubs.  */
DECL|macro|SHT_PARISC_STUBS
mdefine_line|#define SHT_PARISC_STUBS&t;SHT_LOPROC+9
multiline_comment|/* Processor specific section flags.  */
multiline_comment|/* This section is near the global data pointer and thus allows short&n;   addressing modes to be used.  */
DECL|macro|SHF_PARISC_SHORT
mdefine_line|#define SHF_PARISC_SHORT        0x20000000
multiline_comment|/* Processor specific symbol types.  */
multiline_comment|/* Millicode function entry point.  */
DECL|macro|STT_PARISC_MILLICODE
mdefine_line|#define STT_PARISC_MILLICODE&t;STT_LOPROC+0
eof
