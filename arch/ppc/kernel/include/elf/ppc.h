multiline_comment|/* MIPS PPC support for BFD.&n;   Copyright (C) 1995 Free Software Foundation, Inc.&n;&n;   By Michael Meissner, Cygnus Support, &lt;meissner@cygnus.com&gt;, from information&n;   in the System V Application Binary Interface, PowerPC Processor Supplement&n;   and the PowerPC Embedded Application Binary Interface (eabi).&n;&n;This file is part of BFD, the Binary File Descriptor library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
multiline_comment|/* This file holds definitions specific to the PPC ELF ABI.  Note&n;   that most of this is not actually implemented by BFD.  */
multiline_comment|/* Processor specific flags for the ELF header e_flags field.  */
DECL|macro|EF_PPC_EMB
mdefine_line|#define&t;EF_PPC_EMB&t;&t;0x80000000&t;/* PowerPC embedded flag  */
multiline_comment|/* CYGNUS local bits below */
DECL|macro|EF_PPC_RELOCATABLE
mdefine_line|#define&t;EF_PPC_RELOCATABLE&t;0x00010000&t;/* PowerPC -mrelocatable flag */
eof
