macro_line|#ifndef __SPARC64_PCI_H
DECL|macro|__SPARC64_PCI_H
mdefine_line|#define __SPARC64_PCI_H
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n; * already-configured bus numbers - to be used for buggy BIOSes&n; * or architectures with incomplete PCI setup by the loader.&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
multiline_comment|/* Map kernel buffer using consistant mode DMA for PCI device.&n; * Returns a 32-bit PCI DMA address.&n; */
r_extern
id|u32
id|pci_map_consistant
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Unmap a consistant DMA translation. */
r_extern
r_void
id|pci_unmap_consistant
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
multiline_comment|/* Map a single buffer for PCI DMA in streaming mode. */
r_extern
id|u32
id|pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Unmap a single streaming mode DMA translation. */
r_extern
r_void
id|pci_unmap_single
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
multiline_comment|/* Map a set of buffers described by scatterlist in streaming&n; * mode for PCI DMA.&n; */
r_extern
r_void
id|pci_map_sg
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
multiline_comment|/* Unmap a set of streaming mode DMA translations. */
r_extern
r_void
id|pci_unmap_sg
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
multiline_comment|/* Make physical memory consistant for a single&n; * streaming mode DMA translation after a transfer.&n; */
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
multiline_comment|/* Make physical memory consistant for a set of streaming&n; * mode DMA translations after a transfer.&n; */
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
