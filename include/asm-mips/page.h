macro_line|#ifndef __ASM_MIPS_PAGE_H
DECL|macro|__ASM_MIPS_PAGE_H
mdefine_line|#define __ASM_MIPS_PAGE_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|invalidate
mdefine_line|#define invalidate()&t;tlbflush();
r_extern
id|asmlinkage
r_void
id|tlbflush
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;&t;&t;12
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;&t;22
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) ((addr) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_PAGE_RESERVED
mdefine_line|#define MAP_PAGE_RESERVED (1&lt;&lt;15)
DECL|typedef|mem_map_t
r_typedef
r_int
r_int
id|mem_map_t
suffix:semicolon
multiline_comment|/*&n; * Note that we shift the lower 32bits of each EntryLo[01] entry&n; * 6 bits to the left. That way we can convert the PFN into the&n; * physical address by a single &squot;and&squot; operation and gain 6 aditional&n; * bits for storing information which isn&squot;t present in a normal&n; * MIPS page table.&n; * I&squot;ve also changed the naming of some bits so that they conform&n; * the i386 naming as much as possible.&n; * PAGE_USER isn&squot;t implemented in software yet.&n; */
DECL|macro|PAGE_PRESENT
mdefine_line|#define PAGE_PRESENT               (1&lt;&lt;0)   /* implemented in software */
DECL|macro|PAGE_COW
mdefine_line|#define PAGE_COW                   (1&lt;&lt;1)   /* implemented in software */
DECL|macro|PAGE_DIRTY
mdefine_line|#define PAGE_DIRTY                 (1&lt;&lt;2)   /* implemented in software */
DECL|macro|PAGE_USER
mdefine_line|#define PAGE_USER                  (1&lt;&lt;3)   /* implemented in software */
DECL|macro|PAGE_UNUSED1
mdefine_line|#define PAGE_UNUSED1               (1&lt;&lt;4)   /* implemented in software */
DECL|macro|PAGE_UNUSED2
mdefine_line|#define PAGE_UNUSED2               (1&lt;&lt;5)   /* implemented in software */
DECL|macro|PAGE_GLOBAL
mdefine_line|#define PAGE_GLOBAL                (1&lt;&lt;6)
DECL|macro|PAGE_ACCESSED
mdefine_line|#define PAGE_ACCESSED              (1&lt;&lt;7)   /* The MIPS valid bit      */
DECL|macro|PAGE_RW
mdefine_line|#define PAGE_RW                    (1&lt;&lt;8)   /* The MIPS dirty bit      */
DECL|macro|CACHE_CACHABLE_NO_WA
mdefine_line|#define CACHE_CACHABLE_NO_WA       (0&lt;&lt;9)
DECL|macro|CACHE_CACHABLE_WA
mdefine_line|#define CACHE_CACHABLE_WA          (1&lt;&lt;9)
DECL|macro|CACHE_UNCACHED
mdefine_line|#define CACHE_UNCACHED             (2&lt;&lt;9)
DECL|macro|CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define CACHE_CACHABLE_NONCOHERENT (3&lt;&lt;9)
DECL|macro|CACHE_CACHABLE_CE
mdefine_line|#define CACHE_CACHABLE_CE          (4&lt;&lt;9)
DECL|macro|CACHE_CACHABLE_COW
mdefine_line|#define CACHE_CACHABLE_COW         (5&lt;&lt;9)
DECL|macro|CACHE_CACHABLE_CUW
mdefine_line|#define CACHE_CACHABLE_CUW         (6&lt;&lt;9)
DECL|macro|CACHE_MASK
mdefine_line|#define CACHE_MASK                 (7&lt;&lt;9)
DECL|macro|PAGE_PRIVATE
mdefine_line|#define PAGE_PRIVATE    (PAGE_PRESENT | PAGE_ACCESSED | PAGE_DIRTY | PAGE_RW | &bslash;&n;                         PAGE_COW | CACHE_CACHABLE_NO_WA)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     (PAGE_PRESENT | PAGE_ACCESSED | PAGE_DIRTY | PAGE_RW | &bslash;&n;                         CACHE_CACHABLE_NO_WA)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       (PAGE_PRESENT | PAGE_ACCESSED | PAGE_COW | &bslash;&n;                         CACHE_CACHABLE_NO_WA)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   (PAGE_PRESENT | PAGE_ACCESSED | CACHE_CACHABLE_NO_WA)
DECL|macro|PAGE_TABLE
mdefine_line|#define PAGE_TABLE      (PAGE_PRESENT | PAGE_ACCESSED | PAGE_DIRTY | PAGE_RW | &bslash;&n;                         CACHE_CACHABLE_NO_WA)
DECL|macro|PAGE_CHG_MASK
mdefine_line|#define PAGE_CHG_MASK (PAGE_MASK | PAGE_ACCESSED | PAGE_DIRTY | CACHE_MASK)
macro_line|#ifdef __KERNEL__
multiline_comment|/* page table for 0-4MB for everybody */
r_extern
r_int
r_int
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
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
multiline_comment|/* to mask away the intra-page address bits */
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;&t;(~(PAGE_SIZE-1))
multiline_comment|/* to mask away the intra-page address bits */
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;&t;(~(PGDIR_SIZE-1))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;2
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) &bslash;&n;((((unsigned long)(address)) &gt;&gt; 22) + (unsigned long *) (tsk)-&gt;tss.pg_dir)
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)&t;&t;&bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* the no. of pointers that fit on a page */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;&t;&t;(PAGE_SIZE/sizeof(void*))
multiline_comment|/* to set the page-dir */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) &bslash;&n;do { &bslash;&n;&t;(tsk)-&gt;tss.pg_dir = (unsigned long) (pgdir); &bslash;&n;&t;if ((tsk) == current) &bslash;&n;&t;&t;invalidate(); &bslash;&n;} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_MIPS_PAGE_H */
eof
