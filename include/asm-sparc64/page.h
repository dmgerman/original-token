multiline_comment|/* $Id: page.h,v 1.18 1998/05/01 09:33:50 davem Exp $ */
macro_line|#ifndef _SPARC64_PAGE_H
DECL|macro|_SPARC64_PAGE_H
mdefine_line|#define _SPARC64_PAGE_H
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   13
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* I have my suspicions... -DaveM */
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1UL &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1 &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK    (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE_ALIAS_BITS
mdefine_line|#define PAGE_ALIAS_BITS&t;&t;(PAGE_SIZE)&t;/* 16K Dcache, 8K pages */
macro_line|#ifdef __SMP__
DECL|macro|ULOCK_DECLARE
mdefine_line|#define ULOCK_DECLARE extern spinlock_t user_page_lock;
macro_line|#else
DECL|macro|ULOCK_DECLARE
mdefine_line|#define ULOCK_DECLARE
macro_line|#endif
DECL|struct|upcache
r_struct
id|upcache
(brace
DECL|member|list
r_struct
id|page
op_star
id|list
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|upcache
id|user_page_cache
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|USER_PAGE_WATER
mdefine_line|#define USER_PAGE_WATER&t;&t;16
r_extern
r_int
r_int
id|get_user_page_slow
c_func
(paren
r_int
id|which
)paren
suffix:semicolon
DECL|macro|get_user_page
mdefine_line|#define get_user_page(__vaddr) &bslash;&n;({ &bslash;&n;&t;ULOCK_DECLARE &bslash;&n;&t;int which = ((__vaddr) &amp; PAGE_ALIAS_BITS) ? 1 : 0; &bslash;&n;&t;struct upcache *up = &amp;user_page_cache[which]; &bslash;&n;&t;struct page *p; &bslash;&n;&t;unsigned long ret; &bslash;&n;&t;spin_lock(&amp;user_page_lock); &bslash;&n;&t;if((p = up-&gt;list) != NULL) { &bslash;&n;&t;&t;up-&gt;list = p-&gt;next; &bslash;&n;&t;&t;up-&gt;count--; &bslash;&n;&t;} &bslash;&n;&t;spin_unlock(&amp;user_page_lock); &bslash;&n;&t;if(p != NULL) &bslash;&n;&t;&t;ret = PAGE_OFFSET+PAGE_SIZE*p-&gt;map_nr; &bslash;&n;&t;else &bslash;&n;&t;&t;ret = get_user_page_slow(which); &bslash;&n;&t;ret; &bslash;&n;})
DECL|macro|free_user_page
mdefine_line|#define free_user_page(__page, __addr) &bslash;&n;do { &bslash;&n;&t;ULOCK_DECLARE &bslash;&n;&t;int which = ((__addr) &amp; PAGE_ALIAS_BITS) ? 1 : 0; &bslash;&n;&t;struct upcache *up = &amp;user_page_cache[which]; &bslash;&n;&t;if(atomic_read(&amp;(__page)-&gt;count) == 1 &amp;&amp; &bslash;&n;           up-&gt;count &lt; USER_PAGE_WATER) { &bslash;&n;&t;&t;spin_lock(&amp;user_page_lock); &bslash;&n;&t;&t;(__page)-&gt;age = PAGE_INITIAL_AGE; &bslash;&n;&t;&t;(__page)-&gt;next = up-&gt;list; &bslash;&n;&t;&t;up-&gt;list = (__page); &bslash;&n;&t;&t;up-&gt;count++; &bslash;&n;&t;&t;spin_unlock(&amp;user_page_lock); &bslash;&n;&t;} else &bslash;&n;&t;&t;free_page(addr); &bslash;&n;} while(0)
DECL|macro|clear_page
mdefine_line|#define clear_page(page) memset((void *)(page), 0, PAGE_SIZE)
r_extern
r_void
id|copy_page
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
)paren
suffix:semicolon
multiline_comment|/* GROSS, defining this makes gcc pass these types as aggregates,&n; * and thus on the stack, turn this crap off... -DaveM&n; */
multiline_comment|/* #define STRICT_MM_TYPECHECKS */
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/* These are used to make use of C type-checking.. */
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
DECL|member|iopte
DECL|typedef|iopte_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopte
suffix:semicolon
)brace
id|iopte_t
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
DECL|member|ctxd
DECL|typedef|ctxd_t
r_typedef
r_struct
(brace
r_int
r_int
id|ctxd
suffix:semicolon
)brace
id|ctxd_t
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
DECL|member|iopgprot
DECL|typedef|iopgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopgprot
suffix:semicolon
)brace
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;((x).iopte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((unsigned long)(x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((unsigned long)(x).pgd)
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;((x).ctxd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;((x).iopgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;((iopte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;((ctxd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;((iopgprot_t) { (x) } )
macro_line|#else
multiline_comment|/* .. while these make it easier on the compiler */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|iopte_t
r_typedef
r_int
r_int
id|iopte_t
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
DECL|typedef|ctxd_t
r_typedef
r_int
r_int
id|ctxd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|typedef|iopgprot_t
r_typedef
r_int
r_int
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((unsigned long)(x))
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((unsigned long)(x))
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;(x)
macro_line|#endif /* (STRICT_MM_TYPECHECKS) */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE(__off)&t;(((current-&gt;tss.flags &amp; SPARC_FLAG_32BIT) ? &bslash;&n;&t;&t;&t;&t; &t; (0x0000000070000000UL) : &bslash;&n;&t;&t;&t;&t; &t; (0xfffff80000000000UL)) + &bslash;&n;&t;&t;&t;&t;&t; (__off &amp; PAGE_SIZE))
multiline_comment|/* On Ultra this aligns to the size of the L1 cache. */
DECL|macro|TASK_UNMAPPED_ALIGN
mdefine_line|#define TASK_UNMAPPED_ALIGN(__addr, __off) &bslash;&n;&t;((((__addr)+((PAGE_SIZE&lt;&lt;1UL)-1UL)) &amp; ~((PAGE_SIZE &lt;&lt; 1UL)-1UL)) + &bslash;&n;&t; (__off&amp;PAGE_SIZE))
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Do prdele, look what happens to be in %g4... */
r_register
r_int
r_int
id|page_offset
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;page_offset
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xFFFFF80000000000
macro_line|#endif
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long) (x) + PAGE_OFFSET))
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(__pa(addr) &gt;&gt; PAGE_SHIFT)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* The following structure is used to hold the physical&n; * memory configuration of the machine.  This is filled in&n; * probe_memory() and is later used by mem_init() to set up&n; * mem_map[].  We statically allocate SPARC_PHYS_BANKS of&n; * these structs, this is arbitrary.  The entry after the&n; * last valid one has num_bytes==0.&n; */
DECL|struct|sparc_phys_banks
r_struct
id|sparc_phys_banks
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_PHYS_BANKS
mdefine_line|#define SPARC_PHYS_BANKS 32
r_extern
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__KERNEL__) */
macro_line|#endif /* !(_SPARC64_PAGE_H) */
eof
