macro_line|#ifndef __SPARC64_PCI_H
DECL|macro|__SPARC64_PCI_H
mdefine_line|#define __SPARC64_PCI_H
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n; * already-configured bus numbers - to be used for buggy BIOSes&n; * or architectures with incomplete PCI setup by the loader.&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0UL
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0UL
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* Allocate and map kernel buffer using consistant mode DMA for PCI device.&n; * Returns non-NULL cpu-view pointer to the buffer if successful and&n; * sets *dma_addrp to the pci side dma address as well, else *dma_addrp&n; * is undefined.&n; */
r_extern
r_void
op_star
id|pci_alloc_consistant
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
id|u32
op_star
id|dma_addrp
)paren
suffix:semicolon
multiline_comment|/* Free and unmap a consistant DMA buffer.&n; * cpu_addr is what was returned from pci_alloc_consistant,&n; * size must be the same as what as passed into pci_alloc_consistant,&n; * and likewise dma_addr must be the same as what *dma_addrp was set to.&n; *&n; * References to the memory and mappings assosciated with cpu_addr/dma_addr&n; * past this call are illegal.&n; */
r_extern
r_void
id|pci_free_consistant
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
id|u32
id|dma_addr
)paren
suffix:semicolon
multiline_comment|/* Map a single buffer of the indicate size for PCI DMA in streaming mode.&n; * The 32-bit PCI bus mastering address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_sync_single is performed.&n; */
r_extern
id|u32
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
id|buffer
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Unmap a single streaming mode DMA translation.  The dma_addr and size&n; * must match what was provided for in a previous pci_map_single call.  All&n; * other usages are undefined.&n; *&n; * After this call, reads by the cpu to the buffer are guarenteed to see&n; * whatever the device wrote there.&n; */
r_extern
r_void
id|pci_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|u32
id|dma_addr
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Map a set of buffers described by scatterlist in streaming&n; * mode for PCI DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate PCI dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *&t; The routine returns the number of addr/length pairs actually&n; *&t; used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
r_extern
r_int
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
)paren
suffix:semicolon
multiline_comment|/* Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
r_extern
r_void
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
)paren
suffix:semicolon
multiline_comment|/* Make physical memory consistant for a single&n; * streaming mode DMA translation after a transfer.&n; *&n; * If you perform a pci_map_single() but wish to interrogate the&n; * buffer using the cpu, yet do not wish to teardown the PCI dma&n; * mapping, you must call this function before doing so.  At the&n; * next point you give the PCI dma address back to the card, the&n; * device again owns the buffer.&n; */
r_extern
r_void
id|pci_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|u32
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Make physical memory consistant for a set of streaming&n; * mode DMA translations after a transfer.&n; *&n; * The same as pci_dma_sync_single but for a scatter-gather list,&n; * same rules and usage.&n; */
r_extern
r_void
id|pci_dma_sync_sg
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __SPARC64_PCI_H */
eof
