multiline_comment|/* pgtsun4c.h:  Sun4c specific pgtable.h defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PGTSUN4C_H
DECL|macro|_SPARC_PGTSUN4C_H
mdefine_line|#define _SPARC_PGTSUN4C_H
DECL|macro|SUN4C_PAGE_TABLE_SIZE
mdefine_line|#define SUN4C_PAGE_TABLE_SIZE 0x100   /* 64 entries, 4 bytes a piece */
multiline_comment|/* NOTE:  Now we put the free page pool and the page structures&n; *        up in high memory above the kernel image which itself&n; *        starts at KERNBASE.  Also note PAGE_OFFSET in page.h&n; *        This is just like what Linus does on the ALPHA.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|SUN4C_PMD_SHIFT
mdefine_line|#define SUN4C_PMD_SHIFT       22
DECL|macro|SUN4C_PMD_SIZE
mdefine_line|#define SUN4C_PMD_SIZE        (1UL &lt;&lt; SUN4C_PMD_SHIFT)
DECL|macro|SUN4C_PMD_MASK
mdefine_line|#define SUN4C_PMD_MASK        (~(SUN4C_PMD_SIZE-1))
DECL|macro|SUN4C_PMD_ALIGN
mdefine_line|#define SUN4C_PMD_ALIGN(addr) (((addr)+SUN4C_PMD_SIZE-1)&amp;SUN4C_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|SUN4C_PGDIR_SHIFT
mdefine_line|#define SUN4C_PGDIR_SHIFT       22
DECL|macro|SUN4C_PGDIR_SIZE
mdefine_line|#define SUN4C_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_PGDIR_SHIFT)
DECL|macro|SUN4C_PGDIR_MASK
mdefine_line|#define SUN4C_PGDIR_MASK        (~(SUN4C_PGDIR_SIZE-1))
DECL|macro|SUN4C_PGDIR_ALIGN
mdefine_line|#define SUN4C_PGDIR_ALIGN(addr) (((addr)+SUN4C_PGDIR_SIZE-1)&amp;SUN4C_PGDIR_MASK)
multiline_comment|/* To make sun4c_paging_init() happy, I provide the following macros. */
DECL|macro|SUN4C_REAL_PGDIR_SHIFT
mdefine_line|#define SUN4C_REAL_PGDIR_SHIFT  18
DECL|macro|SUN4C_REAL_PGDIR_SIZE
mdefine_line|#define SUN4C_REAL_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_REAL_PGDIR_SHIFT)
DECL|macro|SUN4C_REAL_PGDIR_MASK
mdefine_line|#define SUN4C_REAL_PGDIR_MASK        (~(SUN4C_REAL_PGDIR_SIZE-1))
DECL|macro|SUN4C_REAL_PGDIR_ALIGN
mdefine_line|#define SUN4C_REAL_PGDIR_ALIGN(addr) (((addr)+SUN4C_REAL_PGDIR_SIZE-1)&amp;SUN4C_REAL_PGDIR_MASK)
multiline_comment|/*&n; * To be efficient, and not have to worry about allocating such&n; * a huge pgd, we make the kernel sun4c tables each hold 1024&n; * entries and the pgd similarly.&n; */
DECL|macro|SUN4C_PTRS_PER_PTE
mdefine_line|#define SUN4C_PTRS_PER_PTE    1024
DECL|macro|SUN4C_PTRS_PER_PMD
mdefine_line|#define SUN4C_PTRS_PER_PMD    1
DECL|macro|SUN4C_PTRS_PER_PGD
mdefine_line|#define SUN4C_PTRS_PER_PGD    1024
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|SUN4C_VMALLOC_OFFSET
mdefine_line|#define SUN4C_VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|SUN4C_VMALLOC_START
mdefine_line|#define SUN4C_VMALLOC_START ((high_memory + SUN4C_VMALLOC_OFFSET) &amp; ~(SUN4C_VMALLOC_OFFSET-1))
multiline_comment|/*&n; * Sparc SUN4C page table fields. (for now, basically the same as the i386)&n; */
DECL|macro|_SUN4C_PAGE_VALID
mdefine_line|#define _SUN4C_PAGE_VALID     0x80000000   /* valid page */
DECL|macro|_SUN4C_PAGE_WRITE
mdefine_line|#define _SUN4C_PAGE_WRITE     0x40000000   /* can be written to */
DECL|macro|_SUN4C_PAGE_USER
mdefine_line|#define _SUN4C_PAGE_USER      0x00000000   /* User page */
DECL|macro|_SUN4C_PAGE_NOCACHE
mdefine_line|#define _SUN4C_PAGE_NOCACHE   0x10000000   /* non-cacheable page */
DECL|macro|_SUN4C_PAGE_PRIV
mdefine_line|#define _SUN4C_PAGE_PRIV      0x20000000   /* bit to signify privileged page */
DECL|macro|_SUN4C_PAGE_REF
mdefine_line|#define _SUN4C_PAGE_REF       0x02000000   /* Page has been accessed/referenced */
DECL|macro|_SUN4C_PAGE_DIRTY
mdefine_line|#define _SUN4C_PAGE_DIRTY     0x01000000   /* Page has been modified, is dirty */
DECL|macro|_SUN4C_PAGE_COW
mdefine_line|#define _SUN4C_PAGE_COW       0x00800000   /* COW page */
multiline_comment|/* Sparc sun4c mmu has only a writable bit. Thus if a page is valid it can be&n; * read in a load, and executed as code automatically. Although, the memory &n; * fault hardware does make a distinction between data-read faults and &n; * insn-read faults which is determined by which trap happened plus magic&n; * sync/async fault register values which must be checked in the actual&n; * fault handler.&n; */
DECL|macro|_SUN4C_PFN_MASK
mdefine_line|#define _SUN4C_PFN_MASK       0x0000ffff    /* just the page frame number */
DECL|macro|_SUN4C_MMU_MASK
mdefine_line|#define _SUN4C_MMU_MASK       0xffff0000    /* just the non-page pte bits */
multiline_comment|/* The following are for pgd/pmd&squot;s */
DECL|macro|_SUN4C_PGD_PFN_MASK
mdefine_line|#define _SUN4C_PGD_PFN_MASK   0x00ffffff    /* bits to hold page tables address */
DECL|macro|_SUN4C_PGD_MMU_MASK
mdefine_line|#define _SUN4C_PGD_MMU_MASK   0xff000000    /* pgd/pfn protection bits          */
DECL|macro|_SUN4C_PGD_PAGE_SHIFT
mdefine_line|#define _SUN4C_PGD_PAGE_SHIFT 8             /* bits to shift to obtain address  */
multiline_comment|/* We want the swapper not to swap out page tables, thus dirty and writable&n; * so that the kernel can change the entries as needed. Also valid for&n; * obvious reasons.&n; */
DECL|macro|_SUN4C_PAGE_TABLE
mdefine_line|#define _SUN4C_PAGE_TABLE     (_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | _SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY | _SUN4C_PAGE_PRIV | _SUN4C_PAGE_NOCACHE) /* No cache for now */
DECL|macro|_SUN4C_PAGE_CHG_MASK
mdefine_line|#define _SUN4C_PAGE_CHG_MASK  (_SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY | _SUN4C_PFN_MASK)
DECL|macro|_SUN4C_PGD_CHG_MASK
mdefine_line|#define _SUN4C_PGD_CHG_MASK   (_SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY | _SUN4C_PGD_PFN_MASK)
DECL|macro|SUN4C_PAGE_NONE
mdefine_line|#define SUN4C_PAGE_NONE       __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_SHARED
mdefine_line|#define SUN4C_PAGE_SHARED     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_COPY
mdefine_line|#define SUN4C_PAGE_COPY       __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_REF | _SUN4C_PAGE_COW)
DECL|macro|SUN4C_PAGE_READONLY
mdefine_line|#define SUN4C_PAGE_READONLY   __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_REF)
DECL|macro|SUN4C_PAGE_KERNEL
mdefine_line|#define SUN4C_PAGE_KERNEL     __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_WRITE | _SUN4C_PAGE_PRIV | _SUN4C_PAGE_REF | _SUN4C_PAGE_DIRTY | _SUN4C_PAGE_NOCACHE)
DECL|macro|SUN4C_PAGE_INVALID
mdefine_line|#define SUN4C_PAGE_INVALID    __pgprot(0)
DECL|macro|_SUN4C_PAGE_NORMAL
mdefine_line|#define _SUN4C_PAGE_NORMAL(x) __pgprot(_SUN4C_PAGE_VALID | _SUN4C_PAGE_REF | (x))
multiline_comment|/* The Sun4c mmu physical segment map allocation data structure.&n; * For each physical segmap available on the mmu we have one entry,&n; * 127 on the sun4c (except SparcStation 2&squot;s which seem to have 255)&n; * and 512 on the sun4.  Each segmap can be in various stages of&n; * allocation.&n; */
DECL|macro|PSEG_ENTRIES
mdefine_line|#define PSEG_ENTRIES  513     /* We allocate 513 entries for simplicity */
r_extern
r_int
r_int
id|phys_seg_map
(braket
id|PSEG_ENTRIES
)braket
suffix:semicolon
r_extern
r_int
r_int
id|phys_seg_life
(braket
id|PSEG_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* for phys_seg_map entries */
DECL|macro|PSEG_AVL
mdefine_line|#define PSEG_AVL      0x0     /* Physical segment is available/free */
DECL|macro|PSEG_USED
mdefine_line|#define PSEG_USED     0x1     /* A segmap currently being used */
DECL|macro|PSEG_RSV
mdefine_line|#define PSEG_RSV      0x2     /* This segmap is reserved (used for proms addr space) */
DECL|macro|PSEG_KERNEL
mdefine_line|#define PSEG_KERNEL   0x3     /* This is a kernel hard segment, cannot deallocate */
multiline_comment|/* for phys_seg_life entries */
multiline_comment|/* The idea is, every call to update_mmu_cache we increment all the life&n; * counters.  When we re-allocate or allocate a physical segment for the&n; * first time we set the phys_seg_life entry to PSEG_BORN.  Also, when we&n; * fill a pte for a segment already loaded we *decrease* the life count&n; * by two for that segment.  We&squot;ll see how this works.&n; */
DECL|macro|PSEG_BORN
mdefine_line|#define PSEG_BORN     0x00     /* Just allocated */
macro_line|#endif /* !(_SPARC_PGTSUN4C_H) */
eof
