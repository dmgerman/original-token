multiline_comment|/*&n; * include/asm-mips/mipsregs.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MIPSREGS_H
DECL|macro|__ASM_MIPS_MIPSREGS_H
mdefine_line|#define __ASM_MIPS_MIPSREGS_H
multiline_comment|/*&n; * The following macros are especially useful for __asm__&n; * inline assembler.&n; */
macro_line|#ifndef __STR
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#endif
macro_line|#ifndef STR
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#endif
multiline_comment|/*&n; * On the R2000/3000 load instructions are not interlocked -&n; * we therefore sometimes need to fill load delay slots with a nop&n; * which are useless for &gt;=R4000.&n; *&n; * FIXME: Don&squot;t know about R6000&n; */
macro_line|#if !defined (__R4000__)
DECL|macro|FILL_LDS
mdefine_line|#define FILL_LDS nop
macro_line|#else
DECL|macro|FILL_LDS
mdefine_line|#define FILL_LDS
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
multiline_comment|/*&n; * Values for PageMask register&n; */
DECL|macro|PM_4K
mdefine_line|#define PM_4K   0x00000000
DECL|macro|PM_16K
mdefine_line|#define PM_16K  0x00006000
DECL|macro|PM_64K
mdefine_line|#define PM_64K  0x0001e000
DECL|macro|PM_256K
mdefine_line|#define PM_256K 0x0007e000
DECL|macro|PM_1M
mdefine_line|#define PM_1M   0x001fe000
DECL|macro|PM_4M
mdefine_line|#define PM_4M   0x007fe000
DECL|macro|PM_16M
mdefine_line|#define PM_16M  0x01ffe000
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
multiline_comment|/*&n; * Macros to access the system control copprocessor&n; */
DECL|macro|read_32bit_cp0_register
mdefine_line|#define read_32bit_cp0_register(source)                                        &bslash;&n;({ int __res;                                                                  &bslash;&n;        __asm__ __volatile__(                                                  &bslash;&n;        &quot;mfc0&bslash;t%0,&quot;STR(source)                                                 &bslash;&n;        : &quot;=r&quot; (__res));                                                       &bslash;&n;        __res;})
DECL|macro|read_64bit_cp0_register
mdefine_line|#define read_64bit_cp0_register(source)                                        &bslash;&n;({ int __res;                                                                  &bslash;&n;        __asm__ __volatile__(                                                  &bslash;&n;        &quot;dmfc0&bslash;t%0,&quot;STR(source)                                                &bslash;&n;        : &quot;=r&quot; (__res));                                                       &bslash;&n;        __res;})
DECL|macro|write_32bit_cp0_register
mdefine_line|#define write_32bit_cp0_register(register,value)                               &bslash;&n;        __asm__ __volatile__(                                                  &bslash;&n;        &quot;mtc0&bslash;t%0,&quot;STR(register)                                               &bslash;&n;        : : &quot;r&quot; (value));
multiline_comment|/*&n; * Inline code for use of the ll and sc instructions&n; *&n; * FIXME: This instruction is only available on MIPS ISA &gt;=3.&n; * Since these operations are only being used for atomic operations&n; * the easiest workaround for the R[23]00 is to disable interrupts.&n; */
DECL|macro|load_linked
mdefine_line|#define load_linked(addr)                                                      &bslash;&n;({                                                                             &bslash;&n;&t;unsigned int __res;                                                    &bslash;&n;                                                                               &bslash;&n;&t;__asm__ __volatile__(                                                  &bslash;&n;&t;&quot;ll&bslash;t%0,(%1)&quot;                                                          &bslash;&n;&t;: &quot;=r&quot; (__res)                                                         &bslash;&n;&t;: &quot;r&quot; ((unsigned int) (addr)));                                        &bslash;&n;                                                                               &bslash;&n;&t;__res;                                                                 &bslash;&n;})
DECL|macro|store_conditional
mdefine_line|#define store_conditional(addr,value)                                          &bslash;&n;({                                                                             &bslash;&n;&t;int&t;__res;                                                         &bslash;&n;                                                                               &bslash;&n;&t;__asm__ __volatile__(                                                  &bslash;&n;&t;&quot;sc&bslash;t%0,(%2)&quot;                                                          &bslash;&n;&t;: &quot;=r&quot; (__res)                                                         &bslash;&n;&t;: &quot;0&quot; (value), &quot;r&quot; (addr));                                            &bslash;&n;                                                                               &bslash;&n;&t;__res;                                                                 &bslash;&n;})
multiline_comment|/*&n; * Bitfields in the cp0 status register&n; *&n; * Refer to MIPS R4600 manual, page 5-4 for explanation&n; */
DECL|macro|ST0_IE
mdefine_line|#define ST0_IE  (1   &lt;&lt;  0)
DECL|macro|ST0_EXL
mdefine_line|#define ST0_EXL (1   &lt;&lt;  1)
DECL|macro|ST0_ERL
mdefine_line|#define ST0_ERL (1   &lt;&lt;  2)
DECL|macro|ST0_KSU
mdefine_line|#define ST0_KSU (3   &lt;&lt;  3)
DECL|macro|ST0_UX
mdefine_line|#define ST0_UX  (1   &lt;&lt;  5)
DECL|macro|ST0_SX
mdefine_line|#define ST0_SX  (1   &lt;&lt;  6)
DECL|macro|ST0_KX
mdefine_line|#define ST0_KX  (1   &lt;&lt;  7)
DECL|macro|ST0_IM
mdefine_line|#define ST0_IM  (255 &lt;&lt;  8)
DECL|macro|ST0_DE
mdefine_line|#define ST0_DE  (1   &lt;&lt; 16)
DECL|macro|ST0_CE
mdefine_line|#define ST0_CE  (1   &lt;&lt; 17)
DECL|macro|ST0_CH
mdefine_line|#define ST0_CH  (1   &lt;&lt; 18)
DECL|macro|ST0_SR
mdefine_line|#define ST0_SR  (1   &lt;&lt; 20)
DECL|macro|ST0_BEV
mdefine_line|#define ST0_BEV (1   &lt;&lt; 22)
DECL|macro|ST0_RE
mdefine_line|#define ST0_RE  (1   &lt;&lt; 25)
DECL|macro|ST0_FR
mdefine_line|#define ST0_FR  (1   &lt;&lt; 26)
DECL|macro|ST0_CU
mdefine_line|#define ST0_CU  (15  &lt;&lt; 28)
DECL|macro|ST0_CU0
mdefine_line|#define ST0_CU0 (1   &lt;&lt; 28)
DECL|macro|ST0_CU1
mdefine_line|#define ST0_CU1 (1   &lt;&lt; 29)
DECL|macro|ST0_CU2
mdefine_line|#define ST0_CU2 (1   &lt;&lt; 30)
DECL|macro|ST0_CU3
mdefine_line|#define ST0_CU3 (1   &lt;&lt; 31)
macro_line|#endif /* __ASM_MIPS_MIPSREGS_H */
eof
