multiline_comment|/*&n; * linux/include/asm-arm/proc-armo/pgtable.h&n; *&n; * Copyright (C) 1995, 1996 Russell King&n; * Modified 18/19-Oct-1997 for two-level page table&n; */
macro_line|#ifndef __ASM_PROC_PGTABLE_H
DECL|macro|__ASM_PROC_PGTABLE_H
mdefine_line|#define __ASM_PROC_PGTABLE_H
macro_line|#include &lt;asm/arch/mmu.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/arch/processor.h&gt;&t;&t;/* For TASK_SIZE */
DECL|macro|LIBRARY_TEXT_START
mdefine_line|#define LIBRARY_TEXT_START 0x0c000000
multiline_comment|/*&n; * Cache flushing...&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm,start,end)&t;&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start,end)&t;&t;do { } while (0)
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; */
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;&t;&t;do { } while (0)
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;do { } while (0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm, start, end) do { } while (0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, vmaddr)&t;do { } while (0)
multiline_comment|/*&n; * We have a mem map cache...&n; */
DECL|function|update_memc_all
r_extern
id|__inline__
r_void
id|update_memc_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|init_task
suffix:semicolon
r_do
(brace
id|processor.u.armv2
dot
id|_update_map
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next_task
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|init_task
)paren
suffix:semicolon
id|processor.u.armv2._remap_memc
(paren
id|current
)paren
suffix:semicolon
)brace
DECL|function|update_memc_task
r_extern
id|__inline__
r_void
id|update_memc_task
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|processor.u.armv2
dot
id|_update_map
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|processor.u.armv2._remap_memc
(paren
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|update_memc_mm
r_extern
id|__inline__
r_void
id|update_memc_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|init_task
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|p-&gt;mm
op_eq
id|mm
)paren
id|processor.u.armv2
dot
id|_update_map
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next_task
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|init_task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
op_eq
id|mm
)paren
id|processor.u.armv2._remap_memc
(paren
id|current
)paren
suffix:semicolon
)brace
DECL|function|update_memc_addr
r_extern
id|__inline__
r_void
id|update_memc_addr
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
id|pte_t
id|pte
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|init_task
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|p-&gt;mm
op_eq
id|mm
)paren
id|processor.u.armv2
dot
id|_update_mmu_cache
c_func
(paren
id|p
comma
id|addr
comma
id|pte
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next_task
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|init_task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
op_eq
id|mm
)paren
id|processor.u.armv2._remap_memc
(paren
id|current
)paren
suffix:semicolon
)brace
DECL|macro|__flush_entry_to_ram
mdefine_line|#define __flush_entry_to_ram(entry)
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       20
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        (~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     20
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      (1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      (~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the arm3 is one-level, so&n; * we don&squot;t really have any PMD or PTE directory physically.&n; *&n; * 18-Oct-1997 RMK Now two-level (32x32)&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    32
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    32
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;0x01a00000
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;&t;0x01
DECL|macro|_PAGE_READONLY
mdefine_line|#define _PAGE_READONLY&t;&t;0x02
DECL|macro|_PAGE_NOT_USER
mdefine_line|#define _PAGE_NOT_USER&t;&t;0x04
DECL|macro|_PAGE_OLD
mdefine_line|#define _PAGE_OLD&t;&t;0x08
DECL|macro|_PAGE_CLEAN
mdefine_line|#define _PAGE_CLEAN&t;&t;0x10
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE     (_PAGE_PRESENT)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_OLD | _PAGE_CLEAN)
multiline_comment|/*                               -- present --   -- !dirty --  --- !write ---   ---- !user --- */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY | _PAGE_NOT_USER)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_CLEAN                                  )
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_PRESENT                                | _PAGE_NOT_USER)
multiline_comment|/*&n; * The arm can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
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
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
r_extern
r_int
r_int
op_star
id|empty_zero_page
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE ((unsigned long) empty_zero_page)
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BYTES_PER_PTR
mdefine_line|#define BYTES_PER_PTR&t;&t;&t;(sizeof(unsigned long))
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR                    (8*BYTES_PER_PTR)
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK                        (~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2                 2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* to set the page-dir */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tsk-&gt;tss.memmap = (unsigned long)pgdir;&t;&t;&t;&t;&bslash;&n;&t;processor.u.armv2._update_map(tsk);&t;&t;&t;&t;&bslash;&n;&t;if ((tsk) == current)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;processor.u.armv2._remap_memc (current);&t;&t;&bslash;&n;} while (0)
r_extern
r_int
r_int
id|physical_start
suffix:semicolon
r_extern
r_int
r_int
id|physical_end
suffix:semicolon
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;set_pte((ptep), __pte(0))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;((pmd_val(pmd) &amp; 0xfc000002))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;(pmd_val(pmd) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;set_pmd(pmdp, __pmd(0))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_extern
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_NOT_USER
)paren
suffix:semicolon
)brace
DECL|function|pte_write
r_extern
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READONLY
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_extern
r_inline
r_int
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_NOT_USER
)paren
suffix:semicolon
)brace
DECL|function|pte_dirty
r_extern
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CLEAN
)paren
suffix:semicolon
)brace
DECL|function|pte_young
r_extern
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_OLD
)paren
suffix:semicolon
)brace
DECL|macro|pte_cacheable
mdefine_line|#define pte_cacheable(pte) 1
DECL|function|pte_nocache
r_extern
r_inline
id|pte_t
id|pte_nocache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_READONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_extern
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_extern
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_CLEAN
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_OLD
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_READONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_extern
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_NOT_USER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_extern
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_CLEAN
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_OLD
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
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
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
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
DECL|function|mk_pmd
r_extern
id|__inline__
id|pmd_t
id|mk_pmd
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pmd_t
id|pmd
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|__virt_to_phys
c_func
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
op_or
id|_PAGE_TABLE
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd) ((*(pmdp)) = (pmd))
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
r_return
id|__phys_to_virt
c_func
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|_PAGE_TABLE
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *)(dir))
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
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
macro_line|#ifndef __SMP__
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|quicklists
suffix:semicolon
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist ((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist (quicklists.pte_cache)
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist (quicklists.pgd_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size (quicklists.pgtable_cache_sz)
macro_line|#else
macro_line|#error Pgtable caches have to be per-CPU, so that no locking is needed.
macro_line|#endif
r_extern
id|pgd_t
op_star
id|get_pgd_slow
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_pgd_fast
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|pgd_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_else
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_extern
id|__inline__
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
op_assign
(paren
r_int
r_int
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd
suffix:semicolon
id|pgtable_cache_size
op_increment
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
id|kfree
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
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
DECL|function|get_pte_fast
r_extern
id|__inline__
id|pte_t
op_star
id|get_pte_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
)paren
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pte_fast
r_extern
id|__inline__
r_void
id|free_pte_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
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
id|kfree
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t use pmd cache, so this is a dummy routine */
DECL|function|get_pmd_fast
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_fast
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
l_int|0
suffix:semicolon
)brace
DECL|function|free_pmd_fast
r_extern
id|__inline__
r_void
id|free_pmd_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
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
r_extern
r_void
id|__bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)    free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)           free_pte_fast(pte)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)           free_pgd_fast(pgd)
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc()             get_pgd_fast()
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
id|mk_pmd
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
mdefine_line|#define pmd_free_kernel         pmd_free
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel        pmd_alloc
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel        pte_alloc
DECL|function|set_pgdir
r_extern
id|__inline__
r_void
id|set_pgdir
c_func
(paren
r_int
r_int
id|address
comma
id|pgd_t
id|entry
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
r_continue
suffix:semicolon
op_star
id|pgd_offset
c_func
(paren
id|p-&gt;mm
comma
id|address
)paren
op_assign
id|entry
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd
suffix:semicolon
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
)paren
id|pgd
(braket
id|address
op_rshift
id|PGDIR_SHIFT
)braket
op_assign
id|entry
suffix:semicolon
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte)
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry) (((entry) &gt;&gt; 1) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry) ((entry) &gt;&gt; 8)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset) (((type) &lt;&lt; 1) | ((offset) &lt;&lt;  8))
macro_line|#endif /* __ASM_PROC_PAGE_H */
eof
