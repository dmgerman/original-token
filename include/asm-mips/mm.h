macro_line|#ifndef __ASM_MIPS_MM_H
DECL|macro|__ASM_MIPS_MM_H
mdefine_line|#define __ASM_MIPS_MM_H
macro_line|#if defined (__KERNEL__)
multiline_comment|/*&n; * Note that we shift the lower 32bits of each EntryLo[01] entry&n; * 6 bits to the left. That way we can convert the PFN into the&n; * physical address by a single &squot;and&squot; operation and gain 6 additional&n; * bits for storing information which isn&squot;t present in a normal&n; * MIPS page table.&n; * I&squot;ve also changed the naming of some bits so that they conform&n; * the i386 naming as much as possible.&n; * PAGE_USER isn&squot;t implemented in software yet.&n; */
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
mdefine_line|#define PAGE_ACCESSED              (1&lt;&lt;7)   /* The Mips valid bit      */
DECL|macro|PAGE_RW
mdefine_line|#define PAGE_RW                    (1&lt;&lt;8)   /* The Mips dirty bit      */
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
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_int
r_int
id|invalid_pg_table
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * memory.c &amp; swap.c&n; */
r_extern
r_void
id|mem_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
suffix:semicolon
macro_line|#endif /* !defined (__ASSEMBLY__) */
macro_line|#endif /* defined (__KERNEL__) */
macro_line|#endif /* __ASM_MIPS_MM_H */
eof
