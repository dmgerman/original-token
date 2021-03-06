multiline_comment|/*&n; * Copyright (C) 2000   Ani Joshi &lt;ajoshi@unixbox.com&gt;&n; *&n; *&n; * Dynamic DMA mapping support.&n; *&n; * swiped from i386, and cloned for MIPS by Geert.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|pci_alloc_consistent
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_int
id|gfp
op_assign
id|GFP_ATOMIC
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
op_logical_or
id|hwdev-&gt;dma_mask
op_ne
l_int|0xffffffff
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|gfp
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
id|virt_to_bus
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pci_free_consistent
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
eof
