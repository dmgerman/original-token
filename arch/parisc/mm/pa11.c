multiline_comment|/* $Id: pa11.c,v 1.1 1999/03/17 01:05:41 pjlahaie Exp $&n; *&n; * pa11.c: PA 1.1 specific mmu/cache code.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
r_extern
r_int
r_int
id|mips_tlb_entries
suffix:semicolon
multiline_comment|/* page functions */
DECL|function|pa11_clear_page
r_void
id|pa11_clear_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
)brace
DECL|function|pa11_copy_page
r_static
r_void
id|pa11_copy_page
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
)paren
(brace
)brace
multiline_comment|/* Cache operations. */
DECL|function|pa11_flush_cache_all
r_static
r_inline
r_void
id|pa11_flush_cache_all
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|pa11_flush_cache_mm
r_static
r_void
id|pa11_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
DECL|function|pa11_flush_cache_range
r_static
r_void
id|pa11_flush_cache_range
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
)brace
DECL|function|pa11_flush_cache_page
r_static
r_void
id|pa11_flush_cache_page
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
)brace
DECL|function|pa11_flush_page_to_ram
r_static
r_void
id|pa11_flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
(brace
)brace
DECL|function|pa11_flush_cache_sigtramp
r_static
r_void
id|pa11_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|page
)paren
(brace
)brace
multiline_comment|/* TLB operations. */
DECL|function|pa11_flush_tlb_all
r_static
r_inline
r_void
id|pa11_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|entry
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Here we will need to flush all the TLBs */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pa11_flush_tlb_mm
r_static
r_void
id|pa11_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* This is what the MIPS does..  Is it the right thing for PA-RISC? */
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
(brace
id|pa11_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|pa11_flush_tlb_range
r_static
r_void
id|pa11_flush_tlb_range
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
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
(brace
id|pa11_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|pa11_flush_tlb_page
r_static
r_void
id|pa11_flush_tlb_page
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
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
(brace
id|pa11_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|pa11_load_pgd
r_static
r_void
id|pa11_load_pgd
c_func
(paren
r_int
r_int
id|pg_dir
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* We need to do the right thing here */
)brace
multiline_comment|/*&n; * Initialize new page directory with pointers to invalid ptes&n; */
DECL|function|pa11_pgd_init
r_static
r_void
id|pa11_pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|dummy1
comma
id|dummy2
suffix:semicolon
)brace
DECL|function|pa11_update_mmu_cache
r_static
r_void
id|pa11_update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
id|pa11_flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pa11_show_regs
r_static
r_void
id|pa11_show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Saved main processor registers&n;&t; */
id|printk
c_func
(paren
l_string|&quot;$0 : %08x %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
l_int|0
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|2
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|3
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|4
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|5
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|6
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$8 : %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|8
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|9
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|10
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|11
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|12
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|13
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|14
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$16: %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|16
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|17
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|18
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|19
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|20
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|21
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|22
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|23
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;$24: %08lx %08lx                   %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|24
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|25
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|28
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|30
)braket
comma
(paren
r_int
r_int
)paren
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Saved cp0 registers&n;&t; */
id|printk
c_func
(paren
l_string|&quot;epc  : %08lx&bslash;nStatus: %08x&bslash;nCause : %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_epc
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_status
comma
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_cause
)paren
suffix:semicolon
)brace
DECL|function|pa11_user_mode
r_static
r_int
id|pa11_user_mode
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Return user mode stuff?? */
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|ld_mmu_pa11
c_func
(paren
r_void
)paren
)paren
(brace
multiline_comment|/* Taken directly from the MIPS arch..  Lots of bad things here */
id|clear_page
op_assign
id|pa11_clear_page
suffix:semicolon
id|copy_page
op_assign
id|pa11_copy_page
suffix:semicolon
id|flush_cache_all
op_assign
id|pa11_flush_cache_all
suffix:semicolon
id|flush_cache_mm
op_assign
id|pa11_flush_cache_mm
suffix:semicolon
id|flush_cache_range
op_assign
id|pa11_flush_cache_range
suffix:semicolon
id|flush_cache_page
op_assign
id|pa11_flush_cache_page
suffix:semicolon
id|flush_cache_sigtramp
op_assign
id|pa11_flush_cache_sigtramp
suffix:semicolon
id|flush_page_to_ram
op_assign
id|pa11_flush_page_to_ram
suffix:semicolon
id|flush_tlb_all
op_assign
id|pa11_flush_tlb_all
suffix:semicolon
id|flush_tlb_mm
op_assign
id|pa11_flush_tlb_mm
suffix:semicolon
id|flush_tlb_range
op_assign
id|pa11_flush_tlb_range
suffix:semicolon
id|flush_tlb_page
op_assign
id|pa11_flush_tlb_page
suffix:semicolon
id|pa11_asid_setup
c_func
(paren
)paren
suffix:semicolon
id|load_pgd
op_assign
id|pa11_load_pgd
suffix:semicolon
id|pgd_init
op_assign
id|pa11_pgd_init
suffix:semicolon
id|update_mmu_cache
op_assign
id|pa11_update_mmu_cache
suffix:semicolon
id|show_regs
op_assign
id|pa11_show_regs
suffix:semicolon
id|add_wired_entry
op_assign
id|pa11_add_wired_entry
suffix:semicolon
id|user_mode
op_assign
id|pa11_user_mode
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
eof
