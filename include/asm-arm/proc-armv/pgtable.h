multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/pgtable.h&n; *&n; * Copyright (C) 1995-1999 Russell King&n; *&n; * 12-Jan-1997&t;RMK&t;Altered flushing routines to use function pointers&n; *&t;&t;&t;now possible to combine ARM6, ARM7 and StrongARM versions.&n; * 17-Apr-1999&t;RMK&t;Now pass an area size to clean_cache_area and&n; *&t;&t;&t;flush_icache_area.&n; */
macro_line|#ifndef __ASM_PROC_PGTABLE_H
DECL|macro|__ASM_PROC_PGTABLE_H
mdefine_line|#define __ASM_PROC_PGTABLE_H
macro_line|#include &lt;asm/proc/domain.h&gt;
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page table can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       20
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        (~(PMD_SIZE-1))
multiline_comment|/*&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     20
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      (1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      (~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the sa110 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    256
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    4096
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  (((unsigned long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       (PAGE_OFFSET + 0x10000000)
r_extern
r_int
r_int
id|get_page_2k
c_func
(paren
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|free_page_2k
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
multiline_comment|/****************&n;* PMD functions *&n;****************/
multiline_comment|/* PMD types (actually level 1 descriptor) */
DECL|macro|PMD_TYPE_MASK
mdefine_line|#define PMD_TYPE_MASK&t;&t;0x0003
DECL|macro|PMD_TYPE_FAULT
mdefine_line|#define PMD_TYPE_FAULT&t;&t;0x0000
DECL|macro|PMD_TYPE_TABLE
mdefine_line|#define PMD_TYPE_TABLE&t;&t;0x0001
DECL|macro|PMD_TYPE_SECT
mdefine_line|#define PMD_TYPE_SECT&t;&t;0x0002
DECL|macro|PMD_UPDATABLE
mdefine_line|#define PMD_UPDATABLE&t;&t;0x0010
DECL|macro|PMD_SECT_CACHEABLE
mdefine_line|#define PMD_SECT_CACHEABLE&t;0x0008
DECL|macro|PMD_SECT_BUFFERABLE
mdefine_line|#define PMD_SECT_BUFFERABLE&t;0x0004
DECL|macro|PMD_SECT_AP_WRITE
mdefine_line|#define PMD_SECT_AP_WRITE&t;0x0400
DECL|macro|PMD_SECT_AP_READ
mdefine_line|#define PMD_SECT_AP_READ&t;0x0800
DECL|macro|PMD_DOMAIN
mdefine_line|#define PMD_DOMAIN(x)&t;&t;((x) &lt;&lt; 5)
DECL|macro|_PAGE_USER_TABLE
mdefine_line|#define _PAGE_USER_TABLE&t;(PMD_TYPE_TABLE | PMD_DOMAIN(DOMAIN_USER))
DECL|macro|_PAGE_KERNEL_TABLE
mdefine_line|#define _PAGE_KERNEL_TABLE&t;(PMD_TYPE_TABLE | PMD_DOMAIN(DOMAIN_KERNEL))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;set_pmd(pmdp, __pmd(0))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; 2)
DECL|macro|mk_user_pmd
mdefine_line|#define mk_user_pmd(ptep)&t;__mk_pmd(ptep, _PAGE_USER_TABLE)
DECL|macro|mk_kernel_pmd
mdefine_line|#define mk_kernel_pmd(ptep)&t;__mk_pmd(ptep, _PAGE_KERNEL_TABLE)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd)&t;cpu_set_pmd(pmdp,pmd)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *)(dir))
DECL|function|pmd_present
r_extern
id|__inline__
r_int
id|pmd_present
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
(paren
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_plus
l_int|1
)paren
op_amp
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_extern
id|__inline__
r_void
id|free_pmd_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|function|pmd_free
r_extern
id|__inline__
r_void
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
DECL|function|pmd_alloc
r_extern
id|__inline__
id|pmd_t
op_star
id|pmd_alloc
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
)brace
DECL|macro|pmd_free_kernel
mdefine_line|#define pmd_free_kernel&t;&t;pmd_free
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel&t;pmd_alloc
DECL|function|__mk_pmd
r_extern
id|__inline__
id|pmd_t
id|__mk_pmd
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|prot
)paren
(brace
r_int
r_int
id|pte_ptr
op_assign
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
id|pmd_t
id|pmd
suffix:semicolon
id|pte_ptr
op_sub_assign
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
suffix:semicolon
multiline_comment|/*&n;&t; * The pmd must be loaded with the physical&n;&t; * address of the PTE table&n;&t; */
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|__virt_to_phys
c_func
(paren
id|pte_ptr
)paren
op_or
id|prot
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
DECL|function|pmd_page
r_extern
id|__inline__
r_int
r_int
id|pmd_page
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_int
r_int
id|ptr
suffix:semicolon
id|ptr
op_assign
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
(paren
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
op_minus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
id|PTRS_PER_PTE
op_star
id|BYTES_PER_PTR
suffix:semicolon
r_return
id|__phys_to_virt
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/****************&n;* PTE functions *&n;****************/
multiline_comment|/* PTE types (actially level 2 descriptor) */
DECL|macro|PTE_TYPE_MASK
mdefine_line|#define PTE_TYPE_MASK&t;&t;0x0003
DECL|macro|PTE_TYPE_FAULT
mdefine_line|#define PTE_TYPE_FAULT&t;&t;0x0000
DECL|macro|PTE_TYPE_LARGE
mdefine_line|#define PTE_TYPE_LARGE&t;&t;0x0001
DECL|macro|PTE_TYPE_SMALL
mdefine_line|#define PTE_TYPE_SMALL&t;&t;0x0002
DECL|macro|PTE_AP_READ
mdefine_line|#define PTE_AP_READ&t;&t;0x0aa0
DECL|macro|PTE_AP_WRITE
mdefine_line|#define PTE_AP_WRITE&t;&t;0x0550
DECL|macro|PTE_CACHEABLE
mdefine_line|#define PTE_CACHEABLE&t;&t;0x0008
DECL|macro|PTE_BUFFERABLE
mdefine_line|#define PTE_BUFFERABLE&t;&t;0x0004
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;set_pte(ptep, __pte(0))
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|function|mk_pte
r_extern
id|__inline__
id|pte_t
id|mk_pte
c_func
(paren
r_int
r_int
id|page
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|__virt_to_phys
c_func
(paren
id|page
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|function|mk_pte_phys
r_extern
id|__inline__
id|pte_t
id|mk_pte_phys
c_func
(paren
r_int
r_int
id|physpage
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|physpage
op_plus
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pte)&t;cpu_set_pte(ptep,pte)
DECL|function|pte_page
r_extern
id|__inline__
r_int
r_int
id|pte_page
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|__phys_to_virt
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
r_extern
id|pte_t
op_star
id|get_pte_kernel_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address_preadjusted
)paren
suffix:semicolon
DECL|function|free_pte_slow
r_extern
id|__inline__
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page_2k
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|pte
op_minus
id|PTRS_PER_PTE
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(pte)
multiline_comment|/*###############################################################################&n; * New PageTableEntry stuff...&n; */
multiline_comment|/* We now keep two sets of ptes - the physical and the linux version.&n; * This gives us many advantages, and allows us greater flexibility.&n; *&n; * The Linux pte&squot;s contain:&n; *  bit   meaning&n; *   0    page present&n; *   1    young&n; *   2    bufferable&t;- matches physical pte&n; *   3    cacheable&t;- matches physical pte&n; *   4    user&n; *   5    write&n; *   6    execute&n; *   7    dirty&n; *  8-11  unused&n; *  12-31 virtual page address&n; *&n; * These are stored at the pte pointer; the physical PTE is at -1024bytes&n; */
DECL|macro|L_PTE_PRESENT
mdefine_line|#define L_PTE_PRESENT&t;&t;(1 &lt;&lt; 0)
DECL|macro|L_PTE_YOUNG
mdefine_line|#define L_PTE_YOUNG&t;&t;(1 &lt;&lt; 1)
DECL|macro|L_PTE_BUFFERABLE
mdefine_line|#define L_PTE_BUFFERABLE&t;(1 &lt;&lt; 2)
DECL|macro|L_PTE_CACHEABLE
mdefine_line|#define L_PTE_CACHEABLE&t;&t;(1 &lt;&lt; 3)
DECL|macro|L_PTE_USER
mdefine_line|#define L_PTE_USER&t;&t;(1 &lt;&lt; 4)
DECL|macro|L_PTE_WRITE
mdefine_line|#define L_PTE_WRITE&t;&t;(1 &lt;&lt; 5)
DECL|macro|L_PTE_EXEC
mdefine_line|#define L_PTE_EXEC&t;&t;(1 &lt;&lt; 6)
DECL|macro|L_PTE_DIRTY
mdefine_line|#define L_PTE_DIRTY&t;&t;(1 &lt;&lt; 7)
multiline_comment|/*&n; * The following macros handle the cache and bufferable bits...&n; */
DECL|macro|_L_PTE_DEFAULT
mdefine_line|#define _L_PTE_DEFAULT&t;L_PTE_PRESENT | L_PTE_YOUNG
DECL|macro|_L_PTE_READ
mdefine_line|#define _L_PTE_READ&t;L_PTE_USER | L_PTE_CACHEABLE
DECL|macro|_L_PTE_EXEC
mdefine_line|#define _L_PTE_EXEC&t;_L_PTE_READ | L_PTE_EXEC
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_L_PTE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_L_PTE_DEFAULT | _L_PTE_READ  | L_PTE_BUFFERABLE)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_L_PTE_DEFAULT | _L_PTE_READ  | L_PTE_BUFFERABLE | L_PTE_WRITE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_L_PTE_DEFAULT | L_PTE_CACHEABLE | L_PTE_BUFFERABLE | L_PTE_DIRTY | L_PTE_WRITE)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;&t;(PAGE_MASK | L_PTE_DIRTY | L_PTE_YOUNG)
multiline_comment|/*&n; * The table below defines the page protection levels that we insert into our&n; * Linux page table version.  These get translated into the best that the&n; * architecture can perform.  Note that on most ARM hardware:&n; *  1) We cannot do execute protection&n; *  2) If we could do execute protection, then read is implied&n; *  3) write implies read permissions&n; */
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_SHARED
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; L_PTE_PRESENT)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_USER)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_WRITE)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_EXEC)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_DIRTY)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_YOUNG)
DECL|macro|PTE_BIT_FUNC
mdefine_line|#define PTE_BIT_FUNC(fn,op)&t;&t;&t;&bslash;&n;extern inline pte_t fn##(pte_t pte) { pte_val(pte) op##; return pte; }
multiline_comment|/*PTE_BIT_FUNC(pte_rdprotect, &amp;= ~L_PTE_USER);*/
id|PTE_BIT_FUNC
c_func
(paren
id|pte_wrprotect
comma
op_and_assign
op_complement
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_exprotect
comma
op_and_assign
op_complement
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkclean
comma
op_and_assign
op_complement
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkold
comma
op_and_assign
op_complement
id|L_PTE_YOUNG
)paren
suffix:semicolon
multiline_comment|/*PTE_BIT_FUNC(pte_mkread,    |= L_PTE_USER);*/
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkwrite
comma
op_or_assign
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkexec
comma
op_or_assign
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkdirty
comma
op_or_assign
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_mkyoung
comma
op_or_assign
id|L_PTE_YOUNG
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|pte_nocache
comma
op_and_assign
op_complement
id|L_PTE_CACHEABLE
)paren
suffix:semicolon
DECL|function|pte_modify
r_extern
id|__inline__
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset
r_extern
id|__inline__
id|pte_t
op_star
id|pte_offset
c_func
(paren
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_kernel
r_extern
id|__inline__
id|pte_t
op_star
id|pte_alloc_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte_t
op_star
id|page
op_assign
(paren
id|pte_t
op_star
)paren
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|get_pte_kernel_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_kernel_pmd
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|__bad_pmd_kernel
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
)brace
DECL|function|pte_alloc
r_extern
id|__inline__
id|pte_t
op_star
id|pte_alloc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
r_extern
id|pte_t
op_star
id|get_pte_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address_preadjusted
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte_t
op_star
id|page
op_assign
(paren
id|pte_t
op_star
)paren
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|mk_user_pmd
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|__bad_pmd
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
)brace
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|function|pgd_offset
r_extern
id|__inline__
id|pgd_t
op_star
id|pgd_offset
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|mm-&gt;pgd
op_plus
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_extern
id|__inline__
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
id|pgd
)paren
(brace
multiline_comment|/* can pgd be NULL? */
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
multiline_comment|/* pgd is never none and bad - it is&n;&t;&t;&t; * detected in the pmd macros.&n;&t;&t;&t; */
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_pgd_slow: bad directory entry %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
l_int|0
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
id|pte_free
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pmd_free
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
DECL|function|pgd_alloc
r_extern
id|__inline__
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_void
)paren
(brace
r_extern
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pgd
op_assign
id|get_pgd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
id|pgd
op_assign
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
macro_line|#endif /* __ASM_PROC_PGTABLE_H */
eof
