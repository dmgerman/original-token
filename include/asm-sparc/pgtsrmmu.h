multiline_comment|/* $Id: pgtsrmmu.h,v 1.9 1995/11/25 02:32:24 davem Exp $&n; * pgtsrmmu.h:  SRMMU page table defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/page.h&gt;  /* just in case */
macro_line|#ifndef _SPARC_PGTSRMMU_H
DECL|macro|_SPARC_PGTSRMMU_H
mdefine_line|#define _SPARC_PGTSRMMU_H
DECL|macro|SRMMU_PAGE_TABLE_SIZE
mdefine_line|#define SRMMU_PAGE_TABLE_SIZE 0x100 /* 64 entries, 4 bytes a piece */
DECL|macro|SRMMU_PMD_TABLE_SIZE
mdefine_line|#define SRMMU_PMD_TABLE_SIZE  0x100 /* 64 entries, 4 bytes a piece */
DECL|macro|SRMMU_PGD_TABLE_SIZE
mdefine_line|#define SRMMU_PGD_TABLE_SIZE  0x400 /* 256 entries, 4 bytes a piece */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|SRMMU_PMD_SHIFT
mdefine_line|#define SRMMU_PMD_SHIFT       18
DECL|macro|SRMMU_PMD_SIZE
mdefine_line|#define SRMMU_PMD_SIZE        (1UL &lt;&lt; SRMMU_PMD_SHIFT)
DECL|macro|SRMMU_PMD_MASK
mdefine_line|#define SRMMU_PMD_MASK        (~(SRMMU_PMD_SIZE-1))
DECL|macro|SRMMU_PMD_ALIGN
mdefine_line|#define SRMMU_PMD_ALIGN(addr) (((addr)+SRMMU_PMD_SIZE-1)&amp;SRMMU_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|SRMMU_PGDIR_SHIFT
mdefine_line|#define SRMMU_PGDIR_SHIFT       24
DECL|macro|SRMMU_PGDIR_SIZE
mdefine_line|#define SRMMU_PGDIR_SIZE        (1UL &lt;&lt; SRMMU_PGDIR_SHIFT)
DECL|macro|SRMMU_PGDIR_MASK
mdefine_line|#define SRMMU_PGDIR_MASK        (~(SRMMU_PGDIR_SIZE-1))
DECL|macro|SRMMU_PGDIR_ALIGN
mdefine_line|#define SRMMU_PGDIR_ALIGN(addr) (((addr)+SRMMU_PGDIR_SIZE-1)&amp;SRMMU_PGDIR_MASK)
multiline_comment|/*&n; * Three-level on SRMMU.&n; */
DECL|macro|SRMMU_PTRS_PER_PTE
mdefine_line|#define SRMMU_PTRS_PER_PTE    64
DECL|macro|SRMMU_PTRS_PER_PMD
mdefine_line|#define SRMMU_PTRS_PER_PMD    64
DECL|macro|SRMMU_PTRS_PER_PGD
mdefine_line|#define SRMMU_PTRS_PER_PGD    256
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|SRMMU_VMALLOC_OFFSET
mdefine_line|#define SRMMU_VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|SRMMU_VMALLOC_START
mdefine_line|#define SRMMU_VMALLOC_START ((high_memory + SRMMU_VMALLOC_OFFSET) &amp; ~(SRMMU_VMALLOC_OFFSET-1))
multiline_comment|/*&n; * Sparc SRMMU page table fields.&n; */
DECL|macro|_SRMMU_PAGE_VALID
mdefine_line|#define _SRMMU_PAGE_VALID      (SRMMU_ET_PTE)
DECL|macro|_SRMMU_PMD_VALID
mdefine_line|#define _SRMMU_PMD_VALID       (SRMMU_ET_PTD)
DECL|macro|_SRMMU_PGD_VALID
mdefine_line|#define _SRMMU_PGD_VALID       (SRMMU_ET_PTD)
DECL|macro|_SRMMU_PAGE_WRITE_USR
mdefine_line|#define _SRMMU_PAGE_WRITE_USR  (SRMMU_ACC_US_RDWR)
DECL|macro|_SRMMU_PAGE_WRITE_KERN
mdefine_line|#define _SRMMU_PAGE_WRITE_KERN (SRMMU_ACC_S_RDWR)
DECL|macro|_SRMMU_PAGE_EXEC
mdefine_line|#define _SRMMU_PAGE_EXEC       (SRMMU_ACC_US_RDEXEC)
DECL|macro|_SRMMU_PAGE_RDONLY
mdefine_line|#define _SRMMU_PAGE_RDONLY     (SRMMU_ACC_US_RDONLY)
DECL|macro|_SRMMU_PAGE_NOREAD
mdefine_line|#define _SRMMU_PAGE_NOREAD     (SRMMU_ACC_U_ACCDENIED)
DECL|macro|_SRMMU_PAGE_NOCACHE
mdefine_line|#define _SRMMU_PAGE_NOCACHE    (~SRMMU_PTE_C_MASK)
DECL|macro|_SRMMU_PAGE_PRIV
mdefine_line|#define _SRMMU_PAGE_PRIV       (SRMMU_ACC_S_RDWREXEC)
DECL|macro|_SRMMU_PAGE_REF
mdefine_line|#define _SRMMU_PAGE_REF        (SRMMU_PTE_R_MASK)
DECL|macro|_SRMMU_PAGE_DIRTY
mdefine_line|#define _SRMMU_PAGE_DIRTY      (SRMMU_PTE_M_MASK)
DECL|macro|_SRMMU_PAGE_COW
mdefine_line|#define _SRMMU_PAGE_COW        (SRMMU_ACC_U_RDONLY)
DECL|macro|_SRMMU_PAGE_UNCOW
mdefine_line|#define _SRMMU_PAGE_UNCOW      (SRMMU_ACC_US_RDWR)
multiline_comment|/* We want the swapper not to swap out page tables, thus dirty and writable&n; * so that the kernel can change the entries as needed. Also valid for&n; * obvious reasons.&n; */
DECL|macro|_SRMMU_PAGE_TABLE
mdefine_line|#define _SRMMU_PAGE_TABLE     (_SRMMU_PAGE_VALID | _SRMMU_PAGE_WRITE_KERN | _SRMMU_PAGE_REF | _SRMMU_PAGE_DIRTY)
DECL|macro|_SRMMU_PAGE_CHG_MASK
mdefine_line|#define _SRMMU_PAGE_CHG_MASK  (_SRMMU_PAGE_REF | _SRMMU_PAGE_DIRTY | SRMMU_ET_PTE)
DECL|macro|_SRMMU_PMD_CHG_MASK
mdefine_line|#define _SRMMU_PMD_CHG_MASK   (SRMMU_ET_PTD)
DECL|macro|_SRMMU_PGD_CHG_MASK
mdefine_line|#define _SRMMU_PGD_CHG_MASK   (SRMMU_ET_PTD)
DECL|macro|SRMMU_PAGE_NONE
mdefine_line|#define SRMMU_PAGE_NONE       __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_REF)
DECL|macro|SRMMU_PAGE_SHARED
mdefine_line|#define SRMMU_PAGE_SHARED     __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_WRITE_USR | _SRMMU_PAGE_REF)
DECL|macro|SRMMU_PAGE_COPY
mdefine_line|#define SRMMU_PAGE_COPY       __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_REF | _SRMMU_PAGE_COW)
DECL|macro|SRMMU_PAGE_READONLY
mdefine_line|#define SRMMU_PAGE_READONLY   __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_REF | SRMMU_ACC_US_RDONLY)
DECL|macro|SRMMU_PAGE_KERNEL
mdefine_line|#define SRMMU_PAGE_KERNEL     __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_PRIV | SRMMU_PTE_C_MASK)
DECL|macro|SRMMU_PAGE_INVALID
mdefine_line|#define SRMMU_PAGE_INVALID    __pgprot(SRMMU_ET_INVALID)
DECL|macro|_SRMMU_PAGE_NORMAL
mdefine_line|#define _SRMMU_PAGE_NORMAL(x) __pgprot(_SRMMU_PAGE_VALID | _SRMMU_PAGE_REF | (x))
multiline_comment|/* SRMMU Register addresses */
DECL|macro|SRMMU_CTRL_REG
mdefine_line|#define SRMMU_CTRL_REG           0x00000000
DECL|macro|SRMMU_CTXTBL_PTR
mdefine_line|#define SRMMU_CTXTBL_PTR         0x00000100
DECL|macro|SRMMU_CTX_REG
mdefine_line|#define SRMMU_CTX_REG            0x00000200
DECL|macro|SRMMU_FAULT_STATUS
mdefine_line|#define SRMMU_FAULT_STATUS       0x00000300
DECL|macro|SRMMU_FAULT_ADDR
mdefine_line|#define SRMMU_FAULT_ADDR         0x00000400
DECL|macro|SRMMU_AFAULT_STATUS
mdefine_line|#define SRMMU_AFAULT_STATUS      0x00000500
DECL|macro|SRMMU_AFAULT_ADDR
mdefine_line|#define SRMMU_AFAULT_ADDR        0x00000600
multiline_comment|/* The SRMMU control register fields:&n; * -------------------------------------------------------------------&n; * | IMPL  |  VERS  |    SysControl | PSO | Resv | No Fault | Enable |&n; * -------------------------------------------------------------------&n; * 31    28 27    24 23            8   7    6   2      1        0&n; *&n; * IMPL:  Indicates the implementation of this SRMMU, read-only.&n; * VERS:  The version of this implementation, again read-only.&n; * SysControl:  This is an implementation specific field, the SRMMU&n; *              specification does not define anything for this field.&n; * PSO: This determines whether the memory model as seen by the CPU&n; *      is Partial Store Order (PSO=1) or Total Store Ordering (PSO=0).&n; * Resv: Don&squot;t touch these bits ;)&n; * No Fault: If zero, any fault acts as expected where the fault status&n; *           and address registers are updated and a trap hits the CPU.&n; *           When this bit is one, on any fault other than in ASI 9, the&n; *           MMU updates the status and address fault registers but does&n; *           not signal the CPU with a trap.  This is useful to beat&n; *           race conditions in low-level code when we have to throw&n; *           a register window onto the stack in a spill/fill handler&n; *           on multiprocessors.&n; * Enable: If one the MMU is doing translations, if zero the addresses&n; *         given to the bus are pure physical.&n; */
DECL|macro|SRMMU_CTREG_IMPL_MASK
mdefine_line|#define SRMMU_CTREG_IMPL_MASK        0xf0000000
DECL|macro|SRMMU_CTREG_IMPL_SHIFT
mdefine_line|#define SRMMU_CTREG_IMPL_SHIFT       28
DECL|macro|SRMMU_CTREG_VERS_MASK
mdefine_line|#define SRMMU_CTREG_VERS_MASK        0x0f000000
DECL|macro|SRMMU_CTREG_VERS_SHIFT
mdefine_line|#define SRMMU_CTREG_VERS_SHIFT       24
DECL|macro|SRMMU_CTREG_SYSCNTRL_MASK
mdefine_line|#define SRMMU_CTREG_SYSCNTRL_MASK    0x00ffff00
DECL|macro|SRMMU_CTREG_SYSCNTRL_SHIFT
mdefine_line|#define SRMMU_CTREG_SYSCNTRL_SHIFT   8
DECL|macro|SRMMU_CTREG_PSO_MASK
mdefine_line|#define SRMMU_CTREG_PSO_MASK         0x00000080
DECL|macro|SRMMU_CTREG_PSO_SHIFT
mdefine_line|#define SRMMU_CTREG_PSO_SHIFT        7
DECL|macro|SRMMU_CTREG_RESV_MASK
mdefine_line|#define SRMMU_CTREG_RESV_MASK        0x0000007c
DECL|macro|SRMMU_CTREG_RESV_SHIFT
mdefine_line|#define SRMMU_CTREG_RESV_SHIFT       2
DECL|macro|SRMMU_CTREG_NOFAULT_MASK
mdefine_line|#define SRMMU_CTREG_NOFAULT_MASK     0x00000002
DECL|macro|SRMMU_CTREG_NOFAULT_SHIFT
mdefine_line|#define SRMMU_CTREG_NOFAULT_SHIFT    1
DECL|macro|SRMMU_CTREG_ENABLE_MASK
mdefine_line|#define SRMMU_CTREG_ENABLE_MASK      0x00000001
DECL|macro|SRMMU_CTREG_ENABLE_SHIFT
mdefine_line|#define SRMMU_CTREG_ENABLE_SHIFT     0
multiline_comment|/* Get the MMU control register */
DECL|function|srmmu_get_mmureg
r_extern
r_inline
r_int
r_int
id|srmmu_get_mmureg
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%%g0] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Set the MMU control register */
DECL|function|srmmu_set_mmureg
r_extern
r_inline
r_void
id|srmmu_set_mmureg
c_func
(paren
r_int
r_int
id|regval
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%%g0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regval
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The SRMMU Context Table Pointer Register:&n; * ---------------------------------&n; * |  Context Table Pointer | Resv |&n; * ---------------------------------&n; * 31                      2 1    0&n; *&n; * This is where the MMU goes to in physical RAM to fetch the&n; * elements in the context table.  The non-Resv bits of this&n; * address appear in bits 6-35 of the physical bus during miss&n; * processing, then indexed by the value in the Context Register.&n; * This table must be aligned on a boundary equal to the size of&n; * the table, we provide a nice macro for doing this based upon&n; * the significant bits in the context register.&n; */
DECL|macro|SRMMU_CTP_ADDR_MASK
mdefine_line|#define SRMMU_CTP_ADDR_MASK          0xfffffffc
DECL|macro|SRMMU_CTP_ADDR_PADDR_SHIFT
mdefine_line|#define SRMMU_CTP_ADDR_PADDR_SHIFT   0x4
DECL|macro|SRMMU_CTP_RESV_MASK
mdefine_line|#define SRMMU_CTP_RESV_MASK          0x00000003
DECL|macro|SRMMU_SIGBITS_TO_ALIGNMENT
mdefine_line|#define SRMMU_SIGBITS_TO_ALIGNMENT(numbits)  ((1 &lt;&lt; (numbits + 2)))
multiline_comment|/* Set the address of the context table.  You pass this routine&n; * the physical address, we do the magic shifting for you.&n; */
DECL|function|srmmu_set_ctable_ptr
r_extern
r_inline
r_void
id|srmmu_set_ctable_ptr
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|ctp
suffix:semicolon
id|ctp
op_assign
(paren
id|paddr
op_rshift
id|SRMMU_CTP_ADDR_PADDR_SHIFT
)paren
suffix:semicolon
id|ctp
op_and_assign
id|SRMMU_CTP_ADDR_MASK
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ctp
)paren
comma
l_string|&quot;r&quot;
(paren
id|SRMMU_CTXTBL_PTR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Get the address of the context table.  We return the physical&n; * address of the table, again we do the shifting here.&n; */
DECL|function|srmmu_get_ctable_ptr
r_extern
r_inline
r_int
r_int
id|srmmu_get_ctable_ptr
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_CTXTBL_PTR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
id|retval
op_and_assign
id|SRMMU_CTP_ADDR_MASK
suffix:semicolon
id|retval
op_assign
(paren
id|retval
op_lshift
id|SRMMU_CTP_ADDR_PADDR_SHIFT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Set the context on an SRMMU */
DECL|function|srmmu_set_context
r_extern
r_inline
r_void
id|srmmu_set_context
c_func
(paren
r_int
id|context
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|context
)paren
comma
l_string|&quot;r&quot;
(paren
id|SRMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Get the context on an SRMMU */
DECL|function|srmmu_get_context
r_extern
r_inline
r_int
id|srmmu_get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* SRMMU diagnostic register:&n; * --------------------------------------------------------&n; * |   Virtual Address   |   PDC entry   | DiagReg | Resv |&n; * --------------------------------------------------------&n; * 31                  12 11            4 3       2 1    0&n; *&n; * An SRMMU implementation has the choice of providing this register&n; * and I don&squot;t know much about it.&n; */
DECL|macro|SRMMU_DIAG_VADDR_MASK
mdefine_line|#define SRMMU_DIAG_VADDR_MASK        0xfffff000
DECL|macro|SRMMU_DIAG_PDC_MASK
mdefine_line|#define SRMMU_DIAG_PDC_MASK          0x00000ff0
DECL|macro|SRMMU_DIAG_REG_MASK
mdefine_line|#define SRMMU_DIAG_REG_MASK          0x0000000c
DECL|macro|SRMMU_DIAG_RESV_MASK
mdefine_line|#define SRMMU_DIAG_RESV_MASK         0x00000003
multiline_comment|/* SRMMU Fault Status Register:&n; * -----------------------------------------------------------&n; * | Reserved          | EBE  |  L  |  AT  |  FT  | FAV | OW |&n; * -----------------------------------------------------------&n; *  31               18 17  10  9  8 7    5  4   2   1     0&n; *&n; * WARNING!!! On certain VERY BROKEN Viking Sun4d modules this register&n; * is complete TOAST!  During a fault you cannot trust the values&n; * contained in this register, you must calculate them yourself&n; * by first using the trap program counter to decode the&n; * instruction the code tried to execute (ie. load or store) and&n; * the address they tried to access.  I think the Fault Virtual&n; * Address register may be ok on these chips, but who knows. Grrr.&n; *&n; * Reserved:  These bits must be zero.&n; * EBE: External bus error bits, implementation dependant (at least&n; *      we know what the bits mean on sun4d Viking modules) ;)&n; * L: The level in tree traversal at which the fault occured. The&n; *    values are... 0 = context table&n; *                  1 = level-1 page table&n; *                  2 = level-2 page table&n; *                  3 = level-3 page table&n; * AT: Access type field. This is decoded as follows...&n; *     0 -- Load from user data space&n; *     1 -- Load from supervisor data space&n; *     2 -- Read/Execute from user instruction space&n; *     3 -- Read/Execute from supervisor instruction space&n; *     4 -- Store to user data space&n; *     5 -- Store to supervisor data space&n; *     6 -- Store to user instruction space&n; *     7 -- Store to supervisor instruction space (emacs does this)&n; *     On the Viking --  TOAST!&n; * FT:  This is the fault type field.  It is used to determine what was&n; *      wrong in the attempted translation. It can be one of...&n; *     0 -- None&n; *     1 -- Invalid address error&n; *     2 -- Protection violation error&n; *     3 -- Priviledge violation error&n; *     4 -- Translation error (your tables are fucked up)&n; *     5 -- Bus access error (you lose)&n; *     6 -- Internal error (might as well have a Viking)&n; *     7 -- Reserved (don&squot;t touch)&n; * FAV: Fault Address Valid bit.  When set to one the fault address&n; *      register contents are valid.  It need not be valid for text&n; *      faults as the trapped PC tells us this anyway.&n; * OW: The Overwrite Bit, if set to one, this register has been&n; *     written to more than once by the hardware since software did&n; *     a read.  This mean multiple faults have occurred and you have&n; *     to a manual page table tree traversal to continue the handling&n; *     of the first fault. And on the Viking module....&n; *&n; * The Fault Address Register is just a 32-bit register representing the&n; * virtual address which caused the fault.  It&squot;s validity is determined&n; * by the following equation:&n; * if(module==VIKING || FSR.FAV==0) forget_it();&n; * It&squot;s ok for the FAV to be invalid for a text fault because we can&n; * use the trapped program counter, however for a data fault we are SOL.&n; * I&squot;ll probably have to write a workaround for this situation too ;-(&n; */
DECL|macro|SRMMU_FSR_RESV_MASK
mdefine_line|#define SRMMU_FSR_RESV_MASK      0xfffc0000  /* Reserved bits */
DECL|macro|SRMMU_FSR_EBE_MASK
mdefine_line|#define SRMMU_FSR_EBE_MASK       0x0003fc00  /* External Bus Error bits */
DECL|macro|SRMMU_FSR_EBE_BERR
mdefine_line|#define SRMMU_FSR_EBE_BERR       0x00000400  /* Bus Error */
DECL|macro|SRMMU_FSR_EBE_BTIMEO
mdefine_line|#define SRMMU_FSR_EBE_BTIMEO     0x00000800  /* Bus Time Out */
DECL|macro|SRMMU_FSR_EBE_UNCOR
mdefine_line|#define SRMMU_FSR_EBE_UNCOR      0x00001000  /* Uncorrectable Error */
DECL|macro|SRMMU_FSR_EBE_UNDEF
mdefine_line|#define SRMMU_FSR_EBE_UNDEF      0x00002000  /* Undefined Error */
DECL|macro|SRMMU_FSR_EBE_PARITY
mdefine_line|#define SRMMU_FSR_EBE_PARITY     0x00004000  /* Parity error */
DECL|macro|SRMMU_FSR_EBE_TPARITY
mdefine_line|#define SRMMU_FSR_EBE_TPARITY    0x00006000  /* Tsunami parity error */
DECL|macro|SRMMU_FSR_EBE_SBUF
mdefine_line|#define SRMMU_FSR_EBE_SBUF       0x00008000  /* Store Buffer error */
DECL|macro|SRMMU_FSR_EBE_CSA
mdefine_line|#define SRMMU_FSR_EBE_CSA        0x00010000  /* Control space access error (bad ASI) */
DECL|macro|SRMMU_FSR_EBE_EMRT
mdefine_line|#define SRMMU_FSR_EBE_EMRT       0x00020000  /* Viking Emergency Response Team */
DECL|macro|SRMMU_FSR_L_MASK
mdefine_line|#define SRMMU_FSR_L_MASK         0x00000300  /* Fault level bits */
DECL|macro|SRMMU_FSR_L_CTABLE
mdefine_line|#define SRMMU_FSR_L_CTABLE       0x00000000  /* Context table level flt/err */
DECL|macro|SRMMU_FSR_L_ONE
mdefine_line|#define SRMMU_FSR_L_ONE          0x00000100  /* Level1 ptable flt/err */
DECL|macro|SRMMU_FSR_L_TWO
mdefine_line|#define SRMMU_FSR_L_TWO          0x00000200  /* Level2 ptable flt/err */
DECL|macro|SRMMU_FSR_L_THREE
mdefine_line|#define SRMMU_FSR_L_THREE        0x00000300  /* Level3 ptable flt/err */
DECL|macro|SRMMU_FSR_AT_MASK
mdefine_line|#define SRMMU_FSR_AT_MASK        0x000000e0  /* Access Type bits */
DECL|macro|SRMMU_FSR_AT_LUD
mdefine_line|#define SRMMU_FSR_AT_LUD         0x00000000  /* Load from User Data space */
DECL|macro|SRMMU_FSR_AT_LSD
mdefine_line|#define SRMMU_FSR_AT_LSD         0x00000020  /* What I&squot;ll need after writing this code */
DECL|macro|SRMMU_FSR_AT_RXUI
mdefine_line|#define SRMMU_FSR_AT_RXUI        0x00000040  /* Read/Execute from user text */
DECL|macro|SRMMU_FSR_AT_RXSI
mdefine_line|#define SRMMU_FSR_AT_RXSI        0x00000060  /* Read/Execute from supv text */
DECL|macro|SRMMU_FSR_AT_SUD
mdefine_line|#define SRMMU_FSR_AT_SUD         0x00000080  /* Store to user data space */
DECL|macro|SRMMU_FSR_AT_SSD
mdefine_line|#define SRMMU_FSR_AT_SSD         0x000000a0  /* Store to supv data space */
DECL|macro|SRMMU_FSR_AT_SUI
mdefine_line|#define SRMMU_FSR_AT_SUI         0x000000c0  /* Store to user text */
DECL|macro|SRMMU_FSR_AT_SSI
mdefine_line|#define SRMMU_FSR_AT_SSI         0x000000e0  /* Store to supv text */
DECL|macro|SRMMU_FSR_FT_MASK
mdefine_line|#define SRMMU_FSR_FT_MASK        0x0000001c  /* Fault Type bits */
DECL|macro|SRMMU_FSR_FT_NONE
mdefine_line|#define SRMMU_FSR_FT_NONE        0x00000000  /* No fault occurred */
DECL|macro|SRMMU_FSR_FT_IADDR
mdefine_line|#define SRMMU_FSR_FT_IADDR       0x00000002  /* Invalid address */
DECL|macro|SRMMU_FSR_FT_PROT
mdefine_line|#define SRMMU_FSR_FT_PROT        0x00000004  /* Protection violation */
DECL|macro|SRMMU_FSR_FT_PRIV
mdefine_line|#define SRMMU_FSR_FT_PRIV        0x00000008  /* Privilege violation */
DECL|macro|SRMMU_FSR_FT_TRANS
mdefine_line|#define SRMMU_FSR_FT_TRANS       0x0000000a  /* Translation error */
DECL|macro|SRMMU_FSR_FT_BACC
mdefine_line|#define SRMMU_FSR_FT_BACC        0x0000000c  /* Bus Access error */
DECL|macro|SRMMU_FSR_FT_IACC
mdefine_line|#define SRMMU_FSR_FT_IACC        0x0000000e  /* Internal error */
DECL|macro|SRMMU_FSR_FT_RESV
mdefine_line|#define SRMMU_FSR_FT_RESV        0x00000010  /* Reserved, should not get this */
DECL|macro|SRMMU_FSR_FAV_MASK
mdefine_line|#define SRMMU_FSR_FAV_MASK       0x00000002  /* Fault Address Valid bits */
DECL|macro|SRMMU_FSR_OW_MASK
mdefine_line|#define SRMMU_FSR_OW_MASK        0x00000001  /* SFSR OverWritten bits */
multiline_comment|/* Read the Fault Status Register on the SRMMU */
DECL|function|srmmu_get_fstatus
r_extern
r_inline
r_int
r_int
id|srmmu_get_fstatus
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_FAULT_STATUS
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Read the Fault Address Register on the SRMMU */
DECL|function|srmmu_get_faddr
r_extern
r_inline
r_int
r_int
id|srmmu_get_faddr
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_FAULT_ADDR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* SRMMU Asynchronous Fault Status Register:&n; * -----------------------------------------&n; * |  RESERVED |UCE|BTO|BERR|RSV|HFADDR|AFO|&n; * -----------------------------------------&n; *  31       13  12  11  10  9-8  7-4     0&n; *&n; * UCE: UnCorrectable Error&n; * BTO: Bus TimeOut&n; * BERR: Genreic Bus Error&n; * HFADDR: High 4 bits of the faulting address&n; * AFO: Asynchronous Fault Occurred&n; */
DECL|macro|SRMMU_AFSR_RESVMASK
mdefine_line|#define SRMMU_AFSR_RESVMASK  0xffffe000
DECL|macro|SRMMU_AFSR_UCE
mdefine_line|#define SRMMU_AFSR_UCE       0x00001000
DECL|macro|SRMMU_AFSR_BTO
mdefine_line|#define SRMMU_AFSR_BTO       0x00000800
DECL|macro|SRMMU_AFSR_BERR
mdefine_line|#define SRMMU_AFSR_BERR      0x00000400
DECL|macro|SRMMU_AFSR_HFADDR
mdefine_line|#define SRMMU_AFSR_HFADDR    0x000000f0
DECL|macro|SRMMU_AFSR_AFO
mdefine_line|#define SRMMU_AFSR_AFO       0x00000001
multiline_comment|/* Read the asynchronous fault register */
DECL|function|srmmu_get_afstatus
r_extern
r_inline
r_int
r_int
id|srmmu_get_afstatus
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_AFAULT_STATUS
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Read the Asynchronous Fault Address Register on the SRMMU */
DECL|function|srmmu_get_afaddr
r_extern
r_inline
r_int
r_int
id|srmmu_get_afaddr
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_AFAULT_ADDR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Flush the entire TLB cache on the SRMMU. */
DECL|function|srmmu_flush_whole_tlb
r_extern
r_inline
r_void
id|srmmu_flush_whole_tlb
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x400
)paren
comma
multiline_comment|/* Flush entire TLB!! */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Probe for an entry in the page-tables of the SRMMU. */
DECL|function|srmmu_hwprobe
r_extern
r_inline
r_int
r_int
id|srmmu_hwprobe
c_func
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|vaddr
op_or
l_int|0x400
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_PGTSRMMU_H) */
eof
