multiline_comment|/*&n; * include/asm-mips/mipsregs.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_MIPS_MIPSREGS_H_
DECL|macro|_ASM_MIPS_MIPSREGS_H_
mdefine_line|#define _ASM_MIPS_MIPSREGS_H_
multiline_comment|/*&n; * The following macros are especially useful for __asm__&n; * inline assembler.&n; */
macro_line|#ifndef __STR
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#endif
macro_line|#ifndef STR
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#endif
multiline_comment|/*&n; * Coprocessor 0 register names&n; */
DECL|macro|CP0_INDEX
mdefine_line|#define CP0_INDEX $0
DECL|macro|CP0_RANDOM
mdefine_line|#define CP0_RANDOM $1
DECL|macro|CP0_ENTRYLO0
mdefine_line|#define CP0_ENTRYLO0 $2
DECL|macro|CP0_ENTRYLO1
mdefine_line|#define CP0_ENTRYLO1 $3
DECL|macro|CP0_CONTEXT
mdefine_line|#define CP0_CONTEXT $4
DECL|macro|CP0_PAGEMASK
mdefine_line|#define CP0_PAGEMASK $5
DECL|macro|CP0_WIRED
mdefine_line|#define CP0_WIRED $6
DECL|macro|CP0_BADVADDR
mdefine_line|#define CP0_BADVADDR $8
DECL|macro|CP0_COUNT
mdefine_line|#define CP0_COUNT $9
DECL|macro|CP0_ENTRYHI
mdefine_line|#define CP0_ENTRYHI $10
DECL|macro|CP0_COMPARE
mdefine_line|#define CP0_COMPARE $11
DECL|macro|CP0_STATUS
mdefine_line|#define CP0_STATUS $12
DECL|macro|CP0_CAUSE
mdefine_line|#define CP0_CAUSE $13
DECL|macro|CP0_EPC
mdefine_line|#define CP0_EPC $14
DECL|macro|CP0_PRID
mdefine_line|#define CP0_PRID $15
DECL|macro|CP0_CONFIG
mdefine_line|#define CP0_CONFIG $16
DECL|macro|CP0_LLADDR
mdefine_line|#define CP0_LLADDR $17
DECL|macro|CP0_WATCHLO
mdefine_line|#define CP0_WATCHLO $18
DECL|macro|CP0_WATCHHI
mdefine_line|#define CP0_WATCHHI $19
DECL|macro|CP0_XCONTEXT
mdefine_line|#define CP0_XCONTEXT $20
DECL|macro|CP0_ECC
mdefine_line|#define CP0_ECC $26
DECL|macro|CP0_CACHEERR
mdefine_line|#define CP0_CACHEERR $27
DECL|macro|CP0_TAGLO
mdefine_line|#define CP0_TAGLO $28
DECL|macro|CP0_TAGHI
mdefine_line|#define CP0_TAGHI $29
DECL|macro|CP0_ERROREPC
mdefine_line|#define CP0_ERROREPC $30
multiline_comment|/*&n; * Values for pagemask register&n; */
DECL|macro|PM_4K
mdefine_line|#define PM_4K   0x000000000
DECL|macro|PM_16K
mdefine_line|#define PM_16K  0x000060000
DECL|macro|PM_64K
mdefine_line|#define PM_64K  0x0001e0000
DECL|macro|PM_256K
mdefine_line|#define PM_256K 0x0007e0000
DECL|macro|PM_1M
mdefine_line|#define PM_1M   0x001fe0000
DECL|macro|PM_4M
mdefine_line|#define PM_4M   0x007fe0000
DECL|macro|PM_16M
mdefine_line|#define PM_16M  0x01ffe0000
multiline_comment|/*&n; * Values used for computation of new tlb entries&n; */
DECL|macro|PL_4K
mdefine_line|#define PL_4K   12
DECL|macro|PL_16K
mdefine_line|#define PL_16K  14
DECL|macro|PL_64K
mdefine_line|#define PL_64K  16
DECL|macro|PL_256K
mdefine_line|#define PL_256K 18
DECL|macro|PL_1M
mdefine_line|#define PL_1M   20
DECL|macro|PL_4M
mdefine_line|#define PL_4M   22
DECL|macro|PL_16M
mdefine_line|#define PL_16M  24
multiline_comment|/*&n; * Compute a vpn/pfn entry for EntryHi register&n; */
DECL|macro|VPN
mdefine_line|#define VPN(addr,pagesizeshift) ((addr) &amp; ~((1 &lt;&lt; (pagesizeshift))-1))
DECL|macro|PFN
mdefine_line|#define PFN(addr,pagesizeshift) (((addr) &amp; ((1 &lt;&lt; (pagesizeshift))-1)) &lt;&lt; 6)
macro_line|#endif /* _ASM_MIPS_MIPSREGS_H_ */
eof
