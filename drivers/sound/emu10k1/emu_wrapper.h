macro_line|#ifndef __EMU_WRAPPER_H
DECL|macro|__EMU_WRAPPER_H
mdefine_line|#define __EMU_WRAPPER_H
macro_line|#include &lt;linux/wrapper.h&gt;
DECL|macro|PCI_SET_DMA_MASK
mdefine_line|#define PCI_SET_DMA_MASK(pdev,mask)        (((pdev)-&gt;dma_mask) = (mask))
macro_line|#ifndef PCI_GET_DRIVER_DATA
DECL|macro|PCI_GET_DRIVER_DATA
mdefine_line|#define PCI_GET_DRIVER_DATA(pdev)             ((pdev)-&gt;driver_data)
DECL|macro|PCI_SET_DRIVER_DATA
mdefine_line|#define PCI_SET_DRIVER_DATA(pdev,data)        (((pdev)-&gt;driver_data) = (data))
macro_line|#endif /* PCI_GET_DRIVER_DATA */
macro_line|#endif
eof
