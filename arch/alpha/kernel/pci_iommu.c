multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/pci_iommu.c&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
DECL|macro|DEBUG_ALLOC
mdefine_line|#define DEBUG_ALLOC 0
macro_line|#if DEBUG_ALLOC &gt; 0
DECL|macro|DBGA
macro_line|# define DBGA(args...)&t;&t;printk(KERN_DEBUG ##args)
macro_line|#else
DECL|macro|DBGA
macro_line|# define DBGA(args...)
macro_line|#endif
macro_line|#if DEBUG_ALLOC &gt; 1
DECL|macro|DBGA2
macro_line|# define DBGA2(args...)&t;&t;printk(KERN_DEBUG ##args)
macro_line|#else
DECL|macro|DBGA2
macro_line|# define DBGA2(args...)
macro_line|#endif
DECL|macro|DEBUG_NODIRECT
mdefine_line|#define DEBUG_NODIRECT 0
r_static
r_inline
r_int
r_int
DECL|function|mk_iommu_pte
id|mk_iommu_pte
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_return
(paren
id|paddr
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
)paren
op_or
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|calc_npages
id|calc_npages
c_func
(paren
r_int
id|bytes
)paren
(brace
r_return
(paren
id|bytes
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
"&f;"
r_struct
id|pci_iommu_arena
op_star
DECL|function|iommu_arena_new
id|iommu_arena_new
c_func
(paren
r_struct
id|pci_controler
op_star
id|hose
comma
id|dma_addr_t
id|base
comma
r_int
r_int
id|window_size
comma
r_int
r_int
id|align
)paren
(brace
r_int
r_int
id|mem_size
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
id|mem_size
op_assign
id|window_size
op_div
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* Note that the TLB lookup logic uses bitwise concatenation,&n;&t;   not addition, so the required arena alignment is based on&n;&t;   the size of the window.  Retain the align parameter so that&n;&t;   particular systems can over-align the arena.  */
r_if
c_cond
(paren
id|align
OL
id|mem_size
)paren
id|align
op_assign
id|mem_size
suffix:semicolon
id|arena
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
op_star
id|arena
)paren
)paren
suffix:semicolon
id|arena-&gt;ptes
op_assign
id|__alloc_bootmem
c_func
(paren
id|mem_size
comma
id|align
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|arena-&gt;lock
)paren
suffix:semicolon
id|arena-&gt;hose
op_assign
id|hose
suffix:semicolon
id|arena-&gt;dma_base
op_assign
id|base
suffix:semicolon
id|arena-&gt;size
op_assign
id|window_size
suffix:semicolon
id|arena-&gt;next_entry
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Align allocations to a multiple of a page size.  Not needed&n;&t;   unless there are chip bugs.  */
id|arena-&gt;align_entry
op_assign
l_int|1
suffix:semicolon
r_return
id|arena
suffix:semicolon
)brace
r_int
DECL|function|iommu_arena_alloc
id|iommu_arena_alloc
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
id|arena
comma
r_int
id|n
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|ptes
suffix:semicolon
r_int
id|i
comma
id|p
comma
id|nent
comma
id|mask
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|arena-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Search forward for the first sequence of N empty ptes.  */
id|ptes
op_assign
id|arena-&gt;ptes
suffix:semicolon
id|nent
op_assign
id|arena-&gt;size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|mask
op_assign
id|arena-&gt;align_entry
op_minus
l_int|1
suffix:semicolon
id|p
op_assign
(paren
id|arena-&gt;next_entry
op_plus
id|mask
)paren
op_amp
op_complement
id|mask
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|n
op_logical_and
id|p
op_plus
id|i
OL
id|nent
)paren
(brace
r_if
c_cond
(paren
id|ptes
(braket
id|p
op_plus
id|i
)braket
)paren
id|p
op_assign
(paren
id|p
op_plus
id|i
op_plus
l_int|1
op_plus
id|mask
)paren
op_amp
op_complement
id|mask
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_else
id|i
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|n
)paren
(brace
multiline_comment|/* Reached the end.  Flush the TLB and restart the&n;                   search from the beginning.  */
id|alpha_mv
dot
id|mv_pci_tbi
c_func
(paren
id|arena-&gt;hose
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|n
op_logical_and
id|p
op_plus
id|i
OL
id|nent
)paren
(brace
r_if
c_cond
(paren
id|ptes
(braket
id|p
op_plus
id|i
)braket
)paren
id|p
op_assign
(paren
id|p
op_plus
id|i
op_plus
l_int|1
op_plus
id|mask
)paren
op_amp
op_complement
id|mask
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_else
id|i
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|n
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|arena-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Success.  Mark them all in use, ie not zero.  Typically&n;&t;   bit zero is the valid bit, so write ~1 into everything.&n;&t;   The chip specific bits will fill this in with something&n;&t;   kosher when we return.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
op_increment
id|i
)paren
id|ptes
(braket
id|p
op_plus
id|i
)braket
op_assign
op_complement
l_int|1UL
suffix:semicolon
id|arena-&gt;next_entry
op_assign
id|p
op_plus
id|n
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|arena-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
r_void
DECL|function|iommu_arena_free
id|iommu_arena_free
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
id|arena
comma
r_int
id|ofs
comma
r_int
id|n
)paren
(brace
r_int
r_int
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|p
op_assign
id|arena-&gt;ptes
op_plus
id|ofs
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
op_increment
id|i
)paren
id|p
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Map a single buffer of the indicated size for PCI DMA in streaming&n;   mode.  The 32-bit PCI bus mastering address to use is returned.&n;   Once the device is given the dma address, the device owns this memory&n;   until either pci_unmap_single or pci_dma_sync_single is performed.  */
id|dma_addr_t
DECL|function|pci_map_single
id|pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_void
op_star
id|cpu_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|pci_controler
op_star
id|hose
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;sysdata
suffix:colon
id|pci_isa_hose
suffix:semicolon
id|dma_addr_t
id|max_dma
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;dma_mask
suffix:colon
l_int|0x00ffffff
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
r_int
id|npages
comma
id|dma_ofs
comma
id|i
suffix:semicolon
r_int
r_int
id|paddr
suffix:semicolon
id|dma_addr_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|paddr
op_assign
id|virt_to_phys
c_func
(paren
id|cpu_addr
)paren
suffix:semicolon
macro_line|#if !DEBUG_NODIRECT
multiline_comment|/* First check to see if we can use the direct map window.  */
r_if
c_cond
(paren
id|paddr
op_plus
id|size
op_plus
id|__direct_map_base
op_minus
l_int|1
op_le
id|max_dma
op_logical_and
id|paddr
op_plus
id|size
op_le
id|__direct_map_size
)paren
(brace
id|ret
op_assign
id|paddr
op_plus
id|__direct_map_base
suffix:semicolon
id|DBGA2
c_func
(paren
l_string|&quot;pci_map_single: [%p,%lx] -&gt; direct %x from %p&bslash;n&quot;
comma
id|cpu_addr
comma
id|size
comma
id|ret
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* If the machine doesn&squot;t define a pci_tbi routine, we have to&n;&t;   assume it doesn&squot;t support sg mapping.  */
r_if
c_cond
(paren
op_logical_neg
id|alpha_mv.mv_pci_tbi
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci_map_single failed: no hw sg&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|arena
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arena
op_logical_or
id|arena-&gt;dma_base
op_plus
id|arena-&gt;size
OG
id|max_dma
)paren
id|arena
op_assign
id|hose-&gt;sg_isa
suffix:semicolon
id|npages
op_assign
id|calc_npages
c_func
(paren
(paren
id|paddr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|size
)paren
suffix:semicolon
id|dma_ofs
op_assign
id|iommu_arena_alloc
c_func
(paren
id|arena
comma
id|npages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_ofs
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci_map_single failed: &quot;
l_string|&quot;could not allocate dma page tables&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|paddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|npages
suffix:semicolon
op_increment
id|i
comma
id|paddr
op_add_assign
id|PAGE_SIZE
)paren
id|arena-&gt;ptes
(braket
id|i
op_plus
id|dma_ofs
)braket
op_assign
id|mk_iommu_pte
c_func
(paren
id|paddr
)paren
suffix:semicolon
id|ret
op_assign
id|arena-&gt;dma_base
op_plus
id|dma_ofs
op_star
id|PAGE_SIZE
suffix:semicolon
id|ret
op_add_assign
(paren
r_int
r_int
)paren
id|cpu_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;pci_map_single: [%p,%lx] np %ld -&gt; sg %x from %p&bslash;n&quot;
comma
id|cpu_addr
comma
id|size
comma
id|npages
comma
id|ret
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Unmap a single streaming mode DMA translation.  The DMA_ADDR and&n;   SIZE must match what was provided for in a previous pci_map_single&n;   call.  All other usages are undefined.  After this call, reads by&n;   the cpu to the buffer are guarenteed to see whatever the device&n;   wrote there.  */
r_void
DECL|function|pci_unmap_single
id|pci_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|pci_controler
op_star
id|hose
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;sysdata
suffix:colon
id|pci_isa_hose
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
r_int
id|dma_ofs
comma
id|npages
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#if !DEBUG_NODIRECT
r_if
c_cond
(paren
id|dma_addr
op_ge
id|__direct_map_base
op_logical_and
id|dma_addr
OL
id|__direct_map_base
op_plus
id|__direct_map_size
)paren
(brace
multiline_comment|/* Nothing to do.  */
id|DBGA2
c_func
(paren
l_string|&quot;pci_unmap_single: direct [%x,%lx] from %p&bslash;n&quot;
comma
id|dma_addr
comma
id|size
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|arena
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arena
op_logical_or
id|dma_addr
OL
id|arena-&gt;dma_base
)paren
id|arena
op_assign
id|hose-&gt;sg_isa
suffix:semicolon
id|dma_ofs
op_assign
(paren
id|dma_addr
op_minus
id|arena-&gt;dma_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|dma_ofs
op_star
id|PAGE_SIZE
op_ge
id|arena-&gt;size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Bogus pci_unmap_single: dma_addr %x &quot;
l_string|&quot; base %x size %x&bslash;n&quot;
comma
id|dma_addr
comma
id|arena-&gt;dma_base
comma
id|arena-&gt;size
)paren
suffix:semicolon
r_return
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|npages
op_assign
id|calc_npages
c_func
(paren
(paren
id|dma_addr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|size
)paren
suffix:semicolon
id|iommu_arena_free
c_func
(paren
id|arena
comma
id|dma_ofs
comma
id|npages
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   If we&squot;re freeing ptes above the `next_entry&squot; pointer (they&n;           may have snuck back into the TLB since the last wrap flush),&n;           we need to flush the TLB before reallocating the latter.&n;&t;*/
r_if
c_cond
(paren
id|dma_ofs
op_ge
id|arena-&gt;next_entry
)paren
id|alpha_mv
dot
id|mv_pci_tbi
c_func
(paren
id|hose
comma
id|dma_addr
comma
id|dma_addr
op_plus
id|size
op_minus
l_int|1
)paren
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;pci_unmap_single: sg [%x,%lx] np %ld from %p&bslash;n&quot;
comma
id|dma_addr
comma
id|size
comma
id|npages
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate and map kernel buffer using consistent mode DMA for PCI&n;   device.  Returns non-NULL cpu-view pointer to the buffer if&n;   successful and sets *DMA_ADDRP to the pci side dma address as well,&n;   else DMA_ADDRP is undefined.  */
r_void
op_star
DECL|function|pci_alloc_consistent
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addrp
)paren
(brace
r_void
op_star
id|cpu_addr
suffix:semicolon
r_int
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
id|cpu_addr
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci_alloc_consistent: &quot;
l_string|&quot;get_free_pages failed from %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* ??? Really atomic allocation?  Otherwise we could play&n;&t;&t;   with vmalloc and sg if we can&squot;t find contiguous memory.  */
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cpu_addr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
op_star
id|dma_addrp
op_assign
id|pci_map_single
c_func
(paren
id|pdev
comma
id|cpu_addr
comma
id|size
comma
id|PCI_DMA_BIDIRECTIONAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dma_addrp
op_eq
l_int|0
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|cpu_addr
comma
id|order
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|DBGA2
c_func
(paren
l_string|&quot;pci_alloc_consistent: %lx -&gt; [%p,%x] from %p&bslash;n&quot;
comma
id|size
comma
id|cpu_addr
comma
op_star
id|dma_addrp
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|cpu_addr
suffix:semicolon
)brace
multiline_comment|/* Free and unmap a consistent DMA buffer.  CPU_ADDR and DMA_ADDR must&n;   be values that were returned from pci_alloc_consistent.  SIZE must&n;   be the same as what as passed into pci_alloc_consistent.&n;   References to the memory and mappings assosciated with CPU_ADDR or&n;   DMA_ADDR past this call are illegal.  */
r_void
DECL|function|pci_free_consistent
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|size
comma
r_void
op_star
id|cpu_addr
comma
id|dma_addr_t
id|dma_addr
)paren
(brace
id|pci_unmap_single
c_func
(paren
id|pdev
comma
id|dma_addr
comma
id|size
comma
id|PCI_DMA_BIDIRECTIONAL
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|cpu_addr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
id|DBGA2
c_func
(paren
l_string|&quot;pci_free_consistent: [%x,%lx] from %p&bslash;n&quot;
comma
id|dma_addr
comma
id|size
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Classify the elements of the scatterlist.  Write dma_address&n;   of each element with:&n;&t;0   : Followers all physically adjacent.&n;&t;1   : Followers all virtually adjacent.&n;&t;-1  : Not leader, physically adjacent to previous.&n;&t;-2  : Not leader, virtually adjacent to previous.&n;   Write dma_length of each leader with the combined lengths of&n;   the mergable followers.  */
r_static
r_inline
r_void
DECL|function|sg_classify
id|sg_classify
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_struct
id|scatterlist
op_star
id|end
comma
r_int
id|virt_ok
)paren
(brace
r_int
r_int
id|next_vaddr
suffix:semicolon
r_struct
id|scatterlist
op_star
id|leader
suffix:semicolon
r_int
id|leader_flag
comma
id|leader_length
suffix:semicolon
id|leader
op_assign
id|sg
suffix:semicolon
id|leader_flag
op_assign
l_int|0
suffix:semicolon
id|leader_length
op_assign
id|leader-&gt;length
suffix:semicolon
id|next_vaddr
op_assign
(paren
r_int
r_int
)paren
id|leader-&gt;address
op_plus
id|leader_length
suffix:semicolon
r_for
c_loop
(paren
op_increment
id|sg
suffix:semicolon
id|sg
OL
id|end
suffix:semicolon
op_increment
id|sg
)paren
(brace
r_int
r_int
id|addr
comma
id|len
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|sg-&gt;address
suffix:semicolon
id|len
op_assign
id|sg-&gt;length
suffix:semicolon
r_if
c_cond
(paren
id|next_vaddr
op_eq
id|addr
)paren
(brace
id|sg-&gt;dma_address
op_assign
op_minus
l_int|1
suffix:semicolon
id|leader_length
op_add_assign
id|len
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|next_vaddr
op_or
id|addr
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_eq
l_int|0
op_logical_and
id|virt_ok
)paren
(brace
id|sg-&gt;dma_address
op_assign
op_minus
l_int|2
suffix:semicolon
id|leader_flag
op_assign
l_int|1
suffix:semicolon
id|leader_length
op_add_assign
id|len
suffix:semicolon
)brace
r_else
(brace
id|leader-&gt;dma_address
op_assign
id|leader_flag
suffix:semicolon
id|leader-&gt;dma_length
op_assign
id|leader_length
suffix:semicolon
id|leader
op_assign
id|sg
suffix:semicolon
id|leader_flag
op_assign
l_int|0
suffix:semicolon
id|leader_length
op_assign
id|len
suffix:semicolon
)brace
id|next_vaddr
op_assign
id|addr
op_plus
id|len
suffix:semicolon
)brace
id|leader-&gt;dma_address
op_assign
id|leader_flag
suffix:semicolon
id|leader-&gt;dma_length
op_assign
id|leader_length
suffix:semicolon
)brace
multiline_comment|/* Given a scatterlist leader, choose an allocation method and fill&n;   in the blanks.  */
r_static
r_inline
r_int
DECL|function|sg_fill
id|sg_fill
c_func
(paren
r_struct
id|scatterlist
op_star
id|leader
comma
r_struct
id|scatterlist
op_star
id|end
comma
r_struct
id|scatterlist
op_star
id|out
comma
r_struct
id|pci_iommu_arena
op_star
id|arena
comma
id|dma_addr_t
id|max_dma
)paren
(brace
r_int
r_int
id|paddr
op_assign
id|virt_to_phys
c_func
(paren
id|leader-&gt;address
)paren
suffix:semicolon
r_int
id|size
op_assign
id|leader-&gt;dma_length
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
r_int
r_int
op_star
id|ptes
suffix:semicolon
r_int
id|npages
comma
id|dma_ofs
comma
id|i
suffix:semicolon
macro_line|#if !DEBUG_NODIRECT
multiline_comment|/* If everything is physically contiguous, and the addresses&n;&t;   fall into the direct-map window, use it.  */
r_if
c_cond
(paren
id|leader-&gt;dma_address
op_eq
l_int|0
op_logical_and
id|paddr
op_plus
id|size
op_plus
id|__direct_map_base
op_minus
l_int|1
op_le
id|max_dma
op_logical_and
id|paddr
op_plus
id|size
op_le
id|__direct_map_size
)paren
(brace
id|out-&gt;dma_address
op_assign
id|paddr
op_plus
id|__direct_map_base
suffix:semicolon
id|out-&gt;dma_length
op_assign
id|size
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;    sg_fill: [%p,%lx] -&gt; direct %x&bslash;n&quot;
comma
id|leader-&gt;address
comma
id|size
comma
id|out-&gt;dma_address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Otherwise, we&squot;ll use the iommu to make the pages virtually&n;&t;   contiguous.  */
id|paddr
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
id|npages
op_assign
id|calc_npages
c_func
(paren
id|paddr
op_plus
id|size
)paren
suffix:semicolon
id|dma_ofs
op_assign
id|iommu_arena_alloc
c_func
(paren
id|arena
comma
id|npages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_ofs
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|out-&gt;dma_address
op_assign
id|arena-&gt;dma_base
op_plus
id|dma_ofs
op_star
id|PAGE_SIZE
op_plus
id|paddr
suffix:semicolon
id|out-&gt;dma_length
op_assign
id|size
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;    sg_fill: [%p,%lx] -&gt; sg %x np %ld&bslash;n&quot;
comma
id|leader-&gt;address
comma
id|size
comma
id|out-&gt;dma_address
comma
id|npages
)paren
suffix:semicolon
multiline_comment|/* All virtually contiguous.  We need to find the length of each&n;&t;   physically contiguous subsegment to fill in the ptes.  */
id|ptes
op_assign
op_amp
id|arena-&gt;ptes
(braket
id|dma_ofs
)braket
suffix:semicolon
id|sg
op_assign
id|leader
suffix:semicolon
r_do
(brace
macro_line|#if DEBUG_ALLOC &gt; 0
r_struct
id|scatterlist
op_star
id|last_sg
op_assign
id|sg
suffix:semicolon
macro_line|#endif
id|size
op_assign
id|sg-&gt;length
suffix:semicolon
id|paddr
op_assign
id|virt_to_phys
c_func
(paren
id|sg-&gt;address
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sg
op_plus
l_int|1
OL
id|end
op_logical_and
(paren
r_int
)paren
id|sg
(braket
l_int|1
)braket
dot
id|dma_address
op_eq
op_minus
l_int|1
)paren
(brace
id|size
op_add_assign
id|sg
(braket
l_int|1
)braket
dot
id|length
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
id|npages
op_assign
id|calc_npages
c_func
(paren
(paren
id|paddr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|size
)paren
suffix:semicolon
id|paddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|npages
suffix:semicolon
op_increment
id|i
comma
id|paddr
op_add_assign
id|PAGE_SIZE
)paren
op_star
id|ptes
op_increment
op_assign
id|mk_iommu_pte
c_func
(paren
id|paddr
)paren
suffix:semicolon
macro_line|#if DEBUG_ALLOC &gt; 0
id|DBGA
c_func
(paren
l_string|&quot;    (%ld) [%p,%x] np %ld&bslash;n&quot;
comma
id|last_sg
op_minus
id|leader
comma
id|last_sg-&gt;address
comma
id|last_sg-&gt;length
comma
id|npages
)paren
suffix:semicolon
r_while
c_loop
(paren
op_increment
id|last_sg
op_le
id|sg
)paren
(brace
id|DBGA
c_func
(paren
l_string|&quot;        (%ld) [%p,%x] cont&bslash;n&quot;
comma
id|last_sg
op_minus
id|leader
comma
id|last_sg-&gt;address
comma
id|last_sg-&gt;length
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_while
c_loop
(paren
op_increment
id|sg
OL
id|end
op_logical_and
(paren
r_int
)paren
id|sg-&gt;dma_address
OL
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|pci_map_sg
id|pci_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_struct
id|scatterlist
op_star
id|start
comma
op_star
id|end
comma
op_star
id|out
suffix:semicolon
r_struct
id|pci_controler
op_star
id|hose
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
id|dma_addr_t
id|max_dma
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fast path single entry scatterlists.  */
r_if
c_cond
(paren
id|nents
op_eq
l_int|1
)paren
(brace
id|sg-&gt;dma_length
op_assign
id|sg-&gt;length
suffix:semicolon
id|sg-&gt;dma_address
op_assign
id|pci_map_single
c_func
(paren
id|pdev
comma
id|sg-&gt;address
comma
id|sg-&gt;length
comma
id|direction
)paren
suffix:semicolon
r_return
id|sg-&gt;dma_address
op_ne
l_int|0
suffix:semicolon
)brace
id|start
op_assign
id|sg
suffix:semicolon
id|end
op_assign
id|sg
op_plus
id|nents
suffix:semicolon
multiline_comment|/* First, prepare information about the entries.  */
id|sg_classify
c_func
(paren
id|sg
comma
id|end
comma
id|alpha_mv.mv_pci_tbi
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Second, figure out where we&squot;re going to map things.  */
r_if
c_cond
(paren
id|alpha_mv.mv_pci_tbi
)paren
(brace
id|hose
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;sysdata
suffix:colon
id|pci_isa_hose
suffix:semicolon
id|max_dma
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;dma_mask
suffix:colon
l_int|0x00ffffff
suffix:semicolon
id|arena
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arena
op_logical_or
id|arena-&gt;dma_base
op_plus
id|arena-&gt;size
OG
id|max_dma
)paren
id|arena
op_assign
id|hose-&gt;sg_isa
suffix:semicolon
)brace
r_else
(brace
id|max_dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|arena
op_assign
l_int|NULL
suffix:semicolon
id|hose
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Third, iterate over the scatterlist leaders and allocate&n;&t;   dma space as needed.  */
r_for
c_loop
(paren
id|out
op_assign
id|sg
suffix:semicolon
id|sg
OL
id|end
suffix:semicolon
op_increment
id|sg
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|sg-&gt;dma_address
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sg_fill
c_func
(paren
id|sg
comma
id|end
comma
id|out
comma
id|arena
comma
id|max_dma
)paren
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|out
op_increment
suffix:semicolon
)brace
multiline_comment|/* Mark the end of the list for pci_unmap_sg.  */
r_if
c_cond
(paren
id|out
OL
id|end
)paren
id|out-&gt;dma_length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|out
op_minus
id|start
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci_map_sg failed: no entries?&bslash;n&quot;
)paren
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;pci_map_sg: %ld entries&bslash;n&quot;
comma
id|out
op_minus
id|start
)paren
suffix:semicolon
r_return
id|out
op_minus
id|start
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci_map_sg failed: &quot;
l_string|&quot;could not allocate dma page tables&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Some allocation failed while mapping the scatterlist&n;&t;   entries.  Unmap them now.  */
r_if
c_cond
(paren
id|out
OG
id|start
)paren
id|pci_unmap_sg
c_func
(paren
id|pdev
comma
id|start
comma
id|out
op_minus
id|start
comma
id|direction
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Unmap a set of streaming mode DMA translations.  Again, cpu read&n;   rules concerning calls here are the same as for pci_unmap_single()&n;   above.  */
r_void
DECL|function|pci_unmap_sg
id|pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_struct
id|pci_controler
op_star
id|hose
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
r_struct
id|scatterlist
op_star
id|end
suffix:semicolon
id|dma_addr_t
id|max_dma
suffix:semicolon
id|dma_addr_t
id|fbeg
comma
id|fend
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_mv.mv_pci_tbi
)paren
r_return
suffix:semicolon
id|hose
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;sysdata
suffix:colon
id|pci_isa_hose
suffix:semicolon
id|max_dma
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;dma_mask
suffix:colon
l_int|0x00ffffff
suffix:semicolon
id|arena
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arena
op_logical_or
id|arena-&gt;dma_base
op_plus
id|arena-&gt;size
OG
id|max_dma
)paren
id|arena
op_assign
id|hose-&gt;sg_isa
suffix:semicolon
id|fbeg
op_assign
op_minus
l_int|1
comma
id|fend
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|end
op_assign
id|sg
op_plus
id|nents
suffix:semicolon
id|sg
OL
id|end
suffix:semicolon
op_increment
id|sg
)paren
(brace
r_int
r_int
id|addr
comma
id|size
suffix:semicolon
r_int
id|npages
comma
id|ofs
suffix:semicolon
id|dma_addr_t
id|tend
suffix:semicolon
id|addr
op_assign
id|sg-&gt;dma_address
suffix:semicolon
id|size
op_assign
id|sg-&gt;dma_length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_break
suffix:semicolon
macro_line|#if !DEBUG_NODIRECT
r_if
c_cond
(paren
id|addr
op_ge
id|__direct_map_base
op_logical_and
id|addr
OL
id|__direct_map_base
op_plus
id|__direct_map_size
)paren
(brace
multiline_comment|/* Nothing to do.  */
id|DBGA
c_func
(paren
l_string|&quot;    (%ld) direct [%lx,%lx]&bslash;n&quot;
comma
id|sg
op_minus
id|end
op_plus
id|nents
comma
id|addr
comma
id|size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
id|DBGA
c_func
(paren
l_string|&quot;    (%ld) sg [%lx,%lx]&bslash;n&quot;
comma
id|sg
op_minus
id|end
op_plus
id|nents
comma
id|addr
comma
id|size
)paren
suffix:semicolon
id|npages
op_assign
id|calc_npages
c_func
(paren
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|size
)paren
suffix:semicolon
id|ofs
op_assign
(paren
id|addr
op_minus
id|arena-&gt;dma_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_arena_free
c_func
(paren
id|arena
comma
id|ofs
comma
id|npages
)paren
suffix:semicolon
id|tend
op_assign
id|addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fbeg
OG
id|addr
)paren
id|fbeg
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|fend
OL
id|tend
)paren
id|fend
op_assign
id|tend
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   If we&squot;re freeing ptes above the `next_entry&squot; pointer (they&n;           may have snuck back into the TLB since the last wrap flush),&n;           we need to flush the TLB before reallocating the latter.&n;&t;*/
r_if
c_cond
(paren
(paren
id|fend
op_minus
id|arena-&gt;dma_base
)paren
op_rshift
id|PAGE_SHIFT
op_ge
id|arena-&gt;next_entry
)paren
id|alpha_mv
dot
id|mv_pci_tbi
c_func
(paren
id|hose
comma
id|fbeg
comma
id|fend
)paren
suffix:semicolon
id|DBGA
c_func
(paren
l_string|&quot;pci_unmap_sg: %d entries&bslash;n&quot;
comma
id|nents
op_minus
(paren
id|end
op_minus
id|sg
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Return whether the given PCI device DMA address mask can be&n;   supported properly.  */
r_int
DECL|function|pci_dma_supported
id|pci_dma_supported
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma_addr_t
id|mask
)paren
(brace
r_struct
id|pci_controler
op_star
id|hose
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|arena
suffix:semicolon
macro_line|#if !DEBUG_NODIRECT
multiline_comment|/* If there exists a direct map, and the mask fits either&n;&t;   MAX_DMA_ADDRESS defined such that GFP_DMA does something&n;&t;   useful, or the total system memory as shifted by the&n;&t;   map base.  */
r_if
c_cond
(paren
id|__direct_map_size
op_ne
l_int|0
op_logical_and
(paren
id|__direct_map_base
op_plus
id|MAX_DMA_ADDRESS
op_minus
id|IDENT_ADDR
op_minus
l_int|1
op_le
id|mask
op_logical_or
id|__direct_map_base
op_plus
(paren
id|max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_minus
l_int|1
op_le
id|mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/* Check that we have a scatter-gather arena that fits.  */
id|hose
op_assign
id|pdev
ques
c_cond
id|pdev-&gt;sysdata
suffix:colon
id|pci_isa_hose
suffix:semicolon
id|arena
op_assign
id|hose-&gt;sg_isa
suffix:semicolon
r_if
c_cond
(paren
id|arena
op_logical_and
id|arena-&gt;dma_base
op_plus
id|arena-&gt;size
op_le
id|mask
)paren
r_return
l_int|1
suffix:semicolon
id|arena
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
id|arena
op_logical_and
id|arena-&gt;dma_base
op_plus
id|arena-&gt;size
op_le
id|mask
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
