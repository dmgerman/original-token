multiline_comment|/* $Id: andes.c,v 1.1 1997/06/06 09:34:31 ralf Exp $&n; * andes.c: MMU and cache operations for the R10000 (ANDES).&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
r_extern
r_int
r_int
id|mips_tlb_entries
suffix:semicolon
multiline_comment|/* Cache operations. XXX Write these dave... */
DECL|function|andes_flush_cache_all
r_static
r_inline
r_void
id|andes_flush_cache_all
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_cache_mm
r_static
r_void
id|andes_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_cache_range
r_static
r_void
id|andes_flush_cache_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_cache_page
r_static
r_void
id|andes_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_page_to_ram
r_static
r_void
id|andes_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_cache_sigtramp
r_static
r_void
id|andes_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
multiline_comment|/* TLB operations. XXX Write these dave... */
DECL|function|andes_flush_tlb_all
r_static
r_inline
r_void
id|andes_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_tlb_mm
r_static
r_void
id|andes_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_tlb_range
r_static
r_void
id|andes_flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_flush_tlb_page
r_static
r_void
id|andes_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* XXX */
)brace
DECL|function|andes_load_pgd
r_static
r_void
id|andes_load_pgd
c_func
(paren
r_int
r_int
id|pg_dir
)paren
(brace
)brace
DECL|function|andes_pgd_init
r_static
r_void
id|andes_pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
(brace
)brace
DECL|function|ld_mmu_andes
r_void
id|ld_mmu_andes
c_func
(paren
r_void
)paren
(brace
id|flush_cache_all
op_assign
id|andes_flush_cache_all
suffix:semicolon
id|flush_cache_mm
op_assign
id|andes_flush_cache_mm
suffix:semicolon
id|flush_cache_range
op_assign
id|andes_flush_cache_range
suffix:semicolon
id|flush_cache_page
op_assign
id|andes_flush_cache_page
suffix:semicolon
id|flush_cache_sigtramp
op_assign
id|andes_flush_cache_sigtramp
suffix:semicolon
id|flush_page_to_ram
op_assign
id|andes_flush_page_to_ram
suffix:semicolon
id|flush_tlb_all
op_assign
id|andes_flush_tlb_all
suffix:semicolon
id|flush_tlb_mm
op_assign
id|andes_flush_tlb_mm
suffix:semicolon
id|flush_tlb_range
op_assign
id|andes_flush_tlb_range
suffix:semicolon
id|flush_tlb_page
op_assign
id|andes_flush_tlb_page
suffix:semicolon
id|load_pgd
op_assign
id|andes_load_pgd
suffix:semicolon
id|pgd_init
op_assign
id|andes_pgd_init
suffix:semicolon
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
eof