multiline_comment|/* page.h:  Various defines and such for MMU operations on the Sparc for&n; *          the Linux kernel.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PAGE_H
DECL|macro|_SPARC_PAGE_H
mdefine_line|#define _SPARC_PAGE_H
macro_line|#include &lt;asm/asi.h&gt;        /* for get/set segmap/pte routines */
macro_line|#include &lt;asm/contregs.h&gt;   /* for switch_to_context */
macro_line|#include &lt;asm/head.h&gt;       /* for KERNBASE */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   12             /* This is the virtual page... */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET    KERNBASE
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1 &lt;&lt; PAGE_SHIFT)
multiline_comment|/* to mask away the intra-page address bits */
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK         (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* The following structure is used to hold the physical&n; * memory configuration of the machine.  This is filled in&n; * probe_memory() and is later used by mem_init() to set up&n; * mem_map[].  We statically allocate SPARC_PHYS_BANKS of&n; * these structs, this is arbitrary.  The entry after the&n; * last valid one has num_bytes==0.&n; */
DECL|struct|sparc_phys_banks
r_struct
id|sparc_phys_banks
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_PHYS_BANKS
mdefine_line|#define SPARC_PHYS_BANKS 32
r_extern
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
DECL|macro|CONFIG_STRICT_MM_TYPECHECKS
mdefine_line|#define CONFIG_STRICT_MM_TYPECHECKS
macro_line|#ifdef CONFIG_STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      (x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
multiline_comment|/* The current va context is global and known, so all that is needed to&n; * do an invalidate is flush the VAC on a sun4c or call the ASI flushing&n; * routines on a SRMMU.&n; */
r_extern
r_void
(paren
op_star
id|invalidate
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)  (((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* We now put the free page pool mapped contiguously in high memory above&n; * the kernel.&n; */
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) ((((unsigned long)addr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_PAGE_RESERVED
mdefine_line|#define MAP_PAGE_RESERVED (1&lt;&lt;15)
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* The rest is kind of funky because on the sparc, the offsets into the mmu &n; * entries are encoded in magic alternate address space tables. I will &n; * probably find some nifty inline assembly routines to do the equivalent. &n; * Much thought must go into this code.   (davem@caip.rutgers.edu)&n; */
multiline_comment|/* Bitfields within a Sparc sun4c PTE (page table entry). */
DECL|macro|PTE_V
mdefine_line|#define PTE_V     0x80000000   /* valid bit */
DECL|macro|PTE_ACC
mdefine_line|#define PTE_ACC   0x60000000   /* access bits */
DECL|macro|PTE_W
mdefine_line|#define PTE_W     0x40000000   /* writable bit */
DECL|macro|PTE_P
mdefine_line|#define PTE_P     0x20000000   /* privileged page */
DECL|macro|PTE_NC
mdefine_line|#define PTE_NC    0x10000000   /* page is non-cacheable */
DECL|macro|PTE_TYP
mdefine_line|#define PTE_TYP   0x0c000000   /* page type field */
DECL|macro|PTE_RMEM
mdefine_line|#define PTE_RMEM  0x00000000   /* type == on board real memory */
DECL|macro|PTE_IO
mdefine_line|#define PTE_IO    0x04000000   /* type == i/o area */
DECL|macro|PTE_VME16
mdefine_line|#define PTE_VME16 0x08000000   /* type == 16-bit VME area */
DECL|macro|PTE_VME32
mdefine_line|#define PTE_VME32 0x0c000000   /* type == 32-bit VME area */
DECL|macro|PTE_R
mdefine_line|#define PTE_R     0x02000000   /* page has been referenced */
DECL|macro|PTE_M
mdefine_line|#define PTE_M     0x01000000   /* page has been modified */
DECL|macro|PTE_RESV
mdefine_line|#define PTE_RESV  0x00f80000   /* reserved bits */
DECL|macro|PTE_PHYPG
mdefine_line|#define PTE_PHYPG 0x0007ffff   /* phys pg number, sun4c only uses 16bits */
multiline_comment|/* SRMMU defines */
multiline_comment|/* The fields in an srmmu virtual address when it gets translated.&n; *&n; *  -------------------------------------------------------------&n; *  |   INDEX 1   |   INDEX 2   |   INDEX 3   |   PAGE OFFSET   |&n; *  -------------------------------------------------------------&n; *  31          24 23        18  17         12  11              0&n; */
DECL|macro|SRMMU_IDX1_SHIFT
mdefine_line|#define SRMMU_IDX1_SHIFT      24
DECL|macro|SRMMU_IDX1_MASK
mdefine_line|#define SRMMU_IDX1_MASK       0xff000000
DECL|macro|SRMMU_IDX2_SHIFT
mdefine_line|#define SRMMU_IDX2_SHIFT      18
DECL|macro|SRMMU_IDX2_MASK
mdefine_line|#define SRMMU_IDX2_MASK       0x00fc0000
DECL|macro|SRMMU_IDX3_SHIFT
mdefine_line|#define SRMMU_IDX3_SHIFT      12
DECL|macro|SRMMU_IDX3_MASK
mdefine_line|#define SRMMU_IDX3_MASK       0x0003f000
DECL|macro|SRMMU_PGOFFSET_MASK
mdefine_line|#define SRMMU_PGOFFSET_MASK   0x00000fff
multiline_comment|/* The page table sizes for the various levels in bytes. */
DECL|macro|SRMMU_LV1_PTSIZE
mdefine_line|#define SRMMU_LV1_PTSIZE      1024
DECL|macro|SRMMU_LV2_PTSIZE
mdefine_line|#define SRMMU_LV2_PTSIZE      256
DECL|macro|SRMMU_LV3_PTSIZE
mdefine_line|#define SRMMU_LV3_PTSIZE      256
multiline_comment|/* Definition of the values in the ET field of PTD&squot;s and PTE&squot;s */
DECL|macro|SRMMU_ET_INVALID
mdefine_line|#define SRMMU_ET_INVALID      0x0
DECL|macro|SRMMU_ET_PTD
mdefine_line|#define SRMMU_ET_PTD          0x1
DECL|macro|SRMMU_ET_PTE
mdefine_line|#define SRMMU_ET_PTE          0x2
DECL|macro|SRMMU_ET_RESV
mdefine_line|#define SRMMU_ET_RESV         0x3
DECL|macro|SRMMU_ET_PTDBAD
mdefine_line|#define SRMMU_ET_PTDBAD       0x3   /* Upward compatability my butt. */
multiline_comment|/* Page table directory bits.&n; *&n; * ----------------&n; * |  PTP    | ET |&n; * ----------------&n; * 31       2 1  0&n; *&n; * PTP:  The physical page table pointer.  This value appears on&n; *       bits 35-&gt;6 on the physical address bus during translation.&n; *&n; * ET:   Entry type field.  Must be 1 for a PTD.&n; */
DECL|macro|SRMMU_PTD_PTP_SHIFT
mdefine_line|#define SRMMU_PTD_PTP_SHIFT         0x2
DECL|macro|SRMMU_PTD_PTP_MASK
mdefine_line|#define SRMMU_PTD_PTP_MASK          0xfffffffc
DECL|macro|SRMMU_PTD_PTP_PADDR_SHIFT
mdefine_line|#define SRMMU_PTD_PTP_PADDR_SHIFT   0x4
DECL|macro|SRMMU_PTD_ET_SHIFT
mdefine_line|#define SRMMU_PTD_ET_SHIFT          0x0
DECL|macro|SRMMU_PTD_ET_MASK
mdefine_line|#define SRMMU_PTD_ET_MASK           0x00000003
multiline_comment|/* Page table entry bits.&n; *&n; * -------------------------------------------------&n; * |  Physical Page Number  | C | M | R | ACC | ET |&n; * -------------------------------------------------&n; * 31                     8   7   6   5  4   2  1  0&n; *&n; * PPN: Physical page number, high order 24 bits of the 36-bit&n; *      physical address, thus is you mask off all the non&n; *      PPN bits you have the physical address of your page.&n; *      No shifting necessary.&n; *&n; * C:   Whether the page is cacheable in the mmu TLB or not.  If&n; *      not set the CPU cannot cache values to these addresses. For&n; *      IO space translations this bit should be clear.&n; *&n; * M:   Modified.  This tells whether the page has been written to&n; *      since the bit was last cleared.  NOTE: this does not include&n; *      accesses via the ASI physical page pass through since that does&n; *      not use the MMU.&n; *&n; * R:   References.  This tells whether the page has been referenced&n; *      in any way shape or form since the last clearing of the bit.&n; *      NOTE: this does not include accesses via the ASI physical page&n; *      pass through since that does not use the MMU.&n; *&n; * ACC: Access permissions for this page.  This is further explained below&n; *      with appropriate macros.&n; */
DECL|macro|SRMMU_PTE_PPN_SHIFT
mdefine_line|#define SRMMU_PTE_PPN_SHIFT         0x8
DECL|macro|SRMMU_PTE_PPN_MASK
mdefine_line|#define SRMMU_PTE_PPN_MASK          0xffffff00
DECL|macro|SRMMU_PTE_PPN_PADDR_SHIFT
mdefine_line|#define SRMMU_PTE_PPN_PADDR_SHIFT   0x4
DECL|macro|SRMMU_PTE_C_SHIFT
mdefine_line|#define SRMMU_PTE_C_SHIFT           0x7
DECL|macro|SRMMU_PTE_C_MASK
mdefine_line|#define SRMMU_PTE_C_MASK            0x00000080
DECL|macro|SRMMU_PTE_M_SHIFT
mdefine_line|#define SRMMU_PTE_M_SHIFT           0x6
DECL|macro|SRMMU_PTE_M_MASK
mdefine_line|#define SRMMU_PTE_M_MASK            0x00000040
DECL|macro|SRMMU_PTE_R_SHIFT
mdefine_line|#define SRMMU_PTE_R_SHIFT           0x5
DECL|macro|SRMMU_PTE_R_MASK
mdefine_line|#define SRMMU_PTE_R_MASK            0x00000020
DECL|macro|SRMMU_PTE_ACC_SHIFT
mdefine_line|#define SRMMU_PTE_ACC_SHIFT         0x2
DECL|macro|SRMMU_PTE_ACC_MASK
mdefine_line|#define SRMMU_PTE_ACC_MASK          0x0000001c
DECL|macro|SRMMU_PTE_ET_SHIFT
mdefine_line|#define SRMMU_PTE_ET_SHIFT          0x0
DECL|macro|SRMMU_PTE_ET_MASK
mdefine_line|#define SRMMU_PTE_ET_MASK           0x00000003
multiline_comment|/* SRMMU pte access bits.&n; *&n; * BIT    USER ACCESS          SUPERVISOR ACCESS&n; * ---    --------------       -----------------&n; * 0x0    read only            read only&n; * 0x1    read&amp;write           read&amp;write&n; * 0x2    read&amp;execute         read&amp;execute&n; * 0x3    read&amp;write&amp;execute   read&amp;write&amp;execute&n; * 0x4    execute only         execute only&n; * 0x5    read only            read&amp;write&n; * 0x6    ACCESS DENIED        read&amp;execute&n; * 0x7    ACCESS DENIED        read&amp;write&amp;execute&n; *&n; * All these values are shifted left two bits.&n; */
DECL|macro|SRMMU_ACC_US_RDONLY
mdefine_line|#define SRMMU_ACC_US_RDONLY      0x00
DECL|macro|SRMMU_ACC_US_RDWR
mdefine_line|#define SRMMU_ACC_US_RDWR        0x04
DECL|macro|SRMMU_ACC_US_RDEXEC
mdefine_line|#define SRMMU_ACC_US_RDEXEC      0x08
DECL|macro|SRMMU_ACC_US_RDWREXEC
mdefine_line|#define SRMMU_ACC_US_RDWREXEC    0x0c
DECL|macro|SRMMU_ACC_US_EXECONLY
mdefine_line|#define SRMMU_ACC_US_EXECONLY    0x10
DECL|macro|SRMMU_ACC_U_RDONLY
mdefine_line|#define SRMMU_ACC_U_RDONLY       0x14
DECL|macro|SRMMU_ACC_S_RDWR
mdefine_line|#define SRMMU_ACC_S_RDWR         0x14
DECL|macro|SRMMU_ACC_U_ACCDENIED
mdefine_line|#define SRMMU_ACC_U_ACCDENIED    0x18
DECL|macro|SRMMU_ACC_S_RDEXEC
mdefine_line|#define SRMMU_ACC_S_RDEXEC       0x18
DECL|macro|SRMMU_ACC_U_ACCDENIED2
mdefine_line|#define SRMMU_ACC_U_ACCDENIED2   0x1c
DECL|macro|SRMMU_ACC_S_RDWREXEC
mdefine_line|#define SRMMU_ACC_S_RDWREXEC     0x1c
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* SUN4C pte, segmap, and context manipulation */
DECL|function|get_segmap
r_extern
id|__inline__
r_int
r_int
id|get_segmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
(paren
id|entry
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|put_segmap
r_extern
id|__inline__
r_void
id|put_segmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba %1, [%0] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|entry
op_amp
l_int|0xff
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|get_pte
r_extern
id|__inline__
r_int
r_int
id|get_pte
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|put_pte
r_extern
id|__inline__
r_void
id|put_pte
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %1, [%0] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|entry
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
(paren
op_star
id|switch_to_context
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|function|get_context
r_extern
id|__inline__
r_int
id|get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|ctx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
DECL|typedef|mem_map_t
r_typedef
r_int
r_int
id|mem_map_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_PAGE_H */
eof
