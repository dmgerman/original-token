macro_line|#ifndef _PPC_PGTABLE_H
DECL|macro|_PPC_PGTABLE_H
mdefine_line|#define _PPC_PGTABLE_H
macro_line|#include &lt;linux/mm.h&gt;
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
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
id|vmaddr
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
multiline_comment|/*&n; * No cache flushing is required when address mappings are&n; * changed, because the caches on PowerPCs are physically&n; * addressed.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, a, b)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, p)&t;do { } while (0)
r_extern
r_void
id|flush_icache_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * For the page specified, write modified lines in the data cache&n; * out to memory, and invalidate lines in the instruction cache.&n; */
r_extern
r_void
id|flush_page_to_ram
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|va_to_phys
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/*&n; * The PowerPC MMU uses a hash table containing PTEs, together with&n; * a set of 16 segment registers (on 32-bit implementations), to define&n; * the virtual to physical address mapping.&n; *&n; * We use the hash table as an extended TLB, i.e. a cache of currently&n; * active mappings.  We maintain a two-level page table tree, much like&n; * that used by the i386, for the sake of the Linux memory management code.&n; * Low-level assembler code in head.S (procedure hash_page) is responsible&n; * for extracting ptes from the tree and putting them into the hash table&n; * when necessary, and updating the accessed and modified bits in the&n; * page table tree.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area mapped by the second-level page tables */
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
multiline_comment|/*&n; * entries per page directory level: our page-table tree is two-level, so&n; * we don&squot;t really have any PMD directory.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(0x2000000) /* 32M */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START ((((long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1)))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
multiline_comment|/*&n; * Bits in a linux-style PTE.  These match the bits in the&n; * (hardware-defined) PowerPC PTE as closely as possible.&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001&t;/* software: pte contains a translation */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x002&t;/* matches one of the PP bits */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x004&t;/* software: user write access allowed */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x008
DECL|macro|_PAGE_COHERENT
mdefine_line|#define _PAGE_COHERENT&t;0x010&t;/* M: enforce memory coherence (SMP systems) */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x020&t;/* I: cache inhibit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU&t;0x040&t;/* W: cache write-through */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x080&t;/* C: page changed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x100&t;/* R: page referenced */
DECL|macro|_PAGE_HWWRITE
mdefine_line|#define _PAGE_HWWRITE&t;0x200&t;/* software: _PAGE_RW &amp; _PAGE_DIRTY */
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | &bslash;&n;&t;&t;&t;&t; _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | &bslash;&n;&t;&t;&t;&t; _PAGE_HWWRITE | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL_CI
mdefine_line|#define PAGE_KERNEL_CI&t;__pgprot(_PAGE_PRESENT | _PAGE_NO_CACHE | _PAGE_RW | &bslash;&n;&t;&t;&t;&t; _PAGE_HWWRITE | _PAGE_DIRTY | _PAGE_ACCESSED)
multiline_comment|/*&n; * The PowerPC can only do execute protection on a segment (256MB) basis,&n; * not on a page basis.  So we consider execute permission the same as read.&n; * Also, write permissions imply read permissions.&n; * This is the closest we can get..&n; */
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
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE&t;__bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE&t;__bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE&t;((unsigned long) empty_zero_page)
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*) == 1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;2
multiline_comment|/* to set the page-dir */
multiline_comment|/* tsk is a task_struct and pgdir is a pte_t */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) 
DECL|function|pte_none
r_extern
r_inline
r_int
id|pte_none
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_present
r_extern
r_inline
r_int
id|pte_present
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
id|_PAGE_PRESENT
suffix:semicolon
)brace
DECL|function|pte_clear
r_extern
r_inline
r_void
id|pte_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_none
r_extern
r_inline
r_int
id|pmd_none
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
op_logical_neg
id|pmd_val
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pmd_bad
r_extern
r_inline
r_int
id|pmd_bad
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_present
r_extern
r_inline
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
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|PAGE_MASK
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_clear
r_extern
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
l_int|0
suffix:semicolon
)brace
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
DECL|function|pte_uncache
r_extern
r_inline
r_int
id|pte_uncache
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
op_or_assign
id|_PAGE_NO_CACHE
suffix:semicolon
)brace
DECL|function|pte_cache
r_extern
r_inline
r_int
id|pte_cache
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
op_and_assign
op_complement
id|_PAGE_NO_CACHE
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
(paren
id|_PAGE_RW
op_or
id|_PAGE_HWWRITE
)paren
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
(paren
id|_PAGE_DIRTY
op_or
id|_PAGE_HWWRITE
)paren
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
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_HWWRITE
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
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RW
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_HWWRITE
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
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
macro_line|#if 1
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)&t;((*(pteptr)) = (pteval))
macro_line|#else
DECL|function|set_pte
r_extern
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
(brace
r_int
r_int
id|val
op_assign
id|pte_val
c_func
(paren
id|pteval
)paren
suffix:semicolon
r_extern
r_void
id|xmon
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
id|_PAGE_PRESENT
)paren
op_logical_and
(paren
(paren
id|val
OL
l_int|0x111000
op_logical_or
(paren
id|val
op_amp
l_int|0x800
)paren
op_logical_or
(paren
(paren
id|val
op_amp
id|_PAGE_HWWRITE
)paren
op_logical_and
(paren
op_complement
id|val
op_amp
(paren
id|_PAGE_RW
op_or
id|_PAGE_DIRTY
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad pte val %lx ptr=%p&bslash;n&quot;
comma
id|val
comma
id|pteptr
)paren
suffix:semicolon
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
op_star
id|pteptr
op_assign
id|pteval
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|function|mk_pte_phys
r_static
r_inline
id|pte_t
id|mk_pte_phys
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
DECL|function|mk_pte
r_extern
r_inline
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
id|__pa
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
DECL|function|pte_page
r_extern
r_inline
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
op_plus
id|KERNELBASE
suffix:semicolon
)brace
DECL|function|pmd_page
r_extern
r_inline
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
id|pmd_val
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|function|pgd_offset
r_extern
r_inline
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
DECL|function|pte_offset
r_extern
r_inline
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
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table, but are actually identical&n; * to the xxx() versions.&n; */
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
(paren
r_int
r_int
)paren
id|page
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
(paren
r_int
r_int
)paren
id|BAD_PAGETABLE
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
l_string|&quot;Bad pmd in pte_alloc: %08lx&bslash;n&quot;
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
(paren
r_int
r_int
)paren
id|BAD_PAGETABLE
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
(paren
r_int
r_int
)paren
id|page
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
(paren
r_int
r_int
)paren
id|BAD_PAGETABLE
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
l_string|&quot;Bad pmd in pte_alloc: %08lx&bslash;n&quot;
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
(paren
r_int
r_int
)paren
id|BAD_PAGETABLE
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
multiline_comment|/*&n; * Page tables may have changed.  We don&squot;t need to do anything here&n; * as entries are faulted into the hash table by the low-level&n; * data/instruction access exception handlers.&n; */
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma, addr, pte)&t;do { } while (0)
multiline_comment|/*&n; * When flushing the tlb entry for a page, we also need to flush the&n; * hash table entry.  flush_hash_page is assembler (for speed) in head.S.&n; */
r_extern
r_void
id|flush_hash_segments
c_func
(paren
r_int
id|low_vsid
comma
r_int
id|high_vsid
)paren
suffix:semicolon
r_extern
r_void
id|flush_hash_page
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|va
)paren
suffix:semicolon
r_extern
r_inline
r_void
DECL|function|flush_tlb_page
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
id|vmaddr
)paren
(brace
r_if
c_cond
(paren
id|vmaddr
OL
id|TASK_SIZE
)paren
id|flush_hash_page
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
id|vmaddr
)paren
suffix:semicolon
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
macro_line|#endif /* _PPC_PGTABLE_H */
eof
