multiline_comment|/*&n; * High memory handling common code and variables.&n; *&n; * (C) 1999 Andrea Arcangeli, SuSE GmbH, andrea@suse.de&n; *          Gerhard Wichert, Siemens AG, Gerhard.Wichert@pdb.siemens.de&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with&n; * 64-bit physical space. With current x86 CPUs this&n; * means up to 64 Gigabytes physical RAM.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
DECL|variable|highmem_mapnr
r_int
r_int
id|highmem_mapnr
suffix:semicolon
DECL|variable|nr_free_highpages
r_int
r_int
id|nr_free_highpages
op_assign
l_int|0
suffix:semicolon
DECL|function|prepare_highmem_swapout
r_struct
id|page
op_star
id|prepare_highmem_swapout
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|regular_page
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/*&n;&t; * If this is a highmem page so it can&squot;t be swapped out directly&n;&t; * otherwise the b_data buffer addresses will break&n;&t; * the lowlevel device drivers.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
id|page
suffix:semicolon
id|regular_page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|regular_page
)paren
r_return
l_int|NULL
suffix:semicolon
id|vaddr
op_assign
id|kmap
c_func
(paren
id|page
comma
id|KM_READ
)paren
suffix:semicolon
id|copy_page
c_func
(paren
(paren
r_void
op_star
)paren
id|regular_page
comma
(paren
r_void
op_star
)paren
id|vaddr
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|vaddr
comma
id|KM_READ
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ok, we can just forget about our highmem page since &n;&t; * we stored its data into the new regular_page.&n;&t; */
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|regular_page
)paren
suffix:semicolon
)brace
DECL|function|replace_with_highmem
r_struct
id|page
op_star
id|replace_with_highmem
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|page
op_star
id|highpage
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
op_logical_or
op_logical_neg
id|nr_free_highpages
)paren
r_return
id|page
suffix:semicolon
id|highpage
op_assign
id|get_free_highpage
c_func
(paren
id|GFP_ATOMIC
op_or
id|__GFP_HIGHMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|highpage
)paren
r_return
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|highpage
)paren
)paren
(brace
id|__free_page
c_func
(paren
id|highpage
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
id|vaddr
op_assign
id|kmap
c_func
(paren
id|highpage
comma
id|KM_WRITE
)paren
suffix:semicolon
id|copy_page
c_func
(paren
(paren
r_void
op_star
)paren
id|vaddr
comma
(paren
r_void
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|vaddr
comma
id|KM_WRITE
)paren
suffix:semicolon
multiline_comment|/* Preserve the caching of the swap_entry. */
id|highpage-&gt;pg_offset
op_assign
id|page-&gt;pg_offset
suffix:semicolon
id|highpage-&gt;mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
multiline_comment|/*&n;&t; * We can just forget the old page since &n;&t; * we stored its data into the new highmem-page.&n;&t; */
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|highpage
suffix:semicolon
)brace
eof
