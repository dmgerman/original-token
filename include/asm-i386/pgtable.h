macro_line|#ifndef _I386_PGTABLE_H
DECL|macro|_I386_PGTABLE_H
mdefine_line|#define _I386_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the i386, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * i386 mmu expects.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the i386 page table tree.&n; */
multiline_comment|/* Caches aren&squot;t brain-dead on the intel. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; *&n; * ..but the i386 has somewhat limited tlb flushing capabilities,&n; * and page-granular flushes are available only on i486 and up.&n; */
DECL|macro|__flush_tlb
mdefine_line|#define __flush_tlb() &bslash;&n;do { unsigned long tmpreg; __asm__ __volatile__(&quot;movl %%cr3,%0&bslash;n&bslash;tmovl %0,%%cr3&quot;:&quot;=r&quot; (tmpreg) : :&quot;memory&quot;); } while (0)
macro_line|#ifdef CONFIG_M386
DECL|macro|__flush_tlb_one
mdefine_line|#define __flush_tlb_one(addr) flush_tlb()
macro_line|#else
DECL|macro|__flush_tlb_one
mdefine_line|#define __flush_tlb_one(addr) &bslash;&n;__asm__ __volatile__(&quot;invlpg %0&quot;: :&quot;m&quot; (*(char *) addr))
macro_line|#endif
macro_line|#ifndef __SMP__
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() __flush_tlb()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() __flush_tlb()
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() __flush_tlb()
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
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
id|mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb_one
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
id|mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * We aren&squot;t very clever about this yet -  SMP could certainly&n; * avoid some global flushes..&n; */
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() &bslash;&n;&t;__flush_tlb()
DECL|macro|CLEVER_SMP_INVALIDATE
mdefine_line|#define CLEVER_SMP_INVALIDATE
macro_line|#ifdef CLEVER_SMP_INVALIDATE
multiline_comment|/*&n; *&t;Smarter SMP flushing macros. &n; *&t;&t;c/o Linus Torvalds.&n; *&n; *&t;These mean you can really definitely utterly forget about&n; *&t;writing to user space from interrupts. (Its not allowed anyway).&n; */
DECL|function|flush_tlb_current_task
r_static
r_inline
r_void
id|flush_tlb_current_task
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;mm-&gt;count
op_eq
l_int|1
)paren
multiline_comment|/* just one copy of this mm */
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* and that&squot;s us, so.. */
r_else
id|smp_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() flush_tlb_current_task()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() smp_flush_tlb()
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
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
id|mm
op_eq
id|current-&gt;mm
op_logical_and
id|mm-&gt;count
op_eq
l_int|1
)paren
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_else
id|smp_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|va
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
op_logical_and
id|current-&gt;mm-&gt;count
op_eq
l_int|1
)paren
id|__flush_tlb_one
c_func
(paren
id|va
)paren
suffix:semicolon
r_else
id|smp_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
id|flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() &bslash;&n;&t;smp_flush_tlb()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all() flush_tlb()
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
id|flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the i386 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;(((unsigned long) high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
multiline_comment|/*&n; * The 4MB page is guessing..  Detailed in the infamous &quot;Chapter H&quot;&n; * of the Pentium details, but assuming intel did the straightforward&n; * thing, this bit set in the page directory entry just means that&n; * the page directory entry points directly to a 4MB-aligned block of&n; * memory. &n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x002
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x004
DECL|macro|_PAGE_PCD
mdefine_line|#define _PAGE_PCD&t;0x010
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x020
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x040
DECL|macro|_PAGE_4M
mdefine_line|#define _PAGE_4M&t;0x080&t;/* 4 MB page, Pentium+.. */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL&t;0x100&t;/* Global TLB entry PPro+ */
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
multiline_comment|/*&n; * The i386 can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED
multiline_comment|/*&n; * Define this if things work differently on an i386 and an i486:&n; * it will (on an i486) warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; */
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
multiline_comment|/* page table for 0-4MB for everybody */
r_extern
r_int
r_int
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
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
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* to set the page-dir */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) &bslash;&n;do { &bslash;&n;&t;unsigned long __pgdir = __pa(pgdir); &bslash;&n;&t;(tsk)-&gt;tss.cr3 = __pgdir; &bslash;&n;&t;if ((tsk) == current) &bslash;&n;&t;&t;__asm__ __volatile__(&quot;movl %0,%%cr3&quot;: :&quot;r&quot; (__pgdir)); &bslash;&n;} while (0)
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!pte_val(x))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { pte_val(*(xp)) = 0; } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { pmd_val(*(xp)) = 0; } while (0)
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_extern
r_inline
r_int
id|pgd_none
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_bad
r_extern
r_inline
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_extern
r_inline
r_int
id|pgd_present
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pgd_clear
r_extern
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
)brace
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RW
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
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
op_and_assign
op_complement
id|_PAGE_RW
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
op_and_assign
op_complement
id|_PAGE_USER
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
op_and_assign
op_complement
id|_PAGE_USER
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
op_and_assign
op_complement
id|_PAGE_DIRTY
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
op_and_assign
op_complement
id|_PAGE_ACCESSED
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
op_or_assign
id|_PAGE_RW
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
op_or_assign
id|_PAGE_USER
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
op_or_assign
id|_PAGE_USER
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
op_or_assign
id|_PAGE_DIRTY
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
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = __pa(page) + pgprot_val(pgprot); __pte; })
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; })
DECL|function|pte_modify
r_extern
r_inline
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
DECL|macro|pte_page
mdefine_line|#define pte_page(pte) &bslash;&n;((unsigned long) __va(pte_val(pte) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) &bslash;&n;((mm)-&gt;pgd + ((address) &gt;&gt; PGDIR_SHIFT))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_extern
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
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
id|pmd_t
op_star
)paren
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(pmd, address) &bslash;&n;((pte_t *) (pmd_page(*pmd) + ((address&gt;&gt;10) &amp; ((PTRS_PER_PTE-1)&lt;&lt;2))))
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
DECL|function|pte_free_kernel
r_extern
r_inline
r_void
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
r_extern
r_const
r_char
id|bad_pmd_string
(braket
)braket
suffix:semicolon
DECL|function|pte_alloc_kernel
r_extern
r_inline
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
id|get_free_page
c_func
(paren
id|GFP_KERNEL
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
r_if
c_cond
(paren
id|page
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|BAD_PAGETABLE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
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
id|printk
c_func
(paren
id|bad_pmd_string
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_KERNPG_TABLE
op_plus
id|__pa
c_func
(paren
id|BAD_PAGETABLE
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
DECL|function|pmd_free_kernel
r_extern
r_inline
r_void
id|pmd_free_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_alloc_kernel
r_extern
r_inline
id|pmd_t
op_star
id|pmd_alloc_kernel
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
DECL|function|pte_free
r_extern
r_inline
r_void
id|pte_free
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc
r_extern
r_inline
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
(paren
id|PAGE_SHIFT
op_minus
l_int|2
)paren
)paren
op_amp
l_int|4
op_star
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
suffix:semicolon
id|repeat
suffix:colon
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
r_goto
id|getnew
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
r_goto
id|fix
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
(paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
)paren
suffix:semicolon
id|getnew
suffix:colon
(brace
r_int
r_int
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|freenew
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|oom
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
(paren
id|page
op_plus
id|address
)paren
suffix:semicolon
id|freenew
suffix:colon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|fix
suffix:colon
id|printk
c_func
(paren
id|bad_pmd_string
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
id|oom
suffix:colon
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|BAD_PAGETABLE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|function|pmd_free
r_extern
r_inline
r_void
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_alloc
r_extern
r_inline
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
DECL|function|pgd_free
r_extern
r_inline
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pgd_alloc
r_extern
r_inline
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pgd_t
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * The i386 doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
DECL|function|update_mmu_cache
r_extern
r_inline
r_void
id|update_mmu_cache
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
)brace
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry) (((entry) &gt;&gt; 1) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry) ((entry) &gt;&gt; 8)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset) (((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8))
DECL|macro|module_map
mdefine_line|#define module_map      vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap    vfree
macro_line|#endif /* _I386_PAGE_H */
eof
