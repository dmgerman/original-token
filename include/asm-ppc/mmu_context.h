macro_line|#ifndef __PPC_MMU_CONTEXT_H
DECL|macro|__PPC_MMU_CONTEXT_H
mdefine_line|#define __PPC_MMU_CONTEXT_H
multiline_comment|/* the way contexts are handled on the ppc they are vsid&squot;s and&n;   don&squot;t need any special treatment right now.&n;   perhaps I can defer flushing the tlb by keeping a list of&n;   zombie vsid/context&squot;s and handling that through destroy_context&n;   later -- Cort&n; */
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT&t;0
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT&t;0xfffff
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
r_extern
r_void
id|set_context
c_func
(paren
r_int
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocating context numbers this way tends to spread out&n; * the entries in the hash table better than a simple linear&n; * allocation.&n; */
DECL|macro|MUNGE_CONTEXT
mdefine_line|#define MUNGE_CONTEXT(n)&t;(((n) * 897) &amp; LAST_CONTEXT)
multiline_comment|/*&n; * Get a new mmu context for task tsk if necessary.&n; */
DECL|macro|get_mmu_context
mdefine_line|#define get_mmu_context(tsk)&t;&t;&t;&t;&t;&bslash;&n;do { &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct mm_struct *mm = (tsk)-&gt;mm;&t;&t;&t;&bslash;&n;&t;if (mm-&gt;context == NO_CONTEXT) {&t;&t;&t;&bslash;&n;&t;        int i; &bslash;&n;&t;&t;if (next_mmu_context == LAST_CONTEXT)&t;&t;&bslash;&n;&t;&t;&t;mmu_context_overflow();&t;&t;&t;&bslash;&n;&t;&t;mm-&gt;context = MUNGE_CONTEXT(++next_mmu_context);&bslash;&n;&t; &t;if ( tsk == current )                           &bslash;&n;&t;&t;&t;set_context(mm-&gt;context);               &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Set up the context for a new address space.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(mm)&t;((mm)-&gt;context = NO_CONTEXT)
multiline_comment|/*&n; * We&squot;re finished using the context for an address space.&n; */
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;do { } while (0)
multiline_comment|/*&n; * compute the vsid from the context and segment&n; * segments &gt; 7 are kernel segments and their&n; * vsid is the segment -- Cort&n; */
DECL|macro|VSID_FROM_CONTEXT
mdefine_line|#define&t;VSID_FROM_CONTEXT(segment,context) &bslash;&n;   ((segment &lt; 8) ? ((segment) | (context)&lt;&lt;4) : (segment))
macro_line|#endif
eof
