multiline_comment|/* dvma support routines */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sun3mmu.h&gt;
macro_line|#include &lt;asm/dvma.h&gt;
DECL|variable|dvma_next_free
r_int
r_int
id|dvma_next_free
op_assign
id|DVMA_START
suffix:semicolon
multiline_comment|/* get needed number of free dma pages, or panic if not enough */
DECL|function|sun3_dvma_malloc
r_void
op_star
id|sun3_dvma_malloc
c_func
(paren
r_int
id|len
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/* if the next free pages have been accessed, skip them */
r_while
c_loop
(paren
(paren
id|dvma_next_free
OL
id|DVMA_END
)paren
op_logical_and
(paren
id|sun3_get_pte
c_func
(paren
id|dvma_next_free
)paren
op_amp
id|SUN3_PAGE_ACCESSED
)paren
)paren
(brace
id|dvma_next_free
op_add_assign
id|SUN3_PTE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dvma_next_free
op_plus
id|len
)paren
OG
id|DVMA_END
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;sun3_dvma_malloc: out of dvma pages&quot;
)paren
suffix:semicolon
)brace
id|vaddr
op_assign
id|dvma_next_free
suffix:semicolon
id|dvma_next_free
op_assign
id|PAGE_ALIGN
c_func
(paren
id|dvma_next_free
op_plus
id|len
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|vaddr
suffix:semicolon
)brace
eof
