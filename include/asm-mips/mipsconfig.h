multiline_comment|/*&n; * include/asm-mips/mipsconfig.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MIPSCONFIG_H
DECL|macro|__ASM_MIPS_MIPSCONFIG_H
mdefine_line|#define __ASM_MIPS_MIPSCONFIG_H
multiline_comment|/*&n; * This is the virtual address to which all ports are being mapped.&n; * Must be a value that can be load with a lui instruction.&n; */
macro_line|#ifndef PORT_BASE
DECL|macro|PORT_BASE
mdefine_line|#define PORT_BASE&t;&t;0xe2000000
macro_line|#endif
multiline_comment|/*&n; * Pagetables are 4MB mapped at 0xe4000000&n; * Must be a value that can be loaded with a single instruction.&n; */
DECL|macro|TLBMAP
mdefine_line|#define TLBMAP&t;&t;&t;0xe4000000
multiline_comment|/*&n; * The virtual address where we&squot;ll map the pagetables&n; * For a base address of 0xe3000000 this is 0xe338c000&n; * For a base address of 0xe4000000 this is 0xe4390000&n; * FIXME: Gas computes the following expression with signed&n; *        shift and therefore false&n;#define TLB_ROOT&t;&t;(TLBMAP + (TLBMAP &gt;&gt; (12-2)))&n; */
DECL|macro|TLB_ROOT
mdefine_line|#define TLB_ROOT&t;&t;0xe4390000
multiline_comment|/*&n; * Use this to activate extra TLB error checking&n; */
DECL|macro|CONF_DEBUG_TLB
mdefine_line|#define CONF_DEBUG_TLB
multiline_comment|/*&n; * Use this to activate extra TLB profiling code&n; * (currently not implemented)&n; */
DECL|macro|CONF_PROFILE_TLB
macro_line|#undef CONF_PROFILE_TLB
multiline_comment|/*&n; * Disable all caching.  Usefull to find trouble with caches in drivers.&n; */
DECL|macro|CONF_DISABLE_KSEG0_CACHING
macro_line|#undef CONF_DISABLE_KSEG0_CACHING
multiline_comment|/*&n; * Set this to one to enable additional vdma debug code.&n; */
DECL|macro|CONF_DEBUG_VDMA
mdefine_line|#define CONF_DEBUG_VDMA 0
macro_line|#endif /* __ASM_MIPS_MIPSCONFIG_H */
eof
