multiline_comment|/* $Id: andes.c,v 1.7 2000/03/13 22:43:25 kanoj Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/r10kcache.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* CP0 hazard avoidance.  I think we can drop this for the R10000.  */
DECL|macro|BARRIER
mdefine_line|#define BARRIER __asm__ __volatile__(&quot;.set noreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;nop; nop; nop; nop; nop; nop;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;.set reorder&bslash;n&bslash;t&quot;)
multiline_comment|/* R10000 has no Create_Dirty type cacheops.  */
DECL|function|andes_clear_page
r_static
r_void
id|andes_clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t$1,%0,%2&bslash;n&quot;
l_string|&quot;1:&bslash;tsd&bslash;t$0,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t%0,64&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,-32(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,-24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,-16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$1,%0,1b&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t$0,-8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|andes_copy_page
r_static
r_void
id|andes_copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_int
r_int
id|dummy1
comma
id|dummy2
comma
id|reg1
comma
id|reg2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t$1,%0,%6&bslash;n&quot;
l_string|&quot;1:&bslash;tld&bslash;t%2,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%3,8(%1)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%2,(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%3,8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%2,16(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%3,24(%1)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%2,16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%3,24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t%0,64&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t%1,64&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%2,-32(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%3,-24(%1)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%2,-32(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%3,-24(%0)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%2,-16(%1)&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t%3,-8(%1)&bslash;n&bslash;t&quot;
l_string|&quot;sd&bslash;t%2,-16(%0)&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t$1,%0,1b&bslash;n&bslash;t&quot;
l_string|&quot; sd&bslash;t%3,-8(%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|reg1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|reg2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|to
)paren
comma
l_string|&quot;1&quot;
(paren
id|from
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Cache operations.  These are only used with the virtual memory system,&n;   not for non-coherent I/O so it&squot;s ok to ignore the secondary caches.  */
r_static
r_void
DECL|function|andes_flush_cache_all
id|andes_flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|blast_dcache32
c_func
(paren
)paren
suffix:semicolon
id|blast_icache64
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|andes_flush_cache_mm
id|andes_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;cmm[%d]&quot;
comma
(paren
r_int
)paren
id|mm-&gt;context
)paren
suffix:semicolon
macro_line|#endif
id|andes_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|andes_flush_cache_range
id|andes_flush_cache_range
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
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;crange[%d,%08lx,%08lx]&quot;
comma
(paren
r_int
)paren
id|mm-&gt;context
comma
id|start
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|blast_dcache32
c_func
(paren
)paren
suffix:semicolon
id|blast_icache64
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|andes_flush_cache_page
id|andes_flush_cache_page
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
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|text
suffix:semicolon
multiline_comment|/*&n;&t; * If ownes no valid ASID yet, cannot possibly have gotten&n;&t; * this page into the cache.&n;&t; */
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;cpage[%d,%08lx]&quot;
comma
(paren
r_int
)paren
id|mm-&gt;context
comma
id|page
)paren
suffix:semicolon
macro_line|#endif
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|page
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|page
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the page isn&squot;t marked valid, the page cannot possibly be&n;&t; * in the cache.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_PRESENT
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|text
op_assign
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Doing flushes for another ASID than the current one is&n;&t; * too difficult since stupid R4k caches do a TLB translation&n;&t; * for every cache flush operation.  So we do indexed flushes&n;&t; * in that case, which doesn&squot;t overly flush the cache too much.&n;&t; */
r_if
c_cond
(paren
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
op_logical_and
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_VALID
)paren
)paren
(brace
id|blast_dcache32_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|text
)paren
(brace
id|blast_icache64_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Do indexed flush, too much work to get the (possible)&n;&t;&t; * tlb refills to work correctly.&n;&t;&t; */
id|page
op_assign
(paren
id|CKSEG0
op_plus
(paren
id|page
op_amp
(paren
id|dcache_size
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|blast_dcache32_page_indexed
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|text
)paren
(brace
id|blast_icache64_page_indexed
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Hoo hum...  will this ever be called for an address that is not in CKSEG0&n;   and not cacheable?  */
r_static
r_void
DECL|function|andes_flush_page_to_ram
id|andes_flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|addr
op_assign
id|page_address
c_func
(paren
id|page
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|K0BASE_NONCOH
op_logical_and
id|addr
OL
(paren
l_int|0xb0UL
op_lshift
l_int|56
)paren
)paren
op_logical_or
(paren
id|addr
op_ge
id|KSEG0
op_logical_and
id|addr
OL
id|KSEG1
)paren
op_logical_or
(paren
id|addr
op_ge
id|KSEG2
)paren
)paren
(brace
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;cram[%08lx]&quot;
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
id|blast_dcache32_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|andes_flush_cache_sigtramp
id|andes_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|daddr
comma
id|iaddr
suffix:semicolon
id|daddr
op_assign
id|addr
op_amp
op_complement
(paren
id|dc_lsize
op_minus
l_int|1
)paren
suffix:semicolon
id|protected_writeback_dcache_line
c_func
(paren
id|daddr
)paren
suffix:semicolon
id|protected_writeback_dcache_line
c_func
(paren
id|daddr
op_plus
id|dc_lsize
)paren
suffix:semicolon
id|iaddr
op_assign
id|addr
op_amp
op_complement
(paren
id|ic_lsize
op_minus
l_int|1
)paren
suffix:semicolon
id|protected_flush_icache_line
c_func
(paren
id|iaddr
)paren
suffix:semicolon
id|protected_flush_icache_line
c_func
(paren
id|iaddr
op_plus
id|ic_lsize
)paren
suffix:semicolon
)brace
DECL|macro|NTLB_ENTRIES
mdefine_line|#define NTLB_ENTRIES       64
DECL|macro|NTLB_ENTRIES_HALF
mdefine_line|#define NTLB_ENTRIES_HALF  32
multiline_comment|/* TLB operations.&n;   XXX These should work fine on R10k without the BARRIERs.  */
r_static
r_inline
r_void
DECL|function|andes_flush_tlb_all
id|andes_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|old_ctx
suffix:semicolon
r_int
r_int
id|entry
suffix:semicolon
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlball]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Save old context and create impossible VPN2 value */
id|old_ctx
op_assign
id|get_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|set_entryhi
c_func
(paren
id|CKSEG0
)paren
suffix:semicolon
id|set_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|entry
op_assign
id|get_wired
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Blast &squot;em all away. */
r_while
c_loop
(paren
id|entry
OL
id|NTLB_ENTRIES
)paren
(brace
id|set_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|entry
op_increment
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|set_entryhi
c_func
(paren
id|old_ctx
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|andes_flush_tlb_mm
r_static
r_void
id|andes_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbmm&lt;%d&gt;]&quot;
comma
id|mm-&gt;context
)paren
suffix:semicolon
macro_line|#endif
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|get_new_cpu_mmu_context
c_func
(paren
id|mm
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
(brace
id|set_entryhi
c_func
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|andes_flush_tlb_range
id|andes_flush_tlb_range
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
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbrange&lt;%02x,%08lx,%08lx&gt;]&quot;
comma
(paren
id|mm-&gt;context
op_amp
l_int|0xff
)paren
comma
id|start
comma
id|end
)paren
suffix:semicolon
macro_line|#endif
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|size
op_assign
(paren
id|end
op_minus
id|start
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|NTLB_ENTRIES_HALF
)paren
(brace
r_int
id|oldpid
op_assign
(paren
id|get_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_int
id|newpid
op_assign
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|start
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|end
op_add_assign
(paren
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
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
r_int
id|idx
suffix:semicolon
id|set_entryhi
c_func
(paren
id|start
op_or
id|newpid
)paren
suffix:semicolon
id|start
op_add_assign
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|get_index
c_func
(paren
)paren
suffix:semicolon
id|set_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entryhi
c_func
(paren
id|KSEG0
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
)brace
id|set_entryhi
c_func
(paren
id|oldpid
)paren
suffix:semicolon
)brace
r_else
(brace
id|get_new_cpu_mmu_context
c_func
(paren
id|mm
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
(brace
id|set_entryhi
c_func
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|andes_flush_tlb_page
id|andes_flush_tlb_page
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
r_if
c_cond
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm
)paren
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|oldpid
comma
id|newpid
comma
id|idx
suffix:semicolon
macro_line|#ifdef DEBUG_TLB
id|printk
c_func
(paren
l_string|&quot;[tlbpage&lt;%d,%08lx&gt;]&quot;
comma
id|vma-&gt;vm_mm-&gt;context
comma
id|page
)paren
suffix:semicolon
macro_line|#endif
id|newpid
op_assign
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|page
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|oldpid
op_assign
(paren
id|get_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|set_entryhi
c_func
(paren
id|page
op_or
id|newpid
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|idx
op_assign
id|get_index
c_func
(paren
)paren
suffix:semicolon
id|set_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entryhi
c_func
(paren
id|KSEG0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
r_goto
id|finish
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
id|finish
suffix:colon
id|BARRIER
suffix:semicolon
id|set_entryhi
c_func
(paren
id|oldpid
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* XXX Simplify this.  On the R10000 writing a TLB entry for an virtual&n;   address that already exists will overwrite the old entry and not result&n;   in TLB malfunction or TLB shutdown.  */
DECL|function|andes_update_mmu_cache
r_static
r_void
id|andes_update_mmu_cache
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
r_int
r_int
id|flags
suffix:semicolon
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|idx
comma
id|pid
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|pid
op_assign
id|get_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pid
op_ne
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm
)paren
op_amp
l_int|0xff
)paren
)paren
op_logical_or
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
"&quot;"
id|update_mmu_cache
suffix:colon
id|Wheee
comma
id|bogus
id|tlbpid
id|mmpid
op_assign
op_mod
id|d
id|tlbpid
op_assign
op_mod
id|d
"&bslash;"
id|n
"&quot;"
comma
(paren
r_int
)paren
(paren
id|CPU_CONTEXT
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vma-&gt;vm_mm
)paren
op_amp
l_int|0xff
)paren
comma
id|pid
)paren
suffix:semicolon
)brace
id|address
op_and_assign
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
suffix:semicolon
id|set_entryhi
c_func
(paren
id|address
op_or
(paren
id|pid
)paren
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|tlb_probe
c_func
(paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|address
)paren
suffix:semicolon
id|idx
op_assign
id|get_index
c_func
(paren
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|address
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|set_entrylo0
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
op_increment
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|set_entrylo1
c_func
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|set_entryhi
c_func
(paren
id|address
op_or
(paren
id|pid
)paren
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
id|tlb_write_random
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
id|BARRIER
suffix:semicolon
id|set_entryhi
c_func
(paren
id|pid
)paren
suffix:semicolon
id|BARRIER
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|andes_user_mode
id|andes_user_mode
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
(paren
id|regs-&gt;cp0_status
op_amp
id|ST0_KSU
)paren
op_eq
id|KSU_USER
suffix:semicolon
)brace
DECL|function|andes_show_regs
r_static
r_void
id|andes_show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Cpu %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Saved main processor registers. */
id|printk
c_func
(paren
l_string|&quot;$0      : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
l_int|0UL
comma
id|regs-&gt;regs
(braket
l_int|1
)braket
comma
id|regs-&gt;regs
(braket
l_int|2
)braket
comma
id|regs-&gt;regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$4      : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|4
)braket
comma
id|regs-&gt;regs
(braket
l_int|5
)braket
comma
id|regs-&gt;regs
(braket
l_int|6
)braket
comma
id|regs-&gt;regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$8      : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|8
)braket
comma
id|regs-&gt;regs
(braket
l_int|9
)braket
comma
id|regs-&gt;regs
(braket
l_int|10
)braket
comma
id|regs-&gt;regs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$12     : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|12
)braket
comma
id|regs-&gt;regs
(braket
l_int|13
)braket
comma
id|regs-&gt;regs
(braket
l_int|14
)braket
comma
id|regs-&gt;regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$16     : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|16
)braket
comma
id|regs-&gt;regs
(braket
l_int|17
)braket
comma
id|regs-&gt;regs
(braket
l_int|18
)braket
comma
id|regs-&gt;regs
(braket
l_int|19
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$20     : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|20
)braket
comma
id|regs-&gt;regs
(braket
l_int|21
)braket
comma
id|regs-&gt;regs
(braket
l_int|22
)braket
comma
id|regs-&gt;regs
(braket
l_int|23
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$24     : %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|24
)braket
comma
id|regs-&gt;regs
(braket
l_int|25
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$28     : %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|28
)braket
comma
id|regs-&gt;regs
(braket
l_int|29
)braket
comma
id|regs-&gt;regs
(braket
l_int|30
)braket
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hi      : %016lx&bslash;n&quot;
comma
id|regs-&gt;hi
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Lo      : %016lx&bslash;n&quot;
comma
id|regs-&gt;lo
)paren
suffix:semicolon
multiline_comment|/* Saved cp0 registers. */
id|printk
c_func
(paren
l_string|&quot;epc     : %016lx&bslash;nbadvaddr: %016lx&bslash;n&quot;
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;cp0_badvaddr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Status  : %08x&bslash;nCause   : %08x&bslash;n&quot;
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
DECL|function|ld_mmu_andes
r_void
id|__init
id|ld_mmu_andes
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU revision is: %08x&bslash;n&quot;
comma
id|read_32bit_cp0_register
c_func
(paren
id|CP0_PRID
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary instruction cache %dkb, linesize %d bytes&bslash;n&quot;
comma
id|icache_size
op_rshift
l_int|10
comma
id|ic_lsize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary data cache %dkb, linesize %d bytes&bslash;n&quot;
comma
id|dcache_size
op_rshift
l_int|10
comma
id|dc_lsize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Secondary cache sized at %ldK, linesize %ld&bslash;n&quot;
comma
id|scache_size
c_func
(paren
)paren
op_rshift
l_int|10
comma
id|sc_lsize
c_func
(paren
)paren
)paren
suffix:semicolon
id|_clear_page
op_assign
id|andes_clear_page
suffix:semicolon
id|_copy_page
op_assign
id|andes_copy_page
suffix:semicolon
id|_flush_cache_all
op_assign
id|andes_flush_cache_all
suffix:semicolon
id|_flush_cache_mm
op_assign
id|andes_flush_cache_mm
suffix:semicolon
id|_flush_cache_range
op_assign
id|andes_flush_cache_range
suffix:semicolon
id|_flush_cache_page
op_assign
id|andes_flush_cache_page
suffix:semicolon
id|_flush_cache_sigtramp
op_assign
id|andes_flush_cache_sigtramp
suffix:semicolon
id|_flush_page_to_ram
op_assign
id|andes_flush_page_to_ram
suffix:semicolon
id|_flush_tlb_all
op_assign
id|andes_flush_tlb_all
suffix:semicolon
id|_flush_tlb_mm
op_assign
id|andes_flush_tlb_mm
suffix:semicolon
id|_flush_tlb_range
op_assign
id|andes_flush_tlb_range
suffix:semicolon
id|_flush_tlb_page
op_assign
id|andes_flush_tlb_page
suffix:semicolon
id|update_mmu_cache
op_assign
id|andes_update_mmu_cache
suffix:semicolon
id|_show_regs
op_assign
id|andes_show_regs
suffix:semicolon
id|_user_mode
op_assign
id|andes_user_mode
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * You should never change this register:&n;&t; *   - On R4600 1.7 the tlbp never hits for pages smaller than&n;&t; *     the value in the c0_pagemask register.&n;&t; *   - The entire mm handling assumes the c0_pagemask register to&n;&t; *     be set for 4kb pages.&n;&t; */
id|write_32bit_cp0_register
c_func
(paren
id|CP0_PAGEMASK
comma
id|PM_4K
)paren
suffix:semicolon
multiline_comment|/* From this point on the ARC firmware is dead.  */
id|_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Did I tell you that ARC SUCKS?  */
)brace
eof
