macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward-declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t change this structure - ASM code&n; * relies on it.&n; */
DECL|struct|processor
r_extern
r_struct
id|processor
(brace
multiline_comment|/* MISC&n;&t; * get data abort address/flags&n;&t; */
DECL|member|_data_abort
r_void
(paren
op_star
id|_data_abort
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check for any bugs&n;&t; */
DECL|member|_check_bugs
r_void
(paren
op_star
id|_check_bugs
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up any processor specifics&n;&t; */
DECL|member|_proc_init
r_void
(paren
op_star
id|_proc_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable any processor specifics&n;&t; */
DECL|member|_proc_fin
r_void
(paren
op_star
id|_proc_fin
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Processor architecture specific&n;&t; */
multiline_comment|/* CACHE&n;&t; *&n;&t; * flush all caches&n;&t; */
DECL|member|_flush_cache_all
r_void
(paren
op_star
id|_flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush a specific page or pages&n;&t; */
DECL|member|_flush_cache_area
r_void
(paren
op_star
id|_flush_cache_area
)paren
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush cache entry for an address&n;&t; */
DECL|member|_flush_cache_entry
r_void
(paren
op_star
id|_flush_cache_entry
)paren
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * clean a virtual address range from the&n;&t; * D-cache without flushing the cache.&n;&t; */
DECL|member|_clean_cache_area
r_void
(paren
op_star
id|_clean_cache_area
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush a page to RAM&n;&t; */
DECL|member|_flush_ram_page
r_void
(paren
op_star
id|_flush_ram_page
)paren
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
multiline_comment|/* TLB&n;&t; *&n;&t; * flush all TLBs&n;&t; */
DECL|member|_flush_tlb_all
r_void
(paren
op_star
id|_flush_tlb_all
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush a specific TLB&n;&t; */
DECL|member|_flush_tlb_area
r_void
(paren
op_star
id|_flush_tlb_area
)paren
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the page table&n;&t; */
DECL|member|_set_pgd
r_void
(paren
op_star
id|_set_pgd
)paren
(paren
r_int
r_int
id|pgd_phys
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set a PMD (handling IMP bit 4)&n;&t; */
DECL|member|_set_pmd
r_void
(paren
op_star
id|_set_pmd
)paren
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pmd_t
id|pmd
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set a PTE&n;&t; */
DECL|member|_set_pte
r_void
(paren
op_star
id|_set_pte
)paren
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Special stuff for a reset&n;&t; */
DECL|member|reset
r_volatile
r_void
(paren
op_star
id|reset
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush an icached page&n;&t; */
DECL|member|_flush_icache_area
r_void
(paren
op_star
id|_flush_icache_area
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * write back dirty cached data&n;&t; */
DECL|member|_cache_wback_area
r_void
(paren
op_star
id|_cache_wback_area
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * purge cached data without (necessarily) writing it back&n;&t; */
DECL|member|_cache_purge_area
r_void
(paren
op_star
id|_cache_purge_area
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush a specific TLB&n;&t; */
DECL|member|_flush_tlb_page
r_void
(paren
op_star
id|_flush_tlb_page
)paren
(paren
r_int
r_int
id|address
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Idle the processor&n;&t; */
DECL|member|_do_idle
r_int
(paren
op_star
id|_do_idle
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * flush I cache for a page&n;&t; */
DECL|member|_flush_icache_page
r_void
(paren
op_star
id|_flush_icache_page
)paren
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
)brace
id|processor
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm6_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm7_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|sa110_processor_functions
suffix:semicolon
DECL|macro|cpu_data_abort
mdefine_line|#define cpu_data_abort(pc)&t;&t;&t;processor._data_abort(pc)
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs()&t;&t;&t;processor._check_bugs()
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init()&t;&t;&t;&t;processor._proc_init()
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin()&t;&t;&t;&t;processor._proc_fin()
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle()&t;&t;&t;&t;processor._do_idle()
DECL|macro|cpu_flush_cache_all
mdefine_line|#define cpu_flush_cache_all()&t;&t;&t;processor._flush_cache_all()
DECL|macro|cpu_flush_cache_area
mdefine_line|#define cpu_flush_cache_area(start,end,flags)&t;processor._flush_cache_area(start,end,flags)
DECL|macro|cpu_flush_cache_entry
mdefine_line|#define cpu_flush_cache_entry(addr)&t;&t;processor._flush_cache_entry(addr)
DECL|macro|cpu_clean_cache_area
mdefine_line|#define cpu_clean_cache_area(start,size)&t;processor._clean_cache_area(start,size)
DECL|macro|cpu_flush_ram_page
mdefine_line|#define cpu_flush_ram_page(page)&t;&t;processor._flush_ram_page(page)
DECL|macro|cpu_flush_tlb_all
mdefine_line|#define cpu_flush_tlb_all()&t;&t;&t;processor._flush_tlb_all()
DECL|macro|cpu_flush_tlb_area
mdefine_line|#define cpu_flush_tlb_area(start,end,flags)&t;processor._flush_tlb_area(start,end,flags)
DECL|macro|cpu_flush_tlb_page
mdefine_line|#define cpu_flush_tlb_page(addr,flags)&t;&t;processor._flush_tlb_page(addr,flags)
DECL|macro|cpu_set_pgd
mdefine_line|#define cpu_set_pgd(pgd)&t;&t;&t;processor._set_pgd(pgd)
DECL|macro|cpu_set_pmd
mdefine_line|#define cpu_set_pmd(pmdp, pmd)&t;&t;&t;processor._set_pmd(pmdp, pmd)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte(ptep, pte)&t;&t;&t;processor._set_pte(ptep, pte)
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset(addr)&t;&t;&t;&t;processor.reset(addr)
DECL|macro|cpu_flush_icache_area
mdefine_line|#define cpu_flush_icache_area(start,end)&t;processor._flush_icache_area(start,end)
DECL|macro|cpu_cache_wback_area
mdefine_line|#define cpu_cache_wback_area(start,end)&t;&t;processor._cache_wback_area(start,end)
DECL|macro|cpu_cache_purge_area
mdefine_line|#define cpu_cache_purge_area(start,end)&t;&t;processor._cache_purge_area(start,end)
DECL|macro|cpu_flush_icache_page
mdefine_line|#define cpu_flush_icache_page(virt)&t;&t;processor._flush_icache_page(virt)
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,tsk)&t;&t;&t;cpu_set_pgd(__virt_to_phys((unsigned long)(pgd)))
macro_line|#endif
eof
