macro_line|#ifndef _I386_PAGE_H
DECL|macro|_I386_PAGE_H
mdefine_line|#define _I386_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
DECL|macro|CONFIG_STRICT_MM_TYPECHECKS
mdefine_line|#define CONFIG_STRICT_MM_TYPECHECKS
macro_line|#ifdef CONFIG_STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;(x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;(x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
multiline_comment|/*&n; * TLB invalidation:&n; *&n; *  - invalidate() invalidates the current task TLBs&n; *  - invalidate_all() invalidates all processes TLBs&n; *  - invalidate_task(task) invalidates the specified tasks TLB&squot;s&n; *  - invalidate_page(task, vmaddr) invalidates one page&n; *&n; * ..but the i386 has somewhat limited invalidation capabilities.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__(&quot;movl %%cr3,%%eax&bslash;n&bslash;tmovl %%eax,%%cr3&quot;: : :&quot;ax&quot;)
DECL|macro|invalidate_all
mdefine_line|#define invalidate_all() invalidate()
DECL|macro|invalidate_task
mdefine_line|#define invalidate_task(task) &bslash;&n;do { if ((task)-&gt;mm == current-&gt;mm) invalidate(); } while (0)
DECL|macro|invalidate_page
mdefine_line|#define invalidate_page(task,addr) &bslash;&n;do { if ((task)-&gt;mm == current-&gt;mm) invalidate(); } while (0)
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|local_invalidate
mdefine_line|#define local_invalidate() &bslash;&n;__asm__ __volatile__(&quot;movl %%cr3,%%eax&bslash;n&bslash;tmovl %%eax,%%cr3&quot;: : :&quot;ax&quot;)
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;&t;smp_invalidate();
macro_line|#endif
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* This handles the memory map.. */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(((unsigned long)(addr)) &gt;&gt; PAGE_SHIFT)
r_typedef
r_struct
(brace
DECL|member|count
r_int
id|count
suffix:colon
l_int|24
comma
DECL|member|age
id|age
suffix:colon
l_int|6
comma
DECL|member|dirty
id|dirty
suffix:colon
l_int|1
comma
DECL|member|reserved
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|mem_map_t
)brace
id|mem_map_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_PAGE_H */
eof
