multiline_comment|/* $Id: pgtable.h,v 1.51 1996/10/27 08:55:32 davem Exp $ */
macro_line|#ifndef _SPARC_PGTABLE_H
DECL|macro|_SPARC_PGTABLE_H
mdefine_line|#define _SPARC_PGTABLE_H
multiline_comment|/*  asm-sparc/pgtable.h:  Defines and functions used to work&n; *                        with Sparc page tables.&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/pgtsun4c.h&gt;
macro_line|#include &lt;asm/pgtsrmmu.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
r_extern
r_void
id|load_mmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|io_remap_page_range
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|quick_kernel_fault
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Allocate a block of RAM which is aligned to its size.&n;   This procedure can be used until the call to mem_init(). */
r_extern
r_void
op_star
id|sparc_init_alloc
c_func
(paren
r_int
r_int
op_star
id|kbrk
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* mmu-specific process creation/cloning/etc hooks. */
r_extern
r_void
(paren
op_star
id|mmu_exit_hook
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_flush_hook
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* translate between physical and virtual addresses */
r_extern
r_int
r_int
(paren
op_star
id|mmu_v2p
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|mmu_p2v
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Routines for data transfer buffers. */
r_extern
r_char
op_star
(paren
op_star
id|mmu_lockarea
)paren
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_unlockarea
)paren
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Routines for getting a dvma scsi buffer. */
DECL|struct|mmu_sglist
r_struct
id|mmu_sglist
(brace
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
DECL|member|__dont_touch
r_char
op_star
id|__dont_touch
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|dvma_addr
r_char
op_star
id|dvma_addr
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_char
op_star
(paren
op_star
id|mmu_get_scsi_one
)paren
(paren
r_char
op_star
comma
r_int
r_int
comma
r_struct
id|linux_sbus
op_star
id|sbus
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_get_scsi_sgl
)paren
(paren
r_struct
id|mmu_sglist
op_star
comma
r_int
comma
r_struct
id|linux_sbus
op_star
id|sbus
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_release_scsi_one
)paren
(paren
r_char
op_star
comma
r_int
r_int
comma
r_struct
id|linux_sbus
op_star
id|sbus
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_release_scsi_sgl
)paren
(paren
r_struct
id|mmu_sglist
op_star
comma
r_int
comma
r_struct
id|linux_sbus
op_star
id|sbus
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mmu_map_dma_area
)paren
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pmd_shift
suffix:semicolon
r_extern
r_int
r_int
id|pmd_size
suffix:semicolon
r_extern
r_int
r_int
id|pmd_mask
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|pmd_align
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pgdir_shift
suffix:semicolon
r_extern
r_int
r_int
id|pgdir_size
suffix:semicolon
r_extern
r_int
r_int
id|pgdir_mask
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|pgdir_align
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ptrs_per_pte
suffix:semicolon
r_extern
r_int
r_int
id|ptrs_per_pmd
suffix:semicolon
r_extern
r_int
r_int
id|ptrs_per_pgd
suffix:semicolon
r_extern
r_int
r_int
id|ptrs_per_page
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
(paren
id|vmalloc_start
)paren
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START vmalloc_start()
r_extern
id|pgprot_t
id|page_none
suffix:semicolon
r_extern
id|pgprot_t
id|page_shared
suffix:semicolon
r_extern
id|pgprot_t
id|page_copy
suffix:semicolon
r_extern
id|pgprot_t
id|page_readonly
suffix:semicolon
r_extern
id|pgprot_t
id|page_kernel
suffix:semicolon
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT      (pmd_shift)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE       (pmd_size)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK       (pmd_mask)
DECL|macro|PMD_ALIGN
mdefine_line|#define PMD_ALIGN      (pmd_align)
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT    (pgdir_shift)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE     (pgdir_size)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK     (pgdir_mask)
DECL|macro|PGDIR_ALIGN
mdefine_line|#define PGDIR_ALIGN    (pgdir_align)
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE   (ptrs_per_pte)
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD   (ptrs_per_pmd)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD   (ptrs_per_pgd)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE      (page_none)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED    (page_shared)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY      (page_copy)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY  (page_readonly)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL    (page_kernel)
DECL|macro|PAGE_INVALID
mdefine_line|#define PAGE_INVALID   (page_invalid)
multiline_comment|/* Top-level page directory */
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Page table for 0-4MB for everybody, on the Sparc this&n; * holds the same as on the i386.&n; */
r_extern
id|pte_t
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
r_int
id|ptr_in_current_pgd
suffix:semicolon
multiline_comment|/* the no. of pointers that fit on a page: this will go away */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE   (PAGE_SIZE/sizeof(void*))
multiline_comment|/* Here is a trick, since mmap.c need the initializer elements for&n; * protection_map[] to be constant at compile time, I set the following&n; * to all zeros.  I set it to the real values after I link in the&n; * appropriate MMU page table routines at boot time.&n; */
DECL|macro|__P000
mdefine_line|#define __P000  __pgprot(0)
DECL|macro|__P001
mdefine_line|#define __P001  __pgprot(0)
DECL|macro|__P010
mdefine_line|#define __P010  __pgprot(0)
DECL|macro|__P011
mdefine_line|#define __P011  __pgprot(0)
DECL|macro|__P100
mdefine_line|#define __P100  __pgprot(0)
DECL|macro|__P101
mdefine_line|#define __P101  __pgprot(0)
DECL|macro|__P110
mdefine_line|#define __P110  __pgprot(0)
DECL|macro|__P111
mdefine_line|#define __P111  __pgprot(0)
DECL|macro|__S000
mdefine_line|#define __S000&t;__pgprot(0)
DECL|macro|__S001
mdefine_line|#define __S001&t;__pgprot(0)
DECL|macro|__S010
mdefine_line|#define __S010&t;__pgprot(0)
DECL|macro|__S011
mdefine_line|#define __S011&t;__pgprot(0)
DECL|macro|__S100
mdefine_line|#define __S100&t;__pgprot(0)
DECL|macro|__S101
mdefine_line|#define __S101&t;__pgprot(0)
DECL|macro|__S110
mdefine_line|#define __S110&t;__pgprot(0)
DECL|macro|__S111
mdefine_line|#define __S111&t;__pgprot(0)
r_extern
r_int
id|num_contexts
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
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE ((unsigned long)(&amp;(empty_zero_page)))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR      (8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK          (~(sizeof(void*)-1))
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2   2
r_extern
r_int
r_int
(paren
op_star
id|pte_page
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|pmd_page
)paren
(paren
id|pmd_t
)paren
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|pgd_page
)paren
(paren
id|pgd_t
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|sparc_update_rootmmu_dir
)paren
(paren
r_struct
id|task_struct
op_star
comma
id|pgd_t
op_star
id|pgdir
)paren
suffix:semicolon
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) sparc_update_rootmmu_dir(tsk, pgdir)
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
r_extern
r_int
(paren
op_star
id|pte_none
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pte_present
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pte_clear
)paren
(paren
id|pte_t
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pmd_none
)paren
(paren
id|pmd_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pmd_bad
)paren
(paren
id|pmd_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pmd_present
)paren
(paren
id|pmd_t
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pmd_clear
)paren
(paren
id|pmd_t
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pgd_none
)paren
(paren
id|pgd_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pgd_bad
)paren
(paren
id|pgd_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pgd_present
)paren
(paren
id|pgd_t
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pgd_clear
)paren
(paren
id|pgd_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
r_extern
r_int
(paren
op_star
id|pte_write
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pte_dirty
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pte_young
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_wrprotect
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_mkclean
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_mkold
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_mkwrite
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_mkdirty
)paren
(paren
id|pte_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_mkyoung
)paren
(paren
id|pte_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
r_extern
id|pte_t
(paren
op_star
id|mk_pte
)paren
(paren
r_int
r_int
comma
id|pgprot_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|mk_pte_phys
)paren
(paren
r_int
r_int
comma
id|pgprot_t
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|mk_pte_io
)paren
(paren
r_int
r_int
comma
id|pgprot_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pgd_set
)paren
(paren
id|pgd_t
op_star
comma
id|pmd_t
op_star
)paren
suffix:semicolon
r_extern
id|pte_t
(paren
op_star
id|pte_modify
)paren
(paren
id|pte_t
comma
id|pgprot_t
)paren
suffix:semicolon
multiline_comment|/* to find an entry in a page-table-directory */
r_extern
id|pgd_t
op_star
(paren
op_star
id|pgd_offset
)paren
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Find an entry in the second-level page table.. */
r_extern
id|pmd_t
op_star
(paren
op_star
id|pmd_offset
)paren
(paren
id|pgd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Find an entry in the third-level page table.. */
r_extern
id|pte_t
op_star
(paren
op_star
id|pte_offset
)paren
(paren
id|pmd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any, and marks the page tables reserved.&n; */
r_extern
r_void
(paren
op_star
id|pte_free_kernel
)paren
(paren
id|pte_t
op_star
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
(paren
op_star
id|pte_alloc_kernel
)paren
(paren
id|pmd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
r_extern
r_void
(paren
op_star
id|pmd_free_kernel
)paren
(paren
id|pmd_t
op_star
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
(paren
op_star
id|pmd_alloc_kernel
)paren
(paren
id|pgd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pte_free
)paren
(paren
id|pte_t
op_star
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
(paren
op_star
id|pte_alloc
)paren
(paren
id|pmd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
r_extern
r_void
(paren
op_star
id|pmd_free
)paren
(paren
id|pmd_t
op_star
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
(paren
op_star
id|pmd_alloc
)paren
(paren
id|pgd_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pgd_free
)paren
(paren
id|pgd_t
op_star
)paren
suffix:semicolon
r_extern
id|pgd_t
op_star
(paren
op_star
id|pgd_alloc
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Fine grained cache/tlb flushing. */
macro_line|#ifdef __SMP__
r_extern
r_void
(paren
op_star
id|local_flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_cache_mm
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_cache_range
)paren
(paren
r_struct
id|mm_struct
op_star
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
r_extern
r_void
(paren
op_star
id|local_flush_cache_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_tlb_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_tlb_mm
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_tlb_range
)paren
(paren
r_struct
id|mm_struct
op_star
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
r_extern
r_void
(paren
op_star
id|local_flush_tlb_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|local_flush_page_to_ram
)paren
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_cache_mm
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
id|smp_flush_cache_range
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
r_extern
r_void
id|smp_flush_cache_page
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
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb_mm
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
id|smp_flush_tlb_range
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
r_extern
r_void
id|smp_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|mm
comma
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|smp_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
(paren
op_star
id|flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_mm
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_range
)paren
(paren
r_struct
id|mm_struct
op_star
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
r_extern
r_void
(paren
op_star
id|flush_cache_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_tlb_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_tlb_mm
)paren
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_tlb_range
)paren
(paren
r_struct
id|mm_struct
op_star
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
r_extern
r_void
(paren
op_star
id|flush_tlb_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_page_to_ram
)paren
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
multiline_comment|/* The permissions for pgprot_val to make a page mapped on the obio space */
r_extern
r_int
r_int
id|pg_iobits
suffix:semicolon
multiline_comment|/* MMU context switching. */
r_extern
r_void
(paren
op_star
id|switch_to_context
)paren
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
macro_line|#if 0 /* XXX try this soon XXX */
r_extern
r_void
(paren
op_star
id|set_pte
)paren
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
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
suffix:semicolon
macro_line|#else
r_extern
r_void
(paren
op_star
id|set_pte
)paren
(paren
id|pte_t
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_char
op_star
(paren
op_star
id|mmu_info
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Fault handler stuff... */
DECL|macro|FAULT_CODE_PROT
mdefine_line|#define FAULT_CODE_PROT     0x1
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE    0x2
DECL|macro|FAULT_CODE_USER
mdefine_line|#define FAULT_CODE_USER     0x4
r_extern
r_void
(paren
op_star
id|update_mmu_cache
)paren
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
suffix:semicolon
r_extern
r_int
id|invalid_segment
suffix:semicolon
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry) (((entry)&gt;&gt;2) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry) (((entry) &gt;&gt; 9) &amp; 0x7ffff)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset) (((type) &lt;&lt; 2) | ((offset) &lt;&lt; 9))
DECL|struct|ctx_list
r_struct
id|ctx_list
(brace
DECL|member|next
r_struct
id|ctx_list
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|ctx_list
op_star
id|prev
suffix:semicolon
DECL|member|ctx_number
r_int
r_int
id|ctx_number
suffix:semicolon
DECL|member|ctx_mm
r_struct
id|mm_struct
op_star
id|ctx_mm
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ctx_list
op_star
id|ctx_list_pool
suffix:semicolon
multiline_comment|/* Dynamically allocated */
r_extern
r_struct
id|ctx_list
id|ctx_free
suffix:semicolon
multiline_comment|/* Head of free list */
r_extern
r_struct
id|ctx_list
id|ctx_used
suffix:semicolon
multiline_comment|/* Head of used contexts list */
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT     -1
DECL|function|remove_from_ctx_list
r_extern
id|__inline__
r_void
id|remove_from_ctx_list
c_func
(paren
r_struct
id|ctx_list
op_star
id|entry
)paren
(brace
id|entry-&gt;next-&gt;prev
op_assign
id|entry-&gt;prev
suffix:semicolon
id|entry-&gt;prev-&gt;next
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
DECL|function|add_to_ctx_list
r_extern
id|__inline__
r_void
id|add_to_ctx_list
c_func
(paren
r_struct
id|ctx_list
op_star
id|head
comma
r_struct
id|ctx_list
op_star
id|entry
)paren
(brace
id|entry-&gt;next
op_assign
id|head
suffix:semicolon
(paren
id|entry-&gt;prev
op_assign
id|head-&gt;prev
)paren
op_member_access_from_pointer
id|next
op_assign
id|entry
suffix:semicolon
id|head-&gt;prev
op_assign
id|entry
suffix:semicolon
)brace
DECL|macro|add_to_free_ctxlist
mdefine_line|#define add_to_free_ctxlist(entry) add_to_ctx_list(&amp;ctx_free, entry)
DECL|macro|add_to_used_ctxlist
mdefine_line|#define add_to_used_ctxlist(entry) add_to_ctx_list(&amp;ctx_used, entry)
macro_line|#endif /* !(_SPARC_PGTABLE_H) */
eof
