multiline_comment|/* ross.h: Ross module specific definitions and defines.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ROSS_H
DECL|macro|_SPARC_ROSS_H
mdefine_line|#define _SPARC_ROSS_H
multiline_comment|/* Ross made Hypersparcs have a %psr &squot;impl&squot; field of &squot;0001&squot;.  The &squot;vers&squot;&n; * field has &squot;1111&squot;.&n; */
multiline_comment|/* The MMU control register fields on the HyperSparc.&n; *&n; * -----------------------------------------------------------------&n; * |implvers| RSV |CWR|SE|WBE| MID |BM| C|CS|MR|CM|RSV|CE|RSV|NF|ME|&n; * -----------------------------------------------------------------&n; *  31    24 23-22 21  20  19 18-15 14 13 12 11 10  9   8 7-2  1  0&n; *&n; * Phew, lots of fields there ;-)&n; *&n; * CWR: Cache Wrapping Enabled, if one cache wrapping is on.&n; * SE: Snoop Enable, turns on bus snooping for cache activity if one.&n; * WBE: Write Buffer Enable, one turns it on.&n; * MID: The ModuleID of the chip for MBus transactions.&n; * BM: Boot-Mode. One indicates the MMU is in boot mode.&n; * C: Indicates whether accesses are cachable while the MMU is&n; *    disabled.&n; * CS: Cache Size -- 0 = 128k, 1 = 256k&n; * MR: Memory Reflection, one indicates that the memory bus connected&n; *     to the MBus supports memory reflection.&n; * CM: Cache Mode -- 0 = write-through, 1 = copy-back&n; * CE: Cache Enable -- 0 = no caching, 1 = cache is on&n; * NF: No Fault -- 0 = faults trap the CPU from supervisor mode&n; *                 1 = faults from supervisor mode do not generate traps&n; * ME: MMU Enable -- 0 = MMU is off, 1 = MMU is on&n; */
DECL|macro|HYPERSPARC_CWENABLE
mdefine_line|#define HYPERSPARC_CWENABLE   0x00200000
DECL|macro|HYPERSPARC_SBENABLE
mdefine_line|#define HYPERSPARC_SBENABLE   0x00100000
DECL|macro|HYPERSPARC_WBENABLE
mdefine_line|#define HYPERSPARC_WBENABLE   0x00080000
DECL|macro|HYPERSPARC_MIDMASK
mdefine_line|#define HYPERSPARC_MIDMASK    0x00078000
DECL|macro|HYPERSPARC_BMODE
mdefine_line|#define HYPERSPARC_BMODE      0x00004000
DECL|macro|HYPERSPARC_ACENABLE
mdefine_line|#define HYPERSPARC_ACENABLE   0x00002000
DECL|macro|HYPERSPARC_CSIZE
mdefine_line|#define HYPERSPARC_CSIZE      0x00001000
DECL|macro|HYPERSPARC_MRFLCT
mdefine_line|#define HYPERSPARC_MRFLCT     0x00000800
DECL|macro|HYPERSPARC_CMODE
mdefine_line|#define HYPERSPARC_CMODE      0x00000400
DECL|macro|HYPERSPARC_CENABLE
mdefine_line|#define HYPERSPARC_CENABLE    0x00000100
DECL|macro|HYPERSPARC_NFAULT
mdefine_line|#define HYPERSPARC_NFAULT     0x00000002
DECL|macro|HYPERSPARC_MENABLE
mdefine_line|#define HYPERSPARC_MENABLE    0x00000001
multiline_comment|/* Flushes which clear out only the on-chip Ross HyperSparc ICACHE. */
DECL|function|flush_i_page
r_extern
r_inline
r_void
id|flush_i_page
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
id|ASI_M_IFLUSH_PAGE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_i_seg
r_extern
r_inline
r_void
id|flush_i_seg
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
id|ASI_M_IFLUSH_SEG
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_i_region
r_extern
r_inline
r_void
id|flush_i_region
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
id|ASI_M_IFLUSH_REGION
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_i_ctx
r_extern
r_inline
r_void
id|flush_i_ctx
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
id|ASI_M_IFLUSH_CTX
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_i_user
r_extern
r_inline
r_void
id|flush_i_user
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
id|ASI_M_IFLUSH_USER
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Finally, flush the entire ICACHE. */
DECL|function|flush_whole_icache
r_extern
r_inline
r_void
id|flush_whole_icache
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%%g0] %0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_IWHOLE
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The ICCR instruction cache register on the HyperSparc.&n; *&n; * -----------------------------------------------&n; * |                                 | FTD | IDC |&n; * -----------------------------------------------&n; *  31                                  1     0&n; *&n; * This register is accessed using the V8 &squot;wrasr&squot; and &squot;rdasr&squot;&n; * opcodes, since not all assemblers understand them and those&n; * that do use different semantics I will just hard code the&n; * instruction with a &squot;.word&squot; statement.&n; *&n; * FTD:  If set to one flush instructions executed during an&n; *       instruction cache hit occurs, the corresponding line&n; *       for said cache-hit is invalidated.  If FTD is zero,&n; *       an unimplemented &squot;flush&squot; trap will occur when any&n; *       flush is executed by the processor.&n; *&n; * ICE:  If set to one, the instruction cache is enabled.  If&n; *       zero, the cache will not be used for instruction fetches.&n; *&n; * All other bits are read as zeros, and writes to them have no&n; * effect.&n; */
DECL|function|get_ross_icr
r_extern
r_inline
r_int
r_int
id|get_ross_icr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|icreg
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.word 0xbf402000&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* rd %iccr, %g1 */
l_string|&quot;=r&quot;
(paren
id|icreg
)paren
suffix:colon
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|icreg
suffix:semicolon
)brace
DECL|function|put_ross_icr
r_extern
r_inline
r_void
id|put_ross_icr
c_func
(paren
r_int
r_int
id|icreg
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %%g0, %0, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;.word 0xbf802000&bslash;n&bslash;t&quot;
multiline_comment|/* wr %g1, 0x0, %iccr */
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|icreg
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_ROSS_H) */
eof
