multiline_comment|/*&n; *  linux/arch/arm/mm/ioremap.c&n; *&n; * Re-map IO memory to kernel address space so that we can access it.&n; *&n; * (C) Copyright 1995 1996 Linus Torvalds&n; *&n; * Hacked for ARM by Phil Blundell &lt;philb@gnu.org&gt;&n; * Hacked to allow all architectures to build, and various cleanups&n; * by Russell King&n; */
multiline_comment|/*&n; * This allows a driver to remap an arbitrary region of bus memory into&n; * virtual space.  One should *only* use readl, writel, memcpy_toio and&n; * so on with such remapped areas.&n; *&n; * Because the ARM only has a 32-bit address space we can&squot;t address the&n; * whole of the (physical) PCI space at once.  PCI huge-mode addressing&n; * allows us to circumvent this restriction by splitting PCI space into&n; * two 2GB chunks and mapping only one at a time into processor memory.&n; * We use MMU protection domains to trap any attempt to access the bank&n; * that is not currently mapped.  (This isn&squot;t fully implemented yet.)&n; *&n; * DC21285 currently has a bug in that the PCI address extension&n; * register affects the address of any writes waiting in the outbound&n; * FIFO.  Unfortunately, it is not possible to tell the DC21285 to&n; * flush this - flushing the area causes the bus to lock.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|remap_area_pte
r_static
r_inline
r_void
id|remap_area_pte
c_func
(paren
id|pte_t
op_star
id|pte
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|phys_addr
comma
id|pgprot_t
id|pgprot
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;remap_area_pte: page already exists&bslash;n&quot;
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte_phys
c_func
(paren
id|phys_addr
comma
id|pgprot
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|phys_addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|remap_area_pmd
r_static
r_inline
r_int
id|remap_area_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|pgprot_t
id|pgprot
suffix:semicolon
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
id|pgprot
op_assign
id|__pgprot
c_func
(paren
id|L_PTE_PRESENT
op_or
id|L_PTE_YOUNG
op_or
id|L_PTE_DIRTY
op_or
id|L_PTE_WRITE
op_or
id|flags
)paren
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|remap_area_pte
c_func
(paren
id|pte
comma
id|address
comma
id|end
op_minus
id|address
comma
id|address
op_plus
id|phys_addr
comma
id|pgprot
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remap_area_pages
r_static
r_int
id|remap_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc_kernel
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pmd
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|phys_addr
op_plus
id|address
comma
id|flags
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_pgdir
c_func
(paren
id|address
comma
op_star
id|dir
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; *&n; * NOTE! We need to allow non-page-aligned mappings too: we will obviously&n; * have to convert them into an offset in a page-aligned mapping, but the&n; * caller shouldn&squot;t need to know that small detail.&n; *&n; * &squot;flags&squot; are the extra L_PTE_ flags that you want to specify for this&n; * mapping.  See include/asm-arm/proc-armv/pgtable.h for more information.&n; */
DECL|function|__ioremap
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|offset
comma
id|last_addr
suffix:semicolon
multiline_comment|/* Don&squot;t allow wraparound or zero size */
id|last_addr
op_assign
id|phys_addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|last_addr
OL
id|phys_addr
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Mappings have to be page-aligned&n;&t; */
id|offset
op_assign
id|phys_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|phys_addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last_addr
)paren
op_minus
id|phys_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, go for it..&n;&t; */
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|area-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|addr
)paren
comma
id|phys_addr
comma
id|size
comma
id|flags
)paren
)paren
(brace
id|vfree
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
id|offset
op_plus
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__iounmap
r_void
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
)paren
suffix:semicolon
)brace
eof
