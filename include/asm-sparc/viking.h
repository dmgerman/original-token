multiline_comment|/* $Id: viking.h,v 1.6 1996/03/01 07:21:05 davem Exp $&n; * viking.h:  Defines specific to the TI Viking MBUS module.&n; *            This is SRMMU stuff.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_VIKING_H
DECL|macro|_SPARC_VIKING_H
mdefine_line|#define _SPARC_VIKING_H
macro_line|#include &lt;asm/mxcc.h&gt;
multiline_comment|/* Bits in the SRMMU control register for TI Viking modules.&n; *&n; * -------------------------------------------------------------&n; * |implvers| RSV |DP|RSV|TC|AC|SP|BM|PC|MBM|SB|IC|DC|RSV|NF|ME|&n; * -------------------------------------------------------------&n; *  31    24 23-20 19  18 17 16 15 14 13  12 11 10  9 8-2  1  0&n; *&n; * DP: Data Prefetcher Enable -- 0 = DP is off, 1 = DP is on&n; * TC: Tablewalk Cacheable -- 0 = Twalks are not cacheable&n; *                            1 = Twalks are cacheable&n; * AC: Alternate Cacheable -- 0 = Direct physical accesses not cacheable&n; *                            1 = Direct physical accesses are cacheable&n; * SP: SnooP Enable -- 0 = bus snooping off, 1 = bus snooping on&n; * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode&n; * MBM: MBus Mode -- 0 = not in MBus mode, 1 = in MBus mode&n; * SB: StoreBuffer enable -- 0 = store buffer off, 1 = store buffer on&n; * IC: Instruction Cache -- 0 = off, 1 = on&n; * DC: Data Cache -- 0 = off, 1 = 0n&n; * NF: No Fault -- 0 = faults generate traps, 1 = faults don&squot;t trap&n; * ME: MMU enable -- 0 = mmu not translating, 1 = mmu translating&n; *&n; */
DECL|macro|VIKING_DCENABLE
mdefine_line|#define VIKING_DCENABLE     0x00000100   /* Enable data cache */
DECL|macro|VIKING_ICENABLE
mdefine_line|#define VIKING_ICENABLE     0x00000200   /* Enable instruction cache */
DECL|macro|VIKING_SBENABLE
mdefine_line|#define VIKING_SBENABLE     0x00000400   /* Enable store buffer */
DECL|macro|VIKING_MMODE
mdefine_line|#define VIKING_MMODE        0x00000800   /* MBUS mode */
DECL|macro|VIKING_PCENABLE
mdefine_line|#define VIKING_PCENABLE     0x00001000   /* Enable parity checking */
multiline_comment|/* Boot mode, 0 at boot-time, 1 after prom initializes the MMU. */
DECL|macro|VIKING_BMODE
mdefine_line|#define VIKING_BMODE        0x00002000   
DECL|macro|VIKING_SPENABLE
mdefine_line|#define VIKING_SPENABLE     0x00004000   /* Enable bus cache snooping */
multiline_comment|/* The deal with this AC bit is that if you are going to modify the&n; * contents of physical ram using the MMU bypass, you had better set&n; * this bit or things will get unsynchronized.  This is only applicable&n; * if an E-cache (ie. a PAC) is around and the Viking is not in MBUS mode.&n; */
DECL|macro|VIKING_ACENABLE
mdefine_line|#define VIKING_ACENABLE     0x00008000   /* Enable alternate caching */
DECL|macro|VIKING_TCENABLE
mdefine_line|#define VIKING_TCENABLE     0x00010000   /* Enable table-walks to be cached */
DECL|macro|VIKING_DPENABLE
mdefine_line|#define VIKING_DPENABLE     0x00040000   /* Enable the data prefetcher */
DECL|function|viking_flush_icache
r_extern
r_inline
r_void
id|viking_flush_icache
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
id|ASI_M_IC_FLCLEAR
)paren
)paren
suffix:semicolon
)brace
DECL|function|viking_flush_dcache
r_extern
r_inline
r_void
id|viking_flush_dcache
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
id|ASI_M_DC_FLCLEAR
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* MXCC stuff... */
DECL|function|viking_enable_mxcc
r_extern
r_inline
r_void
id|viking_enable_mxcc
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|viking_mxcc_scrape
r_extern
r_inline
r_void
id|viking_mxcc_scrape
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* David, what did you learn in school today? */
)brace
macro_line|#endif /* !(_SPARC_VIKING_H) */
eof
