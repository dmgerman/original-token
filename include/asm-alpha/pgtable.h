macro_line|#ifndef _ALPHA_PGTABLE_H
DECL|macro|_ALPHA_PGTABLE_H
mdefine_line|#define _ALPHA_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the alpha page table tree.&n; *&n; * This hopefully works with any standard alpha page-size, as defined&n; * in &lt;asm/page.h&gt; (currently 8192).&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PAGE_SHIFT + 2*(PAGE_SHIFT-3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the alpha is three-level, with&n; * all levels having a one-page page table.&n; *&n; * The PGD is special: the last entry is reserved for self-mapping.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;((1UL &lt;&lt; (PAGE_SHIFT-3))-1)
multiline_comment|/* the no. of pointers that fit on a page: this will go away */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0xFFFFFE0000000000
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
multiline_comment|/*&n; * OSF/1 PAL-code-imposed page table bits&n; */
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID&t;0x0001
DECL|macro|_PAGE_FOR
mdefine_line|#define _PAGE_FOR&t;0x0002&t;/* used for page protection (fault on read) */
DECL|macro|_PAGE_FOW
mdefine_line|#define _PAGE_FOW&t;0x0004&t;/* used for page protection (fault on write) */
DECL|macro|_PAGE_FOE
mdefine_line|#define _PAGE_FOE&t;0x0008&t;/* used for page protection (fault on exec) */
DECL|macro|_PAGE_ASM
mdefine_line|#define _PAGE_ASM&t;0x0010
DECL|macro|_PAGE_KRE
mdefine_line|#define _PAGE_KRE&t;0x0100&t;/* xxx - see below on the &quot;accessed&quot; bit */
DECL|macro|_PAGE_URE
mdefine_line|#define _PAGE_URE&t;0x0200&t;/* xxx */
DECL|macro|_PAGE_KWE
mdefine_line|#define _PAGE_KWE&t;0x1000&t;/* used to do the dirty bit in software */
DECL|macro|_PAGE_UWE
mdefine_line|#define _PAGE_UWE&t;0x2000&t;/* used to do the dirty bit in software */
multiline_comment|/* .. and these are ours ... */
DECL|macro|_PAGE_COW
mdefine_line|#define _PAGE_COW&t;0x10000
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x20000
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x40000
multiline_comment|/*&n; * NOTE! The &quot;accessed&quot; bit isn&squot;t necessarily exact: it can be kept exactly&n; * by software (use the KRE/URE/KWE/UWE bits appropriately), but I&squot;ll fake it.&n; * Under Linux/AXP, the &quot;accessed&quot; bit just means &quot;read&quot;, and I&squot;ll just use&n; * the KRE/URE bits to watch for it. That way we don&squot;t need to overload the&n; * KWE/UWE bits with both handling dirty and accessed.&n; *&n; * Note that the kernel uses the accessed bit just to check whether to page&n; * out a page or not, so it doesn&squot;t have to be exact anyway.&n; */
DECL|macro|__DIRTY_BITS
mdefine_line|#define __DIRTY_BITS&t;(_PAGE_DIRTY | _PAGE_KWE | _PAGE_UWE)
DECL|macro|__ACCESS_BITS
mdefine_line|#define __ACCESS_BITS&t;(_PAGE_ACCESSED | _PAGE_KRE | _PAGE_URE)
DECL|macro|_PFN_MASK
mdefine_line|#define _PFN_MASK&t;0xFFFFFFFF00000000
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_VALID | __DIRTY_BITS | __ACCESS_BITS)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(_PFN_MASK | __DIRTY_BITS | __ACCESS_BITS)
multiline_comment|/*&n; * All the normal masks have the &quot;page accessed&quot; bits on, as any time they are used,&n; * the page is accessed. They are cleared only by the page-out routines&n; */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOR | _PAGE_FOW | _PAGE_FOE)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_VALID | __ACCESS_BITS)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW | _PAGE_COW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_VALID | _PAGE_ASM | _PAGE_KRE | _PAGE_KWE)
DECL|macro|_PAGE_NORMAL
mdefine_line|#define _PAGE_NORMAL(x) __pgprot(_PAGE_VALID | __ACCESS_BITS | (x))
DECL|macro|_PAGE_P
mdefine_line|#define _PAGE_P(x) _PAGE_NORMAL((x) | (((x) &amp; _PAGE_FOW)?0:(_PAGE_FOW | _PAGE_COW)))
DECL|macro|_PAGE_S
mdefine_line|#define _PAGE_S(x) _PAGE_NORMAL(x)
multiline_comment|/*&n; * The hardware can handle write-only mappings, but as the alpha&n; * architecture does byte-wide writes with a read-modify-write&n; * sequence, it&squot;s not practical to have write-without-read privs.&n; * Thus the &quot;-w- -&gt; rw-&quot; and &quot;-wx -&gt; rwx&quot; mapping here (and in&n; * arch/alpha/mm/fault.c)&n; */
multiline_comment|/* xwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;_PAGE_P(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
DECL|macro|__P001
mdefine_line|#define __P001&t;_PAGE_P(_PAGE_FOE | _PAGE_FOW)
DECL|macro|__P010
mdefine_line|#define __P010&t;_PAGE_P(_PAGE_FOE)
DECL|macro|__P011
mdefine_line|#define __P011&t;_PAGE_P(_PAGE_FOE)
DECL|macro|__P100
mdefine_line|#define __P100&t;_PAGE_P(_PAGE_FOW | _PAGE_FOR)
DECL|macro|__P101
mdefine_line|#define __P101&t;_PAGE_P(_PAGE_FOW)
DECL|macro|__P110
mdefine_line|#define __P110&t;_PAGE_P(0)
DECL|macro|__P111
mdefine_line|#define __P111&t;_PAGE_P(0)
DECL|macro|__S000
mdefine_line|#define __S000&t;_PAGE_S(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
DECL|macro|__S001
mdefine_line|#define __S001&t;_PAGE_S(_PAGE_FOE | _PAGE_FOW)
DECL|macro|__S010
mdefine_line|#define __S010&t;_PAGE_S(_PAGE_FOE)
DECL|macro|__S011
mdefine_line|#define __S011&t;_PAGE_S(_PAGE_FOE)
DECL|macro|__S100
mdefine_line|#define __S100&t;_PAGE_S(_PAGE_FOW | _PAGE_FOR)
DECL|macro|__S101
mdefine_line|#define __S101&t;_PAGE_S(_PAGE_FOW)
DECL|macro|__S110
mdefine_line|#define __S110&t;_PAGE_S(0)
DECL|macro|__S111
mdefine_line|#define __S111&t;_PAGE_S(0)
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
id|pmd_t
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
id|__zero_page
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
mdefine_line|#define ZERO_PAGE __zero_page()
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;3
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)&t;&t;&bslash;&n;  ((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
r_extern
r_int
r_int
id|high_memory
suffix:semicolon
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
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
(paren
(paren
id|page
op_minus
id|PAGE_OFFSET
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
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
DECL|function|pmd_set
r_extern
r_inline
r_void
id|pmd_set
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pte_t
op_star
id|ptep
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
id|_PAGE_TABLE
op_or
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
op_minus
id|PAGE_OFFSET
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_set
r_extern
r_inline
r_void
id|pgd_set
c_func
(paren
id|pgd_t
op_star
id|pgdp
comma
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
id|_PAGE_TABLE
op_or
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pmdp
)paren
op_minus
id|PAGE_OFFSET
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
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
id|PAGE_OFFSET
op_plus
(paren
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PFN_MASK
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
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
id|PAGE_OFFSET
op_plus
(paren
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|_PFN_MASK
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_page
r_extern
r_inline
r_int
r_int
id|pgd_page
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
id|PAGE_OFFSET
op_plus
(paren
(paren
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PFN_MASK
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
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
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pte_inuse
r_extern
r_inline
r_int
id|pte_inuse
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_return
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|ptep
)paren
)braket
op_ne
l_int|1
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
DECL|function|pte_reuse
r_extern
r_inline
r_void
id|pte_reuse
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|ptep
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
)paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|ptep
)paren
)braket
op_increment
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
id|_PFN_MASK
)paren
op_ne
id|_PAGE_TABLE
op_logical_or
id|pmd_page
c_func
(paren
id|pmd
)paren
OG
id|high_memory
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
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pmd_inuse
r_extern
r_inline
r_int
id|pmd_inuse
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
r_return
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pmdp
)paren
)braket
op_ne
l_int|1
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
DECL|function|pmd_reuse
r_extern
r_inline
r_void
id|pmd_reuse
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pmdp
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
)paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pmdp
)paren
)braket
op_increment
suffix:semicolon
)brace
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
op_logical_neg
id|pgd_val
c_func
(paren
id|pgd
)paren
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
(paren
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
op_complement
id|_PFN_MASK
)paren
op_ne
id|_PAGE_TABLE
op_logical_or
id|pgd_page
c_func
(paren
id|pgd
)paren
OG
id|high_memory
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pgd_inuse
r_extern
r_inline
r_int
id|pgd_inuse
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
r_return
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pgdp
)paren
)braket
op_ne
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
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_reuse
r_extern
r_inline
r_void
id|pgd_reuse
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pgdp
)paren
)braket
op_amp
id|MAP_PAGE_RESERVED
)paren
)paren
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pgdp
)paren
)braket
op_increment
suffix:semicolon
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
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FOR
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
id|_PAGE_FOW
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
id|_PAGE_FOE
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
DECL|function|pte_cow
r_extern
r_inline
r_int
id|pte_cow
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
id|_PAGE_COW
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
id|_PAGE_FOW
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
id|_PAGE_FOR
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
id|_PAGE_FOE
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
id|__DIRTY_BITS
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
(paren
id|__ACCESS_BITS
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_uncow
r_extern
r_inline
id|pte_t
id|pte_uncow
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
id|_PAGE_COW
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
id|_PAGE_FOW
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
id|_PAGE_FOR
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
id|_PAGE_FOE
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
id|__DIRTY_BITS
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
id|__ACCESS_BITS
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkcow
r_extern
r_inline
id|pte_t
id|pte_mkcow
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
id|_PAGE_COW
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* &n; * To set the page-dir. Note the self-mapping in the last entry&n; *&n; * Also note that if we update the current process ptbr, we need to&n; * update the PAL-cached ptbr value as well.. There doesn&squot;t seem to&n; * be any &quot;wrptbr&quot; PAL-insn, but we can do a dummy swpctx to ourself&n; * instead.&n; */
DECL|function|SET_PAGE_DIR
r_extern
r_inline
r_void
id|SET_PAGE_DIR
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|pgd_t
op_star
id|pgdir
)paren
(brace
id|pgd_val
c_func
(paren
id|pgdir
(braket
id|PTRS_PER_PGD
)braket
)paren
op_assign
id|pte_val
c_func
(paren
id|mk_pte
c_func
(paren
(paren
r_int
r_int
)paren
id|pgdir
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
id|tsk-&gt;tss.ptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|pgdir
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;bis %0,%0,$16&bslash;n&bslash;t&quot;
l_string|&quot;call_pal %1&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|tsk-&gt;tss
)paren
comma
l_string|&quot;i&quot;
(paren
id|PAL_swpctx
)paren
suffix:colon
l_string|&quot;$0&quot;
comma
l_string|&quot;$1&quot;
comma
l_string|&quot;$16&quot;
comma
l_string|&quot;$22&quot;
comma
l_string|&quot;$23&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
)brace
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) pgd_offset((tsk),(address))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|function|pgd_offset
r_extern
r_inline
id|pgd_t
op_star
id|pgd_offset
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pgd_t
op_star
)paren
(paren
(paren
id|tsk-&gt;tss.ptbr
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|PAGE_OFFSET
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
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
id|pgd_page
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
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
)paren
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
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*      &n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any, and marks the page tables reserved.&n; */
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
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pte
)paren
)braket
op_assign
l_int|1
suffix:semicolon
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
id|pmd_set
c_func
(paren
id|pmd
comma
id|page
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
op_assign
id|MAP_PAGE_RESERVED
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
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
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
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
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pmd
)paren
)braket
op_assign
l_int|1
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
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
id|address
op_assign
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd_t
op_star
id|page
op_assign
(paren
id|pmd_t
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
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
r_if
c_cond
(paren
id|page
)paren
(brace
id|pgd_set
c_func
(paren
id|pgd
comma
id|page
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|page
)paren
)braket
op_assign
id|MAP_PAGE_RESERVED
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|pgd_set
c_func
(paren
id|pgd
comma
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
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad pgd in pmd_alloc: %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
id|BAD_PAGETABLE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|address
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
id|pmd_set
c_func
(paren
id|pmd
comma
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
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
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
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
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
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
id|address
op_assign
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd_t
op_star
id|page
op_assign
(paren
id|pmd_t
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
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
r_if
c_cond
(paren
id|page
)paren
(brace
id|pgd_set
c_func
(paren
id|pgd
comma
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
suffix:semicolon
)brace
id|pgd_set
c_func
(paren
id|pgd
comma
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
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad pgd in pmd_alloc: %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
id|BAD_PAGETABLE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|address
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
multiline_comment|/*&n; * The alpha doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
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
multiline_comment|/*&n; * Non-present pages: high 24 bits are offset, next 8 bits type,&n; * low 32 bits zero..&n; */
DECL|function|mk_swap_pte
r_extern
r_inline
id|pte_t
id|mk_swap_pte
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|offset
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
id|type
op_lshift
l_int|32
)paren
op_or
(paren
id|offset
op_lshift
l_int|40
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry) (((entry) &gt;&gt; 32) &amp; 0xff)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry) ((entry) &gt;&gt; 40)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset) pte_val(mk_swap_pte((type),(offset)))
macro_line|#endif /* _ALPHA_PGTABLE_H */
eof