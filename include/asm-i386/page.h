macro_line|#ifndef _I386_PAGE_H
DECL|macro|_I386_PAGE_H
mdefine_line|#define _I386_PAGE_H
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__(&quot;movl %%cr3,%%eax&bslash;n&bslash;tmovl %%eax,%%cr3&quot;: : :&quot;ax&quot;)
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
DECL|macro|PAGE_PRESENT
mdefine_line|#define PAGE_PRESENT&t;0x001
DECL|macro|PAGE_RW
mdefine_line|#define PAGE_RW&t;&t;0x002
DECL|macro|PAGE_USER
mdefine_line|#define PAGE_USER&t;0x004
DECL|macro|PAGE_PWT
mdefine_line|#define PAGE_PWT&t;0x008&t;/* 486 only - not used currently */
DECL|macro|PAGE_PCD
mdefine_line|#define PAGE_PCD&t;0x010&t;/* 486 only - not used currently */
DECL|macro|PAGE_ACCESSED
mdefine_line|#define PAGE_ACCESSED&t;0x020
DECL|macro|PAGE_DIRTY
mdefine_line|#define PAGE_DIRTY&t;0x040
DECL|macro|PAGE_COW
mdefine_line|#define PAGE_COW&t;0x200&t;/* implemented in software (one of the AVL bits) */
DECL|macro|PAGE_PRIVATE
mdefine_line|#define PAGE_PRIVATE&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_EXECONLY
mdefine_line|#define PAGE_EXECONLY&t;(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_TABLE
mdefine_line|#define PAGE_TABLE&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_CHG_MASK
mdefine_line|#define PAGE_CHG_MASK (PAGE_MASK | PAGE_ACCESSED | PAGE_DIRTY | PAGE_PWT | PAGE_PCD)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Define this if things work differently on a i386 and a i486:&n; * it will (on a i486) warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; */
DECL|macro|CONFIG_TEST_VERIFY_AREA
macro_line|#undef CONFIG_TEST_VERIFY_AREA
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
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) &bslash;&n;((((unsigned long)(address)) &gt;&gt; 22) + (unsigned long *) (tsk)-&gt;tss.cr3)
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)&t;&t;&bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* the no. of pointers that fit on a page */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;&t;&t;(PAGE_SIZE/sizeof(void*))
multiline_comment|/* to set the page-dir */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) &bslash;&n;do { &bslash;&n;&t;(tsk)-&gt;tss.cr3 = (unsigned long) (pgdir); &bslash;&n;&t;if ((tsk) == current) &bslash;&n;&t;&t;__asm__ __volatile__(&quot;movl %0,%%cr3&quot;: :&quot;a&quot; ((tsk)-&gt;tss.cr3)); &bslash;&n;} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_PAGE_H */
eof
