macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __PPC_MMU_CONTEXT_H
DECL|macro|__PPC_MMU_CONTEXT_H
mdefine_line|#define __PPC_MMU_CONTEXT_H
multiline_comment|/* the way contexts are handled on the ppc they are vsid&squot;s and&n;   don&squot;t need any special treatment right now.&n;   perhaps I can defer flushing the tlb by keeping a list of&n;   zombie vsid/context&squot;s and handling that through destroy_context&n;   later -- Cort&n;&n;   The MPC8xx has only 16 contexts.  We rotate through them on each&n;   task switch.  A better way would be to keep track of tasks that&n;   own contexts, and implement an LRU usage.  That way very active&n;   tasks don&squot;t always have to pay the TLB reload overhead.  The&n;   kernel pages are mapped shared, so the kernel can run on behalf&n;   of any task that makes a kernel entry.  Shared does not mean they&n;   are not protected, just that the ASID comparison is not performed.&n;        -- Dan&n; */
macro_line|#ifdef CONFIG_8xx
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT      16
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT    15
DECL|macro|MUNGE_CONTEXT
mdefine_line|#define MUNGE_CONTEXT(n)        (n)
macro_line|#else
multiline_comment|/* PPC 6xx, 7xx CPUs */
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT      0
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT    0xfffff
multiline_comment|/*&n; * Allocating context numbers this way tends to spread out&n; * the entries in the hash table better than a simple linear&n; * allocation.&n; */
DECL|macro|MUNGE_CONTEXT
mdefine_line|#define MUNGE_CONTEXT(n)        (((n) * 897) &amp; LAST_CONTEXT)
macro_line|#endif
r_extern
r_int
id|next_mmu_context
suffix:semicolon
r_extern
r_void
id|mmu_context_overflow
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_8xx
r_extern
r_void
id|set_context
c_func
(paren
r_int
id|context
)paren
suffix:semicolon
macro_line|#else
DECL|macro|set_context
mdefine_line|#define set_context(context)    do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * Get a new mmu context for task tsk if necessary.&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(tsk)&t;&t;&t;&t;&t;&bslash;&n;do { &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct mm_struct *mm = (tsk)-&gt;mm;&t;&t;&t;&bslash;&n;&t;if (mm-&gt;context == NO_CONTEXT) {&t;&t;&t;&bslash;&n;&t;&t;if (next_mmu_context == LAST_CONTEXT)&t;&t;&bslash;&n;&t;&t;&t;mmu_context_overflow();&t;&t;&t;&bslash;&n;&t;&t;mm-&gt;context = MUNGE_CONTEXT(++next_mmu_context);&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Set up the context for a new address space.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm)&t;((mm)-&gt;context = NO_CONTEXT)
multiline_comment|/*&n; * We&squot;re finished using the context for an address space.&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)     do { } while (0)
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_context
r_extern
r_inline
r_void
id|activate_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|get_mmu_context
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|set_context
c_func
(paren
id|tsk-&gt;mm-&gt;context
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * compute the vsid from the context and segment&n; * segments &gt; 7 are kernel segments and their&n; * vsid is the segment -- Cort&n; */
DECL|macro|VSID_FROM_CONTEXT
mdefine_line|#define&t;VSID_FROM_CONTEXT(segment,context) &bslash;&n;   ((segment &lt; 8) ? ((segment) | (context)&lt;&lt;4) : (segment))
macro_line|#endif
eof
