macro_line|#ifndef _LINUX_BOOTMEM_H
DECL|macro|_LINUX_BOOTMEM_H
mdefine_line|#define _LINUX_BOOTMEM_H
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; *  simple boot-time physical memory area allocator.&n; */
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|init_bootmem
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|memend
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|reserve_bootmem
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|free_bootmem
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__init
id|__alloc_bootmem
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|goal
)paren
suffix:semicolon
DECL|macro|alloc_bootmem
mdefine_line|#define alloc_bootmem(x) &bslash;&n;&t;__alloc_bootmem((x), SMP_CACHE_BYTES, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_pages
mdefine_line|#define alloc_bootmem_pages(x) &bslash;&n;&t;__alloc_bootmem((x), PAGE_SIZE, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_low_pages
mdefine_line|#define alloc_bootmem_low_pages(x) &bslash;&n;&t;__alloc_bootmem((x), PAGE_SIZE, 0)
r_extern
r_int
r_int
id|__init
id|free_all_bootmem
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_BOOTMEM_H */
eof
