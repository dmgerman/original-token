multiline_comment|/* $Id: r6000.c,v 1.1 1997/06/06 09:35:31 ralf Exp $&n; * r6000.c: MMU and cache routines for the R6000 processors.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
id|__asm__
c_func
(paren
l_string|&quot;.set mips3&quot;
)paren
suffix:semicolon
multiline_comment|/* because we know... */
multiline_comment|/* Cache operations. XXX Write these dave... */
DECL|function|r6000_flush_cache_all
r_static
r_inline
r_void
id|r6000_flush_cache_all
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_cache_mm
r_static
r_void
id|r6000_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_cache_range
r_static
r_void
id|r6000_flush_cache_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_cache_page
r_static
r_void
id|r6000_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_page_to_ram
r_static
r_void
id|r6000_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_cache_sigtramp
r_static
r_void
id|r6000_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
multiline_comment|/* TLB operations. XXX Write these dave... */
DECL|function|r6000_flush_tlb_all
r_static
r_inline
r_void
id|r6000_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_tlb_mm
r_static
r_void
id|r6000_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_tlb_range
r_static
r_void
id|r6000_flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_flush_tlb_page
r_static
r_void
id|r6000_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|r6000_load_pgd
r_static
r_void
id|r6000_load_pgd
c_func
(paren
r_int
r_int
id|pg_dir
)paren
(brace
)brace
DECL|function|r6000_pgd_init
r_static
r_void
id|r6000_pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
multiline_comment|/*&n;&t; * This version is optimized for the R6000.  We generate dirty lines&n;&t; * in the datacache, overwrite these lines with zeros and then flush&n;&t; * the cache.  Sounds horribly complicated but is just a trick to&n;&t; * avoid unnecessary loads of from memory and uncached stores which&n;&t; * are very expensive.  Not tested yet as the R6000 is a rare CPU only&n;&t; * available in SGI machines and I don&squot;t have one.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;cache&bslash;t%5,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,4(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,12(%0)&bslash;n&bslash;t&quot;
l_string|&quot;cache&bslash;t%5,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,20(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sw&bslash;t%2,28(%0)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%1,1&bslash;n&bslash;t&quot;
l_string|&quot;bnez&bslash;t%1,1b&bslash;n&bslash;t&quot;
l_string|&quot;addiu&bslash;t%0,32&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
comma
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;1&quot;
(paren
id|PAGE_SIZE
op_div
(paren
r_sizeof
(paren
id|pmd_t
)paren
op_star
l_int|8
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|Create_Dirty_Excl_D
)paren
)paren
suffix:semicolon
)brace
DECL|function|r6000_update_mmu_cache
r_static
r_void
id|r6000_update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
id|r6000_flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: We should also reload a new entry into the TLB to&n;&t; * avoid unnecessary exceptions.&n;&t; */
)brace
DECL|function|r6000_show_regs
r_static
r_void
id|r6000_show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Saved main processor registers&n;&t; */
id|printk
c_func
(paren
l_string|&quot;$0 : %08x %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
l_int|0
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|2
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|3
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|4
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|5
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|6
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$8 : %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|8
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|9
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|10
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|11
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|12
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|13
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|14
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$16: %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|16
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|17
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|18
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|19
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|20
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|21
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|22
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|23
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$24: %08lx %08lx                   %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|24
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|25
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|28
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|30
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Saved cp0 registers&n;&t; */
id|printk
c_func
(paren
l_string|&quot;epc  : %08lx&bslash;nStatus: %08x&bslash;nCause : %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_epc
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_status
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_cause
)paren
suffix:semicolon
)brace
DECL|function|ld_mmu_r6000
r_void
id|ld_mmu_r6000
c_func
(paren
r_void
)paren
(brace
id|flush_cache_all
op_assign
id|r6000_flush_cache_all
suffix:semicolon
id|flush_cache_mm
op_assign
id|r6000_flush_cache_mm
suffix:semicolon
id|flush_cache_range
op_assign
id|r6000_flush_cache_range
suffix:semicolon
id|flush_cache_page
op_assign
id|r6000_flush_cache_page
suffix:semicolon
id|flush_cache_sigtramp
op_assign
id|r6000_flush_cache_sigtramp
suffix:semicolon
id|flush_page_to_ram
op_assign
id|r6000_flush_page_to_ram
suffix:semicolon
id|flush_tlb_all
op_assign
id|r6000_flush_tlb_all
suffix:semicolon
id|flush_tlb_mm
op_assign
id|r6000_flush_tlb_mm
suffix:semicolon
id|flush_tlb_range
op_assign
id|r6000_flush_tlb_range
suffix:semicolon
id|flush_tlb_page
op_assign
id|r6000_flush_tlb_page
suffix:semicolon
id|load_pgd
op_assign
id|r6000_load_pgd
suffix:semicolon
id|pgd_init
op_assign
id|r6000_pgd_init
suffix:semicolon
id|update_mmu_cache
op_assign
id|r6000_update_mmu_cache
suffix:semicolon
id|show_regs
op_assign
id|r6000_show_regs
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
eof