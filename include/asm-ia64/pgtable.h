macro_line|#ifndef _ASM_IA64_PGTABLE_H
DECL|macro|_ASM_IA64_PGTABLE_H
mdefine_line|#define _ASM_IA64_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the ia-64 page table tree.&n; *&n; * This hopefully works with any (fixed) ia-64 page-size, as defined&n; * in &lt;asm/page.h&gt; (currently 8192).&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Size of physical address space: */
DECL|macro|IA64_PHYS_BITS
mdefine_line|#define IA64_PHYS_BITS&t;&t;50&t;&t;/* EAS2.5 defines 50 bits of ppn */
DECL|macro|IA64_PHYS_SIZE
mdefine_line|#define IA64_PHYS_SIZE&t;&t;(__IA64_UL(1) &lt;&lt; IA64_PHYS_BITS)
multiline_comment|/* Is ADDR a valid kernel address? */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;((addr) &gt;= TASK_SIZE)
multiline_comment|/* Is ADDR a valid physical address? */
DECL|macro|phys_addr_valid
mdefine_line|#define phys_addr_valid(addr)&t;((addr) &lt; IA64_PHYS_SIZE)
multiline_comment|/*&n; * First, define the various bits in a PTE.  Note that the PTE format&n; * matches the VHPT short format, the firt doubleword of the VHPD long&n; * format, and the first doubleword of the TLB insertion format.&n; */
DECL|macro|_PAGE_P
mdefine_line|#define _PAGE_P&t;&t;&t;(1 &lt;&lt;  0)&t;/* page present bit */
DECL|macro|_PAGE_MA_WB
mdefine_line|#define _PAGE_MA_WB&t;&t;(0x0 &lt;&lt;  2)&t;/* write back memory attribute */
DECL|macro|_PAGE_MA_UC
mdefine_line|#define _PAGE_MA_UC&t;&t;(0x4 &lt;&lt;  2)&t;/* uncacheable memory attribute */
DECL|macro|_PAGE_MA_UCE
mdefine_line|#define _PAGE_MA_UCE&t;&t;(0x5 &lt;&lt;  2)&t;/* UC exported attribute */
DECL|macro|_PAGE_MA_WC
mdefine_line|#define _PAGE_MA_WC&t;&t;(0x6 &lt;&lt;  2)&t;/* write coalescing memory attribute */
DECL|macro|_PAGE_MA_NAT
mdefine_line|#define _PAGE_MA_NAT&t;&t;(0x7 &lt;&lt;  2)&t;/* not-a-thing attribute */
DECL|macro|_PAGE_MA_MASK
mdefine_line|#define _PAGE_MA_MASK&t;&t;(0x7 &lt;&lt;  2)
DECL|macro|_PAGE_PL_0
mdefine_line|#define _PAGE_PL_0&t;&t;(0 &lt;&lt;  7)&t;/* privilege level 0 (kernel) */
DECL|macro|_PAGE_PL_1
mdefine_line|#define _PAGE_PL_1&t;&t;(1 &lt;&lt;  7)&t;/* privilege level 1 (unused) */
DECL|macro|_PAGE_PL_2
mdefine_line|#define _PAGE_PL_2&t;&t;(2 &lt;&lt;  7)&t;/* privilege level 2 (unused) */
DECL|macro|_PAGE_PL_3
mdefine_line|#define _PAGE_PL_3&t;&t;(3 &lt;&lt;  7)&t;/* privilege level 3 (user) */
DECL|macro|_PAGE_PL_MASK
mdefine_line|#define _PAGE_PL_MASK&t;&t;(3 &lt;&lt;  7)
DECL|macro|_PAGE_AR_R
mdefine_line|#define _PAGE_AR_R&t;&t;(0 &lt;&lt;  9)&t;/* read only */
DECL|macro|_PAGE_AR_RX
mdefine_line|#define _PAGE_AR_RX&t;&t;(1 &lt;&lt;  9)&t;/* read &amp; execute */
DECL|macro|_PAGE_AR_RW
mdefine_line|#define _PAGE_AR_RW&t;&t;(2 &lt;&lt;  9)&t;/* read &amp; write */
DECL|macro|_PAGE_AR_RWX
mdefine_line|#define _PAGE_AR_RWX&t;&t;(3 &lt;&lt;  9)&t;/* read, write &amp; execute */
DECL|macro|_PAGE_AR_R_RW
mdefine_line|#define _PAGE_AR_R_RW&t;&t;(4 &lt;&lt;  9)&t;/* read / read &amp; write */
DECL|macro|_PAGE_AR_RX_RWX
mdefine_line|#define _PAGE_AR_RX_RWX&t;&t;(5 &lt;&lt;  9)&t;/* read &amp; exec / read, write &amp; exec */
DECL|macro|_PAGE_AR_RWX_RW
mdefine_line|#define _PAGE_AR_RWX_RW&t;&t;(6 &lt;&lt;  9)&t;/* read, write &amp; exec / read &amp; write */
DECL|macro|_PAGE_AR_X_RX
mdefine_line|#define _PAGE_AR_X_RX&t;&t;(7 &lt;&lt;  9)&t;/* exec &amp; promote / read &amp; exec */
DECL|macro|_PAGE_AR_MASK
mdefine_line|#define _PAGE_AR_MASK&t;&t;(7 &lt;&lt;  9)
DECL|macro|_PAGE_AR_SHIFT
mdefine_line|#define _PAGE_AR_SHIFT&t;&t;9
DECL|macro|_PAGE_A
mdefine_line|#define _PAGE_A&t;&t;&t;(1 &lt;&lt;  5)&t;/* page accessed bit */
DECL|macro|_PAGE_D
mdefine_line|#define _PAGE_D&t;&t;&t;(1 &lt;&lt;  6)&t;/* page dirty bit */
DECL|macro|_PAGE_PPN_MASK
mdefine_line|#define _PAGE_PPN_MASK&t;&t;((IA64_PHYS_SIZE - 1) &amp; ~0xfffUL)
DECL|macro|_PAGE_ED
mdefine_line|#define _PAGE_ED&t;&t;(__IA64_UL(1) &lt;&lt; 52)&t;/* exception deferral */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;&t;(__IA64_UL(1) &lt;&lt; 63)
DECL|macro|_PFN_MASK
mdefine_line|#define _PFN_MASK&t;&t;_PAGE_PPN_MASK
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;&t;(_PFN_MASK | _PAGE_A | _PAGE_D)
DECL|macro|_PAGE_SIZE_4K
mdefine_line|#define _PAGE_SIZE_4K&t;12
DECL|macro|_PAGE_SIZE_8K
mdefine_line|#define _PAGE_SIZE_8K&t;13
DECL|macro|_PAGE_SIZE_16K
mdefine_line|#define _PAGE_SIZE_16K&t;14
DECL|macro|_PAGE_SIZE_64K
mdefine_line|#define _PAGE_SIZE_64K&t;16
DECL|macro|_PAGE_SIZE_256K
mdefine_line|#define _PAGE_SIZE_256K&t;18
DECL|macro|_PAGE_SIZE_1M
mdefine_line|#define _PAGE_SIZE_1M&t;20
DECL|macro|_PAGE_SIZE_4M
mdefine_line|#define _PAGE_SIZE_4M&t;22
DECL|macro|_PAGE_SIZE_16M
mdefine_line|#define _PAGE_SIZE_16M&t;24
DECL|macro|_PAGE_SIZE_64M
mdefine_line|#define _PAGE_SIZE_64M&t;26
DECL|macro|_PAGE_SIZE_256M
mdefine_line|#define _PAGE_SIZE_256M&t;28
DECL|macro|__ACCESS_BITS
mdefine_line|#define __ACCESS_BITS&t;&t;_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_MA_WB
DECL|macro|__DIRTY_BITS_NO_ED
mdefine_line|#define __DIRTY_BITS_NO_ED&t;_PAGE_A | _PAGE_P | _PAGE_D | _PAGE_MA_WB
DECL|macro|__DIRTY_BITS
mdefine_line|#define __DIRTY_BITS&t;&t;_PAGE_ED | __DIRTY_BITS_NO_ED
multiline_comment|/*&n; * Definitions for first level:&n; *&n; * PGDIR_SHIFT determines what a first-level page table entry can map.&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;(PAGE_SHIFT + 2*(PAGE_SHIFT-3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(__IA64_UL(1) &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE-1))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;(__IA64_UL(1) &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;PTRS_PER_PGD
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
multiline_comment|/*&n; * Definitions for second level:&n; *&n; * PMD_SHIFT determines the size of the area a second-level page table&n; * can map.&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(__IA64_UL(1) &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(__IA64_UL(1) &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/*&n; * Definitions for third level:&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(__IA64_UL(1) &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/* Number of pointers that fit on a page:  this will go away. */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;(__IA64_UL(1) &lt;&lt; (PAGE_SHIFT-3))
macro_line|# ifndef __ASSEMBLY__
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * All the normal masks have the &quot;page accessed&quot; bits on, as any time&n; * they are used, the page is accessed. They are cleared only by the&n; * page-out routines&n; */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_A)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_R)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|PAGE_GATE
mdefine_line|#define PAGE_GATE&t;__pgprot(__ACCESS_BITS | _PAGE_PL_0 | _PAGE_AR_X_RX)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(__DIRTY_BITS  | _PAGE_PL_0 | _PAGE_AR_RW)
multiline_comment|/*&n; * Next come the mappings that determine how mmap() protection bits&n; * (PROT_EXEC, PROT_READ, PROT_WRITE, PROT_NONE) get implemented.  The&n; * _P version gets used for a private shared memory segment, the _S&n; * version gets used for a shared memory segment with MAP_SHARED on.&n; * In a private shared memory segment, we do a copy-on-write if a task&n; * attempts to write to the page.&n; */
multiline_comment|/* xwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_READONLY&t;/* write to priv pg -&gt; copy &amp; make writable */
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_READONLY&t;/* ditto */
DECL|macro|__P100
mdefine_line|#define __P100&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_X_RX)
DECL|macro|__P101
mdefine_line|#define __P101&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__P110
mdefine_line|#define __P110&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__P111
mdefine_line|#define __P111&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED&t;/* we don&squot;t have (and don&squot;t need) write-only */
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_X_RX)
DECL|macro|__S101
mdefine_line|#define __S101&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__S110
mdefine_line|#define __S110&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RWX)
DECL|macro|__S111
mdefine_line|#define __S111&t;__pgprot(_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_PL_3 | _PAGE_AR_RWX)
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e)&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e)&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e)&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
multiline_comment|/*&n; * Some definitions to translate between mem_map, PTEs, and page&n; * addresses:&n; */
multiline_comment|/*&n; * Given a pointer to an mem_map[] entry, return the kernel virtual&n; * address corresponding to that page.&n; */
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
multiline_comment|/*&n; * Given a PTE, return the index of the mem_map[] entry corresponding&n; * to the page frame the PTE.&n; */
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(x)&t;&t;((unsigned long) ((pte_val(x) &amp; _PFN_MASK) &gt;&gt; PAGE_SHIFT))
multiline_comment|/*&n; * Now for some cache flushing routines.  This is the kind of stuff&n; * that can be very expensive, so try to avoid them whenever possible.&n; */
multiline_comment|/* Caches aren&squot;t brain-dead on the ia-64. */
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
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;do { } while (0)
r_extern
r_void
id|ia64_flush_icache_page
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((vma)-&gt;vm_flags &amp; PROT_EXEC)&t;&t;&t;&bslash;&n;&t;&t;ia64_flush_icache_page(page_address(pg));&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Now come the defines and routines to manage and access the three-level&n; * page table.&n; */
multiline_comment|/*&n; * On some architectures, special things need to be done when setting&n; * the PTE in a page table.  Nothing special needs to be on ia-64.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pteval)&t;(*(ptep) = (pteval))
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;(0xa000000000000000+2*PAGE_SIZE)
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;0xbfffffffffffffff
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero:  used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|ia64_bad_page
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
id|ia64_bad_pagetable
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE&t;ia64_bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE&t;ia64_bad_page()
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = ((page - mem_map) &lt;&lt; PAGE_SHIFT) | pgprot_val(pgprot);&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; })
DECL|macro|pte_modify
mdefine_line|#define pte_modify(_pte, newprot) &bslash;&n;&t;(__pte((pte_val(_pte) &amp; _PAGE_CHG_MASK) | pgprot_val(newprot)))
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;&t;page_pte_prot(page, __pgprot(0))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte) &t;&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; (_PAGE_P | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(pte)&t;&t;&t;(pte_val(*(pte)) = 0UL)
multiline_comment|/* pte_page() returns the &quot;struct page *&quot; corresponding to the PTE: */
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;&t;(mem_map + pte_pagenr(pte))
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp, ptep) &t;&t;(pmd_val(*(pmdp)) = __pa(ptep))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;&t;(!phys_addr_valid(pmd_val(pmd)))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;&t;(pmd_val(pmd) != 0UL)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;&t;(pmd_val(*(pmdp)) = 0UL)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;&t;((unsigned long) __va(pmd_val(pmd) &amp; _PFN_MASK))
DECL|macro|pgd_set
mdefine_line|#define pgd_set(pgdp, pmdp)&t;&t;(pgd_val(*(pgdp)) = __pa(pmdp))
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;&t;(!pgd_val(pgd))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;&t;(!phys_addr_valid(pgd_val(pgd)))
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;&t;(pgd_val(pgd) != 0UL)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;&t;(pgd_val(*(pgdp)) = 0UL)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;&t;((unsigned long) __va(pgd_val(pgd) &amp; _PFN_MASK))
multiline_comment|/*&n; * The following have defined behavior only work if pte_present() is true.&n; */
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;(((pte_val(pte) &amp; _PAGE_AR_MASK) &gt;&gt; _PAGE_AR_SHIFT) &lt; 6)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;((unsigned) (((pte_val(pte) &amp; _PAGE_AR_MASK) &gt;&gt; _PAGE_AR_SHIFT) - 2) &lt; 4)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;(pte_val(pte) &amp; _PAGE_D)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;(pte_val(pte) &amp; _PAGE_A)
multiline_comment|/*&n; * Note: we convert AR_RWX to AR_RX and AR_RW to AR_R by clearing the&n; * 2nd bit in the access rights:&n; */
DECL|macro|pte_wrprotect
mdefine_line|#define pte_wrprotect(pte)&t;(__pte(pte_val(pte) &amp; ~_PAGE_AR_RW))
DECL|macro|pte_mkwrite
mdefine_line|#define pte_mkwrite(pte)&t;(__pte(pte_val(pte) | _PAGE_AR_RW))
DECL|macro|pte_mkold
mdefine_line|#define pte_mkold(pte)&t;&t;(__pte(pte_val(pte) &amp; ~_PAGE_A))
DECL|macro|pte_mkyoung
mdefine_line|#define pte_mkyoung(pte)&t;(__pte(pte_val(pte) | _PAGE_A))
DECL|macro|pte_mkclean
mdefine_line|#define pte_mkclean(pte)&t;(__pte(pte_val(pte) &amp; ~_PAGE_D))
DECL|macro|pte_mkdirty
mdefine_line|#define pte_mkdirty(pte)&t;(__pte(pte_val(pte) | _PAGE_D))
multiline_comment|/*&n; * Macro to make mark a page protection value as &quot;uncacheable&quot;.  Note&n; * that &quot;protection&quot; is really a misnomer here as the protection value&n; * contains the memory attribute bits, dirty bits, and various other&n; * bits as well.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;__pgprot((pgprot_val(prot) &amp; ~_PAGE_MA_MASK) | _PAGE_MA_UC)
multiline_comment|/*&n; * Return the region index for virtual address ADDRESS.&n; */
r_extern
id|__inline__
r_int
r_int
DECL|function|rgn_index
id|rgn_index
(paren
r_int
r_int
id|address
)paren
(brace
id|ia64_va
id|a
suffix:semicolon
id|a.l
op_assign
id|address
suffix:semicolon
r_return
id|a.f.reg
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|pgd_index
id|pgd_index
(paren
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|region
op_assign
id|address
op_rshift
l_int|61
suffix:semicolon
r_int
r_int
id|l1index
op_assign
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
op_amp
(paren
(paren
id|PTRS_PER_PGD
op_rshift
l_int|3
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|region
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|6
)paren
)paren
op_or
id|l1index
suffix:semicolon
)brace
multiline_comment|/* The offset in the 1-level directory is given by the 3 region bits&n;   (61..63) and the seven level-1 bits (33-39).  */
r_extern
id|__inline__
id|pgd_t
op_star
DECL|function|pgd_offset
id|pgd_offset
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
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/* In the kernel&squot;s mapped region we have a full 43 bit space available and completely&n;   ignore the region number (since we know its in region number 5). */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr) &bslash;&n;&t;(init_mm.pgd + (((addr) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD - 1)))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) &bslash;&n;&t;((pmd_t *) pgd_page(*(dir)) + (((addr) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD - 1)))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir,addr) &bslash;&n;&t;((pte_t *) pmd_page(*(dir)) + (((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
r_extern
r_void
id|__handle_bad_pgd
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
r_extern
r_void
id|__handle_bad_pmd
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
r_extern
r_void
id|paging_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * IA-64 doesn&squot;t have any external MMU info: the page tables contain&n; * all the necessary information.  However, we can use this macro&n; * to pre-install (override) a PTE that we know is needed anyhow.&n; *&n; * Asit says that on Itanium, it is generally faster to let the VHPT&n; * walker pick up a newly installed PTE (and VHPT misses should be&n; * extremely rare compared to normal misses).  Also, since&n; * pre-installing the PTE has the problem that we may evict another&n; * TLB entry needlessly because we don&squot;t know for sure whether we need&n; * to update the iTLB or dTLB, I tend to prefer this solution, too.&n; * Also, this avoids nasty issues with forward progress (what if the&n; * newly installed PTE gets replaced before we return to the previous&n; * execution context?).&n; *&n; */
macro_line|#if 1
DECL|macro|update_mmu_cache
macro_line|# define update_mmu_cache(vma,address,pte)
macro_line|#else
DECL|macro|update_mmu_cache
macro_line|# define update_mmu_cache(vma,address,pte)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * XXX fix me!!&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * It&squot;s not clear this is a win.  We may end up pollute the&t;&t;&t;&t;&bslash;&n;&t; * dtlb with itlb entries and vice versa (e.g., consider stack&t;&t;&t;&t;&bslash;&n;&t; * pages that are normally marked executable).  It would be&t;&t;&t;&t;&bslash;&n;&t; * better to insert the TLB entry for the TLB cache that we&t;&t;&t;&t;&bslash;&n;&t; * know needs the new entry.  However, the update_mmu_cache()&t;&t;&t;&t;&bslash;&n;&t; * arguments don&squot;t tell us whether we got here through a data&t;&t;&t;&t;&bslash;&n;&t; * access or through an instruction fetch.  Talk to Linus to&t;&t;&t;&t;&bslash;&n;&t; * fix this.&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * If you re-enable this code, you must disable the ptc code in&t;&t;&t;&t;&bslash;&n;&t; * Entry 20 of the ivt.&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_clear_ic(flags);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_itc((vma-&gt;vm_flags &amp; PROT_EXEC) ? 0x3 : 0x2, address, pte_val(pte), PAGE_SHIFT);&t;&bslash;&n;&t;__restore_flags(flags);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;&t;(((entry).val &gt;&gt; 1) &amp; 0xff)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;&t;((entry).val &gt;&gt; 9)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset)&t;&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 9) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|macro|module_map
mdefine_line|#define module_map&t;vmalloc
DECL|macro|module_unmap
mdefine_line|#define module_unmap&t;vfree
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(0)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range&t;/* XXX is this right? */
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (mem_map + MAP_NR(empty_zero_page))
macro_line|# endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PGTABLE_H */
eof
