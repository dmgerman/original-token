multiline_comment|/*&n; * linux/include/asm-mips/mipsconfig.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 by Waldorf Electronics&n; * written by Ralf Baechle&n; *&n; */
macro_line|#ifndef __ASM_MIPS_MIPS_CONFIG_H
DECL|macro|__ASM_MIPS_MIPS_CONFIG_H
mdefine_line|#define __ASM_MIPS_MIPS_CONFIG_H
multiline_comment|/*&n; * This is the virtual adress to which all ports are being mapped.&n; * Must be a value that can be load with a lui instruction.&n; */
DECL|macro|PORT_BASE
mdefine_line|#define PORT_BASE&t;&t;0xe0000000
multiline_comment|/* #define NUMBER_OF_TLB_ENTRIES&t;48  */
multiline_comment|/* see bootinfo.h -- Andy */
DECL|macro|NUMBER_OF_TLB_ENTRIES
mdefine_line|#define NUMBER_OF_TLB_ENTRIES&t;48
multiline_comment|/*&n; * Pagetables are 4MB mapped at 0xe3000000&n; * Must be a value that can be load with a lui instruction.&n; */
DECL|macro|TLBMAP
mdefine_line|#define TLBMAP&t;&t;&t;0xe4000000
multiline_comment|/*&n; * The virtual address where we&squot;ll map the pagetables&n; * For a base address of 0xe3000000 this is 0xe338c000&n; * For a base address of 0xe4000000 this is 0xe4390000&n; * FIXME: Gas misscomputes the following expression!&n;#define TLB_ROOT&t;&t;(TLBMAP + (TLBMAP &gt;&gt; (12-2)))&n; */
DECL|macro|TLB_ROOT
mdefine_line|#define TLB_ROOT&t;&t;0xe4390000
multiline_comment|/*&n; * This ASID is reserved for the swapper&n; */
DECL|macro|SWAPPER_ASID
mdefine_line|#define SWAPPER_ASID&t;&t;0
macro_line|#endif /* __ASM_MIPS_MIPS_CONFIG_H */
eof
