multiline_comment|/*&n; * include/asm-mips/mipsconfig.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MIPSCONFIG_H
DECL|macro|__ASM_MIPS_MIPSCONFIG_H
mdefine_line|#define __ASM_MIPS_MIPSCONFIG_H
multiline_comment|/*&n; * This is the virtual address to which all ports are being mapped.&n; * Must be a value that can be load with a lui instruction.&n; */
macro_line|#ifndef PORT_BASE
macro_line|#if !defined (__LANGUAGE_ASSEMBLY__)
r_extern
r_int
r_int
id|port_base
suffix:semicolon
macro_line|#endif
DECL|macro|PORT_BASE
mdefine_line|#define PORT_BASE port_base
macro_line|#endif
multiline_comment|/* Pgdir is 1 page mapped at 0xff800000. */
DECL|macro|TLBMAP
mdefine_line|#define TLBMAP&t;&t;&t;0xff800000
multiline_comment|/* The virtual address where we&squot;ll map the pgdir. */
DECL|macro|TLB_ROOT
mdefine_line|#define TLB_ROOT&t;&t;0xff000000
macro_line|#endif /* __ASM_MIPS_MIPSCONFIG_H */
eof
