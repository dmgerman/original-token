multiline_comment|/* $Id: viking.h,v 1.16 1996/08/29 09:49:10 davem Exp $&n; * viking.h:  Defines specific to the GNU/Viking MBUS module.&n; *            This is SRMMU stuff.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_VIKING_H
DECL|macro|_SPARC_VIKING_H
mdefine_line|#define _SPARC_VIKING_H
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/mxcc.h&gt;
multiline_comment|/* Bits in the SRMMU control register for GNU/Viking modules.&n; *&n; * -----------------------------------------------------------&n; * |impl-vers| RSV |TC|AC|SP|BM|PC|MBM|SB|IC|DC|PSO|RSV|NF|ME|&n; * -----------------------------------------------------------&n; *  31     24 23-17 16 15 14 13 12 11  10  9  8  7  6-2  1  0&n; *&n; * TC: Tablewalk Cacheable -- 0 = Twalks are not cacheable in E-cache&n; *                            1 = Twalks are cacheable in E-cache&n; *&n; * GNU/Viking will only cache tablewalks in the E-cache (mxcc) if present&n; * and never caches them internally (or so states the docs).  Therefore&n; * for machines lacking an E-cache (ie. in MBUS mode) this bit must&n; * remain cleared.&n; *&n; * AC: Alternate Cacheable -- 0 = Passthru physical accesses not cacheable&n; *                            1 = Passthru physical accesses cacheable&n; *&n; * This indicates whether accesses are cacheable when no cachable bit&n; * is present in the pte when the processor is in boot-mode or the&n; * access does not need pte&squot;s for translation (ie. pass-thru ASI&squot;s).&n; * &quot;Cachable&quot; is only referring to E-cache (if present) and not the&n; * on chip split I/D caches of the GNU/Viking.&n; *&n; * SP: SnooP Enable -- 0 = bus snooping off, 1 = bus snooping on&n; *&n; * This enables snooping on the GNU/Viking bus.  This must be on&n; * for the hardware cache consistency mechanisms of the GNU/Viking&n; * to work at all.  On non-mxcc GNU/Viking modules the split I/D&n; * caches will snoop regardless of whether they are enabled, this&n; * takes care of the case where the I or D or both caches are turned&n; * off yet still contain valid data.  Note also that this bit does&n; * not affect GNU/Viking store-buffer snoops, those happen if the&n; * store-buffer is enabled no matter what.&n; *&n; * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode&n; *&n; * This indicates whether the GNU/Viking is in boot-mode or not,&n; * if it is then all instruction fetch physical addresses are&n; * computed as 0xff0000000 + low 28 bits of requested address.&n; * GNU/Viking boot-mode does not affect data accesses.  Also,&n; * in boot mode instruction accesses bypass the split on chip I/D&n; * caches, they may be cached by the GNU/MXCC if present and enabled.&n; *&n; * MBM: MBus Mode -- 0 = not in MBus mode, 1 = in MBus mode&n; *&n; * This indicated the GNU/Viking configuration present.  If in&n; * MBUS mode, the GNU/Viking lacks a GNU/MXCC E-cache.  If it is&n; * not then the GNU/Viking is on a module VBUS connected directly&n; * to a GNU/MXCC cache controller.  The GNU/MXCC can be thus connected&n; * to either an GNU/MBUS (sun4m) or the packet-switched GNU/XBus (sun4d).&n; *&n; * SB: StoreBuffer enable -- 0 = store buffer off, 1 = store buffer on&n; *&n; * The GNU/Viking store buffer allows the chip to continue execution&n; * after a store even if the data cannot be placed in one of the&n; * caches during that cycle.  If disabled, all stores operations&n; * occur synchronously.&n; *&n; * IC: Instruction Cache -- 0 = off, 1 = on&n; * DC: Data Cache -- 0 = off, 1 = 0n&n; *&n; * These bits enable the on-cpu GNU/Viking split I/D caches.  Note,&n; * as mentioned above, these caches will snoop the bus in GNU/MBUS&n; * configurations even when disabled to avoid data corruption.&n; *&n; * NF: No Fault -- 0 = faults generate traps, 1 = faults don&squot;t trap&n; * ME: MMU enable -- 0 = mmu not translating, 1 = mmu translating&n; *&n; */
DECL|macro|VIKING_MMUENABLE
mdefine_line|#define VIKING_MMUENABLE    0x00000001
DECL|macro|VIKING_NOFAULT
mdefine_line|#define VIKING_NOFAULT      0x00000002
DECL|macro|VIKING_PSO
mdefine_line|#define VIKING_PSO          0x00000080
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
DECL|macro|VIKING_BMODE
mdefine_line|#define VIKING_BMODE        0x00002000   
DECL|macro|VIKING_SPENABLE
mdefine_line|#define VIKING_SPENABLE     0x00004000   /* Enable bus cache snooping */
DECL|macro|VIKING_ACENABLE
mdefine_line|#define VIKING_ACENABLE     0x00008000   /* Enable alternate caching */
DECL|macro|VIKING_TCENABLE
mdefine_line|#define VIKING_TCENABLE     0x00010000   /* Enable table-walks to be cached */
DECL|macro|VIKING_DPENABLE
mdefine_line|#define VIKING_DPENABLE     0x00040000   /* Enable the data prefetcher */
multiline_comment|/*&n; * GNU/Viking Breakpoint Action Register fields.&n; */
DECL|macro|VIKING_ACTION_MIX
mdefine_line|#define VIKING_ACTION_MIX   0x00001000   /* Enable multiple instructions */
multiline_comment|/*&n; * GNU/Viking Cache Tags.&n; */
DECL|macro|VIKING_PTAG_VALID
mdefine_line|#define VIKING_PTAG_VALID   0x01000000   /* Cache block is valid */
DECL|macro|VIKING_PTAG_DIRTY
mdefine_line|#define VIKING_PTAG_DIRTY   0x00010000   /* Block has been modified */
DECL|macro|VIKING_PTAG_SHARED
mdefine_line|#define VIKING_PTAG_SHARED  0x00000100   /* Shared with some other cache */
DECL|function|viking_flush_icache
r_extern
id|__inline__
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
id|__inline__
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
DECL|function|viking_unlock_icache
r_extern
id|__inline__
r_void
id|viking_unlock_icache
c_func
(paren
r_void
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
l_int|0x80000000
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_IC_FLCLEAR
)paren
)paren
suffix:semicolon
)brace
DECL|function|viking_unlock_dcache
r_extern
id|__inline__
r_void
id|viking_unlock_dcache
c_func
(paren
r_void
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
l_int|0x80000000
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_DC_FLCLEAR
)paren
)paren
suffix:semicolon
)brace
DECL|function|viking_set_bpreg
r_extern
id|__inline__
r_void
id|viking_set_bpreg
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
l_string|&quot;sta %0, [%%g0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regval
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_ACTION
)paren
)paren
suffix:semicolon
)brace
DECL|function|viking_get_bpreg
r_extern
id|__inline__
r_int
r_int
id|viking_get_bpreg
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
l_string|&quot;lda [%%g0] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|regval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_ACTION
)paren
)paren
suffix:semicolon
r_return
id|regval
suffix:semicolon
)brace
DECL|function|viking_get_dcache_ptag
r_extern
id|__inline__
r_void
id|viking_get_dcache_ptag
c_func
(paren
r_int
id|set
comma
r_int
id|block
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|ptag
op_assign
(paren
(paren
id|set
op_amp
l_int|0x7f
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|block
op_amp
l_int|0x3
)paren
op_lshift
l_int|26
)paren
op_or
l_int|0x80000000
suffix:semicolon
r_int
r_int
id|info
comma
id|page
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldda [%2] %3, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g2, %0&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g3, %1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|info
)paren
comma
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptag
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_DATAC_TAG
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
id|info
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
id|page
suffix:semicolon
)brace
DECL|function|viking_mxcc_turn_off_parity
r_extern
id|__inline__
r_void
id|viking_mxcc_turn_off_parity
c_func
(paren
r_int
r_int
op_star
id|mregp
comma
r_int
r_int
op_star
id|mxcc_cregp
)paren
(brace
r_int
r_int
id|mreg
op_assign
op_star
id|mregp
suffix:semicolon
r_int
r_int
id|mxcc_creg
op_assign
op_star
id|mxcc_cregp
suffix:semicolon
id|mreg
op_and_assign
op_complement
(paren
id|VIKING_PCENABLE
)paren
suffix:semicolon
id|mxcc_creg
op_and_assign
op_complement
(paren
id|MXCC_CTL_PARE
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;set 1f, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;andcc %%g2, 4, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;bne 2f&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;sta %0, [%%g0] %3&bslash;n&bslash;t&quot;
l_string|&quot;sta %1, [%2] %4&bslash;n&bslash;t&quot;
l_string|&quot;b 1f&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;sta %0, [%%g0] %3&bslash;n&bslash;t&quot;
l_string|&quot;sta %1, [%2] %4&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mreg
)paren
comma
l_string|&quot;r&quot;
(paren
id|mxcc_creg
)paren
comma
l_string|&quot;r&quot;
(paren
id|MXCC_CREG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
suffix:colon
l_string|&quot;g2&quot;
)paren
suffix:semicolon
op_star
id|mregp
op_assign
id|mreg
suffix:semicolon
op_star
id|mxcc_cregp
op_assign
id|mxcc_creg
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_VIKING_H) */
eof
