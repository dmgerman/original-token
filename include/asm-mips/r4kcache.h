multiline_comment|/*&n; * r4kcache.h: Inline assembly cache operations.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * $Id: r4kcache.h,v 1.7 1997/12/18 13:00:45 ralf Exp $&n; *&n; * FIXME: Handle split L2 caches.&n; */
macro_line|#ifndef _MIPS_R4KCACHE_H
DECL|macro|_MIPS_R4KCACHE_H
mdefine_line|#define _MIPS_R4KCACHE_H
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
DECL|function|flush_icache_line_indexed
r_extern
r_inline
r_void
id|flush_icache_line_indexed
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Index_Invalidate_I
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_dcache_line_indexed
r_extern
r_inline
r_void
id|flush_dcache_line_indexed
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Index_Writeback_Inv_D
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_scache_line_indexed
r_extern
r_inline
r_void
id|flush_scache_line_indexed
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Index_Writeback_Inv_SD
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_line
r_extern
r_inline
r_void
id|flush_icache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Invalidate_I
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_dcache_line
r_extern
r_inline
r_void
id|flush_dcache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Writeback_Inv_D
)paren
)paren
suffix:semicolon
)brace
DECL|function|invalidate_dcache_line
r_extern
r_inline
r_void
id|invalidate_dcache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Invalidate_D
)paren
)paren
suffix:semicolon
)brace
DECL|function|invalidate_scache_line
r_extern
r_inline
r_void
id|invalidate_scache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Invalidate_SD
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_scache_line
r_extern
r_inline
r_void
id|flush_scache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Writeback_Inv_SD
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The next two are for badland addresses like signal trampolines.&n; */
DECL|function|protected_flush_icache_line
r_extern
r_inline
r_void
id|protected_flush_icache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&quot;
l_string|&quot;1:&bslash;tcache %1,(%0)&bslash;n&quot;
l_string|&quot;2:&bslash;t.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b,2b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Invalidate_I
)paren
)paren
suffix:semicolon
)brace
DECL|function|protected_writeback_dcache_line
r_extern
r_inline
r_void
id|protected_writeback_dcache_line
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
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&quot;
l_string|&quot;1:&bslash;tcache %1,(%0)&bslash;n&quot;
l_string|&quot;2:&bslash;t.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b,2b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|Hit_Writeback_D
)paren
)paren
suffix:semicolon
)brace
DECL|macro|cache16_unroll32
mdefine_line|#define cache16_unroll32(base,op)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set noreorder;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set mips3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache %1, 0x000(%0); cache %1, 0x010(%0);&t;&bslash;&n;&t;&t;cache %1, 0x020(%0); cache %1, 0x030(%0);&t;&bslash;&n;&t;&t;cache %1, 0x040(%0); cache %1, 0x050(%0);&t;&bslash;&n;&t;&t;cache %1, 0x060(%0); cache %1, 0x070(%0);&t;&bslash;&n;&t;&t;cache %1, 0x080(%0); cache %1, 0x090(%0);&t;&bslash;&n;&t;&t;cache %1, 0x0a0(%0); cache %1, 0x0b0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x0c0(%0); cache %1, 0x0d0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x0e0(%0); cache %1, 0x0f0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x100(%0); cache %1, 0x110(%0);&t;&bslash;&n;&t;&t;cache %1, 0x120(%0); cache %1, 0x130(%0);&t;&bslash;&n;&t;&t;cache %1, 0x140(%0); cache %1, 0x150(%0);&t;&bslash;&n;&t;&t;cache %1, 0x160(%0); cache %1, 0x170(%0);&t;&bslash;&n;&t;&t;cache %1, 0x180(%0); cache %1, 0x190(%0);&t;&bslash;&n;&t;&t;cache %1, 0x1a0(%0); cache %1, 0x1b0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x1c0(%0); cache %1, 0x1d0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x1e0(%0); cache %1, 0x1f0(%0);&t;&bslash;&n;&t;&t;.set mips0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_dcache16
r_extern
r_inline
r_void
id|blast_dcache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|dcache_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_dcache16_page
r_extern
r_inline
r_void
id|blast_dcache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_dcache16_page_indexed
r_extern
r_inline
r_void
id|blast_dcache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_icache16
r_extern
r_inline
r_void
id|blast_icache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|icache_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_icache16_page
r_extern
r_inline
r_void
id|blast_icache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_icache16_page_indexed
r_extern
r_inline
r_void
id|blast_icache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_scache16
r_extern
r_inline
r_void
id|blast_scache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
id|KSEG0
op_plus
id|scache_size
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_scache16_page
r_extern
r_inline
r_void
id|blast_scache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|function|blast_scache16_page_indexed
r_extern
r_inline
r_void
id|blast_scache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
)brace
DECL|macro|cache32_unroll32
mdefine_line|#define cache32_unroll32(base,op)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set noreorder;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set mips3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache %1, 0x000(%0); cache %1, 0x020(%0);&t;&bslash;&n;&t;&t;cache %1, 0x040(%0); cache %1, 0x060(%0);&t;&bslash;&n;&t;&t;cache %1, 0x080(%0); cache %1, 0x0a0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x0c0(%0); cache %1, 0x0e0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x100(%0); cache %1, 0x120(%0);&t;&bslash;&n;&t;&t;cache %1, 0x140(%0); cache %1, 0x160(%0);&t;&bslash;&n;&t;&t;cache %1, 0x180(%0); cache %1, 0x1a0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x1c0(%0); cache %1, 0x1e0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x200(%0); cache %1, 0x220(%0);&t;&bslash;&n;&t;&t;cache %1, 0x240(%0); cache %1, 0x260(%0);&t;&bslash;&n;&t;&t;cache %1, 0x280(%0); cache %1, 0x2a0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x2c0(%0); cache %1, 0x2e0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x300(%0); cache %1, 0x320(%0);&t;&bslash;&n;&t;&t;cache %1, 0x340(%0); cache %1, 0x360(%0);&t;&bslash;&n;&t;&t;cache %1, 0x380(%0); cache %1, 0x3a0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x3c0(%0); cache %1, 0x3e0(%0);&t;&bslash;&n;&t;&t;.set mips0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_dcache32
r_extern
r_inline
r_void
id|blast_dcache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|dcache_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Call this function only with interrupts disabled or R4600 V2.0 may blow&n; * up on you.&n; *&n; * R4600 v2.0 bug: &quot;The CACHE instructions Hit_Writeback_Inv_D,&n; * Hit_Writeback_D, Hit_Invalidate_D and Create_Dirty_Excl_D will only&n; * operate correctly if the internal data cache refill buffer is empty.  These&n; * CACHE instructions should be separated from any potential data cache miss&n; * by a load instruction to an uncached address to empty the response buffer.&quot;&n; * (Revision 2.0 device errata from IDT available on http://www.idt.com/&n; * in .pdf format.)&n; */
DECL|function|blast_dcache32_page
r_extern
r_inline
r_void
id|blast_dcache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Sigh ... workaround for R4600 v1.7 bug.  Explanation see above.&n;&t; */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|KSEG1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop;nop;nop;nop&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_dcache32_page_indexed
r_extern
r_inline
r_void
id|blast_dcache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_icache32
r_extern
r_inline
r_void
id|blast_icache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|icache_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_icache32_page
r_extern
r_inline
r_void
id|blast_icache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_icache32_page_indexed
r_extern
r_inline
r_void
id|blast_icache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
(paren
id|start
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_scache32
r_extern
r_inline
r_void
id|blast_scache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
id|KSEG0
op_plus
id|scache_size
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_scache32_page
r_extern
r_inline
r_void
id|blast_scache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|function|blast_scache32_page_indexed
r_extern
r_inline
r_void
id|blast_scache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
)brace
DECL|macro|cache64_unroll32
mdefine_line|#define cache64_unroll32(base,op)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set noreorder;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set mips3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache %1, 0x000(%0); cache %1, 0x040(%0);&t;&bslash;&n;&t;&t;cache %1, 0x080(%0); cache %1, 0x0c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x100(%0); cache %1, 0x140(%0);&t;&bslash;&n;&t;&t;cache %1, 0x180(%0); cache %1, 0x1c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x200(%0); cache %1, 0x240(%0);&t;&bslash;&n;&t;&t;cache %1, 0x280(%0); cache %1, 0x2c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x300(%0); cache %1, 0x340(%0);&t;&bslash;&n;&t;&t;cache %1, 0x380(%0); cache %1, 0x3c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x400(%0); cache %1, 0x440(%0);&t;&bslash;&n;&t;&t;cache %1, 0x480(%0); cache %1, 0x4c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x500(%0); cache %1, 0x540(%0);&t;&bslash;&n;&t;&t;cache %1, 0x580(%0); cache %1, 0x5c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x600(%0); cache %1, 0x640(%0);&t;&bslash;&n;&t;&t;cache %1, 0x680(%0); cache %1, 0x6c0(%0);&t;&bslash;&n;&t;&t;cache %1, 0x700(%0); cache %1, 0x740(%0);&t;&bslash;&n;&t;&t;cache %1, 0x780(%0); cache %1, 0x7c0(%0);&t;&bslash;&n;&t;&t;.set mips0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_scache64
r_extern
r_inline
r_void
id|blast_scache64
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
id|KSEG0
op_plus
id|scache_size
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache64_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x800
suffix:semicolon
)brace
)brace
DECL|function|blast_scache64_page
r_extern
r_inline
r_void
id|blast_scache64_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache64_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x800
suffix:semicolon
)brace
)brace
DECL|function|blast_scache64_page_indexed
r_extern
r_inline
r_void
id|blast_scache64_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache64_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x800
suffix:semicolon
)brace
)brace
DECL|macro|cache128_unroll32
mdefine_line|#define cache128_unroll32(base,op)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set noreorder;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set mips3;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cache %1, 0x000(%0); cache %1, 0x080(%0);&t;&bslash;&n;&t;&t;cache %1, 0x100(%0); cache %1, 0x180(%0);&t;&bslash;&n;&t;&t;cache %1, 0x200(%0); cache %1, 0x280(%0);&t;&bslash;&n;&t;&t;cache %1, 0x300(%0); cache %1, 0x380(%0);&t;&bslash;&n;&t;&t;cache %1, 0x400(%0); cache %1, 0x480(%0);&t;&bslash;&n;&t;&t;cache %1, 0x500(%0); cache %1, 0x580(%0);&t;&bslash;&n;&t;&t;cache %1, 0x600(%0); cache %1, 0x680(%0);&t;&bslash;&n;&t;&t;cache %1, 0x700(%0); cache %1, 0x780(%0);&t;&bslash;&n;&t;&t;cache %1, 0x800(%0); cache %1, 0x880(%0);&t;&bslash;&n;&t;&t;cache %1, 0x900(%0); cache %1, 0x980(%0);&t;&bslash;&n;&t;&t;cache %1, 0xa00(%0); cache %1, 0xa80(%0);&t;&bslash;&n;&t;&t;cache %1, 0xb00(%0); cache %1, 0xb80(%0);&t;&bslash;&n;&t;&t;cache %1, 0xc00(%0); cache %1, 0xc80(%0);&t;&bslash;&n;&t;&t;cache %1, 0xd00(%0); cache %1, 0xd80(%0);&t;&bslash;&n;&t;&t;cache %1, 0xe00(%0); cache %1, 0xe80(%0);&t;&bslash;&n;&t;&t;cache %1, 0xf00(%0); cache %1, 0xf80(%0);&t;&bslash;&n;&t;&t;.set mips0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.set reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_scache128
r_extern
r_inline
r_void
id|blast_scache128
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|KSEG0
suffix:semicolon
r_int
r_int
id|end
op_assign
id|KSEG0
op_plus
id|scache_size
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|cache128_unroll32
c_func
(paren
id|start
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x1000
suffix:semicolon
)brace
)brace
DECL|function|blast_scache128_page
r_extern
r_inline
r_void
id|blast_scache128_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
id|cache128_unroll32
c_func
(paren
id|page
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|function|blast_scache128_page_indexed
r_extern
r_inline
r_void
id|blast_scache128_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
id|cache128_unroll32
c_func
(paren
id|page
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_MIPS_R4KCACHE_H) */
eof
