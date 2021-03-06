multiline_comment|/* $Id: turbosparc.h,v 1.4 1998/08/16 16:02:42 ecd Exp $&n; * turbosparc.h:  Defines specific to the TurboSparc module.&n; *            This is SRMMU stuff.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC_TURBOSPARC_H
DECL|macro|_SPARC_TURBOSPARC_H
mdefine_line|#define _SPARC_TURBOSPARC_H
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/pgtsrmmu.h&gt;
multiline_comment|/* Bits in the SRMMU control register for TurboSparc modules.&n; *&n; * -------------------------------------------------------------------&n; * |impl-vers| RSV| PMC |PE|PC| RSV |BM| RFR |IC|DC|PSO|RSV|ICS|NF|ME|&n; * -------------------------------------------------------------------&n; *  31    24 23-21 20-19 18 17 16-15 14 13-10  9  8  7  6-3   2  1  0&n; *&n; * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode&n; *&n; * This indicates whether the TurboSparc is in boot-mode or not.&n; *&n; * IC: Instruction Cache -- 0 = off, 1 = on&n; * DC: Data Cache -- 0 = off, 1 = 0n&n; *&n; * These bits enable the on-cpu TurboSparc split I/D caches.&n; *&n; * ICS: ICache Snooping -- 0 = disable, 1 = enable snooping of icache&n; * NF: No Fault -- 0 = faults generate traps, 1 = faults don&squot;t trap&n; * ME: MMU enable -- 0 = mmu not translating, 1 = mmu translating&n; *&n; */
DECL|macro|TURBOSPARC_MMUENABLE
mdefine_line|#define TURBOSPARC_MMUENABLE    0x00000001
DECL|macro|TURBOSPARC_NOFAULT
mdefine_line|#define TURBOSPARC_NOFAULT      0x00000002
DECL|macro|TURBOSPARC_ICSNOOP
mdefine_line|#define TURBOSPARC_ICSNOOP&t;0x00000004
DECL|macro|TURBOSPARC_PSO
mdefine_line|#define TURBOSPARC_PSO          0x00000080
DECL|macro|TURBOSPARC_DCENABLE
mdefine_line|#define TURBOSPARC_DCENABLE     0x00000100   /* Enable data cache */
DECL|macro|TURBOSPARC_ICENABLE
mdefine_line|#define TURBOSPARC_ICENABLE     0x00000200   /* Enable instruction cache */
DECL|macro|TURBOSPARC_BMODE
mdefine_line|#define TURBOSPARC_BMODE        0x00004000   
DECL|macro|TURBOSPARC_PARITYODD
mdefine_line|#define TURBOSPARC_PARITYODD&t;0x00020000   /* Parity odd, if enabled */
DECL|macro|TURBOSPARC_PCENABLE
mdefine_line|#define TURBOSPARC_PCENABLE&t;0x00040000   /* Enable parity checking */
multiline_comment|/* Bits in the CPU configuration register for TurboSparc modules.&n; *&n; * -------------------------------------------------------&n; * |IOClk|SNP|AXClk| RAH |  WS |  RSV  |SBC|WT|uS2|SE|SCC|&n; * -------------------------------------------------------&n; *    31   30 29-28 27-26 25-23   22-8  7-6  5  4   3 2-0&n; *&n; */
DECL|macro|TURBOSPARC_SCENABLE
mdefine_line|#define TURBOSPARC_SCENABLE 0x00000008&t; /* Secondary cache enable */
DECL|macro|TURBOSPARC_uS2
mdefine_line|#define TURBOSPARC_uS2&t;    0x00000010   /* Swift compatibility mode */
DECL|macro|TURBOSPARC_WTENABLE
mdefine_line|#define TURBOSPARC_WTENABLE 0x00000020&t; /* Write thru for dcache */
DECL|macro|TURBOSPARC_SNENABLE
mdefine_line|#define TURBOSPARC_SNENABLE 0x40000000&t; /* DVMA snoop enable */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Bits [13:5] select one of 512 instruction cache tags */
DECL|function|turbosparc_inv_insn_tag
r_extern
id|__inline__
r_void
id|turbosparc_inv_insn_tag
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_TAG
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Bits [13:5] select one of 512 data cache tags */
DECL|function|turbosparc_inv_data_tag
r_extern
id|__inline__
r_void
id|turbosparc_inv_data_tag
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_DATAC_TAG
)paren
)paren
suffix:semicolon
)brace
DECL|function|turbosparc_flush_icache
r_extern
id|__inline__
r_void
id|turbosparc_flush_icache
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0
suffix:semicolon
id|addr
OL
l_int|0x4000
suffix:semicolon
id|addr
op_add_assign
l_int|0x20
)paren
(brace
id|turbosparc_inv_insn_tag
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
DECL|function|turbosparc_flush_dcache
r_extern
id|__inline__
r_void
id|turbosparc_flush_dcache
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0
suffix:semicolon
id|addr
OL
l_int|0x4000
suffix:semicolon
id|addr
op_add_assign
l_int|0x20
)paren
(brace
id|turbosparc_inv_data_tag
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
DECL|function|turbosparc_idflash_clear
r_extern
id|__inline__
r_void
id|turbosparc_idflash_clear
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0
suffix:semicolon
id|addr
OL
l_int|0x4000
suffix:semicolon
id|addr
op_add_assign
l_int|0x20
)paren
(brace
id|turbosparc_inv_insn_tag
c_func
(paren
id|addr
)paren
suffix:semicolon
id|turbosparc_inv_data_tag
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
DECL|function|turbosparc_set_ccreg
r_extern
id|__inline__
r_void
id|turbosparc_set_ccreg
c_func
(paren
r_int
r_int
id|regval
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regval
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x600
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
)brace
DECL|function|turbosparc_get_ccreg
r_extern
id|__inline__
r_int
r_int
id|turbosparc_get_ccreg
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|regval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|regval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x600
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|regval
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* !(_SPARC_TURBOSPARC_H) */
eof
