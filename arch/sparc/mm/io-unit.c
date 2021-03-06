multiline_comment|/* $Id: io-unit.c,v 1.22 2000/08/09 00:00:15 davem Exp $&n; * io-unit.c:  IO-UNIT specific routines for memory management.&n; *&n; * Copyright (C) 1997,1998 Jakub Jelinek    (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/io-unit.h&gt;
macro_line|#include &lt;asm/mxcc.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/* #define IOUNIT_DEBUG */
macro_line|#ifdef IOUNIT_DEBUG
DECL|macro|IOD
mdefine_line|#define IOD(x) printk(x)
macro_line|#else
DECL|macro|IOD
mdefine_line|#define IOD(x) do { } while (0)
macro_line|#endif
DECL|macro|IOPERM
mdefine_line|#define IOPERM        (IOUPTE_CACHE | IOUPTE_WRITE | IOUPTE_VALID)
DECL|macro|MKIOPTE
mdefine_line|#define MKIOPTE(phys) __iopte((((phys)&gt;&gt;4) &amp; IOUPTE_PAGE) | IOPERM)
r_void
id|__init
DECL|function|iounit_init
id|iounit_init
c_func
(paren
r_int
id|sbi_node
comma
r_int
id|io_node
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
id|iopte_t
op_star
id|xpt
comma
op_star
id|xptend
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
suffix:semicolon
r_struct
id|linux_prom_registers
id|iommu_promregs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
id|iounit
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iounit_struct
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|iounit
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|iounit
)paren
)paren
suffix:semicolon
id|iounit-&gt;limit
(braket
l_int|0
)braket
op_assign
id|IOUNIT_BMAP1_START
suffix:semicolon
id|iounit-&gt;limit
(braket
l_int|1
)braket
op_assign
id|IOUNIT_BMAP2_START
suffix:semicolon
id|iounit-&gt;limit
(braket
l_int|2
)braket
op_assign
id|IOUNIT_BMAPM_START
suffix:semicolon
id|iounit-&gt;limit
(braket
l_int|3
)braket
op_assign
id|IOUNIT_BMAPM_END
suffix:semicolon
id|iounit-&gt;rotor
(braket
l_int|1
)braket
op_assign
id|IOUNIT_BMAP2_START
suffix:semicolon
id|iounit-&gt;rotor
(braket
l_int|2
)braket
op_assign
id|IOUNIT_BMAPM_START
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|sbi_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|iommu_promregs
comma
r_sizeof
(paren
id|iommu_promregs
)paren
)paren
suffix:semicolon
id|prom_apply_generic_ranges
c_func
(paren
id|io_node
comma
l_int|0
comma
id|iommu_promregs
comma
l_int|3
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
id|r.flags
op_assign
id|iommu_promregs
(braket
l_int|2
)braket
dot
id|which_io
suffix:semicolon
id|r.start
op_assign
id|iommu_promregs
(braket
l_int|2
)braket
dot
id|phys_addr
suffix:semicolon
id|xpt
op_assign
(paren
id|iopte_t
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
id|PAGE_SIZE
op_star
l_int|16
comma
l_string|&quot;XPT&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpt
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Cannot map External Page Table.&quot;
)paren
suffix:semicolon
)brace
id|sbus-&gt;iommu
op_assign
(paren
r_struct
id|iommu_struct
op_star
)paren
id|iounit
suffix:semicolon
id|iounit-&gt;page_table
op_assign
id|xpt
suffix:semicolon
r_for
c_loop
(paren
id|xptend
op_assign
id|iounit-&gt;page_table
op_plus
(paren
l_int|16
op_star
id|PAGE_SIZE
)paren
op_div
r_sizeof
(paren
id|iopte_t
)paren
suffix:semicolon
id|xpt
OL
id|xptend
suffix:semicolon
)paren
op_star
id|xpt
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* One has to hold iounit-&gt;lock to call this */
DECL|function|iounit_get_area
r_static
r_int
r_int
id|iounit_get_area
c_func
(paren
r_struct
id|iounit_struct
op_star
id|iounit
comma
r_int
r_int
id|vaddr
comma
r_int
id|size
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
comma
id|npages
suffix:semicolon
r_int
r_int
id|rotor
comma
id|scan
comma
id|limit
suffix:semicolon
id|iopte_t
id|iopte
suffix:semicolon
id|npages
op_assign
(paren
(paren
id|vaddr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|size
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* A tiny bit of magic ingredience :) */
r_switch
c_cond
(paren
id|npages
)paren
(brace
r_case
l_int|1
suffix:colon
id|i
op_assign
l_int|0x0231
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|i
op_assign
l_int|0x0132
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|i
op_assign
l_int|0x0213
suffix:semicolon
r_break
suffix:semicolon
)brace
id|IOD
c_func
(paren
(paren
l_string|&quot;iounit_get_area(%08lx,%d[%d])=&quot;
comma
id|vaddr
comma
id|size
comma
id|npages
)paren
)paren
suffix:semicolon
id|next
suffix:colon
id|j
op_assign
(paren
id|i
op_amp
l_int|15
)paren
suffix:semicolon
id|rotor
op_assign
id|iounit-&gt;rotor
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|limit
op_assign
id|iounit-&gt;limit
(braket
id|j
)braket
suffix:semicolon
id|scan
op_assign
id|rotor
suffix:semicolon
id|nexti
suffix:colon
id|scan
op_assign
id|find_next_zero_bit
c_func
(paren
id|iounit-&gt;bmap
comma
id|limit
comma
id|scan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scan
op_plus
id|npages
OG
id|limit
)paren
(brace
r_if
c_cond
(paren
id|limit
op_ne
id|rotor
)paren
(brace
id|limit
op_assign
id|rotor
suffix:semicolon
id|scan
op_assign
id|iounit-&gt;limit
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
r_goto
id|nexti
suffix:semicolon
)brace
id|i
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_amp
l_int|15
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;iounit_get_area: Couldn&squot;t find free iopte slots for (%08lx,%d)&bslash;n&quot;
comma
id|vaddr
comma
id|size
)paren
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
l_int|1
comma
id|scan
op_increment
suffix:semicolon
id|k
OL
id|npages
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|scan
op_increment
comma
id|iounit-&gt;bmap
)paren
)paren
r_goto
id|nexti
suffix:semicolon
id|iounit-&gt;rotor
(braket
id|j
op_minus
l_int|1
)braket
op_assign
(paren
id|scan
OL
id|limit
)paren
ques
c_cond
id|scan
suffix:colon
id|iounit-&gt;limit
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|scan
op_sub_assign
id|npages
suffix:semicolon
id|iopte
op_assign
id|MKIOPTE
c_func
(paren
id|__pa
c_func
(paren
id|vaddr
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|vaddr
op_assign
id|IOUNIT_DMA_BASE
op_plus
(paren
id|scan
op_lshift
id|PAGE_SHIFT
)paren
op_plus
(paren
id|vaddr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|npages
suffix:semicolon
id|k
op_increment
comma
id|iopte
op_assign
id|__iopte
c_func
(paren
id|iopte_val
c_func
(paren
id|iopte
)paren
op_plus
l_int|0x100
)paren
comma
id|scan
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|scan
comma
id|iounit-&gt;bmap
)paren
suffix:semicolon
id|iounit-&gt;page_table
(braket
id|scan
)braket
op_assign
id|iopte
suffix:semicolon
)brace
id|IOD
c_func
(paren
(paren
l_string|&quot;%08lx&bslash;n&quot;
comma
id|vaddr
)paren
)paren
suffix:semicolon
r_return
id|vaddr
suffix:semicolon
)brace
DECL|function|iounit_get_scsi_one
r_static
id|__u32
id|iounit_get_scsi_one
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|ret
comma
id|flags
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|iounit_get_area
c_func
(paren
id|iounit
comma
(paren
r_int
r_int
)paren
id|vaddr
comma
id|len
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|iounit_get_scsi_sgl
r_static
r_void
id|iounit_get_scsi_sgl
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
multiline_comment|/* FIXME: Cache some resolved pages - often several sg entries are to the same page */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|sz
op_ge
l_int|0
suffix:semicolon
id|sz
op_decrement
)paren
(brace
id|sg
(braket
id|sz
)braket
dot
id|dvma_address
op_assign
id|iounit_get_area
c_func
(paren
id|iounit
comma
(paren
r_int
r_int
)paren
id|sg
(braket
id|sz
)braket
dot
id|address
comma
id|sg
(braket
id|sz
)braket
dot
id|length
)paren
suffix:semicolon
id|sg
(braket
id|sz
)braket
dot
id|dvma_length
op_assign
id|sg
(braket
id|sz
)braket
dot
id|length
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iounit_release_scsi_one
r_static
r_void
id|iounit_release_scsi_one
c_func
(paren
id|__u32
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|len
op_assign
(paren
(paren
id|vaddr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|len
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|vaddr
op_assign
(paren
id|vaddr
op_minus
id|IOUNIT_DMA_BASE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|IOD
c_func
(paren
(paren
l_string|&quot;iounit_release %08lx-%08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|vaddr
comma
(paren
r_int
)paren
id|len
op_plus
id|vaddr
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|len
op_add_assign
id|vaddr
suffix:semicolon
id|vaddr
OL
id|len
suffix:semicolon
id|vaddr
op_increment
)paren
id|clear_bit
c_func
(paren
id|vaddr
comma
id|iounit-&gt;bmap
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iounit_release_scsi_sgl
r_static
r_void
id|iounit_release_scsi_sgl
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|vaddr
comma
id|len
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|sz
op_ge
l_int|0
suffix:semicolon
id|sz
op_decrement
)paren
(brace
id|len
op_assign
(paren
(paren
id|sg
(braket
id|sz
)braket
dot
id|dvma_address
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|sg
(braket
id|sz
)braket
dot
id|length
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|vaddr
op_assign
(paren
id|sg
(braket
id|sz
)braket
dot
id|dvma_address
op_minus
id|IOUNIT_DMA_BASE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|IOD
c_func
(paren
(paren
l_string|&quot;iounit_release %08lx-%08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|vaddr
comma
(paren
r_int
)paren
id|len
op_plus
id|vaddr
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|len
op_add_assign
id|vaddr
suffix:semicolon
id|vaddr
OL
id|len
suffix:semicolon
id|vaddr
op_increment
)paren
id|clear_bit
c_func
(paren
id|vaddr
comma
id|iounit-&gt;bmap
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SBUS
DECL|function|iounit_map_dma_area
r_static
r_void
id|iounit_map_dma_area
c_func
(paren
r_int
r_int
id|va
comma
id|__u32
id|addr
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|page
comma
id|end
suffix:semicolon
id|pgprot_t
id|dvma_prot
suffix:semicolon
id|iopte_t
op_star
id|iopte
suffix:semicolon
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
id|dvma_prot
op_assign
id|__pgprot
c_func
(paren
id|SRMMU_CACHE
op_or
id|SRMMU_ET_PTE
op_or
id|SRMMU_PRIV
)paren
suffix:semicolon
id|end
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
id|addr
op_plus
id|len
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|end
)paren
(brace
id|page
op_assign
id|va
suffix:semicolon
(brace
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
id|init_task.mm
comma
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
c_func
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_val
c_func
(paren
id|mk_pte
c_func
(paren
id|virt_to_page
c_func
(paren
id|page
)paren
comma
id|dvma_prot
)paren
)paren
)paren
suffix:semicolon
id|i
op_assign
(paren
(paren
id|addr
op_minus
id|IOUNIT_DMA_BASE
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|iopte
op_assign
(paren
id|iopte_t
op_star
)paren
(paren
id|iounit-&gt;page_table
op_plus
id|i
)paren
suffix:semicolon
op_star
id|iopte
op_assign
id|__iopte
c_func
(paren
id|MKIOPTE
c_func
(paren
id|__pa
c_func
(paren
id|page
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|va
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|iounit_unmap_dma_area
r_static
r_void
id|iounit_unmap_dma_area
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
multiline_comment|/* XXX Somebody please fill this in */
)brace
multiline_comment|/* XXX We do not pass sbus device here, bad. */
DECL|function|iounit_translate_dvma
r_static
r_int
r_int
id|iounit_translate_dvma
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
op_assign
id|sbus_root
suffix:semicolon
multiline_comment|/* They are all the same */
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
r_int
id|i
suffix:semicolon
id|iopte_t
op_star
id|iopte
suffix:semicolon
id|i
op_assign
(paren
(paren
id|addr
op_minus
id|IOUNIT_DMA_BASE
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|iopte
op_assign
(paren
id|iopte_t
op_star
)paren
(paren
id|iounit-&gt;page_table
op_plus
id|i
)paren
suffix:semicolon
r_return
(paren
id|iopte_val
c_func
(paren
op_star
id|iopte
)paren
op_amp
l_int|0xFFFFFFF0
)paren
op_lshift
l_int|4
suffix:semicolon
multiline_comment|/* XXX sun4d guru, help */
)brace
macro_line|#endif
DECL|function|iounit_lockarea
r_static
r_char
op_star
id|iounit_lockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
)paren
(brace
multiline_comment|/* FIXME: Write this */
r_return
id|vaddr
suffix:semicolon
)brace
DECL|function|iounit_unlockarea
r_static
r_void
id|iounit_unlockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
)paren
(brace
multiline_comment|/* FIXME: Write this */
)brace
DECL|function|ld_mmu_iounit
r_void
id|__init
id|ld_mmu_iounit
c_func
(paren
r_void
)paren
(brace
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_lockarea
comma
id|iounit_lockarea
comma
id|BTFIXUPCALL_RETO0
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_unlockarea
comma
id|iounit_unlockarea
comma
id|BTFIXUPCALL_NOP
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_one
comma
id|iounit_get_scsi_one
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_sgl
comma
id|iounit_get_scsi_sgl
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_release_scsi_one
comma
id|iounit_release_scsi_one
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_release_scsi_sgl
comma
id|iounit_release_scsi_sgl
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SBUS
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_map_dma_area
comma
id|iounit_map_dma_area
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_unmap_dma_area
comma
id|iounit_unmap_dma_area
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_translate_dvma
comma
id|iounit_translate_dvma
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|iounit_map_dma_init
id|__u32
id|iounit_map_dma_init
c_func
(paren
r_struct
id|sbus_bus
op_star
id|sbus
comma
r_int
id|size
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
comma
id|npages
suffix:semicolon
r_int
r_int
id|rotor
comma
id|scan
comma
id|limit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|__u32
id|ret
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|npages
op_assign
(paren
id|size
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|i
op_assign
l_int|0x0213
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|next
suffix:colon
id|j
op_assign
(paren
id|i
op_amp
l_int|15
)paren
suffix:semicolon
id|rotor
op_assign
id|iounit-&gt;rotor
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|limit
op_assign
id|iounit-&gt;limit
(braket
id|j
)braket
suffix:semicolon
id|scan
op_assign
id|rotor
suffix:semicolon
id|nexti
suffix:colon
id|scan
op_assign
id|find_next_zero_bit
c_func
(paren
id|iounit-&gt;bmap
comma
id|limit
comma
id|scan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scan
op_plus
id|npages
OG
id|limit
)paren
(brace
r_if
c_cond
(paren
id|limit
op_ne
id|rotor
)paren
(brace
id|limit
op_assign
id|rotor
suffix:semicolon
id|scan
op_assign
id|iounit-&gt;limit
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
r_goto
id|nexti
suffix:semicolon
)brace
id|i
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_amp
l_int|15
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;iounit_map_dma_init: Couldn&squot;t find free iopte slots for %d bytes&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
l_int|1
comma
id|scan
op_increment
suffix:semicolon
id|k
OL
id|npages
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|scan
op_increment
comma
id|iounit-&gt;bmap
)paren
)paren
r_goto
id|nexti
suffix:semicolon
id|iounit-&gt;rotor
(braket
id|j
op_minus
l_int|1
)braket
op_assign
(paren
id|scan
OL
id|limit
)paren
ques
c_cond
id|scan
suffix:colon
id|iounit-&gt;limit
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|scan
op_sub_assign
id|npages
suffix:semicolon
id|ret
op_assign
id|IOUNIT_DMA_BASE
op_plus
(paren
id|scan
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|npages
suffix:semicolon
id|k
op_increment
comma
id|scan
op_increment
)paren
id|set_bit
c_func
(paren
id|scan
comma
id|iounit-&gt;bmap
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iounit-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|iounit_map_dma_page
id|__u32
id|iounit_map_dma_page
c_func
(paren
id|__u32
id|vaddr
comma
r_void
op_star
id|addr
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
id|scan
op_assign
(paren
id|vaddr
op_minus
id|IOUNIT_DMA_BASE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_struct
id|iounit_struct
op_star
id|iounit
op_assign
(paren
r_struct
id|iounit_struct
op_star
)paren
id|sbus-&gt;iommu
suffix:semicolon
id|iounit-&gt;page_table
(braket
id|scan
)braket
op_assign
id|MKIOPTE
c_func
(paren
id|__pa
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
r_return
id|vaddr
op_plus
(paren
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
eof
