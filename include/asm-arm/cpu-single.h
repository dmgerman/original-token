multiline_comment|/*&n; * Single CPU&n; */
macro_line|#ifdef __STDC__
DECL|macro|__cpu_fn
mdefine_line|#define __cpu_fn(name,x)&t;cpu_##name##x
macro_line|#else
DECL|macro|__cpu_fn
mdefine_line|#define __cpu_fn(name,x)&t;cpu_/**/name/**/x
macro_line|#endif
DECL|macro|cpu_fn
mdefine_line|#define cpu_fn(name,x)&t;&t;__cpu_fn(name,x)
multiline_comment|/*&n; * If we are supporting multiple CPUs, then&n; * we must use a table of function pointers&n; * for this lot.  Otherwise, we can optimise&n; * the table away.&n; */
DECL|macro|cpu_data_abort
mdefine_line|#define cpu_data_abort&t;&t;&t;cpu_fn(CPU_NAME,_data_abort)
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs&t;&t;&t;cpu_fn(CPU_NAME,_check_bugs)
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init&t;&t;&t;cpu_fn(CPU_NAME,_proc_init)
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin&t;&t;&t;cpu_fn(CPU_NAME,_proc_fin)
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle&t;&t;&t;cpu_fn(CPU_NAME,_do_idle)
DECL|macro|cpu_flush_cache_all
mdefine_line|#define cpu_flush_cache_all&t;&t;cpu_fn(CPU_NAME,_flush_cache_all)
DECL|macro|cpu_flush_cache_area
mdefine_line|#define cpu_flush_cache_area&t;&t;cpu_fn(CPU_NAME,_flush_cache_area)
DECL|macro|cpu_flush_cache_entry
mdefine_line|#define cpu_flush_cache_entry&t;&t;cpu_fn(CPU_NAME,_flush_cache_entry)
DECL|macro|cpu_clean_cache_area
mdefine_line|#define cpu_clean_cache_area&t;&t;cpu_fn(CPU_NAME,_clean_cache_area)
DECL|macro|cpu_flush_ram_page
mdefine_line|#define cpu_flush_ram_page&t;&t;cpu_fn(CPU_NAME,_flush_ram_page)
DECL|macro|cpu_flush_tlb_all
mdefine_line|#define cpu_flush_tlb_all&t;&t;cpu_fn(CPU_NAME,_flush_tlb_all)
DECL|macro|cpu_flush_tlb_area
mdefine_line|#define cpu_flush_tlb_area&t;&t;cpu_fn(CPU_NAME,_flush_tlb_area)
DECL|macro|cpu_flush_tlb_page
mdefine_line|#define cpu_flush_tlb_page&t;&t;cpu_fn(CPU_NAME,_flush_tlb_page)
DECL|macro|cpu_set_pgd
mdefine_line|#define cpu_set_pgd&t;&t;&t;cpu_fn(CPU_NAME,_set_pgd)
DECL|macro|cpu_set_pmd
mdefine_line|#define cpu_set_pmd&t;&t;&t;cpu_fn(CPU_NAME,_set_pmd)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte&t;&t;&t;cpu_fn(CPU_NAME,_set_pte)
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset&t;&t;&t;cpu_fn(CPU_NAME,_reset)
DECL|macro|cpu_flush_icache_area
mdefine_line|#define cpu_flush_icache_area&t;&t;cpu_fn(CPU_NAME,_flush_icache_area)
DECL|macro|cpu_cache_wback_area
mdefine_line|#define cpu_cache_wback_area&t;&t;cpu_fn(CPU_NAME,_cache_wback_area)
DECL|macro|cpu_cache_purge_area
mdefine_line|#define cpu_cache_purge_area&t;&t;cpu_fn(CPU_NAME,_cache_purge_area)
DECL|macro|cpu_flush_icache_page
mdefine_line|#define cpu_flush_icache_page&t;&t;cpu_fn(CPU_NAME,_flush_icache_page)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* declare all the functions as extern */
r_extern
r_void
id|cpu_data_abort
c_func
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
r_extern
r_void
id|cpu_check_bugs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_proc_fin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpu_do_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_flush_cache_area
c_func
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
r_extern
r_void
id|cpu_flush_cache_entry
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|cpu_clean_cache_area
c_func
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
r_extern
r_void
id|cpu_flush_ram_page
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|cpu_flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_flush_tlb_area
c_func
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
r_extern
r_void
id|cpu_flush_tlb_page
c_func
(paren
r_int
r_int
id|address
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pgd
c_func
(paren
r_int
r_int
id|pgd_phys
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pmd
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pmd_t
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
r_extern
r_volatile
r_void
id|cpu_reset
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|cpu_flush_icache_area
c_func
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
r_extern
r_void
id|cpu_cache_wback_area
c_func
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
r_extern
r_void
id|cpu_cache_purge_area
c_func
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
r_extern
r_void
id|cpu_flush_icache_page
c_func
(paren
r_int
r_int
id|virt
)paren
suffix:semicolon
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,tsk) cpu_set_pgd(__virt_to_phys((unsigned long)(pgd)))
macro_line|#endif
eof
